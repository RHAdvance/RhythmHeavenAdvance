#include "prologues/rhythm_tweezers_2.h"


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089ead54] Buffered Textures List
struct CompressedData *rhythm_tweezers_2_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089ead58] Graphics Table
struct GraphicsTable rhythm_tweezers_2_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &rhythm_tweezers_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &rhythm_tweezers_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &rhythm_tweezers_2_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ rhythm_tweezers_2_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ rhythm_tweezers_2_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089eada0] Engine Events
EngineEvent rhythm_tweezers_2_prologue_engine_events[] = {
    /* 0x00 */ rhythm_tweezers_2_prologue_engine_func_00
};

// [D_089eada4] Prologue (Rhythm Tweezers) Game Engine
struct GameEngine rhythm_tweezers_2_prologue_engine = {
    /* Size in Memory */ sizeof(struct RhythmTweezers2PrologueEngineData),
    /* Start Engine   */ rhythm_tweezers_2_prologue_engine_start,
    /* Update Engine  */ rhythm_tweezers_2_prologue_engine_update,
    /* Stop Engine    */ rhythm_tweezers_2_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ rhythm_tweezers_2_prologue_engine_events,
    /* Input Event    */ NULL
};
