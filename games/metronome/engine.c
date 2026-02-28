#include "engines/metronome.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e585c] Buffered Textures List
struct CompressedData *metronome_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e5860] Graphics Table
struct GraphicsTable metronome_gfx_table[] = {
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

// [D_089e5890] <sprite> LERP Data
struct MetronomeUnknownMovementData D_089e5890[] = {
    /* 0x00 */ {
        /* Initial */ 320, 108,
        /* Target  */ 200, 108
    },
    /* 0x01 */ {
        /* Initial */ -80, 108,
        /* Target  */  40, 108
    }
};

// [D_089e58a0] <sprite> LERP Data
struct MetronomeUnknownMovementData D_089e58a0[] = {
    /* 0x00 */ {
        /* Initial */ 200, 208,
        /* Target  */ 200, 108
    },
    /* 0x01 */ {
        /* Initial */  40, 208,
        /* Target  */  40, 108
    }
};


  //  //  //  CUE DATA  //  //  //


// [D_089e58b0] Cue 00 (Default)
struct CueDefinition metronome_cue_default = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x02, 0x02,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ metronome_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ metronome_cue_update,
    /* Func. Despawn   */ metronome_cue_despawn,
    /* Func. Hit       */ metronome_cue_hit,
    /* Func. Barely    */ metronome_cue_barely,
    /* Func. Miss      */ metronome_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e58f0] Cue Definition Index
struct CueDefinition *metronome_cue_index[] = {
    /* 0x00 */ &metronome_cue_default,
    /* 0x01 */ NULL,
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

const char D_0805a694[] = "Press ‡M in time with the signal.";

const char D_0805a6c0[] = "Measuring...";

const char D_0805a6c8[] = "Finished measuring! Your rhythm score is...";

  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e5924] Common Events
EngineEvent metronome_common_events[] = {
    /* BEAT_ANIMATION */ metronome_common_beat_animation,
    /* DISPLAY_TEXT   */ metronome_common_display_text,
    /* INIT_TUTORIAL  */ metronome_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e5934] Engine Events
EngineEvent metronome_engine_events[] = {
    /* 0x00 */ func_08035780,
    /* 0x01 */ func_080357c4,
    /* 0x02 */ func_080358b0,
    /* 0x03 */ func_080358d8,
    /* 0x04 */ func_080358f8
};

// [D_089e5948] Metronome Game Engine
struct GameEngine metronome_engine = {
    /* Size in Memory */ sizeof(struct MetronomeEngineData),
    /* Start Engine   */ metronome_engine_start,
    /* Update Engine  */ metronome_engine_update,
    /* Stop Engine    */ metronome_engine_stop,
    /* Cue Index      */ metronome_cue_index,
    /* Common Events  */ metronome_common_events,
    /* Engine Events  */ metronome_engine_events,
    /* Input Event    */ metronome_input_event
};
