#include "prologues/marching_orders_extra.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct MarchingOrdersEXPrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: MARCHING ORDERS  //  //  //


// [mo_ex_08046234] GFX_INIT Func_02
void mo_ex_08046234(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [mo_ex_08046244] GFX_INIT Func_01
void mo_ex_08046244(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), marching_orders_extra_prologue_gfx_table, 0x2000);
    run_func_after_task(task, mo_ex_08046234, 0);
}


// [mo_ex_08046274] GFX_INIT Func_00
void mo_ex_08046274(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), marching_orders_extra_prologue_buffered_textures);
    run_func_after_task(task, mo_ex_08046244, 0);
}


// [func_080462a4] MAIN - Init
void marching_orders_extra_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    mo_ex_08046274();
    scene_set_video_mode(VIDEO_MODE_2TEXT_1ROT);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, (BGCNT_TILEMAP_SIZE(BG_ROT_TILEMAP_32x32) | BGCNT_256_PALETTE | BGCNT_PRIORITY(BG_PRIORITY_LOW)));

    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_marching_orders_extra_prologue_title, 0, 112, 140, 0, 0, 0, 0);
}


// [mo_ex_08046300] ENGINE Func_00
void mo_ex_08046300(void) {
}


// [func_08046304] MAIN - Update
void marching_orders_extra_prologue_engine_update(void) {
}


// [func_08046308] MAIN - Close
void marching_orders_extra_prologue_engine_stop(void) {
}


// [mo_ex_0804630c] Event 0 - Set Animation Frame (Text)
void mo_ex_0804630c(u32 frame) {
    sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->textSprite, frame);
}
