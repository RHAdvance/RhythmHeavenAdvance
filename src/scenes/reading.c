#include "global.h"
#include "scenes.h"
#include "reading.h"
#include "graphics/data_room/data_room_graphics.h"
#include "src/code_080092cc.h"


/* READING MATERIAL SCENE */


enum PageStatesEnum {
    /* 00 */ PAGE_STATE_IDLE,
    /* 01 */ PAGE_STATE_SCROLLING_DOWN,
    /* 02 */ PAGE_STATE_SCROLLING_UP,
    /* 03 */ PAGE_STATE_SCROLLED_DOWN,
    /* 04 */ PAGE_STATE_SCROLLED_UP
};


// Graphics Init. 4
void reading_scene_init_gfx4(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), reading_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 3
void reading_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), gReading->material->graphics, 0x3000);
    run_func_after_task(task, reading_scene_init_gfx4, 0);
}


// Graphics Init. 2
void reading_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), reading_gfx_table, 0x3000);
    run_func_after_task(task, reading_scene_init_gfx3, 0);
}


// Graphics Init. 1
void reading_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), reading_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(2));
}


// Scene Start
void reading_scene_start(void *sVar, s32 dArg) {
    struct ReadingMaterial *material;
    struct TextPrinter *titlePrinter;

    material = &reading_material_table[get_current_scene_trans_var()];

    if (material == NULL) {
        material = &reading_material_error;
    }

    gReading->material = material;

    func_08007324(FALSE);
    func_080073f0();
    reading_scene_init_gfx1();

    gReading->pageState = PAGE_STATE_IDLE;
    gReading->pagePosY = 0;
    gReading->iconPrev = sprite_create(gSpriteHandler, anim_reading_icon_prev, 0, 0, 0, 0x4864, 0, 0, 0x8000);
    gReading->iconNext = sprite_create(gSpriteHandler, anim_reading_icon_next, 0, 0, 0, 0x4864, 0, 0, 0x8000);
    sprite_create(gSpriteHandler, anim_reading_title_bar, 0, 120, 0, 0x48C8, 0, 0, 0);
    gReading->currentPage = 0;

    titlePrinter = text_printer_create_new(get_current_mem_id(), 1, 232, 32);
    text_printer_set_x_y(titlePrinter, 4, 7);
    text_printer_set_layer(titlePrinter, 0x4800);
    text_printer_set_alignment(titlePrinter, TEXT_ALIGNMENT_CENTER);
    text_printer_set_colors(titlePrinter, 3);
    text_printer_set_string(titlePrinter, material->title);
    text_printer_update(titlePrinter);
    text_printer_update(titlePrinter);

    gReading->printer = text_printer_create_new(get_current_mem_id(), 9, 230, 30);
    text_printer_set_x_y(gReading->printer, 8, 24);
    text_printer_set_layer(gReading->printer, 0x8800);
    text_printer_set_x_y_controller(gReading->printer, NULL, &gReading->pagePosY);
    text_printer_set_string(gReading->printer, material->text);
    text_printer_export_data(gReading->printer, &gReading->pageData[0]);

    gReading->inputsEnabled = FALSE;
}


// Update UI
void reading_scene_update_page(void) {
    if (!text_printer_is_busy(gReading->printer)) {
        sprite_set_visible(gSpriteHandler, gReading->iconPrev, gReading->currentPage != 0);
        sprite_set_visible(gSpriteHandler, gReading->iconNext, text_printer_get_text(gReading->printer) != NULL);
    }

    if (gReading->pageState == PAGE_STATE_IDLE) {
        return;
    }

    if (!text_printer_is_busy(gReading->printer)) {
        s32 y = gReading->relativeY;

        if (y < 0) {
            y = -y;
        }

        y = FIXED_POINT_MUL(y, 200);

        if (y < 16) {
            y = 0;
        }

        if (gReading->relativeY < 0) {
            y = -y;
        }

        gReading->relativeY = y;
    }

    gReading->pagePosY = gReading->targetY + gReading->relativeY;

    if (gReading->relativeY == 0) {
        switch (gReading->pageState) {
            default:
                gReading->pageState = PAGE_STATE_IDLE;
                break;

            case PAGE_STATE_SCROLLING_DOWN:
                gReading->targetY = 0;
                gReading->relativeY = -SCREEN_HEIGHT;
                gReading->pageState = PAGE_STATE_SCROLLED_DOWN;
                gReading->currentPage++;
                text_printer_resume(gReading->printer);
                text_printer_export_data(gReading->printer, &gReading->pageData[gReading->currentPage]);
                break;

            case PAGE_STATE_SCROLLING_UP:
                gReading->targetY = 0;
                gReading->relativeY = SCREEN_HEIGHT;
                gReading->pageState = PAGE_STATE_SCROLLED_UP;
                gReading->currentPage--;
                text_printer_import_data(gReading->printer, &gReading->pageData[gReading->currentPage]);
                break;
        }
    }
}


// Scene Update (Active)
void reading_scene_update(void *sVar, s32 dArg) {
    s32 event = READING_EV_NONE;

    if (reading_scene_inputs_enabled()) {
        if (D_03004ac0 & DPAD_UP) {
            if (gReading->currentPage > 0) {
                event = READING_EV_SCROLL_UP;
            } else {
                rumble_play_menu_limit();
            }
        }
        if (D_03004ac0 & DPAD_DOWN) {
            if ((text_printer_get_text(gReading->printer) != NULL) && (gReading->currentPage < 31)) {
                event = READING_EV_SCROLL_DOWN;
            } else {
                rumble_play_menu_limit();
            }
        }
        if (D_03004afc & A_BUTTON) {
            if ((text_printer_get_text(gReading->printer) != NULL) && (gReading->currentPage < 31)) {
                event = READING_EV_SCROLL_DOWN;
            } else {
                rumble_play_menu_limit();
            }
        }
        if (D_03004afc & B_BUTTON) {
            event = READING_EV_CANCEL;
        }
    }

    switch (event) {
        case READING_EV_SCROLL_UP:
            gReading->pageState = PAGE_STATE_SCROLLING_UP;
            gReading->targetY = -SCREEN_HEIGHT;
            gReading->relativeY = SCREEN_HEIGHT;
            play_sound(&s_f_env_paper_rev_seqData);
            rumble_play_menu_move();
            break;

        case READING_EV_SCROLL_DOWN:
            gReading->pageState = PAGE_STATE_SCROLLING_DOWN;
            gReading->targetY = SCREEN_HEIGHT;
            gReading->relativeY = -SCREEN_HEIGHT;
            play_sound(&s_f_env_paper_seqData);
            rumble_play_menu_move();
            break;

        case READING_EV_CANCEL:
            set_pause_beatscript_scene(FALSE);
            gReading->inputsEnabled = FALSE;
            play_sound_in_player(SFX_PLAYER_3, &s_menu_cancel2_seqData);
            rumble_play_menu_cancel();
            break;
    }

    reading_scene_update_page();
    text_printer_update(gReading->printer);
    text_printer_update(gReading->printer);
}


// Check if Scene Can Receive Inputs
u32 reading_scene_inputs_enabled(void) {
    if (gReading->inputsEnabled) {
        u32 busy = text_printer_is_busy(gReading->printer);

        if (gReading->pageState == PAGE_STATE_SCROLLING_DOWN) {
            busy = TRUE;
        }

        if (gReading->pageState == PAGE_STATE_SCROLLING_UP) {
            busy = TRUE;
        }

        if (!busy) {
            return TRUE;
        }
    }

    return FALSE;
}


// Scene Stop
void reading_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}


// Play BGM
void reading_scene_play_bgm(void) {
    scene_set_music(gReading->material->sounds[0]);
}
