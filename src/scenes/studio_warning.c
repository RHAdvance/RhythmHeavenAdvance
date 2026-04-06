#include "global.h"
#include "studio.h"
#include "graphics/studio/studio_graphics.h"
#include "src/code_080092cc.h"


/* STUDIO WARNING POPUP */


// Warning Notice - On-Finish Function
void studio_warning_show(void) {
    scene_show_bg_layer(BG_LAYER_0);
    sprite_set_visible(gSpriteHandler, gStudio->warningAdvIcon, TRUE);
    gStudio->warningIsRendering = FALSE;
}


// Warning Notice - Init.
void studio_warning_init(void) {
    gStudio->warningAdvIcon = sprite_create(gSpriteHandler, anim_studio_warning_options_y, 0, 120, 120, 0x800, 1, 0, 0x8000);
    gStudio->warningPrinter = text_printer_create_new(get_current_mem_id(), 2, 160, 10);
    text_printer_set_x_y(gStudio->warningPrinter, 40, 84);
    text_printer_set_layer(gStudio->warningPrinter, 0x800);
    text_printer_center_by_content(gStudio->warningPrinter, TRUE);
    text_printer_run_func_on_finish(gStudio->warningPrinter, studio_warning_show, 0);
}


// Warning Notice - Update
void studio_warning_update(void) {
    s32 event = 0;

    if (!gStudio->warningIsActive) {
        return;
    }

    if (gStudio->warningIsRendering) {
        text_printer_update(gStudio->warningPrinter);
        return;
    }

    switch (gStudio->warningOption) {
        case STUDIO_WARNING_OPT_DISMISS:
            if (D_03004afc & (A_BUTTON | B_BUTTON)) {
                play_sound_in_player(MUSIC_PLAYER_2, gStudio->warningSfx);
                rumble_play_menu_confirm();
                event = 1;
            }
            break;

        case STUDIO_WARNING_OPT_Y:
            if (D_03004afc & DPAD_RIGHT) {
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cursor1_seqData);
                gStudio->warningOption = STUDIO_WARNING_OPT_N;
                sprite_set_anim(gSpriteHandler, gStudio->warningAdvIcon, anim_studio_warning_options_n, 0, 1, 0, 0);
                rumble_play_menu_move();
            } else if (D_03004afc & A_BUTTON) {
                play_sound_in_player(MUSIC_PLAYER_2, gStudio->warningSfx);
                rumble_play_menu_confirm();
                event = 1;
            } else if (D_03004afc & B_BUTTON) {
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
                rumble_play_menu_cancel();
                event = 3;
            } else if (D_03004afc & DPAD_LEFT) {
                rumble_play_menu_limit();
            }
            break;

        case STUDIO_WARNING_OPT_N:
            if (D_03004afc & DPAD_LEFT) {
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cursor1_seqData);
                gStudio->warningOption = STUDIO_WARNING_OPT_Y;
                sprite_set_anim(gSpriteHandler, gStudio->warningAdvIcon, anim_studio_warning_options_y, 0, 1, 0, 0);
                rumble_play_menu_move();
            } else if (D_03004afc & A_BUTTON) {
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
                rumble_play_menu_cancel();
                event = 2;
            } else if (D_03004afc & B_BUTTON) {
                play_sound_in_player(MUSIC_PLAYER_2, &s_menu_cancel3_seqData);
                rumble_play_menu_cancel();
                event = 3;
            } else if (D_03004afc & DPAD_RIGHT) {
                rumble_play_menu_limit();
            }
            break;
    }

    if (event != 0) {
        studio_warning_remove();

        if (gStudio->warningEvent != NULL) {
            gStudio->warningEvent(event, gStudio->warningEventArg);
        }
    }
}


// Warning Notice - Create
void studio_warning_create(u32 options, const char *dialogue, void eventFunc(s32, s32), s32 eventArg, struct SongHeader *sfx) {
    switch (options) {
        case STUDIO_WARNING_OPT_DISMISS:
            sprite_set_anim(gSpriteHandler, gStudio->warningAdvIcon, anim_studio_text_adv_icon, 0, 1, 0, 0);
            break;

        case STUDIO_WARNING_OPT_Y:
            sprite_set_anim(gSpriteHandler, gStudio->warningAdvIcon, anim_studio_warning_options_y, 0, 1, 0, 0);
            break;

        case STUDIO_WARNING_OPT_N:
            sprite_set_anim(gSpriteHandler, gStudio->warningAdvIcon, anim_studio_warning_options_n, 0, 1, 0, 0);
            break;
    }

    text_printer_set_string(gStudio->warningPrinter, dialogue);
    gStudio->warningOption = options;
    gStudio->warningEvent = eventFunc;
    gStudio->warningEventArg = eventArg;
    gStudio->warningSfx = sfx;
    gStudio->warningIsActive = TRUE;
    gStudio->warningIsRendering = TRUE;
    gStudio->sceneState = STUDIO_STATE_WARNING_DISPLAY;
}


// Warning Notice - Remove
void studio_warning_remove(void) {
    text_printer_clear(gStudio->warningPrinter);
    scene_hide_bg_layer(BG_LAYER_0);
    sprite_set_visible(gSpriteHandler, gStudio->warningAdvIcon, FALSE);
    gStudio->warningIsActive = FALSE;
    gStudio->warningIsRendering = FALSE;
}
