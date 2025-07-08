#pragma once

#include "global.h"
#include "engines.h"

#include "games/rhythm_tweezers/graphics/rhythm_tweezers_extra_prologue_graphics.h"


  //  //  //  PROLOGUE: RHYTHM TWEEZERS  //  //  //


// Types:
struct RhythmTweezersExtraPrologueEngineData {
    u8  ver;        // Value:  Version
    s16 textSprite; // Sprite: Text
    s16 tempoSprite; // Sprite: Tempo
};

// Assets:
extern struct CompressedData *rhythm_tweezers_extra_prologue_buffered_textures[]; // Buffered Textures
extern struct GraphicsTable rhythm_tweezers_extra_prologue_gfx_table[]; // Graphics Table

// Functions:
extern void rhythm_tweezers_extra_prologue_init_gfx3(void);    // [func_08045bec] GFX_INIT Func_02
extern void rhythm_tweezers_extra_prologue_init_gfx2(void);    // [func_08045bfc] GFX_INIT Func_01
extern void rhythm_tweezers_extra_prologue_init_gfx1(void);    // [func_08045c2c] GFX_INIT Func_00
extern void rhythm_tweezers_extra_prologue_engine_start(u32);     // [func_08045c5c] MAIN - Init
extern void rhythm_tweezers_extra_prologue_func_00(void);    // [func_08045cb8] ENGINE Func_00   (STUB)
extern void rhythm_tweezers_extra_prologue_engine_update(void);    // [func_08045cbc] MAIN - Update    (STUB)
extern void rhythm_tweezers_extra_prologue_engine_stop(void);    // [func_08045cc0] MAIN - Close     (STUB)
extern void rhythm_tweezers_extra_prologue_event_play_animation(void);    // [func_08045cc4] Event 0 - Play Animation (Text)
