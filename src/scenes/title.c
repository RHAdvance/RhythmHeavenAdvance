#include "global.h"
#include "title.h"
#include "graphics/title/title_graphics.h"
#include "src/code_080092cc.h"


/* TITLE SCENE */


// Update Logo Bubble Position
void title_logo_set_bubble_pos(s32 id) {
    struct LogoBubble *bubble = &gTitle->logoBubbles[id];
    s24_8 xOfs, yOfs, xB, yB;
    s32 x, y, rise;

    rise = FIXED_POINT_MUL(bubble->riseDistance, coss2(bubble->riseAngle));
    xOfs = FIXED_POINT_MUL(bubble->bounceDistance, coss2(bubble->bounceAngle));
    yOfs = FIXED_POINT_MUL(bubble->bounceDistance, sins2(bubble->bounceAngle));
    x = bubble->centerX + FIXED_TO_INT(xOfs);
    y = bubble->centerY + FIXED_TO_INT(yOfs) + rise;
    sprite_set_x_y(gSpriteHandler, bubble->letter, x, y);

    xB = xOfs * 15;
    yB = yOfs * 15;
    x = bubble->centerX + FIXED_TO_INT(xB >> 5);
    y = bubble->centerY + FIXED_TO_INT(yB >> 5) + rise;
    sprite_set_x_y(gSpriteHandler, bubble->inner, x, y);
    sprite_set_x_y(gSpriteHandler, bubble->outer, x, y);
}


// Init. Logo Bubbles
void title_logo_init(void) {
    u32 i;

    for (i = 0; i < TOTAL_TITLE_LOGO_BUBBLES; i++) {
        struct LogoBubble *bubble = &gTitle->logoBubbles[i];
        struct TitleLogoCharData *letter = &title_logo_char_data[i];

        bubble->active = FALSE;
        bubble->letter = sprite_create(gSpriteHandler, letter->anim, 0, letter->x, letter->y, 0x4800, 0, 0, 0x8000);
        if (letter->anim == anim_title_logo_advance) {
            bubble->inner = sprite_create(gSpriteHandler, anim_title_blank1, 0, letter->x, letter->y, 0x4801, 0, 0, 0x8000);
        }
        else
            bubble->inner = sprite_create(gSpriteHandler, anim_title_logo_bubble_inner, 0, letter->x, letter->y, 0x4801, 0, 0, 0x8000);
        if (letter->anim == anim_title_logo_advance) {
            bubble->outer = sprite_create(gSpriteHandler, anim_title_blank1, 0, letter->x, letter->y, 0x4802, 0, 0, 0x8000);
        }
        else
            bubble->outer = sprite_create(gSpriteHandler, anim_title_logo_bubble_outer, 0, letter->x, letter->y, 0x4802, 0, 0, 0x8000);
        bubble->centerX = letter->x;
        bubble->centerY = letter->y;
        bubble->riseDistance = (agb_random(20) - 10) + 160;
        bubble->riseSpeed = (agb_random(5) - 2) + INT_TO_FIXED(0.94);
        bubble->riseAngle = agb_random(INT_TO_FIXED(2.0 / 16)) - INT_TO_FIXED(1.0 / 16);
        bubble->riseTurnSpeed = agb_random(INT_TO_FIXED(1.5 / 32)) + INT_TO_FIXED(1.0 / 32);
        bubble->bounceAngle = letter->bounceAngle;
        bubble->bounceBaseAngle = letter->bounceAngle;
        bubble->bounceDistance = INT_TO_FIXED(0.0);
        title_logo_set_bubble_pos(i);
    }

    gTitle->nextLogoBubble = 0;
}


// Start Logo Bubble Rise (Script Function)
void title_logo_appear(void) {
    u32 i;

    for (i = 0; i < TOTAL_TITLE_LOGO_BUBBLES; i++) {
        struct LogoBubble *bubble = &gTitle->logoBubbles[i];

        bubble->active = TRUE;
        sprite_set_visible(gSpriteHandler, bubble->letter, TRUE);
        sprite_set_visible(gSpriteHandler, bubble->inner, TRUE);
        sprite_set_visible(gSpriteHandler, bubble->outer, TRUE);
    }
}


// Update Logo Bubbles
void title_logo_update(void) {
    u32 i;

    for (i = 0; i < TOTAL_TITLE_LOGO_BUBBLES; i++) {
        struct LogoBubble *bubble = &gTitle->logoBubbles[i];

        if (bubble->active) {
            bubble->riseAngle += bubble->riseTurnSpeed;
            bubble->riseDistance = FIXED_POINT_MUL(bubble->riseDistance, bubble->riseSpeed);
            bubble->bounceDistance = FIXED_POINT_MUL(bubble->bounceDistance, INT_TO_FIXED(0.9));
            title_logo_set_bubble_pos(i);
        }
    }
}


// Logo Bubbles Beat Animation
void title_logo_bounce_all(void) {
    u32 i;

    for (i = 0; i < TOTAL_TITLE_LOGO_BUBBLES; i++) {
        struct LogoBubble *bubble = &gTitle->logoBubbles[i];

        if (bubble->active) {
            bubble->bounceDistance += INT_TO_FIXED(4.0);
            if (bubble->bounceBaseAngle == 37) {
                bubble->bounceAngle = bubble->bounceBaseAngle + INT_TO_FIXED(2.0 / 8) - INT_TO_FIXED(1.0 / 8); }
            else
                bubble->bounceAngle = bubble->bounceBaseAngle + agb_random(INT_TO_FIXED(2.0 / 8)) - INT_TO_FIXED(1.0 / 8);
            title_logo_set_bubble_pos(i);
        }
    }
}


// Animate Logo Bubble (Script Function)
void title_logo_bounce_bubble(s32 id) {
    struct LogoBubble *bubble;

    if (id >= 0) {
        gTitle->nextLogoBubble = id;
    }

    bubble = &gTitle->logoBubbles[gTitle->nextLogoBubble];

    if (bubble->active) {
        bubble->bounceDistance += INT_TO_FIXED(5.0);

        gTitle->nextLogoBubble++;
        if (gTitle->nextLogoBubble >= TOTAL_TITLE_LOGO_BUBBLES) {
            gTitle->nextLogoBubble = 0;
        }
    }
}


// Init. Static Variables
void title_scene_init_memory(void) {
}


// Graphics Init. 3
void title_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), title_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void title_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), title_gfx_table, 0x3000);
    run_func_after_task(task, title_scene_init_gfx3, 0);
}


// Graphics Init. 1
void title_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), title_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void title_scene_start(void *sVar, s32 dArg) {
    struct TextPrinter *textPrinter;

    func_08007324(FALSE);
    func_080073f0();

    gTitle->directiveText = sprite_create(gSpriteHandler, anim_title_text, 0, 120, 129, 0x800, 1, 0x7f, 0x8000);
    gTitle->stars = sprite_create(gSpriteHandler, anim_title_stars_appear, 0, 120, 64, 0x4864, 1, 0x7f, 0x8000);
    textPrinter = text_printer_create_new(get_current_mem_id(), 1, 240, 32);
    text_printer_set_x_y(textPrinter, 0, 8);
    text_printer_set_layer(textPrinter, 0);
    text_printer_center_by_content(textPrinter, TRUE);
    text_printer_set_palette(textPrinter, 2);
    text_printer_set_colors(textPrinter, 0);
    gTitle->textPrinter = textPrinter;

    title_scene_init_gfx1();
    title_logo_init();
    gTitle->inputsEnabled = FALSE;
    gTitle->timeUntilDemo = 180 * 16;
    gTitle->titleIsDisplayed = FALSE;
    set_next_scene(&scene_drum_samurai_demo_cutscene);
    set_scene_trans_var(&scene_main_menu, 0);
}


// Finish Intro (Script Function)
void title_scene_complete_intro(void) {
    sprite_set_visible(gSpriteHandler, gTitle->directiveText, TRUE);
    sprite_set_anim(gSpriteHandler, gTitle->stars, anim_title_stars_spin, 0, 1, 0, 0);
    gTitle->titleIsDisplayed = TRUE;
}


// Beat Animation (Script Function)
void title_scene_beat_anim(void) {
    if (!gTitle->titleIsDisplayed) {
        s32 frame = sprite_get_anim_cel(gSpriteHandler, gTitle->stars);
        sprite_set_anim_cel(gSpriteHandler, gTitle->stars, frame + 1);
        sprite_set_visible(gSpriteHandler, gTitle->stars, TRUE);
    }

    sprite_set_anim_cel(gSpriteHandler, gTitle->directiveText, 0);
    title_logo_bounce_all();
}


// Scene Update (Paused)
void title_scene_paused(void *sVar, s32 dArg) {
}


// Update Inputs
void title_scene_update_inputs(void) {
    if (D_03004afc & (A_BUTTON | START_BUTTON)) {
        if (D_030046a8->data.unkB0) {
            set_next_scene(&scene_main_menu);
        } else {
            set_next_scene(&scene_drum_samurai_opening_cutscene);
        }

        func_0801d968(script_scene_title_exit);
        gTitle->inputsEnabled = FALSE;
        play_sound_w_pitch_volume(&s_nyuka_fan_seqData, INT_TO_FIXED(1.25), INT_TO_FIXED(0.0));
        rumble_play_menu_confirm();
        scene_set_music_volume_env(100);
        D_030046a8->data.unkB0 = TRUE;
        gTitle->timeUntilDemo = 9999;
    }
}


// Scene Update (Active)
void title_scene_update(void *sVar, s32 dArg) {
    if (gTitle->timeUntilDemo > 0) {
        if (--gTitle->timeUntilDemo == 0) {
            set_next_scene(&scene_drum_samurai_demo_cutscene);
            set_scene_trans_target(&scene_drum_samurai_demo_cutscene, &scene_title);
            func_0801d968(script_scene_title_exit);
            gTitle->inputsEnabled = FALSE;
        }
    }

    if (title_scene_inputs_enabled()) {
        title_scene_update_inputs();
    }

    title_logo_update();
    text_printer_update(gTitle->textPrinter);
}


// Check if Scene Can Receive Inputs
u32 title_scene_inputs_enabled(void) {
    if (gTitle->inputsEnabled) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Scene Stop
void title_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}
