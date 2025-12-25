#include "global.h"
#include "disclamer.h"
#include "graphics/disclamer/disclamer_graphics.h"


/* DISCLAMER SCENE */

extern u8 haveSeenDisclamer, isInDisclamer;

// Render Animated Text (Script Function)
void disclamer_scene_render_anim(void) {
    sprite_create(gSpriteHandler, anim_disclamer_text_continue, 15, 120, 152, 0, 1, 0, 0);
}


// Scene Stop
void disclamer_scene_stop(void *sVar, s32 dArg) {
    haveSeenDisclamer = TRUE;
    isInDisclamer = FALSE;

    set_advance_flag(&D_030046a8->data, ADVANCE_FLAG_SEEN_DISCLAMER);
    flush_save_buffer_to_sram();
}

void disclamer_scene_wait_if_not_seen(void) {
    s32 task;

    if (!peek_advance_flag(&D_030046a8->data, ADVANCE_FLAG_SEEN_DISCLAMER)) {
        set_beatscript_tempo(20);
    }
    set_pause_beatscript_scene(FALSE);
}

// Graphics Init. 3
void disclamer_scene_init_gfx3(void) {
    s32 task;

    func_08007324(TRUE);
    task = palette_fade_in(0, ticks_to_frames(12), 1, 0x0000, &disclamer_pal[0][0], BG_PALETTE_BUFFER(0));
    run_func_after_task(task, disclamer_scene_wait_if_not_seen, 0);
}


// Graphics Init. 2
void disclamer_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), disclamer_gfx_table, 0x2000);
    run_func_after_task(task, disclamer_scene_init_gfx3, 0);
}


// Graphics Init. 1
void disclamer_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), disclamer_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void disclamer_scene_start(void *sVar, s32 dArg) {
    func_0801d860(TRUE);
    disclamer_scene_init_gfx1();
    isInDisclamer = TRUE;
    haveSeenDisclamer = FALSE;
    gDisclamer->inputsEnabled = FALSE;
    gDisclamer->timer = 3600;
}


// Scene Update
void disclamer_scene_update(void *sVar, s32 dArg) {
    if (gDisclamer->inputsEnabled) {
        if ((D_03004afc != 0) || (--gDisclamer->timer == 0)) {
            set_pause_beatscript_scene(FALSE);
            gDisclamer->inputsEnabled = FALSE;
        }
    }
}
