#include "global.h"
#include "epilogue.h"
#include "graphics/epilogues/epilogues_graphics.h"

#include "levels.h"
#include "src/code_080092cc.h"
#include "src/scenes/game_select.h"
#include "src/scenes/results.h"
#include "src/scenes/studio.h"


/* EPILOGUE SCENE */


// Init. Static Variables
void epilogue_scene_init_memory(void) {
}


// Graphics Init. 3
void epilogue_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    D_03004b10.objPalette[4][1] = 0x7FFF;
    play_sound(gEpilogue->jingle);
    task = start_new_texture_loader(get_current_mem_id(), epilogue_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void epilogue_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), gEpilogue->gfxTable, 0x3000);
    run_func_after_task(task, epilogue_scene_init_gfx3, 0);
}


// Graphics Init. 1
void epilogue_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), epilogue_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
}


// Scene Start
void epilogue_scene_start(void *sVar, s32 dArg) {
    struct LevelData *levelData;
    const char *text;
    u32 rank;

    levelData = (struct LevelData *)get_current_scene_trans_var();
    gEpilogue->gfxTable = NULL;
    text = NULL;

    if ((levelData != NULL) && (levelData->epilogueGfx != NULL)) {
        if (levelData == &level_data_table[LEVEL_LIVE_MENU]) {
            rank = drum_live_get_result_rank();
        } else {
            switch (D_030046a8->data.recentLevelState) {
                case LEVEL_STATE_CLEARED:
                    rank = RESULTS_RANK_OK;
                    break;
                case LEVEL_STATE_HAS_MEDAL:
                    rank = RESULTS_RANK_SUPERB;
                    break;
                default:
                    rank = RESULTS_RANK_TRY_AGAIN;
                    break;
            }
        }

        gEpilogue->gfxTable = levelData->epilogueGfx[rank];
        if (levelData->epilogueText != NULL) {
            text = levelData->epilogueText[rank];
        }
        gEpilogue->jingle = epilogue_jingles[rank];
    }

    if (gEpilogue->gfxTable == NULL) {
        func_0801d95c(epilogue_end_script);
        return;
    }

    func_08007324(FALSE);
    func_080073f0();
    gEpilogue->bgFont = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    dma3_fill(0, OBJ_TILESET_BASE(0x7800), 0x800, 0x20, 0x200);

    if (text != NULL) {
        struct Animation *anim;
        s16 sprite;

        anim = text_printer_get_unformatted_line_anim(get_current_mem_id(), 0, 30, 0, text, 1, 0, 0x100);
        sprite = sprite_create(gSpriteHandler, anim, 0, 120, 140, 0, 0, 0, 0);
        sprite_set_base_palette(gSpriteHandler, sprite, 4);
    }

    gEpilogue->objFont = scene_create_obj_font_printer(0x300, 4);
    import_all_scene_objects(gSpriteHandler, gEpilogue->objFont, epilogue_scene_objects, D_0300558c);
    epilogue_scene_init_gfx1();
    gEpilogue->inputsEnabled = FALSE;
}


// Scene Update (Paused)
void epilogue_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void epilogue_scene_update(void *sVar, s32 dArg) {
    if (epilogue_scene_inputs_enabled()) {
        if (D_03004afc & A_BUTTON) {
            set_pause_beatscript_scene(FALSE);
            play_sound_w_pitch_volume(&s_menu_se20_seqData, INT_TO_FIXED(0.5), 0);
            gEpilogue->inputsEnabled = FALSE;
            rumble_play_menu_confirm();
        }
    }
}


// Check if Scene Can Receive Inputs
u32 epilogue_scene_inputs_enabled(void) {
    if (gEpilogue->inputsEnabled) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Scene Stop
void epilogue_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
    stop_all_soundplayers();
}
