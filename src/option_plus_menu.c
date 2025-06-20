#include "global.h"
#include "main.h"
#include "bg.h"
#include "decompress.h"
#include "difficulty.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "m4a.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "option_plus_menu.h"
#include "scanline_effect.h"
#include "sound.h"
#include "palette.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "tx_randomizer_and_challenges.h"
#include "window.h"
#include "strings.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"

enum
{
    MENUMODE_OPTIONSPLUS,
    MENUMODE_CHALLENGES
};

enum
{
    OPTIONSPLUS_MENU_VISUALS,
    OPTIONSPLUS_MENU_BATTLE,
    OPTIONSPLUS_MENU_MISC,
    OPTIONSPLUS_MENU_COUNT,
};

enum
{
    CHALLENGES_MENU_RANDOMIZER,
    CHALLENGES_MENU_NUZLOCKE,
    CHALLENGES_MENU_DIFFICULTY,
    CHALLENGES_MENU_COUNT,
};

#define MAX_MENU_AMOUNT 6

// Menu items
enum
{
    MENUITEM_VISUALS_TEXTSPEED,
    MENUITEM_VISUALS_FONT,
    MENUITEM_VISUALS_FRAMETYPE,
    MENUITEM_VISUALS_UNIQUE_COLORS,
    MENUITEM_VISUALS_ANIMATIONS,
    MENUITEM_VISUALS_CANCEL,
    MENUITEM_VISUALS_COUNT,
};

enum
{
    MENUITEM_BATTLE_BATTLESCENE,
    MENUITEM_BATTLE_BATTLESTYLE,
    MENUITEM_BATTLE_HP_BAR,
    MENUITEM_BATTLE_EXP_BAR,
    MENUITEM_BATTLE_ANIM_SPEED,
    MENUITEM_BATTLE_IV_VIEW,
    MENUITEM_BATTLE_EFFECTIVENESS,
    MENUITEM_BATTLE_SHOW_TYPES,
    MENUITEM_BATTLE_CANCEL,
    MENUITEM_BATTLE_COUNT,
};

enum
{
    MENUITEM_MISC_SOUND,
    MENUITEM_MISC_MUSIC_VOLUME,
    MENUITEM_MISC_SFX_VOLUME,
    MENUITEM_MISC_CRIES_VOLUME,
    MENUITEM_MISC_UNIT_SYSTEM,
    MENUITEM_MISC_L_BUTTONMODE,
    MENUITEM_MISC_R_BUTTONMODE,
    MENUITEM_MISC_OVERWORLD_SPEED,
    MENUITEM_MISC_MATCHCALL,
    MENUITEM_MISC_START_MENU,
    MENUITEM_MISC_DEBUG_MODE,
    MENUITEM_MISC_CANCEL,
    MENUITEM_MISC_COUNT,
};

enum
{
    MENUITEM_RANDOM_OFF_ON,
    MENUITEM_RANDOM_STARTER,
    MENUITEM_RANDOM_WILD_PKMN,
    MENUITEM_RANDOM_TRAINER,
    MENUITEM_RANDOM_STATIC,
    MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL,
    MENUITEM_RANDOM_INCLUDE_LEGENDARIES,
    MENUITEM_RANDOM_TYPE,
    MENUITEM_RANDOM_MOVES,
    MENUITEM_RANDOM_ABILITIES,
    MENUITEM_RANDOM_EVOLUTIONS,
    MENUITEM_RANDOM_EVOLUTIONS_METHODS,
    MENUITEM_RANDOM_TYPE_EFFEC,
    MENUITEM_RANDOM_ITEMS,
    MENUITEM_RANDOM_CHAOS,
    MENUITEM_RANDOM_NEXT,
    MENUITEM_RANDOM_COUNT,
};

enum
{
    MENUITEM_NUZLOCKE_NUZLOCKE,
    MENUITEM_NUZLOCKE_SPECIES_CLAUSE,
    MENUITEM_NUZLOCKE_SHINY_CLAUSE,
    MENUITEM_NUZLOCKE_DELETION,
    MENUITEM_NUZLOCKE_NEXT,
    MENUITEM_NUZLOCKE_COUNT,
};

enum
{
    MENUITEM_DIFFICULTY_TRAINER_DIFFICULTY,
    MENUITEM_DIFFICULTY_LEVEL_CAP,
    MENUITEM_DIFFICULTY_ITEM_PLAYER,
    MENUITEM_DIFFICULTY_ITEM_TRAINER,
    MENUITEM_DIFFICULTY_NO_EVS,
    MENUITEM_DIFFICULTY_SCALING_IVS,
    MENUITEM_DIFFICULTY_SCALING_EVS,
    MENUITEM_DIFFICULTY_SAVE,
    MENUITEM_DIFFICULTY_COUNT,
};

// Window Ids
enum
{
    WIN_TOPBAR,
    WIN_OPTIONS,
    WIN_DESCRIPTION
};

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    [WIN_TOPBAR] =
    {
        .bg = 1,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] =
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 10,
        .paletteNum = 1,
        .baseBlock = 62
    },
    [WIN_DESCRIPTION] =
    {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 1,
        .baseBlock = 500
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
    {
       .bg = 0,
       .charBaseIndex = 1,
       .mapBaseIndex = 30,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
    },
    {
       .bg = 1,
       .charBaseIndex = 1,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 0,
    },
    {
       .bg = 2,
       .charBaseIndex = 0,
       .mapBaseIndex = 29,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 1,
    },
    {
       .bg = 3,
       .charBaseIndex = 3,
       .mapBaseIndex = 27,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 2,
    },
};

struct OptionsPlusOptions
{
    u8 visuals[MENUITEM_VISUALS_COUNT];
    u8 battle[MENUITEM_BATTLE_COUNT];
    u8 misc[MENUITEM_MISC_COUNT];
};

struct ChallengesOptions
{
    u8 randomizer[MENUITEM_RANDOM_COUNT];
    u8 nuzlocke[MENUITEM_NUZLOCKE_COUNT];
    u8 difficulty[MENUITEM_DIFFICULTY_COUNT];
};

struct OptionMenu
{
    u8 submenu;
    union
    {
        struct OptionsPlusOptions optionsPlus;
        struct ChallengesOptions challenges;
    } selection;
    int menuCursor[MAX_MENU_AMOUNT];
    int visibleCursor[MAX_MENU_AMOUNT];
    u8 arrowTaskId;
    u8 gfxLoadState;
    u8 optionMode;
};

struct OptionFuncs
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
};

#define MAX_DESCRIPTION_AMOUNT 4

struct OptionInfo
{
    void (*drawChoices)(int selection, int y);
    int (*processInput)(int selection);
    const u8 *const optionName;
    const u8 *const optionDescriptions[MAX_DESCRIPTION_AMOUNT];
    bool8 dontScrollDescription;
    const u8 *const optionDisabledDescription;
};

#define Y_DIFF 16 // Difference in pixels between items.
#define OPTIONS_ON_SCREEN 5
#define NUM_OPTIONS_FROM_BORDER 1

// local functions
static void MainCB2(void);
static void VBlankCB(void);
static void DrawTopBarText(void); //top Option text
static void DrawLeftSideOptionText(int selection, int y);
static void DrawRightSideChoiceText(const u8 *str, int x, int y, bool8 choosen, bool8 active);
static void DrawOptionMenuTexts(void); //left side text;
static void DrawChoices(u32 id, int y); //right side draw function
static void HighlightOptionMenuItem(void);
static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void ScrollMenu(int direction);
static void ScrollAll(int direction); // to bottom or top
static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3);
static int XOptions_ProcessInput(int x, int selection);
static int ProcessInput_Options_Two(int selection);
static int ProcessInput_Options_Three(int selection);
static int ProcessInput_Options_Four(int selection);
static int ProcessInput_Options_Eleven(int selection);
static int ProcessInput_FrameType(int selection);
static int ProcessInput_MusicVolume(int selection);
static int ProcessInput_SoundVolume(int selection);
static const u8 *const OptionTextDescription(void);
static const u8 *OptionTextRight(u8 menuItem);
static u8 MenuItemCount(void);
static u8 MenuItemCancel(void);
static void DrawDescriptionText(void);
static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style, bool8 active);
static void DrawChoices_Options_Four(const u8 *const *const strings, int selection, int y, bool8 active);
static void ReDrawAll(void);

static void DrawChoices_TextSpeed(int selection, int y);
static void DrawChoices_BattleScene(int selection, int y);
static void DrawChoices_BattleStyle(int selection, int y);
static void DrawChoices_Sound(int selection, int y);
static void DrawChoices_BarSpeed(int selection, int y); //HP and EXP
static void DrawChoices_UnitSystem(int selection, int y);
static void DrawChoices_Font(int selection, int y);
static void DrawChoices_FrameType(int selection, int y);
static void DrawChoices_MatchCall(int selection, int y);
static void DrawChoices_StartMenu(int selection, int y);
static void DrawChoices_DebugMode(int selection, int y);
static void DrawChoices_AnimSpeed(int selection, int y);
static void DrawChoices_UniqueColors(int selection, int y);
static void DrawChoices_IvView(int selection, int y);
static void DrawChoices_Effectiveness(int selection, int y);
static void DrawChoices_ShowTypes(int selection, int y);
static void DrawChoices_MonAnimations(int selection, int y);
static void DrawChoices_MusicVolume(int selection, int y);
static void DrawChoices_SFXVolume(int selection, int y);
static void DrawChoices_CriesVolume(int selection, int y);
static void DrawChoices_LButtonMode(int selection, int y);
static void DrawChoices_RButtonMode(int selection, int y);
static void DrawChoices_OverworldSpeed(int selection, int y);
static void DrawBgWindowFrames(void);

static void DrawChoices_Random_OffOn(int selection, int y, bool8 active);
static void DrawChoices_Random_OffRandom(int selection, int y, bool8 active);
static void DrawChoices_Random_Toggle(int selection, int y);
static void DrawChoices_Random_Starter(int selection, int y);
static void DrawChoices_Random_WildPkmn(int selection, int y);
static void DrawChoices_Random_Trainer(int selection, int y);
static void DrawChoices_Random_Static(int selection, int y);
static void DrawChoices_Random_EvoStages(int selection, int y);
static void DrawChoices_Random_Legendaries(int selection, int y);
static void DrawChoices_Random_Types(int selection, int y);
static void DrawChoices_Random_Moves(int selection, int y);
static void DrawChoices_Random_Abilities(int selection, int y);
static void DrawChoices_Random_Evolutions(int selection, int y);
static void DrawChoices_Random_EvolutionMethods(int selection, int y);
static void DrawChoices_Random_TypeEffect(int selection, int y);
static void DrawChoices_Random_Items(int selection, int y);
static void DrawChoices_Random_OffChaos(int selection, int y);

static void DrawChoices_Nuzlocke_OnOff(int selection, int y, bool8 active);
static void DrawChoices_Challenges_Nuzlocke(int selection, int y);
static void DrawChoices_Nuzlocke_SpeciesClause(int selection, int y);
static void DrawChoices_Nuzlocke_ShinyClause(int selection, int y);
static void DrawChoices_Nuzlocke_Deletion(int selection, int y);

static void DrawChoices_Challenges_LevelCap(int selection, int y);
static void DrawChoices_Challenges_TrainerDifficulties(int selection, int y);
static void DrawChoices_Challenges_YesNo(int selection, int y, bool8 active);
static void DrawChoices_Challenges_ItemsPlayer(int selection, int y);
static void DrawChoices_Challenges_ItemsTrainer(int selection, int y);
static void DrawChoices_Challenges_NoEVs(int selection, int y);
static void DrawChoices_Challenges_ScalingIVs(int selection, int y);
static void DrawChoices_Challenges_ScalingEVs(int selection, int y);

// EWRAM vars
EWRAM_DATA static struct OptionMenu *sOptions = NULL;
static EWRAM_DATA u8 *sBg2TilemapBuffer = NULL;
static EWRAM_DATA u8 *sBg3TilemapBuffer = NULL;

// const data
static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};
static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text_custom.gbapal");

static const u32 sOptionsPlusTiles[] = INCBIN_U32("graphics/ui_options_plus/options_plus_tiles.4bpp.smol");
static const u16 sOptionsPlusPalette[] = INCBIN_U16("graphics/ui_options_plus/options_plus_tiles.gbapal");
static const u32 sOptionsPlusTilemap[] = INCBIN_U32("graphics/ui_options_plus/options_plus_tiles.bin.smolTM");

// Scrolling Background
static const u32 sScrollBgTiles[] = INCBIN_U32("graphics/ui_options_plus/scroll_tiles.4bpp.smol");
static const u32 sScrollBgTilemap[] = INCBIN_U32("graphics/ui_options_plus/scroll_tiles.bin.smolTM");
static const u16 sScrollBgPalette[] = INCBIN_U16("graphics/ui_options_plus/scroll_tiles.gbapal");

#define TEXT_COLOR_OPTIONS_GRAY_BG              1
#define TEXT_COLOR_OPTIONS_WHITE                2
#define TEXT_COLOR_OPTIONS_GRAY_SHADOW          3
#define TEXT_COLOR_OPTIONS_GRAY_LIGHT_FG        4
#define TEXT_COLOR_OPTIONS_ORANGE_FG            5
#define TEXT_COLOR_OPTIONS_ORANGE_SHADOW        6
#define TEXT_COLOR_OPTIONS_RED_FG               7
#define TEXT_COLOR_OPTIONS_RED_SHADOW           8
#define TEXT_COLOR_OPTIONS_GREEN_FG             9
#define TEXT_COLOR_OPTIONS_GREEN_SHADOW         10
#define TEXT_COLOR_OPTIONS_GREEN_DARK_FG        11
#define TEXT_COLOR_OPTIONS_GREEN_DARK_SHADOW    12
#define TEXT_COLOR_OPTIONS_RED_DARK_FG          13
#define TEXT_COLOR_OPTIONS_RED_DARK_SHADOW      14

// Menu draw and input functions
static const struct OptionFuncs sItemFunctionsVisuals[MENUITEM_VISUALS_COUNT] =
{
    [MENUITEM_VISUALS_TEXTSPEED]     = {DrawChoices_TextSpeed,     ProcessInput_Options_Four},
    [MENUITEM_VISUALS_FONT]          = {DrawChoices_Font,          ProcessInput_Options_Two},
    [MENUITEM_VISUALS_FRAMETYPE]     = {DrawChoices_FrameType,     ProcessInput_FrameType},
    [MENUITEM_VISUALS_UNIQUE_COLORS] = {DrawChoices_UniqueColors,  ProcessInput_Options_Two},
    [MENUITEM_VISUALS_ANIMATIONS]    = {DrawChoices_MonAnimations, ProcessInput_Options_Two},
    [MENUITEM_VISUALS_CANCEL]        = {NULL, NULL},
};

static const struct OptionInfo sItemInfoVisuals[MENUITEM_VISUALS_COUNT] =
{
    [MENUITEM_VISUALS_TEXTSPEED] =
    {
        .drawChoices = DrawChoices_TextSpeed,
        .processInput = ProcessInput_Options_Four,
        .optionName = COMPOUND_STRING("TEXT SPEED"),
        .optionDescriptions = {
            COMPOUND_STRING("Choose one of the four text-display\nspeeds."),
        },
        .dontScrollDescription = TRUE,
        .optionDisabledDescription = COMPOUND_STRING("Text can only be in a set\nspeed."),
    },
    [MENUITEM_VISUALS_FONT] =
    {
        .drawChoices = DrawChoices_Font,
        .processInput = ProcessInput_Options_Two,
        .optionName = COMPOUND_STRING("FONT"),
        .optionDescriptions = {
            COMPOUND_STRING("Choose the font design."),
            COMPOUND_STRING("Choose the font design."),
        },
        .optionDisabledDescription = COMPOUND_STRING("Fonts cannot be changed\ncurrectly."),
    },
    [MENUITEM_VISUALS_FRAMETYPE] =
    {
        .drawChoices = DrawChoices_FrameType,
        .processInput = ProcessInput_FrameType,
        .optionName = COMPOUND_STRING("FRAME"),
        .optionDescriptions = {
            COMPOUND_STRING("Choose the frame surrounding the\nwindows."),
        },
        .dontScrollDescription = TRUE,
        .optionDisabledDescription = COMPOUND_STRING("Text can only be in a set\nspeed."),
    },
    [MENUITEM_VISUALS_UNIQUE_COLORS] =
    {
        .drawChoices = DrawChoices_UniqueColors,
        .processInput = ProcessInput_Options_Two,
        .optionName = COMPOUND_STRING("UNIQUE COLORS"),
        .optionDescriptions = {
            COMPOUND_STRING("Enables unique colors for\nPuppets."),
            COMPOUND_STRING("Disables unique colors for\nPuppets."),
        },
        .optionDisabledDescription = COMPOUND_STRING("Fonts cannot be changed\ncurrectly."),
    },
    [MENUITEM_VISUALS_ANIMATIONS] =
    {
        .drawChoices = DrawChoices_MonAnimations,
        .processInput = ProcessInput_Options_Two,
        .optionName = COMPOUND_STRING("ANIMATIONS"),
        .optionDescriptions = {
            COMPOUND_STRING("Animations will play for\nPuppets."),
            COMPOUND_STRING("Animations are disabled for\nPuppets."),
        },
        .optionDisabledDescription = COMPOUND_STRING(""),
    },
    [MENUITEM_VISUALS_CANCEL] =
    {
        .optionName = COMPOUND_STRING("SAVE"),
        .optionDescriptions = {
            COMPOUND_STRING("Save your settings."),
        },
        .optionDisabledDescription = COMPOUND_STRING(""),
    },
};

static const struct OptionFuncs sItemFunctionsBattle[MENUITEM_BATTLE_COUNT] =
{
    [MENUITEM_BATTLE_BATTLESCENE]   = {DrawChoices_BattleScene,   ProcessInput_Options_Two},
    [MENUITEM_BATTLE_BATTLESTYLE]   = {DrawChoices_BattleStyle,   ProcessInput_Options_Two},
    [MENUITEM_BATTLE_HP_BAR]        = {DrawChoices_BarSpeed,      ProcessInput_Options_Eleven},
    [MENUITEM_BATTLE_EXP_BAR]       = {DrawChoices_BarSpeed,      ProcessInput_Options_Eleven},
    [MENUITEM_BATTLE_ANIM_SPEED]    = {DrawChoices_AnimSpeed,     ProcessInput_Options_Four},
    [MENUITEM_BATTLE_IV_VIEW]       = {DrawChoices_IvView,        ProcessInput_Options_Two},
    [MENUITEM_BATTLE_EFFECTIVENESS] = {DrawChoices_Effectiveness, ProcessInput_Options_Two},
    [MENUITEM_BATTLE_SHOW_TYPES]    = {DrawChoices_ShowTypes,     ProcessInput_Options_Two},
    [MENUITEM_BATTLE_CANCEL]        = {NULL, NULL},
};

static const struct OptionFuncs sItemFunctionsMisc[MENUITEM_MISC_COUNT] =
{
    [MENUITEM_MISC_SOUND]        = {DrawChoices_Sound,       ProcessInput_Options_Two},
    [MENUITEM_MISC_MUSIC_VOLUME] = {DrawChoices_MusicVolume, ProcessInput_MusicVolume},
    [MENUITEM_MISC_SFX_VOLUME]   = {DrawChoices_SFXVolume,   ProcessInput_SoundVolume},
    [MENUITEM_MISC_CRIES_VOLUME] = {DrawChoices_CriesVolume, ProcessInput_SoundVolume},
    [MENUITEM_MISC_UNIT_SYSTEM]  = {DrawChoices_UnitSystem,  ProcessInput_Options_Two},
    [MENUITEM_MISC_L_BUTTONMODE] = {DrawChoices_LButtonMode, ProcessInput_Options_Four},
    [MENUITEM_MISC_R_BUTTONMODE] = {DrawChoices_RButtonMode, ProcessInput_Options_Four},
    [MENUITEM_MISC_OVERWORLD_SPEED] = {DrawChoices_OverworldSpeed, ProcessInput_Options_Four},
    [MENUITEM_MISC_MATCHCALL]    = {DrawChoices_MatchCall,   ProcessInput_Options_Two},
    [MENUITEM_MISC_START_MENU]   = {DrawChoices_StartMenu,   ProcessInput_Options_Two},
    [MENUITEM_MISC_DEBUG_MODE]   = {DrawChoices_DebugMode,   ProcessInput_Options_Two},
    [MENUITEM_MISC_CANCEL]       = {NULL, NULL},
};

static const struct OptionFuncs sItemFunctionsRandom[MENUITEM_RANDOM_COUNT] =
{
    [MENUITEM_RANDOM_OFF_ON]                    = {DrawChoices_Random_Toggle,           ProcessInput_Options_Two},
    [MENUITEM_RANDOM_STARTER]                   = {DrawChoices_Random_Starter,          ProcessInput_Options_Three},
    [MENUITEM_RANDOM_WILD_PKMN]                 = {DrawChoices_Random_WildPkmn,         ProcessInput_Options_Two},
    [MENUITEM_RANDOM_TRAINER]                   = {DrawChoices_Random_Trainer,          ProcessInput_Options_Two},
    [MENUITEM_RANDOM_STATIC]                    = {DrawChoices_Random_Static,           ProcessInput_Options_Two},
    [MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]   = {DrawChoices_Random_EvoStages,        ProcessInput_Options_Two},
    [MENUITEM_RANDOM_INCLUDE_LEGENDARIES]       = {DrawChoices_Random_Legendaries,      ProcessInput_Options_Two},
    [MENUITEM_RANDOM_TYPE]                      = {DrawChoices_Random_Types,            ProcessInput_Options_Two},
    [MENUITEM_RANDOM_MOVES]                     = {DrawChoices_Random_Moves,            ProcessInput_Options_Two},
    [MENUITEM_RANDOM_ABILITIES]                 = {DrawChoices_Random_Abilities,        ProcessInput_Options_Two},
    [MENUITEM_RANDOM_EVOLUTIONS]                = {DrawChoices_Random_Evolutions,       ProcessInput_Options_Two},
    [MENUITEM_RANDOM_EVOLUTIONS_METHODS]        = {DrawChoices_Random_EvolutionMethods, ProcessInput_Options_Two},
    [MENUITEM_RANDOM_TYPE_EFFEC]                = {DrawChoices_Random_TypeEffect,       ProcessInput_Options_Two},
    [MENUITEM_RANDOM_ITEMS]                     = {DrawChoices_Random_Items,            ProcessInput_Options_Two},
    [MENUITEM_RANDOM_CHAOS]                     = {DrawChoices_Random_OffChaos,         ProcessInput_Options_Two},
    [MENUITEM_RANDOM_NEXT]                      = {NULL, NULL},
};

static const struct OptionFuncs sItemFunctionsNuzlocke[MENUITEM_NUZLOCKE_COUNT] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]        = {DrawChoices_Challenges_Nuzlocke,     ProcessInput_Options_Three},
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]  = {DrawChoices_Nuzlocke_SpeciesClause,  ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]    = {DrawChoices_Nuzlocke_ShinyClause,    ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_DELETION]        = {DrawChoices_Nuzlocke_Deletion,       ProcessInput_Options_Two},
    [MENUITEM_NUZLOCKE_NEXT]            = {NULL, NULL},
};

static const struct OptionFuncs sItemFunctionsDifficulty[MENUITEM_DIFFICULTY_COUNT] =
{
    [MENUITEM_DIFFICULTY_TRAINER_DIFFICULTY]    = {DrawChoices_Challenges_TrainerDifficulties,    ProcessInput_Options_Four},
    [MENUITEM_DIFFICULTY_LEVEL_CAP]             = {DrawChoices_Challenges_LevelCap,         ProcessInput_Options_Three},
    [MENUITEM_DIFFICULTY_ITEM_PLAYER]           = {DrawChoices_Challenges_ItemsPlayer,      ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_ITEM_TRAINER]          = {DrawChoices_Challenges_ItemsTrainer,     ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_NO_EVS]                = {DrawChoices_Challenges_NoEVs,            ProcessInput_Options_Two},
    [MENUITEM_DIFFICULTY_SCALING_IVS]           = {DrawChoices_Challenges_ScalingIVs,       ProcessInput_Options_Three},
    [MENUITEM_DIFFICULTY_SCALING_EVS]           = {DrawChoices_Challenges_ScalingEVs,       ProcessInput_Options_Four},
    [MENUITEM_DIFFICULTY_SAVE] = {NULL, NULL},
};

// Menu left side option names text
static const u8 sText_OptionMenuSave[] = _("SAVE");

static const u8 sText_TextSpeed[]    = _("TEXT SPEED");
static const u8 sText_Font[]         = _("FONT");
static const u8 sText_Frame[]        = _("FRAME");
static const u8 sText_UniqueColors[] = _("UNIQUE COLORS");
static const u8 sText_Animations[]   = _("ANIMATIONS");
static const u8 sText_BattleScene[]    = _("BATTLE SCENE");
static const u8 sText_BattleStyle[]    = _("BATTLE STYLE");
static const u8 sText_HpBar[]          = _("HP BAR");
static const u8 sText_ExpBar[]         = _("EXP BAR");
static const u8 sText_AnimSpeed[]      = _("ANIM. SPEED");
static const u8 sText_IvView[]         = _("IV VIEW");
static const u8 sText_Effectiveness[]  = _("EFFECTIVENESS");
static const u8 sText_ShowTypes[]      = _("SHOW TYPES");
static const u8 sText_Sound[]        = _("SPEAKERS");
static const u8 sText_MusicVolume[]  = _("MUSIC VOLUME");
static const u8 sText_SFXVolume[]    = _("SFX VOLUME");
static const u8 sText_CriesVolume[]  = _("CRIES VOLUME");
static const u8 sText_ButtonMode[]   = _("BUTTON MODE");
static const u8 sText_UnitSystem[]   = _("UNIT SYSTEM");
static const u8 sText_MatchCalls[]   = _("OVERWORLD CALLS");
static const u8 sText_LButtonMode[]  = _("L BUTTON");
static const u8 sText_RButtonMode[]  = _("R BUTTON");
static const u8 sText_DebugMode[]    = _("DEBUG MODE");
static const u8 sText_StartMenu[]    = _("START MENU");
static const u8 sText_OverworldSpeed[] = _("OW. SPEED");

static const u8 sText_Randomizer[] =                _("RANDOMIZER");
static const u8 sText_Starter[] =                   _("STARTER POKéMON");
static const u8 sText_WildPkmn[] =                  _("WILD POKéMON");
static const u8 sText_Trainer[] =                   _("TRAINER");
static const u8 sText_Static[] =                    _("STATIC POKéMON");
static const u8 sText_SimiliarEvolutionLevel[] =    _("BALANCE ON TIERS");
static const u8 sText_InlcudeLegendaries[]=         _("LEGENDARIES");
static const u8 sText_Type[] =                      _("TYPE");
static const u8 sText_Moves[] =                     _("MOVES");
static const u8 sText_Abilities[] =                 _("ABILTIES");
static const u8 sText_Evolutions[] =                _("EVOLUTIONS");
static const u8 sText_EvolutionMethods[] =          _("EVO LINES");
static const u8 sText_TypeEff[] =                   _("EFFECTIVENESS");
static const u8 sText_Items[] =                     _("ITEMS");
static const u8 sText_Chaos[] =                     _("CHAOS MODE");
static const u8 sText_Next[] =                      _("NEXT");
static const u8 sText_Nuzlocke[]        = _("NUZLOCKE");
static const u8 sText_SpeciesClause[]   = _("DUPES CLAUSE");
static const u8 sText_ShinyClause[]     = _("SHINY CLAUSE");
static const u8 sText_Nicknaming[]      = _("NICKNAMES");
static const u8 sText_Deletion[]        = _("FAINTING");
static const u8 sText_TrainerDifficulty[]   = _("TRAINERS");
static const u8 sText_LevelCap[]            = _("LEVEL CAP");
static const u8 sText_Items_Player[]        = _("PLAYER ITEMS");
static const u8 sText_Items_Trainer[]       = _("TRAINER ITEMS");
static const u8 sText_NoEVs[]               = _("PLAYER EVs");
static const u8 sText_ScalingIVs[]          = _("TRAINER IVs");
static const u8 sText_ScalingEVs[]          = _("TRAINER EVs");
static const u8 sText_Save[]                = _("SAVE");

// Descriptions
static const u8 sText_Empty[]                   = _("");
static const u8 sText_Desc_Options_Save[]               = _("Save your settings.");
static const u8 sText_Desc_Visuals_TextSpeed[]          = _("Choose one of the four text-display\nspeeds.");
static const u8 sText_Desc_Visuals_FontType[]           = _("Choose the font design.");
static const u8 sText_Desc_Visuals_FrameType[]          = _("Choose the frame surrounding the\nwindows.");
static const u8 sText_Desc_Visuals_UniqueColorsOn[]     = _("Enables unique colors for\nPuppets.");
static const u8 sText_Desc_Visuals_UniqueColorsOff[]    = _("Disables unique colors for\nPuppets.");
static const u8 sText_Desc_Visuals_MonAnimationsOn[]    = _("Animations will play for\nPuppets.");
static const u8 sText_Desc_Visuals_MonAnimationsOff[]   = _("Animations are disabled\nfor Puppets.");
static const u8 sText_Desc_Battle_BattleScene_On[]     = _("Show the Puppet battle animations.");
static const u8 sText_Desc_Battle_BattleScene_Off[]    = _("Skip the Puppet battle animations.");
static const u8 sText_Desc_Battle_BattleStyle_Shift[]  = _("Get the option to switch your\nPuppet after the enemies faints.");
static const u8 sText_Desc_Battle_BattleStyle_Set[]    = _("No free switch after fainting the\nenemy Puppets.");
static const u8 sText_Desc_Battle_HpBar[]              = _("Choose how fast the HP BAR will get\ndrained in battles.");
static const u8 sText_Desc_Battle_ExpBar[]             = _("Choose how fast the EXP BAR will get\nfilled in battles.");
static const u8 sText_Desc_Battle_AnimSpeed[]          = _("Choose the speed for battle\nanimations.");
static const u8 sText_Desc_IvViewOn[]           = _("IVs can be viewed in the\nsummary by pressing {A_BUTTON}.");
static const u8 sText_Desc_IvViewOff[]          = _("IVs cannot be viewed in the\nsummary.");
static const u8 sText_Desc_Battle_EffectivenessOn[]    = _("If foe was seen before, moves will\nshow effectiveness when selecting.");
static const u8 sText_Desc_Battle_EffectivenessOff[]   = _("Moves won't show effectivenes\nwhen selecting.");
static const u8 sText_Desc_ShowTypesOn[]        = _("If foe was caught, their types will\nshow when selecting a move.");
static const u8 sText_Desc_ShowTypesOff[]       = _("Puppet types will not be shown\nin battle.");
static const u8 sText_Desc_SoundMono[]          = _("Sound is the same in all speakers.\nRecommended for original hardware.");
static const u8 sText_Desc_SoundStereo[]        = _("Play the left and right audio channel\nseperatly. Great with headphones.");
static const u8 sText_Desc_MusicVolume[]        = _("Adjust the volume of background music\nhere.");
static const u8 sText_Desc_SFXVolume[]          = _("Adjust the volume of all sound effects\nand fanfares here.");
static const u8 sText_Desc_CriesVolume[]        = _("Adjust the volume of all Puppet cries\nhere");
static const u8 sText_Desc_LButtonMode_None[]   = _("The L button works as normal.");
static const u8 sText_Desc_LButtonMode_LA[]     = _("The L button acts as another A\nbutton for one-handed play.");
static const u8 sText_Desc_LButtonMode_AutoRun[] = _("Running can be toggled by\nthe L Button.");
static const u8 sText_Desc_LButtonMode_Register[] = _("An item registered can be used with\nthe L Button.");
static const u8 sText_Desc_RButtonMode_None[]   = _("The R button works as normal.");
static const u8 sText_Desc_RButtonMode_DexNav[] = _("When available, the R Button searches\nfor the registered DexNav species.");
static const u8 sText_Desc_RButtonMode_Bike[]   = _("Bike modes can be toggled by\nthe R button.");
static const u8 sText_Desc_RButtonMode_Register[] = _("An item registered can be used with\nthe R Button.");
static const u8 sText_Desc_UnitSystemImperial[] = _("Display Berry and Puppet weight\nand size in pounds and inches.");
static const u8 sText_Desc_UnitSystemMetric[]   = _("Display Berry and Puppet weight\nand size in kilograms and meters.");
static const u8 sText_Desc_OverworldCallsOn[]   = _("TRAINERs will be able to call you,\noffering rematches and info.");
static const u8 sText_Desc_OverworldCallsOff[]  = _("You will not receive calls.\nSpecial events will still occur.");
static const u8 sText_Desc_DebugModeOn[]        = _("WARNING! Please use at your own\nrisk.");
static const u8 sText_Desc_DebugModeOff[]       = _("Enabling this option will enable\ndebug mode options.");
static const u8 sText_Desc_OverworldSpeed[]          = _("Choose the speed for the\noverworld.");

static const u8 sText_Desc_Randomizer_Off[]                  = _("Game will not be randomized.");
static const u8 sText_Desc_Randomizer_On[]                   = _("Play the game randomized.\nSettings below!");
static const u8 sText_Desc_Random_Starter_Off[]              = _("Standard starter Puppets.");
static const u8 sText_Desc_Random_Starter_On[]               = _("Randomize starter Puppets.");
static const u8 sText_Desc_Random_Starter_Stage2[]           = _("Randomize starter Puppets with\n3-stage Puppets.");
static const u8 sText_Desc_Random_WildPokemon_Off[]          = _("Same wild encounter as in the\nbase game.");
static const u8 sText_Desc_Random_WildPokemon_On[]           = _("Randomize wild Puppets.");
static const u8 sText_Desc_Random_Trainer_Off[]              = _("Trainer will have their expected\nparty.");
static const u8 sText_Desc_Random_Trainer_On[]               = _("Randomize enemy trainer parties.");
static const u8 sText_Desc_Random_Static_Off[]               = _("Static encounter will be the same\nas in the base game.");
static const u8 sText_Desc_Random_Static_On[]                = _("Randomize static encounter Puppets.");
static const u8 sText_Desc_Random_BalanceTiers_Off[]         = _("Distribution of Puppets {COLOR 7}{COLOR 8}not balanced{COLOR 1}{COLOR 2}\naround their strength!");
static const u8 sText_Desc_Random_BalanceTiers_On[]          = _("{PKMN} replaced with similar tiered ones.\nCurrently based on evo stages.");
static const u8 sText_Desc_Random_IncludeLegendaries_Off[]   = _("Legendary Puppets will not be\nincluded and randomized.");
static const u8 sText_Desc_Random_IncludeLegendaries_On[]    = _("Include legendary Puppets in\nrandomization!");
static const u8 sText_Desc_Random_Types_Off[]                = _("Puppet types stay the same as in\nthe base game.");
static const u8 sText_Desc_Random_Types_On[]                 = _("Randomize all Puppet types.");
static const u8 sText_Desc_Random_Moves_Off[]                = _("Puppet moves stay the same as in\nthe base game.");
static const u8 sText_Desc_Random_Moves_On[]                 = _("Randomize all Puppet moves.");
static const u8 sText_Desc_Random_Abilities_Off[]            = _("Puppet abilities stay the same as in\nthe base game.");
static const u8 sText_Desc_Random_Abilities_On[]             = _("Randomize all Puppet abilities.");
static const u8 sText_Desc_Random_Evos_Off[]                 = _("Puppet evolutions stay the same as\nin the base game.");
static const u8 sText_Desc_Random_Evos_On[]                  = _("Randomize all Puppet evolutions.");
static const u8 sText_Desc_Random_Evo_Methods_Off[]          = _("The Puppets that can potentially\nevolve are unchanged.");
static const u8 sText_Desc_Random_Evo_Methods_On[]           = _("Randomize evolution lines. Allows\nnew evolution lines to occur!");
static const u8 sText_Desc_Random_Effectiveness_Off[]        = _("Type effectiveness chart will remain\nthe same as in the base game.");
static const u8 sText_Desc_Random_Effectiveness_On[]         = _("Randomize type effectiveness.");
static const u8 sText_Desc_Random_Items_Off[]                = _("All found or recieved items are the\nsame as in the base game.");
static const u8 sText_Desc_Random_Items_On[]                 = _("Randomize found, hidden and revieved\nitems. Key items are excluded!");
static const u8 sText_Desc_Random_ChaosMode_Off[]            = _("Chaos mode disabled.");
static const u8 sText_Desc_Random_ChaosMode_On[]             = _("Every above choosen option will be\nvery chaotic. {COLOR 7}{COLOR 8}NOT recommended!");
static const u8 sText_Desc_Random_Next[]                     = _("Continue to Nuzlocke options.");
static const u8 sText_Desc_Nuzlocke_Base[]               = _("Nuzlocke mode is disabled.");
static const u8 sText_Desc_Nuzlocke_Normal[]             = _("One catch per route! Fainted Puppets\ncan't be used anymore.");
static const u8 sText_Desc_Nuzlocke_Hard[]               = _("Same rules as NORMAL but also\n{COLOR 7}{COLOR 8}deletes SAVE on battle loss!");
static const u8 sText_Desc_Nuzlocke_SpeciesClause_Off[]  = _("The player always has to catch the\nfirst Puppet per route.");
static const u8 sText_Desc_Nuzlocke_SpeciesClause_On[]   = _("Only not prior caught Puppets count\nas first encounter. {COLOR 7}{COLOR 8}RECOMMENDED!");
static const u8 sText_Desc_Nuzlocke_ShinyClause_Off[]    = _("The player can only catch a shiny\nPuppet if it's the first encounter.");
static const u8 sText_Desc_Nuzlocke_ShinyClause_On[]     = _("The player can always catch shiny\nPuppets. {COLOR 7}{COLOR 8}RECOMMENDED!");
static const u8 sText_Desc_Nuzlocke_Nicknaming_Off[]     = _("Nicknames are optional.");
static const u8 sText_Desc_Nuzlocke_Nicknaming_On[]      = _("Forces the player to nickname every\nPuppet. {COLOR 7}{COLOR 8}RECOMMENDED!");
static const u8 sText_Desc_Nuzlocke_Deletion_Cemetery[]  = _("Fainted Puppets are send to the PC\nafter battle and can't be retrieved.");
static const u8 sText_Desc_Nuzlocke_Deletion_Deletion[]  = _("Fainted Puppets are {COLOR 7}{COLOR 8}released{COLOR 1}{COLOR 2} after\nbattle!");
static const u8 sText_Desc_Nuzlocke_Next[]               = _("Continue to difficulty options.");
static const u8 sText_Desc_Difficulty_LevelCap_Base[]            = _("No level cap. Overleveling possible.\n");
static const u8 sText_Desc_Difficulty_LevelCap_Normal[]          = _("Experience over the level cap\nis decreased significantly.");
static const u8 sText_Desc_Difficulty_LevelCap_Hard[]            = _("Experience over the level cap\nis cut off.");
static const u8 sText_Desc_Difficulty_TrainerDifficulty_Easy[]   = _("All trainers have easier teams\nincluding significant trainers.");
static const u8 sText_Desc_Difficulty_TrainerDifficulty_Normal[] = _("All trainers have their regular\nintended teams.");
static const u8 sText_Desc_Difficulty_TrainerDifficulty_Hard[]   = _("Trainers are smarter with better\nteams.");
static const u8 sText_Desc_Difficulty_TrainerDifficulty_Lunatic[] = _("Trainers have unfair gimmicks\nand teams.");
static const u8 sText_Desc_Difficulty_Items_Player_Yes[]         = _("The player can use battle items.");
static const u8 sText_Desc_Difficulty_Items_Player_No[]          = _("The player can {COLOR 7}{COLOR 8}NOT use battle items.\nHold items are allowed!");
static const u8 sText_Desc_Difficulty_Items_Trainer_Yes[]        = _("Enemy trainer can use battle items.");
static const u8 sText_Desc_Difficulty_Items_Trainer_No[]         = _("Enemy trainer can {COLOR 7}{COLOR 8}NOT use battle\nitems.");
static const u8 sText_Desc_Difficulty_NoEVs_Off[]                = _("The players' Puppets gain effort\nvalues as expected.");
static const u8 sText_Desc_Difficulty_NoEVs_On[]                 = _("The players' Puppets do {COLOR 7}{COLOR 8}NOT{COLOR 1}{COLOR 2} gain\nany effort values!");
static const u8 sText_Desc_Difficulty_ScalingIVs_Off[]           = _("The POKéMON of enemy Trainer have\nthe expected IVs.");
static const u8 sText_Desc_Difficulty_ScalingIVs_Scaling[]       = _("The IVs of Trainer POKéMON increase\nwith gym badges!");
static const u8 sText_Desc_Difficulty_ScalingIVs_Hard[]          = _("All Trainer POKéMON have perfect\nIVs!");
static const u8 sText_Desc_Difficulty_ScalingEVs_Off[]           = _("The POKéMON of enemy Trainer have\nthe expected EVs.");
static const u8 sText_Desc_Difficulty_ScalingEVs_Scaling[]       = _("The EVs of Trainer POKéMON increase\nwith gym badges!");
static const u8 sText_Desc_Difficulty_ScalingEVs_Hard[]          = _("All Trainer POKéMON have high EVs!");
static const u8 sText_Desc_Difficulty_ScalingEVs_Extreme[]       = _("All Trainer POKéMON have {COLOR 7}{COLOR 8}252 EVs!\nVery Hard!");
static const u8 sText_Desc_Challenges_Save[]    = _("Save choices and continue...");

static const u8 *const sOptionMenuItemsNamesVisuals[MENUITEM_VISUALS_COUNT] =
{
    [MENUITEM_VISUALS_TEXTSPEED]     = sText_TextSpeed,
    [MENUITEM_VISUALS_FONT]          = sText_Font,
    [MENUITEM_VISUALS_FRAMETYPE]     = sText_Frame,
    [MENUITEM_VISUALS_UNIQUE_COLORS] = sText_UniqueColors,
    [MENUITEM_VISUALS_ANIMATIONS]    = sText_Animations,
    [MENUITEM_VISUALS_CANCEL]        = sText_OptionMenuSave,
};

static const u8 *const sOptionMenuItemsNamesBattle[MENUITEM_BATTLE_COUNT] =
{
    [MENUITEM_BATTLE_BATTLESCENE]   = sText_BattleScene,
    [MENUITEM_BATTLE_BATTLESTYLE]   = sText_BattleStyle,
    [MENUITEM_BATTLE_HP_BAR]        = sText_HpBar,
    [MENUITEM_BATTLE_EXP_BAR]       = sText_ExpBar,
    [MENUITEM_BATTLE_ANIM_SPEED]    = sText_AnimSpeed,
    [MENUITEM_BATTLE_IV_VIEW]       = sText_IvView,
    [MENUITEM_BATTLE_EFFECTIVENESS] = sText_Effectiveness,
    [MENUITEM_BATTLE_SHOW_TYPES]    = sText_ShowTypes,
    [MENUITEM_BATTLE_CANCEL]        = sText_OptionMenuSave,
};

static const u8 *const sOptionMenuItemsNamesMisc[MENUITEM_MISC_COUNT] =
{
    [MENUITEM_MISC_SOUND]        = sText_Sound,
    [MENUITEM_MISC_MUSIC_VOLUME] = sText_MusicVolume,
    [MENUITEM_MISC_SFX_VOLUME]   = sText_SFXVolume,
    [MENUITEM_MISC_CRIES_VOLUME] = sText_CriesVolume,
    [MENUITEM_MISC_UNIT_SYSTEM]  = sText_UnitSystem,
    [MENUITEM_MISC_L_BUTTONMODE] = sText_LButtonMode,
    [MENUITEM_MISC_R_BUTTONMODE] = sText_RButtonMode,
    [MENUITEM_MISC_OVERWORLD_SPEED] = sText_OverworldSpeed,
    [MENUITEM_MISC_MATCHCALL]    = sText_MatchCalls,
    [MENUITEM_MISC_START_MENU]   = sText_StartMenu,
    [MENUITEM_MISC_DEBUG_MODE]   = sText_DebugMode,
    [MENUITEM_MISC_CANCEL]       = sText_OptionMenuSave,
};

static const u8 *const sOptionMenuItemsNamesRandom[MENUITEM_RANDOM_COUNT] =
{
    [MENUITEM_RANDOM_OFF_ON]                    = sText_Randomizer,
    [MENUITEM_RANDOM_STARTER]                   = sText_Starter,
    [MENUITEM_RANDOM_WILD_PKMN]                 = sText_WildPkmn,
    [MENUITEM_RANDOM_TRAINER]                   = sText_Trainer,
    [MENUITEM_RANDOM_STATIC]                    = sText_Static,
    [MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]   = sText_SimiliarEvolutionLevel,
    [MENUITEM_RANDOM_INCLUDE_LEGENDARIES]       = sText_InlcudeLegendaries,
    [MENUITEM_RANDOM_TYPE]                      = sText_Type,
    [MENUITEM_RANDOM_MOVES]                     = sText_Moves,
    [MENUITEM_RANDOM_ABILITIES]                 = sText_Abilities,
    [MENUITEM_RANDOM_EVOLUTIONS]                = sText_Evolutions,
    [MENUITEM_RANDOM_EVOLUTIONS_METHODS]        = sText_EvolutionMethods,
    [MENUITEM_RANDOM_TYPE_EFFEC]                = sText_TypeEff,
    [MENUITEM_RANDOM_ITEMS]                     = sText_Items,
    [MENUITEM_RANDOM_CHAOS]                     = sText_Chaos,
    [MENUITEM_RANDOM_NEXT]                      = sText_Next,
};

static const u8 *const sOptionMenuItemsNamesNuzlocke[MENUITEM_NUZLOCKE_COUNT] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]        = sText_Nuzlocke,
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]  = sText_SpeciesClause,
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]    = sText_ShinyClause,
    [MENUITEM_NUZLOCKE_DELETION]        = sText_Deletion,
    [MENUITEM_NUZLOCKE_NEXT]            = sText_Next,
};

static const u8 *const sOptionMenuItemsNamesDifficulty[MENUITEM_DIFFICULTY_COUNT] =
{
    [MENUITEM_DIFFICULTY_TRAINER_DIFFICULTY]    = sText_TrainerDifficulty,
    [MENUITEM_DIFFICULTY_LEVEL_CAP]             = sText_LevelCap,
    [MENUITEM_DIFFICULTY_ITEM_PLAYER]           = sText_Items_Player,
    [MENUITEM_DIFFICULTY_ITEM_TRAINER]          = sText_Items_Trainer,
    [MENUITEM_DIFFICULTY_NO_EVS]                = sText_NoEVs,
    [MENUITEM_DIFFICULTY_SCALING_IVS]           = sText_ScalingIVs,
    [MENUITEM_DIFFICULTY_SCALING_EVS]           = sText_ScalingEVs,
    [MENUITEM_DIFFICULTY_SAVE]                  = sText_Save,
};

static const u8 *const sOptionMenuItemDescriptionsVisuals[MENUITEM_VISUALS_COUNT][2] =
{
    [MENUITEM_VISUALS_TEXTSPEED]     = {sText_Desc_Visuals_TextSpeed,          sText_Empty},
    [MENUITEM_VISUALS_FONT]          = {sText_Desc_Visuals_FontType,           sText_Desc_Visuals_FontType},
    [MENUITEM_VISUALS_FRAMETYPE]     = {sText_Desc_Visuals_FrameType,          sText_Empty},
    [MENUITEM_VISUALS_UNIQUE_COLORS] = {sText_Desc_Visuals_UniqueColorsOn,     sText_Desc_Visuals_UniqueColorsOff},
    [MENUITEM_VISUALS_ANIMATIONS]    = {sText_Desc_Visuals_MonAnimationsOn,    sText_Desc_Visuals_MonAnimationsOff},
    [MENUITEM_VISUALS_CANCEL]        = {sText_Desc_Options_Save,               sText_Empty},
};

static const u8 *const sOptionMenuItemDescriptionsBattle[MENUITEM_BATTLE_COUNT][2] =
{
    [MENUITEM_BATTLE_BATTLESCENE]   = {sText_Desc_Battle_BattleScene_On,     sText_Desc_Battle_BattleScene_Off},
    [MENUITEM_BATTLE_BATTLESTYLE]   = {sText_Desc_Battle_BattleStyle_Shift,  sText_Desc_Battle_BattleStyle_Set},
    [MENUITEM_BATTLE_HP_BAR]        = {sText_Desc_Battle_HpBar,              sText_Empty},
    [MENUITEM_BATTLE_EXP_BAR]       = {sText_Desc_Battle_ExpBar,             sText_Empty},
    [MENUITEM_BATTLE_ANIM_SPEED]    = {sText_Desc_Battle_AnimSpeed,          sText_Empty},
    [MENUITEM_BATTLE_IV_VIEW]       = {sText_Desc_IvViewOn,           sText_Desc_IvViewOff},
    [MENUITEM_BATTLE_EFFECTIVENESS] = {sText_Desc_Battle_EffectivenessOn,    sText_Desc_Battle_EffectivenessOff},
    [MENUITEM_BATTLE_SHOW_TYPES]    = {sText_Desc_ShowTypesOn,        sText_Desc_ShowTypesOff},
    [MENUITEM_BATTLE_CANCEL]        = {sText_Desc_Options_Save,              sText_Empty},
};

static const u8 *const sOptionMenuItemDescriptionsMisc[MENUITEM_MISC_COUNT][4] =
{
    [MENUITEM_MISC_SOUND]        = {sText_Desc_SoundMono,            sText_Desc_SoundStereo,        sText_Empty,                    sText_Empty},
    [MENUITEM_MISC_MUSIC_VOLUME] = {sText_Desc_MusicVolume,          sText_Empty,                   sText_Empty,                    sText_Empty},
    [MENUITEM_MISC_SFX_VOLUME]   = {sText_Desc_SFXVolume,            sText_Empty,                   sText_Empty,                    sText_Empty},
    [MENUITEM_MISC_CRIES_VOLUME] = {sText_Desc_CriesVolume,          sText_Empty,                   sText_Empty,                    sText_Empty},
    [MENUITEM_MISC_UNIT_SYSTEM]  = {sText_Desc_UnitSystemImperial,   sText_Desc_UnitSystemMetric,   sText_Empty,                    sText_Empty},
    [MENUITEM_MISC_L_BUTTONMODE] = {sText_Desc_LButtonMode_None,     sText_Desc_LButtonMode_LA,     sText_Desc_LButtonMode_AutoRun, sText_Desc_LButtonMode_Register},
    [MENUITEM_MISC_R_BUTTONMODE] = {sText_Desc_RButtonMode_None,     sText_Desc_RButtonMode_DexNav, sText_Desc_RButtonMode_Bike,    sText_Desc_RButtonMode_Register},
    [MENUITEM_MISC_OVERWORLD_SPEED] = {sText_Desc_OverworldSpeed,     sText_Empty, sText_Empty,    sText_Empty},
    [MENUITEM_MISC_MATCHCALL]    = {sText_Desc_OverworldCallsOn,     sText_Desc_OverworldCallsOff,  sText_Empty,                    sText_Empty},
    [MENUITEM_MISC_START_MENU]   = {sText_Desc_DebugModeOn,          sText_Desc_DebugModeOff,       sText_Empty,                    sText_Empty},
    [MENUITEM_MISC_DEBUG_MODE]   = {sText_Desc_DebugModeOn,          sText_Desc_DebugModeOff,       sText_Empty,                    sText_Empty},
    [MENUITEM_MISC_CANCEL]       = {sText_Desc_Options_Save,         sText_Empty,                   sText_Empty,                    sText_Empty},
};

static const u8 *const sOptionMenuItemDescriptionsRandomizer[MENUITEM_RANDOM_COUNT][3] =
{
    [MENUITEM_RANDOM_OFF_ON]                    = {sText_Desc_Randomizer_Off,                    sText_Desc_Randomizer_On,                    sText_Empty},
    [MENUITEM_RANDOM_STARTER]                   = {sText_Desc_Random_Starter_Off,                sText_Desc_Random_Starter_On,                sText_Desc_Random_Starter_Stage2},
    [MENUITEM_RANDOM_WILD_PKMN]                 = {sText_Desc_Random_WildPokemon_Off,            sText_Desc_Random_WildPokemon_On,            sText_Empty},
    [MENUITEM_RANDOM_TRAINER]                   = {sText_Desc_Random_Trainer_Off,                sText_Desc_Random_Trainer_On,                sText_Empty},
    [MENUITEM_RANDOM_STATIC]                    = {sText_Desc_Random_Static_Off,                 sText_Desc_Random_Static_On,                 sText_Empty},
    [MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]   = {sText_Desc_Random_BalanceTiers_On,            sText_Desc_Random_BalanceTiers_Off,          sText_Empty},
    [MENUITEM_RANDOM_INCLUDE_LEGENDARIES]       = {sText_Desc_Random_IncludeLegendaries_Off,     sText_Desc_Random_IncludeLegendaries_On,     sText_Empty},
    [MENUITEM_RANDOM_TYPE]                      = {sText_Desc_Random_Types_Off,                  sText_Desc_Random_Types_On,                  sText_Empty},
    [MENUITEM_RANDOM_MOVES]                     = {sText_Desc_Random_Moves_Off,                  sText_Desc_Random_Moves_On,                  sText_Empty},
    [MENUITEM_RANDOM_ABILITIES]                 = {sText_Desc_Random_Abilities_Off,              sText_Desc_Random_Abilities_On,              sText_Empty},
    [MENUITEM_RANDOM_EVOLUTIONS]                = {sText_Desc_Random_Evos_Off,                   sText_Desc_Random_Evos_On,                   sText_Empty},
    [MENUITEM_RANDOM_EVOLUTIONS_METHODS]        = {sText_Desc_Random_Evo_Methods_Off,            sText_Desc_Random_Evo_Methods_On,            sText_Empty},
    [MENUITEM_RANDOM_TYPE_EFFEC]                = {sText_Desc_Random_Effectiveness_Off,          sText_Desc_Random_Effectiveness_On,          sText_Empty},
    [MENUITEM_RANDOM_ITEMS]                     = {sText_Desc_Random_Items_Off,                  sText_Desc_Random_Items_On,                  sText_Empty},
    [MENUITEM_RANDOM_CHAOS]                     = {sText_Desc_Random_ChaosMode_Off,              sText_Desc_Random_ChaosMode_On,              sText_Empty},
    [MENUITEM_RANDOM_NEXT]                      = {sText_Desc_Random_Next,                       sText_Empty,                                 sText_Empty},
};

static const u8 *const sOptionMenuItemDescriptionsNuzlocke[MENUITEM_NUZLOCKE_COUNT][3] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]            = {sText_Desc_Nuzlocke_Base,                 sText_Desc_Nuzlocke_Normal,                  sText_Desc_Nuzlocke_Hard},
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]      = {sText_Desc_Nuzlocke_SpeciesClause_On,     sText_Desc_Nuzlocke_SpeciesClause_Off,       sText_Empty},
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]        = {sText_Desc_Nuzlocke_ShinyClause_On,       sText_Desc_Nuzlocke_ShinyClause_Off,         sText_Empty},
    [MENUITEM_NUZLOCKE_DELETION]            = {sText_Desc_Nuzlocke_Deletion_Cemetery,    sText_Desc_Nuzlocke_Deletion_Deletion,       sText_Empty},
    [MENUITEM_NUZLOCKE_NEXT]                = {sText_Desc_Nuzlocke_Next,                 sText_Empty,                                 sText_Empty},
};

static const u8 *const sOptionMenuItemDescriptionsDifficulty[MENUITEM_DIFFICULTY_COUNT][4] =
{
    [MENUITEM_DIFFICULTY_TRAINER_DIFFICULTY]    = {sText_Desc_Difficulty_TrainerDifficulty_Easy, sText_Desc_Difficulty_TrainerDifficulty_Normal, sText_Desc_Difficulty_TrainerDifficulty_Hard, sText_Desc_Difficulty_TrainerDifficulty_Lunatic},
    [MENUITEM_DIFFICULTY_LEVEL_CAP]             = {sText_Desc_Difficulty_LevelCap_Base,          sText_Desc_Difficulty_LevelCap_Normal,          sText_Desc_Difficulty_LevelCap_Hard,          sText_Empty},
    [MENUITEM_DIFFICULTY_ITEM_PLAYER]           = {sText_Desc_Difficulty_Items_Player_Yes,       sText_Desc_Difficulty_Items_Player_No,          sText_Empty,                                  sText_Empty},
    [MENUITEM_DIFFICULTY_ITEM_TRAINER]          = {sText_Desc_Difficulty_Items_Trainer_Yes,      sText_Desc_Difficulty_Items_Trainer_No,         sText_Empty,                                  sText_Empty},
    [MENUITEM_DIFFICULTY_NO_EVS]                = {sText_Desc_Difficulty_NoEVs_Off,              sText_Desc_Difficulty_NoEVs_On,                 sText_Empty,                                  sText_Empty},
    [MENUITEM_DIFFICULTY_SCALING_IVS]           = {sText_Desc_Difficulty_ScalingIVs_Off,         sText_Desc_Difficulty_ScalingIVs_Scaling,       sText_Desc_Difficulty_ScalingIVs_Hard,        sText_Empty},
    [MENUITEM_DIFFICULTY_SCALING_EVS]           = {sText_Desc_Difficulty_ScalingEVs_Off,         sText_Desc_Difficulty_ScalingEVs_Scaling,       sText_Desc_Difficulty_ScalingEVs_Hard,        sText_Desc_Difficulty_ScalingEVs_Extreme},
    [MENUITEM_DIFFICULTY_SAVE]                  = {sText_Desc_Challenges_Save,                   sText_Empty,                                    sText_Empty,                                  sText_Empty},
};

// Disabled Descriptions
static const u8 sText_Desc_Disabled_Textspeed[]     = _("Text can only be in a set\nspeed.");
static const u8 sText_Desc_Disabled_FontType[]      = _("Fonts cannot be changed\ncurrectly.");
static const u8 sText_Desc_Disabled_FrameType[]     = _("Only this text frame can be\nused.");
static const u8 sText_Desc_Disabled_UniqueColors[]  = _("Unique colors cannot be enabled\ncurrently.");
static const u8 sText_Desc_Disabled_BattleHPBar[]     = _("HP bar speed can only be in a\nset speed.");
static const u8 sText_Desc_Disabled_BattleExpBar[]    = _("Exp bar speed can only be in a\nset speed.");
static const u8 sText_Desc_Disabled_BattleAnimSpeed[] = _("Animation speed can only be in\na set speed.");
static const u8 sText_Desc_Disabled_DebugMode[]    = _("Debug mode cannot be enabled\ncurrently.");

static const u8 sText_Description_Disabled_Random_SimiliarEvolutionLevel[]  = _("Only usable with random starter,\nTrainer, wild or static Puppets.");
static const u8 sText_Description_Disabled_Random_IncludeLegendaries[]      = _("Only usable with random starter,\nTrainer, wild or static Puppets.");
static const u8 sText_Description_Disabled_Random_Chaos_Mode[]              = _("Only usable if other random options\nare activated.");
static const u8 sText_Description_Disabled_Nuzlocke_Nuzlocke[]   = _("Only usable with Nuzlocke!");

static const u8 *const sOptionMenuItemDescriptionsDisabledVisuals[MENUITEM_VISUALS_COUNT] =
{
    [MENUITEM_VISUALS_TEXTSPEED]     = sText_Desc_Disabled_Textspeed,
    [MENUITEM_VISUALS_FONT]          = sText_Desc_Disabled_FontType,
    [MENUITEM_VISUALS_FRAMETYPE]     = sText_Desc_Disabled_FrameType,
    [MENUITEM_VISUALS_UNIQUE_COLORS] = sText_Desc_Disabled_UniqueColors,
    [MENUITEM_VISUALS_ANIMATIONS]    = sText_Empty,
    [MENUITEM_VISUALS_CANCEL]        = sText_Empty,
};

static const u8 *const sOptionMenuItemDescriptionsDisabledBattle[MENUITEM_BATTLE_COUNT] =
{
    [MENUITEM_BATTLE_BATTLESCENE]   = sText_Empty,
    [MENUITEM_BATTLE_BATTLESTYLE]   = sText_Empty,
    [MENUITEM_BATTLE_HP_BAR]        = sText_Desc_Disabled_BattleHPBar,
    [MENUITEM_BATTLE_EXP_BAR]       = sText_Desc_Disabled_BattleExpBar,
    [MENUITEM_BATTLE_ANIM_SPEED]    = sText_Desc_Disabled_BattleAnimSpeed,
    [MENUITEM_BATTLE_IV_VIEW]       = sText_Empty,
    [MENUITEM_BATTLE_EFFECTIVENESS] = sText_Empty,
    [MENUITEM_BATTLE_SHOW_TYPES]    = sText_Empty,
    [MENUITEM_BATTLE_CANCEL]        = sText_Empty,
};

static const u8 *const sOptionMenuItemDescriptionsDisabledMisc[MENUITEM_MISC_COUNT] =
{
    [MENUITEM_MISC_SOUND]        = sText_Empty,
    [MENUITEM_MISC_MUSIC_VOLUME] = sText_Empty,
    [MENUITEM_MISC_SFX_VOLUME]   = sText_Empty,
    [MENUITEM_MISC_CRIES_VOLUME] = sText_Empty,
    [MENUITEM_MISC_UNIT_SYSTEM]  = sText_Empty,
    [MENUITEM_MISC_L_BUTTONMODE] = sText_Empty,
    [MENUITEM_MISC_R_BUTTONMODE] = sText_Empty,
    [MENUITEM_MISC_OVERWORLD_SPEED]    = sText_Empty,
    [MENUITEM_MISC_MATCHCALL]    = sText_Empty,
    [MENUITEM_MISC_START_MENU]   = sText_Empty,
    [MENUITEM_MISC_DEBUG_MODE]   = sText_Desc_Disabled_DebugMode,
    [MENUITEM_MISC_CANCEL]       = sText_Empty,
};

static const u8 *const sOptionMenuItemDescriptionsDisabledRandomizer[MENUITEM_RANDOM_COUNT] =
{
    [MENUITEM_RANDOM_OFF_ON]                    = sText_Empty,
    [MENUITEM_RANDOM_STARTER]                   = sText_Empty,
    [MENUITEM_RANDOM_WILD_PKMN]                 = sText_Empty,
    [MENUITEM_RANDOM_TRAINER]                   = sText_Empty,
    [MENUITEM_RANDOM_STATIC]                    = sText_Empty,
    [MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]   = sText_Description_Disabled_Random_SimiliarEvolutionLevel,
    [MENUITEM_RANDOM_INCLUDE_LEGENDARIES]       = sText_Description_Disabled_Random_IncludeLegendaries,
    [MENUITEM_RANDOM_TYPE]                      = sText_Empty,
    [MENUITEM_RANDOM_MOVES]                     = sText_Empty,
    [MENUITEM_RANDOM_ABILITIES]                 = sText_Empty,
    [MENUITEM_RANDOM_EVOLUTIONS]                = sText_Empty,
    [MENUITEM_RANDOM_EVOLUTIONS_METHODS]        = sText_Empty,
    [MENUITEM_RANDOM_TYPE_EFFEC]                = sText_Empty,
    [MENUITEM_RANDOM_ITEMS]                     = sText_Empty,
    [MENUITEM_RANDOM_CHAOS]                     = sText_Description_Disabled_Random_Chaos_Mode,
    [MENUITEM_RANDOM_NEXT]                      = sText_Empty,
};

static const u8 *const sOptionMenuItemDescriptionsDisabledNuzlocke[MENUITEM_NUZLOCKE_COUNT] =
{
    [MENUITEM_NUZLOCKE_NUZLOCKE]            = sText_Empty,
    [MENUITEM_NUZLOCKE_SPECIES_CLAUSE]      = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_SHINY_CLAUSE]        = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_DELETION]            = sText_Description_Disabled_Nuzlocke_Nuzlocke,
    [MENUITEM_NUZLOCKE_NEXT]                = sText_Empty,
};

static const u8 *const sOptionMenuItemDescriptionsDisabledDifficulty[MENUITEM_DIFFICULTY_COUNT] =
{
    [MENUITEM_DIFFICULTY_TRAINER_DIFFICULTY]    = sText_Empty,
    [MENUITEM_DIFFICULTY_LEVEL_CAP]             = sText_Empty,
    [MENUITEM_DIFFICULTY_ITEM_PLAYER]           = sText_Empty,
    [MENUITEM_DIFFICULTY_ITEM_TRAINER]          = sText_Empty,
    [MENUITEM_DIFFICULTY_NO_EVS]                = sText_Empty,
    [MENUITEM_DIFFICULTY_SCALING_IVS]           = sText_Empty,
    [MENUITEM_DIFFICULTY_SCALING_EVS]           = sText_Empty,
    [MENUITEM_DIFFICULTY_SAVE]                  = sText_Empty,
};

static const u8 *OptionTextRight(u8 menuItem)
{
    switch (sOptions->optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        switch (sOptions->submenu)
        {
        case OPTIONSPLUS_MENU_VISUALS:
            return sOptionMenuItemsNamesVisuals[menuItem];
        case OPTIONSPLUS_MENU_BATTLE:
            return sOptionMenuItemsNamesBattle[menuItem];
        case OPTIONSPLUS_MENU_MISC:
            return sOptionMenuItemsNamesMisc[menuItem];
        }
        break;
    case MENUMODE_CHALLENGES:
        switch (sOptions->submenu)
        {
        case CHALLENGES_MENU_RANDOMIZER:
            return sOptionMenuItemsNamesRandom[menuItem];
        case CHALLENGES_MENU_NUZLOCKE:
            return sOptionMenuItemsNamesNuzlocke[menuItem];
        case CHALLENGES_MENU_DIFFICULTY:
            return sOptionMenuItemsNamesDifficulty[menuItem];
        }
        break;
    }
    return sText_Empty; // failsafe
}

// Menu left side text conditions
static bool8 CheckConditions(int selection)
{
    switch (sOptions->optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        switch (sOptions->submenu)
        {
        case OPTIONSPLUS_MENU_VISUALS:
            switch(selection)
            {
            default:
                return TRUE;
            }
        case OPTIONSPLUS_MENU_BATTLE:
            switch(selection)
            {
            default:
                return TRUE;
            }
        case OPTIONSPLUS_MENU_MISC:
            switch(selection)
            {
            default:
                return TRUE;
            }
        }
        break;
    case MENUMODE_CHALLENGES:
        switch (sOptions->submenu)
        {
        case CHALLENGES_MENU_RANDOMIZER:
            switch(selection)
            {
            case MENUITEM_RANDOM_OFF_ON:
            case MENUITEM_RANDOM_NEXT:
                return TRUE;
            case MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL:
                return sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_OFF_ON]
                    && (sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_WILD_PKMN]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STARTER]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TRAINER]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STATIC])
                    && !sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_CHAOS];
            case MENUITEM_RANDOM_INCLUDE_LEGENDARIES:
                return sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_OFF_ON]
                    && (sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_WILD_PKMN]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STARTER]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TRAINER]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STATIC]);
            case MENUITEM_RANDOM_CHAOS:
                return sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_OFF_ON]
                    && (sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_WILD_PKMN]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STARTER]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TRAINER]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STATIC]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TYPE]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_MOVES]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_ABILITIES]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_EVOLUTIONS]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_EVOLUTIONS_METHODS]
                    || sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TYPE_EFFEC]);
            default:
                return sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_OFF_ON];
            }
        case CHALLENGES_MENU_NUZLOCKE:
            switch(selection)
            {
            case MENUITEM_NUZLOCKE_SPECIES_CLAUSE:
            case MENUITEM_NUZLOCKE_SHINY_CLAUSE:
            case MENUITEM_NUZLOCKE_DELETION:
                return sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE];
            default:
                return TRUE;
            }
        case CHALLENGES_MENU_DIFFICULTY:
            switch(selection)
            {
            default:
                return TRUE;
            }
        }
        break;
    }
    return FALSE; // failsafe
}

static const u8 *const OptionTextDescription(void)
{
    u8 menuItem = sOptions->menuCursor[sOptions->submenu];
    u8 selection;

    switch (sOptions->optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        switch (sOptions->submenu)
        {
        case OPTIONSPLUS_MENU_VISUALS:
            if (!CheckConditions(menuItem))
                return sOptionMenuItemDescriptionsDisabledVisuals[menuItem];
            selection = sOptions->selection.optionsPlus.visuals[menuItem];
            if (menuItem == MENUITEM_VISUALS_TEXTSPEED || menuItem == MENUITEM_VISUALS_FRAMETYPE)
                selection = 0;
            return sOptionMenuItemDescriptionsVisuals[menuItem][selection];
        case OPTIONSPLUS_MENU_BATTLE:
            if (!CheckConditions(menuItem))
                return sOptionMenuItemDescriptionsDisabledBattle[menuItem];
            selection = sOptions->selection.optionsPlus.battle[menuItem];
            if (menuItem == MENUITEM_BATTLE_HP_BAR || menuItem == MENUITEM_BATTLE_EXP_BAR || menuItem == MENUITEM_BATTLE_ANIM_SPEED)
                selection = 0;
            return sOptionMenuItemDescriptionsBattle[menuItem][selection];
        case OPTIONSPLUS_MENU_MISC:
            if (!CheckConditions(menuItem))
                return sOptionMenuItemDescriptionsDisabledMisc[menuItem];
            selection = sOptions->selection.optionsPlus.misc[menuItem];
            if (menuItem == MENUITEM_MISC_MUSIC_VOLUME || menuItem == MENUITEM_MISC_SFX_VOLUME || menuItem == MENUITEM_MISC_CRIES_VOLUME || menuItem == MENUITEM_MISC_OVERWORLD_SPEED)
                selection = 0;
            return sOptionMenuItemDescriptionsMisc[menuItem][selection];
        }
        break;
    case MENUMODE_CHALLENGES:
        switch (sOptions->submenu)
        {
        case CHALLENGES_MENU_RANDOMIZER:
            if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledRandomizer[menuItem] != sText_Empty)
                return sOptionMenuItemDescriptionsDisabledRandomizer[menuItem];
            selection = sOptions->selection.challenges.randomizer[menuItem];  
            return sOptionMenuItemDescriptionsRandomizer[menuItem][selection];
        case CHALLENGES_MENU_NUZLOCKE:
            if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledNuzlocke[menuItem] != sText_Empty)
                return sOptionMenuItemDescriptionsDisabledNuzlocke[menuItem];
            selection = sOptions->selection.challenges.nuzlocke[menuItem];
            return sOptionMenuItemDescriptionsNuzlocke[menuItem][selection];
        case CHALLENGES_MENU_DIFFICULTY:
            if (!CheckConditions(menuItem) && sOptionMenuItemDescriptionsDisabledDifficulty[menuItem] != sText_Empty)
                return sOptionMenuItemDescriptionsDisabledDifficulty[menuItem];
            selection = sOptions->selection.challenges.difficulty[menuItem];
            return sOptionMenuItemDescriptionsDifficulty[menuItem][selection];
        }
        break;
    }
    return sText_Empty; // failsafe
}

static u8 MenuItemCount(void)
{
    switch (sOptions->optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        switch (sOptions->submenu)
        {
        case OPTIONSPLUS_MENU_VISUALS:
            return MENUITEM_VISUALS_COUNT;
        case OPTIONSPLUS_MENU_BATTLE:
            return MENUITEM_BATTLE_COUNT;
        case OPTIONSPLUS_MENU_MISC:
            return MENUITEM_MISC_COUNT;
        }
        break;
    case MENUMODE_CHALLENGES:
        switch (sOptions->submenu)
        {
        case CHALLENGES_MENU_RANDOMIZER:
            return MENUITEM_RANDOM_COUNT;
        case CHALLENGES_MENU_NUZLOCKE:
            return MENUITEM_NUZLOCKE_COUNT;
        case CHALLENGES_MENU_DIFFICULTY:
            return MENUITEM_DIFFICULTY_COUNT;
        }
        break;
    }
    return 0; // failsafe
}

static u8 MenuItemCancel(void)
{
    switch (sOptions->optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        switch (sOptions->submenu)
        {
        case OPTIONSPLUS_MENU_VISUALS:
            return MENUITEM_VISUALS_CANCEL;
        case OPTIONSPLUS_MENU_BATTLE:
            return MENUITEM_BATTLE_CANCEL;
        case OPTIONSPLUS_MENU_MISC:
            return MENUITEM_MISC_CANCEL;
        }
        break;
    case MENUMODE_CHALLENGES:
        switch (sOptions->submenu)
        {
        case CHALLENGES_MENU_RANDOMIZER:
            return MENUITEM_RANDOM_NEXT;
        case CHALLENGES_MENU_NUZLOCKE:
            return MENUITEM_NUZLOCKE_NEXT;
        case CHALLENGES_MENU_DIFFICULTY:
            return MENUITEM_DIFFICULTY_SAVE;
        }
        break;
    }
    return 0; // failsafe
}

// Main code
static void MainCB2(void)
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
    ChangeBgX(3, 96, BG_COORD_ADD);
    ChangeBgY(3, 96, BG_COORD_ADD);
}

static const u8 sText_TopBar_Visuals[]       = _("VISUALS");
static const u8 sText_TopBar_Custom[]        = _("BATTLE");
static const u8 sText_TopBar_Misc[]          = _("MISC");
static const u8 sText_TopBar_Visuals_Left[]  = _("{L_BUTTON}MISC");
static const u8 sText_TopBar_Visuals_Right[] = _("{R_BUTTON}BATTLE");
static const u8 sText_TopBar_Battle_Left[]   = _("{L_BUTTON}VISUALS");
static const u8 sText_TopBar_Battle_Right[]  = _("{R_BUTTON}MISC");
static const u8 sText_TopBar_Misc_Left[]     = _("{L_BUTTON}BATTLE");
static const u8 sText_TopBar_Misc_Right[]    = _("{R_BUTTON}VISUALS");

static const u8 sText_TopBar_Randomizer_Left[]  = _("{L_BUTTON}RANDOMIZER");
static const u8 sText_TopBar_Nuzlocke_Left[]    = _("{L_BUTTON}NUZLOCKE");
static const u8 sText_TopBar_Nuzlocke_Right[]   = _("{R_BUTTON}NUZLOCKE");
static const u8 sText_TopBar_Difficulty_Right[] = _("{R_BUTTON}DIFFICULTY");
static const u8 sText_TopBar_Randomizer[]       = _("RANDOMIZER");
static const u8 sText_TopBar_Nuzlocke[]         = _("NUZLOCKE");
static const u8 sText_TopBar_Difficulty[]       = _("DIFFICULTY");

static void DrawTopBarText(void)
{
    const u8 color[3] = { TEXT_COLOR_TRANSPARENT, TEXT_COLOR_OPTIONS_WHITE, TEXT_COLOR_OPTIONS_GRAY_BG };

    int width = 0;
    int right = 240 - GetStringWidth(FONT_SMALL, sText_TopBar_Randomizer_Left, 0) - 5;

    FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(0));
    switch (sOptions->optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        switch (sOptions->submenu)
        {
        case OPTIONSPLUS_MENU_VISUALS:
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 105, 1, color, 0, sText_TopBar_Visuals);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 2, 1, color, 0, sText_TopBar_Visuals_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 187, 1, color, 0, sText_TopBar_Visuals_Right);
            break;
        case OPTIONSPLUS_MENU_BATTLE:
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 105, 1, color, 0, sText_TopBar_Custom);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 2, 1, color, 0, sText_TopBar_Battle_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 187, 1, color, 0, sText_TopBar_Battle_Right);
            break;
        case OPTIONSPLUS_MENU_MISC:
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 105, 1, color, 0, sText_TopBar_Misc);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 2, 1, color, 0, sText_TopBar_Misc_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 187, 1, color, 0, sText_TopBar_Misc_Right);
            break;
        }
        break;
    case MENUMODE_CHALLENGES:
        switch (sOptions->submenu)
        {
        case CHALLENGES_MENU_RANDOMIZER:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Randomizer, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120 - width, 1, color, 0, sText_TopBar_Randomizer);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, right, 1, color, 0, sText_TopBar_Nuzlocke_Right);
            break;
        case CHALLENGES_MENU_NUZLOCKE:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Nuzlocke, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 5, 1, color, 0, sText_TopBar_Randomizer_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120 - width, 1, color, 0, sText_TopBar_Nuzlocke);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, right, 1, color, 0, sText_TopBar_Difficulty_Right);
            break;
        case CHALLENGES_MENU_DIFFICULTY:
            width = GetStringWidth(FONT_SMALL, sText_TopBar_Difficulty, 0) / 2;
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 5, 1, color, 0, sText_TopBar_Nuzlocke_Left);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 120 - width, 1, color, 0, sText_TopBar_Difficulty);
            break;
        }
        break;
    }
    PutWindowTilemap(WIN_TOPBAR);
    CopyWindowToVram(WIN_TOPBAR, COPYWIN_FULL);
}

static void DrawOptionMenuTexts(void) //left side text
{
    u8 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(0));
    for (i = 0; i < MenuItemCount(); i++)
        DrawLeftSideOptionText(i, (i * Y_DIFF) + 1);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void DrawDescriptionText(void)
{
    u8 color_gray[3];
    color_gray[0] = TEXT_COLOR_TRANSPARENT;
    color_gray[1] = TEXT_COLOR_OPTIONS_WHITE;
    color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
        
    FillWindowPixelBuffer(WIN_DESCRIPTION, PIXEL_FILL(1));
    AddTextPrinterParameterized4(WIN_DESCRIPTION, FONT_NORMAL, 8, 1, 0, 0, color_gray, TEXT_SKIP_DRAW, OptionTextDescription());
    CopyWindowToVram(WIN_DESCRIPTION, COPYWIN_FULL);
}

static void DrawLeftSideOptionText(int selection, int y)
{
    u8 color_yellow[3];
    u8 color_gray[3];

    color_yellow[0] = TEXT_COLOR_TRANSPARENT;
    color_yellow[1] = TEXT_COLOR_OPTIONS_WHITE;
    color_yellow[2] = TEXT_COLOR_OPTIONS_GRAY_BG;
    color_gray[0] = TEXT_COLOR_TRANSPARENT;
    color_gray[1] = TEXT_COLOR_OPTIONS_GRAY_BG;
    color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;

    if (CheckConditions(selection))
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y, 0, 0, color_yellow, TEXT_SKIP_DRAW, OptionTextRight(selection));
    else
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, 8, y, 0, 0, color_gray, TEXT_SKIP_DRAW, OptionTextRight(selection));
}

static void DrawRightSideChoiceText(const u8 *text, int x, int y, bool8 choosen, bool8 active)
{
    u8 color_red[3];
    u8 color_gray[3];

    if (active)
    {
        color_red[0] = TEXT_COLOR_TRANSPARENT;
        color_red[1] = TEXT_COLOR_OPTIONS_ORANGE_FG;
        color_red[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
        color_gray[0] = TEXT_COLOR_TRANSPARENT;
        color_gray[1] = TEXT_COLOR_OPTIONS_WHITE;
        color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
    }
    else
    {
        color_red[0] = TEXT_COLOR_TRANSPARENT;
        color_red[1] = TEXT_COLOR_OPTIONS_GRAY_BG;
        color_red[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
        color_gray[0] = TEXT_COLOR_TRANSPARENT;
        color_gray[1] = TEXT_COLOR_OPTIONS_GRAY_BG;
        color_gray[2] = TEXT_COLOR_OPTIONS_GRAY_SHADOW;
    }


    if (choosen)
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, x, y, 0, 0, color_red, TEXT_SKIP_DRAW, text);
    else
        AddTextPrinterParameterized4(WIN_OPTIONS, FONT_NORMAL, x, y, 0, 0, color_gray, TEXT_SKIP_DRAW, text);
}

static void DrawChoices(u32 id, int y) //right side draw function
{
    switch (sOptions->optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        switch (sOptions->submenu)
        {
        case OPTIONSPLUS_MENU_VISUALS:
            if (sItemFunctionsVisuals[id].drawChoices != NULL)
                sItemFunctionsVisuals[id].drawChoices(sOptions->selection.optionsPlus.visuals[id], y);
            break;
        case OPTIONSPLUS_MENU_BATTLE:
            if (sItemFunctionsBattle[id].drawChoices != NULL)
                sItemFunctionsBattle[id].drawChoices(sOptions->selection.optionsPlus.battle[id], y);
            break;
        case OPTIONSPLUS_MENU_MISC:
            if (sItemFunctionsMisc[id].drawChoices != NULL)
                sItemFunctionsMisc[id].drawChoices(sOptions->selection.optionsPlus.misc[id], y);
            break;
        }
        break;
    case MENUMODE_CHALLENGES:
        switch (sOptions->submenu)
        {
        case CHALLENGES_MENU_RANDOMIZER:
            if (sItemFunctionsRandom[id].drawChoices != NULL)
                sItemFunctionsRandom[id].drawChoices(sOptions->selection.challenges.randomizer[id], y);
            break;
        case CHALLENGES_MENU_NUZLOCKE:
            if (sItemFunctionsNuzlocke[id].drawChoices != NULL)
                sItemFunctionsNuzlocke[id].drawChoices(sOptions->selection.challenges.nuzlocke[id], y);
            break;
        case CHALLENGES_MENU_DIFFICULTY:
            if (sItemFunctionsDifficulty[id].drawChoices != NULL)
                sItemFunctionsDifficulty[id].drawChoices(sOptions->selection.challenges.difficulty[id], y);
            break;
        }
        break;
    }
}

static void HighlightOptionMenuItem(void)
{
    int cursor = sOptions->visibleCursor[sOptions->submenu];

    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(8, 232));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(cursor * Y_DIFF + 24, cursor * Y_DIFF + 40));
}

static bool8 OptionsMenu_LoadGraphics(void) // Load all the tilesets, tilemaps, spritesheets, and palettes
{
    switch (sOptions->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(2, sOptionsPlusTiles, 0, 0, 0);
        sOptions->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            DecompressDataWithHeaderWram(sOptionsPlusTilemap, sBg2TilemapBuffer);
            sOptions->gfxLoadState++;
        }
        break;
    case 2:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(3, sScrollBgTiles, 0, 0, 0);
        sOptions->gfxLoadState++;
        break;
    case 3:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            DecompressDataWithHeaderWram(sScrollBgTilemap, sBg3TilemapBuffer);
            sOptions->gfxLoadState++;
        }
        break;
    case 4:
        LoadPalette(sOptionsPlusPalette, 64, 32);
        LoadPalette(sScrollBgPalette, 32, 32);
        sOptions->gfxLoadState++;
        break;
    default:
        sOptions->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void OptionsMenu_LoadOptions(u32 optionMode)
{
    switch (optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_TEXTSPEED]     = gSaveBlock2Ptr->optionsTextSpeed;
        sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_FRAMETYPE]     = gSaveBlock2Ptr->optionsWindowFrameType;
        sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_FONT]          = gSaveBlock2Ptr->optionsCurrentFont;
        sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_UNIQUE_COLORS] = gSaveBlock2Ptr->optionsUniqueColors;
        sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_ANIMATIONS]    = gSaveBlock2Ptr->optionsMonAnimations;

        sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_BATTLESCENE]   = gSaveBlock2Ptr->optionsBattleSceneOff;
        sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_BATTLESTYLE]   = gSaveBlock2Ptr->optionsBattleStyle;
        sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_HP_BAR]        = gSaveBlock2Ptr->optionsHpBarSpeed;
        sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_EXP_BAR]       = gSaveBlock2Ptr->optionsExpBarSpeed;
        sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_ANIM_SPEED]    = gSaveBlock2Ptr->optionsAnimSpeed;
        sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_IV_VIEW]       = gSaveBlock2Ptr->optionsSummaryIvView;
        sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_EFFECTIVENESS] = gSaveBlock2Ptr->optionsEffectiveness;
        sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_SHOW_TYPES]    = gSaveBlock2Ptr->optionsShowTypes;

        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_SOUND]        = gSaveBlock2Ptr->optionsSound;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_MUSIC_VOLUME] = gSaveBlock2Ptr->optionsVolumeBGM;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_SFX_VOLUME]   = gSaveBlock2Ptr->optionsVolumeSFX;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_CRIES_VOLUME] = gSaveBlock2Ptr->optionsVolumeCries;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_UNIT_SYSTEM]  = gSaveBlock2Ptr->optionsUnitSystem;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_L_BUTTONMODE] = gSaveBlock2Ptr->optionsLButtonMode;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_R_BUTTONMODE] = gSaveBlock2Ptr->optionsRButtonMode;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_OVERWORLD_SPEED] = gSaveBlock2Ptr->optionsOwSpeed;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_MATCHCALL]    = gSaveBlock2Ptr->optionsDisableMatchCall;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_DEBUG_MODE]   = gSaveBlock2Ptr->optionsDebugMode;
        sOptions->selection.optionsPlus.misc[MENUITEM_MISC_START_MENU]   = gSaveBlock2Ptr->optionsFullStartMenu;

        sOptions->submenu = 0;
        break;
    case MENUMODE_CHALLENGES:
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_OFF_ON]                     = FALSE;
        if (gSaveBlock2Ptr->tx_Random_Starter_Stage2)
            sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STARTER] = 2;
        else if (gSaveBlock2Ptr->tx_Random_Starter)
            sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STARTER] = 1;
        else
            sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STARTER] = 0;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_WILD_PKMN]                  = gSaveBlock2Ptr->tx_Random_WildPokemon;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TRAINER]                    = gSaveBlock2Ptr->tx_Random_Trainer;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STATIC]                     = gSaveBlock2Ptr->tx_Random_Static;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL]    = !gSaveBlock2Ptr->tx_Random_Similar;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_INCLUDE_LEGENDARIES]        = gSaveBlock2Ptr->tx_Random_IncludeLegendaries;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TYPE]                       = gSaveBlock2Ptr->tx_Random_Type;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_MOVES]                      = gSaveBlock2Ptr->tx_Random_Moves;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_ABILITIES]                  = gSaveBlock2Ptr->tx_Random_Abilities;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_EVOLUTIONS]                 = gSaveBlock2Ptr->tx_Random_Evolutions;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_EVOLUTIONS_METHODS]         = gSaveBlock2Ptr->tx_Random_EvolutionMethods;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TYPE_EFFEC]                 = gSaveBlock2Ptr->tx_Random_TypeEffectiveness;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_ITEMS]                      = gSaveBlock2Ptr->tx_Random_Items;
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_CHAOS]                      = gSaveBlock2Ptr->tx_Random_Chaos;

        if (gSaveBlock2Ptr->tx_Challenges_Nuzlocke && gSaveBlock2Ptr->tx_Challenges_NuzlockeHardcore)
            sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 2;
        else if (gSaveBlock2Ptr->tx_Challenges_Nuzlocke)
            sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 1;
        else
            sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE] = 0;
        sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE]    = !gSaveBlock2Ptr->tx_Nuzlocke_SpeciesClause;
        sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE]      = !gSaveBlock2Ptr->tx_Nuzlocke_ShinyClause;
        sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_DELETION]          = gSaveBlock2Ptr->tx_Nuzlocke_Deletion;

        sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_TRAINER_DIFFICULTY] = gSaveBlock2Ptr->tx_Challenges_TrainerDifficulty;
        sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_LEVEL_CAP]      = gSaveBlock2Ptr->tx_Challenges_LevelCap;
        sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_ITEM_PLAYER]    = gSaveBlock2Ptr->tx_Challenges_NoItemPlayer;
        sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_ITEM_TRAINER]   = gSaveBlock2Ptr->tx_Challenges_NoItemTrainer;
        sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_NO_EVS]         = gSaveBlock2Ptr->tx_Challenges_NoEVs;
        sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_SCALING_IVS]    = gSaveBlock2Ptr->tx_Challenges_TrainerScalingIVs;
        sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_SCALING_EVS]    = gSaveBlock2Ptr->tx_Challenges_TrainerScalingEVs;

        sOptions->submenu = 0;
        break;
    }
}

static void CB2_InitOptionsMenu(u32 optionMode)
{
    u32 i;
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        ResetVramOamAndBgCntRegs();
        sOptions = AllocZeroed(sizeof(*sOptions));
        FreeAllSpritePalettes();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        ResetBgsAndClearDma3BusyFlags(0);
        ResetBgPositions();
        
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG2);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        
        ResetAllBgsCoordinates();
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, NELEMS(sOptionMenuBgTemplates));
        InitWindows(sOptionMenuWinTemplates);

        sBg2TilemapBuffer = Alloc(0x800);
        memset(sBg2TilemapBuffer, 0, 0x800);
        SetBgTilemapBuffer(2, sBg2TilemapBuffer);
        ScheduleBgCopyTilemapToVram(2);

        sBg3TilemapBuffer = Alloc(0x800);
        memset(sBg3TilemapBuffer, 0, 0x800);
        SetBgTilemapBuffer(3, sBg3TilemapBuffer);
        ScheduleBgCopyTilemapToVram(3);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        gMain.state++;
        sOptions->gfxLoadState = 0;
        sOptions->optionMode = optionMode;
        break;
    case 3:
        if (OptionsMenu_LoadGraphics() == TRUE)
        {
            gMain.state++;
            LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        }
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, 0, sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, 0x70, 0x20);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, 16, sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        OptionsMenu_LoadOptions(optionMode);

        gMain.state++;
        break;
    case 7:
        PutWindowTilemap(WIN_TOPBAR);
        DrawTopBarText();
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(WIN_DESCRIPTION);
        DrawDescriptionText();
        gMain.state++;
        break;
    case 9:
        PutWindowTilemap(WIN_OPTIONS);
        DrawOptionMenuTexts();
        gMain.state++;
        break;
    case 10:
        CreateTask(Task_OptionMenuFadeIn, 0);
        
        sOptions->arrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 240 / 2, 20, 110, MenuItemCount() - 1, 110, 110, 0);

        for (i = 0; i < min(OPTIONS_ON_SCREEN, MenuItemCount()); i++)
            DrawChoices(i, i * Y_DIFF);

        HighlightOptionMenuItem();

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    case 11:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 12:
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

void CB2_InitOptionPlusMenu(void)
{
    CB2_InitOptionsMenu(MENUMODE_OPTIONSPLUS);
    return;
}

void CB2_InitChallengesMenu(void)
{
    CB2_InitOptionsMenu(MENUMODE_CHALLENGES);
    return;
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_OptionMenuProcessInput;
        SetGpuReg(REG_OFFSET_WIN0H, 0); // Idk man Im just trying to stop this stupid graphical bug from happening dont judge me
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG0 | BLDCNT_TGT1_BG2);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        ShowBg(3);
        HighlightOptionMenuItem();
        return;
    }
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());
    if (JOY_NEW(A_BUTTON))
    {
        if (sOptions->menuCursor[sOptions->submenu] == MenuItemCancel())
        {
            switch (sOptions->optionMode)
            {
            case MENUMODE_OPTIONSPLUS:
                gTasks[taskId].func = Task_OptionMenuSave;
                break;
            case MENUMODE_CHALLENGES:
                if (sOptions->submenu == CHALLENGES_MENU_COUNT - 1)
                {
                    gTasks[taskId].func = Task_OptionMenuSave;
                }
                else
                {
                    sOptions->submenu++;
                    DrawTopBarText();
                    ReDrawAll();
                    HighlightOptionMenuItem();
                    DrawDescriptionText();
                }
                break;
            }
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        switch (sOptions->optionMode)
        {
        case MENUMODE_OPTIONSPLUS:
            gTasks[taskId].func = Task_OptionMenuSave;
            break;
        }
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (sOptions->visibleCursor[sOptions->submenu] == NUM_OPTIONS_FROM_BORDER) // don't advance visible cursor until scrolled to the bottom
        {
            if (--sOptions->menuCursor[sOptions->submenu] == 0)
                sOptions->visibleCursor[sOptions->submenu]--;
            else
                ScrollMenu(1);
        }
        else
        {
            if (--sOptions->menuCursor[sOptions->submenu] < 0) // Scroll all the way to the bottom.
            {
                sOptions->visibleCursor[sOptions->submenu] = sOptions->menuCursor[sOptions->submenu] = optionsToDraw-2;
                ScrollAll(0);
                sOptions->visibleCursor[sOptions->submenu] = optionsToDraw-1;
                sOptions->menuCursor[sOptions->submenu] = MenuItemCount() - 1;
            }
            else
            {
                sOptions->visibleCursor[sOptions->submenu]--;
            }
        }
        HighlightOptionMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (sOptions->visibleCursor[sOptions->submenu] == optionsToDraw-2) // don't advance visible cursor until scrolled to the bottom
        {
            if (++sOptions->menuCursor[sOptions->submenu] == MenuItemCount() - 1)
                sOptions->visibleCursor[sOptions->submenu]++;
            else
                ScrollMenu(0);
        }
        else
        {
            if (++sOptions->menuCursor[sOptions->submenu] >= MenuItemCount() - 1) // Scroll all the way to the top.
            {
                sOptions->visibleCursor[sOptions->submenu] = optionsToDraw-2;
                sOptions->menuCursor[sOptions->submenu] = MenuItemCount() - optionsToDraw-1;
                ScrollAll(1);
                sOptions->visibleCursor[sOptions->submenu] = sOptions->menuCursor[sOptions->submenu] = 0;
            }
            else
            {
                sOptions->visibleCursor[sOptions->submenu]++;
            }
        }
        HighlightOptionMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        int cursor;
        u8 previousOption;
        cursor = sOptions->menuCursor[sOptions->submenu];
        switch (sOptions->optionMode)
        {
        case MENUMODE_OPTIONSPLUS:
            switch (sOptions->submenu)
            {
            case OPTIONSPLUS_MENU_VISUALS:
                previousOption = sOptions->selection.optionsPlus.visuals[cursor];
                if (CheckConditions(cursor))
                {
                    if (sItemFunctionsVisuals[cursor].processInput != NULL)
                    {
                        sOptions->selection.optionsPlus.visuals[cursor] = sItemFunctionsVisuals[cursor].processInput(previousOption);
                        ReDrawAll();
                        DrawDescriptionText();
                    }

                    if (previousOption != sOptions->selection.optionsPlus.visuals[cursor])
                        DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
                }
                break;
            case OPTIONSPLUS_MENU_BATTLE:
                previousOption = sOptions->selection.optionsPlus.battle[cursor];
                if (CheckConditions(cursor))
                {
                    if (sItemFunctionsBattle[cursor].processInput != NULL)
                    {
                        sOptions->selection.optionsPlus.battle[cursor] = sItemFunctionsBattle[cursor].processInput(previousOption);
                        ReDrawAll();
                        DrawDescriptionText();
                    }

                    if (previousOption != sOptions->selection.optionsPlus.battle[cursor])
                        DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
                }
                break;
            case OPTIONSPLUS_MENU_MISC:
                previousOption = sOptions->selection.optionsPlus.misc[cursor];
                if (CheckConditions(cursor))
                {
                    if (sItemFunctionsMisc[cursor].processInput != NULL)
                    {
                        sOptions->selection.optionsPlus.misc[cursor] = sItemFunctionsMisc[cursor].processInput(previousOption);
                        ReDrawAll();
                        DrawDescriptionText();
                    }

                    if (previousOption != sOptions->selection.optionsPlus.misc[cursor])
                        DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
                }
                break;
            }
            break;
        case MENUMODE_CHALLENGES:
            switch (sOptions->submenu)
            {
            case CHALLENGES_MENU_RANDOMIZER:
                previousOption = sOptions->selection.challenges.randomizer[cursor];
                if (CheckConditions(cursor))
                {
                    if (sItemFunctionsRandom[cursor].processInput != NULL)
                    {
                        sOptions->selection.challenges.randomizer[cursor] = sItemFunctionsRandom[cursor].processInput(previousOption);
                        ReDrawAll();
                        DrawDescriptionText();
                    }

                    if (previousOption != sOptions->selection.challenges.randomizer[cursor])
                        DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
                }
                break;
            case CHALLENGES_MENU_NUZLOCKE:
                previousOption = sOptions->selection.challenges.nuzlocke[cursor];
                if (CheckConditions(cursor))
                {
                    if (sItemFunctionsNuzlocke[cursor].processInput != NULL)
                    {
                        sOptions->selection.challenges.nuzlocke[cursor] = sItemFunctionsNuzlocke[cursor].processInput(previousOption);
                        ReDrawAll();
                        DrawDescriptionText();
                    }

                    if (previousOption != sOptions->selection.challenges.nuzlocke[cursor])
                        DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
                }
                break;
            case CHALLENGES_MENU_DIFFICULTY:
                previousOption = sOptions->selection.challenges.difficulty[cursor];
                if (CheckConditions(cursor))
                {
                    if (sItemFunctionsDifficulty[cursor].processInput != NULL)
                    {
                        sOptions->selection.challenges.difficulty[cursor] = sItemFunctionsDifficulty[cursor].processInput(previousOption);
                        ReDrawAll();
                        DrawDescriptionText();
                    }

                    if (previousOption != sOptions->selection.challenges.difficulty[cursor])
                        DrawChoices(cursor, sOptions->visibleCursor[sOptions->submenu] * Y_DIFF);
                }
                break;
            }
            break;
        }
    }
    else if (JOY_NEW(R_BUTTON))
    {
        switch (sOptions->optionMode)
        {
        case MENUMODE_OPTIONSPLUS:
            if (sOptions->submenu == OPTIONSPLUS_MENU_COUNT - 1)
                sOptions->submenu = 0;
            else
                sOptions->submenu++;
            break;
        case MENUMODE_CHALLENGES:
            if (sOptions->submenu != CHALLENGES_MENU_COUNT - 1)
                sOptions->submenu++;
            break;
        }

        DrawTopBarText();
        ReDrawAll();
        HighlightOptionMenuItem();
        DrawDescriptionText();
    }
    else if (JOY_NEW(L_BUTTON))
    {
        switch (sOptions->optionMode)
        {
        case MENUMODE_OPTIONSPLUS:
            if (sOptions->submenu == 0)
                sOptions->submenu = OPTIONSPLUS_MENU_COUNT - 1;
            else
                sOptions->submenu--;
            break;
        case MENUMODE_CHALLENGES:
            if (sOptions->submenu != 0)
                sOptions->submenu--;
            break;
        }
        
        DrawTopBarText();
        ReDrawAll();
        HighlightOptionMenuItem();
        DrawDescriptionText();
    }
}

static void OptionsMenu_SaveOptions(void)
{
    switch (sOptions->optionMode)
    {
    case MENUMODE_OPTIONSPLUS:
        gSaveBlock2Ptr->optionsTextSpeed        = sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_TEXTSPEED];
        gSaveBlock2Ptr->optionsCurrentFont      = sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_FONT];
        gSaveBlock2Ptr->optionsWindowFrameType  = sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_FRAMETYPE];
        gSaveBlock2Ptr->optionsUniqueColors     = sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_UNIQUE_COLORS];
        gSaveBlock2Ptr->optionsMonAnimations    = sOptions->selection.optionsPlus.visuals[MENUITEM_VISUALS_ANIMATIONS];

        gSaveBlock2Ptr->optionsBattleSceneOff   = sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_BATTLESCENE];
        gSaveBlock2Ptr->optionsBattleStyle      = sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_BATTLESTYLE];
        gSaveBlock2Ptr->optionsHpBarSpeed       = sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_HP_BAR];
        gSaveBlock2Ptr->optionsExpBarSpeed      = sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_EXP_BAR];
        gSaveBlock2Ptr->optionsAnimSpeed        = sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_ANIM_SPEED];
        gSaveBlock2Ptr->optionsSummaryIvView    = sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_IV_VIEW];
        gSaveBlock2Ptr->optionsEffectiveness    = sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_EFFECTIVENESS];
        gSaveBlock2Ptr->optionsShowTypes        = sOptions->selection.optionsPlus.battle[MENUITEM_BATTLE_SHOW_TYPES];

        gSaveBlock2Ptr->optionsSound            = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_SOUND];
        gSaveBlock2Ptr->optionsVolumeBGM        = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_MUSIC_VOLUME];
        gSaveBlock2Ptr->optionsVolumeSFX        = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_SFX_VOLUME];
        gSaveBlock2Ptr->optionsVolumeCries      = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_CRIES_VOLUME];
        gSaveBlock2Ptr->optionsUnitSystem       = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_UNIT_SYSTEM];
        gSaveBlock2Ptr->optionsLButtonMode      = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_L_BUTTONMODE];
        gSaveBlock2Ptr->optionsRButtonMode      = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_R_BUTTONMODE];
        gSaveBlock2Ptr->optionsOwSpeed          = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_OVERWORLD_SPEED];
        gSaveBlock2Ptr->optionsDisableMatchCall = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_MATCHCALL];
        gSaveBlock2Ptr->optionsDebugMode        = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_DEBUG_MODE];
        gSaveBlock2Ptr->optionsFullStartMenu    = sOptions->selection.optionsPlus.misc[MENUITEM_MISC_START_MENU];
        break;
    case MENUMODE_CHALLENGES:
        switch (sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STARTER])
        {
        case 0:
            gSaveBlock2Ptr->tx_Random_Starter          = FALSE;
            gSaveBlock2Ptr->tx_Random_Starter_Stage2   = FALSE;
            break;
        case 1:
            gSaveBlock2Ptr->tx_Random_Starter          = TRUE;
            gSaveBlock2Ptr->tx_Random_Starter_Stage2   = FALSE;
            break;
        case 2:
            gSaveBlock2Ptr->tx_Random_Starter          = TRUE;
            gSaveBlock2Ptr->tx_Random_Starter_Stage2   = TRUE;
            break;
        }
        if (sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_OFF_ON] == TRUE)
        {
            gSaveBlock2Ptr->tx_Random_WildPokemon        = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_WILD_PKMN];
            gSaveBlock2Ptr->tx_Random_Trainer            = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TRAINER];
            gSaveBlock2Ptr->tx_Random_Static             = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_STATIC];
            gSaveBlock2Ptr->tx_Random_Similar            = !sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL];
            gSaveBlock2Ptr->tx_Random_MapBased           = TX_RANDOM_MAP_BASED;
            gSaveBlock2Ptr->tx_Random_IncludeLegendaries = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_INCLUDE_LEGENDARIES];
            gSaveBlock2Ptr->tx_Random_Type               = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TYPE];
            gSaveBlock2Ptr->tx_Random_Moves              = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_MOVES];
            gSaveBlock2Ptr->tx_Random_Abilities          = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_ABILITIES];
            gSaveBlock2Ptr->tx_Random_Evolutions         = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_EVOLUTIONS];
            gSaveBlock2Ptr->tx_Random_EvolutionMethods   = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_EVOLUTIONS_METHODS];
            gSaveBlock2Ptr->tx_Random_TypeEffectiveness  = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_TYPE_EFFEC];
            gSaveBlock2Ptr->tx_Random_Items              = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_ITEMS];
            gSaveBlock2Ptr->tx_Random_Chaos              = sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_CHAOS];
        }
        else
        {
            gSaveBlock2Ptr->tx_Random_WildPokemon        = FALSE;
            gSaveBlock2Ptr->tx_Random_Trainer            = FALSE;
            gSaveBlock2Ptr->tx_Random_Static             = FALSE;
            gSaveBlock2Ptr->tx_Random_Similar            = FALSE;
            gSaveBlock2Ptr->tx_Random_MapBased           = FALSE;
            gSaveBlock2Ptr->tx_Random_IncludeLegendaries = FALSE;
            gSaveBlock2Ptr->tx_Random_Type               = FALSE;
            gSaveBlock2Ptr->tx_Random_Moves              = FALSE;
            gSaveBlock2Ptr->tx_Random_Abilities          = FALSE;
            gSaveBlock2Ptr->tx_Random_Evolutions         = FALSE;
            gSaveBlock2Ptr->tx_Random_EvolutionMethods   = FALSE;
            gSaveBlock2Ptr->tx_Random_TypeEffectiveness  = FALSE;
            gSaveBlock2Ptr->tx_Random_Chaos              = FALSE;
        }

        switch (sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_NUZLOCKE])
        {
        case 0:
            gSaveBlock2Ptr->tx_Challenges_Nuzlocke          = FALSE;
            gSaveBlock2Ptr->tx_Challenges_NuzlockeHardcore  = FALSE;
            break;
        case 1:
            gSaveBlock2Ptr->tx_Challenges_Nuzlocke          = TRUE;
            gSaveBlock2Ptr->tx_Challenges_NuzlockeHardcore  = FALSE;
            break;
        case 2:
            gSaveBlock2Ptr->tx_Challenges_Nuzlocke          = TRUE;
            gSaveBlock2Ptr->tx_Challenges_NuzlockeHardcore  = TRUE;
            break;
        }
        if (gSaveBlock2Ptr->tx_Challenges_Nuzlocke)
        {
            gSaveBlock2Ptr->tx_Nuzlocke_SpeciesClause   = !sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE];
            gSaveBlock2Ptr->tx_Nuzlocke_ShinyClause     = !sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE];
            gSaveBlock2Ptr->tx_Nuzlocke_Deletion        = sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_DELETION];
        }
        else
        {
            gSaveBlock2Ptr->tx_Nuzlocke_SpeciesClause   = FALSE;
            gSaveBlock2Ptr->tx_Nuzlocke_ShinyClause     = FALSE;
            gSaveBlock2Ptr->tx_Nuzlocke_Deletion        = FALSE;
        }

        gSaveBlock2Ptr->tx_Challenges_TrainerDifficulty = sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_TRAINER_DIFFICULTY];
        gSaveBlock2Ptr->tx_Challenges_LevelCap      = sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_LEVEL_CAP];
        gSaveBlock2Ptr->tx_Challenges_NoItemPlayer  = sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_ITEM_PLAYER];
        gSaveBlock2Ptr->tx_Challenges_NoItemTrainer = sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_ITEM_TRAINER];
        gSaveBlock2Ptr->tx_Challenges_NoEVs         = sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_NO_EVS];
        gSaveBlock2Ptr->tx_Challenges_TrainerScalingIVs     = sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_SCALING_IVS];
        gSaveBlock2Ptr->tx_Challenges_TrainerScalingEVs     = sOptions->selection.challenges.difficulty[MENUITEM_DIFFICULTY_SCALING_EVS];
        break;
    }
}

static void Task_OptionMenuSave(u8 taskId)
{
    OptionsMenu_SaveOptions();
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        FREE_AND_SET_NULL(sOptions);
        try_free(sBg2TilemapBuffer);
        try_free(sBg3TilemapBuffer);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        HideBg(2);
        HideBg(3);
        SetMainCallback2(gMain.savedCallback);
    }
}

static void ScrollMenu(int direction)
{
    int menuItem, pos;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    if (direction == 0) // scroll down
        menuItem = sOptions->menuCursor[sOptions->submenu] + NUM_OPTIONS_FROM_BORDER, pos = optionsToDraw - 1;
    else
        menuItem = sOptions->menuCursor[sOptions->submenu] - NUM_OPTIONS_FROM_BORDER, pos = 0;

    // Hide one
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF, PIXEL_FILL(0));
    // Show one
    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(0), 0, Y_DIFF * pos, 26 * 8, Y_DIFF);
    // Print
    DrawChoices(menuItem, pos * Y_DIFF);
    DrawLeftSideOptionText(menuItem, (pos * Y_DIFF) + 1);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

static void ScrollAll(int direction) // to bottom or top
{
    int i, y, menuItem, pos;
    int scrollCount;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    scrollCount = MenuItemCount() - optionsToDraw;

    // Move items up/down
    ScrollWindow(WIN_OPTIONS, direction, Y_DIFF * scrollCount, PIXEL_FILL(0));

    // Clear moved items
    if (direction == 0)
    {
        y = optionsToDraw - scrollCount;
        if (y < 0)
            y = optionsToDraw;
        y *= Y_DIFF;
    }
    else
    {
        y = 0;
    }

    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(0), 0, y, 26 * 8, Y_DIFF * scrollCount);
    // Print new texts
    for (i = 0; i < scrollCount; i++)
    {
        if (direction == 0) // From top to bottom
            menuItem = MenuItemCount() - 1 - i, pos = optionsToDraw - 1 - i;
        else // From bottom to top
            menuItem = i, pos = i;
        DrawChoices(menuItem, pos * Y_DIFF);
        DrawLeftSideOptionText(menuItem, (pos * Y_DIFF) + 1);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

// Process Input functions ****GENERIC****
static int GetMiddleX(const u8 *txt1, const u8 *txt2, const u8 *txt3)
{
    int xMid;
    int widthLeft = GetStringWidth(1, txt1, 0);
    int widthMid = GetStringWidth(1, txt2, 0);
    int widthRight = GetStringWidth(1, txt3, 0);

    widthMid -= (198 - 104);
    xMid = (widthLeft - widthMid - widthRight) / 2 + 104;
    return xMid;
}

static int XOptions_ProcessInput(int x, int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (++selection > (x - 1))
            selection = 0;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (--selection < 0)
            selection = (x - 1);
    }
    return selection;
}

static int ProcessInput_Options_Two(int selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
        selection ^= 1;

    return selection;
}

static int ProcessInput_Options_Three(int selection)
{
    return XOptions_ProcessInput(3, selection);
}

static int ProcessInput_Options_Four(int selection)
{
    return XOptions_ProcessInput(4, selection);
}

static int ProcessInput_Options_Eleven(int selection)
{
    return XOptions_ProcessInput(11, selection);
}

static int ProcessInput_FrameType(int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, 0x70, 0x20);
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;

        LoadBgTiles(1, GetWindowFrameTilesPal(selection)->tiles, 0x120, 0x1A2);
        LoadPalette(GetWindowFrameTilesPal(selection)->pal, 0x70, 0x20);
    }
    return selection;
}

static int ProcessInput_MusicVolume(int selection)
{
    bool8 refreshMus = (selection == 0);

    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < 10)
            selection++;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
    }

    gSaveBlock2Ptr->optionsVolumeBGM = selection;

    if (refreshMus || selection == 0)
        FadeOutAndPlayNewMapMusic(GetCurrentMapMusic(), 1);
    m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, (256 * selection / 10));

    return selection;
}

static int ProcessInput_SoundVolume(int selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < 10)
            selection++;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
    }

    return selection;
}

// Draw Choices functions ****GENERIC****
static void DrawOptionMenuChoice(const u8 *text, u8 x, u8 y, u8 style, bool8 active)
{
    bool8 choosen = FALSE;
    if (style != 0)
        choosen = TRUE;

    DrawRightSideChoiceText(text, x, y + 1, choosen, active);
}

static void DrawChoices_Options_Four(const u8 *const *const strings, int selection, int y, bool8 active)
{
    static const u8 choiceOrders[][3] =
    {
        {0, 1, 2},
        {0, 1, 2},
        {1, 2, 3},
        {1, 2, 3},
    };
    u8 styles[4] = {0};
    int xMid;
    const u8 *order = choiceOrders[selection];

    styles[selection] = 1;
    xMid = GetMiddleX(strings[order[0]], strings[order[1]], strings[order[2]]);

    DrawOptionMenuChoice(strings[order[0]], 104, y, styles[order[0]], active);
    DrawOptionMenuChoice(strings[order[1]], xMid, y, styles[order[1]], active);
    DrawOptionMenuChoice(strings[order[2]], GetStringRightAlignXOffset(1, strings[order[2]], 198), y, styles[order[2]], active);
}

static void ReDrawAll(void)
{
    u8 menuItem = sOptions->menuCursor[sOptions->submenu] - sOptions->visibleCursor[sOptions->submenu];
    u8 i;
    u8 optionsToDraw = min(OPTIONS_ON_SCREEN, MenuItemCount());

    if (MenuItemCount() <= OPTIONS_ON_SCREEN) // Draw or delete the scrolling arrows based on options in the menu
    {
        if (sOptions->arrowTaskId != TASK_NONE)
        {
            RemoveScrollIndicatorArrowPair(sOptions->arrowTaskId);
            sOptions->arrowTaskId = TASK_NONE;
        }
    }
    else
    {
        if (sOptions->arrowTaskId == TASK_NONE)
        {
            sOptions->arrowTaskId = AddScrollIndicatorArrowPairParameterized(SCROLL_ARROW_UP, 240 / 2, 20, 110, MenuItemCount() - 1, 110, 110, 0);
        }

    }

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(0));
    for (i = 0; i < optionsToDraw; i++)
    {
        DrawChoices(menuItem+i, i * Y_DIFF);
        DrawLeftSideOptionText(menuItem+i, (i * Y_DIFF) + 1);
    }
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
}

static const u8 sText_On[] = _("ON");
static const u8 sText_Off[] = _("OFF");
static const u8 sText_Faster[] = _("FASTER");
static const u8 sText_Instant[] = _("INSTANT");
static const u8 sText_Normal[] = _("NORMAL");
static const u8 sText_ZeroPercent[] = _("0%{0x77}{0x77}");
static const u8 sText_HundredPercent[] = _("100%");
static const u8 sText_FontEmerald[] = _("EMERALD");    //tx_optionsPlus
static const u8 sText_FontFireRed[] = _("FRLG");        //tx_optionsPlus
static const u8 sText_AnimSpeed1[] = _("1x");
static const u8 sText_AnimSpeed2[] = _("2x");
static const u8 sText_AnimSpeed3[] = _("3x");
static const u8 sText_AnimSpeed4[] = _("4x");
static const u8 sText_None[] = _("NONE");
static const u8 sText_LEqualsA[] = _("L=A TURBO");
static const u8 sText_AutoRun[] = _("AUTO-RUN");
static const u8 sText_Register[] = _("REGISTER");
static const u8 sText_DexNav[] = _("DEXNAV");
static const u8 sText_BikeSwitch[] = _("BIKE SWITCH");
static const u8 sText_Placeholder[] = _("WIP");
static const u8 sText_Fullscreen[] = _("FULLSCREEN");
static const u8 sText_Original[] = _("ORIGINAL");

static const u8 sText_Random[]  = _("RANDOM");
static const u8 sText_3Stage[]  = _("EVO");
static const u8 sText_Random_Chaos[] = _("CHAOS");
static const u8 sText_Challenges_Nuzlocke_Normal[]      = _("NORMAL");
static const u8 sText_Challenges_Nuzlocke_Hardcore[]    = _("HARD");
static const u8 sText_Nuzlocke_Cemetery[]  = _("CEMETERY");
static const u8 sText_Nuzlocke_Deletion[]  = _("RELEASE");
static const u8 sText_Yes[] = _("YES");
static const u8 sText_No[]  = _("NO");
static const u8 sText_ScalingIVsEVs_Scaling[]   = _("SCALE");
static const u8 sText_ScalingIVsEVs_Hard[]      = _("HARD");
static const u8 sText_ScalingIVsEVs_Extreme[]    = _("EXTREME");
static const u8 sText_Challenges_LevelCap_Normal[]  = _("SOFT");
static const u8 sText_Challenges_LevelCap_Hard[]    = _("HARD");
static const u8 sText_Challenges_TrainerDifficulty_Easy[]    = _("EASY");
static const u8 sText_Challenges_TrainerDifficulty_Normal[]  = _("NORMAL");
static const u8 sText_Challenges_TrainerDifficulty_Hard[]    = _("HARD");
static const u8 sText_Challenges_TrainerDifficulty_Lunatic[] = _("LUNATIC");

static const u8 *const sTextSpeedStrings[] = {gText_TextSpeedSlow, gText_TextSpeedMid, gText_TextSpeedFast, sText_Faster};
static const u8 *const sAnimSpeedStrings[] = {sText_AnimSpeed1, sText_AnimSpeed2, sText_AnimSpeed3, sText_AnimSpeed4};

static const u8 *const sText_ScalingEVs_Strings[] = {sText_Off, sText_ScalingIVsEVs_Scaling, sText_ScalingIVsEVs_Hard, sText_ScalingIVsEVs_Extreme};
static const u8 *const sText_Challenges_TrainerDifficulty_Strings[] = {sText_Challenges_TrainerDifficulty_Easy, sText_Challenges_TrainerDifficulty_Normal, sText_Challenges_TrainerDifficulty_Hard, sText_Challenges_TrainerDifficulty_Lunatic};

static void DrawChoices_TextSpeed(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_VISUALS_TEXTSPEED);
    DrawChoices_Options_Four(sTextSpeedStrings, selection, y, active);
}

static void DrawChoices_BattleScene(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_BATTLESCENE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(FONT_NORMAL, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_BattleStyle(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_BATTLESTYLE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_BattleStyleShift, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_BattleStyleSet, GetStringRightAlignXOffset(FONT_NORMAL, gText_BattleStyleSet, 198), y, styles[1], active);
}

static void DrawChoices_Sound(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MISC_SOUND);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_SoundMono, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_SoundStereo, GetStringRightAlignXOffset(FONT_NORMAL, gText_SoundStereo, 198), y, styles[1], active);
}

static void DrawChoices_BarSpeed(int selection, int y) //HP and EXP
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_EXP_BAR);

    if (selection == 0)
         DrawOptionMenuChoice(sText_Normal, 104, y, 1, active);
    else if (selection < 10)
    {
        u8 textPlus[] = _("+1{0x77}{0x77}{0x77}{0x77}{0x77}"); // 0x77 is to clear INSTANT text
        textPlus[1] = CHAR_0 + selection;
        DrawOptionMenuChoice(textPlus, 104, y, 1, active);
    }
    else
        DrawOptionMenuChoice(sText_Instant, 104, y, 1, active);
}

static void DrawChoices_MusicVolume(int selection, int y) //HP and EXP
{
    bool8 active = CheckConditions(MENUITEM_MISC_MUSIC_VOLUME);

    if (selection == 0)
        DrawOptionMenuChoice(sText_ZeroPercent, 104, y, 1, active);
    else if (selection < 10)
    {
        u8 textPlus[] = _("10%{0x77}{0x77}");
        textPlus[0] = CHAR_0 + selection;
        DrawOptionMenuChoice(textPlus, 104, y, 1, active);
    }
    else
        DrawOptionMenuChoice(sText_HundredPercent, 104, y, 1, active);
}

static void DrawChoices_SFXVolume(int selection, int y) //HP and EXP
{
    bool8 active = CheckConditions(MENUITEM_MISC_SFX_VOLUME);

    if (selection == 0)
    {
        DrawOptionMenuChoice(sText_ZeroPercent, 104, y, 1, active);
    }
    else if (selection < 10)
    {
        u8 textPlus[] = _("10%{0x77}{0x77}");
        textPlus[0] = CHAR_0 + selection;
        DrawOptionMenuChoice(textPlus, 104, y, 1, active);
    }
    else
    {
        DrawOptionMenuChoice(sText_HundredPercent, 104, y, 1, active);
    }
}

static void DrawChoices_CriesVolume(int selection, int y) //HP and EXP
{
    bool8 active = CheckConditions(MENUITEM_MISC_CRIES_VOLUME);

    if (selection == 0)
    {
        DrawOptionMenuChoice(sText_ZeroPercent, 104, y, 1, active);
    }
    else if (selection < 10)
    {
        u8 textPlus[] = _("10%{0x77}{0x77}");
        textPlus[0] = CHAR_0 + selection;
        DrawOptionMenuChoice(textPlus, 104, y, 1, active);
    }
    else
    {
        DrawOptionMenuChoice(sText_HundredPercent, 104, y, 1, active);
    }
}

static void DrawChoices_UnitSystem(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MISC_UNIT_SYSTEM);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(gText_UnitSystemImperial, 104, y, styles[0], active);
    DrawOptionMenuChoice(gText_UnitSystemMetric, GetStringRightAlignXOffset(1, gText_UnitSystemMetric, 198), y, styles[1], active);
}

static void DrawChoices_FrameType(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_VISUALS_FRAMETYPE);
    u8 text[16];
    u8 n = selection + 1;
    u16 i;

    for (i = 0; gText_FrameTypeNumber[i] != EOS && i <= 5; i++)
        text[i] = gText_FrameTypeNumber[i];

    // Convert a number to decimal string
    if (n / 10 != 0)
    {
        text[i] = n / 10 + CHAR_0;
        i++;
        text[i] = n % 10 + CHAR_0;
        i++;
    }
    else
    {
        text[i] = n % 10 + CHAR_0;
        i++;
        text[i] = 0x77;
        i++;
    }

    text[i] = EOS;

    DrawOptionMenuChoice(gText_FrameType, 104, y, 0, active);
    DrawOptionMenuChoice(text, 128, y, 1, active);
}

static void DrawChoices_Font(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_VISUALS_FONT);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_FontEmerald, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_FontFireRed, GetStringRightAlignXOffset(1, sText_FontFireRed, 198), y, styles[1], active);
}

static void DrawChoices_MatchCall(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MISC_MATCHCALL);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_StartMenu(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MISC_START_MENU);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Fullscreen, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Original, GetStringRightAlignXOffset(1, sText_Original, 198), y, styles[1], active);
}

static void DrawChoices_DebugMode(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MISC_DEBUG_MODE);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_AnimSpeed(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_ANIM_SPEED);
    DrawChoices_Options_Four(sAnimSpeedStrings, selection, y, active);
}

static void DrawChoices_UniqueColors(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_VISUALS_UNIQUE_COLORS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_IvView(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_IV_VIEW);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_Effectiveness(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_EFFECTIVENESS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_ShowTypes(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_BATTLE_SHOW_TYPES);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_MonAnimations(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_VISUALS_ANIMATIONS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_LButtonMode(int selection, int y) //HP and EXP
{
    bool8 active = CheckConditions(MENUITEM_MISC_L_BUTTONMODE);

    switch (selection)
    {
    default:
    case OPTIONS_L_BUTTON_MODE_NONE:
        DrawOptionMenuChoice(sText_None, 104, y, 1, active);
        break;
    case OPTIONS_L_BUTTON_MODE_L_EQUALS_A:
        DrawOptionMenuChoice(sText_LEqualsA, 104, y, 1, active);
        break;
    case OPTIONS_L_BUTTON_MODE_AUTO_RUN:
        DrawOptionMenuChoice(sText_AutoRun, 104, y, 1, active);
        break;
    case OPTIONS_L_BUTTON_MODE_REGISTER:
        DrawOptionMenuChoice(sText_Register, 104, y, 1, active);
        break;
    }
}

static void DrawChoices_RButtonMode(int selection, int y) //HP and EXP
{
    bool8 active = CheckConditions(MENUITEM_MISC_R_BUTTONMODE);

    switch (selection)
    {
    default:
    case OPTIONS_R_BUTTON_MODE_NONE:
        DrawOptionMenuChoice(sText_None, 104, y, 1, active);
        break;
    case OPTIONS_R_BUTTON_MODE_DEXNAV_SEARCH:
        DrawOptionMenuChoice(sText_DexNav, 104, y, 1, active);
        break;
    case OPTIONS_R_BUTTON_MODE_BIKE_SWITCH:
        DrawOptionMenuChoice(sText_BikeSwitch, 104, y, 1, active);
        break;
    case OPTIONS_R_BUTTON_MODE_REGISTER:
        DrawOptionMenuChoice(sText_Register, 104, y, 1, active);
        break;
    }
}

static void DrawChoices_OverworldSpeed(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_MISC_OVERWORLD_SPEED);
    DrawChoices_Options_Four(sAnimSpeedStrings, selection, y, active);
}

static void DrawChoices_Random_OffOn(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_On, GetStringRightAlignXOffset(1, sText_On, 198), y, styles[1], active);
}

static void DrawChoices_Random_OffRandom(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);   
    DrawOptionMenuChoice(sText_Random, GetStringRightAlignXOffset(1, sText_Random, 198), y, styles[1], active);
}

static void DrawChoices_Random_Toggle(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_OFF_ON);
    DrawChoices_Random_OffOn(selection, y, active);
}

static void DrawChoices_Random_Starter(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_STARTER);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Off, sText_Random, sText_3Stage);
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Random, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_3Stage, GetStringRightAlignXOffset(1, sText_3Stage, 198), y, styles[2], active);
}
static void DrawChoices_Random_WildPkmn(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_WILD_PKMN);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_Trainer(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_TRAINER);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_Static(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_STATIC);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_EvoStages(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_Random_Legendaries(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_INCLUDE_LEGENDARIES);
    DrawChoices_Random_OffOn(selection, y, active);
}

static void DrawChoices_Random_Types(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_TYPE);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_Moves(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_MOVES);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_Abilities(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_ABILITIES);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_Evolutions(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_EVOLUTIONS);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_EvolutionMethods(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_EVOLUTIONS_METHODS);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_TypeEffect(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_TYPE_EFFEC);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_Items(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_ITEMS);
    DrawChoices_Random_OffRandom(selection, y, active);
}

static void DrawChoices_Random_OffChaos(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_RANDOM_CHAOS);
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Random_Chaos, GetStringRightAlignXOffset(1, sText_Random_Chaos, 198), y, styles[1], active);

    if (selection == 1)
        sOptions->selection.challenges.randomizer[MENUITEM_RANDOM_SIMILAR_EVOLUTION_LEVEL] = 1;
}

static void DrawChoices_Nuzlocke_OnOff(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_On, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Off, GetStringRightAlignXOffset(1, sText_Off, 198), y, styles[1], active);
}

static void DrawChoices_Challenges_Nuzlocke(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_NUZLOCKE);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Off, sText_Challenges_Nuzlocke_Normal, sText_Challenges_Nuzlocke_Hardcore);
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Challenges_Nuzlocke_Normal, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_Challenges_Nuzlocke_Hardcore, GetStringRightAlignXOffset(1, sText_Challenges_Nuzlocke_Hardcore, 198), y, styles[2], active);

    if (selection == 0)
    {
        sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_SPECIES_CLAUSE]    = !TX_NUZLOCKE_SPECIES_CLAUSE;
        sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_SHINY_CLAUSE]      = !TX_NUZLOCKE_SHINY_CLAUSE;
        sOptions->selection.challenges.nuzlocke[MENUITEM_NUZLOCKE_DELETION]          = TX_NUZLOCKE_DELETION; 
    }
}

static void DrawChoices_Nuzlocke_SpeciesClause(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_SPECIES_CLAUSE);
    DrawChoices_Nuzlocke_OnOff(selection, y, active);
}

static void DrawChoices_Nuzlocke_ShinyClause(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_SHINY_CLAUSE);
    DrawChoices_Nuzlocke_OnOff(selection, y, active);
}

static void DrawChoices_Nuzlocke_Deletion(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_NUZLOCKE_DELETION);
    u8 styles[2] = {0};
    styles[selection] = 1;
    DrawOptionMenuChoice(sText_Nuzlocke_Cemetery, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Nuzlocke_Deletion, GetStringRightAlignXOffset(1, sText_Nuzlocke_Deletion, 198), y, styles[1], active);
}

static void DrawChoices_Challenges_YesNo(int selection, int y, bool8 active)
{
    u8 styles[2] = {0};
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Yes, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_No, GetStringRightAlignXOffset(1, sText_No, 198), y, styles[1], active);
}
static void DrawChoices_Challenges_ItemsPlayer(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_ITEM_PLAYER);
    DrawChoices_Challenges_YesNo(selection, y, active);
}
static void DrawChoices_Challenges_ItemsTrainer(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_ITEM_TRAINER);
    DrawChoices_Challenges_YesNo(selection, y, active);
}
static void DrawChoices_Challenges_NoEVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_NO_EVS);
    DrawChoices_Challenges_YesNo(selection, y, active);
}

static void DrawChoices_Challenges_ScalingIVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_SCALING_IVS);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Off, sText_ScalingIVsEVs_Scaling, sText_ScalingIVsEVs_Hard);
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_ScalingIVsEVs_Scaling, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_ScalingIVsEVs_Hard, GetStringRightAlignXOffset(1, sText_ScalingIVsEVs_Hard, 198), y, styles[2], active);
}

static void DrawChoices_Challenges_ScalingEVs(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_SCALING_EVS);
    DrawChoices_Options_Four(sText_ScalingEVs_Strings, selection, y, active);
}

static void DrawChoices_Challenges_LevelCap(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_LEVEL_CAP);
    u8 styles[3] = {0};
    int xMid = GetMiddleX(sText_Off, sText_Challenges_LevelCap_Normal, sText_Challenges_LevelCap_Hard);
    styles[selection] = 1;

    DrawOptionMenuChoice(sText_Off, 104, y, styles[0], active);
    DrawOptionMenuChoice(sText_Challenges_LevelCap_Normal, xMid, y, styles[1], active);
    DrawOptionMenuChoice(sText_Challenges_LevelCap_Hard, GetStringRightAlignXOffset(1, sText_Challenges_LevelCap_Hard, 198), y, styles[2], active);
}

static void DrawChoices_Challenges_TrainerDifficulties(int selection, int y)
{
    bool8 active = CheckConditions(MENUITEM_DIFFICULTY_TRAINER_DIFFICULTY);
    DrawOptionMenuChoice(sText_Challenges_TrainerDifficulty_Strings[selection], 104, y, 1, active);
}

// Background tilemap
#define TILE_TOP_CORNER_L 0x1A2 // 418
#define TILE_TOP_EDGE     0x1A3 // 419
#define TILE_TOP_CORNER_R 0x1A4 // 420
#define TILE_LEFT_EDGE    0x1A5 // 421
#define TILE_RIGHT_EDGE   0x1A7 // 423
#define TILE_BOT_CORNER_L 0x1A8 // 424
#define TILE_BOT_EDGE     0x1A9 // 425
#define TILE_BOT_CORNER_R 0x1AA // 426

static void DrawBgWindowFrames(void)
{
    // Description window
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1, 14,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2, 14, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28, 14,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1, 15,  1,  4,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28, 15,  1,  4,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, 19,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, 19, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, 19,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}
