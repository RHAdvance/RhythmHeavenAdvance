#pragma once

#include "global.h"
#include "engines.h"

#include "games/tram_and_pauline/graphics/tram_pauline_graphics.h"

// Engine Macros/Enums:
enum TramPaulineVersionsEnum {
    ENGINE_VER_TRAM_PAULINE_TUTORIAL,
    ENGINE_VER_TRAM_PAULINE,
    ENGINE_VER_TRAM_PAULINE_REMIX_3,
    ENGINE_VER_TRAM_PAULINE_NO_CURTAIN
};


// Engine Types:
struct TramPaulineEngineData {
    u8 version; // 0
    // 3 bytes of alignment
    struct Fox { 
        s16 sprite; // 0x4
        u8 unk_5; // 0x6
        u32 x; // 0x8
        u32 y; // 0xc
        u32 unk_F; // 0x10
        u8 unk_7; // 0x14
        u8 unk_14; // 0x15
        // it probably aligns itself to 0x18 here, 0x18-0x4 = 0x14, which is how big the struct should be
    } foxes[2]; // 0x4-0x2c

    s16 trampolineSprite; // 2c
    u8 unk_2e; 
    s16 trampolineSprite2; // 30
    u8 unk_32;
    u8 pad[0x5]; // 33, 34, 35, 36, 37 (alignment?)
    // Mystical magical byte that doesn't exist 
    struct BitmapFontOBJ *font; // 0x38
    s16 textSprite; // 0x3c ... :3c??
    s16 skipTutorialSprite; // 0x3e
    u8 unk_40;
    s32 curtainScroll; // 0x44 - 0x48 
}; 
struct TramPaulineCue {
    u8 character;
};


// Engine Data:
extern const char D_0805a910[];
extern const u32 D_0805a914[];
extern const u32 D_0805a91c[];


// Engine Definition Data:
extern struct CompressedData *tram_pauline_buffered_textures[];
extern struct GraphicsTable *tram_pauline_gfx_tables[];
extern struct Animation *tram_pauline_anim_table[];


// Functions:
extern void tram_pauline_init_gfx3(void); // Graphics Init. 3
extern void tram_pauline_init_gfx2(void); // Graphics Init. 2
extern void tram_pauline_init_gfx1(void); // Graphics Init. 1
extern void tram_pauline_engine_start(u32 version); // Game Engine Start
extern void func_08040064(); // Engine Event 0x00 (?)
extern void func_080400d0(u8 arg0); // Engine Event 0x01 (?)
// extern ? func_0804016c(?);
// extern ? func_08040314(?);
extern void func_08040434(); // Engine Event 0x02 (?)
// extern ? func_080404c4(?);
// extern ? func_08040718(?);
extern void tram_pauline_engine_update(void); // Game Engine Update
extern void tram_pauline_engine_stop(void); // Game Engine Stop
extern void tram_pauline_cue_spawn(struct Cue *, struct TramPaulineCue *, u32 character); // Cue - Spawn
extern u32  tram_pauline_cue_update(struct Cue *, struct TramPaulineCue *, u32 runningTime, u32 duration); // Cue - Update
extern void tram_pauline_cue_despawn(struct Cue *, struct TramPaulineCue *); // Cue - Despawn
extern void tram_pauline_cue_hit(struct Cue *, struct TramPaulineCue *, u32 pressed, u32 released); // Cue - Hit
extern void tram_pauline_cue_barely(struct Cue *, struct TramPaulineCue *, u32 pressed, u32 released); // Cue - Barely
extern void tram_pauline_cue_miss(struct Cue *, struct TramPaulineCue *); // Cue - Miss
extern void tram_pauline_input_event(u32 pressed, u32 released); // Input Event
extern void tram_pauline_common_beat_animation(void); // Common Event 0 (Beat Animation)
extern void tram_pauline_common_display_text(const char *); // Common Event 1 (Display Text)
extern void tram_pauline_common_init_tutorial(struct Scene *); // Common Event 2 (Init. Tutorial)
