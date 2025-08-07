#include "global.h"
#include "data_room.h"
#include "graphics/data_room/data_room_graphics.h"
#include "src/scenes/reading.h"


/* RHYTHM DATA ROOM SCENE */


static u8 sListSelItem;
static u8 sListSelLine;


// Init. Static Variables
void dataroom_scene_init_memory(void) {
    dataroom_scene_set_listbox_sel(0, 0);
}


// Graphics Init. 3
void dataroom_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), data_room_buffered_textures); // Start new texture loader and store the results in tasks, impressive
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void dataroom_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), data_room_gfx_table, 0x3000);
    run_func_after_task(task, dataroom_scene_init_gfx3, 0);
}


// Graphics Init. 1
void dataroom_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), dataroom_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Listbox - Get Item Name
const char *dataroom_listbox_get_item_name(u32 item) {
    if (item >= 20) {
        return NULL;
    }

    return D_030046a8->data.readingMaterialUnlocked[item]
        ? reading_material_table[item].title : "???";
}


// Listbox - Update
void dataroom_listbox_update(void) {
    s16 baseLine = func_0800b32c(gDataRoom->listbox);
    u32 x, z;
    u32 i;

    if (gDataRoom->lines[0] >= 0) {
        for (i = 0; i < 8; i++) {
            sprite_delete(gSpriteHandler, gDataRoom->lines[i]);
        }
    }

    x = sprite_get_data(gSpriteHandler, baseLine, 4);
    z = sprite_get_data(gSpriteHandler, baseLine, 6);

    for (i = 0; i < 8; i++) {
        s16 sprite = sprite_clone(gSpriteHandler, baseLine);

        sprite_set_base_palette(gSpriteHandler, sprite, i + 2);
        sprite_set_x(gSpriteHandler, sprite, x + (i + 1));
        sprite_set_z(gSpriteHandler, sprite, z + i + 1);
        gDataRoom->lines[i] = sprite;
    }
}


// Listbox - On-Finish
void dataroom_listbox_on_finish(void) {
    dataroom_listbox_update();
}


// Listbox - On-Scroll
void dataroom_listbox_on_scroll(void) {
    dataroom_listbox_update();

    if (gDataRoom->userState != DATAROOM_USER_SCROLLING) {
        sprite_set_anim(gSpriteHandler, gDataRoom->userSprite, anim_data_room_user_scroll, 0, 1, 0, 0);
        gDataRoom->userState = DATAROOM_USER_SCROLLING;
        gDataRoom->userAnimTimer = 30;
    }

    play_sound(&s_menu_cursor1_seqData);
}


// Scene Start
void dataroom_scene_start(void *sVar, s32 dArg) {
    u32 i;

    func_08007324(FALSE);
    func_080073f0();
    dataroom_scene_init_gfx1();

    sprite_create(gSpriteHandler, anim_data_room_green_led, 0, 188, 155, 0x800, 1, 0, 0);

    for (i = 0; i < 8; i++) {
        gDataRoom->lines[i] = -1;
    }

    gDataRoom->listbox = create_new_listbox(
            get_current_mem_id(), 10, 128, 30, 0, 1, 3,
            80, 16, 0x8800, 16, sListSelItem, 20, anim_data_room_cursor, 3, 4, sListSelLine,
            dataroom_listbox_get_item_name, NULL);
    listbox_run_func_on_scroll(gDataRoom->listbox, dataroom_listbox_on_scroll, 0);
    listbox_run_func_on_finish(gDataRoom->listbox, dataroom_listbox_on_finish, 0);

    gDataRoom->userSprite = sprite_create(gSpriteHandler, anim_data_room_user_stare, 0x7F, 0, 160, 0x4800, 1, 0x7F, 0);
    gDataRoom->userState = DATAROOM_USER_STARING;
    gDataRoom->userAnimTimer = 540;
    gDataRoom->inputsEnabled = FALSE;
}


// Set Scene Static Variables
void dataroom_scene_set_listbox_sel(u32 item, u32 line) {
    sListSelItem = item;
    sListSelLine = line;
}


// Scene Update (Paused)
void dataroom_scene_paused(void *sVar, s32 dArg) {
}


// Update User Sprite
void dataroom_scene_update_user(void) {
    if (gDataRoom->userAnimTimer == 0) {
        return;
    }

    if (--gDataRoom->userAnimTimer == 0) {
        switch (gDataRoom->userState) {
            case DATAROOM_USER_STARING:
                sprite_set_anim(gSpriteHandler, gDataRoom->userSprite, anim_data_room_user_fall_asleep, 0, 1, 0x20, 0);
                gDataRoom->userState = DATAROOM_USER_ASLEEP;
                break;

            case DATAROOM_USER_SCROLLING:
                sprite_set_anim(gSpriteHandler, gDataRoom->userSprite, anim_data_room_user_stare, 0, 1, 0x7F, 0);
                gDataRoom->userState = DATAROOM_USER_STARING;
                gDataRoom->userAnimTimer = 540;
                break;

            case DATAROOM_USER_ASLEEP:
                break;
        }
    }
}


// Scene Update (Active)
void dataroom_scene_update(void *sVar, s32 dArg) {
    u32 event = DATAROOM_EV_NONE;

    if (dataroom_scene_inputs_enabled()) {
        if (D_030053b8 & DPAD_UP) {
            event = DATAROOM_EV_SCROLL_UP;
        }

        if (D_030053b8 & DPAD_DOWN) {
            event = DATAROOM_EV_SCROLL_DOWN;
        }

        if (D_03004afc & B_BUTTON) {
            event = DATAROOM_EV_CANCEL;
        }

        if (D_03004afc & A_BUTTON) {
            event = DATAROOM_EV_CONFIRM;
        }
    }

    switch (event) {
        case DATAROOM_EV_CONFIRM:
            if (!D_030046a8->data.readingMaterialUnlocked[listbox_get_sel_item(gDataRoom->listbox)]) {
                play_sound(&s_menu_error_seqData);
            } else {
                func_080006f0(get_scene_trans_target(&scene_data_room), get_scene_trans_var(&scene_data_room));
                set_next_scene(&scene_reading);
                set_scene_trans_target(&scene_reading, &scene_data_room);
                set_scene_trans_var(&scene_reading, listbox_get_sel_item(gDataRoom->listbox));
                play_sound(&s_menu_kettei2_seqData);
                set_pause_beatscript_scene(FALSE);
                gDataRoom->inputsEnabled = FALSE;
            }
            break;

        case DATAROOM_EV_SCROLL_UP:
            listbox_scroll_up(gDataRoom->listbox);
            break;

        case DATAROOM_EV_SCROLL_DOWN:
            listbox_scroll_down(gDataRoom->listbox);
            break;

        case DATAROOM_EV_CANCEL:
            play_sound(&s_menu_cancel3_seqData);
            set_pause_beatscript_scene(FALSE);
            gDataRoom->inputsEnabled = FALSE;
            break;
    }

    update_listbox(gDataRoom->listbox);
    dataroom_scene_update_user();
}


// Check if Scene Can Receive Inputs
u32 dataroom_scene_inputs_enabled(void) {
    if (gDataRoom->inputsEnabled) {
        return TRUE;
    }

    return FALSE;
}


// Scene Stop
void dataroom_scene_stop(void *sVar, s32 dArg) {
    dataroom_scene_set_listbox_sel(listbox_get_sel_item(gDataRoom->listbox), listbox_get_sel_line(gDataRoom->listbox));
    func_08008628();
    func_08004058();
}
