#include "engines/drum_studio.h"


  //  //  //  DRUM SAMURAI DATA  //  //  //


// [D_089e0ce0] Drum Samurai Expressions
struct DrumTeacherExpression drum_teacher_expressions_anim[] = {
    /* 0x00 */ {
        /* Head   */ NULL,
        /* R. Arm */ NULL,
        /* L. Arm */ NULL
    },
    /* 0x01 */ {
        /* Head   */ anim_drum_teacher_watching,
        /* R. Arm */ NULL,
        /* L. Arm */ NULL
    },
    /* 0x02 */ {
        /* Head   */ anim_drum_teacher_finish_pattern_face,
        /* R. Arm */ NULL,
        /* L. Arm */ anim_drum_teacher_finish_pattern_arm
    },
    /* 0x03 */ {
        /* Head   */ anim_drum_teacher_fail_pattern_face,
        /* R. Arm */ anim_drum_teacher_fail_pattern_arm_r,
        /* L. Arm */ anim_drum_teacher_fail_pattern_arm_l
    },
    /* 0x04 */ {
        /* Head   */ anim_drum_teacher_finish_lesson_face,
        /* R. Arm */ anim_drum_teacher_finish_lesson_arm,
        /* L. Arm */ NULL
    }
};


  //  //  //  DRUM SAMURAI KIT DATA  //  //  //


#include "drum_lessons_kits.inc.c"

// [D_089e16b0] ?
DrumPlayFunc D_089e16b0[] = {
    /* 0x00 */ NULL,
    /* 0x01 */ NULL,
    /* 0x02 */ NULL,
    /* 0x03 */ NULL,
    /* 0x04 */ NULL,
    /* 0x05 */ NULL,
    /* 0x06 */ NULL,
    /* 0x07 */ NULL,
    /* 0x08 */ NULL,
    /* 0x09 */ func_080275a8,
    /* 0x0A */ func_080275d0,
    /* 0x0B */ NULL,
    /* 0x0C */ NULL,
    /* 0x0D */ NULL,
    /* 0x0E */ NULL,
    /* 0x0F */ func_080275f8
};

// [D_089e16f0] Samurai Drummer's Kits
struct DrumTechKit *drum_teacher_kits[] = {
    /* 0x00 */ &D_089e1160,
    /* 0x01 */ &D_089e0df0,
    /* 0x02 */ &D_089e0ecc,
    /* 0x03 */ &D_089e0fa8,
    /* 0x04 */ &D_089e1084,
    /* 0x05 */ &D_089e1160,
    /* 0x06 */ &D_089e123c,
    /* 0x07 */ &D_089e1318,
    /* 0x08 */ &D_089e13f4,
    /* 0x09 */ &D_089e14d0,
    /* 0x0A */ &D_089e15ac,
    /* 0x0B */ &D_089e1160,
    /* 0x0C */ &D_089e1160,
    /* 0x0D */ &D_089e1160,
    /* 0x0E */ &D_089e1160
};


  //  //  //  ACCURACY METER DATA  //  //  //


// [D_089e172c] Accuracy Meter Lights
struct Animation *drum_lessons_accuracy_light_anim[] = {
    /* 0x00 */ anim_drum_lessons_accuracy_light1,
    /* 0x01 */ anim_drum_lessons_accuracy_light2,
    /* 0x02 */ anim_drum_lessons_accuracy_light3,
    /* 0x03 */ anim_drum_lessons_accuracy_light4,
    /* 0x04 */ anim_drum_lessons_accuracy_light5,
    /* 0x05 */ anim_drum_lessons_accuracy_light6,
    /* 0x06 */ anim_drum_lessons_accuracy_light7
};

// [D_089e1748] Accuracy Meter Light Positions
struct Vector2 drum_lessons_accuracy_light_positions[] = {
    /* 0x00 */ {  89, 19 },
    /* 0x01 */ { 100, 19 },
    /* 0x02 */ { 111, 18 },
    /* 0x03 */ { 122, 18 },
    /* 0x04 */ { 133, 18 },
    /* 0x05 */ { 144, 17 },
    /* 0x06 */ { 155, 17 },
};


  //  //  //  RESULTS DATA  //  //  //


// [D_089e1764] Rank Animations
struct Animation *drum_lessons_rank_anim[] = {
    /* RANK_0 */ anim_drum_lessons_rank_c,
    /* RANK_C */ anim_drum_lessons_rank_c,
    /* RANK_B */ anim_drum_lessons_rank_b,
    /* RANK_A */ anim_drum_lessons_rank_a,
    /* RANK_S */ anim_drum_lessons_rank_s
};

const char D_08059f94[] = "";

const char D_08059f98[] = "";

const char D_08059f9c[] = "\nFocus only on the beginning!";

const char D_08059fb4[] = "\nAim for the beginning!";

const char D_08059fd0[] = "\nDon't space out!";

const char D_08059fe8[] = "\nPress the A button too.";

const char D_0805a004[] = "\nPress the R button too.";

const char D_0805a020[] = "\npress them simultaneously!";

const char D_0805a038[] = "\nDon't rush it!";

const char D_0805a048[] = "\nYou were late";

const char D_0805a058[] = "\nFlawless!";

const char D_0805a06c[] = "\nPretty good!";

// [D_089e1778] Rank Text
const char *drum_lessons_rank_text[] = {
    /* RANK_0 */ "\n",
    /* RANK_C */ "\nNot bad!",
    /* RANK_B */ "\nYou're doin' pretty good!",
    /* RANK_A */ "\nYeah! That was great!",
    /* RANK_S */ "\nUnbelievable!",
};

const char D_0805a0c0[] = "\nYou scored ";

const char D_0805a0c8[] = ".";

const char D_0805a0cc[] = " points.";

// [D_089e178c] Rank SFX
struct SongHeader *drum_lessons_rank_sfx[] = {
    /* RANK_0 */ NULL,
    /* RANK_C */ &s_f_lesson_c_seqData,
    /* RANK_B */ &s_f_lesson_b_seqData,
    /* RANK_A */ &s_f_lesson_a_seqData,
    /* RANK_S */ &s_f_lesson_s_seqData
};


  //  //  //  STUDIO BG MONITOR DATA  //  //  //


#include "drum_studio_monitor_gfx.inc.c"


  //  //  //  PLAYER DRUM KIT DATA  //  //  //


#include "drum_studio_kits.inc.c"

// [D_089e2988] ?
DrumPlayFunc D_089e2988[] = {
    /* 0x00 */ NULL,
    /* 0x01 */ NULL,
    /* 0x02 */ NULL,
    /* 0x03 */ NULL,
    /* 0x04 */ NULL,
    /* 0x05 */ NULL,
    /* 0x06 */ NULL,
    /* 0x07 */ NULL,
    /* 0x08 */ NULL,
    /* 0x09 */ func_080286f4,
    /* 0x0A */ func_0802871c,
    /* 0x0B */ NULL,
    /* 0x0C */ NULL,
    /* 0x0D */ NULL,
    /* 0x0E */ NULL,
    /* 0x0F */ func_08028744,
};

// [D_089e29c8] Drum Kits
struct DrumTechKit *drum_studio_kits[] = {
    /* 0x00 */ &D_089e201c,
    /* 0x01 */ &D_089e1cac,
    /* 0x02 */ &D_089e1d88,
    /* 0x03 */ &D_089e1e64,
    /* 0x04 */ &D_089e1f40,
    /* 0x05 */ &D_089e2960,
    /* 0x06 */ &D_089e20f8,
    /* 0x07 */ &D_089e21d4,
    /* 0x08 */ &D_089e22b0,
    /* 0x09 */ &D_089e238c,
    /* 0x0A */ &D_089e2468,
    /* 0x0B */ &D_089e260c,
    /* 0x0C */ &D_089e26d4,
    /* 0x0D */ &D_089e27d0,
    /* 0x0E */ &D_089e2898
};


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e2a04] Buffered Textures List
struct CompressedData *drum_studio_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e2a08] Graphics Table (Studio Drumming)
struct GraphicsTable drum_studio_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &drum_studio_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &drum_studio_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &drum_studio_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ drum_lessons_bg_screen_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ drum_lessons_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e2a50] Graphics Table (Drum Lessons)
struct GraphicsTable drum_lessons_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &drum_studio_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &drum_studio_bg_map_lessons,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Tileset */ {
        /* Src.  */ &drum_lessons_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &drum_lessons_bg_map,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &drum_lessons_bg_map_level_up,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &drum_lessons_obj,
        /* Dest. */ OBJ_TILESET_BASE(0x5000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &drum_studio_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ drum_lessons_bg_screen_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ drum_lessons_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* BG Palette */ {
        /* Src.  */ drum_lessons_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x80
    },
    END_OF_GRAPHICS_TABLE
};


  //  //  //  SCRIPT DATA  //  //  //


asm(".include \"games/drum_studio/ending_scripts.inc\"");


  //  //  //  CUE DATA  //  //  //


// [D_089e2b58] ?
struct Vector2 D_089e2b58[] = {
    /* 0x00 */ { 1, 2 },
    /* 0x01 */ { 0, 1 },
    /* 0x02 */ { 0, 0 },
    /* 0x03 */ { 0, 0 },
    /* 0x04 */ { 0, 0 },
    /* 0x05 */ { 0, 0 },
    /* 0x06 */ { 0, 0 },
    /* 0x07 */ { 0, 0 }
};

// [D_089e2b78] ?
struct Vector2 D_089e2b78[] = {
    /* 0x00 */ { 0, 2 },
    /* 0x01 */ { 0, 1 },
    /* 0x02 */ { 0, 0 },
    /* 0x03 */ { 0, 0 },
    /* 0x04 */ { 0, 0 },
    /* 0x05 */ { 0, 0 },
    /* 0x06 */ { 0, 0 },
    /* 0x07 */ { 0, 0 }
};

// [D_089e2b98] ?
struct SpritePlaybackData D_089e2b98[] = {
    /* 0x00 */ {
        /* Animation  */ anim_drum_student_head,
        /* Start Cel  */ 0x7f,
        /* Direction  */ 1,
        /* Loop Start */ 0x7f,
    },
    /* 0x01 */ {
        /* Animation  */ anim_drum_student_happy,
        /* Start Cel  */ 0,
        /* Direction  */ 1,
        /* Loop Start */ 0x7f,
    }
};

// [D_089e2ba8] Button Inputs for Cues
u16 D_089e2ba8[] = {
    /* 0x00 */ DPAD_DOWN,
    /* 0x01 */ B_BUTTON,
    /* 0x02 */ DPAD_LEFT,
    /* 0x03 */ A_BUTTON,
    /* 0x04 */ DPAD_UP,
    /* 0x05 */ DPAD_RIGHT,
    /* 0x06 */ LEFT_SHOULDER_BUTTON,
    /* 0x07 */ RIGHT_SHOULDER_BUTTON,
    /* 0x08 */ DPAD_UP
};

// [D_089e2bbc] Cue 00 (Bass Drum - Left Pedal)
struct CueDefinition drum_studio_cue_kick_l = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(B_BUTTON | DPAD_DOWN),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2bfc] Cue 01 (Bass Drum - Right Pedal)
struct CueDefinition drum_studio_cue_kick_r = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(B_BUTTON | DPAD_DOWN),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2c3c] Cue 02 (Snare Drum - Left Hand)
struct CueDefinition drum_studio_cue_snare_l = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | DPAD_LEFT),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 2,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2c7c] Cue 03 (Snare Drum - Right Hand)
struct CueDefinition drum_studio_cue_snare_r = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | DPAD_LEFT),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 3,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2cbc] Cue 04 (Hi-Hat / Roll)
struct CueDefinition drum_studio_cue_04 = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(DPAD_UP),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 4,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2cfc] Cue 05 (Tom Drum)
struct CueDefinition drum_studio_cue_tom = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(DPAD_RIGHT),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 5,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2d3c] Cue 06 (Splash Cymbal)
struct CueDefinition drum_studio_cue_splash = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(RIGHT_SHOULDER_BUTTON | LEFT_SHOULDER_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x05, 0x05,
    /* Barely Window   */ -0x08, 0x08,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 6,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2d7c] Cue 07 (Crash Cymbal)
struct CueDefinition drum_studio_cue_crash = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(RIGHT_SHOULDER_BUTTON | LEFT_SHOULDER_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x05, 0x05,
    /* Barely Window   */ -0x08, 0x08,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 7,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2dbc] Cue 08 (Hi-Hat / Roll)
struct CueDefinition drum_studio_cue_08 = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(DPAD_UP),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x05, 0x05,
    /* Barely Window   */ -0x08, 0x08,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct DrumLessonsCue),
    /* Func. Spawn     */ drum_studio_cue_spawn,
    /* Spawn Parameter */ 8,
    /* Func. Update    */ drum_studio_cue_update,
    /* Func. Despawn   */ drum_studio_cue_despawn,
    /* Func. Hit       */ drum_studio_cue_hit,
    /* Func. Barely    */ drum_studio_cue_barely,
    /* Func. Miss      */ drum_studio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e2dfc] Cue Definition Index
struct CueDefinition *drum_studio_cue_index[] = {
    /* 0x00 */ &drum_studio_cue_kick_l,
    /* 0x01 */ &drum_studio_cue_kick_r,
    /* 0x02 */ &drum_studio_cue_snare_l,
    /* 0x03 */ &drum_studio_cue_snare_r,
    /* 0x04 */ &drum_studio_cue_04,
    /* 0x05 */ &drum_studio_cue_tom,
    /* 0x06 */ &drum_studio_cue_splash,
    /* 0x07 */ &drum_studio_cue_crash,
    /* 0x08 */ &drum_studio_cue_08,
    END_OF_CUE_INDEX
};


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e2e24] Common Events
EngineEvent drum_studio_common_events[] = {
    /* BEAT_ANIMATION */ drum_studio_common_beat_animation,
    /* DISPLAY_TEXT   */ drum_studio_common_display_text,
    /* INIT_TUTORIAL  */ drum_studio_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

extern void func_08029178();
extern void func_08029b8c();
extern void func_08027728();
extern void func_08027744();
extern void func_08027760();
extern void func_0802777c();
extern void func_080277a0();
extern void func_080277b8();
extern void drum_lessons_set_dialogue();
extern void func_08027888();
extern void func_080278d0();
extern void drum_lessons_show_dialogue();
extern void func_08029cec();
extern void func_08027bd8();
extern void func_08027c54();
extern void func_08027c90();
extern void func_080281e8();
extern void func_080281fc();

// [D_089e2e34] Engine Events
EngineEvent drum_studio_engine_events[] = {
    /* 0x00 */ drum_studio_init_script,
    /* 0x01 */ func_080295d4,
    /* 0x02 */ func_08029178,
    /* 0x03 */ drum_studio_event_start_monitor,
    /* 0x04 */ drum_studio_event_stop_monitor,
    /* 0x05 */ drum_studio_show_save_options,
    /* 0x06 */ func_08029b8c,
    /* 0x07 */ func_08027728,
    /* 0x08 */ func_08027744,
    /* 0x09 */ func_08027760,
    /* 0x0A */ func_0802777c,
    /* 0x0B */ func_080277a0,
    /* 0x0C */ func_080277b8,
    /* 0x0D */ drum_lessons_set_dialogue,
    /* 0x0E */ func_08027888,
    /* 0x0F */ func_080278d0,
    /* 0x10 */ drum_lessons_show_dialogue,
    /* 0x11 */ func_08027f70,
    /* 0x12 */ drum_lessons_set_teacher_expression,
    /* 0x13 */ func_08029cec,
    /* 0x14 */ drum_lessons_get_score,
    /* 0x15 */ func_08027bd8,
    /* 0x16 */ func_08027c54,
    /* 0x17 */ func_08027c90,
    /* 0x18 */ func_080281e8,
    /* 0x19 */ func_080281fc,
    /* 0x1A */ drum_studio_engine_event_stub
};

// [D_089e2ea0] Drum Lessons Game Engine
struct GameEngine drum_studio_engine = {
    /* Size in Memory */ sizeof(struct DrumStudioEngineData),
    /* Start Engine   */ drum_studio_engine_start,
    /* Update Engine  */ drum_studio_engine_update,
    /* Stop Engine    */ drum_studio_engine_stop,
    /* Cue Index      */ drum_studio_cue_index,
    /* Common Events  */ drum_studio_common_events,
    /* Engine Events  */ drum_studio_engine_events,
    /* Input Event    */ drum_studio_input_event
};


  //  //  //  MISCELLANEOUS DATA  //  //  //


// [D_089e2ec0] ?
s32 D_089e2ec0[] = {
    /* 0x00 */ -0x80,
    /* 0x01 */ -0x80,
    /* 0x02 */ -0x100,
    /* 0x03 */ -0x200,
    /* 0x04 */ -0x400,
};
