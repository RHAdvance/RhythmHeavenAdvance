#pragma once

#include "global.h"
#include "engines.h"

#include "games/fireworks/graphics/fireworks_graphics.h"

// Engine Macros/Enums:
#define FIREWORKS_PARTICLE_AMOUNT 72

enum FireworksPatternsEnum {
    FIREWORKS_PATTERN_L3,           // Left;    3 Layers
    FIREWORKS_PATTERN_C3,           // Centre;  3 Layers
    FIREWORKS_PATTERN_R3,           // Right;   3 Layers
    FIREWORKS_PATTERN_LL2,          // Far-Left;    2 Layers
    FIREWORKS_PATTERN_CL2,          // Mid-Left;    2 Layers (unused)
    FIREWORKS_PATTERN_CR2,          // Mid-Right;   2 Layers (unused)
    FIREWORKS_PATTERN_RR2,          // Far-Right;   2 Layers
    FIREWORKS_PATTERN_L3_BARELY,    // Centre;  1 Layer
    FIREWORKS_PATTERN_C3_BARELY,    // Centre;  1 Layer
    FIREWORKS_PATTERN_R3_BARELY,    // Centre;  1 Layer
    FIREWORKS_PATTERN_LL2_BARELY,   // Centre;  1 Layer
    FIREWORKS_PATTERN_CL2_BARELY,   // Centre;  1 Layer (unused)
    FIREWORKS_PATTERN_CR2_BARELY,   // Centre;  1 Layer (unused)
    FIREWORKS_PATTERN_RR2_BARELY,   // Centre;  1 Layer
    FIREWORKS_PATTERN_SP_STAR,      // Centre;  Special - Large Star
    FIREWORKS_PATTERN_SP_CIRCLE,    // Centre;  Special - Circle
    FIREWORKS_PATTERN_SP_SPIRAL,    // Centre;  Special - Spiral
    FIREWORKS_PATTERN_SP_SMILE,     // Centre;  Special - Smile
    FIREWORKS_PATTERN_SP_TSUNKU,    // Centre;  Special - Tsunku (unused)
    FIREWORKS_PATTERN_TAIKO_BOMBER, // Hawfinch Taiko Bomber
};

enum FireworksParticlesEnum {
    FIREWORKS_PARTICLE_RED,
    FIREWORKS_PARTICLE_GREEN,
    FIREWORKS_PARTICLE_BLUE,
    FIREWORKS_PARTICLE_MULTI
};

enum FireworksPatternModesEnum {
    FIREWORKS_PATTERN_MODE_0,
    FIREWORKS_PATTERN_MODE_1,
    FIREWORKS_PATTERN_MODE_TAIKO_BOMBER,
    FIREWORKS_PATTERN_MODE_USE_TABLE
};

enum FireworksCueTypesEnum {
    FIREWORKS_CUE_TYPE_SPIRIT_SPARKLER,
    FIREWORKS_CUE_TYPE_NORMAL_FIREWORK,
    FIREWORKS_CUE_TYPE_HAWFINCH_TAIKO_BOMBER
};

enum FireworksSoundsEnum {
    FIREWORKS_SFX_COME_ON,
    FIREWORKS_SFX_ONE,
    FIREWORKS_SFX_TWO,
    FIREWORKS_SFX_THREE,
    FIREWORKS_SFX_NUEI
};


// Engine Types:
struct FireworksEngineData {
    u8  version;        // Version Number
    struct BitmapFontOBJ *unk4;  // Font?
    s16 textSprite;     // Tutorial Text (Sprite)
    struct FireworksParticle {
        s16 sprite;     // Sprite
        u8  active;     // Currently in-use.
        s32 x;          // X Position
        s32 y;          // Y Position
        s32 velX;       // X Velocity
        s32 velY;       // Y Velocity
        u8  initAngle;  // Trajectory Angle
        s32 initVel;    // Trajectory Velocity
        u8  colour;     // Colour ID { 0..3 }
    } particles[FIREWORKS_PARTICLE_AMOUNT];        // Firework Particle Entities
    s16 skipTutorialSprite; // Unused "Start to Skip" Text (Sprite)
    u8  screenBrightness;   // Screen Brightness (for Taiko Bomber screen flash)
    u8  patternTableNext;   // Current Position in Fireworks 1 Pattern Table
    u8  patternMode;        // Pattern-Handling Mode { 0..3 }
    u8  patternDefault;     // Pattern ID to use if Pattern Mode is not within { 0..3 }
};

struct FireworksCue {
    s16 sprite;     // Sprite
    s32 x;          // X Position
    s32 y;          // Y Position
    s32 velX;       // X Velocity
    s32 velY;       // Y Velocity
    s32 targetX;    // Target X Position
    s32 targetY;    // Target Y Position
    u8  pattern;    // Pattern ID
    u8  state;      // Current State (range varies between cues)
    u8  type;       // Cue Type { 0..2 }
    u8  exploded;   // Has Exploded
};

struct FireworksPatternColours {
    s32 inner;
    s32 middle;
    s32 outer;
};

struct FireworksParticleTrajectory {
    s32 initAngle; // Uses precision of sins2 table.
    s32 initVelocity;
};


// Engine Data:
extern const char D_0805a3d0[];
extern const struct FireworksPatternColours fireworks_particle_combinations[];
extern const s32 fireworks_particle_durations[];
extern const struct FireworksParticleTrajectory fireworks_mars_pattern[];
extern const s32 fireworks_1_pattern_sequence[];


// Engine Definition Data:
extern struct CompressedData *fireworks_buffered_textures[]; // Buffered Textures List
extern struct GraphicsTable *fireworks_gfx_tables[]; // Graphics Table Index
extern u16 fireworks_cue_durations[]; // Cue Expiration Times


// Functions:
extern void fireworks_init_gfx3(void); // Graphics Init. 3
extern void fireworks_init_gfx2(void); // Graphics Init. 2
extern void fireworks_init_gfx1(void); // Graphics Init. 1
extern void fireworks_engine_start(u32 version); // Game Engine Start
extern void fireworks_set_pattern_mode(u32); // Engine Event 00 (Set Pattern Mode)
extern void fireworks_play_sound(u32); // Engine Event 01 (Play Sound)
extern void fireworks_set_pattern(u32); // Engine Event 02 (Set Pattern)
extern void fireworks_update_explosion(void); // Update Particles
extern void fireworks_create_explosion(u8, s32, s32); // Create Explosion
extern void fireworks_engine_update(void); // Game Engine Update
extern void fireworks_engine_stop(void); // Game Engine Stop
extern void fireworks_cue_spawn(struct Cue *, struct FireworksCue *, u32 type); // Cue - Spawn
extern u32  fireworks_cue_update(struct Cue *, struct FireworksCue *, u32 runningTime, u32 duration); // Cue - Update
extern void fireworks_cue_despawn(struct Cue *, struct FireworksCue *); // Cue - Despawn
extern void fireworks_cue_hit(struct Cue *, struct FireworksCue *, u32 pressed, u32 released); // Cue - Hit
extern void fireworks_cue_barely(struct Cue *, struct FireworksCue *, u32 pressed, u32 released); // Cue - Barely
extern void fireworks_cue_miss(struct Cue *, struct FireworksCue *); // Cue - Miss
extern void fireworks_input_event(u32 pressed, u32 released); // Input Event
extern void fireworks_common_beat_animation(void); // Common Event 0 (Beat Animation, Unimplemented)
extern void fireworks_common_display_text(char *); // Common Event 1 (Display Text)
extern void fireworks_common_init_tutorial(struct Scene *); // Common Event 2 (Init. Tutorial)
