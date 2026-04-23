#include "global.h"
#include "sequence_player.h"
#include "src/audio.h"
#include "graphics/sequence_player/sequence_player_graphics.h"

extern u32 song_header_table_size;

enum SequencePlayerAction {
    SP_ACTION_NONE,
    SP_ACTION_PLAY_OK,
    SP_ACTION_STOPPED,
    SP_ACTION_SONG_NULL,
    SP_ACTION_PLAYER_INVALID,
    SP_ACTION_PLAY_FAILED
};

enum {
    SP_TOTAL_OPTIONS = 5,
    SP_VISIBLE_OPTIONS = 4
};

#define DEFINE_SONG(song, player) #song,
static const char *sSequenceSymbolNames[] = {
    #include "audio/song_defines.inc.c"
};
#undef DEFINE_SONG

#define DEFINE_SONG(song, player) +1
enum {
    SEQUENCE_SYMBOL_COUNT = (0
        #include "audio/song_defines.inc.c"
    )
};
#undef DEFINE_SONG

static u32 wrap_index(u32 val, u32 deltaPositive, u32 max) {
    if (max == 0) {
        return 0;
    }

    return (val + deltaPositive) % max;
}

static s32 clamp_s32(s32 value, s32 min, s32 max) {
    if (value < min) {
        return min;
    }

    if (value > max) {
        return max;
    }

    return value;
}

static u32 sequence_player_get_song_count(void) {
    return song_header_table_size;
}

static const struct SongTable *sequence_player_get_song_entry(u32 songIndex) {
    if (songIndex >= sequence_player_get_song_count()) {
        return NULL;
    }

    return &song_header_table[songIndex];
}

static u32 sequence_player_song_is_valid(u32 songIndex) {
    const struct SongTable *entry = sequence_player_get_song_entry(songIndex);

    if ((entry == NULL) || (entry->song == NULL)) {
        return FALSE;
    }

    return TRUE;
}

static u32 sequence_player_find_valid_song(u32 startIndex, s32 direction, u32 *found) {
    u32 count = sequence_player_get_song_count();
    u32 step;
    u32 index;
    u32 i;

    if (found != NULL) {
        *found = FALSE;
    }

    if (count == 0) {
        return 0;
    }

    step = (direction < 0) ? (count - 1) : 1;
    index = startIndex % count;

    for (i = 0; i < count; i++) {
        if (sequence_player_song_is_valid(index)) {
            if (found != NULL) {
                *found = TRUE;
            }
            return index;
        }
        index = wrap_index(index, step, count);
    }

    return startIndex % count;
}

static const char *sequence_player_get_symbol_name(u32 songIndex) {
    const char *name;

    if (songIndex >= SEQUENCE_SYMBOL_COUNT) {
        return "<unknown>";
    }

    name = sSequenceSymbolNames[songIndex];
    if (name == NULL) {
        return "<unknown>";
    }

    if (name[0] == '&') {
        name++;
    }

    if (name[0] == '\0') {
        return "<unknown>";
    }

    return name;
}

static const char *sequence_player_get_song_title(const struct SongHeader *song) {
    if ((song == NULL) || (song->title == NULL) || (song->title[0] == '\0')) {
        return "<empty>";
    }

    return song->title;
}

static const char *sequence_player_get_status_text(void) {
    if (gSequencePlayer->activePlayer != NULL && soundplayer_is_playing(gSequencePlayer->activePlayer)) {
        return "Playing";
    }

    switch (gSequencePlayer->lastAction) {
        case SP_ACTION_PLAY_OK:       return "Play request sent";
        case SP_ACTION_STOPPED:       return "Stopped";
        case SP_ACTION_SONG_NULL:     return "Song entry is NULL";
        case SP_ACTION_PLAYER_INVALID:return "Player override is invalid";
        case SP_ACTION_PLAY_FAILED:   return "Play failed";
        default:                      return "Idle";
    }
}

static void sequence_player_format_option(char *buf, u32 bufSize, u32 optionIndex, u32 isSelected) {
    const char *marker = isSelected ? "[*]" : "[ ]";

    switch (optionIndex) {
        case 0:
            snprintf(buf, bufSize, "%s Override Player: %s", marker,
                    gSequencePlayer->overridePlayer ? "ON" : "OFF");
            break;

        case 1:
            snprintf(buf, bufSize, "%s Player ID: %u/%u", marker,
                    gSequencePlayer->selectedPlayer,
                    (sound_player_count > 0) ? (u32)(sound_player_count - 1) : 0);
            break;

        case 2:
            snprintf(buf, bufSize, "%s Volume: %u/256", marker,
                    gSequencePlayer->volume);
            break;

        case 3:
            snprintf(buf, bufSize, "%s Pitch: %+d semitones", marker,
                    gSequencePlayer->pitch);
            break;

        case 4:
            snprintf(buf, bufSize, "%s Stop Others: %s", marker,
                    gSequencePlayer->stopOthers ? "ON" : "OFF");
            break;

        default:
            snprintf(buf, bufSize, "%s <invalid option>", marker);
            break;
    }
}

static void sequence_player_stop_active(void) {
    if (gSequencePlayer->activePlayer != NULL) {
        stop_soundplayer(gSequencePlayer->activePlayer);
        gSequencePlayer->activePlayer = NULL;
    }

    gSequencePlayer->lastAction = SP_ACTION_STOPPED;
}

static void sequence_player_play_current(void) {
    const struct SongTable *entry;
    struct SongHeader *song;
    struct SoundPlayer *player;

    entry = sequence_player_get_song_entry(gSequencePlayer->currentSong);
    if ((entry == NULL) || (entry->song == NULL)) {
        gSequencePlayer->activePlayer = NULL;
        gSequencePlayer->lastAction = SP_ACTION_SONG_NULL;
        return;
    }

    song = entry->song;
    player = NULL;

    if (gSequencePlayer->stopOthers) {
        stop_all_soundplayers();
    } else {
        sequence_player_stop_active();
    }

    if (gSequencePlayer->overridePlayer) {
        if ((sound_player_count == 0) || (gSequencePlayer->selectedPlayer >= sound_player_count)) {
            gSequencePlayer->activePlayer = NULL;
            gSequencePlayer->lastAction = SP_ACTION_PLAYER_INVALID;
            return;
        }

        player = play_sound_in_player(gSequencePlayer->selectedPlayer, song);
    } else {
        player = play_sound(song);

        if ((player == NULL) && (entry->player < sound_player_count)) {
            player = play_sound_in_player(entry->player, song);
        }
    }

    if (player == NULL) {
        gSequencePlayer->activePlayer = NULL;
        gSequencePlayer->lastAction = SP_ACTION_PLAY_FAILED;
        return;
    }

    set_soundplayer_volume(player, (u8_8)gSequencePlayer->volume);
    set_soundplayer_pitch(player, (s8_8)(gSequencePlayer->pitch << 8));
    gSequencePlayer->activePlayer = player;
    gSequencePlayer->lastAction = SP_ACTION_PLAY_OK;
}

static void sequence_player_adjust_option(s32 delta) {
    switch (gSequencePlayer->optionIndex) {
        case 0:
            gSequencePlayer->overridePlayer ^= TRUE;
            break;

        case 1:
            if (sound_player_count > 0) {
                if (delta > 0) {
                    gSequencePlayer->selectedPlayer = wrap_index(gSequencePlayer->selectedPlayer, 1, sound_player_count);
                } else {
                    gSequencePlayer->selectedPlayer = wrap_index(gSequencePlayer->selectedPlayer, sound_player_count - 1, sound_player_count);
                }
            }
            break;

        case 2:
            gSequencePlayer->volume = clamp_s32((s32)gSequencePlayer->volume + (delta * 8), 0, 256);
            break;

        case 3:
            gSequencePlayer->pitch = clamp_s32(gSequencePlayer->pitch + delta, -24, 24);
            break;

        case 4:
            gSequencePlayer->stopOthers ^= TRUE;
            break;
    }
}

void sequence_player_scene_init_gfx3(void) {
    s32 task = start_new_texture_loader(get_current_mem_id(), sequence_player_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
    func_0800c604(0);
}

void sequence_player_scene_init_gfx2(void) {
    s32 task = func_08002ee0(get_current_mem_id(), sequence_player_gfx_table, 0x3000);
    run_func_after_task(task, sequence_player_scene_init_gfx3, 0);
    func_0800c604(0);
}

void sequence_player_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), sequence_player_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}

void sequence_player_scene_start(void *sVar, s32 dArg) {
    const struct SongTable *entry;
    u32 hasValidSong;
    u32 i;

    func_08007324(TRUE);
    func_080073f0();

    gSequencePlayer->bgFont = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    gSequencePlayer->objFont = scene_create_obj_font_printer(0x300, 4);
    gSequencePlayer->activePlayer = NULL;

    gSequencePlayer->inputsEnabled = FALSE;
    gSequencePlayer->currentSong = 0;
    gSequencePlayer->optionIndex = 0;
    gSequencePlayer->overridePlayer = FALSE;
    gSequencePlayer->selectedPlayer = 0;
    gSequencePlayer->pitch = 0;
    gSequencePlayer->volume = 256;
    gSequencePlayer->stopOthers = TRUE;
    gSequencePlayer->lastAction = SP_ACTION_NONE;

    for (i = 0; i < SP_LINE_COUNT; i++) {
        gSequencePlayer->textLineSprites[i] = -1;
    }

    gSequencePlayer->currentSong = sequence_player_find_valid_song(0, 1, &hasValidSong);
    if (!hasValidSong) {
        gSequencePlayer->currentSong = 0;
    }

    entry = sequence_player_get_song_entry(gSequencePlayer->currentSong);
    if ((entry != NULL) && (entry->player < sound_player_count)) {
        gSequencePlayer->selectedPlayer = entry->player;
    }

    sequence_player_scene_init_gfx1();

    sequence_player_clear_bg_text();

    set_next_scene(&scene_debug_menu);
    sequence_player_render_page();
}

void sequence_player_scene_paused(void *sVar, s32 dArg) {
}

void sequence_player_scene_update(void *sVar, s32 dArg) {
    u32 oldSong = gSequencePlayer->currentSong;
    u32 oldOption = gSequencePlayer->optionIndex;
    u32 oldOverride = gSequencePlayer->overridePlayer;
    u32 oldPlayer = gSequencePlayer->selectedPlayer;
    s32 oldPitch = gSequencePlayer->pitch;
    u32 oldVolume = gSequencePlayer->volume;
    u32 oldStopOthers = gSequencePlayer->stopOthers;
    u32 oldAction = gSequencePlayer->lastAction;
    u32 songCount = sequence_player_get_song_count();
    u32 hasValidSong;
    u32 targetSong;

    if (!sequence_player_inputs_enabled()) {
        return;
    }

    if ((songCount > 0) && (D_030053b8 & LEFT_SHOULDER_BUTTON)) {
        targetSong = wrap_index(gSequencePlayer->currentSong, songCount - 1, songCount);
        targetSong = sequence_player_find_valid_song(targetSong, -1, &hasValidSong);
        if (hasValidSong) {
            gSequencePlayer->currentSong = targetSong;
        }
    }

    if ((songCount > 0) && (D_030053b8 & RIGHT_SHOULDER_BUTTON)) {
        targetSong = wrap_index(gSequencePlayer->currentSong, 1, songCount);
        targetSong = sequence_player_find_valid_song(targetSong, 1, &hasValidSong);
        if (hasValidSong) {
            gSequencePlayer->currentSong = targetSong;
        }
    }

    if (D_03004afc & DPAD_UP) {
        gSequencePlayer->optionIndex = wrap_index(gSequencePlayer->optionIndex, 4, 5);
    }

    if (D_03004afc & DPAD_DOWN) {
        gSequencePlayer->optionIndex = wrap_index(gSequencePlayer->optionIndex, 1, 5);
    }

    if (D_03004afc & DPAD_LEFT) {
        sequence_player_adjust_option(-1);
    }

    if (D_03004afc & DPAD_RIGHT) {
        sequence_player_adjust_option(1);
    }

    if (D_03004afc & START_BUTTON) {
        gSequencePlayer->stopOthers ^= TRUE;
    }

    if (D_03004afc & A_BUTTON) {
        sequence_player_play_current();
    }

    if (D_03004afc & B_BUTTON) {
        sequence_player_stop_active();
    }

    if (D_03004afc & SELECT_BUTTON) {
        sequence_player_stop_active();
        gSequencePlayer->inputsEnabled = FALSE;
        set_pause_beatscript_scene(FALSE);
    }

    if ((gSequencePlayer->currentSong != oldSong)
     || (gSequencePlayer->optionIndex != oldOption)
     || (gSequencePlayer->overridePlayer != oldOverride)
     || (gSequencePlayer->selectedPlayer != oldPlayer)
     || (gSequencePlayer->pitch != oldPitch)
     || (gSequencePlayer->volume != oldVolume)
     || (gSequencePlayer->stopOthers != oldStopOthers)
     || (gSequencePlayer->lastAction != oldAction)) {
        sequence_player_render_page();
    }
}

void sequence_player_draw_line(u32 line, u32 palette, const char *string, s16 x, s16 y) {
    struct Animation *anim;
    void *tileset;
    u32 tileY;
    s16 sprite;

    sequence_player_clear_line(line);

    tileY = (line * 2) + 12;
    tileset = OBJ_TILESET_BASE(tileY * 0x400);
    dma3_fill(0, tileset, 0x800, 0x20, 0x200);

    anim = text_printer_get_unformatted_line_anim(get_current_mem_id(), 0, tileY,
            TEXT_PRINTER_FONT_SMALL, string, TEXT_ANCHOR_BOTTOM_LEFT, 0, SCREEN_WIDTH - x);
    sprite = sprite_create(gSpriteHandler, anim, 0, x, y, 0, 0, 0, 0);
    sprite_set_base_palette(gSpriteHandler, sprite, palette + 8);

    gSequencePlayer->textLineSprites[line] = sprite;
}

void sequence_player_clear_line(u32 line) {
    s16 sprite = gSequencePlayer->textLineSprites[line];

    if (sprite >= 0) {
        struct Animation *anim = (void *)sprite_get_data(gSpriteHandler, sprite, 7);
        sprite_delete(gSpriteHandler, sprite);
        text_printer_delete_anim(anim);
        gSequencePlayer->textLineSprites[line] = -1;
    }
}

void sequence_player_draw_bg_text(const char *text, u16 tileX, u16 tileY, u32 palette) {
    u16 *bgMap = (u16 *)BG_MAP_BASE(0xE800);
    u16 *dest = bgMap + tileX + tileY * 32;

    bmp_font_bg_print_text(gSequencePlayer->bgFont, dest, 32, text, palette + 8);
}

void sequence_player_clear_bg_text(void) {
    dma3_fill(0, (u16 *)BG_MAP_BASE(0xE800), 0x800, 0x20, 0x200);
}

void sequence_player_render_page(void) {
    const struct SongTable *entry;
    struct SongHeader *song;
    const char *symbol;
    const char *title;
    const char *status;
    char buf[128];
    u32 songCount;
    u32 hasValidSong;
    u32 optionTop;
    u32 optionEnd;
    u32 visible;
    u32 i;

    song = NULL;
    songCount = sequence_player_get_song_count();

    if (songCount > 0 && gSequencePlayer->currentSong >= songCount) {
        gSequencePlayer->currentSong = songCount - 1;
    }

    if ((songCount > 0) && !sequence_player_song_is_valid(gSequencePlayer->currentSong)) {
        gSequencePlayer->currentSong = sequence_player_find_valid_song(gSequencePlayer->currentSong, 1, &hasValidSong);
    }

    entry = sequence_player_get_song_entry(gSequencePlayer->currentSong);
    if (entry != NULL) {
        song = entry->song;
    }

    symbol = sequence_player_get_symbol_name(gSequencePlayer->currentSong);
    title = sequence_player_get_song_title(song);
    status = sequence_player_get_status_text();

    if (songCount == 0) {
        snprintf(buf, sizeof(buf), "No valid songs.");
    } else {
        snprintf(buf, sizeof(buf), "Song [%03u/%03u]", gSequencePlayer->currentSong, songCount - 1);
    }
    sequence_player_draw_line(SP_LINE_HEADER, 0, buf, 8, 10);

    snprintf(buf, sizeof(buf), "Symbol: %.34s", symbol);
    sequence_player_draw_line(SP_LINE_SYMBOL, 0, buf, 8, 24);

    snprintf(buf, sizeof(buf), "Seq Name: %.30s", title);
    sequence_player_draw_line(SP_LINE_TITLE, 0, buf, 8, 38);

    if ((entry != NULL) && (song != NULL)) {
        snprintf(buf, sizeof(buf), "Default Player:%u  Bank:%u  Vol:%u", entry->player, song->soundBank, song->volume);
    } else {
        snprintf(buf, sizeof(buf), "Selected entry is NULL; cannot play.");
    }
    sequence_player_draw_line(SP_LINE_INFO, 0, buf, 8, 52);

    optionTop = (gSequencePlayer->optionIndex > 1) ? (gSequencePlayer->optionIndex - 1) : 0;
    if (optionTop + SP_VISIBLE_OPTIONS > SP_TOTAL_OPTIONS) {
        optionTop = SP_TOTAL_OPTIONS - SP_VISIBLE_OPTIONS;
    }
    optionEnd = optionTop + SP_VISIBLE_OPTIONS;
    visible = optionEnd - optionTop;

    for (i = 0; i < visible; i++) {
        u32 optionIndex = optionTop + i;
        sequence_player_format_option(buf, sizeof(buf), optionIndex, optionIndex == gSequencePlayer->optionIndex);
        sequence_player_draw_line(SP_LINE_OPTION_0 + i, 0, buf, 8, 70 + (i * 12));
    }

    for (; i < SP_VISIBLE_OPTIONS; i++) {
        sequence_player_clear_line(SP_LINE_OPTION_0 + i);
    }

    snprintf(buf, sizeof(buf), "Options %u-%u/%u -- ⑯ Up/Down: Scroll", optionTop + 1, optionEnd, SP_TOTAL_OPTIONS);
    sequence_player_draw_line(SP_LINE_OPTION_4, 0, buf, 8, 120);

    sequence_player_draw_line(SP_LINE_HINT, 0, "⑫/⑬: Song -- ⑯ Left/Right: Edit -- ⑭: Play", 8, 134);

    snprintf(buf, sizeof(buf), "Status: %.32s", status);
    sequence_player_draw_line(SP_LINE_STATUS, 0, buf, 8, 148);
}

u32 sequence_player_inputs_enabled(void) {
    return gSequencePlayer->inputsEnabled ? TRUE : FALSE;
}

void sequence_player_scene_stop(void *sVar, s32 dArg) {
    sequence_player_stop_active();
    func_08008628();
    func_08004058();
}