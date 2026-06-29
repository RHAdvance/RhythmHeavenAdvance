
/* ------------------------ Beatscript Labels: Mr. Upbeat ------------------------ */


@ Load Data
.macro load_mr_upbeat_labels
    @ Game Events
    .set EVENT_00,      0x00
    .set EVENT_01,      0x01
    .set EVENT_02,      0x02
    .set EVENT_03,      0x03
    .set EVENT_04,      0x04
    .set EVENT_05,      0x05

    @ Cues
    .set CUE_H_BEAT_REALTIME,   0x00
    .set CUE_1_BEAT_TO_TEMPO,   0x01
    .set CUE_H_BEAT_TO_TEMPO,   0x08
.endm


@ Load Game: Mr. Upbeat
.macro load_mr_upbeat
    load_mr_upbeat_labels
    load_game mr_upbeat_engine, 0
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm


/* ---------------- Game Engine Events ---------------- */


@ Run Game Event
.macro mr_upbeat_event event, args
    game_event mr_upbeat_engine, \event, \args
.endm


@ [Event 0x00] ?
.macro mr_upbeat_event00 args
    mr_upbeat_event EVENT_00, \args
.endm


@ [Event 0x01] ?
.macro mr_upbeat_event01 args
    mr_upbeat_event EVENT_01, \args
.endm


@ [Event 0x02] ?
.macro mr_upbeat_event02
    mr_upbeat_event EVENT_02, 0
.endm


@ [Event 0x03] ?
.macro mr_upbeat_event03
    mr_upbeat_event EVENT_03, 0
.endm


@ [Event 0x04] ?
.macro mr_upbeat_event04
    mr_upbeat_event EVENT_04, 0
.endm


@ [Event 0x05] ?
.macro mr_upbeat_event05
    mr_upbeat_event EVENT_05, 0
.endm
