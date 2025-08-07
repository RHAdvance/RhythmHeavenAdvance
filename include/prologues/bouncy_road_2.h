#pragma once

#include "global.h"
#include "engines.h"

#include "games/bouncy_road/graphics/bouncy_road_2_prologue_graphics.h"


  //  //  //  PROLOGUE: BOUNCY ROAD  //  //  //


// Types:
struct BouncyRoad2PrologueEngineData {
    u8  ver;            // Value:  Version
    s16 textSprite;     // Sprite: Text
    s16 bouncersSprite; // Sprite: Bouncers
};

// Assets:
extern struct CompressedData *bouncy_road_2_prologue_buffered_textures[]; // Buffered Textures
extern struct GraphicsTable bouncy_road_2_prologue_gfx_table[]; // Graphics Table

// Functions:
extern void bouncy_road_2_prologue_gfx_init_02(void);    // [func_08045a90] GFX_INIT Func_02
extern void bouncy_road_2_prologue_gfx_init_01(void);    // [func_08045aa0] GFX_INIT Func_01
extern void bouncy_road_2_prologue_gfx_init_00(void);    // [func_08045ad0] GFX_INIT Func_00
extern void bouncy_road_2_prologue_engine_start(u32);     // [func_08045b00] MAIN - Init
extern void bouncy_road_2_engine_func_00(void);    // [func_08045b88] ENGINE Func_00   (STUB)
extern void bouncy_road_2_prologue_engine_update(void);    // [func_08045b8c] MAIN - Update    (STUB)
extern void bouncy_road_2_prologue_engine_stop(void);    // [func_08045b90] MAIN - Close     (STUB)
extern void bouncy_road_2_prologue_play_animation(u32);     // [func_08045b94] Event 0 - Play Animation (Bouncers); Event 1 - Play Animation (Text)
