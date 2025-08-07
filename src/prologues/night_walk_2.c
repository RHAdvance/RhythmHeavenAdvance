#include "prologues/night_walk_2.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct NightWalk2PrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: NIGHT WALK  //  //  //


// [func_080457b4] GFX_INIT Func_02
void night_walk_2_gfx_init_func_02(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [func_080457c4] GFX_INIT Func_01
void night_walk_2_gfx_init_func_01(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), night_walk_2_prologue_gfx_table, 0x2000);
    run_func_after_task(task, night_walk_2_gfx_init_func_02, 0);
}


// [func_080457f4] GFX_INIT Func_00
void night_walk_2_gfx_init_func_00(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), night_walk_2_prologue_buffered_textures);
    run_func_after_task(task, night_walk_2_gfx_init_func_01, 0);
}


// [func_08045824] MAIN - Init
void night_walk_2_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    night_walk_2_gfx_init_func_00();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);

    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_night_walk_2_prologue_title, 0, 95, 120, 0, 0, 0x7f, 0);
    gPrologueEngineData->playYanSprite = sprite_create(gSpriteHandler, anim_night_walk_2_prologue_play_yan, 0, 60, 120, 0, 0, 0x7f, 0);
    gPrologueEngineData->balloonsSprite = sprite_create(gSpriteHandler, anim_night_walk_2_prologue_balloons, 0, 60, 120, 0, 1, 0, 0);
}


// [func_080458e0] ENGINE Func_00
void night_walk_2_engine_func_00(void) {
}


// [func_080458e4] MAIN - Update
void night_walk_2_prologue_engine_update(void) {
}


// [func_080458e8] MAIN - Close
void night_walk_2_prologue_engine_stop(void) {
}


// [func_080458ec] Event 0 - Play Animation (Play-yan); Event 1 - Play Animation (Text)
void night_walk_2_play_animation_event(u32 event) {
    switch (event) {
        case 0: // Event 0 - Play Animation (Play-yan)
            sprite_set_playback(gSpriteHandler, gPrologueEngineData->playYanSprite, 1, 0x7f, 0);
            break;
        case 1: // Event 1 - Play Animation (Text)
            sprite_set_playback(gSpriteHandler, gPrologueEngineData->textSprite, 1, 0x7f, 0);
            break;
    }
}
