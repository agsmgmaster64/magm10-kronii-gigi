#include "global.h"
#include "new_game.h"
#include "derby.h"
#include "random.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
#include "lottery_corner.h"
#include "play_time.h"
#include "mauville_old_man.h"
#include "match_call.h"
#include "lilycove_lady.h"
#include "load_save.h"
#include "pokeblock.h"
#include "dewford_trend.h"
#include "berry.h"
#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "constants/flags.h"
#include "money.h"
#include "trainer_hill.h"
#include "tv.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "pokedex.h"
#include "apprentice.h"
#include "frontier_util.h"
#include "pokedex.h"
#include "save.h"
#include "link_rfu.h"
#include "main.h"
#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "pokemon_jump.h"
#include "decoration_inventory.h"
#include "secret_base.h"
#include "player_pc.h"
#include "field_specials.h"
#include "berry_powder.h"
#include "mystery_gift.h"
#include "outfit_menu.h"
#include "union_room_chat.h"
#include "constants/map_groups.h"
#include "quests.h"
#include "constants/items.h"
#include "music_player.h"
#include "difficulty.h"
#include "tx_randomizer_and_challenges.h"
#include "randomizer.h"
#include "follower_npc.h"
#include "string_util.h"
#include "strings.h"

extern const u8 EventScript_ResetAllMapFlags[];

static void ClearFrontierRecord(void);
static void WarpToTruck(void);
static void ResetMiniGamesRecords(void);
static void ResetItemFlags(void);
static void ResetOutfitData(void);
static void ResetDexNav(void);

EWRAM_DATA bool8 gDifferentSaveFile = FALSE;
EWRAM_DATA bool8 gEnableContestDebugging = FALSE;

static const struct ContestWinner sContestWinnerPicDummy =
{
    .monName = _(""),
    .trainerName = _("")
};

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

u32 GetTrainerId(u8 *trainerId)
{
    return (trainerId[3] << 24) | (trainerId[2] << 16) | (trainerId[1] << 8) | (trainerId[0]);
}

void CopyTrainerId(u8 *dst, u8 *src)
{
    s32 i;
    for (i = 0; i < TRAINER_ID_LENGTH; i++)
        dst[i] = src[i];
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 16) | GetGeneratedTrainerIdLower();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
}

static void SetDefaultOptions(void)
{
    gSaveBlock2Ptr->optionsButtonMode = OPTIONS_BUTTON_MODE_LR;
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlock2Ptr->optionsWindowFrameType = 0;
    gSaveBlock2Ptr->optionsSound = OPTIONS_SOUND_STEREO;
    gSaveBlock2Ptr->optionsBattleStyle = OPTIONS_BATTLE_STYLE_SHIFT;
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    gSaveBlock2Ptr->regionMapZoom = FALSE;
    gSaveBlock2Ptr->optionsUnitSystem = UNITS_IMPERIAL;
    gSaveBlock2Ptr->optionsHpBarSpeed = 0;
    gSaveBlock2Ptr->optionsExpBarSpeed = 0;
    gSaveBlock2Ptr->optionsDisableMatchCall = 0;
    gSaveBlock2Ptr->optionsCurrentFont = 0;
    gSaveBlock2Ptr->optionsAnimSpeed = OPTIONS_BATTLE_SCENE_1X;
    gSaveBlock2Ptr->optionsUniqueColors = 0;
    gSaveBlock2Ptr->optionsSummaryIvView = 1;
    gSaveBlock2Ptr->optionsMonAnimations = 1;
    gSaveBlock2Ptr->optionsShowTypes = 0;
    gSaveBlock2Ptr->optionsEffectiveness = 0;
    gSaveBlock2Ptr->optionsDebugMode = 1;
    gSaveBlock2Ptr->optionsVolumeBGM = 10;
    gSaveBlock2Ptr->optionsVolumeSFX = 10;
    gSaveBlock2Ptr->optionsVolumeCries = 10;
    gSaveBlock2Ptr->optionsRButtonMode = OPTIONS_R_BUTTON_MODE_NONE;
    gSaveBlock2Ptr->optionsLButtonMode = OPTIONS_L_BUTTON_MODE_NONE;
    gSaveBlock2Ptr->optionsOwSpeed = OPTIONS_OVERWORLD_SPEED_1X;
}

static void ClearPokedexFlags(void)
{
    gUnusedPokedexU8 = 0;
    memset(&gSaveBlock1Ptr->dexCaught, 0, sizeof(gSaveBlock1Ptr->dexCaught));
    memset(&gSaveBlock1Ptr->dexSeen, 0, sizeof(gSaveBlock1Ptr->dexSeen));
}

void ClearAllContestWinnerPics(void)
{
    s32 i;

    ClearContestWinnerPicsInContestHall();

    // Clear Museum paintings
    for (i = MUSEUM_CONTEST_WINNERS_START; i < NUM_CONTEST_WINNERS; i++)
        gSaveBlock1Ptr->contestWinners[i] = sContestWinnerPicDummy;
}

static void ClearFrontierRecord(void)
{
    CpuFill32(0, &gSaveBlock2Ptr->frontier, sizeof(gSaveBlock2Ptr->frontier));

    gSaveBlock2Ptr->frontier.opponentNames[0][0] = EOS;
    gSaveBlock2Ptr->frontier.opponentNames[1][0] = EOS;
}

static void WarpToTruck(void)
{
    if (HOUSE_LIKE_CARPET)
        SetWarpDestination(MAP_GROUP(MAP_CARPET_PORT), MAP_NUM(MAP_CARPET_PORT), WARP_ID_NONE, -1, -1);
    else
        SetWarpDestination(MAP_GROUP(MAP_INSIDE_OF_TRUCK), MAP_NUM(MAP_INSIDE_OF_TRUCK), WARP_ID_NONE, -1, -1);
    WarpIntoMap();
}

void Sav2_ClearSetDefault(void)
{
    ClearSav2();
    SetDefaultOptions();
    ResetChallengesData();
    ResetOutfitData();
}

void ResetMenuAndMonGlobals(void)
{
    gDifferentSaveFile = FALSE;
    ResetPokedexScrollPositions();
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
    ResetPokeblockScrollPositions();
}

static void ResetOutfitData(void)
{
    memset(gSaveBlock3Ptr->outfits, 0, sizeof(gSaveBlock3Ptr->outfits));
    UnlockOutfit(DEFAULT_OUTFIT);
    if (!StringCompare(gSaveBlock2Ptr->playerName, gText_Gigi))
    {
        UnlockOutfit(OUTFIT_GIGI_MURIN);
        gSaveBlock3Ptr->currOutfitId = OUTFIT_GIGI_MURIN;
    }
    else
    {
        gSaveBlock3Ptr->currOutfitId = DEFAULT_OUTFIT;
    }
}

void NewGameInitData(void)
{
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        RtcReset();

    gDifferentSaveFile = TRUE;
    gSaveBlock2Ptr->encryptionKey = 0;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    ClearFrontierRecord();
    ClearSav1();
    ClearSav3();
    ClearAllMail();
    gSaveBlock2Ptr->specialSaveWarpFlags = 0;
    gSaveBlock2Ptr->gcnLinkFlags = 0;
    InitPlayerTrainerId();
    PlayTimeCounter_Reset();
    ClearPokedexFlags();
    InitEventData();
    ClearTVShowData();
    ResetGabbyAndTy();
    ClearSecretBases();
    ClearBerryTrees();
    SetMoney(&gSaveBlock1Ptr->money, 3000);
    SetCoins(0);
    GetNewDerby();
    ResetLinkContestBoolean();
    ResetGameStats();
    ClearAllContestWinnerPics();
    ClearPlayerLinkBattleRecords();
    InitSeedotSizeRecord();
    InitLotadSizeRecord();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    DeactivateAllRoamers();
    ClearBag();
    NewGameInitPCItems();
    ClearPokeblocks();
    ClearDecorationInventories();
    InitEasyChatPhrases();
    SetMauvilleOldMan();
    InitDewfordTrend();
    ResetFanClub();
    ResetLotteryCorner();
    WarpToTruck();
    RunScriptImmediately(EventScript_ResetAllMapFlags);
    ResetMiniGamesRecords();
    InitUnionRoomChatRegisteredTexts();
    InitLilycoveLady();
    ResetAllApprenticeData();
    ClearRankingHallRecords();
    InitMatchCallCounters();
    ClearMysteryGift();
    WipeTrainerNameRecords();
    ResetTrainerHillResults();
    ResetContestLinkResults();
    //SetCurrentDifficultyLevel(DIFFICULTY_NORMAL); // handled via ResetChallengesData
    #if (RANDOMIZER_AVAILABLE == TRUE) && (RANDOMIZER_DYNAMIC_SPECIES == TRUE)
        PreloadRandomizationTables();
    #endif
    ResetItemFlags();
    ResetDexNav();
    QuestMenu_ResetMenuSaveData();
    gSaveBlock3Ptr->followerIndex = OW_FOLLOWER_NOT_SET;
    ResetAllPlayerMusic();
    ResetOutfitData();
    ClearFollowerNPCData();
    gSaveBlock3Ptr->playerBike = MACH_BIKE;
    gSaveBlock1Ptr->registeredItemSelect = ITEM_NONE;
    gSaveBlock3Ptr->registeredItemL = ITEM_NONE;
    gSaveBlock3Ptr->registeredItemR = ITEM_NONE;
    gSaveBlock3Ptr->autoRun = FALSE;
}

void ResetChallengesData(void)
{
    gSaveBlock2Ptr->tx_Random_Starter                   = TX_RANDOM_STARTER;
    gSaveBlock2Ptr->tx_Random_Starter_Stage2            = TX_RANDOM_STARTER_STAGE2;
    gSaveBlock2Ptr->tx_Random_WildPokemon               = TX_RANDOM_WILD_POKEMON;
    gSaveBlock2Ptr->tx_Random_Trainer                   = TX_RANDOM_TRAINER;
    gSaveBlock2Ptr->tx_Random_Static                    = TX_RANDOM_STATIC;
    gSaveBlock2Ptr->tx_Random_Similar                   = TX_RANDOM_SIMILAR;
    gSaveBlock2Ptr->tx_Random_MapBased                  = TX_RANDOM_MAP_BASED;
    gSaveBlock2Ptr->tx_Random_IncludeLegendaries        = TX_RANDOM_INCLUDE_LEGENDARIES;
    gSaveBlock2Ptr->tx_Random_Type                      = TX_RANDOM_TYPE;
    gSaveBlock2Ptr->tx_Random_Moves                     = TX_RANDOM_MOVES;
    gSaveBlock2Ptr->tx_Random_Abilities                 = TX_RANDOM_ABILITIES;
    gSaveBlock2Ptr->tx_Random_Evolutions                = TX_RANDOM_EVOLUTION;
    gSaveBlock2Ptr->tx_Random_EvolutionMethods          = TX_RANDOM_EVOLUTION_METHODE;
    gSaveBlock2Ptr->tx_Random_TypeEffectiveness         = TX_RANDOM_TYPE_EFFECTIVENESS;
    gSaveBlock2Ptr->tx_Random_Items                     = TX_RANDOM_ITEMS;
    gSaveBlock2Ptr->tx_Random_Chaos                     = TX_RANDOM_CHAOS_MODE;
    gSaveBlock2Ptr->tx_Random_OneForOne                 = TX_RANDOM_ONE_FOR_ONE;

    gSaveBlock2Ptr->tx_Challenges_Nuzlocke              = TX_NUZLOCKE_NUZLOCKE;
    gSaveBlock2Ptr->tx_Challenges_NuzlockeHardcore      = TX_NUZLOCKE_NUZLOCKE_HARDCORE;
    gSaveBlock2Ptr->tx_Nuzlocke_SpeciesClause           = TX_NUZLOCKE_SPECIES_CLAUSE;
    gSaveBlock2Ptr->tx_Nuzlocke_ShinyClause             = TX_NUZLOCKE_SHINY_CLAUSE;
    gSaveBlock2Ptr->tx_Nuzlocke_Deletion                = TX_NUZLOCKE_DELETION;

    gSaveBlock2Ptr->tx_Challenges_PartyLimit            = TX_DIFFICULTY_PARTY_LIMIT;
    gSaveBlock2Ptr->tx_Challenges_LevelCap              = TX_DIFFICULTY_LEVEL_CAP;
    gSaveBlock2Ptr->tx_Challenges_TrainerDifficulty     = DIFFICULTY_NORMAL;
    gSaveBlock2Ptr->tx_Challenges_NoItemPlayer          = TX_DIFFICULTY_NO_ITEM_PLAYER;
    gSaveBlock2Ptr->tx_Challenges_NoItemTrainer         = TX_DIFFICULTY_NO_ITEM_TRAINER;
    gSaveBlock2Ptr->tx_Challenges_NoEVs                 = TX_DIFFICULTY_NO_EVS;
    gSaveBlock2Ptr->tx_Challenges_TrainerScalingIVs     = TX_DIFFICULTY_SCALING_IVS;
    gSaveBlock2Ptr->tx_Challenges_TrainerScalingEVs     = TX_DIFFICULTY_SCALING_EVS;
    gSaveBlock2Ptr->tx_Challenges_PkmnCenter            = TX_DIFFICULTY_PKMN_CENTER;

    gSaveBlock2Ptr->tx_Challenges_EvoLimit              = TX_CHALLENGE_EVO_LIMIT;
    gSaveBlock2Ptr->tx_Challenges_OneTypeChallenge      = TX_CHALLENGE_TYPE;
    gSaveBlock2Ptr->tx_Challenges_BaseStatEqualizer     = TX_CHALLENGE_BASE_STAT_EQUALIZER;
    gSaveBlock2Ptr->tx_Challenges_Mirror                = TX_CHALLENGE_MIRROR;
    gSaveBlock2Ptr->tx_Challenges_Mirror_Thief          = TX_CHALLENGE_MIRROR_THIEF;
}

static void ResetMiniGamesRecords(void)
{
    CpuFill16(0, &gSaveBlock2Ptr->berryCrush, sizeof(struct BerryCrush));
    SetBerryPowder(&gSaveBlock2Ptr->berryCrush.berryPowderAmount, 0);
    CpuFill16(0, &gSaveBlock2Ptr->berryPick, sizeof(struct BerryPickingResults));
}

static void ResetItemFlags(void)
{
#if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_FIRST_TIME
    memset(&gSaveBlock3Ptr->itemFlags, 0, sizeof(gSaveBlock3Ptr->itemFlags));
#endif
}

static void ResetDexNav(void)
{
#if USE_DEXNAV_SEARCH_LEVELS == TRUE
    memset(gSaveBlock1Ptr->dexNavSearchLevels, 0, sizeof(gSaveBlock1Ptr->dexNavSearchLevels));
#endif
    gSaveBlock1Ptr->dexNavChain = 0;
}
