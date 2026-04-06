#include "global.h"
#include "results.h"
#include "graphics/results/results_graphics.h"
#include "src/code_080092cc.h"


/* RESULTS SCENE 3 (SCORE-TYPE) */


static s32 D_0300132c; // Unused
static u16 *sGradeThresholds;
static const char **sGradeComments;


// Init. Static Variables
void score_results_scene_init_memory() {
    sGradeThresholds = NULL;
    sGradeComments = 0;
}


// Graphics Init. 4
void score_results_scene_init_gfx4(void) {
    D_03004b10.objPalette[15][1] = 0;
    set_pause_beatscript_scene(FALSE);
}


// Graphics Init. 3
void score_results_scene_init_gfx3(void) {
    u32 data;

    func_0800c604(0);
    data = start_new_texture_loader(get_current_mem_id(), score_results_buffered_textures);
    run_func_after_task(data, score_results_scene_init_gfx4, 0);
}


// Graphics Init. 2
void score_results_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), score_results_gfx_table, 0x3000);
    run_func_after_task(task, score_results_scene_init_gfx3, 0);
}


// Graphics Init. 1
void score_results_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), score_results_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
}


// Scene Start
void score_results_scene_start(void *sVar, s32 dArg) {
    const char **comments;
    u16 *thresholds;
    struct Animation *textAnim;
    s16 textSprite;
    u32 score, n, result;

    func_08007324(FALSE);
    func_080073f0();
    gResults->bgFont = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    dma3_fill(0, OBJ_TILESET_BASE(0x4000), 0x4000, 0x20, 0x200);
    gResults->objFont = scene_create_obj_font_printer(0x300, 4);
    score_results_scene_init_gfx1();

    score = results_calculate_final_score();
    sprite_create(gSpriteHandler, anim_score_results_dec_num, (score % 10), 196, 114, 0, 0, 0, 0);

    n = score / 10;
    sprite_create(gSpriteHandler, anim_score_results_num, (n % 10), 152, 80, 0, 0, 0, 0);

    n /= 10;
    if (n != 0) {
        sprite_create(gSpriteHandler, anim_score_results_num, (n % 10), 96, 80, 0, 0, 0, 0);
    }

    n /= 10;
    if (n != 0) {
        sprite_create(gSpriteHandler, anim_score_results_num, (n % 10), 40, 80, 0, 0, 0, 0);
    }

    sprite_create(gSpriteHandler, anim_score_results_points_label, 0, 200, 136, 0, 0, 0, 0);

    thresholds = (sGradeThresholds != NULL) ? sGradeThresholds : score_results_default_thresholds;
    comments = (sGradeComments != NULL) ? sGradeComments : score_results_default_comments;

    for (result = SCORE_RESULT_BEST;
         result < SCORE_RESULT_FAIL && score < thresholds[result];
         result++);
    gResults->scoreGrade = result;

    textAnim = text_printer_get_unformatted_line_anim(get_current_mem_id(), 0, 16, TEXT_PRINTER_FONT_SMALL, comments[result], TEXT_ANCHOR_BOTTOM_CENTER, 0, 0x100);
    textSprite = sprite_create(gSpriteHandler, textAnim, 0, 120, 152, 0, 0, 0, 0);
    sprite_set_base_palette(gSpriteHandler, textSprite, 15);

    gResults->inputsEnabled = FALSE;
}


// Import Score Thresholds (Script Event)
void score_results_set_grade_thresholds(u16 *thresholds) {
    sGradeThresholds = thresholds;
}


// Import Text? (Script Event)
void score_results_set_grade_comments(const char **comments) {
    sGradeComments = comments;
}


// Scene Update (Paused)
void score_results_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void score_results_scene_update(void *sVar, s32 dArg) {
    if (results_scene_inputs_enabled()) {
        if (D_03004afc & A_BUTTON) {
            set_pause_beatscript_scene(FALSE);
            gResults->inputsEnabled = FALSE;
            play_sound_w_pitch_volume(&s_menu_se20_seqData, INT_TO_FIXED(0.5), INT_TO_FIXED(0.0));
            rumble_play_menu_confirm();
        }
    }
}


// Scene Stop
void score_results_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}


// Reveal Score (Script Event)
void score_results_reveal(void) {
    play_sound(score_results_reveal_sfx[gResults->scoreGrade]);
}
