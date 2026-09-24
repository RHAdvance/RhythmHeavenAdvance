#include "engines/ninja_bodyguard.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gNinjaBodyguard ((struct NinjaBodyguardEngineData *)gCurrentEngineData)


/* NINJA BODYGUARD */


#include "asm/engines/ninja_bodyguard/asm_0803bd88.s"

#include "asm/engines/ninja_bodyguard/asm_0803bda8.s"

#include "asm/engines/ninja_bodyguard/asm_0803be04.s"

#include "asm/engines/ninja_bodyguard/asm_0803be44.s"

#include "asm/engines/ninja_bodyguard/asm_0803be88.s"

#include "asm/engines/ninja_bodyguard/asm_0803bec4.s"

#include "asm/engines/ninja_bodyguard/asm_0803bf14.s"

#include "asm/engines/ninja_bodyguard/asm_0803bf74.s"

#include "asm/engines/ninja_bodyguard/asm_0803c034.s"

#include "asm/engines/ninja_bodyguard/asm_0803c08c.s"

#include "asm/engines/ninja_bodyguard/asm_0803c190.s"

#include "asm/engines/ninja_bodyguard/asm_0803c20c.s"

#include "asm/engines/ninja_bodyguard/asm_0803c260.s"

#include "asm/engines/ninja_bodyguard/asm_0803c28c.s"

#include "asm/engines/ninja_bodyguard/asm_0803c2b8.s"

#include "asm/engines/ninja_bodyguard/asm_0803c2f4.s"

#include "asm/engines/ninja_bodyguard/asm_0803c3c4.s"

#include "asm/engines/ninja_bodyguard/asm_0803c400.s"

#include "asm/engines/ninja_bodyguard/asm_0803c43c.s"

#include "asm/engines/ninja_bodyguard/asm_0803c52c.s"

#include "asm/engines/ninja_bodyguard/asm_0803c5c0.s"

#include "asm/engines/ninja_bodyguard/asm_0803c5cc.s"

#include "asm/engines/ninja_bodyguard/asm_0803c5f8.s"

#include "asm/engines/ninja_bodyguard/asm_0803c638.s"

#include "asm/engines/ninja_bodyguard/asm_0803c6fc.s"

#include "asm/engines/ninja_bodyguard/asm_0803c710.s"

#include "asm/engines/ninja_bodyguard/asm_0803c834.s"

#include "asm/engines/ninja_bodyguard/asm_0803c8c4.s"

#include "asm/engines/ninja_bodyguard/asm_0803c960.s"

#include "asm/engines/ninja_bodyguard/asm_0803c964.s"

#include "asm/engines/ninja_bodyguard/asm_0803c9f4.s"

#include "asm/engines/ninja_bodyguard/asm_0803c9f8.s"

#include "asm/engines/ninja_bodyguard/asm_0803cad0.s"

#include "asm/engines/ninja_bodyguard/asm_0803cb0c.s"

#include "asm/engines/ninja_bodyguard/asm_0803cb60.s"

#include "asm/engines/ninja_bodyguard/asm_0803cb7c.s"

#include "asm/engines/ninja_bodyguard/asm_0803cbbc.s"

#include "asm/engines/ninja_bodyguard/asm_0803cbe8.s"

#include "asm/engines/ninja_bodyguard/asm_0803ccb0.s"

#include "asm/engines/ninja_bodyguard/asm_0803ccb4.s"

#include "asm/engines/ninja_bodyguard/asm_0803cce0.s"

#include "asm/engines/ninja_bodyguard/asm_0803ccf4.s"

#include "asm/engines/ninja_bodyguard/asm_0803cd04.s"

#include "asm/engines/ninja_bodyguard/asm_0803cd08.s"

#include "asm/engines/ninja_bodyguard/asm_0803cd1c.s"

#include "asm/engines/ninja_bodyguard/asm_0803cd38.s"

#include "asm/engines/ninja_bodyguard/asm_0803cd3c.s"

#include "asm/engines/ninja_bodyguard/asm_0803ce24.s"

#include "asm/engines/ninja_bodyguard/asm_0803cf00.s"

#include "asm/engines/ninja_bodyguard/asm_0803cf60.s"

#include "asm/engines/ninja_bodyguard/asm_0803d010.s"

#include "asm/engines/ninja_bodyguard/asm_0803d014.s"


void func_0803ca8c() {
	sprite_set_anim(gSpriteHandler,
		gNinjaBodyguard->lordId,
		ninja_get_anim(NINJA_ANIM_LORD_WALK),
		0, 0, 0, 0
	);

	play_sound(
		CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_SFX) != 0 ?
		&s_f_ninja_v_huh_seqData : &s_f_ninja_v_nanu_seqData
	);
}
