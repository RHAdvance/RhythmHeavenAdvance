#include "global.h"
#include "graphics.h"

#include "game_select_anim_cells.inc.c"

// [D_08902960] Large Rotating Square
struct Animation anim_game_select_bg_square_large[] = {
    /* 000 */ { game_select_cel031, 3 },
    /* 001 */ { game_select_cel032, 3 },
    /* 002 */ { game_select_cel033, 3 },
    /* 003 */ { game_select_cel034, 3 },
    /* 004 */ { game_select_cel035, 3 },
    /* 005 */ { game_select_cel036, 3 },
    /* End */ END_ANIMATION
};

// [D_08902998] Small Rotating Square
struct Animation anim_game_select_bg_square_small[] = {
    /* 000 */ { game_select_cel037, 3 },
    /* 001 */ { game_select_cel038, 3 },
    /* 002 */ { game_select_cel039, 3 },
    /* 003 */ { game_select_cel040, 3 },
    /* 004 */ { game_select_cel041, 3 },
    /* 005 */ { game_select_cel042, 3 },
    /* End */ END_ANIMATION
};

// [D_089029d0] Selected Rhythm Game Border
struct Animation anim_game_select_border_target[] = {
    /* 000 */ { game_select_cel005, 5 },
    /* 001 */ { game_select_cel006, 5 },
    /* 002 */ { game_select_cel009, 5 },
    /* 003 */ { game_select_cel008, 5 },
    /* 004 */ { game_select_cel009, 5 },
    /* 005 */ { game_select_cel007, 5 },
    /* 006 */ { game_select_cel010, 5 },
    /* End */ END_ANIMATION
};

// [D_08902a10] Rhythm Game Gradient Border
struct Animation anim_game_select_new_game[] = {
    /* 000 */ { game_select_cel011, 2 },
    /* 001 */ { game_select_cel012, 2 },
    /* 002 */ { game_select_cel013, 2 },
    /* 003 */ { game_select_cel014, 2 },
    /* 004 */ { game_select_cel015, 2 },
    /* End */ END_ANIMATION
};

// [D_08902a40] Flickering, Shrinking White Square
struct Animation anim_game_select_clear_game[] = {
    /* 000 */ { game_select_cel016, 2 },
    /* 001 */ { game_select_cel000, 1 },
    /* 002 */ { game_select_cel017, 2 },
    /* 003 */ { game_select_cel000, 1 },
    /* 004 */ { game_select_cel018, 2 },
    /* 005 */ { game_select_cel000, 1 },
    /* 006 */ { game_select_cel019, 2 },
    /* 007 */ { game_select_cel000, 1 },
    /* 008 */ { game_select_cel020, 2 },
    /* 009 */ { game_select_cel000, 1 },
    /* 010 */ { game_select_cel021, 2 },
    /* 011 */ { game_select_cel000, 1 },
    /* 012 */ { game_select_cel022, 2 },
    /* 013 */ { game_select_cel000, 1 },
    /* 014 */ { game_select_cel023, 2 },
    /* 015 */ { game_select_cel000, 1 },
    /* 016 */ { game_select_cel024, 2 },
    /* End */ END_ANIMATION
};

// [D_08902ad0] Rhythm Game Get Superb Shine
struct Animation anim_game_select_get_superb[] = {
    /* 000 */ { game_select_cel025, 2 },
    /* 001 */ { game_select_cel026, 2 },
    /* 002 */ { game_select_cel027, 2 },
    /* 003 */ { game_select_cel028, 2 },
    /* 004 */ { game_select_cel029, 2 },
    /* 005 */ { game_select_cel030, 2 },
    /* 006 */ { game_select_cel000, 10 },
    /* 007 */ { game_select_cel025, 1 },
    /* 008 */ { game_select_cel026, 1 },
    /* 009 */ { game_select_cel027, 1 },
    /* 010 */ { game_select_cel028, 1 },
    /* 011 */ { game_select_cel029, 1 },
    /* 012 */ { game_select_cel030, 1 },
    /* End */ END_ANIMATION
};

// [D_08902b40] STAGE 1
struct Animation anim_game_select_stage1[] = {
    /* 000 */ { game_select_cel043, 30 },
    /* 001 */ { game_select_cel044, 3 },
    /* 002 */ { game_select_cel045, 3 },
    /* 003 */ { game_select_cel046, 40 },
    /* End */ END_ANIMATION
};

// [D_08902b68] Blank Stage Text Box
struct Animation anim_game_select_stage_box[] = {
    /* 000 */ { game_select_cel080, 4 },
    /* End */ END_ANIMATION
};

// [D_08902b78] Flow Count Numbers
struct Animation anim_game_select_flow_num[] = {
    /* 000 */ { game_select_cel081, 4 },
    /* 001 */ { game_select_cel082, 4 },
    /* 002 */ { game_select_cel083, 4 },
    /* 003 */ { game_select_cel084, 4 },
    /* 004 */ { game_select_cel085, 4 },
    /* 005 */ { game_select_cel086, 4 },
    /* 006 */ { game_select_cel087, 4 },
    /* 007 */ { game_select_cel088, 4 },
    /* 008 */ { game_select_cel089, 4 },
    /* 009 */ { game_select_cel090, 4 },
    /* 010 */ { game_select_cel000, 4 },
    /* End */ END_ANIMATION
};

// [D_08902bd8] Your Flow
struct Animation anim_game_select_flow_text[] = {
    /* 000 */ { game_select_cel091, 20 },
    /* 001 */ { game_select_cel092, 10 },
    /* End */ END_ANIMATION
};

// [D_08902bf0] Flow Direction
struct Animation anim_game_select_flow_arrow[] = {
    /* 000 */ { game_select_cel093, 40 },
    /* 001 */ { game_select_cel094, 40 },
    /* 002 */ { game_select_cel095, 40 },
    /* End */ END_ANIMATION
};

// [D_08902c10] Perfect Campaign Border (3 Attempts Remaining)
struct Animation anim_game_select_border_perfect3[] = {
    /* 000 */ { game_select_cel097, 4 },
    /* 001 */ { game_select_cel098, 4 },
    /* 002 */ { game_select_cel099, 4 },
    /* End */ END_ANIMATION
};

// [D_08902c30] A Button Prompt
struct Animation anim_game_select_text_button[] = {
    /* 000 */ { game_select_cel107, 3 },
    /* 001 */ { game_select_cel108, 3 },
    /* 002 */ { game_select_cel106, 40 },
    /* End */ END_ANIMATION
};

// [D_08902c50] Unused Medal Count
struct Animation anim_game_select_medal_count_unused[] = {
    /* 000 */ { game_select_cel109, 3 },
    /* 001 */ { game_select_cel110, 3 },
    /* 002 */ { game_select_cel111, 3 },
    /* 003 */ { game_select_cel112, 3 },
    /* 004 */ { game_select_cel113, 3 },
    /* 005 */ { game_select_cel114, 60 },
    /* End */ END_ANIMATION
};

// [D_08902c88] Medal Count Numbers
struct Animation anim_game_select_medal_num[] = {
    /* 000 */ { game_select_cel115, 10 },
    /* 001 */ { game_select_cel116, 10 },
    /* 002 */ { game_select_cel117, 10 },
    /* 003 */ { game_select_cel118, 10 },
    /* 004 */ { game_select_cel119, 10 },
    /* 005 */ { game_select_cel120, 10 },
    /* 006 */ { game_select_cel121, 10 },
    /* 007 */ { game_select_cel122, 10 },
    /* 008 */ { game_select_cel123, 10 },
    /* 009 */ { game_select_cel124, 10 },
    /* 010 */ { game_select_cel000, 10 },
    /* End */ END_ANIMATION
};

// [D_08902ce8] Medal Count Number 0
struct Animation anim_game_select_medal_num0[] = {
    /* 000 */ { game_select_cel115, 4 },
    /* End */ END_ANIMATION
};

// [D_08902cf8] Medal Count Text
struct Animation anim_game_select_medal_text[] = {
    /* 000 */ { game_select_cel125, 4 },
    /* End */ END_ANIMATION
};

// [D_08902d08] STAGE 2
struct Animation anim_game_select_stage2[] = {
    /* 000 */ { game_select_cel047, 30 },
    /* 001 */ { game_select_cel048, 3 },
    /* 002 */ { game_select_cel049, 3 },
    /* 003 */ { game_select_cel050, 40 },
    /* End */ END_ANIMATION
};

// [D_08902d30] STAGE 3
struct Animation anim_game_select_stage3[] = {
    /* 000 */ { game_select_cel051, 30 },
    /* 001 */ { game_select_cel052, 3 },
    /* 002 */ { game_select_cel053, 3 },
    /* 003 */ { game_select_cel054, 40 },
    /* End */ END_ANIMATION
};

// [D_08902d58] STAGE 4
struct Animation anim_game_select_stage4[] = {
    /* 000 */ { game_select_cel055, 30 },
    /* 001 */ { game_select_cel056, 3 },
    /* 002 */ { game_select_cel057, 3 },
    /* 003 */ { game_select_cel058, 40 },
    /* End */ END_ANIMATION
};

// [D_08902d80] STAGE 5
struct Animation anim_game_select_stage5[] = {
    /* 000 */ { game_select_cel059, 30 },
    /* 001 */ { game_select_cel060, 3 },
    /* 002 */ { game_select_cel061, 3 },
    /* 003 */ { game_select_cel062, 40 },
    /* End */ END_ANIMATION
};

// [D_08902da8] MEDAL CORNER
struct Animation anim_game_select_stage0[] = {
    /* 000 */ { game_select_cel063, 30 },
    /* 001 */ { game_select_cel064, 3 },
    /* 002 */ { game_select_cel065, 3 },
    /* 003 */ { game_select_cel066, 40 },
    /* End */ END_ANIMATION
};

// [D_08902dd0] REVIVAL
struct Animation anim_game_select_stage6[] = {
    /* 000 */ { game_select_cel067, 30 },
    /* 001 */ { game_select_cel068, 3 },
    /* 002 */ { game_select_cel069, 3 },
    /* 003 */ { game_select_cel070, 40 },
    /* End */ END_ANIMATION
};

// [D_08902df8] TECHNICIAN
struct Animation anim_game_select_stage7[] = {
    /* 000 */ { game_select_cel071, 30 },
    /* 001 */ { game_select_cel072, 3 },
    /* 002 */ { game_select_cel073, 3 },
    /* 003 */ { game_select_cel074, 40 },
    /* End */ END_ANIMATION
};

// [D_08902e20] LAST TECHNICIAN
struct Animation anim_game_select_stage8[] = {
    /* 000 */ { game_select_cel075, 30 },
    /* 001 */ { game_select_cel076, 3 },
    /* 002 */ { game_select_cel077, 3 },
    /* 003 */ { game_select_cel078, 40 },
    /* End */ END_ANIMATION
};

// [D_08902e20] EXTRA
struct Animation anim_game_select_stage9[] = {
    /* 000 */ { game_select_cel128, 30 },
    /* 001 */ { game_select_cel129, 3 },
    /* 002 */ { game_select_cel130, 3 },
    /* 003 */ { game_select_cel131, 40 },
    /* End */ END_ANIMATION
};

// [D_08902e48] Perfect Campaign Border (2 Attempts Remaining)
struct Animation anim_game_select_border_perfect2[] = {
    /* 000 */ { game_select_cel100, 4 },
    /* 001 */ { game_select_cel101, 4 },
    /* 002 */ { game_select_cel102, 4 },
    /* End */ END_ANIMATION
};

// [D_08902e68] Perfect Campaign Border (1 Attempt Remaining)
struct Animation anim_game_select_border_perfect1[] = {
    /* 000 */ { game_select_cel103, 4 },
    /* 001 */ { game_select_cel104, 4 },
    /* 002 */ { game_select_cel105, 4 },
    /* End */ END_ANIMATION
};

// [D_08902e88] Cursor
struct Animation anim_game_select_cursor[] = {
    /* 000 */ { game_select_cel001, 4 },
    /* 001 */ { game_select_cel002, 2 },
    /* 002 */ { game_select_cel003, 5 },
    /* 003 */ { game_select_cel004, 30 },
    /* End */ END_ANIMATION
};

// [D_08902eb0] Perfect Cleared
struct Animation anim_game_select_perfect_rank[] = {
    /* 000 */ { game_select_cel126, 4 },
    /* End */ END_ANIMATION
};

struct Animation anim_game_select_no_practice[] = {
    /* 000 */ { game_select_cel127, 1 },
    /* End */ END_ANIMATION
};

struct Animation anim_game_select_tempo_up[] = {
    /* 000 */ { game_select_cel132, 1 },
    /* End */ END_ANIMATION
};  
