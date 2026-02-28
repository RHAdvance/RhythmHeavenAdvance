#include "engines/tram_and_pauline.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gTramPauline ((struct TramPaulineEngineData *)gCurrentEngineData)


/* TRAM & PAULINE */


#include "asm/engines/tram_and_pauline/asm_0803fc94.s"

#include "asm/engines/tram_and_pauline/asm_0803fca4.s"

#include "asm/engines/tram_and_pauline/asm_0803fce4.s"

#include "asm/engines/tram_and_pauline/asm_0803fd10.s"

#include "asm/engines/tram_and_pauline/asm_08040064.s"


void func_080400d0(u8 fox) {
    
    if (fox > 1) {
        fox -= 2;
        gTramPauline->foxes[fox].unk_5 = 3;
    } else {
        gTramPauline->foxes[fox].unk_5 = 2;
    }

    gTramPauline->foxes[fox].unk_F = 0;
    gTramPauline->foxes[fox].unk_7 = fox;

    sprite_set_anim(gSpriteHandler, gTramPauline->foxes[fox].sprite, 
        tram_pauline_anim_table[
            gTramPauline->version * 0x18
            + (gTramPauline->foxes[fox].unk_14 + 0xc)
        ],
        0, 0, 0, 0
    );
    
    if (fox == 0) {
        // Left for Tram
        play_sound_in_player(3, &s_tran_jump_se_left_seqData);
    }
    if (fox == 1) {
        // Right for Pauline
        play_sound_in_player(4, &s_tran_jump_se_right_seqData);
    }
    
}

#include "asm/engines/tram_and_pauline/asm_0804016c.s"

#include "asm/engines/tram_and_pauline/asm_08040314.s"

#include "asm/engines/tram_and_pauline/asm_08040434.s"

#include "asm/engines/tram_and_pauline/asm_080404c4.s"

#include "asm/engines/tram_and_pauline/asm_08040718.s"

#include "asm/engines/tram_and_pauline/asm_080409cc.s"

#include "asm/engines/tram_and_pauline/asm_08040a18.s"

#include "asm/engines/tram_and_pauline/asm_08040a1c.s"

#include "asm/engines/tram_and_pauline/asm_08040a20.s"

#include "asm/engines/tram_and_pauline/asm_08040a80.s"

#include "asm/engines/tram_and_pauline/asm_08040a84.s"

#include "asm/engines/tram_and_pauline/asm_08040b04.s"

#include "asm/engines/tram_and_pauline/asm_08040b14.s"

#include "asm/engines/tram_and_pauline/asm_08040b20.s"

#include "asm/engines/tram_and_pauline/asm_08040b24.s"

#include "asm/engines/tram_and_pauline/asm_08040b58.s"

#include "asm/engines/tram_and_pauline/asm_08040bd4.s"
