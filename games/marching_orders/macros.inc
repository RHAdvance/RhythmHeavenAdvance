
/* ------------------------ Beatscript Labels: Marching Orders ------------------------ */


@ Load Data
.macro load_marching_orders_labels
    @ Game Events
    .set EVENT_00,          0x00
    .set EVENT_01,          0x01
    .set EVENT_02,          0x02
    .set EVENT_03,          0x03
    .set EVENT_04,          0x04
    .set PLAY_VOICE_SFX,    0x05

    @ Cues
    .set CUE_STEP,          0x00
    .set CUE_TURN_LEFT,     0x01
    .set CUE_TURN_RIGHT,    0x02
    .set CUE_HALT,          0x03

    @ [Event 0x05] Voice Sounds
    .set SHOUT_START,           0
    .set SHOUT_STOP,            1
    .set SHOUT_TURN,            2
    .set VOICE_ATTENTION,       3
    .set VOICE_MARCH,           4
    .set VOICE_HALT,            5
    .set VOICE_RIGHT_FACE,      6
    .set VOICE_RIGHT_FACE_F,    7
    .set VOICE_TURN_RIGHT,      8
    .set VOICE_LEFT_FACE,       9
    .set VOICE_LEFT_FACE_F,     10
    .set VOICE_TURN_LEFT,       11
    #ifdef SFX
    .set VOICE_ATTENTION_2,     12
    .set VOICE_ATTENTION_3,     13
    .set VOICE_LEFT_FACE_2,     14
    .set VOICE_RIGHT_FACE_2,    15
    .set VOICE_F_FACE_RIGHT,    16
    .set VOICE_F_FACE_LEFT,     17
    #endif
.endm


@ Load Game: Marching Orders
.macro load_marching_orders
    load_marching_orders_labels
    load_game marching_orders_engine, 0
.endm

@ Load Game: Marching Orders (Remix 7, Remix 8)
.macro load_marching_space_rabbits
    load_marching_orders_labels
    load_game marching_orders_engine, 1
.endm

@ Load Game: Marching Orders 2 (Unused)
.macro load_marching_orders_2_unused
    load_marching_orders_labels
    load_game marching_orders_engine, 2
.endm

@ Load Game: Marching Orders 2
.macro load_marching_orders_2
    load_marching_orders_labels
    load_game marching_orders_engine, 3
.endm

@ Load Game: Marching Orders (Extra)
.macro load_marching_orders_extra
    load_marching_orders_labels
    load_game marching_orders_engine, 4
.endm


/* ---------------- Game Engine Events ---------------- */


@ Run Game Event
.macro marching_orders_event event, args
    game_event marching_orders_engine, \event, \args
.endm


@ [Event 0x00] ?
.macro marching_orders_event00 args
    marching_orders_event EVENT_00, \args
.endm


@ [Event 0x01] ?
.macro marching_orders_event01
    marching_orders_event EVENT_01, 0
.endm


@ [Event 0x02] ?
.macro marching_orders_event02 args
    marching_orders_event EVENT_02, \args
.endm


@ [Event 0x03] ?
.macro marching_orders_event03
    marching_orders_event EVENT_03, 0
.endm


@ [Event 0x04] ?
.macro marching_orders_event04 args
    marching_orders_event EVENT_04, \args
.endm


@ [Event 0x05] Play Voice SFX
.macro marching_orders_play_voice_sfx id
    marching_orders_event PLAY_VOICE_SFX, \id
.endm
