#include "prologues/karate_man_2.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct KarateMan2PrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: KARATE MAN  //  //  //


// [func_0804550c] GFX_INIT Func_02
void karate_man_2_prologue_gfx_init_02(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [func_0804551c] GFX_INIT Func_01
void karate_man_2_prologue_gfx_init_01(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), karate_man_2_prologue_gfx_table, 0x2000);
    run_func_after_task(task, karate_man_2_prologue_gfx_init_02, 0);
}


// [func_0804554c] GFX_INIT Func_00
void karate_man_2_prologue_gfx_init_00(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), karate_man_2_prologue_buffered_textures);
    run_func_after_task(task, karate_man_2_prologue_gfx_init_01, 0);
}


// [func_0804557c] MAIN - Init
void karate_man_2_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    karate_man_2_prologue_gfx_init_00();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);

    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_karate_man_2_prologue_title, 0, 110, 80, 0, 0, 0, 0);
    gPrologueEngineData->kickSprite = sprite_create(gSpriteHandler, anim_karate_man_2_prologue_kick, 0, 96, 110, 0, 0, 0, 0);
}


// [func_080455f8] ENGINE Func_00
void karate_man_2_prologue_engine_func_00(void) {
}


// [func_080455fc] MAIN - Update
void karate_man_2_prologue_engine_update(void) {
}


// [func_08045600] MAIN - Close
void karate_man_2_prologue_engine_stop(void) {
}


// [func_08045604] Event 0 - Set Animation Frame (Text)
void karate_man_2_prologue_set_text_frame(u32 frame) {
    sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->textSprite, frame);
}


// [func_08045628] Event 1 - Play Animation (Kick)
void karate_man_2_prologue_play_kick_anim(void) {
    sprite_set_anim_cel(gSpriteHandler, gPrologueEngineData->kickSprite, 1);
    sprite_set_playback(gSpriteHandler, gPrologueEngineData->kickSprite, 1, 0x7f, 0);
}
