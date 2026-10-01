#include "prologues/tap_trial_2.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct TapTrial2PrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: TAP TRIAL 2  //  //  //


// [func_080477b4] GFX_INIT Func_02
void func_080477b4(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [func_080477c4] GFX_INIT Func_01
void func_080477c4(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), tap_trial_2_prologue_gfx_table, 0x2000);
    run_func_after_task(task, func_080477b4, 0);
}


// [func_080477f4] GFX_INIT Func_00
void func_080477f4(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), tap_trial_2_prologue_buffered_textures);
    run_func_after_task(task, func_080477c4, 0);
}


// [func_08047824] MAIN - Init
void tap_trial_2_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    func_080477f4();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);

    #ifdef PLUS
    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_tap_trial_2_prologue_title, 0, 112, 100, 0, 1, 0x7f, 0x8000);
    #else
    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_tap_trial_prologue_title, 0, 120, 85, 0, 1, 0x7f, 0x8000);
    #endif
}


// [func_08047888] ENGINE Func_00
void func_08047888(void) {
}


// [func_0804788c] MAIN - Update
void tap_trial_2_prologue_engine_update(void) {
}


// [func_08047890] MAIN - Close
void tap_trial_2_prologue_engine_stop(void) {
}


// [func_08047894] Event 0 - Set Animation Frame (Text)
void func_08047894(u32 frame) {
    sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->textSprite, frame);
}


// [func_080478b8] Event 1 - Animate Text
void func_080478b8(void) {
    sprite_set_visible(gSpriteHandler, gPrologueEngineData->textSprite, TRUE);
}
