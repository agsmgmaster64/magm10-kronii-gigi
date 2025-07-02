KroniiCeremonyIndoor_MapScripts::
	.byte 0


KroniiCeremonyIndoor_EventScript_Gigi::
# 4 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	lock
# 5 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	faceplayer
# 6 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	goto_if_set FLAG_CEREMONY_OUTSIDE_HIKER, KroniiCeremonyIndoor_EventScript_Gigi_4
KroniiCeremonyIndoor_EventScript_Gigi_1:
# 9 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername gText_Gigi
# 10 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_GigiNormal, MSGBOX_YESNO
# 11 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyIndoor_EventScript_Gigi_9
# 17 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 18 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 19 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername gText_Gigi
# 20 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_GigiNormal2
# 21 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 22 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername gText_Gigi
# 23 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_GigiRemember
# 24 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 25 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end

KroniiCeremonyIndoor_EventScript_Gigi_2:
# 7 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	goto KroniiCeremonyIndoor_EventScript_GigiReady
	goto KroniiCeremonyIndoor_EventScript_Gigi_1

KroniiCeremonyIndoor_EventScript_Gigi_3:
# 6 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	goto_if_set FLAG_CEREMONY_OUTSIDE_KINDLER, KroniiCeremonyIndoor_EventScript_Gigi_2
	goto KroniiCeremonyIndoor_EventScript_Gigi_1

KroniiCeremonyIndoor_EventScript_Gigi_4:
# 6 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	goto_if_set FLAG_CEREMONY_OUTSIDE_ENGINEER, KroniiCeremonyIndoor_EventScript_Gigi_3
	goto KroniiCeremonyIndoor_EventScript_Gigi_1

KroniiCeremonyIndoor_EventScript_Gigi_9:
# 12 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_GigiRemember
# 13 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 14 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_EventScript_GigiReady::
# 30 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername gText_Gigi
# 31 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_GigiReady, MSGBOX_YESNO
# 32 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyIndoor_EventScript_GigiReady_2
# 37 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 38 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setvar VAR_HOUSE_LIKE_CARPET_STATE, 2
# 39 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setflag FLAG_SPAWN_INVISIBLE
# 40 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setflag FLAG_CEREMONU_OUTSIDE_GUARD
# 41 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	clearflag FLAG_CEREMONY_OUTSIDE_KRONII
# 42 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	warp MAP_KRONII_CEREMONY_MAIN, WARP_ID_NONE, 17, 11
# 43 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end

KroniiCeremonyIndoor_EventScript_GigiReady_2:
# 33 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 34 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_EventScript_Kindler::
# 48 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	lock
# 49 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	faceplayer
# 50 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername KroniiCeremonyIndoor_Text_KindlerName
# 51 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_KindlerNormal
# 52 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 53 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_EventScript_Engineer::
# 58 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	lock
# 59 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	faceplayer
# 60 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername KroniiCeremonyIndoor_Text_EngineerName
# 61 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_EngineerNormal
# 62 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 63 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_EventScript_Hiker::
# 68 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	lock
# 69 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	faceplayer
# 70 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername KroniiCeremonyIndoor_Text_HikerName
# 71 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_KindlerNormal
# 72 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 73 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_Text_GigiNormal::
# 77 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_NORMAL}What's up, you need a heal here?{DESTROY_MUGSHOT}$"

KroniiCeremonyIndoor_Text_GigiNormal2::
# 81 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_9}There you go, a complete heal from Gigi\n"
	.string "Murin herself.$"

KroniiCeremonyIndoor_Text_GigiRemember::
# 85 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_9}Just remember you need to get me an\n"
	.string "engineer, hiker, and kindler here for\l"
	.string "help with Kronii.$"

KroniiCeremonyIndoor_Text_GigiReady::
# 89 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_NORMAL}You got the three people I need for\n"
	.string "Kronii's ceremony here.\p"
	.string "Shall we continue on with the plan\n"
	.string "then?{DESTROY_MUGSHOT}$"

KroniiCeremonyIndoor_Text_KindlerNormal::
# 94 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Hey, I know you saw me trying to burn\n"
	.string "down that tree earlier.\p"
	.string "I just want to say that it was kinda\n"
	.string "stupid in hindsight considering the\l"
	.string "recent lack of water in this place here.\p"
	.string "I didn't know what to do until you got\n"
	.string "me into this gig here, which I think\l"
	.string "should bring my skills out better here.$"

KroniiCeremonyIndoor_Text_EngineerNormal::
# 100 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Something about this sink here, it tells\n"
	.string "me that whoever cares for it hasn't\l"
	.string "taken care of it.\p"
	.string "You can't even get water out of it\n"
	.string "anymore, it doesn't even work.$"

KroniiCeremonyIndoor_Text_HikerNormal::
# 105 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Man, some of these books here are a\n"
	.string "good read for knowledge here.\p"
	.string "Take this for example, 72 Uses for\n"
	.string "Snails.\p"
	.string "Who knew those slimy critters would be\n"
	.string "useful for so many things?$"

KroniiCeremonyIndoor_Text_KindlerName::
# 111 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Kindler$"

KroniiCeremonyIndoor_Text_EngineerName::
# 115 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Engineer$"

KroniiCeremonyIndoor_Text_HikerName::
# 119 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Hiker$"
