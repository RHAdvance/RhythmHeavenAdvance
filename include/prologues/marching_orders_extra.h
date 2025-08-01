#pragma once

#include "global.h"
#include "engines.h"

#include "games/marching_orders/graphics/marching_orders_extra_prologue_graphics.h"


  //  //  //  PROLOGUE: MARCHING ORDERS  //  //  //


// Types:
struct MarchingOrdersEXPrologueEngineData {
    u8  ver;        // Value:  Version
    s16 textSprite; // Sprite: Text
};

// Assets:
extern struct CompressedData *marching_orders_extra_prologue_buffered_textures[]; // Buffered Textures
extern struct GraphicsTable marching_orders_extra_prologue_gfx_table[]; // Graphics Table

// Functions:
extern void mo_ex_08046234(void);    // [mo_ex_08046234] GFX_INIT mo_ex_02
extern void mo_ex_08046244(void);    // [mo_ex_08046244] GFX_INIT mo_ex_01
extern void mo_ex_08046274(void);    // [mo_ex_08046274] GFX_INIT mo_ex_00
extern void marching_orders_extra_prologue_engine_start(u32);     // [mo_ex_080462a4] MAIN - Init
extern void mo_ex_08046300(void);    // [mo_ex_08046300] ENGINE mo_ex_00   (STUB)
extern void marching_orders_extra_prologue_engine_update(void);    // [mo_ex_08046304] MAIN - Update    (STUB)
extern void marching_orders_extra_prologue_engine_stop(void);    // [mo_ex_08046308] MAIN - Close     (STUB)
extern void mo_ex_0804630c(u32);     // [mo_ex_0804630c] Event 0 - Set Animation Frame (Text)
