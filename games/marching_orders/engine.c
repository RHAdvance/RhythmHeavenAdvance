#include "engines/marching_orders.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e50d8] All Animations
struct Animation *marching_anim[][5] = {
    /* 0x00 */ { anim_marching1_turn_l, anim_space_rabbit_turn_l, anim_marching1_turn_l, anim_marching2_turn_l, anim_marching_extra_turn_l },
    /* 0x01 */ { anim_marching1_turn_r, anim_space_rabbit_turn_r, anim_marching1_turn_r, anim_marching2_turn_r, anim_marching_extra_turn_r },
    /* 0x02 */ { anim_marching1_point_l, anim_space_rabbit_point_l, anim_marching1_point_l, anim_marching2_point_l, anim_marching_extra_point_l },
    /* 0x03 */ { anim_marching1_point_r, anim_space_rabbit_point_r, anim_marching1_point_r, anim_marching2_point_r, anim_marching_extra_point_r },
    /* 0x04 */ { anim_marching1_commander_angry, anim_space_rabbit_commander_angry, anim_marching1_commander_angry, anim_marching2_commander_angry, anim_marching_extra_commander_angry },
    /* 0x05 */ { anim_marching1_stop_beat, anim_space_rabbit_stop_beat, anim_marching1_stop_beat, anim_marching2_stop_beat, anim_marching_extra_stop_beat },
    /* 0x06 */ { anim_marching1_beat, anim_space_rabbit_beat, anim_marching1_beat, anim_marching2_beat, anim_marching_extra_beat },
    /* 0x07 */ { anim_marching1_step_r, anim_space_rabbit_step_r, anim_marching1_step_r, anim_marching2_step_r, anim_marching_extra_step_r },
    /* 0x08 */ { anim_marching1_step_l, anim_space_rabbit_step_l, anim_marching1_step_l, anim_marching2_step_l, anim_marching_extra_step_l },
    /* 0x09 */ { anim_marching1_head_turn_r, anim_space_rabbit_head_turn_r, anim_marching1_head_turn_r, anim_marching2_head_turn_r, anim_marching_extra_head_turn_r },
    /* 0x0A */ { anim_marching1_head_turn_l, anim_space_rabbit_head_turn_l, anim_marching1_head_turn_l, anim_marching2_head_turn_l, anim_marching_extra_head_turn_l },
    /* 0x0B */ { anim_marching1_tutorial_icons, anim_space_rabbit_tutorial_icons, anim_marching1_tutorial_icons, anim_marching2_tutorial_icons, anim_marching_extra_tutorial_icons },
    /* 0x0C */ { anim_marching1_angry_puff, anim_space_rabbit_angry_puff, anim_marching1_angry_puff, anim_marching2_angry_puff, anim_marching_extra_angry_puff },
    /* 0x0D */ { anim_marching1_clap, anim_space_rabbit_clap, anim_marching1_clap, anim_marching2_clap, anim_marching_extra_clap },
    /* 0x0E */ { anim_marching1_commander_annoyed, anim_space_rabbit_commander_annoyed, anim_marching1_commander_annoyed, anim_marching2_commander_annoyed, anim_marching_extra_commander_annoyed }
};

// [D_089e51c8] Animation Table
struct Animation **marching_anim_table[] = {
    /* 0x00 */ marching_anim[0],
    /* 0x01 */ marching_anim[1],
    /* 0x02 */ marching_anim[2],
    /* 0x03 */ marching_anim[3],
    /* 0x04 */ marching_anim[4],
    /* 0x05 */ marching_anim[5],
    /* 0x06 */ marching_anim[6],
    /* 0x07 */ marching_anim[7],
    /* 0x08 */ marching_anim[8],
    /* 0x09 */ marching_anim[9],
    /* 0x0A */ marching_anim[10],
    /* 0x0B */ marching_anim[11],
    /* 0x0C */ marching_anim[12],
    /* 0x0D */ marching_anim[13],
    /* 0x0E */ marching_anim[14]
};

// [D_089e5204] Buffered Textures List
struct CompressedData *marching_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e5208] Graphics Table (Marching Orders)
struct GraphicsTable marching_orders_1_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &marching_orders_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE 
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_bg_map_text_bubble,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_bg_map_floor,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &marching_orders_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ marching_orders_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ marching_orders_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[4],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e5280] Graphics Table (Remix 7, Remix 8)
struct GraphicsTable marching_orders_remix_7_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &marching_orders_remix_7_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_remix_7_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_remix_7_bg_map_text_bubble,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_remix_7_bg_map_floor,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &marching_orders_remix_7_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ marching_orders_remix_7_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ marching_orders_remix_7_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[4],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e52ec] Graphics Table (Marching Orders 2)
struct GraphicsTable marching_orders_2_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &marching_orders_2_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE 
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_2_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_bg_map_text_bubble,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_2_bg_map_floor,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &marching_orders_2_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ marching_orders_2_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ marching_orders_2_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[4],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e5208] Graphics Table (Marching Orders)
struct GraphicsTable marching_orders_extra_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &marching_orders_extra_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE 
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_extra_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_extra_bg_map_text_bubble,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_extra_bg_map_floor,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &marching_orders_extra_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ marching_orders_extra_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ marching_orders_extra_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[4],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e5358] Graphics Table Index
struct GraphicsTable *marching_gfx_tables[] = {
    /* 0x00 */ marching_orders_1_gfx_table,
    /* 0x01 */ marching_orders_remix_7_gfx_table,
    /* 0x02 */ marching_orders_1_gfx_table,
    /* 0x03 */ marching_orders_2_gfx_table,
    /* 0x04 */ marching_orders_extra_gfx_table,
};

// [D_089e5368] Position of <sprite> per Animation Frame
struct Vector2 D_089e5368[][4] = {
    /* 0x00 */ {
        /* ver0 */ {  0,  3 },
        /* ver1 */ {  0,  1 },
        /* ver2 */ {  0,  3 },
        /* ver3 */ {  0,  3 }
    },
    /* 0x01 */ {
        /* ver0 */ {  0,  3 },
        /* ver1 */ {  0,  1 },
        /* ver2 */ {  0,  3 },
        /* ver3 */ {  0,  3 }
    },
    /* 0x02 */ {
        /* ver0 */ {  0,  3 },
        /* ver1 */ {  0,  1 },
        /* ver2 */ {  0,  3 },
        /* ver3 */ {  0,  3 }
    },
    /* 0x03 */ {
        /* ver0 */ {  0,  2 },
        /* ver1 */ {  0,  0 },
        /* ver2 */ {  0,  2 },
        /* ver3 */ {  0,  2 }
    },
    /* 0x04 */ {
        /* ver0 */ {  0,  1 },
        /* ver1 */ {  0, -1 },
        /* ver2 */ {  0,  1 },
        /* ver3 */ {  0,  1 }
    }
};


  //  //  //  CUE DATA  //  //  //


// [D_089e53b8] Cue 00 (Step)
struct CueDefinition marching_cue_step = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ marching_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ marching_cue_update,
    /* Func. Despawn   */ marching_cue_despawn,
    /* Func. Hit       */ marching_cue_hit,
    /* Func. Barely    */ marching_cue_barely,
    /* Func. Miss      */ marching_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e53f8] Cue 01 (Turn Left)
struct CueDefinition marching_cue_turn_left = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(DPAD_LEFT),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ marching_cue_spawn,
    /* Spawn Parameter */ 1,
    /* Func. Update    */ marching_cue_update,
    /* Func. Despawn   */ marching_cue_despawn,
    /* Func. Hit       */ marching_cue_hit,
    /* Func. Barely    */ marching_cue_barely,
    /* Func. Miss      */ marching_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e5438] Cue 02 (Turn Right)
struct CueDefinition marching_cue_turn_right = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(DPAD_RIGHT),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ marching_cue_spawn,
    /* Spawn Parameter */ 2,
    /* Func. Update    */ marching_cue_update,
    /* Func. Despawn   */ marching_cue_despawn,
    /* Func. Hit       */ marching_cue_hit,
    /* Func. Barely    */ marching_cue_barely,
    /* Func. Miss      */ marching_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e5478] Cue 03 (Halt)
struct CueDefinition marching_cue_halt = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(B_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ marching_cue_spawn,
    /* Spawn Parameter */ 3,
    /* Func. Update    */ marching_cue_update,
    /* Func. Despawn   */ marching_cue_despawn,
    /* Func. Hit       */ marching_cue_hit,
    /* Func. Barely    */ marching_cue_barely,
    /* Func. Miss      */ marching_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e54b8] Cue Definition Index
struct CueDefinition *marching_cue_index[] = {
    /* 0x00 */ &marching_cue_step,
    /* 0x01 */ &marching_cue_turn_left,
    /* 0x02 */ &marching_cue_turn_right,
    /* 0x03 */ &marching_cue_halt,
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

const char D_0805a670[] = "";


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e54ec] Common Events
EngineEvent marching_common_events[] = {
    /* BEAT_ANIMATION */ marching_common_beat_animation,
    /* DISPLAY_TEXT   */ marching_common_display_text,
    /* INIT_TUTORIAL  */ marching_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e54fc] Engine Events
EngineEvent marching_engine_events[] = {
    /* 0x00 */ func_08034544,
    /* 0x01 */ func_080346e0,
    /* 0x02 */ func_080347c0,
    /* 0x03 */ func_0803481c,
    /* 0x04 */ func_08034850,
    /* 0x05 */ func_08034ae4,
    /* 0x06 */ marching_engine_event_stub
};

// [D_089e5518] Marching Orders Game Engine
struct GameEngine marching_orders_engine = {
    /* Size in Memory */ sizeof(struct MarchingOrdersEngineData),
    /* Start Engine   */ marching_engine_start,
    /* Update Engine  */ marching_engine_update,
    /* Stop Engine    */ marching_engine_stop,
    /* Cue Index      */ marching_cue_index,
    /* Common Events  */ marching_common_events,
    /* Engine Events  */ marching_engine_events,
    /* Input Event    */ marching_input_event
};


  //  //  //  SOUND DATA  //  //  //


// [D_089e5538] Sound Effects Table
struct MarchingSfxData marching_sfx_table[][12] = {
    /* ver0 */ {
        /* SHOUT_START */ {
            /* Sound  */ &s_guntai_v_es_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* SHOUT_HALT */ {
            /* Sound  */ &s_guntai_v_yoh_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* SHOUT_TURN */ {
            /* Sound  */ &s_guntai_v_ka_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_ATTENTION */ {
            /* Sound  */ &s_guntai_v_zentai1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_MARCH */ {
            /* Sound  */ &s_guntai_v_susume_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_HALT */ {
            /* Sound  */ &s_guntai_v_tomare_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE */ {
            /* Sound  */ &s_guntai_v_migi_muke1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE_F */ {
            /* Sound  */ &s_guntai_v_migi_muke2_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_RIGHT */ {
            /* Sound  */ &s_guntai_v_migi_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE */ {
            /* Sound  */ &s_guntai_v_hidari_muke1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE_F */ {
            /* Sound  */ &s_guntai_v_hidari_muke2_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_LEFT */ {
            /* Sound  */ &s_guntai_v_hidari_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        }
    },
    /* ver1 */ {
        /* SHOUT_START */ {
            /* Sound  */ &s_guntai_v_es_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(12.0)
        },
        /* SHOUT_HALT */ {
            /* Sound  */ &s_guntai_v_yoh_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(12.0)
        },
        /* SHOUT_TURN */ {
            /* Sound  */ &s_guntai_v_ka_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(12.0)
        },
        /* CMD_ATTENTION */ {
            /* Sound  */ &s_guntai_v_zentai1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_MARCH */ {
            /* Sound  */ &s_guntai_v_susume_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_HALT */ {
            /* Sound  */ &s_guntai_v_tomare_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE */ {
            /* Sound  */ &s_guntai_v_migi_muke1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE_F */ {
            /* Sound  */ &s_guntai_v_migi_muke2_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_RIGHT */ {
            /* Sound  */ &s_guntai_v_migi_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE */ {
            /* Sound  */ &s_guntai_v_hidari_muke1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE_F */ {
            /* Sound  */ &s_guntai_v_hidari_muke2_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_LEFT */ {
            /* Sound  */ &s_guntai_v_hidari_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        }
    },
    /* ver2 */ {
        /* SHOUT_START */ {
            /* Sound  */ &s_guntai_v_es_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* SHOUT_HALT */ {
            /* Sound  */ &s_guntai_v_yoh_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* SHOUT_TURN */ {
            /* Sound  */ &s_guntai_v_ka_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_ATTENTION */ {
            /* Sound  */ &s_guntai_v_zentai1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_MARCH */ {
            /* Sound  */ &s_guntai_v_susume_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_HALT */ {
            /* Sound  */ &s_guntai_v_tomare_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE */ {
            /* Sound  */ &s_guntai_v_migi_muke1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE_F */ {
            /* Sound  */ &s_guntai_v_migi_muke2_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_RIGHT */ {
            /* Sound  */ &s_guntai_v_migi_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE */ {
            /* Sound  */ &s_guntai_v_hidari_muke1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE_F */ {
            /* Sound  */ &s_guntai_v_hidari_muke2_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_LEFT */ {
            /* Sound  */ &s_guntai_v_hidari_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        }
    },
    /* ver3 */ {
        /* SHOUT_START */ {
            /* Sound  */ &s_guntai_v_es_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(-4.0)
        },
        /* SHOUT_HALT */ {
            /* Sound  */ &s_guntai_v_yoh_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(-4.0)
        },
        /* SHOUT_TURN */ {
            /* Sound  */ &s_guntai_v_ka_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(-4.0)
        },
        /* CMD_ATTENTION */ {
            /* Sound  */ &s_f_marcher2_v_zentai_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_MARCH */ {
            /* Sound  */ &s_f_marcher2_v_susume_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_HALT */ {
            /* Sound  */ &s_f_marcher2_v_tomare_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE */ {
            /* Sound  */ &s_f_marcher2_v_migimukeL_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE_F */ {
            /* Sound  */ &s_f_marcher2_v_migimukeS_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_RIGHT */ {
            /* Sound  */ &s_f_marcher2_v_migi_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE */ {
            /* Sound  */ &s_f_marcher2_v_hidarimukeL_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE_F */ {
            /* Sound  */ &s_f_marcher2_v_hidarimukeS_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_LEFT */ {
            /* Sound  */ &s_f_marcher2_v_hidari_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        }
    },
    /* ver4 */ {
        /* SHOUT_START */ {
            /* Sound  */ &s_guntai_v_es_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* SHOUT_HALT */ {
            /* Sound  */ &s_guntai_v_yoh_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* SHOUT_TURN */ {
            /* Sound  */ &s_guntai_v_ka_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_ATTENTION */ {
            /* Sound  */ &s_guntai_v_zentai1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_MARCH */ {
            /* Sound  */ &s_guntai_v_susume_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_HALT */ {
            /* Sound  */ &s_guntai_v_tomare_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE */ {
            /* Sound  */ &s_guntai_v_migi_muke1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_RIGHT_FACE_F */ {
            /* Sound  */ &s_guntai_v_migi_muke2_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_RIGHT */ {
            /* Sound  */ &s_guntai_v_migi_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE */ {
            /* Sound  */ &s_guntai_v_hidari_muke1_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_LEFT_FACE_F */ {
            /* Sound  */ &s_guntai_v_hidari_muke2_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        },
        /* CMD_TURN_LEFT */ {
            /* Sound  */ &s_guntai_v_hidari_seqData,
            /* Volume */ INT_TO_FIXED(1.0),
            /* Pitch  */ INT_TO_FIXED(0.0)
        }
    }
};
