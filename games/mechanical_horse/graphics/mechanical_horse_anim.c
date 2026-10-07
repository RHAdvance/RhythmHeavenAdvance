#include "global.h"
#include "graphics.h"

#include "mechanical_horse_anim_cells.inc.c"

// [D_089303c0] Walk (Horse)
struct Animation anim_horse_walk[] = {
    /* 000 */ { mechanical_horse_cel005, 16 },
    /* 001 */ { mechanical_horse_cel002, 16 },
    /* 002 */ { mechanical_horse_cel003, 16 },
    /* 003 */ { mechanical_horse_cel004, 16 },
    /* End */ END_ANIMATION
};

// [D_089303e8] Walk (Jockey)
struct Animation anim_horse_walk_jockey[] = {
    /* 000 */ { mechanical_horse_cel010, 16 },
    /* 001 */ { mechanical_horse_cel011, 16 },
    /* 002 */ { mechanical_horse_cel010, 16 },
    /* 003 */ { mechanical_horse_cel011, 16 },
    /* End */ END_ANIMATION
};

// [D_08930410] Trot (Horse)
struct Animation anim_horse_trot[] = {
    /* 000 */ { mechanical_horse_cel007, 12 },
    /* 001 */ { mechanical_horse_cel008, 12 },
    /* 002 */ { mechanical_horse_cel009, 12 },
    /* 003 */ { mechanical_horse_cel006, 12 },
    /* End */ END_ANIMATION
};

// [D_08930438] Trot (Jockey)
struct Animation anim_horse_trot_jockey[] = {
    /* 000 */ { mechanical_horse_cel010, 12 },
    /* 001 */ { mechanical_horse_cel011, 12 },
    /* 002 */ { mechanical_horse_cel010, 12 },
    /* 003 */ { mechanical_horse_cel011, 12 },
    /* End */ END_ANIMATION
};

// [D_08930460] Canter (Horse)
struct Animation anim_horse_canter[] = {
    /* 000 */ { mechanical_horse_cel015, 8 },
    /* 001 */ { mechanical_horse_cel012, 8 },
    /* 002 */ { mechanical_horse_cel013, 8 },
    /* 003 */ { mechanical_horse_cel014, 8 },
    /* End */ END_ANIMATION
};

// [D_08930488] Canter (Jockey)
struct Animation anim_horse_canter_jockey[] = {
    /* 000 */ { mechanical_horse_cel019, 8 },
    /* 001 */ { mechanical_horse_cel016, 8 },
    /* 002 */ { mechanical_horse_cel017, 8 },
    /* 003 */ { mechanical_horse_cel018, 8 },
    /* End */ END_ANIMATION
};

// [D_089304b0] Gallop (Horse)
struct Animation anim_horse_gallop[] = {
    /* 000 */ { mechanical_horse_cel021, 6 },
    /* 001 */ { mechanical_horse_cel022, 6 },
    /* 002 */ { mechanical_horse_cel023, 6 },
    /* 003 */ { mechanical_horse_cel024, 6 },
    /* 004 */ { mechanical_horse_cel025, 6 },
    /* End */ END_ANIMATION
};

// [D_089304e0] Gallop (Jockey)
struct Animation anim_horse_gallop_jockey[] = {
    /* 000 */ { mechanical_horse_cel019, 6 },
    /* 001 */ { mechanical_horse_cel016, 6 },
    /* 002 */ { mechanical_horse_cel017, 6 },
    /* 003 */ { mechanical_horse_cel017, 6 },
    /* 004 */ { mechanical_horse_cel018, 6 },
    /* End */ END_ANIMATION
};

// [D_08930510] Blank
struct Animation anim_mechanical_horse_blank1[] = {
    /* 000 */ { mechanical_horse_cel000, 12 },
    /* End */ END_ANIMATION
};

// [D_08930520] Blank
struct Animation anim_mechanical_horse_blank2[] = {
    /* 000 */ { mechanical_horse_cel000, 12 },
    /* End */ END_ANIMATION
};

// [D_08930530] Blank
struct Animation anim_mechanical_horse_blank3[] = {
    /* 000 */ { mechanical_horse_cel000, 2 },
    /* End */ END_ANIMATION
};

// [D_08930540] Blank
struct Animation anim_mechanical_horse_blank4[] = {
    /* 000 */ { mechanical_horse_cel000, 12 },
    /* End */ END_ANIMATION
};

// [D_08930550] Indicator - "パッ" ("pa[k]")
struct Animation anim_horse_text_pak[] = {
    /* 000 */ { mechanical_horse_cel026, 4 },
    /* 001 */ { mechanical_horse_cel027, 4 },
    /* End */ END_ANIMATION
};

// [D_08930568] Indicator - "カ" ("ka")
struct Animation anim_horse_text_ka[] = {
    /* 000 */ { mechanical_horse_cel028, 4 },
    /* 001 */ { mechanical_horse_cel029, 4 },
    /* End */ END_ANIMATION
};

// [D_08930580] Indicator - "ラッ" ("ra[p]")
struct Animation anim_horse_text_rap[] = {
    /* 000 */ { mechanical_horse_cel032, 4 },
    /* 001 */ { mechanical_horse_cel033, 4 },
    /* End */ END_ANIMATION
};

// [D_08930598] Indicator - "トッ" ("to[t]")
struct Animation anim_horse_text_tot[] = {
    /* 000 */ { mechanical_horse_cel034, 4 },
    /* 001 */ { mechanical_horse_cel035, 4 },
    /* End */ END_ANIMATION
};

// [D_089305b0] Indicator - "ドッ" ("do[d]")
struct Animation anim_horse_text_dod[] = {
    /* 000 */ { mechanical_horse_cel038, 4 },
    /* 001 */ { mechanical_horse_cel039, 4 },
    /* End */ END_ANIMATION
};

// [D_089305c8] Blank
struct Animation anim_horse_text_blank[] = {
    /* 000 */ { mechanical_horse_cel000, 1 },
    /* End */ END_ANIMATION
};

// [D_089305d8] Indicator - "パ" ("pa")
struct Animation anim_horse_text_pa[] = {
    /* 000 */ { mechanical_horse_cel030, 4 },
    /* 001 */ { mechanical_horse_cel031, 4 },
    /* End */ END_ANIMATION
};

// [D_089305f0] Horse Standing Still
struct Animation anim_horse_still[] = {
    /* 000 */ { mechanical_horse_cel002, 4 },
    /* End */ END_ANIMATION
};

// [D_08930600] Indicator - "ド" ("do")
struct Animation anim_horse_text_do[] = {
    /* 000 */ { mechanical_horse_cel036, 4 },
    /* 001 */ { mechanical_horse_cel037, 4 },
    /* End */ END_ANIMATION
};

// [D_08930550] Indicator - "ta"
struct Animation anim_horse_text_ta[] = {
    /* 000 */ { mechanical_horse_cel043, 4 },
    /* 001 */ { mechanical_horse_cel044, 4 },
    /* End */ END_ANIMATION
};

// [D_08930618] Tachometer Hand
struct Animation anim_horse_tachometer_hand[] = {
    /* 000 */ { mechanical_horse_cel040, 4 },
    /* End */ END_ANIMATION
};

// [D_08930628] Speedometer Hand
struct Animation anim_horse_speedometer_hand[] = {
    /* 000 */ { mechanical_horse_cel040, 4 },
    /* End */ END_ANIMATION
};

// [D_08930638] Tachometer High-Speed Light
struct Animation anim_horse_high_speed_light[] = {
    /* 000 */ { mechanical_horse_cel042, 4 },
    /* 001 */ { mechanical_horse_cel041, 8 },
    /* End */ END_ANIMATION
};
