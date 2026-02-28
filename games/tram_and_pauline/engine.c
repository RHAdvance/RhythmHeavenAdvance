#include "engines/tram_and_pauline.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e8a28] Buffered Textures List
struct CompressedData *tram_pauline_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e8a2c] Graphics Table (Tutorial)
struct GraphicsTable gfx_table_tram_pauline_tutorial[] = {
    /* OBJ Tileset */ {
        /* Src.  */ &tram_pauline_remix_3_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ tram_pauline_tutorial_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ tram_pauline_tutorial_pal,
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

// [D_089e8a68] Graphics Table (Tram & Pauline)
struct GraphicsTable gfx_table_tram_pauline[] = {
    /* BG Tileset */ {
        /* Src.  */ &tram_pauline_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tram_pauline_bg_map_curtain,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tram_pauline_bg_map,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &tram_pauline_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ tram_pauline_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ tram_pauline_obj_pal,
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

// [D_089e8ac8] Graphics Table (Remix 3)
struct GraphicsTable gfx_table_tram_pauline_remix_3[] = {
    /* BG Tileset */ {
        /* Src.  */ &tram_pauline_remix_3_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tram_pauline_remix_3_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &tram_pauline_remix_3_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ tram_pauline_remix_3_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ tram_pauline_tutorial_pal,
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

// [D_089e8b1c] Graphics Table Index
struct GraphicsTable *tram_pauline_gfx_tables[] = {
    /* 0x00 */ gfx_table_tram_pauline_tutorial,
    /* 0x01 */ gfx_table_tram_pauline,
    /* 0x02 */ gfx_table_tram_pauline_remix_3,
    /* 0x03 */ gfx_table_tram_pauline
};

// [D_089e8b2c] All Animations
struct Animation *tram_pauline_anim_table[] = {

    // version = 0

    /* 0x00 */ anim_casual_fox_beat,
    /* 0x01 */ anim_casual_fox_beat,
    /* 0x02 */ anim_casual_tram_beat,
    /* 0x03 */ anim_casual_pauline_beat,
    /* 0x04 */ anim_casual_half_tram_beat,
    /* 0x05 */ anim_casual_half_pauline_beat,

    /* 0x06 */ anim_casual_fox_crouch,
    /* 0x07 */ anim_casual_fox_crouch,
    /* 0x08 */ anim_casual_tram_crouch,
    /* 0x09 */ anim_casual_pauline_crouch,
    /* 0x0a */ anim_casual_half_tram_crouch,
    /* 0x0b */ anim_casual_half_pauline_crouch,

    /* 0x0c */ anim_casual_fox_jump,
    /* 0x0d */ anim_casual_fox_jump,
    /* 0x0e */ anim_casual_tram_jump,
    /* 0x0f */ anim_casual_pauline_jump,
    /* 0x10 */ anim_casual_half_tram_jump,
    /* 0x11 */ anim_casual_half_pauline_jump,

    /* 0x12 */ anim_casual_fox_transform,
    /* 0x13 */ anim_casual_fox_transform,
    /* 0x14 */ anim_casual_tram_transform,
    /* 0x15 */ anim_casual_pauline_transform,
    /* 0x16 */ anim_casual_half_tram_transform,
    /* 0x17 */ anim_casual_half_pauline_transform,

    // version = 1

    /* 0x18 */ anim_circus_fox_beat,
    /* 0x19 */ anim_circus_fox_beat,
    /* 0x1a */ anim_circus_tram_beat,
    /* 0x1b */ anim_circus_pauline_beat,
    /* 0x1c */ anim_circus_half_tram_beat,
    /* 0x1d */ anim_circus_half_pauline_beat,

    /* 0x1e */ anim_circus_fox_crouch,
    /* 0x1f */ anim_circus_fox_crouch,
    /* 0x20 */ anim_circus_tram_crouch,
    /* 0x21 */ anim_circus_pauline_crouch,
    /* 0x22 */ anim_circus_half_tram_crouch,
    /* 0x23 */ anim_circus_half_pauline_crouch,

    /* 0x24 */ anim_circus_fox_jump,
    /* 0x25 */ anim_circus_fox_jump,
    /* 0x26 */ anim_circus_tram_jump,
    /* 0x27 */ anim_circus_pauline_jump,
    /* 0x28 */ anim_circus_half_tram_jump,
    /* 0x29 */ anim_circus_half_pauline_jump,

    /* 0x2a */ anim_circus_fox_transform,
    /* 0x2b */ anim_circus_fox_transform,
    /* 0x2c */ anim_circus_tram_transform,
    /* 0x2d */ anim_circus_pauline_transform,
    /* 0x2e */ anim_circus_half_tram_transform,
    /* 0x2f */ anim_circus_half_pauline_transform,

    // version = 2

    /* 0x30 */ anim_casual_fox_beat,
    /* 0x31 */ anim_casual_fox_beat,
    /* 0x32 */ anim_casual_tram_beat,
    /* 0x33 */ anim_casual_pauline_beat,
    /* 0x34 */ anim_casual_half_tram_beat,
    /* 0x35 */ anim_casual_half_pauline_beat,

    /* 0x36 */ anim_casual_fox_crouch,
    /* 0x37 */ anim_casual_fox_crouch,
    /* 0x38 */ anim_casual_tram_crouch,
    /* 0x39 */ anim_casual_pauline_crouch,
    /* 0x3a */ anim_casual_half_tram_crouch,
    /* 0x3b */ anim_casual_half_pauline_crouch,

    /* 0x3c */ anim_casual_fox_jump,
    /* 0x3d */ anim_casual_fox_jump,
    /* 0x3e */ anim_casual_tram_jump,
    /* 0x3f */ anim_casual_pauline_jump,
    /* 0x40 */ anim_casual_half_tram_jump,
    /* 0x41 */ anim_casual_half_pauline_jump,
    
    /* 0x42 */ anim_casual_fox_transform,
    /* 0x43 */ anim_casual_fox_transform,
    /* 0x44 */ anim_casual_tram_transform,
    /* 0x45 */ anim_casual_pauline_transform,
    /* 0x46 */ anim_casual_half_tram_transform,
    /* 0x47 */ anim_casual_half_pauline_transform,

    // version = 3

    /* 0x48 */ anim_circus_fox_beat,
    /* 0x49 */ anim_circus_fox_beat,
    /* 0x4a */ anim_circus_tram_beat,
    /* 0x4b */ anim_circus_pauline_beat,
    /* 0x4c */ anim_circus_half_tram_beat,
    /* 0x4d */ anim_circus_half_pauline_beat,
    
    /* 0x4e */ anim_circus_fox_crouch,
    /* 0x4f */ anim_circus_fox_crouch,
    /* 0x50 */ anim_circus_tram_crouch,
    /* 0x51 */ anim_circus_pauline_crouch,
    /* 0x52 */ anim_circus_half_tram_crouch,
    /* 0x53 */ anim_circus_half_pauline_crouch,

    /* 0x54 */ anim_circus_fox_jump,
    /* 0x55 */ anim_circus_fox_jump,
    /* 0x56 */ anim_circus_tram_jump,
    /* 0x57 */ anim_circus_pauline_jump,
    /* 0x58 */ anim_circus_half_tram_jump,
    /* 0x59 */ anim_circus_half_pauline_jump,
    
    /* 0x5a */ anim_circus_fox_transform,
    /* 0x5b */ anim_circus_fox_transform,
    /* 0x5c */ anim_circus_tram_transform,
    /* 0x5d */ anim_circus_pauline_transform,
    /* 0x5e */ anim_circus_half_tram_transform,
    /* 0x5f */ anim_circus_half_pauline_transform,
};


const char D_0805a910[] = "";

const u32 D_0805a914[] = { 0x18, 0x18 };

const u32 D_0805a91c[] = { 0x48, 0x48 };


  //  //  //  CUE DATA  //  //  //


// [D_089e8cac] Cue 00 (Tram)
struct CueDefinition tram_pauline_cue_tram = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ tram_pauline_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ tram_pauline_cue_update,
    /* Func. Despawn   */ tram_pauline_cue_despawn,
    /* Func. Hit       */ tram_pauline_cue_hit,
    /* Func. Barely    */ tram_pauline_cue_barely,
    /* Func. Miss      */ tram_pauline_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_hanabi_pon_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e8cec] Cue 01 (Pauline)
struct CueDefinition tram_pauline_cue_pauline = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ tram_pauline_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ tram_pauline_cue_update,
    /* Func. Despawn   */ tram_pauline_cue_despawn,
    /* Func. Hit       */ tram_pauline_cue_hit,
    /* Func. Barely    */ tram_pauline_cue_barely,
    /* Func. Miss      */ tram_pauline_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_witch_cake_seqData,
    /* SFX Barely      */ &s_witch_donats_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e8d2c] Cue Definition Index
struct CueDefinition *tram_pauline_cue_index[] = {
    /* 0x00 */ &tram_pauline_cue_tram,
    /* 0x01 */ &tram_pauline_cue_pauline,
    /* 0x02 */ NULL,
    /* 0x03 */ NULL,
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


// [D_089e8d60] Common Events
EngineEvent tram_pauline_common_events[] = {
    /* BEAT_ANIMATION */ tram_pauline_common_beat_animation,
    /* DISPLAY_TEXT   */ tram_pauline_common_display_text,
    /* INIT_TUTORIAL  */ tram_pauline_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e8d70] Engine Events
EngineEvent tram_pauline_engine_events[] = {
    /* 0x00 */ func_08040064,
    /* 0x01 */ func_080400d0,
    /* 0x02 */ func_08040434
};

// [D_089e8d7c] Tram & Pauline Game Engine
struct GameEngine tram_pauline_engine = {
    /* Size in Memory */ sizeof(struct TramPaulineEngineData),
    /* Start Engine   */ tram_pauline_engine_start,
    /* Update Engine  */ tram_pauline_engine_update,
    /* Stop Engine    */ tram_pauline_engine_stop,
    /* Cue Index      */ tram_pauline_cue_index,
    /* Common Events  */ tram_pauline_common_events,
    /* Engine Events  */ tram_pauline_engine_events,
    /* Input Event    */ tram_pauline_input_event
};
