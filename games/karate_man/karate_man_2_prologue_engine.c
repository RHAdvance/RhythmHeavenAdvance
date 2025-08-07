#include "prologues/karate_man_2.h"


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089ea650] Buffered Textures List
struct CompressedData *karate_man_2_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089ea654] Graphics Table
struct GraphicsTable karate_man_2_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &karate_man_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &karate_man_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &karate_man_2_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ karate_man_2_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ karate_man_2_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089ea69c] Engine Events
EngineEvent karate_man_2_prologue_engine_events[] = {
    /* 0x00 */ karate_man_2_prologue_engine_func_00
};

// [D_089ea6a0] Prologue (Karate Man) Game Engine
struct GameEngine karate_man_2_prologue_engine = {
    /* Size in Memory */ sizeof(struct KarateMan2PrologueEngineData),
    /* Start Engine   */ karate_man_2_prologue_engine_start,
    /* Update Engine  */ karate_man_2_prologue_engine_update,
    /* Stop Engine    */ karate_man_2_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ karate_man_2_prologue_engine_events,
    /* Input Event    */ NULL
};
