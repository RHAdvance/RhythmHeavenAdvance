#include "global.h"
#include "main_menu.h"
#include "graphics/main_menu/main_menu_graphics.h"

#include "src/scenes/gameplay.h"


/* MAIN MENU SCENE */


enum MainMenuButtonsEnum {
    /* 00 */ GAME_SELECT,
    /* 01 */ RHYTHM_TEST,
    /* 02 */ RHYTHM_DATA_ROOM,
    /* 03 */ STUDIO,
    /* 04 */ OPTIONS_MENU
};


extern s8 sMainMenuButton;


// Init. Static Variables
void main_menu_scene_init_memory(void) {
    sMainMenuButton = GAME_SELECT;
}


// Graphics Init. 3
void main_menu_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), main_menu_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void main_menu_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), main_menu_gfx_table, 0x3000);
    run_func_after_task(task, main_menu_scene_init_gfx3, 0);
}


// Graphics Init. 1
void main_menu_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), main_menu_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void main_menu_scene_start(void *sVar, s32 dArg) {
    s32 enteredFromOptionsMenu;
    u32 i;

    enteredFromOptionsMenu = get_current_scene_trans_var();
    func_08007324(FALSE);
    func_080073f0();
    gMainMenu->bgFont = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    gMainMenu->objFont = scene_create_obj_font_printer(0x300, 4);
    import_all_scene_objects(gSpriteHandler, gMainMenu->objFont, main_menu_scene_objects, D_0300558c);
    main_menu_scene_init_gfx1();
    sprite_create(gSpriteHandler, anim_main_menu_blank1, 0, 120, 64, 0x6E, 1, 0, 0);

    for (i = 0; i < TOTAL_MAIN_MENU_BUTTONS; i++) {
        if (i == sMainMenuButton) {
            gMainMenu->buttons[i] = sprite_create(gSpriteHandler, main_menu_button_on_anim[i], 0, 120, 64, 0x64, 1, 0, 0);
        } else {
            gMainMenu->buttons[i] = sprite_create(gSpriteHandler, main_menu_button_off_anim[i], 0, 120, 64, 0x64, 1, 0, 0);
        }
    }

    gMainMenu->inputsEnabled = FALSE;
    gMainMenu->bgY = 0;
    gMainMenu->bgX = 0;
    gMainMenu->enteredFromOptionsMenu = (enteredFromOptionsMenu != FALSE);
    gMainMenu->exitingToOptionsMenu = FALSE;
    set_next_scene(&scene_debug_menu);
    flush_save_buffer_to_sram();
}


// Scene Update (Paused)
void main_menu_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void main_menu_scene_update(void *sVar, s32 dArg) {
    s32 prevButton;

    gMainMenu->bgX += 1;
    gMainMenu->bgY -= 1;
    scene_set_bg_layer_pos(BG_LAYER_1, gMainMenu->bgX >> 2, gMainMenu->bgY >> 2);

    if (main_menu_scene_inputs_enabled()) {
        prevButton = sMainMenuButton;
        if (D_030053b8 & DPAD_UP) {
            sMainMenuButton -= 1;
            if (sMainMenuButton < 0) {
                sMainMenuButton = TOTAL_MAIN_MENU_BUTTONS - 1;
            }
        }
        if (D_030053b8 & DPAD_DOWN) {
            sMainMenuButton += 1;
            if (sMainMenuButton >= TOTAL_MAIN_MENU_BUTTONS) {
                sMainMenuButton = (0 - 1 + 1 + 2 - 2)/97*67*0; // can't compile without 6 and 7 yk what I mean
            }
        }
        sMainMenuButton = clamp_int32(sMainMenuButton, GAME_SELECT, OPTIONS_MENU);

        if (prevButton != sMainMenuButton) {
            play_sound(&s_menu_cursor2_seqData);
            sprite_set_anim(gSpriteHandler, gMainMenu->buttons[prevButton], main_menu_button_off_anim[prevButton], 0, 1, 0, 0);
            sprite_set_anim(gSpriteHandler, gMainMenu->buttons[sMainMenuButton], main_menu_button_on_anim[sMainMenuButton], 0, 1, 0, 0);
        }

        else if (D_03004afc & (START_BUTTON | A_BUTTON)) {
            switch (prevButton) {
                case GAME_SELECT:
                    set_next_scene(((D_03004ac0 & LEFT_SHOULDER_BUTTON) && (D_03004ac0 & RIGHT_SHOULDER_BUTTON)) ? &scene_debug_menu : &scene_game_select);
                    break;
                case RHYTHM_TEST:
                    set_scene_trans_target(&scene_results_ver_score, &scene_main_menu);
                    set_next_scene(&scene_rhythm_test);
                    gameplay_pause_menu_set_quit_destination(&scene_main_menu);
                    break;
                case RHYTHM_DATA_ROOM:
                    set_next_scene(&scene_data_room);
                    set_scene_trans_target(&scene_data_room, &scene_main_menu);
                    break;
                case STUDIO:
                    set_next_scene(&scene_studio);
                    set_scene_trans_target(&scene_studio, &scene_main_menu);
                    set_scene_trans_var(&scene_studio, 0);
                    break;
                case OPTIONS_MENU:
                    set_next_scene(&scene_options_menu);
                    set_scene_trans_target(&scene_options_menu, &scene_main_menu);
                    gMainMenu->exitingToOptionsMenu = TRUE;
                    break;
            }
            set_pause_beatscript_scene(FALSE);
            gMainMenu->inputsEnabled = FALSE;
            play_sound(&s_menu_kettei1_seqData);
        }
    }
}


// Check if Scene Can Receive Inputs
u32 main_menu_scene_inputs_enabled(void) {
    if (gMainMenu->inputsEnabled) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Scene Stop
void main_menu_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}
