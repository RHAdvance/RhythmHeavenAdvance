#pragma once

#include "global.h"
#include "engines.h"

#include "games/karate_man/graphics/karate_man_extra_prologue_graphics.h"


  //  //  //  PROLOGUE: KARATE MAN  //  //  //


// Types:
struct KarateManExtraPrologueEngineData {
    u8  ver;        // Value:  Version
    s16 textSprite; // Sprite: Text
    s16 kickSprite; // Sprite: Kick
};

// Assets:
extern struct CompressedData *karate_man_extra_prologue_buffered_textures[]; // Buffered Textures
extern struct GraphicsTable karate_man_extra_prologue_gfx_table[]; // Graphics Table

// Functions:
extern void karate_man_extra_init_gfx2(void);    // [func_0804550c] GFX_INIT Func_02
extern void karate_man_extra_init_gfx1(void);    // [func_0804551c] GFX_INIT Func_01
extern void karate_man_extra_init_gfx0(void);    // [func_0804554c] GFX_INIT Func_00
extern void karate_man_extra_prologue_engine_start(u32);     // [func_0804557c] MAIN - Init
extern void karate_man_extra_engine_func(void);    // [func_080455f8] ENGINE Func_00   (STUB)
extern void karate_man_extra_prologue_engine_update(void);    // [func_080455fc] MAIN - Update    (STUB)
extern void karate_man_extra_prologue_engine_stop(void);    // [func_08045600] MAIN - Close     (STUB)
extern void karate_man_extra_set_text_frame(u32);     // [func_08045604] Event 0 - Set Animation Frame (Text)
extern void karate_man_extra_play_kick_anim(void);    // [func_08045628] Event 1 - Play Animation (Kick)
