#pragma once

#include "global.h"
#include "engines.h"
#include "engines/night_walk.h"

#include "games/toss_boys/graphics/toss_boys_graphics.h"

// Engine Macros/Enums:
#define TOSS_BOYS_PLAYER_COUNT 3
#define TOSS_BOYS_ACTION_COUNT 4

enum TossBoysVersionsEnum {
    ENGINE_VER_TOSS_BOYS,
    ENGINE_VER_TOSS_REMIX_5,
    ENGINE_VER_TOSS_BOYS_2
};

enum TossBoysAnimationsEnum {
    TOSS_BOYS_ANIM_BEAT_RED,
    TOSS_BOYS_ANIM_BEAT_BLUE,
    TOSS_BOYS_ANIM_BEAT_YELLOW,
    TOSS_BOYS_ANIM_PASS_RED,
    TOSS_BOYS_ANIM_PASS_BLUE,
    TOSS_BOYS_ANIM_PASS_YELLOW,
    TOSS_BOYS_ANIM_DISPENSER,
    TOSS_BOYS_ANIM_BALL1,
    TOSS_BOYS_ANIM_BALL3,
    TOSS_BOYS_ANIM_BALL2,
    TOSS_BOYS_ANIM_BALL_WOBBLE,
    TOSS_BOYS_ANIM_MISS_RED,
    TOSS_BOYS_ANIM_MISS_BLUE,
    TOSS_BOYS_ANIM_MISS_YELLOW,
    TOSS_BOYS_ANIM_SUPER_PASS_RED,
    TOSS_BOYS_ANIM_SUPER_PASS_BLUE,
    TOSS_BOYS_ANIM_SUPER_PASS_YELLOW,
    TOSS_BOYS_ANIM_POP_EFFECT,
    TOSS_BOYS_ANIM_SUPER_BEAT_RED,
    TOSS_BOYS_ANIM_SUPER_BEAT_BLUE,
    TOSS_BOYS_ANIM_SUPER_BEAT_YELLOW,
    TOSS_BOYS_ANIM_CATCH_RED,
    TOSS_BOYS_ANIM_CATCH_BLUE,
    TOSS_BOYS_ANIM_CATCH_YELLOW,
    TOSS_BOYS_ANIM_READY_RED,
    TOSS_BOYS_ANIM_READY_BLUE,
    TOSS_BOYS_ANIM_READY_YELLOW,
    TOSS_BOYS_ANIM_POP_RED,
    TOSS_BOYS_ANIM_POP_BLUE,
    TOSS_BOYS_ANIM_POP_YELLOW,
    TOSS_BOYS_ANIM_BARELY_RED,
    TOSS_BOYS_ANIM_BARELY_BLUE,
    TOSS_BOYS_ANIM_BARELY_YELLOW,
    TOSS_BOYS_ANIM_ARROW_RED,
    TOSS_BOYS_ANIM_ARROW_BLUE,
    TOSS_BOYS_ANIM_ARROW_YELLOW
};

enum TossBoyActionsEnum {
    TOSS_BOY_ACTION_PASS,
    TOSS_BOY_ACTION_SUPER_PASS,
    TOSS_BOY_ACTION_CATCH,
    TOSS_BOY_ACTION_POP
};

enum TossBoysPlayerEnum {
    TOSS_BOYS_PLAYER_RED,
    TOSS_BOYS_PLAYER_BLUE,
    TOSS_BOYS_PLAYER_YELLOW,
    TOSS_BOYS_PLAYER_DISPENSER
};

enum TossBoysPlayerStateEnum {
    TOSS_BOYS_ACTION_PASS,
    TOSS_BOYS_ACTION_SUPER_PASS,
    TOSS_BOYS_ACTION_CATCH,
    TOSS_BOYS_ACTION_POP,
};

// Engine Types:
struct TossBoysEngineData {
    u8 version;
    
    struct DrumTechController drumTech;
    
    s16 playerSprite[TOSS_BOYS_PLAYER_COUNT];

    u8 playerAnimCooldown[TOSS_BOYS_PLAYER_COUNT];
    u8 playerReadyState[TOSS_BOYS_PLAYER_COUNT];
    u8 playerBarelyTimer[TOSS_BOYS_PLAYER_COUNT];

    s16 dispenserSprite;
    s16 ballSprite;

    s8 ballAffineGroup;
    u16 affineRotation;
    s16 affineRotationSpeed;
    u16 affineScaleOffset;

    u8 targetIndex;
    u8 sourceIndex;
    u16 defaultCueDuration;
    s16 throwVelocity;

    s32 ballMotionTaskId;

    u8 ballInFlightFlag;
    u8 barelyActive;
    u8 barelyOscPhase;

    u16 enabledButtonsMask;

    u32 playerButtonLockTimer[TOSS_BOYS_PLAYER_COUNT];

    s16 queuedDrumNoteId;

    s16 pitchOffset;
    u16 pitchOscPhase;

    u16 recoveryTimer;
    u8 recoveryCompleteFlag;

    u16 colorEffectLevel;
    s16 soshiSprite;
    u16 soshiStrumTimer;
    s16 arrowSprite;
};

struct TossBoysCue {
    u8 playerIndex;
    s16 throwSpeed;
    u16 duration;
    u8 fromIndex;
    u8 toIndex;
    s16 drumNoteId;
    u8 actionType;
    u8 inputDisabled;
};


// Engine Definition Data:
extern struct Animation **toss_boys_anim_table[];
extern struct CompressedData *toss_boys_buffered_textures[];
extern struct GraphicsTable *toss_boys_gfx_tables[];
extern struct DrumTechInstrument toss_boys_drumtech_bank[];
extern u16 toss_boys_button_masks[];
extern struct Animation *toss_boys_action_anims[][TOSS_BOYS_PLAYER_COUNT];
extern s8 toss_boys_action_anim_playback[][TOSS_BOYS_PLAYER_COUNT];
extern struct Vector2 toss_boys_bg_pan_targets[];
extern struct Vector2 toss_boys_player_positions[];
extern u8 toss_boys_arrow_anim_ids[];
extern s16 toss_boys_affine_rotation_table[][TOSS_BOYS_ACTION_COUNT];
extern struct SongHeader *toss_boys_ball_bounce_sfx[];
extern struct SongHeader *toss_boys_ball_pop_sfx[];
extern s8 toss_boys_miss_anim_ids[];
extern struct SongHeader *toss_boys_ball_miss_sfx[];
extern u8 toss_boys_throw_speed_table[][TOSS_BOYS_ACTION_COUNT];
extern s8 toss_boys_hit_anim_ids[][TOSS_BOYS_PLAYER_COUNT];
extern s8 toss_boys_barely_anim_ids[][TOSS_BOYS_PLAYER_COUNT];
extern s8 toss_boys_ready_anim_ids[][TOSS_BOYS_PLAYER_COUNT];
extern s8 toss_boys_ready_anim_playback[][TOSS_BOYS_PLAYER_COUNT];
extern s8 toss_boys_beat_anim_ids[][TOSS_BOYS_PLAYER_COUNT];
extern s8 toss_boys_beat_anim_playback[][TOSS_BOYS_PLAYER_COUNT];

// Functions:
extern void toss_boys_init_soshi_sprite(void);
extern void toss_boys_show_soshi_sprite(void); // Engine Event 0x08
extern void toss_boys_soshi_update(void);
extern void toss_boys_play_soshi_strum(void);
extern void toss_boys_update_soshi_timer(void);
extern struct Animation *toss_boys_get_anim(u32 anim); // Get Animation
extern void toss_boys_play_drum_note(u32 id);
extern void toss_boys_queue_drum_note(s16 id);
extern void toss_boys_init_gfx3(void); // Graphics Init. 3
extern void toss_boys_init_gfx2(void); // Graphics Init. 2
extern void toss_boys_init_gfx1(void); // Graphics Init. 1
extern void toss_boys_engine_start(u32 version); // Game Engine Start
extern void toss_boys_engine_event_stub(void); // Engine Event 0x09 (STUB)
extern void toss_boys_update_player_timers(void);
extern void toss_boys_lock_player_buttons(u32 index, u32 value);
extern void toss_boys_update_button_locks(void);
extern void toss_boys_update_ball_affine(void);
extern void toss_boys_update_pitch_modulation(void);
extern void toss_boys_pan_bg_to_target();
extern void toss_boys_clear_color_effect();
extern void toss_boys_engine_update(void); // Game Engine Update
extern void toss_boys_engine_stop(void); // Game Engine Stop
extern void toss_boys_reset_ball();
extern void toss_boys_throw_ball(u32 param, s32 velocity, u32 amplitude, u32 throwSpeed);
extern void toss_boys_throw_ball_event();
extern void toss_boys_set_throw_param();
extern void toss_boys_start_ball_motion(struct TossBoysCue *, s32 offset);
extern void toss_boys_cue_spawn(struct Cue *, struct TossBoysCue *, u32 param); // Cue - Spawn
extern u32  toss_boys_cue_update(struct Cue *, struct TossBoysCue *, u32 runningTime, u32 duration); // Cue - Update
extern void toss_boys_cue_despawn(struct Cue *, struct TossBoysCue *); // Cue - Despawn
extern void toss_boys_process_cue_result(struct Cue *, struct TossBoysCue *, u32 result);
extern void toss_boys_cue_hit(struct Cue *, struct TossBoysCue *, u32 pressed, u32 released); // Cue - Hit
extern void toss_boys_cue_barely(struct Cue *, struct TossBoysCue *, u32 pressed, u32 released); // Cue - Barely
extern void toss_boys_cue_miss(struct Cue *, struct TossBoysCue *); // Cue - Miss
extern void toss_boys_play_player_animation(u32 index, u32 value);
extern void toss_boys_set_player_ready_state(u32 index, u32 value);
extern void toss_boys_set_player_ready_state_event(u32 arg0); // Engine Event 0x05 (?)
extern void toss_boys_tick_affine_transform(void);
extern void toss_boys_input_event(u32 pressed, u32 released); // Input Event
extern void toss_boys_common_beat_animation(void); // Common Event 0 (Beat Animation)
extern void toss_boys_common_display_text(void); // Common Event 1 (Display Text, Unimplemented)
extern void toss_boys_common_init_tutorial(void); // Common Event 2 (Init. Tutorial, Unimplemented)
