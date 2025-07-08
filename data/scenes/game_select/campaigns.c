#include "global.h"
#include "graphics.h"
#include "levels.h"
#include "src/scenes/game_select.h"
#include "src/scenes/studio.h"
#include "src/scenes/reading.h"
#include "graphics/game_select/game_select_graphics.h"


  /* GAME SELECT - PERFECT CAMPAIGN DATA */


// [D_089cdf24] Perfect Campaign Gifts
struct CampaignGiftData campaign_gifts_table[] = {
    /* REMIX1 */ {
        /* Grid Pos. */ 2, 6,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_SFX
    },
    /* REMIX2 */ {
        /* Grid Pos. */ 3, 6,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_BON_ODORI
    },
    /* REMIX3 */ {
        /* Grid Pos. */ 4, 6,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_HONEY_SWEET_ANGEL
    },
    /* REMIX4 */ {
        /* Grid Pos. */ 5, 6,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_CAFE
    },
    /* REMIX5 */ {
        /* Grid Pos. */ 6, 6,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_WISH
    },
    /* REMIX6 */ {
        /* Grid Pos. */ 7, 6,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_REMIX6
    },
    /* REMIX7 */ {
        /* Grid Pos. */ 8, 6,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_FAN_MAIL
    },
    /* REMIX8 */ {
        /* Grid Pos. */ 9, 6,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_REMIX8
    },
    /* CLAPPY_TRIO */ {
        /* Grid Pos. */ 2, 7,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_CLAPPY_TRIO
    },
    /* BON_ODORI */ {
        /* Grid Pos. */ 3, 7,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_BON_ODORI
    },
    /* SPACE_DANCE */ {
        /* Grid Pos. */ 4, 7,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SPACE_DANCE
    },
    /* RAP_MEN */ {
        /* Grid Pos. */ 5, 7,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_RAP_MEN
    },
    /* TAP_TRIAL */ {
        /* Grid Pos. */ 6, 7,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_TAP_TRIAL
    },
    /* TAP_TRIAL_2 */ {
        /* Grid Pos. */ 7, 7,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_TAP_TRIAL_2
    },
    /* MARCHING_ORDERS_2 */ {
        /* Grid Pos. */ 8, 7,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_HEEL_TECH_1
    },
    /* SNEAKY_SPIRITS_2 */ {
        /* Grid Pos. */ 9, 7,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_HEAVY
    },
    /* SPACEBALL */ {
        /* Grid Pos. */ 2, 8,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_SPACEBALL
    },
    /* SICK_BEATS */ {
        /* Grid Pos. */ 3, 8,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_RHYTHM_DIAGNOSIS
    },
    /* TRAM_PAULINE */ {
        /* Grid Pos. */ 4, 8,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_MARCHING_ORDERS
    },
    /* POLYRHYTHM */ {
        /* Grid Pos. */ 5, 8,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_REMIX3
    },
    /* FIREWORKS */ {
        /* Grid Pos. */ 6, 8,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_RHYTHM_HAIKU
    },
    /* RAP_WOMEN */ {
        /* Grid Pos. */ 7, 8,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_REMIX5
    },
    /* NIGHT_WALK_2 */ {
        /* Grid Pos. */ 8, 8,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_NIGHT_WALK
    },
    /* SPACEBALL_2 */ {
        /* Grid Pos. */ 9, 8,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_MECHANICAL_HORSE
    },
    /* MARCHING_ORDERS */ {
        /* Grid Pos. */ 2, 9,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_DRY
    },
    /* RAT_RACE */ {
        /* Grid Pos. */ 3, 9,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_TAP
    },
    /* BUNNY_HOP */ {
        /* Grid Pos. */ 4, 9,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_BUNNY_HOP
    },
    /* POWER_CALLIGRAPHY */ {
        /* Grid Pos. */ 5, 9,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_POWER_CALLIGRAPHY
    },
    /* TOSS_BOYS */ {
        /* Grid Pos. */ 6, 9,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_AIR
    },
    /* COSMIC_DANCE */ {
        /* Grid Pos. */ 7, 9,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_COSMIC_DANCE
    },
    /* NINJA_REINCARNATE */ {
        /* Grid Pos. */ 8, 9,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_NINJA_BODYGUARD
    },
    /* POLYRHYTHM_2 */ {
        /* Grid Pos. */ 9, 9,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_HEEL_TECH_2
    },
    /* RHYTHM_TWEEZERS */ {
        /* Grid Pos. */ 2, 10,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_RHYTHM_TWEEZERS
    },
    /* SAMURAI_SLICE */ {
        /* Grid Pos. */ 3, 10,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_ASIAN
    },
    /* SHOWTIME */ {
        /* Grid Pos. */ 4, 10,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SHOWTIME
    },
    /* NIGHT_WALK */ {
        /* Grid Pos. */ 5, 10,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_NIGHT_WALK
    },
    /* NINJA_BODYGUARD */ {
        /* Grid Pos. */ 6, 10,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_LIGHT
    },
    /* BON_DANCE */ {
        /* Grid Pos. */ 7, 10,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_BON_DANCE
    },
    /* RHYTHM_TWEEZERS_2 */ {
        /* Grid Pos. */ 8, 10,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_HIHAT
    },
    /* TOSS_BOYS_2 */ {
        /* Grid Pos. */ 9, 10,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_TOSS_BOYS
    },
    /* KARATE_MAN */ {
        /* Grid Pos. */ 2, 11,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_KARATE_MAN
    },
    /* SNEAKY_SPIRITS */ {
        /* Grid Pos. */ 3, 11,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_POWER
    },
    /* WIZARDS_WALTZ */ {
        /* Grid Pos. */ 4, 11,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_RHYTHM_POEM
    },
    /* QUIZ_SHOW */ {
        /* Grid Pos. */ 5, 11,
        /* Gift Type */ CAMPAIGN_GIFT_READING_MATERIAL,
        /* Gift ID   */ READING_MATERIAL_RHYTHM_FORMULA
    },
    /* BOUNCY_ROAD */ {
        /* Grid Pos. */ 6, 11,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_MATTE
    },
    /* SNAPPY_TRIO */ {
        /* Grid Pos. */ 7, 11,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SNAPPY_TRIO
    },
    /* KARATE_MAN_2 */ {
        /* Grid Pos. */ 8, 11,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_SAMURAI
    },
    /* BOUNCY_ROAD_2 */ {
        /* Grid Pos. */ 9, 11,
        /* Gift Type */ CAMPAIGN_GIFT_DRUM_KIT,
        /* Gift ID   */ STUDIO_DRUM_TECHNO
    },
    /* KARATE_MAN_EXTRA */ {
        /* Grid Pos. */ 10, 11,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SILENCE
    },
    /* RHYTHM_TWEEZERS_EXTRA */ {
        /* Grid Pos. */ 10, 10,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SILENCE
    },
    /* MARCHNG_ORDERS_EXTRA */ {
        /* Grid Pos. */ 10, 9,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SILENCE
    },
    /* SPACEBALL_EXTRA */ {
        /* Grid Pos. */ 10, 8,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SILENCE
    },
    /* CLAPPY_TRIO_EXTRA */ {
        /* Grid Pos. */ 10, 7,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SILENCE
    },
    /* REMIX_1_EXTRA */ {
        /* Grid Pos. */ 10, 6,
        /* Gift Type */ CAMPAIGN_GIFT_SONG,
        /* Gift ID   */ STUDIO_SONG_SILENCE
    }
};


// [D_089ce0a4] Perfect Campaign Border Sprites
struct Animation *campaign_icon_borders[MAX_PERFECT_ATTEMPTS] = {
    /* Attempt 3 */ anim_game_select_border_perfect1,
    /* Attempt 2 */ anim_game_select_border_perfect2,
    /* Attempt 1 */ anim_game_select_border_perfect3
};
