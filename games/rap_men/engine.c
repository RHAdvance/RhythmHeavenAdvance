#include "engines/rap_men.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e63a0] All Animations
struct Animation *rap_men_anim[][2] = {
    /* 0x00 */ { anim_rap_men_red_desuka, anim_rap_women_red_desuka },
    /* 0x01 */ { anim_rap_men_yellow_barely, anim_rap_women_blue_barely },
    /* 0x02 */ { anim_rap_men_yellow_hit, anim_rap_women_blue_hit },
    /* 0x03 */ { anim_rap_men_yellow_start, anim_rap_women_blue_start },
    /* 0x04 */ { anim_rap_men_red_kamone, anim_rap_women_red_kamone },
    /* 0x05 */ { anim_rap_men_red_saiko, anim_rap_women_red_saiko },
    /* 0x06 */ { anim_rap_men_red_recoil, anim_rap_women_red_recoil },
    /* 0x07 */ { anim_rap_men_smoke_effect, anim_rap_women_smoke_effect },
    /* 0x08 */ { anim_rap_men_yellow_miss, anim_rap_women_blue_miss },
    /* 0x09 */ { anim_rap_men_yellow_beat, anim_rap_women_blue_beat },
    /* 0x0A */ { anim_rap_men_red_beat, anim_rap_women_red_beat },
};

// [D_089e63f8] Animation Table
struct Animation **rap_men_anim_table[] = {
    /* 0x00 */ rap_men_anim[0],
    /* 0x01 */ rap_men_anim[1],
    /* 0x02 */ rap_men_anim[2],
    /* 0x03 */ rap_men_anim[3],
    /* 0x04 */ rap_men_anim[4],
    /* 0x05 */ rap_men_anim[5],
    /* 0x06 */ rap_men_anim[6],
    /* 0x07 */ rap_men_anim[7],
    /* 0x08 */ rap_men_anim[8],
    /* 0x09 */ rap_men_anim[9],
    /* 0x0A */ rap_men_anim[10]
};

// [D_089e6424] Buffered Textures List
struct CompressedData *rap_men_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e6428] Graphics Table (Rap Men)
struct GraphicsTable rap_men_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rap_men_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rap_men_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rap_men_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rap_men_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rap_men_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[1],
        /* Dest. */ OBJ_PALETTE_BUFFER(8.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[10],
        /* Dest. */ OBJ_PALETTE_BUFFER(9.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[13],
        /* Dest. */ OBJ_PALETTE_BUFFER(10.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[12],
        /* Dest. */ OBJ_PALETTE_BUFFER(11.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e64a0] Graphics Table (Rap Women)
struct GraphicsTable rap_women_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rap_women_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rap_women_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rap_women_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rap_women_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rap_women_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[1],
        /* Dest. */ OBJ_PALETTE_BUFFER(8.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[10],
        /* Dest. */ OBJ_PALETTE_BUFFER(9.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[13],
        /* Dest. */ OBJ_PALETTE_BUFFER(10.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[12],
        /* Dest. */ OBJ_PALETTE_BUFFER(11.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e6518] Graphics Table Index
struct GraphicsTable *rap_men_gfx_tables[] = {
    /* 0x00 */ rap_men_gfx_table,
    /* 0x01 */ rap_women_gfx_table
};

// [D_089e6520] Rapping Animations
u8 rapping_anim_map[] = {
    /* DESUKA */ RAP_MEN_ANIM_DESUKA,
    /* KAMONE */ RAP_MEN_ANIM_KAMONE,
    /* SAIKO  */ RAP_MEN_ANIM_SAIKO,
    /* RECOIL */ RAP_MEN_ANIM_RECOIL,
    /* HONTO  */ RAP_MEN_ANIM_KAMONE,
};

// [D_089e6525] Rapping Animation Durations
u8 rapping_anim_durations[] = {
    /* DESUKA */ 0x24,
    /* KAMONE */ 0x24,
    /* SAIKO  */ 0x24,
    /* RECOIL */ 0x24,
    /* HONTO  */ 0x6C
};

const char D_0805a8b0[] = "";


  //  //  //  CUE DATA  //  //  //


// [D_089e652c] Cue Hit Sounds
struct SongHeader *rap_men_cue_hit_sfx[][2] = {
    /* RAP_MEN   */ { &s_rap_un_seqData, &s_rap_uun_seqData },
    /* RAP_WOMEN */ { &s_f_rapW_v_Un_seqData, &s_f_rapW_v_Uun_seqData }
};

// [D_089e653c] Cue 00 (Un)
struct CueDefinition rap_men_cue_short = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct RapMenCue),
    /* Func. Spawn     */ rap_men_cue_spawn,
    /* Spawn Parameter */ RAP_CUE_SFX_SHORT,
    /* Func. Update    */ rap_men_cue_update,
    /* Func. Despawn   */ rap_men_cue_despawn,
    /* Func. Hit       */ rap_men_cue_hit,
    /* Func. Barely    */ rap_men_cue_barely,
    /* Func. Miss      */ rap_men_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e657c] Cue 01 (Uun)
struct CueDefinition rap_men_cue_long = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct RapMenCue),
    /* Func. Spawn     */ rap_men_cue_spawn,
    /* Spawn Parameter */ RAP_CUE_SFX_LONG,
    /* Func. Update    */ rap_men_cue_update,
    /* Func. Despawn   */ rap_men_cue_despawn,
    /* Func. Hit       */ rap_men_cue_hit,
    /* Func. Barely    */ rap_men_cue_barely,
    /* Func. Miss      */ rap_men_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e65bc] Cue Definition Index
struct CueDefinition *rap_men_cue_index[] = {
    /* 0x00 */ &rap_men_cue_short,
    /* 0x01 */ &rap_men_cue_long,
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

// [D_089e65f0] Cue Miss Sounds
struct SongHeader *rap_men_cue_miss_sfx[] = {
    /* RAP_MEN   */ &s_rap_two_seqData,
    /* RAP_WOMEN */ &s_f_rapW_v_CheckIt_seqData,
};


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e65f8] Common Events
EngineEvent rap_men_common_events[] = {
    /* BEAT_ANIMATION */ rap_men_common_beat_animation,
    /* DISPLAY_TEXT   */ rap_men_common_display_text,
    /* INIT_TUTORIAL  */ rap_men_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e6608] Engine Events
EngineEvent rap_men_engine_events[] = {
    /* 0x00 */ rap_men_set_rapper_anim,
    /* 0x01 */ rap_men_enable_tutorial,
    /* 0x02 */ rap_men_engine_event_stub
};

// [D_089e6614] Rap Men Game Engine
struct GameEngine rap_men_engine = {
    /* Size in Memory */ sizeof(struct RapMenEngineData),
    /* Start Engine   */ rap_men_engine_start,
    /* Update Engine  */ rap_men_engine_update,
    /* Stop Engine    */ rap_men_engine_stop,
    /* Cue Index      */ rap_men_cue_index,
    /* Common Events  */ rap_men_common_events,
    /* Engine Events  */ rap_men_engine_events,
    /* Input Event    */ rap_men_input_event
};
