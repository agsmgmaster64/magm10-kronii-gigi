KroniiCeremonyMain_MapScripts::
# 2 "data/maps/KroniiCeremonyMain/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, KroniiCeremonyMain_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

KroniiCeremonyMain_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 3 "data/maps/KroniiCeremonyMain/scripts.pory"
	map_script_2 VAR_HOUSE_LIKE_CARPET_STATE, 0, KroniiCeremonyMain_EventScript_KroniiGigiIntroduction
	.2byte 0


KroniiCeremonyMain_EventScript_KroniiGigiIntroduction::
# 8 "data/maps/KroniiCeremonyMain/scripts.pory"
	lockall
# 9 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, KroniiCeremonyMain_Movement_KroniiIntroMove
# 10 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, KroniiCeremonyMain_Movement_GigiIntroMove
# 11 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 12 "data/maps/KroniiCeremonyMain/scripts.pory"
	playse SE_PIN
# 13 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_ExclamationMark
# 14 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 15 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitse
# 16 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, Common_Movement_WalkInPlaceFasterRight
# 17 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, Common_Movement_WalkInPlaceFasterLeft
# 18 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 19 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 20 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiIntro
# 21 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 22 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_KRONII, KroniiCeremonyMain_Movement_KroniiIntroGo
# 23 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_KRONII
# 24 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_KRONII
# 25 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Gigi
# 26 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_GigiGoInside
# 27 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 28 "data/maps/KroniiCeremonyMain/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 29 "data/maps/KroniiCeremonyMain/scripts.pory"
	givemon SPECIES_CHIBI_BIJOU, 10
# 30 "data/maps/KroniiCeremonyMain/scripts.pory"
	givemon SPECIES_CHIBI_MINORIKO_SANNI, 10
# 31 "data/maps/KroniiCeremonyMain/scripts.pory"
	givemon SPECIES_CHIBI_MARISA, 10
# 32 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_PLAYER, KroniiCeremonyMain_Movement_PlayerDoorWay
# 33 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, KroniiCeremonyMain_Movement_GigiMoveToDoor
# 34 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 35 "data/maps/KroniiCeremonyMain/scripts.pory"
	opendoor 30, 31
# 36 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitdooranim
# 37 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_CEREMONY_GIGI, KroniiCeremonyMain_Movement_GigiGoInDoor
# 38 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_CEREMONY_GIGI
# 39 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_GIGI
# 40 "data/maps/KroniiCeremonyMain/scripts.pory"
	closedoor 30, 31
# 41 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitdooranim
# 42 "data/maps/KroniiCeremonyMain/scripts.pory"
	clearflag FLAG_CEREMONY_INSIDE_GIGI
# 43 "data/maps/KroniiCeremonyMain/scripts.pory"
	setvar VAR_HOUSE_LIKE_CARPET_STATE, 1
# 44 "data/maps/KroniiCeremonyMain/scripts.pory"
	releaseall
	end


KroniiCeremonyMain_EventScript_CantGoToStage::
# 49 "data/maps/KroniiCeremonyMain/scripts.pory"
	lockall
# 50 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CantGoToStage
# 51 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 52 "data/maps/KroniiCeremonyMain/scripts.pory"
	applymovement LOCALID_PLAYER, KroniiCeremonyMain_Movement_PlayerGoDown
# 53 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmovement LOCALID_PLAYER
# 54 "data/maps/KroniiCeremonyMain/scripts.pory"
	releaseall
	end


KroniiCeremonyMain_EventScript_SuspiciousGuy::
# 59 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 60 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 61 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_SkualperGuyName
# 62 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuyIntro
# 63 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuySwindle, MSGBOX_YESNO
# 64 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_SuspiciousGuy_2
# 69 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_SuspiciousGuy_2:
# 65 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuyDenied
# 66 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Kindler::
# 74 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 75 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 76 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_KindlerName
# 77 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KindlerNormal, MSGBOX_YESNO
# 78 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_Kindler_2
# 83 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 84 "data/maps/KroniiCeremonyMain/scripts.pory"
	trainerbattle_no_intro TRAINER_HAYDEN, KroniiCeremonyMain_Text_KindlerDefeat
# 85 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_KindlerName
# 86 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KindlerRecruit
# 87 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 88 "data/maps/KroniiCeremonyMain/scripts.pory"
	clearflag FLAG_CEREMONY_INSIDE_KINDLER
# 89 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_KINDLER
# 90 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_Kindler_2:
# 79 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 80 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Engineer::
# 95 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 96 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 97 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_EngineerName
# 98 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_EngineerNormal, MSGBOX_YESNO
# 99 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_Engineer_2
# 104 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 105 "data/maps/KroniiCeremonyMain/scripts.pory"
	trainerbattle_no_intro TRAINER_BIANCA, KroniiCeremonyMain_Text_EngineerDefeat
# 106 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_EngineerName
# 107 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_EngineerRecruit
# 108 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 109 "data/maps/KroniiCeremonyMain/scripts.pory"
	clearflag FLAG_CEREMONY_INSIDE_ENGINEER
# 110 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_ENGINEER
# 111 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_Engineer_2:
# 100 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 101 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Hiker::
# 116 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 117 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 118 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_HikerName
# 119 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_HikerNormal, MSGBOX_YESNO
# 120 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_Hiker_2
# 125 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 126 "data/maps/KroniiCeremonyMain/scripts.pory"
	trainerbattle_no_intro TRAINER_BRICE, KroniiCeremonyMain_Text_HikerDefeat
# 127 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_HikerName
# 128 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_HikerRecruit
# 129 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 130 "data/maps/KroniiCeremonyMain/scripts.pory"
	clearflag FLAG_CEREMONY_INSIDE_HIKER
# 131 "data/maps/KroniiCeremonyMain/scripts.pory"
	removeobject LOCALID_CEREMONY_HIKER
# 132 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_Hiker_2:
# 121 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 122 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_CyanFan::
# 137 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 138 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 139 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Cyan
# 140 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CyanNormal
# 141 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 142 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Kronie1::
# 147 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 148 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 149 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_Kronie1Name
# 150 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_Kronie1Normal
# 151 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 152 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Kronie2::
# 157 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 158 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 159 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_Kronie2Name
# 160 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_Kronie2Normal
# 161 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 162 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_Kronie3::
# 167 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 168 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 169 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_Kronie3Name
# 170 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_Kronie3Normal
# 171 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 172 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_CaveGuard::
# 177 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 178 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 179 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_CaveGuardName
# 180 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CaveGuardNormal
# 181 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 182 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_JuiceSeller::
# 187 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 188 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 189 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_JuiceSellerName
# 190 "data/maps/KroniiCeremonyMain/scripts.pory"
	message KroniiCeremonyMain_Text_JuiceSellerNormal
# 191 "data/maps/KroniiCeremonyMain/scripts.pory"
	waitmessage
# 192 "data/maps/KroniiCeremonyMain/scripts.pory"
	pokemart KroniiCeremonyMain_Mart_JuiceSellerMart
# 193 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 194 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_CaveSign::
# 199 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_CaveSign, MSGBOX_SIGN
	end


KroniiCeremonyMain_EventScript_KroniiCeremonySign::
# 204 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiCeremonySign, MSGBOX_SIGN
	end


	.align 2
# 208 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Mart_JuiceSellerMart:
# 209 "data/maps/KroniiCeremonyMain/scripts.pory"
	.2byte ITEM_BERRY_JUICE
	.2byte ITEM_NONE

# 212 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_KroniiIntroMove:
# 213 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 213 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 213 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 213 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 213 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 213 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 213 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 213 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 214 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 214 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
	step_end

# 217 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_GigiIntroMove:
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 218 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_right
# 219 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 219 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 219 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
	step_end

# 222 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_KroniiIntroGo:
# 223 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 223 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
# 224 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 224 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 224 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 224 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 224 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 224 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 224 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 224 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
	step_end

# 227 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_PlayerDoorWay:
# 228 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 229 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_right
	step_end

# 232 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_GigiMoveToDoor:
# 233 "data/maps/KroniiCeremonyMain/scripts.pory"
	delay_8
# 234 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
# 235 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_left
# 236 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_in_place_up
	step_end

# 239 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_GigiGoInDoor:
# 240 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_up
	step_end

# 243 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_Movement_PlayerGoDown:
# 244 "data/maps/KroniiCeremonyMain/scripts.pory"
	walk_down
	step_end

KroniiCeremonyMain_Text_KroniiIntro::
# 247 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kronii and Gigi say something here,\n"
	.string "please add some additional movements\l"
	.string "for dialog as well.$"

KroniiCeremonyMain_Text_GigiGoInside::
# 251 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Gigi says something about going inside.$"

KroniiCeremonyMain_Text_NoWaterGuy::
# 255 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You're wondering where the water is at?\p"
	.string "Sorry bud, our organizer here banned\n"
	.string "straight up water here after the last\l"
	.string "incident with a water cooler.\p"
	.string "Safe to say we don't want to risk\n"
	.string "anything like that again with our\l"
	.string "organizer Kronii here.$"

KroniiCeremonyMain_Text_SkualperGuyName::
# 261 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Skualper$"

KroniiCeremonyMain_Text_KindlerName::
# 265 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kindler$"

KroniiCeremonyMain_Text_EngineerName::
# 269 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Engineer$"

KroniiCeremonyMain_Text_HikerName::
# 273 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Hiker$"

KroniiCeremonyMain_Text_Kronie1Name::
# 277 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kronie 1$"

KroniiCeremonyMain_Text_Kronie2Name::
# 281 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kronie 2$"

KroniiCeremonyMain_Text_Kronie3Name::
# 285 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kronie 3$"

KroniiCeremonyMain_Text_CaveGuardName::
# 289 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Cave Guard$"

KroniiCeremonyMain_Text_JuiceSellerName::
# 293 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Juicer Seller$"

KroniiCeremonyMain_Text_SkualperGuyIntro::
# 297 "data/maps/KroniiCeremonyMain/scripts.pory"
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
# 304 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "But that's just me here, what do you say\n"
	.string "kid?\p"
	.string "Do you want this exclusive ticket here?$"

KroniiCeremonyMain_Text_SkualperGuyDenied::
# 309 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "So it's like that, huh?\p"
	.string "Just gonna get a ticket the old\n"
	.string "fashionhed way, you think?\p"
	.string "Well, let's see how that will work out for\n"
	.string "you, if it even does at all.\p"
	.string "I'll still be here though if you change\n"
	.string "your mind.$"

KroniiCeremonyMain_Text_KindlerNormal::
# 316 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You ask Kindler to battle.$"

KroniiCeremonyMain_Text_EngineerNormal::
# 320 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You ask Engineer to battle.$"

KroniiCeremonyMain_Text_HikerNormal::
# 324 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You ask Hiker to battle.$"

KroniiCeremonyMain_Text_KindlerDefeat::
# 328 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Defeat Text Kindler$"

KroniiCeremonyMain_Text_EngineerDefeat::
# 332 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Defeat Text Engineer$"

KroniiCeremonyMain_Text_HikerDefeat::
# 336 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Defeat Text Hiker$"

KroniiCeremonyMain_Text_KindlerRecruit::
# 340 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kindler recruited.$"

KroniiCeremonyMain_Text_EngineerRecruit::
# 344 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Engineer recruited.$"

KroniiCeremonyMain_Text_HikerRecruit::
# 348 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Hiker recruited.$"

KroniiCeremonyMain_Text_CyanNormal::
# 352 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "This fan says something interesting\n"
	.string "about Kronii's ceremony.$"

KroniiCeremonyMain_Text_Kronie1Normal::
# 356 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "This fan says something about Kronii\n"
	.string "herself.$"

KroniiCeremonyMain_Text_Kronie2Normal::
# 360 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "This fan says something about Kronii\n"
	.string "herself.$"

KroniiCeremonyMain_Text_Kronie3Normal::
# 364 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "This fan says something about Kronii\n"
	.string "herself.$"

KroniiCeremonyMain_Text_CaveGuardNormal::
# 368 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Cave Guard says something here.$"

KroniiCeremonyMain_Text_JuiceSellerNormal::
# 372 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Juice Seller says something here.$"

KroniiCeremonyMain_Text_CantGoToStage::
# 376 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Cannot go to stage yet.$"

KroniiCeremonyMain_Text_CaveSign::
# 380 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Cave Sign$"

KroniiCeremonyMain_Text_KroniiCeremonySign::
# 384 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kronii Ceremony Sign$"
