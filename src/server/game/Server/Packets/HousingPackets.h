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

#ifndef TRINITYCORE_HOUSING_PACKETS_H
#define TRINITYCORE_HOUSING_PACKETS_H

#include "Packet.h"
#include "ObjectGuid.h"

namespace WorldPackets::Housing
{
    // ============================================
    // CLIENT PACKETS
    // ============================================

    class DeclineNeighborhoodInvites final : public ClientPacket
    {
    public:
        explicit DeclineNeighborhoodInvites(WorldPacket&& packet) : ClientPacket(CMSG_DECLINE_NEIGHBORHOOD_INVITES, std::move(packet)) { }

        void Read() override;

        bool Allow = false;
    };

    // Neighborhood Management
    class NeighborhoodBuyHouse final : public ClientPacket
    {
    public:
        explicit NeighborhoodBuyHouse(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_BUY_HOUSE, std::move(packet)) { }

        void Read() override;

        uint32 PlotID = 0;
        uint32 HouseTemplateID = 0;
        std::string HouseName;
    };

    class NeighborhoodMoveHouse final : public ClientPacket
    {
    public:
        explicit NeighborhoodMoveHouse(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_MOVE_HOUSE, std::move(packet)) { }

        void Read() override;

        uint32 NewPlotID = 0;
    };

    class NeighborhoodInviteResident final : public ClientPacket
    {
    public:
        explicit NeighborhoodInviteResident(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_INVITE_RESIDENT, std::move(packet)) { }

        void Read() override;

        ObjectGuid TargetPlayerGUID;
        uint32 NeighborhoodID = 0;
    };

    class NeighborhoodCancelInvitation final : public ClientPacket
    {
    public:
        explicit NeighborhoodCancelInvitation(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_CANCEL_INVITATION, std::move(packet)) { }

        void Read() override;

        uint32 InvitationID = 0;
    };

    class NeighborhoodPlayerDeclineInvite final : public ClientPacket
    {
    public:
        explicit NeighborhoodPlayerDeclineInvite(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_PLAYER_DECLINE_INVITE, std::move(packet)) { }

        void Read() override;

        uint32 InvitationID = 0;
    };

    class NeighborhoodPlayerGetInvite final : public ClientPacket
    {
    public:
        explicit NeighborhoodPlayerGetInvite(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_PLAYER_GET_INVITE, std::move(packet)) { }

        void Read() override;
    };

    class NeighborhoodGetInvites final : public ClientPacket
    {
    public:
        explicit NeighborhoodGetInvites(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_GET_INVITES, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    class NeighborhoodGetRoster final : public ClientPacket
    {
    public:
        explicit NeighborhoodGetRoster(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_GET_ROSTER, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    class NeighborhoodUpdateName final : public ClientPacket
    {
    public:
        explicit NeighborhoodUpdateName(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_UPDATE_NAME, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        std::string NewName;
    };

    class NeighborhoodSetPublicFlag final : public ClientPacket
    {
    public:
        explicit NeighborhoodSetPublicFlag(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_SET_PUBLIC_FLAG, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        bool IsPublic = false;
    };

    class NeighborhoodEvictPlot final : public ClientPacket
    {
    public:
        explicit NeighborhoodEvictPlot(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_EVICT_PLOT, std::move(packet)) { }

        void Read() override;

        uint32 PlotID = 0;
    };

    class NeighborhoodOfferOwnership final : public ClientPacket
    {
    public:
        explicit NeighborhoodOfferOwnership(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_OFFER_OWNERSHIP, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        ObjectGuid TargetPlayerGUID;
    };

    class NeighborhoodAddSecondaryOwner final : public ClientPacket
    {
    public:
        explicit NeighborhoodAddSecondaryOwner(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_ADD_SECONDARY_OWNER, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        ObjectGuid TargetPlayerGUID;
    };

    class NeighborhoodRemoveSecondaryOwner final : public ClientPacket
    {
    public:
        explicit NeighborhoodRemoveSecondaryOwner(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_REMOVE_SECONDARY_OWNER, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        ObjectGuid TargetPlayerGUID;
    };

    class NeighborhoodOpenCornerstoneUI final : public ClientPacket
    {
    public:
        explicit NeighborhoodOpenCornerstoneUI(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_OPEN_CORNERSTONE_UI, std::move(packet)) { }

        void Read() override;

        uint32 PlotID = 0;
    };

    // Charter System
    class NeighborhoodCharterOpenConfirmationUI final : public ClientPacket
    {
    public:
        explicit NeighborhoodCharterOpenConfirmationUI(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_CHARTER_OPEN_CONFIRMATION_UI, std::move(packet)) { }

        void Read() override;
    };

    class NeighborhoodCharterCreate final : public ClientPacket
    {
    public:
        explicit NeighborhoodCharterCreate(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_CHARTER_CREATE, std::move(packet)) { }

        void Read() override;

        std::string NeighborhoodName;
        uint32 Faction = 0;
    };

    class NeighborhoodCharterEdit final : public ClientPacket
    {
    public:
        explicit NeighborhoodCharterEdit(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_CHARTER_EDIT, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        std::string NewName;
    };

    class NeighborhoodCharterFinalize final : public ClientPacket
    {
    public:
        explicit NeighborhoodCharterFinalize(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_CHARTER_FINALIZE, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    class NeighborhoodCharterSendSignatureRequest final : public ClientPacket
    {
    public:
        explicit NeighborhoodCharterSendSignatureRequest(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_CHARTER_SEND_SIGNATURE_REQUEST, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        ObjectGuid TargetPlayerGUID;
    };

    class NeighborhoodCharterAddSignature final : public ClientPacket
    {
    public:
        explicit NeighborhoodCharterAddSignature(WorldPacket&& packet) : ClientPacket(CMSG_NEIGHBORHOOD_CHARTER_ADD_SIGNATURE, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    // Housing Services
    class HousingSvcsGetPlayerHousesInfo final : public ClientPacket
    {
    public:
        explicit HousingSvcsGetPlayerHousesInfo(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_GET_PLAYER_HOUSES_INFO, std::move(packet)) { }

        void Read() override;
    };

    class HousingSvcsTeleportToPlot final : public ClientPacket
    {
    public:
        explicit HousingSvcsTeleportToPlot(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_TELEPORT_TO_PLOT, std::move(packet)) { }

        void Read() override;

        uint32 HouseID = 0;
    };

    class HousingSvcsRelinquishHouse final : public ClientPacket
    {
    public:
        explicit HousingSvcsRelinquishHouse(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_RELINQUISH_HOUSE, std::move(packet)) { }

        void Read() override;

        uint32 HouseID = 0;
    };

    class HousingSvcsUpdateHouseSettings final : public ClientPacket
    {
    public:
        explicit HousingSvcsUpdateHouseSettings(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_UPDATE_HOUSE_SETTINGS, std::move(packet)) { }

        void Read() override;

        uint32 HouseID = 0;
        std::string HouseName;
        uint8 ExteriorLockState = 0;
        uint8 InteriorLockState = 0;
    };

    class HousingSvcsGetHouseFinderInfo final : public ClientPacket
    {
    public:
        explicit HousingSvcsGetHouseFinderInfo(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_GET_HOUSE_FINDER_INFO, std::move(packet)) { }

        void Read() override;
    };

    class HousingSvcsGetHouseFinderNeighborhood final : public ClientPacket
    {
    public:
        explicit HousingSvcsGetHouseFinderNeighborhood(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_GET_HOUSE_FINDER_NEIGHBORHOOD, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    class HousingSvcsHouseFinderIgnoreNeighborhood final : public ClientPacket
    {
    public:
        explicit HousingSvcsHouseFinderIgnoreNeighborhood(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_HOUSE_FINDER_IGNORE_NEIGHBORHOOD, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        bool Ignore = false;
    };

    class HousingSvcsGetPotentialHouseOwners final : public ClientPacket
    {
    public:
        explicit HousingSvcsGetPotentialHouseOwners(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_GET_POTENTIAL_HOUSE_OWNERS, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    class HousingSvcsNeighborhoodReservePlot final : public ClientPacket
    {
    public:
        explicit HousingSvcsNeighborhoodReservePlot(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_NEIGHBORHOOD_RESERVE_PLOT, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
        uint32 PlotNumber = 0;
    };

    class HousingSvcsGuildCreateNeighborhood final : public ClientPacket
    {
    public:
        explicit HousingSvcsGuildCreateNeighborhood(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_GUILD_CREATE_NEIGHBORHOOD, std::move(packet)) { }

        void Read() override;

        std::string NeighborhoodName;
        uint32 Faction = 0;
    };

    class HousingSvcsAcceptNeighborhoodOwnership final : public ClientPacket
    {
    public:
        explicit HousingSvcsAcceptNeighborhoodOwnership(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_ACCEPT_NEIGHBORHOOD_OWNERSHIP, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    class HousingSvcsRejectNeighborhoodOwnership final : public ClientPacket
    {
    public:
        explicit HousingSvcsRejectNeighborhoodOwnership(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_REJECT_NEIGHBORHOOD_OWNERSHIP, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    class HousingSvcsDeleteAllNeighborhoodInvites final : public ClientPacket
    {
    public:
        explicit HousingSvcsDeleteAllNeighborhoodInvites(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_DELETE_ALL_NEIGHBORHOOD_INVITES, std::move(packet)) { }

        void Read() override;
    };

    class HousingSvcsGetBnetFriendNeighborhoods final : public ClientPacket
    {
    public:
        explicit HousingSvcsGetBnetFriendNeighborhoods(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_GET_BNET_FRIEND_NEIGHBORHOODS, std::move(packet)) { }

        void Read() override;
    };

    class HousingSvcsPlayerViewHousesByPlayer final : public ClientPacket
    {
    public:
        explicit HousingSvcsPlayerViewHousesByPlayer(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_PLAYER_VIEW_HOUSES_BY_PLAYER, std::move(packet)) { }

        void Read() override;

        ObjectGuid PlayerGUID;
    };

    class HousingSvcsPlayerViewHousesByBnetAccount final : public ClientPacket
    {
    public:
        explicit HousingSvcsPlayerViewHousesByBnetAccount(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_PLAYER_VIEW_HOUSES_BY_BNET_ACCOUNT, std::move(packet)) { }

        void Read() override;

        uint32 BnetAccountID = 0;
    };

    class HousingSvcsStartTutorial final : public ClientPacket
    {
    public:
        explicit HousingSvcsStartTutorial(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_SVCS_START_TUTORIAL, std::move(packet)) { }

        void Read() override;
    };

    // Decor Management
    class HousingDecorSetEditMode final : public ClientPacket
    {
    public:
        explicit HousingDecorSetEditMode(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_SET_EDIT_MODE, std::move(packet)) { }

        void Read() override;

        bool EditMode = false;
    };

    class HousingDecorPlace final : public ClientPacket
    {
    public:
        explicit HousingDecorPlace(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_PLACE, std::move(packet)) { }

        void Read() override;

        uint32 DecorDefinitionID = 0;
        uint32 RoomID = 0;
        float PositionX = 0.0f;
        float PositionY = 0.0f;
        float PositionZ = 0.0f;
        float Orientation = 0.0f;
        float Scale = 1.0f;
        bool IsExterior = false;
    };

    class HousingDecorMove final : public ClientPacket
    {
    public:
        explicit HousingDecorMove(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_MOVE, std::move(packet)) { }

        void Read() override;

        uint32 PlacementID = 0;
        float PositionX = 0.0f;
        float PositionY = 0.0f;
        float PositionZ = 0.0f;
        float Orientation = 0.0f;
        float Scale = 1.0f;
    };

    class HousingDecorRemove final : public ClientPacket
    {
    public:
        explicit HousingDecorRemove(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_REMOVE, std::move(packet)) { }

        void Read() override;

        uint32 PlacementID = 0;
    };

    class HousingDecorLock final : public ClientPacket
    {
    public:
        explicit HousingDecorLock(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_LOCK, std::move(packet)) { }

        void Read() override;

        uint32 PlacementID = 0;
        bool Lock = false;
    };

    class HousingDecorSetPet final : public ClientPacket
    {
    public:
        explicit HousingDecorSetPet(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_SET_PET, std::move(packet)) { }

        void Read() override;

        uint32 PlacementID = 0;
        ObjectGuid PetGUID;
    };

    class HousingDecorSetDyeSlots final : public ClientPacket
    {
    public:
        explicit HousingDecorSetDyeSlots(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_SET_DYE_SLOTS, std::move(packet)) { }

        void Read() override;

        uint32 PlacementID = 0;
        uint32 DyeSlot1 = 0;
        uint32 DyeSlot2 = 0;
        uint32 DyeSlot3 = 0;
    };

    class HousingDecorRequestStorage final : public ClientPacket
    {
    public:
        explicit HousingDecorRequestStorage(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_REQUEST_STORAGE, std::move(packet)) { }

        void Read() override;

        uint32 HouseID = 0;
    };

    class HousingDecorDeleteFromStorage final : public ClientPacket
    {
    public:
        explicit HousingDecorDeleteFromStorage(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_DELETE_FROM_STORAGE, std::move(packet)) { }

        void Read() override;

        uint32 StorageID = 0;
    };

    class HousingDecorRedeemDeferredDecor final : public ClientPacket
    {
    public:
        explicit HousingDecorRedeemDeferredDecor(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_DECOR_REDEEM_DEFERRED_DECOR, std::move(packet)) { }

        void Read() override;

        uint32 DeferredDecorID = 0;
    };

    // Room Management
    class HousingRoomSetLayoutEditMode final : public ClientPacket
    {
    public:
        explicit HousingRoomSetLayoutEditMode(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_SET_LAYOUT_EDIT_MODE, std::move(packet)) { }

        void Read() override;

        bool EditMode = false;
    };

    class HousingRoomAdd final : public ClientPacket
    {
    public:
        explicit HousingRoomAdd(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_ADD, std::move(packet)) { }

        void Read() override;

        uint32 RoomTemplateID = 0;
        float PositionX = 0.0f;
        float PositionY = 0.0f;
        float PositionZ = 0.0f;
        float Orientation = 0.0f;
    };

    class HousingRoomRemove final : public ClientPacket
    {
    public:
        explicit HousingRoomRemove(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_REMOVE, std::move(packet)) { }

        void Read() override;

        uint32 RoomID = 0;
    };

    class HousingRoomMove final : public ClientPacket
    {
    public:
        explicit HousingRoomMove(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_MOVE, std::move(packet)) { }

        void Read() override;

        uint32 RoomID = 0;
        float PositionX = 0.0f;
        float PositionY = 0.0f;
        float PositionZ = 0.0f;
        float Orientation = 0.0f;
    };

    class HousingRoomRotate final : public ClientPacket
    {
    public:
        explicit HousingRoomRotate(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_ROTATE, std::move(packet)) { }

        void Read() override;

        uint32 RoomID = 0;
        float Orientation = 0.0f;
    };

    class HousingRoomSetComponentTheme final : public ClientPacket
    {
    public:
        explicit HousingRoomSetComponentTheme(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_SET_COMPONENT_THEME, std::move(packet)) { }

        void Read() override;

        uint32 RoomID = 0;
        uint32 ThemeID = 0;
    };

    class HousingRoomApplyComponentMaterials final : public ClientPacket
    {
    public:
        explicit HousingRoomApplyComponentMaterials(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_APPLY_COMPONENT_MATERIALS, std::move(packet)) { }

        void Read() override;

        uint32 RoomID = 0;
        uint32 MaterialID = 0;
    };

    class HousingRoomSetCeilingType final : public ClientPacket
    {
    public:
        explicit HousingRoomSetCeilingType(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_SET_CEILING_TYPE, std::move(packet)) { }

        void Read() override;

        uint32 RoomID = 0;
        uint32 CeilingType = 0;
    };

    class HousingRoomSetDoorType final : public ClientPacket
    {
    public:
        explicit HousingRoomSetDoorType(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_ROOM_SET_DOOR_TYPE, std::move(packet)) { }

        void Read() override;

        uint32 RoomID = 0;
        uint32 DoorType = 0;
    };

    // Fixture Management
    class HousingFixtureSetEditMode final : public ClientPacket
    {
    public:
        explicit HousingFixtureSetEditMode(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_FIXTURE_SET_EDIT_MODE, std::move(packet)) { }

        void Read() override;

        bool EditMode = false;
    };

    class HousingFixtureSetCoreFixture final : public ClientPacket
    {
    public:
        explicit HousingFixtureSetCoreFixture(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_FIXTURE_SET_CORE_FIXTURE, std::move(packet)) { }

        void Read() override;

        uint32 FixtureDefinitionID = 0;
    };

    class HousingFixtureSetHouseType final : public ClientPacket
    {
    public:
        explicit HousingFixtureSetHouseType(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_FIXTURE_SET_HOUSE_TYPE, std::move(packet)) { }

        void Read() override;

        uint32 HouseTemplateID = 0;
    };

    class HousingFixtureSetHouseSize final : public ClientPacket
    {
    public:
        explicit HousingFixtureSetHouseSize(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_FIXTURE_SET_HOUSE_SIZE, std::move(packet)) { }

        void Read() override;

        uint32 HouseSize = 0;
    };

    class HousingFixtureCreateFixture final : public ClientPacket
    {
    public:
        explicit HousingFixtureCreateFixture(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_FIXTURE_CREATE_FIXTURE, std::move(packet)) { }

        void Read() override;

        uint32 FixtureDefinitionID = 0;
        float PositionX = 0.0f;
        float PositionY = 0.0f;
        float PositionZ = 0.0f;
        float Orientation = 0.0f;
    };

    class HousingFixtureDeleteFixture final : public ClientPacket
    {
    public:
        explicit HousingFixtureDeleteFixture(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_FIXTURE_DELETE_FIXTURE, std::move(packet)) { }

        void Read() override;

        uint32 FixtureID = 0;
    };

    // Blueprint Management
    class HousingBlueprintRequestCollection final : public ClientPacket
    {
    public:
        explicit HousingBlueprintRequestCollection(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_BLUEPRINT_REQUEST_COLLECTION, std::move(packet)) { }

        void Read() override;
    };

    class HousingBlueprintRequestContents final : public ClientPacket
    {
    public:
        explicit HousingBlueprintRequestContents(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_BLUEPRINT_REQUEST_CONTENTS, std::move(packet)) { }

        void Read() override;

        uint32 BlueprintID = 0;
    };

    class HousingBlueprintExport final : public ClientPacket
    {
    public:
        explicit HousingBlueprintExport(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_BLUEPRINT_EXPORT, std::move(packet)) { }

        void Read() override;

        std::string BlueprintName;
        std::string Description;
        bool IsPublic = false;
    };

    class HousingBlueprintImport final : public ClientPacket
    {
    public:
        explicit HousingBlueprintImport(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_BLUEPRINT_IMPORT, std::move(packet)) { }

        void Read() override;

        uint32 BlueprintID = 0;
    };

    class HousingBlueprintRename final : public ClientPacket
    {
    public:
        explicit HousingBlueprintRename(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_BLUEPRINT_RENAME, std::move(packet)) { }

        void Read() override;

        uint32 BlueprintID = 0;
        std::string NewName;
    };

    class HousingBlueprintDelete final : public ClientPacket
    {
    public:
        explicit HousingBlueprintDelete(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_BLUEPRINT_DELETE, std::move(packet)) { }

        void Read() override;

        uint32 BlueprintID = 0;
    };

    // House Info
    class HousingGetCurrentHouseInfo final : public ClientPacket
    {
    public:
        explicit HousingGetCurrentHouseInfo(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_GET_CURRENT_HOUSE_INFO, std::move(packet)) { }

        void Read() override;
    };

    class HousingGetPlayerPermissions final : public ClientPacket
    {
    public:
        explicit HousingGetPlayerPermissions(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_GET_PLAYER_PERMISSIONS, std::move(packet)) { }

        void Read() override;

        uint32 HouseID = 0;
    };

    class HousingHouseStatus final : public ClientPacket
    {
    public:
        explicit HousingHouseStatus(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_HOUSE_STATUS, std::move(packet)) { }

        void Read() override;

        uint32 HouseID = 0;
    };

    class HousingResetHouse final : public ClientPacket
    {
    public:
        explicit HousingResetHouse(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_RESET_HOUSE, std::move(packet)) { }

        void Read() override;

        uint32 HouseID = 0;
    };

    class HousingResetKioskMode final : public ClientPacket
    {
    public:
        explicit HousingResetKioskMode(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_RESET_KIOSK_MODE, std::move(packet)) { }

        void Read() override;
    };

    // House Exterior
    class HouseExteriorSetHousePosition final : public ClientPacket
    {
    public:
        explicit HouseExteriorSetHousePosition(WorldPacket&& packet) : ClientPacket(CMSG_HOUSE_EXTERIOR_SET_HOUSE_POSITION, std::move(packet)) { }

        void Read() override;

        float PositionX = 0.0f;
        float PositionY = 0.0f;
        float PositionZ = 0.0f;
        float Orientation = 0.0f;
    };

    class HouseInteriorLeaveHouse final : public ClientPacket
    {
    public:
        explicit HouseInteriorLeaveHouse(WorldPacket&& packet) : ClientPacket(CMSG_HOUSE_INTERIOR_LEAVE_HOUSE, std::move(packet)) { }

        void Read() override;
    };

    // Initiative
    class InitiativeUpdateActiveNeighborhood final : public ClientPacket
    {
    public:
        explicit InitiativeUpdateActiveNeighborhood(WorldPacket&& packet) : ClientPacket(CMSG_INITIATIVE_UPDATE_ACTIVE_NEIGHBORHOOD, std::move(packet)) { }

        void Read() override;

        uint32 HouseID = 0;
    };

    // Photo Sharing
    class HousingPhotoSharingCompleteAuthorization final : public ClientPacket
    {
    public:
        explicit HousingPhotoSharingCompleteAuthorization(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_PHOTO_SHARING_COMPLETE_AUTHORIZATION, std::move(packet)) { }

        void Read() override;

        std::string AuthorizationCode;
    };

    class HousingPhotoSharingClearAuthorization final : public ClientPacket
    {
    public:
        explicit HousingPhotoSharingClearAuthorization(WorldPacket&& packet) : ClientPacket(CMSG_HOUSING_PHOTO_SHARING_CLEAR_AUTHORIZATION, std::move(packet)) { }

        void Read() override;
    };

    // Invite Player to Neighborhood
    class InvitePlayerToNeighborhood final : public ClientPacket
    {
    public:
        explicit InvitePlayerToNeighborhood(WorldPacket&& packet) : ClientPacket(CMSG_INVITE_PLAYER_TO_NEIGHBORHOOD, std::move(packet)) { }

        void Read() override;

        ObjectGuid TargetPlayerGUID;
        uint32 NeighborhoodID = 0;
    };

    // Query Neighborhood Info
    class QueryNeighborhoodInfo final : public ClientPacket
    {
    public:
        explicit QueryNeighborhoodInfo(WorldPacket&& packet) : ClientPacket(CMSG_QUERY_NEIGHBORHOOD_INFO, std::move(packet)) { }

        void Read() override;

        uint32 NeighborhoodID = 0;
    };

    // ============================================
    // SERVER PACKETS
    // ============================================

    // Blueprint Responses
    class HousingBlueprintExportResponse final : public ServerPacket
    {
    public:
        HousingBlueprintExportResponse() : ServerPacket(SMSG_HOUSING_BLUEPRINT_EXPORT_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
        uint32 BlueprintID = 0;
    };

    class HousingBlueprintGetResponse final : public ServerPacket
    {
    public:
        HousingBlueprintGetResponse() : ServerPacket(SMSG_HOUSING_BLUEPRINT_GET_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 BlueprintID = 0;
        std::string Name;
        std::string Description;
        uint32 TemplateID = 0;
        uint64 CreatedTime = 0;
        uint64 LastModified = 0;
        bool IsPublic = false;
        std::string ShareCode;
    };

    class HousingBlueprintImportResponse final : public ServerPacket
    {
    public:
        HousingBlueprintImportResponse() : ServerPacket(SMSG_HOUSING_BLUEPRINT_IMPORT_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingBlueprintRenameResponse final : public ServerPacket
    {
    public:
        HousingBlueprintRenameResponse() : ServerPacket(SMSG_HOUSING_BLUEPRINT_RENAME_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingBlueprintDeleteResponse final : public ServerPacket
    {
    public:
        HousingBlueprintDeleteResponse() : ServerPacket(SMSG_HOUSING_BLUEPRINT_DELETE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingBlueprintCheckResponse final : public ServerPacket
    {
    public:
        HousingBlueprintCheckResponse() : ServerPacket(SMSG_HOUSING_BLUEPRINT_CHECK_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 BlueprintID = 0;
        bool IsValid = false;
    };

    // Decor Responses
    class HousingDecorAddToHouseChestResponse final : public ServerPacket
    {
    public:
        HousingDecorAddToHouseChestResponse() : ServerPacket(SMSG_HOUSING_DECOR_ADD_TO_HOUSE_CHEST_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingDecorDeleteFromStorageResponse final : public ServerPacket
    {
    public:
        HousingDecorDeleteFromStorageResponse() : ServerPacket(SMSG_HOUSING_DECOR_DELETE_FROM_STORAGE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingDecorLockResponse final : public ServerPacket
    {
    public:
        HousingDecorLockResponse() : ServerPacket(SMSG_HOUSING_DECOR_LOCK_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingDecorMoveResponse final : public ServerPacket
    {
    public:
        HousingDecorMoveResponse() : ServerPacket(SMSG_HOUSING_DECOR_MOVE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingDecorPlaceResponse final : public ServerPacket
    {
    public:
        HousingDecorPlaceResponse() : ServerPacket(SMSG_HOUSING_DECOR_PLACE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
        uint32 PlacementID = 0;
    };

    class HousingDecorRemoveResponse final : public ServerPacket
    {
    public:
        HousingDecorRemoveResponse() : ServerPacket(SMSG_HOUSING_DECOR_REMOVE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingDecorRequestStorageResponse final : public ServerPacket
    {
    public:
        HousingDecorRequestStorageResponse() : ServerPacket(SMSG_HOUSING_DECOR_REQUEST_STORAGE_RESPONSE) { }

        WorldPacket const* Write() override;

        std::vector<uint32> DecorDefinitionIDs;
        std::vector<uint16> Quantities;
    };

    class HousingDecorSetDyeSlotsResponse final : public ServerPacket
    {
    public:
        HousingDecorSetDyeSlotsResponse() : ServerPacket(SMSG_HOUSING_DECOR_SYSTEM_SET_DYE_SLOTS_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingDecorSetEditModeResponse final : public ServerPacket
    {
    public:
        HousingDecorSetEditModeResponse() : ServerPacket(SMSG_HOUSING_DECOR_SET_EDIT_MODE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    // Fixture Responses
    class HousingFixtureCreateFixtureResponse final : public ServerPacket
    {
    public:
        HousingFixtureCreateFixtureResponse() : ServerPacket(SMSG_HOUSING_FIXTURE_CREATE_FIXTURE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
        uint32 FixtureID = 0;
    };

    class HousingFixtureDeleteFixtureResponse final : public ServerPacket
    {
    public:
        HousingFixtureDeleteFixtureResponse() : ServerPacket(SMSG_HOUSING_FIXTURE_DELETE_FIXTURE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingFixtureSetCoreFixtureResponse final : public ServerPacket
    {
    public:
        HousingFixtureSetCoreFixtureResponse() : ServerPacket(SMSG_HOUSING_FIXTURE_SET_CORE_FIXTURE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingFixtureSetEditModeResponse final : public ServerPacket
    {
    public:
        HousingFixtureSetEditModeResponse() : ServerPacket(SMSG_HOUSING_FIXTURE_SET_EDIT_MODE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingFixtureSetHouseSizeResponse final : public ServerPacket
    {
    public:
        HousingFixtureSetHouseSizeResponse() : ServerPacket(SMSG_HOUSING_FIXTURE_SET_HOUSE_SIZE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingFixtureSetHouseTypeResponse final : public ServerPacket
    {
    public:
        HousingFixtureSetHouseTypeResponse() : ServerPacket(SMSG_HOUSING_FIXTURE_SET_HOUSE_TYPE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    // House Info Responses
    class HousingGetCurrentHouseInfoResponse final : public ServerPacket
    {
    public:
        HousingGetCurrentHouseInfoResponse() : ServerPacket(SMSG_HOUSING_GET_CURRENT_HOUSE_INFO_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 HouseID = 0;
        uint32 NeighborhoodID = 0;
        uint32 PlotID = 0;
        uint32 TemplateID = 0;
        uint8 HouseLevel = 1;
        uint32 HouseXP = 0;
        uint32 XPNeededForNextLevel = 100;
        std::string HouseName;
        uint8 ExteriorLockState = 0;
        uint8 InteriorLockState = 0;
    };

    class HousingGetPlayerPermissionsResponse final : public ServerPacket
    {
    public:
        HousingGetPlayerPermissionsResponse() : ServerPacket(SMSG_HOUSING_GET_PLAYER_PERMISSIONS_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 HouseID = 0;
        bool ExteriorAccess = false;
        bool InteriorAccess = false;
        bool CanEdit = false;
    };

    class HousingHouseStatusResponse final : public ServerPacket
    {
    public:
        HousingHouseStatusResponse() : ServerPacket(SMSG_HOUSING_HOUSE_STATUS_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 HouseID = 0;
        bool IsActive = false;
    };

    class HousingResetHouseResponse final : public ServerPacket
    {
    public:
        HousingResetHouseResponse() : ServerPacket(SMSG_HOUSING_RESET_HOUSE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingResetKioskModeResponse final : public ServerPacket
    {
    public:
        HousingResetKioskModeResponse() : ServerPacket(SMSG_HOUSING_RESET_KIOSK_MODE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    // Room Responses
    class HousingRoomAddResponse final : public ServerPacket
    {
    public:
        HousingRoomAddResponse() : ServerPacket(SMSG_HOUSING_ROOM_ADD_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
        uint32 RoomID = 0;
    };

    class HousingRoomApplyComponentMaterialsResponse final : public ServerPacket
    {
    public:
        HousingRoomApplyComponentMaterialsResponse() : ServerPacket(SMSG_HOUSING_ROOM_APPLY_COMPONENT_MATERIALS_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingRoomRemoveResponse final : public ServerPacket
    {
    public:
        HousingRoomRemoveResponse() : ServerPacket(SMSG_HOUSING_ROOM_REMOVE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingRoomSetCeilingTypeResponse final : public ServerPacket
    {
    public:
        HousingRoomSetCeilingTypeResponse() : ServerPacket(SMSG_HOUSING_ROOM_SET_CEILING_TYPE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingRoomSetComponentThemeResponse final : public ServerPacket
    {
    public:
        HousingRoomSetComponentThemeResponse() : ServerPacket(SMSG_HOUSING_ROOM_SET_COMPONENT_THEME_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingRoomSetDoorTypeResponse final : public ServerPacket
    {
    public:
        HousingRoomSetDoorTypeResponse() : ServerPacket(SMSG_HOUSING_ROOM_SET_DOOR_TYPE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingRoomSetLayoutEditModeResponse final : public ServerPacket
    {
    public:
        HousingRoomSetLayoutEditModeResponse() : ServerPacket(SMSG_HOUSING_ROOM_SET_LAYOUT_EDIT_MODE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    // Housing Services Responses
    class HousingSvcsAcceptNeighborhoodOwnershipResponse final : public ServerPacket
    {
    public:
        HousingSvcsAcceptNeighborhoodOwnershipResponse() : ServerPacket(SMSG_HOUSING_SVCS_ACCEPT_NEIGHBORHOOD_OWNERSHIP_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingSvcsDeleteAllNeighborhoodInvitesResponse final : public ServerPacket
    {
    public:
        HousingSvcsDeleteAllNeighborhoodInvitesResponse() : ServerPacket(SMSG_HOUSING_SVCS_DELETE_ALL_NEIGHBORHOOD_INVITES_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingSvcsGetBnetFriendNeighborhoodsResponse final : public ServerPacket
    {
    public:
        HousingSvcsGetBnetFriendNeighborhoodsResponse() : ServerPacket(SMSG_HOUSING_SVCS_GET_BNET_FRIEND_NEIGHBORHOODS_RESPONSE) { }

        WorldPacket const* Write() override;

        std::vector<uint32> NeighborhoodIDs;
    };

    class HousingSvcsGetHouseFinderInfoResponse final : public ServerPacket
    {
    public:
        HousingSvcsGetHouseFinderInfoResponse() : ServerPacket(SMSG_HOUSING_SVCS_GET_HOUSE_FINDER_INFO_RESPONSE) { }

        WorldPacket const* Write() override;

        std::vector<uint32> AvailableNeighborhoodIDs;
    };

    class HousingSvcsGetHouseFinderNeighborhoodResponse final : public ServerPacket
    {
    public:
        HousingSvcsGetHouseFinderNeighborhoodResponse() : ServerPacket(SMSG_HOUSING_SVCS_GET_HOUSE_FINDER_NEIGHBORHOOD_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 NeighborhoodID = 0;
        std::string NeighborhoodName;
        uint32 Type = 0;
        uint32 Faction = 0;
        std::vector<uint32> AvailablePlotIDs;
    };

    class HousingSvcsGetPlayerHousesInfoResponse final : public ServerPacket
    {
    public:
        HousingSvcsGetPlayerHousesInfoResponse() : ServerPacket(SMSG_HOUSING_SVCS_GET_PLAYER_HOUSES_INFO_RESPONSE) { }

        WorldPacket const* Write() override;

        struct HouseInfo
        {
            uint32 HouseID = 0;
            uint32 NeighborhoodID = 0;
            uint32 PlotID = 0;
            uint32 TemplateID = 0;
            uint8 HouseLevel = 1;
            uint32 HouseXP = 0;
            std::string HouseName;
        };

        std::vector<HouseInfo> Houses;
    };

    class HousingSvcsGetPotentialHouseOwnersResponse final : public ServerPacket
    {
    public:
        HousingSvcsGetPotentialHouseOwnersResponse() : ServerPacket(SMSG_HOUSING_SVCS_GET_POTENTIAL_HOUSE_OWNERS_RESPONSE) { }

        WorldPacket const* Write() override;

        std::vector<ObjectGuid> PlayerGUIDs;
    };
        
    class HousingSvcsNeighborhoodReservePlotResponse final : public ServerPacket
    {
    public:
        HousingSvcsNeighborhoodReservePlotResponse() : ServerPacket(SMSG_HOUSING_SVCS_NEIGHBORHOOD_RESERVE_PLOT_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
        uint32 PlotID = 0;
    };

    class HousingSvcsRejectNeighborhoodOwnershipResponse final : public ServerPacket
    {
    public:
        HousingSvcsRejectNeighborhoodOwnershipResponse() : ServerPacket(SMSG_HOUSING_SVCS_REJECT_NEIGHBORHOOD_OWNERSHIP_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingSvcsRelinquishHouseResponse final : public ServerPacket
    {
    public:
        HousingSvcsRelinquishHouseResponse() : ServerPacket(SMSG_HOUSING_SVCS_RELINQUISH_HOUSE_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HousingSvcsUpdateHouseSettingsResponse final : public ServerPacket
    {
    public:
        HousingSvcsUpdateHouseSettingsResponse() : ServerPacket(SMSG_HOUSING_SVCS_UPDATE_HOUSE_SETTINGS_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    // House Exterior Responses
    class HouseExteriorLockResponse final : public ServerPacket
    {
    public:
        HouseExteriorLockResponse() : ServerPacket(SMSG_HOUSE_EXTERIOR_LOCK_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };

    class HouseExteriorSetHousePositionResponse final : public ServerPacket
    {
    public:
        HouseExteriorSetHousePositionResponse() : ServerPacket(SMSG_HOUSE_EXTERIOR_SET_HOUSE_POSITION_RESPONSE) { }

        WorldPacket const* Write() override;

        uint32 Result = 0;
    };
}

#endif // TRINITYCORE_HOUSING_PACKETS_H
