#include "prologues/polyrhythm_2.h"


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089eb9bc] Buffered Textures List
struct CompressedData *polyrhythm_2_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089eb9c0] Graphics Table
struct GraphicsTable polyrhythm_2_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &polyrhythm_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &polyrhythm_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &polyrhythm_2_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ polyrhythm_2_prologue_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ polyrhythm_2_prologue_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089eba08] Engine Events
EngineEvent polyrhythm_2_prologue_engine_events[] = {
    /* 0x00 */ polyrhythm_2_prologue_engine_func_00
};

// [D_089eba0c] Prologue (Polyrhythm) Game Engine
struct GameEngine polyrhythm_2_prologue_engine = {
    /* Size in Memory */ sizeof(struct Polyrhythm2PrologueEngineData),
    /* Start Engine   */ polyrhythm_2_prologue_engine_start,
    /* Update Engine  */ polyrhythm_2_prologue_engine_update,
    /* Stop Engine    */ polyrhythm_2_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ polyrhythm_2_prologue_engine_events,
    /* Input Event    */ NULL
};
