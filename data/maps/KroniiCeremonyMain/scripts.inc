KroniiCeremonyMain_MapScripts::
# 2 "data/maps/KroniiCeremonyMain/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, KroniiCeremonyMain_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

KroniiCeremonyMain_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 3 "data/maps/KroniiCeremonyMain/scripts.pory"
	map_script_2 VAR_HOUSE_LIKE_CARPET_STATE, 0, KroniiCeremonyMain_EventScript_KroniiGigiIntroduction
# 4 "data/maps/KroniiCeremonyMain/scripts.pory"
	map_script_2 VAR_HOUSE_LIKE_CARPET_STATE, 2, KroniiCeremonyMain_EventScript_KroniiCeremonyEvent
	.2byte 0


KroniiCeremonyMain_EventScript_KroniiGigiIntroduction::
# 9 "data/maps/KroniiCeremonyMain/scripts.pory"
	lockall
# 10 "data/maps/KroniiCeremonyMain/scripts.pory"
	addobject LOCALID_CEREMONY_KRONII
# 11 "data/maps/KroniiCeremonyMain/scripts.pory"
	setobjectxy LOCALID_CEREMONY_KRONII, 22, 35
# 12 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, KroniiCeremonyMain_Movement_KroniiIntroMove
# 13 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, KroniiCeremonyMain_Movement_GigiIntroMove
# 14 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 15 "data/maps/KroniiCeremonyMain/scripts.pory"
	playse SE_PIN
# 16 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_ExclamationMark
# 17 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 18 "data/maps/KroniiCeremonyMain/scripts.pory"
	delay 80
# 21 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterUp
# 22 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 23 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 24 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiIntro
# 25 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 26 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterUp
# 27 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 28 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 29 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiIntro
# 30 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 31 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterRight
# 32 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 33 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 34 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiIntro2
# 35 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 36 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterLeft
# 37 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 38 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 39 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiIntro2
# 40 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 41 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterRight
# 42 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 43 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 44 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiIntro3
# 45 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 46 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterLeft
# 47 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 48 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 49 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiIntro3
# 50 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 51 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterRight
# 52 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 53 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 54 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiIntro4
# 55 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 58 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, KroniiCeremonyMain_Movement_KroniiIntroGo
# 59 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 60 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_KRONII
# 63 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterUp
# 64 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 65 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 66 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiGiveStartingTeam
# 67 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 68 "data/maps/KroniiCeremonyMain/scripts.pory"
	call KroniiCeremonyMain_EventScript_GetStartingStuff
# 69 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 70 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiGoInside
# 71 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 74 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_PLAYER, KroniiCeremonyMain_Movement_PlayerDoorWay
# 75 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, KroniiCeremonyMain_Movement_GigiMoveToDoor
# 76 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 77 "data/maps/KroniiCeremonyMain/scripts.pory"
	opendoor 30, 31
# 78 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitdooranim
# 79 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, KroniiCeremonyMain_Movement_GigiGoInDoor
# 80 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 81 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_GIGI
# 82 "data/maps/KroniiCeremonyMain/scripts.pory"
	closedoor 30, 31
# 83 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitdooranim
# 84 "data/maps/KroniiCeremonyMain/scripts.pory"
	clearflag FLAG_CEREMONY_INSIDE_GIGI
# 85 "data/maps/KroniiCeremonyMain/scripts.pory"
	setvar VAR_HOUSE_LIKE_CARPET_STATE, 1
# 86 "data/maps/KroniiCeremonyMain/scripts.pory"
	releaseall
	end


KroniiCeremonyMain_EventScript_KroniiCeremonyEvent::
# 91 "data/maps/KroniiCeremonyMain/scripts.pory"
	lockall
# 92 "data/maps/KroniiCeremonyMain/scripts.pory"
	addobject LOCALID_CEREMONY_GIGI
# 93 "data/maps/KroniiCeremonyMain/scripts.pory"
	addobject LOCALID_CEREMONY_ENGINEER
# 94 "data/maps/KroniiCeremonyMain/scripts.pory"
	addobject LOCALID_CEREMONY_HIKER
# 95 "data/maps/KroniiCeremonyMain/scripts.pory"
	addobject LOCALID_CEREMONY_KINDLER
# 96 "data/maps/KroniiCeremonyMain/scripts.pory"
	setobjectxy LOCALID_CEREMONY_GIGI, 10, 17
# 97 "data/maps/KroniiCeremonyMain/scripts.pory"
	setobjectxy LOCALID_CEREMONY_ENGINEER, 25, 17
# 98 "data/maps/KroniiCeremonyMain/scripts.pory"
	setobjectxy LOCALID_CEREMONY_HIKER, 25, 17
# 99 "data/maps/KroniiCeremonyMain/scripts.pory"
	setobjectxy LOCALID_CEREMONY_KINDLER, 25, 17
# 100 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceDown
# 101 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 104 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 105 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiCeremonyIntro
# 106 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 109 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 110 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiCeremonyHoldOn
# 111 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 112 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterLeft
# 113 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, KroniiCeremonyMain_Movement_GigiMoveToStage
# 114 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 117 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 118 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiCeremonyInterruption
# 119 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 120 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 121 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiCeremonyRudelyInterrupted
# 122 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 123 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 124 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiCeremonyCueOthers
# 125 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 128 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterDown
# 129 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterDown
# 130 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_HIKER, KroniiCeremonyMain_Movement_HikerWalkToStage
# 131 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_ENGINEER, KroniiCeremonyMain_Movement_EngineerWalkToStage
# 132 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KINDLER, KroniiCeremonyMain_Movement_KindlerWalkToStage
# 133 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KINDLER
# 134 "data/maps/KroniiCeremonyMain/scripts.pory"
	playbgm MUS_B_FACTORY, FALSE
# 135 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_HIKER, KroniiCeremonyMain_Movement_HelpersStageActing
# 136 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_ENGINEER, KroniiCeremonyMain_Movement_HelpersStageActing
# 137 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KINDLER, KroniiCeremonyMain_Movement_HelpersStageActing
# 138 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KINDLER
# 139 "data/maps/KroniiCeremonyMain/scripts.pory"
	delay 80
# 142 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterLeft
# 143 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 144 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 145 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiCeremonySadAboutCeremony
# 146 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 147 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterRight
# 148 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 149 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 150 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiCeremonyCheckAudience
# 151 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 154 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterDown
# 155 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterDown
# 156 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 157 "data/maps/KroniiCeremonyMain/scripts.pory"
	special SpawnCameraObject
# 158 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CAMERA, KroniiCeremonyMain_Movement_CameraPanToAudience
# 159 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CAMERA
# 162 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_CYAN, Common_Movement_WalkInPlaceFasterUp
# 163 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_CYAN
# 164 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Cyan
# 165 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CyanReaction
# 166 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 167 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_KRONIE_2, Common_Movement_WalkInPlaceFasterUp
# 168 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_KRONIE_2
# 169 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_Kronie2Name
# 170 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_Kronie2Reaction
# 171 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 174 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CAMERA, KroniiCeremonyMain_Movement_CameraPanBackToStage
# 175 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CAMERA
# 176 "data/maps/KroniiCeremonyMain/scripts.pory"
	special RemoveCameraObject
# 177 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 178 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterRight
# 179 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 180 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 181 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiCeremonySeeAudience
# 182 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 183 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterDown
# 184 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 185 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 186 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiCeremonyApologizeGigi
# 187 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 188 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterRight
# 189 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 190 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 191 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiCeremonyAcceptApology
# 192 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 194 "data/maps/KroniiCeremonyMain/scripts.pory"
	setvar VAR_HOUSE_LIKE_CARPET_STATE, 3
# 195 "data/maps/KroniiCeremonyMain/scripts.pory"
	setrespawn HEAL_LOCATION_CARPET_TOWN
# 196 "data/maps/KroniiCeremonyMain/scripts.pory"
	fadescreenspeed FADE_TO_BLACK, 24
# 197 "data/maps/KroniiCeremonyMain/scripts.pory"
	special GameClear
# 198 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitstate
# 199 "data/maps/KroniiCeremonyMain/scripts.pory"
	releaseall
	end


KroniiCeremonyMain_EventScript_GetStartingStuff::
# 204 "data/maps/KroniiCeremonyMain/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 205 "data/maps/KroniiCeremonyMain/scripts.pory"
	playfanfare MUS_RG_OBTAIN_KEY_ITEM
# 206 "data/maps/KroniiCeremonyMain/scripts.pory"
	message KroniiCeremonyMain_Text_YouGotStartingTeam
# 207 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitfanfare
# 208 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 209 "data/maps/KroniiCeremonyMain/scripts.pory"
	givemon SPECIES_CHIBI_BIJOU, 10, ITEM_BENTO_BOX, ITEM_TOHO_ORB, NUM_NATURES, NUM_ABILITY_PERSONALITY, MON_GENDERLESS, 0, 0, 0, 0, 0, 0, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MOVE_CHARGE_BEAM, MOVE_CHARM, MOVE_MUD_BOMB, MOVE_NONE
# 210 "data/maps/KroniiCeremonyMain/scripts.pory"
	givemon SPECIES_CHIBI_MINORIKO_SANNI, 10, ITEM_CAMOUFLAGE, ITEM_TOHO_ORB, NUM_NATURES, NUM_ABILITY_PERSONALITY, MON_GENDERLESS, 0, 0, 0, 0, 0, 0, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MOVE_ABSORB, MOVE_EMBER, MOVE_BURN_POWDER, MOVE_LEECH_SEED
# 211 "data/maps/KroniiCeremonyMain/scripts.pory"
	givemon SPECIES_CHIBI_MARISA, 10, ITEM_NONE, ITEM_TOHO_ORB, NUM_NATURES, NUM_ABILITY_PERSONALITY, MON_GENDERLESS, 0, 0, 0, 0, 0, 0, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MAX_PER_STAT_IVS + 1, MOVE_THUNDERSHOCK, MOVE_THIEF, MOVE_AURORA_BEAM, MOVE_RAZOR_WIND
	return


KroniiCeremonyMain_EventScript_CantGoToStage::
# 216 "data/maps/KroniiCeremonyMain/scripts.pory"
	lockall
# 217 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CantGoToStage
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 219 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_PLAYER, KroniiCeremonyMain_Movement_PlayerGoDown
# 220 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_PLAYER
# 221 "data/maps/KroniiCeremonyMain/scripts.pory"
	releaseall
	end


KroniiCeremonyMain_EventScript_SuspiciousGuy::
# 226 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 227 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 228 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_SkualperGuyName
# 229 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuyIntro
# 230 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuySwindle, MSGBOX_YESNO
# 231 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_SuspiciousGuy_2
# 236 "data/maps/KroniiCeremonyMain/scripts.pory"
	showmoneybox 0, 0
# 237 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuyConvinced, MSGBOX_YESNO
# 238 "data/maps/KroniiCeremonyMain/scripts.pory"
	hidemoneybox
# 239 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuyNotEnoughMoney
# 240 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_SuspiciousGuy_2:
# 232 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuyDenied
# 233 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Kindler::
# 245 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 246 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 247 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_KindlerName
# 248 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KindlerNormal, MSGBOX_YESNO
# 249 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_Kindler_2
# 255 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 256 "data/maps/KroniiCeremonyMain/scripts.pory"
	trainerbattle_no_intro TRAINER_HAYDEN, KroniiCeremonyMain_Text_KindlerDefeat
# 257 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_KindlerName
# 258 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KindlerRecruit
# 259 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 260 "data/maps/KroniiCeremonyMain/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 261 "data/maps/KroniiCeremonyMain/scripts.pory"
	clearflag FLAG_CEREMONY_INSIDE_KINDLER
# 262 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_KINDLER
# 263 "data/maps/KroniiCeremonyMain/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 264 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_Kindler_2:
# 250 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KindlerRejected
# 251 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 252 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Engineer::
# 269 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 270 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 271 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_EngineerName
# 272 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_EngineerNormal, MSGBOX_YESNO
# 273 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_Engineer_2
# 279 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 280 "data/maps/KroniiCeremonyMain/scripts.pory"
	trainerbattle_no_intro TRAINER_BIANCA, KroniiCeremonyMain_Text_EngineerDefeat
# 281 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_EngineerName
# 282 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_EngineerRecruit
# 283 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 284 "data/maps/KroniiCeremonyMain/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 285 "data/maps/KroniiCeremonyMain/scripts.pory"
	clearflag FLAG_CEREMONY_INSIDE_ENGINEER
# 286 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_ENGINEER
# 287 "data/maps/KroniiCeremonyMain/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 288 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_Engineer_2:
# 274 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_EngineerRejected
# 275 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 276 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Hiker::
# 293 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 294 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 295 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_HikerName
# 296 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_HikerNormal, MSGBOX_YESNO
# 297 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_Hiker_2
# 303 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 304 "data/maps/KroniiCeremonyMain/scripts.pory"
	trainerbattle_no_intro TRAINER_BRICE, KroniiCeremonyMain_Text_HikerDefeat
# 305 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_HikerName
# 306 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_HikerRecruit
# 307 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 308 "data/maps/KroniiCeremonyMain/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 309 "data/maps/KroniiCeremonyMain/scripts.pory"
	clearflag FLAG_CEREMONY_INSIDE_HIKER
# 310 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_HIKER
# 311 "data/maps/KroniiCeremonyMain/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 312 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_Hiker_2:
# 298 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_EngineerRejected
# 299 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 300 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_CyanFan::
# 317 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 318 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 319 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Cyan
# 320 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CyanNormal
# 321 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 322 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Kronie1::
# 327 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 328 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 329 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_Kronie1Name
# 330 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_Kronie1Normal
# 331 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 332 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Kronie2::
# 337 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 338 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 339 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_Kronie2Name
# 340 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_Kronie2Normal
# 341 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 342 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Kronie3::
# 347 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 348 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 349 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_Kronie3Name
# 350 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_Kronie3Normal
# 351 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 352 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_CaveGuard::
# 357 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 358 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 359 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_CaveGuardName
# 360 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CaveGuardNormal
# 361 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 362 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_JuiceSeller::
# 367 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 368 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 369 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_JuiceSellerName
# 370 "data/maps/KroniiCeremonyMain/scripts.pory"
	message KroniiCeremonyMain_Text_JuiceSellerNormal
# 371 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmessage
# 372 "data/maps/KroniiCeremonyMain/scripts.pory"
	pokemart KroniiCeremonyMain_Mart_JuiceSellerMart
# 373 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_JuiceSellerThankYou
# 374 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 375 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_CaveSign::
# 380 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CaveSign, MSGBOX_SIGN
	end


KroniiCeremonyMain_EventScript_KroniiCeremonySign::
# 385 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiCeremonySign, MSGBOX_SIGN
	end


	.align 2
# 389 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Mart_JuiceSellerMart:
# 390 "data/maps/KroniiCeremonyMain/scripts.pory"
	.2byte ITEM_BERRY_JUICE
	.2byte ITEM_NONE

# 393 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_KroniiIntroMove:
# 394 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 394 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 394 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 394 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 394 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 394 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 394 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 394 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 395 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 395 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
	step_end

# 398 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_GigiIntroMove:
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 399 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 400 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 400 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 400 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
	step_end

# 403 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_KroniiIntroGo:
# 404 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 404 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 405 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 405 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 405 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 405 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 405 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 405 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 405 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 405 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
	step_end

# 408 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_PlayerDoorWay:
# 409 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 410 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_right
	step_end

# 413 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_GigiMoveToDoor:
# 414 "data/maps/KroniiCeremonyMain/scripts.pory"
	delay_8
# 415 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 416 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 417 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_up
	step_end

# 420 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_GigiMoveToStage:
# 421 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 421 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 421 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 421 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 421 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 422 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 423 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_diag_northeast
# 424 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 424 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 424 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 424 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
	step_end

# 427 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_CameraPanToAudience:
# 428 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 428 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 428 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 428 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 428 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
	step_end

# 431 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_CameraPanBackToStage:
# 432 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 432 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 432 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 432 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 432 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
	step_end

# 435 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_HikerWalkToStage:
# 436 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 436 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 436 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 436 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 436 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 437 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 438 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_diag_northwest
# 439 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 440 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 441 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 441 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 441 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 441 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 441 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 441 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 442 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
	step_end

# 445 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_EngineerWalkToStage:
# 446 "data/maps/KroniiCeremonyMain/scripts.pory"
	delay_16
# 447 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 447 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 447 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 447 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 447 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 448 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 449 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_diag_northwest
# 450 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 451 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 452 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 452 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 452 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 452 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 452 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 453 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
	step_end

# 456 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_KindlerWalkToStage:
# 457 "data/maps/KroniiCeremonyMain/scripts.pory"
	delay_16
# 457 "data/maps/KroniiCeremonyMain/scripts.pory"
	delay_16
# 458 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 458 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 458 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 458 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 458 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 459 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 460 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_diag_northwest
# 461 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 462 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 463 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 463 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 463 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 463 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 464 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
	step_end

# 467 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_HelpersStageActing:
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
# 468 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_down
	step_end

# 471 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_GigiGoInDoor:
# 472 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
	step_end

# 475 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_PlayerGoDown:
# 476 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
	step_end

KroniiCeremonyMain_Text_KroniiIntro::
# 479 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_NORMAL}Oh, Kroniichiwa! What are you doing here\n"
	.string "exactly?$"

KroniiCeremonyMain_Text_GigiIntro::
# 483 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_9}Gi Murin! You wanted some help, right\n"
	.string "Kronii?\p"
	.string "I managed to find this trainer here to\n"
	.string "help out with your ceremony here.$"

KroniiCeremonyMain_Text_KroniiIntro2::
# 487 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SERIOUS}Huh, and you think this trainer here will\n"
	.string "get my ceremony at perfect condition\l"
	.string "here?$"

KroniiCeremonyMain_Text_GigiIntro2::
# 491 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_8}Not quite. I'm having them help out by\n"
	.string "getting some people to do some extra\l"
	.string "stuff as well to make it absolutely\l"
	.string "memorable here.$"

KroniiCeremonyMain_Text_KroniiIntro3::
# 495 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SERIOUS}That's certainly a plan here, I guess.\p"
	.string "Just don't mess up anything here, I\n"
	.string "worked hard to get this all set up here\l"
	.string "for my fans.$"

KroniiCeremonyMain_Text_GigiIntro3::
# 499 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_9}Don't worry, I won't make it be a\n"
	.string "complete mess here, you know me better\l"
	.string "than that, right Kronii?$"

KroniiCeremonyMain_Text_KroniiIntro4::
# 503 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SERIOUS}Alright, I'm trusting you here then,\n"
	.string "Gigi.\p"
	.string "I need to set up right now, so just make\n"
	.string "sure whatever you do is all good over\l"
	.string "here.$"

KroniiCeremonyMain_Text_GigiGiveStartingTeam::
# 508 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_NORMAL}Oh yeah, I forgot I brought you without\n"
	.string "your usual team here, so here's a pretty\l"
	.string "basic one I managed to find here!$"

KroniiCeremonyMain_Text_YouGotStartingTeam::
# 512 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You received your stating team from\n"
	.string "Gigi Murin herself.$"

KroniiCeremonyMain_Text_GigiGoInside::
# 516 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_NORMAL}You shouldn't need anything more than\n"
	.string "this to help recruit the three people I\l"
	.string "need for this.\p"
	.string "A hiker, a kindler, and an engineer are\n"
	.string "the other three people I want to help\l"
	.string "me with this ceremony here.\p"
	.string "Don't worry about training yourself\n"
	.string "here, everything should be relatively\l"
	.string "low stakes here with trying to recruit\l"
	.string "everyone here.\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_8}Anyways, I'll be going inside if you need\n"
	.string "me, whether it'd be for healing or just\l"
	.string "getting those tips again.$"

KroniiCeremonyMain_Text_KroniiCeremonyIntro::
# 523 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_NORMAL}Kroniichiwa! Hello everyone who made it\n"
	.string "here today to my ceremony.\p"
	.string "You all know me as Ouro Kronii, the\n"
	.string "Warden of Time herself, and today, I\l"
	.string "would like to celebrate the achievement\l"
	.string "of my tenth star here.\p"
	.string "Now, without further ado-$"

KroniiCeremonyMain_Text_GigiCeremonyHoldOn::
# 529 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Hey Kronii! Guess who's here to join you\n"
	.string "for this ceremony.$"

KroniiCeremonyMain_Text_GigiCeremonyInterruption::
# 533 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_9}Gi Murin! Hello everyone, the name's Gigi\n"
	.string "Murin here, and I've come to help Kronii\l"
	.string "with her ceremony here.$"

KroniiCeremonyMain_Text_KroniiCeremonyRudelyInterrupted::
# 537 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SERIOUS}What the hell are you doing, Gigi?\p"
	.string "This is supposed to be MY ceremony\n"
	.string "here.$"

KroniiCeremonyMain_Text_GigiCeremonyCueOthers::
# 541 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_8}I thought you wanted some help getting\n"
	.string "it to work though, which is why I\l"
	.string "managed to get some other guys here.\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_NORMAL}Hit it, you three!$"

KroniiCeremonyMain_Text_KroniiCeremonySadAboutCeremony::
# 546 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SAD}No, my ceremony, the thing I planned for\n"
	.string "a while now. Gigi, why would you ruin this\l"
	.string "moment for me here?$"

KroniiCeremonyMain_Text_GigiCeremonyCheckAudience::
# 551 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_8}Hey, I mean, the audience doesn't seem\n"
	.string "like they're bothered at all here.$"

KroniiCeremonyMain_Text_CyanReaction::
# 555 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "WOOHH! YEAH, GO KRONII AND GIGI!\p"
	.string "YOU TWO MAKE THIS CEREMONY EPIC HERE!$"

KroniiCeremonyMain_Text_Kronie2Reaction::
# 560 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "I won't lie, this certainly is more\n"
	.string "exciting here than what I was gonna do\l"
	.string "originally.$"

KroniiCeremonyMain_Text_GigiCeremonySeeAudience::
# 564 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_8}See, the audience loves what you're\n"
	.string "doing here right now.\p"
	.string "I told you I wouldn't just ruin it for\n"
	.string "you here.$"

KroniiCeremonyMain_Text_KroniiCeremonyApologizeGigi::
# 569 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SAD}I guess I judged you too quick here\n"
	.string "with what you were doing.\p"
	.string "I'm sorry I thought you tried to ruin my\n"
	.string "ceremony here, it's just that I was\l"
	.string "looking forwards to it for a while now.$"

KroniiCeremonyMain_Text_GigiCeremonyAcceptApology::
# 574 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_8}It's all good Kronii, it's your event\n"
	.string "after all.\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_8}Now, let's just enjoy the music here for\n"
	.string "this ceremony here.$"

KroniiCeremonyMain_Text_NoWaterGuy::
# 579 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You're wondering where the water is at?\p"
	.string "Sorry bud, our organizer here banned\n"
	.string "straight up water here after the last\l"
	.string "incident with a water cooler.\p"
	.string "Safe to say we don't want to risk\n"
	.string "anything like that again with our\l"
	.string "organizer Kronii here.$"

KroniiCeremonyMain_Text_SkualperGuyName::
# 585 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Skualper$"

KroniiCeremonyMain_Text_KindlerName::
# 589 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kindler$"

KroniiCeremonyMain_Text_EngineerName::
# 593 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Engineer$"

KroniiCeremonyMain_Text_HikerName::
# 597 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Hiker$"

KroniiCeremonyMain_Text_Kronie1Name::
# 601 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Darkie$"

KroniiCeremonyMain_Text_Kronie2Name::
# 605 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Napper$"

KroniiCeremonyMain_Text_Kronie3Name::
# 609 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Machro$"

KroniiCeremonyMain_Text_CaveGuardName::
# 613 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Cave Guard$"

KroniiCeremonyMain_Text_JuiceSellerName::
# 617 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Juicer Seller$"

KroniiCeremonyMain_Text_SkualperGuyIntro::
# 621 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Hey you there! You with the blue there!\p"
	.string "Do you want a ticket for this exclusive\n"
	.string "event here?\p"
	.string "I happen to have one here, but I'm not\n"
	.string "really interested in this lame person\l"
	.string "that this event is about.\p"
	.string "No point in joining this sad community,\n"
	.string "I got nothing to gain by doing so after\l"
	.string "all.$"

KroniiCeremonyMain_Text_SkualperGuySwindle::
# 628 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "But that's just me here, what do you say\n"
	.string "kid?\p"
	.string "Do you want this exclusive ticket here?$"

KroniiCeremonyMain_Text_SkualperGuyDenied::
# 633 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "So it's like that, huh?\p"
	.string "Just gonna get a ticket the old\n"
	.string "fashionhed way, you think?\p"
	.string "Well, let's see how that will work out for\n"
	.string "you, if it even does at all.\p"
	.string "I'll still be here though if you change\n"
	.string "your mind.$"

KroniiCeremonyMain_Text_SkualperGuyConvinced::
# 640 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Sweet, it'll be ¥10000 if you can get\n"
	.string "that for me.$"

KroniiCeremonyMain_Text_SkualperGuyNotEnoughMoney::
# 644 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Darn. Guess you won't do for helping me\n"
	.string "out- I mean getting this sweet\l"
	.string "opportunity for this event here.\p"
	.string "Come back once you have enough for\n"
	.string "this ticket here.\p"
	.string "Oh, and if you can, ignore the lack of\n"
	.string "water here as well, I had nothing to\l"
	.string "with it, I swear.$"

KroniiCeremonyMain_Text_KindlerNormal::
# 650 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Oh hey, don't mind me trying to hone in\n"
	.string "my skills here with this tree.\p"
	.string "What's that, you need me for a ceremony\n"
	.string "here?$"

KroniiCeremonyMain_Text_KindlerRejected::
# 655 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Alright then, let me just continue on\n"
	.string "with this tree here then.$"

KroniiCeremonyMain_Text_EngineerNormal::
# 659 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Have you seen this lack of water here?\p"
	.string "It's absurd, it's like somebody just\n"
	.string "drained it entirely before this event\l"
	.string "was going to happen.\p"
	.string "Huh, you need me to help out with this\n"
	.string "event here?$"

KroniiCeremonyMain_Text_EngineerRejected::
# 665 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Weird, but alright, I just wanted to\n"
	.string "know who or what caused this lake to be\l"
	.string "like such.$"

KroniiCeremonyMain_Text_HikerNormal::
# 669 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "This certainly doesn't seem natural at\n"
	.string "all, this once lake here.\p"
	.string "I bet whoever came for this event here\n"
	.string "is certainly disappointed with the lack\l"
	.string "of water in this place.\p"
	.string "Oh, you're asking for my assistance for\n"
	.string "this event here?$"

KroniiCeremonyMain_Text_HikerRejected::
# 675 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "I'll just be doing my thing here then,\n"
	.string "wondering what happened to the water\l"
	.string "here.$"

KroniiCeremonyMain_Text_KindlerDefeat::
# 679 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Man, you've burnt me out here.$"

KroniiCeremonyMain_Text_EngineerDefeat::
# 683 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Jeez, I'm gonna need a drink to cool me down again.$"

KroniiCeremonyMain_Text_HikerDefeat::
# 687 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Huh, you're some trainer here alright.$"

KroniiCeremonyMain_Text_KindlerRecruit::
# 691 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Well, you mentioned you wanting me to\n"
	.string "join someone named Gigi, right?\p"
	.string "I guess if she can help me out with\n"
	.string "these skills here, then I'll help her out\l"
	.string "with what she needs then.$"

KroniiCeremonyMain_Text_EngineerRecruit::
# 696 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "I've been beat now, huh?\p"
	.string "In that case then, I guess I'll have to\n"
	.string "hear you out on this case then.\p"
	.string "So this Gigi needs my help for something\n"
	.string "here, huh?\p"
	.string "I guess I can see what she needs me to\n"
	.string "do then.$"

KroniiCeremonyMain_Text_HikerRecruit::
# 703 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "So what's the deal with this Gigi person,\n"
	.string "then?\p"
	.string "She needs me to help out with this\n"
	.string "ceremony here, huh?\p"
	.string "I guess I got nothing else better to do\n"
	.string "then, that and I don't want to be left\l"
	.string "out of this here.$"

KroniiCeremonyMain_Text_CyanNormal::
# 709 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "HOWDY!!\p"
	.string "I can't believe I got invited to this\n"
	.string "event here by both Kronii and Gigi\l"
	.string "herself, isn't that cool?\p"
	.string "It's like I get to see them in their own\n"
	.string "private concert here.\p"
	.string "I think it has to do with something\n"
	.string "about her getting a tenth star or\l"
	.string "something, but I'm here for both her and\l"
	.string "Gigi.$"

KroniiCeremonyMain_Text_Kronie1Normal::
# 715 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kronii's pretty cool, I won't lie.\p"
	.string "She may not be the best all around, but\n"
	.string "you can tell she tries with what she can\l"
	.string "do.$"

KroniiCeremonyMain_Text_Kronie2Normal::
# 720 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You know, I honestly didn't expect\n"
	.string "being here originally.\p"
	.string "I was gonna play some DELTARUNE\n"
	.string "considering the newly released\l"
	.string "chapters 3 and 4 here.\p"
	.string "But you know, I had the chance to join\n"
	.string "this ceremony hosted by Kronii herself,\l"
	.string "and I couldn't resist coming here.\p"
	.string "It's a shame I'm missing out a bit on the\n"
	.string "lore of DELTARUNE, but hey, maybe Kronii\l"
	.string "is related to it, so I'll stay here.$"

KroniiCeremonyMain_Text_Kronie3Normal::
# 727 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You know, I do wonder what happened to\n"
	.string "the lake that was supposed to be here.\p"
	.string "It feels like somebody just took all the\n"
	.string "water away for some reason.\p"
	.string "It's a bit sad really, how the lake here\n"
	.string "would make this ceremony feel better.$"

KroniiCeremonyMain_Text_CaveGuardNormal::
# 733 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Halt! You don't have any authority to\n"
	.string "go inside currently.\p"
	.string "The warden told me anyone who knows\n"
	.string "about this event must stay until it is\l"
	.string "over.\p"
	.string "You don't seem like the warden herself,\n"
	.string "so I can't allow you to go further right\l"
	.string "now unfortunately.$"

KroniiCeremonyMain_Text_JuiceSellerNormal::
# 739 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Hey, I'm the Juice Seller here.\p"
	.string "For some reason, all the natural water\n"
	.string "in this place went away for some weird\l"
	.string "reason.\p"
	.string "Fortunately, I've brought over the next\n"
	.string "best thing, natural Berry Juice, if you\l"
	.string "want to buy some of course.$"

KroniiCeremonyMain_Text_JuiceSellerThankYou::
# 745 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Thank you for at least checking out my\n"
	.string "shop here.$"

KroniiCeremonyMain_Text_CantGoToStage::
# 749 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Seems like you can't just go on stage\n"
	.string "alone with the people here already.$"

KroniiCeremonyMain_Text_CaveSign::
# 753 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Exit over this cave here$"

KroniiCeremonyMain_Text_KroniiCeremonySign::
# 757 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kronii's Official Tenth Star Ceremony\p"
	.string "Invitation Only$"
