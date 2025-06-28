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
# 16 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 17 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	call Common_EventScript_OutOfCenterPartyHeal
# 18 "data/maps/KroniiCeremonyIndoor/scripts.pory"
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
	closemessage
# 13 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_EventScript_GigiReady::
# 23 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername gText_Gigi
# 24 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_GigiReady, MSGBOX_YESNO
# 25 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyIndoor_EventScript_GigiReady_2
# 30 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 31 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setvar VAR_HOUSE_LIKE_CARPET_STATE, 2
# 32 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end

KroniiCeremonyIndoor_EventScript_GigiReady_2:
# 26 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 27 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_EventScript_Kindler::
# 37 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	lock
# 38 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	faceplayer
# 39 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername KroniiCeremonyIndoor_Text_KindlerName
# 40 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_KindlerNormal
# 41 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 42 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_EventScript_Engineer::
# 47 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	lock
# 48 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	faceplayer
# 49 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername KroniiCeremonyIndoor_Text_EngineerName
# 50 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_EngineerNormal
# 51 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 52 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_EventScript_Hiker::
# 57 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	lock
# 58 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	faceplayer
# 59 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	setspeakername KroniiCeremonyIndoor_Text_HikerName
# 60 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	msgbox KroniiCeremonyIndoor_Text_KindlerNormal
# 61 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	closemessage
# 62 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	release
	end


KroniiCeremonyIndoor_Text_GigiNormal::
# 66 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Gigi asks if you want to be healed.$"

KroniiCeremonyIndoor_Text_GigiReady::
# 70 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Gigi knows you got everyone now.$"

KroniiCeremonyIndoor_Text_KindlerNormal::
# 74 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Kindler says something here.$"

KroniiCeremonyIndoor_Text_EngineerNormal::
# 78 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Engineer says something here.$"

KroniiCeremonyIndoor_Text_HikerNormal::
# 82 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Hiker says something here.$"

KroniiCeremonyIndoor_Text_KindlerName::
# 86 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Kindler$"

KroniiCeremonyIndoor_Text_EngineerName::
# 90 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Engineer$"

KroniiCeremonyIndoor_Text_HikerName::
# 94 "data/maps/KroniiCeremonyIndoor/scripts.pory"
	.string "Hiker$"
