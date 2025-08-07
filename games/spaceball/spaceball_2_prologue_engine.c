#include "prologues/spaceball_2.h"


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089ea26c] Buffered Textures List
struct CompressedData *spaceball_2_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089ea270] Graphics Table
struct GraphicsTable spaceball_2_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &spaceball_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &spaceball_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &spaceball_2_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ spaceball_2_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ spaceball_2_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089ea2b8] Engine Events
EngineEvent spaceball_2_prologue_engine_events[] = {
    /* 0x00 */ spaceball_2_prologue_engine_func_00
};

// [D_089ea2bc] Prologue (Spaceball) Game Engine
struct GameEngine spaceball_2_prologue_engine = {
    /* Size in Memory */ sizeof(struct Spaceball2PrologueEngineData),
    /* Start Engine   */ spaceball_2_prologue_engine_start,
    /* Update Engine  */ spaceball_2_prologue_engine_update,
    /* Stop Engine    */ spaceball_2_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ spaceball_2_prologue_engine_events,
    /* Input Event    */ NULL
};
