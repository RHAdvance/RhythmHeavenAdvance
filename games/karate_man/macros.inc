
/* ------------------------ Beatscript Labels: Karate Man ------------------------ */


@ Load Data
.macro load_karate_labels
    @ Game Events
    .set RESET_BG_FACE,             0x00
    .set START_SERIOUS_NEXT_HIT,    0x01
    .set STOP_SERIOUS_NEXT_HIT,     0x02
    .set PRINT_TEXTBOX,             0x03
    .set WAIT_AT_TEXTBOX,           0x04
    .set ENABLE_FLOW_METER,         0x05
    .set START_TUTORIAL_LOOP,       0x06
    .set EXIT_LOOP_IF_ALL_HIT,      0x07
    .set USE_THE_FACE,              0x08

    @ Cues
    .set CUE_POT,           0x00
    .set CUE_SOCCER_BALL,   0x01
    .set CUE_POT_STRICT,    0x02
    .set CUE_ROCK,          0x04
    .set CUE_BOMB,          0x05
    .set CUE_LIGHT_BULB,    0x08
.endm


@ Load Game: Karate Man
.macro load_karate_man
    load_karate_labels
    load_game karate_man_engine, 0
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Karate Man (Unused Faces)
.macro load_karate_man_unused
    load_karate_labels
    load_game karate_man_engine, 1
.endm

@ Load Game: Karate Man (Start with Serious Mode Active)
.macro load_karate_man_serious
    load_karate_labels
    load_game karate_man_engine, 2
.endm

@ Load Game: Karate Man 2
.macro load_karate_man_2
    load_karate_labels
    load_game karate_man_engine, 3
.endm

@ Load Game: Karate Man (Extra)
.macro load_karate_man_extra
    load_karate_labels
    load_game karate_man_engine, 4
.endm


/* ---------------- Game Engine Events ---------------- */


@ Run Game Event
.macro karate_man_event event, args
    game_event karate_man_engine, \event, \args
.endm


@ [Event 0x00] Reset BG Face
.macro karate_man_reset_bg_face
    karate_man_event RESET_BG_FACE, 0
.endm


@ [Event 0x01] Start "Serious Mode" on Next Hit
.macro karate_man_start_serious_next_hit
    karate_man_event START_SERIOUS_NEXT_HIT, 0
.endm


@ [Event 0x02] Finish "Serious Mode" on Next Hit
.macro karate_man_stop_serious_next_hit
    karate_man_event STOP_SERIOUS_NEXT_HIT, 0
.endm


@ [Event 0x03] Print Textbox
.macro karate_man_print_textbox string
    karate_man_event PRINT_TEXTBOX, \string
.endm

.macro karate_man_clear_textbox
    karate_man_print_textbox NULL
.endm


@ [Event 0x04] Wait at Textbox for Player Input
.macro karate_man_wait_at_textbox
    karate_man_event WAIT_AT_TEXTBOX, 0
.endm


@ [Event 0x05] Enable Flow Meter
.macro karate_man_enable_flow enable
    karate_man_event ENABLE_FLOW_METER, \enable
.endm


@ [Event 0x06] Start Tutorial Loop (set required inputs to pass)
.macro karate_man_start_tutorial_loop totalCues
    karate_man_event START_TUTORIAL_LOOP, \totalCues
.endm


@ [Event 0x07] Proceed With Tutorial if All Hit
.macro karate_man_exit_loop_if_all_hit
    karate_man_event EXIT_LOOP_IF_ALL_HIT, 0
.endm


@ [Event 0x08] Use The Face
.macro karate_man_use_the_face use
    karate_man_event USE_THE_FACE, \use
.endm
