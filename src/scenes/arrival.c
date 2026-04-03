#include "global.h"
#include "arrival.h"
#include "graphics/arrival/arrival_graphics.h"
#include "reading.h"


/* READING NOTIFICATION SCENE */


// Init. Static Variables
void arrival_scene_init_memory(void) {
}


// Graphics Init. 3
void arrival_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), arrival_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void arrival_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), arrival_gfx_table, 0x3000);
    run_func_after_task(task, arrival_scene_init_gfx3, 0);
}


// Graphics Init. 1
void arrival_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), arrival_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void arrival_scene_start(void *sVar, s32 dArg) {
    struct TextPrinter *printer;
    const char *title = arrival_default_title;
    char *message = mem_heap_alloc_id(get_current_mem_id(), 0x100);
    struct Scene *source;

    source = (struct Scene *)get_current_scene_trans_var();

    if (source != NULL) {
        struct ReadingMaterial *material = &reading_material_table[get_scene_trans_var(source)];

        if (material != NULL) {
            title = material->title;
        }
    }

    func_08007324(FALSE);
    func_080073f0();
    arrival_scene_init_gfx1();

    gArrival->dialogOptions = sprite_create(gSpriteHandler, anim_arrival_option1, 0, 120, 144, 0x800, 1, 0, 0x8000);
    gArrival->selectedOption = 0;

    printer = text_printer_create_new(get_current_mem_id(), 1, 240, 32);
    text_printer_set_x_y(printer, 24, 48);
    text_printer_set_string(printer, "        Notification from the Rhythm Archives:"); // "Notification from the Rhythm Reference Room"
    text_printer_update(printer);
    text_printer_update(printer);

    printer = text_printer_create_new(get_current_mem_id(), 1, 240, 30);
    text_printer_set_x_y(printer, 24, 96);
    text_printer_set_string(printer, "　　　　　　　　　　　　　　　　　　　　        has been received!"); // "You have received [_______]."
    text_printer_update(printer);
    text_printer_update(printer);

    memcpy(message, "\"", 5);
    strcat(message, title);
    strcat(message, "\"");

    printer = text_printer_create_new(get_current_mem_id(), 1, 240, 28);
    text_printer_set_x_y(printer, 0, 72);
    text_printer_center_by_content(printer, TRUE);
    text_printer_set_string(printer, message);
    text_printer_update(printer);
    text_printer_update(printer);

    gArrival->inputsEnabled = FALSE;
}


// Scene Update (Paused)
void arrival_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void arrival_scene_update(void *sVar, s32 dArg) {
    s8 option;

    if (!arrival_scene_inputs_enabled()) {
        return;
    }

    option = gArrival->selectedOption;

    if (D_03004afc & DPAD_LEFT) {
        option--;
    }

    if (D_03004afc & DPAD_RIGHT) {
        option++;
    }

    option = clamp_int32(option, 0, 1);

    if (option != gArrival->selectedOption) {
        gArrival->selectedOption = option;
        sprite_set_anim(gSpriteHandler, gArrival->dialogOptions, arrival_option_anim[option], 0, 1, 0, 0);
    }

    if (D_03004afc & A_BUTTON) {
        if (gArrival->selectedOption == 0) {
            set_next_scene((struct Scene *)get_current_scene_trans_var());
        } else {
            dealloc_scene_trans((struct Scene *)get_current_scene_trans_var());
        }

        set_pause_beatscript_scene(FALSE);
        gArrival->inputsEnabled = FALSE;
    }
}


// Check if Scene Can Receive Inputs
u32 arrival_scene_inputs_enabled(void) {
    if (gArrival->inputsEnabled) {
        return TRUE;
    }

    return FALSE;
}


// Scene Stop
void arrival_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}


// Display Dialog Options (Script Function)
void arrival_scene_show_options(void) {
    sprite_set_visible(gSpriteHandler, gArrival->dialogOptions, TRUE);
}
