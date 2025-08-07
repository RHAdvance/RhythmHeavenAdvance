#include "prologues/rhythm_tweezers_2.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct RhythmTweezers2PrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: RHYTHM TWEEZERS  //  //  //


// [func_08045bec] GFX_INIT Func_02
void rhythm_tweezers_2_prologue_gfx_init_02(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [func_08045bfc] GFX_INIT Func_01
void rhythm_tweezers_2_prologue_gfx_init_01(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), rhythm_tweezers_2_prologue_gfx_table, 0x2000);
    run_func_after_task(task, rhythm_tweezers_2_prologue_gfx_init_02, 0);
}


// [func_08045c2c] GFX_INIT Func_00
void rhythm_tweezers_2_prologue_gfx_init_00(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), rhythm_tweezers_2_prologue_buffered_textures);
    run_func_after_task(task, rhythm_tweezers_2_prologue_gfx_init_01, 0);
}


// [func_08045c5c] MAIN - Init
void rhythm_tweezers_2_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    rhythm_tweezers_2_prologue_gfx_init_00();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);

    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_rhythm_tweezers_2_prologue_title, 0, 60, 64, 0, 0, 0x7f, 0);
}


// [func_08045cb8] ENGINE Func_00
void rhythm_tweezers_2_prologue_engine_func_00(void) {
}


// [func_08045cbc] MAIN - Update
void rhythm_tweezers_2_prologue_engine_update(void) {
}


// [func_08045cc0] MAIN - Close
void rhythm_tweezers_2_prologue_engine_stop(void) {
}


// [func_08045cc4] Event 0 - Play Animation (Text)
void rhythm_tweezers_2_prologue_play_text_anim(void) {
    sprite_set_playback(gSpriteHandler, gPrologueEngineData->textSprite, 1, 0x7f, 0);
}
