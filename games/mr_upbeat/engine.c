#include "engines/mr_upbeat.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e56b8] Trip Over Animations
struct Animation *mr_upbeat_trip_anim[] = {
    /* 0x00 */ anim_mr_upbeat_r_trip_r,
    /* 0x01 */ anim_mr_upbeat_r_trip_l,
    /* 0x02 */ anim_mr_upbeat_l_trip_l,
    /* 0x03 */ anim_mr_upbeat_l_trip_r
};

// [D_089e56c8] Game Over Animations
struct Animation *mr_upbeat_game_over_anim[][4] = {
    /* LOW SCORE */ {
        /* 0x00 */ anim_mr_upbeat_r_mope_r,
        /* 0x01 */ anim_mr_upbeat_r_mope_l,
        /* 0x02 */ anim_mr_upbeat_l_mope_l,
        /* 0x03 */ anim_mr_upbeat_l_mope_r
    },
    /* HIGH SCORE */ {
        /* 0x00 */ anim_mr_upbeat_r_cheer_r,
        /* 0x01 */ anim_mr_upbeat_r_cheer_l,
        /* 0x02 */ anim_mr_upbeat_l_cheer_l,
        /* 0x03 */ anim_mr_upbeat_l_cheer_r
    }
};

// [D_089e56e8] Buffered Textures List
struct CompressedData *mr_upbeat_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e56ec] Graphics Table
struct GraphicsTable mr_upbeat_gfx_table[] = {
    /* OBJ Tileset */ {
        /* Src.  */ &metronome_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ metronome_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ metronome_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};


  //  //  //  CUE DATA  //  //  //


// [D_089e571c] Cue 00 (0.5 Beats, Timing Window is Static)
struct CueDefinition mr_upbeat_cue_half_beat = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x03, 0x03,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ mr_upbeat_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ mr_upbeat_cue_update,
    /* Func. Despawn   */ mr_upbeat_cue_despawn,
    /* Func. Hit       */ mr_upbeat_cue_hit,
    /* Func. Barely    */ mr_upbeat_cue_barely,
    /* Func. Miss      */ mr_upbeat_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e575c] Cue 01 (1 Beat, Timing Window Follows Tempo)
struct CueDefinition mr_upbeat_cue_full_beat_to_tempo = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x02, 0x02,
    /* Barely Window   */ -0x02, 0x02,
    /* Tempo-Dependent */ TRUE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ mr_upbeat_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ mr_upbeat_cue_update,
    /* Func. Despawn   */ mr_upbeat_cue_despawn,
    /* Func. Hit       */ mr_upbeat_cue_hit,
    /* Func. Barely    */ mr_upbeat_cue_barely,
    /* Func. Miss      */ mr_upbeat_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e579c] Cue 08 (0.5 Beats, Timing Window Follows Tempo)
struct CueDefinition mr_upbeat_cue_half_beat_to_tempo = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x02, 0x02,
    /* Barely Window   */ -0x02, 0x02,
    /* Tempo-Dependent */ TRUE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ mr_upbeat_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ mr_upbeat_cue_update,
    /* Func. Despawn   */ mr_upbeat_cue_despawn,
    /* Func. Hit       */ mr_upbeat_cue_hit,
    /* Func. Barely    */ mr_upbeat_cue_barely,
    /* Func. Miss      */ mr_upbeat_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e57dc] Cue Definition Index
struct CueDefinition *mr_upbeat_cue_index[] = {
    /* 0x00 */ &mr_upbeat_cue_half_beat,
    /* 0x01 */ &mr_upbeat_cue_full_beat_to_tempo,
    /* 0x02 */ NULL,
    /* 0x03 */ NULL,
    /* 0x04 */ NULL,
    /* 0x05 */ NULL,
    /* 0x06 */ NULL,
    /* 0x07 */ NULL,
    /* 0x08 */ &mr_upbeat_cue_half_beat_to_tempo,
    /* 0x09 */ NULL,
    /* 0x0A */ NULL,
    /* 0x0B */ NULL,
    END_OF_CUE_INDEX
};

const char D_0805a674[] = "New record!";

const char D_0805a684[] = "Good job!";


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e5810] Common Events
EngineEvent mr_upbeat_common_events[] = {
    /* BEAT_ANIMATION */ mr_upbeat_common_beat_animation,
    /* DISPLAY_TEXT   */ mr_upbeat_common_display_text,
    /* INIT_TUTORIAL  */ mr_upbeat_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e5820] Engine Events
EngineEvent mr_upbeat_engine_events[] = {
    /* 0x00 */ func_08034f18,
    /* 0x01 */ func_08035314,
    /* 0x02 */ func_08034e84,
    /* 0x03 */ func_08034d6c,
    /* 0x04 */ func_08034db0,
    /* 0x05 */ func_0803516c,
    /* 0x06 */ mr_upbeat_engine_event_stub
};

// [D_089e583c] Mr. Upbeat Game Engine
struct GameEngine mr_upbeat_engine = {
    /* Size in Memory */ sizeof(struct MrUpbeatEngineData),
    /* Start Engine   */ mr_upbeat_engine_start,
    /* Update Engine  */ mr_upbeat_engine_update,
    /* Stop Engine    */ mr_upbeat_engine_stop,
    /* Cue Index      */ mr_upbeat_cue_index,
    /* Common Events  */ mr_upbeat_common_events,
    /* Engine Events  */ mr_upbeat_engine_events,
    /* Input Event    */ mr_upbeat_input_event
};
