#define INLINE_GFX_TABLE(tiles, map, palette) (struct GraphicsTable[]) {    \
        /* BG Tileset */ {                                                  \
            /* Src.  */ tiles,                                              \
            /* Dest. */ BG_TILESET_BASE(0),                                 \
            /* Size  */ COMPRESSED_GFX_SOURCE                               \
        },                                                                  \
        /* BG Map */ {                                                      \
            /* Src.  */ map,                                                \
            /* Dest. */ BG_MAP_BASE(0xE800),                                \
            /* Size  */ COMPRESSED_GFX_SOURCE                               \
        },                                                                  \
        /* BG Palette */ {                                                  \
            /* Src.  */ palette,                                            \
            /* Dest. */ BG_PALETTE_BUFFER(0),                               \
            /* Size  */ 0x140                                               \
        },                                                                  \
        END_OF_GRAPHICS_TABLE                                               \
    }

// [D_089ce0b0] Karate Man
const struct GraphicsTable *epilogue_karate_man_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&karate_man_epilogue_bg_tiles, &karate_man_epilogue_bg_map_try_again, epilogue_karate_man_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&karate_man_epilogue_bg_tiles, &karate_man_epilogue_bg_map_ok, epilogue_karate_man_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&karate_man_epilogue_bg_tiles, &karate_man_epilogue_bg_map_superb, epilogue_karate_man_bg_pal)
};

// [D_089ce0bc] Karate Man 2
const struct GraphicsTable *epilogue_karate_man_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&karate_man_epilogue_bg_tiles, &karate_man_epilogue_bg_map_try_again, epilogue_karate_man_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&karate_man_epilogue_bg_tiles, &karate_man_epilogue_bg_map_ok, epilogue_karate_man_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&karate_man_epilogue_bg_tiles, &karate_man_epilogue_bg_map_superb, epilogue_karate_man_bg_pal)
};

// [D_089ce0c8] The Clappy Trio
const struct GraphicsTable *epilogue_clappy_trio_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&clappy_trio_epilogue_bg_tiles, &clappy_trio_epilogue_bg_map_try_again, epilogue_clappy_trio_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&clappy_trio_epilogue_bg_tiles, &clappy_trio_epilogue_bg_map_ok, epilogue_clappy_trio_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&clappy_trio_epilogue_bg_tiles, &clappy_trio_epilogue_bg_map_superb, epilogue_clappy_trio_bg_pal)
};

// [D_089ce0d4] The Snappy Trio
const struct GraphicsTable *epilogue_snappy_trio_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&snappy_trio_epilogue_bg_tiles, &snappy_trio_epilogue_bg_map_try_again, epilogue_snappy_trio_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&snappy_trio_epilogue_bg_tiles, &snappy_trio_epilogue_bg_map_ok, epilogue_snappy_trio_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&snappy_trio_epilogue_bg_tiles, &snappy_trio_epilogue_bg_map_superb, epilogue_snappy_trio_bg_pal)
};

// [D_089ce0e0] Polyrhythm
const struct GraphicsTable *epilogue_polyrhythm_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&polyrhythm_epilogue_bg_tiles, &polyrhythm_epilogue_bg_map_try_again, epilogue_polyrhythm_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&polyrhythm_epilogue_bg_tiles, &polyrhythm_epilogue_bg_map_ok, epilogue_polyrhythm_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&polyrhythm_epilogue_bg_tiles, &polyrhythm_epilogue_bg_map_superb, epilogue_polyrhythm_bg_pal)
};

// [D_089ce0ec] Polyrhythm 2
const struct GraphicsTable *epilogue_polyrhythm_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&polyrhythm_epilogue_bg_tiles, &polyrhythm_epilogue_bg_map_try_again, epilogue_polyrhythm_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&polyrhythm_epilogue_bg_tiles, &polyrhythm_epilogue_bg_map_ok, epilogue_polyrhythm_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&polyrhythm_epilogue_bg_tiles, &polyrhythm_epilogue_bg_map_superb, epilogue_polyrhythm_bg_pal)
};

// [D_089ce0f8] Night Walk
const struct GraphicsTable *epilogue_night_walk_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&night_walk_epilogue_bg_tiles, &night_walk_epilogue_bg_map_try_again, epilogue_night_walk_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&night_walk_epilogue_bg_tiles, &night_walk_epilogue_bg_map_ok, epilogue_night_walk_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&night_walk_epilogue_bg_tiles, &night_walk_epilogue_bg_map_superb, epilogue_night_walk_bg_pal)
};

// [D_089ce104] Night Walk 2
const struct GraphicsTable *epilogue_night_walk_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&night_walk_epilogue_bg_tiles, &night_walk_epilogue_bg_map_try_again, epilogue_night_walk_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&night_walk_epilogue_bg_tiles, &night_walk_epilogue_bg_map_ok, epilogue_night_walk_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&night_walk_epilogue_bg_tiles, &night_walk_epilogue_bg_map_superb, epilogue_night_walk_bg_pal)
};

// [D_089ce110] Rhythm Tweezers
const struct GraphicsTable *epilogue_rhythm_tweezers_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_try_again, epilogue_rhythm_tweezers_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_ok, epilogue_rhythm_tweezers_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_superb, epilogue_rhythm_tweezers_bg_pal)
};

// [D_089ce11c] Rhythm Tweezers 2
const struct GraphicsTable *epilogue_rhythm_tweezers_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_try_again, epilogue_rhythm_tweezers_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_ok, epilogue_rhythm_tweezers_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_superb, epilogue_rhythm_tweezers_bg_pal)
};

// [D_089ce128] Sick Beats
const struct GraphicsTable *epilogue_sick_beats_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&sick_beats_epilogue_bg_tiles, &sick_beats_epilogue_bg_map_try_again, epilogue_sick_beats_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&sick_beats_epilogue_bg_tiles, &sick_beats_epilogue_bg_map_ok, epilogue_sick_beats_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&sick_beats_epilogue_bg_tiles, &sick_beats_epilogue_bg_map_superb, epilogue_sick_beats_bg_pal)
};

// [D_089ce134] Bouncy Road
const struct GraphicsTable *epilogue_bouncy_road_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&bouncy_road_epilogue_bg_tiles, &bouncy_road_epilogue_bg_map_try_again, epilogue_bouncy_road_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&bouncy_road_epilogue_bg_tiles, &bouncy_road_epilogue_bg_map_ok, epilogue_bouncy_road_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&bouncy_road_epilogue_bg_tiles, &bouncy_road_epilogue_bg_map_superb, epilogue_bouncy_road_bg_pal)
};

// [D_089ce140] Bouncy Road 2
const struct GraphicsTable *epilogue_bouncy_road_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&bouncy_road_epilogue_bg_tiles, &bouncy_road_epilogue_bg_map_try_again, epilogue_bouncy_road_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&bouncy_road_epilogue_bg_tiles, &bouncy_road_epilogue_bg_map_ok, epilogue_bouncy_road_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&bouncy_road_epilogue_bg_tiles, &bouncy_road_epilogue_bg_map_superb, epilogue_bouncy_road_bg_pal)
};

// [D_089ce14c] Ninja Bodyguard
const struct GraphicsTable *epilogue_ninja_bodyguard_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&ninja_bodyguard_epilogue_bg_tiles, &ninja_bodyguard_epilogue_bg_map_try_again, epilogue_ninja_bodyguard_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&ninja_bodyguard_epilogue_bg_tiles, &ninja_bodyguard_epilogue_bg_map_ok, epilogue_ninja_bodyguard_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&ninja_bodyguard_epilogue_bg_tiles, &ninja_bodyguard_epilogue_bg_map_superb, epilogue_ninja_bodyguard_bg_pal)
};

// [D_089ce158] Ninja Reincarnate
const struct GraphicsTable *epilogue_ninja_reincarnate_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&ninja_reincarnate_epilogue_bg_tiles, &ninja_reincarnate_epilogue_bg_map_try_again, epilogue_ninja_reincarnate_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&ninja_reincarnate_epilogue_bg_tiles, &ninja_reincarnate_epilogue_bg_map_ok, epilogue_ninja_reincarnate_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&ninja_reincarnate_epilogue_bg_tiles, &ninja_reincarnate_epilogue_bg_map_superb, epilogue_ninja_reincarnate_bg_pal)
};

// [D_089ce164] Sneaky Spirits
const struct GraphicsTable *epilogue_sneaky_spirits_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&sneaky_spirits_epilogue_bg_tiles, &sneaky_spirits_epilogue_bg_map_try_again, epilogue_sneaky_spirits_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&sneaky_spirits_epilogue_bg_tiles, &sneaky_spirits_epilogue_bg_map_ok, epilogue_sneaky_spirits_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&sneaky_spirits_epilogue_bg_tiles, &sneaky_spirits_epilogue_bg_map_superb, epilogue_sneaky_spirits_bg_pal)
};

// [D_089ce170] Sneaky Spirits 2
const struct GraphicsTable *epilogue_sneaky_spirits_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&sneaky_spirits_epilogue_bg_tiles, &sneaky_spirits_epilogue_bg_map_try_again, epilogue_sneaky_spirits_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&sneaky_spirits_epilogue_bg_tiles, &sneaky_spirits_epilogue_bg_map_ok, epilogue_sneaky_spirits_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&sneaky_spirits_epilogue_bg_tiles, &sneaky_spirits_epilogue_bg_map_superb, epilogue_sneaky_spirits_bg_pal)
};

// [D_089ce17c] Samurai Slice
const struct GraphicsTable *epilogue_samurai_slice_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&samurai_slice_epilogue_bg_tiles, &samurai_slice_epilogue_bg_map_try_again, epilogue_samurai_slice_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&samurai_slice_epilogue_bg_tiles, &samurai_slice_epilogue_bg_map_ok, epilogue_samurai_slice_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&samurai_slice_epilogue_bg_tiles, &samurai_slice_epilogue_bg_map_superb, epilogue_samurai_slice_bg_pal)
};

// [D_089ce188] Spaceball
const struct GraphicsTable *epilogue_spaceball_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_try_again, epilogue_spaceball_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_ok, epilogue_spaceball_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_superb, epilogue_spaceball_bg_pal)
};

// [D_089ce194] Spaceball 2
const struct GraphicsTable *epilogue_spaceball_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_try_again, epilogue_spaceball_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_ok, epilogue_spaceball_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_superb, epilogue_spaceball_bg_pal)
};

// [D_089ce1a0] Tap Trial
const struct GraphicsTable *epilogue_tap_trial_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&tap_trial_epilogue_bg_tiles, &tap_trial_epilogue_bg_map_try_again, epilogue_tap_trial_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&tap_trial_epilogue_bg_tiles, &tap_trial_epilogue_bg_map_ok, epilogue_tap_trial_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&tap_trial_epilogue_bg_tiles, &tap_trial_epilogue_bg_map_superb, epilogue_tap_trial_bg_pal)
};

// [D_089ce1ac] Tap Trial 2
const struct GraphicsTable *epilogue_tap_trial_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&tap_trial_2_epilogue_bg_tiles, &tap_trial_2_epilogue_bg_map_try_again, epilogue_tap_trial_2_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&tap_trial_2_epilogue_bg_tiles, &tap_trial_2_epilogue_bg_map_ok, epilogue_tap_trial_2_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&tap_trial_2_epilogue_bg_tiles, &tap_trial_2_epilogue_bg_map_superb, epilogue_tap_trial_2_bg_pal)
};

// [D_089ce1b8] Marching Orders
const struct GraphicsTable *epilogue_marching_orders_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&marching_orders_epilogue_bg_tiles, &marching_orders_epilogue_bg_map_try_again, epilogue_marching_orders_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&marching_orders_epilogue_bg_tiles, &marching_orders_epilogue_bg_map_ok, epilogue_marching_orders_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&marching_orders_epilogue_bg_tiles, &marching_orders_epilogue_bg_map_superb, epilogue_marching_orders_bg_pal)
};

// [D_089ce1c4] Marching Orders 2
const struct GraphicsTable *epilogue_marching_orders_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&marching_orders_2_epilogue_bg_tiles, &marching_orders_2_epilogue_bg_map_try_again, epilogue_marching_orders_2_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&marching_orders_2_epilogue_bg_tiles, &marching_orders_2_epilogue_bg_map_ok, epilogue_marching_orders_2_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&marching_orders_2_epilogue_bg_tiles, &marching_orders_2_epilogue_bg_map_superb, epilogue_marching_orders_2_bg_pal)
};

// [D_089ce1d0] Wizard's Waltz
const struct GraphicsTable *epilogue_wizards_waltz_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&wizards_waltz_epilogue_bg_tiles, &wizards_waltz_epilogue_bg_map_try_again, epilogue_wizards_waltz_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&wizards_waltz_epilogue_bg_tiles, &wizards_waltz_epilogue_bg_map_ok, epilogue_wizards_waltz_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&wizards_waltz_epilogue_bg_tiles, &wizards_waltz_epilogue_bg_map_superb, epilogue_wizards_waltz_bg_pal)
};

// [D_089ce1dc] Bunny Hop
const struct GraphicsTable *epilogue_bunny_hop_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&bunny_hop_epilogue_bg_tiles, &bunny_hop_epilogue_bg_map_try_again, epilogue_bunny_hop_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&bunny_hop_epilogue_bg_tiles, &bunny_hop_epilogue_bg_map_ok, epilogue_bunny_hop_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&bunny_hop_epilogue_bg_tiles, &bunny_hop_epilogue_bg_map_superb, epilogue_bunny_hop_bg_pal)
};

// [D_089ce1e8] Fireworks
const struct GraphicsTable *epilogue_fireworks_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&fireworks_epilogue_bg_tiles, &fireworks_epilogue_bg_map_try_again, epilogue_fireworks_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&fireworks_epilogue_bg_tiles, &fireworks_epilogue_bg_map_ok, epilogue_fireworks_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&fireworks_epilogue_bg_tiles, &fireworks_epilogue_bg_map_superb, epilogue_fireworks_bg_pal)
};

// [D_089ce1f4] Power Calligraphy
const struct GraphicsTable *epilogue_power_power_calligraphy_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&power_calligraphy_epilogue_bg_tiles, &power_calligraphy_epilogue_bg_map_try_again, epilogue_power_calligraphy_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&power_calligraphy_epilogue_bg_tiles, &power_calligraphy_epilogue_bg_map_ok, epilogue_power_calligraphy_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&power_calligraphy_epilogue_bg_tiles, &power_calligraphy_epilogue_bg_map_superb, epilogue_power_calligraphy_bg_pal)
};

// [D_089ce200] Power Calligraphy 2
const struct GraphicsTable *epilogue_power_calligraphy_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&power_calligraphy_epilogue_bg_tiles, &power_calligraphy_epilogue_bg_map_try_again, epilogue_power_calligraphy_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&power_calligraphy_epilogue_bg_tiles, &power_calligraphy_epilogue_bg_map_ok, epilogue_power_calligraphy_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&power_calligraphy_epilogue_bg_tiles, &power_calligraphy_epilogue_bg_map_superb, epilogue_power_calligraphy_bg_pal)
};

// [D_089ce20c] Toss Boys
const struct GraphicsTable *epilogue_toss_boys_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&toss_boys_epilogue_bg_tiles, &toss_boys_epilogue_bg_map_try_again, epilogue_toss_boys_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&toss_boys_epilogue_bg_tiles, &toss_boys_epilogue_bg_map_ok, epilogue_toss_boys_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&toss_boys_epilogue_bg_tiles, &toss_boys_epilogue_bg_map_superb, epilogue_toss_boys_bg_pal)
};

// [D_089ce218] Toss Boys 2
const struct GraphicsTable *epilogue_toss_boys_2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&toss_boys_2_epilogue_bg_tiles, &toss_boys_2_epilogue_bg_map_try_again, epilogue_toss_boys_2_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&toss_boys_2_epilogue_bg_tiles, &toss_boys_2_epilogue_bg_map_ok, epilogue_toss_boys_2_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&toss_boys_2_epilogue_bg_tiles, &toss_boys_2_epilogue_bg_map_superb, epilogue_toss_boys_2_bg_pal)
};

// [D_089ce224] Rat Race
const struct GraphicsTable *epilogue_rat_race_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&rat_race_epilogue_bg_tiles, &rat_race_epilogue_bg_map_try_again, epilogue_rat_race_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&rat_race_epilogue_bg_tiles, &rat_race_epilogue_bg_map_ok, epilogue_rat_race_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&rat_race_epilogue_bg_tiles, &rat_race_epilogue_bg_map_superb, epilogue_rat_race_bg_pal)
};

// [D_089ce230] Tram & Pauline
const struct GraphicsTable *epilogue_tram_pauline_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&tram_pauline_epilogue_bg_tiles, &tram_pauline_epilogue_bg_map_try_again, epilogue_tram_pauline_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&tram_pauline_epilogue_bg_tiles, &tram_pauline_epilogue_bg_map_ok, epilogue_tram_pauline_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&tram_pauline_epilogue_bg_tiles, &tram_pauline_epilogue_bg_map_superb, epilogue_tram_pauline_bg_pal)
};

// [D_089ce23c] Showtime
const struct GraphicsTable *epilogue_showtime_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&showtime_epilogue_bg_tiles, &showtime_epilogue_bg_map_try_again, epilogue_showtime_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&showtime_epilogue_bg_tiles, &showtime_epilogue_bg_map_ok, epilogue_showtime_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&showtime_epilogue_bg_tiles, &showtime_epilogue_bg_map_superb, epilogue_showtime_bg_pal)
};

// [D_089ce248] Space Dance
const struct GraphicsTable *epilogue_space_dance_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&space_dance_epilogue_bg_tiles, &space_dance_epilogue_bg_map_try_again, epilogue_space_dance_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&space_dance_epilogue_bg_tiles, &space_dance_epilogue_bg_map_ok, epilogue_space_dance_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&space_dance_epilogue_bg_tiles, &space_dance_epilogue_bg_map_superb, epilogue_space_dance_bg_pal)
};

// [D_089ce254] Cosmic Dance
const struct GraphicsTable *epilogue_cosmic_dance_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&cosmic_dance_epilogue_bg_tiles, &cosmic_dance_epilogue_bg_map_try_again, epilogue_cosmic_dance_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&cosmic_dance_epilogue_bg_tiles, &cosmic_dance_epilogue_bg_map_ok, epilogue_cosmic_dance_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&cosmic_dance_epilogue_bg_tiles, &cosmic_dance_epilogue_bg_map_superb, epilogue_cosmic_dance_bg_pal)
};

// [D_089ce260] Rap Men
const struct GraphicsTable *epilogue_rap_men_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&rap_men_epilogue_bg_tiles, &rap_men_epilogue_bg_map_try_again, epilogue_rap_men_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&rap_men_epilogue_bg_tiles, &rap_men_epilogue_bg_map_ok, epilogue_rap_men_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&rap_men_epilogue_bg_tiles, &rap_men_epilogue_bg_map_superb, epilogue_rap_men_bg_pal)
};

// [D_089ce26c] Rap Women
const struct GraphicsTable *epilogue_rap_women_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&rap_women_epilogue_bg_tiles, &rap_women_epilogue_bg_map_try_again, epilogue_rap_women_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&rap_women_epilogue_bg_tiles, &rap_women_epilogue_bg_map_ok, epilogue_rap_women_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&rap_women_epilogue_bg_tiles, &rap_women_epilogue_bg_map_superb, epilogue_rap_women_bg_pal)
};

// [D_089ce278] Quiz Show
const struct GraphicsTable *epilogue_quiz_show_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&quiz_show_epilogue_bg_tiles, &quiz_show_epilogue_bg_map_try_again, epilogue_quiz_show_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&quiz_show_epilogue_bg_tiles, &quiz_show_epilogue_bg_map_ok, epilogue_quiz_show_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&quiz_show_epilogue_bg_tiles, &quiz_show_epilogue_bg_map_superb, epilogue_quiz_show_bg_pal)
};

// [D_089ce284] The Bon Odori
const struct GraphicsTable *epilogue_bon_odori_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&bon_odori_epilogue_bg_tiles, &bon_odori_epilogue_bg_map_try_again, epilogue_bon_odori_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&bon_odori_epilogue_bg_tiles, &bon_odori_epilogue_bg_map_ok, epilogue_bon_odori_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&bon_odori_epilogue_bg_tiles, &bon_odori_epilogue_bg_map_superb, epilogue_bon_odori_bg_pal)
};

// [D_089ce290] Bon Dance
const struct GraphicsTable *epilogue_bon_dance_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&bon_dance_epilogue_bg_tiles, &bon_dance_epilogue_bg_map_try_again, epilogue_bon_dance_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&bon_dance_epilogue_bg_tiles, &bon_dance_epilogue_bg_map_ok, epilogue_bon_dance_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&bon_dance_epilogue_bg_tiles, &bon_dance_epilogue_bg_map_superb, epilogue_bon_dance_bg_pal)
};

// [D_089ce29c] Remix 1
const struct GraphicsTable *epilogue_remix1_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_1_epilogue_bg_tiles, &remix_1_epilogue_bg_map_try_again, epilogue_remix1_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_1_epilogue_bg_tiles, &remix_1_epilogue_bg_map_ok, epilogue_remix1_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_1_epilogue_bg_tiles, &remix_1_epilogue_bg_map_superb, epilogue_remix1_bg_pal)
};

// [D_089ce2a8] Remix 2
const struct GraphicsTable *epilogue_remix2_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_2_epilogue_bg_tiles, &remix_2_epilogue_bg_map_try_again, epilogue_remix2_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_2_epilogue_bg_tiles, &remix_2_epilogue_bg_map_ok, epilogue_remix2_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_2_epilogue_bg_tiles, &remix_2_epilogue_bg_map_superb, epilogue_remix2_bg_pal)
};

// [D_089ce2b4] Remix 3
const struct GraphicsTable *epilogue_remix3_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_3_epilogue_bg_tiles, &remix_3_epilogue_bg_map_try_again, epilogue_remix3_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_3_epilogue_bg_tiles, &remix_3_epilogue_bg_map_ok, epilogue_remix3_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_3_epilogue_bg_tiles, &remix_3_epilogue_bg_map_superb, epilogue_remix3_bg_pal)
};

// [D_089ce2c0] Remix 4
const struct GraphicsTable *epilogue_remix4_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_4_epilogue_bg_tiles, &remix_4_epilogue_bg_map_try_again, epilogue_remix4_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_4_epilogue_bg_tiles, &remix_4_epilogue_bg_map_ok, epilogue_remix4_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_4_epilogue_bg_tiles, &remix_4_epilogue_bg_map_superb, epilogue_remix4_bg_pal)
};

// [D_089ce2cc] Remix 5
const struct GraphicsTable *epilogue_remix5_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_5_epilogue_bg_tiles, &remix_5_epilogue_bg_map_try_again, epilogue_remix5_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_5_epilogue_bg_tiles, &remix_5_epilogue_bg_map_ok, epilogue_remix5_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_5_epilogue_bg_tiles, &remix_5_epilogue_bg_map_superb, epilogue_remix5_bg_pal)
};

// [D_089ce2d8] Remix 6
const struct GraphicsTable *epilogue_remix6_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_6_epilogue_bg_tiles, &remix_6_epilogue_bg_map_try_again, epilogue_remix6_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_6_epilogue_bg_tiles, &remix_6_epilogue_bg_map_ok, epilogue_remix6_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_6_epilogue_bg_tiles, &remix_6_epilogue_bg_map_superb, epilogue_remix6_bg_pal)
};

// [D_089ce2e4] Remix 7
const struct GraphicsTable *epilogue_remix7_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_7_epilogue_bg_tiles, &remix_7_epilogue_bg_map_try_again, epilogue_remix7_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_7_epilogue_bg_tiles, &remix_7_epilogue_bg_map_ok, epilogue_remix7_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_7_epilogue_bg_tiles, &remix_7_epilogue_bg_map_superb, epilogue_remix7_bg_pal)
};

// [D_089ce2f0] Remix 8
const struct GraphicsTable *epilogue_remix8_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_8_epilogue_bg_tiles, &remix_8_epilogue_bg_map_try_again, epilogue_remix8_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_8_epilogue_bg_tiles, &remix_8_epilogue_bg_map_ok, epilogue_remix8_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_8_epilogue_bg_tiles, &remix_8_epilogue_bg_map_superb, epilogue_remix8_bg_pal)
};

// [D_089ce2fc] Cafe
const struct GraphicsTable *epilogue_cafe_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_try_again, epilogue_placeholder_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_ok, epilogue_placeholder_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_superb, epilogue_placeholder_bg_pal)
};

// [D_089ce308] Rhythm Toys Menu
const struct GraphicsTable *epilogue_toys_menu_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_try_again, epilogue_placeholder_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_ok, epilogue_placeholder_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_superb, epilogue_placeholder_bg_pal)
};

// [D_089ce314] Endless Games Menu
const struct GraphicsTable *epilogue_endless_menu_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_try_again, epilogue_placeholder_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_ok, epilogue_placeholder_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_superb, epilogue_placeholder_bg_pal)
};

// [D_089ce320] Drum Lessons Menu
const struct GraphicsTable *epilogue_lessons_menu_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_try_again, epilogue_placeholder_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_ok, epilogue_placeholder_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_superb, epilogue_placeholder_bg_pal)
};

// [D_089ce32c] Staff Credit
const struct GraphicsTable *epilogue_staff_credit_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_try_again, epilogue_placeholder_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_ok, epilogue_placeholder_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&placeholder_epilogue_bg_tiles, &placeholder_epilogue_bg_map_superb, epilogue_placeholder_bg_pal)
};

// [D_089ce338] LIVE
const struct GraphicsTable *epilogue_drum_live_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&drum_live_epilogue_bg_tiles, &drum_live_epilogue_bg_map_try_again, epilogue_drum_live_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&drum_live_epilogue_bg_tiles, &drum_live_epilogue_bg_map_ok, epilogue_drum_live_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&drum_live_epilogue_bg_tiles, &drum_live_epilogue_bg_map_superb, epilogue_drum_live_bg_pal)
};

// Extra Games

const struct GraphicsTable *epilogue_karate_man_extra_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&karate_man_extra_epilogue_bg_tiles, &karate_man_extra_epilogue_bg_map_try_again, epilogue_karate_man_extra_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&karate_man_extra_epilogue_bg_tiles, &karate_man_extra_epilogue_bg_map_ok, epilogue_karate_man_extra_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&karate_man_extra_epilogue_bg_tiles, &karate_man_extra_epilogue_bg_map_superb, epilogue_karate_man_extra_bg_pal)
};

const struct GraphicsTable *epilogue_rhythm_tweezers_extra_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_try_again, epilogue_rhythm_tweezers_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_ok, epilogue_rhythm_tweezers_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&rhythm_tweezers_epilogue_bg_tiles, &rhythm_tweezers_epilogue_bg_map_superb, epilogue_rhythm_tweezers_bg_pal)
};

const struct GraphicsTable *epilogue_marching_orders_extra_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&marching_orders_epilogue_bg_tiles, &marching_orders_epilogue_bg_map_try_again, epilogue_marching_orders_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&marching_orders_epilogue_bg_tiles, &marching_orders_epilogue_bg_map_ok, epilogue_marching_orders_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&marching_orders_epilogue_bg_tiles, &marching_orders_epilogue_bg_map_superb, epilogue_marching_orders_bg_pal)
};

const struct GraphicsTable *epilogue_spaceball_extra_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_try_again, epilogue_spaceball_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_ok, epilogue_spaceball_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&spaceball_epilogue_bg_tiles, &spaceball_epilogue_bg_map_superb, epilogue_spaceball_bg_pal)
};

const struct GraphicsTable *epilogue_clappy_trio_extra_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&clappy_trio_epilogue_bg_tiles, &clappy_trio_epilogue_bg_map_try_again, epilogue_clappy_trio_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&clappy_trio_epilogue_bg_tiles, &clappy_trio_epilogue_bg_map_ok, epilogue_clappy_trio_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&clappy_trio_epilogue_bg_tiles, &clappy_trio_epilogue_bg_map_superb, epilogue_clappy_trio_bg_pal)
};

const struct GraphicsTable *epilogue_remix1_extra_gfx_tables[] = {
    /* TRY AGAIN */ INLINE_GFX_TABLE(&remix_1_epilogue_bg_tiles, &remix_1_epilogue_bg_map_try_again, epilogue_remix1_bg_pal),
    /* JUST OK   */ INLINE_GFX_TABLE(&remix_1_epilogue_bg_tiles, &remix_1_epilogue_bg_map_ok, epilogue_remix1_bg_pal),
    /* SUPERB    */ INLINE_GFX_TABLE(&remix_1_epilogue_bg_tiles, &remix_1_epilogue_bg_map_superb, epilogue_remix1_bg_pal)
};