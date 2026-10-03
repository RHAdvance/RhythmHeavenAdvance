
/* ------------------------ Beatscript Labels: Drum Intro ------------------------ */


@ Load Data
.macro load_drum_intro_labels
    @ Game Events
    .set EVENT_00,      0x00
    .set EVENT_01,      0x01
    .set EVENT_02,      0x02
    .set EVENT_03,      0x03
    .set EVENT_04,      0x04
    .set EVENT_05,      0x05
    .set EVENT_06,      0x06
    .set EVENT_07,      0x07
    .set EVENT_08,      0x08
    .set EVENT_09,      0x09
    .set EVENT_0A,      0x0A
    .set EVENT_0B,      0x0B
    .set EVENT_0C,      0x0C
    .set EVENT_0D,      0x0D
    .set EVENT_0E,      0x0E
    .set EVENT_0F,      0x0F

    @ Cues
    .set CUE_KICK,      0x00
    .set CUE_SNARE,     0x01
    .set CUE_CYMBAL,    0x02
    .set CUE_TOM,       0x03
    .set CUE_HIHAT,     0x04
    .set CUE_ROLL,      0x04
    .set CUE_AUTO,      0x05
.endm


@ Load Game: Unused Drumming Intro (Talking)
.macro load_drum_intro_talk
    load_drum_intro_labels
    load_game drum_intro_engine, 0
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Unused Drumming Intro (Playing)
.macro load_drum_intro_play
    load_drum_intro_labels
    load_game drum_intro_engine, 1
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Tanuki & Monkey
.macro load_tanuki_and_monkey
    load_drum_intro_labels
    load_game drum_intro_engine, 2
.endm

@ Load Game: Samurai Drummer Cutscene
.macro load_drum_samurai_cutscene
    load_drum_intro_labels
    load_game drum_intro_engine, 3
.endm


/* ---------------- Game Engine Events ---------------- */


@ Run Game Event
.macro drum_intro_event event, args
    game_event drum_intro_engine, \event, \args
.endm


@ [Event 0x00] ?
.macro dmi_event00 args
    drum_intro_event EVENT_00, \args
.endm


@ [Event 0x01] ?
.macro dmi_event01 args
    drum_intro_event EVENT_01, \args
.endm


@ [Event 0x02] ?
.macro dmi_event02 args
    drum_intro_event EVENT_02, \args
.endm


@ [Event 0x03] ?
.macro dmi_event03 args
    drum_intro_event EVENT_03, \args
.endm


@ [Event 0x04] ?
.macro dmi_event04 args
    drum_intro_event EVENT_04, \args
.endm


@ [Event 0x05] ?
.macro dmi_event05 args
    drum_intro_event EVENT_05, \args
.endm


@ [Event 0x06] ?
.macro dmi_event06
    drum_intro_event EVENT_06, 0
.endm


@ [Event 0x07] ?
.macro dmi_event07 args
    drum_intro_event EVENT_07, \args
.endm


@ [Event 0x08] ?
.macro dmi_event08 args
    drum_intro_event EVENT_08, \args
.endm


@ [Event 0x09] ?
.macro dmi_event09 args
    drum_intro_event EVENT_09, \args
.endm


@ [Event 0x0A] ?
.macro dmi_event0A args
    drum_intro_event EVENT_0A, \args
.endm


@ [Event 0x0B] ?
.macro dmi_event0B textTable, offset
    drum_intro_event EVENT_0B, \textTable + (\offset * 0xC)
.endm


@ [Event 0x0C] ?
.macro dmi_event0C
    drum_intro_event EVENT_0C, 0
.endm


@ [Event 0x0D] ?
.macro dmi_event0D
    drum_intro_event EVENT_0D, 0
.endm


@ [Event 0x0E] ?
.macro dmi_event0E
    drum_intro_event EVENT_0E, 0
.endm


@ [Event 0x0F] ?
.macro dmi_event0F args
    drum_intro_event EVENT_0F, \args
.endm
