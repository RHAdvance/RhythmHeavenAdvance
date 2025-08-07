#include "prologues/remix_1_extra.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct Remix1EXPrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: REMIX 1  //  //  //


// [r1_ex_08046628] GFX_INIT Func_02
void r1_ex_08046628(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [r1_ex_08046638] GFX_INIT Func_01
void r1_ex_08046638(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), remix_1_extra_prologue_gfx_table, 0x2000);
    run_func_after_task(task, r1_ex_08046628, 0);
}


// [r1_ex_08046668] GFX_INIT Func_00
void r1_ex_08046668(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), remix_1_extra_prologue_buffered_textures);
    run_func_after_task(task, r1_ex_08046638, 0);
}


// [func_08046698] MAIN - Init
void remix_1_extra_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    r1_ex_08046668();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);

    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_remix_1_extra_prologue_title, 0, 112, 128, 0, 0, 0, 0);
}


// [r1_ex_080466f4] ENGINE Func_00
void r1_ex_080466f4(void) {
}


// [func_080466f8] MAIN - Update
void remix_1_extra_prologue_engine_update(void) {
}


// [func_080466fc] MAIN - Close
void remix_1_extra_prologue_engine_stop(void) {
}


// [r1_ex_08046700] Event 0 - Set Animation Frame (Text)
void r1_ex_08046700(u32 frame) {
    sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->textSprite, frame);
}
