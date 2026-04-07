#include "global.h"
#include "graphics.h"
#include "src/scenes/sequence_player.h"
#include "graphics/sequence_player/sequence_player_graphics.h"


/* SEQUENCE PLAYER - SCENE DATA */


struct GraphicsTable sequence_player_gfx_table[] = {
    /* BG Palette */ {
        /* Src.  */ sequence_player_pal,
        /* Dest. */ BG_PALETTE_BUFFER(8),
        /* Size  */ 0x40
    },
    /* OBJ Palette */ {
        /* Src.  */ sequence_player_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(8),
        /* Size  */ 0x40
    },
    END_OF_GRAPHICS_TABLE
};

struct CompressedData *sequence_player_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};