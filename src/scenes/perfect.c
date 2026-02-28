#include "global.h"
#include "scenes.h"
#include "perfect.h"
#include "graphics/perfect/perfect_certificate_graphics.h"

#include "levels.h"
#include "src/scenes/game_select.h"
#include "src/scenes/studio.h"


/* PERFECT CERTIFICATE SCENE */


// Init. Static Variables
void perfect_scene_init_memory(void) {
}


// Graphics Init. 3
void perfect_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), perfect_certificate_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void perfect_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), perfect_certificate_gfx_table, 0x3000);
    run_func_after_task(task, perfect_scene_init_gfx3, 0);
}


// Graphics Init. 1
void perfect_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), perfect_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void perfect_scene_start(void *sVar, s32 dArg) {
    char count[0x10];
    u32 campaignsLeft;
    u32 giftType, giftID;

    func_08007324(FALSE);
    func_080073f0();
    perfect_scene_init_gfx1();

    gPerfect->campaignID = get_current_campaign();

    if ((gPerfect->campaignID >= 0) && results_campaign_is_enabled()) {
        giftType = campaign_gifts_table[gPerfect->campaignID].type;
        giftID = campaign_gifts_table[gPerfect->campaignID].id;

        if (!get_campaign_cleared(&D_030046a8->data, gPerfect->campaignID)) {
            switch (giftType) {
                case CAMPAIGN_GIFT_SONG:
                    save_studio_song(giftID, -1, 1, 0);
                    break;

                case CAMPAIGN_GIFT_DRUM_KIT:
                    D_030046a8->data.drumKitsUnlocked[giftID] = TRUE;
                    break;

                case CAMPAIGN_GIFT_READING_MATERIAL:
                    set_reading_material_unlocked(&D_030046a8->data, giftID, TRUE);
                    break;
            }

            D_030046a8->data.totalPerfects++;
            set_campaign_cleared(&D_030046a8->data, gPerfect->campaignID, TRUE);

            if (D_030046a8->data.totalPerfects == TOTAL_PERFECT_CAMPAIGNS) {
                unlock_all_unassigned_campaign_gift_songs();
                D_030046a8->data.unk294[9] = TRUE;
            }

            cafe_session_add_perfect_level(get_level_id_from_grid_xy(D_030046a8->data.recentLevelX, D_030046a8->data.recentLevelY));
            results_save_to_cart(LEVEL_STATE_NULL);
        }
    } else {
        gPerfect->campaignID = 0;
        giftType = campaign_gifts_table[gPerfect->campaignID].type;
        giftID = campaign_gifts_table[gPerfect->campaignID].id;
    }

    gPerfect->printer = text_printer_create_new(get_current_mem_id(), 4, 238, 32);
    text_printer_set_x_y(gPerfect->printer, 1, 88);
    text_printer_set_layer(gPerfect->printer, 0x800);
    text_printer_set_colors(gPerfect->printer, 1);
    text_printer_set_palette(gPerfect->printer, 4);
    text_printer_set_line_spacing(gPerfect->printer, 16);
    text_printer_center_by_content(gPerfect->printer, TRUE);

    campaignsLeft = TOTAL_PERFECT_CAMPAIGNS - D_030046a8->data.totalPerfects;
    strint(count, campaignsLeft);
    memcpy(gPerfect->string, "\0021" "\0011" "\001C" "\0030" "\001s" "\0054" "\0018" "", 25);
    strcat(gPerfect->string, get_campaign_gift_title(gPerfect->campaignID, FALSE));
    strcat(gPerfect->string, "");

    if (giftType == CAMPAIGN_GIFT_SONG) {
        switch (giftID) {
            case STUDIO_SONG_HONEY_SWEET_ANGEL:
            case STUDIO_SONG_WISH:
                break;

            default:
                strcat(gPerfect->string, "'s song");
                break;
        }
    }

    strcat(gPerfect->string, "\0020" "\0010" "\nYou've earned a gift! "); // You've earned a gift!
    strcat(gPerfect->string, perfect_gift_directive_text[giftType]);

    if (campaignsLeft > 0) {
        strcat(gPerfect->string, "Looks like there are still " "\0021" "\0011"); // There are still...
        strcat(gPerfect->string, count);
        if (campaignsLeft > 1) {
            strcat(gPerfect->string, " gifts " "\0020" "\0010" "left.\n" // ...gifts
                                         "Keep up the good work!"); // left to get. Keep going!
        } else {
            strcat(gPerfect->string, " gift " "\0020" "\0010" "left.\n" // ...gift
                                         "Keep up the good work!"); // left to get. Keep going!
        }
    } else {
        strcat(gPerfect->string,"\0021" "\0011" "You've earned all of the gifts!" "\0020" "\0010" "\n"); // You finally got them all!
        strcat(gPerfect->string, "That means you got a Perfect in everything!"); // Congratulations!
    }

    text_printer_set_string(gPerfect->printer, gPerfect->string);

    gPerfect->inputsEnabled = FALSE;
}


// Unlock Studio Songs
void unlock_all_unassigned_campaign_gift_songs(void) {
    s8 *studioSongs;

    if (*unassigned_campaign_gift_songs < 0) {
        return;
    }

    for (studioSongs = unassigned_campaign_gift_songs; *studioSongs >= 0; studioSongs++) {
        save_studio_song(*studioSongs, -1, 1, 0);
    }
}


// Scene Update (Paused)
void perfect_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void perfect_scene_update(void *sVar, s32 dArg) {
    if (perfect_scene_inputs_enabled()) {
        if (D_03004afc & A_BUTTON) {
            play_sound(&s_menu_kettei2_seqData);
            set_pause_beatscript_scene(FALSE);
            gPerfect->inputsEnabled = FALSE;
        }
    }

    text_printer_update(gPerfect->printer);
}


// Check if Scene Can Receive Inputs
u32 perfect_scene_inputs_enabled(void) {
    if (gPerfect->inputsEnabled) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Scene Stop
void perfect_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}
