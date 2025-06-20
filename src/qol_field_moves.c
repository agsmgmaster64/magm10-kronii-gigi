#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "field_control_avatar.h"
#include "field_move.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "fieldmap.h"
#include "fldeff.h"
#include "fldeff_misc.h"
#include "item.h"
#include "item_menu.h"
#include "item_use.h"
#include "map_name_popup.h"
#include "metatile_behavior.h"
#include "music_player.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "qol_field_moves.h"
#include "region_map.h"
#include "script.h"
#include "sound.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/map_types.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
#include "constants/songs.h"
#include "constants/vars.h"

static void FieldCallback_UseFlyTool(void);
static void Task_UseFlyTool(void);

static void Task_UseWaterfallTool(u8);

static void Task_UseDiveTool(u8);

static bool32 CanSpeciesLearnMoveLevelUp(u16 species, u16 move);
static bool32 SetMonResultVariables(u32 partyIndex, u32 species);

#define tState      data[0]
#define tFallOffset data[1]
#define tTotalFall  data[2]

static inline u32 GetFieldMoveUsage(u32 fieldMove, u32 item)
{
    if (PartyCanUseFieldMove(fieldMove, TRUE) || CheckBagHasItem(item, 1))
        return TRUE;
    return FALSE;
}

// Fly
void ReturnToFieldFromFlyToolMapSelect(void)
{
    SetMainCallback2(CB2_ReturnToField);
    gFieldCallback = Task_UseFlyTool;
}

static void Task_UseFlyTool(void)
{
    Overworld_ResetStateAfterFly();
    WarpIntoMap();
    SetMainCallback2(CB2_LoadMap);
    gFieldCallback = FieldCallback_UseFlyTool;
}

static void FieldCallback_UseFlyTool(void)
{
    Overworld_PlaySpecialMapMusic();
    FadeInFromBlack();
    if (gPaletteFade.active)
            return;

    UnlockPlayerFieldControls();
    UnfreezeObjectEvents();
    gFieldCallback = NULL;
}

bool32 IsFlyToolUsed(void)
{
    return (VarGet(VAR_FLY_TOOL_SOURCE));
}

void ReturnToFieldOrBagFromFlyTool(void)
{
    if (VarGet(VAR_FLY_TOOL_SOURCE) == FLY_SOURCE_BAG)
        GoToBagMenu(ITEMMENULOCATION_LAST, POCKET_KEY_ITEMS, CB2_ReturnToFullScreenStartMenu);
    else if (VarGet(VAR_FLY_TOOL_SOURCE) == FLY_SOURCE_FIELD)
        SetMainCallback2(CB2_ReturnToField);
}

void ResetFlyTool(void)
{
    VarSet(VAR_FLY_TOOL_SOURCE, FLY_SOURCE_MOVE);
}

u32 CanUseSurfFromInteractedWater(void)
{
    if (IsPlayerFacingSurfableFishableWater())
    {
        return GetFieldMoveUsage(FIELD_MOVE_SURF, ITEM_SURFBOARD);
    }

    return FALSE;
}

u8 FldEff_UseSurfTool(void)
{
    CreateTask(Task_SurfToolFieldEffect, 0);
    Overworld_ClearSavedMusic();
    Overworld_ChangeMusicTo(GetSurfMusic());
    return FALSE;
}

static void SurfToolFieldEffect_CheckHeldMovementStatus(struct Task *task)
{
    struct ObjectEvent *objectEvent;
    objectEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    if (ObjectEventCheckHeldMovementStatus(objectEvent))
        task->tState++;
}

static void (*const sSurfToolFieldEffectFuncs[])(struct Task *) =
{
    SurfFieldEffect_Init,
    SurfToolFieldEffect_CheckHeldMovementStatus,
    SurfFieldEffect_JumpOnSurfBlob,
    SurfFieldEffect_End,
};

void Task_SurfToolFieldEffect(u8 taskId)
{
    sSurfToolFieldEffectFuncs[gTasks[taskId].tState](&gTasks[taskId]);
}

void RemoveRelevantSurfFieldEffect(void)
{
    if (FieldEffectActiveListContains(FLDEFF_USE_SURF))
    {
        FieldEffectActiveListRemove(FLDEFF_USE_SURF);
        DestroyTask(FindTaskIdByFunc(Task_SurfFieldEffect));
    }
    else if(FieldEffectActiveListContains(FLDEFF_USE_SURF_TOOL))
    {
        FieldEffectActiveListRemove(FLDEFF_USE_SURF_TOOL);
        DestroyTask(FindTaskIdByFunc(Task_SurfToolFieldEffect));
    }
}

// Flash

void FldEff_UseFlashTool(void)
{
    HideMapNamePopUpWindow();
    PlaySE(SE_M_REFLECT);
    FlagSet(FLAG_SYS_USE_FLASH);
    ScriptContext_SetupScript(EventScript_UseLantern);
}

u32 CanUseFlashTool(void)
{
    bool32 playerIsInCave = (gMapHeader.cave == TRUE);
    bool32 mapIsNotLit = (GetFlashLevel() == (gMaxFlashLevel - 1));
    bool32 playerHasUsedFlash = FlagGet(FLAG_SYS_USE_FLASH);

    if (playerIsInCave && mapIsNotLit && !playerHasUsedFlash)
    {
        return TRUE;
    }
    return FALSE;
}

//Waterfall

u32 CanUseWaterfallFromInteractedWater(void)
{
    if (IsPlayerSurfingNorth())
    {
        return GetFieldMoveUsage(FIELD_MOVE_WATERFALL, ITEM_CLIMBING_GEAR);
    }

    return FALSE;
}

u32 CanUseWaterfallTool(void)
{
    struct ObjectEvent *playerObjEvent = &gObjectEvents[gPlayerAvatar.objectEventId];
    s16 x = playerObjEvent->currentCoords.x;
    s16 y = playerObjEvent->currentCoords.y;

    MoveCoords(playerObjEvent->facingDirection, &x, &y);
    if (GetCollisionAtCoords(playerObjEvent, x, y, playerObjEvent->facingDirection) == COLLISION_NONE
     && MetatileBehavior_IsWaterfall(MapGridGetMetatileBehaviorAt(x, y))
     && IsPlayerSurfingNorth())
    {
        return TRUE;
    }

    return FALSE;
}

static bool8 WaterfallToolFieldEffect_ContinueRideOrEnd(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (!ObjectEventClearHeldMovementIfFinished(objectEvent))
        return FALSE;

    if (MetatileBehavior_IsWaterfall(objectEvent->currentMetatileBehavior))
    {
        // Still ascending waterfall, back to WaterfallFieldEffect_RideUp
        task->tState = 1;
        return TRUE;
    }

    UnlockPlayerFieldControls();
    gPlayerAvatar.preventStep = FALSE;
    DestroyTask(FindTaskIdByFunc(Task_UseWaterfallTool));
    FieldEffectActiveListRemove(FLDEFF_USE_WATERFALL_TOOL);
    return FALSE;
    return WaterfallFieldEffect_ContinueRideOrEnd(task, objectEvent);
}

static bool8 (*const sWaterfallToolFieldEffectFuncs[])(struct Task *, struct ObjectEvent *) =
{
    WaterfallFieldEffect_Init,
    WaterfallFieldEffect_RideUp,
    WaterfallToolFieldEffect_ContinueRideOrEnd,
};

static void Task_UseWaterfallTool(u8 taskId)
{
    while (sWaterfallToolFieldEffectFuncs[gTasks[taskId].tState](&gTasks[taskId], &gObjectEvents[gPlayerAvatar.objectEventId]));
}

u8 FldEff_UseWaterfallTool(void)
{
    u8 taskId = CreateTask(Task_UseWaterfallTool, 0);
    Task_UseWaterfallTool(taskId);
    return FALSE;
}

void RemoveRelevantWaterfallFieldEffect(void)
{
    if (FieldEffectActiveListContains(FLDEFF_USE_WATERFALL))
    {
        FieldEffectActiveListRemove(FLDEFF_USE_WATERFALL);
        DestroyTask(FindTaskIdByFunc(Task_UseWaterfall));
    }
    else if(FieldEffectActiveListContains(FLDEFF_USE_WATERFALL_TOOL))
    {
        FieldEffectActiveListRemove(FLDEFF_USE_SURF_TOOL);
        DestroyTask(FindTaskIdByFunc(Task_UseWaterfallTool));
    }
}

// Dive

u32 CanUseDiveDown(void)
{
    if (TrySetDiveWarp() == 2)
    {
        return GetFieldMoveUsage(FIELD_MOVE_DIVE, ITEM_SCUBA_GEAR);
    }

    return FALSE;
}

u32 CanUseDiveEmerge(void)
{
    if (TrySetDiveWarp() == 1 && gMapHeader.mapType == MAP_TYPE_UNDERWATER)
    {
        return GetFieldMoveUsage(FIELD_MOVE_DIVE, ITEM_SCUBA_GEAR);
    }

    return FALSE;
}


static bool8 (*const sDiveToolFieldEffectFuncs[])(struct Task *) =
{
    DiveFieldEffect_Init,
    DiveFieldEffect_TryWarp,
};

bool8 FldEff_UseDiveTool(void)
{
    u8 taskId;
    taskId = CreateTask(Task_UseDiveTool, 0xFF);
    Task_UseDiveTool(taskId);
    return FALSE;
}

static void Task_UseDiveTool(u8 taskId)
{
    while (sDiveToolFieldEffectFuncs[gTasks[taskId].data[0]](&gTasks[taskId]));
}

void RemoveRelevantDiveFieldEffect(void)
{
    if (FieldEffectActiveListContains(FLDEFF_USE_DIVE))
    {
        FieldEffectActiveListRemove(FLDEFF_USE_DIVE);
        DestroyTask(FindTaskIdByFunc(Task_UseDive));
    }
    else if(FieldEffectActiveListContains(FLDEFF_USE_DIVE_TOOL))
    {
        FieldEffectActiveListRemove(FLDEFF_USE_SURF_TOOL);
        DestroyTask(FindTaskIdByFunc(Task_UseDiveTool));
    }
}

u32 CanUseRockClimbTool(void)
{
    s16 x, y;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);

    if (MetatileBehavior_IsRockClimbable(MapGridGetMetatileBehaviorAt(x, y)))
    {
        return TRUE;
    }

    return FALSE;
}

static bool32 CanSpeciesLearnMoveLevelUp(u16 species, u16 move)
{
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
    u32 i = 0;

    for (i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        if (learnset[i].move == move)
            return TRUE;
    }
    return FALSE;
}

bool32 PartyCanUseFieldMove(u32 fieldMove, bool32 doUnlockedCheck)
{
    struct Pokemon *mon;
    u32 species, i, monCanLearn, move, canUseMove;
    gSpecialVar_Result = PARTY_SIZE;
    gSpecialVar_0x8004 = 0;
    move = FieldMove_GetMoveId(fieldMove);

    if (doUnlockedCheck && !IsFieldMoveUnlocked(fieldMove))
        return FALSE;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        mon = &gPlayerParty[i];
        species = GetMonData(mon, MON_DATA_SPECIES, NULL);

        if (species == SPECIES_NONE)
            break;

        monCanLearn = CanTeachMove(mon, move);

        if (monCanLearn == ALREADY_KNOWS_MOVE)
            return SetMonResultVariables(i, species);

        if (CanSpeciesLearnMoveLevelUp(species, move) || monCanLearn == CAN_LEARN_MOVE)
        {
            return SetMonResultVariables(i, species);
        }
    }

    return FALSE;
}

static bool32 SetMonResultVariables(u32 partyIndex, u32 species)
{
    gSpecialVar_Result = partyIndex;
    gSpecialVar_0x8004 = species;
    return TRUE;
}

#undef tState
#undef tFallOffset
#undef tTotalFall
