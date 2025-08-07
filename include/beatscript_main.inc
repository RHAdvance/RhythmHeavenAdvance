.include "include/gba.inc"

@ Booleans
.set FALSE, 0
.set TRUE,  1

@ Buttons
.set A_BUTTON,              (1 << 0)
.set B_BUTTON,              (1 << 1)
.set SELECT_BUTTON,         (1 << 2)
.set START_BUTTON,          (1 << 3)
.set DPAD_RIGHT,            (1 << 4)
.set DPAD_LEFT,             (1 << 5)
.set DPAD_UP,               (1 << 6)
.set DPAD_DOWN,             (1 << 7)
.set RIGHT_SHOULDER_BUTTON, (1 << 8)
.set LEFT_SHOULDER_BUTTON,  (1 << 9)
.set DPAD_ALL,              (DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN)
.set DPAD_ANY,              (DPAD_ALL)

@ Read/Write Target Types
.set INT8,  0
.set INT16, 1
.set INT32, 2
.set FUNC,  3

@ Marking Criteria Flags
.set CHECK_AVERAGE_MISSES, 0x100
.set OVERRIDE_COMMENTS,    0x80
.set CHECK_AVERAGE_HITS,   0x1

.set END_OF_CRITERIA, NULL

@ Music/Sound Players
.set MUSIC_PLAYER_0,        0
.set MUSIC_PLAYER_1,        1
.set MUSIC_PLAYER_2,        2
.set SFX_PLAYER_0,          3
.set SFX_PLAYER_1,          4
.set SFX_PLAYER_2,          5
.set SFX_PLAYER_3,          6
.set SFX_PLAYER_4,          7
.set SFX_PLAYER_5,          8
.set SFX_PLAYER_6,          9
.set SFX_PLAYER_7,          10
.set SFX_PLAYER_8,          11
.set SFX_PLAYER_9,          12
.set DEFAULT_SOUND_PLAYER,  255

@ Music Tracks
.set MIDI_TRACK_0,  (1 << 0)
.set MIDI_TRACK_1,  (1 << 1)
.set MIDI_TRACK_2,  (1 << 2)
.set MIDI_TRACK_3,  (1 << 3)
.set MIDI_TRACK_4,  (1 << 4)
.set MIDI_TRACK_5,  (1 << 5)
.set MIDI_TRACK_6,  (1 << 6)
.set MIDI_TRACK_7,  (1 << 7)
.set MIDI_TRACK_8,  (1 << 8)
.set MIDI_TRACK_9,  (1 << 9)
.set MIDI_TRACK_10, (1 << 10)
.set MIDI_TRACK_11, (1 << 11)
.set MIDI_TRACK_12, (1 << 12)
.set MIDI_TRACK_13, (1 << 13)
.set MIDI_TRACK_14, (1 << 14)
.set MIDI_TRACK_15, (1 << 15)

@ RGB555 Colors
.set BLACK, 0x0000
.set WHITE, 0x7FFF

@ Macros for making Beatscript look nicer.
.macro script label
    glabel \label
.endm

.macro struct label
    glabel \label
.endm

.macro endstruct
    .balign 4, 0
.endm

.macro text label
    glabel \label
.endm

.macro endtext
    .balign 4, 0
.endm

@ Beatscript Gameplay Scene Definitions
.macro define_gameplay_scene name, entrypoint
struct sub_\name
    /* Init Func   */ .word gameplay_start_scene,         NULL
    /* Paused Func */ .word gameplay_update_paused_scene, NULL
    /* Update Func */ .word gameplay_update_scene,        NULL
    /* End Func    */ .word gameplay_stop_scene,          NULL
    /* Beatscript  */ .word \entrypoint
endstruct

struct \name
    /* Init Func   */ .word func_0801d86c, sub_\name
    /* Update Func */ .word func_0801d8d8, NULL
    /* End Func    */ .word NULL,          NULL
    /* Memory      */ .hword 0x5BC
endstruct
.endm

/* ------------------------ Command Macros ------------------------ */


@ Generic Beatscript Command
.macro beatscript_cmd id, arg1, arg2, arg3
    .word (((\id) & 0xff) | ((\arg1) << 8))
    .word (\arg2)
    .word (\arg3)
.endm


@ [0x00] Rest
.macro rest time
    beatscript_cmd 0x00, 0, 0, \time
.endm

.macro no_op
    rest 0
.endm

.macro rest_beats beats
    rest (\beats * 24)
.endm


@ [0x01] Stop
.macro stop
    beatscript_cmd 0x01, 0, 0, 0
.endm


@ [0x02] (Scene) Run Function
.macro scene_run function, arg=0
    beatscript_cmd 0x02, 0, \function, \arg
.endm


@ [0x03] Run Function (1 Argument)
.macro run function, arg=0
    beatscript_cmd 0x03, 0, \function, \arg
.endm


@ [0x04] Run Function (2 Arguments)
.macro run2 function, arg1, arg2
    beatscript_cmd 0x04, \arg1, \function, \arg2
.endm


@ [0x05] Set Variable
.macro set_var type, address, value
    beatscript_cmd 0x05, \type, \address, \value
.endm

.macro set_byte address, value
    set_var INT8, \address, \value
.endm


@ [0x06] Add to Variable
.macro add_var type, address, value
    beatscript_cmd 0x06, \type, \address, \value
.endm

.macro add_byte address, value
    add_var INT8, \address, \value
.endm


@ [0x07] Set Bit
.macro set_bit type, address, bit
    beatscript_cmd 0x07, \type, \address, \bit
.endm


@ [0x08] Clear Bit
.macro clear_bit type, address, bit
    beatscript_cmd 0x08, \type, \address, \bit
.endm


@ [0x09] (Scene) Set Variable
.macro scene_set_var type, offset, value
    beatscript_cmd 0x09, \type, \offset, \value
.endm

.macro scene_set_byte address, value
    scene_set_var INT8, \address, \value
.endm


@ [0x0A] (Scene) Add to Variable
.macro scene_add_var type, offset, value
    beatscript_cmd 0x0A, \type, \offset, \value
.endm

.macro scene_add_byte offset, value
    scene_add_var INT8, \offset, \value
.endm


@ [0x0B] (Scene) Set Bit
.macro scene_set_bit type, offset, bit
    beatscript_cmd 0x0B, \type, \offset, \bit
.endm


@ [0x0C] (Scene) Clear Bit
.macro scene_clear_bit type, offset, bit
    beatscript_cmd 0x0C, \type, \offset, \bit
.endm


@ [0x0D] Branch with Link
.macro call script
    beatscript_cmd 0x0D, 0, \script, 0
.endm


@ [0x0E] Return
.macro return
    beatscript_cmd 0x0E, 0, 0, 0
.endm


@ [0x0F] Branch without Link
.macro goto script
    beatscript_cmd 0x0F, 0, \script, 0
.endm


@ [0x10] Start Loop
.macro loop_start
    beatscript_cmd 0x10, 0, 0, 0
.endm


@ [0x11] End Loop
.macro loop_end
    beatscript_cmd 0x11, 0, 0, 0
.endm


@ [0x12] If Equal
.macro if_eq type, address, value
    beatscript_cmd 0x12, \type, \address, \value
.endm

.macro if_globalvar_eq value
    if_eq INT8, GLOBAL_VARIABLE, \value
.endm


@ [0x13] If Not Equal
.macro if_neq type, address, value
    beatscript_cmd 0x13, \type, \address, \value
.endm


@ [0x14] Else
.macro else
    beatscript_cmd 0x14, 0, 0, 0
.endm


@ [0x15] End If Statement
.macro end_if
    beatscript_cmd 0x15, 0, 0, 0
.endm


@ [0x16] If Bit Set
.macro if_set address, bit
    beatscript_cmd 0x16, 0, \address, \bit
.endm


@ [0x17] If Bit Clear
.macro if_clear address, bit
    beatscript_cmd 0x17, 0, \address, \bit
.endm


@ [0x18] ? (operations on the global scene variable)
@ [0x19] ? (operations on the global scene variable)


@ [0x1A] Switch Statement
.macro switch type, address
    beatscript_cmd 0x1A, \type, 0, \address
.endm

.macro switch_loop_counter
    switch FUNC, gameplay_get_loop_counter
.endm

.macro switch_random range
    run agb_random, \range
    switch INT8, GLOBAL_VARIABLE
.endm


@ [0x1B] End Switch Statement
.macro end_switch
    beatscript_cmd 0x1B, 0, 0, 0
.endm


@ [0x1C] Switch Case
.macro case value
    beatscript_cmd 0x1C, 0, 0, \value
.endm


@ [0x1D] End Switch Case
.macro break
    beatscript_cmd 0x1D, 0, 0, 0
.endm


@ [0x1E] ? (conditional statement (while?))
@ [0x1F] ? (conditional statement (while not?))
@ [0x20] ? (branch-related)


@ [0x21] (Scene) If Equal
.macro scene_if_eq type, offset, value
    beatscript_cmd 0x21, \type, \offset, \value
.endm


@ [0x22] (Scene) If Not Equal
.macro scene_if_neq type, offset, value
    beatscript_cmd 0x22, \type, \offset, \value
.endm


@ [0x23] Scene Switch Statement
.macro scene_switch type, offset
    beatscript_cmd 0x23, \type, 0, \offset
.endm


@ [0x24] ? (scene variant of 0x1F)
@ [0x25] ? (scene variant of 0x1E)
@ [0x26]
@ [0x27]


@ [0x28] Play Music
.macro play_music_in player, music
    beatscript_cmd 0x28, 0, \player, \music
.endm

.macro play_music music
    play_music_in DEFAULT_SOUND_PLAYER, \music
.endm


@ [0x29] Play Sound Effect
.macro play_sfx sound
    beatscript_cmd 0x29, 0, 0, \sound
.endm

@ [0x29] Play Sound Effect (Localized)
.macro play_sfx_localized jap_sound, eng_sound
#ifdef SFX
    beatscript_cmd 0x29, 0, 0, \eng_sound
#else
    beatscript_cmd 0x29, 0, 0, \jap_sound
#endif
.endm


@ [0x2A]
@ [0x2B]
@ [0x2C]
@ [0x2D]
@ [0x2E]
@ [0x2F]
@ [0x30]
@ [0x31]
@ [0x32]
@ [0x33]
@ [0x34]


@ [0x35] Music Fade-In
.macro fade_music_in_cmd toTempo, time
    beatscript_cmd 0x35, \toTempo, 0, \time
.endm

.macro fade_music_in time
    fade_music_in_cmd TRUE, \time
.endm


@ [0x36] Music Fade-Out
.macro fade_music_out_cmd toTempo, time
    beatscript_cmd 0x36, \toTempo, 0, \time
.endm

.macro fade_music_out time
    fade_music_out_cmd TRUE, \time
.endm


@ [0x37]


@ [0x38] Sound Effect Fade-Out
.macro fade_sfx_out sound, time
    beatscript_cmd 0x38, 0, \sound, \time
.endm


@ [0x39] Load Graphics Table (Immediate)
.macro load_graphics address
    beatscript_cmd 0x39, 0, \address, 0
.endm


@ [0x3A] Play Music (without overriding existing music if possible)
.macro add_music player, music
    beatscript_cmd 0x3A, 0, \player, \music
.endm


@ [0x3B]


@ [0x3C] Set Speed
.macro set_speed speed
    beatscript_cmd 0x3C, 0, 0, \speed
.endm


@ [0x3D] Set Music Pitch (also updates an unknown flag)
.macro set_music_pitch_s pitch
    beatscript_cmd 0x3D, 0, 0, \pitch
.endm


@ [0x3E] Set Music Pitch (avoids resetting an unknown flag)
.macro set_music_pitch pitch
    beatscript_cmd 0x3E, 0, 0, \pitch
.endm


@ [0x3F] Change LCD Special Effect Controls (Blend)
.macro mod_lcd_blend reverse, controls, toTempo, time
    beatscript_cmd 0x3F, \reverse, \controls, ((\toTempo << 31) | (\time & 0x7FFFFFFF))
.endm

.macro mod_lcd_blend_to controls, time
    mod_lcd_blend FALSE, \controls, TRUE, \time
.endm

.macro mod_lcd_blend_from controls, time
    mod_lcd_blend TRUE, \controls, TRUE, \time
.endm


@ [0x40] Change Palette
@ [0x41] Set BG Layer Registers
@ [0x42] Start Data Interpolation Task (Linear)
@ [0x43]
@ [0x44]
@ [0x45]
@ [0x46] Stub Function


@ [0x47] Load Graphics Table (with bytes-per-update process limit)
.macro task_load_graphics address, limit
    beatscript_cmd 0x47, 0, \address, \limit
.endm


@ [0x48] Set Backdrop
.macro set_backdrop arg1, arg2, arg3
    beatscript_cmd 0x48, \arg1, \arg2, \arg3
.endm


@ [0x49] Set Video Mode
.macro set_video_mode mode
    beatscript_cmd 0x49, 0, \mode, 0
.endm


@ [0x4A] Fade Palette from Solid Colour
.macro fade_screen reverse, time, color
    beatscript_cmd 0x4A, \reverse, \time, \color
.endm

.macro fade_screen_in time, color
    fade_screen 0, \time, \color
.endm

.macro fade_screen_out time, color
    fade_screen 1, \time, \color
.endm


@ [0x4B]


@ [0x4C] Gradually Change Tempo
.macro mod_tempo tempo, time
    beatscript_cmd 0x4C, 0, \tempo, \time
.endm


@ [0x4D]


@ [0x4E] Gradually Change Music Pitch
.macro mod_music_pitch pitch, time
    beatscript_cmd 0x4E, 0, \pitch, \time
.endm


@ [0x4F] Default Case
.macro default
    beatscript_cmd 0x4F, 0, 0, 0
.endm


@ [0x50] Gradually Change Music Volume
.macro mod_music_volume volume, time
    beatscript_cmd 0x50, 0, \volume, \time
.endm


@ [0x51] ?
@ [0x52] ?
@ [0x53]
@ [0x54]
@ [0x55]
@ [0x56]
@ [0x57]
@ [0x58]
@ [0x59]
@ [0x5A]
@ [0x5B]
@ [0x5C]
@ [0x5D]
@ [0x5E]
@ [0x5F]
@ [0x60]
@ [0x61]
@ [0x62]
@ [0x63]
@ [0x64]
@ [0x65]
@ [0x66]
@ [0x67]
@ [0x68]
@ [0x69]
@ [0x6A]
@ [0x6B]
@ [0x6C]
@ [0x6D]
@ [0x6E]
@ [0x6F]
@ [0x70]
@ [0x71]
@ [0x72]
@ [0x73]
@ [0x74]
@ [0x75]
@ [0x76]
@ [0x77]
@ [0x78]
@ [0x79]
@ [0x7A]
@ [0x7B]
@ [0x7C]
@ [0x7D]
@ [0x7E]
@ [0x7F]
@ [0x80] (Global Scene Sprite) Set Animation
@ [0x81] (Global Scene Sprite) Set Animation Frame
@ [0x82] (Global Scene Sprite) Set Animation Params.
@ [0x83] (Global Scene Sprite) Set XYZ
@ [0x84] (Global Scene Sprite) Set XY
@ [0x85] (Global Scene Sprite) Set Z
@ [0x86] (Global Scene Sprite) Show/Hide
@ [0x87] (Global Scene Sprite) Set XY (Vector2)
@ [0x88] (Global Scene Sprite) Set Palette
@ [0x89] (Global Scene Sprite) sprite_set_base_tile()
@ [0x8A] (Global Scene Sprite) sprite_set_enable_updates()
@ [0x8B] (Global Scene Sprite) Set Playback Speed
@ [0x8C] (Global Scene Sprite) Indefinite Linear Motion
@ [0x8D] ?
@ [0x8E] ?
@ [0x8F] ?
@ [0x90] ?
@ [0x91] ?
@ [0x92] (Global Scene Sprite) Run Function Upon Motion Task End
@ [0x93] ?
@ [0x94] ?
@ [0x95] ?
@ [0x96] (Global Scene Sprite) Add to XY
@ [0x97] (Global Scene Sprite) Add to Z
@ [0x98] ?
@ [0x99] ?
@ [0x9A] ?
@ [0x9B] ?
@ [0x9C] ?
@ [0x9D] (Global Scene Sprite) Run Function Upon Animation End
@ [0x9E] (Global Scene Sprite) Delete
@ [0x9F] (Global Scene Sprite) Delete All
@ [0xA0] ?
@ [0xA1] ?
@ [0xA2] ?
@ [0xA3] ?
@ [0xA4] ?
@ [0xA5] ?


@ [0xA6] DMA3 Set
.macro dma_set tileCount, src, dest
    beatscript_cmd 0xA6, \tileCount, \src, \dest
.endm


@ [0xA7] Set Speed to Music (this also plays the given music)
.macro set_speed_to_music music
    beatscript_cmd 0xA7, 0, 0, \music
.endm


@ [0xA8] (Global Scene Sprite) Fix XY to BG Layer
@ [0xA9] (Global Scene Sprite) ?
@ [0xAA]
@ [0xAB]


@ [0xAC] Set Music Track Volume
.macro set_music_track_volume tracks, volume
    beatscript_cmd 0xAC, \tracks, \volume, 0
.endm

.macro mute_music_track tracks
    set_music_track_volume \tracks, 0
.endm

.macro reset_music_track_volumes
    set_music_track_volume 0, 0
.endm


@ [0xAD] Gradually Change Music Track Volume
.macro mod_music_track_volume tracks, volume, time
    beatscript_cmd 0xAD, \tracks, \volume, \time
.endm


@ [0xAE] Play Sound Effect (at given volume & pitch)
.macro play_sfx_vol_pitch sound, volume, pitch
    beatscript_cmd 0xAE, \volume, \pitch, \sound
.endm

.macro play_sfx_vol sound, volume
    play_sfx_vol_pitch \sound, \volume, 0
.endm


@ [0xAF] Gradually Add to Speed Multiplier
.macro increase_speed multiplier, time
    beatscript_cmd 0xAF, 0, \multiplier, \time
.endm


@ [0xB0] Branch to Global Scene Variable
.macro call_result
    beatscript_cmd 0xB0, 0, 0, 0
.endm


@ [0xB1] Reset Rest Timer
.macro rest_reset
    beatscript_cmd 0xB1, 0, 0, 0
.endm


@ [0xB2] Play Sound Effect (at given volume & pitch)
.macro play_sfx_synced_pitch sound, baseBPM, volume, pitch
    beatscript_cmd 0xB2, \baseBPM, ((\volume & 0xFFFF) | (\pitch << 16)), \sound
.endm

.macro play_sfx_synced sound, baseBPM, volume
    play_sfx_synced_pitch \sound, \baseBPM, \volume, 0
.endm
