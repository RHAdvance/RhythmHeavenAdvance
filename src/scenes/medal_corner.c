#include "global.h"
#include "medal_corner.h"
#include "graphics/medal_corner/medal_corner_graphics.h"
#include "src/scenes/results.h"


/* MEDAL CORNER MENU SCENES */
/* (Rhythm Toys Menu, Endless Games Menu, Drum Lessons Menu) */


static u8 sListSelItems[4];
static u8 sListSelLines[4];
static s8 sDrumLessonID;


// Display Drum Lessons Grades
void medal_corner_init_lesson_grades(void) {
    s16 sprite;
    u32 grade;
    u32 i;

    for (i = 0; i < TOTAL_DRUM_LESSONS; i++) {
        grade = func_080281c4(i);

        if (grade != RESULTS_GRADE_D) {
            sprite = sprite_create(gSpriteHandler, lessons_menu_rank_icons[grade], 0, 0, 0, 0x8800, 1, 0, 0);
            listbox_link_sprite_x_y_to_line(gMedalCorner->listbox, sprite, i);
        }
    }
}


// Init. Level Icon
void medal_corner_init_level_icon(void) {
    gMedalCorner->currentLevelIcon = sprite_clone(gSpriteHandler, gMedalCorner->lockedLevelIcon);
    sprite_set_base_tile(gSpriteHandler, gMedalCorner->currentLevelIcon, 0);
}


// Get Level Name
const char *medal_corner_get_level_name(s32 item) {
    return gMedalCorner->menuData->levels[item].title;
}


// Set Current Level
void medal_corner_set_current_level(s32 item) {
    struct MedalCornerLevel *levels = gMedalCorner->menuData->levels;

    medal_corner_set_level_req_counter(levels[item].medalsToUnlock);

    if (medal_corner_level_is_unlocked(item)) {
        sprite_set_visible(gSpriteHandler, gMedalCorner->lockedLevelIcon, FALSE);
        sprite_set_visible(gSpriteHandler, gMedalCorner->currentLevelIcon, TRUE);
        sprite_set_anim(gSpriteHandler, gMedalCorner->currentLevelIcon, levels[item].icon, 0, 1, 0, 0);
    } else {
        sprite_set_visible(gSpriteHandler, gMedalCorner->lockedLevelIcon, TRUE);
        sprite_set_visible(gSpriteHandler, gMedalCorner->currentLevelIcon, FALSE);
    }
}


// Get Level Scene
struct Scene *medal_corner_get_level_scene(s32 item) {
    return gMedalCorner->menuData->levels[item].scene;
}


// Check if Level Medal Requirement is Met
u32 medal_corner_level_is_unlocked(s32 item) {
    struct MedalCornerLevel *levels = gMedalCorner->menuData->levels;

    if (D_030046a8->data.totalMedals < levels[item].medalsToUnlock) {
        return FALSE;
    } else {
        return TRUE;
    }
}


// Init. Counters
void medal_corner_init_counters(void) {
    u32 totalMedals;

    totalMedals = D_030046a8->data.totalMedals;
    gMedalCorner->medalCountDigit1 = sprite_create(gSpriteHandler, anim_medal_corner_count_num, 0, 157, 151, 0x800, 0, 0x7F, 0);
    gMedalCorner->medalCountDigit2 = sprite_clone(gSpriteHandler, gMedalCorner->medalCountDigit1);
    sprite_set_x(gSpriteHandler, gMedalCorner->medalCountDigit2, 150);
    sprite_set_anim_cel(gSpriteHandler, gMedalCorner->medalCountDigit1, totalMedals % 10);
    sprite_set_anim_cel(gSpriteHandler, gMedalCorner->medalCountDigit2, (totalMedals >= 10) ? totalMedals / 10 : 10);
    sprite_set_x(gSpriteHandler, gMedalCorner->medalCountDigit1, (totalMedals < 10) ? 153 : 157);

    gMedalCorner->reqCountDigit1 = sprite_create(gSpriteHandler, anim_medal_corner_req_num, 0, 58, 142, 0x800, 0, 0x7F, 0);
    gMedalCorner->reqCountDigit2 = sprite_clone(gSpriteHandler, gMedalCorner->reqCountDigit1);
    sprite_set_x(gSpriteHandler, gMedalCorner->reqCountDigit2, 49);

    medal_corner_set_level_req_counter(0);
    medal_corner_use_ui_texture_base(gMedalCorner->medalCountDigit1);
    medal_corner_use_ui_texture_base(gMedalCorner->medalCountDigit2);
    medal_corner_use_ui_texture_base(gMedalCorner->reqCountDigit1);
    medal_corner_use_ui_texture_base(gMedalCorner->reqCountDigit2);
}


// Set Level Requirement Counter
void medal_corner_set_level_req_counter(u32 count) {
    sprite_set_anim_cel(gSpriteHandler, gMedalCorner->reqCountDigit1, count % 10);
    sprite_set_anim_cel(gSpriteHandler, gMedalCorner->reqCountDigit2, (count >= 10) ? count / 10 : 10);
    sprite_set_x(gSpriteHandler, gMedalCorner->reqCountDigit1, (count < 10) ? 53 : 58);
}


// Reset Listbox Positions
void medal_corner_reset_list_positions(void) {
    u32 i;

    for (i = 0; i < TOTAL_MEDAL_CORNER_MENUS; i++) {
        sListSelItems[i] = 0;
        sListSelLines[i] = 0;
    }
}


// Remember Listbox Position
void medal_corner_remember_list_position(void) {
    sListSelItems[gMedalCorner->menuID] = listbox_get_sel_item(gMedalCorner->listbox);
    sListSelLines[gMedalCorner->menuID] = listbox_get_sel_line(gMedalCorner->listbox);
}


// Listbox 'getString()' Method
const char *medal_corner_listbox_get_string(s32 item) {
    if (item < 0 || item >= gMedalCorner->menuData->levelCount) {
        return NULL;
    }

    if (!medal_corner_level_is_unlocked(item)) {
        return medal_corner_locked_text;
    }

    return medal_corner_get_level_name(item);
}


// Listbox 'onScroll()' Method
void medal_corner_listbox_on_scroll(s32 arg, u32 current, u32 previous) {
    medal_corner_set_current_level(current);
    play_sound(&s_menu_cursor1_seqData);
}


// Init. Listbox
void medal_corner_listbox_init(void) {
    u32 totalLevels = gMedalCorner->menuData->levelCount;

    gMedalCorner->listbox = create_new_listbox(
            get_current_mem_id(), 8, 128, 32, 10, 11, 0, 143, 40, 0x8800, 16,
            sListSelItems[gMedalCorner->menuID], totalLevels, anim_medal_corner_cursor, 2, 4,
            sListSelLines[gMedalCorner->menuID], medal_corner_listbox_get_string, NULL);
    medal_corner_use_ui_texture_base(listbox_get_sel_sprite(gMedalCorner->listbox));
    listbox_run_func_on_scroll(gMedalCorner->listbox, medal_corner_listbox_on_scroll, 0);
    medal_corner_set_current_level(sListSelItems[gMedalCorner->menuID]);
}


// Init. Static Variables
void medal_corner_scene_init_memory(void) {
    medal_corner_reset_list_positions();
    medal_corner_set_lesson_id(DRUM_LESSON_NULL);
}


// Graphics Init. 3
void medal_corner_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), medal_corner_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void medal_corner_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), gMedalCorner->menuData->gfx, 0x3000);
    run_func_after_task(task, medal_corner_scene_init_gfx3, 0);
}


// Graphics Init. 1
void medal_corner_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), medal_corner_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void medal_corner_scene_start(void *sVar, s32 dArg) {
    gMedalCorner->menuID = dArg;
    gMedalCorner->menuData = medal_corner_menu_table[dArg];

    func_08007324(FALSE);
    func_080073f0();
    medal_corner_scene_init_gfx1();

    medal_corner_init_counters();
    gMedalCorner->lockedLevelIcon = sprite_create(gSpriteHandler, anim_medal_corner_locked_icon, 0, 0x38, 0x58, 0x800, 1, 0, 0);
    medal_corner_use_ui_texture_base(gMedalCorner->lockedLevelIcon);
    medal_corner_init_level_icon();
    medal_corner_listbox_init();

    if (gMedalCorner->menuID == MEDAL_CORNER_MENU_DRUM_LESSONS) {
        medal_corner_init_lesson_grades();
    }

    gameplay_pause_menu_set_quit_destination(get_current_scene());
    gMedalCorner->inputsEnabled = FALSE;
    write_game_save_data();
}


// Set Current Drum Lesson
void medal_corner_set_lesson_id(s32 item) {
    sDrumLessonID = item;
}


// Get Current Drum Lesson
s32 medal_corner_get_lesson_id(void) {
    return sDrumLessonID;
}


// Scene Update (Paused)
void medal_corner_scene_paused(void *sVar, s32 dArg) {
}


// Set Sprite Texture Base Tile
void medal_corner_use_ui_texture_base(s32 sprite) {
    sprite_set_base_tile(gSpriteHandler, sprite, 640);
}


// Scene Update (Active)
void medal_corner_scene_update(void *sVar, s32 dArg) {
    struct Scene *scene;
    u32 event = MEDAL_CORNER_EV_NONE;
    u32 item;

    if (medal_corner_scene_inputs_enabled()) {
        if (D_030053b8 & DPAD_UP) {
            event = MEDAL_CORNER_EV_SCROLL_UP;
        }

        if (D_030053b8 & DPAD_DOWN) {
            event = MEDAL_CORNER_EV_SCROLL_DOWN;
        }

        if (D_03004afc & B_BUTTON) {
            event = MEDAL_CORNER_EV_CANCEL;
        }

        if (D_03004afc & A_BUTTON) {
            event = MEDAL_CORNER_EV_CONFIRM;
        }
    }

    switch (event) {
        case MEDAL_CORNER_EV_CONFIRM:
            item = listbox_get_sel_item(gMedalCorner->listbox);

            if (medal_corner_level_is_unlocked(item)) {
                func_080006f0(get_current_scene_trans_target(), get_current_scene_trans_var());
                scene = medal_corner_get_level_scene(item);
                set_next_scene(scene);
                set_scene_trans_target(scene, get_current_scene());
                medal_corner_set_lesson_id(item);
                play_sound(&s_menu_kettei2_seqData);
                set_pause_beatscript_scene(FALSE);
                gMedalCorner->inputsEnabled = FALSE;
            } else {
                play_sound(&s_menu_error_seqData);
            }
            break;

        case MEDAL_CORNER_EV_SCROLL_UP:
            listbox_scroll_up(gMedalCorner->listbox);
            break;

        case MEDAL_CORNER_EV_SCROLL_DOWN:
            listbox_scroll_down(gMedalCorner->listbox);
            break;

        case MEDAL_CORNER_EV_CANCEL:
            play_sound(&s_menu_cancel3_seqData);
            set_pause_beatscript_scene(FALSE);
            gMedalCorner->inputsEnabled = FALSE;
            break;
    }

    update_listbox(gMedalCorner->listbox);
}


// Check if Scene Can Receive Inputs
u32 medal_corner_scene_inputs_enabled(void) {
    if (gMedalCorner->inputsEnabled) {
        return TRUE;
    }

    return FALSE;
}


// Scene Stop
void medal_corner_scene_stop(void *sVar, s32 dArg) {
    medal_corner_remember_list_position();
    func_08008628();
    func_08004058();
}


// Play Music (Script Function)
void medal_corner_start_music(void) {
    scene_set_music(gMedalCorner->menuData->bgm);
}
