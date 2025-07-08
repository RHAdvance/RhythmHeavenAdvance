#include "engines/rhythm_tweezers.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e3d98] Vegetable Face Animations
struct Animation *rhythm_tweezers_veg_face_anim[] = {
    /* 0x00 */ anim_veg_face_onion,
    /* 0x01 */ anim_veg_face_turnip,
    /* 0x02 */ anim_veg_face_potato
};

// [D_089e3da4] Vegetable BG Maps
struct CompressedData *rhythm_tweezers_veg_bg_maps[] = {
    &rhythm_tweezers_bg_map_onion,
    &rhythm_tweezers_bg_map_turnip,
    &rhythm_tweezers_bg_map_potato
};

struct CompressedData *rhythm_tweezers_extra_veg_bg_maps[] = {
    &rhythm_tweezers_extra_bg_map_pumpkin,
    &rhythm_tweezers_extra_bg_map_sweet_potato,
    &rhythm_tweezers_extra_bg_map_watermelon
};

// [D_089e3db0] Buffered Textures List
struct CompressedData *rhythm_tweezers_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e3db4] Graphics Table (Rhythm Tweezers - Onion)
struct GraphicsTable rhythm_tweezers_1_onion_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_bg_map_onion,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e3e14] Graphics Table (Rhythm Tweezers - Turnip)
struct GraphicsTable rhythm_tweezers_1_turnip_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_bg_map_turnip,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e3e74] Graphics Table (Rhythm Tweezers - Potato)
struct GraphicsTable rhythm_tweezers_1_potato_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_bg_map_potato,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e3ed4] Graphics Table (Rhythm Tweezers 2 - Onion)
struct GraphicsTable rhythm_tweezers_2_onion_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_bg_map_onion,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_2_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_2_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e3f34] Graphics Table (Rhythm Tweezers 2 - Turnip)
struct GraphicsTable rhythm_tweezers_2_turnip_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_bg_map_turnip,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_2_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_2_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e3f94] Graphics Table (Rhythm Tweezers 2 - Potato)
struct GraphicsTable rhythm_tweezers_2_potato_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_bg_map_potato,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_2_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_2_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

/*
extern struct CompressedData rhythm_tweezers_extra_bg_map_pumpkin; // BG Map - Pumpkin
extern struct CompressedData rhythm_tweezers_extra_bg_map_sweet_potato; // BG Map - Sweet Potato
extern struct CompressedData rhythm_tweezers_extra_bg_map_watermelon; // BG Map - Watermelon
*/

// Graphics Table (Rhythm Tweezers Extra - Pumpkin)
struct GraphicsTable rhythm_tweezers_extra_pumpkin_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_extra_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_extra_bg_map_pumpkin,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_extra_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// Graphics Table (Rhythm Tweezers Extra - Sweet Potato)
struct GraphicsTable rhythm_tweezers_extra_sweet_potato_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_extra_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_extra_bg_map_sweet_potato,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_extra_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// Graphics Table (Rhythm Tweezers Extra - Watermelon)
struct GraphicsTable rhythm_tweezers_extra_watermelon_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_extra_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_extra_bg_map_watermelon,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_extra_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_no_peeking_sign_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e3ff4] Graphics Table Index
struct GraphicsTable *rhythm_tweezers_gfx_tables[] = {
    /* 0x00 */ rhythm_tweezers_1_onion_gfx_table,
    /* 0x01 */ rhythm_tweezers_1_turnip_gfx_table,
    /* 0x02 */ rhythm_tweezers_1_potato_gfx_table,
    /* 0x03 */ rhythm_tweezers_2_onion_gfx_table,
    /* 0x04 */ rhythm_tweezers_2_turnip_gfx_table,
    /* 0x05 */ rhythm_tweezers_2_potato_gfx_table,
    /* 0x06 */ rhythm_tweezers_extra_pumpkin_table,
    /* 0x07 */ rhythm_tweezers_extra_sweet_potato_table,
    /* 0x08 */ rhythm_tweezers_extra_watermelon_table,
};


  //  //  //  CUE DATA  //  //  //


// [D_089e400c] Cue 00 (Short Hair, 4 Beats)
struct CueDefinition rhythm_tweezers_cue_short_4beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0x60,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct RhythmTweezersCue),
    /* Func. Spawn     */ rhythm_tweezers_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ rhythm_tweezers_cue_update_short,
    /* Func. Despawn   */ rhythm_tweezers_cue_despawn,
    /* Func. Hit       */ rhythm_tweezers_cue_hit_short,
    /* Func. Barely    */ rhythm_tweezers_cue_barely_short,
    /* Func. Miss      */ rhythm_tweezers_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_datumo_nuki_seqData,
    /* SFX Barely      */ &s_f_hair_kegire_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e404c] Cue 01 (Long Hair, 4 Beats)
struct CueDefinition rhythm_tweezers_cue_long_4beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0x60,
    /* Hit Window      */ -0x04, 0x04,
    /* Barely Window   */ -0x04, 0x04,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct RhythmTweezersCue),
    /* Func. Spawn     */ rhythm_tweezers_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ rhythm_tweezers_cue_update_long,
    /* Func. Despawn   */ rhythm_tweezers_cue_despawn,
    /* Func. Hit       */ rhythm_tweezers_cue_hit_long,
    /* Func. Barely    */ rhythm_tweezers_cue_hit_long,
    /* Func. Miss      */ rhythm_tweezers_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_witch_furu_seqData,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e408c] Cue 02 (Short Hair, 4 Beats, Lenient)
struct CueDefinition rhythm_tweezers_cue_fast_4beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0x60,
    /* Hit Window      */ -0x04, 0x04,
    /* Barely Window   */ -0x06, 0x06,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct RhythmTweezersCue),
    /* Func. Spawn     */ rhythm_tweezers_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ rhythm_tweezers_cue_update_short,
    /* Func. Despawn   */ rhythm_tweezers_cue_despawn,
    /* Func. Hit       */ rhythm_tweezers_cue_hit_short,
    /* Func. Barely    */ rhythm_tweezers_cue_barely_short,
    /* Func. Miss      */ rhythm_tweezers_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_datumo_nuki_seqData,
    /* SFX Barely      */ &s_f_hair_kegire_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e40cc] Cue 04 (Short Hair, 8 Beats)
struct CueDefinition rhythm_tweezers_cue_short_8beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0xC0,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct RhythmTweezersCue),
    /* Func. Spawn     */ rhythm_tweezers_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ rhythm_tweezers_cue_update_short,
    /* Func. Despawn   */ rhythm_tweezers_cue_despawn,
    /* Func. Hit       */ rhythm_tweezers_cue_hit_short,
    /* Func. Barely    */ rhythm_tweezers_cue_barely_short,
    /* Func. Miss      */ rhythm_tweezers_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_datumo_nuki_seqData,
    /* SFX Barely      */ &s_f_hair_kegire_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e410c] Cue 05 (Long Hair, 8 Beats)
struct CueDefinition rhythm_tweezers_cue_long_8beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0xC0,
    /* Hit Window      */ -0x04, 0x04,
    /* Barely Window   */ -0x04, 0x04,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct RhythmTweezersCue),
    /* Func. Spawn     */ rhythm_tweezers_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ rhythm_tweezers_cue_update_long,
    /* Func. Despawn   */ rhythm_tweezers_cue_despawn,
    /* Func. Hit       */ rhythm_tweezers_cue_hit_long,
    /* Func. Barely    */ rhythm_tweezers_cue_hit_long,
    /* Func. Miss      */ rhythm_tweezers_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_witch_furu_seqData,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e414c] Cue 06 (Short Hair, 8 Beats, Lenient)
struct CueDefinition rhythm_tweezers_cue_fast_8beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0xC0,
    /* Hit Window      */ -0x04, 0x04,
    /* Barely Window   */ -0x06, 0x06,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct RhythmTweezersCue),
    /* Func. Spawn     */ rhythm_tweezers_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ rhythm_tweezers_cue_update_short,
    /* Func. Despawn   */ rhythm_tweezers_cue_despawn,
    /* Func. Hit       */ rhythm_tweezers_cue_hit_short,
    /* Func. Barely    */ rhythm_tweezers_cue_barely_short,
    /* Func. Miss      */ rhythm_tweezers_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_datumo_nuki_seqData,
    /* SFX Barely      */ &s_f_hair_kegire_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e418c] Cue Definition Index
struct CueDefinition *rhythm_tweezers_cue_index[] = {
    /* 0x00 */ &rhythm_tweezers_cue_short_4beat,
    /* 0x01 */ &rhythm_tweezers_cue_long_4beat,
    /* 0x02 */ &rhythm_tweezers_cue_fast_4beat,
    /* 0x03 */ NULL,
    /* 0x04 */ &rhythm_tweezers_cue_short_8beat,
    /* 0x05 */ &rhythm_tweezers_cue_long_8beat,
    /* 0x06 */ &rhythm_tweezers_cue_fast_8beat,
    /* 0x07 */ NULL,
    /* 0x08 */ NULL,
    /* 0x09 */ NULL,
    /* 0x0A */ NULL,
    /* 0x0B */ NULL,
    END_OF_CUE_INDEX
};


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e41c0] Common Events
EngineEvent rhythm_tweezers_common_events[] = {
    /* BEAT_ANIMATION */ rhythm_tweezers_common_beat_animation,
    /* DISPLAY_TEXT   */ rhythm_tweezers_common_display_text,
    /* INIT_TUTORIAL  */ // None
    END_OF_COMMON_EVENT_LIST
};

// [D_089e41cc] Engine Events
EngineEvent rhythm_tweezers_engine_events[] = {
    /* 0x00 */ rhythm_tweezers_spawn_tweezers,
    /* 0x01 */ rhythm_tweezers_start_hair_cycle,
    /* 0x02 */ rhythm_tweezers_scroll_to_next_veg,
    /* 0x03 */ rhythm_tweezers_set_next_veg_type,
    /* 0x04 */ rhythm_tweezers_play_cash_reg_sfx,
    /* 0x05 */ rhythm_tweezers_hide_tutorial_text,
    /* 0x06 */ rhythm_tweezers_removed_engine_event,
    /* 0x07 */ rhythm_tweezers_show_mask,
    /* 0x08 */ rhythm_tweezers_hide_mask,
    /* 0x09 */ rhythm_tweezers_engine_event_stub
};

// [D_089e41f4] Rhythm Tweezers Game Engine
struct GameEngine rhythm_tweezers_engine = {
    /* Size in Memory */ sizeof(struct RhythmTweezersEngineData),
    /* Start Engine   */ rhythm_tweezers_engine_start,
    /* Update Engine  */ rhythm_tweezers_engine_update,
    /* Stop Engine    */ rhythm_tweezers_engine_stop,
    /* Cue Index      */ rhythm_tweezers_cue_index,
    /* Common Events  */ rhythm_tweezers_common_events,
    /* Engine Events  */ rhythm_tweezers_engine_events,
    /* Input Event    */ rhythm_tweezers_input_event
};
