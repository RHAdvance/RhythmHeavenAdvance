#pragma once

#include "global.h"
#include "scenes.h"


// VALUES
enum OptionsPageEnum {
    OPTIONS_PAGE_CLASSIC,
    OPTIONS_PAGE_ADVANCE
};

enum OptionsBitmapEntryEnum {
#ifdef RUMBLE
    OPTIONS_BITMAP_RUMBLE,
#endif
    OPTIONS_BITMAP_SKIP_DISCLAIMER,
    OPTIONS_BITMAP_ALT_GAME_SELECT_MUSIC,
    OPTIONS_BITMAP_TOTAL
};

enum OptionsSceneStatesEnum {
    /* 00 */ OPTIONS_SCENE_STATE_EXIT,
    /* 01 */ OPTIONS_SCENE_STATE_MAIN,
    /* 02 */ OPTIONS_SCENE_STATE_WARNING
};

enum OptionsEventsEnum {
    /* 00 */ OPTIONS_EV_NONE,
    /* 01 */ OPTIONS_EV_CURSOR_UP,
    /* 02 */ OPTIONS_EV_CURSOR_DOWN,
    /* 03 */ OPTIONS_EV_CONFIRM,
    /* 04 */ OPTIONS_EV_CANCEL,

    /* 05 */ OPTIONS_BITMAP_EV_NONE,
    /* 06 */ OPTIONS_BITMAP_EV_SCROLL_UP,
    /* 07 */ OPTIONS_BITMAP_EV_SCROLL_DOWN,
    /* 08 */ OPTIONS_BITMAP_EV_CONFIRM,
    /* 09 */ OPTIONS_BITMAP_EV_CANCEL,
    /* 10 */ OPTIONS_BITMAP_EV_PAGE_PREV
};

enum OptionsButtonsEnum {
    /* 00 */ OPTIONS_BUTTON_SOUND_MODE,
    /* 01 */ OPTIONS_BUTTON_DATA_CLEAR
};

enum OptionsButtonSelectedEnum {
    /* 00 */ OPTIONS_BUTTON_ON,
    /* 01 */ OPTIONS_BUTTON_OFF
};

enum OptionsWarningEnum {
    /* 00 */ OPTIONS_WARNING_YES,
    /* 01 */ OPTIONS_WARNING_NO
};


// MACROS
#define gOptionsMenu ((struct OptionsSceneData *)gCurrentSceneData)

#define OPTIONS_BITMAP_VISIBLE_ROWS 3
#define OPTIONS_BITMAP_LINE_SPRITE_COUNT (OPTIONS_BITMAP_VISIBLE_ROWS + 1)
#define OPTIONS_BITMAP_LINE_CENTER_INDEX 1
#define OPTIONS_BITMAP_LINE_START_Y 40
#define OPTIONS_BITMAP_LINE_SPACING_Y 20
#define OPTIONS_BITMAP_TEXT_X 32
#define OPTIONS_BITMAP_TEXT_Z 0x5100
#define OPTIONS_BITMAP_FONT_BASE_TILE 384
#define OPTIONS_BITMAP_FONT_TILE_ROWS 4
#define OPTIONS_BITMAP_CURSOR_STEP 3
#define OPTIONS_BITMAP_SCROLL_STEP 6
#define OPTIONS_BITMAP_LINE_BUFFER_SIZE 96

#define OPTIONS_CURSOR_CLASSIC_X 104
#define OPTIONS_CURSOR_ADVANCE_X OPTIONS_BITMAP_TEXT_X
#define OPTIONS_CURSOR_SOUND_MODE_Y 56
#define OPTIONS_CURSOR_DATA_CLEAR_Y 84
#define OPTIONS_WARNING_CURSOR_X OPTIONS_CURSOR_CLASSIC_X

// TYPES
struct OptionsSceneData {
    u8 state;
    s16 cursorPos;
    s16 uiBarista;
    s16 uiSoundMode;
    s16 uiDataClear;
    u32 soundMode;
    u32 inputsEnabled;
    struct TextPrinter *descText;
    u8 warningCursorPos;
    s16 uiWarningPane;
    s16 uiWarningCursor;
    struct TextPrinter *warningText;
    u32 clearDataOnExit;
    u32 canceledDataClear;
    u8 activePage;
    s16 uiRShoulder;
    s16 uiLShoulder;
    struct BitmapFontOBJ *bitmapFont;
    s16 bitmapCursor;
    s16 bitmapLineSprites[OPTIONS_BITMAP_LINE_SPRITE_COUNT];
    u8 bitmapSelected;
    u8 bitmapTopIndex;
    s16 bitmapCursorY;
    s16 bitmapCursorTargetY;
    char bitmapLineBuffer[OPTIONS_BITMAP_LINE_BUFFER_SIZE];
};


// DATA
extern struct GraphicsTable options_gfx_table[];
extern struct CompressedData *options_buffered_textures[];
extern const char options_data_clear_confirm_text[];
extern const char *options_desc_text[];
extern const char *advance_options_desc_text[];
extern const char *advance_options_label_text[];
extern struct Animation *options_sound_mode_anim[][2];


// FUNCTIONS
extern void options_scene_init_memory(void);
extern void options_scene_init_gfx3(void);
extern void options_scene_init_gfx2(void);
extern void options_scene_init_gfx1(void);
extern void options_scene_start(void *sVar, s32 dArg);
extern void options_scene_paused(void *sVar, s32 dArg);
extern void options_scene_move_warning_cursor(u32 index);
extern void options_scene_update_main(void);
extern void options_scene_update_warning(void);
extern void options_scene_update(void *sVar, s32 dArg);
extern u32  options_scene_inputs_enabled(void);
extern void options_scene_stop(void *sVar, s32 dArg);
