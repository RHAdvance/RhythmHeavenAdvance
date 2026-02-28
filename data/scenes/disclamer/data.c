#include "global.h"
#include "graphics.h"
#include "src/scenes/disclaimer.h"
#include "graphics/disclaimer/disclaimer_graphics.h"


  /* disclaimer SCREEN - SCENE DATA */


// [D_089dda68] Graphics Table
struct GraphicsTable disclaimer_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &disclaimer_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &disclaimer_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ disclaimer_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ disclaimer_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    END_OF_GRAPHICS_TABLE
};
