#pragma once

#include "global.h"
#include "engines.h"

#include "games/ninja_bodyguard/graphics/ninja_bodyguard_graphics.h"

// Engine Macros/Enums:
enum NinjaBodyguardVersionsEnum {
    ENGINE_VER_NINJA_BODYGUARD,
    ENGINE_VER_NINJA_REINCARNATE
};

enum NinjaBodyguardAnimationsEnum {
    NINJA_ANIM_LORD_BLINK,
    NINJA_ANIM_LORD_SCARED1,
    NINJA_ANIM_LORD_SCARED2,
    NINJA_ANIM_LORD_WALK,
    NINJA_ANIM_HEART_EYES,
    NINJA_ANIM_ARCHER_DRAW,
    NINJA_ANIM_ARROW_TO_WALL,
    NINJA_ANIM_ARROW_IN_WALL1,
    NINJA_ANIM_ARROW_IN_WALL2,
    NINJA_ANIM_ARROW_IN_WALL3,
    NINJA_ANIM_ARROW_DEFLECT_L,
    NINJA_ANIM_ARROW_DEFLECT_R,
    NINJA_ANIM_ARCHER_FIRE,
    NINJA_ANIM_ARROW_PIECES,
    NINJA_ANIM_ARROW_TO_NINJA,
    NINJA_ANIM_SWING_R,
    NINJA_ANIM_SWING_L,
    NINJA_ANIM_SLICE_R,
    NINJA_ANIM_SLICE_L,
    NINJA_ANIM_APPEAR,
    NINJA_ANIM_RAISE_SWORD,
    NINJA_ANIM_BUTTON_INDICATOR,
    NINJA_ANIM_CUTSCENE_ARROW
};


// Engine Types:
struct NinjaBodyguardEngineData {
    u8 pad00[0x2D0];
    s16 lordId;
    u8 pad01[0x300 - (0x2D0 + sizeof(s16))];
};

struct NinjaBodyguardCue {
    /* add fields here */
};

struct SpriteVector3 {
    s16 x;
    s16 y;
    s16 z;
};


// Engine Definition Data:
extern struct Animation **ninja_bodyguard_anim_table[];
extern struct SpriteVector3 D_089e69cc[];
extern struct CompressedData *ninja_bodyguard_buffered_textures[];
extern struct GraphicsTable *ninja_bodyguard_gfx_tables[];


// Functions:
extern struct Animation *ninja_get_anim(u32 anim); // Get Animation
// extern ? func_0803bda8(?);
extern void func_0803be04(); // Engine Event 10 (?)
// extern ? func_0803be44(?);
extern void func_0803be88(); // Engine Event 11 (?)
// extern ? func_0803bec4(?);
// extern ? func_0803bf14(?);
extern void func_0803bf74(); // Engine Event 07 (?)
extern void func_0803c034(); // Engine Event 08 (?)
extern void func_0803c08c(); // Engine Event 09 (?)
// extern ? func_0803c190(?);
// extern ? func_0803c20c(?);
// extern ? func_0803c260(?);
// extern ? func_0803c28c(?);
extern void func_0803c2b8(); // Engine Event 0B (?)
// extern ? func_0803c2f4(?);
// extern ? func_0803c3c4(?);
extern void func_0803c400(); // Engine Event 0C (?)
// extern ? func_0803c43c(?);
// extern ? func_0803c52c(?);
// extern ? func_0803c5c0(?);
extern void func_0803c5cc(); // Engine Event 03 (?)
extern void func_0803c5f8(); // Engine Event 04 (?)
extern void func_0803c638(); // Engine Event 05 (?)
extern void func_0803c6fc(); // Engine Event 0D (?)
// extern ? func_0803c710(?);
// extern ? func_0803c834(?);
// extern ? func_0803c8c4(?);
extern void func_0803c960(); // Engine Event 06 (?)
// extern ? func_0803c964(?);
// extern ? func_0803c9f4(?);
extern void func_0803c9f8(); // Engine Event 00 (?)
extern void func_0803ca8c(); // Engine Event 01 (?)
extern void func_0803cad0(); // Engine Event 02 (?)
extern void func_0803cb0c(); // Engine Event 0A (?)
extern void ninja_bodyguard_init_gfx3(void); // Graphics Init. 3
extern void ninja_bodyguard_init_gfx2(void); // Graphics Init. 2
extern void ninja_bodyguard_init_gfx1(void); // Graphics Init. 1
extern void ninja_bodyguard_engine_start(u32 version); // Game Engine Start
extern void ninja_bodyguard_engine_event_stub(void); // Engine Event 12 (STUB)
extern void func_0803ccb4(); // Engine Event 0E (?)
extern void func_0803cce0(); // Engine Event 0F (?)
extern void ninja_bodyguard_engine_update(void); // Game Engine Update
extern void ninja_bodyguard_engine_stop(void); // Game Engine Stop
extern void ninja_bodyguard_cue_spawn(struct Cue *, struct NinjaBodyguardCue *, u32 unused); // Cue - Spawn
extern u32  ninja_bodyguard_cue_update(struct Cue *, struct NinjaBodyguardCue *, u32 runningTime, u32 duration); // Cue - Update
extern void ninja_bodyguard_cue_despawn(struct Cue *, struct NinjaBodyguardCue *); // Cue - Despawn
extern void ninja_bodyguard_cue_hit(struct Cue *, struct NinjaBodyguardCue *, u32 pressed, u32 released); // Cue - Hit
extern void ninja_bodyguard_cue_barely(struct Cue *, struct NinjaBodyguardCue *, u32 pressed, u32 released); // Cue - Barely
extern void ninja_bodyguard_cue_miss(struct Cue *, struct NinjaBodyguardCue *); // Cue - Miss
extern void ninja_bodyguard_input_event(u32 pressed, u32 released); // Input Event
extern void ninja_bodyguard_common_beat_animation(void); // Common Event 0 (Beat Animation, Unimplemented)
extern void ninja_bodyguard_common_display_text(void); // Common Event 1 (Display Text, Unimplemented)
