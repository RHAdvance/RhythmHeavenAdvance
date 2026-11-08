#include "engines/rat_race.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e6634] Buffered Textures List
struct CompressedData *rat_race_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e6638] Graphics Table
struct GraphicsTable rat_race_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rat_race_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rat_race_bg_map_near,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rat_race_bg_map_middle,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rat_race_bg_map_far,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rat_race_bg_map_cheese,
        /* Dest. */ BG_MAP_BASE(0xC000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rat_race_bg_map_cat,
        /* Dest. */ BG_MAP_BASE(0xD000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rat_race_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rat_race_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rat_race_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[1],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e66bc] ?
u32 D_089e66bc[] = {
    /* 0x00 */ 0x100,
    /* 0x01 */ 0x80,
};


  //  //  //  CUE DATA  //  //  //


// [D_089e66c4] Cue 00 (Stop, 4 Beats)
struct CueDefinition rat_race_cue_stop_4beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x60,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0xc,
    /* Func. Spawn     */ rat_race_cue_spawn_stop,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ rat_race_cue_update_stop,
    /* Func. Despawn   */ rat_race_cue_despawn_stop,
    /* Func. Hit       */ rat_race_cue_hit_stop,
    /* Func. Barely    */ rat_race_cue_barely,
    /* Func. Miss      */ rat_race_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_rat_stop_seqData,
    /* SFX Barely      */ &s_f_rat_slip_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e6704] Cue 01 (Stop, 2 Beats)
struct CueDefinition rat_race_cue_stop_2beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x30,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0xc,
    /* Func. Spawn     */ rat_race_cue_spawn_stop,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ rat_race_cue_update_stop,
    /* Func. Despawn   */ rat_race_cue_despawn_stop,
    /* Func. Hit       */ rat_race_cue_hit_stop,
    /* Func. Barely    */ rat_race_cue_barely,
    /* Func. Miss      */ rat_race_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ &s_rat_stop_seqData,
    /* SFX Barely      */ &s_f_rat_slip_seqData,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e6744] Cue 03 (Dash)
struct CueDefinition rat_race_cue_dash = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ RELEASE_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0xc,
    /* Func. Spawn     */ rat_race_cue_spawn_dash,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ rat_race_cue_update_dash,
    /* Func. Despawn   */ rat_race_cue_despawn_dash,
    /* Func. Hit       */ rat_race_cue_hit_dash,
    /* Func. Barely    */ rat_race_cue_barely,
    /* Func. Miss      */ rat_race_cue_miss,
    #ifdef PLUS
    /* SFX Spawn       */ &s_rat_squeak_seqData,
    #else
    /* SFX Spawn       */ NULL,
    #endif
    /* SFX Hit         */ &s_rat_dash_seqData,
    /* SFX Barely      */ &s_f_rat_error_seqData,
    /* SFX Miss        */ &s_f_rat_error_seqData,
    /* Miss Condition  */ NULL
};

// [D_089e6784] Cue Definition Index
struct CueDefinition *rat_race_cue_index[] = {
    /* 0x00 */ &rat_race_cue_stop_4beat,
    /* 0x01 */ &rat_race_cue_stop_2beat,
    /* 0x02 */ NULL,
    /* 0x03 */ &rat_race_cue_dash,
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


// [D_089e67b8] Common Events
EngineEvent rat_race_common_events[] = {
    /* BEAT_ANIMATION */ rat_race_common_beat_animation,
    /* DISPLAY_TEXT   */ rat_race_common_display_text,
    /* INIT_TUTORIAL  */ rat_race_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e67c8] Engine Events
EngineEvent rat_race_engine_events[] = {
    /* 0x00 */ rat_race_engine_event_stub,
    /* 0x01 */ func_0803b034,
    /* 0x02 */ func_0803a158,
    /* 0x03 */ func_0803a1f8,
    /* 0x04 */ func_0803a204,
    /* 0x05 */ func_0803a798,
    /* 0x06 */ func_0803a2a8,
    /* 0x07 */ func_0803a350,
    /* 0x08 */ func_0803a3b8,
    /* 0x09 */ func_0803a1d4,
    /* 0x0A */ func_0803a1e4,
    /* 0x0B */ func_0803aa58,
    /* 0x0C */ func_0803a41c,
    /* 0x0D */ func_0803ac98,
    /* 0x0E */ func_0803bc98,
    /* 0x0F */ func_0803a434,
    /* 0x10 */ func_0803ad50,
    /* 0x11 */ func_0803a47c,
    /* 0x12 */ func_0803a490
};

// [D_089e6814] Rat Race Game Engine
struct GameEngine rat_race_engine = {
    /* Size in Memory */ sizeof(struct RatRaceEngineData),
    /* Start Engine   */ rat_race_engine_start,
    /* Update Engine  */ rat_race_engine_update,
    /* Stop Engine    */ rat_race_engine_stop,
    /* Cue Index      */ rat_race_cue_index,
    /* Common Events  */ rat_race_common_events,
    /* Engine Events  */ rat_race_engine_events,
    /* Input Event    */ rat_race_input_event
};


  //  //  //  MISCELLANEOUS DATA  //  //  //

const char D_0805a8b4[] = "";

// [D_089e6834] ?
u8 D_089e6834[] = {
    /* 0x00 */ 4, 4, 4, 4, 4, 4, 4, 4,
    /* 0x08 */ 4, 4, 4, 4, 4, 4, 4, 4,
    /* 0x10 */ 4, 4, 4, 4, 5, 6, 7, 8
};

// [D_089e684c] ?
u8 D_089e684c[] = {
    /* 0x00 */ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 0x08 */ 0, 0, 0, 0, 0, 0, 0, 0,
    /* 0x10 */ 1, 2, 3, 4, 5, 6, 7, 8,
    /* 0x18 */ 8, 8, 8, 8, 8, 8, 8, 8,
    /* 0x20 */ 8, 8, 8, 8, 8, 8, 8, 8,
    /* 0x28 */ 7, 6, 5, 4, 3, 2, 1, 0
};

// [D_089e687c] Initial Rat Data(?)
struct Rat rat_race_init_rat_data[] = {
    /* 0x00 */ {
        /* Rat   */ 0,
        /* Sweat */ 0,
        /* unk4  */ 0,
        /* unk5  */ 0,
        /* unk8  */ INT_TO_FIXED(120.0),
        /* unkC  */ 0
    },
    /* 0x01 */ {
        /* Rat   */ 0,
        /* Sweat */ 0,
        /* unk4  */ 0,
        /* unk5  */ 1,
        /* unk8  */ INT_TO_FIXED(120.0),
        /* unkC  */ 0
    },
    /* 0x02 */ {
        /* Rat   */ 0,
        /* Sweat */ 0,
        /* unk4  */ 0,
        /* unk5  */ 2,
        /* unk8  */ INT_TO_FIXED(120.0),
        /* unkC  */ 0
    },
};

// [D_089e68ac] ?
s32 D_089e68ac[] = {
    /* 0x00 */ INT_TO_FIXED(0.0),
    /* 0x01 */ INT_TO_FIXED(40.0),
    /* 0x02 */ INT_TO_FIXED(-40.0),
};
