#include "global.h"
#include "options.h"
#include "graphics/options/options_graphics.h"


/* OPTIONS MENU SCENE */


// Init. Static Variables
void options_scene_init_memory(void) {
}


// Graphics Init. 3
void options_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), options_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void options_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), options_gfx_table, 0x3000);
    run_func_after_task(task, options_scene_init_gfx3, 0);
}


// Graphics Init. 1
void options_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), options_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void options_scene_start(void *sVar, s32 dArg) {
    struct TextPrinter *printer;

    func_08007324(FALSE);
    func_080073f0();
    options_scene_init_gfx1();

    sprite_create(gSpriteHandler, anim_options_banner, 0, 120, 16, 0x4800, 1, 0, 0);
    gOptionsMenu->uiBarista = sprite_create(gSpriteHandler, anim_options_cursor_barista, 0, 104, 64, 0x4800, 1, 0, 0);
    gOptionsMenu->soundMode = D_030046a8->data.unk294[8];
    gOptionsMenu->uiSoundMode = sprite_create(gSpriteHandler, anim_options_select_stereo, 0x7F, 104, 56, 0x4800, 1, 0x7F, 0);
    gOptionsMenu->uiDataClear = sprite_create(gSpriteHandler, anim_options_select_data_clear, 0x7F, 104, 84, 0x4800, 1, 0x7F, 0);
    sprite_create(gSpriteHandler, anim_options_desc_box, 0, 120, 116, 0x4F00, 0, 0, 0);
    sprite_set_anim(gSpriteHandler, gOptionsMenu->uiSoundMode, options_sound_mode_anim[gOptionsMenu->soundMode][OPTIONS_BUTTON_ON], 0x7F, 1, 0x7F, 0);
    sprite_set_anim(gSpriteHandler, gOptionsMenu->uiDataClear, anim_options_off_data_clear, 0, 0, 0, 0);
    sprite_set_x_y(gSpriteHandler, gOptionsMenu->uiBarista, 104, 56);
    gOptionsMenu->cursorPos = OPTIONS_BUTTON_SOUND_MODE;

    printer = text_printer_create_new(get_current_mem_id(), 3, 208, 32);
    text_printer_set_x_y(printer, 16, 117);
    text_printer_set_layer(printer, 0x4800);
    text_printer_set_alignment(printer, TEXT_ALIGNMENT_CENTER);
    text_printer_center_by_content(printer, TRUE);
    text_printer_set_palette(printer, 12);
    text_printer_set_colors(printer, 0);
    text_printer_set_line_spacing(printer, 15);
    text_printer_set_string(printer, options_desc_text[OPTIONS_BUTTON_SOUND_MODE]);
    gOptionsMenu->descText = printer;

    gOptionsMenu->uiWarningPane = sprite_create(gSpriteHandler, anim_options_warning_box, 0, 120, 74, 0x440A, 1, 0, 0x8000);
    gOptionsMenu->uiWarningCursor = sprite_create(gSpriteHandler, anim_options_cursor_default, 0, 64, 64, 0x4400, 1, 0, 0x8000);
    sprite_set_x(gSpriteHandler, gOptionsMenu->uiWarningCursor, 104);

    printer = text_printer_create_new(get_current_mem_id(), 3, 80, 26);
    text_printer_set_x_y(printer, 80, 75);
    text_printer_set_layer(printer, 0x4400);
    text_printer_set_alignment(printer, TEXT_ALIGNMENT_CENTER);
    text_printer_center_by_content(printer, FALSE);
    text_printer_set_palette(printer, 12);
    text_printer_set_colors(printer, 0);
    text_printer_set_line_spacing(printer, 15);
    text_printer_show_text(printer, FALSE);
    text_printer_set_string(printer, options_data_clear_confirm_text);
    gOptionsMenu->warningText = printer;

    gOptionsMenu->inputsEnabled = FALSE;
    gOptionsMenu->state = OPTIONS_SCENE_STATE_MAIN;
    gOptionsMenu->clearDataOnExit = FALSE;
    gOptionsMenu->canceledDataClear = FALSE;
}


// Scene Update (Paused)
void options_scene_paused(void *sVar, s32 dArg) {
}


// Set Warning Cursor Position
void options_scene_move_warning_cursor(u32 index) {
    sprite_set_y(gSpriteHandler, gOptionsMenu->uiWarningCursor, 75 + (15 * (index + 1)));
}


// Update (State 1)
void options_scene_update_main(void) {
    u32 event = OPTIONS_EV_NONE;

    if (!options_scene_inputs_enabled()) {
        return;
    }

    if (D_03004afc & DPAD_UP) {
        if (gOptionsMenu->cursorPos >= OPTIONS_BUTTON_DATA_CLEAR) {
            event = OPTIONS_EV_CURSOR_UP;
        }
    }

    if (D_03004afc & DPAD_DOWN) {
        if (gOptionsMenu->cursorPos <= OPTIONS_BUTTON_SOUND_MODE) {
            event = OPTIONS_EV_CURSOR_DOWN;
        }
    }

    if (D_03004afc & A_BUTTON) {
        event = OPTIONS_EV_CONFIRM;
    }

    if (D_03004afc & B_BUTTON) {
        event = OPTIONS_EV_CANCEL;
    }

    if (D_030053b8 & RIGHT_SHOULDER_BUTTON) {
        TOGGLE_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_USE_ALT_GAME_SELECT_MUSIC);
        if(CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_USE_ALT_GAME_SELECT_MUSIC)) {
            play_sound(&s_menu_kettei1_seqData);
        } else {
            play_sound(&s_menu_cancel3_seqData);
        }
    }

    switch (event) {
        case OPTIONS_EV_CURSOR_UP:
            gOptionsMenu->cursorPos = OPTIONS_BUTTON_SOUND_MODE;
            sprite_set_y(gSpriteHandler, gOptionsMenu->uiBarista, 56);
            sprite_set_anim(gSpriteHandler, gOptionsMenu->uiSoundMode, options_sound_mode_anim[gOptionsMenu->soundMode][OPTIONS_BUTTON_ON], 0x7F, 1, 0x7F, 0);
            sprite_set_anim(gSpriteHandler, gOptionsMenu->uiDataClear, anim_options_off_data_clear, 0, 0, 0, 0);
            text_printer_set_string(gOptionsMenu->descText, options_desc_text[OPTIONS_BUTTON_SOUND_MODE]);
            play_sound(&s_menu_cursor2_seqData);
            break;

        case OPTIONS_EV_CURSOR_DOWN:
            gOptionsMenu->cursorPos = OPTIONS_BUTTON_DATA_CLEAR;
            sprite_set_y(gSpriteHandler, gOptionsMenu->uiBarista, 84);
            sprite_set_anim(gSpriteHandler, gOptionsMenu->uiSoundMode, options_sound_mode_anim[gOptionsMenu->soundMode][OPTIONS_BUTTON_OFF], 0, 0, 0, 0);
            sprite_set_anim(gSpriteHandler, gOptionsMenu->uiDataClear, anim_options_select_data_clear, 0, 0, 0, 0);
            text_printer_set_string(gOptionsMenu->descText, options_desc_text[OPTIONS_BUTTON_DATA_CLEAR]);
            play_sound(&s_menu_cursor2_seqData);
            break;

        case OPTIONS_EV_CONFIRM:
            if (gOptionsMenu->cursorPos == OPTIONS_BUTTON_SOUND_MODE) {
                gOptionsMenu->soundMode ^= 1;
                sprite_set_anim(gSpriteHandler, gOptionsMenu->uiSoundMode, options_sound_mode_anim[gOptionsMenu->soundMode][OPTIONS_BUTTON_ON], 0, 1, 0x7F, 0);
                D_030046a8->data.unk294[8] = gOptionsMenu->soundMode;
                set_sound_mode(gOptionsMenu->soundMode);
                write_game_save_data();
            } else {
                gOptionsMenu->warningCursorPos = OPTIONS_WARNING_NO;
                options_scene_move_warning_cursor(gOptionsMenu->warningCursorPos);
                sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningPane, TRUE);
                sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningCursor, TRUE);
                text_printer_show_text(gOptionsMenu->warningText, TRUE);
                gOptionsMenu->state = OPTIONS_SCENE_STATE_WARNING;
            }
            play_sound(&s_menu_kettei2_seqData);
            break;

        case OPTIONS_EV_CANCEL:
            gOptionsMenu->canceledDataClear = TRUE;
            set_scene_trans_var(&scene_main_menu, TRUE);
            set_pause_beatscript_scene(FALSE);
            gOptionsMenu->inputsEnabled = FALSE;
            play_sound(&s_menu_cancel3_seqData);
            break;
    }
}


// Update Warning
void options_scene_update_warning(void) {
    if (!options_scene_inputs_enabled()) {
        return;
    }

    if (D_03004afc & B_BUTTON) {
        play_sound(&s_menu_cancel2_seqData);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningPane, FALSE);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningCursor, FALSE);
        text_printer_show_text(gOptionsMenu->warningText, FALSE);
        gOptionsMenu->state = OPTIONS_SCENE_STATE_MAIN;
        return;
    }

    if (D_03004afc & A_BUTTON) {
        if (gOptionsMenu->warningCursorPos == OPTIONS_WARNING_YES) {
            set_next_scene(&scene_title);
            gOptionsMenu->clearDataOnExit = TRUE;
            set_pause_beatscript_scene(FALSE);
            gOptionsMenu->inputsEnabled = FALSE;
            gOptionsMenu->state = OPTIONS_SCENE_STATE_EXIT;
            play_sound(&s_menu_kettei2_seqData);
            return;
        } else {
            sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningPane, FALSE);
            sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningCursor, FALSE);
            text_printer_show_text(gOptionsMenu->warningText, FALSE);
            play_sound(&s_menu_cancel2_seqData);
            gOptionsMenu->state = OPTIONS_SCENE_STATE_MAIN;
        }
    }

    if (D_03004afc & DPAD_UP) {
        if (gOptionsMenu->warningCursorPos != OPTIONS_WARNING_YES) {
            gOptionsMenu->warningCursorPos = OPTIONS_WARNING_YES;
            options_scene_move_warning_cursor(gOptionsMenu->warningCursorPos);
            sprite_set_anim_cel(gSpriteHandler, gOptionsMenu->uiWarningCursor, 0);
            play_sound(&s_menu_cursor1_seqData);
        }
    }

    if (D_03004afc & DPAD_DOWN) {
        if (gOptionsMenu->warningCursorPos == OPTIONS_WARNING_YES) {
            gOptionsMenu->warningCursorPos = OPTIONS_WARNING_NO;
            options_scene_move_warning_cursor(gOptionsMenu->warningCursorPos);
            sprite_set_anim_cel(gSpriteHandler, gOptionsMenu->uiWarningCursor, 0);
            play_sound(&s_menu_cursor1_seqData);
        }
    }
}


// Scene Update (Active)
void options_scene_update(void *sVar, s32 dArg) {
    switch (gOptionsMenu->state) {
        case OPTIONS_SCENE_STATE_EXIT:
            break;
        case OPTIONS_SCENE_STATE_MAIN:
            options_scene_update_main();
            break;
        case OPTIONS_SCENE_STATE_WARNING:
            options_scene_update_warning();
            break;
    }

    text_printer_update(gOptionsMenu->descText);
    text_printer_update(gOptionsMenu->warningText);
}


// Check if Scene Can Receive Inputs
u32 options_scene_inputs_enabled(void) {
    if (gOptionsMenu->inputsEnabled) {
        return TRUE;
    }

    return FALSE;
}


// Scene Stop
void options_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();

    if (gOptionsMenu->clearDataOnExit) {
        clear_save_data();
#ifdef PLAYTEST
        set_playtest_save_data();
#endif
        flush_save_buffer_to_sram();
        set_sound_mode(D_030046a8->data.unk294[8]);
        init_scene_static_var();
    }
}
