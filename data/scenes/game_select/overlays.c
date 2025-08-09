#include "global.h"
#include "graphics.h"
#include "levels.h"
#include "src/task_pool.h"
#include "src/scenes/game_select.h"
#include "graphics/game_select/game_select_graphics.h"


  /* GAME SELECT - LEVEL ICON OVERLAY DATA */


// [D_089cfa08] Blank, Unused
struct GameSelectOverlay game_select_icon_overlay_null = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_blank2_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 0, 1,
        /* End */ LEVEL_ICON_ANIM_STOP
    }
};

// [D_089cfa14] Blank
struct GameSelectOverlay game_select_icon_overlay_hidden = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_blank1_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 0, 1,
        /* End */ LEVEL_ICON_ANIM_STOP
    }
};

// [D_089cfa20] Not Yet Unlocked (Rhythm Game)
struct GameSelectOverlay game_select_icon_overlay_closed = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_closed_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 0, 1,
        /* End */ LEVEL_ICON_ANIM_STOP
    }
};

// [D_089cfa2c] Not Yet Unlocked (Remix)
struct GameSelectOverlay game_select_icon_overlay_remix_closed = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_closed_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 1, 24,
        /* 001 */ 2, 24,
        /* End */ LEVEL_ICON_ANIM_LOOP
    }
};

// [D_089cfa38] Unlocked, Not Yet Cleared (Rhythm Game)
struct GameSelectOverlay game_select_icon_overlay_uncleared = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_new_game_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 0, 5,
        /* 001 */ 1, 2,
        /* 002 */ 2, 2,
        /* 003 */ 3, 2,
        /* 004 */ 4, 2,
        /* 005 */ 5, 2,
        /* 006 */ 6, 2,
        /* 007 */ 7, 2,
        /* 008 */ 8, 5,
        /* 009 */ 8, 5,
        /* 010 */ 7, 2,
        /* 011 */ 6, 2,
        /* 012 */ 5, 2,
        /* 013 */ 4, 2,
        /* 014 */ 3, 2,
        /* 015 */ 2, 2,
        /* 016 */ 1, 2,
        /* 017 */ 0, 5,
        /* End */ LEVEL_ICON_ANIM_LOOP
    }
};

// [D_089cfa44] Unlocked, Not Yet Cleared (Remix)
struct GameSelectOverlay game_select_icon_overlay_remix_uncleared = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_new_game_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */  4, 2,
        /* 001 */  5, 2,
        /* 002 */  6, 2,
        /* 003 */  7, 2,
        /* 004 */  8, 5,
        /* 005 */  8, 5,
        /* 006 */  7, 2,
        /* 007 */  6, 2,
        /* 008 */  5, 2,
        /* 009 */  4, 2,
        /* 010 */ 12, 2,
        /* 011 */ 11, 2,
        /* 012 */ 10, 2,
        /* 013 */  9, 5,
        /* 014 */  9, 5,
        /* 015 */ 10, 2,
        /* 016 */ 11, 2,
        /* 017 */ 12, 2,
        /* End */ LEVEL_ICON_ANIM_LOOP
    }
};

// [D_089cfa50] Cleared, No Medal
struct GameSelectOverlay game_select_icon_overlay_cleared = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_normal_border_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 0, 1,
        /* End */ LEVEL_ICON_ANIM_STOP
    }
};

// [D_089cfa5c] Cleared, With Medal
struct GameSelectOverlay game_select_icon_overlay_medal = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_medal_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 0, 40,
        /* 001 */ 1, 3,
        /* 002 */ 2, 3,
        /* 003 */ 3, 3,
        /* 004 */ 4, 3,
        /* End */ LEVEL_ICON_ANIM_LOOP
    }
};

// [D_089cfa68] Medal Corner
struct GameSelectOverlay game_select_icon_overlay_bonus = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_striped_border_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 0, 3,
        /* 001 */ 1, 3,
        /* 002 */ 2, 3,
        /* 003 */ 3, 3,
        /* End */ LEVEL_ICON_ANIM_LOOP
    }
};

// [D_089cfa74] Perfect Cleared
struct GameSelectOverlay game_select_icon_overlay_perfect = {
    /* Dimensions */ 3, 3,
    /* Texture    */ icon_overlay_perfect_bin,
    /* Anim. Data */ (s8[]) {
        /* 000 */ 0, 1,
        /* End */ LEVEL_ICON_ANIM_STOP
    }
};

// [D_089cfa80] Overlay Data Table
struct GameSelectOverlay *level_icon_overlay_data[] = {
    /* 00 */ &game_select_icon_overlay_hidden,
    /* 01 */ &game_select_icon_overlay_closed,
    /* 02 */ &game_select_icon_overlay_uncleared,
    /* 03 */ &game_select_icon_overlay_cleared,
    /* 04 */ &game_select_icon_overlay_medal,
    /* 05 */ &game_select_icon_overlay_remix_closed,
    /* 06 */ &game_select_icon_overlay_remix_uncleared,
    /* 07 */ &game_select_icon_overlay_bonus,
    /* 08 */ &game_select_icon_overlay_perfect,
    /* 09 */ NULL
};


// [D_089cfa98] Icon Overlay Map (Rhythm Game)
u8 game_level_icon_overlays_map[] = {
    /* HIDDEN    */ LEVEL_ICON_OVERLAY_BLANK,
    /* INVALID   */ LEVEL_ICON_OVERLAY_BLANK,
    /* CLOSED    */ LEVEL_ICON_OVERLAY_CLOSED,
    /* UNCLEARED */ LEVEL_ICON_OVERLAY_UNCLEARED,
    /* CLEARED   */ LEVEL_ICON_OVERLAY_CLEARED,
    /* HAS_MEDAL */ LEVEL_ICON_OVERLAY_MEDAL,
    /* PERFECT   */ LEVEL_ICON_OVERLAY_PERFECT
};

// [D_089cfa9e] Icon Overlay Map (Remix)
u8 remix_level_icon_overlays_map[] = {
    /* HIDDEN    */ LEVEL_ICON_OVERLAY_BLANK,
    /* INVALID   */ LEVEL_ICON_OVERLAY_BLANK,
    /* CLOSED    */ LEVEL_ICON_OVERLAY_REMIX_CLOSED,
    /* UNCLEARED */ LEVEL_ICON_OVERLAY_REMIX_UNCLEARED,
    /* CLEARED   */ LEVEL_ICON_OVERLAY_CLEARED,
    /* HAS_MEDAL */ LEVEL_ICON_OVERLAY_MEDAL,
    /* PERFECT   */ LEVEL_ICON_OVERLAY_PERFECT
};

// [D_089cfaa4] Icon Overlay Map (Medal Corner)
u8 bonus_level_icon_overlays_map[] = {
    /* HIDDEN    */ LEVEL_ICON_OVERLAY_BLANK,
    /* INVALID   */ LEVEL_ICON_OVERLAY_BLANK,
    /* CLOSED    */ LEVEL_ICON_OVERLAY_CLOSED,
    /* UNCLEARED */ LEVEL_ICON_OVERLAY_UNCLEARED,
    /* CLEARED   */ LEVEL_ICON_OVERLAY_BONUS,
    /* HAS_MEDAL */ LEVEL_ICON_OVERLAY_MEDAL,
    /* PERFECT   */ LEVEL_ICON_OVERLAY_PERFECT
};

// [D_089cfaac] Icon Overlay Map
u8 *level_icon_overlays_map[] = {
    /* GAME  */ game_level_icon_overlays_map,
    /* REMIX */ remix_level_icon_overlays_map,
    /* BONUS */ bonus_level_icon_overlays_map
};


// [D_089cfab8] Level Icon Overlay Animator Task
struct TaskMethods level_icon_overlay_animator_task = {
    (TaskStartFunc)game_select_init_icon_animator,
    NULL,
    (TaskUpdateFunc)game_select_update_icon_animator,
    NULL
};
