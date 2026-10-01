#include "prologues/marching_orders_2.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct MarchingOrders2PrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: MARCHING ORDERS 2  //  //  //


// [func_08046330] GFX_INIT Func_02
void func_08046330(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [func_08046340] GFX_INIT Func_01
void func_08046340(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), marching_orders_2_prologue_gfx_table, 0x2000);
    run_func_after_task(task, func_08046330, 0);
}


// [func_08046370] GFX_INIT Func_00
void func_08046370(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), marching_orders_2_prologue_buffered_textures);
    run_func_after_task(task, func_08046340, 0);
}


// [func_080463a0] MAIN - Init
void marching_orders_2_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    func_08046370();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);

    #ifdef PLUS
    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_marching_orders_2_prologue_title, 0, 112, 140, 0, 0, 0x7f, 0);
    #else
    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_marching_orders_prologue_title, 0, 112, 140, 0, 0, 0x7f, 0);
    #endif
}


// [func_080463fc] ENGINE Func_00
void func_080463fc(void) {
}


// [func_08046400] MAIN - Update
void marching_orders_2_prologue_engine_update(void) {
}


// [func_08046404] MAIN - Close
void marching_orders_2_prologue_engine_stop(void) {
}


// [func_08046408] Event 0 - Set Animation Frame (Text)
void func_08046408(u32 frame) {
    sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->textSprite, frame);
}
