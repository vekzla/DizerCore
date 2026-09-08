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
  
#include "HousingPackets.h"  
#include "PacketOperators.h"  
  
namespace WorldPackets::Housing  
{  
void DeclineNeighborhoodInvites::Read()  
{  
    _worldPacket >> Bits<1>(Allow);  
}  
  
// Client Packet Read Methods  
  
void NeighborhoodBuyHouse::Read()  
{  
    _worldPacket >> PlotID;  
    _worldPacket >> HouseTemplateID;  
    HouseName = _worldPacket.ReadCString();  
}  
  
void NeighborhoodMoveHouse::Read()  
{  
    _worldPacket >> NewPlotID;  
}  
  
void NeighborhoodInviteResident::Read()  
{  
    _worldPacket >> TargetPlayerGUID;  
    _worldPacket >> NeighborhoodID;  
}  
  
void NeighborhoodCancelInvitation::Read()  
{  
    _worldPacket >> InvitationID;  
}  
  
void NeighborhoodPlayerDeclineInvite::Read()  
{  
    _worldPacket >> InvitationID;  
}  
  
void NeighborhoodPlayerGetInvite::Read()  
{  
    // No additional data to read  
}  
  
void NeighborhoodGetInvites::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
void NeighborhoodGetRoster::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
void NeighborhoodUpdateName::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    NewName = _worldPacket.ReadCString();  
}  
  
void NeighborhoodSetPublicFlag::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    _worldPacket >> Bits<1>(IsPublic);  
}  
  
void NeighborhoodEvictPlot::Read()  
{  
    _worldPacket >> PlotID;  
}  
  
void NeighborhoodOfferOwnership::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    _worldPacket >> TargetPlayerGUID;  
}  
  
void NeighborhoodAddSecondaryOwner::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    _worldPacket >> TargetPlayerGUID;  
}  
  
void NeighborhoodRemoveSecondaryOwner::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    _worldPacket >> TargetPlayerGUID;  
}  
  
void NeighborhoodOpenCornerstoneUI::Read()  
{  
    _worldPacket >> PlotID;  
}  
  
void NeighborhoodCharterOpenConfirmationUI::Read()  
{  
    // No additional data to read  
}  
  
void NeighborhoodCharterCreate::Read()  
{  
    NeighborhoodName = _worldPacket.ReadCString();  
    _worldPacket >> Faction;  
}  
  
void NeighborhoodCharterEdit::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    NewName = _worldPacket.ReadCString();  
}  
  
void NeighborhoodCharterFinalize::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
void NeighborhoodCharterSendSignatureRequest::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    _worldPacket >> TargetPlayerGUID;  
}  
  
void NeighborhoodCharterAddSignature::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
void HousingSvcsGetPlayerHousesInfo::Read()  
{  
    // No additional data to read  
}  
  
void HousingSvcsTeleportToPlot::Read()  
{  
    _worldPacket >> HouseID;  
}  
  
void HousingSvcsRelinquishHouse::Read()  
{  
    _worldPacket >> HouseID;  
}  
  
void HousingSvcsUpdateHouseSettings::Read()  
{  
    _worldPacket >> HouseID;  
    HouseName = _worldPacket.ReadCString();  
    _worldPacket >> ExteriorLockState;  
    _worldPacket >> InteriorLockState;  
}  
  
void HousingSvcsGetHouseFinderInfo::Read()  
{  
    // No additional data to read  
}  
  
void HousingSvcsGetHouseFinderNeighborhood::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
void HousingSvcsHouseFinderIgnoreNeighborhood::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    _worldPacket >> Bits<1>(Ignore);  
}  
  
void HousingSvcsGetPotentialHouseOwners::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
void HousingSvcsNeighborhoodReservePlot::Read()  
{  
    _worldPacket >> NeighborhoodID;  
    _worldPacket >> PlotNumber;  
}  
  
void HousingSvcsGuildCreateNeighborhood::Read()  
{  
    NeighborhoodName = _worldPacket.ReadCString();  
    _worldPacket >> Faction;  
}  
  
void HousingSvcsAcceptNeighborhoodOwnership::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
void HousingSvcsRejectNeighborhoodOwnership::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
void HousingSvcsDeleteAllNeighborhoodInvites::Read()  
{  
    // No additional data to read  
}  
  
void HousingSvcsGetBnetFriendNeighborhoods::Read()  
{  
    // No additional data to read  
}  
  
void HousingSvcsPlayerViewHousesByPlayer::Read()  
{  
    _worldPacket >> PlayerGUID;  
}  
  
void HousingSvcsPlayerViewHousesByBnetAccount::Read()  
{  
    _worldPacket >> BnetAccountID;  
}  
  
void HousingSvcsStartTutorial::Read()  
{  
    // No additional data to read  
}  
  
void HousingDecorSetEditMode::Read()  
{  
    _worldPacket >> Bits<1>(EditMode);  
}  
  
void HousingDecorPlace::Read()  
{  
    _worldPacket >> DecorDefinitionID;  
    _worldPacket >> RoomID;  
    _worldPacket >> PositionX;  
    _worldPacket >> PositionY;  
    _worldPacket >> PositionZ;  
    _worldPacket >> Orientation;  
    _worldPacket >> Scale;  
    _worldPacket >> Bits<1>(IsExterior);  
}  
  
void HousingDecorMove::Read()  
{  
    _worldPacket >> PlacementID;  
    _worldPacket >> PositionX;  
    _worldPacket >> PositionY;  
    _worldPacket >> PositionZ;  
    _worldPacket >> Orientation;  
    _worldPacket >> Scale;  
}  
  
void HousingDecorRemove::Read()  
{  
    _worldPacket >> PlacementID;  
}  
  
void HousingDecorLock::Read()  
{  
    _worldPacket >> PlacementID;  
    _worldPacket >> Bits<1>(Lock);  
}  
  
void HousingDecorSetPet::Read()  
{  
    _worldPacket >> PlacementID;  
    _worldPacket >> PetGUID;  
}  
  
void HousingDecorSetDyeSlots::Read()  
{  
    _worldPacket >> PlacementID;  
    _worldPacket >> DyeSlot1;  
    _worldPacket >> DyeSlot2;  
    _worldPacket >> DyeSlot3;  
}  
  
void HousingDecorRequestStorage::Read()  
{  
    _worldPacket >> HouseID;  
}  
  
void HousingDecorDeleteFromStorage::Read()  
{  
    _worldPacket >> StorageID;  
}  
  
void HousingDecorRedeemDeferredDecor::Read()  
{  
    _worldPacket >> DeferredDecorID;  
}  
  
void HousingRoomSetLayoutEditMode::Read()  
{  
    _worldPacket >> Bits<1>(EditMode);  
}  
  
void HousingRoomAdd::Read()  
{  
    _worldPacket >> RoomTemplateID;  
    _worldPacket >> PositionX;  
    _worldPacket >> PositionY;  
    _worldPacket >> PositionZ;  
    _worldPacket >> Orientation;  
}  
  
void HousingRoomRemove::Read()  
{  
    _worldPacket >> RoomID;  
}  
  
void HousingRoomMove::Read()  
{  
    _worldPacket >> RoomID;  
    _worldPacket >> PositionX;  
    _worldPacket >> PositionY;  
    _worldPacket >> PositionZ;  
    _worldPacket >> Orientation;  
}  
  
void HousingRoomRotate::Read()  
{  
    _worldPacket >> RoomID;  
    _worldPacket >> Orientation;  
}  
  
void HousingRoomSetComponentTheme::Read()  
{  
    _worldPacket >> RoomID;  
    _worldPacket >> ThemeID;  
}  
  
void HousingRoomApplyComponentMaterials::Read()  
{  
    _worldPacket >> RoomID;  
    _worldPacket >> MaterialID;  
}  
  
void HousingRoomSetCeilingType::Read()  
{  
    _worldPacket >> RoomID;  
    _worldPacket >> CeilingType;  
}  
  
void HousingRoomSetDoorType::Read()  
{  
    _worldPacket >> RoomID;  
    _worldPacket >> DoorType;  
}  
  
void HousingFixtureSetEditMode::Read()  
{  
    _worldPacket >> Bits<1>(EditMode);  
}  
  
void HousingFixtureSetCoreFixture::Read()  
{  
    _worldPacket >> FixtureDefinitionID;  
}  
  
void HousingFixtureSetHouseType::Read()  
{  
    _worldPacket >> HouseTemplateID;  
}  
  
void HousingFixtureSetHouseSize::Read()  
{  
    _worldPacket >> HouseSize;  
}  
  
void HousingFixtureCreateFixture::Read()  
{  
    _worldPacket >> FixtureDefinitionID;  
    _worldPacket >> PositionX;  
    _worldPacket >> PositionY;  
    _worldPacket >> PositionZ;  
    _worldPacket >> Orientation;  
}  
  
void HousingFixtureDeleteFixture::Read()  
{  
    _worldPacket >> FixtureID;  
}  
  
void HousingBlueprintRequestCollection::Read()  
{  
    // No additional data to read  
}  
  
void HousingBlueprintRequestContents::Read()  
{  
    _worldPacket >> BlueprintID;  
}  
  
void HousingBlueprintExport::Read()  
{  
    BlueprintName = _worldPacket.ReadCString();  
    Description = _worldPacket.ReadCString();  
    _worldPacket >> Bits<1>(IsPublic);  
}  
  
void HousingBlueprintImport::Read()  
{  
    _worldPacket >> BlueprintID;  
}  
  
void HousingBlueprintRename::Read()  
{  
    _worldPacket >> BlueprintID;  
    NewName = _worldPacket.ReadCString();  
}  
  
void HousingBlueprintDelete::Read()  
{  
    _worldPacket >> BlueprintID;  
}  
  
void HousingGetCurrentHouseInfo::Read()  
{  
    // No additional data to read  
}  
  
void HousingGetPlayerPermissions::Read()  
{  
    _worldPacket >> HouseID;  
}  
  
void HousingHouseStatus::Read()  
{  
    _worldPacket >> HouseID;  
}  
  
void HousingResetHouse::Read()  
{  
    _worldPacket >> HouseID;  
}  
  
void HousingResetKioskMode::Read()  
{  
    // No additional data to read  
}  
  
void HouseExteriorSetHousePosition::Read()  
{  
    _worldPacket >> PositionX;  
    _worldPacket >> PositionY;  
    _worldPacket >> PositionZ;  
    _worldPacket >> Orientation;  
}  
  
void HouseInteriorLeaveHouse::Read()  
{  
    // No additional data to read  
}  
  
void InitiativeUpdateActiveNeighborhood::Read()  
{  
    _worldPacket >> HouseID;  
}  
  
void HousingPhotoSharingCompleteAuthorization::Read()  
{  
    AuthorizationCode = _worldPacket.ReadCString();  
}  
  
void HousingPhotoSharingClearAuthorization::Read()  
{  
    // No additional data to read  
}  
  
void InvitePlayerToNeighborhood::Read()  
{  
    _worldPacket >> TargetPlayerGUID;  
    _worldPacket >> NeighborhoodID;  
}  
  
void QueryNeighborhoodInfo::Read()  
{  
    _worldPacket >> NeighborhoodID;  
}  
  
// Server Packet Write Methods  
  
WorldPacket const* HousingBlueprintExportResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    _worldPacket << uint32(BlueprintID);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingBlueprintGetResponse::Write()  
{  
    _worldPacket << uint32(BlueprintID);  
    _worldPacket << Name;  
    _worldPacket << Description;  
    _worldPacket << uint32(TemplateID);  
    _worldPacket << uint64(CreatedTime);  
    _worldPacket << uint64(LastModified);  
    _worldPacket << uint8(IsPublic);  
    _worldPacket << ShareCode;  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingBlueprintImportResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingBlueprintRenameResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingBlueprintDeleteResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingBlueprintCheckResponse::Write()  
{  
    _worldPacket << uint32(BlueprintID);  
    _worldPacket << uint8(IsValid);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorAddToHouseChestResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorDeleteFromStorageResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorLockResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorMoveResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorPlaceResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    _worldPacket << uint32(PlacementID);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorRemoveResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorRequestStorageResponse::Write()  
{  
    _worldPacket << uint32(DecorDefinitionIDs.size());  
    for (uint32 decorID : DecorDefinitionIDs)  
        _worldPacket << uint32(decorID);  
  
    _worldPacket << uint32(Quantities.size());  
    for (uint16 quantity : Quantities)  
        _worldPacket << uint16(quantity);  
  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorSetDyeSlotsResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingDecorSetEditModeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingFixtureCreateFixtureResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    _worldPacket << uint32(FixtureID);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingFixtureDeleteFixtureResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingFixtureSetCoreFixtureResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingFixtureSetEditModeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingFixtureSetHouseSizeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingFixtureSetHouseTypeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingGetCurrentHouseInfoResponse::Write()  
{  
    _worldPacket << uint32(HouseID);  
    _worldPacket << uint32(NeighborhoodID);  
    _worldPacket << uint32(PlotID);  
    _worldPacket << uint32(TemplateID);  
    _worldPacket << uint8(HouseLevel);  
    _worldPacket << uint32(HouseXP);  
    _worldPacket << uint32(XPNeededForNextLevel);  
    _worldPacket << HouseName;  
    _worldPacket << uint8(ExteriorLockState);  
    _worldPacket << uint8(InteriorLockState);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingGetPlayerPermissionsResponse::Write()  
{  
    _worldPacket << uint32(HouseID);  
    _worldPacket << uint8(ExteriorAccess);  
    _worldPacket << uint8(InteriorAccess);  
    _worldPacket << uint8(CanEdit);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingHouseStatusResponse::Write()  
{  
    _worldPacket << uint32(HouseID);  
    _worldPacket << uint8(IsActive);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingResetHouseResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingResetKioskModeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingRoomAddResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    _worldPacket << uint32(RoomID);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingRoomApplyComponentMaterialsResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingRoomRemoveResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingRoomSetCeilingTypeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingRoomSetComponentThemeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingRoomSetDoorTypeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingRoomSetLayoutEditModeResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsAcceptNeighborhoodOwnershipResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsDeleteAllNeighborhoodInvitesResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsGetBnetFriendNeighborhoodsResponse::Write()  
{  
    _worldPacket << uint32(NeighborhoodIDs.size());  
    for (uint32 neighborhoodID : NeighborhoodIDs)  
        _worldPacket << uint32(neighborhoodID);  
  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsGetHouseFinderInfoResponse::Write()  
{  
    _worldPacket << uint32(AvailableNeighborhoodIDs.size());  
    for (uint32 neighborhoodID : AvailableNeighborhoodIDs)  
        _worldPacket << uint32(neighborhoodID);  
  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsGetHouseFinderNeighborhoodResponse::Write()  
{  
    _worldPacket << uint32(NeighborhoodID);  
    _worldPacket << NeighborhoodName;  
    _worldPacket << uint32(Type);  
    _worldPacket << uint32(Faction);  
  
    _worldPacket << uint32(AvailablePlotIDs.size());  
    for (uint32 plotID : AvailablePlotIDs)  
        _worldPacket << uint32(plotID);  
  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsGetPlayerHousesInfoResponse::Write()  
{  
    _worldPacket << uint32(Houses.size());  
    for (HouseInfo const& house : Houses)  
    {  
        _worldPacket << uint32(house.HouseID);  
        _worldPacket << uint32(house.NeighborhoodID);  
        _worldPacket << uint32(house.PlotID);  
        _worldPacket << uint32(house.TemplateID);  
        _worldPacket << uint8(house.HouseLevel);  
        _worldPacket << uint32(house.HouseXP);  
        _worldPacket << house.HouseName;  
    }  
  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsGetPotentialHouseOwnersResponse::Write()  
{  
    _worldPacket << uint32(PlayerGUIDs.size());  
    for (ObjectGuid const& guid : PlayerGUIDs)  
        _worldPacket << guid;  
  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsNeighborhoodReservePlotResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    _worldPacket << uint32(PlotID);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsRejectNeighborhoodOwnershipResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsRelinquishHouseResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HousingSvcsUpdateHouseSettingsResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HouseExteriorLockResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
  
WorldPacket const* HouseExteriorSetHousePositionResponse::Write()  
{  
    _worldPacket << uint32(Result);  
    return &_worldPacket;  
}  
}