#include "engines/fireworks.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e4214] Buffered Textures List
struct CompressedData *fireworks_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e4218] Graphics Table (Fireworks)
struct GraphicsTable fireworks_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &fireworks_obj,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &fireworks_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &fireworks_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ fireworks_obj_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ fireworks_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[8],
        /* Dest. */ OBJ_PALETTE_BUFFER(11.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[7],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[13],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e4284] Graphics Table (Remix 5 [1])
struct GraphicsTable fireworks_remix_5_gfx_table_1[] = {
    /* BG Tileset */ {
        /* Src.  */ &fireworks_remix_5_bg_tiles_1,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &fireworks_remix_5_bg_map_1,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &fireworks_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ fireworks_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ fireworks_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[7],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e42d8] Graphics Table (Remix 5 [2])
struct GraphicsTable fireworks_remix_5_gfx_table_2[] = {
    /* BG Tileset */ {
        /* Src.  */ &fireworks_remix_5_bg_tiles_2,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &fireworks_remix_5_bg_map_2,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &fireworks_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ fireworks_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ fireworks_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[7],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e432c] Graphics Table (Remix 5 [3])
struct GraphicsTable fireworks_remix_5_gfx_table_3[] = {
    /* BG Tileset */ {
        /* Src.  */ &fireworks_remix_5_bg_tiles_3,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &fireworks_remix_5_bg_map_3,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &fireworks_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ fireworks_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ fireworks_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[7],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e4380] Graphics Table (Remix 5 [4])
struct GraphicsTable fireworks_remix_5_gfx_table_4[] = {
    /* BG Tileset */ {
        /* Src.  */ &fireworks_remix_5_bg_tiles_4,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &fireworks_remix_5_bg_map_4,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &fireworks_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ fireworks_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ fireworks_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[7],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e43d4] Graphics Table Index
struct GraphicsTable *fireworks_gfx_tables[] = {
    /* 0x00 */ fireworks_gfx_table,
    /* 0x01 */ fireworks_remix_5_gfx_table_1,
    /* 0x02 */ fireworks_remix_5_gfx_table_2,
    /* 0x03 */ fireworks_remix_5_gfx_table_3,
    /* 0x04 */ fireworks_remix_5_gfx_table_4
};


  //  //  //  CUE DATA  //  //  //


// [D_089e43e8] Firework Durations
u16 fireworks_cue_durations[] = {
    /* SPIRIT SPARKLER */ 0x30,
    /* NORMAL FIREWORK */ 0x60,
    /* TAIKO BOMBER    */ 0x48
};

// [D_089e43f0] Cue 00 (Spirit Sparkler)
struct CueDefinition fireworks_cue_spirit_sparkler = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct FireworksCue),
    /* Func. Spawn     */ fireworks_cue_spawn,
    /* Spawn Parameter */ FIREWORKS_CUE_TYPE_SPIRIT_SPARKLER,
    /* Func. Update    */ fireworks_cue_update,
    /* Func. Despawn   */ fireworks_cue_despawn,
    /* Func. Hit       */ fireworks_cue_hit,
    /* Func. Barely    */ fireworks_cue_barely,
    /* Func. Miss      */ fireworks_cue_miss,
    /* SFX Spawn       */ &s_hanabi_utiage_seqData,
    /* SFX Hit         */ &s_hanabi_don_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e4430] Cue 01 (Normal Firework)
struct CueDefinition fireworks_cue_normal = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x48,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct FireworksCue),
    /* Func. Spawn     */ fireworks_cue_spawn,
    /* Spawn Parameter */ FIREWORKS_CUE_TYPE_NORMAL_FIREWORK,
    /* Func. Update    */ fireworks_cue_update,
    /* Func. Despawn   */ fireworks_cue_despawn,
    /* Func. Hit       */ fireworks_cue_hit,
    /* Func. Barely    */ fireworks_cue_barely,
    /* Func. Miss      */ fireworks_cue_miss,
    /* SFX Spawn       */ &s_hanabi_utiage_seqData,
    /* SFX Hit         */ &s_hanabi_don_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e4470] Cue 04 (Hawfinch Taiko Bomber)
struct CueDefinition fireworks_cue_taiko_bomber = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x30,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct FireworksCue),
    /* Func. Spawn     */ fireworks_cue_spawn,
    /* Spawn Parameter */ FIREWORKS_CUE_TYPE_HAWFINCH_TAIKO_BOMBER,
    /* Func. Update    */ fireworks_cue_update,
    /* Func. Despawn   */ fireworks_cue_despawn,
    /* Func. Hit       */ fireworks_cue_hit,
    /* Func. Barely    */ fireworks_cue_barely,
    /* Func. Miss      */ fireworks_cue_miss,
    /* SFX Spawn       */ &s_hanabi_utiage_v_seqData,
    /* SFX Hit         */ &s_hanabi_pon_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e44b0] Cue Definition Index
struct CueDefinition *fireworks_cue_index[] = {
    /* 0x00 */ &fireworks_cue_spirit_sparkler,
    /* 0x01 */ &fireworks_cue_normal,
    /* 0x02 */ NULL,
    /* 0x03 */ NULL,
    /* 0x04 */ &fireworks_cue_taiko_bomber,
    /* 0x05 */ NULL,
    /* 0x06 */ NULL,
    /* 0x07 */ NULL,
    /* 0x08 */ NULL,
    /* 0x09 */ NULL,
    /* 0x0A */ NULL,
    /* 0x0B */ NULL,
    END_OF_CUE_INDEX
};


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e44e4] Common Events
EngineEvent fireworks_common_events[] = {
    /* BEAT_ANIMATION */ fireworks_common_beat_animation,
    /* DISPLAY_TEXT   */ fireworks_common_display_text,
    /* INIT_TUTORIAL  */ fireworks_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e44f4] Engine Events
EngineEvent fireworks_engine_events[] = {
    /* 0x00 */ fireworks_set_pattern_mode,
    /* 0x01 */ fireworks_play_sound,
    /* 0x02 */ fireworks_set_pattern
};

// [D_089e4500] Fireworks Game Engine
struct GameEngine fireworks_engine = {
    /* Size in Memory */ sizeof(struct FireworksEngineData),
    /* Start Engine   */ fireworks_engine_start,
    /* Update Engine  */ fireworks_engine_update,
    /* Stop Engine    */ fireworks_engine_stop,
    /* Cue Index      */ fireworks_cue_index,
    /* Common Events  */ fireworks_common_events,
    /* Engine Events  */ fireworks_engine_events,
    /* Input Event    */ fireworks_input_event
};

// [D_0805a3d0] Default Tutorial Text
const char D_0805a3d0[] = "";


// [D_0805a3d4] Unique 3-Colour Patterns
const struct FireworksPatternColours fireworks_particle_combinations[] = {
    /* RGB */ {
        /* INNER  */ FIREWORKS_PARTICLE_RED,
        /* MIDDLE */ FIREWORKS_PARTICLE_GREEN,
        /* OUTER  */ FIREWORKS_PARTICLE_BLUE
    },
    /* RBG */ {
        /* INNER  */ FIREWORKS_PARTICLE_RED,
        /* MIDDLE */ FIREWORKS_PARTICLE_BLUE,
        /* OUTER  */ FIREWORKS_PARTICLE_GREEN
    },
    /* GRB */ {
        /* INNER  */ FIREWORKS_PARTICLE_GREEN,
        /* MIDDLE */ FIREWORKS_PARTICLE_RED,
        /* OUTER  */ FIREWORKS_PARTICLE_BLUE
    },
    /* GBR */ {
        /* INNER  */ FIREWORKS_PARTICLE_GREEN,
        /* MIDDLE */ FIREWORKS_PARTICLE_BLUE,
        /* OUTER  */ FIREWORKS_PARTICLE_RED
    },
    /* BRG */ {
        /* INNER  */ FIREWORKS_PARTICLE_BLUE,
        /* MIDDLE */ FIREWORKS_PARTICLE_RED,
        /* OUTER  */ FIREWORKS_PARTICLE_GREEN
    },
    /* BGR */ {
        /* INNER  */ FIREWORKS_PARTICLE_BLUE,
        /* MIDDLE */ FIREWORKS_PARTICLE_GREEN,
        /* OUTER  */ FIREWORKS_PARTICLE_RED
    }
};


// [D_0805a41c] Particle Durations
const s32 fireworks_particle_durations[] = {
    /* RED   */ 0x08,
    /* GREEN */ 0x10,
    /* BLUE  */ 0x08,
    /* MULTI */ 0x18
};


// [D_0805a42c] Particle Trajectory for ♂ Pattern (Unused)
const struct FireworksParticleTrajectory fireworks_mars_pattern[] = {
    /* 00 */ {   0,   0 },
    /* 01 */ { 224,  64 },
    /* 02 */ { 224, 128 },
    /* 03 */ { 224, 192 },
    /* 04 */ { 224, 256 },
    /* 05 */ { 224, 320 },
    /* 06 */ { 224, 384 },
    /* 07 */ { 192, 320 },
    /* 08 */ { 200, 336 },
    /* 09 */ { 208, 352 },
    /* 10 */ { 216, 368 },
    /* 11 */ {   0, 320 },
    /* 12 */ { 248, 336 },
    /* 13 */ { 240, 352 },
    /* 14 */ { 232, 368 },
    /* 15 */ {  68, 224 },
    /* 16 */ {  70, 160 },
    /* 17 */ {  96,  96 },
    /* 18 */ { 124, 160 },
    /* 19 */ { 128, 256 },
    /* 20 */ { 124, 320 },
    /* 21 */ { 120, 384 },
    /* 22 */ { 116, 448 },
    /* 23 */ { 112, 512 },
    /* 24 */ { 104, 576 },
    /* 25 */ {  96, 608 },
    /* 26 */ {  88, 576 },
    /* 27 */ {  80, 512 },
    /* 28 */ {  76, 448 },
    /* 29 */ {  72, 384 },
    /* 30 */ {  68, 320 }
};


// [D_0805a524] Pattern Sequence for Fireworks 1
const s32 fireworks_1_pattern_sequence[] = {
    FIREWORKS_PATTERN_L3,
    FIREWORKS_PATTERN_C3,
    FIREWORKS_PATTERN_R3,
    FIREWORKS_PATTERN_TAIKO_BOMBER,

    FIREWORKS_PATTERN_L3,
    FIREWORKS_PATTERN_C3,
    FIREWORKS_PATTERN_R3,
    FIREWORKS_PATTERN_TAIKO_BOMBER,

    FIREWORKS_PATTERN_SP_STAR,
    FIREWORKS_PATTERN_TAIKO_BOMBER,
    FIREWORKS_PATTERN_SP_CIRCLE,
    FIREWORKS_PATTERN_TAIKO_BOMBER,

    FIREWORKS_PATTERN_SP_SPIRAL,
    FIREWORKS_PATTERN_TAIKO_BOMBER,
    FIREWORKS_PATTERN_L3, FIREWORKS_PATTERN_R3,
    FIREWORKS_PATTERN_L3, FIREWORKS_PATTERN_TAIKO_BOMBER, FIREWORKS_PATTERN_R3,

    FIREWORKS_PATTERN_TAIKO_BOMBER,
    FIREWORKS_PATTERN_TAIKO_BOMBER,
    FIREWORKS_PATTERN_SP_SMILE,
    FIREWORKS_PATTERN_TAIKO_BOMBER,

    FIREWORKS_PATTERN_SP_STAR, FIREWORKS_PATTERN_L3,
    FIREWORKS_PATTERN_SP_STAR, FIREWORKS_PATTERN_R3,
    FIREWORKS_PATTERN_SP_STAR, FIREWORKS_PATTERN_C3,
    FIREWORKS_PATTERN_TAIKO_BOMBER,

    FIREWORKS_PATTERN_L3,
    FIREWORKS_PATTERN_C3,
    FIREWORKS_PATTERN_R3,
    FIREWORKS_PATTERN_TAIKO_BOMBER,

    FIREWORKS_PATTERN_SP_STAR, FIREWORKS_PATTERN_L3,
    FIREWORKS_PATTERN_SP_STAR, FIREWORKS_PATTERN_R3,
    FIREWORKS_PATTERN_LL2, FIREWORKS_PATTERN_RR2,
    FIREWORKS_PATTERN_L3, FIREWORKS_PATTERN_TAIKO_BOMBER, FIREWORKS_PATTERN_R3
};

