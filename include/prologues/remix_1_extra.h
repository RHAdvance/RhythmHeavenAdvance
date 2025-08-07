#pragma once

#include "global.h"
#include "engines.h"

#include "games/remix_1/graphics/remix_1_prologue_graphics.h"


  //  //  //  PROLOGUE: REMIX 1  //  //  //


// Types:
struct Remix1EXPrologueEngineData {
    u8  ver;        // Value:  Version
    s16 textSprite; // Sprite: Text
};

// Assets:
extern struct CompressedData *remix_1_extra_prologue_buffered_textures[]; // Buffered Textures List
extern struct GraphicsTable remix_1_extra_prologue_gfx_table[]; // Graphics Table

// Functions:
extern void r1_ex_08046628(void);    // [r1_ex_08046628] GFX_INIT r1_ex_02
extern void r1_ex_08046638(void);    // [r1_ex_08046638] GFX_INIT r1_ex_01
extern void r1_ex_08046668(void);    // [r1_ex_08046668] GFX_INIT r1_ex_00
extern void remix_1_extra_prologue_engine_start(u32);     // [r1_ex_08046698] MAIN - Init
extern void r1_ex_080466f4(void);    // [r1_ex_080466f4] ENGINE r1_ex_00   (STUB)
extern void remix_1_extra_prologue_engine_update(void);    // [r1_ex_080466f8] MAIN - Update    (STUB)
extern void remix_1_extra_prologue_engine_stop(void);    // [r1_ex_080466fc] MAIN - Close     (STUB)
extern void r1_ex_08046700(u32);     // [r1_ex_08046700] Event 0 - Set Animation Frame (Text)
