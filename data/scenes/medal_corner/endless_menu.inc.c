// [D_089dd548] Endless Games Menu - Levels
struct MedalCornerLevel endless_menu_levels[] = {
    /* MR_UPBEAT */ {
        /* Scene  */ &scene_mr_upbeat,	
        #ifdef PARADISE
        /* Title  */ "Mr Upbeat",
        #else
        /* Title  */ "Mr. Upbeat",
        #endif
        /* Anim   */ anim_endless_menu_mr_upbeat,
        /* Medals */ 1
    },
    /* SICK_BEATS */ {
        /* Scene  */ &scene_sick_beats_endless,
        /* Title  */ "Sick Beats Special",
        /* Anim   */ anim_endless_menu_sick_beats,
        /* Medals */ 10
    },
    /* QUIZ_SHOW */ {
        /* Scene  */ &scene_quiz_show_endless,
        /* Title  */ "Quiz Show Special",
        /* Anim   */ anim_endless_menu_quiz_show,
        /* Medals */ 20
    },
    /* MANNEQUIN_FACTORY */ {
        /* Scene  */ &scene_mannequin_factory,
        /* Title  */ "Mannequin Factory",
        /* Anim   */ anim_endless_menu_mannequin,
        /* Medals */ 30
    }
};


// [D_089dd588] Endless Games Menu - Graphics Table
struct GraphicsTable endless_menu_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &endless_games_menu_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &endless_games_menu_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &endless_games_menu_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &medal_corner_obj,
        /* Dest. */ OBJ_TILESET_BASE(0x5000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ endless_menu_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ endless_menu_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    END_OF_GRAPHICS_TABLE
};


// [D_089dd5dc] Endless Games Menu
struct MedalCornerMenu endless_menu_data = {
    /* Level Count */ TOTAL_ENDLESS_GAMES,
    /* Music       */ &s_mini_game_bgm_seqData,
    /* Graphics    */ endless_menu_gfx_table,
    /* Level Data  */ endless_menu_levels
};
