#include "prologues/sneaky_spirits_2.h"


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089ea088] Buffered Textures List
struct CompressedData *sneaky_spirits_2_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089ea08c] Graphics Table
struct GraphicsTable sneaky_spirits_2_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &sneaky_spirits_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &sneaky_spirits_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &sneaky_spirits_2_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ sneaky_spirits_prologue_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ sneaky_spirits_prologue_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089ea0d4] Engine Events
EngineEvent sneaky_spirits_2_prologue_engine_events[] = {
    /* 0x00 */ sneaky_spirits_2_prologue_engine_func_00
};

// [D_089ea0d8] Prologue (Sneaky Spirits) Game Engine
struct GameEngine sneaky_spirits_2_prologue_engine = {
    /* Size in Memory */ sizeof(struct SneakySpirits2PrologueEngineData),
    /* Start Engine   */ sneaky_spirits_2_prologue_engine_start,
    /* Update Engine  */ sneaky_spirits_2_prologue_engine_update,
    /* Stop Engine    */ sneaky_spirits_2_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ sneaky_spirits_2_prologue_engine_events,
    /* Input Event    */ NULL
};
