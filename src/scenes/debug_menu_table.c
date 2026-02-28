#include "global.h"
#include "debug_menu.h"


/* DEBUG MENU TABLE */


// [D_089ddbe8] Debug Menu Table
struct DebugMenuEntry debug_menu_entry_table[] = {
    /* Drum LIVE */ {
        /* Scene */ &scene_drum_live,
        /* Label */ "‚b‚‚Ž‚ƒ‚…‚’‚”",
        /* Epil. */ TRUE
    },
    /* Sick Beats Endless */ {
        /* Scene */ &scene_sick_beats_endless,
        /* Label */ "‚r‚‰‚ƒ‚‹@‚a‚…‚‚”‚“@‚r‚o",
        /* Epil. */ FALSE
    },
    /* Quiz Show Endless */ {
        /* Scene */ &scene_quiz_show_endless,
        /* Label */ "‚p‚•‚‰‚š@‚r‚ˆ‚‚—@‚r‚o",
        /* Epil. */ FALSE
    },
    /* Mannequin Factory */ {
        /* Scene */ &scene_mannequin_factory,
        /* Label */ "‚l‚‚Ž‚Ž‚…‚‘‚•‚‰‚Ž@‚e‚‚ƒ‚”‚‚’‚™",
        /* Epil. */ FALSE
    },
    /* Mr. Upbeat */ {
        /* Scene */ &scene_mr_upbeat,
        /* Label */ "‚l‚’D@‚t‚‚‚‚…‚‚”",
        /* Epil. */ FALSE
    },
    /* Remix 8 */ {
        /* Scene */ &scene_remix_8,
        /* Label */ "‚q‚…‚‚‰‚˜@‚W",
        /* Epil. */ TRUE
    },
    /* Remix 7 */ {
        /* Scene */ &scene_remix_7,
        /* Label */ "‚q‚…‚‚‰‚˜@‚V",
        /* Epil. */ TRUE
    },
    /* Remix 6 */ {
        /* Scene */ &scene_remix_6,
        /* Label */ "‚q‚…‚‚‰‚˜@‚U",
        /* Epil. */ TRUE
    },
    /* Remix 5 */ {
        /* Scene */ &scene_remix_5,
        /* Label */ "‚q‚…‚‚‰‚˜@‚T",
        /* Epil. */ TRUE
    },
    /* Remix 4 */ {
        /* Scene */ &scene_remix_4,
        /* Label */ "‚q‚…‚‚‰‚˜@‚S",
        /* Epil. */ TRUE
    },
    /* Remix 3 */ {
        /* Scene */ &scene_remix_3,
        /* Label */ "‚q‚…‚‚‰‚˜@‚R",
        /* Epil. */ TRUE
    },
    /* Remix 2 */ {
        /* Scene */ &scene_remix_2,
        /* Label */ "‚q‚…‚‚‰‚˜@‚Q",
        /* Epil. */ TRUE
    },
    /* Remix 1 */ {
        /* Scene */ &scene_remix_1,
        /* Label */ "‚q‚…‚‚‰‚˜@‚P",
        /* Epil. */ TRUE
    },
    /* Remix 1 (Tempo Up) */ {
        /* Scene */ &scene_remix_1_extra,
        /* Label */ "‚q‚…‚‚‰‚˜@‚P@i‚s‚…‚‚‚@‚t‚j",
        /* Epil. */ TRUE
    },
    /* The Bon Odori */ {
        /* Scene */ &scene_bon_odori,
        /* Label */ "‚s‚ˆ‚…@‚a‚‚Ž@‚n‚„‚‚’‚‰",
        /* Epil. */ TRUE
    },
    /* Bon Dance */ {
        /* Scene */ &scene_bon_dance,
        /* Label */ "‚s‚ˆ‚…@‚a‚‚Ž@‚c‚‚Ž‚ƒ‚…",
        /* Epil. */ TRUE
    },
    /* Rhythm Toys (Cat Machine) */ {
        /* Scene */ &scene_cat_machine,
        /* Label */ "‚b‚‚”@‚l‚‚ƒ‚ˆ‚‰‚Ž‚…",
        /* Epil. */ FALSE
    },
    /* Rhythm Toys (Confession Machine) */ {
        /* Scene */ &scene_love_machine,
        /* Label */ "‚k‚‚–‚…@‚l‚‚ƒ‚ˆ‚‰‚Ž‚…",
        /* Epil. */ FALSE
    },
    /* Rhythm Toys (Rap Machine) */ {
        /* Scene */ &scene_rap_machine,
        /* Label */ "‚q‚‚@‚l‚‚ƒ‚ˆ‚‰‚Ž‚…",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 1) */ {
        /* Scene */ &scene_drum_lesson_short_1,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Pj",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 4) */ {
        /* Scene */ &scene_drum_lesson_short_4,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Sj",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 8) */ {
        /* Scene */ &scene_drum_lesson_short_8,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Wj",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 5) */ {
        /* Scene */ &scene_drum_lesson_short_5,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Tj",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 7) */ {
        /* Scene */ &scene_drum_lesson_short_7,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Vj",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 6) */ {
        /* Scene */ &scene_drum_lesson_short_6,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Uj",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 9) */ {
        /* Scene */ &scene_drum_lesson_short_9,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Xj",
        /* Epil. */ FALSE
    },
    /* Lesson (Basic 1) */ {
        /* Scene */ &scene_drum_lesson_basic_1,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚a‚‚“‚‰‚ƒ@‚Pj",
        /* Epil. */ FALSE
    },
    /* Lesson (Basic 2) */ {
        /* Scene */ &scene_drum_lesson_basic_2,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚a‚‚“‚‰‚ƒ@‚Qj",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 2) */ {
        /* Scene */ &scene_drum_lesson_short_2,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Qj",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 3) */ {
        /* Scene */ &scene_drum_lesson_short_3,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚r‚ˆ‚‚’‚”@‚Rj",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 4) */ {
        /* Scene */ &scene_drum_lesson_long_4,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚k‚‚Ž‚‡@‚Sj",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 2) */ {
        /* Scene */ &scene_drum_lesson_long_2,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚k‚‚Ž‚‡@‚Qj",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 3) */ {
        /* Scene */ &scene_drum_lesson_long_3,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚k‚‚Ž‚‡@‚Rj",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 1) */ {
        /* Scene */ &scene_drum_lesson_long_1,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚k‚‚Ž‚‡@‚Pj",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 5) */ {
        /* Scene */ &scene_drum_lesson_long_5,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚k‚‚Ž‚‡@‚Tj",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 6) */ {
        /* Scene */ &scene_drum_lesson_long_6,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚k‚‚Ž‚‡@‚Uj",
        /* Epil. */ FALSE
    },
    /* Lesson (High-Tech 1) */ {
        /* Scene */ &scene_drum_lesson_hi_tech_1,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚s‚…‚ƒ‚ˆ‚Ž‚‰‚ƒ‚‚Œ@‚Pj",
        /* Epil. */ FALSE
    },
    /* Lesson (High-Tech 2) */ {
        /* Scene */ &scene_drum_lesson_hi_tech_2,
        /* Label */ "‚k‚…‚“‚“‚‚Ž@i‚s‚…‚ƒ‚ˆ‚Ž‚‰‚ƒ‚‚Œ@‚Qj",
        /* Epil. */ FALSE
    },
    /* Studio Drummer */ {
        /* Scene */ &scene_drum_studio_ver0,
        /* Label */ "‚r‚”‚•‚„‚‰‚@‚c‚’‚•‚‚“@i‚u‚…‚’D‚Oj",
        /* Epil. */ FALSE
    },
    /* Studio Drummer */ {
        /* Scene */ &scene_drum_studio_ver2,
        /* Label */ "‚r‚”‚•‚„‚‰‚@‚c‚’‚•‚‚“@i‚u‚…‚’D‚Qj",
        /* Epil. */ FALSE
    },
    /* Rhythm Test */ {
        /* Scene */ &scene_rhythm_test,
        /* Label */ "‚q‚ˆ‚™‚”‚ˆ‚@‚s‚…‚“‚”",
        /* Epil. */ FALSE
    },
    /* Reading Material */ {
        /* Scene */ &scene_reading,
        /* Label */ "‚d‚‚‚‰‚Œ",
        /* Epil. */ FALSE
    },
    /* Quiz Show */ {
        /* Scene */ &scene_quiz_show,
        /* Label */ "‚p‚•‚‰‚š@‚r‚ˆ‚‚—",
        /* Epil. */ TRUE
    },
    /* Rap Men */ {
        /* Scene */ &scene_rap_men,
        /* Label */ "‚q‚`‚o‚l‚d‚m",
        /* Epil. */ TRUE
    },
    /* Rap Women (by YONE) */ {
        /* Scene */ &scene_rap_women,
        /* Label */ "‚q‚`‚o‚v‚n‚l‚d‚m@i‚‚‚™@‚x‚n‚m‚dj",
        /* Epil. */ TRUE
    },
    /* Rap Women (by KAZU) */ {
        /* Scene */ &scene_rap_women_unused,
        /* Label */ "‚q‚`‚o‚v‚n‚l‚d‚m@i‚a‚™@‚j‚`‚y‚tj",
        /* Epil. */ TRUE
    },
    /* Space Dance */ {
        /* Scene */ &scene_space_dance,
        /* Label */ "‚r‚‚‚ƒ‚…@‚c‚‚Ž‚ƒ‚…",
        /* Epil. */ TRUE
    },
    /* Cosmic Dance */ {
        /* Scene */ &scene_cosmic_dance,
        /* Label */ "‚b‚‚“‚‚‰‚ƒ@‚c‚‚Ž‚ƒ‚…",
        /* Epil. */ TRUE
    },
    /* Showtime */ {
        /* Scene */ &scene_showtime,
        /* Label */ "‚r‚ˆ‚‚—‚”‚‰‚‚…",
        /* Epil. */ TRUE
    },
    /* RIQ Data Check */ {
        /* Scene */ &scene_data_check,
        /* Label */ "‚q|‚h‚p@‚c‚‚”‚@‚b‚ˆ‚…‚ƒ‚‹",
        /* Epil. */ FALSE
    },
    /* Opening (B Type) */ {
        /* Scene */ &scene_drum_samurai_opening_cutscene,
        /* Label */ "‚n‚‚…‚Ž‚‰‚Ž‚‡@i‚s‚™‚‚…@‚aj",
        /* Epil. */ FALSE
    },
    /* Opening (A Type) */ {
        /* Scene */ &scene_drum_samurai_demo_cutscene,
        /* Label */ "‚n‚‚…‚Ž‚‰‚Ž‚‡@i‚s‚™‚‚…@‚`j",
        /* Epil. */ FALSE
    },
    /* Drum Inrto (Unused 1) */ {
        /* Scene */ &scene_drum_intro_unused,
        /* Label */ "‚c‚’‚•‚@‚h‚Ž‚”‚’‚@i‚t‚Ž‚•‚“‚…‚„j",
        /* Epil. */ TRUE
    },
    /* Drum Intro (Unused 2) */ {
        /* Scene */ &scene_drum_intro_unused_2,
        /* Label */ "‚c‚’‚•‚@‚h‚Ž‚”‚’‚@i‚t‚Ž‚•‚“‚…‚„@‚Qj",
        /* Epil. */ TRUE
    },
    /* Drum Intro (Unused 3) */ {
        /* Scene */ &scene_drum_intro_unused_3,
        /* Label */ "‚c‚’‚•‚@‚h‚Ž‚”‚’‚@i‚t‚Ž‚•‚“‚…‚„@‚Rj",
        /* Epil. */ TRUE
    },
    /* Tram & Pauline */ {
        /* Scene */ &scene_tram_pauline,
        /* Label */ "‚s‚’‚‚@•@‚o‚‚•‚Œ‚‰‚Ž‚…",
        /* Epil. */ TRUE
    },
    /* Toss Boys */ {
        /* Scene */ &scene_toss_boys,
        /* Label */ "‚s‚‚“‚“@‚s‚…‚‚",
        /* Epil. */ TRUE
    },
    /* Toss Boys 2 */ {
        /* Scene */ &scene_toss_boys_2,
        /* Label */ "‚s‚‚“‚“@‚s‚…‚‚@‚Q",
        /* Epil. */ TRUE
    },
    /* Drum Girls LIVE */ {
        /* Scene */ &scene_drum_girls_live_unused,
        /* Label */ "‚c‚’‚•‚@‚f‚‰‚’‚Œ‚“",
        /* Epil. */ TRUE
    },
    /* Power Calligraphy */ {
        /* Scene */ &scene_power_calligraphy,
        /* Label */ "‚o‚‚—‚…‚’@‚b‚‚Œ‚Œ‚‰‚‡‚’‚‚‚ˆ‚™",
        /* Epil. */ TRUE
    },
    /* Rat Race */ {
        /* Scene */ &scene_rat_race,
        /* Label */ "‚q‚‚”@‚q‚‚ƒ‚…",
        /* Epil. */ TRUE
    },
    /* Flash Memory Test */ {
        /* Scene */ &scene_flash_mem_test,
        /* Label */ "‚e‚Œ‚‚“‚ˆ@‚l‚…‚‚‚’‚™@‚s‚…‚“‚”",
        /* Epil. */ FALSE
    },
    /* Fireworks */ {
        /* Scene */ &scene_fireworks,
        /* Label */ "‚e‚‰‚’‚…‚—‚‚’‚‹‚“",
        /* Epil. */ TRUE
    },
    /* Metronome */ {
        /* Scene */ &scene_metronome,
        /* Label */ "‚l‚…‚”‚’‚‚Ž‚‚‚…",
        /* Epil. */ TRUE
    },
    /* Bunny Hop */ {
        /* Scene */ &scene_bunny_hop,
        /* Label */ "‚a‚•‚Ž‚Ž‚™@‚g‚‚",
        /* Epil. */ TRUE
    },
    /* Dance Lesson 1 */ {
        /* Scene */ &scene_remix_1_unused,
        /* Label */ "‚c‚‚Ž‚ƒ‚…@‚k‚…‚“‚“‚‚Ž@‚P",
        /* Epil. */ TRUE
    },
    /* Wizard's Waltz */ {
        /* Scene */ &scene_wizards_waltz,
        /* Label */ "‚v‚‰‚š‚‚’‚„f‚“@‚v‚‚Œ‚”‚š",
        /* Epil. */ TRUE
    },
    /* Marching Orders */ {
        /* Scene */ &scene_marching_orders,
        /* Label */ "‚l‚‚’‚ƒ‚ˆ‚‰‚Ž‚‡@‚n‚’‚„‚…‚’‚“",
        /* Epil. */ TRUE
    },
    /* Marching Orders 2 */ {
        /* Scene */ &scene_marching_orders_2,
        /* Label */ "‚l‚‚’‚ƒ‚ˆ‚‰‚Ž‚‡@‚n‚’‚„‚…‚’‚“@‚Q",
        /* Epil. */ TRUE
    },
    /* Marching Orders (Tempo Up) */ {
        /* Scene */ &scene_marching_orders_extra,
        /* Label */ "‚l‚‚’‚ƒ‚ˆ‚‰‚Ž‚‡@‚n‚’‚„‚…‚’‚“@i‚s‚…‚‚‚@‚t‚j",
        /* Epil. */ TRUE
    },
    /* Mechanical Horse */ {
        /* Scene */ &scene_mechanical_horse,
        /* Label */ "‚g‚‚’‚“‚…@‚l‚‚ƒ‚ˆ‚‰‚Ž‚…",
        /* Epil. */ FALSE
    },
    /* Tap Trial */ {
        /* Scene */ &scene_tap_trial,
        /* Label */ "‚s‚‚@‚s‚’‚‰‚‚Œ",
        /* Epil. */ TRUE
    },
    /* Tap Trial 2 */ {
        /* Scene */ &scene_tap_trial_2,
        /* Label */ "‚s‚‚@‚s‚’‚‰‚‚Œ@‚Q",
        /* Epil. */ TRUE
    },
    /* Samurai Slice */ {
        /* Scene */ &scene_samurai_slice,
        /* Label */ "‚r‚‚‚•‚’‚‚‰@‚r‚Œ‚‰‚ƒ‚…",
        /* Epil. */ TRUE
    },
    /* Spaceball */ {
        /* Scene */ &scene_spaceball,
        /* Label */ "‚r‚‚‚ƒ‚…‚‚‚‚Œ‚Œ",
        /* Epil. */ TRUE
    },
    /* Spaceball 2 */ {
        /* Scene */ &scene_spaceball_2,
        /* Label */ "‚r‚‚‚ƒ‚…‚‚‚‚Œ‚Œ@‚Q",
        /* Epil. */ TRUE
    },
    /* Spaceball (Tempo Up) */ {
        /* Scene */ &scene_spaceball_extra,
        /* Label */ "‚r‚‚‚ƒ‚…‚‚‚‚Œ‚Œ@i‚s‚…‚‚‚@‚t‚j",
        /* Epil. */ TRUE
    },
    /* Sneaky Spirits */ {
        /* Scene */ &scene_sneaky_spirits,
        /* Label */ "‚r‚Ž‚…‚‚‹‚™@‚r‚‚‰‚’‚‰‚”‚“",
        /* Epil. */ TRUE
    },
    /* Sneaky Spirits 2 */ {
        /* Scene */ &scene_sneaky_spirits_2,
        /* Label */ "‚r‚Ž‚…‚‚‹‚™@‚r‚‚‰‚’‚‰‚”‚“@‚Q",
        /* Epil. */ TRUE
    },
    /* Ninja Bodyguard */ {
        /* Scene */ &scene_ninja_bodyguard,
        /* Label */ "‚m‚‰‚Ž‚Š‚@‚a‚‚„‚™‚‡‚•‚‚’‚„",
        /* Epil. */ TRUE
    },
    /* Ninja Bodyguard 2 */ {
        /* Scene */ &scene_ninja_reincarnate,
        /* Label */ "‚m‚‰‚Ž‚Š‚@‚c‚…‚“‚ƒ‚…‚Ž‚„‚‚Ž‚”",
        /* Epil. */ TRUE
    },
    /* Bouncy Road */ {
        /* Scene */ &scene_bouncy_road,
        /* Label */ "‚a‚‚•‚Ž‚ƒ‚™@‚q‚‚‚„",
        /* Epil. */ TRUE
    },
    /* Bouncy Road 2 */ {
        /* Scene */ &scene_bouncy_road_2,
        /* Label */ "‚a‚‚•‚Ž‚ƒ‚™@‚q‚‚‚„@‚Q",
        /* Epil. */ TRUE
    },
    /* Sick Beats */ {
        /* Scene */ &scene_sick_beats,
        /* Label */ "‚r‚‰‚ƒ‚‹@‚a‚…‚‚”‚“",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers */ {
        /* Scene */ &scene_rhythm_tweezers,
        /* Label */ "‚q‚ˆ‚™‚”‚ˆ‚@‚s‚—‚…‚…‚š‚…‚’‚“",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers 2 */ {
        /* Scene */ &scene_rhythm_tweezers_2,
        /* Label */ "‚q‚ˆ‚™‚”‚ˆ‚@‚s‚—‚…‚…‚š‚…‚’‚“@‚Q",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers (Tempo Up) */ {
        /* Scene */ &scene_rhythm_tweezers_extra,
        /* Label */ "‚q‚ˆ‚™‚”‚ˆ‚@‚s‚—‚…‚…‚š‚…‚’‚“@i‚s‚…‚‚‚@‚t‚j",
        /* Epil. */ TRUE
    },
    /* Night Walk */ {
        /* Scene */ &scene_night_walk,
        /* Label */ "‚m‚‰‚‡‚ˆ‚”@‚v‚‚Œ‚‹",
        /* Epil. */ TRUE
    },
    /* Night Walk 2 */ {
        /* Scene */ &scene_night_walk_2,
        /* Label */ "‚m‚‰‚‡‚ˆ‚”@‚v‚‚Œ‚‹@‚Q",
        /* Epil. */ TRUE
    },
    /* Polyrhythm */ {
        /* Scene */ &scene_polyrhythm,
        /* Label */ "‚o‚‚Œ‚™‚’‚ˆ‚™‚”‚ˆ‚",
        /* Epil. */ TRUE
    },
    /* Polyrhythm 2 */ {
        /* Scene */ &scene_polyrhythm_2,
        /* Label */ "‚o‚‚Œ‚™‚’‚ˆ‚™‚”‚ˆ‚@‚Q",
        /* Epil. */ TRUE
    },
    /* The Clappy Trio */ {
        /* Scene */ &scene_clappy_trio,
        /* Label */ "‚s‚ˆ‚…@‚b‚Œ‚‚‚‚™@‚s‚’‚‰‚",
        /* Epil. */ TRUE
    },
    /* The Snappy Trio */ {
        /* Scene */ &scene_snappy_trio,
        /* Label */ "‚s‚ˆ‚…@‚r‚Ž‚‚‚‚™@‚s‚’‚‰‚",
        /* Epil. */ TRUE
    },
    /* The Clappy Trio (Tempo Up) */ {
        /* Scene */ &scene_clappy_trio_extra,
        /* Label */ "‚s‚ˆ‚…@‚b‚Œ‚‚‚‚™@‚s‚’‚‰‚@i‚s‚…‚‚‚@‚t‚j",
        /* Epil. */ TRUE
    }, 
    /* Karate Man */ {
        /* Scene */ &scene_karate_man,
        /* Label */ "‚j‚‚’‚‚”‚…@‚l‚‚Ž",
        /* Epil. */ TRUE
    },
    /* Karate Man 2 */ {
        /* Scene */ &scene_karate_man_2,
        /* Label */ "‚j‚‚’‚‚”‚…@‚l‚‚Ž@‚Q",
        /* Epil. */ TRUE
    },
    /* Karate Man (Tempo Up) */ {
        /* Scene */ &scene_karate_man_extra,
        /* Label */ "‚j‚‚’‚‚”‚…@‚l‚‚Ž@i‚s‚…‚‚‚@‚t‚j",
        /* Epil. */ TRUE
    },
    /* Tanuki and Monkey */ {
        /* Scene */ &scene_tanuki_and_monkey,
        /* Label */ "‚s‚‚Ž‚•‚‹‚‰@•@‚l‚‚Ž‚‹‚…‚™",
        /* Epil. */ TRUE
    },
    /* R-IQ (Title Screen) */ {
        /* Scene */ &scene_title,
        /* Label */ "‚q|‚h‚p@i‚s‚‰‚”‚Œ‚…j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Main Menu) */ {
        /* Scene */ &scene_main_menu,
        /* Label */ "‚q|‚h‚p@i‚l‚…‚Ž‚•j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Game Select) */ {
        /* Scene */ &scene_game_select,
        /* Label */ "‚q|‚h‚p@i‚f‚‚‚…j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Rhythm Data Room) */ {
        /* Scene */ &scene_data_room,
        /* Label */ "‚q|‚h‚p@i‚k‚…‚”‚”‚…‚’j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Studio) */ {
        /* Scene */ &scene_studio,
        /* Label */ "‚q|‚h‚p@i‚r‚”‚•‚„‚‰‚j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Options) */ {
        /* Scene */ &scene_options_menu,
        /* Label */ "‚q|‚h‚p@i‚n‚‚”‚‰‚‚Žj",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 1) */ {
        /* Scene */ &scene_results_ver_debug,
        /* Label */ "‚q|‚h‚p@i‚q‚…‚“‚•‚Œ‚”j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 2) */ {
        /* Scene */ &scene_results_ver_rank,
        /* Label */ "‚q|‚h‚p@i‚q‚…‚“‚•‚Œ‚”@‚Qj",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 3) */ {
        /* Scene */ &scene_results_ver_score,
        /* Label */ "‚q|‚h‚p@i‚q‚…‚“‚•‚Œ‚”@‚Rj",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 4) */ {
        /* Scene */ &scene_epilogue,
        /* Label */ "‚q|‚h‚p@i‚q‚…‚“‚•‚Œ‚”@‚Sj",
        /* Epil. */ TRUE
    },
    /* R-IQ (Debug Menu) */ {
        /* Scene */ &scene_debug_menu,
        /* Label */ "‚q|‚h‚p@i‚c‚…‚‚‚•‚‡j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Rhythm Library) */ {
        /* Scene */ &scene_arrival,
        /* Label */ "‚q|‚h‚p@i‚d‚‚‚‰‚Œj",
        /* Epil. */ FALSE
    },
    /* R-IQ (Perfect) */ {
        /* Scene */ &scene_perfect,
        /* Label */ "‚q|‚h‚p@i‚o‚…‚’‚†‚…‚ƒ‚”j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Cafe) */ {
        /* Scene */ &scene_cafe,
        /* Label */ "‚q|‚h‚p@i‚b‚‚†‚…j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Endless Games) */ {
        /* Scene */ &scene_endless_menu,
        /* Label */ "‚q|‚h‚p@i‚l‚‰‚Ž‚‰‚‡‚‚‚…j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Drum Lessons) */ {
        /* Scene */ &scene_lessons_menu,
        /* Label */ "‚q|‚h‚p@i‚c‚’‚•‚@‚k‚…‚“‚“‚‚Ž‚“j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Rhythm Toys) */ {
        /* Scene */ &scene_toys_menu,
        /* Label */ "‚q|‚h‚p@i‚s‚‚™‚“j",
        /* Epil. */ FALSE
    },
    /* R-IQ (Cafe) */ {
        /* Scene */ &scene_cafe,
        /* Label */ "‚q|‚h‚p@i‚b‚‚†‚…j",
        /* Epil. */ FALSE
    },
    /* Ending (from clearing Remix 6) */ {
        /* Scene */ &scene_staff_credit_remix_6,
        /* Label */ "‚d‚Ž‚„‚‰‚Ž‚‡@i‚f‚‚‚…@‚b‚Œ‚…‚‚’‚…‚„j",
        /* Epil. */ FALSE
    },
    /* Ending (from Game Select) */ {
        /* Scene */ &scene_staff_credit,
        /* Label */ "‚d‚Ž‚„‚‰‚Ž‚‡@i‚d‚˜‚”‚’‚@‚u‚‰‚…‚—‚‰‚Ž‚‡‚“j",
        /* Epil. */ FALSE
    },
    /* Data Clear */ {
        /* Scene */ &scene_data_clear,
        /* Label */ "‚r‚‚–‚…@‚c‚‚”‚@‚b‚Œ‚…‚‚’",
        /* Epil. */ FALSE
    },
    /* Warning */ {
        /* Scene */ &scene_warning,
        /* Label */ "‚v‚‚’‚Ž‚‰‚Ž‚‡",
        /* Epil. */ FALSE
    },
    /* Disclaimer */ {
        /* Scene */ &scene_disclaimer,
        /* Label */ "‚c‚‰‚“‚ƒ‚Œ‚‚‰‚‚…‚’",
        /* Epil. */ FALSE
    },
    /* Snappy Trio (Unused) */ {
        /* Scene */ &scene_snappy_trio_unused,
        /* Label */ "‚s‚ˆ‚…@‚r‚Ž‚‚‚‚™@‚s‚’‚‰‚@i‚t‚Ž‚•‚“‚…‚„j",
        /* Epil. */ TRUE
    },
    /* Bouncy Road (Unused) */ {
        /* Scene */ &scene_bouncy_road_unused,
        /* Label */ "‚a‚‚•‚Ž‚ƒ‚™@‚q‚‚‚„@i‚t‚Ž‚•‚“‚…‚„j",
        /* Epil. */ TRUE
    },
    /* Bouncy Road (Unused 2) */ {
        /* Scene */ &scene_bouncy_road_unused_2,
        /* Label */ "‚a‚‚•‚Ž‚ƒ‚™@‚q‚‚‚„@i‚t‚Ž‚•‚“‚…‚„@‚Qj",
        /* Epil. */ TRUE
    },
    /* Spaceball (Unused) */ {
        /* Scene */ &scene_spaceball_unused,
        /* Label */ "‚r‚‚‚ƒ‚…‚‚‚‚Œ‚Œ@i‚t‚Ž‚•‚“‚…‚„j",
        /* Epil. */ TRUE
    },
    /* Spaceball (Unused 2) */ {
        /* Scene */ &scene_spaceball_unused_2,
        /* Label */ "‚r‚‚‚ƒ‚…‚‚‚‚Œ‚Œ@i‚t‚Ž‚•‚“‚…‚„@‚Qj",
        /* Epil. */ TRUE
    },
    /* Tap Trial (Unused) */ {
        /* Scene */ &scene_tap_trial_unused,
        /* Label */ "‚s‚‚@‚s‚’‚‰‚‚Œ@i‚t‚Ž‚•‚“‚…‚„j",
        /* Epil. */ TRUE
    },
    /* Marching Orders (Unused) */ {
        /* Scene */ &scene_marching_orders_unused,
        /* Label */ "‚l‚‚’‚ƒ‚ˆ‚‰‚Ž‚‡@‚n‚’‚„‚…‚’‚“@i‚t‚Ž‚•‚“‚…‚„j",
        /* Epil. */ TRUE
    },
    /* Horse Machine (Unused) */ {
        /* Scene */ &scene_mechanical_horse_unused,
        /* Label */ "‚g‚‚’‚“‚…@‚l‚‚ƒ‚ˆ‚‰‚Ž‚…@i‚t‚Ž‚•‚“‚…‚„j",
        /* Epil. */ TRUE
    },
    END_OF_DEBUG_ENTRIES
};


// [D_089ddf60] Page Number Digits
char debug_menu_counter_digits[] = "‚O‚P‚Q‚R‚S‚T‚U‚V‚W‚X‚`‚a‚b‚c‚d‚e‚f‚g‚h‚i‚j‚k‚l‚m‚n‚o‚p‚q‚r‚s‚t‚u‚v‚w‚x‚y";


// Render Text
void debug_menu_render_table(s32 targetPage, s32 targetRow) {
    char string[100];
    s32 totalPages;
    u32 i, j;

    totalPages = (gDebugMenu->totalEntries - 1) / DEBUG_MENU_ENTRY_PER_PAGE;

    if (targetPage < 0) {
        targetPage = totalPages;
    }

    if (targetPage > totalPages) {
        targetPage = 0;
    }

    if ((targetPage * DEBUG_MENU_ENTRY_PER_PAGE) + targetRow >= gDebugMenu->totalEntries) {
        targetRow = (gDebugMenu->totalEntries - 1) - (totalPages * DEBUG_MENU_ENTRY_PER_PAGE);
    }

    if (targetPage != gDebugMenu->page) {
        struct PrintedTextAnim *textAnim;

        for (i = 0; i < DEBUG_MENU_ENTRY_PER_PAGE; i++) {
            if (gDebugMenu->textLines[i] > -1) {
                delete_bmp_font_obj_text_anim(gDebugMenu->objFont, gDebugMenu->textLines[i]);
                sprite_delete(gSpriteHandler, gDebugMenu->textLines[i]);
                gDebugMenu->textLines[i] = -1;
            }
        }

        for (j = 0, i = (targetPage * DEBUG_MENU_ENTRY_PER_PAGE); (i < (targetPage * DEBUG_MENU_ENTRY_PER_PAGE) + DEBUG_MENU_ENTRY_PER_PAGE) && (i < gDebugMenu->totalEntries); j++, i++) {
            textAnim = bmp_font_obj_print_l(gDebugMenu->objFont, debug_menu_entry_table[i].label, 1, 0);
            gDebugMenu->textLines[j] = sprite_create(gSpriteHandler, textAnim->frames, 0, 32, (j * 18) + 32, 0x800, 0, 0, 0);
        }

        delete_bmp_font_obj_text_anim(gDebugMenu->objFont, gDebugMenu->counter);
        strncpy(string, &debug_menu_counter_digits[(targetPage + 1) * 2], 2);
        string[2] = '\0';
        strcat(string, "^");
        strncat(string, &debug_menu_counter_digits[(totalPages + 1) * 2], 2);
        textAnim = bmp_font_obj_print_r(gDebugMenu->objFont, string, 1, 4);
        sprite_set_anim(gSpriteHandler, gDebugMenu->counter, textAnim->frames, 0, 0, 0, 0);
    }

    gDebugMenu->page = targetPage;
    gDebugMenu->row = targetRow;

    for (i = 0; i < DEBUG_MENU_ENTRY_PER_PAGE; i++) {
        if (gDebugMenu->textLines[i] > -1) {
            sprite_set_base_palette(gSpriteHandler, gDebugMenu->textLines[i], 0);
        }
    }

    sprite_set_base_palette(gSpriteHandler, gDebugMenu->textLines[gDebugMenu->row], 7);
    sprite_set_x_y(gSpriteHandler, gDebugMenu->cursor, 16, (gDebugMenu->row * 18) + 32);
}
