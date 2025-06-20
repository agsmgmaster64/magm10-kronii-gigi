#include "global.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_icon.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_use.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "quests.h"
#include "overworld.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/field_weather.h"
#include "constants/songs.h"
#include "constants/rgb.h"
#include "constants/event_objects.h"
#include "event_object_movement.h"
#include "pokemon_icon.h"

#include "random.h"

#define tPageItems      data[4]
#define tItemPcParam    data[6]

struct QuestMenuResources
{
    MainCallback savedCallback;
    u8 moveModeOrigPos;
    u8 spriteIconSlot;
    u16 oldPaletteTag;
    u8 maxShowed;
    u8 nItems;
    u8 scrollIndicatorArrowPairId;
    s16 data[3];
    u8 filterMode;
    u8 parentQuest;
    bool8 restoreCursor;
};

struct QuestMenuStaticResources
{
    MainCallback savedCallback;
    u16 scroll;
    u16 row;
    u8 initialized;
    u16 storedScrollOffset;
    u16 storedRowPosition;
};

enum QuestColors
{
    QUESTCOLOR_HEADER,
    QUESTCOLOR_QUEST_REWARD,
    QUESTCOLOR_QUEST_DONE,
    QUESTCOLOR_QUEST_ACTIVE,
    QUESTCOLOR_FOOTER
};

// RAM
EWRAM_DATA static struct QuestMenuResources *sStateDataPtr = NULL;
EWRAM_DATA static u8 *sBg1TilemapBuffer = NULL;
EWRAM_DATA static struct ListMenuItem *sListMenuItems = NULL;
EWRAM_DATA static struct QuestMenuStaticResources sListMenuState = {0};
EWRAM_DATA static u8 sItemMenuIconSpriteIds[12] = {0};        // from pokefirered src/item_menu_icons.c
EWRAM_DATA static void *questNamePointer = NULL;
EWRAM_DATA static u8 **questNameArray = NULL;

// This File's Functions
void QuestMenu_Init(u8 a0, MainCallback callback);
static void MainCB(void);
static void VBlankCB(void);
static void RunSetup(void);

static bool8 SetupGraphics(void);
static bool8 LoadGraphics(void);
static void QuestMenu_InitWindows(void);
static bool8 InitBackgrounds(void);
static void InitItems(void);
static bool8 AllocateResourcesForListMenu(void);
static void AllocateMemoryForArray();
static void PlaceTopMenuScrollIndicatorArrows(void);
static void SetInitializedFlag(u8 a0);

static u8 GetCursorPosition(void);
static void SetCursorPosition(void);
static void SetScrollPosition(void);
static bool8 IfScrollIsOutOfBounds(void);
static bool8 IfRowIsOutOfBounds(void);
static void SaveScrollAndRow(s16 *data);

static void ClearModeOnStartup(void);
static u8 ManageMode(u8 action);
static u8 ToggleAlphaMode(u8 mode);
static u8 ToggleSubquestMode(u8 mode);
static u8 IncrementMode(u8 mode);
static bool8 IsSubquestMode(void);
static bool8 IsNotFilteredMode(void);
static bool8 IsAlphaMode(void);

static void BuildMenuTemplate(void);
static u8 GetModeAndGenerateList();
static u8 CountNumberListRows();
static u8 *DefineQuestOrder();
static u8 GenerateSubquestList();
static u8 GenerateList(bool8 isFiltered);
static void AssignCancelNameAndId(u8 numRow);

static u8 CountUnlockedQuests(void);
static u8 CountInactiveQuests(void);
static u8 CountActiveQuests(void);
static u8 CountRewardQuests(void);
static u8 CountCompletedQuests(void);
static u8 CountFavoriteQuests(void);

static void PopulateEmptyRow(u8 countQuest);
static void PrependQuestNumber(u8 countQuest);
static void SetFavoriteQuest(u8 countQuest);
static void PopulateQuestName(u8 countQuest);
static void PopulateSubquestName(u8 parentQuest, u8 countQuest);
static void PopulateListRowNameAndId(u8 row, u8 countQuest);
static bool8 DoesQuestHaveChildrenAndNotInactive(u16 itemId);
static void AddSubQuestButton(u8 countQuest);

static void QuestMenu_AddTextPrinterParameterized(u8 windowId, u8 fontId,
            const u8 *str, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, u8 speed,
            u8 colorIdx);

static void MoveCursorFunc(s32 itemIndex, bool8 onInit,
                           struct ListMenu *list);
static void PlayCursorSound(bool8 firstRun);
static void PrintDetailsForCancel();
static void GenerateAndPrintQuestDetails(s32 questId);
static void GenerateQuestLocation(s32 questId);
static void PrintQuestLocation(s32 questId);
static void GenerateQuestFlavorText(s32 questId);
static void UpdateQuestFlavorText(s32 questId);
static void PrintQuestFlavorText(s32 questId);

static bool8 IsQuestUnlocked(s32 questId);
static bool8 IsQuestActiveState(s32 questId);
static bool8 IsQuestInactiveState(s32 questId);
static bool8 IsQuestRewardState(s32 questId);
static bool8 IsQuestCompletedState(s32 questId);
static bool8 IsSubquestCompletedState(s32 questId);

static void DetermineSpriteType(s32 questId);
static void QuestMenu_CreateSprite(u16 itemId, u8 idx, u8 spriteType);
static void ResetSpriteState(void);
static void QuestMenu_DestroySprite(u8 idx);

static void GenerateStateAndPrint(u8 windowId, u32 itemId, u8 y);
static u8 GenerateSubquestState(u8 questId);
static u8 GenerateQuestState(u8 questId);
static void PrintQuestState(u8 windowId, u8 y, u8 colorIndex);

static void GenerateAndPrintHeader(void);
static void GenerateDenominatorNumQuests(void);
static void GenerateNumeratorNumQuests(void);
static void GenerateMenuContext(void);
static void PrintNumQuests(void);
static void PrintMenuContext(void);
static void PrintTypeFilterButton(void);

static void Task_Main(u8 taskId);
static void ManageFavorites(u8 index);
static void Task_QuestMenuCleanUp(u8 taskId);
static void RestoreSavedScrollAndRow(s16 *data);
static void ResetCursorToTop(s16 *data);
static void QuestMenu_RemoveScrollIndicatorArrowPair(void);
static void EnterSubquestModeAndCleanUp(u8 taskId, s16 *data, s32 input);
static void ChangeModeAndCleanUp(u8 taskId);
static void ToggleAlphaModeAndCleanUp(u8 taskId);
static void ToggleFavoriteAndCleanUp(u8 taskId, u8 selectedQuestId);
static bool8 CheckSelectedIsCancel(u8 selectedQuestId);
static void ReturnFromSubquestAndCleanUp(u8 taskId);

static void SetGpuRegBaseForFade(void);
static void InitFadeVariables(u8 taskId, u8 blendWeight, u8 frameDelay,
                              u8 frameTimerBase, u8 delta);
static void PrepareFadeOut(u8 taskId);
static bool8 HandleFadeOut(u8 taskId);
static void PrepareFadeIn(u8 taskId);
static bool8 HandleFadeIn(u8 taskId);
static void Task_FadeOut(u8 taskId);
static void Task_FadeIn(u8 taskId);

static void Task_QuestMenuWaitFadeAndBail(u8 taskId);
static void FadeAndBail(void);
static void FreeResources(void);
static void TurnOffQuestMenu(u8 taskId);
static void Task_QuestMenuTurnOff1(u8 taskId);
static void Task_QuestMenuTurnOff2(u8 taskId);

// Tiles, palettes and tilemaps for the Quest Menu
static const u32 sQuestMenuTiles[] =
        INCBIN_U32("graphics/quest_menu/menu.4bpp.smol");
static const u16 sQuestMenuBgPals[] =
        INCBIN_U16("graphics/quest_menu/menu.gbapal");
static const u32 sQuestMenuTilemap[] =
        INCBIN_U32("graphics/quest_menu/menu.bin.smolTM");

//Strings used for the Quest Menu
static const u8 sText_Empty[] = _("");
static const u8 sText_AllHeader[] = _("All Missions");
static const u8 sText_InactiveHeader[] = _("Inactive Missions");
static const u8 sText_ActiveHeader[] = _("Active Missions");
static const u8 sText_RewardHeader[] = _("Reward Available");
static const u8 sText_CompletedHeader[] =
      _("Completed Missions");
static const u8 sText_QuestNumberDisplay[] =
      _("{STR_VAR_1}/{STR_VAR_2}");
static const u8 sText_Unk[] = _("??????");
static const u8 sText_Active[] = _("Active");
static const u8 sText_Reward[] = _("Reward");
static const u8 sText_Complete[] = _("Done");
static const u8 sText_ShowLocation[] =
      _("Location: {STR_VAR_2}");
static const u8 sText_StartForMore[] =
      _("Start for more details.");
static const u8 sText_ReturnRecieveReward[] =
      _("Return to {STR_VAR_2}\nto recieve your reward!");
static const u8 sText_SubQuestButton[] = _(" {A_BUTTON}");
static const u8 sText_Type[] = _("{R_BUTTON}Type");
static const u8 sText_Caught[] = _("Caught");
static const u8 sText_Found[] = _("Found");
static const u8 sText_Done[] = _("Done");
static const u8 sText_Read[] = _("Read");
static const u8 sText_Back[] = _("Back");
static const u8 sText_DotSpace[] = _(". ");
static const u8 sText_Close[] = _("Close");
static const u8 sText_ColorGreen[] = _("{COLOR}{GREEN}");
static const u8 sText_AZ[] = _(" A-Z");

///////////////////////////////////////////////////////////////////////////////
//////////////////////BEGIN SUBQUEST CUSTOMIZATION/////////////////////////////

//names
const u8 sText_SideQuestName_IDollDex[] = _("Complete the iDollDex");
const u8 sText_SideQuestDesc_1[] = _("Description 1");

const u8 sText_SideQuestName_Champion[] = _("Journey to Champion");
const u8 sText_SideQuestDesc_2[] = _("Defeat all the gym leaders\nto challenge the Elite 4 and\nbecome the champion.");

const u8 sText_SideQuestName_3[] = _("Side Quest 3");
const u8 sText_SideQuestName_4[] = _("Side Quest 4");
const u8 sText_SideQuestName_5[] = _("Side Quest 5");
const u8 sText_SideQuestName_6[] = _("Side Quest 6");
const u8 sText_SideQuestName_7[] = _("Side Quest 7");
const u8 sText_SideQuestName_8[] = _("Side Quest 8");
const u8 sText_SideQuestName_9[] = _("Side Quest 9");
const u8 sText_SideQuestName_10[] = _("Side Quest 10");
const u8 sText_SideQuestName_11[] = _("Side Quest 11");
const u8 sText_SideQuestName_12[] = _("Side Quest 12");
const u8 sText_SideQuestName_13[] = _("Side Quest 13");
const u8 sText_SideQuestName_14[] = _("Side Quest 14");
const u8 sText_SideQuestName_15[] = _("Side Quest 15");
const u8 sText_SideQuestName_16[] = _("Side Quest 16");
const u8 sText_SideQuestName_17[] = _("Side Quest 17");
const u8 sText_SideQuestName_18[] = _("Side Quest 18");
const u8 sText_SideQuestName_19[] = _("Side Quest 19");
const u8 sText_SideQuestName_20[] = _("Side Quest 20");
const u8 sText_SideQuestName_21[] = _("Side Quest 21");
const u8 sText_SideQuestName_22[] = _("Side Quest 22");
const u8 sText_SideQuestName_23[] = _("Side Quest 23");
const u8 sText_SideQuestName_24[] = _("Side Quest 24");
const u8 sText_SideQuestName_25[] = _("Side Quest 25");
const u8 sText_SideQuestName_26[] = _("Side Quest 26");
const u8 sText_SideQuestName_27[] = _("Side Quest 27");
const u8 sText_SideQuestName_28[] = _("Side Quest 28");
const u8 sText_SideQuestName_29[] = _("Side Quest 29");
const u8 sText_SideQuestName_30[] = _("Side Quest 30");

//descriptions
const u8 sText_SideQuestDesc_3[] = _("Description 3");
const u8 sText_SideQuestDesc_4[] = _("Description 4");
const u8 sText_SideQuestDesc_5[] = _("Description 5");
const u8 sText_SideQuestDesc_6[] = _("Description 6");
const u8 sText_SideQuestDesc_7[] = _("Description 7");
const u8 sText_SideQuestDesc_8[] = _("Description 8");
const u8 sText_SideQuestDesc_9[] = _("Description 9");
const u8 sText_SideQuestDesc_10[] = _("Description 10");
const u8 sText_SideQuestDesc_11[] = _("Description 11");
const u8 sText_SideQuestDesc_12[] = _("Description 12");
const u8 sText_SideQuestDesc_13[] = _("Description 13");
const u8 sText_SideQuestDesc_14[] = _("Description 14");
const u8 sText_SideQuestDesc_15[] = _("Description 15");
const u8 sText_SideQuestDesc_16[] = _("Description 16");
const u8 sText_SideQuestDesc_17[] = _("Description 17");
const u8 sText_SideQuestDesc_18[] = _("Description 18");
const u8 sText_SideQuestDesc_19[] = _("Description 19");
const u8 sText_SideQuestDesc_20[] = _("Description 20");
const u8 sText_SideQuestDesc_21[] = _("Description 21");
const u8 sText_SideQuestDesc_22[] = _("Description 22");
const u8 sText_SideQuestDesc_23[] = _("Description 23");
const u8 sText_SideQuestDesc_24[] = _("Description 24");
const u8 sText_SideQuestDesc_25[] = _("Description 25");
const u8 sText_SideQuestDesc_26[] = _("Description 26");
const u8 sText_SideQuestDesc_27[] = _("Description 27");
const u8 sText_SideQuestDesc_28[] = _("Description 28");
const u8 sText_SideQuestDesc_29[] = _("Description 29");
const u8 sText_SideQuestDesc_30[] = _("Description 30");

//completed quest description
const u8 sText_SideQuestDoneDesc_1[] = _("Completed Quest 1");
const u8 sText_SideQuestDoneDesc_2[] = _("Completed Quest 2");
const u8 sText_SideQuestDoneDesc_3[] = _("Completed Quest 3");
const u8 sText_SideQuestDoneDesc_4[] = _("Completed Quest 4");
const u8 sText_SideQuestDoneDesc_5[] = _("Completed Quest 5");
const u8 sText_SideQuestDoneDesc_6[] = _("Completed Quest 6");
const u8 sText_SideQuestDoneDesc_7[] = _("Completed Quest 7");
const u8 sText_SideQuestDoneDesc_8[] = _("Completed Quest 8");
const u8 sText_SideQuestDoneDesc_9[] = _("Completed Quest 9");
const u8 sText_SideQuestDoneDesc_10[] = _("Completed Quest 10");
const u8 sText_SideQuestDoneDesc_11[] = _("Completed Quest 11");
const u8 sText_SideQuestDoneDesc_12[] = _("Completed Quest 12");
const u8 sText_SideQuestDoneDesc_13[] = _("Completed Quest 13");
const u8 sText_SideQuestDoneDesc_14[] = _("Completed Quest 14");
const u8 sText_SideQuestDoneDesc_15[] = _("Completed Quest 15");
const u8 sText_SideQuestDoneDesc_16[] = _("Completed Quest 16");
const u8 sText_SideQuestDoneDesc_17[] = _("Completed Quest 17");
const u8 sText_SideQuestDoneDesc_18[] = _("Completed Quest 18");
const u8 sText_SideQuestDoneDesc_19[] = _("Completed Quest 19");
const u8 sText_SideQuestDoneDesc_20[] = _("Completed Quest 20");
const u8 sText_SideQuestDoneDesc_21[] = _("Completed Quest 21");
const u8 sText_SideQuestDoneDesc_22[] = _("Completed Quest 22");
const u8 sText_SideQuestDoneDesc_23[] = _("Completed Quest 23");
const u8 sText_SideQuestDoneDesc_24[] = _("Completed Quest 24");
const u8 sText_SideQuestDoneDesc_25[] = _("Completed Quest 25");
const u8 sText_SideQuestDoneDesc_26[] = _("Completed Quest 26");
const u8 sText_SideQuestDoneDesc_27[] = _("Completed Quest 27");
const u8 sText_SideQuestDoneDesc_28[] = _("Completed Quest 28");
const u8 sText_SideQuestDoneDesc_29[] = _("Completed Quest 29");
const u8 sText_SideQuestDoneDesc_30[] = _("Completed Quest 30");

//map
const u8 sText_SideQuestMap1[] = _("Map 1");
const u8 sText_SideQuestMap2[] = _("Map 2");
const u8 sText_SideQuestMap3[] = _("Map 3");
const u8 sText_SideQuestMap4[] = _("Map 4");
const u8 sText_SideQuestMap5[] = _("Map 5");
const u8 sText_SideQuestMap6[] = _("Map 6");
const u8 sText_SideQuestMap7[] = _("Map 7");
const u8 sText_SideQuestMap8[] = _("Map 8");
const u8 sText_SideQuestMap9[] = _("Map 9");
const u8 sText_SideQuestMap10[] = _("Map 10");
const u8 sText_SideQuestMap11[] = _("Map 11");
const u8 sText_SideQuestMap12[] = _("Map 12");
const u8 sText_SideQuestMap13[] = _("Map 13");
const u8 sText_SideQuestMap14[] = _("Map 14");
const u8 sText_SideQuestMap15[] = _("Map 15");
const u8 sText_SideQuestMap16[] = _("Map 16");
const u8 sText_SideQuestMap17[] = _("Map 17");
const u8 sText_SideQuestMap18[] = _("Map 18");
const u8 sText_SideQuestMap19[] = _("Map 19");
const u8 sText_SideQuestMap20[] = _("Map 20");
const u8 sText_SideQuestMap21[] = _("Map 21");
const u8 sText_SideQuestMap22[] = _("Map 22");
const u8 sText_SideQuestMap23[] = _("Map 23");
const u8 sText_SideQuestMap24[] = _("Map 24");
const u8 sText_SideQuestMap25[] = _("Map 25");
const u8 sText_SideQuestMap26[] = _("Map 26");
const u8 sText_SideQuestMap27[] = _("Map 27");
const u8 sText_SideQuestMap28[] = _("Map 28");
const u8 sText_SideQuestMap29[] = _("Map 29");
const u8 sText_SideQuestMap30[] = _("Map 30");

const u8 sText_SideQuestHoenn[] = _("Hoenn");
const u8 sText_SideQuestLittleroot[] = _("Littleroot");
const u8 sText_SideQuestNoiseboro[] = _("Noiseboro");
const u8 sText_SideQuestDreamford[] = _("Dreamford");
const u8 sText_SideQuestMauville[] = _("Mauville");
const u8 sText_SideQuestLavaridge[] = _("Lavaridge");
const u8 sText_SideQuestPetalburg[] = _("Petalburg");

//subquests
const u8 sText_SubQuestChampion_Gym1[] = _("A Rocky Start");
const u8 sText_SubQuestChampion_Gym3[] = _("Messing with Time");
const u8 sText_SubQuestChampion_Gym2[] = _("The Dark Turn");
const u8 sText_SubQuestChampion_Gym4[] = _("Heating up Stakes");
const u8 sText_SubQuestChampion_Gym5[] = _("Part 5");
const u8 sText_SubQuestChampion_Gym6[] = _("Part 6");
const u8 sText_SubQuestChampion_Gym7[] = _("Twin Takedown");
const u8 sText_SubQuestChampion_Gym8[] = _("Last Judgement");
const u8 sText_SubQuestChampion_Elite4[] = _("Beating the Elites");

const u8 sText_SubQuestChampion_Desc_Gym1[] = _("Description Sub 1");
const u8 sText_SubQuestChampion_Desc_Gym2[] = _("Description Sub 2");
const u8 sText_SubQuestChampion_Desc_Gym3[] = _("Description Sub 3");
const u8 sText_SubQuestChampion_Desc_Gym4[] = _("Description Sub 4");
const u8 sText_SubQuestChampion_Desc_Gym5[] = _("Description Sub 5");
const u8 sText_SubQuestChampion_Desc_Gym6[] = _("Description Sub 6");
const u8 sText_SubQuestChampion_Desc_Gym7[] = _("Description Sub 7");
const u8 sText_SubQuestChampion_Desc_Gym8[] = _("Description Sub 8");
const u8 sText_SubQuestChampion_Desc_Elite4[] = _("Description Sub 9");

const u8 gText_SubQuest2_Name1[] = _("Part 1");
const u8 gText_SubQuest2_Name2[] = _("Part 2");
const u8 gText_SubQuest2_Name3[] = _("Part 3");
const u8 gText_SubQuest2_Name4[] = _("Part 4");
const u8 gText_SubQuest2_Name5[] = _("Part 5");
const u8 gText_SubQuest2_Name6[] = _("Part 6");
const u8 gText_SubQuest2_Name7[] = _("Part 7");
const u8 gText_SubQuest2_Name8[] = _("Part 8");
const u8 gText_SubQuest2_Name9[] = _("Part 9");
const u8 gText_SubQuest2_Name10[] = _("Part 10");
const u8 gText_SubQuest2_Name11[] = _("Part 11");
const u8 gText_SubQuest2_Name12[] = _("Part 12");
const u8 gText_SubQuest2_Name13[] = _("Part 13");
const u8 gText_SubQuest2_Name14[] = _("Part 14");
const u8 gText_SubQuest2_Name15[] = _("Part 15");
const u8 gText_SubQuest2_Name16[] = _("Part 16");
const u8 gText_SubQuest2_Name17[] = _("Part 17");
const u8 gText_SubQuest2_Name18[] = _("Part 18");
const u8 gText_SubQuest2_Name19[] = _("Part 19");
const u8 gText_SubQuest2_Name20[] = _("Part 20");

const u8 gText_SubQuest1_Desc10[] = _("Description Sub 10");

const u8 gText_SubQuest2_Desc1[] = _("Description Sub 1");
const u8 gText_SubQuest2_Desc2[] = _("Description Sub 2");
const u8 gText_SubQuest2_Desc3[] = _("Description Sub 3");
const u8 gText_SubQuest2_Desc4[] = _("Description Sub 4");
const u8 gText_SubQuest2_Desc5[] = _("Description Sub 5");
const u8 gText_SubQuest2_Desc6[] = _("Description Sub 6");
const u8 gText_SubQuest2_Desc7[] = _("Description Sub 7");
const u8 gText_SubQuest2_Desc8[] = _("Description Sub 8");
const u8 gText_SubQuest2_Desc9[] = _("Description Sub 9");
const u8 gText_SubQuest2_Desc10[] = _("Description Sub 10");
const u8 gText_SubQuest2_Desc11[] = _("Description Sub 11");
const u8 gText_SubQuest2_Desc12[] = _("Description Sub 12");
const u8 gText_SubQuest2_Desc13[] = _("Description Sub 13");
const u8 gText_SubQuest2_Desc14[] = _("Description Sub 14");
const u8 gText_SubQuest2_Desc15[] = _("Description Sub 15");
const u8 gText_SubQuest2_Desc16[] = _("Description Sub 16");
const u8 gText_SubQuest2_Desc17[] = _("Description Sub 17");
const u8 gText_SubQuest2_Desc18[] = _("Description Sub 18");
const u8 gText_SubQuest2_Desc19[] = _("Description Sub 19");
const u8 gText_SubQuest2_Desc20[] = _("Description Sub 20");

//Declaration of subquest structures. Edits to subquests are made here.
static const struct SubQuest sSubQuestsChampion[QUEST_CHAMPION_SUB_COUNT] =
{
    [SUB_QUEST_GYM_1] =
    {
        .id = SUB_QUEST_GYM_1,
        .name = sText_SubQuestChampion_Gym1,
        .desc = sText_SubQuestChampion_Desc_Gym1,
        .map = sText_SideQuestNoiseboro,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
    [SUB_QUEST_GYM_2] =
    {
        .id = SUB_QUEST_GYM_2,
        .name = sText_SubQuestChampion_Gym2,
        .desc = sText_SubQuestChampion_Desc_Gym2,
        .map = sText_SideQuestDreamford,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
    [SUB_QUEST_GYM_3] =
    {
        .id = SUB_QUEST_GYM_3,
        .name = sText_SubQuestChampion_Gym3,
        .desc = sText_SubQuestChampion_Desc_Gym3,
        .map = sText_SideQuestMauville,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
    [SUB_QUEST_GYM_4] =
    {
        .id = SUB_QUEST_GYM_4,
        .name = sText_SubQuestChampion_Gym4,
        .desc = sText_SubQuestChampion_Desc_Gym4,
        .map = sText_SideQuestLavaridge,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
    [SUB_QUEST_GYM_5] =
    {
        .id = SUB_QUEST_GYM_5,
        .name = sText_SubQuestChampion_Gym5,
        .desc = sText_SubQuestChampion_Desc_Gym5,
        .map = sText_SideQuestPetalburg,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
    [SUB_QUEST_GYM_6] =
    {
        .id = SUB_QUEST_GYM_6,
        .name = sText_SubQuestChampion_Gym6,
        .desc = sText_SubQuestChampion_Desc_Gym6,
        .map = sText_SideQuestHoenn,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
    [SUB_QUEST_GYM_7] =
    {
        .id = SUB_QUEST_GYM_7,
        .name = sText_SubQuestChampion_Gym7,
        .desc = sText_SubQuestChampion_Desc_Gym7,
        .map = sText_SideQuestHoenn,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
    [SUB_QUEST_GYM_8] =
    {
        .id = SUB_QUEST_GYM_8,
        .name = sText_SubQuestChampion_Gym8,
        .desc = sText_SubQuestChampion_Desc_Gym8,
        .map = sText_SideQuestHoenn,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
    [SUB_QUEST_ELITE_4] =
    {
        .id = SUB_QUEST_ELITE_4,
        .name = sText_SubQuestChampion_Elite4,
        .desc = sText_SubQuestChampion_Desc_Elite4,
        .map = sText_SideQuestHoenn,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .type = sText_Done,
    },
};

#define sub_quest(i, n, d, m, s, st, t) {.id = i, .name = n, .desc = d, .map = m, .sprite = s, .spritetype = st, .type = t}
static const struct SubQuest sSubQuests2[QUEST_2_SUB_COUNT] =
{
    sub_quest(
          9,
          gText_SubQuest2_Name1,
          gText_SubQuest2_Desc1,
          sText_SideQuestMap1,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          10,
          gText_SubQuest2_Name1,
          gText_SubQuest2_Desc1,
          sText_SideQuestMap1,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          11,
          gText_SubQuest2_Name2,
          gText_SubQuest2_Desc2,
          sText_SideQuestMap2,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          12,
          gText_SubQuest2_Name3,
          gText_SubQuest2_Desc3,
          sText_SideQuestMap3,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          13,
          gText_SubQuest2_Name4,
          gText_SubQuest2_Desc4,
          sText_SideQuestMap4,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          14,
          gText_SubQuest2_Name5,
          gText_SubQuest2_Desc5,
          sText_SideQuestMap5,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          15,
          gText_SubQuest2_Name6,
          gText_SubQuest2_Desc6,
          sText_SideQuestMap6,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          16,
          gText_SubQuest2_Name7,
          gText_SubQuest2_Desc7,
          sText_SideQuestMap7,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          17,
          gText_SubQuest2_Name8,
          gText_SubQuest2_Desc8,
          sText_SideQuestMap8,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          18,
          gText_SubQuest2_Name9,
          gText_SubQuest2_Desc9,
          sText_SideQuestMap9,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          19,
          gText_SubQuest2_Name10,
          gText_SubQuest2_Desc10,
          sText_SideQuestMap10,
          SPECIES_ATTACK_SHINMYOUMARU,
          PKMN,
          sText_Caught

    ),

    sub_quest(
          20,
          gText_SubQuest2_Name11,
          gText_SubQuest2_Desc11,
          sText_SideQuestMap11,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          21,
          gText_SubQuest2_Name12,
          gText_SubQuest2_Desc12,
          sText_SideQuestMap12,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          22,
          gText_SubQuest2_Name13,
          gText_SubQuest2_Desc13,
          sText_SideQuestMap13,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          23,
          gText_SubQuest2_Name14,
          gText_SubQuest2_Desc14,
          sText_SideQuestMap14,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          24,
          gText_SubQuest2_Name15,
          gText_SubQuest2_Desc15,
          sText_SideQuestMap15,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          25,
          gText_SubQuest2_Name16,
          gText_SubQuest2_Desc16,
          sText_SideQuestMap16,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          26,
          gText_SubQuest2_Name17,
          gText_SubQuest2_Desc17,
          sText_SideQuestMap17,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          27,
          gText_SubQuest2_Name18,
          gText_SubQuest2_Desc18,
          sText_SideQuestMap18,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          28,
          gText_SubQuest2_Name19,
          gText_SubQuest2_Desc19,
          sText_SideQuestMap19,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

    sub_quest(
          29,
          gText_SubQuest2_Name20,
          gText_SubQuest2_Desc20,
          sText_SideQuestMap20,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          sText_Found
    ),

};

////////////////////////END SUBQUEST CUSTOMIZATION/////////////////////////////
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
////////////////////////BEGIN QUEST CUSTOMIZATION//////////////////////////////

//Declaration of side quest structures. Edits to quests are made here.
#define side_quest(n, d, dd, m, s, st, sq, ns) {.name = n, .desc = d, .donedesc = dd, .map = m, .sprite = s, .spritetype = st, .subquests = sq, .numSubquests = ns}
static const struct SideQuest sSideQuests[QUEST_COUNT] =
{
    [QUEST_IDOLLDEX] = 
    {
        .name = sText_SideQuestName_IDollDex,
        .desc = sText_SideQuestDesc_1,
        .donedesc = sText_SideQuestDoneDesc_1,
        .map = sText_SideQuestMap1,
        .sprite = ITEM_TOHO_ORB,
        .spritetype = ITEM,
    },
    [QUEST_CHAMPION] = 
    {
        .name = sText_SideQuestName_Champion,
        .desc = sText_SideQuestDesc_2,
        .donedesc = sText_SideQuestDoneDesc_2,
        .map = sText_SideQuestHoenn,
        .sprite = OBJ_EVENT_GFX_WALLY,
        .spritetype = OBJECT,
        .subquests = sSubQuestsChampion,
        .numSubquests = QUEST_CHAMPION_SUB_COUNT,
    },
    [QUEST_3] = side_quest(
          sText_SideQuestName_3,
          sText_SideQuestDesc_3,
          sText_SideQuestDoneDesc_3,
          sText_SideQuestMap3,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_4,
          sText_SideQuestDesc_4,
          sText_SideQuestDoneDesc_4,
          sText_SideQuestMap4,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_5,
          sText_SideQuestDesc_5,
          sText_SideQuestDoneDesc_5,
          sText_SideQuestMap5,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_6,
          sText_SideQuestDesc_6,
          sText_SideQuestDoneDesc_6,
          sText_SideQuestMap6,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_7,
          sText_SideQuestDesc_7,
          sText_SideQuestDoneDesc_7,
          sText_SideQuestMap7,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_8,
          sText_SideQuestDesc_8,
          sText_SideQuestDoneDesc_8,
          sText_SideQuestMap8,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_9,
          sText_SideQuestDesc_9,
          sText_SideQuestDoneDesc_9,
          sText_SideQuestMap9,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_10,
          sText_SideQuestDesc_10,
          sText_SideQuestDoneDesc_10,
          sText_SideQuestMap10,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_11,
          sText_SideQuestDesc_11,
          sText_SideQuestDoneDesc_11,
          sText_SideQuestMap11,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_12,
          sText_SideQuestDesc_12,
          sText_SideQuestDoneDesc_12,
          sText_SideQuestMap12,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_13,
          sText_SideQuestDesc_13,
          sText_SideQuestDoneDesc_13,
          sText_SideQuestMap13,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_14,
          sText_SideQuestDesc_14,
          sText_SideQuestDoneDesc_14,
          sText_SideQuestMap14,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_15,
          sText_SideQuestDesc_15,
          sText_SideQuestDoneDesc_15,
          sText_SideQuestMap15,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_16,
          sText_SideQuestDesc_16,
          sText_SideQuestDoneDesc_16,
          sText_SideQuestMap16,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_17,
          sText_SideQuestDesc_17,
          sText_SideQuestDoneDesc_17,
          sText_SideQuestMap17,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_18,
          sText_SideQuestDesc_18,
          sText_SideQuestDoneDesc_18,
          sText_SideQuestMap18,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_19,
          sText_SideQuestDesc_19,
          sText_SideQuestDoneDesc_19,
          sText_SideQuestMap19,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_20,
          sText_SideQuestDesc_20,
          sText_SideQuestDoneDesc_20,
          sText_SideQuestMap20,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_21,
          sText_SideQuestDesc_21,
          sText_SideQuestDoneDesc_21,
          sText_SideQuestMap21,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_22,
          sText_SideQuestDesc_22,
          sText_SideQuestDoneDesc_22,
          sText_SideQuestMap22,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_23,
          sText_SideQuestDesc_23,
          sText_SideQuestDoneDesc_23,
          sText_SideQuestMap23,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_24,
          sText_SideQuestDesc_24,
          sText_SideQuestDoneDesc_24,
          sText_SideQuestMap24,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_25,
          sText_SideQuestDesc_25,
          sText_SideQuestDoneDesc_25,
          sText_SideQuestMap25,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_26,
          sText_SideQuestDesc_26,
          sText_SideQuestDoneDesc_26,
          sText_SideQuestMap26,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_27,
          sText_SideQuestDesc_27,
          sText_SideQuestDoneDesc_27,
          sText_SideQuestMap27,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_28,
          sText_SideQuestDesc_28,
          sText_SideQuestDoneDesc_28,
          sText_SideQuestMap28,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_29,
          sText_SideQuestDesc_29,
          sText_SideQuestDoneDesc_29,
          sText_SideQuestMap29,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
    side_quest(
          sText_SideQuestName_30,
          sText_SideQuestDesc_30,
          sText_SideQuestDoneDesc_30,
          sText_SideQuestMap30,
          OBJ_EVENT_GFX_WALLY,
          OBJECT,
          NULL,
          0
    ),
};
////////////////////////END QUEST CUSTOMIZATION////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//BG layer defintions
static const struct BgTemplate sQuestMenuBgTemplates[2] =
{
    {
        //All text and content is loaded to this window
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    },
    {
        ///Backgrounds and UI elements are loaded to this window
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 2
    }
};

//Window definitions
static const struct WindowTemplate sQuestMenuHeaderWindowTemplates[] =
{
    {
        //0: Content window
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 2,
        .width = 30,
        .height = 8,
        .paletteNum = 15,
        .baseBlock = 1
    },
    {
        //1: Footer window
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 12,
        .width = 30,
        .height = 12,
        .paletteNum = 15,
        .baseBlock = 361
    },
    {
        // 2: Header window
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 721
    },
    DUMMY_WIN_TEMPLATE
};

//Font color combinations for printed text
static const u8 sQuestMenuWindowFontColors[][4] =
{
    [QUESTCOLOR_HEADER] =
    {
        //Header of Quest Menu
        TEXT_COLOR_TRANSPARENT,
        TEXT_COLOR_WHITE,
        TEXT_DYNAMIC_COLOR_1
    },
    [QUESTCOLOR_QUEST_REWARD] =
    {
        //Reward state progress indicator
        TEXT_COLOR_TRANSPARENT,
        TEXT_COLOR_RED,
        TEXT_COLOR_LIGHT_RED
    },
    [QUESTCOLOR_QUEST_DONE] =
    {
        //Done state progress indicator
        TEXT_COLOR_TRANSPARENT,
        TEXT_COLOR_GREEN,
        TEXT_COLOR_LIGHT_GREEN
    },
    [QUESTCOLOR_QUEST_ACTIVE] =
    {
        //Active state progress indicator
        TEXT_COLOR_TRANSPARENT,
        TEXT_COLOR_BLUE,
        TEXT_COLOR_LIGHT_BLUE
    },
    [QUESTCOLOR_FOOTER] =
    {
        //Footer flavor text
        TEXT_COLOR_TRANSPARENT,
        TEXT_COLOR_DARK_GRAY,
        TEXT_COLOR_LIGHT_GRAY
    },
};

//Functions begin here

//ported from firered by ghoulslash
void QuestMenu_Init(u8 a0, MainCallback callback)
{
    u8 i;

    if (a0 >= 2)
    {
        SetMainCallback2(callback);
        return;
    }

    if ((sStateDataPtr = Alloc(sizeof(struct QuestMenuResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    if (a0 != 1)
    {
        sListMenuState.savedCallback = callback;
        sListMenuState.scroll = sListMenuState.row = 0;
    }

    sStateDataPtr->moveModeOrigPos = 0xFF;
    sStateDataPtr->spriteIconSlot = 0;
    sStateDataPtr->scrollIndicatorArrowPairId = 0xFF;
    sStateDataPtr->savedCallback = 0;
    for (i = 0; i < 3; i++)
    {
        sStateDataPtr->data[i] = 0;
    }

    SetMainCallback2(RunSetup);
}

static void MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void RunSetup(void)
{
    while (1)
    {
        if (SetupGraphics() == TRUE)
        {
            break;
        }
    }
}

static bool8 SetupGraphics(void)
{
    u8 taskId;
    switch (gMain.state)
    {
        case 0:
            SetVBlankHBlankCallbacksToNull();
            ClearScheduledBgCopiesToVram();
            gMain.state++;
            break;
        case 1:
            ScanlineEffect_Stop();
            gMain.state++;
            break;
        case 2:
            FreeAllSpritePalettes();
            gMain.state++;
            break;
        case 3:
            ResetPaletteFade();
            gMain.state++;
            break;
        case 4:
            ResetSpriteData();
            gMain.state++;
            break;
        case 5:
            ResetSpriteState();
            gMain.state++;
            break;
        case 6:
            ResetTasks();
            gMain.state++;
            break;
        case 7:
            if (InitBackgrounds())
            {
                sStateDataPtr->data[0] = 0;
                gMain.state++;
            }
            else
            {
                FadeAndBail();
                return TRUE;
            }
            break;
        case 8:
            if (LoadGraphics() == TRUE)
            {
                gMain.state++;
            }
            break;
        case 9:
            QuestMenu_InitWindows();
            gMain.state++;
            break;
        case 10:
            ClearModeOnStartup();
            InitItems();
            SetCursorPosition();
            SetScrollPosition();
            gMain.state++;
            break;
        case 11:
            if (AllocateResourcesForListMenu())
            {
                gMain.state++;
            }
            else
            {
                FadeAndBail();
                return TRUE;
            }
            break;
        case 12:
            AllocateMemoryForArray();
            BuildMenuTemplate();
            gMain.state++;
            break;
        case 13:
            GenerateAndPrintHeader();
            gMain.state++;
            break;
        case 14:
            gMain.state++;
            break;
        case 15:
            taskId = CreateTask(Task_Main, 0);
            gTasks[taskId].data[0] = ListMenuInit(&gMultiuseListMenuTemplate,
                                                  sListMenuState.scroll,
                                                  sListMenuState.row);
            gMain.state++;
            break;
        case 16:
            PlaceTopMenuScrollIndicatorArrows();
            gMain.state++;
            break;
        case 17:
            gMain.state++;
            break;
        case 18:
            if (sListMenuState.initialized == 1)
            {
                BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
            }
            gMain.state++;
            break;
        case 19:
            if (sListMenuState.initialized == 1)
            {
                BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
            }
            else
            {

                BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
                SetInitializedFlag(1);
            }
            gMain.state++;
            break;
        default:
            SetVBlankCallback(VBlankCB);
            SetMainCallback2(MainCB);
            return TRUE;
    }
    return FALSE;
}

static bool8 LoadGraphics(void)
{
    switch (sStateDataPtr->data[0])
    {
        case 0:
            ResetTempTileDataBuffers();
            DecompressAndCopyTileDataToVram(1, sQuestMenuTiles, 0, 0, 0);
            sStateDataPtr->data[0]++;
            break;
        case 1:
            if (FreeTempTileDataBuffersIfPossible() != TRUE)
            {
                DecompressDataWithHeaderWram(sQuestMenuTilemap, sBg1TilemapBuffer);
                sStateDataPtr->data[0]++;
            }
            break;
        case 2:
            LoadPalette(sQuestMenuBgPals, 0x00, 0x60);
            sStateDataPtr->data[0]++;
            break;
        case 3:
            sStateDataPtr->data[0]++;
            break;
        default:
            sStateDataPtr->data[0] = 0;
            return TRUE;
    }
    return FALSE;
}

static void QuestMenu_InitWindows(void)
{
    u8 i;

    InitWindows(sQuestMenuHeaderWindowTemplates);
    DeactivateAllTextPrinters();

    for (i = 0; i < 3; i++)
    {
        FillWindowPixelBuffer(i, 0x00);
        PutWindowTilemap(i);
    }

    ScheduleBgCopyTilemapToVram(0);
}

static bool8 InitBackgrounds(void)
{
    ResetAllBgsCoordinatesAndBgCntRegs();
    sBg1TilemapBuffer = Alloc(0x800);
    if (sBg1TilemapBuffer == NULL)
    {
        return FALSE;
    }

    memset(sBg1TilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sQuestMenuBgTemplates,
                         NELEMS(sQuestMenuBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    ShowBg(0);
    ShowBg(1);
    return TRUE;
}

static void InitItems(void)
{
    sStateDataPtr->nItems = (CountNumberListRows()) - 1;

    sStateDataPtr->maxShowed = sStateDataPtr->nItems + 1 <= 4 ?
                               sStateDataPtr->nItems + 1 : 4;
}

#define try_alloc(ptr__, size) ({ \
        void ** ptr = (void **)&(ptr__);             \
        *ptr = Alloc(size);                 \
        if (*ptr == NULL)                   \
        {                                   \
            FreeResources();                  \
            FadeAndBail();                  \
            return FALSE;                   \
        }                                   \
    })

static bool8 AllocateResourcesForListMenu(void)
{
    try_alloc(sListMenuItems,
              sizeof(struct ListMenuItem) * CountNumberListRows() + 1);
    return TRUE;
}

void AllocateMemoryForArray(void)
{
    u8 i;
    u8 allocateRows = QUEST_ARRAY_COUNT + 1;

    questNameArray = Alloc(sizeof(void *) * allocateRows);

    for (i = 0; i < allocateRows; i++)
    {
        questNameArray[i] = Alloc(sizeof(u8) * 32);
    }
}

static void PlaceTopMenuScrollIndicatorArrows(void)
{
    u8 listSize = CountNumberListRows();

    if (listSize < sStateDataPtr->maxShowed)
    {
        listSize = sStateDataPtr->maxShowed;
    }

    sStateDataPtr->scrollIndicatorArrowPairId =
          AddScrollIndicatorArrowPairParameterized(2, 94, 8, 90,
                      (listSize - sStateDataPtr->maxShowed), 110, 110, &sListMenuState.scroll);
}

static void SetInitializedFlag(u8 a0)
{
    sListMenuState.initialized = a0;
}

static u8 GetCursorPosition(void)
{
    return sListMenuState.scroll + sListMenuState.row;
}

static void SetCursorPosition(void)
{
    if (IfScrollIsOutOfBounds())
    {
        sListMenuState.scroll = (sStateDataPtr->nItems + 1) -
                                sStateDataPtr->maxShowed;
    }

    if (IfRowIsOutOfBounds())
    {
        if (sStateDataPtr->nItems + 1 < 2)
        {
            sListMenuState.row = 0;
        }
        else
        {
            sListMenuState.row = sStateDataPtr->nItems;
        }
    }
}


static void SetScrollPosition(void)
{
    u8 i;

    if (sListMenuState.row > 3)
    {
        for (i = 0; i <= sListMenuState.row - 3;
                    sListMenuState.row--, sListMenuState.scroll++, i++)
        {
            if (sListMenuState.scroll + sStateDataPtr->maxShowed ==
                        sStateDataPtr->nItems + 1)
            {
                break;
            }
        }
    }
}

bool8 IfScrollIsOutOfBounds(void)
{
    if (sListMenuState.scroll != 0
                && sListMenuState.scroll + sStateDataPtr->maxShowed >
                sStateDataPtr->nItems + 1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool8 IfRowIsOutOfBounds(void)
{
    if (sListMenuState.scroll + sListMenuState.row >= sStateDataPtr->nItems +
                1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void SaveScrollAndRow(s16 *data)
{
    ListMenuGetScrollAndRow(data[0], &sListMenuState.storedScrollOffset,
                            &sListMenuState.storedRowPosition);
}


void ClearModeOnStartup(void)
{
    sStateDataPtr->filterMode = 0;
}

static u8 ManageMode(u8 action)
{
    u8 mode = sStateDataPtr->filterMode;

    switch (action)
    {
        case SUB:
            mode = ToggleSubquestMode(mode);
            break;

        case ALPHA:
            mode = ToggleAlphaMode(mode);
            sStateDataPtr->restoreCursor = FALSE;
            break;

        default:
            mode = IncrementMode(mode);
            sStateDataPtr->restoreCursor = FALSE;
            break;
    }
    return mode;
}

u8 ToggleSubquestMode(u8 mode)
{
    if (IsSubquestMode())
    {
        mode -= SORT_SUBQUEST;
        sStateDataPtr->restoreCursor = TRUE;
    }
    else
    {
        mode += SORT_SUBQUEST;
        sStateDataPtr->restoreCursor = FALSE;
    }

    return mode;
}

u8 ToggleAlphaMode(u8 mode)
{
    if (IsAlphaMode())
    {
        mode -= SORT_DEFAULT_AZ;
    }
    else
    {
        mode += SORT_DEFAULT_AZ;
    }

    return mode;
}

u8 IncrementMode(u8 mode)
{
    if (mode % 10 == SORT_DONE)
    {
        mode -= SORT_DONE;
    }
    else
    {
        mode++;
    }

    return mode;
}

static bool8 IsSubquestMode(void)
{
    if (sStateDataPtr->filterMode > SORT_DONE_AZ)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static bool8 IsNotFilteredMode(void)
{
    u8 mode = sStateDataPtr->filterMode % 10;

    if (mode == FLAG_GET_UNLOCKED)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static bool8 IsAlphaMode(void)
{
    if (sStateDataPtr->filterMode < SORT_SUBQUEST
                && sStateDataPtr->filterMode > SORT_DONE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void BuildMenuTemplate(void)
{
    u8 lastRow = GetModeAndGenerateList();

    AssignCancelNameAndId(lastRow);

    gMultiuseListMenuTemplate.totalItems = CountNumberListRows();
    gMultiuseListMenuTemplate.items = sListMenuItems;
    gMultiuseListMenuTemplate.windowId = 0;
    gMultiuseListMenuTemplate.header_X = 0;
    gMultiuseListMenuTemplate.cursor_X = 15;
    gMultiuseListMenuTemplate.item_X = 23;
    gMultiuseListMenuTemplate.lettersSpacing = 1;
    gMultiuseListMenuTemplate.itemVerticalPadding = 2;
    gMultiuseListMenuTemplate.upText_Y = 2;
    gMultiuseListMenuTemplate.maxShowed = sStateDataPtr->maxShowed;
    gMultiuseListMenuTemplate.fontId = FONT_SHORT;
    gMultiuseListMenuTemplate.cursorPal = TEXT_COLOR_WHITE;
    gMultiuseListMenuTemplate.fillValue = TEXT_COLOR_TRANSPARENT;
    gMultiuseListMenuTemplate.cursorShadowPal = TEXT_DYNAMIC_COLOR_1;
    gMultiuseListMenuTemplate.moveCursorFunc = MoveCursorFunc;
    gMultiuseListMenuTemplate.itemPrintFunc = GenerateStateAndPrint;
    gMultiuseListMenuTemplate.scrollMultiple = LIST_MULTIPLE_SCROLL_DPAD;
    gMultiuseListMenuTemplate.cursorKind = 0;
}

u8 GetModeAndGenerateList()
{
    if (IsSubquestMode())
    {
        return GenerateSubquestList();
    }
    else
    {
        return GenerateList(!IsNotFilteredMode());
    }
}

static u8 CountNumberListRows()
{
    u8 mode = sStateDataPtr->filterMode % 10;

    if (IsSubquestMode())
    {
        return sSideQuests[sStateDataPtr->parentQuest].numSubquests + 1;
    }

    switch (mode)
    {
        case SORT_DEFAULT:
            return QUEST_COUNT + 1;
        case SORT_INACTIVE:
            return CountInactiveQuests() + 1;
        case SORT_ACTIVE:
            return CountActiveQuests() + 1;
        case SORT_REWARD:
            return CountRewardQuests() + 1;
        case SORT_DONE:
            return CountCompletedQuests() + 1;
    }
    
    return 1;
}

u8 *DefineQuestOrder()
{
    static u8 sortedList[QUEST_COUNT];
    u8 a, c, d;
    u8 placeholderVariable;

    for (a = 0; a < QUEST_COUNT; a++)
    {
        sortedList[a] = a;
    }

    if (IsAlphaMode())
    {
        for (c = 0; c < QUEST_COUNT; c++)
        {
            for (d = c + 1; d < QUEST_COUNT; d++)
            {
                if (StringCompare(sSideQuests[sortedList[c]].name,
                                  sSideQuests[sortedList[d]].name) > 0)
                {
                    placeholderVariable = sortedList[c];
                    sortedList[c] = sortedList[d];
                    sortedList[d] = placeholderVariable;
                }
            }
        }
    }

    return sortedList;
}

u8 GenerateSubquestList()
{
    u8 parentQuest = sStateDataPtr->parentQuest;
    u8 lastRow = 0, numRow = 0, countQuest = 0;

    for (numRow = 0; numRow < sSideQuests[parentQuest].numSubquests; numRow++)
    {
        PrependQuestNumber(countQuest);
        PopulateSubquestName(parentQuest, countQuest);
        PopulateListRowNameAndId(numRow, countQuest);

        countQuest++;
        lastRow = numRow + 1;
    }
    return lastRow;
}

u8 GenerateList(bool8 isFiltered)
{
    u8 mode = sStateDataPtr-> filterMode % 10;
    u8 numRow = 0, offset = 0, newRow = 0, countQuest = 0,
       selectedQuestId = 0;
    u8 *sortedQuestList;

    sortedQuestList = DefineQuestOrder();

    for (countQuest = 0; countQuest < QUEST_COUNT; countQuest++)
    {
        selectedQuestId = *(sortedQuestList + countQuest);

        if (isFiltered && !QuestMenu_GetSetQuestState(selectedQuestId, mode))
        {
            continue;
        }

        PopulateEmptyRow(selectedQuestId);

        if (QuestMenu_GetSetQuestState(selectedQuestId, FLAG_GET_FAVORITE))
        {
            SetFavoriteQuest(selectedQuestId);
            newRow = numRow;
            numRow++;
        }
        else
        {
            newRow = CountFavoriteQuests() + offset;
            offset++;
        }

        PopulateQuestName(selectedQuestId);
        PopulateListRowNameAndId(newRow, selectedQuestId);
    }
    return numRow + offset;
}

static void AssignCancelNameAndId(u8 numRow)
{
    if (IsSubquestMode())
    {
        sListMenuItems[numRow].name = sText_Back;
    }
    else
    {
        sListMenuItems[numRow].name = sText_Close;
    }

    sListMenuItems[numRow].id = LIST_CANCEL;
}

u8 QuestMenu_GetSetSubquestState(u8 quest, u8 caseId, u8 childQuest)
{

    u8 uniqueId = sSideQuests[quest].subquests[childQuest].id;
    u8  index = uniqueId / 8; //8 bits per byte
    u8    bit = uniqueId % 8;
    u8    mask = 1 << bit;

    switch (caseId)
    {
        case FLAG_GET_COMPLETED:
            return gSaveBlock3Ptr->subQuests[index] & mask;
        case FLAG_SET_COMPLETED:
            gSaveBlock3Ptr->subQuests[index] |= mask;
            return 1;
    }

    return -1;
}

u8 QuestMenu_GetSetQuestState(u8 quest, u8 caseId)
{
    u8 index = quest * 5 / 8;
    u8 bit = quest * 5 % 8;
    u8 mask = 0, index2 = 0, bit2 = 0, index3 = 0, bit3 = 0, mask2 = 0,
       mask3 = 0;

    // 0 : locked
    // 1 : actived
    // 2 : rewarded
    // 3 : completed
    // 4 : favorited

    switch (caseId)
    {
        case FLAG_GET_UNLOCKED:
        case FLAG_SET_UNLOCKED:
            break;
        case FLAG_GET_INACTIVE:
        case FLAG_GET_ACTIVE:
        case FLAG_SET_ACTIVE:
        case FLAG_REMOVE_ACTIVE:
            bit += 1;
            break;
        case FLAG_GET_REWARD:
        case FLAG_SET_REWARD:
        case FLAG_REMOVE_REWARD:
            bit += 2;
            break;
        case FLAG_GET_COMPLETED:
        case FLAG_SET_COMPLETED:
            bit += 3;
            break;
        case FLAG_GET_FAVORITE:
        case FLAG_SET_FAVORITE:
        case FLAG_REMOVE_FAVORITE:
            bit += 4;
            break;
    }
    if (bit >= 8)
    {
        index += 1;
        bit %= 8;
    }
    mask = 1 << bit;

    switch (caseId)
    {
        case FLAG_GET_UNLOCKED:
            return gSaveBlock3Ptr->questData[index] & mask;
        case FLAG_SET_UNLOCKED:
            gSaveBlock3Ptr->questData[index] |= mask;
            return 1;
        case FLAG_GET_INACTIVE:
            bit2 = bit + 1;
            bit3 = bit + 2;
            index2 = index;
            index3 = index;

            if (bit2 >= 8)
            {
                index2 += 1;
                bit2 %= 8;
            }
            if (bit3 >= 8)
            {
                index3 += 1;
                bit3 %= 8;
            }

            mask2 = 1 << bit2;
            mask3 = 1 << bit3;
            return !(gSaveBlock3Ptr->questData[index] & mask) && \
                   !(gSaveBlock3Ptr->questData[index2] & mask2) && \
                   !(gSaveBlock3Ptr->questData[index3] & mask3);
        case FLAG_GET_ACTIVE:
            return gSaveBlock3Ptr->questData[index] & mask;
        case FLAG_SET_ACTIVE:
            gSaveBlock3Ptr->questData[index] |= mask;
            return 1;
        case FLAG_REMOVE_ACTIVE:
            gSaveBlock3Ptr->questData[index] &= ~mask;
            return 1;
        case FLAG_GET_REWARD:
            return gSaveBlock3Ptr->questData[index] & mask;
        case FLAG_SET_REWARD:
            gSaveBlock3Ptr->questData[index] |= mask;
            return 1;
        case FLAG_REMOVE_REWARD:
            gSaveBlock3Ptr->questData[index] &= ~mask;
            return 1;
        case FLAG_GET_COMPLETED:
            return gSaveBlock3Ptr->questData[index] & mask;
        case FLAG_SET_COMPLETED:
            gSaveBlock3Ptr->questData[index] |= mask;
            return 1;
        case FLAG_GET_FAVORITE:
            return gSaveBlock3Ptr->questData[index] & mask;
        case FLAG_SET_FAVORITE:
            gSaveBlock3Ptr->questData[index] |= mask;
            return 1;
        case FLAG_REMOVE_FAVORITE:
            gSaveBlock3Ptr->questData[index] &= ~mask;
            return 1;
    }
    return -1;  //failure
}

u8 CountUnlockedQuests(void)
{
    u8 q = 0, i = 0;

    for (i = 0; i < QUEST_COUNT; i++)
    {
        if (QuestMenu_GetSetQuestState(i, FLAG_GET_UNLOCKED))
        {
            q++;
        }
    }
    return q;
}

u8 CountInactiveQuests(void)
{
    u8 q = 0, i = 0;

    for (i = 0; i < QUEST_COUNT; i++)
    {
        if (QuestMenu_GetSetQuestState(i, FLAG_GET_INACTIVE))
        {
            q++;
        }
    }
    return q;
}

u8 CountActiveQuests(void)
{
    u8 q = 0, i = 0;

    for (i = 0; i < QUEST_COUNT; i++)
    {
        if (QuestMenu_GetSetQuestState(i, FLAG_GET_ACTIVE))
        {
            q++;
        }
    }
    return q;
}

u8 CountRewardQuests(void)
{
    u8 q = 0, i = 0;

    for (i = 0; i < QUEST_COUNT; i++)
    {
        if (QuestMenu_GetSetQuestState(i, FLAG_GET_REWARD))
        {
            q++;
        }
    }
    return q;
}

u8 CountCompletedQuests(void)
{
    u8 q = 0, i = 0;

    u8 parentQuest = sStateDataPtr->parentQuest;

    if (IsSubquestMode())
    {
        for (i = 0; i < sSideQuests[parentQuest].numSubquests; i++)
        {
            if (QuestMenu_GetSetSubquestState(parentQuest, FLAG_GET_COMPLETED, i))
            {
                q++;
            }
        }
    }
    else
    {
        for (i = 0; i < QUEST_COUNT; i++)
        {
            if (QuestMenu_GetSetQuestState(i, FLAG_GET_COMPLETED))
            {
                q++;
            }
        }
    }

    return q;
}

u8 CountFavoriteQuests(void)
{
    u8 q = 0, i = 0, x = 0;
    u8 mode = sStateDataPtr->filterMode % 10;

    for (i = 0; i < QUEST_COUNT; i++)
    {
        if (QuestMenu_GetSetQuestState(i, FLAG_GET_FAVORITE))
        {
            if (QuestMenu_GetSetQuestState(i, mode))
            {
                x++;
            }
            q++;
        }
    }

    if (IsNotFilteredMode())
    {
        return q;
    }
    else
    {
        return x;
    }

}

void PopulateEmptyRow(u8 countQuest)
{
    questNamePointer = StringCopy(questNameArray[countQuest], sText_Empty);
}
void PrependQuestNumber(u8 countQuest)
{
    questNamePointer = ConvertIntToDecimalStringN(questNameArray[countQuest],
                       countQuest + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
    questNamePointer = StringAppend(questNamePointer,
                                    sText_DotSpace);
}

void SetFavoriteQuest(u8 countQuest)
{
    questNamePointer = StringAppend(questNameArray[countQuest],
                                    sText_ColorGreen);
}

void PopulateQuestName(u8 countQuest)
{
    if (QuestMenu_GetSetQuestState(countQuest, FLAG_GET_UNLOCKED))
    {
        questNamePointer = StringAppend(questNameArray[countQuest],
                                        sSideQuests[countQuest].name);
        AddSubQuestButton(countQuest);
    }
    else
    {
        StringAppend(questNameArray[countQuest], sText_Unk);
    }
}

void PopulateSubquestName(u8 parentQuest, u8 countQuest)
{
    if (IsSubquestCompletedState(countQuest))
    {
        questNamePointer = StringAppend(questNamePointer,
                                        sSideQuests[parentQuest].subquests[countQuest].name);
    }
    else
    {
        questNamePointer = StringAppend(questNamePointer, sText_Unk);
    }
}

void PopulateListRowNameAndId(u8 row, u8 countQuest)
{
    sListMenuItems[row].name = questNameArray[countQuest];
    sListMenuItems[row].id = countQuest;
}

static bool8 DoesQuestHaveChildrenAndNotInactive(u16 itemId)
{
    if (sSideQuests[itemId].numSubquests != 0
                && QuestMenu_GetSetQuestState(itemId, FLAG_GET_UNLOCKED)
                && !QuestMenu_GetSetQuestState(itemId, FLAG_GET_INACTIVE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void AddSubQuestButton(u8 countQuest)
{
    if (DoesQuestHaveChildrenAndNotInactive(countQuest))
    {
        questNamePointer = StringAppend(questNameArray[countQuest],
                                        sText_SubQuestButton);
    }

}
static void QuestMenu_AddTextPrinterParameterized(u8 windowId, u8 fontId,
            const u8 *str, u8 x, u8 y,
            u8 letterSpacing, u8 lineSpacing, u8 speed, u8 colorIdx)
{
    AddTextPrinterParameterized4(windowId, fontId, x, y, letterSpacing,
                                 lineSpacing,
                                 sQuestMenuWindowFontColors[colorIdx], speed, str);
}

static void MoveCursorFunc(s32 questId, bool8 onInit,
                           struct ListMenu *list)
{
    PlayCursorSound(onInit);

    if (sStateDataPtr->moveModeOrigPos == 0xFF)
    {
        QuestMenu_DestroySprite(sStateDataPtr->spriteIconSlot ^ 1);
        sStateDataPtr->spriteIconSlot ^= 1;

        if (questId == LIST_CANCEL)
        {
            PrintDetailsForCancel();
        }
        else
        {
            GenerateAndPrintQuestDetails(questId);
            DetermineSpriteType(questId);
        }
    }
}

static void PlayCursorSound(bool8 firstRun)
{
    if (firstRun == FALSE)
    {
        PlaySE(SE_RG_BAG_CURSOR);
    }
}

static void PrintDetailsForCancel()
{
    FillWindowPixelBuffer(1, 0);

    QuestMenu_AddTextPrinterParameterized(1, FONT_SHORT, sText_Empty, 2, 3, 2, 0, 0,
                                          QUESTCOLOR_HEADER);
    QuestMenu_AddTextPrinterParameterized(1, FONT_SHORT, sText_Empty, 40, 19, 5, 0, 0,
                                          QUESTCOLOR_HEADER);

    QuestMenu_CreateSprite(-1, sStateDataPtr->spriteIconSlot, ITEM);
}

void GenerateAndPrintQuestDetails(s32 questId)
{
    GenerateQuestLocation(questId);
    PrintQuestLocation(questId);
    GenerateQuestFlavorText(questId);
    PrintQuestFlavorText(questId);
}
void GenerateQuestLocation(s32 questId)
{
    if (!IsSubquestMode())
    {
        StringCopy(gStringVar2, sSideQuests[questId].map);
    }
    else
    {
        StringCopy(gStringVar2,
                   sSideQuests[sStateDataPtr->parentQuest].subquests[questId].map);
    }

    StringExpandPlaceholders(gStringVar4, sText_ShowLocation);
}
void PrintQuestLocation(s32 questId)
{
    FillWindowPixelBuffer(1, 0);
    QuestMenu_AddTextPrinterParameterized(1, FONT_SHORT, gStringVar4, 2, 3, 2, 0, 0,
                                          QUESTCOLOR_FOOTER);
}
void GenerateQuestFlavorText(s32 questId)
{
    if (IsSubquestMode() == FALSE)
    {
        if (IsQuestInactiveState(questId) == TRUE)
        {
            StringCopy(gStringVar1, sText_StartForMore);
        }
        if (IsQuestActiveState(questId) == TRUE)
        {
            UpdateQuestFlavorText(questId);
        }
        if (IsQuestRewardState(questId) == TRUE)
        {
            StringCopy(gStringVar1, sText_ReturnRecieveReward);
        }
        if (IsQuestCompletedState(questId) == TRUE)
        {
            StringCopy(gStringVar1, sSideQuests[questId].donedesc);
        }
    }
    else
    {
        if (IsSubquestCompletedState(questId) == TRUE)
        {
            StringCopy(gStringVar1,
                       sSideQuests[sStateDataPtr->parentQuest].subquests[questId].desc);
        }
        else
        {
            StringCopy(gStringVar1, sText_Empty);
        }
    }

    StringExpandPlaceholders(gStringVar3, gStringVar1);
}
void UpdateQuestFlavorText(s32 questId)
{
    StringCopy(gStringVar1, sSideQuests[questId].desc);
}
void PrintQuestFlavorText(s32 questId)
{
    QuestMenu_AddTextPrinterParameterized(1, FONT_SHORT, gStringVar3, 40, 19, 5, 0, 0,
                                          QUESTCOLOR_FOOTER);
}

bool8 IsSubquestCompletedState(s32 questId)
{
    if (QuestMenu_GetSetSubquestState(sStateDataPtr->parentQuest,
                                      FLAG_GET_COMPLETED,
                                      questId))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
bool8 IsQuestRewardState(s32 questId)
{
    if (QuestMenu_GetSetQuestState(questId, FLAG_GET_REWARD))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool8 IsQuestInactiveState(s32 questId)
{
    if (!QuestMenu_GetSetQuestState(questId, FLAG_GET_ACTIVE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool8 IsQuestActiveState(s32 questId)
{
    if (QuestMenu_GetSetQuestState(questId, FLAG_GET_ACTIVE))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool8 IsQuestCompletedState(s32 questId)
{
    if (QuestMenu_GetSetQuestState(questId, FLAG_GET_COMPLETED))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool8 UNUSED IsQuestUnlocked(s32 questId)
{
    if (QuestMenu_GetSetQuestState(questId, FLAG_GET_UNLOCKED))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void DetermineSpriteType(s32 questId)
{
    u16 spriteId;
    u8 spriteType;

    if (IsSubquestMode() == FALSE)
    {
        spriteId = sSideQuests[questId].sprite;
        spriteType = sSideQuests[questId].spritetype;

        QuestMenu_CreateSprite(spriteId, sStateDataPtr->spriteIconSlot,
                               spriteType);
    }
    else if (IsSubquestCompletedState(questId) == TRUE)
    {
        spriteId =
              sSideQuests[sStateDataPtr->parentQuest].subquests[questId].sprite;
        spriteType =
              sSideQuests[sStateDataPtr->parentQuest].subquests[questId].spritetype;
        QuestMenu_CreateSprite(spriteId, sStateDataPtr->spriteIconSlot,
                               spriteType);
    }
    else
    {
        QuestMenu_CreateSprite(ITEM_NONE, sStateDataPtr->spriteIconSlot, ITEM);
    }
    QuestMenu_DestroySprite(sStateDataPtr->spriteIconSlot ^ 1);
    sStateDataPtr->spriteIconSlot ^= 1;
}
static void QuestMenu_CreateSprite(u16 itemId, u8 idx, u8 spriteType)
{
    u8 *ptr = &sItemMenuIconSpriteIds[10];
    u8 spriteId = MAX_SPRITES;

    if (ptr[idx] == 0xFF)
    {
        FreeSpriteTilesByTag(102 + idx);
        FreeSpritePaletteByTag(102 + idx);

        switch (spriteType)
        {
            case OBJECT:
                spriteId = CreateObjectGraphicsSprite(itemId, SpriteCallbackDummy, 20,
                                                      132, 0);
                break;
            case ITEM:
                spriteId = AddItemIconSprite(102 + idx, 102 + idx, itemId);
                break;
            case PKMN:
                LoadMonIconPalettes();
                spriteId = CreateMonIcon(itemId, SpriteCallbackDummy, 20, 132, 0, 0xFFFFFFFF);
                break;
            default:
                break;
        }

        if (spriteId != MAX_SPRITES)
        {
            gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
            ptr[idx] = spriteId;

            if (spriteType == ITEM)
            {
                gSprites[spriteId].x2 = 24;
                gSprites[spriteId].y2 = 140;
            }
        }
    }
}

void ResetSpriteState(void)
{
    u16 i;

    for (i = 0; i < NELEMS(sItemMenuIconSpriteIds); i++)
    {
        sItemMenuIconSpriteIds[i] = 0xFF;
    }
}

static void QuestMenu_DestroySprite(u8 idx)
{
    u8 *ptr = &sItemMenuIconSpriteIds[10];

    if (ptr[idx] != 0xFF)
    {
        u16 palTag = GetSpritePaletteTagByPaletteNum(
                           gSprites[ptr[idx]].oam.paletteNum);
        DestroySprite(&gSprites[ptr[idx]]);
        ptr[idx] = 0xFF;

        if (sStateDataPtr->oldPaletteTag != palTag)
        {
            if (sStateDataPtr->oldPaletteTag != 0)
            {
                FreeSpriteTilesByTag(sStateDataPtr->oldPaletteTag);
                sStateDataPtr->oldPaletteTag = palTag;
            }
        }
    }
}
static void GenerateStateAndPrint(u8 windowId, u32 questId,
                                  u8 y)
{
    u8 colorIndex;

    if (questId != LIST_CANCEL)
    {
        if (IsSubquestMode())
        {
            colorIndex = GenerateSubquestState(questId);
        }
        else
        {
            colorIndex = GenerateQuestState(questId);
        }

        PrintQuestState(windowId, y, colorIndex);
    }
}

u8 GenerateSubquestState(u8 questId)
{
    u8 parentQuest = sStateDataPtr->parentQuest;

    if (QuestMenu_GetSetSubquestState(parentQuest, FLAG_GET_COMPLETED,
                                      questId))
    {
        StringCopy(gStringVar4, sSideQuests[parentQuest].subquests[questId].type);
    }
    else
    {
        StringCopy(gStringVar4, sText_Empty);
    }

    return QUESTCOLOR_QUEST_DONE;
}

u8 GenerateQuestState(u8 questId)
{
    if (QuestMenu_GetSetQuestState(questId, FLAG_GET_COMPLETED))
    {
        StringCopy(gStringVar4, sText_Complete);
        return QUESTCOLOR_QUEST_DONE;
    }
    else if (QuestMenu_GetSetQuestState(questId, FLAG_GET_REWARD))
    {
        StringCopy(gStringVar4, sText_Reward);
        return QUESTCOLOR_QUEST_REWARD;
    }
    else if (QuestMenu_GetSetQuestState(questId, FLAG_GET_ACTIVE))
    {
        StringCopy(gStringVar4, sText_Active);
        return QUESTCOLOR_QUEST_ACTIVE;
    }
    else
    {
        StringCopy(gStringVar4, sText_Empty);
    }

    return 0;
}

void PrintQuestState(u8 windowId, u8 y, u8 colorIndex)
{
    QuestMenu_AddTextPrinterParameterized(windowId, FONT_SMALL, gStringVar4, 200, y, 0,
                                          0, 0xFF, colorIndex);
}

static void GenerateAndPrintHeader(void)
{
    GenerateDenominatorNumQuests();
    GenerateNumeratorNumQuests();
    GenerateMenuContext();

    PrintNumQuests();
    PrintMenuContext();

    if (!IsSubquestMode())
    {
        PrintTypeFilterButton();
    }
}
static void GenerateDenominatorNumQuests(void)
{
    ConvertIntToDecimalStringN(gStringVar2, QUEST_COUNT,
                               STR_CONV_MODE_LEFT_ALIGN, 6);
}

static void GenerateNumeratorNumQuests(void)
{
    u8 mode = sStateDataPtr->filterMode % 10;
    u8 parentQuest = sStateDataPtr->parentQuest;

    switch (mode)
    {
        case SORT_DEFAULT:
            ConvertIntToDecimalStringN(gStringVar1, CountUnlockedQuests(),
                                       STR_CONV_MODE_LEFT_ALIGN,
                                       6);
            break;
        case SORT_INACTIVE:
            ConvertIntToDecimalStringN(gStringVar1, CountInactiveQuests(),
                                       STR_CONV_MODE_LEFT_ALIGN,
                                       6);
            break;
        case SORT_ACTIVE:
            ConvertIntToDecimalStringN(gStringVar1, CountActiveQuests(),
                                       STR_CONV_MODE_LEFT_ALIGN, 6);
            break;
        case SORT_REWARD:
            ConvertIntToDecimalStringN(gStringVar1, CountRewardQuests(),
                                       STR_CONV_MODE_LEFT_ALIGN, 6);
            break;
        case SORT_DONE:
            ConvertIntToDecimalStringN(gStringVar1, CountCompletedQuests(),
                                       STR_CONV_MODE_LEFT_ALIGN,
                                       6);
            break;
    }

    if (IsSubquestMode())
    {
        ConvertIntToDecimalStringN(gStringVar2,
                                   sSideQuests[parentQuest].numSubquests,
                                   STR_CONV_MODE_LEFT_ALIGN, 6);
        ConvertIntToDecimalStringN(gStringVar1, CountCompletedQuests(),
                                   STR_CONV_MODE_LEFT_ALIGN,
                                   6);
    }
}

static void GenerateMenuContext(void)
{
    u8 mode = sStateDataPtr->filterMode % 10;
    u8 parentQuest = sStateDataPtr->parentQuest;

    switch (mode)
    {
        case SORT_DEFAULT:
            questNamePointer = StringCopy(questNameArray[QUEST_ARRAY_COUNT],
                                          sText_AllHeader);
            break;
        case SORT_INACTIVE:
            questNamePointer = StringCopy(questNameArray[QUEST_ARRAY_COUNT],
                                          sText_InactiveHeader);
            break;
        case SORT_ACTIVE:
            questNamePointer = StringCopy(questNameArray[QUEST_ARRAY_COUNT],
                                          sText_ActiveHeader);
            break;
        case SORT_REWARD:
            questNamePointer = StringCopy(questNameArray[QUEST_ARRAY_COUNT],
                                          sText_RewardHeader);
            break;
        case SORT_DONE:
            questNamePointer = StringCopy(questNameArray[QUEST_ARRAY_COUNT],
                                          sText_CompletedHeader);
            break;
    }

    if (IsAlphaMode())
    {
        questNamePointer = StringAppend(questNameArray[QUEST_ARRAY_COUNT],
                                        sText_AZ);
    }
    if (IsSubquestMode())
    {
        questNamePointer = StringCopy(questNameArray[QUEST_ARRAY_COUNT],
                                      sSideQuests[parentQuest].name);

    }
}

static void PrintNumQuests(void)
{
    StringExpandPlaceholders(gStringVar4, sText_QuestNumberDisplay);
    QuestMenu_AddTextPrinterParameterized(2, FONT_SMALL, gStringVar4, 167, 1, 0, 1, 0,
                                          QUESTCOLOR_HEADER);
}
static void PrintMenuContext(void)
{
    QuestMenu_AddTextPrinterParameterized(2, FONT_SMALL,
                                          questNameArray[QUEST_ARRAY_COUNT], 10, 1, 0, 1, 0, QUESTCOLOR_HEADER);
}
static void PrintTypeFilterButton(void)
{
    QuestMenu_AddTextPrinterParameterized(2, FONT_SMALL, sText_Type, 198, 1,
                                          0, 1, 0, QUESTCOLOR_HEADER);

}

static void Task_Main(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    s32 input = ListMenu_ProcessInput(data[0]);

    u8 selectedQuestId = sListMenuItems[GetCursorPosition()].id;

    if (!gPaletteFade.active)
    {
        ListMenuGetScrollAndRow(data[0], &sListMenuState.scroll,
                                &sListMenuState.row);

        switch (input)
        {
            case LIST_NOTHING_CHOSEN:
                if (JOY_NEW(R_BUTTON))
                {
                    ChangeModeAndCleanUp(taskId);
                }
                if (JOY_NEW(START_BUTTON))
                {
                    ToggleAlphaModeAndCleanUp(taskId);
                }
                if (JOY_NEW(SELECT_BUTTON))
                {
                    ToggleFavoriteAndCleanUp(taskId, selectedQuestId);
                }
                break;

            case LIST_CANCEL:
                if (IsSubquestMode())
                {
                    ReturnFromSubquestAndCleanUp(taskId);
                }
                else
                {
                    TurnOffQuestMenu(taskId);
                }
                break;

            default:
                if (!IsSubquestMode())
                {
                    EnterSubquestModeAndCleanUp(taskId, data, input);
                }
                break;
        }
    }
}

void ManageFavorites(u8 selectedQuestId)
{
    if (QuestMenu_GetSetQuestState(selectedQuestId, FLAG_GET_FAVORITE))
    {
        QuestMenu_GetSetQuestState(selectedQuestId, FLAG_REMOVE_FAVORITE);
    }
    else
    {
        QuestMenu_GetSetQuestState(selectedQuestId, FLAG_SET_FAVORITE);
    }
}

static void Task_QuestMenuCleanUp(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    QuestMenu_RemoveScrollIndicatorArrowPair();
    DestroyListMenuTask(data[0], &sListMenuState.scroll, &sListMenuState.row);
    ClearStdWindowAndFrameToTransparent(2, FALSE);

    InitItems();
    GenerateAndPrintHeader();
    AllocateResourcesForListMenu();
    BuildMenuTemplate();
    PlaceTopMenuScrollIndicatorArrows();

    if (sStateDataPtr->restoreCursor == TRUE)
    {
        RestoreSavedScrollAndRow(data);
    }
    else
    {
        ResetCursorToTop(data);
    }

}

static void RestoreSavedScrollAndRow(s16 *data)
{
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate,
                           sListMenuState.storedScrollOffset,
                           sListMenuState.storedRowPosition);
}
static void ResetCursorToTop(s16 *data)
{
    sListMenuState.row = 0;
    sListMenuState.scroll = 0;
    data[0] = ListMenuInit(&gMultiuseListMenuTemplate, sListMenuState.scroll,
                           sListMenuState.row);
}

static void QuestMenu_RemoveScrollIndicatorArrowPair(void)
{
    if (sStateDataPtr->scrollIndicatorArrowPairId != 0xFF)
    {
        RemoveScrollIndicatorArrowPair(sStateDataPtr->scrollIndicatorArrowPairId);
        sStateDataPtr->scrollIndicatorArrowPairId = 0xFF;
    }
}


void EnterSubquestModeAndCleanUp(u8 taskId, s16 *data,
                                 s32 input)
{
    if (DoesQuestHaveChildrenAndNotInactive(input))
    {
        PrepareFadeOut(taskId);

        PlaySE(SE_SELECT);
        sStateDataPtr->parentQuest = input;
        sStateDataPtr->filterMode = ManageMode(SUB);
        SaveScrollAndRow(data);
        gTasks[taskId].func = Task_FadeOut;
    }
}
void ChangeModeAndCleanUp(u8 taskId)
{
    if (!IsSubquestMode())
    {
        PlaySE(SE_SELECT);
        sStateDataPtr->filterMode = ManageMode(INCREMENT);
        Task_QuestMenuCleanUp(taskId);
    }
}
void ToggleAlphaModeAndCleanUp(u8 taskId)
{
    if (!IsSubquestMode())
    {
        PlaySE(SE_SELECT);
        sStateDataPtr->filterMode = ManageMode(ALPHA);
        Task_QuestMenuCleanUp(taskId);
    }
}
void ToggleFavoriteAndCleanUp(u8 taskId, u8 selectedQuestId)
{
    if (!IsSubquestMode()
                && !CheckSelectedIsCancel(selectedQuestId))
    {
        PlaySE(SE_SELECT);
        ManageFavorites(selectedQuestId);
        sStateDataPtr->restoreCursor = FALSE;
        Task_QuestMenuCleanUp(taskId);
    }
}
bool8 CheckSelectedIsCancel(u8 selectedQuestId)
{
    if (selectedQuestId == (0xFF - 1))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
void ReturnFromSubquestAndCleanUp(u8 taskId)
{
    PrepareFadeOut(taskId);

    PlaySE(SE_SELECT);
    sStateDataPtr->filterMode = ManageMode(SUB);
    gTasks[taskId].func = Task_FadeOut;
}

static void SetGpuRegBaseForFade()
{
    //Sets the GPU registers to prepare for a hardware fade
    SetGpuReg(REG_OFFSET_BLDCNT,
              BLDCNT_TGT1_OBJ | BLDCNT_TGT1_BG0 | BLDCNT_TGT2_BG1 |
              BLDCNT_EFFECT_BLEND);      //Blend Sprites and BG0 into BG1
    SetGpuReg(REG_OFFSET_BLDY, 0);
}

#define MAX_FADE_INTENSITY 16
#define MIN_FADE_INTENSITY 0

void InitFadeVariables(u8 taskId, u8 blendWeight, u8 frameDelay,
                       u8 frameTimerBase, u8 delta)
{
    gTasks[taskId].data[1] = blendWeight;
    gTasks[taskId].data[2] = frameDelay;
    gTasks[taskId].data[3] = gTasks[taskId].data[frameTimerBase];
    gTasks[taskId].data[4] = delta;
}


static void PrepareFadeOut(u8 taskId)
{
    SetGpuRegBaseForFade();
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(MAX_FADE_INTENSITY, 0));
    InitFadeVariables(taskId, MAX_FADE_INTENSITY, 0, 2, 2);
}

static bool8 HandleFadeOut(u8 taskId)
{
    if (gTasks[taskId].data[3]-- != 0)
    {
        return FALSE;
    }

    //Set the timer, decrease the fade weight by the delta, increase the delta by the timer
    gTasks[taskId].data[3] = gTasks[taskId].data[2];
    gTasks[taskId].data[1] -= gTasks[taskId].data[4];
    gTasks[taskId].data[2] += gTasks[taskId].data[3];

    //When blend weight runs out, set final blend and quit
    if (gTasks[taskId].data[1] <= 0)
    {
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, gTasks[taskId].data[1]));
        return TRUE;
    }
    //Set intermediate blend state
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[1],
                MAX_FADE_INTENSITY - gTasks[taskId].data[1]));
    return FALSE;
}

static void PrepareFadeIn(u8 taskId)
{
    SetGpuRegBaseForFade();
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0,
                MAX_FADE_INTENSITY));
    InitFadeVariables(taskId, MIN_FADE_INTENSITY, 0, 1, 2);
}

static bool8 HandleFadeIn(u8 taskId)
{
    //Set the timer, ncrease the fade weight by the delta,
    gTasks[taskId].data[3] = gTasks[taskId].data[2];
    gTasks[taskId].data[1] += gTasks[taskId].data[4];

    //When blend weight reaches max, set final blend and quit
    if (gTasks[taskId].data[1] >= MAX_FADE_INTENSITY)
    {
        SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(MAX_FADE_INTENSITY,
                    MIN_FADE_INTENSITY));
        return TRUE;
    }
    //Set intermediate blend state
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(gTasks[taskId].data[1],
                MAX_FADE_INTENSITY - gTasks[taskId].data[1]));
    return FALSE;
}

static void Task_FadeOut(u8 taskId)
{
    if (HandleFadeOut(taskId))
    {
        PrepareFadeIn(taskId);
        Task_QuestMenuCleanUp(taskId);
        gTasks[taskId].func = Task_FadeIn;
    }
}

static void Task_FadeIn(u8 taskId)
{
    if (HandleFadeIn(taskId))
    {
        gTasks[taskId].func = Task_Main;
    }
}

static void Task_QuestMenuWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sListMenuState.savedCallback);
        FreeResources();
        DestroyTask(taskId);
    }
}

static void FadeAndBail(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_QuestMenuWaitFadeAndBail, 0);
    SetVBlankCallback(VBlankCB);
    SetMainCallback2(MainCB);
}


#define try_free(ptr) ({        \
        void ** ptr__ = (void **)&(ptr);   \
        if (*ptr__ != NULL)                \
            Free(*ptr__);                  \
    })

static void FreeResources(void)
{
    int i;

    try_free(sStateDataPtr);
    try_free(sBg1TilemapBuffer);
    try_free(sListMenuItems);

    for (i = QUEST_ARRAY_COUNT; i > -1; i--)
    {
        try_free(questNameArray[i]);
    }

    try_free(questNameArray);
    FreeAllWindowBuffers();
}

void TurnOffQuestMenu(u8 taskId)
{
    SetInitializedFlag(0);
    gTasks[taskId].func = Task_QuestMenuTurnOff1;
}
static void Task_QuestMenuTurnOff1(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_QuestMenuTurnOff2;
}

static void Task_QuestMenuTurnOff2(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        DestroyListMenuTask(data[0], &sListMenuState.scroll, &sListMenuState.row);
        if (sStateDataPtr->savedCallback != NULL)
        {
            SetMainCallback2(sStateDataPtr->savedCallback);
        }
        else
        {
            SetMainCallback2(sListMenuState.savedCallback);
        }

        QuestMenu_RemoveScrollIndicatorArrowPair();
        FreeResources();
        DestroyTask(taskId);
    }
}

void Task_QuestMenu_OpenFromStartMenu(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        QuestMenu_Init(tItemPcParam, CB2_ReturnToFullScreenStartMenu);
        DestroyTask(taskId);
    }
}

void QuestMenu_CopyQuestName(u8 *dst, u8 questId)
{
    StringCopy(dst, sSideQuests[questId].name);
}

void QuestMenu_CopySubquestName(u8 *dst, u8 parentId, u8 childId)
{
    StringCopy(dst, sSideQuests[parentId].subquests[childId].name);
}

void QuestMenu_ResetMenuSaveData(void)
{
    memset(&gSaveBlock3Ptr->questData, 0,
           sizeof(gSaveBlock3Ptr->questData));
    memset(&gSaveBlock3Ptr->subQuests, 0,
           sizeof(gSaveBlock3Ptr->subQuests));
}
