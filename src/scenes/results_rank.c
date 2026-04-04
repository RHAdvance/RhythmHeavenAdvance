#include "global.h"
#include "results.h"
#include "graphics/results/results_graphics.h"
#include "src/code_080092cc.h"


/* RESULTS SCENE 2 (RANK-TYPE) */


#define COMMENT_TILESET_BASE OBJ_TILESET_BASE(0x4000)
#define RANK_HEADER_PALETTE 4
#define RANK_HEADER_Y 24
#define RANK_HEADER_ICON_X 45
#define RANK_HEADER_BOX_X 24
#define RANK_RESULT_ICON_X 180
#define RANK_RESULT_ICON_Y 140
#define RANK_RESULT_ICON_BUT_X 88
#define RANK_RESULT_ICON_BUT_Y 140


// Init. Static Variables
void rank_results_scene_init_memory(void) {
}


// Graphics Init. 3
void rank_results_scene_init_gfx3(void) {
    u32 data;

    func_0800c604(0);
    data = start_new_texture_loader(get_current_mem_id(), rank_results_buffered_textures);
    run_func_after_task(data, set_pause_beatscript_scene, FALSE);
}


// Graphics Init. 2
void rank_results_scene_init_gfx2(void) {
    u32 data;

    func_0800c604(0);
    data = func_08002ee0(get_current_mem_id(), rank_results_gfx_table, 0x3000);
    run_func_after_task(data, rank_results_scene_init_gfx3, 0);
}


// Graphics Init. 1
void rank_results_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), rank_results_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
}


// Scene Start
void rank_results_scene_start(void *sVar, s32 dArg) {
    func_08007324(FALSE);
    func_080073f0();
    gResults->bgFont = create_new_bmp_font_bg(get_current_mem_id(), bitmap_font_warioware_body, 0, 0x340, 6);
    gResults->objFont = scene_create_obj_font_printer(0x300, 4);
    dma3_fill(0, COMMENT_TILESET_BASE, 0x4000, 0x20, 0x200);
    gResults->currentLine = 0;

    gResults->placeholderIcon = sprite_create(gSpriteHandler, anim_rank_results_header_placeholder, 0, RANK_HEADER_ICON_X, RANK_HEADER_Y, 0x800, 0, 0, 0x8000);
    gResults->resultIcon = sprite_create(gSpriteHandler, anim_rank_results_icon, 0, RANK_RESULT_ICON_X, RANK_RESULT_ICON_Y, 0x800, 0, 0, 0x8000);
    rank_results_scene_init_gfx1();
    gMidiLFOMode = LFO_MODE_DISABLED;
    gResults->inputsEnabled = FALSE;
    gResults->medalObtained = FALSE;
    gResults->stillJustOK = FALSE;
}


// Scene Update (Paused)
void rank_results_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void rank_results_scene_update(void *sVar, s32 dArg) {
    if (!results_scene_inputs_enabled()) {
        return;
    }

    if (D_03004afc & A_BUTTON) {
        set_pause_beatscript_scene(FALSE);
        gResults->inputsEnabled = FALSE;
        play_sound_w_pitch_volume(&s_menu_se20_seqData, INT_TO_FIXED(0.5), 0);
        rumble_play_menu_confirm();
    }
}


// Scene Stop
void rank_results_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}


// Display Header Text (Script Event)
void rank_results_display_header(void) {
    struct Animation *anim;
    s32 sprite, width;

    if (score_handler->headerText == NULL) {
        sprite_set_visible(gSpriteHandler, gResults->placeholderIcon, TRUE);
        return;
    }

    anim = results_get_comment_anim(score_handler->headerText, TEXT_ANCHOR_BOTTOM_LEFT, 0);
    sprite = sprite_create(gSpriteHandler, anim, 0, RANK_HEADER_BOX_X, RANK_HEADER_Y, 0x800, 0, 0, 0);
    sprite_set_base_palette(gSpriteHandler, sprite, RANK_HEADER_PALETTE);
    width = sprite_get_data(gSpriteHandler, sprite, 24);
    sprite_create(gSpriteHandler, anim_rank_results_header_box, 0, SCREEN_CENTER_X, RANK_HEADER_Y, 0x864, 0, 0, 0);
    sprite_create(gSpriteHandler, anim_rank_results_header_box_mask, 0, SCREEN_CENTER_X + width, RANK_HEADER_Y, 0x850, 0, 0, 0);
}


// Display Result Icon (Script Event)
void rank_results_display_rank(void) {
    sprite_set_visible(gSpriteHandler, gResults->resultIcon, TRUE);

    if (gResults->medalObtained) {
        sprite_create(gSpriteHandler, anim_rank_results_medal_get, 0, 180, 140, 0x700, 1, 0, 0);
    }

    if (gResults->stillJustOK) {
        sprite_create(gSpriteHandler, anim_rank_results_comment_append, 0, 180, 140, 0x700, 1, 0, 0);
    }

    play_sound_in_player(SFX_PLAYER_2, rank_results_sfx[gResults->finalResultLevel]);
}


// Play Music (Script Event)
void rank_results_play_bgm(void) {
    struct SongHeader *music = rank_results_bgm[gResults->finalResultLevel];

    scene_set_music(music);
    set_beatscript_tempo(get_music_base_tempo(music));
}


// Display Positive Reinforcement (Script Event)
void rank_results_append_encouragement(void) {
    u16 *commentSprites;
    u32 totalNegativeComments, totalComments;
    u32 i;

    commentSprites = gResults->commentSprites;
    totalNegativeComments = gResults->totalNegativeComments;
    totalComments = gResults->totalNegativeComments + gResults->totalPositiveComments;

    if ((gResults->finalResultLevel != RESULTS_RANK_TRY_AGAIN)
      || (gResults->totalPositiveComments == 0)
      || (gResults->singleCommentTryAgain)) {
        return;
    }

    for (i = 0; i < totalComments; i++) {
        s32 y = sprite_get_data(gSpriteHandler, commentSprites[i], 5);

        sprite_set_y(gSpriteHandler, commentSprites[i], y - 10);
    }

    for (i = totalNegativeComments; i < totalComments; i++) {
        sprite_set_visible(gSpriteHandler, commentSprites[i], TRUE);
    }

    play_sound(&s_f_result_mes_add_seqData);
    sprite_create(gSpriteHandler, anim_rank_results_supportive_bubble, 0, RANK_RESULT_ICON_BUT_X, RANK_RESULT_ICON_BUT_Y, 0, 0, 0, 0);
}
