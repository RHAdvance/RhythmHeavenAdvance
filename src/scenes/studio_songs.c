#include "global.h"
#include "studio.h"
#include "graphics/studio/studio_graphics.h"
#include "src/code_080092cc.h"


/* STUDIO SONG LIST */


// Song Save Data - Unlock Default Songs
void unlock_default_studio_songs(void) {
    save_studio_song(STUDIO_SONG_SILENCE, -1, 1, 2);
    save_studio_song(STUDIO_SONG_TITLE, -1, 1, 0);
    save_studio_song(STUDIO_SONG_OPENING, -1, 1, 0);
    save_studio_song(STUDIO_SONG_MAIN_MENU, -1, 1, 0);
    save_studio_song(STUDIO_SONG_GAME_SELECT_1, -1, 1, 0);
    save_studio_song(STUDIO_SONG_DATA_ROOM, -1, 1, 0);
}


// Song Save Data - Save
s32 save_studio_song(s32 song, s32 replay, s32 drumKit, s32 flags) {
    struct StudioSongData *data;
    s32 id;

    id = D_030046a8->data.totalSongs;

    if (id >= 55) {
        return -1;
    }

    data = &D_030046a8->data.studioSongs[id];
    data->songID = song;
    data->replayID = replay;
    data->drumKitID = drumKit;
    data->unk3 = flags;
    D_030046a8->data.totalSongs++;

    return id;
}


// Song Save Data - Swap
void swap_studio_songs(s32 id1, s32 id2) {
    struct StudioSongData *data1, *data2;
    struct StudioSongData temp;

    data1 = &D_030046a8->data.studioSongs[id1];
    data2 = &D_030046a8->data.studioSongs[id2];

    temp.songID = data1->songID;
    temp.replayID = data1->replayID;
    temp.drumKitID = data1->drumKitID;
    temp.unk3 = data1->unk3;

    data1->songID = data2->songID;
    data1->replayID = data2->replayID;
    data1->drumKitID = data2->drumKitID;
    data1->unk3 = data2->unk3;

    data2->songID = temp.songID;
    data2->replayID = temp.replayID;
    data2->drumKitID = temp.drumKitID;
    data2->unk3 = temp.unk3;
}


// Song Save Data - Move
void move_studio_song(s32 id, s32 newIndex) {
    if (id > newIndex) {
        while (id > newIndex) {
            swap_studio_songs(id, id - 1);
            id--;
        }
    } else {
        while (id < newIndex) {
            swap_studio_songs(id, id + 1);
            id++;
        }
    }
}


// Song Save Data - Delete
void delete_studio_song(s32 id) {
    s32 totalSongs, replay;
    u32 i;

    totalSongs = D_030046a8->data.totalSongs;
    replay = D_030046a8->data.studioSongs[id].replayID;

    if (replay >= 0) {
        delete_saved_replay(&D_030046a8->data.drumReplaysAlloc, replay);
    }

    for (i = id; i < (totalSongs - 1); i++) {
        D_030046a8->data.studioSongs[i].songID = D_030046a8->data.studioSongs[i+1].songID;
        D_030046a8->data.studioSongs[i].replayID = D_030046a8->data.studioSongs[i+1].replayID;
        D_030046a8->data.studioSongs[i].drumKitID = D_030046a8->data.studioSongs[i+1].drumKitID;
        D_030046a8->data.studioSongs[i].unk3 = D_030046a8->data.studioSongs[i+1].unk3;
    }

    D_030046a8->data.totalSongs--;
}


// Song List - Get String
const char *studio_song_list_get_string(s32 line) {
    struct StudioSongData *songData;
    struct StudioEntry *songEntry;
    char numString[0x10];

    if ((line < 0) || (line >= D_030046a8->data.totalSongs)) {
        return NULL;
    }

    strint(numString, line + 1);
    memcpy(gStudio->string, "\00414.", 5);
    songData = &D_030046a8->data.studioSongs[line];
    songEntry = &studio_song_table[songData->songID];

    if (songEntry->shortTitle != NULL) {
        strcat(gStudio->string, songEntry->shortTitle);
    } else {
        strcat(gStudio->string, songEntry->fullTitle);
    }

    return gStudio->string;
}


// Song List - Get Sprite
s16 studio_song_list_get_sprite(s32 line) {
    struct StudioSongData *songData;

    if ((line < 0) || (line >= D_030046a8->data.totalSongs)) {
        return -1;
    }

    switch (D_030046a8->data.studioSongs[line].unk3 & 3u) {
        case 0:
            return sprite_create(gSpriteHandler, anim_studio_item_marker_check, 0, 64, 64, 0, 0, 0, 0);

        case 1:
            return sprite_create(gSpriteHandler, anim_studio_item_markers, D_030046a8->data.studioSongs[line].replayID, 118, 96, 0, 0, 0, 0);

        case 3:
            return sprite_create(gSpriteHandler, anim_studio_item_marker_replay, D_030046a8->data.studioSongs[line].replayID, 64, 64, 0, 0, 0, 0);

        default:
            return -1;
    }
}


// Song List - On Scroll
void studio_song_list_on_scroll(s32 arg, u32 current, u32 previous) {
    s32 isMoveState = FALSE;

    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cursor1_seqData);

    if (gStudio->sceneState == 4) {
        isMoveState = TRUE;
    }

    if (gStudio->sceneState == 5) {
        isMoveState = TRUE;
    }

    if (isMoveState) {
        if (current == gStudio->selectedItem) {
            listbox_set_sel_sprite(gStudio->songList, anim_studio_selection_item);
        } else if (current < gStudio->selectedItem) {
            listbox_set_sel_sprite(gStudio->songList, anim_studio_item_move_above);
        } else {
            listbox_set_sel_sprite(gStudio->songList, anim_studio_item_move_below);
        }
    }
}


// Song List - Init.
void studio_song_list_init(s32 state, s32 selItem, s32 selLine) {
    gStudio->songListState = state;
    gStudio->songList = create_new_listbox(
            get_current_mem_id(), 10, 128, 32, 0, 1, 3, 118, 16, 0x8800, 16,
            selItem, D_030046a8->data.totalSongs, anim_studio_selection_item, 2, 6, selLine,
            studio_song_list_get_string, studio_song_list_get_sprite);
    listbox_run_func_on_scroll(gStudio->songList, studio_song_list_on_scroll, 0);
}


// Song List - Update
void studio_song_list_update(void) {
    s32 songItem, optionItem;
    s32 event = STUDIO_LIST_EV_NONE;

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
        if (D_03004afc & LEFT_SHOULDER_BUTTON) {
            event = STUDIO_LIST_EV_MOVE_ITEM;
        }
        if (D_03004afc & RIGHT_SHOULDER_BUTTON) {
            event = STUDIO_LIST_EV_CHECK_ITEM;
        }
    }

    switch (event) {
        case STUDIO_LIST_EV_CONFIRM:
            stop_sound(&s_studio_bgm_seqData);
            play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
            rumble_play_menu_confirm();

            songItem = listbox_get_sel_item(gStudio->songList);
            studio_scene_play_music(songItem);
            optionItem = listbox_get_sel_item(gStudio->optionList);
            delete_listbox(gStudio->optionList);

            if (D_030046a8->data.studioSongs[songItem].replayID < 0) {
                studio_option_list_init(FALSE, optionItem);
            } else {
                if (optionItem == STUDIO_OPTION_DELETE) {
                    optionItem = STUDIO_OPTION_LISTEN;
                }
                studio_option_list_init(TRUE, optionItem);
            }

            listbox_hide_sel_sprite(gStudio->songList);
            listbox_show_sel_sprite(gStudio->optionList);
            studio_scene_pan_to_menu(STUDIO_MENU_OPTION_LIST);
            gStudio->sceneState = STUDIO_STATE_NAV_OPTION_LIST;
            break;

        case STUDIO_LIST_EV_CANCEL:
            play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
            rumble_play_menu_cancel();
            listbox_hide_sel_sprite(gStudio->songList);
            func_0801d968(script_scene_studio_exit);
            gStudio->inputsEnabled = FALSE;
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

        case STUDIO_LIST_EV_MOVE_ITEM:
            play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
            rumble_play_menu_confirm();
            gStudio->selectedItem = listbox_get_sel_item(gStudio->songList);
            listbox_link_sprite_x_y_to_line(gStudio->songList, gStudio->itemMoveHighlight, gStudio->selectedItem);
            sprite_set_visible(gSpriteHandler, gStudio->itemMoveHighlight, TRUE);
            gStudio->sceneState = STUDIO_STATE_EDIT_VIA_SONG_LIST;
            break;

        case STUDIO_LIST_EV_CHECK_ITEM:
            songItem = listbox_get_sel_item(gStudio->songList);
            if ((D_030046a8->data.studioSongs[songItem].songID == STUDIO_SONG_SILENCE)
              && ((D_030046a8->data.studioSongs[songItem].unk3 & 1) == 0)) {
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_error_seqData);
                rumble_play_menu_error();
            } else {
                D_030046a8->data.studioSongs[songItem].unk3 ^= 2;
                func_0800b454(gStudio->songList, songItem);
                if (D_030046a8->data.studioSongs[songItem].unk3 & 2) {
                    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
                    rumble_play_menu_cancel();
                } else {
                    play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                    rumble_play_menu_confirm();
                }
            }
            break;
    }
}


// Song List - Select Item
void studio_song_list_select_item(s32 id) {
    studio_set_current_song(id, clamp_int32(id, 0, 5));
}


// Song List - Move Item
void studio_song_list_move_item(s32 prevIndex, s32 newIndex) {
    s32 first, last;
    s32 i;

    move_studio_song(prevIndex, newIndex);

    if (prevIndex < newIndex) {
        first = prevIndex;
        last = newIndex;
    } else {
        last = prevIndex;
        first = newIndex;
    }

    for (i = first; i <= last; i++) {
        func_0800b454(gStudio->songList, i);
    }
}


// Song List - Update (Moving Selected Item)
void studio_song_list_update_w_selection(void) {
    s32 songItem;
    u32 event = STUDIO_LIST_EV_NONE;

    if (!listbox_is_busy(gStudio->songList) && studio_scene_inputs_enabled()) {
        if (D_03004afc & LEFT_SHOULDER_BUTTON) {
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
            songItem = listbox_get_sel_item(gStudio->songList);
            if (songItem != gStudio->selectedItem) {
                studio_song_list_move_item(gStudio->selectedItem, songItem);
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_kettei2_seqData);
                rumble_play_menu_confirm();
                sprite_set_visible(gSpriteHandler, gStudio->itemMoveHighlight, FALSE);
                listbox_set_sel_sprite(gStudio->songList, anim_studio_selection_item);
                gStudio->sceneState = STUDIO_STATE_NAV_SONG_LIST;
                break;
            }

        case STUDIO_LIST_EV_CANCEL:
            play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
            rumble_play_menu_cancel();
            sprite_set_visible(gSpriteHandler, gStudio->itemMoveHighlight, FALSE);
            listbox_set_sel_sprite(gStudio->songList, anim_studio_selection_item);
            gStudio->sceneState = STUDIO_STATE_NAV_SONG_LIST;
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


#include "data/scenes/studio/songs.inc.c"
