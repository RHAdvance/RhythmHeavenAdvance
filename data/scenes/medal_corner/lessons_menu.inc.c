// [D_089dd5ec] Drum Lessons Menu - Levels
struct MedalCornerLevel lessons_menu_levels[] = {
    /* BASIC_1 */ {
        /* Scene  */ &scene_drum_lesson_basic_1,
        /* Title  */ "Intro 1",
        /* Anim   */ anim_lessons_menu_basic_1,
        /* Medals */ 3
    },
    /* BASIC_2 */ {
        /* Scene  */ &scene_drum_lesson_basic_2,
        /* Title  */ "Intro 2",
        /* Anim   */ anim_lessons_menu_basic_2,
        /* Medals */ 6
    },
    /* SHORT_1 */ {
        /* Scene  */ &scene_drum_lesson_short_1,
        /* Title  */ "Basic 1",
        /* Anim   */ anim_lessons_menu_short_1,
        /* Medals */ 9
    },
    /* SHORT_2 */ {
        /* Scene  */ &scene_drum_lesson_short_2,
        /* Title  */ "Basic 2",
        /* Anim   */ anim_lessons_menu_short_2,
        /* Medals */ 12
    },
    /* SHORT_3 */ {
        /* Scene  */ &scene_drum_lesson_short_3,
        /* Title  */ "Basic 3",
        /* Anim   */ anim_lessons_menu_short_3,
        /* Medals */ 15
    },
    /* SHORT_4 */ {
        /* Scene  */ &scene_drum_lesson_short_4,
        /* Title  */ "Basic 4",
        /* Anim   */ anim_lessons_menu_short_4,
        /* Medals */ 18
    },
    /* SHORT_5 */ {
        /* Scene  */ &scene_drum_lesson_short_5,
        /* Title  */ "Basic 5",
        /* Anim   */ anim_lessons_menu_short_5,
        /* Medals */ 21
    },
    /* SHORT_6 */ {
        /* Scene  */ &scene_drum_lesson_short_6,
        /* Title  */ "Basic 6",
        /* Anim   */ anim_lessons_menu_short_6,
        /* Medals */ 24
    },
    /* SHORT_7 */ {
        /* Scene  */ &scene_drum_lesson_short_7,
        /* Title  */ "Basic 7",
        /* Anim   */ anim_lessons_menu_short_7,
        /* Medals */ 27
    },
    /* SHORT_8 */ {
        /* Scene  */ &scene_drum_lesson_short_8,
        /* Title  */ "Basic 8",
        /* Anim   */ anim_lessons_menu_short_8,
        /* Medals */ 30
    },
    /* SHORT_9 */ {
        /* Scene  */ &scene_drum_lesson_short_9,
        /* Title  */ "Basic 9",
        /* Anim   */ anim_lessons_menu_short_9,
        /* Medals */ 32
    },
    /* LONG_1 */ {
        /* Scene  */ &scene_drum_lesson_long_1,
        /* Title  */ "Advanced 1",
        /* Anim   */ anim_lessons_menu_long_1,
        /* Medals */ 34
    },
    /* LONG_2 */ {
        /* Scene  */ &scene_drum_lesson_long_2,
        /* Title  */ "Advanced 2",
        /* Anim   */ anim_lessons_menu_long_2,
        /* Medals */ 36
    },
    /* LONG_3 */ {
        /* Scene  */ &scene_drum_lesson_long_3,
        /* Title  */ "Advanced 3",
        /* Anim   */ anim_lessons_menu_long_3,
        /* Medals */ 38
    },
    /* LONG_4 */ {
        /* Scene  */ &scene_drum_lesson_long_4,
        /* Title  */ "Advanced 4",
        /* Anim   */ anim_lessons_menu_long_4,
        /* Medals */ 40
    },
    /* LONG_5 */ {
        /* Scene  */ &scene_drum_lesson_long_5,
        /* Title  */ "Advanced 5",
        /* Anim   */ anim_lessons_menu_long_5_6,
        /* Medals */ 42
    },
    /* LONG_6 */ {
        /* Scene  */ &scene_drum_lesson_long_6,
        /* Title  */ "Advanced 6",
        /* Anim   */ anim_lessons_menu_long_5_6,
        /* Medals */ 44
    },
    /* HI_TECH_1 */ {
        /* Scene  */ &scene_drum_lesson_hi_tech_1,
        /* Title  */ "Technical 1",
        /* Anim   */ anim_lessons_menu_hi_tech_1_2,
        /* Medals */ 46
    },
    /* HI_TECH_2 */ {
        /* Scene  */ &scene_drum_lesson_hi_tech_2,
        /* Title  */ "Technical 2",
        /* Anim   */ anim_lessons_menu_hi_tech_1_2,
        /* Medals */ 48
    }
};


// [D_089dd71c] Drum Lessons Menu - Graphics Table
struct GraphicsTable lessons_menu_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &drum_lessons_menu_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &drum_lessons_menu_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &drum_lessons_menu_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &medal_corner_obj,
        /* Dest. */ OBJ_TILESET_BASE(0x5000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ lessons_menu_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ lessons_menu_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    END_OF_GRAPHICS_TABLE
};


// [D_089dd770] Drum Lessons Menu
struct MedalCornerMenu lessons_menu_data = {
    /* Level Count */ TOTAL_DRUM_LESSONS,
    /* Music       */ &s_lesson_sel_bgm_seqData,
    /* Graphics    */ lessons_menu_gfx_table,
    /* Level Data  */ lessons_menu_levels
};


// [D_089dd780] Drum Lessons Menu - Rank Icons
struct Animation *lessons_menu_rank_icons[] = {
    /* 0x00 */ anim_lessons_menu_rank_c,
    /* 0x01 */ anim_lessons_menu_rank_c,
    /* 0x02 */ anim_lessons_menu_rank_b,
    /* 0x03 */ anim_lessons_menu_rank_a,
    /* 0x04 */ anim_lessons_menu_rank_s
};