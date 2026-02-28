#include "global.h"
#include "graphics.h"
#include "src/scenes/perfect.h"
#include "graphics/perfect/perfect_certificate_graphics.h"
#include "src/scenes/studio.h"


  /* PERFECT CERTIFICATE - SCENE DATA */


// [D_089cfc38] Graphics Table
struct GraphicsTable perfect_certificate_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &perfect_certificate_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &perfect_certificate_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ perfect_certificate_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ perfect_certificate_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    END_OF_GRAPHICS_TABLE
};


// [D_089cfc74] Buffered Textures List
struct CompressedData *perfect_certificate_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};


// [D_089cfc78] Gift Directive Text (by Type)
        // You can listen to it in the studio.
        // You can play it in the studio.
        // You can read it in your e-mail.
        //
const char *perfect_gift_directive_text[] = {
    /* Song     */ "Listen to it in the studio!\n",
    /* Drum Kit */ "Play it in the studio!\n",
    /* E-Mail   */ "Read it in the archives!\n",
    /* Other    */ "",
};


// [D_089cfc88] Songs Provided Upon Getting All Perfects
s8 unassigned_campaign_gift_songs[] = {
    STUDIO_SONG_RHYTHM_TWEEZERS,
    STUDIO_SONG_WIZARDS_WALTZ,
    STUDIO_SONG_MARCHING_ORDERS,
    STUDIO_SONG_SPACEBALL,
    STUDIO_SONG_SNEAKY_SPIRITS,
    STUDIO_SONG_SAMURAI_SLICE,
    STUDIO_SONG_RAT_RACE,
    STUDIO_SONG_SICK_BEATS,
    STUDIO_SONG_TRAM_PAULINE,
    STUDIO_SONG_QUIZ_SHOW,
    STUDIO_SONG_POLYRHYTHM,
    STUDIO_SONG_BOUNCY_ROAD,
    STUDIO_SONG_TOSS_BOYS,
    STUDIO_SONG_FIREWORKS,
    STUDIO_SONG_REMIX7,
    STUDIO_SONG_REMIX8,
    STUDIO_SONG_STAFF_CREDIT,
    STUDIO_SONG_GAME_SELECT_2,
    STUDIO_SONG_CAFE,
    STUDIO_SONG_TRY_AGAIN,
    STUDIO_SONG_OK,
    STUDIO_SONG_SUPERB,
    STUDIO_SONG_PERFECT,
    -1
};
