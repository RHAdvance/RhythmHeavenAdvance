#pragma once

#include "global.h"
#include "graphics.h"
#include "sound.h"
#include "task_pool.h"
#include "data/beatscript_scene_data.h"


/* BEATSCRIPT SCENE HANDLER */


// Beatscript Commands
enum BeatscriptCommandsEnum {
    /* 00 */ BS_CMD_REST,
    /* 01 */ BS_CMD_STOP,
    /* 02 */ BS_CMD_SCENE_RUN,
    /* 03 */ BS_CMD_RUN_1ARG,
    /* 04 */ BS_CMD_RUN_2ARG,
    /* 05 */ BS_CMD_SET_VAR,
    /* 06 */ BS_CMD_ADD_VAR,
    /* 07 */ BS_CMD_SET_BIT,
    /* 08 */ BS_CMD_CLEAR_BIT,
    /* 09 */ BS_CMD_SCENE_SET_VAR,
    /* 0A */ BS_CMD_SCENE_ADD_VAR,
    /* 0B */ BS_CMD_SCENE_SET_BIT,
    /* 0C */ BS_CMD_SCENE_CLEAR_BIT,
    /* 0D */ BS_CMD_CALL,
    /* 0E */ BS_CMD_RETURN,
    /* 0F */ BS_CMD_GOTO,
    /* 10 */ BS_CMD_LOOP_START,
    /* 11 */ BS_CMD_LOOP_END,
    /* 12 */ BS_CMD_IF_EQ,
    /* 13 */ BS_CMD_IF_NEQ,
    /* 14 */ BS_CMD_ELSE,
    /* 15 */ BS_CMD_END_IF,
    /* 16 */ BS_CMD_IF_SET,
    /* 17 */ BS_CMD_IF_CLEAR,
    /* 18 */ BS_CMD_18,
    /* 19 */ BS_CMD_19,
    /* 1A */ BS_CMD_SWITCH,
    /* 1B */ BS_CMD_END_SWITCH,
    /* 1C */ BS_CMD_CASE,
    /* 1D */ BS_CMD_BREAK,
    /* 1E */ BS_CMD_WHILE_NEQ,
    /* 1F */ BS_CMD_WHILE_EQ,
    /* 20 */ BS_CMD_END_WHILE,
    /* 21 */ BS_CMD_SCENE_IF_EQ,
    /* 22 */ BS_CMD_SCENE_IF_NEQ,
    /* 23 */ BS_CMD_SCENE_SWITCH,
    /* 24 */ BS_CMD_SCENE_WHILE_EQ,
    /* 25 */ BS_CMD_SCENE_WHILE_NEQ,
    /* 26 */ BS_CMD_26,
    /* 27 */ BS_CMD_27,
    /* 28 */ BS_CMD_PLAY_MUSIC,
    /* 29 */ BS_CMD_PLAY_SFX,
    /* 2A */ BS_CMD_2A,
    /* 2B */ BS_CMD_2B,
    /* 2C */ BS_CMD_2C,
    /* 2D */ BS_CMD_2D,
    /* 2E */ BS_CMD_2E,
    /* 2F */ BS_CMD_2F,
    /* 30 */ BS_CMD_30,
    /* 31 */ BS_CMD_31,
    /* 32 */ BS_CMD_32,
    /* 33 */ BS_CMD_33,
    /* 34 */ BS_CMD_34,
    /* 35 */ BS_CMD_FADE_MUSIC_IN,
    /* 36 */ BS_CMD_FADE_MUSIC_OUT,
    /* 37 */ BS_CMD_37,
    /* 38 */ BS_CMD_FADE_SFX_OUT,
    /* 39 */ BS_CMD_LOAD_GRAPHICS,
    /* 3A */ BS_CMD_ADD_MUSIC,
    /* 3B */ BS_CMD_3B,
    /* 3C */ BS_CMD_SET_SPEED,
    /* 3D */ BS_CMD_SET_MUSIC_PITCH_S,
    /* 3E */ BS_CMD_SET_MUSIC_PITCH,
    /* 3F */ BS_CMD_INTERP_LCD_BLEND,
    /* 40 */ BS_CMD_CHANGE_PALETTE,
    /* 41 */ BS_CMD_SET_BG_REG,
    /* 42 */ BS_CMD_START_INTEGER_LERP,
    /* 43 */ BS_CMD_43,
    /* 44 */ BS_CMD_44,
    /* 45 */ BS_CMD_45,
    /* 46 */ BS_CMD_46,
    /* 47 */ BS_CMD_LOAD_GRAPHICS_ASYNC,
    /* 48 */ BS_CMD_SET_BACKDROP,
    /* 49 */ BS_CMD_SET_VIDEO_MODE,
    /* 4A */ BS_CMD_FADE_SCREEN,
    /* 4B */ BS_CMD_4B,
    /* 4C */ BS_CMD_INTERP_TEMPO,
    /* 4D */ BS_CMD_4D,
    /* 4E */ BS_CMD_INTERP_MUSIC_PITCH,
    /* 4F */ BS_CMD_DEFAULT_CASE,
    /* 50 */ BS_CMD_INTERP_MUSIC_VOLUME,
    /* 51 */ BS_CMD_51,
    /* 52 */ BS_CMD_52,
    /* 53 */ BS_CMD_53,
    /* 54 */ BS_CMD_54,
    /* 55 */ BS_CMD_55,
    /* 56 */ BS_CMD_56,
    /* 57 */ BS_CMD_57,
    /* 58 */ BS_CMD_58,
    /* 59 */ BS_CMD_59,
    /* 5A */ BS_CMD_5A,
    /* 5B */ BS_CMD_5B,
    /* 5C */ BS_CMD_5C,
    /* 5D */ BS_CMD_5D,
    /* 5E */ BS_CMD_5E,
    /* 5F */ BS_CMD_5F,
    /* 60 */ BS_CMD_60,
    /* 61 */ BS_CMD_61,
    /* 62 */ BS_CMD_62,
    /* 63 */ BS_CMD_63,
    /* 64 */ BS_CMD_64,
    /* 65 */ BS_CMD_65,
    /* 66 */ BS_CMD_66,
    /* 67 */ BS_CMD_67,
    /* 68 */ BS_CMD_68,
    /* 69 */ BS_CMD_69,
    /* 6A */ BS_CMD_6A,
    /* 6B */ BS_CMD_6B,
    /* 6C */ BS_CMD_6C,
    /* 6D */ BS_CMD_6D,
    /* 6E */ BS_CMD_6E,
    /* 6F */ BS_CMD_6F,
    /* 70 */ BS_CMD_70,
    /* 71 */ BS_CMD_71,
    /* 72 */ BS_CMD_72,
    /* 73 */ BS_CMD_73,
    /* 74 */ BS_CMD_74,
    /* 75 */ BS_CMD_75,
    /* 76 */ BS_CMD_76,
    /* 77 */ BS_CMD_77,
    /* 78 */ BS_CMD_78,
    /* 79 */ BS_CMD_79,
    /* 7A */ BS_CMD_7A,
    /* 7B */ BS_CMD_7B,
    /* 7C */ BS_CMD_7C,
    /* 7D */ BS_CMD_7D,
    /* 7E */ BS_CMD_7E,
    /* 7F */ BS_CMD_7F,
    /* 80 */ BS_CMD_SPRITE_SET_ANIM,
    /* 81 */ BS_CMD_SPRITE_SET_FRAME,
    /* 82 */ BS_CMD_SPRITE_SET_PLAYBACK,
    /* 83 */ BS_CMD_SPRITE_SET_XYZ,
    /* 84 */ BS_CMD_SPRITE_SET_XY,
    /* 85 */ BS_CMD_SPRITE_SET_Z,
    /* 86 */ BS_CMD_SPRITE_RENDER,
    /* 87 */ BS_CMD_SPRITE_SET_XY_WITH_VECTOR2,
    /* 88 */ BS_CMD_SPRITE_SET_PALETTE,
    /* 89 */ BS_CMD_SPRITE_SET_TILE_NUM,
    /* 8A */ BS_CMD_SPRITE_SET_ENABLE_UPDATES,
    /* 8B */ BS_CMD_SPRITE_SET_ANIM_SPEED,
    /* 8C */ BS_CMD_SPRITE_START_MOTION_INDEFINITE,
    /* 8D */ BS_CMD_SPRITE_START_MOTION_DECELERATE,
    /* 8E */ BS_CMD_SPRITE_START_MOTION_ACCELERATE,
    /* 8F */ BS_CMD_SPRITE_START_MOTION_LERP,
    /* 90 */ BS_CMD_SPRITE_START_MOTION_SINE_VEL,
    /* 91 */ BS_CMD_SPRITE_START_MOTION_SINE_WAVE,
    /* 92 */ BS_CMD_SPRITE_SET_MOTION_CALLBACK,
    /* 93 */ BS_CMD_TEXT_DELETE_ANIM,
    /* 94 */ BS_CMD_TEXT_MANAGE,
    /* 95 */ BS_CMD_SPRITE_EDIT_ATTRIBUTES,
    /* 96 */ BS_CMD_SPRITE_ADD_XY,
    /* 97 */ BS_CMD_SPRITE_ADD_Z,
    /* 98 */ BS_CMD_SPRITE_MOVE_DECELERATE,
    /* 99 */ BS_CMD_SPRITE_MOVE_ACCELERATE,
    /* 9A */ BS_CMD_SPRITE_MOVE_LERP,
    /* 9B */ BS_CMD_SPRITE_MOVE_SINE_VEL,
    /* 9C */ BS_CMD_SPRITE_MOVE_SINE_WAVE,
    /* 9D */ BS_CMD_SPRITE_SET_ANIM_CALLBACK,
    /* 9E */ BS_CMD_SPRITE_DELETE,
    /* 9F */ BS_CMD_SPRITE_DELETE_ALL,
    /* A0 */ BS_CMD_PAUSE_TASKS,
    /* A1 */ BS_CMD_START_INTEGER_ALTERNATOR,
    /* A2 */ BS_CMD_START_INTEGER_INCREMENTER,
    /* A3 */ BS_CMD_GET_ACTIVE_TASK,
    /* A4 */ BS_CMD_START_INTEGER_SINE_INTERP,
    /* A5 */ BS_CMD_STOP_TASK,
    /* A6 */ BS_CMD_DMA3_SET,
    /* A7 */ BS_CMD_SET_SPEED_TO_MUSIC,
    /* A8 */ BS_CMD_SPRITE_LINK_XY_TO_BG_OFFSET,
    /* A9 */ BS_CMD_TEXT_A9,
    /* AA */ BS_CMD_AA,
    /* AB */ BS_CMD_AB,
    /* AC */ BS_CMD_SET_MUSIC_TRACK_VOLUME,
    /* AD */ BS_CMD_INTERP_MUSIC_TRACK_VOLUME,
    /* AE */ BS_CMD_PLAY_SFX_SP,
    /* AF */ BS_CMD_INCREASE_SPEED,
    /* B0 */ BS_CMD_CALL_RESULT,
    /* B1 */ BS_CMD_REST_RESET,
    /* B2 */ BS_CMD_PLAY_SFX_SYNCED,
    /* B3 */ BS_CMD_SET_LOCALIZED,
    /* B4 */ BS_CMD_REST_LOCALIZED,
    /* B5 */ BS_CMD_PLAY_SFX_LOCALIZED
};


// TYPES
struct Struct_0800b71c_sub {
    u32 id:8;
    u32 unk1_0:10;
    u32 unk4;
};

struct Struct_0800b71c {
    u32 total:8;
    u32 unk1_0:1;
    u32 unk1_1:23;
    struct Struct_0800b71c_sub *objects;
};

struct struct_0800e75c {
    const char **unk0;
    s16 unk4;
    s16 unk6;
    u16 unk8;
    u16 unkA;
    s16 *unkC;
};

struct struct_0800f0b4_sub {
    s16 unk0;
    s32 unk4[3];
    s32 unk10[3];
    s16 unk1C[3];
    s16 unk22;
    s16 unk24;
    struct Animation *unk28;
    s32 unk2C;
};

struct struct_0800f0b4_sub1 {
    u32 unk0;
    u32 unk4;
    u32 unk8;
};

struct struct_0800f0b4_sub2 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u32 unk8;
    u32 unkC;
};

struct struct_0800f0b4_sub3 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
};

struct struct_0800f0b4 {
    u16 unk0;
    u16 *unk4;
    struct struct_0800f0b4_sub2 *unk8;
    struct struct_0800f0b4_sub1 unkC;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    struct struct_0800f0b4_sub3 unk20;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    u16 unk48;
    u16 unk4A;
    u16 unk4C;
    u8 unk4E;
    u8 unk4F;
    struct struct_0800f0b4_sub *unk50;
    s8 unk54[0x20];
    void *unk74;
    u16 unk78;
    u8 unk7A;
    u8 unk7B[1];
    u8 pad7C[0x1E];
};


// FUNCTIONS
extern u8 func_0800b634(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3);
extern void run_beatscript_scene_callback(void);
extern void set_beatscript_scene_callback(void function(s32), s32 argument);
extern void func_0800b6dc(struct Struct_0800b71c *, u32, u32, struct Struct_0800b71c_sub *);
extern void func_0800b71c(struct Struct_0800b71c *, u32, u32, u32);
extern void func_0800b768_stub(void);
extern void func_0800b76c_stub(void);
extern void func_0800b770_stub(void);
extern void func_0800b774_stub(void);
extern void start_beatscript_scene(u32 mode); // Beatscript Init.
extern void set_beatscript_subscenes(const struct SubScene **subScenes); // Set SubScenes
extern void update_paused_beatscript_scene(void); // ? (called each loop after the pause menu has been opened at least once)
extern void update_active_beatscript_scene(void); // Beatscript Update
extern s32 beatscript_scene_is_inactive(void); // Check if No Beatscript Threads Are Active
extern void beatscript_enable_loops(void); // Enable Loops
extern void beatscript_exit_loop_after_delay_callback(void); // Delayed Loop Exit Task Function
extern void beatscript_exit_loop_after_delay(u32 duration); // Exit Loop After Delay
extern void beatscript_exit_loop_after_one_beat(void); // Exit Loop After One Beat
extern void beatscript_force_exit_loop(void); // Exit Loop (If Within a Loop)
extern void beatscript_disable_loops(void); // Force Stop Loop
extern void beatscript_force_exit_loop_next_update(void); // Exit Loop on Next Update
extern void set_pause_beatscript_scene(u32); // Pause Script
extern u32 beatscript_scene_is_paused(void); // Check if Beatscript Handler Is Paused
extern void stop_beatscript_scene(void); // Beatscript Engine Force Quit
extern void set_beatscript_tempo(u16 tempo); // Set Script Tempo
extern void update_beatscript_tempo(void); // Update Script Tempo
extern void set_beatscript_speed(u16 speed); // Set Script Speed (Q8.8)
extern void func_0800be9c_stub(void);
extern void func_0800bea0(u32 arg); // Set unk0_b7
extern void func_0800bebc(u32 arg); // Set unk1C
extern u32  scene_change_music(struct SongHeader *, u32 override, s32 soundPlayer); // Play Music
extern void scene_set_music(struct SongHeader *); // Play Music (Override)
extern void scene_play_music(struct SongHeader *); // Play Music (No Override)
extern void scene_set_music_with_soundplayer(struct SongHeader *, s32 soundPlayer); // Play Music in Given SoundPlayer (Override)
extern void scene_play_music_with_soundplayer(struct SongHeader *, s32 soundPlayer); // Play Music in Given SoundPlayer (No Override)
extern void scene_set_music_player_by_sound(struct SongHeader *); // Play Music (override, use predefined SoundPlayer ID)
extern void scene_stop_music(void); // Stop Music
extern void scene_fade_in_music(u16 duration); // Fade-In Music
extern void scene_fade_out_music(u16 duration); // Fade-Out Music
extern void scene_update_music_pitch(void); // Update Music Pitch
extern void scene_set_music_pitch(s16 pitch); // Set Music Pitch
extern void scene_set_music_pitch_env(s16 pitch); // Set Music Pitch Source 2
extern void scene_set_music_volume(u16 volume); // Set Music Volume
extern void scene_set_music_track_volume(u16 selection, u16 volume); // Set Music Volume for Selected Tracks
extern void scene_set_music_volume_env(u32 volume); // Set Music Volume 2 (just calls the other one)
extern void scene_interpolate_music_volume(u32 volume, u32 duration); // Interpolate Music Volume
extern void scene_set_music_track_volume_env(u32 selection, u32 volume); // Set Music Volume for Selected Tracks (Integer)
extern void scene_interpolate_music_track_volume(u32 volume, u32 duration); // Interpolate Music Volume for Selected Tracks
extern void scene_set_music_key(s32 key); // Set Music Key Offset
extern void func_0800c1a4_stub(void);
extern u32 get_beatscript_tempo(void); // Get Current Script Tempo
extern u32 func_0800c1b4(void); // Get Sprite Animation Speed
extern s32 func_0800c1c0(s24_8 arg); // Return (arg * spriteAnimSpeed)
extern s32 func_0800c1d0(s24_8 arg); // Return (arg * (spriteAnimSpeed ^ 2))
extern void scene_set_soundplayer_panning(struct SoundPlayer *player, s16 panning); // Set Music Panning
extern struct SoundPlayer *scene_set_random_music(struct SongHeader **musicPool);
extern struct SoundPlayer *scene_play_sound_to_tempo_and_pitch(struct SongHeader *sfx);
extern struct SoundPlayer *scene_play_sound_to_tempo(struct SongHeader *sfx);
extern struct SoundPlayer *scene_play_random_sound(struct SongHeader **sfxPool);
extern struct SoundPlayer *scene_play_random_sound_to_tempo_and_pitch(struct SongHeader **sfxPool);
extern struct SoundPlayer *scene_play_random_sound_to_tempo(struct SongHeader **sfxPool);
extern void func_0800c390_stub(void);
extern u32 func_0800c394(void);
extern u32 func_0800c398(void);
extern s32 ticks_to_frames(u32); // Convert Script Tatums to Real-Time Frames
extern u32 get_current_mem_id(void); // Get Current Memory ID / SubScene
extern void set_current_mem_id(u32 memID); // Set Current Memory ID / SubScene
extern void func_0800c3e4_stub(void);
extern void func_0800c3e8_stub(u32 arg);
extern void func_0800c3ec(u32 arg);
extern void func_0800c3fc_stub(void);
extern void func_0800c400_stub(void);
extern void func_0800c404_stub(void);
extern void func_0800c408_stub(void);
extern void func_0800c40c_stub(void);
extern void func_0800c410_stub(void);
extern void func_0800c414_stub(void);
extern void func_0800c418_stub(void);
extern void func_0800c41c_stub(void);
extern void func_0800c420_stub(void);
extern void func_0800c424_stub(void);
extern void func_0800c428_stub(void);
extern s32 scene_affine_group_alloc(void);
extern void *scene_mem_heap_alloc(u32 size);
extern s32 scene_start_new_task(struct TaskMethods *methods, void *inputs, TaskFinalFunc onFinish, u32 onFinishArg);
extern void scene_flush_save_buffer(void);
extern u32 scene_get_default_text_id(void);
extern void func_0800c494(u32 thread);
extern void func_0800c4ac_stub(void);
extern s32 scene_start_integer_interp(u32 type, u32 duration, void *source, s32 initial, s32 target);
extern s32 scene_start_integer_alternator(u32 type, u32 interval, void *source, s32 initial, s32 target);
extern s32 scene_start_integer_incrementer(u32 type, u32 interval, void *source, s32 initial, s32 increment);
extern s32 scene_start_integer_sine_interp(u32 type, void *source, s32 baseValue, s24_8 initialAngle, s24_8 speed);
extern void func_0800c604(u32 thread);
extern void func_0800c654_stub(void);
extern void func_0800c658_stub(void);
extern void func_0800c65c_stub(void);
extern struct BitmapFontOBJ *scene_create_obj_font_printer(u16 baseTileNum, u8 maxTileRows);
extern void func_0800c694(u32 arg);
extern void func_0800c6a4(void);
extern void func_0800c6c8(void);
extern void func_0800c6d4_stub(void);
extern void func_0800c6d8_stub(void);
extern void func_0800c6dc_stub(void);
extern void func_0800c6e0_stub(void);
extern struct Beatscript *beatscript_stream_jump_cond_if(struct Beatscript *currentCmd); // IF Statement Failed
extern struct Beatscript *beatscript_stream_jump_cond_else(struct Beatscript *currentCmd); // ELSE Statement Jump
extern struct Beatscript *beatscript_stream_jump_cond_switch(struct Beatscript *currentCmd, s32 arg); // SWITCH Statement Start
extern struct Beatscript *beatscript_stream_jump_cond_break(struct Beatscript *currentCmd); // BREAK Statement Jump
extern struct Beatscript *beatscript_stream_jump_cond_while(struct Beatscript *currentCmd); // WHILE Statement Failed
extern struct Beatscript *beatscript_stream_jump_cond_end_while(struct Beatscript *currentCmd); // END_WHILE Statement Jump
extern s16 beatscript_stream_get_sprite_for_motion(s16 *spritePool, s16 args, s16 *destX, s16 *destY);
extern void func_0800cb28(u32 threadID); // Update Beatscript Stream
extern void func_0800dfbc_stub(void);
extern void func_0800dfc0_stub(void);
extern s32 func_0800dfc4(void);
extern void func_0800dfe0_stub(void);
extern void func_0800dfe4_stub(void);
extern void func_0800dfe8_stub(void);
extern void func_0800dfec_stub(void);
extern void func_0800dff0_stub(void);
extern void func_0800dff4_stub(void);
extern void func_0800dff8_stub(void);
extern void func_0800dffc_stub(void);
extern void func_0800e000_stub(void);
extern void func_0800e004_stub(void);
extern void func_0800e008_stub(void);
extern void func_0800e00c_stub(void);
extern void func_0800e010_stub(void);
extern void func_0800e014_stub(void);
extern void scene_set_video_mode(s32 videoMode);
extern void scene_show_bg_layer(s32 layer);
extern void scene_hide_bg_layer(s32 layer);
extern void scene_set_bg_layer_pos(s32 layer, s16 x, s16 y);
extern void scene_set_bg_layer_controls(s32 layer, s32 tileset, s32 map, s32 priority);
extern void scene_set_bg_layer_priority(s32 layer, s32 priority);
extern void scene_set_bg_layer_display(s32 layer, s32 show, s32 x, s32 y, s32 tileset, s32 map, s32 params);
extern void scene_show_obj_layer(void);
extern void scene_hide_obj_layer(void);
extern void scene_enable_obj_windows(void);
extern void scene_disable_obj_windows(void);
extern void scene_set_obj_mosaic_size(s16 xSize, s16 ySize);
extern void scene_set_bg_mosaic_size(s16 xSize, s16 ySize);
extern s32 scene_set_sprite_motion_indefinite(s16 sprite, s16 startX, s16 startY, s8_8 velX, s8_8 velY);
extern s32 scene_move_sprite_indefinite(s16 sprite, s8_8 velX, s8_8 velY);
extern s32 scene_set_sprite_motion_decelerate(s16 sprite, s16 startX, s16 startY, s16 destX, s16 destY, s8_8 multiplier);
extern s32 scene_move_sprite_decelerate(s16 sprite, s16 destX, s16 destY, s8_8 multiplier);
extern s32 scene_set_sprite_motion_accelerate(s16 sprite, s16 startX, s16 startY, s16 destX, s16 destY, s8_8 velocity, s8_8 acceleration);
extern s32 scene_move_sprite_accelerate(s16 sprite, s16 destX, s16 destY, s8_8 velocity, s8_8 acceleration);
extern s32 scene_set_sprite_motion_lerp(s16 sprite, s16 startX, s16 startY, s16 destX, s16 destY, u16 duration);
extern s32 scene_move_sprite_lerp(s16 sprite, s16 destX, s16 destY, u16 duration);
extern s32 scene_set_sprite_motion_sine_osc(s16 sprite, u8 angle, s16 baseX, s16 baseY, s16 baseOffset, s16 amplitude, s16 waveStart, s16 waveEnd, u16 duration);
extern s32 scene_move_sprite_sine_osc(s16 sprite, u8 angle, s16 amplitude, s16 waveStart, s16 waveEnd, u16 duration);
extern s32 scene_set_sprite_motion_sine_vel(s16 sprite, u32 mode, s16 startX, s16 startY, s16 destX, s16 destY, u16 duration);
extern s32 scene_move_sprite_sine_vel(s16 sprite, u32 mode, s16 destX, s16 destY, u16 duration);
extern s32 scene_set_sprite_motion_sine_wave(s16 sprite, s16 startX, s16 startY, s16 destX, s16 destY, s16 amplitude, u16 duration);
extern s32 scene_move_sprite_sine_wave(s16 sprite, s16 destX, s16 destY, s16 amplitude, u16 duration);
extern void func_0800e75c(struct struct_0800e75c *arg0);
extern void func_0800e768(struct BitmapFontOBJ *textObj, struct struct_0800e75c *arg1);
extern void func_0800e7e8(struct BitmapFontOBJ *textObj, struct struct_0800e75c *arg1);
extern void func_0800e830(struct struct_0800e75c **arg0);
extern void func_0800e850(struct BitmapFontOBJ *textObj, struct struct_0800e75c **arg1);
extern void func_0800e86c(struct BitmapFontOBJ *textObj, struct struct_0800e75c **arg1);
extern void func_0800e888(u32 arg0);
extern void func_0800e8b0(u32 arg1);
extern void func_0800e8d8(struct SpriteHandler *handler, s16 id, s8 *arg, u32 cel);
extern void func_0800e8f4(s16 arg0, s8 *arg1);
extern void func_0800e940_stub(void);
extern void func_0800e944_stub(void);
extern void func_0800e948(void);
extern void func_0800e970(void);
extern void func_0800e9d8(void);
extern void func_0800e9f8(void);
extern void func_0800ea1c(u16 arg);
extern void func_0800ea2c(s16 arg);
extern void func_0800ea3c(u16 arg);
extern void func_0800ea70(u16 arg);
extern s32 func_0800eaa0(void);
extern void scene_tempo_interp_stop(void);
extern void scene_tempo_interp_update(void);
extern void scene_tempo_interp_start(u32 initial, u32 target, u32 duration);
extern void scene_interpolate_tempo(u32 target, u32 duration); // BEATSCRIPT - Change Tempo
extern void scene_music_pitch_interp_stop(void);
extern void scene_music_pitch_interp_update(void);
extern void scene_music_pitch_interp_start(s32 initial, s32 target, u32 duration);
extern void scene_interpolate_music_pitch(s32 target, u32 duration); // BEATSCRIPT - Change Music Pitch
extern void scene_set_music_interp_enabled(u32 enable);
extern void scene_fade_music_in(u32 duration); // BEATSCRIPT - Fade-In Music
extern void scene_fade_music_out(u32 duration); // BEATSCRIPT - Fade-Out Music
extern void func_0800ed54_stub(void);
extern void func_0800ed58_stub(void);
extern void func_0800ed5c_stub(void);
extern void func_0800ed60_stub(u32 speed);
extern u16 *func_0800ed64(u16 arg0, u16 arg1, u16 arg2);
extern void func_0800edb8(void *data);
extern void func_0800edc8(u16 *gradientBuffer, u16 arg1, u16 arg2, u16 arg3);
extern void func_0800edfc(void *bgPalette);
extern void func_0800ee1c(void *objPalette);
extern void func_0800ee3c(void *bgPalette);
extern void func_0800ee5c(void *objPalette);
extern void func_0800ee7c(void *bgPalette);
extern void func_0800ee9c(void *objPalette);
extern void func_0800eebc(char *dest, const char *src);
extern void func_0800f070(u32 id, const char *string);
extern void func_0800f084(void);
extern void func_0800f09c(struct BitmapFontOBJ *objFont);
extern struct struct_0800f0b4 *func_0800f0b4(u32 arg0, u32 arg1, u16 *arg2, u32 arg3, u16 arg4, s32 arg5);
extern void func_0800f180(struct struct_0800f0b4 *arg0);
extern void func_0800f1ec(struct struct_0800f0b4 *arg0);
extern void func_0800f218(struct struct_0800f0b4 *arg0);
extern void func_0800f22c(struct struct_0800f0b4 *arg0);
extern void func_0800f4a0(struct struct_0800f0b4 *arg0, s32 *arg1, s32 *arg2);
extern void func_0800f524(struct struct_0800f0b4 *arg0, s32 *arg1, u16 *arg2);
extern void func_0800f570(struct struct_0800f0b4 *arg0, u32 arg1, u32 arg2, u32 arg3);
extern void func_0800f578(struct struct_0800f0b4 *arg0, s32 arg1, s32 arg2);
extern void func_0800f580(struct struct_0800f0b4 *arg0, s32 arg1, s32 arg2);
extern void func_0800f588(struct struct_0800f0b4 *arg0, u32 arg1);
extern void func_0800f614(struct struct_0800f0b4 *arg0);
extern s16 func_0800f7c0(struct struct_0800f0b4 *arg0, struct Animation *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 arg6, s32 arg7, s32 arg8);
extern void func_0800f89c(struct struct_0800f0b4 *arg0, s16 arg1);
extern s16 func_0800f8d8(struct struct_0800f0b4 *arg0, s16 arg1);
extern void func_0800f8ec(struct struct_0800f0b4 *arg0);
extern void func_0800f8f8(struct struct_0800f0b4 *arg0, u32 arg1);
