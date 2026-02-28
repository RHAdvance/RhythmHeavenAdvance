#include "global.h"
#include "studio.h"
#include "graphics/studio/studio_graphics.h"


/* STUDIO DRUM LIST */


// [D_089d83d0] Drum Kit Names
const char *studio_drum_kit_names[] = {
    /* DEFAULT */ "Standard Drum",
    /* DRY     */ "Dry Drum",
    /* POWER   */ "Power Drum",
    /* TECHNO  */ "Techno Drum",
    /* MATTE   */ "Matte Drum",
    /* ASIAN   */ "Asian Drum",
    /* LIGHT   */ "Light Drum",
    /* HEAVY   */ "Heavy Drum",
    /* HIHAT   */ "Hi-Hat Drum",
    /* HEEL1   */ "Heel Drop Drum 1",
    /* HEEL2   */ "Heel Drop Drum 2",
    /* SFX     */ "Sound FX Drum",
    /* TAP     */ "Tap Drum",
    /* AIR     */ "Swift Drum",
    /* SAMURAI */ "Samurai Drum"
};


// Drum Kit List - Get String
const char *studio_drum_list_get_string(s32 line) {
    char numString[0x10];

    if ((line < 0) || (line >= 15)) {
        return NULL;
    }

    strint(numString, line + 1);
    memcpy(gStudio->string, "", 1);
    strcat(gStudio->string, "\0048.");

    if (D_030046a8->data.drumKitsUnlocked[line]) {
        strcat(gStudio->string, studio_drum_kit_names[line]);
    } else {
        strcat(gStudio->string, "HHH");
    }

    return gStudio->string;
}


// Drum Kit List - On Scroll
void studio_drum_list_on_scroll(s32 arg, u32 current, u32 previous) {
    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cursor1_seqData);
}


// Drum Kit List - Init.
void studio_drum_list_init(s32 state, s32 selItem, s32 selLine) {
    gStudio->drumListState = state;
    gStudio->drumList = create_new_listbox(
            get_current_mem_id(), 10, 128, 22, 0, 1, 3, 358, 16, 0x8800, 16,
            selItem, 15, anim_studio_selection_item, 2, 6, clamp_int32(selLine, 0, 5),
            studio_drum_list_get_string, NULL);
    listbox_run_func_on_scroll(gStudio->drumList, studio_drum_list_on_scroll, 0);
}


// Drum Kit List - Exit to Listening Scene
void studio_drum_list_exit_to_drumming(void) {
    const struct Scene *scene;
    s32 songItem, drumItem;

    func_080006f0(get_scene_trans_target(&scene_studio), 1);

    songItem = listbox_get_sel_item(gStudio->songList);
    drumItem = listbox_get_sel_item(gStudio->drumList);
    studio_set_current_kit(drumItem);
    set_next_scene(&scene_drum_studio_drumming);
    set_scene_trans_target(&scene_drum_studio_drumming, &scene_studio);
    set_scene_trans_var(&scene_drum_studio_drumming, songItem);
    func_0801d968(script_scene_studio_exit);
    gStudio->inputsEnabled = FALSE;
}


// Drum Kit List - End of Memory Warning
void studio_drum_list_warning_memory_result(s32 event, s32 arg) {
    if (event == 1) {
        studio_drum_list_exit_to_drumming();
    } else {
        gStudio->sceneState = STUDIO_STATE_NAV_DRUM_LIST;
    }
}


// [D_089d840c] Memory Warnings
const char *studio_mem_warnings_text[] = {
    /* NO WARNING NEEDED ------------------------------ */
        NULL,
    /* NO MEMORY -------------------------------------- */
        // [ You can't save any more data. ]
        // [ Perform without saving? ]
        "Your memory is full.\n"
        "Perform anyway?",
    /* TOO MANY REPLAYS ------------------------------- */
        // [ You can only save 10 recitals. ]
        // [ Perform without saving? ]
        "There's no more room for\n"
        "saving. Perform anyway?",
    /* LOW MEMORY ------------------------------------- */
        // [ There's not much memory left. ]
        // [ Perform anyway? ]
        "Save memory is running low.\n"
        "Do you want to perform anyway?"
    /* ------------------------------------------------ */
};


// Drum Kit List - Update
void studio_drum_list_update(void) {
    struct TengokuSaveData *saveBuffer;
    u32 remaining, warningReason;
    u32 event = STUDIO_LIST_EV_NONE;

    if (!listbox_is_busy(gStudio->drumList) && studio_scene_inputs_enabled()) {
        if (D_03004afc & A_BUTTON) {
            event = STUDIO_LIST_EV_CONFIRM;
        }
        if (D_03004afc & B_BUTTON) {
            event = STUDIO_LIST_EV_CANCEL;
        }
        if (D_030053b8 & DPAD_UP) {
            event = STUDIO_LIST_EV_SCROLL_UP;
        }
        if (D_030053b8 & DPAD_DOWN) {
            event = STUDIO_LIST_EV_SCROLL_DOWN;
        }
    }

    switch(event) {
        case STUDIO_LIST_EV_CONFIRM:
            if (!D_030046a8->data.drumKitsUnlocked[listbox_get_sel_item(gStudio->drumList)]) {
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_error_seqData);
            } else {
                remaining = get_remaining_replay_data_space(&D_030046a8->data.drumReplaysAlloc) >> 8;
                if (remaining != 0) {
                    if (get_available_replay_data_id(&D_030046a8->data.drumReplaysAlloc) < 0) {
                        warningReason = 2;
                    } else if (remaining < 10) {
                        warningReason = 3;
                    } else {
                        warningReason = 0;
                    }
                } else {
                    warningReason = 1;
                }
                if (warningReason != 0) {
                    studio_warning_create(STUDIO_WARNING_OPT_Y, studio_mem_warnings_text[warningReason], studio_drum_list_warning_memory_result, 0, &s_menu_se24_seqData);
                    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                } else {
                    studio_drum_list_exit_to_drumming();
                    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_se24_seqData);
                }
            }
            break;

        case STUDIO_LIST_EV_CANCEL:
            play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
            listbox_hide_sel_sprite(gStudio->drumList);
            listbox_show_sel_sprite(gStudio->optionList);
            studio_scene_pan_to_menu(STUDIO_MENU_OPTION_LIST);
            gStudio->sceneState = STUDIO_STATE_NAV_OPTION_LIST;
            break;

        case STUDIO_LIST_EV_SCROLL_UP:
            listbox_scroll_up(gStudio->drumList);
            break;

        case STUDIO_LIST_EV_SCROLL_DOWN:
            listbox_scroll_down(gStudio->drumList);
            break;
    }
}
