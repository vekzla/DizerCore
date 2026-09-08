#include "HousingManager.h"
#include "Player.h"
#include "WorldSession.h"
#include "Database/DatabaseEnv.h"
#include "World.h"
#include <algorithm>

HousingManager* HousingManager::instance()
{
    static HousingManager instance;
    return &instance;
}

HousingManager::HousingManager() { }

HousingManager::~HousingManager() { }

bool HousingManager::PurchasePlot(Player* player, uint32 neighborhoodId, uint32 plotId, uint32 houseTemplateId)
{
    if (!player)
        return false;

    // Check if player is already at max houses
    if (GetPlayerHouseCount(player->GetGUID().GetCounter()) >= GetMaxHousesPerPlayer())
    {
        player->SendSystemMessage("You have reached the maximum number of houses you can own");
        return false;
    }

    // Check if plot is available
    if (!CheckPlotAvailability(plotId))
    {
        player->SendSystemMessage("This plot is no longer available");
        return false;
    }

    // Check purchase cooldown
    if (!CanPlayerPurchaseHouse(player->GetGUID().GetCounter()))
    {
        player->SendSystemMessage("You must wait before purchasing another house");
        return false;
    }

    // Get house cost
    HousingCost cost = GetHouseCost(houseTemplateId);
    
    // Validate resources
    if (!ValidatePurchaseCost(player, cost))
    {
        player->SendSystemMessage("You do not have enough gold to purchase this house");
        return false;
    }

    if (!ValidateResourceRequirements(player, houseTemplateId))
    {
        player->SendSystemMessage("You do not meet the requirements for this house");
        return false;
    }

    // Begin transaction
    BeginHousingTransaction(player->GetGUID().GetCounter());

    // Lock the plot
    if (!LockPlot(plotId, player->GetGUID().GetCounter()))
    {
        RollbackHousingTransaction(player->GetGUID().GetCounter());
        player->SendSystemMessage("Failed to acquire plot lock. Please try again.");
        return false;
    }

    // Deduct costs
    if (!DeductPurchaseCost(player, cost))
    {
        RollbackHousingTransaction(player->GetGUID().GetCounter());
        UnlockPlot(plotId);
        player->SendSystemMessage("Transaction failed. Gold not deducted.");
        return false;
    }

    // Update plot in database
    HousingPlot plot;
    plot.plotId = plotId;
    plot.neighborhoodId = neighborhoodId;
    plot.ownerId = player->GetGUID().GetCounter();
    plot.ownerAccountId = player->GetSession()->GetAccountId();
    plot.houseTemplateId = houseTemplateId;
    plot.isAvailable = false;
    plot.purchaseDate = time(nullptr);
    plot.lastAccessDate = time(nullptr);

    if (!SavePlotData(plot))
    {
        RollbackHousingTransaction(player->GetGUID().GetCounter());
        UnlockPlot(plotId);
        player->SendSystemMessage("Failed to save house data. Purchase cancelled.");
        return false;
    }

    // Grant owner permission
    if (!GrantPermission(player->GetGUID().GetCounter(), plotId, 3)) // Level 3 = owner
    {
        RollbackHousingTransaction(player->GetGUID().GetCounter());
        UnlockPlot(plotId);
        player->SendSystemMessage("Failed to grant ownership permissions.");
        return false;
    }

    // Commit transaction
    CommitHousingTransaction(player->GetGUID().GetCounter());
    UnlockPlot(plotId);

    // Cache update
    CachePlotData(plotId);

    player->SendSystemMessage("House purchased successfully!");
    return true;
}

bool HousingManager::CheckPlotAvailability(uint32 plotId)
{
    auto itr = m_plotCache.find(plotId);
    if (itr != m_plotCache.end())
        return itr->second.isAvailable;

    // Query database
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_HOUSING_PLOT_AVAILABLE);
    stmt->setUInt32(0, plotId);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);
    
    if (result)
    {
        Field* fields = result->Fetch();
        return fields[0].GetBool();
    }

    return false;
}

bool HousingManager::ReleasePlot(uint32 plotId)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_HOUSING_PLOT_RELEASE);
    stmt->setUInt32(0, plotId);
    CharacterDatabase.Execute(stmt);

    InvalidatePlotCache(plotId);
    return true;
}

bool HousingManager::TransferPlotOwnership(uint32 plotId, uint32 newOwnerId)
{
    if (!LockPlot(plotId, newOwnerId))
        return false;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_HOUSING_PLOT_OWNER);
    stmt->setUInt32(0, newOwnerId);
    stmt->setUInt32(1, plotId);
    CharacterDatabase.Execute(stmt);

    InvalidatePlotCache(plotId);
    UnlockPlot(plotId);
    return true;
}

bool HousingManager::GrantPermission(uint32 playerId, uint32 houseId, uint8 permissionLevel)
{
    if (permissionLevel > 3)
        return false;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_HOUSING_PERMISSION);
    stmt->setUInt32(0, playerId);
    stmt->setUInt32(1, houseId);
    stmt->setUInt8(2, permissionLevel);
    stmt->setUInt32(3, uint32(time(nullptr)));
    CharacterDatabase.Execute(stmt);

    return true;
}

bool HousingManager::RevokePermission(uint32 playerId, uint32 houseId)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_DEL_HOUSING_PERMISSION);
    stmt->setUInt32(0, playerId);
    stmt->setUInt32(1, houseId);
    CharacterDatabase.Execute(stmt);

    return true;
}

bool HousingManager::CheckPermission(uint32 playerId, uint32 houseId, uint8 requiredLevel)
{
    uint8 playerLevel = GetPlayerPermissionLevel(playerId, houseId);
    return playerLevel >= requiredLevel;
}

uint8 HousingManager::GetPlayerPermissionLevel(uint32 playerId, uint32 houseId)
{
    auto& permissions = m_permissionCache[houseId];
    for (const auto& perm : permissions)
    {
        if (perm.playerId == playerId)
            return perm.permissionLevel;
    }

    // Query database
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_HOUSING_PERMISSION);
    stmt->setUInt32(0, playerId);
    stmt->setUInt32(1, houseId);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        Field* fields = result->Fetch();
        return fields[0].GetUInt8();
    }

    return 0; // No permission
}

bool HousingManager::ValidatePurchaseCost(Player* player, const HousingCost& cost)
{
    return player->HasEnoughMoney(cost.baseCost);
}

bool HousingManager::DeductPurchaseCost(Player* player, const HousingCost& cost)
{
    if (!ValidatePurchaseCost(player, cost))
        return false;

    player->ModifyMoney(-int32(cost.baseCost));
    return true;
}

bool HousingManager::ValidateResourceRequirements(Player* player, uint32 houseTemplateId)
{
    // TODO: Implement skill/recipe requirements checking based on house template
    // For now, just check level requirement
    return player->GetLevel() >= 10; // Minimum level 10 to own a house
}

bool HousingManager::LockPlot(uint32 plotId, uint32 playerId)
{
    if (IsPlotLocked(plotId))
        return false;

    m_plotLocks[plotId] = true;
    return true;
}

bool HousingManager::UnlockPlot(uint32 plotId)
{
    m_plotLocks[plotId] = false;
    return true;
}

bool HousingManager::IsPlotLocked(uint32 plotId)
{
    auto itr = m_plotLocks.find(plotId);
    return itr != m_plotLocks.end() && itr->second;
}

bool HousingManager::BeginHousingTransaction(uint32 playerId)
{
    // Start transaction on character database
    CharacterDatabase.BeginTransaction();
    return true;
}

bool HousingManager::CommitHousingTransaction(uint32 playerId)
{
    // Commit transaction on character database
    CharacterDatabase.CommitTransaction();
    return true;
}

void HousingManager::RollbackHousingTransaction(uint32 playerId)
{
    // Rollback transaction on character database
    CharacterDatabase.RollbackTransaction();
}

HousingPlot* HousingManager::GetPlotInfo(uint32 plotId)
{
    auto itr = m_plotCache.find(plotId);
    if (itr != m_plotCache.end())
        return &itr->second;
    return nullptr;
}

std::vector<HousingPlot> HousingManager::GetPlayerHouses(uint32 playerId)
{
    std::vector<HousingPlot> houses;
    
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_HOUSING_PLAYER_HOUSES);
    stmt->setUInt32(0, playerId);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            HousingPlot plot;
            plot.plotId = fields[0].GetUInt32();
            plot.neighborhoodId = fields[1].GetUInt32();
            plot.ownerId = fields[2].GetUInt32();
            plot.ownerAccountId = fields[3].GetUInt64();
            plot.houseTemplateId = fields[4].GetUInt32();
            plot.isAvailable = fields[5].GetBool();
            plot.purchaseDate = fields[6].GetUInt32();
            plot.lastAccessDate = fields[7].GetUInt32();
            houses.push_back(plot);
        } while (result->NextRow());
    }

    return houses;
}

bool HousingManager::SavePlotData(const HousingPlot& plot)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_HOUSING_PLOT);
    stmt->setUInt32(0, plot.plotId);
    stmt->setUInt32(1, plot.neighborhoodId);
    stmt->setUInt32(2, plot.ownerId);
    stmt->setUInt64(3, plot.ownerAccountId);
    stmt->setUInt32(4, plot.houseTemplateId);
    stmt->setBool(5, plot.isAvailable);
    stmt->setUInt32(6, uint32(plot.purchaseDate));
    stmt->setUInt32(7, uint32(plot.lastAccessDate));
    CharacterDatabase.Execute(stmt);

    return true;
}

HousingCost HousingManager::GetHouseCost(uint32 houseTemplateId)
{
    HousingCost cost = {0, 0, 0, 0};
    
    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_HOUSING_TEMPLATE_COST);
    stmt->setUInt32(0, houseTemplateId);
    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (result)
    {
        Field* fields = result->Fetch();
        cost.baseCost = fields[0].GetUInt32();
        cost.maintenanceCost = fields[1].GetUInt32();
        cost.roomExpansionCost = fields[2].GetUInt32();
        cost.decorItemCost = fields[3].GetUInt32();
    }

    return cost;
}

void HousingManager::RefreshPlotCache()
{
    m_plotCache.clear();
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_HOUSING_ALL_PLOTS);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            HousingPlot plot;
            plot.plotId = fields[0].GetUInt32();
            plot.neighborhoodId = fields[1].GetUInt32();
            plot.ownerId = fields[2].GetUInt32();
            plot.ownerAccountId = fields[3].GetUInt64();
            plot.houseTemplateId = fields[4].GetUInt32();
            plot.isAvailable = fields[5].GetBool();
            plot.purchaseDate = fields[6].GetUInt32();
            plot.lastAccessDate = fields[7].GetUInt32();
            m_plotCache[plot.plotId] = plot;
        } while (result->NextRow());
    }
}

void HousingManager::CachePlotData(uint32 plotId)
{
    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_HOUSING_PLOT);
    stmt->setUInt32(0, plotId);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        Field* fields = result->Fetch();
        HousingPlot plot;
        plot.plotId = fields[0].GetUInt32();
        plot.neighborhoodId = fields[1].GetUInt32();
        plot.ownerId = fields[2].GetUInt32();
        plot.ownerAccountId = fields[3].GetUInt64();
        plot.houseTemplateId = fields[4].GetUInt32();
        plot.isAvailable = fields[5].GetBool();
        plot.purchaseDate = fields[6].GetUInt32();
        plot.lastAccessDate = fields[7].GetUInt32();
        m_plotCache[plotId] = plot;
    }
}

void HousingManager::InvalidatePlotCache(uint32 plotId)
{
    m_plotCache.erase(plotId);
}

bool HousingManager::IsHouseAvailableForPurchase(uint32 plotId, uint32 playerId)
{
    HousingPlot* plot = GetPlotInfo(plotId);
    if (!plot)
        return false;

    if (!plot->isAvailable)
        return false;

    if (IsPlotLocked(plotId))
        return false;

    return true;
}

std::vector<uint32> HousingManager::GetAvailablePlots(uint32 neighborhoodId)
{
    std::vector<uint32> availablePlots;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_HOUSING_AVAILABLE_PLOTS);
    stmt->setUInt32(0, neighborhoodId);
    PreparedQueryResult result = CharacterDatabase.Query(stmt);

    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            availablePlots.push_back(fields[0].GetUInt32());
        } while (result->NextRow());
    }

    return availablePlots;
}

bool HousingManager::CanPlayerPurchaseHouse(uint32 playerId)
{
    auto itr = m_purchaseCooldown.find(playerId);
    if (itr != m_purchaseCooldown.end())
    {
        time_t now = time(nullptr);
        if (now - itr->second < PURCHASE_COOLDOWN_SECONDS)
            return false;
    }

    m_purchaseCooldown[playerId] = time(nullptr);
    return true;
}

uint32 HousingManager::GetPlayerHouseCount(uint32 playerId)
{
    std::vector<HousingPlot> houses = GetPlayerHouses(playerId);
    return houses.size();
}

uint32 HousingManager::GetMaxHousesPerPlayer()
{
    return MAX_HOUSES_PER_PLAYER;
}