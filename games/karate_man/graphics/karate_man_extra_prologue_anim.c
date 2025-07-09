#include "global.h"
#include "graphics.h"

#include "karate_man_extra_prologue_anim_cells.inc.c"

// [D_088ada78] Title
struct Animation anim_karate_man_extra_prologue_title[] = {
    /* 000 */ { karate_man_extra_prologue_cel000, 20 },
    /* 001 */ { karate_man_extra_prologue_cel001, 10 },
    /* 002 */ { karate_man_extra_prologue_cel002, 10 },
    /* 003 */ { karate_man_extra_prologue_cel003, 10 },
    /* 004 */ { karate_man_extra_prologue_cel004, 60 },
    /* End */ END_ANIMATION
};

// [D_088adaa8] Kick
struct Animation anim_karate_man_extra_prologue_kick[] = {
    /* 000 */ { karate_man_extra_prologue_cel007, 60 },
    /* 001 */ { karate_man_extra_prologue_cel005, 2 },
    /* 002 */ { karate_man_extra_prologue_cel006, 2 },
    /* 003 */ { karate_man_extra_prologue_cel005, 2 },
    /* 004 */ { karate_man_extra_prologue_cel006, 1 },
    /* 005 */ { karate_man_extra_prologue_cel005, 60 },
    /* End */ END_ANIMATION
};
