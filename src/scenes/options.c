#include "global.h"
#include "options.h"
#include "graphics/options/options_graphics.h"
#include "src/bitmap_font.h"
#include "src/code_0800b778.h"
#include "src/code_080092cc.h"

extern u8 haveSeenDisclaimer;

static void options_scene_refresh_classic_visuals(void);
static const char *options_scene_bitmap_get_value(s32 entry);
static void options_scene_bitmap_build_line_text(s32 line, u32 lineBuffer);
static void options_scene_bitmap_delete_line_sprite(u32 lineIndex);
static void options_scene_bitmap_refresh_visible_lines(void);
static void options_scene_bitmap_refresh_line(s32 itemIndex);
static void options_scene_bitmap_position_lines(s16 yOffset);
static void options_scene_bitmap_set_description(u32 selected);
static void options_scene_set_page(u32 page);
static void options_scene_update_main_classic(void);
static void options_scene_update_main_bitmap(void);
static void options_scene_shoulder_hold_cb(struct SpriteHandler *handler, s16 sprite, u32 arg);
static void options_scene_rshoulder_switch_cb(struct SpriteHandler *handler, s16 sprite, u32 arg);
static void options_scene_lshoulder_switch_cb(struct SpriteHandler *handler, s16 sprite, u32 arg);


/* OPTIONS MENU SCENE */


// Init. Static Variables
void options_scene_init_memory(void) {
}


// Graphics Init. 3
void options_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), options_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void options_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), options_gfx_table, 0x3000);
    run_func_after_task(task, options_scene_init_gfx3, 0);
}


// Graphics Init. 1
void options_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), options_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}

static void options_scene_refresh_classic_visuals(void) {
    if (gOptionsMenu->cursorPos == OPTIONS_BUTTON_SOUND_MODE) {
        sprite_set_y(gSpriteHandler, gOptionsMenu->uiBarista, OPTIONS_CURSOR_SOUND_MODE_Y);
        sprite_set_anim(gSpriteHandler, gOptionsMenu->uiSoundMode, options_sound_mode_anim[gOptionsMenu->soundMode][OPTIONS_BUTTON_ON], 0x7F, 1, 0x7F, 0);
        sprite_set_anim(gSpriteHandler, gOptionsMenu->uiDataClear, anim_options_off_data_clear, 0, 0, 0, 0);
    } else {
        sprite_set_y(gSpriteHandler, gOptionsMenu->uiBarista, OPTIONS_CURSOR_DATA_CLEAR_Y);
        sprite_set_anim(gSpriteHandler, gOptionsMenu->uiSoundMode, options_sound_mode_anim[gOptionsMenu->soundMode][OPTIONS_BUTTON_OFF], 0, 0, 0, 0);
        sprite_set_anim(gSpriteHandler, gOptionsMenu->uiDataClear, anim_options_select_data_clear, 0, 0, 0, 0);
    }
}

static const char *options_scene_bitmap_get_value(s32 entry) {
    switch (entry) {
        case OPTIONS_BITMAP_NON_JP_SFX:
            return CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_SFX) ? "English" : "Japanese";

        case OPTIONS_BITMAP_NON_JP_MUSIC:
            return CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_MUSIC) ? "English" : "Japanese";
#ifdef RUMBLE
        case OPTIONS_BITMAP_RUMBLE:
            return CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_DISABLE_RUMBLE) ? "Off" : "On";
#endif
        case OPTIONS_BITMAP_SKIP_DISCLAIMER:
            return CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_SKIP_DISCLAIMER) ? "Skip" : "Show";

        case OPTIONS_BITMAP_ALT_GAME_SELECT_MUSIC:
            return CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_USE_ALT_GAME_SELECT_MUSIC) ? "On" : "Off";
    }

    return "SHAFFY FUCKED UP";
}

static void options_scene_bitmap_build_line_text(s32 line, u32 lineBuffer) {
    if (lineBuffer >= OPTIONS_BITMAP_LINE_SPRITE_COUNT) {
        return;
    }

    if ((line < 0) || (line >= OPTIONS_BITMAP_TOTAL)) {
        gOptionsMenu->bitmapLineBuffer[lineBuffer][0] = '\0';
        return;
    }

    snprintf(gOptionsMenu->bitmapLineBuffer[lineBuffer], OPTIONS_BITMAP_LINE_BUFFER_SIZE, "%s: %s",
            advance_options_label_text[line], options_scene_bitmap_get_value(line));
}

static void options_scene_bitmap_delete_line_sprite(u32 lineIndex) {
    s16 sprite;

    if (lineIndex >= OPTIONS_BITMAP_LINE_SPRITE_COUNT) {
        return;
    }

    sprite = gOptionsMenu->bitmapLineSprites[lineIndex];
    if (sprite < 0) {
        return;
    }

    bmp_font_obj_delete_printed_anim(gOptionsMenu->bitmapFont, (struct Animation *)sprite_get_data(gSpriteHandler, sprite, 7));
    sprite_delete(gSpriteHandler, sprite);
    gOptionsMenu->bitmapLineSprites[lineIndex] = -1;
}

static void options_scene_bitmap_refresh_visible_lines(void) {
    u32 line;

    for (line = 0; line < OPTIONS_BITMAP_LINE_SPRITE_COUNT; line++) {
        struct PrintedTextAnim *textAnim;
        s32 itemIndex;

        options_scene_bitmap_delete_line_sprite(line);

        itemIndex = gOptionsMenu->bitmapTopIndex + ((s32)line - OPTIONS_BITMAP_LINE_CENTER_INDEX);
        if ((itemIndex < 0) || (itemIndex >= OPTIONS_BITMAP_TOTAL)) {
            continue;
        }

        options_scene_bitmap_build_line_text(itemIndex, line);
        textAnim = bmp_font_obj_print_l(gOptionsMenu->bitmapFont, gOptionsMenu->bitmapLineBuffer[line], 1, 0);
        gOptionsMenu->bitmapLineSprites[line] = sprite_create(gSpriteHandler, textAnim->frames, 0,
                OPTIONS_BITMAP_TEXT_X,
            OPTIONS_BITMAP_LINE_START_Y + (((s32)line - OPTIONS_BITMAP_LINE_CENTER_INDEX) * OPTIONS_BITMAP_LINE_SPACING_Y),
                OPTIONS_BITMAP_TEXT_Z, 0, 0, 0);

        sprite_set_base_palette(gSpriteHandler, gOptionsMenu->bitmapLineSprites[line],
                (itemIndex == gOptionsMenu->bitmapSelected) ? 7 : 6); // hahahah 67
    }

    options_scene_bitmap_position_lines(gOptionsMenu->bitmapCursor);
}

static void options_scene_bitmap_refresh_line(s32 itemIndex) {
    s16 lineIndex;
    struct PrintedTextAnim *textAnim;
    s16 y;

    if ((itemIndex < 0) || (itemIndex >= OPTIONS_BITMAP_TOTAL)) {
        return;
    }

    lineIndex = (itemIndex - gOptionsMenu->bitmapTopIndex) + OPTIONS_BITMAP_LINE_CENTER_INDEX;
    if ((lineIndex < 0) || (lineIndex >= OPTIONS_BITMAP_LINE_SPRITE_COUNT)) {
        return;
    }

    options_scene_bitmap_delete_line_sprite(lineIndex);
    options_scene_bitmap_build_line_text(itemIndex, lineIndex);

    textAnim = bmp_font_obj_print_l(gOptionsMenu->bitmapFont, gOptionsMenu->bitmapLineBuffer[lineIndex], 1, 0);
    y = OPTIONS_BITMAP_LINE_START_Y
            + (((s32)lineIndex - OPTIONS_BITMAP_LINE_CENTER_INDEX) * OPTIONS_BITMAP_LINE_SPACING_Y)
            + gOptionsMenu->bitmapCursor;
    gOptionsMenu->bitmapLineSprites[lineIndex] = sprite_create(gSpriteHandler, textAnim->frames, 0,
            OPTIONS_BITMAP_TEXT_X, y,
            OPTIONS_BITMAP_TEXT_Z, 0, 0, 0);

    sprite_set_base_palette(gSpriteHandler, gOptionsMenu->bitmapLineSprites[lineIndex],
            (itemIndex == gOptionsMenu->bitmapSelected) ? 7 : 6);
}

static void options_scene_bitmap_position_lines(s16 yOffset) {
    u32 line;
    s16 y;
    const s16 minY = OPTIONS_BITMAP_LINE_START_Y;
    const s16 maxY = OPTIONS_BITMAP_LINE_START_Y
            + ((OPTIONS_BITMAP_VISIBLE_ROWS - 1) * OPTIONS_BITMAP_LINE_SPACING_Y);
    const s16 transitionMinY = minY - OPTIONS_BITMAP_LINE_SPACING_Y;
    const s16 transitionMaxY = maxY + OPTIONS_BITMAP_LINE_SPACING_Y;
    u32 moving;

    moving = (yOffset != 0);

    for (line = 0; line < OPTIONS_BITMAP_LINE_SPRITE_COUNT; line++) {
        if (gOptionsMenu->bitmapLineSprites[line] >= 0) {
            y = OPTIONS_BITMAP_LINE_START_Y
                    + (((s32)line - OPTIONS_BITMAP_LINE_CENTER_INDEX) * OPTIONS_BITMAP_LINE_SPACING_Y)
                    + yOffset;

            sprite_set_y(gSpriteHandler, gOptionsMenu->bitmapLineSprites[line], y);
            sprite_set_visible(gSpriteHandler, gOptionsMenu->bitmapLineSprites[line],
                    moving ? ((y >= transitionMinY) && (y <= transitionMaxY))
                           : ((y >= minY) && (y <= maxY)));
        }
    }
}

static void options_scene_bitmap_set_selection(s32 newSelection) {
    s32 oldSelection;
    s32 oldTopIndex;
    s32 maxTopIndex;
    s32 preferredTopIndex;

    if (newSelection < 0) {
        newSelection = 0;
    }

    if (newSelection >= OPTIONS_BITMAP_TOTAL) {
        newSelection = OPTIONS_BITMAP_TOTAL - 1;
    }

    oldSelection = gOptionsMenu->bitmapSelected;
    oldTopIndex = gOptionsMenu->bitmapTopIndex;

    if (newSelection == oldSelection) {
        return;
    }

    gOptionsMenu->bitmapSelected = newSelection;

    maxTopIndex = OPTIONS_BITMAP_TOTAL - OPTIONS_BITMAP_VISIBLE_ROWS;
    if (maxTopIndex < 0) {
        maxTopIndex = 0;
    }

    preferredTopIndex = oldTopIndex;

    if (gOptionsMenu->bitmapSelected < preferredTopIndex) {
        preferredTopIndex = gOptionsMenu->bitmapSelected;
    } else if (gOptionsMenu->bitmapSelected >= (preferredTopIndex + OPTIONS_BITMAP_VISIBLE_ROWS)) {
        preferredTopIndex = gOptionsMenu->bitmapSelected - (OPTIONS_BITMAP_VISIBLE_ROWS - 1);
    }

    if (preferredTopIndex < 0) {
        preferredTopIndex = 0;
    }
    if (preferredTopIndex > maxTopIndex) {
        preferredTopIndex = maxTopIndex;
    }

    gOptionsMenu->bitmapTopIndex = preferredTopIndex;
    gOptionsMenu->bitmapCursorTargetY = OPTIONS_BITMAP_LINE_START_Y
            + ((gOptionsMenu->bitmapSelected - gOptionsMenu->bitmapTopIndex) * OPTIONS_BITMAP_LINE_SPACING_Y);

    if (gOptionsMenu->bitmapTopIndex != oldTopIndex) {
        gOptionsMenu->bitmapCursor = (gOptionsMenu->bitmapTopIndex - oldTopIndex) * OPTIONS_BITMAP_LINE_SPACING_Y;
        options_scene_bitmap_refresh_visible_lines();
    } else {
        s16 oldLine;
        s16 newLine;

        gOptionsMenu->bitmapCursor = 0;

        oldLine = (oldSelection - gOptionsMenu->bitmapTopIndex) + OPTIONS_BITMAP_LINE_CENTER_INDEX;
        if ((oldLine >= 0)
            && (oldLine < OPTIONS_BITMAP_LINE_SPRITE_COUNT)
            && (gOptionsMenu->bitmapLineSprites[oldLine] >= 0)) {
            sprite_set_base_palette(gSpriteHandler, gOptionsMenu->bitmapLineSprites[oldLine], 6);
        }

        newLine = (gOptionsMenu->bitmapSelected - gOptionsMenu->bitmapTopIndex) + OPTIONS_BITMAP_LINE_CENTER_INDEX;
        if ((newLine >= 0)
            && (newLine < OPTIONS_BITMAP_LINE_SPRITE_COUNT)
            && (gOptionsMenu->bitmapLineSprites[newLine] >= 0)) {
            sprite_set_base_palette(gSpriteHandler, gOptionsMenu->bitmapLineSprites[newLine], 7);
        }
    }

    options_scene_bitmap_set_description(gOptionsMenu->bitmapSelected);
}

static void options_scene_bitmap_update_cursor(void) {
    /*if (gOptionsMenu->bitmapCursorY < gOptionsMenu->bitmapCursorTargetY) {
        gOptionsMenu->bitmapCursorY += OPTIONS_BITMAP_CURSOR_STEP;
        if (gOptionsMenu->bitmapCursorY > gOptionsMenu->bitmapCursorTargetY) {
            gOptionsMenu->bitmapCursorY = gOptionsMenu->bitmapCursorTargetY;
        }
    } else if (gOptionsMenu->bitmapCursorY > gOptionsMenu->bitmapCursorTargetY) {
        gOptionsMenu->bitmapCursorY -= OPTIONS_BITMAP_CURSOR_STEP;
        if (gOptionsMenu->bitmapCursorY < gOptionsMenu->bitmapCursorTargetY) {
            gOptionsMenu->bitmapCursorY = gOptionsMenu->bitmapCursorTargetY;
        }
    }*/
    gOptionsMenu->bitmapCursorY = gOptionsMenu->bitmapCursorTargetY;

    sprite_set_y(gSpriteHandler, gOptionsMenu->uiBarista, gOptionsMenu->bitmapCursorY);
}

static void options_scene_bitmap_update_text_scroll(void) {
    if (gOptionsMenu->bitmapCursor > 0) {
        gOptionsMenu->bitmapCursor -= OPTIONS_BITMAP_SCROLL_STEP;
        if (gOptionsMenu->bitmapCursor < 0) {
            gOptionsMenu->bitmapCursor = 0;
        }
    } else if (gOptionsMenu->bitmapCursor < 0) {
        gOptionsMenu->bitmapCursor += OPTIONS_BITMAP_SCROLL_STEP;
        if (gOptionsMenu->bitmapCursor > 0) {
            gOptionsMenu->bitmapCursor = 0;
        }
    }

    options_scene_bitmap_position_lines(gOptionsMenu->bitmapCursor);
}

static void options_scene_bitmap_set_description(u32 selected) {
    if (selected < OPTIONS_BITMAP_TOTAL) {
        text_printer_set_string(gOptionsMenu->descText, advance_options_desc_text[selected]);
    }
}

static void options_scene_set_page(u32 page) {
    u32 i;

    gOptionsMenu->activePage = page;

    sprite_set_visible(gSpriteHandler, gOptionsMenu->uiSoundMode, FALSE);
    sprite_set_visible(gSpriteHandler, gOptionsMenu->uiDataClear, FALSE);
    for (i = 0; i < OPTIONS_BITMAP_LINE_SPRITE_COUNT; i++) {
        if (gOptionsMenu->bitmapLineSprites[i] >= 0) {
            sprite_set_visible(gSpriteHandler, gOptionsMenu->bitmapLineSprites[i], FALSE);
        }
    }

    if (page == OPTIONS_PAGE_ADVANCE) {
        options_scene_bitmap_refresh_visible_lines();

        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiBarista, TRUE);
        sprite_set_x(gSpriteHandler, gOptionsMenu->uiBarista, OPTIONS_CURSOR_ADVANCE_X);
        sprite_set_y(gSpriteHandler, gOptionsMenu->uiBarista, gOptionsMenu->bitmapCursorY);

        options_scene_bitmap_position_lines(gOptionsMenu->bitmapCursor);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiBarista, TRUE);
        options_scene_bitmap_set_description(gOptionsMenu->bitmapSelected);

        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiRShoulder, TRUE);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiLShoulder, TRUE);
    } else {
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiBarista, TRUE);
        sprite_set_x(gSpriteHandler, gOptionsMenu->uiBarista, OPTIONS_CURSOR_CLASSIC_X);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiSoundMode, TRUE);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiDataClear, TRUE);
        options_scene_refresh_classic_visuals();
        text_printer_set_string(gOptionsMenu->descText, options_desc_text[gOptionsMenu->cursorPos]);

        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiRShoulder, TRUE);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiLShoulder, TRUE);
    }
}

static void options_scene_shoulder_hold_cb(struct SpriteHandler *handler, s16 sprite, u32 arg) {
    sprite_set_callback(handler, sprite, NULL, 0);
    sprite_set_anim_cel(handler, sprite, arg);
    sprite_set_paused(handler, sprite, TRUE);
}

static void options_scene_rshoulder_switch_cb(struct SpriteHandler *handler, s16 sprite, u32 arg) {
    sprite_set_callback(handler, sprite, NULL, 0);
    sprite_set_anim_cel(handler, sprite, 0);
    sprite_set_paused(handler, sprite, TRUE);
    options_scene_set_page(OPTIONS_PAGE_ADVANCE);
    gOptionsMenu->inputsEnabled = TRUE;
}

static void options_scene_lshoulder_switch_cb(struct SpriteHandler *handler, s16 sprite, u32 arg) {
    sprite_set_callback(handler, sprite, NULL, 0);
    sprite_set_anim_cel(handler, sprite, 0);
    sprite_set_paused(handler, sprite, TRUE);
    options_scene_set_page(OPTIONS_PAGE_CLASSIC);
    gOptionsMenu->inputsEnabled = TRUE;
}


// Scene Start
void options_scene_start(void *sVar, s32 dArg) {
    struct TextPrinter *printer;
    u32 i;

    func_08007324(FALSE);
    func_080073f0();
    options_scene_init_gfx1();

    sprite_create(gSpriteHandler, anim_options_banner, 0, 120, 16, 0x4800, 1, 0, 0);
    gOptionsMenu->uiBarista = sprite_create(gSpriteHandler, anim_options_cursor_barista, 0,
        OPTIONS_CURSOR_CLASSIC_X, 64, 0x4800, 1, 0, 0);
    gOptionsMenu->soundMode = D_030046a8->data.unk294[8];
    gOptionsMenu->uiSoundMode = sprite_create(gSpriteHandler, anim_options_select_stereo, 0x7F,
        OPTIONS_CURSOR_CLASSIC_X, OPTIONS_CURSOR_SOUND_MODE_Y, 0x4800, 1, 0x7F, 0);
    gOptionsMenu->uiDataClear = sprite_create(gSpriteHandler, anim_options_select_data_clear, 0x7F,
        OPTIONS_CURSOR_CLASSIC_X, OPTIONS_CURSOR_DATA_CLEAR_Y, 0x4800, 1, 0x7F, 0);
    sprite_create(gSpriteHandler, anim_options_desc_box, 0, 120, 116, 0x4F00, 0, 0, 0);
    sprite_set_anim(gSpriteHandler, gOptionsMenu->uiSoundMode, options_sound_mode_anim[gOptionsMenu->soundMode][OPTIONS_BUTTON_ON], 0x7F, 1, 0x7F, 0);
    sprite_set_anim(gSpriteHandler, gOptionsMenu->uiDataClear, anim_options_off_data_clear, 0, 0, 0, 0);
    sprite_set_x_y(gSpriteHandler, gOptionsMenu->uiBarista, OPTIONS_CURSOR_CLASSIC_X, OPTIONS_CURSOR_SOUND_MODE_Y);
    gOptionsMenu->cursorPos = OPTIONS_BUTTON_SOUND_MODE;

    gOptionsMenu->uiRShoulder = sprite_create(gSpriteHandler, anim_options_rshoulder, 4, 120, 80, 0x5000, 0, 0, SPRITE_PLAYBACK_NORMAL_LOOP);
    gOptionsMenu->uiLShoulder = sprite_create(gSpriteHandler, anim_options_lshoulder, 4, 120, 80, 0x5000, 0, 0, SPRITE_PLAYBACK_NORMAL_LOOP);

    sprite_set_anim_cel(gSpriteHandler, gOptionsMenu->uiRShoulder, 0);
    sprite_set_paused(gSpriteHandler, gOptionsMenu->uiRShoulder, TRUE);
    sprite_set_anim_cel(gSpriteHandler, gOptionsMenu->uiLShoulder, 0);
    sprite_set_paused(gSpriteHandler, gOptionsMenu->uiLShoulder, TRUE);

    printer = text_printer_create_new(get_current_mem_id(), 3, 208, 32);
    text_printer_set_x_y(printer, 16, 117);
    text_printer_set_layer(printer, 0x4800);
    text_printer_set_alignment(printer, TEXT_ALIGNMENT_CENTER);
    text_printer_center_by_content(printer, TRUE);
    text_printer_set_palette(printer, 12);
    text_printer_set_colors(printer, 0);
    text_printer_set_line_spacing(printer, 15);
    text_printer_set_string(printer, options_desc_text[OPTIONS_BUTTON_SOUND_MODE]);
    gOptionsMenu->descText = printer;

    gOptionsMenu->uiWarningPane = sprite_create(gSpriteHandler, anim_options_warning_box, 0, 120, 74, 0x440A, 1, 0, 0x8000);
    gOptionsMenu->uiWarningCursor = sprite_create(gSpriteHandler, anim_options_cursor_default, 0, 64, 64, 0x4400, 1, 0, 0x8000);
    sprite_set_x(gSpriteHandler, gOptionsMenu->uiWarningCursor, OPTIONS_WARNING_CURSOR_X);

    printer = text_printer_create_new(get_current_mem_id(), 3, 80, 26);
    text_printer_set_x_y(printer, 80, 75);
    text_printer_set_layer(printer, 0x4400);
    text_printer_set_alignment(printer, TEXT_ALIGNMENT_CENTER);
    text_printer_center_by_content(printer, FALSE);
    text_printer_set_palette(printer, 12);
    text_printer_set_colors(printer, 0);
    text_printer_set_line_spacing(printer, 15);
    text_printer_show_text(printer, FALSE);
    text_printer_set_string(printer, options_data_clear_confirm_text);
    gOptionsMenu->warningText = printer;

    gOptionsMenu->bitmapFont = scene_create_obj_font_printer(OPTIONS_BITMAP_FONT_BASE_TILE, OPTIONS_BITMAP_FONT_TILE_ROWS);
    gOptionsMenu->bitmapCursor = 0;
    gOptionsMenu->bitmapSelected = 0;
    gOptionsMenu->bitmapTopIndex = 0;
    gOptionsMenu->bitmapCursorY = OPTIONS_BITMAP_LINE_START_Y;
    gOptionsMenu->bitmapCursorTargetY = OPTIONS_BITMAP_LINE_START_Y;

    for (i = 0; i < OPTIONS_BITMAP_LINE_SPRITE_COUNT; i++) {
        gOptionsMenu->bitmapLineSprites[i] = -1;
    }

    options_scene_bitmap_refresh_visible_lines();

    gOptionsMenu->inputsEnabled = FALSE;
    gOptionsMenu->state = OPTIONS_SCENE_STATE_MAIN;
    gOptionsMenu->clearDataOnExit = FALSE;
    gOptionsMenu->canceledDataClear = FALSE;
    options_scene_set_page(OPTIONS_PAGE_CLASSIC);

    sprite_set_paused(gSpriteHandler, gOptionsMenu->uiRShoulder, FALSE);
    sprite_set_callback(gSpriteHandler, gOptionsMenu->uiRShoulder, options_scene_shoulder_hold_cb, 4);
    sprite_set_anim(gSpriteHandler, gOptionsMenu->uiRShoulder, anim_options_rshoulder,
            0, 1, 4, SPRITE_PLAYBACK_NORMAL_CALLBACK);
}


// Scene Update (Paused)
void options_scene_paused(void *sVar, s32 dArg) {
}


// Set Warning Cursor Position
void options_scene_move_warning_cursor(u32 index) {
    sprite_set_y(gSpriteHandler, gOptionsMenu->uiWarningCursor, 75 + (15 * (index + 1)));
}


// Update (State 1)
static void options_scene_update_main_classic(void) {
    u32 event = OPTIONS_EV_NONE;

    if (!options_scene_inputs_enabled()) {
        return;
    }

    if (D_03004afc & RIGHT_SHOULDER_BUTTON) {
        gOptionsMenu->inputsEnabled = FALSE;

        sprite_set_paused(gSpriteHandler, gOptionsMenu->uiLShoulder, FALSE);
        sprite_set_callback(gSpriteHandler, gOptionsMenu->uiLShoulder, options_scene_shoulder_hold_cb, 4);
        sprite_set_anim(gSpriteHandler, gOptionsMenu->uiLShoulder, anim_options_lshoulder,
            0, 1, 4, SPRITE_PLAYBACK_NORMAL_CALLBACK);

        sprite_set_paused(gSpriteHandler, gOptionsMenu->uiRShoulder, FALSE);
        sprite_set_callback(gSpriteHandler, gOptionsMenu->uiRShoulder, options_scene_rshoulder_switch_cb, 0);
        sprite_set_anim(gSpriteHandler, gOptionsMenu->uiRShoulder, anim_options_rshoulder,
            4, -1, 0, SPRITE_PLAYBACK_NORMAL_CALLBACK);
        play_sound(&s_menu_cursor2_seqData);
        rumble_play_menu_move();
        return;
    }

    if (D_03004afc & DPAD_UP) {
        if (gOptionsMenu->cursorPos >= OPTIONS_BUTTON_DATA_CLEAR) {
            event = OPTIONS_EV_CURSOR_UP;
        } else {
            rumble_play_menu_limit();
        }
    }

    if (D_03004afc & DPAD_DOWN) {
        if (gOptionsMenu->cursorPos <= OPTIONS_BUTTON_SOUND_MODE) {
            event = OPTIONS_EV_CURSOR_DOWN;
        } else {
            rumble_play_menu_limit();
        }
    }

    if (D_03004afc & A_BUTTON) {
        event = OPTIONS_EV_CONFIRM;
    }

    if (D_03004afc & B_BUTTON) {
        event = OPTIONS_EV_CANCEL;
    }

    switch (event) {
        case OPTIONS_EV_CURSOR_UP:
            gOptionsMenu->cursorPos = OPTIONS_BUTTON_SOUND_MODE;
            options_scene_refresh_classic_visuals();
            text_printer_set_string(gOptionsMenu->descText, options_desc_text[OPTIONS_BUTTON_SOUND_MODE]);
            play_sound(&s_menu_cursor2_seqData);
            rumble_play_menu_move();
            break;

        case OPTIONS_EV_CURSOR_DOWN:
            gOptionsMenu->cursorPos = OPTIONS_BUTTON_DATA_CLEAR;
            options_scene_refresh_classic_visuals();
            text_printer_set_string(gOptionsMenu->descText, options_desc_text[OPTIONS_BUTTON_DATA_CLEAR]);
            play_sound(&s_menu_cursor2_seqData);
            rumble_play_menu_move();
            break;

        case OPTIONS_EV_CONFIRM:
            if (gOptionsMenu->cursorPos == OPTIONS_BUTTON_SOUND_MODE) {
                gOptionsMenu->soundMode ^= 1;
                options_scene_refresh_classic_visuals();
                D_030046a8->data.unk294[8] = gOptionsMenu->soundMode;
                set_sound_mode(gOptionsMenu->soundMode);
                write_game_save_data();
            } else {
                gOptionsMenu->warningCursorPos = OPTIONS_WARNING_NO;
                options_scene_move_warning_cursor(gOptionsMenu->warningCursorPos);
                sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningPane, TRUE);
                sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningCursor, TRUE);
                text_printer_show_text(gOptionsMenu->warningText, TRUE);
                gOptionsMenu->state = OPTIONS_SCENE_STATE_WARNING;
            }
            play_sound(&s_menu_kettei2_seqData);
            rumble_play_menu_confirm();
            break;

        case OPTIONS_EV_CANCEL:
            gOptionsMenu->canceledDataClear = TRUE;
            set_scene_trans_var(&scene_main_menu, TRUE);
            set_pause_beatscript_scene(FALSE);
            gOptionsMenu->inputsEnabled = FALSE;
            play_sound(&s_menu_cancel3_seqData);
            rumble_play_menu_cancel();
            break;
    }
}


// Update Main (Bitmap Page)
static void options_scene_update_main_bitmap(void) {
    u32 event = OPTIONS_BITMAP_EV_NONE;
    s32 selectedItem;

    options_scene_bitmap_update_cursor();
    options_scene_bitmap_update_text_scroll();

    if (!options_scene_inputs_enabled()) {
        return;
    }

    if (gOptionsMenu->bitmapCursor != 0) {
        return;
    }

    if (D_03004afc & LEFT_SHOULDER_BUTTON) {
        event = OPTIONS_BITMAP_EV_PAGE_PREV;
    } else {
        if (D_030053b8 & DPAD_UP) {
            event = OPTIONS_BITMAP_EV_SCROLL_UP;
        }

        if (D_030053b8 & DPAD_DOWN) {
            event = OPTIONS_BITMAP_EV_SCROLL_DOWN;
        }

        if (D_03004afc & A_BUTTON) {
            event = OPTIONS_BITMAP_EV_CONFIRM;
        }

        if (D_03004afc & B_BUTTON) {
            event = OPTIONS_BITMAP_EV_CANCEL;
        }
    }

    switch (event) {
        case OPTIONS_BITMAP_EV_PAGE_PREV:
            gOptionsMenu->inputsEnabled = FALSE;

            sprite_set_paused(gSpriteHandler, gOptionsMenu->uiRShoulder, FALSE);
            sprite_set_callback(gSpriteHandler, gOptionsMenu->uiRShoulder, options_scene_shoulder_hold_cb, 4);
            sprite_set_anim(gSpriteHandler, gOptionsMenu->uiRShoulder, anim_options_rshoulder,
                0, 1, 4, SPRITE_PLAYBACK_NORMAL_CALLBACK);

            sprite_set_paused(gSpriteHandler, gOptionsMenu->uiLShoulder, FALSE);
            sprite_set_callback(gSpriteHandler, gOptionsMenu->uiLShoulder, options_scene_lshoulder_switch_cb, 0);
            sprite_set_anim(gSpriteHandler, gOptionsMenu->uiLShoulder, anim_options_lshoulder,
                4, -1, 0, SPRITE_PLAYBACK_NORMAL_CALLBACK);
            play_sound(&s_menu_cursor2_seqData);
            rumble_play_menu_move();
            break;

        case OPTIONS_BITMAP_EV_SCROLL_UP:
            if (gOptionsMenu->bitmapSelected <= 0) {
                rumble_play_menu_limit();
            } else {
                options_scene_bitmap_set_selection(gOptionsMenu->bitmapSelected - 1);
                play_sound(&s_menu_cursor2_seqData);
                rumble_play_menu_move();
            }
            break;

        case OPTIONS_BITMAP_EV_SCROLL_DOWN:
            if (gOptionsMenu->bitmapSelected >= (OPTIONS_BITMAP_TOTAL - 1)) {
                rumble_play_menu_limit();
            } else {
                options_scene_bitmap_set_selection(gOptionsMenu->bitmapSelected + 1);
                play_sound(&s_menu_cursor2_seqData);
                rumble_play_menu_move();
            }
            break;

        case OPTIONS_BITMAP_EV_CONFIRM:
            selectedItem = gOptionsMenu->bitmapSelected;

            switch (selectedItem) {
                case OPTIONS_BITMAP_NON_JP_SFX:
                    TOGGLE_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_SFX);
                    write_game_save_data();
                    options_scene_bitmap_refresh_line(OPTIONS_BITMAP_NON_JP_SFX);
                    if (CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_SFX)) {
                        play_sound(&s_menu_kettei2_seqData);
                        rumble_play_menu_confirm();
                    } else {
                        play_sound(&s_menu_cancel3_seqData);
                        rumble_play_menu_cancel();
                    }
                    break;

                case OPTIONS_BITMAP_NON_JP_MUSIC:
                    TOGGLE_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_MUSIC);
                    write_game_save_data();
                    options_scene_bitmap_refresh_line(OPTIONS_BITMAP_NON_JP_MUSIC);
                    if (CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_MUSIC)) {
                        play_sound(&s_menu_kettei2_seqData);
                        rumble_play_menu_confirm();
                    } else {
                        play_sound(&s_menu_cancel3_seqData);
                        rumble_play_menu_cancel();
                    }
                    break;

#ifdef RUMBLE
                case OPTIONS_BITMAP_RUMBLE:
                    TOGGLE_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_DISABLE_RUMBLE);
                    write_game_save_data();
                    options_scene_bitmap_refresh_line(OPTIONS_BITMAP_RUMBLE);
                    if (CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_DISABLE_RUMBLE)) {
                        play_sound(&s_menu_cancel3_seqData);
                        rumble_play_menu_cancel();
                    } else {
                        play_sound(&s_menu_kettei2_seqData);
                        rumble_play_long();
                    }
                    break;
#endif

                case OPTIONS_BITMAP_SKIP_DISCLAIMER:
                    if (D_03004afc & RIGHT_SHOULDER_BUTTON) {
                        play_sound(&s_mario_melo1_seqData);
                        haveSeenDisclaimer = FALSE;
                        write_game_save_data();
                        rumble_play_menu_bonus();
                        set_next_scene(&scene_title);
                        set_pause_beatscript_scene(FALSE);
                        gOptionsMenu->inputsEnabled = FALSE;
                        gOptionsMenu->state = OPTIONS_SCENE_STATE_EXIT;
                        
                    } else {
                        TOGGLE_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_SKIP_DISCLAIMER);
                        write_game_save_data();
                        options_scene_bitmap_refresh_line(OPTIONS_BITMAP_SKIP_DISCLAIMER);
                        play_sound(&s_menu_kettei2_seqData);
                        rumble_play_menu_confirm();
                    }
                    break;

                case OPTIONS_BITMAP_ALT_GAME_SELECT_MUSIC:
                    TOGGLE_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_USE_ALT_GAME_SELECT_MUSIC);
                    write_game_save_data();
                    options_scene_bitmap_refresh_line(OPTIONS_BITMAP_ALT_GAME_SELECT_MUSIC);
                    if (CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_USE_ALT_GAME_SELECT_MUSIC)) {
                        play_sound(&s_menu_kettei2_seqData);
                        rumble_play_menu_confirm();
                    } else {
                        play_sound(&s_menu_cancel3_seqData);
                        rumble_play_menu_cancel();
                    }
                    break;
            }
            break;

        case OPTIONS_BITMAP_EV_CANCEL:
            gOptionsMenu->canceledDataClear = TRUE;
            set_scene_trans_var(&scene_main_menu, TRUE);
            set_pause_beatscript_scene(FALSE);
            gOptionsMenu->inputsEnabled = FALSE;
            play_sound(&s_menu_cancel3_seqData);
            rumble_play_menu_cancel();
            break;
    }
}


// Update (State 1)
void options_scene_update_main(void) {
    if (gOptionsMenu->activePage == OPTIONS_PAGE_ADVANCE) {
        options_scene_update_main_bitmap();
    } else {
        options_scene_update_main_classic();
    }
}


// Update Warning
void options_scene_update_warning(void) {
    if (!options_scene_inputs_enabled()) {
        return;
    }

    if (D_03004afc & B_BUTTON) {
        play_sound(&s_menu_cancel2_seqData);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningPane, FALSE);
        sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningCursor, FALSE);
        text_printer_show_text(gOptionsMenu->warningText, FALSE);
        gOptionsMenu->state = OPTIONS_SCENE_STATE_MAIN;
        rumble_play_menu_cancel();
        return;
    }

    if (D_03004afc & A_BUTTON) {
        if (gOptionsMenu->warningCursorPos == OPTIONS_WARNING_YES) {
            set_next_scene(&scene_title);
            gOptionsMenu->clearDataOnExit = TRUE;
            set_pause_beatscript_scene(FALSE);
            gOptionsMenu->inputsEnabled = FALSE;
            gOptionsMenu->state = OPTIONS_SCENE_STATE_EXIT;
            play_sound(&s_menu_kettei2_seqData);
            rumble_play_menu_confirm();
            return;
        } else {
            sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningPane, FALSE);
            sprite_set_visible(gSpriteHandler, gOptionsMenu->uiWarningCursor, FALSE);
            text_printer_show_text(gOptionsMenu->warningText, FALSE);
            play_sound(&s_menu_cancel2_seqData);
            gOptionsMenu->state = OPTIONS_SCENE_STATE_MAIN;
            rumble_play_menu_cancel();
        }
    }

    if (D_03004afc & DPAD_UP) {
        if (gOptionsMenu->warningCursorPos != OPTIONS_WARNING_YES) {
            gOptionsMenu->warningCursorPos = OPTIONS_WARNING_YES;
            options_scene_move_warning_cursor(gOptionsMenu->warningCursorPos);
            sprite_set_anim_cel(gSpriteHandler, gOptionsMenu->uiWarningCursor, 0);
            play_sound(&s_menu_cursor1_seqData);
            rumble_play_menu_move();
        } else {
            rumble_play_menu_limit();
        }
    }

    if (D_03004afc & DPAD_DOWN) {
        if (gOptionsMenu->warningCursorPos == OPTIONS_WARNING_YES) {
            gOptionsMenu->warningCursorPos = OPTIONS_WARNING_NO;
            options_scene_move_warning_cursor(gOptionsMenu->warningCursorPos);
            sprite_set_anim_cel(gSpriteHandler, gOptionsMenu->uiWarningCursor, 0);
            play_sound(&s_menu_cursor1_seqData);
            rumble_play_menu_move();
        } else {
            rumble_play_menu_limit();
        }
    }
}


// Scene Update (Active)
void options_scene_update(void *sVar, s32 dArg) {
    switch (gOptionsMenu->state) {
        case OPTIONS_SCENE_STATE_EXIT:
            break;
        case OPTIONS_SCENE_STATE_MAIN:
            options_scene_update_main();
            break;
        case OPTIONS_SCENE_STATE_WARNING:
            options_scene_update_warning();
            break;
    }

    text_printer_update(gOptionsMenu->descText);
    text_printer_update(gOptionsMenu->warningText);
}


// Check if Scene Can Receive Inputs
u32 options_scene_inputs_enabled(void) {
    if (gOptionsMenu->inputsEnabled) {
        return TRUE;
    }

    return FALSE;
}


// Scene Stop
void options_scene_stop(void *sVar, s32 dArg) {
    u32 i;

    for (i = 0; i < OPTIONS_BITMAP_LINE_SPRITE_COUNT; i++) {
        options_scene_bitmap_delete_line_sprite(i);
    }

    if (gOptionsMenu->bitmapFont != NULL) {
        delete_bmp_font_obj(gOptionsMenu->bitmapFont);
        gOptionsMenu->bitmapFont = NULL;
    }

    func_08008628();
    func_08004058();

    if (gOptionsMenu->clearDataOnExit) {
        clear_save_data();
#ifdef PLAYTEST
        set_playtest_save_data();
#endif
        flush_save_buffer_to_sram();
        set_sound_mode(D_030046a8->data.unk294[8]);
        init_scene_static_var();
    }
}
