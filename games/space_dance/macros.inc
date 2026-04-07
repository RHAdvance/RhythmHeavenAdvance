
/* ------------------------ Beatscript Labels: Space Dance ------------------------ */


@ Load Data
.macro load_space_dance_labels
    @ Game Events
    .set EVENT_00,      0x00
    .set EVENT_01,      0x01
    .set EVENT_02,      0x02
    .set EVENT_03,      0x03
    .set EVENT_04,      0x04
    .set EVENT_05,      0x05
    .set EVENT_06,      0x06
    .set EVENT_07,      0x07

    @ Cues
    .set CUE_TURN_RIGHT,    0x00
    .set CUE_SIT_DOWN,      0x01
    .set CUE_PUNCH,         0x02
    .set CUE_PUNCH_S,       0x03

    @ Dance Move Animations
    .set ANIM_HIT_RIGHT,    0
    .set ANIM_HIT_PUNCH,    1
    .set ANIM_HIT_DOWN,     2
    .set ANIM_CUE_RIGHT,    3
    .set ANIM_CUE_PUNCH1,   4
    .set ANIM_CUE_PUNCH2,   5
    .set ANIM_CUE_DOWN,     6

    @ Animations specific to Space Gramps
    .set ANIM_SPEAK,        7
    .set ANIM_BLINK,        8
.endm


@ Load Game: Space Dance
.macro load_space_dance
    load_space_dance_labels
    load_game space_dance_engine, 0
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Cosmic Dance
.macro load_cosmic_dance
    load_space_dance_labels
    load_game space_dance_engine, 1
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Space Dance (Remix 3)
.macro load_space_dance_remix_3
    load_space_dance_labels
    load_game space_dance_engine, 2
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm


/* ---------------- Game Engine Events ---------------- */


@ Run Game Event
.macro space_dance_event event, args
    game_event space_dance_engine, \event, \args
.endm


@ [Event 0x00] ?
.macro space_dance_event00 args
    space_dance_event EVENT_00, \args
.endm


@ [Event 0x01] ?
.macro space_dance_event01 arg1, arg2
    space_dance_event EVENT_01, ((\arg1 & 0xFF) << 8) | (\arg2 & 0xFF)
.endm


@ [Event 0x02] ?
.macro space_dance_event02 args
    space_dance_event EVENT_02, \args
.endm


@ [Event 0x03] ?
.macro space_dance_event03
    space_dance_event EVENT_03, 0
.endm


@ [Event 0x04] ?
.macro space_dance_event04 args
    space_dance_event EVENT_04, \args
.endm


@ [Event 0x05] ?
.macro space_dance_event05 args
    space_dance_event EVENT_05, \args
.endm


@ [Event 0x06] ?
.macro space_dance_event06 args
    space_dance_event EVENT_06, \args
.endm


@ [Event 0x07] ?
.macro space_dance_event07 args
    space_dance_event EVENT_07, \args
.endm
