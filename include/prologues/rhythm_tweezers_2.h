#pragma once

#include "global.h"
#include "engines.h"

#include "games/rhythm_tweezers/graphics/rhythm_tweezers_2_prologue_graphics.h"


  //  //  //  PROLOGUE: RHYTHM TWEEZERS  //  //  //


// Types:
struct RhythmTweezers2PrologueEngineData {
    u8  ver;        // Value:  Version
    s16 textSprite; // Sprite: Text
};

// Assets:
extern struct CompressedData *rhythm_tweezers_2_prologue_buffered_textures[]; // Buffered Textures
extern struct GraphicsTable rhythm_tweezers_2_prologue_gfx_table[]; // Graphics Table

// Functions:
extern void rhythm_tweezers_2_prologue_gfx_init_02(void);    // [func_08045bec] GFX_INIT Func_02
extern void rhythm_tweezers_2_prologue_gfx_init_01(void);    // [func_08045bfc] GFX_INIT Func_01
extern void rhythm_tweezers_2_prologue_gfx_init_00(void);    // [func_08045c2c] GFX_INIT Func_00
extern void rhythm_tweezers_2_prologue_engine_start(u32);     // [func_08045c5c] MAIN - Init
extern void rhythm_tweezers_2_prologue_engine_func_00(void);    // [func_08045cb8] ENGINE Func_00   (STUB)
extern void rhythm_tweezers_2_prologue_engine_update(void);    // [func_08045cbc] MAIN - Update    (STUB)
extern void rhythm_tweezers_2_prologue_engine_stop(void);    // [func_08045cc0] MAIN - Close     (STUB)
extern void rhythm_tweezers_2_prologue_play_text_anim(void);    // [func_08045cc4] Event 0 - Play Animation (Text)
