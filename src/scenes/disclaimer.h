#pragma once

#include "global.h"
#include "scenes.h"

// so you know, i could totally just use the same header as warning.h, but i won't

// MACROS
#define gdisclaimer ((struct disclaimerSceneData *)gCurrentSceneData)


// TYPES
struct disclaimerSceneData {
    u32 inputsEnabled;
    u32 timer;
};


// DATA
extern struct GraphicsTable disclaimer_gfx_table[];

// FUNCTIONS
extern void disclaimer_scene_render_anim(void);
extern void disclaimer_scene_wait_if_not_seen(void);
extern void disclaimer_scene_init_gfx3(void);
extern void disclaimer_scene_init_gfx2(void);
extern void disclaimer_scene_init_gfx1(void);
extern void disclaimer_scene_start(void *sVar, s32 dArg);
extern void disclaimer_scene_update(void *sVar, s32 dArg);
