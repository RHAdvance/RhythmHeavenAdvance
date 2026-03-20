#include "global.h"
#include "graphics.h"
#include "src/bitmap_font.h"
#include "src/scenes/results.h"
#include "graphics/results/results_graphics.h"


  /* RESULTS (SCORE-TYPE) - SCENE DATA */


// [D_089d7800] Scene Objects
union SceneObject score_results_scene_objects[] = {
    END_OF_SCENE_OBJECTS_LIST
};


// [D_089d7804] Graphics Table
struct GraphicsTable score_results_gfx_table[] = {
    /* OBJ Tileset */ {
        /* Src.  */ &score_results_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ score_results_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ score_results_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    END_OF_GRAPHICS_TABLE
};


// [D_089d7834] Buffered Textures List
struct CompressedData *score_results_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};


// [D_089d7838] Score Level Default Comments
    // The Highest Level!!
    // Pretty Good!
    // Average.
    // Almost there.
    // Hmm...
const char *score_results_default_comments[] = {
    /* BEST */ "Fantastic!",
    /* HIGH */ "Pretty good!",
    /* MID  */ "Fairly average.",
    /* LOW  */ "Getting there...",
    /* FAIL */ "Hm..."
};


// [D_089d784c] Score Thresholds
u16 score_results_default_thresholds[] = {
    /* BEST */ 1000,
    /* HIGH */ 950,
    /* MID  */ 800,
    /* LOW  */ 500
};


// [D_089d7854] Score Result SFX
struct SongHeader *score_results_reveal_sfx[] = {
    /* Best */ &s_jingle_hi_level_seqData,
    /* High */ &s_fanfare_drum1_seqData,
    /* OK   */ &s_fanfare_drum2_seqData,
    /* Low  */ &s_fanfare_drum3_seqData,
    /* Fail */ &s_yuri_naki_seqData
};
