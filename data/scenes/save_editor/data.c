#include "global.h"
#include "graphics.h"
#include "src/scenes/save_editor.h"
#include "graphics/save_editor/save_editor_graphics.h"


/* R-IQ SAVE EDITOR - SCENE DATA */


struct GraphicsTable save_editor_gfx_table[] = {
    /* BG Palette */ {
        /* Src.  */ save_editor_pal,
        /* Dest. */ BG_PALETTE_BUFFER(8),
        /* Size  */ 0x40
    },
    /* OBJ Palette */ {
        /* Src.  */ save_editor_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(8),
        /* Size  */ 0x40
    },
    END_OF_GRAPHICS_TABLE
};

struct CompressedData *save_editor_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};