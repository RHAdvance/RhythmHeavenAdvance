#include "global.h"
#include "graphics.h"

#include "results_level_anim_cells.inc.c"

// [D_0890b6ac] Placeholder Header ("nori-kan check")
struct Animation anim_rank_results_header_placeholder[] = {
    /* 000 */ { results_level_cel000, 4 },
    /* End */ END_ANIMATION
};

// [D_0890b6bc] Result Icon { 0 = OK; 1 = Try Again; 2 = Superb }
struct Animation anim_rank_results_icon[] = {
    /* 000 */ { results_level_cel001, 90 },
    /* 001 */ { results_level_cel002, 90 },
    /* 002 */ { results_level_cel003, 90 },
    /* End */ END_ANIMATION
};

// [D_0890b6dc] Positive Reinforcement Text Bubble
struct Animation anim_rank_results_supportive_bubble[] = {
    /* 000 */ { results_level_cel007, 4 },
    /* End */ END_ANIMATION
};

// [D_0890b6ec] Header Text Box
struct Animation anim_rank_results_header_box[] = {
    /* 000 */ { results_level_cel008, 4 },
    /* End */ END_ANIMATION
};

// [D_0890b6fc] Header Text Box Mask
struct Animation anim_rank_results_header_box_mask[] = {
    /* 000 */ { results_level_cel009, 4 },
    /* End */ END_ANIMATION
};

// [D_0890b70c] "Medal Get!"
struct Animation anim_rank_results_medal_get[] = {
    /* 000 */ { results_level_cel004, 30 },
    /* 001 */ { results_level_cel005, 20 },
    /* End */ END_ANIMATION
};

// [D_0890b724] "でも" ("but")
struct Animation anim_rank_results_comment_append[] = {
    /* 000 */ { results_level_cel006, 4 },
    /* End */ END_ANIMATION
};
