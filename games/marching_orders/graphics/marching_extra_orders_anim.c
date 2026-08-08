#include "global.h"
#include "graphics.h"

#include "marching_orders_extra_anim_cells.inc.c"

// [D_088f124c] Marcher Test
struct Animation anim_marching_extra_test[] = {
    /* 000 */ { marching_orders_extra_cel005, 3 },
    /* 001 */ { marching_orders_extra_cel006, 3 },
    /* 002 */ { marching_orders_extra_cel007, 3 },
    /* 003 */ { marching_orders_extra_cel008, 3 },
    /* 004 */ { marching_orders_extra_cel009, 3 },
    /* 005 */ { marching_orders_extra_cel008, 3 },
    /* 006 */ { marching_orders_extra_cel007, 3 },
    /* 007 */ { marching_orders_extra_cel006, 3 },
    /* 008 */ { marching_orders_extra_cel005, 3 },
    /* 009 */ { marching_orders_extra_cel010, 3 },
    /* 010 */ { marching_orders_extra_cel011, 3 },
    /* 011 */ { marching_orders_extra_cel012, 3 },
    /* 012 */ { marching_orders_extra_cel013, 3 },
    /* 013 */ { marching_orders_extra_cel012, 3 },
    /* 014 */ { marching_orders_extra_cel011, 3 },
    /* 015 */ { marching_orders_extra_cel010, 3 },
    /* 016 */ { marching_orders_extra_cel005, 3 },
    /* 017 */ { marching_orders_extra_cel006, 3 },
    /* 018 */ { marching_orders_extra_cel007, 3 },
    /* 019 */ { marching_orders_extra_cel008, 3 },
    /* 020 */ { marching_orders_extra_cel009, 3 },
    /* 021 */ { marching_orders_extra_cel008, 3 },
    /* 022 */ { marching_orders_extra_cel007, 3 },
    /* 023 */ { marching_orders_extra_cel006, 3 },
    /* 024 */ { marching_orders_extra_cel005, 3 },
    /* 025 */ { marching_orders_extra_cel010, 3 },
    /* 026 */ { marching_orders_extra_cel011, 3 },
    /* 027 */ { marching_orders_extra_cel012, 3 },
    /* 028 */ { marching_orders_extra_cel013, 3 },
    /* 029 */ { marching_orders_extra_cel012, 3 },
    /* 030 */ { marching_orders_extra_cel011, 3 },
    /* 031 */ { marching_orders_extra_cel010, 3 },
    /* 032 */ { marching_orders_extra_cel010, 3 },
    /* 033 */ { marching_orders_extra_cel005, 3 },
    /* 034 */ { marching_orders_extra_cel004, 30 },
    /* End */ END_ANIMATION
};

// [D_088f136c] Marcher - Turn Left
struct Animation anim_marching_extra_turn_l[] = {
    /* 000 */ { marching_orders_extra_cel014, 10 },
    /* 001 */ { marching_orders_extra_cel015, 4 },
    /* 002 */ { marching_orders_extra_cel016, 4 },
    /* 003 */ { marching_orders_extra_cel004, 30 },
    /* End */ END_ANIMATION
};

// [D_088f1394] Marcher - Turn Right
struct Animation anim_marching_extra_turn_r[] = {
    /* 000 */ { marching_orders_extra_cel018, 10 },
    /* 001 */ { marching_orders_extra_cel019, 4 },
    /* 002 */ { marching_orders_extra_cel020, 4 },
    /* 003 */ { marching_orders_extra_cel004, 30 },
    /* End */ END_ANIMATION
};

// [D_088f13bc] Marcher - Point Left
struct Animation anim_marching_extra_point_l[] = {
    /* 000 */ { marching_orders_extra_cel023, 10 },
    /* 001 */ { marching_orders_extra_cel022, 4 },
    /* 002 */ { marching_orders_extra_cel021, 3 },
    /* 003 */ { marching_orders_extra_cel017, 30 },
    /* End */ END_ANIMATION
};

// [D_088f13e4] Marcher - Point Right
struct Animation anim_marching_extra_point_r[] = {
    /* 000 */ { marching_orders_extra_cel026, 10 },
    /* 001 */ { marching_orders_extra_cel025, 4 },
    /* 002 */ { marching_orders_extra_cel024, 3 },
    /* 003 */ { marching_orders_extra_cel017, 30 },
    /* End */ END_ANIMATION
};

// [D_088f140c] Commander - Angry
struct Animation anim_marching_extra_commander_angry[] = {
    /* 000 */ { marching_orders_extra_cel003, 20 },
    /* 001 */ { marching_orders_extra_cel002, 6 },
    /* 002 */ { marching_orders_extra_cel001, 6 },
    /* 003 */ { marching_orders_extra_cel000, 6 },
    /* End */ END_ANIMATION
};

// [D_088f1434] Marcher - Stop Beat
struct Animation anim_marching_extra_stop_beat[] = {
    /* 000 */ { marching_orders_extra_cel039, 4 },
    /* 001 */ { marching_orders_extra_cel040, 4 },
    /* 002 */ { marching_orders_extra_cel041, 50 },
    /* End */ END_ANIMATION
};

// [D_088f1454] Marcher - Clap
struct Animation anim_marching_extra_clap[] = {
    /* 000 */ { marching_orders_extra_cel036, 4 },
    /* 001 */ { marching_orders_extra_cel038, 3 },
    /* 002 */ { marching_orders_extra_cel037, 30 },
    /* End */ END_ANIMATION
};

// [D_088f1474] Marcher - Beat
struct Animation anim_marching_extra_beat[] = {
    /* 000 */ { marching_orders_extra_cel041, 4 },
    /* 001 */ { marching_orders_extra_cel040, 4 },
    /* 002 */ { marching_orders_extra_cel039, 40 },
    /* End */ END_ANIMATION
};

// [D_088f1494] Marcher - Step Right (Body)
struct Animation anim_marching_extra_step_r[] = {
    /* 000 */ { marching_orders_extra_cel042, 2 },
    /* 001 */ { marching_orders_extra_cel043, 2 },
    /* 002 */ { marching_orders_extra_cel044, 2 },
    /* 003 */ { marching_orders_extra_cel045, 2 },
    /* 004 */ { marching_orders_extra_cel046, 40 },
    /* End */ END_ANIMATION
};

// [D_088f14c4] Marcher - Step Left (Body)
struct Animation anim_marching_extra_step_l[] = {
    /* 000 */ { marching_orders_extra_cel042, 2 },
    /* 001 */ { marching_orders_extra_cel047, 2 },
    /* 002 */ { marching_orders_extra_cel048, 2 },
    /* 003 */ { marching_orders_extra_cel049, 2 },
    /* 004 */ { marching_orders_extra_cel050, 40 },
    /* End */ END_ANIMATION
};

// [D_088f14f4] Marcher - Turn Right (Head)
struct Animation anim_marching_extra_head_turn_r[] = {
    /* 000 */ { marching_orders_extra_cel033, 10 },
    /* 001 */ { marching_orders_extra_cel034, 4 },
    /* 002 */ { marching_orders_extra_cel035, 4 },
    /* 003 */ { marching_orders_extra_cel029, 30 },
    /* End */ END_ANIMATION
};

// [D_088f151c] Marcher - Turn Left (Head)
struct Animation anim_marching_extra_head_turn_l[] = {
    /* 000 */ { marching_orders_extra_cel030, 10 },
    /* 001 */ { marching_orders_extra_cel031, 4 },
    /* 002 */ { marching_orders_extra_cel032, 4 },
    /* 003 */ { marching_orders_extra_cel029, 30 },
    /* End */ END_ANIMATION
};

// [D_088f1544] Tutorial Icons
struct Animation anim_marching_extra_tutorial_icons[] = {
    /* 000 */ { marching_orders_extra_cel051, 40 },
    /* 001 */ { marching_orders_extra_cel053, 40 },
    /* 002 */ { marching_orders_extra_cel054, 40 },
    /* 003 */ { marching_orders_extra_cel055, 40 },
    /* 004 */ { marching_orders_extra_cel056, 40 },
    /* End */ END_ANIMATION
};

// [D_088f1574] "Start to Skip" Tutorial Icon (Unused)
struct Animation anim_marching_extra_tutorial_skip_icon[] = {
    /* 000 */ { marching_orders_extra_cel052, 4 },
    /* End */ END_ANIMATION
};

// [D_088f1584] Commander Frustration Cloud
struct Animation anim_marching_extra_angry_puff[] = {
    /* 000 */ { marching_orders_extra_cel057, 4 },
    /* 001 */ { marching_orders_extra_cel058, 5 },
    /* 002 */ { marching_orders_extra_cel059, 4 },
    /* 003 */ { marching_orders_extra_cel060, 4 },
    /* 004 */ { marching_orders_extra_cel061, 4 },
    /* 005 */ { marching_orders_extra_cel062, 4 },
    /* End */ END_ANIMATION
};

// [D_088f15bc] Commander - Annoyed
struct Animation anim_marching_extra_commander_annoyed[] = {
    /* 000 */ { marching_orders_extra_cel063, 30 },
    /* 001 */ { marching_orders_extra_cel064, 6 },
    /* 002 */ { marching_orders_extra_cel000, 6 },
    /* End */ END_ANIMATION
};
