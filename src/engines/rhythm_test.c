#include "engines/rhythm_test.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gRhythmTest ((struct RhythmTestEngineData *)gCurrentEngineData)


/* RHYTHM TEST */


#include "asm/engines/rhythm_test/asm_08033960.s"

#include "asm/engines/rhythm_test/asm_0803397c.s"

#include "asm/engines/rhythm_test/asm_080339bc.s"

#include "asm/engines/rhythm_test/asm_08033b24.s"

#include "asm/engines/rhythm_test/asm_08033b34.s"

#include "asm/engines/rhythm_test/asm_08033b48.s"

#include "asm/engines/rhythm_test/asm_08033b9c.s"

#include "asm/engines/rhythm_test/asm_08033c2c.s"

#include "asm/engines/rhythm_test/asm_08033c50.s"

#include "asm/engines/rhythm_test/asm_08033c80.s"

// Engine Start
void rhythm_test_engine_start(u32 version) {
    struct TextPrinter *printer;

    gRhythmTest->version = version;
    
    rhythm_test_init_gfx1();
    scene_show_obj_layer();

    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 0x1e, 1);
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0x18, 0, 0x1c, 0x8002);
    scene_set_bg_layer_display(BG_LAYER_3, TRUE, 0, 0, 0, 0x1f, 3);

    printer = text_printer_create_new(get_current_mem_id(), 2, 0xf0, 0x1e);
    text_printer_set_x_y(printer, 0, 16);
    text_printer_center_by_content(printer, TRUE);
    gameplay_set_text_printer(printer);
    gameplay_set_text_z(0x48c8);

    gRhythmTest->spriteId4 = sprite_create(gSpriteHandler, anim_rhythm_test_button, 0, 0x78, 0x64, 0x90 << 7, 1, 0x7f, 0);
    gRhythmTest->spriteId6 = sprite_create(gSpriteHandler, anim_rhythm_test_monitor_note, 0x7f, 0x78, 0x3c, 0x4864, 1, 0x7f, 0x80 << 8);
    gRhythmTest->unk8 = 0;
    gRhythmTest->spriteIdA = sprite_create(gSpriteHandler, anim_rhythm_test_monitor_count_num, 0xa, 0x78, 0x3c, 0x4800, 0, 0x7f, 0x80 << 8);
    
    func_0803397c();
    init_drumtech(&gRhythmTest->drumTech);
    gameplay_set_input_buttons(1, 0);
}

#include "asm/engines/rhythm_test/asm_08033dfc.s"

#include "asm/engines/rhythm_test/asm_08033e00.s"

#include "asm/engines/rhythm_test/asm_08033f08.s"

#include "asm/engines/rhythm_test/asm_08033f28.s"

#include "asm/engines/rhythm_test/asm_08033f80.s"

#include "asm/engines/rhythm_test/asm_08034004.s"

#include "asm/engines/rhythm_test/asm_08034014.s"

#include "asm/engines/rhythm_test/asm_08034018.s"

#include "asm/engines/rhythm_test/asm_0803401c.s"

#include "asm/engines/rhythm_test/asm_08034038.s"

#include "asm/engines/rhythm_test/asm_0803403c.s"

#include "asm/engines/rhythm_test/asm_08034068.s"

#include "asm/engines/rhythm_test/asm_08034094.s"

#include "asm/engines/rhythm_test/asm_080340a4.s"

#include "asm/engines/rhythm_test/asm_080340b8.s"

#include "asm/engines/rhythm_test/asm_080340cc.s"

#include "asm/engines/rhythm_test/asm_080340f8.s"

#include "asm/engines/rhythm_test/asm_080340fc.s"
