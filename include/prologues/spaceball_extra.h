#pragma once

#include "global.h"
#include "engines.h"

#include "games/spaceball/graphics/spaceball_extra_prologue_graphics.h"



  //  //  //  PROLOGUE: SPACEBALL  //  //  //


// Types:
struct SpaceballEXPrologueEngineData {
    u8  ver;        // Value:  Version
    s16 textSprite; // Sprite: Text
};

// Assets:
extern struct CompressedData *spaceball_extra_prologue_buffered_textures[]; // Buffered Textures
extern struct GraphicsTable spaceball_extra_prologue_gfx_table[]; // Graphics Table

// Functions:
extern void sb_ex_08045208(void);    // [sb_ex_08045208] GFX_INIT sb_ex_02
extern void sb_ex_08045218(void);    // [sb_ex_08045218] GFX_INIT sb_ex_01
extern void sb_ex_08045248(void);    // [sb_ex_08045248] GFX_INIT sb_ex_00
extern void spaceball_extra_prologue_engine_start(u32);     // [sb_ex_08045278] MAIN - Init
extern void sb_ex_080452d4(void);    // [sb_ex_080452d4] ENGINE sb_ex_00   (STUB)
extern void spaceball_extra_prologue_engine_update(void);    // [sb_ex_080452d8] MAIN - Update    (STUB)
extern void spaceball_extra_prologue_engine_stop(void);    // [sb_ex_080452dc] MAIN - Close     (STUB)
extern void sb_ex_080452e0(u32);     // [sb_ex_080452e0] Event 0 - Set Animation Frame (Text)
