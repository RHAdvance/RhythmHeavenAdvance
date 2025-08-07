#include "engines/clappy_trio.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e4520] All Animations
struct Animation *clappy_trio_anim[][3] = {
    /* BEAT  */ { anim_clappy_trio_beat, anim_snappy_trio_beat, anim_clappy_trio_extra_beat },
    /* SMILE */ { anim_clappy_trio_smile, anim_snappy_trio_smile, anim_clappy_trio_extra_smile },
    /* GLARE */ { anim_clappy_trio_glare, anim_snappy_trio_glare, anim_clappy_trio_extra_glare },
    /* SMIRK */ { anim_clappy_trio_smirk, anim_snappy_trio_smirk, anim_clappy_trio_extra_smirk },
    /* CLAP  */ { anim_clappy_trio_clap, anim_snappy_trio_clap, anim_clappy_trio_extra_clap },
    /* YOU   */ { anim_clappy_trio_player_icon, anim_snappy_trio_player_icon, anim_clappy_trio_extra_player_icon },
    /* SIGN  */ { anim_clappy_trio_sign, anim_snappy_trio_sign, anim_clappy_trio_extra_sign },
    /* TEXT  */ { anim_clappy_trio_text_box, anim_snappy_trio_text_box, anim_clappy_trio_extra_text_box }
};

// [D_089e4560] Animation Table
struct Animation **clappy_trio_anim_table[] = {
    clappy_trio_anim[0],
    clappy_trio_anim[1],
    clappy_trio_anim[2],
    clappy_trio_anim[3],
    clappy_trio_anim[4],
    clappy_trio_anim[5],
    clappy_trio_anim[6],
    clappy_trio_anim[7]
};

// [D_089e4580] Buffered Textures List
struct CompressedData *clappy_trio_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e4584] Graphics Table (The Clappy Trio)
struct GraphicsTable clappy_trio_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &clappy_trio_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &clappy_trio_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &clappy_trio_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ clappy_trio_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ clappy_trio_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e45cc] Graphics Table (The Snappy Trio)
struct GraphicsTable snappy_trio_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &snappy_trio_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &snappy_trio_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &snappy_trio_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ snappy_trio_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ snappy_trio_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

struct GraphicsTable clappy_trio_extra_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &clappy_trio_extra_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &clappy_trio_extra_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &clappy_trio_extra_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ clappy_trio_extra_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ clappy_trio_extra_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e4614] Graphics Table Index
struct GraphicsTable *clappy_trio_gfx_tables[] = {
    /* 0x00 */ clappy_trio_gfx_table,
    /* 0x01 */ snappy_trio_gfx_table,
    /* 0x02 */ clappy_trio_extra_gfx_table,
};


  //  //  //  CUE DATA  //  //  //


// [D_089e461c] Cue 00 (1 Beat)
struct CueDefinition clappy_trio_cue_full_beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x28,
    /* Func. Spawn     */ clappy_trio_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ clappy_trio_cue_update,
    /* Func. Despawn   */ clappy_trio_cue_despawn,
    /* Func. Hit       */ clappy_trio_cue_hit,
    /* Func. Barely    */ clappy_trio_cue_barely,
    /* Func. Miss      */ clappy_trio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e465c] Cue 01 (0.5 Beats)
struct CueDefinition clappy_trio_cue_half_beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x28,
    /* Func. Spawn     */ clappy_trio_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ clappy_trio_cue_update,
    /* Func. Despawn   */ clappy_trio_cue_despawn,
    /* Func. Hit       */ clappy_trio_cue_hit,
    /* Func. Barely    */ clappy_trio_cue_barely,
    /* Func. Miss      */ clappy_trio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e469c] Cue 04 (1 Beat, Smile After)
struct CueDefinition clappy_trio_cue_full_beat_smile_after = {
    /* Unknown Param.  */ 1,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x28,
    /* Func. Spawn     */ clappy_trio_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ clappy_trio_cue_update,
    /* Func. Despawn   */ clappy_trio_cue_despawn,
    /* Func. Hit       */ clappy_trio_cue_hit,
    /* Func. Barely    */ clappy_trio_cue_barely,
    /* Func. Miss      */ clappy_trio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e46dc] Cue 05 (0.5 Beats, Smile After)
struct CueDefinition clappy_trio_cue_half_beat_smile_after = {
    /* Unknown Param.  */ 1,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x28,
    /* Func. Spawn     */ clappy_trio_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ clappy_trio_cue_update,
    /* Func. Despawn   */ clappy_trio_cue_despawn,
    /* Func. Hit       */ clappy_trio_cue_hit,
    /* Func. Barely    */ clappy_trio_cue_barely,
    /* Func. Miss      */ clappy_trio_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e471c] Cue Definition Index
struct CueDefinition *clappy_trio_cue_index[] = {
    /* 0x00 */ &clappy_trio_cue_full_beat,
    /* 0x01 */ &clappy_trio_cue_half_beat,
    /* 0x02 */ NULL,
    /* 0x03 */ NULL,
    /* 0x04 */ &clappy_trio_cue_full_beat_smile_after,
    /* 0x05 */ &clappy_trio_cue_half_beat_smile_after,
    /* 0x06 */ NULL,
    /* 0x07 */ NULL,
    /* 0x08 */ NULL,
    /* 0x09 */ NULL,
    /* 0x0A */ NULL,
    /* 0x0B */ NULL,
    END_OF_CUE_INDEX
};


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e4750] Common Events
EngineEvent clappy_trio_common_events[] = {
    /* BEAT_ANIMATION */ clappy_trio_common_beat_animation,
    /* DISPLAY_TEXT   */ clappy_trio_common_display_text,
    /* INIT_TUTORIAL  */ clappy_trio_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e4760] Engine Events
EngineEvent clappy_trio_engine_events[] = {
    /* 0x00 */ clappy_trio_crouch,
    /* 0x01 */ clappy_trio_crouch_smirk,
    /* 0x02 */ clappy_trio_manual_clap,
    /* 0x03 */ clappy_trio_enable_grayscale,
    /* 0x04 */ clappy_trio_set_clap_volume,
    /* 0x05 */ clappy_trio_textbox_shown
};

// [D_089e4778] The Clappy Trio Game Engine
struct GameEngine clappy_trio_engine = {
    /* Size in Memory */ sizeof(struct ClappyTrioEngineData),
    /* Start Engine   */ clappy_trio_engine_start,
    /* Update Engine  */ clappy_trio_engine_update,
    /* Stop Engine    */ clappy_trio_engine_stop,
    /* Cue Index      */ clappy_trio_cue_index,
    /* Common Events  */ clappy_trio_common_events,
    /* Engine Events  */ clappy_trio_engine_events,
    /* Input Event    */ clappy_trio_input_event
};
