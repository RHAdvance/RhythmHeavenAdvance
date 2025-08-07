#include "prologues/clappy_trio_extra.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct ClappyTrioEXPrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: THE CLAPPY TRIO  //  //  //


// [ct_ex_08045dec] GFX_INIT Func_02
void ct_ex_08045dec(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [ct_ex_08045dfc] GFX_INIT Func_01
void ct_ex_08045dfc(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), clappy_trio_extra_prologue_gfx_table, 0x2000);
    run_func_after_task(task, ct_ex_08045dec, 0);
}


// [ct_ex_08045e2c] GFX_INIT Func_00
void ct_ex_08045e2c(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), clappy_trio_extra_prologue_buffered_textures);
    run_func_after_task(task, ct_ex_08045dfc, 0);
}


// [func_08045e5c] MAIN - Init
void clappy_trio_extra_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    ct_ex_08045e2c();
    scene_set_video_mode(VIDEO_MODE_2TEXT_1ROT);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, (BGCNT_TILEMAP_SIZE(BG_ROT_TILEMAP_32x32) | BGCNT_256_PALETTE | BGCNT_PRIORITY(BG_PRIORITY_LOW)));

    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_clappy_trio_extra_prologue_title, 0, 120, 100, 0, 0, 0, 0);
}


// [ct_ex_08045eb8] ENGINE Func_00
void ct_ex_08045eb8(void) {
}


// [func_08045ebc] MAIN - Update
void clappy_trio_extra_prologue_engine_update(void) {
}


// [func_08045ec0] MAIN - Close
void clappy_trio_extra_prologue_engine_stop(void) {
}


// [ct_ex_08045ec4] Event 0 - Set Animation Frame (Text)
void ct_ex_08045ec4(u32 frame) {
    sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->textSprite, frame);
}
