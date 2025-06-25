KroniiCeremonyMain_EventScript_KroniiIntroduction::
# 2 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 3 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername gText_Kronii
# 4 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_KroniiIntro
# 5 "data/maps/KroniiCeremonyMain/scripts.pory"
	closemessage
# 6 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


KroniiCeremonyMain_EventScript_SuspiciousGuy::
# 10 "data/maps/KroniiCeremonyMain/scripts.pory"
	lock
# 11 "data/maps/KroniiCeremonyMain/scripts.pory"
	faceplayer
# 12 "data/maps/KroniiCeremonyMain/scripts.pory"
	setspeakername KroniiCeremonyMain_Text_SkualperGuyName
# 13 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuyIntro
# 14 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuySwindle, MSGBOX_YESNO
# 15 "data/maps/KroniiCeremonyMain/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq KroniiCeremonyMain_EventScript_SuspiciousGuy_2
# 20 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end

KroniiCeremonyMain_EventScript_SuspiciousGuy_2:
# 16 "data/maps/KroniiCeremonyMain/scripts.pory"
	msgbox KroniiCeremonyMain_Text_SkualperGuyDenied
# 17 "data/maps/KroniiCeremonyMain/scripts.pory"
	release
	end


# 62 "data/maps/KroniiCeremonyMain/scripts.pory"

# 63 "data/maps/KroniiCeremonyMain/scripts.pory"
KroniiCeremonyMain_MapScripts::
# 64 "data/maps/KroniiCeremonyMain/scripts.pory"
	.byte 0

KroniiCeremonyMain_Text_KroniiIntro::
# 24 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Kroniichiwa!\p"
	.string "My name is Ouro Kronii. Nice to see\n"
	.string "you've taken my offer to help out with\l"
	.string "my ceremony here.\p"
	.string "I'm very gald you chose to help out, so\n"
	.string "here's a little pass to allow you to go\l"
	.string "through wherever you need.\p"
	.string "I do need some help however with\n"
	.string "setting up the stage for me to talk\l"
	.string "about myself, so if you can, please get\l"
	.string "some people to help me out with it.\p"
	.string "I've also invited my friend Gigi here as\n"
	.string "well, although I'm not sure if she'll be\l"
	.string "much help, considering who she is.\p"
	.string "Do feel free to talk to me if you need\n"
	.string "any help here.$"

KroniiCeremonyMain_Text_NoWaterGuy::
# 33 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "You're wondering where the water is at?\p"
	.string "Sorry bud, our organizer here banned\n"
	.string "straight up water here after the last\l"
	.string "incident with a water cooler.\p"
	.string "Safe to say we don't want to risk\n"
	.string "anything like that again with our\l"
	.string "organizer Kronii here.$"

KroniiCeremonyMain_Text_SkualperGuyName::
# 39 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "Skualper$"

KroniiCeremonyMain_Text_SkualperGuyIntro::
# 43 "data/maps/KroniiCeremonyMain/scripts.pory"
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
# 50 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "But that's just me here, what do you say\n"
	.string "kid?\p"
	.string "Do you want this exclusive ticket here?$"

KroniiCeremonyMain_Text_SkualperGuyDenied::
# 55 "data/maps/KroniiCeremonyMain/scripts.pory"
	.string "So it's like that, huh?\p"
	.string "Just gonna get a ticket the old\n"
	.string "fashionhed way, you think?\p"
	.string "Well, let's see how that will work out for\n"
	.string "you, if it even does at all.\p"
	.string "I'll still be here though if you change\n"
	.string "your mind.$"
