#include "engines/spaceball.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089de93c] Buffered Textures List
struct CompressedData *spaceball_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};


// [D_089de940] Graphics Table
struct GraphicsTable spaceball_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &spaceball_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &spaceball_bg_map,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &spaceball_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ spaceball_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ spaceball_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

struct GraphicsTable spaceball_extra_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &spaceball_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &spaceball_bg_map,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &spaceball_extra_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ spaceball_extra_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ spaceball_extra_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// i can just make my own table mwehehehe >:) i got freewill
// i don't have funny moth facts unfortunately
// writting this comment is a waste of time
// but i don't care, i like to write comments
// especially when they serve absolutely no purpose
// not like anyone read those anyway
// yeah
// writting code is fun but you do get a bit lonely
// i just realized this is going to be seen when implement tempo up
// yeah right, just replace the second table with a tempo up table
// that is made like the one above (the fact that the bg is 8bpp doesn't matter)
struct GraphicsTable *spaceball_gfx_tables[] = {
    /* 0x00 */ spaceball_gfx_table,
    /* 0x01 */ spaceball_extra_gfx_table
};

struct Animation **spaceball_anim_table_batter_close_tables[] = {
    /* 0x00 */ spaceball_anim_table_batter_close,
    /* 0x01 */ spaceball_extra_anim_table_batter_close
};

struct Animation **spaceball_anim_table_batter_far_tables[] = {
    /* 0x00 */ spaceball_anim_table_batter_far,
    /* 0x01 */ spaceball_extra_anim_table_batter_far
};

struct Animation **spaceball_anim_table_ball_tables[] = {
    /* 0x00 */ spaceball_anim_table_ball,
    /* 0x01 */ spaceball_extra_anim_table_ball
};

// [D_089de988] Batter Animations (Close)
struct Animation *spaceball_anim_table_batter_close[] = {
    anim_spaceball_batter_green,
    anim_spaceball_batter_red,
    anim_spaceball_batter_pink
};


// [D_089de994] Batter Animations (Far)
struct Animation *spaceball_anim_table_batter_far[] = {
    anim_spaceball_batter_green_far,
    anim_spaceball_batter_red_far,
    anim_spaceball_batter_pink_far
};

// [D_089de9a0] Ball Animations
struct Animation *spaceball_anim_table_ball[] = {
    anim_spaceball_baseball,
    anim_spaceball_rice_ball,
    anim_spaceball_star_ball
};


struct Animation *spaceball_extra_anim_table_batter_close[] = {
    anim_spaceball_extra_batter_green,
    anim_spaceball_extra_batter_red,
    anim_spaceball_extra_batter_pink
};


// [D_089de994] Batter Animations (Far)
struct Animation *spaceball_extra_anim_table_batter_far[] = {
    anim_spaceball_extra_batter_green_far,
    anim_spaceball_extra_batter_red_far,
    anim_spaceball_extra_batter_pink_far
};

struct Animation *spaceball_extra_anim_table_ball[] = {
    anim_spaceball_extra_baseball,
    anim_spaceball_extra_rice_ball,
    anim_spaceball_extra_star_ball
};

  //  //  //  CUE DATA  //  //  //


// [D_089de9ac] Cue 00 (0.5 Beats)
struct CueDefinition spaceball_cue_low_fast = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct SpaceballCue),
    /* Func. Spawn     */ spaceball_cue_spawn,
    /* Spawn Parameter */ 0xC,
    /* Func. Update    */ spaceball_cue_update,
    /* Func. Despawn   */ spaceball_cue_despawn,
    /* Func. Hit       */ spaceball_cue_hit,
    /* Func. Barely    */ spaceball_cue_barely,
    /* Func. Miss      */ spaceball_cue_miss,
    /* SFX Spawn       */ &s_f_dummy_vol0_seqData,
    /* SFX Hit         */ &s_f_dummy_vol0_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089de9ec] Cue 01 (1 Beat)
struct CueDefinition spaceball_cue_low = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct SpaceballCue),
    /* Func. Spawn     */ spaceball_cue_spawn,
    /* Spawn Parameter */ 0x18,
    /* Func. Update    */ spaceball_cue_update,
    /* Func. Despawn   */ spaceball_cue_despawn,
    /* Func. Hit       */ spaceball_cue_hit,
    /* Func. Barely    */ spaceball_cue_barely,
    /* Func. Miss      */ spaceball_cue_miss,
    /* SFX Spawn       */ &s_batter_mit_seqData,
    /* SFX Hit         */ &s_batter_hit_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089dea2c] Cue 02 (2 Beats)
struct CueDefinition spaceball_cue_high = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x30,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct SpaceballCue),
    /* Func. Spawn     */ spaceball_cue_spawn,
    /* Spawn Parameter */ 0x30,
    /* Func. Update    */ spaceball_cue_update,
    /* Func. Despawn   */ spaceball_cue_despawn,
    /* Func. Hit       */ spaceball_cue_hit,
    /* Func. Barely    */ spaceball_cue_barely,
    /* Func. Miss      */ spaceball_cue_miss,
    /* SFX Spawn       */ &s_f_batter_ball_high_seqData,
    /* SFX Hit         */ &s_batter_hit_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089dea6c] Cue 03 (1.5 Beats)
struct CueDefinition spaceball_cue_high_fast = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x24,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct SpaceballCue),
    /* Func. Spawn     */ spaceball_cue_spawn,
    /* Spawn Parameter */ 0x24,
    /* Func. Update    */ spaceball_cue_update,
    /* Func. Despawn   */ spaceball_cue_despawn,
    /* Func. Hit       */ spaceball_cue_hit,
    /* Func. Barely    */ spaceball_cue_barely,
    /* Func. Miss      */ spaceball_cue_miss,
    /* SFX Spawn       */ &s_f_batter_ball_high_seqData,
    /* SFX Hit         */ &s_batter_hit_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089deaac] Cue Definition Index
struct CueDefinition *spaceball_cue_index[] = {
    /* 0x00 */ &spaceball_cue_low_fast,
    /* 0x01 */ &spaceball_cue_low,
    /* 0x02 */ &spaceball_cue_high,
    /* 0x03 */ &spaceball_cue_high_fast,
    /* 0x04 */ NULL,
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


// [D_089deae0] Common Events
EngineEvent spaceball_common_events[] = {
    /* BEAT_ANIMATION */ spaceball_common_beat_animation,
    /* DISPLAY_TEXT   */ spaceball_common_display_text,
    /* INIT_TUTORIAL  */ // None
    END_OF_COMMON_EVENT_LIST
};

// [D_089deaec] Engine Events
EngineEvent spaceball_engine_events[] = {
    /* 0x00 */ spaceball_prepare_pitcher,
    /* 0x01 */ spaceball_loop_exit_condition,
    /* 0x02 */ spaceball_set_camera_zoom,
    /* 0x03 */ spaceball_set_batter_type,
    /* 0x04 */ spaceball_open_ufo,
    /* 0x05 */ spaceball_set_ball_type,
    /* 0x06 */ spaceball_engine_event_stub
};

// [D_089deb08] Spaceball Game Engine
struct GameEngine spaceball_engine = {
    /* Size in Memory */ sizeof(struct SpaceballEngineData),
    /* Start Engine   */ spaceball_engine_start,
    /* Update Engine  */ spaceball_engine_update,
    /* Stop Engine    */ spaceball_engine_stop,
    /* Cue Index      */ spaceball_cue_index,
    /* Common Events  */ spaceball_common_events,
    /* Engine Events  */ spaceball_engine_events,
    /* Input Event    */ spaceball_input_event
};
