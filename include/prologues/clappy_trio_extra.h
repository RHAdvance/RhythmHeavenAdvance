#pragma once

#include "global.h"
#include "engines.h"

#include "games/clappy_trio/graphics/clappy_trio_prologue_graphics.h"


  //  //  //  PROLOGUE: THE CLAPPY TRIO  //  //  //


// Types:
struct ClappyTrioEXPrologueEngineData {
    u8  ver;        // Value:  Version
    s16 textSprite; // Sprite: Text
};

// Assets:
extern struct CompressedData *clappy_trio_extra_prologue_buffered_textures[]; // Buffered Textures
extern struct GraphicsTable clappy_trio_extra_prologue_gfx_table[]; // Graphics Table

// Functions:
extern void ct_ex_08045dec(void);    // [ct_ex_08045dec] GFX_INIT ct_ex_02
extern void ct_ex_08045dfc(void);    // [ct_ex_08045dfc] GFX_INIT ct_ex_01
extern void ct_ex_08045e2c(void);    // [ct_ex_08045e2c] GFX_INIT ct_ex_00
extern void clappy_trio_extra_prologue_engine_start(u32);     // [ct_ex_08045e5c] MAIN - Init
extern void ct_ex_08045eb8(void);    // [ct_ex_08045eb8] ENGINE ct_ex_00   (STUB)
extern void clappy_trio_extra_prologue_engine_update(void);    // [ct_ex_08045ebc] MAIN - Update    (STUB)
extern void clappy_trio_extra_prologue_engine_stop(void);    // [ct_ex_08045ec0] MAIN - Close     (STUB)
extern void ct_ex_08045ec4(u32);     // [ct_ex_08045ec4] Event 0 - Set Animation Frame (Text)
