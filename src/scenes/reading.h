#pragma once

#include "global.h"
#include "scenes.h"


// VALUES
enum ReadingMaterialEnum {
    /* 00 */ READING_MATERIAL_WELCOME,
    /* 01 */ READING_MATERIAL_MANUAL,
    /* 02 */ READING_MATERIAL_CAFE,
    /* 03 */ READING_MATERIAL_RHYTHM_TWEEZERS,
    /* 04 */ READING_MATERIAL_NIGHT_WALK,
    /* 05 */ READING_MATERIAL_SPACEBALL,
    /* 06 */ READING_MATERIAL_MECHANICAL_HORSE,
    /* 07 */ READING_MATERIAL_MARCHING_ORDERS,
    /* 08 */ READING_MATERIAL_RAP_MEN,
    /* 09 */ READING_MATERIAL_BON_ODORI,
    /* 10 */ READING_MATERIAL_REMIX3,
    /* 11 */ READING_MATERIAL_REMIX5,
    /* 12 */ READING_MATERIAL_REMIX8,
    /* 13 */ READING_MATERIAL_NINJA_BODYGUARD,
    /* 14 */ READING_MATERIAL_TOSS_BOYS,
    /* 15 */ READING_MATERIAL_FAN_MAIL,
    /* 16 */ READING_MATERIAL_RHYTHM_FORMULA,
    /* 17 */ READING_MATERIAL_RHYTHM_DIAGNOSIS,
    /* 18 */ READING_MATERIAL_RHYTHM_POEM,
    /* 19 */ READING_MATERIAL_RHYTHM_HAIKU,
    /* 20 */ READING_MATERIAL_CREDITS
};

enum ReadingEventsEnum {
    /* 00 */ READING_EV_NONE,
    /* 01 */ READING_EV_SCROLL_UP,
    /* 02 */ READING_EV_SCROLL_DOWN,
    /* 03 */ READING_EV_CANCEL
};


// MACROS
#define gReading ((struct ReadingSceneData *)gCurrentSceneData)


// TYPES
struct ReadingSceneData {
    struct ReadingMaterial *material;
    u32 inputsEnabled;
    struct TextPrinter *printer;
    s8 currentPage;
    struct TextPrinterData pageData[32];
    u8 pageState;
    s16 targetY;
    s16 relativeY;
    s16 pagePosY;
    s16 iconPrev;
    s16 iconNext;
};

struct ReadingMaterial {
    const char *title;
    const char *text;
    const struct GraphicsTable *graphics;
    struct SongHeader **sounds;
};


// DATA
extern struct ReadingMaterial reading_material_table[];
extern struct GraphicsTable reading_gfx_table[];
extern struct CompressedData *reading_buffered_textures[];
extern struct ReadingMaterial reading_material_error;


// FUNCTIONS
extern void reading_scene_init_gfx4(void);
extern void reading_scene_init_gfx3(void);
extern void reading_scene_init_gfx2(void);
extern void reading_scene_init_gfx1(void);
extern void reading_scene_start(void *sVar, s32 dArg);
extern void reading_scene_update_page(void);
extern void reading_scene_update(void *sVar, s32 dArg);
extern u32  reading_scene_inputs_enabled(void);
extern void reading_scene_stop(void *sVar, s32 dArg);
extern void reading_scene_play_bgm(void);
