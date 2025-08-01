Debug_MessageEnd:
	waitmessage
	waitbuttonpress
	releaseall
	end

Debug_ShowFieldMessageStringVar4::
	special ShowFieldMessageStringVar4
	goto Debug_MessageEnd

Debug_CheatStart::
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar VAR_BIRCH_LAB_STATE, 2
	setvar VAR_ROUTE101_STATE, 3
	givemon SPECIES_CHIBI_SARA, 20, ITEM_NONE
	givemon SPECIES_CHIBI_LOUISE, 20, ITEM_NONE
	givemon SPECIES_CHIBI_KURUMI, 20, ITEM_NONE
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 2
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	setvar VAR_LITTLEROOT_TOWN_STATE, 4 @ 4: Received Running Shoes
	setvar VAR_LITTLEROOT_INTRO_STATE, 7 @ 7: Told to go meet rival
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2 @ 2: Met Rival's Mom (and is corresponding gender)
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2 @ 2: Met Rival's Mom (and is corresponding gender)
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4 @ 4: Received Pokedex
	setflag FLAG_RECEIVED_BIKE
	additem ITEM_ACRO_BIKE
	setvar VAR_BRINEY_HOUSE_STATE, 1
	setvar VAR_ROUTE116_STATE, 2
	setflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	setflag FLAG_VISITED_OLDALE_TOWN
	setflag FLAG_VISITED_DEWFORD_TOWN
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	setflag FLAG_VISITED_PETALBURG_CITY
	setflag FLAG_VISITED_SLATEPORT_CITY
	setflag FLAG_VISITED_MAUVILLE_CITY
	setflag FLAG_VISITED_RUSTBORO_CITY
	setflag FLAG_VISITED_FORTREE_CITY
	setflag FLAG_VISITED_LILYCOVE_CITY
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setflag FLAG_VISITED_SOOTOPOLIS_CITY
	setflag FLAG_VISITED_EVER_GRANDE_CITY
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	release
	end

Debug_FlagsNotSetOverworldConfigMessage::
	message Debug_FlagsNotSetOverworldConfigMessage_Text
	goto Debug_MessageEnd

Debug_FlagsNotSetOverworldConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable flag in:\l"
	.string "'include/config/overworld.h'!$"

Debug_FlagsNotSetBattleConfigMessage::
	message Debug_FlagsNotSetBattleConfigMessage_Text
	goto Debug_MessageEnd

Debug_FlagsNotSetBattleConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable flag in:\l"
	.string "'include/config/battle.h'!$"

Debug_BoxFilledMessage::
	message Debug_BoxFilledMessage_Text
	goto Debug_MessageEnd

Debug_BoxFilledMessage_Text:
	.string "Storage boxes filled!$"

Debug_EventScript_CheckEVs::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_CheckEVs_End
	callnative Script_GetChosenMonOffensiveEVs
	msgbox Debug_EventScript_Text_OffensiveEVs, MSGBOX_DEFAULT
	callnative Script_GetChosenMonDefensiveEVs
	msgbox Debug_EventScript_Text_DefensiveEVs, MSGBOX_DEFAULT
Debug_EventScript_CheckEVs_End::
	releaseall
	end

Debug_EventScript_Text_OffensiveEVs:
	.string "ATK EVs: {STR_VAR_1}, SPATK EVs: {STR_VAR_2}, SPEED EVs: {STR_VAR_3}$"

Debug_EventScript_Text_DefensiveEVs:
	.string "HP EVs: {STR_VAR_1}, DEF EVs: {STR_VAR_2}, SPDEF EVs: {STR_VAR_3}$"

Debug_EventScript_CheckIVs::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_CheckIVs_End
	callnative Script_GetChosenMonOffensiveIVs
	msgbox Debug_EventScript_Text_OffensiveIVs, MSGBOX_DEFAULT
	callnative Script_GetChosenMonDefensiveIVs
	msgbox Debug_EventScript_Text_DefensiveIVs, MSGBOX_DEFAULT
Debug_EventScript_CheckIVs_End::
	releaseall
	end

Debug_EventScript_Text_OffensiveIVs:
	.string "ATK IVs: {STR_VAR_1}, SPATK IVs: {STR_VAR_2}, SPEED IVs: {STR_VAR_3}$"

Debug_EventScript_Text_DefensiveIVs:
	.string "HP IVs: {STR_VAR_1}, DEF IVs: {STR_VAR_2}, SPDEF IVs: {STR_VAR_3}$"

Debug_EventScript_Script_1::
	lockall
	msgbox Debug_EventScript_Script_1_TestMessage, MSGBOX_DEFAULT
	closemessage
	coinmart Debug_EventScript_Script_1_Mart
	movetutorpointmart Debug_EventScript_Script_1_Mart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_Script_1_TestMessage:
	.string "{CREATE_MUGSHOT MUGSHOT_AMELIA EMOTE_NORMAL}Amelia Normal\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_SHIORI EMOTE_NORMAL}Shiori\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_BAELZ EMOTE_NORMAL}Baelz Normal\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_BAELZ EMOTE_SERIOUS}Baelz Serious\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_BAELZ EMOTE_HAPPY}Baelz Happy\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_NORMAL}Kronii Normal\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_HAPPY}Kronii Happy\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SAD}Kronii Sad\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SERIOUS}Kronii Serious\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_ANNOYED}Kronii Annoyed\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_ANGRY}Kronii Angry\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SHADOW}Kronii Shadow\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_NORMAL}Gigi Normal\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_HAPPY}Gigi OwO\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_8}Gigi X Smile\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_9}Gigi Laugh\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_SHADOW}Gigi Shadow$"

	.align 2
Debug_EventScript_Script_1_Mart:
	.2byte ITEM_POWER_HEART
	.2byte ITEM_GUARD_HEART
	.2byte ITEM_SWIFT_HEART
	.2byte ITEM_TECH_HEART
	.2byte ITEM_HELPER_HEART
	.2byte ITEM_JUST_HEART
	.2byte ITEM_NONE

	.align 2
Debug_EventScript_Script_1_Mart2:
	.2byte MOVE_SURF
	.2byte MOVE_STRENGTH
	.2byte ITEM_NONE

Debug_EventScript_Script_2::
	givemon SPECIES_NORMAL_YOUMU, 100, ITEM_MAID_UNIFORM, ITEM_LUXURY_ORB, NATURE_ADAMANT, 2, 0, 0, 252, 0, 252, 0, 0, 31, 31, 31, 31, 31, 31, MOVE_BLADE_FLASH, MOVE_DRAWN_LINE, MOVE_SHADOW_HIT, MOVE_SWORDS_DANCE, TRUE, 0, TYPE_STELLAR
	release
	end

Debug_EventScript_Script_3::
	lock
	message Debug_EventScript_Script_3_Text_ChoosePrintType
	waitmessage
	multichoice 21, 0, MULTI_TRAINER_CARD_ICON_TINT, TRUE
	switch VAR_RESULT
	case 1, Debug_EventScript_Script_3_PrintTypeBlack
	case 2, Debug_EventScript_Script_3_PrintTypePink
	case 3, Debug_EventScript_Script_3_PrintTypeSepia
	setvar VAR_0x8004, 0
	goto Debug_EventScript_Script_3_UpdateTrainerCard

Debug_EventScript_Script_3_PrintTypeBlack::
	setvar VAR_0x8004, 1
	goto Debug_EventScript_Script_3_UpdateTrainerCard

Debug_EventScript_Script_3_PrintTypePink::
	setvar VAR_0x8004, 2
	goto Debug_EventScript_Script_3_UpdateTrainerCard

Debug_EventScript_Script_3_PrintTypeSepia::
	setvar VAR_0x8004, 3
	goto Debug_EventScript_Script_3_UpdateTrainerCard

Debug_EventScript_Script_3_UpdateTrainerCard::
	playse MUS_RG_PHOTO
	special UpdateTrainerCardPhotoIcons
	release
	end


Debug_EventScript_Script_3_Text_ChoosePrintType::
	.string "Please choose the print type.$"

Debug_EventScript_Script_4::
	giveitem ITEM_FISHING_ROD
	giveitem ITEM_BICYCLE
	giveitem ITEM_ITEMFINDER
	giveitem ITEM_VS_SEEKER
	giveitem ITEM_POKEMON_BOX_LINK
	giveitem ITEM_WAILMER_PAIL
	giveitem ITEM_TOHOVIAL
	giveitem ITEM_POKE_FLUTE
	giveitem ITEM_HEXORB
	giveitem ITEM_OUTFIT_BOX
	giveitem ITEM_MUSIC_PLAYER
	giveitem ITEM_COIN_CASE
	giveitem ITEM_POWDER_JAR
	giveitem ITEM_BIG_AXE
	giveitem ITEM_PAGER
	giveitem ITEM_SURFBOARD
	giveitem ITEM_POWER_GLOVE
	giveitem ITEM_LANTERN
	giveitem ITEM_PICKAXE
	giveitem ITEM_CLIMBING_GEAR
	giveitem ITEM_SCUBA_GEAR
	giveitem ITEM_TERA_ORB
	release
	end

Debug_EventScript_Script_5::
	lockall
	setvar VAR_0x8008, INGAME_TRADE_MEOWTH
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox Debug_EventScript_Script_5_Text_WouldYouLikeToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Debug_EventScript_Script_5_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Debug_EventScript_Script_5_DeclineTrade
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, Debug_EventScript_Script_5_DeclineTrade
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox Debug_EventScript_Script_5_Text_PromiseIllBeGoodToIt, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_Script_5_DeclineTrade::
	msgbox Debug_EventScript_Script_5_Text_WellThatsFineToo, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_Script_5_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox Debug_EventScript_Script_5_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_Script_5_Text_WouldYouLikeToTrade:
	.string "My POKéMON is a {STR_VAR_2}.\n"
	.string "Do you know it?\l"
	.string "It's quite cute and rather nice.\p"
	.string "This little one, I could trade with\n"
	.string "pride!\p"
	.string "Would you like to trade me a {STR_VAR_1}\n"
	.string "for my {STR_VAR_2}?$"

Debug_EventScript_Script_5_Text_PromiseIllBeGoodToIt:
	.string "Oh, it's adorable!\n"
	.string "Thank you!\l"
	.string "I promise I'll be good to it!\p"
	.string "Oh! I hope you'll be good to\n"
	.string "my {STR_VAR_2}, too!$"

Debug_EventScript_Script_5_Text_DontTradeForAnythingButMon:
	.string "Oh, I'm sorry!\n"
	.string "I don't intend to trade for anything\l"
	.string "but a {STR_VAR_1}.$"

Debug_EventScript_Script_5_Text_WellThatsFineToo:
	.string "Oh, you won't?\n"
	.string "Well, that's fine, too.\l"
	.string "Please come visit us again.$"

Debug_EventScript_Script_5_Text_SkittySoMuchCuterThanImagined:
	.string "Giggle!\n"
	.string "A SKITTY is so much cuter than I had\l"
	.string "imagined. I'm delighted!$"


Debug_EventScript_Script_6::
	lockall
	message gText_HowMayIServeYou
	waitmessage
	pokemartoutfit Debug_EventScript_Script_6_Mart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	releaseall
	end

	.align 2
Debug_EventScript_Script_6_Mart:
	.2byte OUTFIT_THE_ALTERNATE
	.2byte OUTFIT_YOUNG_START
	.2byte OUTFIT_ALTERED_YOUTH
	.2byte OUTFIT_GIGI_MURIN
	.2byte OUTFIT_NONE

Debug_EventScript_Script_7::
	lockall
	choose_mons
	multi_2_vs_1 TRAINER_JOEY, Debug_EventScript_Script_5_Text_SkittySoMuchCuterThanImagined, PARTNER_STEVEN
	release
	end

Debug_EventScript_Script_8::
	release
	end

Debug_CheckSaveBlock::
	callnative CheckSaveBlock1Size
	msgbox Debug_SaveBlock1Size, MSGBOX_DEFAULT
	callnative CheckSaveBlock2Size
	msgbox Debug_SaveBlock2Size, MSGBOX_DEFAULT
	callnative CheckSaveBlock3Size
	msgbox Debug_SaveBlock3Size, MSGBOX_DEFAULT
	callnative CheckPokemonStorageSize
	msgbox Debug_PokemonStorageSize, MSGBOX_DEFAULT
	release
	end

Debug_SaveBlock1Size::
	.string "SaveBlock1 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_SaveBlock2Size::
	.string "SaveBlock2 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_SaveBlock3Size::
	.string "SaveBlock3 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_PokemonStorageSize::
	.string "{PKMN}Storage size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_CheckROMSpace::
	callnative CheckROMSize
	msgbox Debug_ROMSize, MSGBOX_DEFAULT
	release
	end

Debug_ROMSize::
	.string "ROM size: {STR_VAR_1}MB/32MB.\n"
	.string "Free space: {STR_VAR_2}MB.$"

Debug_HatchAnEgg::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_HatchAnEgg_End
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_ne VAR_RESULT, SPECIES_EGG, DebugScript_HatchAnEgg_CantForceHatch
	special EggHatch
	waitstate
Debug_HatchAnEgg_End::
	releaseall
	end

Debug_NoPokemon::
	msgbox DebugScript_Text_EmptyParty, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_HatchAnEgg_CantForceHatch::
	msgbox DebugScript_HatchAnEgg_Text_NotAnEgg, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_Text_EmptyParty::
	.string "You have no Pokémon nor Eggs.$"

DebugScript_HatchAnEgg_Text_NotAnEgg::
	.string "That's not a Pokémon Egg.$"

DebugScript_ZeroDaycareMons::
	msgbox DebugText_DaycareNoPokemon, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_OneDaycareMons::
	msgbox DebugText_DaycareOnePokemon, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_DaycareMonsNotCompatible::
	msgbox DebugText_DaycarePokemonNotCompatible, MSGBOX_DEFAULT
	releaseall
	end

DebugText_DaycareNoPokemon:
	.string "You have no Pokémon at Daycare.$"

DebugText_DaycareOnePokemon:
	.string "You have only one Pokémon at Daycare.$"

DebugText_DaycarePokemonNotCompatible:
	.string "Your Pokémon at Daycare can't\nhave babies together!$"

Debug_ShowExpansionVersion::
	callnative BufferExpansionVersion
	msgbox Debug_ExpansionVersion, MSGBOX_DEFAULT
	release
	end

Debug_ExpansionVersion:
	.string "pokeemerald-expansion {STR_VAR_1}$"

Debug_Follower_NPC_Not_Enabled::
	msgbox Debug_Enable_To_Use_Follower_NPCs, MSGBOX_DEFAULT
	release
	end

Debug_Enable_To_Use_Follower_NPCs:
	.string "Feature unavailable.\nSet FNPC_ENABLE_NPC_FOLLOWERS to\lTRUE in 'include/config/follower_npc.h'.$"

Debug_Follower_NPC_Event_Script::
	lock
	facefollowernpc
	msgbox Debug_Follower_NPC_Test_Message, MSGBOX_DEFAULT
	releaseall
	end

Debug_Follower_NPC_Test_Message:
	.string "This is a Follower NPC test.$"

Debug_EventScript_Steven_Multi::
	call MossdeepCity_SpaceCenter_2F_EventScript_ChoosePartyForMultiBattle
	release
	end

Debug_BerryPestsDisabled::
	msgbox DebugText_BerryPestsDisabled, MSGBOX_DEFAULT
	release
	end

DebugText_BerryPestsDisabled:
	.string "OW_BERRY_PESTS is disabled.\n"
	.string "Unable to force pests onto berry trees.$"

Debug_BerryWeedsDisabled::
	msgbox DebugText_BerryWeedsDisabled, MSGBOX_DEFAULT
	release
	end

DebugText_BerryWeedsDisabled:
	.string "OW_BERRY_WEEDS is disabled.\n"
	.string "Unable to force weeds onto berry trees.$"

Debug_EventScript_InflictStatus1::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	dynmultipush Debug_EventScript_InflictStatus1_Text_Single, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_PartyWide, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 2
	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Single
	case 1, Debug_EventScript_InflictStatus1_Party
	case 2, Debug_EventScript_InflictStatus1_Close
Debug_EventScript_InflictStatus1_Close:
	releaseall
	end

Debug_EventScript_InflictStatus1_Single:
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_InflictStatus1_Close
	dynmultipush Debug_EventScript_InflictStatus1_Text_Poison, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_Paralysis, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Sleep, 2
	dynmultipush Debug_EventScript_InflictStatus1_Text_Burn, 3
	dynmultipush Debug_EventScript_InflictStatus1_Text_Freeze, 4
	dynmultipush Debug_EventScript_InflictStatus1_Text_Frostbite, 5
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Single_Poison
	case 1, Debug_EventScript_InflictStatus1_Single_Paralysis
	case 2, Debug_EventScript_InflictStatus1_Single_Sleep
	case 3, Debug_EventScript_InflictStatus1_Single_Burn
	case 4, Debug_EventScript_InflictStatus1_Single_Freeze
	case 5, Debug_EventScript_InflictStatus1_Single_Frostbite
	case 6, Debug_EventScript_InflictStatus1_Close
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
	releaseall
	end

Debug_EventScript_SetHiddenNature::
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_InflictStatus1_Close
	dynmultipush Debug_EventScript_ChangeNature_Text_Hardy, 0
	dynmultipush Debug_EventScript_ChangeNature_Text_Lonely, 1
	dynmultipush Debug_EventScript_ChangeNature_Text_Brave, 2
	dynmultipush Debug_EventScript_ChangeNature_Text_Adamant, 3
	dynmultipush Debug_EventScript_ChangeNature_Text_Naughty, 4
	dynmultipush Debug_EventScript_ChangeNature_Text_Bold, 5
	dynmultipush Debug_EventScript_ChangeNature_Text_Docile, 6
	dynmultipush Debug_EventScript_ChangeNature_Text_Relaxed, 7
	dynmultipush Debug_EventScript_ChangeNature_Text_Impish, 8
	dynmultipush Debug_EventScript_ChangeNature_Text_Lax, 9
	dynmultipush Debug_EventScript_ChangeNature_Text_Timid, 10
	dynmultipush Debug_EventScript_ChangeNature_Text_Hasty, 11
	dynmultipush Debug_EventScript_ChangeNature_Text_Serious, 12
	dynmultipush Debug_EventScript_ChangeNature_Text_Jolly, 13
	dynmultipush Debug_EventScript_ChangeNature_Text_Naive, 14
	dynmultipush Debug_EventScript_ChangeNature_Text_Modest, 15
	dynmultipush Debug_EventScript_ChangeNature_Text_Mild, 16
	dynmultipush Debug_EventScript_ChangeNature_Text_Quiet, 17
	dynmultipush Debug_EventScript_ChangeNature_Text_Bashful, 18
	dynmultipush Debug_EventScript_ChangeNature_Text_Rash, 19
	dynmultipush Debug_EventScript_ChangeNature_Text_Calm, 20
	dynmultipush Debug_EventScript_ChangeNature_Text_Gentle, 21
	dynmultipush Debug_EventScript_ChangeNature_Text_Sassy, 22
	dynmultipush Debug_EventScript_ChangeNature_Text_Careful, 23
	dynmultipush Debug_EventScript_ChangeNature_Text_Quirky, 24
	dynmultistack 0, 0, TRUE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
    special SetHiddenNature
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Poison:
	setstatus1 STATUS1_POISON, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Paralysis:
	setstatus1 STATUS1_PARALYSIS, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Sleep:
	setstatus1 STATUS1_SLEEP, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Burn:
	setstatus1 STATUS1_BURN, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Freeze:
	setstatus1 STATUS1_FREEZE, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Frostbite:
	setstatus1 STATUS1_FROSTBITE, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Party:
	dynmultipush Debug_EventScript_InflictStatus1_Text_Poison, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_Paralysis, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Sleep, 2
	dynmultipush Debug_EventScript_InflictStatus1_Text_Burn, 3
	dynmultipush Debug_EventScript_InflictStatus1_Text_Freeze, 4
	dynmultipush Debug_EventScript_InflictStatus1_Text_Frostbite, 5
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Party_Poison
	case 1, Debug_EventScript_InflictStatus1_Party_Paralysis
	case 2, Debug_EventScript_InflictStatus1_Party_Sleep
	case 3, Debug_EventScript_InflictStatus1_Party_Burn
	case 4, Debug_EventScript_InflictStatus1_Party_Freeze
	case 5, Debug_EventScript_InflictStatus1_Party_Frostbite
	case 6, Debug_EventScript_InflictStatus1_Close
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Poison:
	setstatus1 STATUS1_POISON, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Paralysis:
	setstatus1 STATUS1_PARALYSIS, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Sleep:
	setstatus1 STATUS1_SLEEP, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Burn:
	setstatus1 STATUS1_BURN, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Freeze:
	setstatus1 STATUS1_FREEZE, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Frostbite:
	setstatus1 STATUS1_FROSTBITE, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Text_Single:
	.string "Single$"

Debug_EventScript_InflictStatus1_Text_PartyWide:
	.string "Party-wide$"

Debug_EventScript_InflictStatus1_Text_Close:
	.string "Close$"

Debug_EventScript_InflictStatus1_Text_Poison:
	.string "Poison$"

Debug_EventScript_InflictStatus1_Text_Paralysis:
	.string "Paralysis$"

Debug_EventScript_InflictStatus1_Text_Sleep:
	.string "Sleep$"

Debug_EventScript_InflictStatus1_Text_Burn:
	.string "Burn$"

Debug_EventScript_InflictStatus1_Text_Freeze:
	.string "Freeze$"

Debug_EventScript_InflictStatus1_Text_Frostbite:
	.string "Frostbite$"

Debug_EventScript_SetTeraType::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_SetTeraType_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_SetTeraType_Close
	dynmultipush Debug_EventScript_SetTeraType_Text_Illusion, 0
	dynmultipush Debug_EventScript_SetTeraType_Text_Dream, 1
	dynmultipush Debug_EventScript_SetTeraType_Text_Flying, 2
	dynmultipush Debug_EventScript_SetTeraType_Text_Miasma, 3
	dynmultipush Debug_EventScript_SetTeraType_Text_Earth, 4
	dynmultipush Debug_EventScript_SetTeraType_Text_Beast, 5
	dynmultipush Debug_EventScript_SetTeraType_Text_Heart, 6
	dynmultipush Debug_EventScript_SetTeraType_Text_Ghost, 7
	dynmultipush Debug_EventScript_SetTeraType_Text_Steel, 8
	dynmultipush Debug_EventScript_SetTeraType_Text_Fire, 9
	dynmultipush Debug_EventScript_SetTeraType_Text_Water, 10
	dynmultipush Debug_EventScript_SetTeraType_Text_Nature, 11
	dynmultipush Debug_EventScript_SetTeraType_Text_Wind, 12
	dynmultipush Debug_EventScript_SetTeraType_Text_Reason, 13
	dynmultipush Debug_EventScript_SetTeraType_Text_Ice, 14
	dynmultipush Debug_EventScript_SetTeraType_Text_Faith, 15
	dynmultipush Debug_EventScript_SetTeraType_Text_Dark, 16
	dynmultipush Debug_EventScript_SetTeraType_Text_Cosmic, 17
	dynmultipush Debug_EventScript_SetTeraType_Text_Stellar, 18
	dynmultipush Debug_EventScript_SetTeraType_Text_Close, 19
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_SetTeraType_Illusion
	case 1, Debug_EventScript_SetTeraType_Dream
	case 2, Debug_EventScript_SetTeraType_Flying
	case 3, Debug_EventScript_SetTeraType_Miasma
	case 4, Debug_EventScript_SetTeraType_Earth
	case 5, Debug_EventScript_SetTeraType_Beast
	case 6, Debug_EventScript_SetTeraType_Heart
	case 7, Debug_EventScript_SetTeraType_Ghost
	case 8, Debug_EventScript_SetTeraType_Steel
	case 9, Debug_EventScript_SetTeraType_Fire
	case 10, Debug_EventScript_SetTeraType_Water
	case 11, Debug_EventScript_SetTeraType_Nature
	case 12, Debug_EventScript_SetTeraType_Wind
	case 13, Debug_EventScript_SetTeraType_Reason
	case 14, Debug_EventScript_SetTeraType_Ice
	case 15, Debug_EventScript_SetTeraType_Faith
	case 16, Debug_EventScript_SetTeraType_Dark
	case 17, Debug_EventScript_SetTeraType_Cosmic
	case 18, Debug_EventScript_SetTeraType_Stellar
	case 19, Debug_EventScript_SetTeraType_Close
	case MULTI_B_PRESSED, Debug_EventScript_SetTeraType_Close
Debug_EventScript_SetTeraType_Close:
	releaseall
	end

Debug_EventScript_SetTeraType_Illusion:
	setteratype TYPE_ILLUSION, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Dream:
	setteratype TYPE_DREAM, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Flying:
	setteratype TYPE_FLYING, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Miasma:
	setteratype TYPE_MIASMA, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Earth:
	setteratype TYPE_EARTH, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Beast:
	setteratype TYPE_BEAST, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Heart:
	setteratype TYPE_HEART, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Ghost:
	setteratype TYPE_GHOST, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Steel:
	setteratype TYPE_STEEL, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Fire:
	setteratype TYPE_FIRE, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Water:
	setteratype TYPE_WATER, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Nature:
	setteratype TYPE_NATURE, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Wind:
	setteratype TYPE_WIND, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Reason:
	setteratype TYPE_REASON, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Ice:
	setteratype TYPE_ICE, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Faith:
	setteratype TYPE_FAITH, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Dark:
	setteratype TYPE_DARK, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Cosmic:
	setteratype TYPE_COSMIC, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Stellar:
	setteratype TYPE_STELLAR, VAR_0x8004
	releaseall
	end

Debug_EventScript_SetTeraType_Text_Illusion:
	.string "Illusion$"

Debug_EventScript_SetTeraType_Text_Dream:
	.string "Dream$"

Debug_EventScript_SetTeraType_Text_Flying:
	.string "Flying$"

Debug_EventScript_SetTeraType_Text_Miasma:
	.string "Miasma$"

Debug_EventScript_SetTeraType_Text_Earth:
	.string "Earth$"

Debug_EventScript_SetTeraType_Text_Beast:
	.string "Beast$"

Debug_EventScript_SetTeraType_Text_Heart:
	.string "Heart$"

Debug_EventScript_SetTeraType_Text_Ghost:
	.string "Ghost$"

Debug_EventScript_SetTeraType_Text_Steel:
	.string "Steel$"

Debug_EventScript_SetTeraType_Text_Fire:
	.string "Fire$"

Debug_EventScript_SetTeraType_Text_Water:
	.string "Water$"

Debug_EventScript_SetTeraType_Text_Nature:
	.string "Nature$"

Debug_EventScript_SetTeraType_Text_Wind:
	.string "Wind$"

Debug_EventScript_SetTeraType_Text_Reason:
	.string "Reason$"

Debug_EventScript_SetTeraType_Text_Ice:
	.string "Ice$"

Debug_EventScript_SetTeraType_Text_Faith:
	.string "Faith$"

Debug_EventScript_SetTeraType_Text_Dark:
	.string "Dark$"

Debug_EventScript_SetTeraType_Text_Cosmic:
	.string "Cosmic$"

Debug_EventScript_SetTeraType_Text_Stellar:
	.string "Stellar$"

Debug_EventScript_SetTeraType_Text_Close:
	.string "Close$"
Debug_EventScript_ChangeNature_Text_Hardy:
	.string "Hardy$"
Debug_EventScript_ChangeNature_Text_Lonely:
	.string "Lonely$"
Debug_EventScript_ChangeNature_Text_Brave:
	.string "Brave$"
Debug_EventScript_ChangeNature_Text_Adamant:
	.string "Adamant$"
Debug_EventScript_ChangeNature_Text_Naughty:
	.string "Naughty$"
Debug_EventScript_ChangeNature_Text_Bold:
	.string "Bold$"
Debug_EventScript_ChangeNature_Text_Docile:
	.string "Docile$"
Debug_EventScript_ChangeNature_Text_Relaxed:
	.string "Relaxed$"
Debug_EventScript_ChangeNature_Text_Impish:
	.string "Impish$"
Debug_EventScript_ChangeNature_Text_Lax:
	.string "Lax$"
Debug_EventScript_ChangeNature_Text_Timid:
	.string "Timid$"
Debug_EventScript_ChangeNature_Text_Hasty:
	.string "Hasty$"
Debug_EventScript_ChangeNature_Text_Serious:
	.string "Serious$"
Debug_EventScript_ChangeNature_Text_Jolly:
	.string "Jolly$"
Debug_EventScript_ChangeNature_Text_Naive:
	.string "Naive$"
Debug_EventScript_ChangeNature_Text_Modest:
	.string "Modest$"
Debug_EventScript_ChangeNature_Text_Mild:
	.string "Mild$"
Debug_EventScript_ChangeNature_Text_Quiet:
	.string "Quiet$"
Debug_EventScript_ChangeNature_Text_Bashful:
	.string "Bashful$"
Debug_EventScript_ChangeNature_Text_Rash:
	.string "Rash$"
Debug_EventScript_ChangeNature_Text_Calm:
	.string "Calm$"
Debug_EventScript_ChangeNature_Text_Gentle:
	.string "Gentle$"
Debug_EventScript_ChangeNature_Text_Sassy:
	.string "Sassy$"
Debug_EventScript_ChangeNature_Text_Careful:
	.string "Careful$"
Debug_EventScript_ChangeNature_Text_Quirky:
	.string "Quirky$"

Debug_EventScript_EWRAMCounters::
	callnative CheckEWRAMCounters
	msgbox Debug_EventScript_EWRAMCounters_Text, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_EWRAMCounters_Text::
	.string "Follower Steps: {STR_VAR_1}.\n"
	.string "Fishing Chain: {STR_VAR_2}.$"

Debug_EventScript_FontTest_Text_1::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Angel Adept Blind Bodice Clique\n"
	.string "Coast Dunce Docile Enact Eosin\l"
	.string "Furlong Focal Gnome Gondola Human\l"
	.string "Hoist Inlet Iodine Justin Jocose\l"
	.string "Knoll Koala Linden Loads Milliner\l"
	.string "Modal Number Nodule Onset Oddball\l"
	.string "Pneumo Poncho Quanta Qophs Rhone\l"
	.string "Roman Snout Sodium Tundra Tocsin\l"
	.string "Uncle Udder Vulcan Vocal Whale\l"
	.string "Woman Xmas Xenon Yunnan Young\l"
	.string "Zloty Zodiac.$"

Debug_EventScript_FontTest_Text_2::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Angel angel adept for the nuance loads\n"
	.string "of the arena cocoa and quaalude. Blind\l"
	.string "blind bodice for the submit oboe of the\l"
	.string "club snob and abbot. Clique clique\l"
	.string "coast for the pouch loco of the franc\l"
	.string "assoc and accede. Dunce dunce docile\l"
	.string "for the loudness mastodon of the\l"
	.string "loud statehood and huddle.$"

Debug_EventScript_FontTest_Text_3::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Enact enact eosin for the quench coed\n"
	.string "of the pique canoe and bleep. Furlong\l"
	.string "furlong focal for the genuflect\l"
	.string "profound of the motif aloof and offers.\l"
	.string "Gnome gnome gondola for the impugn\l"
	.string "logos of the unplug analog and smuggle.\l"
	.string "Human human hoist for the buddhist\l"
	.string "alcohol of the riyadh caliph and\l"
	.string "bathhouse.$"

Debug_EventScript_FontTest_Text_4::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Inlet inlet iodine for the quince\n"
	.string "champion of the ennui scampi and shiite.\l"
	.string "Justin justin jocose for the djibouti\l"
	.string "sojourn of the oranj raj and hajjis.\l"
	.string "Knoll knoll koala for the banknote\l"
	.string "lookout of the dybbuk outlook and\l"
	.string "trekked. Linden linden loads for the\l"
	.string "ulna monolog of the consul menthol and\l"
	.string "shallot.$"

Debug_EventScript_FontTest_Text_5::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Milliner milliner modal for the alumna\n"
	.string "solomon of the album custom and summon.\l"
	.string "Number number nodule for the unmade\l"
	.string "economic of the shotgun bison and\l"
	.string "tunnel. Onset onset oddball for the\l"
	.string "abandon podium of the antiquo tempo\l"
	.string "and moonlit. Pneumo pneumo poncho for\l"
	.string "the dauphin opossum of the holdup\l"
	.string "bishop and supplies.$"

Debug_EventScript_FontTest_Text_6::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Quanta quanta qophs for the inquest\n"
	.string "sheqel of the cinq coq and suqqu. Rhone\l"
	.string "rhone roman for the burnt porous of the\l"
	.string "lemur clamor and carrot. Snout snout\l"
	.string "sodium for the ensnare bosom of the\l"
	.string "genus pathos and missing. Tundra\l"
	.string "tundra tocsin for the nutmeg isotope\l"
	.string "of the peasant ingot and ottoman.$"

Debug_EventScript_FontTest_Text_7::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Uncle uncle udder for the dunes cloud\n"
	.string "of the hindu thou and continuum. Vulcan\l"
	.string "vulcan vocal for the alluvial ovoid of\l"
	.string "the yugoslav chekhov and revved. Whale\l"
	.string "whale woman for the meanwhile blowout\l"
	.string "of the forepaw meadow and glowworm.\l"
	.string "Xmas xmas xenon for the bauxite\l"
	.string "doxology of the tableaux equinox and\l"
	.string "exxon.$"

Debug_EventScript_FontTest_Text_8::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Yunnan yunnan young for the dynamo\n"
	.string "coyote of the obloquy employ and\l"
	.string "sayyid. Zloty zloty zodiac for the gizmo\l"
	.string "ozone of the franz laissez and buzzing.$"


Debug_EventScript_FontTest_Text_9::                 @ Special thanks to Nintendo for this nice pangram to test other glyphs
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "42 × 138 = 5796.\n"
	.string "Mr Jock, TV quiz PhD: bags 20% fewer\l"
	.string "lynx at a café; voilà, they're “worth”\l"
	.string "♂1/♀1 = ¥1. That's 10 + 9 - 8 = 11\l"
	.string "Nintendo GBA can connect to a Nintendo\l"
	.string "GameCube console! He claimed-though I don't\l"
	.string "believe him-to have done so in an eyes-shut\l"
	.string "state…?$"

Debug_PrintFontTest::
	msgbox Debug_EventScript_FontTest_Text_1, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_2, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_3, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_4, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_5, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_6, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_7, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_8, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_9, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_FontTest::
	lockall
	goto Debug_PrintFontTest
@	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
@	dynmultipush Debug_EventScript_InflictStatus1_Text_Single, 0
@	dynmultipush Debug_EventScript_InflictStatus1_Text_PartyWide, 1
@	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 2
@	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
@	switch VAR_RESULT
@	case 0, Debug_EventScript_InflictStatus1_Single
@	case 1, Debug_EventScript_InflictStatus1_Party
@	case 2, Debug_EventScript_InflictStatus1_Close
@Debug_EventScript_InflictStatus1_Close:
@	releaseall
@	end

Debug_EventScript_TellTheTime::
	callnative DebugMenu_CalculateTime
	msgbox Debug_EventScript_TellTheTime_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	end

Debug_EventScript_PrintTimeOfDay::
	callnative DebugMenu_CalculateTimeOfDay
	msgbox DebugEventScript_PrintWeekday_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	end

Debug_EventScript_FakeRTCNotEnabled::
	msgbox Debug_EventScript_FakeRTCNotEnabled_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	return

Debug_EventScript_FakeRTCNotEnabled_Text_0:
	.string "You currently do not have Fake RTC\nenabled. Please enable it in include/\lconfig/overworld.h$"


Debug_EventScript_TellTheTime_Text_0:
	.string "Time and date:\n"
	.string "{STR_VAR_1}, {STR_VAR_2}:{STR_VAR_3}$"

DebugEventScript_PrintWeekday_Text_0:
	.string "Time of day: {STR_VAR_1}$"
