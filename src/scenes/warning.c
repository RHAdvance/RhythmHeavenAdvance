#include "global.h"
#include "warning.h"
#include "graphics/warning/warning_graphics.h"


/* WARNING SCENE */


extern u8 D_03004498;


// Render Animated Text (Script Function)
void warning_scene_render_anim(void) {
    sprite_create(gSpriteHandler, anim_warning_text_continue, 15, 120, 150, 0, 1, 0, 0);
}


// Scene Stop
void warning_scene_stop(void *sVar, s32 dArg) {
    D_03004498 = TRUE;
}


// Graphics Init. 3
void warning_scene_init_gfx3(void) {
    s32 task;

    func_08007324(TRUE);
    task = palette_fade_in(0, ticks_to_frames(12), 1, 0x7FFF, &warning_pal[0][0], BG_PALETTE_BUFFER(0));
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void warning_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), warning_gfx_table, 0x2000);
    run_func_after_task(task, warning_scene_init_gfx3, 0);
}


// Graphics Init. 1
void warning_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), warning_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void warning_scene_start(void *sVar, s32 dArg) {
    func_0801d860(TRUE);
    D_03004498 = FALSE;
    warning_scene_init_gfx1();
    gWarning->inputsEnabled = FALSE;
    gWarning->timer = 3600;
}


// Scene Update
void warning_scene_update(void *sVar, s32 dArg) {
    if (gWarning->inputsEnabled) {
        if ((D_03004afc != 0) || (--gWarning->timer == 0)) {
            set_pause_beatscript_scene(FALSE);
            gWarning->inputsEnabled = FALSE;
        }
    }
}
