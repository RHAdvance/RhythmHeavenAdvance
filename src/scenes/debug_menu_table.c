#include "global.h"
#include "debug_menu.h"


/* DEBUG MENU TABLE */


// [D_089ddbe8] Debug Menu Table
struct DebugMenuEntry debug_menu_entry_table[] = {
    /* R-IQ (Title Screen) */ {
        /* Scene */ &scene_title,
        /* Label */ "R-IQ (Title)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Main Menu) */ {
        /* Scene */ &scene_main_menu,
        /* Label */ "R-IQ (Menu)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Game Select) */ {
        /* Scene */ &scene_game_select,
        /* Label */ "R-IQ (Game)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Rhythm Data Room) */ {
        /* Scene */ &scene_data_room,
        /* Label */ "R-IQ (Letter)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Studio) */ {
        /* Scene */ &scene_studio,
        /* Label */ "R-IQ (Studio)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Options) */ {
        /* Scene */ &scene_options_menu,
        /* Label */ "R-IQ (Options)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 1) */ {
        /* Scene */ &scene_results_ver_debug,
        /* Label */ "R-IQ (Result)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 2) */ {
        /* Scene */ &scene_results_ver_rank,
        /* Label */ "R-IQ (Result 2)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 3) */ {
        /* Scene */ &scene_results_ver_score,
        /* Label */ "R-IQ (Result 3)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 4) */ {
        /* Scene */ &scene_epilogue,
        /* Label */ "R-IQ (Result 4)",
        /* Epil. */ TRUE
    },
    /* R-IQ (Rhythm Library) */ {
        /* Scene */ &scene_arrival,
        /* Label */ "R-IQ (Email)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Perfect) */ {
        /* Scene */ &scene_perfect,
        /* Label */ "R-IQ (Perfect)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Endless Games) */ {
        /* Scene */ &scene_endless_menu,
        /* Label */ "R-IQ (Endless Games)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Drum Lessons) */ {
        /* Scene */ &scene_lessons_menu,
        /* Label */ "R-IQ (Drum Lessons)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Rhythm Toys) */ {
        /* Scene */ &scene_toys_menu,
        /* Label */ "R-IQ (Rhythm Toys)",
        /* Epil. */ FALSE
    },
    /* R-IQ (Cafe) */ {
        /* Scene */ &scene_cafe,
        /* Label */ "R-IQ (Cafe Counseling)", // shoutout to british people
        /* Epil. */ FALSE
    },
    /* Warning */ {
        /* Scene */ &scene_warning,
        /* Label */ "Warning",
        /* Epil. */ FALSE
    },
    /* GBP Handshake */ {
        /* Scene */ &scene_gbp_handshake,
        /* Label */ "GBP Handshake",
        /* Epil. */ FALSE
    },
    /* Disclaimer */ {
        /* Scene */ &scene_disclaimer,
        /* Label */ "Disclaimer",
        /* Epil. */ FALSE
    },
    /* Opening (A Type) */ {
        /* Scene */ &scene_drum_samurai_demo_cutscene,
        /* Label */ "Opening (Type A)",
        /* Epil. */ FALSE
    },
    /* Opening (B Type) */ {
        /* Scene */ &scene_drum_samurai_opening_cutscene,
        /* Label */ "Opening (Type B)",
        /* Epil. */ FALSE
    },
    /* Rhythm Test (Total) */ {
        /* Scene */ &scene_rhythm_test_opening,
        /* Label */ "Rhythm Test (Opening)"
    },
    /* Rhythm Test (Click) */ {
        /* Scene */ &scene_rhythm_test_click,
        /* Label */ "Rhythm Test (Click)",
    },
    /* Rhythm Test (Cue) */ {
        /* Scene */ &scene_rhythm_test_cue,
        /* Label */ "Rhythm Test (Cue)",
    },
    /* Rhythm Test (Trick) */ {
        /* Scene */ &scene_rhythm_test_trick,
        /* Label */ "Rhythm Test (Trick)"
    },
    /* Reading Material */ {
        /* Scene */ &scene_reading,
        /* Label */ "Email",
        /* Epil. */ FALSE
    },
    /* Studio Drummer */ {
        /* Scene */ &scene_drum_studio_ver0,
        /* Label */ "Studio Drums (Ver. 0)",
        /* Epil. */ FALSE
    },
    /* Studio Drummer */ {
        /* Scene */ &scene_drum_studio_ver2,
        /* Label */ "Studio Drums (Ver. 2)",
        /* Epil. */ FALSE
    },
 /* Drum LIVE */ {
        /* Scene */ &scene_drum_live,
        /* Label */ "Concert",
        /* Epil. */ TRUE
    },
    /* Ending (from clearing Remix 6) */ {
        /* Scene */ &scene_staff_credit_remix_6,
        /* Label */ "Ending (Game Cleared)",
        /* Epil. */ FALSE
    },
    /* Ending (from Game Select) */ {
        /* Scene */ &scene_staff_credit,
        /* Label */ "Ending (Extra Viewings)",
        /* Epil. */ FALSE
    },
    /* Lesson (Basic 1) */ {
        /* Scene */ &scene_drum_lesson_basic_1,
        /* Label */ "Lesson (Intro 1)",
        /* Epil. */ FALSE
    },
    /* Lesson (Basic 2) */ {
        /* Scene */ &scene_drum_lesson_basic_2,
        /* Label */ "Lesson (Intro 2)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 1) */ {
        /* Scene */ &scene_drum_lesson_short_1,
        /* Label */ "Lesson (Basic 1)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 2) */ {
        /* Scene */ &scene_drum_lesson_short_2,
        /* Label */ "Lesson (Basic 2)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 3) */ {
        /* Scene */ &scene_drum_lesson_short_3,
        /* Label */ "Lesson (Basic 3)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 4) */ {
        /* Scene */ &scene_drum_lesson_short_4,
        /* Label */ "Lesson (Basic 4)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 5) */ {
        /* Scene */ &scene_drum_lesson_short_5,
        /* Label */ "Lesson (Basic 5)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 6) */ {
        /* Scene */ &scene_drum_lesson_short_6,
        /* Label */ "Lesson (Basic 6)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 7) */ {
        /* Scene */ &scene_drum_lesson_short_7,
        /* Label */ "Lesson (Basic 7)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 8) */ {
        /* Scene */ &scene_drum_lesson_short_8,
        /* Label */ "Lesson (Basic 8)",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 9) */ {
        /* Scene */ &scene_drum_lesson_short_9,
        /* Label */ "Lesson (Basic 9)",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 1) */ {
        /* Scene */ &scene_drum_lesson_long_1,
        /* Label */ "Lesson (Advanced 1)",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 2) */ {
        /* Scene */ &scene_drum_lesson_long_2,
        /* Label */ "Lesson (Advanced 2)",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 3) */ {
        /* Scene */ &scene_drum_lesson_long_3,
        /* Label */ "Lesson (Advanced 3)",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 4) */ {
        /* Scene */ &scene_drum_lesson_long_4,
        /* Label */ "Lesson (Advanced 4)",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 5) */ {
        /* Scene */ &scene_drum_lesson_long_5,
        /* Label */ "Lesson (Advanced 5)",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 6) */ {
        /* Scene */ &scene_drum_lesson_long_6,
        /* Label */ "Lesson (Advanced 6)",
        /* Epil. */ FALSE
    },
    /* Lesson (High-Tech 1) */ {
        /* Scene */ &scene_drum_lesson_hi_tech_1,
        /* Label */ "Lesson (Technical 1)",
        /* Epil. */ FALSE
    },
    /* Lesson (High-Tech 2) */ {
        /* Scene */ &scene_drum_lesson_hi_tech_2,
        /* Label */ "Lesson (Technical 2)",
        /* Epil. */ FALSE
    },
    /* Mr. Upbeat */ {
        /* Scene */ &scene_mr_upbeat,
        /* Label */ "Mr. Upbeat",
        /* Epil. */ FALSE
    },
    /* Sick Beats Endless */ {
        /* Scene */ &scene_sick_beats_endless,
        /* Label */ "Sick Beats Special",
        /* Epil. */ FALSE
    },
    /* Quiz Show Endless */ {
        /* Scene */ &scene_quiz_show_endless,
        /* Label */ "Quiz Show Special",
        /* Epil. */ FALSE
    },
    /* Mannequin Factory */ {
        /* Scene */ &scene_mannequin_factory,
        /* Label */ "Mannequin Factory",
        /* Epil. */ FALSE
    },
    /* Rhythm Toys (Cat Machine) */ {
        /* Scene */ &scene_cat_machine,
        /* Label */ "Cat Machine",
        /* Epil. */ FALSE
    },
    /* Mechanical Horse */ {
        /* Scene */ &scene_mechanical_horse,
        /* Label */ "Horse Machine",
        /* Epil. */ FALSE

    },
    /* Rhythm Toys (Confession Machine) */ {
        /* Scene */ &scene_love_machine,
        /* Label */ "Love Machine",
        /* Epil. */ FALSE
    },
    /* Rhythm Toys (Rap Machine) */ {
        /* Scene */ &scene_rap_machine,
        /* Label */ "Rap Machine",
        /* Epil. */ FALSE
    },
    /* Karate Man */ {
        /* Scene */ &scene_karate_man,
        /* Label */ "Karate Man",
        /* Epil. */ TRUE
    },
    /* Karate Man 2 */ {
        /* Scene */ &scene_karate_man_2,
        /* Label */ "Karate Man 2",
        /* Epil. */ TRUE
    },
    /* Karate Man (Extra) */ {
        /* Scene */ &scene_karate_man_extra,
        /* Label */ "Karate Man (Extra)",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers */ {
        /* Scene */ &scene_rhythm_tweezers,
        /* Label */ "Rhythm Tweezers",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers 2 */ {
        /* Scene */ &scene_rhythm_tweezers_2,
        /* Label */ "Rhythm Tweezers 2",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers (Extra) */ {
        /* Scene */ &scene_rhythm_tweezers_extra,
        /* Label */ "Rhythm Tweezers (Extra)",
        /* Epil. */ TRUE
    },
    /* Marching Orders */ {
        /* Scene */ &scene_marching_orders,
        /* Label */ "Marching Orders",
        /* Epil. */ TRUE
    },
    /* Marching Orders 2 */ {
        /* Scene */ &scene_marching_orders_2,
        /* Label */ "Marching Orders 2",
        /* Epil. */ TRUE
    },
    /* Marching Orders (Extra) */ {
        /* Scene */ &scene_marching_orders_extra,
        /* Label */ "Marching Orders (Extra)",
        /* Epil. */ TRUE
    },
    /* Spaceball */ {
        /* Scene */ &scene_spaceball,
        /* Label */ "Spaceball",
        /* Epil. */ TRUE
    },
    /* Spaceball 2 */ {
        /* Scene */ &scene_spaceball_2,
        /* Label */ "Spaceball 2",
        /* Epil. */ TRUE

    },
    /* Spaceball (Extra) */ {
        /* Scene */ &scene_spaceball_extra,
        /* Label */ "Spaceball (Extra)",
        /* Epil. */ TRUE
    },
    /* The Clappy Trio */ {
        /* Scene */ &scene_clappy_trio,
        /* Label */ "The Clappy Trio",
        /* Epil. */ TRUE
    },
    /* The Snappy Trio */ {
        /* Scene */ &scene_snappy_trio,
        /* Label */ "The Snappy Trio",
        /* Epil. */ TRUE
    },
    /* The Clappy Trio (Extra) */ {
        /* Scene */ &scene_clappy_trio_extra,
        /* Label */ "The Clappy Trio (Extra)",
        /* Epil. */ TRUE
    },
    /* Sneaky Spirits */ {
        /* Scene */ &scene_sneaky_spirits,
        /* Label */ "Sneaky Spirits",
        /* Epil. */ TRUE
    },
    /* Sneaky Spirits 2 */ {
        /* Scene */ &scene_sneaky_spirits_2,
        /* Label */ "Sneaky Spirits 2",
        /* Epil. */ TRUE
    },
    /* Samurai Slice */ {
        /* Scene */ &scene_samurai_slice,
        /* Label */ "Samurai Slice",
        /* Epil. */ TRUE
    },
    /* Rat Race */ {
        /* Scene */ &scene_rat_race,
        /* Label */ "Rat Race",
        /* Epil. */ TRUE
    },
    /* Sick Beats */ {
        /* Scene */ &scene_sick_beats,
        /* Label */ "Sick Beats",
        /* Epil. */ TRUE
    },
    /* The Bon Odori */ {
        /* Scene */ &scene_bon_odori,
        /* Label */ "The Bon Odori",
        /* Epil. */ TRUE
    },
    /* Bon Dance */ {
        /* Scene */ &scene_bon_dance,
        /* Label */ "The Bon Dance",
        /* Epil. */ TRUE
    },
    /* Wizard's Waltz */ {
        /* Scene */ &scene_wizards_waltz,
        /* Label */ "Wizard's Waltz",
        /* Epil. */ TRUE
    },
    /* Showtime */ {
        /* Scene */ &scene_showtime,
        /* Label */ "Showtime",
        /* Epil. */ TRUE
    },
    /* Bunny Hop */ {
        /* Scene */ &scene_bunny_hop,
        /* Label */ "Bunny Hop",
        /* Epil. */ TRUE
    },
    /* Tram & Pauline */ {
        /* Scene */ &scene_tram_pauline,
        /* Label */ "Tram & Pauline",
        /* Epil. */ TRUE
    },
    /* Space Dance */ {
        /* Scene */ &scene_space_dance,
        /* Label */ "Space Dance",
        /* Epil. */ TRUE
    },
    /* Cosmic Dance */ {
        /* Scene */ &scene_cosmic_dance,
        /* Label */ "Cosmic Dance",
        /* Epil. */ TRUE
   },
    /* Quiz Show */ {
        /* Scene */ &scene_quiz_show,
        /* Label */ "Quiz Show",
        /* Epil. */ TRUE
    },
    /* Night Walk */ {
        /* Scene */ &scene_night_walk,
        /* Label */ "Night Walk",
        /* Epil. */ TRUE
    },
    /* Night Walk 2 */ {
        /* Scene */ &scene_night_walk_2,
        /* Label */ "Night Walk 2",
        /* Epil. */ TRUE
    },
    /* Power Calligraphy */ {
        /* Scene */ &scene_power_calligraphy,
        /* Label */ "Power Calligraphy",
        /* Epil. */ TRUE
    },
    /* Polyrhythm */ {
        /* Scene */ &scene_polyrhythm,
        /* Label */ "Polyrhythm",
        /* Epil. */ TRUE
    },
    /* Polyrhythm 2 */ {
        /* Scene */ &scene_polyrhythm_2,
        /* Label */ "Polyrhythm 2",
        /* Epil. */ TRUE
    },
    /* Rap Men */ {
        /* Scene */ &scene_rap_men,
        /* Label */ "RAPMEN",
        /* Epil. */ TRUE
    },
    /* Rap Women (by YONE) */ {
        /* Scene */ &scene_rap_women,
        /* Label */ "RAPWOMEN (by YONE)",
        /* Epil. */ TRUE
    },
    /* Bouncy Road */ {
        /* Scene */ &scene_bouncy_road,
        /* Label */ "Bouncy Road",
        /* Epil. */ TRUE
    },
    /* Bouncy Road 2 */ {
        /* Scene */ &scene_bouncy_road_2,
        /* Label */ "Bouncy Road 2",
        /* Epil. */ TRUE
    },
    /* Ninja Bodyguard */ {
        /* Scene */ &scene_ninja_bodyguard,
        /* Label */ "Ninja Bodyguard",
        /* Epil. */ TRUE
    },
    /* Ninja Bodyguard 2 */ {
        /* Scene */ &scene_ninja_reincarnate,
        /* Label */ "Ninja Descendant",
        /* Epil. */ TRUE
    },
    /* Toss Boys */ {
        /* Scene */ &scene_toss_boys,
        /* Label */ "Toss Team",
        /* Epil. */ TRUE
    },
    /* Toss Boys 2 */ {
        /* Scene */ &scene_toss_boys_2,
        /* Label */ "Toss Team 2",
        /* Epil. */ TRUE
    },
    /* Fireworks */ {
        /* Scene */ &scene_fireworks,
        /* Label */ "Fireworks",
        /* Epil. */ TRUE
    },
    /* Tap Trial */ {
        /* Scene */ &scene_tap_trial,
        /* Label */ "Tap Trial",
        /* Epil. */ TRUE
    },
    /* Tap Trial 2 */ {
        /* Scene */ &scene_tap_trial_2,
        /* Label */ "Tap Trial 2",
        /* Epil. */ TRUE
    },
    /* Remix 1 */ {
        /* Scene */ &scene_remix_1,
        /* Label */ "Remix 1",
        /* Epil. */ TRUE
    },
    /* Remix 2 */ {
        /* Scene */ &scene_remix_2,
        /* Label */ "Remix 2",
        /* Epil. */ TRUE
    },
    /* Remix 3 */ {
        /* Scene */ &scene_remix_3,
        /* Label */ "Remix 3",
        /* Epil. */ TRUE
    },
    /* Remix 4 */ {
        /* Scene */ &scene_remix_4,
        /* Label */ "Remix 4",
        /* Epil. */ TRUE
    },
    /* Remix 5 */ {
        /* Scene */ &scene_remix_5,
        /* Label */ "Remix 5",
        /* Epil. */ TRUE
    },
    /* Remix 6 */ {
        /* Scene */ &scene_remix_6,
        /* Label */ "Remix 6",
        /* Epil. */ TRUE
    },
    /* Remix 7 */ {
        /* Scene */ &scene_remix_7,
        /* Label */ "Remix 7",
        /* Epil. */ TRUE
    },
    /* Remix 8 */ {
        /* Scene */ &scene_remix_8,
        /* Label */ "Remix 8",
        /* Epil. */ TRUE
    },
    /* Remix 1 (Extra) */ {
        /* Scene */ &scene_remix_1_extra,
        /* Label */ "Remix 1 (Extra)",
        /* Epil. */ TRUE
    },
    /* Drum Intro (Unused 1) */ {
        /* Scene */ &scene_drum_intro_unused,
        /* Label */ "Drum Intro (Unused)",
        /* Epil. */ TRUE
    },
    /* Drum Intro (Unused 2) */ {
        /* Scene */ &scene_drum_intro_unused_2,
        /* Label */ "Drum Intro (Unused 2)",
        /* Epil. */ TRUE
    },
    /* Drum Intro (Unused 3) */ {
        /* Scene */ &scene_drum_intro_unused_3,
        /* Label */ "Drum Intro (Unused 3)",
        /* Epil. */ TRUE
    },
    /* Tanuki and Monkey */ {
        /* Scene */ &scene_tanuki_and_monkey,
        /* Label */ "Tanuki and Monkey (Unused)",
        /* Epil. */ TRUE
    },
    /* Metronome */ {
        /* Scene */ &scene_metronome,
        /* Label */ "Metronome (Unused)",
        /* Epil. */ TRUE
    },
    /* Drum Girls LIVE */ {
        /* Scene */ &scene_drum_girls_live_unused,
        /* Label */ "Drum Girls (Unused)",
        /* Epil. */ TRUE
    },
    /* Horse Machine (Unused) */ {
        /* Scene */ &scene_mechanical_horse_unused,
        /* Label */ "Horse Machine (Unused)",
        /* Epil. */ TRUE
    },
    /* Marching Orders (Unused) */ {
        /* Scene */ &scene_marching_orders_unused,
        /* Label */ "Marching Orders (Unused)",
        /* Epil. */ TRUE
    },
    /* Spaceball (Unused) */ {
        /* Scene */ &scene_spaceball_unused,
        /* Label */ "Spaceball (Unused)",
        /* Epil. */ TRUE
    },
    /* Spaceball (Unused 2) */ {
        /* Scene */ &scene_spaceball_unused_2,
        /* Label */ "Spaceball (Unused 2)",
        /* Epil. */ TRUE
    },
    /* Snappy Trio (Unused) */ {
        /* Scene */ &scene_snappy_trio_unused,
        /* Label */ "The Snappy Trio (Unused)",
        /* Epil. */ TRUE
    },
    /* Rap Women (by KAZU) */ {
        /* Scene */ &scene_rap_women_unused,
        /* Label */ "RAPWOMEN (by KAZU)",
        /* Epil. */ TRUE
    },
    /* Bouncy Road (Unused) */ {
        /* Scene */ &scene_bouncy_road_unused,
        /* Label */ "Bouncy Road (Unused)",
        /* Epil. */ TRUE
    },
    /* Bouncy Road (Unused 2) */ {
        /* Scene */ &scene_bouncy_road_unused_2,
        /* Label */ "Bouncy Road (Unused 2)",
        /* Epil. */ TRUE
    },
    /* Tap Trial (Unused) */ {
        /* Scene */ &scene_tap_trial_unused,
        /* Label */ "Tap Trial (Unused)",
        /* Epil. */ TRUE
    },
    /* Dance Lesson 1 */ {
        /* Scene */ &scene_remix_1_unused,
        /* Label */ "Dance Lesson 1 (Unused)",
        /* Epil. */ TRUE
    },
    /* RIQ Data Check */ {
        /* Scene */ &scene_data_check,
        /* Label */ "R-IQ Data Check",
        /* Epil. */ FALSE
    },
    /* Asset Test */ {
        /* Scene */ &scene_asset_test,
        /* Label */ "Asset Test",
        /* Epil. */ FALSE  
    },
    /* Flash Memory Test */ {
        /* Scene */ &scene_flash_mem_test,
        /* Label */ "Flash Memory Test",
        /* Epil. */ FALSE
    },
    /* Read Error */ {
        /* Scene */ &scene_read_error,
        /* Label */ "Read Error",
        /* Epil. */ FALSE  
    },
    /* Template Scene */ {
        /* Scene */ &scene_template,
        /* Label */ "Template Scene",
        /* Epil. */ FALSE  
    },
    /* Data Clear */ {
        /* Scene */ &scene_data_clear,
        /* Label */ "Save Data Clear",
        /* Epil. */ FALSE
    },
    /* R-IQ Save Editor */ {
        /* Scene */ &scene_save_editor,
        /* Label */ "R-IQ Save Editor",
        /* Epil. */ FALSE
    },
    /* Sequence Player */ {
        /* Scene */ &scene_sequence_player,
        /* Label */ "Sequence Player",
        /* Epil. */ FALSE
    },
    /* Debug Menu */ {
        /* Scene */ &scene_debug_menu,
        /* Label */ "Debug Menu",
        /* Epil. */ FALSE
    },
    END_OF_DEBUG_ENTRIES
};


// [D_089ddf60] Page Number Digits
char debug_menu_counter_digits[] = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


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
            gDebugMenu->textLines[j] = sprite_create(gSpriteHandler, textAnim->frames, 0, 32, (j * 21) + 32, 0x800, 0, 0, 0);
        }

        delete_bmp_font_obj_text_anim(gDebugMenu->objFont, gDebugMenu->counter);
        snprintf(string, 100, "%c/%c", debug_menu_counter_digits[targetPage], debug_menu_counter_digits[totalPages]);
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
    sprite_set_x_y(gSpriteHandler, gDebugMenu->cursor, 16, (gDebugMenu->row * 21) + 32);
}
