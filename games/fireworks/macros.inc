
/* ------------------------ Beatscript Labels: Fireworks ------------------------ */


@ Load Data
.macro load_fireworks_labels
    @ Game Events
    .set SET_PATTERN_MODE,      0x00
    .set PLAY_SOUND,            0x01
    .set SET_DEFAULT_PATTERN,   0x02

    @ Cues
    .set CUE_SPIRIT_SPARKLER,   0x00
    .set CUE_NORMAL_FIREWORK,   0x01
    .set CUE_TAIKO_BOMBER,      0x04

    @ [Event 0x00] Pattern Modes
    .set PATTERN_MODE_0,            0
    .set PATTERN_MODE_1,            1
    .set PATTERN_MODE_TAIKO_BOMBER, 2
    .set PATTERN_MODE_USE_TABLE,    3
    .set PATTERN_MODE_USE_DEFAULT,  99

    @ [Event 0x01] Sound Effects
    .set SFX_COME_ON,   0
    .set SFX_ONE,       1
    .set SFX_TWO,       2
    .set SFX_THREE,     3
    .set SFX_NUEI,      4

    @ [Event 0x02] Firework Patterns
    .set PATTERN_3L,            0
    .set PATTERN_3C,            1
    .set PATTERN_3R,            2
    .set PATTERN_2LL,           3
    .set PATTERN_2CL,           4
    .set PATTERN_2CR,           5
    .set PATTERN_2RR,           6
    .set PATTERN_3L_BARELY,     7
    .set PATTERN_3C_BARELY,     8
    .set PATTERN_3R_BARELY,     9
    .set PATTERN_2LL_BARELY,    10
    .set PATTERN_2CL_BARELY,    11
    .set PATTERN_2CR_BARELY,    12
    .set PATTERN_2RR_BARELY,    13
    .set PATTERN_SP_STAR,       14
    .set PATTERN_SP_CIRCLE,     15
    .set PATTERN_SP_SPIRAL,     16
    .set PATTERN_SP_SMILE,      17
    .set PATTERN_SP_TSUNKU,     18
    .set PATTERN_TAIKO_BOMBER,  19
.endm


@ Load Game: Fireworks
.macro load_fireworks
    load_fireworks_labels
    load_game fireworks_engine, 0
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Fireworks (Remix 5, BG 1)
.macro load_fireworks_remix_5_bg1
    load_fireworks_labels
    load_game fireworks_engine, 1
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Fireworks (Remix 5, BG 2)
.macro load_fireworks_remix_5_bg2
    load_fireworks_labels
    load_game fireworks_engine, 2
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Fireworks (Remix 5, BG 3)
.macro load_fireworks_remix_5_bg3
    load_fireworks_labels
    load_game fireworks_engine, 3
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm

@ Load Game: Fireworks (Remix 5, BG 4)
.macro load_fireworks_remix_5_bg4
    load_fireworks_labels
    load_game fireworks_engine, 4
    set_localized BEATSCRIPT_LOCALIZED_COND_GLOBAL_NON_JP_SFX
.endm


/* ---------------- Game Engine Events ---------------- */


@ Run Game Event
.macro fireworks_event event, args
    game_event fireworks_engine, \event, \args
.endm


@ [Event 0x00] Set Pattern Sourcing Mode
.macro fireworks_set_pattern_mode mode
    fireworks_event SET_PATTERN_MODE, \mode
.endm


@ [Event 0x01] Play Count-In SFX (includes "Nuei!" but not "Tamaya~")
.macro fireworks_play_sfx id
    fireworks_event PLAY_SOUND, \id
.endm


@ [Event 0x02] Set Default Firework Pattern
.macro fireworks_set_default_pattern pattern
    fireworks_event SET_DEFAULT_PATTERN, \pattern
.endm
