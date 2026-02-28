#include "engines/quiz_show.h"
#include "games/quiz_show/graphics/quiz_show_graphics.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gQuizShow ((struct QuizShowEngineData *)gCurrentEngineData)


/* QUIZ SHOW */


#include "asm/engines/quiz_show/asm_0803709c.s"

void func_08037178(void) {
    u32 i;
    
    // Endless Score and High Score Text And Numbers
    if (gQuizShow->unk0 != 1) return;

    gQuizShow->unk4a = 0;

    gQuizShow->unk4c = D_030046a8->data.unk294[3];

    sprite_create(gSpriteHandler, anim_quiz_show_current_score_label, 0, 0xba, 4, 0x800, 0, 0, 0);
    sprite_create(gSpriteHandler, anim_quiz_show_high_score_label, 0, 0x3a, 4, 0x800, 0, 0, 0);

    for (i = 0; i < 2; i++) {
        gQuizShow->curScoreSprites[i] = sprite_create(gSpriteHandler, anim_quiz_show_score_num, 0, 0xC0 - (i*8), 4, 0x800, 0, 0x7f, 0);
    }

    
    for (i = 0; i < 2; i++) {
        gQuizShow->highScoreSprites[i] = sprite_create(gSpriteHandler, anim_quiz_show_score_num, 0, 0x27 - (i*8), 4, 0x800, 0, 0x7f, 0);
    }
    
    func_0803709c();
}

#include "asm/engines/quiz_show/asm_08037280.s"

#include "asm/engines/quiz_show/asm_080372c0.s"

#include "asm/engines/quiz_show/asm_080372e8.s"

#include "asm/engines/quiz_show/asm_08037378.s"

#include "asm/engines/quiz_show/asm_080373ac.s"

#include "asm/engines/quiz_show/asm_080373dc.s"

#include "asm/engines/quiz_show/asm_080373f4.s"

#include "asm/engines/quiz_show/asm_08037404.s"

#include "asm/engines/quiz_show/asm_08037434.s"

#include "asm/engines/quiz_show/asm_08037460.s"

#include "asm/engines/quiz_show/asm_08037858.s"

#include "asm/engines/quiz_show/asm_0803785c.s"

#include "asm/engines/quiz_show/asm_080378d8.s"

#include "asm/engines/quiz_show/asm_08037a64.s"

#include "asm/engines/quiz_show/asm_08037a78.s"

#include "asm/engines/quiz_show/asm_08037be0.s"

#include "asm/engines/quiz_show/asm_08037bf4.s"

#include "asm/engines/quiz_show/asm_08037cb8.s"

#include "asm/engines/quiz_show/asm_08037cd0.s"

#include "asm/engines/quiz_show/asm_08037cf4.s"

#include "asm/engines/quiz_show/asm_08037d00.s"

#include "asm/engines/quiz_show/asm_08037d0c.s"

#include "asm/engines/quiz_show/asm_08037d1c.s"

#include "asm/engines/quiz_show/asm_08037d2c.s"

#include "asm/engines/quiz_show/asm_08037d6c.s"

#include "asm/engines/quiz_show/asm_08037d90.s"

#include "asm/engines/quiz_show/asm_08037dc8.s"

#include "asm/engines/quiz_show/asm_08037e24.s"

#include "asm/engines/quiz_show/asm_08037e4c.s"

#include "asm/engines/quiz_show/asm_08037e50.s"

#include "asm/engines/quiz_show/asm_08037e54.s"

#include "asm/engines/quiz_show/asm_08037e70.s"

#include "asm/engines/quiz_show/asm_08037e74.s"

#include "asm/engines/quiz_show/asm_08037e78.s"

#include "asm/engines/quiz_show/asm_08037e7c.s"

#include "asm/engines/quiz_show/asm_08037e80.s"

#include "asm/engines/quiz_show/asm_08037f58.s"

#include "asm/engines/quiz_show/asm_08037f5c.s"

#include "asm/engines/quiz_show/asm_08037f60.s"
