#pragma once

#include "global.h"
#include "engines.h"

#include "games/spaceball/graphics/spaceball_graphics.h"

// Engine Macros/Enums:
#define SPACEBALL_STAR_AMOUNT 24

enum SpaceballCueStatesEnum {
    SPACEBALL_CUE_STATE_LAUNCH,
    SPACEBALL_CUE_STATE_HIT,
    SPACEBALL_CUE_STATE_BARELY
};


struct SpaceballEntity {
    struct AffineSprite *sprite;
    s32 x;
    s32 y;
    s32 z;
};

struct SpaceballEngineData {
    u8 version;
    s32 zoom;   // Value: Camera Position
    struct SpaceballBatter {
        struct AffineSprite *sprite;
        s32 x;
        s32 y;
        s32 z;
        u32 swingTimer;
        struct Animation *animClose;
        struct Animation *animFar;
    } batter;
    struct SpaceballEntity pitcher;
    struct SpaceballEntity umpire;
    struct SpaceballEntity poofR;   // Sprite used when a spaceball is missed (right)
    struct SpaceballEntity poofL;   // Sprite used when a spaceball is missed (left)
    u16 currentStar;    // Counter: Number of Existing BG Stars
    s16 starSprite[SPACEBALL_STAR_AMOUNT];
    struct SpaceballStar {
        s16 x;
        s16 y;
        s16 z;
    } stars[SPACEBALL_STAR_AMOUNT];
    u8 totalMissed;
    u8 spaceballType;
};

struct SpaceballCue {
    u8 state;
    struct AffineSprite *sprite;
    u32 endTime;
    s16 rotation;
    s16 rotationSpeed;
    s32 x;
    s32 y;
    s32 z;
    u32 unk1C; // (90 * number of beats)
    u32 xSpeed; // Used for 'Barely' arc only
    u32 ySpeed; // Used for 'Barely' arc only
    u8 missed;
};


// Engine Definition Data:
extern struct CompressedData *spaceball_buffered_textures[]; // Buffered Textures List
extern struct GraphicsTable spaceball_gfx_table[]; // Graphics Table
extern struct Animation **spaceball_anim_table_batter_close_tables[];
extern struct Animation **spaceball_anim_table_batter_far_tables[];
extern struct Animation **spaceball_anim_table_ball_tables[]; // Spaceball Animations Tables
extern struct Animation *spaceball_anim_table_batter_close[3]; // Batter Animations (Close)
extern struct Animation *spaceball_anim_table_batter_far[3]; // Batter Animations (Far)
extern struct Animation *spaceball_anim_table_ball[3]; // Spaceball Animations
extern struct Animation *spaceball_extra_anim_table_batter_close[3]; // Batter Animations (Close)
extern struct Animation *spaceball_extra_anim_table_batter_far[3]; // Batter Animations (Far)
extern struct Animation *spaceball_extra_anim_table_ball[3]; // Spaceball Animations
extern struct GraphicsTable *spaceball_gfx_tables[];

// Functions:
extern void spaceball_reset_star(u32);              // Initialise/Reset BG Star Position
extern void spaceball_update_stars_x_y(void);       // Update BG Star Positions (X, Y)
extern void spaceball_update_stars_z(void);         // Update BG Star Positions (Z)
extern void spaceball_update_entity(struct AffineSprite *, s32, s32, s32); // Update Entity Position
extern void spaceball_update_batter(struct AffineSprite *, s32, s32, s32, struct Animation *, struct Animation *); // Update Batter Position
extern void spaceball_update_graphics(void);        // Update Entities, Stars & Camera
extern void spaceball_init_gfx3(void);              // GFX_INIT Func_02
extern void spaceball_init_gfx2(void);              // GFX_INIT Func_01
extern void spaceball_init_gfx1(void);              // GFX_INIT Func_00
extern void spaceball_engine_start(u32);            // MAIN - Init
extern void spaceball_engine_event_stub(void);      // ENGINE Func_06 - STUB
extern void spaceball_prepare_pitcher(void);        // ENGINE Func_00 - Pitcher Prepare
extern void spaceball_update_batter_swing(struct SpaceballBatter *); // Update Batter Swing
extern void spaceball_loop_exit_condition(void);    // ENGINE Func_01 - Loop Exit Condition (Tutorial)
extern void spaceball_set_camera_zoom(u32);         // ENGINE Func_02 - Set Camera Zoom
extern void spaceball_set_batter_type(u32);         // ENGINE Func_03 - Set Batter Variant
extern void spaceball_set_ball_type(u32);           // ENGINE Func_05 - Set Next Spaceball Sprite
extern void spaceball_open_ufo(u32);                // ENGINE Func_04 - Set Umpire Animation
extern void spaceball_engine_update(void);          // MAIN - Update
extern void spaceball_engine_stop(void);            // MAIN - Close (STUB)
extern void spaceball_cue_spawn(struct Cue *, struct SpaceballCue *, u32);              // CUE - Spawn
extern u32  spaceball_cue_update_launch(struct Cue *, struct SpaceballCue *, u32, u32); // Update Spaceball (Launch)
extern u32  spaceball_cue_update_hit(struct Cue *, struct SpaceballCue *, u32, u32);    // Update Spaceball (Hit)
extern u32  spaceball_cue_update_barely(struct Cue *, struct SpaceballCue *, u32, u32); // Update Spaceball (Barely)
extern u32  spaceball_cue_update(struct Cue *, struct SpaceballCue *, u32, u32);        // CUE - Update
extern void spaceball_cue_despawn(struct Cue *, struct SpaceballCue *);                 // CUE - Despawn
extern void spaceball_cue_hit(struct Cue *, struct SpaceballCue *, u32, u32);           // CUE - Hit
extern void spaceball_cue_barely(struct Cue *, struct SpaceballCue *, u32, u32);        // CUE - Barely
extern void spaceball_cue_miss(struct Cue *, struct SpaceballCue *);                    // CUE - Miss
extern void spaceball_input_event(u32, u32);        // MAIN - Input Event
extern void spaceball_common_beat_animation(void);  // COMMON Func_00 - STUB
extern void spaceball_common_display_text(void);    // COMMON Func_01 - STUB
