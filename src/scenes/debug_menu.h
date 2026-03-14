#pragma once

#include "global.h"
#include "scenes.h"


// MACROS
#define gDebugMenu ((struct DebugMenuSceneData *)gCurrentSceneData)
#define END_OF_DEBUG_ENTRIES { NULL, NULL }
#define DEBUG_MENU_ENTRY_PER_PAGE 6


// TYPES
struct DebugMenuSceneData {
    struct BitmapFontBG *bgFont;
    struct BitmapFontOBJ *objFont;
    u32 inputsEnabled;
    u16 totalEntries;
    s16 page;
    s16 row;
    s16 cursor;
    s16 counter;
    s16 textLines[8];
};

struct DebugMenuEntry {
    struct Scene *scene;
    const char *label;
    u8 seeEpilogue;
};


// DATA
extern union SceneObject debug_menu_scene_objects[];
extern struct GraphicsTable debug_menu_gfx_table[];
extern struct CompressedData *debug_menu_buffered_textures[];
extern struct DebugMenuEntry debug_menu_entry_table[];
extern char debug_menu_counter_digits[];


// FUNCTIONS
extern void debug_menu_scene_init_memory(void);
extern void debug_menu_scene_update_static_var(void);
extern void debug_menu_scene_init_gfx3(void);
extern void debug_menu_scene_init_gfx2(void);
extern void debug_menu_scene_init_gfx1(void);
extern void debug_menu_scene_start(void *sVar, s32 dArg);
extern void debug_menu_scene_paused(void *sVar, s32 dArg);
extern void debug_menu_scene_update(void *sVar, s32 dArg);
extern u32  debug_menu_scene_inputs_enabled(void);
extern void debug_menu_scene_stop(void *sVar, s32 dArg);
extern void debug_menu_render_table(s32 page, s32 row);
