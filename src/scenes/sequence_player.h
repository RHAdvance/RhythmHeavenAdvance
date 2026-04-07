#pragma once

#include "global.h"
#include "scenes.h"
#include "sound.h"

#define gSequencePlayer ((struct SequencePlayerSceneData *)gCurrentSceneData)

enum SequencePlayerLine {
    SP_LINE_HEADER = 0,
    SP_LINE_SYMBOL = 1,
    SP_LINE_TITLE = 2,
    SP_LINE_INFO = 3,
    SP_LINE_OPTION_0 = 4,
    SP_LINE_OPTION_1 = 5,
    SP_LINE_OPTION_2 = 6,
    SP_LINE_OPTION_3 = 7,
    SP_LINE_OPTION_4 = 8,
    SP_LINE_HINT = 9,
    SP_LINE_STATUS = 10,
    SP_LINE_COUNT
};

struct SequencePlayerSceneData {
    struct BitmapFontBG *bgFont;
    struct BitmapFontOBJ *objFont;
    struct SoundPlayer *activePlayer;

    u32 inputsEnabled;
    u32 currentSong;
    u32 optionIndex;
    u32 overridePlayer;
    u32 selectedPlayer;
    s32 pitch;
    u32 volume;
    u32 stopOthers;
    u32 lastAction;

    s16 textLineSprites[SP_LINE_COUNT];
};

extern struct GraphicsTable sequence_player_gfx_table[];
extern struct CompressedData *sequence_player_buffered_textures[];

extern void sequence_player_scene_init_gfx3(void);
extern void sequence_player_scene_init_gfx2(void);
extern void sequence_player_scene_init_gfx1(void);
extern void sequence_player_scene_start(void *sVar, s32 dArg);
extern void sequence_player_scene_paused(void *sVar, s32 dArg);
extern void sequence_player_scene_update(void *sVar, s32 dArg);
extern void sequence_player_scene_stop(void *sVar, s32 dArg);

extern u32 sequence_player_inputs_enabled(void);
extern void sequence_player_draw_line(u32 line, u32 palette, const char *string, s16 x, s16 y);
extern void sequence_player_clear_line(u32 line);
extern void sequence_player_draw_bg_text(const char *text, u16 tileX, u16 tileY, u32 palette);
extern void sequence_player_clear_bg_text(void);
extern void sequence_player_render_page(void);
