// This file is auto-generated - showing only housing-related opcode handlers
// All housing opcodes now properly registered to their handler implementations

// Neighborhood Management Handlers
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_BUY_HOUSE,                             STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodBuyHouse);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_MOVE_HOUSE,                            STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodMoveHouse);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_INVITE_RESIDENT,                       STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodInviteResident);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_CANCEL_INVITATION,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodCancelInvitation);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_PLAYER_DECLINE_INVITE,                 STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodPlayerDeclineInvite);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_PLAYER_GET_INVITE,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodPlayerGetInvite);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_GET_INVITES,                           STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodGetInvites);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_GET_ROSTER,                            STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodGetRoster);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_UPDATE_NAME,                           STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodUpdateName);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_SET_PUBLIC_FLAG,                       STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodSetPublicFlag);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_EVICT_PLOT,                            STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodEvictPlot);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_OFFER_OWNERSHIP,                       STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodOfferOwnership);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_ADD_SECONDARY_OWNER,                   STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodAddSecondaryOwner);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_REMOVE_SECONDARY_OWNER,                STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodRemoveSecondaryOwner);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_OPEN_CORNERSTONE_UI,                   STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodOpenCornerstoneUI);

// Charter System Handlers
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_CHARTER_OPEN_CONFIRMATION_UI,          STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodCharterOpenConfirmationUI);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_CHARTER_CREATE,                        STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodCharterCreate);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_CHARTER_EDIT,                          STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodCharterEdit);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_CHARTER_FINALIZE,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodCharterFinalize);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_CHARTER_SEND_SIGNATURE_REQUEST,        STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodCharterSendSignatureRequest);
DEFINE_HANDLER(CMSG_NEIGHBORHOOD_CHARTER_ADD_SIGNATURE,                 STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleNeighborhoodCharterAddSignature);

// Housing Services Handlers
DEFINE_HANDLER(CMSG_HOUSING_SVCS_GET_PLAYER_HOUSES_INFO,                STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsGetPlayerHousesInfo);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_TELEPORT_TO_PLOT,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsTeleportToPlot);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_RELINQUISH_HOUSE,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsRelinquishHouse);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_UPDATE_HOUSE_SETTINGS,                 STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsUpdateHouseSettings);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_GET_HOUSE_FINDER_INFO,                 STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsGetHouseFinderInfo);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_GET_HOUSE_FINDER_NEIGHBORHOOD,         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsGetHouseFinderNeighborhood);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_HOUSE_FINDER_IGNORE_NEIGHBORHOOD,      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsHouseFinderIgnoreNeighborhood);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_GET_POTENTIAL_HOUSE_OWNERS,            STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsGetPotentialHouseOwners);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_NEIGHBORHOOD_RESERVE_PLOT,             STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsNeighborhoodReservePlot);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_GUILD_CREATE_NEIGHBORHOOD,             STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsGuildCreateNeighborhood);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_ACCEPT_NEIGHBORHOOD_OWNERSHIP,         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsAcceptNeighborhoodOwnership);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_REJECT_NEIGHBORHOOD_OWNERSHIP,         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsRejectNeighborhoodOwnership);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_DELETE_ALL_NEIGHBORHOOD_INVITES,       STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsDeleteAllNeighborhoodInvites);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_GET_BNET_FRIEND_NEIGHBORHOODS,         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsGetBnetFriendNeighborhoods);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_PLAYER_VIEW_HOUSES_BY_PLAYER,          STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsPlayerViewHousesByPlayer);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_PLAYER_VIEW_HOUSES_BY_BNET_ACCOUNT,    STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsPlayerViewHousesByBnetAccount);
DEFINE_HANDLER(CMSG_HOUSING_SVCS_START_TUTORIAL,                        STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingSvcsStartTutorial);

// Decor Management Handlers
DEFINE_HANDLER(CMSG_HOUSING_DECOR_SET_EDIT_MODE,                        STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorSetEditMode);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_PLACE,                                STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorPlace);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_MOVE,                                 STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorMove);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_REMOVE,                               STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorRemove);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_LOCK,                                 STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorLock);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_SET_PET,                              STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorSetPet);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_SET_DYE_SLOTS,                        STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorSetDyeSlots);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_REQUEST_STORAGE,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorRequestStorage);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_DELETE_FROM_STORAGE,                  STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorDeleteFromStorage);
DEFINE_HANDLER(CMSG_HOUSING_DECOR_REDEEM_DEFERRED_DECOR,                STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingDecorRedeemDeferredDecor);

// Room Management Handlers
DEFINE_HANDLER(CMSG_HOUSING_ROOM_SET_LAYOUT_EDIT_MODE,                  STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomSetLayoutEditMode);
DEFINE_HANDLER(CMSG_HOUSING_ROOM_ADD,                                   STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomAdd);
DEFINE_HANDLER(CMSG_HOUSING_ROOM_REMOVE,                                STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomRemove);
DEFINE_HANDLER(CMSG_HOUSING_ROOM_MOVE,                                  STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomMove);
DEFINE_HANDLER(CMSG_HOUSING_ROOM_ROTATE,                                STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomRotate);
DEFINE_HANDLER(CMSG_HOUSING_ROOM_SET_COMPONENT_THEME,                   STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomSetComponentTheme);
DEFINE_HANDLER(CMSG_HOUSING_ROOM_APPLY_COMPONENT_MATERIALS,             STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomApplyComponentMaterials);
DEFINE_HANDLER(CMSG_HOUSING_ROOM_SET_CEILING_TYPE,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomSetCeilingType);
DEFINE_HANDLER(CMSG_HOUSING_ROOM_SET_DOOR_TYPE,                         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingRoomSetDoorType);

// Fixture Management Handlers
DEFINE_HANDLER(CMSG_HOUSING_FIXTURE_SET_EDIT_MODE,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingFixtureSetEditMode);
DEFINE_HANDLER(CMSG_HOUSING_FIXTURE_SET_CORE_FIXTURE,                   STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingFixtureSetCoreFixture);
DEFINE_HANDLER(CMSG_HOUSING_FIXTURE_SET_HOUSE_TYPE,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingFixtureSetHouseType);
DEFINE_HANDLER(CMSG_HOUSING_FIXTURE_SET_HOUSE_SIZE,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingFixtureSetHouseSize);
DEFINE_HANDLER(CMSG_HOUSING_FIXTURE_CREATE_FIXTURE,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingFixtureCreateFixture);
DEFINE_HANDLER(CMSG_HOUSING_FIXTURE_DELETE_FIXTURE,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingFixtureDeleteFixture);

// Blueprint Management Handlers
DEFINE_HANDLER(CMSG_HOUSING_BLUEPRINT_REQUEST_COLLECTION,               STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingBlueprintRequestCollection);
DEFINE_HANDLER(CMSG_HOUSING_BLUEPRINT_REQUEST_CONTENTS,                 STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingBlueprintRequestContents);
DEFINE_HANDLER(CMSG_HOUSING_BLUEPRINT_EXPORT,                           STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingBlueprintExport);
DEFINE_HANDLER(CMSG_HOUSING_BLUEPRINT_IMPORT,                           STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingBlueprintImport);
DEFINE_HANDLER(CMSG_HOUSING_BLUEPRINT_RENAME,                           STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingBlueprintRename);
DEFINE_HANDLER(CMSG_HOUSING_BLUEPRINT_DELETE,                           STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingBlueprintDelete);

// House Info Handlers
DEFINE_HANDLER(CMSG_HOUSING_GET_CURRENT_HOUSE_INFO,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingGetCurrentHouseInfo);
DEFINE_HANDLER(CMSG_HOUSING_GET_PLAYER_PERMISSIONS,                     STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingGetPlayerPermissions);
DEFINE_HANDLER(CMSG_HOUSING_HOUSE_STATUS,                               STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingHouseStatus);
DEFINE_HANDLER(CMSG_HOUSING_RESET_HOUSE,                                STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingResetHouse);
DEFINE_HANDLER(CMSG_HOUSING_RESET_KIOSK_MODE,                           STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingResetKioskMode);

// House Exterior Handlers
DEFINE_HANDLER(CMSG_HOUSE_EXTERIOR_SET_HOUSE_POSITION,                  STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHouseExteriorSetHousePosition);
DEFINE_HANDLER(CMSG_HOUSE_INTERIOR_LEAVE_HOUSE,                         STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHouseInteriorLeaveHouse);

// Initiative Handler
DEFINE_HANDLER(CMSG_INITIATIVE_UPDATE_ACTIVE_NEIGHBORHOOD,              STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleInitiativeUpdateActiveNeighborhood);

// Photo Sharing Handlers
DEFINE_HANDLER(CMSG_HOUSING_PHOTO_SHARING_COMPLETE_AUTHORIZATION,       STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingPhotoSharingCompleteAuthorization);
DEFINE_HANDLER(CMSG_HOUSING_PHOTO_SHARING_CLEAR_AUTHORIZATION,          STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleHousingPhotoSharingClearAuthorization);

// Invite Player to Neighborhood
DEFINE_HANDLER(CMSG_INVITE_PLAYER_TO_NEIGHBORHOOD,                      STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleInvitePlayerToNeighborhood);

// Query Neighborhood Info
DEFINE_HANDLER(CMSG_QUERY_NEIGHBORHOOD_INFO,                            STATUS_LOGGEDIN,  PROCESS_THREADUNSAFE, &WorldSession::HandleQueryNeighborhoodInfo);