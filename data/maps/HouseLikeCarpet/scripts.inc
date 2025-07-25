HouseLikeCarpet_MapScripts::
	.byte 0


HouseLikeCarpet_Event_LostGarbage::
# 4 "data/maps/HouseLikeCarpet/scripts.pory"
	lock
# 5 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_Garbage
# 6 "data/maps/HouseLikeCarpet/scripts.pory"
	release
	end


HouseLikeCarpet_Event_GigiStanding::
# 11 "data/maps/HouseLikeCarpet/scripts.pory"
	lock
# 12 "data/maps/HouseLikeCarpet/scripts.pory"
	faceplayer
# 13 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Gigi
# 14 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiWantToFollow, MSGBOX_YESNO
# 15 "data/maps/HouseLikeCarpet/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq HouseLikeCarpet_Event_GigiStanding_2
HouseLikeCarpet_Event_GigiStanding_1:
# 18 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiAwwMan
# 19 "data/maps/HouseLikeCarpet/scripts.pory"
	release
	end

HouseLikeCarpet_Event_GigiStanding_2:
# 16 "data/maps/HouseLikeCarpet/scripts.pory"
	goto HouseLikeCarpet_Event_GigiAcceptFollow
	goto HouseLikeCarpet_Event_GigiStanding_1


HouseLikeCarpet_Event_GigiAcceptFollow::
# 24 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiYayFollow
# 25 "data/maps/HouseLikeCarpet/scripts.pory"
	setfollowernpc LOCALID_HOUSE_GIGI, FOLLOWER_NPC_FLAG_ALL_LAND, HouseLikeCarpet_Event_GigiFollower, PARTNER_GIGI
# 26 "data/maps/HouseLikeCarpet/scripts.pory"
	release
	end


HouseLikeCarpet_Event_GigiFollower::
# 31 "data/maps/HouseLikeCarpet/scripts.pory"
	lock
# 32 "data/maps/HouseLikeCarpet/scripts.pory"
	faceplayer
# 33 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Gigi
# 34 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiFollowing, MSGBOX_YESNO
# 35 "data/maps/HouseLikeCarpet/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq HouseLikeCarpet_Event_GigiFollower_2
HouseLikeCarpet_Event_GigiFollower_1:
# 38 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiForYou
# 39 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 40 "data/maps/HouseLikeCarpet/scripts.pory"
	release
	end

HouseLikeCarpet_Event_GigiFollower_2:
# 36 "data/maps/HouseLikeCarpet/scripts.pory"
	goto HouseLikeCarpet_Event_CallKronii
	goto HouseLikeCarpet_Event_GigiFollower_1


HouseLikeCarpet_Event_GigiBoatGoesBinted::
# 45 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 46 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Gigi
# 47 "data/maps/HouseLikeCarpet/scripts.pory"
	playtrainervoice TRAINER_VOICE_GIGI, 1
# 48 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiBogosBinted
# 49 "data/maps/HouseLikeCarpet/scripts.pory"
	waitmoncry
# 50 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 51 "data/maps/HouseLikeCarpet/scripts.pory"
	release
	end


HouseLikeCarpet_Event_CallKronii::
# 56 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 57 "data/maps/HouseLikeCarpet/scripts.pory"
	playse SE_POKENAV_CALL
# 58 "data/maps/HouseLikeCarpet/scripts.pory"
	waitse
# 59 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Kronii
# 60 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_KroniiHeyaGigi
# 61 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 62 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Gigi
# 63 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiMetalCapLie
# 64 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 65 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Kronii
# 66 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_KroniiDang
# 67 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 68 "data/maps/HouseLikeCarpet/scripts.pory"
	playse SE_POKENAV_HANG_UP
# 69 "data/maps/HouseLikeCarpet/scripts.pory"
	waitse
# 70 "data/maps/HouseLikeCarpet/scripts.pory"
	release
	end


HouseLikeCarpet_Event_KroniiDeltarune::
# 75 "data/maps/HouseLikeCarpet/scripts.pory"
	lock
# 76 "data/maps/HouseLikeCarpet/scripts.pory"
	faceplayer
# 77 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Kronii
# 78 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_KroniiWhatsUpGigi
# 79 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 80 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Gigi
# 81 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiDeltaruneTomorrow
# 82 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 83 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Kronii
# 84 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_KroniiWaitTomorrow
# 85 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 86 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Gigi
# 87 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_GigiInDeltarune
# 88 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 89 "data/maps/HouseLikeCarpet/scripts.pory"
	setspeakername gText_Kronii
# 90 "data/maps/HouseLikeCarpet/scripts.pory"
	msgbox HouseLikeCarpet_Text_KroniiCanIBeInIt
# 91 "data/maps/HouseLikeCarpet/scripts.pory"
	closemessage
# 92 "data/maps/HouseLikeCarpet/scripts.pory"
	release
	end


HouseLikeCarpet_Text_GigiWantToFollow::
# 96 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "Yo, mind if I follow you here?$"

HouseLikeCarpet_Text_GigiAwwMan::
# 100 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "Aww, man. But it would be pretty nice.$"

HouseLikeCarpet_Text_GigiYayFollow::
# 104 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "Yay, I get to follow you around!$"

HouseLikeCarpet_Text_GigiFollowing::
# 108 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_NORMAL}Hey, should I call Kronii right now?{DESTROY_MUGSHOT}$"

HouseLikeCarpet_Text_GigiForYou::
# 112 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_NORMAL}Aww, but it's just for you, {PLAYER}.$"

HouseLikeCarpet_Text_GigiBogosBinted::
# 116 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_HAPPY}Boat goes Binted?$"

HouseLikeCarpet_Text_KroniiHeyaGigi::
# 120 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_HAPPY}Heya, what's up Gigi, you need me for\n"
	.string "something?\p"
	.string "I was just about to go skydiving with\n"
	.string "just a metal cap here.$"

HouseLikeCarpet_Text_GigiMetalCapLie::
# 125 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_ALT_9}Hey Kronii, did you know that the metal\n"
	.string "cap doesn't actually make you\l"
	.string "invincible when using it?\p"
	.string "It doesn't even protect you from fall\n"
	.string "damage at all!$"

HouseLikeCarpet_Text_KroniiDang::
# 130 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_NORMAL}…\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_DEADPAN}…\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SAD}…\p"
	.string "I've been lied to, haven't I?$"

HouseLikeCarpet_Text_KroniiWhatsUpGigi::
# 137 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_HAPPY}Heya, what's up Gigi? I'm just hanging\n"
	.string "around in this unusual place here.\p"
	.string "It's pretty calm here, I won't lie.$"

HouseLikeCarpet_Text_GigiDeltaruneTomorrow::
# 142 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_HAPPY}Deltarune tomorrow, Kronii!\p"
	.string "Toby Fox is releasing Deltarune in a few\n"
	.string "hours from now!$"

HouseLikeCarpet_Text_KroniiWaitTomorrow::
# 147 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_ALT_9}Wait, frick, I almost forgot, Deltarune\n"
	.string "is just in a couple hours from today,\l"
	.string "huh? {DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SERIOUS}Actually hold on, didn't Toby Fox\l"
	.string "mention your name in his latest tweets?$"

HouseLikeCarpet_Text_GigiInDeltarune::
# 152 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_GIGI EMOTE_HAPPY}Yep, I'm gonna be in Deltarune soon,\n"
	.string "doing a bunch of shenanigans with the\l"
	.string "Fun Gang.\p"
	.string "Bet you feel kinda jealous for me being\n"
	.string "in the game, huh Kronii?$"

HouseLikeCarpet_Text_KroniiCanIBeInIt::
# 157 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_SAD}…\p"
	.string "{DESTROY_MUGSHOT}{CREATE_MUGSHOT MUGSHOT_KRONII EMOTE_DEADPAN}You think you can convince Toby Fox to\n"
	.string "add me in as well?$"

HouseLikeCarpet_Text_Garbage::
# 162 "data/maps/HouseLikeCarpet/scripts.pory"
	.string "It's just garbage now.$"
