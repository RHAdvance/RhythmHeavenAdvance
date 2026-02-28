#include "engines/rat_race.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gRatRace ((struct RatRaceEngineData *)gCurrentEngineData)


/* RAT RACE */


#include "asm/engines/rat_race/asm_08039dfc.s"

#include "asm/engines/rat_race/asm_08039e0c.s"

#include "asm/engines/rat_race/asm_08039e3c.s"

#include "asm/engines/rat_race/asm_08039e68.s"

#include "asm/engines/rat_race/asm_0803a154.s"

#include "asm/engines/rat_race/asm_0803a158.s"

#include "asm/engines/rat_race/asm_0803a164.s"

#include "asm/engines/rat_race/asm_0803a198.s"

#include "asm/engines/rat_race/asm_0803a1d4.s"

#include "asm/engines/rat_race/asm_0803a1e4.s"

#include "asm/engines/rat_race/asm_0803a1f8.s"

#include "asm/engines/rat_race/asm_0803a204.s"

#include "asm/engines/rat_race/asm_0803a230.s"

#include "asm/engines/rat_race/asm_0803a2a8.s"

#include "asm/engines/rat_race/asm_0803a350.s"

#include "asm/engines/rat_race/asm_0803a3b8.s"

#include "asm/engines/rat_race/asm_0803a3c4.s"

#include "asm/engines/rat_race/asm_0803a41c.s"

#include "asm/engines/rat_race/asm_0803a434.s"

#include "asm/engines/rat_race/asm_0803a458.s"

#include "asm/engines/rat_race/asm_0803a47c.s"

#include "asm/engines/rat_race/asm_0803a490.s"

#include "asm/engines/rat_race/asm_0803a4a4.s"

#include "asm/engines/rat_race/asm_0803a4a8.s"

#include "asm/engines/rat_race/asm_0803a4f8.s"

#include "asm/engines/rat_race/asm_0803a564.s"

#include "asm/engines/rat_race/asm_0803a5a4.s"

#include "asm/engines/rat_race/asm_0803a5bc.s"

#include "asm/engines/rat_race/asm_0803a5c0.s"

#include "asm/engines/rat_race/asm_0803a5dc.s"

#include "asm/engines/rat_race/asm_0803a5e0.s"

#include "asm/engines/rat_race/asm_0803a610.s"

#include "asm/engines/rat_race/asm_0803a640.s"

#include "asm/engines/rat_race/asm_0803a644.s"

#include "asm/engines/rat_race/asm_0803a648.s"

#include "asm/engines/rat_race/asm_0803a64c.s"

#include "asm/engines/rat_race/asm_0803a650.s"

#include "asm/engines/rat_race/asm_0803a654.s"

#include "asm/engines/rat_race/asm_0803a678.s"

void func_0803a798(u32 param) {
    gRatRace->unk80 = 0;
    gRatRace->unk80 = 0;
    gRatRace->unk7C = param;

    if (param > 6) return;

    // another state machine mwehehehe
    switch (param) {
        case 0:
            gRatRace->unk84 = 0x5000;
            sprite_set_visible(gSpriteHandler, gRatRace->cat_eyelids_sprite, 0);
            sprite_set_anim_cel(gSpriteHandler, gRatRace->cat_eyelids_sprite, 0);
            sprite_set_visible(gSpriteHandler, gRatRace->cat_paw_sprite, 0);
            sprite_set_visible(gSpriteHandler, gRatRace->cat_paw2_sprite, 0);
        break;
        case 1: 
            play_sound(&s_rat_paw_seqData);
            sprite_set_anim_cel(gSpriteHandler, gRatRace->cat_paw_sprite, 0);
            sprite_set_playback(gSpriteHandler, gRatRace->cat_paw_sprite, 1, 0x7f, 0);
            sprite_set_visible(gSpriteHandler, gRatRace->cat_paw_sprite, 1);
        break;
        case 2:
            play_sound(&s_rat_cat_seqData);
            sprite_set_anim_cel(gSpriteHandler, gRatRace->cat_paw2_sprite, 0);
            sprite_set_playback(gSpriteHandler, gRatRace->cat_paw2_sprite, 1, 0x7f, 0);
            sprite_set_visible(gSpriteHandler, gRatRace->cat_paw2_sprite, 1);
        break;
        case 4:
            gRatRace->unk84 = 0;
        break;
        case 5:
            sprite_set_visible(gSpriteHandler, gRatRace->cat_eyelids_sprite, 1);
        break;
        case 3:
        case 6:
            // do nothing
        break;
    }
}

#include "asm/engines/rat_race/asm_0803a8e4.s"

#include "asm/engines/rat_race/asm_0803aa58.s"

#include "asm/engines/rat_race/asm_0803aa9c.s"

#include "asm/engines/rat_race/asm_0803aba4.s"

#include "asm/engines/rat_race/asm_0803ac98.s"

#include "asm/engines/rat_race/asm_0803ad50.s"

#include "asm/engines/rat_race/asm_0803ad60.s"

#include "asm/engines/rat_race/asm_0803aef4.s"

#include "asm/engines/rat_race/asm_0803b034.s"

#include "asm/engines/rat_race/asm_0803b1ac.s"

#include "asm/engines/rat_race/asm_0803b1e8.s"

#include "asm/engines/rat_race/asm_0803b230.s"

#include "asm/engines/rat_race/asm_0803b258.s"

#include "asm/engines/rat_race/asm_0803b37c.s"

#include "asm/engines/rat_race/asm_0803b924.s"

#include "asm/engines/rat_race/asm_0803b9fc.s"

#include "asm/engines/rat_race/asm_0803baa0.s"

#include "asm/engines/rat_race/asm_0803baf8.s"

#include "asm/engines/rat_race/asm_0803bb2c.s"

#include "asm/engines/rat_race/asm_0803bbd8.s"

#include "asm/engines/rat_race/asm_0803bc08.s"

#include "asm/engines/rat_race/asm_0803bc40.s"

#include "asm/engines/rat_race/asm_0803bc98.s"

#include "asm/engines/rat_race/asm_0803bd0c.s"

#include "asm/engines/rat_race/asm_0803bd58.s"
