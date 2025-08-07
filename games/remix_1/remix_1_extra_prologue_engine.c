#include "prologues/remix_1_extra.h"


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089ebcac] Buffered Textures List
struct CompressedData *remix_1_extra_prologue_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089ebcb0] Graphics Table
struct GraphicsTable remix_1_extra_prologue_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &remix_1_extra_prologue_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &remix_1_extra_prologue_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &remix_1_extra_prologue_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ remix_1_extra_prologue_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ remix_1_extra_prologue_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089ebcf8] Engine Events
EngineEvent remix_1_extra_prologue_engine_events[] = {
    /* 0x00 */ r1_ex_080466f4
};

// [D_089ebcfc] Prologue (Remix 1) Game Engine
struct GameEngine remix_1_extra_prologue_engine = {
    /* Size in Memory */ sizeof(struct Remix1EXPrologueEngineData),
    /* Start Engine   */ remix_1_extra_prologue_engine_start,
    /* Update Engine  */ remix_1_extra_prologue_engine_update,
    /* Stop Engine    */ remix_1_extra_prologue_engine_stop,
    /* Cue Index      */ NULL,
    /* Common Events  */ NULL,
    /* Engine Events  */ remix_1_extra_prologue_engine_events,
    /* Input Event    */ NULL
};
