@ Pokémon Center service vendor. Stands left of the counter in every Hoenn Pokémon Center.
@ To add a service: push another option in PkmnCenterVendor_EventScript_Menu with the next id,
@ add a case for it, and end the service with "goto PkmnCenterVendor_EventScript_AnythingElse".

PkmnCenterVendor_EventScript_Vendor::
	lock
	faceplayer
	message PkmnCenterVendor_Text_Welcome
	waitmessage
	goto PkmnCenterVendor_EventScript_Menu

PkmnCenterVendor_EventScript_AnythingElse::
	message PkmnCenterVendor_Text_AnythingElse
	waitmessage
PkmnCenterVendor_EventScript_Menu::
	dynmultipush PkmnCenterVendor_Text_OptionNature, 0
	dynmultipush PkmnCenterVendor_Text_OptionExit, 1
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, PkmnCenterVendor_EventScript_ChangeNature
	goto PkmnCenterVendor_EventScript_Goodbye

PkmnCenterVendor_EventScript_Goodbye::
	msgbox PkmnCenterVendor_Text_Goodbye, MSGBOX_DEFAULT
	release
	end

@ Service: free nature change
PkmnCenterVendor_EventScript_ChangeNature::
	msgbox PkmnCenterVendor_Text_WhichMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	lock
	faceplayer
	goto_if_ge VAR_0x8004, PARTY_SIZE, PkmnCenterVendor_EventScript_AnythingElse
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, PkmnCenterVendor_EventScript_NatureEgg
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	callnative NatureVendor_BufferCurrentNature
	message PkmnCenterVendor_Text_WhichNature
	waitmessage
	callnative NatureVendor_PushNatureOptions
	dynmultistack 0, 0, FALSE, 7, FALSE, VAR_0x8005, DYN_MULTICHOICE_CB_NONE
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, PkmnCenterVendor_EventScript_AnythingElse
	goto_if_eq VAR_RESULT, VAR_0x8005, PkmnCenterVendor_EventScript_SameNature
	copyvar VAR_0x8006, VAR_RESULT
	callnative NatureVendor_BufferNewNature
	msgbox PkmnCenterVendor_Text_ConfirmNature, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PkmnCenterVendor_EventScript_AnythingElse
	callnative NatureVendor_SetNature
	playse SE_SUCCESS
	msgbox PkmnCenterVendor_Text_NatureChanged, MSGBOX_DEFAULT
	goto PkmnCenterVendor_EventScript_AnythingElse

PkmnCenterVendor_EventScript_NatureEgg::
	msgbox PkmnCenterVendor_Text_NatureEgg, MSGBOX_DEFAULT
	goto PkmnCenterVendor_EventScript_AnythingElse

PkmnCenterVendor_EventScript_SameNature::
	msgbox PkmnCenterVendor_Text_SameNature, MSGBOX_DEFAULT
	goto PkmnCenterVendor_EventScript_AnythingElse

PkmnCenterVendor_Text_Welcome:
	.string "Hi! I offer special services\n"
	.string "for your Pokémon. What'll it be?$"

PkmnCenterVendor_Text_AnythingElse:
	.string "Anything else I can do for you?$"

PkmnCenterVendor_Text_OptionNature:
	.string "Change nature$"

PkmnCenterVendor_Text_OptionExit:
	.string "Exit$"

PkmnCenterVendor_Text_Goodbye:
	.string "Come back anytime!$"

PkmnCenterVendor_Text_WhichMon:
	.string "Which Pokémon's nature should\n"
	.string "I change? It's free of charge!$"

PkmnCenterVendor_Text_NatureEgg:
	.string "That's an Egg! It doesn't have\n"
	.string "much of a nature yet.$"

PkmnCenterVendor_Text_WhichNature:
	.string "{STR_VAR_1} is {STR_VAR_2} right now.\n"
	.string "Which nature should it have?$"

PkmnCenterVendor_Text_SameNature:
	.string "{STR_VAR_1} already has\n"
	.string "that nature!$"

PkmnCenterVendor_Text_ConfirmNature:
	.string "Change {STR_VAR_1}'s nature\n"
	.string "to {STR_VAR_2}?$"

PkmnCenterVendor_Text_NatureChanged:
	.string "All done! {STR_VAR_1} is\n"
	.string "{STR_VAR_2} now.$"
