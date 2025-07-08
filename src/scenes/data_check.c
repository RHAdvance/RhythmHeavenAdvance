#include "global.h"
#include "data_check.h"
#include "src/scenes/game_select.h"


/* DATA CHECK SCENE */


// Init. Static Variables
void data_check_scene_init_memory(void) {
}


// Graphics Init. 3
void data_check_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    D_03004b10.objPalette[8][1] = 0x7FFF;
    D_03004b10.objPalette[9][1] = 0x03FF;
    task = start_new_texture_loader(get_current_mem_id(), data_check_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void data_check_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), data_check_gfx_table, 0x3000);
    run_func_after_task(task, data_check_scene_init_gfx3, 0);
}


// Graphics Init. 1
void data_check_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), data_check_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
}


// Scene Start
void data_check_scene_start(void *sVar, s32 dArg) {
    u32 i;

    func_08007324(FALSE);
    func_080073f0();
    gDataCheck->bgFont = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    gDataCheck->objFont = scene_create_obj_font_printer(0x300, 4);

    for (i = 0; i < 10; i++) {
        gDataCheck->textLineSprites[i] = -1;
    }

    data_check_print_line(0, 1, "Gameplay Logs"); // Gameplay Logs
    gDataCheck->currentPage = 0;
    gDataCheck->totalPages = game_select_get_total_levels();
    data_check_print_page(gDataCheck->currentPage);

    import_all_scene_objects(gSpriteHandler, gDataCheck->objFont, data_check_scene_objects, D_0300558c);
    data_check_scene_init_gfx1();
    gDataCheck->inputsEnabled = FALSE;
    set_next_scene(&scene_debug_menu);
}


// Scene Update (Paused)
void data_check_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update
void data_check_scene_update(void *sVar, s32 dArg) {
    s32 previousPage;

    if (data_check_scene_inputs_enabled()) {
        previousPage = gDataCheck->currentPage;

        if (D_030053b8 & DPAD_LEFT) {
            gDataCheck->currentPage--;
        }

        if (D_030053b8 & DPAD_RIGHT) {
            gDataCheck->currentPage++;
        }

        if (gDataCheck->currentPage < 0) {
            gDataCheck->currentPage = gDataCheck->totalPages - 1;
        }

        if (gDataCheck->currentPage > gDataCheck->totalPages - 1) {
            gDataCheck->currentPage = 0;
        }

        if (gDataCheck->currentPage != previousPage) {
            data_check_print_page(gDataCheck->currentPage);
        }

        if (D_03004afc & B_BUTTON) {
            set_pause_beatscript_scene(FALSE);
            gDataCheck->inputsEnabled = FALSE;
        }
    }
}


// Check if Scene Can Receive Inputs
u32 data_check_scene_inputs_enabled(void) {
    if (gDataCheck->inputsEnabled) {
        return TRUE;
    }

    return FALSE;
}


// Print Line
void data_check_print_line(u32 line, u32 palette, const char *string) {
    struct Animation *anim;
    void *tileset;
    u32 tileY;
    s16 sprite;

    sprite = gDataCheck->textLineSprites[line];

    if (sprite >= 0) {
        anim = (void *)sprite_get_data(gSpriteHandler, sprite, 7);
        sprite_delete(gSpriteHandler, sprite);
        text_printer_delete_anim(anim);
    }

    tileY = (line * 2) + 12;
    tileset = OBJ_TILESET_BASE(tileY * 0x400);
    dma3_fill(0, tileset, 0x800, 0x20, 0x200);

    anim = text_printer_get_unformatted_line_anim(get_current_mem_id(), 0, tileY, TEXT_PRINTER_FONT_SMALL, string, TEXT_ANCHOR_BOTTOM_LEFT, 0, 256);
    sprite = sprite_create(gSpriteHandler, anim, 0, 8, (line * 16) + 8, 0, 0, 0, 0);
    sprite_set_base_palette(gSpriteHandler, sprite, palette + 8);
    gDataCheck->textLineSprites[line] = sprite;
}


// Print Page
void data_check_print_page(s32 id) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    u32 avgPoints, totalPlays, firstOK, firstSuperb;
    char string[0x100], number[0x20];

    strintf(number, id);
    memcpy(string, "  ", 3);
    strcat(string, "No. ");
    strcat(string, number);
    strcat(string, "  ");
    strcat(string, game_select_get_level_name(id));
    data_check_print_line(2, 0, string);

    avgPoints = get_level_score(saveData, id);

    if (avgPoints == DEFAULT_LEVEL_SCORE) {
        memcpy(number, "---", 4);
    } else {
        strintf(number, avgPoints);
    }

    memcpy(string, "  ", 3);
    strcat(string, "Average Points "); // Average Points:
    strcat(string, number);

    if (avgPoints != DEFAULT_LEVEL_SCORE) {
        strcat(string, " Out of 1000 Points"); // (Out of 1000 Points)
    }

    data_check_print_line(3, 0, string);

    totalPlays = get_level_total_plays(saveData, id);
    firstOK = get_level_first_ok(saveData, id);
    firstSuperb = get_level_first_superb(saveData, id);

    memcpy(string, "  ", 3);
    strcat(string, "Number of Times Played "); // Number of Times Played:
    strintf(number, totalPlays);
    strcat(string, number);
    strcat(string, " Times"); // [x] Times
    data_check_print_line(4, 0, string);

    if (totalPlays > 0) {
        memcpy(string, "  ", 3);
        strcat(string, "  ( First OK: "); // ( First OK:

        if (firstOK == 0) {
            strcat(string, "Not Yet"); // Not Yet
        } else {
            strintf(number, firstOK);
            strcat(string, number);
            strcat(string, "th Time"); // [x]th Time
        }

        strcat(string, "  First Superb: "); // First Superb:

        if (firstSuperb == 0) {
            strcat(string, "Not Yet )"); // Not Yet )
        } else {
            strintf(number, firstSuperb);
            strcat(string, number);
            strcat(string, "th Time )"); // [x]th Time )
        }

        data_check_print_line(5, 0, string);
    } else {
        data_check_print_line(5, 0, "");
    }
}


// Scene Stop
void data_check_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}
