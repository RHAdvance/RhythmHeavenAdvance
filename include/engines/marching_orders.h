#pragma once

#include "global.h"
#include "engines.h"

#include "games/marching_orders/graphics/marching_orders_graphics.h"

// Engine Macros/Enums:
enum MarchingOrdersVersionsEnum {
    MARCHING_ORDERS_VER_0,
    MARCHING_ORDERS_VER_REMIX,
    MARCHING_ORDERS_VER_2_UNUSED,
    MARCHING_ORDERS_VER_BUNNY
};

enum MarchingOrdersAnimationsEnum {
    MARCHING_ANIM_TURN_L,
    MARCHING_ANIM_TURN_R,
    MARCHING_ANIM_POINT_L,
    MARCHING_ANIM_POINT_R,
    MARCHING_ANIM_COMMANDER,
    MARCHING_ANIM_STOP_BEAT,
    MARCHING_ANIM_BEAT,
    MARCHING_ANIM_STEP_R,
    MARCHING_ANIM_STEP_L,
    MARCHING_ANIM_HEAD_L,
    MARCHING_ANIM_HEAD_R,
    MARCHING_ANIM_TUTORIAL_ICONS,
    MARCHING_ANIM_ANGRY_PUFF,
    MARCHING_ANIM_CLAP,
    MARCHING_ANIM_COMMANDER_ANNOYED
};

enum MarchingOrdersSoundEffectsEnum {
    MARCHING_SFX_SHOUT_START,
    MARCHING_SFX_SHOUT_STOP,
    MARCHING_SFX_SHOUT_TURN,
    MARCHING_SFX_CMD_ATTENTION,
    MARCHING_SFX_CMD_MARCH,
    MARCHING_SFX_CMD_HALT,
    MARCHING_SFX_CMD_RIGHT_FACE,
    MARCHING_SFX_CMD_RIGHT_FACE_F,
    MARCHING_SFX_CMD_TURN_RIGHT,
    MARCHING_SFX_CMD_LEFT_FACE,
    MARCHING_SFX_CMD_LEFT_FACE_F,
    MARCHING_SFX_CMD_TURN_LEFT
};

enum MarchingOrdersCueEnum {
    MARCHING_CUE_STEP,
    MARCHING_CUE_TURN_LEFT,
    MARCHING_CUE_TURN_RIGHT,
    MARCHING_CUE_HALT
};


// Engine Types:
struct MarchingOrdersEngineData {
    u8 version;
    struct BitmapFontOBJ *font;
    struct Marcher {
        s16 sprite;
        s16 headSprite;
        u8 currentAction;
        u16 idleTimer;
        u8 idled;
    } marchers[4];
    u8 marcherNextFoot;
    u16 playerActionTimer;
    s16 commanderSprite;
    u16 commanderActionTimer;
    s16 textSprite;
    s16 tutorialIcon;
    u8 conveyorEnabled;
    u8 marchersPointing;
};

struct MarchingOrdersCue {
    u8 command;
};

struct MarchingSfxData {
    struct SongHeader *sound;
    u16 volume;
    s16 pitch;
};


// Engine Data:
extern const char D_0805a670[];


// Engine Definition Data:
extern struct Animation **marching_anim_table[];
extern struct CompressedData *marching_buffered_textures[];
extern struct GraphicsTable *marching_gfx_tables[];
extern struct Vector2 D_089e5368[][4];
extern struct MarchingSfxData marching_sfx_table[][12];


// Functions:
extern struct Animation *func_08034100(s32 anim); // Get Animation
extern void marching_init_gfx3(void); // Graphics Init. 3
extern void marching_init_gfx2(void); // Graphics Init. 2
extern void marching_init_gfx1(void); // Graphics Init. 1
extern void marching_engine_start(u32 version); // Game Engine Start
extern void marching_engine_event_stub(void); // Engine Event 06 (STUB)
// extern ? func_080343b8(?);
extern void marching_play_action(); // Engine Event 00 (?)
// extern ? func_080345cc(?);
// extern ? func_080346b0(?);
extern void marching_set_commander_action(u32 action); // Engine Event 01 (?)
extern void marching_set_tutorial_icon(); // Engine Event 02 (?)
extern void marching_enable_conveyor(); // Engine Event 03 (Enable Conveyer)
// extern ? func_0803482c(?);
extern void marching_set_marchers_pointing(u8 enabled); // Engine Event 04 (?)
extern void marching_engine_update(void); // Game Engine Update
extern void marching_engine_stop(void); // Game Engine Close
extern void marching_cue_spawn(struct Cue *, struct MarchingOrdersCue *, u32 command); // Cue - Spawn
extern u32  marching_cue_update(struct Cue *, struct MarchingOrdersCue *, u32 runningTime, u32 duration); // Cue - Update
extern void marching_cue_despawn(struct Cue *, struct MarchingOrdersCue *); // Cue - Despawn
extern void marching_cue_hit(struct Cue *, struct MarchingOrdersCue *, u32 pressed, u32 released); // Cue - Hit
extern void marching_cue_barely(struct Cue *, struct MarchingOrdersCue *, u32 pressed, u32 released); // Cue - Barely
extern void marching_cue_miss(struct Cue *, struct MarchingOrdersCue *); // Cue - Miss
// extern ? func_0803494c(?);
// extern ? func_08034988(?);
// extern ? func_080349ac(?);
// extern ? func_080349d0(?);
extern void marching_input_event(u32 pressed, u32 released); // Input Event
extern void marching_common_beat_animation(void); // Common Event 0 (Beat Animation, Unimplemented)
extern void marching_common_display_text(const char *); // Common Event 1 (Display Text)
extern void marching_common_init_tutorial(void); // Common Event 2 (Init. Tutorial, Unimplemented)
extern void marching_play_sound(u32 sound); // Engine Event 05 (Play Sound)
