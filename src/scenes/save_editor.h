#pragma once

#include "global.h"
#include "scenes.h"

#define gSaveEditor ((struct SaveEditorSceneData *)gCurrentSceneData)
#define END_OF_FLAG {NULL, -1}

enum SaveEditorKind {
    SE_KIND_S8,
    SE_KIND_U8,
    SE_KIND_S16,
    SE_KIND_U16,
    SE_KIND_S32,
    SE_KIND_U32,
    SE_KIND_BOOL,
    SE_KIND_LEVEL_STATE,
    SE_KIND_CAMPAIGN_STATE,

    SE_KIND_BITFLAGS,
    SE_KIND_STRUCT_FIELD
};

struct SaveEditorFlag {
    const char *name;
    s8          bit;
};

struct SaveEditorField {
    const char        *name;
    enum SaveEditorKind kind;
};

struct SaveEditorMember {
    const char *name;
    enum SaveEditorKind kind;

    u16 arrayLen;

    s32 clampMin;
    s32 clampMax;

    const struct SaveEditorFlag *flags;
    u8 flagCount;

    const struct SaveEditorField *fields;
    u8 fieldCount;
};

enum SaveEditorMemberIdx {
    SE_MBR_GAME_SELECT_CURSOR_X,
    SE_MBR_GAME_SELECT_CURSOR_Y,
    SE_MBR_RECENT_LEVEL_X,
    SE_MBR_RECENT_LEVEL_Y,
    SE_MBR_RECENT_LEVEL_STATE,
    SE_MBR_RECENT_LEVEL_CLEARED_BY_BARISTA,
    SE_MBR_LEVEL_STATES,
    SE_MBR_RECENT_LEVEL_SCORE,
    SE_MBR_LEVEL_SCORES,
    SE_MBR_CURRENT_FLOW,
    SE_MBR_UNK_B0,
    SE_MBR_ADVANCE_FLAGS,
    SE_MBR_TOTAL_SONGS,
    SE_MBR_UNK_B3,
    SE_MBR_STUDIO_SONGS,
    SE_MBR_LEVEL_TOTAL_PLAYS,
    SE_MBR_LEVEL_FIRST_OK,
    SE_MBR_LEVEL_FIRST_SUPERB,
    SE_MBR_TOTAL_PERFECTS,
    SE_MBR_CAMPAIGNS_CLEARED,
    SE_MBR_CAMPAIGN_STATE,
    SE_MBR_CAMPAIGN_ATTEMPTS_LEFT,
    SE_MBR_PLAYS_UNTIL_NEXT_CAMPAIGN,
    SE_MBR_CURRENT_CAMPAIGN,
    SE_MBR_UNK_26A,
    SE_MBR_READING_MATERIAL_UNLOCKED,
    SE_MBR_DRUM_KITS_UNLOCKED,
    SE_MBR_TOTAL_MEDALS,
    SE_MBR_UNK_28F,
    SE_MBR_MINIMUM_FAILS_FOR_BARISTA_HELP,
    SE_MBR_UNK_291,
    SE_MBR_HIGH_SCORE_MR_UPBEAT,
    SE_MBR_HIGH_SCORE_MANNEQUIN_FACTORY,
    SE_MBR_HIGH_SCORE_SICK_BEATS_SP,
    SE_MBR_HIGH_SCORE_QUIZ_SHOW_EX,
    SE_MBR_UNK_2A4,
    SE_MBR_UNK_2A8,
    SE_MBR_UNK_2AC,
    SE_MBR_UNK_2B0,
    SE_MBR_SOUND_MODE,
    SE_MBR_PERFECT_CLEAR_CAFE_DIALOGUE_PENDING,
    SE_MBR_UNK_2BC,
    SE_MBR_UNK_2C0,
    SE_MBR_UNK_2C4,
    SE_MBR_UNK_2C8,
    SE_MBR_UNK_2CC,
    SE_MBR_UNK_2D0,
    SE_MBR_COUNT
};

enum SaveEditorLine {
    SE_LINE_HEADER  = 0,
    SE_LINE_HINT_A  = 1,
    SE_LINE_HINT_B  = 2,
    SE_LINE_FLAG_0  = 3,
    SE_LINE_FLAG_1  = 4,
    SE_LINE_FLAG_2  = 5,
    SE_LINE_FLAG_3  = 6,
    SE_LINE_FLAG_4  = 7,
    SE_LINE_FLAG_5  = 8,
    SE_LINE_FLAG_6  = 9,
    SE_LINE_FLAG_7  = 10,
    SE_LINE_COUNT   = 11
};

struct SaveEditorSceneData {
    struct BitmapFontBG  *bgFont;
    struct BitmapFontOBJ *objFont;
    struct TengokuSaveData *saveData;

    u32  inputsEnabled;
    s16  textLineSprites[SE_LINE_COUNT];

    u32  currentMember;
    u32  arrayIndex;
    u32  fieldIndex;
    u32  flagIndex;
};

extern struct SaveEditorMember gSaveEditorMembers[SE_MBR_COUNT];

extern struct GraphicsTable         save_editor_gfx_table[];
extern struct CompressedData       *save_editor_buffered_textures[];

extern void save_editor_scene_init_gfx3(void);
extern void save_editor_scene_init_gfx2(void);
extern void save_editor_scene_init_gfx1(void);
extern void save_editor_scene_start(void *sVar, s32 dArg);
extern void save_editor_scene_paused(void *sVar, s32 dArg);
extern void save_editor_scene_update(void *sVar, s32 dArg);
extern void save_editor_scene_stop(void *sVar, s32 dArg);

extern u32   save_editor_inputs_enabled(void);
extern void *save_editor_get_value_ptr(u32 member, u32 arrayIndex, u32 fieldIndex);
extern s32   save_editor_read_value(const void *ptr, enum SaveEditorKind kind);
extern void  save_editor_write_value(void *ptr, enum SaveEditorKind kind, s32 val);
extern s32   save_editor_clamp(const struct SaveEditorMember *m, s32 val);
extern void  save_editor_modify_value(u32 member, u32 arrayIndex, u32 fieldIndex, s32 delta);

extern void save_editor_draw_line(u32 line, u32 palette, const char *str, s16 x, s16 y);
extern void save_editor_clear_line(u32 line);
extern void save_editor_draw_bg_text(const char *text, u16 tileX, u16 tileY, u32 palette);
extern void save_editor_clear_bg_text(void);
extern void save_editor_render_page(void);