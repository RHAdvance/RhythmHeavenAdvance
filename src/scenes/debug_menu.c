#include "global.h"
#include "debug_menu.h"
#include "src/scenes/medal_corner.h"


/* DEBUG MENU SCENE */

/* EXTERNS */
extern struct LevelData *get_level_data_from_id(s32 id);

static s8 sMenuPage;
static s8 sMenuRow;


// Init. Static Variables
void debug_menu_scene_init_memory(void) {
    struct DebugMenuEntry *entries = debug_menu_entry_table;
    u32 i;

    for (i = 0; entries[i].scene != NULL; i++) {
        if (entries[i].scene == &scene_title) {
            sMenuPage = i / DEBUG_MENU_ENTRY_PER_PAGE;
            sMenuRow = i % DEBUG_MENU_ENTRY_PER_PAGE;
            return;
        }
    }

    sMenuPage = 0;
    sMenuRow = 0;
}


// Update Static Variables
void debug_menu_scene_update_static_var(void) {
    sMenuPage = gDebugMenu->page;
    sMenuRow = gDebugMenu->row;
}


// Graphics Init. 3
void debug_menu_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), debug_menu_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void debug_menu_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), debug_menu_gfx_table, 0x3000);
    run_func_after_task(task, debug_menu_scene_init_gfx3, 0);
}


// Graphics Init. 1
void debug_menu_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), debug_menu_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
}


// Scene Start
void debug_menu_scene_start(void *sVar, s32 dArg) {
    struct PrintedTextAnim *textAnim;
    struct DebugMenuEntry *entry;
    u32 i;

    func_08007324(FALSE);
    func_080073f0();

    gDebugMenu->bgFont = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    gDebugMenu->objFont = scene_create_obj_font_printer(0x200, 8);
    import_all_scene_objects(gSpriteHandler, gDebugMenu->objFont, debug_menu_scene_objects, D_0300558c);
    debug_menu_scene_init_gfx1();

    textAnim = bmp_font_obj_print_l(gDebugMenu->objFont, "‚c‚…‚‚‚•‚‡@‚l‚…‚Ž‚•", 1, 6); // Sequence Test
    sprite_create(gSpriteHandler, textAnim->frames, 0, 0, 8, 0x800, 0, 0, 0);

    textAnim = bmp_font_obj_print_l(gDebugMenu->objFont, "–", 1, 7);
    gDebugMenu->cursor = sprite_create(gSpriteHandler, textAnim->frames, 0, 0, 0, 0x800, 0, 0, 0);

    textAnim = bmp_font_obj_print_r(gDebugMenu->objFont, "‚P^‚P", 1, 4);
    gDebugMenu->counter = sprite_create(gSpriteHandler, textAnim->frames, 0, 240, 8, 0x800, 0, 0, 0);

    gDebugMenu->page = -1;
    gDebugMenu->row = 0;

    for (i = 0; i < DEBUG_MENU_ENTRY_PER_PAGE; i++) {
        gDebugMenu->textLines[i] = -1;
    }

    gDebugMenu->totalEntries = 0;
    if (debug_menu_entry_table[gDebugMenu->totalEntries].scene != NULL) {
        do {
            gDebugMenu->totalEntries++;
        } while (debug_menu_entry_table[gDebugMenu->totalEntries].scene != NULL);
    }

    debug_menu_render_table(sMenuPage, sMenuRow);
    gDebugMenu->inputsEnabled = FALSE;

    set_scene_trans_var(&scene_epilogue, 0);
    set_scene_trans_var(&scene_arrival, (u32)&scene_reading);
    set_scene_trans_var(&scene_reading, agb_random(20));
    gameplay_pause_menu_set_quit_destination(&scene_debug_menu);
    results_set_enable_save(FALSE);
    medal_corner_set_lesson_id(DRUM_LESSON_NULL);
}


// Scene Update (Paused)
void debug_menu_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void debug_menu_scene_update(void *sVar, s32 dArg) {
    s32 maxRow;

    if (!debug_menu_scene_inputs_enabled()) {
        return;
    }

    for (maxRow = 0; gDebugMenu->textLines[maxRow] > -1; maxRow++) {
        if (maxRow > DEBUG_MENU_ENTRY_PER_PAGE-1) {
            break;
        }
    }

    if (D_030053b8 & DPAD_UP) {
        debug_menu_render_table(gDebugMenu->page, (gDebugMenu->row > 0) ? gDebugMenu->row - 1 : maxRow - 1);
        play_sound(&s_menu_cursor1_seqData);
    } else if (D_030053b8 & DPAD_DOWN) {
        debug_menu_render_table(gDebugMenu->page, (gDebugMenu->row < maxRow - 1) ? gDebugMenu->row + 1 : 0);
        play_sound(&s_menu_cursor1_seqData);
    }

    if (D_030053b8 & DPAD_LEFT) {
        debug_menu_render_table(gDebugMenu->page - 1, gDebugMenu->row);
        play_sound(&s_f_pause_cursor_seqData);
    } else if (D_030053b8 & DPAD_RIGHT) {
        debug_menu_render_table(gDebugMenu->page + 1, gDebugMenu->row);
        play_sound(&s_f_pause_cursor_seqData);
    }

    if (D_03004afc & (START_BUTTON | A_BUTTON)) {
        set_next_scene(debug_menu_entry_table[(gDebugMenu->page * DEBUG_MENU_ENTRY_PER_PAGE) + gDebugMenu->row].scene);
        if(debug_menu_entry_table[(gDebugMenu->page * DEBUG_MENU_ENTRY_PER_PAGE) + gDebugMenu->row].seeEpilogue) {
            set_scene_trans_target(&scene_results_ver_rank, &scene_debug_menu);
            set_scene_trans_target(&scene_results_ver_score, &scene_debug_menu);
            set_scene_trans_target(&scene_epilogue, &scene_debug_menu);
            set_scene_trans_var(&scene_epilogue, (s32)get_level_data_from_id(agb_random(TOTAL_LEVELS))); // yes it's on purpose that PC2 might show up here, it'll show the debug one
        } else {
            set_scene_trans_target(debug_menu_entry_table[(gDebugMenu->page * DEBUG_MENU_ENTRY_PER_PAGE) + gDebugMenu->row].scene, &scene_debug_menu);
        }
        set_pause_beatscript_scene(FALSE);
        gDebugMenu->inputsEnabled = FALSE;
        play_sound(&s_menu_kettei1_seqData);
    } else if (D_03004afc & B_BUTTON) {
        set_next_scene(&scene_main_menu);
        set_pause_beatscript_scene(FALSE);
        gDebugMenu->inputsEnabled = FALSE;
        play_sound(&s_menu_cancel3_seqData);
    }
}


// Check if Scene Can Receive Inputs
u32 debug_menu_scene_inputs_enabled(void) {
    if (gDebugMenu->inputsEnabled) {
        return TRUE;
    }

    return FALSE;
}


// Scene Stop
void debug_menu_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
    debug_menu_scene_update_static_var();
}
