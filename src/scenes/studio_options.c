#include "global.h"
#include "studio.h"
#include "graphics/studio/studio_graphics.h"
#include "src/code_080092cc.h"


/* STUDIO OPTIONS LIST */


// [D_089d841c] Options
const char *studio_options_no_replay[] = {
    /* LISTEN */ "Play",
    /* DRUM   */ "Drum",
    /* SORT   */ "Sort",
    /* MARK   */ "Bookmark"
};


// [D_089d842c] Options (Replay)
const char *studio_options_is_replay[] = {
    /* LISTEN */ "Play",
    /* DELETE */ "Erase Data",
    /* SORT   */ "Sort",
    /* MARK   */ "Bookmark"
};


// [D_089d843c] Option Labels
const char **studio_options_text[] = {
    /* NO_REPLAY */ studio_options_no_replay,
    /* IS_REPLAY */ studio_options_is_replay
};


// [D_089d8444] Total Options
u8 studio_total_options[] = {
    /* NO_REPLAY */ 4,
    /* IS_REPLAY */ 4
};


// Option List - Get String
const char *studio_option_list_get_string(s32 line) {
    char numString[0x10];

    if ((line < 0) || (line >= studio_total_options[gStudio->optionListState])) {
        return NULL;
    }

    strint(numString, line + 1);
    memcpy(gStudio->string, "", 1);
    strcat(gStudio->string, studio_options_text[gStudio->optionListState][line]);

    return gStudio->string;
}


// Option List - On Scroll
void studio_option_list_on_scroll(s32 arg, u32 current, u32 previous) {
    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cursor1_seqData);
}


// Option List - Init.
void studio_option_list_init(s32 state, s32 selItem) {
    gStudio->optionListState = state;
    gStudio->optionList = create_new_listbox(
            get_current_mem_id(), 4, 64, 12, 0, 1, 3, 264, 44, 0x8800, 16,
            selItem, studio_total_options[state], anim_studio_selection_option, 0, 4, clamp_int32(selItem, 0, 3),
            studio_option_list_get_string, NULL);
    listbox_run_func_on_scroll(gStudio->optionList, studio_option_list_on_scroll, 0);
}


// Option List - Check for No Checks
s32 studio_option_list_no_checked_songs(void) {
    u32 i;

    for (i = 0; i < D_030046a8->data.totalSongs; i++) {
        if (!(D_030046a8->data.studioSongs[i].unk3 & 2)) {
            return FALSE;
        }
    }

    return TRUE;
}


// Option List - Exit to Listening Scene
void studio_option_list_exit_to_listening(void) {
    struct Scene *scene;
    s32 var, songItem;

    scene = get_scene_trans_target(&scene_studio);
    var = 0;
    func_080006f0(scene, var);

    songItem = listbox_get_sel_item(gStudio->songList);
    set_next_scene(&scene_drum_studio_listening);
    set_scene_trans_target(&scene_drum_studio_listening, &scene_studio);
    set_scene_trans_var(&scene_drum_studio_listening, songItem);
    func_0801d968(script_scene_studio_exit);
    gStudio->inputsEnabled = FALSE;
}


// Option List - End of "No Checks" Warning
void studio_option_list_warning_no_checks_result(s32 event, s32 arg) {
    gStudio->sceneState = STUDIO_STATE_NAV_OPTION_LIST;
}


// Option List - End of "Unchecked" Warning
void studio_option_list_warning_unchecked_result(s32 event, s32 arg) {
    if (event == 1) {
        studio_option_list_exit_to_listening();
    } else {
        gStudio->sceneState = STUDIO_STATE_NAV_OPTION_LIST;
    }
}


// Options List - End of "Delete" Warning
void studio_option_list_warning_deletion_result(s32 result, s32 arg) {
    s32 selItem, selLine;
    s32 totalSongs;

    if (result == 1) {
        selItem = listbox_get_sel_item(gStudio->songList);
        selLine = listbox_get_sel_line(gStudio->songList);
        delete_listbox(gStudio->songList);

        totalSongs = D_030046a8->data.totalSongs;
        if (totalSongs > 1) {
            delete_studio_song(selItem);
            if (selItem >= (totalSongs - 1)) {
                selItem--;

                if (selLine > 0) {
                    selLine--;
                }
            }
            update_replay_memory_graph_data_bars(gStudio->replayMemoryGraph);
        }
        studio_song_list_init(0, selItem, selLine);
        studio_scene_clear_music();
        listbox_hide_sel_sprite(gStudio->optionList);
        listbox_show_sel_sprite(gStudio->songList);
        studio_scene_pan_to_menu(STUDIO_MENU_SONG_LIST);
        gStudio->sceneState = STUDIO_STATE_NAV_SONG_LIST;
        gStudio->musicPlayer = play_sound(&s_studio_bgm_seqData);
    } else {
        gStudio->sceneState = STUDIO_STATE_NAV_OPTION_LIST;
    }
}


// Option List - Update
void studio_option_list_update(void) {
    s32 songItem, isValid;
    u32 event = STUDIO_LIST_EV_NONE;

    if (!listbox_is_busy(gStudio->optionList) && studio_scene_inputs_enabled()) {
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

    switch (event) {
        case STUDIO_LIST_EV_CONFIRM:
            if (listbox_get_sel_item(gStudio->optionList) == STUDIO_OPTION_LISTEN) {
                if (studio_option_list_no_checked_songs()) {
                    studio_warning_create(
                            STUDIO_WARNING_OPT_DISMISS,
                            // Not even one song has
                            // a check mark on it.
                            "There are currently\n"
                            "no songs selected.",
                            studio_option_list_warning_no_checks_result, 0,
                            &s_menu_kettei2_seqData);
                    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                    rumble_play_menu_confirm();
                } else {
                    songItem = listbox_get_sel_item(gStudio->songList);

                    if (D_030046a8->data.studioSongs[songItem].unk3 & 2) {
                        studio_warning_create(
                                STUDIO_WARNING_OPT_Y,
                                // In listening mode, only the songs
                                // with a check mark will be played.
                                "Only selected songs will be played.\n"
                                "Is that OK?",
                                studio_option_list_warning_unchecked_result, 0,
                                &s_menu_se24_seqData);
                        play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                        rumble_play_menu_confirm();
                    } else {
                        studio_option_list_exit_to_listening();
                        play_sound_in_player(MUSIC_PLAYER_2, &s_menu_se24_seqData);
                        rumble_play_menu_confirm();
                    }
                }
            }

            if (listbox_get_sel_item(gStudio->optionList) == STUDIO_OPTION_DRUM) {
                if (gStudio->optionListState == 0) {
                    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                    rumble_play_menu_confirm();
                    listbox_hide_sel_sprite(gStudio->optionList);
                    listbox_show_sel_sprite(gStudio->drumList);
                    studio_scene_pan_to_menu(STUDIO_MENU_DRUM_LIST);
                    gStudio->sceneState = STUDIO_STATE_NAV_DRUM_LIST;
                } else {
                    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                    rumble_play_menu_confirm();
                    studio_warning_create(
                            STUDIO_WARNING_OPT_N,
                            // You'll erase this performance
                            // data! Is that really OK?
                            "Delete this drum performance!\n"
                            "Are you sure?",
                            studio_option_list_warning_deletion_result, 0,
                            &s_menu_se13_seqData);
                }
            }

            if (listbox_get_sel_item(gStudio->optionList) == STUDIO_OPTION_SORT) {
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                rumble_play_menu_confirm();
                listbox_hide_sel_sprite(gStudio->optionList);
                listbox_show_sel_sprite(gStudio->songList);
                gStudio->selectedItem = listbox_get_sel_item(gStudio->songList);
                listbox_link_sprite_x_y_to_line(gStudio->songList, gStudio->itemMoveHighlight, gStudio->selectedItem);
                sprite_set_visible(gSpriteHandler, gStudio->itemMoveHighlight, TRUE);
                gStudio->sceneState = STUDIO_STATE_EDIT_VIA_OPTION_LIST;
            }

            if (listbox_get_sel_item(gStudio->optionList) == STUDIO_OPTION_MARK) {
                songItem = listbox_get_sel_item(gStudio->songList);
                isValid = TRUE;

                if (D_030046a8->data.studioSongs[songItem].songID == STUDIO_SONG_SILENCE) {
                    if (!(D_030046a8->data.studioSongs[songItem].unk3 & 1)) {
                        isValid = FALSE;
                    }
                }

                if (isValid) {
                    D_030046a8->data.studioSongs[songItem].unk3 ^= 2;
                    func_0800b454(gStudio->songList, songItem);

                    if (D_030046a8->data.studioSongs[songItem].unk3 & 2) {
                        play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
                        rumble_play_menu_cancel();
                    } else {
                        play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                        rumble_play_menu_confirm();
                    }
                } else {
                    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_error_seqData);
                    rumble_play_menu_error();
                }
            }
            break;

        case STUDIO_LIST_EV_CANCEL:
            play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
            rumble_play_menu_cancel();
            studio_scene_clear_music();
            listbox_hide_sel_sprite(gStudio->optionList);
            listbox_show_sel_sprite(gStudio->songList);
            studio_scene_pan_to_menu(STUDIO_MENU_SONG_LIST);
            gStudio->musicPlayer = play_sound(&s_studio_bgm_seqData);
            gStudio->sceneState = STUDIO_STATE_NAV_SONG_LIST;
            break;

        case STUDIO_LIST_EV_SCROLL_UP:
            if (listbox_get_sel_item(gStudio->optionList) <= 0) {
                rumble_play_menu_limit();
            } else {
                listbox_scroll_up(gStudio->optionList);
            }
            break;

        case STUDIO_LIST_EV_SCROLL_DOWN:
            if (listbox_get_sel_item(gStudio->optionList) >= (gStudio->optionList->totalItems - 1)) {
                rumble_play_menu_limit();
            } else {
                listbox_scroll_down(gStudio->optionList);
            }
            break;
    }
}


// Option List - Update (Moving Item)
void studio_option_list_update_w_selection(void) {
    s32 songItem;
    u32 event = STUDIO_LIST_EV_NONE;

    if (!listbox_is_busy(gStudio->songList) && studio_scene_inputs_enabled()) {
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
            songItem = listbox_get_sel_item(gStudio->songList);
            if (songItem != gStudio->selectedItem) {
                studio_song_list_move_item(gStudio->selectedItem, songItem);
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                rumble_play_menu_confirm();
                sprite_set_visible(gSpriteHandler, gStudio->itemMoveHighlight, FALSE);
                listbox_set_sel_sprite(gStudio->songList, anim_studio_selection_item);
                listbox_show_sel_sprite(gStudio->optionList);
                listbox_hide_sel_sprite(gStudio->songList);
                gStudio->sceneState = STUDIO_STATE_NAV_OPTION_LIST;
                break;
            }

        case STUDIO_LIST_EV_CANCEL:
            play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
            rumble_play_menu_cancel();
            sprite_set_visible(gSpriteHandler, gStudio->itemMoveHighlight, FALSE);
            listbox_set_sel_sprite(gStudio->songList, anim_studio_selection_item);
            listbox_show_sel_sprite(gStudio->optionList);
            listbox_hide_sel_sprite(gStudio->songList);
            gStudio->sceneState = STUDIO_STATE_NAV_OPTION_LIST;
            break;

        case STUDIO_LIST_EV_SCROLL_UP:
            if (listbox_get_sel_item(gStudio->songList) <= 0) {
                rumble_play_menu_limit();
            } else {
                listbox_scroll_up(gStudio->songList);
            }
            break;

        case STUDIO_LIST_EV_SCROLL_DOWN:
            if (listbox_get_sel_item(gStudio->songList) >= (gStudio->songList->totalItems - 1)) {
                rumble_play_menu_limit();
            } else {
                listbox_scroll_down(gStudio->songList);
            }
            break;
    }
}
