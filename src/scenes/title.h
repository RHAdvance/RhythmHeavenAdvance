#pragma once

#include "global.h"
#include "scenes.h"


// VALUES
#define TOTAL_TITLE_LOGO_BUBBLES 7


// MACROS
#define gTitle ((struct TitleSceneData *)gCurrentSceneData)


// TYPES
struct TitleSceneData {
    u32 inputsEnabled;
    u32 timeUntilDemo;
    struct TextPrinter *textPrinter;
    s16 directiveText;
    s16 stars;
    u8 titleIsDisplayed;
    struct LogoBubble {
        u8 active;
        s16 inner;
        s16 outer;
        s16 letter;
        s16 centerX;
        s16 centerY;
        s16 riseDistance;
        s8_8 riseSpeed;
        s8_8 riseAngle;
        s8_8 riseTurnSpeed;
        s8_8 bounceAngle;
        s8_8 bounceBaseAngle;
        s8_8 bounceDistance;
    } logoBubbles[TOTAL_TITLE_LOGO_BUBBLES];
    s32 nextLogoBubble;
};

struct TitleLogoCharData {
    struct Animation *anim;
    s16 x, y;
    s16 bounceAngle;
};


// DATA
extern struct TitleLogoCharData title_logo_char_data_paradise[];
extern struct TitleLogoCharData title_logo_char_data_heaven[];
extern struct GraphicsTable title_gfx_table[];
extern struct CompressedData *title_buffered_textures[];
extern struct Beatscript script_scene_title_exit[];


// FUNCTIONS
extern void title_logo_set_bubble_pos(s32 id);
extern void title_logo_init(void);
extern void title_logo_appear(void);
extern void title_logo_update(void);
extern void title_logo_bounce_all(void);
extern void title_logo_bounce_bubble(s32 id);
extern void title_scene_init_memory(void);
extern void title_scene_init_gfx3(void);
extern void title_scene_init_gfx2(void);
extern void title_scene_init_gfx1(void);
extern void title_scene_start(void *sVar, s32 dArg);
extern void title_scene_complete_intro(void);
extern void title_scene_beat_anim(void);
extern void title_scene_paused(void *sVar, s32 dArg);
extern void title_scene_update_inputs(void);
extern void title_scene_update(void *sVar, s32 dArg);
extern u32  title_scene_inputs_enabled(void);
extern void title_scene_stop(void *sVar, s32 dArg);
