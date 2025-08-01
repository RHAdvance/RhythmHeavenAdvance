#include "prologues/marching_orders_extra.h"


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089eb66c] Buffered Textures List
struct CompressedData *marching_orders_extra_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089eb670] Graphics Table
struct GraphicsTable marching_orders_extra_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &marching_orders_extra_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &marching_orders_extra_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &marching_orders_extra_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ marching_orders_extra_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ marching_orders_extra_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089eb6b8] Engine Events
EngineEvent marching_orders_extra_prologue_engine_events[] = {
    /* 0x00 */ mo_ex_08046300
};

// [D_089eb6bc] Prologue (Marching Orders) Game Engine
struct GameEngine marching_orders_extra_prologue_engine = {
    /* Size in Memory */ sizeof(struct MarchingOrdersEXPrologueEngineData),
    /* Start Engine   */ marching_orders_extra_prologue_engine_start,
    /* Update Engine  */ marching_orders_extra_prologue_engine_update,
    /* Stop Engine    */ marching_orders_extra_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ marching_orders_extra_prologue_engine_events,
    /* Input Event    */ NULL
};
