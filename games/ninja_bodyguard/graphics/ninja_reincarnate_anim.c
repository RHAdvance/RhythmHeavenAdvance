#include "global.h"
#include "graphics.h"

#include "ninja_reincarnate_anim_cells.inc.c"

// [D_08935070] Tanaka - Cut Right + Spin
struct Animation anim_tanaka_slice_spin_r[] = {
    /* 000 */ { ninja_reincarnate_cel019, 20 },
    /* 001 */ { ninja_reincarnate_cel024, 4 },
    /* 002 */ { ninja_reincarnate_cel025, 8 },
    /* 003 */ { ninja_reincarnate_cel026, 4 },
    /* 004 */ { ninja_reincarnate_cel027, 4 },
    /* 005 */ { ninja_reincarnate_cel028, 4 },
    /* 006 */ { ninja_reincarnate_cel001, 8 },
    /* 007 */ { ninja_reincarnate_cel002, 20 },
    /* End */ END_ANIMATION
};

// [D_089350b8] Tanaka - Cut Left + Spin
struct Animation anim_tanaka_slice_spin_l[] = {
    /* 000 */ { ninja_reincarnate_cel025, 20 },
    /* 001 */ { ninja_reincarnate_cel030, 4 },
    /* 002 */ { ninja_reincarnate_cel031, 8 },
    /* 003 */ { ninja_reincarnate_cel033, 4 },
    /* 004 */ { ninja_reincarnate_cel034, 4 },
    /* 005 */ { ninja_reincarnate_cel035, 4 },
    /* 006 */ { ninja_reincarnate_cel036, 8 },
    /* 007 */ { ninja_reincarnate_cel036, 20 },
    /* End */ END_ANIMATION
};

// [D_08935100] Tanaka - Bow to Woman
struct Animation anim_tanaka_bow_to_girlfriend[] = {
    /* 000 */ { ninja_reincarnate_cel037, 8 },
    /* 001 */ { ninja_reincarnate_cel038, 8 },
    /* 002 */ { ninja_reincarnate_cel039, 8 },
    /* End */ END_ANIMATION
};

// [D_08935120] Bad Guy - Draw Slingshot
struct Animation anim_bad_guy_draw_slingshot[] = {
    /* 000 */ { ninja_reincarnate_cel069, 1 },
    /* 001 */ { ninja_reincarnate_cel070, 1 },
    /* 002 */ { ninja_reincarnate_cel071, 1 },
    /* 003 */ { ninja_reincarnate_cel074, 1 },
    /* 004 */ { ninja_reincarnate_cel076, 1 },
    /* 005 */ { ninja_reincarnate_cel078, 1 },
    /* 006 */ { ninja_reincarnate_cel079, 1 },
    /* 007 */ { ninja_reincarnate_cel080, 2 },
    /* 008 */ { ninja_reincarnate_cel081, 2 },
    /* 009 */ { ninja_reincarnate_cel082, 10 },
    /* End */ END_ANIMATION
};

// [D_08935178] Rock - Drawn
struct Animation anim_bad_guy_rock_draw[] = {
    /* 000 */ { ninja_reincarnate_cel101, 36 },
    /* 001 */ { ninja_reincarnate_cel087, 1 },
    /* 002 */ { ninja_reincarnate_cel088, 1 },
    /* 003 */ { ninja_reincarnate_cel089, 1 },
    /* 004 */ { ninja_reincarnate_cel090, 1 },
    /* 005 */ { ninja_reincarnate_cel091, 1 },
    /* 006 */ { ninja_reincarnate_cel092, 1 },
    /* 007 */ { ninja_reincarnate_cel093, 1 },
    /* 008 */ { ninja_reincarnate_cel094, 1 },
    /* 009 */ { ninja_reincarnate_cel095, 1 },
    /* 010 */ { ninja_reincarnate_cel096, 1 },
    /* 011 */ { ninja_reincarnate_cel097, 1 },
    /* 012 */ { ninja_reincarnate_cel098, 1 },
    /* 013 */ { ninja_reincarnate_cel099, 1 },
    /* 014 */ { ninja_reincarnate_cel100, 10 },
    /* End */ END_ANIMATION
};

// [D_089351f8] Woman - Blink
struct Animation anim_girlfriend_blink[] = {
    /* 000 */ { ninja_reincarnate_cel012, 8 },
    /* 001 */ { ninja_reincarnate_cel011, 8 },
    /* 002 */ { ninja_reincarnate_cel011, 30 },
    /* 003 */ { ninja_reincarnate_cel012, 8 },
    /* 004 */ { ninja_reincarnate_cel011, 20 },
    /* End */ END_ANIMATION
};

// [D_08935228] Woman - Scared
struct Animation anim_girlfriend_scared[] = {
    /* 000 */ { ninja_reincarnate_cel016, 4 },
    /* 001 */ { ninja_reincarnate_cel017, 50 },
    /* End */ END_ANIMATION
};

// [D_08935240] Woman - Shaking
struct Animation anim_girlfriend_shaking[] = {
    /* 000 */ { ninja_reincarnate_cel016, 2 },
    /* 001 */ { ninja_reincarnate_cel018, 2 },
    /* End */ END_ANIMATION
};

// [D_08935258] Heart Eyes
struct Animation anim_ninja2_heart_eyes[] = {
    /* 000 */ { ninja_reincarnate_cel007, 8 },
    /* 001 */ { ninja_reincarnate_cel008, 8 },
    /* 002 */ { ninja_reincarnate_cel009, 30 },
    /* 003 */ { ninja_reincarnate_cel010, 8 },
    /* End */ END_ANIMATION
};

// [D_08935280] Cherry Blossom Petal
struct Animation anim_ninja2_cherry_petal[] = {
    /* 000 */ { ninja_reincarnate_cel004, 6 },
    /* 001 */ { ninja_reincarnate_cel005, 6 },
    /* 002 */ { ninja_reincarnate_cel006, 6 },
    /* 003 */ { ninja_reincarnate_cel005, 6 },
    /* End */ END_ANIMATION
};

// [D_089352a8] Rock - Hit Wall
struct Animation anim_ninja2_rock_to_wall[] = {
    /* 000 */ { ninja_reincarnate_cel040, 1 },
    /* 001 */ { ninja_reincarnate_cel041, 2 },
    /* 002 */ { ninja_reincarnate_cel042, 2 },
    /* 003 */ { ninja_reincarnate_cel043, 1 },
    /* 004 */ { ninja_reincarnate_cel044, 1 },
    /* 005 */ { ninja_reincarnate_cel045, 1 },
    /* 006 */ { ninja_reincarnate_cel046, 1 },
    /* 007 */ { ninja_reincarnate_cel047, 1 },
    /* 008 */ { ninja_reincarnate_cel110, 1 },
    /* 009 */ { ninja_reincarnate_cel111, 1 },
    /* 010 */ { ninja_reincarnate_cel112, 1 },
    /* 011 */ { ninja_reincarnate_cel113, 1 },
    /* 012 */ { ninja_reincarnate_cel114, 1 },
    /* 013 */ { ninja_reincarnate_cel115, 1 },
    /* 014 */ { ninja_reincarnate_cel116, 1 },
    /* 015 */ { ninja_reincarnate_cel117, 1 },
    /* 016 */ { ninja_reincarnate_cel118, 1 },
    /* 017 */ { ninja_reincarnate_cel119, 30 },
    /* End */ END_ANIMATION
};

// [D_08935340] Rock - In Wall
struct Animation anim_ninja2_rock_in_wall1[] = {
    /* 000 */ { ninja_reincarnate_cel131, 2 },
    /* End */ END_ANIMATION
};

// [D_08935350] Rock - In Wall (Duplicate)
struct Animation anim_ninja2_rock_in_wall2[] = {
    /* 000 */ { ninja_reincarnate_cel131, 2 },
    /* End */ END_ANIMATION
};

// [D_08935360] Rock - In Wall (Another Duplicate)
struct Animation anim_ninja2_rock_in_wall3[] = {
    /* 000 */ { ninja_reincarnate_cel131, 2 },
    /* End */ END_ANIMATION
};

// [D_08935370] Rock - Deflected Left
struct Animation anim_ninja2_rock_deflect_l[] = {
    /* 000 */ { ninja_reincarnate_cel040, 1 },
    /* 001 */ { ninja_reincarnate_cel049, 1 },
    /* 002 */ { ninja_reincarnate_cel050, 2 },
    /* 003 */ { ninja_reincarnate_cel051, 2 },
    /* 004 */ { ninja_reincarnate_cel052, 2 },
    /* 005 */ { ninja_reincarnate_cel120, 2 },
    /* 006 */ { ninja_reincarnate_cel121, 1 },
    /* 007 */ { ninja_reincarnate_cel122, 1 },
    /* 008 */ { ninja_reincarnate_cel123, 1 },
    /* 009 */ { ninja_reincarnate_cel124, 1 },
    /* 010 */ { ninja_reincarnate_cel125, 1 },
    /* 011 */ { ninja_reincarnate_cel126, 1 },
    /* 012 */ { ninja_reincarnate_cel127, 1 },
    /* 013 */ { ninja_reincarnate_cel128, 1 },
    /* 014 */ { ninja_reincarnate_cel129, 1 },
    /* 015 */ { ninja_reincarnate_cel130, 1 },
    /* 016 */ { ninja_reincarnate_cel119, 30 },
    /* End */ END_ANIMATION
};

// [D_08935400] Rock - Deflected Right
struct Animation anim_ninja2_rock_deflect_r[] = {
    /* 000 */ { ninja_reincarnate_cel040, 1 },
    /* 001 */ { ninja_reincarnate_cel053, 2 },
    /* 002 */ { ninja_reincarnate_cel054, 2 },
    /* 003 */ { ninja_reincarnate_cel055, 1 },
    /* 004 */ { ninja_reincarnate_cel056, 1 },
    /* 005 */ { ninja_reincarnate_cel057, 1 },
    /* 006 */ { ninja_reincarnate_cel058, 1 },
    /* 007 */ { ninja_reincarnate_cel059, 1 },
    /* 008 */ { ninja_reincarnate_cel060, 1 },
    /* 009 */ { ninja_reincarnate_cel061, 1 },
    /* 010 */ { ninja_reincarnate_cel062, 1 },
    /* 011 */ { ninja_reincarnate_cel063, 1 },
    /* 012 */ { ninja_reincarnate_cel064, 1 },
    /* 013 */ { ninja_reincarnate_cel065, 1 },
    /* 014 */ { ninja_reincarnate_cel066, 1 },
    /* 015 */ { ninja_reincarnate_cel067, 1 },
    /* 016 */ { ninja_reincarnate_cel068, 1 },
    /* 017 */ { ninja_reincarnate_cel119, 30 },
    /* End */ END_ANIMATION
};

// [D_08935498] Bad Guy - Release Slingshot
struct Animation anim_bad_guy_release_slingshot[] = {
    /* 000 */ { ninja_reincarnate_cel083, 1 },
    /* 001 */ { ninja_reincarnate_cel085, 1 },
    /* 002 */ { ninja_reincarnate_cel084, 1 },
    /* 003 */ { ninja_reincarnate_cel086, 1 },
    /* 004 */ { ninja_reincarnate_cel085, 1 },
    /* 005 */ { ninja_reincarnate_cel084, 1 },
    /* 006 */ { ninja_reincarnate_cel086, 30 },
    /* End */ END_ANIMATION
};

// [D_089354d8] Tanaka - Swing Right
struct Animation anim_tanaka_swing_r[] = {
    /* 000 */ { ninja_reincarnate_cel023, 2 },
    /* 001 */ { ninja_reincarnate_cel025, 80 },
    /* End */ END_ANIMATION
};

// [D_089354f0] Tanaka - Swing Left
struct Animation anim_tanaka_swing_l[] = {
    /* 000 */ { ninja_reincarnate_cel029, 2 },
    /* 001 */ { ninja_reincarnate_cel031, 80 },
    /* End */ END_ANIMATION
};

// [D_08935508] Tanaka - Cut Right
struct Animation anim_tanaka_slice_r[] = {
    /* 000 */ { ninja_reincarnate_cel024, 2 },
    /* 001 */ { ninja_reincarnate_cel025, 80 },
    /* End */ END_ANIMATION
};

// [D_08935520] Tanaka - Cut Left
struct Animation anim_tanaka_slice_l[] = {
    /* 000 */ { ninja_reincarnate_cel030, 2 },
    /* 001 */ { ninja_reincarnate_cel031, 80 },
    /* End */ END_ANIMATION
};

// [D_08935538] Tanaka - Spin Right
struct Animation anim_tanaka_spin_r[] = {
    /* 000 */ { ninja_reincarnate_cel026, 4 },
    /* 001 */ { ninja_reincarnate_cel027, 4 },
    /* 002 */ { ninja_reincarnate_cel028, 4 },
    /* 003 */ { ninja_reincarnate_cel001, 8 },
    /* 004 */ { ninja_reincarnate_cel002, 20 },
    /* End */ END_ANIMATION
};

// [D_08935568] Tanaka - Spin Left
struct Animation anim_tanaka_spin_l[] = {
    /* 000 */ { ninja_reincarnate_cel033, 4 },
    /* 001 */ { ninja_reincarnate_cel034, 4 },
    /* 002 */ { ninja_reincarnate_cel035, 4 },
    /* 003 */ { ninja_reincarnate_cel036, 8 },
    /* 004 */ { ninja_reincarnate_cel036, 20 },
    /* End */ END_ANIMATION
};

// [D_08935598] Woman - Walk
struct Animation anim_girlfriend_walk[] = {
    /* 000 */ { ninja_reincarnate_cel013, 10 },
    /* 001 */ { ninja_reincarnate_cel014, 10 },
    /* 002 */ { ninja_reincarnate_cel013, 10 },
    /* 003 */ { ninja_reincarnate_cel015, 10 },
    /* End */ END_ANIMATION
};

// [D_089355c0] Tanaka - Appear
struct Animation anim_tanaka_appear[] = {
    /* 000 */ { ninja_reincarnate_cel102, 1 },
    /* 001 */ { ninja_reincarnate_cel103, 1 },
    /* 002 */ { ninja_reincarnate_cel104, 1 },
    /* 003 */ { ninja_reincarnate_cel002, 5 },
    /* 004 */ { ninja_reincarnate_cel001, 40 },
    /* End */ END_ANIMATION
};

// [D_089355f0] Tanaka - Raise Stick
struct Animation anim_tanaka_raise_stick[] = {
    /* 000 */ { ninja_reincarnate_cel019, 3 },
    /* 001 */ { ninja_reincarnate_cel020, 3 },
    /* 002 */ { ninja_reincarnate_cel021, 3 },
    /* 003 */ { ninja_reincarnate_cel022, 40 },
    /* End */ END_ANIMATION
};

// [D_08935618] Button Indicators
struct Animation anim_ninja2_button_indicators[] = {
    /* 000 */ { ninja_reincarnate_cel105, 4 },
    /* 001 */ { ninja_reincarnate_cel106, 4 },
    /* End */ END_ANIMATION
};

// [D_08935630] Rock Shrapnel
struct Animation anim_ninja2_rock_pieces[] = {
    /* 000 */ { ninja_reincarnate_cel107, 4 },
    /* 001 */ { ninja_reincarnate_cel108, 4 },
    /* End */ END_ANIMATION
};

// [D_08935648] Rock - Fired at Tanaka
struct Animation anim_ninja2_rock_to_tanaka[] = {
    /* 000 */ { ninja_reincarnate_cel040, 1 },
    /* 001 */ { ninja_reincarnate_cel048, 1 },
    /* 002 */ { ninja_reincarnate_cel000, 1 },
    /* End */ END_ANIMATION
};

// [D_08935668] Intro Cutscene Rock
struct Animation anim_ninja2_cutscene_rock[] = {
    /* 000 */ { ninja_reincarnate_cel109, 4 },
    /* End */ END_ANIMATION
};
