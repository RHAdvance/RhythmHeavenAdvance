#include "engines/karate_man.h"


  //  //  //  GAME ENGINE DATA  //  //  //


extern const u8 karate_face_maps_bin[]; // BG Map (Face)

extern struct CueDefinition *karate_cue_index[];

// [D_089df010] Common Events
EngineEvent karate_common_events[] = {
    /* BEAT_ANIMATION */ karate_common_beat_animation,
    /* DISPLAY_TEXT   */ karate_common_display_text,
    /* INIT_TUTORIAL  */ karate_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089df020] Engine Events
EngineEvent karate_engine_events[] = {
    /* 0x00 */ karate_reset_bg_face,
    /* 0x01 */ karate_start_serious_mode_next_hit,
    /* 0x02 */ karate_stop_serious_mode_next_hit,
    /* 0x03 */ karate_tutorial_display_text,
    /* 0x04 */ karate_tutorial_wait_for_input,
    /* 0x05 */ karate_enable_flow,
    /* 0x06 */ karate_tutorial_loop_start,
    /* 0x07 */ karate_tutorial_loop_end,
    /* 0x08 */ karate_use_the_face
};

// [D_089df044] Karate Man Game Engine
struct GameEngine karate_man_engine = {
    /* Size in Memory */ sizeof(struct KarateManEngineData),
    /* Start Engine   */ karate_engine_start,
    /* Update Engine  */ karate_engine_update,
    /* Stop Engine    */ karate_engine_stop,
    /* Cue Index      */ karate_cue_index,
    /* Common Events  */ karate_common_events,
    /* Engine Events  */ karate_engine_events,
    /* Input Event    */ karate_input_event
};


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089df064] Buffered Textures List
struct CompressedData *karate_buffered_textures[] = {
    &karate_man_bg_tiles_unused_face_1,
    &karate_man_bg_tiles_unused_face_2,
    &karate_man_bg_tiles_unused_face_3,
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089df074] Graphics Table (Faces)
struct GraphicsTable karate_man_faces_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &karate_man_bg_tiles_unused_face_1,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ karate_face_maps_bin,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ 0x500
    },
    /* BG Tileset */ {
        /* Src.  */ &karate_man_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &karate_man_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &karate_man_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ karate_man_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Palette */ {
        /* Src.  */ karate_man_pal,
        /* Dest. */ BG_PALETTE_BUFFER(12),
        /* Size  */ 0x80
    },
    /* OBJ Palette */ {
        /* Src.  */ karate_man_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089df0e0] Graphics Table (Remix)
struct GraphicsTable karate_man_remix_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &karate_man_bg_tiles_serious,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &karate_man_bg_map_serious,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Tileset */ {
        /* Src.  */ &karate_man_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &karate_man_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &karate_man_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ karate_man_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ karate_man_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089df140] Graphics Table (Karate Man 2)
struct GraphicsTable karate_man_2_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &karate_man_bg_tiles_unused_face_1,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ karate_face_maps_bin,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ 0x500
    },
    /* BG Tileset */ {
        /* Src.  */ &karate_man_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &karate_man_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &karate_man_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ karate_man_2_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Palette */ {
        /* Src.  */ karate_man_2_pal,
        /* Dest. */ BG_PALETTE_BUFFER(12),
        /* Size  */ 0x80
    },
    /* OBJ Palette */ {
        /* Src.  */ karate_man_2_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089df0e0] Graphics Table (Remix)
struct GraphicsTable karate_man_extra_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &karate_man_bg_tiles_serious,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &karate_man_bg_map_serious,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Tileset */ {
        /* Src.  */ &karate_man_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &karate_man_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &karate_man_extra_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ karate_man_extra_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ karate_man_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089df1ac] Graphics Table Index
struct GraphicsTable *karate_gfx_tables[] = {
    /* 0x00 */ karate_man_remix_gfx_table,
    /* 0x01 */ karate_man_faces_gfx_table,
    /* 0x02 */ karate_man_remix_gfx_table,
    /* 0x03 */ karate_man_2_gfx_table,
    /* 0x04 */ karate_man_extra_gfx_table,
};

// [D_089df1bc] BG Face Textures
struct CompressedData *karate_bg_face_textures[] = {
    &karate_man_bg_tiles_unused_face_1,
    &karate_man_bg_tiles_unused_face_2,
    &karate_man_bg_tiles_unused_face_3
};


  //  //  //  CUE DATA  //  //  //


// [D_089df1c8] Cue 00 (Pot)
struct CueDefinition karate_cue_pot = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct KarateManCue),
    /* Func. Spawn     */ karate_cue_spawn,
    /* Spawn Parameter */ KARATE_OBJECT_POT,
    /* Func. Update    */ karate_cue_update,
    /* Func. Despawn   */ karate_cue_despawn,
    /* Func. Hit       */ karate_cue_hit,
    /* Func. Barely    */ karate_cue_barely,
    /* Func. Miss      */ karate_cue_miss,
    /* SFX Spawn       */ &s_f_boxing_fly_nml_seqData,
    /* SFX Hit         */ &s_f_boxing_just_hati_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089df208] Cue 02 (Pot, Low Leniency)
struct CueDefinition karate_cue_pot_strict = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x01, 0x01,
    /* Barely Window   */ -0x03, 0x03,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct KarateManCue),
    /* Func. Spawn     */ karate_cue_spawn,
    /* Spawn Parameter */ KARATE_OBJECT_POT,
    /* Func. Update    */ karate_cue_update,
    /* Func. Despawn   */ karate_cue_despawn,
    /* Func. Hit       */ karate_cue_hit,
    /* Func. Barely    */ karate_cue_barely,
    /* Func. Miss      */ karate_cue_miss,
    /* SFX Spawn       */ &s_f_boxing_fly_nml_seqData,
    /* SFX Hit         */ &s_f_boxing_just_hati_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089df248] Cue 04 (Rock)
struct CueDefinition karate_cue_rock = {
    /* Unknown Param.  */ 1,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct KarateManCue),
    /* Func. Spawn     */ karate_cue_spawn,
    /* Spawn Parameter */ KARATE_OBJECT_ROCK,
    /* Func. Update    */ karate_cue_update,
    /* Func. Despawn   */ karate_cue_despawn,
    /* Func. Hit       */ karate_cue_hit,
    /* Func. Barely    */ karate_cue_barely,
    /* Func. Miss      */ karate_cue_miss,
    /* SFX Spawn       */ &s_f_boxing_fly_nml_seqData,
    /* SFX Hit         */ &s_f_boxing_just_rock_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089df288] Cue 01 (Soccer Ball)
struct CueDefinition karate_cue_soccer_ball = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct KarateManCue),
    /* Func. Spawn     */ karate_cue_spawn,
    /* Spawn Parameter */ KARATE_OBJECT_SOCCER_BALL,
    /* Func. Update    */ karate_cue_update,
    /* Func. Despawn   */ karate_cue_despawn,
    /* Func. Hit       */ karate_cue_hit,
    /* Func. Barely    */ karate_cue_barely,
    /* Func. Miss      */ karate_cue_miss,
    /* SFX Spawn       */ &s_f_boxing_fly_nml_seqData,
    /* SFX Hit         */ &s_f_boxing_just_ball_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089df2c8] Cue 05 (Bomb)
struct CueDefinition karate_cue_bomb = {
    /* Unknown Param.  */ 1,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct KarateManCue),
    /* Func. Spawn     */ karate_cue_spawn,
    /* Spawn Parameter */ KARATE_OBJECT_BOMB,
    /* Func. Update    */ karate_cue_update,
    /* Func. Despawn   */ karate_cue_despawn,
    /* Func. Hit       */ karate_cue_hit,
    /* Func. Barely    */ karate_cue_barely,
    /* Func. Miss      */ karate_cue_miss,
    /* SFX Spawn       */ &s_f_boxing_fly_nml_seqData,
    /* SFX Hit         */ &s_f_boxing_just_bomb_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089df308] Cue 06 (Light Bulb)
struct CueDefinition karate_cue_light_bulb = {
    /* Unknown Param.  */ 2,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct KarateManCue),
    /* Func. Spawn     */ karate_cue_spawn,
    /* Spawn Parameter */ KARATE_OBJECT_LIGHT_BULB,
    /* Func. Update    */ karate_cue_update,
    /* Func. Despawn   */ karate_cue_despawn,
    /* Func. Hit       */ karate_cue_hit,
    /* Func. Barely    */ karate_cue_barely,
    /* Func. Miss      */ karate_cue_miss,
    /* SFX Spawn       */ &s_f_boxing_fly_nml_seqData,
    /* SFX Hit         */ &s_f_boxing_just_light_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089df348] Cue Definition Index
struct CueDefinition *karate_cue_index[] = {
    /* 0x00 */ &karate_cue_pot,
    /* 0x01 */ &karate_cue_soccer_ball,
    /* 0x02 */ &karate_cue_pot_strict,
    /* 0x03 */ NULL,
    /* 0x04 */ &karate_cue_rock,
    /* 0x05 */ &karate_cue_bomb,
    /* 0x06 */ NULL,
    /* 0x07 */ NULL,
    /* 0x08 */ &karate_cue_light_bulb,
    /* 0x09 */ NULL,
    /* 0x0A */ NULL,
    /* 0x0B */ NULL,
    END_OF_CUE_INDEX
};


  //  //  //  MISCELLANEOUS DATA  //  //  //


// [D_089df37c] Flow Meter Palette IDs (Low Flow)
u8 karate_flow_palette_low[] = {
    5, -1
};

// [D_089df37e] Flow Meter Palette IDs (High Flow)
u8 karate_flow_palette_high[] = {
    6, 7, -1
};
