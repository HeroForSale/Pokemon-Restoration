Route101_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route101_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route101_OnFrame
	.byte 0

Route101_OnTransition:
	call ProfBirch_EventScript_UpdateLocation
	end

Route101_OnFrame:
	map_script_2 VAR_ROUTE101_STATE, 0, Route101_EventScript_HideMapNamePopup
	.2byte 0

Route101_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_ROUTE101_STATE, 1
	end

Route101_EventScript_StartBirchRescue::
	lockall
	playbgm MUS_HELP, TRUE
	msgbox Route101_Text_HelpMe, MSGBOX_DEFAULT
	closemessage
	setobjectxy LOCALID_ROUTE101_BIRCH, 0, 15
	setobjectxy LOCALID_ROUTE101_ZIGZAGOON, 0, 16
	applymovement LOCALID_PLAYER, Route101_Movement_EnterScene
	applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_BirchRunAway1
	applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_ZigzagoonChase1
	waitmovement 0
	applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_ZigzagoonChaseInCircles
	applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_BirchRunInCircles
	waitmovement 0
	applymovement LOCALID_ROUTE101_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_ROUTE101_ZIGZAGOON, Route101_Movement_ZigzagoonFaceBirch
	applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_BirchFaceZigzagoon
	waitmovement 0
	msgbox Route101_Text_PleaseHelp, MSGBOX_DEFAULT
	closemessage
	setvar VAR_ROUTE101_STATE, 2
	releaseall
	end

Route101_EventScript_PreventExitSouth::
	lockall
	msgbox Route101_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Route101_Movement_PreventExitSouth
	waitmovement 0
	releaseall
	end

Route101_EventScript_PreventExitWest::
	lockall
	msgbox Route101_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Route101_Movement_PreventExitWest
	waitmovement 0
	releaseall
	end

Route101_EventScript_PreventExitNorth::
	lockall
	msgbox Route101_Text_DontLeaveMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Route101_Movement_PreventExitNorth
	waitmovement 0
	releaseall
	end

Route101_Movement_PreventExitSouth:
	walk_up
	step_end

Route101_Movement_PreventExitWest:
	walk_right
	step_end

Route101_Movement_PreventExitNorth:
	walk_down
	step_end

Route101_Movement_ZigzagoonChaseInCircles:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	step_end

Route101_Movement_ZigzagoonChase1:
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

@ Leftover data? This command is unused.
	step_end

Route101_Movement_ZigzagoonFaceBirch:
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	walk_in_place_fast_left
	step_end

Route101_Movement_EnterScene:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_in_place_faster_left
	step_end

Route101_Movement_BirchRunInCircles:
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route101_Movement_BirchRunAway1:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	step_end

@ Leftover data? This command is unused.
	step_end

Route101_Movement_BirchFaceZigzagoon:
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_in_place_fast_right
	step_end

Route101_Movement_Unused1:
	walk_up
	walk_up
	step_end

Route101_Movement_Unused2:
	walk_up
	walk_left
	walk_up
	step_end


@ Gen menu at Birch's bag: picks which trio goes in the 3 balls (VAR_STARTER_GEN).
@ VAR_STARTER_MON still stores the ball slot, so the rival keeps using Gen 3 counters.
Route101_EventScript_ChooseStarterGen::
	message Route101_Text_WhichStartersInBag
	waitmessage
.if STARTER_TEST_MENU == TRUE
	dynmultipush Route101_Text_GenTest, STARTER_GEN_TEST
.endif
	dynmultipush Route101_Text_GenKanto, STARTER_GEN_1
	dynmultipush Route101_Text_GenJohto, STARTER_GEN_2
	dynmultipush Route101_Text_GenHoenn, STARTER_GEN_3
	dynmultipush Route101_Text_GenSinnoh, STARTER_GEN_4
	dynmultipush Route101_Text_GenUnova, STARTER_GEN_5
	dynmultipush Route101_Text_GenKalos, STARTER_GEN_6
	dynmultipush Route101_Text_GenAlola, STARTER_GEN_7
	dynmultipush Route101_Text_GenGalar, STARTER_GEN_8
	dynmultipush Route101_Text_GenPaldea, STARTER_GEN_9
	dynmultistack 0, 0, TRUE, 6, FALSE, STARTER_GEN_3, DYN_MULTICHOICE_CB_NONE
	copyvar VAR_STARTER_GEN, VAR_RESULT
	closemessage
.if STARTER_TEST_MENU == TRUE
	goto_if_eq VAR_STARTER_GEN, STARTER_GEN_TEST, Route101_EventScript_ChooseTestStarters
.endif
	return

.if STARTER_TEST_MENU == TRUE
@ TEST: pick 3 reworked mons for the left, middle and right balls.
@ To add a mon, add a dynmultipush line (and its name text) in Route101_EventScript_PushTestStarters.
Route101_EventScript_ChooseTestStarters::
	message Route101_Text_PickTestLeft
	waitmessage
	call Route101_EventScript_PushTestStarters
	copyvar VAR_STARTER_TEST_1, VAR_RESULT
	message Route101_Text_PickTestMiddle
	waitmessage
	call Route101_EventScript_PushTestStarters
	copyvar VAR_STARTER_TEST_2, VAR_RESULT
	message Route101_Text_PickTestRight
	waitmessage
	call Route101_EventScript_PushTestStarters
	copyvar VAR_STARTER_TEST_3, VAR_RESULT
	closemessage
	return

Route101_EventScript_PushTestStarters::
	dynmultipush Route101_Text_TestCranidos, SPECIES_CRANIDOS
	dynmultipush Route101_Text_TestRampardos, SPECIES_RAMPARDOS
	dynmultipush Route101_Text_TestOmanyte, SPECIES_OMANYTE
	dynmultipush Route101_Text_TestOmastar, SPECIES_OMASTAR
	dynmultipush Route101_Text_TestKabuto, SPECIES_KABUTO
	dynmultipush Route101_Text_TestKabutops, SPECIES_KABUTOPS
	dynmultipush Route101_Text_TestLileep, SPECIES_LILEEP
	dynmultipush Route101_Text_TestCradily, SPECIES_CRADILY
	dynmultipush Route101_Text_TestAnorith, SPECIES_ANORITH
	dynmultipush Route101_Text_TestArmaldo, SPECIES_ARMALDO
	dynmultipush Route101_Text_TestShieldon, SPECIES_SHIELDON
	dynmultipush Route101_Text_TestBastiodon, SPECIES_BASTIODON
	dynmultipush Route101_Text_TestTirtouga, SPECIES_TIRTOUGA
	dynmultipush Route101_Text_TestCarracosta, SPECIES_CARRACOSTA
	dynmultipush Route101_Text_TestTyrunt, SPECIES_TYRUNT
	dynmultipush Route101_Text_TestTyrantrum, SPECIES_TYRANTRUM
	dynmultipush Route101_Text_TestAmaura, SPECIES_AMAURA
	dynmultipush Route101_Text_TestAurorus, SPECIES_AURORUS
	dynmultipush Route101_Text_TestBlitzle, SPECIES_BLITZLE
	dynmultipush Route101_Text_TestZebstrika, SPECIES_ZEBSTRIKA
	dynmultipush Route101_Text_TestAlolanRaichu, SPECIES_RAICHU_ALOLA
	dynmultistack 0, 0, TRUE, 6, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	return
.endif

Route101_EventScript_Youngster::
	msgbox Route101_Text_TakeTiredPokemonToPokeCenter, MSGBOX_NPC
	end

Route101_EventScript_Boy::
	msgbox Route101_Text_WildPokemonInTallGrass, MSGBOX_NPC
	end

Route101_EventScript_RouteSign::
	msgbox Route101_Text_RouteSign, MSGBOX_SIGN
	end

Route101_EventScript_BirchsBag::
	lock
	faceplayer
	call Route101_EventScript_ChooseStarterGen
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ROUTE101_ZIGZAGOON
	setobjectxy LOCALID_PLAYER, 6, 13
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special ChooseStarter
	applymovement LOCALID_ROUTE101_BIRCH, Route101_Movement_BirchApproachPlayer
	waitmovement 0
	msgbox Route101_Text_YouSavedMe, MSGBOX_DEFAULT
	special HealPlayerParty
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar VAR_BIRCH_LAB_STATE, 2
	setvar VAR_ROUTE101_STATE, 3
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route101_EventScript_HideMayInBedroom
	call_if_eq VAR_RESULT, FEMALE, Route101_EventScript_HideBrendanInBedroom
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	release
	end

Route101_EventScript_HideMayInBedroom::
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	return

Route101_EventScript_HideBrendanInBedroom::
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	return

Route101_Movement_BirchApproachPlayer:
	walk_right
	step_end

Route101_Text_HelpMe:
	.string "H-help me!$"

Route101_Text_PleaseHelp:
	.string "Hello! You over there!\n"
	.string "Please! Help!\p"
	.string "In my BAG!\n"
	.string "There's a POKé BALL!$"

Route101_Text_DontLeaveMe:
	.string "Wh-Where are you going?!\n"
	.string "Don't leave me like this!$"

Route101_Text_YouSavedMe:
	.string "PROF. BIRCH: Whew…\p"
	.string "I was in the tall grass studying wild\n"
	.string "POKéMON when I was jumped.\p"
	.string "You saved me.\n"
	.string "Thanks a lot!\p"
	.string "Oh?\p"
	.string "Hi, you're {PLAYER}{KUN}!\p"
	.string "This is not the place to chat, so come\n"
	.string "by my POKéMON LAB later, okay?$"

Route101_Text_TakeTiredPokemonToPokeCenter:
	.string "If POKéMON get tired, take them to\n"
	.string "a POKéMON CENTER.\p"
	.string "There's a POKéMON CENTER in OLDALE\n"
	.string "TOWN right close by.$"

Route101_Text_WildPokemonInTallGrass:
	.string "Wild POKéMON will jump out at you in\n"
	.string "tall grass.\p"
	.string "If you want to catch POKéMON, you have\n"
	.string "to go into the tall grass and search.$"

Route101_Text_RouteSign:
	.string "ROUTE 101\n"
	.string "{UP_ARROW} OLDALE TOWN$"

Route101_Text_WhichStartersInBag:
	.string "PROF. BIRCH's bag has POKé BALLS\n"
	.string "from all over. Which ones?$"

Route101_Text_GenKanto:
	.string "Kanto (Gen 1)$"

Route101_Text_GenJohto:
	.string "Johto (Gen 2)$"

Route101_Text_GenHoenn:
	.string "Hoenn (Gen 3)$"

Route101_Text_GenSinnoh:
	.string "Sinnoh (Gen 4)$"

Route101_Text_GenUnova:
	.string "Unova (Gen 5)$"

Route101_Text_GenKalos:
	.string "Kalos (Gen 6)$"

Route101_Text_GenAlola:
	.string "Alola (Gen 7)$"

Route101_Text_GenGalar:
	.string "Galar (Gen 8)$"

Route101_Text_GenPaldea:
	.string "Paldea (Gen 9)$"

.if STARTER_TEST_MENU == TRUE
Route101_Text_GenTest:
	.string "TEST$"

Route101_Text_PickTestLeft:
	.string "TEST: POKéMON for the left ball?$"

Route101_Text_PickTestMiddle:
	.string "TEST: POKéMON for the middle ball?$"

Route101_Text_PickTestRight:
	.string "TEST: POKéMON for the right ball?$"

Route101_Text_TestCranidos:
	.string "Cranidos$"

Route101_Text_TestRampardos:
	.string "Rampardos$"

Route101_Text_TestOmanyte:
	.string "Omanyte$"

Route101_Text_TestOmastar:
	.string "Omastar$"

Route101_Text_TestKabuto:
	.string "Kabuto$"

Route101_Text_TestKabutops:
	.string "Kabutops$"

Route101_Text_TestLileep:
	.string "Lileep$"

Route101_Text_TestCradily:
	.string "Cradily$"

Route101_Text_TestAnorith:
	.string "Anorith$"

Route101_Text_TestArmaldo:
	.string "Armaldo$"

Route101_Text_TestShieldon:
	.string "Shieldon$"

Route101_Text_TestBastiodon:
	.string "Bastiodon$"

Route101_Text_TestTirtouga:
	.string "Tirtouga$"

Route101_Text_TestCarracosta:
	.string "Carracosta$"

Route101_Text_TestTyrunt:
	.string "Tyrunt$"

Route101_Text_TestTyrantrum:
	.string "Tyrantrum$"

Route101_Text_TestAmaura:
	.string "Amaura$"

Route101_Text_TestAurorus:
	.string "Aurorus$"

Route101_Text_TestBlitzle:
	.string "Blitzle$"

Route101_Text_TestZebstrika:
	.string "Zebstrika$"

Route101_Text_TestAlolanRaichu:
	.string "Alolan Raichu$"
.endif
