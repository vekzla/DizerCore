#ifndef HOUSING_MANAGER_H
#define HOUSING_MANAGER_H

#include "Define.h"
#include "DatabaseEnv.h"
#include <memory>
#include <unordered_map>
#include <vector>

class Player;
class WorldSession;

struct HousingPlot
{
    uint32 plotId;
    uint32 neighborhoodId;
    uint32 ownerId;
    uint64 ownerAccountId;
    uint32 houseTemplateId;
    bool isAvailable;
    time_t purchaseDate;
    time_t lastAccessDate;
};

struct HousingPermissions
{
    uint32 playerId;
    uint32 houseId;
    uint8 permissionLevel; // 0=visitor, 1=resident, 2=secondary_owner, 3=owner
    time_t grantedDate;
};

struct HousingCost
{
    uint32 baseCost;
    uint32 maintenanceCost;
    uint32 roomExpansionCost;
    uint32 decorItemCost;
};

class HousingManager
{
public:
    static HousingManager* instance();

    // Plot Management
    bool PurchasePlot(Player* player, uint32 neighborhoodId, uint32 plotId, uint32 houseTemplateId);
    bool CheckPlotAvailability(uint32 plotId);
    bool ReleasePlot(uint32 plotId);
    bool TransferPlotOwnership(uint32 plotId, uint32 newOwnerId);
    
    // Permission Management
    bool GrantPermission(uint32 playerId, uint32 houseId, uint8 permissionLevel);
    bool RevokePermission(uint32 playerId, uint32 houseId);
    bool CheckPermission(uint32 playerId, uint32 houseId, uint8 requiredLevel);
    uint8 GetPlayerPermissionLevel(uint32 playerId, uint32 houseId);
    
    // Resource Validation
    bool ValidatePurchaseCost(Player* player, const HousingCost& cost);
    bool DeductPurchaseCost(Player* player, const HousingCost& cost);
    bool ValidateResourceRequirements(Player* player, uint32 houseTemplateId);
    
    // Plot State Management
    bool LockPlot(uint32 plotId, uint32 playerId);
    bool UnlockPlot(uint32 plotId);
    bool IsPlotLocked(uint32 plotId);
    
    // Transaction Management
    bool BeginHousingTransaction(uint32 playerId);
    bool CommitHousingTransaction(uint32 playerId);
    void RollbackHousingTransaction(uint32 playerId);
    
    // Database Queries
    HousingPlot* GetPlotInfo(uint32 plotId);
    std::vector<HousingPlot> GetPlayerHouses(uint32 playerId);
    bool SavePlotData(const HousingPlot& plot);
    HousingCost GetHouseCost(uint32 houseTemplateId);
    
    // Cache Management
    void RefreshPlotCache();
    void CachePlotData(uint32 plotId);
    void InvalidatePlotCache(uint32 plotId);
    
    // Availability Checking
    bool IsHouseAvailableForPurchase(uint32 plotId, uint32 playerId);
    std::vector<uint32> GetAvailablePlots(uint32 neighborhoodId);
    
    // Rate Limiting
    bool CanPlayerPurchaseHouse(uint32 playerId);
    uint32 GetPlayerHouseCount(uint32 playerId);
    uint32 GetMaxHousesPerPlayer();
    
private:
    HousingManager();
    ~HousingManager();
    
    std::unordered_map<uint32, HousingPlot> m_plotCache;
    std::unordered_map<uint32, std::vector<HousingPermissions>> m_permissionCache;
    std::unordered_map<uint32, bool> m_plotLocks; // plotId -> isLocked
    std::unordered_map<uint32, time_t> m_purchaseCooldown; // playerId -> lastPurchaseTime
    
    static constexpr uint32 PURCHASE_COOLDOWN_SECONDS = 3600; // 1 hour
    static constexpr uint32 MAX_HOUSES_PER_PLAYER = 3;
    static constexpr uint32 PLOT_LOCK_TIMEOUT = 300; // 5 minutes
};

#define sHousingManager HousingManager::instance()

#endif