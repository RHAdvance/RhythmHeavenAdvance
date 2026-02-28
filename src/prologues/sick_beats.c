#include "prologues/sick_beats.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gPrologueEngineData ((struct SickBeatsPrologueEngineData *)gCurrentEngineData)


  //  //  //  PROLOGUE: SICK BEATS  //  //  //


// [func_08047c08] GFX_INIT Func_02
void func_08047c08(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [func_08047c18] GFX_INIT Func_01
void func_08047c18(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), sick_beats_prologue_gfx_table, 0x2000);
    run_func_after_task(task, func_08047c08, 0);
}


// [func_08047c48] GFX_INIT Func_00
void func_08047c48(void) {
    u32 task;

    func_0800c604(0);
    func_08006d80();
    task = start_new_texture_loader(get_current_mem_id(), sick_beats_prologue_buffered_textures);
    run_func_after_task(task, func_08047c18, 0);
}


// [func_08047c78] MAIN - Init
void sick_beats_prologue_engine_start(u32 ver) {
    gPrologueEngineData->ver = ver;

    func_08047c48();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);

    gPrologueEngineData->textSprite = sprite_create(gSpriteHandler, anim_sick_beats_prologue_title, 0, 100, 17, 0, 0, 0x7f, 0);
    gPrologueEngineData->virusSprite = sprite_create(gSpriteHandler, anim_sick_beats_prologue_virus, 0, 160, 48, 0, 0, 0x7f, 0);
}


// [func_08047d00] ENGINE Func_00
void func_08047d00(void) {
}


// [func_08047d04] MAIN - Update
void sick_beats_prologue_engine_update(void) {
}


// [func_08047d08] MAIN - Close
void sick_beats_prologue_engine_stop(void) {
}


// [func_08047d0c] Event 0 - Play Animation (Text), Play Animation (Virus)
void func_08047d0c(void) {
    sprite_set_playback(gSpriteHandler, gPrologueEngineData->textSprite, 1, 0x7f, 0);
    sprite_set_playback(gSpriteHandler, gPrologueEngineData->virusSprite, 1, 0x7f, 0);
}
