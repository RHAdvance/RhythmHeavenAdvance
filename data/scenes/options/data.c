#include "global.h"
#include "graphics.h"
#include "src/scenes/options.h"
#include "graphics/options/options_graphics.h"
#include "text.h"


  /* OPTIONS MENU - SCENE DATA */


// [D_089cfac8] Graphics Table
struct GraphicsTable options_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &options_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &options_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &options_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ options_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ options_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    END_OF_GRAPHICS_TABLE
};


// [D_089cfb10] Buffered Textures List
struct CompressedData *options_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

const char options_data_clear_confirm_text[] =
        "\0023" "\0013" "\001C" "Are you sure?\n"
        "\0021" "\0011" "\001C" "       Yes\n"
        "     No";

const char *options_desc_text[] = {
    /* SOUND MODE ------------------------------------- */
        "\0023" "\0013" "\001C" "Sound Mode\n"
        "\0024" "\0011" "\001L" "Stereo  " TEXT_COLOR_1 " For dual-speaker systems. (DS, etc.)\n"
        "\0024" "\0011" "\001L" "Mono   " CHAR_1_PIXEL_GAP_UTF8 TEXT_COLOR_1 "For single-speaker systems. (GBA, etc.)",
    /* DATA CLEAR ------------------------------------- */
        "\0023" "\0013" "\001C" "Clear Data\n"
        "\0021" "\0011" "\001C" "This will delete " TEXT_COLOR_2 "all " TEXT_COLOR_1 "of your save data and start\n"
        "you over from the beginning." TEXT_COLOR_2 " Be careful!"
    /* ------------------------------------------------ */
};

const char *advance_options_label_text[] = {
    "Sound Effects",
    "Music",
#ifdef RUMBLE
    "Rumble",
#endif
    "Show Disclaimer",
    "Alt. Game Select Music",
};

const char *advance_options_desc_text[] = {
    /* NON-JP SFX ------------------------------------- */
        "\0023" "\0013" "\001C" "Sound Effects\n"
        "\0024" "\0011" "\001L" "English   " "\0021" "Use the localized sound effects.\n"
        "\0024" "\0011" "\001L" "Japanese  " "\0021" "Use the original sound effects.",
    /* NON-JP MUSIC ----------------------------------- */
        "\0023" "\0013" "\001C" "Music\n"
        "\0024" "\0011" "\001L" "English   " "\0021" "Use the localized music.\n"
        "\0024" "\0011" "\001L" "Japanese  " "\0021" "Use the original music.",
    /* RUMBLE ----------------------------------------- */
#ifdef RUMBLE
        "\0023" "\0013" "\001C" "Rumble\n"
        "\0024" "\0011" "\001L" "On        " "\0021" "Rumble is active during gameplay.\n"
        "\0024" "\0011" "\001L" "Off       " "\0021" "Rumble is disabled.",
#endif
    /* SHOW DISCLAIMER -------------------------------- */
        "\0023" "\0013" "\001C" "Show Disclaimer\n"
        "\0024" "\0011" "\001L" "Show      " "\0021" "Show the disclaimer at startup.\n"
        "\0024" "\0011" "\001L" "Skip      " "\0021" "Skip the disclaimer at startup.",
    /* ALT GAME SELECT MUSIC --------------------------- */
        "\0023" "\0013" "\001C" "Alt. Game Select Music\n"
        "\0024" "\0011" "\001L" "On        " "\0021" "Use alternate music in Game Select.\n"
        "\0024" "\0011" "\001L" "Off       " "\0021" "Use normal music in Game Select.",
};


// [D_089cfb1c] Audio Options
struct Animation *options_sound_mode_anim[][2] = {
    /* Stereo */ {
        /* Selected   */ anim_options_select_stereo,
        /* Unselected */ anim_options_off_stereo
    },
    /* Monaural */ {
        /* Selected   */ anim_options_select_mono,
        /* Unselected */ anim_options_off_mono
    }
};
