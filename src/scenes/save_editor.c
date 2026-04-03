#include "global.h"
#include "save_editor.h"
#include "src/scenes/game_select.h"
#include "graphics/save_editor/save_editor_graphics.h"
#include "reading.h"
#include "studio.h"

static const struct SaveEditorFlag sAdvanceFlags[] = {
    { "Save Converted",          0 },
    { "Use. Alt GS Music",       1 },
    { "Seen Disclaimer",     2 },
    END_OF_FLAG
};

static const struct SaveEditorField sStudioSongFields[] = {
    { "songID",   SE_KIND_U8 },
    { "replayID", SE_KIND_S8 },
    { "kit",      SE_KIND_U8 },
    { "unk",      SE_KIND_U8 }
};

struct SaveEditorMember gSaveEditorMembers[SE_MBR_COUNT] = {
    /* SE_MBR_GAME_SELECT_CURSOR_X */
    { "Game Select Cursor X",                SE_KIND_S8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_GAME_SELECT_CURSOR_Y */
    { "Game Select Cursor Y",                SE_KIND_S8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_RECENT_LEVEL_X */
    { "Recent Level X",                      SE_KIND_S8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_RECENT_LEVEL_Y */
    { "Recent Level Y",                      SE_KIND_S8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_RECENT_LEVEL_STATE */
    { "Recent Level State",                  SE_KIND_LEVEL_STATE, 0,  -1, 5, NULL,          0, NULL,               0 },
    /* SE_MBR_RECENT_LEVEL_CLEARED_BY_BARISTA */
    { "Recent Level Cleared By Barista",     SE_KIND_BOOL,        0,   0,  1, NULL,          0, NULL,               0 },
    /* SE_MBR_LEVEL_STATES */
    { "Level States",                        SE_KIND_LEVEL_STATE, TOTAL_LEVELS, -1, 5, NULL,        0, NULL,        0 },
    /* SE_MBR_RECENT_LEVEL_SCORE */
    { "Recent Level Score",                  SE_KIND_S16,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_LEVEL_SCORES */
    { "Level Scores",                        SE_KIND_S16, TOTAL_LEVELS, -1, -1, NULL,        0, NULL,               0 },
    /* SE_MBR_CURRENT_FLOW */
    { "Current Flow",                        SE_KIND_U16,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_B0 */
    { "unkB0",                               SE_KIND_U8,    0,  -1, -1, NULL,   0, NULL,               0 },
    /* SE_MBR_ADVANCE_FLAGS */
    { "Advance Flags",                       SE_KIND_BITFLAGS,    0,  -1, -1, sAdvanceFlags, 3, NULL,               0 },
    /* SE_MBR_TOTAL_SONGS */
    { "Total Songs",                         SE_KIND_U8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_B3 */
    { "unkB3",                               SE_KIND_U8,    0,  -1, -1, NULL,   8, NULL,               0 },
    /* SE_MBR_STUDIO_SONGS */
    { "Studio Songs",                        SE_KIND_STRUCT_FIELD, 55, -1, -1, NULL,          0, sStudioSongFields,  4 },
    /* SE_MBR_LEVEL_TOTAL_PLAYS */
    { "Level Total Plays",                   SE_KIND_U8,  TOTAL_LEVELS, -1, -1, NULL,        0, NULL,               0 },
    /* SE_MBR_LEVEL_FIRST_OK */
    { "Level First OK",                      SE_KIND_U8,  TOTAL_LEVELS, -1, -1, NULL,        0, NULL,               0 },
    /* SE_MBR_LEVEL_FIRST_SUPERB */
    { "Level First Superb",                  SE_KIND_U8,  TOTAL_LEVELS, -1, -1, NULL,        0, NULL,               0 },
    /* SE_MBR_TOTAL_PERFECTS */
    { "Total Perfects",                      SE_KIND_U8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_CAMPAIGNS_CLEARED */
    { "Campaigns Cleared",                   SE_KIND_U8,  TOTAL_PERFECT_CAMPAIGNS, -1, -1, NULL, 0, NULL,           0 },
    /* SE_MBR_CAMPAIGN_STATE */
    { "Campaign State",                      SE_KIND_CAMPAIGN_STATE, 0,  0, 2, NULL,          0, NULL,               0 },
    /* SE_MBR_CAMPAIGN_ATTEMPTS_LEFT */
    { "Campaign Attempts Left",              SE_KIND_U8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_PLAYS_UNTIL_NEXT_CAMPAIGN */
    { "Plays Until Next Campaign",           SE_KIND_U8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_CURRENT_CAMPAIGN */
    { "Current Campaign",                    SE_KIND_U8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_26A */
    { "unk26A",                              SE_KIND_U8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_READING_MATERIAL_UNLOCKED */
    { "Reading Material Unlocked",           SE_KIND_U8,         20,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_DRUM_KITS_UNLOCKED */
    { "Drum Kits Unlocked",                  SE_KIND_U8,         15,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_TOTAL_MEDALS */
    { "Total Medals",                        SE_KIND_U8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_28F */
    { "unk28F",                              SE_KIND_U8,    0,  -1, -1, NULL,   8, NULL,               0 },
    /* SE_MBR_MINIMUM_FAILS_FOR_BARISTA_HELP */
    { "Minimum Fails for Barista's Help",    SE_KIND_U8,          0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_291 */
    { "unk291",                              SE_KIND_U8,    0,  -1, -1, NULL,   8, NULL,               0 },
    /* SE_MBR_HIGH_SCORE_MR_UPBEAT */
    { "High Score Mr. Upbeat",               SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_HIGH_SCORE_MANNEQUIN_FACTORY */
    { "High Score Mannequin Factory",        SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_HIGH_SCORE_SICK_BEATS_SP */
    { "High Score Sick Beats SP",            SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_HIGH_SCORE_QUIZ_SHOW_EX */
    { "High Score Quiz Show EX",             SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2A4 */
    { "unk2A4",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2A8 */
    { "unk2A8",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2AC */
    { "unk2AC",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2B0 */
    { "unk2B0",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_SOUND_MODE */
    { "Sound Mode",                          SE_KIND_U32,         0,  1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_PERFECT_CLEAR_CAFE_DIALOGUE_PENDING */
    { "Perfect Clear Cafe Dialogue Pending", SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2BC */
    { "unk2BC",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2C0 */
    { "unk2C0",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2C4 */
    { "unk2C4",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2C8 */
    { "unk2C8",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2CC */
    { "unk2CC",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 },
    /* SE_MBR_UNK_2D0 */
    { "unk2D0",                              SE_KIND_U32,         0,  -1, -1, NULL,          0, NULL,               0 }
};

void save_editor_scene_init_gfx3(void) {
    s32 task = start_new_texture_loader(get_current_mem_id(), save_editor_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
    func_0800c604(0);
}

void save_editor_scene_init_gfx2(void) {
    s32 task = func_08002ee0(get_current_mem_id(), save_editor_gfx_table, 0x3000);
    run_func_after_task(task, save_editor_scene_init_gfx3, 0);
    func_0800c604(0);
}

void save_editor_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), save_editor_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}

void save_editor_scene_start(void *sVar, s32 dArg) {
    u32 i;

    func_08007324(TRUE);
    func_080073f0();

    gSaveEditor->bgFont       = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    gSaveEditor->objFont      = scene_create_obj_font_printer(0x300, 4);
    gSaveEditor->saveData     = &D_030046a8->data;
    gSaveEditor->inputsEnabled = FALSE;
    gSaveEditor->currentMember = 0;
    gSaveEditor->arrayIndex    = 0;
    gSaveEditor->fieldIndex    = 0;
    gSaveEditor->flagIndex     = 0;

    for (i = 0; i < SE_LINE_COUNT; ++i) {
        gSaveEditor->textLineSprites[i] = -1;
    }

    save_editor_scene_init_gfx1();

    save_editor_clear_bg_text();
    save_editor_draw_bg_text("@–@‚q|‚h‚p@‚r‚‚–‚…@‚d‚„‚‰‚”‚‚’@–", 4, 0, 0);

    set_next_scene(&scene_debug_menu);
    save_editor_render_page();
}

void save_editor_scene_paused(void *sVar, s32 dArg) {
}

void save_editor_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}

u32 save_editor_inputs_enabled(void) {
    return gSaveEditor->inputsEnabled ? TRUE : FALSE;
}

/* Wrap val into [0, max). */
static u32 wrap_index(u32 val, u32 delta_positive, u32 max) {
    return (val + delta_positive) % max;
}

void save_editor_scene_update(void *sVar, s32 dArg) {
    u32 oldMember = gSaveEditor->currentMember;
    u32 oldArray  = gSaveEditor->arrayIndex;
    u32 oldField  = gSaveEditor->fieldIndex;
    u32 oldFlag   = gSaveEditor->flagIndex;
    u32 dirty     = 0;

    const struct SaveEditorMember *m;

    if (!save_editor_inputs_enabled()) {
        return;
    }

    if (D_030053b8 & LEFT_SHOULDER_BUTTON) {
        gSaveEditor->currentMember = wrap_index(gSaveEditor->currentMember, SE_MBR_COUNT - 1, SE_MBR_COUNT);
    }
    if (D_030053b8 & RIGHT_SHOULDER_BUTTON) {
        gSaveEditor->currentMember = wrap_index(gSaveEditor->currentMember, 1, SE_MBR_COUNT);
    }

    if (gSaveEditor->currentMember != oldMember) {
        gSaveEditor->arrayIndex = 0;
        gSaveEditor->fieldIndex = 0;
        gSaveEditor->flagIndex  = 0;
    }

    m = &gSaveEditorMembers[gSaveEditor->currentMember];

    if (m->arrayLen > 0) {
        if (D_03004afc & DPAD_UP) {
            gSaveEditor->arrayIndex = wrap_index(gSaveEditor->arrayIndex, 1, m->arrayLen);
        }
        if (D_03004afc & DPAD_DOWN) {
            gSaveEditor->arrayIndex = wrap_index(gSaveEditor->arrayIndex, m->arrayLen - 1, m->arrayLen);
        }
    }

    if (D_03004afc & START_BUTTON) {
        if (m->kind == SE_KIND_STRUCT_FIELD && m->fieldCount > 0) {
            gSaveEditor->fieldIndex = wrap_index(gSaveEditor->fieldIndex, 1, m->fieldCount);
            dirty = 1;
        }
        if (m->kind == SE_KIND_BITFLAGS && m->flagCount > 0) {
            gSaveEditor->flagIndex = wrap_index(gSaveEditor->flagIndex, 1, m->flagCount);
            dirty = 1;
        }
    }

    if (D_03004afc & DPAD_LEFT) {
        save_editor_modify_value(gSaveEditor->currentMember, gSaveEditor->arrayIndex, gSaveEditor->fieldIndex, -1);
        dirty = 1;
    }
    if (D_03004afc & DPAD_RIGHT) {
        save_editor_modify_value(gSaveEditor->currentMember, gSaveEditor->arrayIndex, gSaveEditor->fieldIndex, 1);
        dirty = 1;
    }
    if (D_03004afc & A_BUTTON) {
        if (m->kind == SE_KIND_BITFLAGS && m->flagCount > 0) {
            void *ptr = save_editor_get_value_ptr(gSaveEditor->currentMember, gSaveEditor->arrayIndex, 0);
            if (ptr != NULL) {
                u8 mask = 1u << m->flags[gSaveEditor->flagIndex].bit;
                *(u8 *)ptr ^= mask;
                dirty = 1;
            }
        } else {
            save_editor_modify_value(gSaveEditor->currentMember, gSaveEditor->arrayIndex, gSaveEditor->fieldIndex, 10);
            dirty = 1;
        }
    }
    if (D_03004afc & B_BUTTON) {
        if(m->kind == SE_KIND_BITFLAGS && m->flagCount > 0){
            void *ptr = save_editor_get_value_ptr(gSaveEditor->currentMember, gSaveEditor->arrayIndex, 0);
            if (ptr != NULL) {
                *(u8 *)ptr = 0;
                dirty = 1;
            }
        } else {
            save_editor_modify_value(gSaveEditor->currentMember, gSaveEditor->arrayIndex, gSaveEditor->fieldIndex, -10);
            dirty = 1;
        }
    }

    if (D_03004afc & SELECT_BUTTON) {
        if (!(D_030053b8 & LEFT_SHOULDER_BUTTON)) {
            write_game_save_data();
        }
        set_pause_beatscript_scene(FALSE);
    }

    if (gSaveEditor->currentMember != oldMember
     || gSaveEditor->arrayIndex    != oldArray
     || gSaveEditor->fieldIndex    != oldField
     || gSaveEditor->flagIndex     != oldFlag
     || dirty) {
        save_editor_render_page();
    }
}

void *save_editor_get_value_ptr(u32 member, u32 arrayIndex, u32 fieldIndex) {
    struct TengokuSaveData *save = gSaveEditor->saveData;
    const struct SaveEditorMember *m = &gSaveEditorMembers[member];

    if (m->arrayLen > 0 && arrayIndex >= (u32)m->arrayLen) {
        return NULL;
    }

    switch (member) {
        case SE_MBR_GAME_SELECT_CURSOR_X:              return &save->gsCursorX;
        case SE_MBR_GAME_SELECT_CURSOR_Y:              return &save->gsCursorY;
        case SE_MBR_RECENT_LEVEL_X:                    return &save->recentLevelX;
        case SE_MBR_RECENT_LEVEL_Y:                    return &save->recentLevelY;
        case SE_MBR_RECENT_LEVEL_STATE:                return &save->recentLevelState;
        case SE_MBR_RECENT_LEVEL_CLEARED_BY_BARISTA:   return &save->recentLevelClearedByBarista;
        case SE_MBR_RECENT_LEVEL_SCORE:                return &save->recentLevelScore;
        case SE_MBR_CURRENT_FLOW:                      return &save->currentFlow;
        case SE_MBR_UNK_B0:                            return &save->unkB0;
        case SE_MBR_ADVANCE_FLAGS:                     return &save->advanceFlags;
        case SE_MBR_TOTAL_SONGS:                       return &save->totalSongs;
        case SE_MBR_UNK_B3:                            return &save->unkB3;
        case SE_MBR_TOTAL_PERFECTS:                    return &save->totalPerfects;
        case SE_MBR_CAMPAIGN_STATE:                    return &save->campaignState;
        case SE_MBR_CAMPAIGN_ATTEMPTS_LEFT:            return &save->campaignAttemptsLeft;
        case SE_MBR_PLAYS_UNTIL_NEXT_CAMPAIGN:         return &save->playsUntilNextCampaign;
        case SE_MBR_CURRENT_CAMPAIGN:                  return &save->currentCampaign;
        case SE_MBR_UNK_26A:                           return &save->unk26A;
        case SE_MBR_TOTAL_MEDALS:                      return &save->totalMedals;
        case SE_MBR_UNK_28F:                           return &save->unk28F;
        case SE_MBR_MINIMUM_FAILS_FOR_BARISTA_HELP:    return &save->minFailsForBaristaHelp;
        case SE_MBR_UNK_291:                           return &save->unk291;

        case SE_MBR_LEVEL_STATES:                      return &save->levelStates[arrayIndex];
        case SE_MBR_LEVEL_SCORES:                      return &save->levelScores[arrayIndex];
        case SE_MBR_LEVEL_TOTAL_PLAYS:                 return &save->levelTotalPlays[arrayIndex];
        case SE_MBR_LEVEL_FIRST_OK:                    return &save->levelFirstOK[arrayIndex];
        case SE_MBR_LEVEL_FIRST_SUPERB:                return &save->levelFirstSuperb[arrayIndex];
        case SE_MBR_CAMPAIGNS_CLEARED:                 return &save->campaignsCleared[arrayIndex];
        case SE_MBR_READING_MATERIAL_UNLOCKED:         return &save->readingMaterialUnlocked[arrayIndex];
        case SE_MBR_DRUM_KITS_UNLOCKED:                return &save->drumKitsUnlocked[arrayIndex];

        case SE_MBR_STUDIO_SONGS: {
            u8 *base = (u8 *)&save->studioSongs[arrayIndex];
            if (fieldIndex >= (u32)m->fieldCount) return NULL;
            return base + fieldIndex;
        }

        default: {
            u32 offset = member - SE_MBR_HIGH_SCORE_MR_UPBEAT;
            if (member >= SE_MBR_HIGH_SCORE_MR_UPBEAT && member <= SE_MBR_UNK_2D0) {
                return &save->unk294[offset];
            }
            return NULL;
        }
    }
}

s32 save_editor_read_value(const void *ptr, enum SaveEditorKind kind) {
    switch (kind) {
        case SE_KIND_S8:          return *(const s8  *)ptr;
        case SE_KIND_LEVEL_STATE: return *(const s8  *)ptr;
        case SE_KIND_U8:          return *(const u8  *)ptr;
        case SE_KIND_CAMPAIGN_STATE:   return *(const u8  *)ptr;
        case SE_KIND_S16:         return *(const s16 *)ptr;
        case SE_KIND_U16:         return *(const u16 *)ptr;
        case SE_KIND_S32:         return *(const s32 *)ptr;
        case SE_KIND_U32:         return (s32)*(const u32 *)ptr;
        case SE_KIND_BOOL:        return *(const u8  *)ptr ? 1 : 0;
        case SE_KIND_BITFLAGS:    return *(const u8  *)ptr;
        case SE_KIND_STRUCT_FIELD:return *(const u8  *)ptr;
        default:                  return 0;
    }
}

void save_editor_write_value(void *ptr, enum SaveEditorKind kind, s32 val) {
    switch (kind) {
        case SE_KIND_S8:          *(s8  *)ptr = (s8) val;   break;
        case SE_KIND_LEVEL_STATE: *(s8  *)ptr = (s8) val;   break;
        case SE_KIND_U8:          *(u8  *)ptr = (u8) val;   break;
        case SE_KIND_CAMPAIGN_STATE:   *(u8  *)ptr = (u8) val;   break;
        case SE_KIND_S16:         *(s16 *)ptr = (s16)val;   break;
        case SE_KIND_U16:         *(u16 *)ptr = (u16)val;   break;
        case SE_KIND_S32:         *(s32 *)ptr = val;         break;
        case SE_KIND_U32:         *(u32 *)ptr = (u32)val;   break;
        case SE_KIND_BOOL:        *(u8  *)ptr = val ? 1 : 0; break;
        case SE_KIND_BITFLAGS:    *(u8  *)ptr = (u8) val;   break;
        case SE_KIND_STRUCT_FIELD:*(u8  *)ptr = (u8) val;   break;
        default:                  break;
    }
}

s32 save_editor_clamp(const struct SaveEditorMember *m, s32 val) {
    if ((m->clampMin != -1 || m->clampMax != -1) && val < m->clampMin) return m->clampMin;
    if ((m->clampMax != -1 || m->clampMin != -1) && val > m->clampMax) return m->clampMax;
    return val;
}

static enum SaveEditorKind resolve_kind(const struct SaveEditorMember *m, u32 fieldIndex) {
    if (m->kind == SE_KIND_STRUCT_FIELD && m->fields != NULL && fieldIndex < (u32)m->fieldCount) {
        return m->fields[fieldIndex].kind;
    }
    return m->kind;
}

void save_editor_modify_value(u32 member, u32 arrayIndex, u32 fieldIndex, s32 delta) {
    const struct SaveEditorMember *m = &gSaveEditorMembers[member];
    enum SaveEditorKind            kind;
    u32  bypass;
    void *ptr;
    s32  val;

    ptr = save_editor_get_value_ptr(member, arrayIndex, fieldIndex);
    if (ptr == NULL) return;

    // bypass clamping
    bypass = (D_030053b8 & LEFT_SHOULDER_BUTTON) && (D_030053b8 & RIGHT_SHOULDER_BUTTON);

    kind = resolve_kind(m, fieldIndex);
    val  = save_editor_read_value(ptr, kind);
    val += delta;

    if (!bypass) {
        val = save_editor_clamp(m, val);
    }

    save_editor_write_value(ptr, kind, val);
}

void save_editor_draw_line(u32 line, u32 palette, const char *string, s16 x, s16 y) {
    struct Animation *anim;
    void  *tileset;
    u32    tileY;
    s16    sprite;

    save_editor_clear_line(line);

    tileY   = (line * 2) + 12;
    tileset = OBJ_TILESET_BASE(tileY * 0x400);
    dma3_fill(0, tileset, 0x800, 0x20, 0x200);

    anim   = text_printer_get_unformatted_line_anim(get_current_mem_id(), 0, tileY,
                 TEXT_PRINTER_FONT_SMALL, string, TEXT_ANCHOR_BOTTOM_LEFT, 0, 256);
    sprite = sprite_create(gSpriteHandler, anim, 0, x, y, 0, 0, 0, 0);
    sprite_set_base_palette(gSpriteHandler, sprite, palette + 8);

    gSaveEditor->textLineSprites[line] = sprite;
}

void save_editor_clear_line(u32 line) {
    s16 sprite = gSaveEditor->textLineSprites[line];
    if (sprite >= 0) {
        struct Animation *anim = (void *)sprite_get_data(gSpriteHandler, sprite, 7);
        sprite_delete(gSpriteHandler, sprite);
        text_printer_delete_anim(anim);
        gSaveEditor->textLineSprites[line] = -1;
    }
}

void save_editor_draw_bg_text(const char *text, u16 tileX, u16 tileY, u32 palette) {
    u16 *bgMap    = (u16 *)BG_MAP_BASE(0xE800);
    u16 *dest     = bgMap + tileX + tileY * 32;
    bmp_font_bg_print_text(gSaveEditor->bgFont, dest, 32, text, palette+8);
}

void save_editor_clear_bg_text(void) {
    dma3_fill(0, (u16 *)BG_MAP_BASE(0xE800), 0x800, 0x20, 0x200);
}

static void format_value(char *buf, u32 bufSize, const struct SaveEditorMember *m, u32 arrayIndex, u32 fieldIndex) {
    void *ptr  = save_editor_get_value_ptr((u32)(m - gSaveEditorMembers), arrayIndex, fieldIndex);
    enum SaveEditorKind kind = resolve_kind(m, fieldIndex);
    s32 val;

    if (ptr == NULL) {
        snprintf(buf, bufSize, "n/a");
        return;
    }

    val = save_editor_read_value(ptr, kind);

    switch (kind) {
        case SE_KIND_BOOL:
            snprintf(buf, bufSize, "%s", val ? "TRUE" : "FALSE");
            break;
        case SE_KIND_BITFLAGS:
            snprintf(buf, bufSize, "0x%02X", (u32)val);
            break;
        case SE_KIND_LEVEL_STATE:
            switch (val) {
                case -1: snprintf(buf, bufSize, "LEVEL_STATE_NULL"); break;
                case 0:  snprintf(buf, bufSize, "LEVEL_STATE_HIDDEN");     break;
                case 1:  snprintf(buf, bufSize, "LEVEL_STATE_APPEARING");         break;
                case 2:  snprintf(buf, bufSize, "LEVEL_STATE_CLOSED");     break;
                case 3:  snprintf(buf, bufSize, "LEVEL_STATE_OPEN");     break;
                case 4:  snprintf(buf, bufSize, "LEVEL_STATE_CLEARED");     break;
                case 5:  snprintf(buf, bufSize, "LEVEL_STATE_HAS_MEDAL");     break;
                default: snprintf(buf, bufSize, "n/a");    break;
            }
            break;
        case SE_KIND_CAMPAIGN_STATE:
            switch (val) {
                case 0:  snprintf(buf, bufSize, "CAMPAIGN_STATE_INACTIVE");     break;
                case 1:  snprintf(buf, bufSize, "CAMPAIGN_STATE_AVAILABLE");     break;
                case 2:  snprintf(buf, bufSize, "CAMPAIGN_STATE_ACTIVE");     break;
                default: snprintf(buf, bufSize, "n/a");    break;
            }
            break;
        case SE_KIND_S8:
        case SE_KIND_S16:
        case SE_KIND_S32:
            snprintf(buf, bufSize, "%d", val);
            break;
        default:
            snprintf(buf, bufSize, "%u", (u32)val);
            break;
    }
}

void save_editor_render_page(void) {
    char buf[256];
    char valStr[64];
    u32  i;
    u32  member     = gSaveEditor->currentMember;
    u32  arrIdx     = gSaveEditor->arrayIndex;
    u32  fieldIdx   = gSaveEditor->fieldIndex;
    u32  flagIdx    = gSaveEditor->flagIndex;
    const struct SaveEditorMember *m = &gSaveEditorMembers[member];

    format_value(valStr, sizeof(valStr), m, arrIdx, fieldIdx);

    if (m->kind == SE_KIND_STRUCT_FIELD && m->fieldCount > 0) {
        snprintf(buf, sizeof(buf), "%s [%u/%u] .%s: %s",
                 m->name, arrIdx, (u32)(m->arrayLen - 1),
                 m->fields[fieldIdx].name, valStr);
    } else if (m->kind == SE_KIND_BITFLAGS && m->flagCount > 0) {
        snprintf(buf, sizeof(buf), "%s: %s",
                 m->name, valStr);
    } else if (m->arrayLen > 0) {
        snprintf(buf, sizeof(buf), "%s [%u/%u]: %s",
                 m->name, arrIdx, (u32)(m->arrayLen - 1), valStr);
    } else {
        snprintf(buf, sizeof(buf), "%s: %s", m->name, valStr);
    }
    save_editor_draw_line(SE_LINE_HEADER, 0, buf, 8, 24);

    save_editor_draw_line(SE_LINE_HINT_A, 0, "‡K/‡L:Change Current Save Member", 8, 48);

    save_editor_draw_line(SE_LINE_HINT_B, 0, "SELECT: Save and Exit", 8, 64);

    if (m->kind == SE_KIND_BITFLAGS && m->flagCount > 0) {
        void* ptr = save_editor_get_value_ptr(member, arrIdx, 0);
        u8 raw = (ptr != NULL) ? *(u8 *)ptr : 0;

        for (i = 0; i < 8; i++) {
            if (i < (u32)m->flagCount) {
                const struct SaveEditorFlag *f = &m->flags[i];
                snprintf(buf, sizeof(buf), "%s %-22s %s", (i == flagIdx) ? ">" : "\x87\x53  ", f->name, (raw >> f->bit) & 1u ? "[!]" : "[ ]");
                save_editor_draw_line(SE_LINE_FLAG_0 + i, 0, buf, (i >= 4) ? 128 : 0, 80 + (i * 18) - ((i >= 4) ? 72 : 0));
            } else {
                save_editor_clear_line(SE_LINE_FLAG_0 + i);
            }
        }
    } else if (m->kind == SE_KIND_STRUCT_FIELD && m->fieldCount > 0) {
        for(i = 0; i< 8; i++){
            if(i < m->fieldCount){
                format_value(valStr, sizeof(valStr), m, arrIdx, i);
                snprintf(buf, sizeof(buf), "%c .%s %s", (i == fieldIdx) ? '>' : ' ', m->fields[i].name, valStr);
                save_editor_draw_line(SE_LINE_FLAG_0 + i, 0, buf, (i >= 4) ? 128 : 0, 80 + (i * 18) - ((i >= 4) ? 72 : 0));
            } else {
                save_editor_clear_line(SE_LINE_FLAG_0 + i);
            }
        }
    } else {
        for (i = 0; i < 8; ++i) {
            save_editor_clear_line(SE_LINE_FLAG_0 + i);
        }

        if(m->arrayLen>0){
            if(member == SE_MBR_LEVEL_STATES || member == SE_MBR_LEVEL_SCORES || member == SE_MBR_LEVEL_TOTAL_PLAYS || member == SE_MBR_LEVEL_FIRST_OK || member == SE_MBR_LEVEL_FIRST_SUPERB){
                snprintf(buf, sizeof(buf), "Level: %s", (arrIdx < TOTAL_LEVELS) ? game_select_get_level_name(arrIdx) : "n/a");
                save_editor_draw_line(SE_LINE_FLAG_0, 0, buf, 32, 80);
            } else if (member == SE_MBR_CAMPAIGNS_CLEARED){
                snprintf(buf, sizeof(buf), "Campaign: %s", (arrIdx < TOTAL_PERFECT_CAMPAIGNS) ? get_level_name_from_campaign(arrIdx) : "n/a");
                save_editor_draw_line(SE_LINE_FLAG_0, 0, buf, 32, 80);
            } else if (member == SE_MBR_READING_MATERIAL_UNLOCKED){
                snprintf(buf, sizeof(buf), "Reading Material: %s", (arrIdx < 20) ? reading_material_table[arrIdx].title : "n/a");
                save_editor_draw_line(SE_LINE_FLAG_0, 0, buf, 32, 80);
            } else if (member == SE_MBR_DRUM_KITS_UNLOCKED){
                snprintf(buf, sizeof(buf), "Drum Kit: %s", (arrIdx < 20) ? studio_drum_kit_names[arrIdx] : "n/a");
                save_editor_draw_line(SE_LINE_FLAG_0, 0, buf, 32, 80);
            } else {
                save_editor_draw_line(SE_LINE_FLAG_0, 0, "shaffy did something wrong :(", 64, 80);
            }
        }
    }
}