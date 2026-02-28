#include "global.h"
#include "disclaimer.h"
#include "graphics/disclaimer/disclaimer_graphics.h"


/* disclaimer SCENE */

extern u8 haveSeenDisclaimer;

// Render Animated Text (Script Function)
void disclaimer_scene_render_anim(void) {
    sprite_create(gSpriteHandler, anim_disclaimer_text_continue, 15, 120, 152, 0, 1, 0, 0);
}


// Scene Stop
void disclaimer_scene_stop(void *sVar, s32 dArg) {
    haveSeenDisclaimer = TRUE;

    SET_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_SEEN_DISCLAIMER);
    flush_save_buffer_to_sram();
}

void disclaimer_scene_wait_if_not_seen(void) {
    s32 task;

    if(!CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_SEEN_DISCLAIMER)) {
        set_beatscript_tempo(20);
    }
    set_pause_beatscript_scene(FALSE);
}

// Graphics Init. 3
void disclaimer_scene_init_gfx3(void) {
    s32 task;

    func_08007324(TRUE);
    task = palette_fade_in(0, ticks_to_frames(12), 1, 0x0000, &disclaimer_pal[0][0], BG_PALETTE_BUFFER(0));
    run_func_after_task(task, disclaimer_scene_wait_if_not_seen, 0);
}


// Graphics Init. 2
void disclaimer_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), disclaimer_gfx_table, 0x2000);
    run_func_after_task(task, disclaimer_scene_init_gfx3, 0);
}


// Graphics Init. 1
void disclaimer_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), disclaimer_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void disclaimer_scene_start(void *sVar, s32 dArg) {
    func_0801d860(TRUE);
    disclaimer_scene_init_gfx1();
    haveSeenDisclaimer = FALSE;
    gdisclaimer->inputsEnabled = FALSE;
    gdisclaimer->timer = 3600;
}


// Scene Update
void disclaimer_scene_update(void *sVar, s32 dArg) {
    if (gdisclaimer->inputsEnabled) {
        if ((D_03004afc != 0) || (--gdisclaimer->timer == 0)) {
            set_pause_beatscript_scene(FALSE);
            gdisclaimer->inputsEnabled = FALSE;
        }
    }
}
