/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WorldSession.h"
#include "HousingPackets.h"
#include "Player.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "ObjectMgr.h"

void WorldSession::HandleDeclineNeighborhoodInvites(WorldPackets::Housing::DeclineNeighborhoodInvites const& declineNeighborhoodInvites)
{
    if (declineNeighborhoodInvites.Allow)
        GetPlayer()->SetPlayerFlagEx(PLAYER_FLAGS_EX_AUTO_DECLINE_NEIGHBORHOOD);
    else
        GetPlayer()->RemovePlayerFlagEx(PLAYER_FLAGS_EX_AUTO_DECLINE_NEIGHBORHOOD);
}

// Neighborhood Management Handlers

void WorldSession::HandleNeighborhoodBuyHouse(WorldPackets::Housing::NeighborhoodBuyHouse const& packet)  
{  
    Player* player = GetPlayer();  
    if (!player)  
        return;  
  
    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_BUY_HOUSE from Player {}, PlotID: {}, HouseTemplateID: {}, HouseName: {}",  
        player->GetName(), packet.PlotID, packet.HouseTemplateID, packet.HouseName);  
  
    // Persist the house record. Column order matches CHAR_INS_HOUSING_HOUSE:  
    // (owner_account_id, owner_character_guid, template_id, neighborhood_id, plot_id, house_level=1, purchase_time=UNIX_TIMESTAMP())  
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_HOUSING_HOUSE);  
    stmt->setUInt32(0, GetAccountId());  
    stmt->setUInt64(1, player->GetGUID().GetCounter());  
    stmt->setUInt32(2, packet.HouseTemplateID);  
    stmt->setUInt32(3, 0); // neighborhood_id: not carried in this packet yet; resolve from plot when neighborhoods are wired  
    stmt->setUInt32(4, packet.PlotID);  
    CharacterDatabase.Execute(stmt);  
  
    // TODO: send SMSG_NEIGHBORHOOD_BUY_HOUSE_RESPONSE once a NeighborhoodBuyHouseResponse packet class exists.  
    // Do NOT reuse HousingSvcsUpdateHouseSettingsResponse here — it writes a different opcode  
    // (SMSG_HOUSING_SVCS_UPDATE_HOUSE_SETTINGS_RESPONSE), so the client would not treat it as a buy-house reply.  
}

void WorldSession::HandleNeighborhoodMoveHouse(WorldPackets::Housing::NeighborhoodMoveHouse const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_MOVE_HOUSE from Player {}, NewPlotID: {}",
        player->GetName(), packet.NewPlotID);

    // TODO: Implement house move logic
    // 1. Verify player owns a house
    // 2. Verify new plot is available
    // 3. Update house plot assignment
    // 4. Send response
}

void WorldSession::HandleNeighborhoodInviteResident(WorldPackets::Housing::NeighborhoodInviteResident const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_INVITE_RESIDENT from Player {}, Target: {}, NeighborhoodID: {}",
        player->GetName(), packet.TargetPlayerGUID.ToString(), packet.NeighborhoodID);

    // TODO: Implement neighborhood invitation logic
    // 1. Verify player has permission to invite
    // 2. Verify target player exists
    // 3. Create invitation record
    // 4. Send invitation to target player
}

void WorldSession::HandleNeighborhoodCancelInvitation(WorldPackets::Housing::NeighborhoodCancelInvitation const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_CANCEL_INVITATION from Player {}, InvitationID: {}",
        player->GetName(), packet.InvitationID);

    // TODO: Implement invitation cancellation logic
}

void WorldSession::HandleNeighborhoodPlayerDeclineInvite(WorldPackets::Housing::NeighborhoodPlayerDeclineInvite const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_PLAYER_DECLINE_INVITE from Player {}, InvitationID: {}",
        player->GetName(), packet.InvitationID);

    // TODO: Implement invitation decline logic
}

void WorldSession::HandleNeighborhoodPlayerGetInvite(WorldPackets::Housing::NeighborhoodPlayerGetInvite const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_PLAYER_GET_INVITE from Player {}", player->GetName());

    // TODO: Implement get pending invitations logic
}

void WorldSession::HandleNeighborhoodGetInvites(WorldPackets::Housing::NeighborhoodGetInvites const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_GET_INVITES from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement get neighborhood invitations logic
}

void WorldSession::HandleNeighborhoodGetRoster(WorldPackets::Housing::NeighborhoodGetRoster const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_GET_ROSTER from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement get neighborhood roster logic
}

void WorldSession::HandleNeighborhoodUpdateName(WorldPackets::Housing::NeighborhoodUpdateName const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_UPDATE_NAME from Player {}, NeighborhoodID: {}, NewName: {}",
        player->GetName(), packet.NeighborhoodID, packet.NewName);

    // TODO: Implement neighborhood name update logic
}

void WorldSession::HandleNeighborhoodSetPublicFlag(WorldPackets::Housing::NeighborhoodSetPublicFlag const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_SET_PUBLIC_FLAG from Player {}, NeighborhoodID: {}, IsPublic: {}",
        player->GetName(), packet.NeighborhoodID, packet.IsPublic);

    // TODO: Implement public flag update logic
}

void WorldSession::HandleNeighborhoodEvictPlot(WorldPackets::Housing::NeighborhoodEvictPlot const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_EVICT_PLOT from Player {}, PlotID: {}",
        player->GetName(), packet.PlotID);

    // TODO: Implement plot eviction logic
}

void WorldSession::HandleNeighborhoodOfferOwnership(WorldPackets::Housing::NeighborhoodOfferOwnership const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_OFFER_OWNERSHIP from Player {}, NeighborhoodID: {}, Target: {}",
        player->GetName(), packet.NeighborhoodID, packet.TargetPlayerGUID.ToString());

    // TODO: Implement ownership offer logic
}

void WorldSession::HandleNeighborhoodAddSecondaryOwner(WorldPackets::Housing::NeighborhoodAddSecondaryOwner const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_ADD_SECONDARY_OWNER from Player {}, NeighborhoodID: {}, Target: {}",
        player->GetName(), packet.NeighborhoodID, packet.TargetPlayerGUID.ToString());

    // TODO: Implement secondary owner addition logic
}

void WorldSession::HandleNeighborhoodRemoveSecondaryOwner(WorldPackets::Housing::NeighborhoodRemoveSecondaryOwner const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_REMOVE_SECONDARY_OWNER from Player {}, NeighborhoodID: {}, Target: {}",
        player->GetName(), packet.NeighborhoodID, packet.TargetPlayerGUID.ToString());

    // TODO: Implement secondary owner removal logic
}

void WorldSession::HandleNeighborhoodOpenCornerstoneUI(WorldPackets::Housing::NeighborhoodOpenCornerstoneUI const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_OPEN_CORNERSTONE_UI from Player {}, PlotID: {}",
        player->GetName(), packet.PlotID);

    // TODO: Implement cornerstone UI opening logic
}

// Charter System Handlers

void WorldSession::HandleNeighborhoodCharterOpenConfirmationUI(WorldPackets::Housing::NeighborhoodCharterOpenConfirmationUI const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_CHARTER_OPEN_CONFIRMATION_UI from Player {}", player->GetName());

    // TODO: Implement charter confirmation UI logic
}

void WorldSession::HandleNeighborhoodCharterCreate(WorldPackets::Housing::NeighborhoodCharterCreate const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_CHARTER_CREATE from Player {}, Name: {}, Faction: {}",
        player->GetName(), packet.NeighborhoodName, packet.Faction);

    // TODO: Implement charter creation logic
}

void WorldSession::HandleNeighborhoodCharterEdit(WorldPackets::Housing::NeighborhoodCharterEdit const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_CHARTER_EDIT from Player {}, NeighborhoodID: {}, NewName: {}",
        player->GetName(), packet.NeighborhoodID, packet.NewName);

    // TODO: Implement charter edit logic
}

void WorldSession::HandleNeighborhoodCharterFinalize(WorldPackets::Housing::NeighborhoodCharterFinalize const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_CHARTER_FINALIZE from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement charter finalization logic
}

void WorldSession::HandleNeighborhoodCharterSendSignatureRequest(WorldPackets::Housing::NeighborhoodCharterSendSignatureRequest const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_CHARTER_SEND_SIGNATURE_REQUEST from Player {}, NeighborhoodID: {}, Target: {}",
        player->GetName(), packet.NeighborhoodID, packet.TargetPlayerGUID.ToString());

    // TODO: Implement signature request logic
}

void WorldSession::HandleNeighborhoodCharterAddSignature(WorldPackets::Housing::NeighborhoodCharterAddSignature const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_NEIGHBORHOOD_CHARTER_ADD_SIGNATURE from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement signature addition logic
}

// Housing Services Handlers

void WorldSession::HandleHousingSvcsGetPlayerHousesInfo(WorldPackets::Housing::HousingSvcsGetPlayerHousesInfo const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_GET_PLAYER_HOUSES_INFO from Player {}", player->GetName());

    // TODO: Implement get player houses info logic
    // Query database for player's houses and send response
}

void WorldSession::HandleHousingSvcsTeleportToPlot(WorldPackets::Housing::HousingSvcsTeleportToPlot const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_TELEPORT_TO_PLOT from Player {}, HouseID: {}",
        player->GetName(), packet.HouseID);

    // TODO: Implement teleport to plot logic
    // 1. Verify player owns house or has permission
    // 2. Get plot coordinates
    // 3. Teleport player to plot
}

void WorldSession::HandleHousingSvcsRelinquishHouse(WorldPackets::Housing::HousingSvcsRelinquishHouse const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_RELINQUISH_HOUSE from Player {}, HouseID: {}",
        player->GetName(), packet.HouseID);

    // TODO: Implement house relinquishment logic
    // 1. Verify player owns house
    // 2. Remove house ownership
    // 3. Clear plot assignment
    // 4. Send response
}

void WorldSession::HandleHousingSvcsUpdateHouseSettings(WorldPackets::Housing::HousingSvcsUpdateHouseSettings const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_UPDATE_HOUSE_SETTINGS from Player {}, HouseID: {}, Name: {}, ExteriorLock: {}, InteriorLock: {}",
        player->GetName(), packet.HouseID, packet.HouseName, packet.ExteriorLockState, packet.InteriorLockState);

    // TODO: Implement house settings update logic
    // 1. Verify player owns house
    // 2. Update house settings in database
    // 3. Send response
}

void WorldSession::HandleHousingSvcsGetHouseFinderInfo(WorldPackets::Housing::HousingSvcsGetHouseFinderInfo const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_GET_HOUSE_FINDER_INFO from Player {}", player->GetName());

    // TODO: Implement house finder info logic
    // Return available neighborhoods
}

void WorldSession::HandleHousingSvcsGetHouseFinderNeighborhood(WorldPackets::Housing::HousingSvcsGetHouseFinderNeighborhood const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_GET_HOUSE_FINDER_NEIGHBORHOOD from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement house finder neighborhood logic
    // Return neighborhood details and available plots
}

void WorldSession::HandleHousingSvcsHouseFinderIgnoreNeighborhood(WorldPackets::Housing::HousingSvcsHouseFinderIgnoreNeighborhood const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_HOUSE_FINDER_IGNORE_NEIGHBORHOOD from Player {}, NeighborhoodID: {}, Ignore: {}",
        player->GetName(), packet.NeighborhoodID, packet.Ignore);

    // TODO: Implement neighborhood ignore logic
}

void WorldSession::HandleHousingSvcsGetPotentialHouseOwners(WorldPackets::Housing::HousingSvcsGetPotentialHouseOwners const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_GET_POTENTIAL_HOUSE_OWNERS from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement potential house owners logic
}

void WorldSession::HandleHousingSvcsNeighborhoodReservePlot(WorldPackets::Housing::HousingSvcsNeighborhoodReservePlot const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_NEIGHBORHOOD_RESERVE_PLOT from Player {}, NeighborhoodID: {}, PlotNumber: {}",
        player->GetName(), packet.NeighborhoodID, packet.PlotNumber);

    // TODO: Implement plot reservation logic
}

void WorldSession::HandleHousingSvcsGuildCreateNeighborhood(WorldPackets::Housing::HousingSvcsGuildCreateNeighborhood const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_GUILD_CREATE_NEIGHBORHOOD from Player {}, Name: {}, Faction: {}",
        player->GetName(), packet.NeighborhoodName, packet.Faction);

    // TODO: Implement guild neighborhood creation logic
}

void WorldSession::HandleHousingSvcsAcceptNeighborhoodOwnership(WorldPackets::Housing::HousingSvcsAcceptNeighborhoodOwnership const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_ACCEPT_NEIGHBORHOOD_OWNERSHIP from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement neighborhood ownership acceptance logic
}

void WorldSession::HandleHousingSvcsRejectNeighborhoodOwnership(WorldPackets::Housing::HousingSvcsRejectNeighborhoodOwnership const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_REJECT_NEIGHBORHOOD_OWNERSHIP from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement neighborhood ownership rejection logic
}

void WorldSession::HandleHousingSvcsDeleteAllNeighborhoodInvites(WorldPackets::Housing::HousingSvcsDeleteAllNeighborhoodInvites const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_DELETE_ALL_NEIGHBORHOOD_INVITES from Player {}", player->GetName());

    // TODO: Implement delete all neighborhood invites logic
}

void WorldSession::HandleHousingSvcsGetBnetFriendNeighborhoods(WorldPackets::Housing::HousingSvcsGetBnetFriendNeighborhoods const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_GET_BNET_FRIEND_NEIGHBORHOODS from Player {}", player->GetName());

    // TODO: Implement get friend neighborhoods logic
}

void WorldSession::HandleHousingSvcsPlayerViewHousesByPlayer(WorldPackets::Housing::HousingSvcsPlayerViewHousesByPlayer const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_PLAYER_VIEW_HOUSES_BY_PLAYER from Player {}, Target: {}",
        player->GetName(), packet.PlayerGUID.ToString());

    // TODO: Implement view houses by player logic
}

void WorldSession::HandleHousingSvcsPlayerViewHousesByBnetAccount(WorldPackets::Housing::HousingSvcsPlayerViewHousesByBnetAccount const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_PLAYER_VIEW_HOUSES_BY_BNET_ACCOUNT from Player {}, BnetAccountID: {}",
        player->GetName(), packet.BnetAccountID);

    // TODO: Implement view houses by bnet account logic
}

void WorldSession::HandleHousingSvcsStartTutorial(WorldPackets::Housing::HousingSvcsStartTutorial const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_SVCS_START_TUTORIAL from Player {}", player->GetName());

    // TODO: Implement tutorial start logic
}

// Decor Management Handlers

void WorldSession::HandleHousingDecorSetEditMode(WorldPackets::Housing::HousingDecorSetEditMode const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_SET_EDIT_MODE from Player {}, EditMode: {}",
        player->GetName(), packet.EditMode);

    // TODO: Implement decor edit mode logic
}

void WorldSession::HandleHousingDecorPlace(WorldPackets::Housing::HousingDecorPlace const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_PLACE from Player {}, DecorID: {}, RoomID: {}, IsExterior: {}",
        player->GetName(), packet.DecorDefinitionID, packet.RoomID, packet.IsExterior);

    // TODO: Implement decor placement logic
    // 1. Verify player owns house or has permission
    // 2. Verify player has decor in collection
    // 3. Check placement limits
    // 4. Create decor placement record
    // 5. Send response
}

void WorldSession::HandleHousingDecorMove(WorldPackets::Housing::HousingDecorMove const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_MOVE from Player {}, PlacementID: {}",
        player->GetName(), packet.PlacementID);

    // TODO: Implement decor move logic
}

void WorldSession::HandleHousingDecorRemove(WorldPackets::Housing::HousingDecorRemove const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_REMOVE from Player {}, PlacementID: {}",
        player->GetName(), packet.PlacementID);

    // TODO: Implement decor removal logic
}

void WorldSession::HandleHousingDecorLock(WorldPackets::Housing::HousingDecorLock const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_LOCK from Player {}, PlacementID: {}, Lock: {}",
        player->GetName(), packet.PlacementID, packet.Lock);

    // TODO: Implement decor lock logic
}

void WorldSession::HandleHousingDecorSetPet(WorldPackets::Housing::HousingDecorSetPet const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_SET_PET from Player {}, PlacementID: {}, Pet: {}",
        player->GetName(), packet.PlacementID, packet.PetGUID.ToString());

    // TODO: Implement decor pet assignment logic
}

void WorldSession::HandleHousingDecorSetDyeSlots(WorldPackets::Housing::HousingDecorSetDyeSlots const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_SET_DYE_SLOTS from Player {}, PlacementID: {}, Dyes: {}, {}, {}",
        player->GetName(), packet.PlacementID, packet.DyeSlot1, packet.DyeSlot2, packet.DyeSlot3);

    // TODO: Implement decor dye slots logic
}

void WorldSession::HandleHousingDecorRequestStorage(WorldPackets::Housing::HousingDecorRequestStorage const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_REQUEST_STORAGE from Player {}, HouseID: {}",
        player->GetName(), packet.HouseID);

    // TODO: Implement decor storage request logic
}

void WorldSession::HandleHousingDecorDeleteFromStorage(WorldPackets::Housing::HousingDecorDeleteFromStorage const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_DELETE_FROM_STORAGE from Player {}, StorageID: {}",
        player->GetName(), packet.StorageID);

    // TODO: Implement decor storage deletion logic
}

void WorldSession::HandleHousingDecorRedeemDeferredDecor(WorldPackets::Housing::HousingDecorRedeemDeferredDecor const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_DECOR_REDEEM_DEFERRED_DECOR from Player {}, DeferredDecorID: {}",
        player->GetName(), packet.DeferredDecorID);

    // TODO: Implement deferred decor redemption logic
}

// Room Management Handlers

void WorldSession::HandleHousingRoomSetLayoutEditMode(WorldPackets::Housing::HousingRoomSetLayoutEditMode const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_SET_LAYOUT_EDIT_MODE from Player {}, EditMode: {}",
        player->GetName(), packet.EditMode);

    // TODO: Implement room layout edit mode logic
}

void WorldSession::HandleHousingRoomAdd(WorldPackets::Housing::HousingRoomAdd const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_ADD from Player {}, RoomTemplateID: {}",
        player->GetName(), packet.RoomTemplateID);

    // TODO: Implement room addition logic
}

void WorldSession::HandleHousingRoomRemove(WorldPackets::Housing::HousingRoomRemove const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_REMOVE from Player {}, RoomID: {}",
        player->GetName(), packet.RoomID);

    // TODO: Implement room removal logic
}

void WorldSession::HandleHousingRoomMove(WorldPackets::Housing::HousingRoomMove const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_MOVE from Player {}, RoomID: {}",
        player->GetName(), packet.RoomID);

    // TODO: Implement room move logic
}

void WorldSession::HandleHousingRoomRotate(WorldPackets::Housing::HousingRoomRotate const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_ROTATE from Player {}, RoomID: {}",
        player->GetName(), packet.RoomID);

    // TODO: Implement room rotation logic
}

void WorldSession::HandleHousingRoomSetComponentTheme(WorldPackets::Housing::HousingRoomSetComponentTheme const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_SET_COMPONENT_THEME from Player {}, RoomID: {}, ThemeID: {}",
        player->GetName(), packet.RoomID, packet.ThemeID);

    // TODO: Implement room component theme logic
}

void WorldSession::HandleHousingRoomApplyComponentMaterials(WorldPackets::Housing::HousingRoomApplyComponentMaterials const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_APPLY_COMPONENT_MATERIALS from Player {}, RoomID: {}, MaterialID: {}",
        player->GetName(), packet.RoomID, packet.MaterialID);

    // TODO: Implement room component materials logic
}

void WorldSession::HandleHousingRoomSetCeilingType(WorldPackets::Housing::HousingRoomSetCeilingType const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_SET_CEILING_TYPE from Player {}, RoomID: {}, CeilingType: {}",
        player->GetName(), packet.RoomID, packet.CeilingType);

    // TODO: Implement room ceiling type logic
}

void WorldSession::HandleHousingRoomSetDoorType(WorldPackets::Housing::HousingRoomSetDoorType const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_ROOM_SET_DOOR_TYPE from Player {}, RoomID: {}, DoorType: {}",
        player->GetName(), packet.RoomID, packet.DoorType);

    // TODO: Implement room door type logic
}

// Fixture Management Handlers

void WorldSession::HandleHousingFixtureSetEditMode(WorldPackets::Housing::HousingFixtureSetEditMode const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_FIXTURE_SET_EDIT_MODE from Player {}, EditMode: {}",
        player->GetName(), packet.EditMode);

    // TODO: Implement fixture edit mode logic
}

void WorldSession::HandleHousingFixtureSetCoreFixture(WorldPackets::Housing::HousingFixtureSetCoreFixture const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_FIXTURE_SET_CORE_FIXTURE from Player {}, FixtureDefinitionID: {}",
        player->GetName(), packet.FixtureDefinitionID);

    // TODO: Implement core fixture logic
}

void WorldSession::HandleHousingFixtureSetHouseType(WorldPackets::Housing::HousingFixtureSetHouseType const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_FIXTURE_SET_HOUSE_TYPE from Player {}, HouseTemplateID: {}",
        player->GetName(), packet.HouseTemplateID);

    // TODO: Implement house type logic
}

void WorldSession::HandleHousingFixtureSetHouseSize(WorldPackets::Housing::HousingFixtureSetHouseSize const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_FIXTURE_SET_HOUSE_SIZE from Player {}, HouseSize: {}",
        player->GetName(), packet.HouseSize);

    // TODO: Implement house size logic
}

void WorldSession::HandleHousingFixtureCreateFixture(WorldPackets::Housing::HousingFixtureCreateFixture const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_FIXTURE_CREATE_FIXTURE from Player {}, FixtureDefinitionID: {}",
        player->GetName(), packet.FixtureDefinitionID);

    // TODO: Implement fixture creation logic
}

void WorldSession::HandleHousingFixtureDeleteFixture(WorldPackets::Housing::HousingFixtureDeleteFixture const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_FIXTURE_DELETE_FIXTURE from Player {}, FixtureID: {}",
        player->GetName(), packet.FixtureID);

    // TODO: Implement fixture deletion logic
}

// Blueprint Management Handlers

void WorldSession::HandleHousingBlueprintRequestCollection(WorldPackets::Housing::HousingBlueprintRequestCollection const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_BLUEPRINT_REQUEST_COLLECTION from Player {}", player->GetName());

    // TODO: Implement blueprint collection request logic
}

void WorldSession::HandleHousingBlueprintRequestContents(WorldPackets::Housing::HousingBlueprintRequestContents const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_BLUEPRINT_REQUEST_CONTENTS from Player {}, BlueprintID: {}",
        player->GetName(), packet.BlueprintID);

    // TODO: Implement blueprint contents request logic
}

void WorldSession::HandleHousingBlueprintExport(WorldPackets::Housing::HousingBlueprintExport const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_BLUEPRINT_EXPORT from Player {}, Name: {}, IsPublic: {}",
        player->GetName(), packet.BlueprintName, packet.IsPublic);

    // TODO: Implement blueprint export logic
}

void WorldSession::HandleHousingBlueprintImport(WorldPackets::Housing::HousingBlueprintImport const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_BLUEPRINT_IMPORT from Player {}, BlueprintID: {}",
        player->GetName(), packet.BlueprintID);

    // TODO: Implement blueprint import logic
}

void WorldSession::HandleHousingBlueprintRename(WorldPackets::Housing::HousingBlueprintRename const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_BLUEPRINT_RENAME from Player {}, BlueprintID: {}, NewName: {}",
        player->GetName(), packet.BlueprintID, packet.NewName);

    // TODO: Implement blueprint rename logic
}

void WorldSession::HandleHousingBlueprintDelete(WorldPackets::Housing::HousingBlueprintDelete const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_BLUEPRINT_DELETE from Player {}, BlueprintID: {}",
        player->GetName(), packet.BlueprintID);

    // TODO: Implement blueprint deletion logic
}

// House Info Handlers

void WorldSession::HandleHousingGetCurrentHouseInfo(WorldPackets::Housing::HousingGetCurrentHouseInfo const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_GET_CURRENT_HOUSE_INFO from Player {}", player->GetName());

    // TODO: Implement get current house info logic
}

void WorldSession::HandleHousingGetPlayerPermissions(WorldPackets::Housing::HousingGetPlayerPermissions const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_GET_PLAYER_PERMISSIONS from Player {}, HouseID: {}",
        player->GetName(), packet.HouseID);

    // TODO: Implement get player permissions logic
}

void WorldSession::HandleHousingHouseStatus(WorldPackets::Housing::HousingHouseStatus const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_HOUSE_STATUS from Player {}, HouseID: {}",
        player->GetName(), packet.HouseID);

    // TODO: Implement house status logic
}

void WorldSession::HandleHousingResetHouse(WorldPackets::Housing::HousingResetHouse const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_RESET_HOUSE from Player {}, HouseID: {}",
        player->GetName(), packet.HouseID);

    // TODO: Implement house reset logic
}

void WorldSession::HandleHousingResetKioskMode(WorldPackets::Housing::HousingResetKioskMode const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_RESET_KIOSK_MODE from Player {}", player->GetName());

    // TODO: Implement kiosk mode reset logic
}

// House Exterior Handlers

void WorldSession::HandleHouseExteriorSetHousePosition(WorldPackets::Housing::HouseExteriorSetHousePosition const& packet)  
{  
    Player* player = GetPlayer();  
    if (!player)  
        return;  
  
    TC_LOG_INFO("network", "CMSG_HOUSE_EXTERIOR_SET_HOUSE_POSITION from Player {}, Pos: {}, {}, {}, Orient: {}",  
        player->GetName(), packet.PositionX, packet.PositionY, packet.PositionZ, packet.Orientation);  
  
    // TODO: Implement house position logic  
}

void WorldSession::HandleHouseInteriorLeaveHouse(WorldPackets::Housing::HouseInteriorLeaveHouse const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSE_INTERIOR_LEAVE_HOUSE from Player {}", player->GetName());

    // TODO: Implement leave house logic
}

// Initiative Handler

void WorldSession::HandleInitiativeUpdateActiveNeighborhood(WorldPackets::Housing::InitiativeUpdateActiveNeighborhood const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_INITIATIVE_UPDATE_ACTIVE_NEIGHBORHOOD from Player {}, HouseID: {}",
        player->GetName(), packet.HouseID);

    // TODO: Implement active neighborhood update logic
}

// Photo Sharing Handlers

void WorldSession::HandleHousingPhotoSharingCompleteAuthorization(WorldPackets::Housing::HousingPhotoSharingCompleteAuthorization const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_PHOTO_SHARING_COMPLETE_AUTHORIZATION from Player {}, Code: {}",
        player->GetName(), packet.AuthorizationCode);

    // TODO: Implement photo sharing authorization logic
}

void WorldSession::HandleHousingPhotoSharingClearAuthorization(WorldPackets::Housing::HousingPhotoSharingClearAuthorization const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_HOUSING_PHOTO_SHARING_CLEAR_AUTHORIZATION from Player {}", player->GetName());

    // TODO: Implement photo sharing authorization clear logic
}

// Invite Player Handler

void WorldSession::HandleInvitePlayerToNeighborhood(WorldPackets::Housing::InvitePlayerToNeighborhood const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_INVITE_PLAYER_TO_NEIGHBORHOOD from Player {}, Target: {}, NeighborhoodID: {}",
        player->GetName(), packet.TargetPlayerGUID.ToString(), packet.NeighborhoodID);

    // TODO: Implement player invitation logic
}

// Query Neighborhood Info Handler

void WorldSession::HandleQueryNeighborhoodInfo(WorldPackets::Housing::QueryNeighborhoodInfo const& packet)
{
    Player* player = GetPlayer();
    if (!player)
        return;

    TC_LOG_INFO("network", "CMSG_QUERY_NEIGHBORHOOD_INFO from Player {}, NeighborhoodID: {}",
        player->GetName(), packet.NeighborhoodID);

    // TODO: Implement neighborhood info query logic
}
