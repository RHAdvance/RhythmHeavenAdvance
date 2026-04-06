#include "global.h"
#include "results.h"
#include "graphics/results/results_graphics.h"
#include "src/code_080092cc.h"


/* RESULTS SCENE 1 (DEBUG-TYPE) */


// Init. Static Variables
void results_scene_init_memory(void) {
}


// Graphics Init. 3
void results_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), debug_results_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void results_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), debug_results_gfx_table, 0x3000);
    run_func_after_task(task, results_scene_init_gfx3, 0);
}


// Graphics Init. 1
void results_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), results_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
}


// Scene Start
void results_scene_start(void *sVar, s32 dArg) {
    func_08007324(FALSE);
    func_080073f0();
    gResults->bgFont = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    gResults->objFont = scene_create_obj_font_printer(0x300, 4);
    import_all_scene_objects(gSpriteHandler, gResults->objFont, debug_results_scene_objects, D_0300558c);
    results_scene_init_gfx1();
    gResults->inputsEnabled = FALSE;
    set_next_scene(&scene_debug_menu);
}


// Scene Update (Paused)
void results_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void results_scene_update(void *sVar, s32 dArg) {
    if (!results_scene_inputs_enabled()) {
        return;
    }

    if (D_03004afc & A_BUTTON) {
        set_pause_beatscript_scene(FALSE);
        gResults->inputsEnabled = FALSE;
        play_sound_w_pitch_volume(&s_menu_se20_seqData, INT_TO_FIXED(0.5), INT_TO_FIXED(0.0));
        rumble_play_menu_confirm();
    }
}


// Check if Scene Can Receive Inputs
u32 results_scene_inputs_enabled(void) {
    if (gResults->inputsEnabled) {
        return TRUE;
    }

    return FALSE;
}


// Scene Stop
void results_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}
