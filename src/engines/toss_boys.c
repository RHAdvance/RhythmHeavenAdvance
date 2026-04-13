#include "engines/toss_boys.h"

// For readability.
#define gTossBoys ((struct TossBoysEngineData *)gCurrentEngineData)


/* TOSS BOYS */

void toss_boys_init_soshi_sprite() {
    if (gTossBoys->version == ENGINE_VER_TOSS_REMIX_5) {
        gTossBoys->soshiSprite = sprite_create(gSpriteHandler, anim_toss_remix_5_soshi_strum_pop, 0x7f, 116, 56, 0x4C00, 1, 0x7f, 0x8000);
    } else {
        gTossBoys->soshiSprite = -1;
    }
}
    
void toss_boys_show_soshi_sprite(void) {
    if(gTossBoys->soshiSprite >= 0){
        sprite_set_visible(gSpriteHandler, gTossBoys->soshiSprite, TRUE);
    }
}

void toss_boys_soshi_update(void) {
    if (gTossBoys->soshiSprite >= 0 && gTossBoys->soshiStrumTimer == 0){
        sprite_set_anim(gSpriteHandler, gTossBoys->soshiSprite, anim_toss_remix_5_soshi_strum_pop, 0, 1, 127, 0);
    }
}

void toss_boys_play_soshi_strum(void) {
    if(gTossBoys->soshiSprite >= 0){
        sprite_set_anim(gSpriteHandler, gTossBoys->soshiSprite, anim_toss_remix_5_soshi_strum_launch, 0, 1, 127, 0);
        gTossBoys->soshiStrumTimer = ticks_to_frames(0x3C);
    }
}

void toss_boys_update_soshi_timer(void) {
    if (gTossBoys->soshiSprite >= 0){
        if (gTossBoys->soshiStrumTimer != 0){
            gTossBoys->soshiStrumTimer--;
        }
    }
}

struct Animation* toss_boys_get_anim(u32 anim) {
    return toss_boys_anim_table[anim][gTossBoys->version];
}

void toss_boys_play_drum_note(u32 id) {
    if (gTossBoys->ballInFlightFlag != 0 && gTossBoys->recoveryTimer == 0 && gTossBoys->recoveryCompleteFlag == FALSE) {
        struct SoundPlayer* note = play_drumtech_note(id, 0x100, 0);

        s32 tempo = get_beatscript_tempo();
        u8_8 speed = FIXED_POINT_DIV(tempo, 120);

        set_soundplayer_speed(note, speed);
    }
}

void toss_boys_queue_drum_note(s16 id) {
    gTossBoys->queuedDrumNoteId = id;
}

void toss_boys_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

void toss_boys_init_gfx2(void) {
    s32 task;
    
    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), toss_boys_gfx_tables[gTossBoys->version], 0x2000);
    run_func_after_task(task, toss_boys_init_gfx3, 0);
}

void toss_boys_init_gfx1(void) {
    s32 task;
    
    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), toss_boys_buffered_textures);
    run_func_after_task(task, toss_boys_init_gfx2, 0);
}

void toss_boys_engine_start(u32 version) {
    u32 i;
    struct TextPrinter* tp;

    gTossBoys->version = version;
    toss_boys_init_gfx1();
    scene_show_obj_layer();

    scene_set_bg_layer_display(BG_LAYER_0, TRUE, 0, 0, 2, 28, 0x4000);
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 0, 30, BG_PRIORITY_HIGH);

    gTossBoys->playerSprite[TOSS_BOYS_PLAYER_RED] = sprite_create(gSpriteHandler, toss_boys_get_anim(TOSS_BOYS_ANIM_BEAT_RED), 0, 185, 115, 0x4810, 1, 0x7f, 0);
    gTossBoys->playerSprite[TOSS_BOYS_PLAYER_BLUE] = sprite_create(gSpriteHandler, toss_boys_get_anim(TOSS_BOYS_ANIM_BEAT_BLUE), 0, 161, 140, 0x4800, 1, 0x7f, 0);
    gTossBoys->playerSprite[TOSS_BOYS_PLAYER_YELLOW] = sprite_create(gSpriteHandler, toss_boys_get_anim(TOSS_BOYS_ANIM_BEAT_YELLOW), 0, 58, 124, 0x4800, 1, 0x7f, 0);

    for (i = 0; i < TOSS_BOYS_PLAYER_COUNT; i++) {
        gTossBoys->playerAnimCooldown[i] = 0;
        gTossBoys->playerReadyState[i] = 0;
        gTossBoys->playerBarelyTimer[i] = 0;
    }

    gTossBoys->dispenserSprite = sprite_create(gSpriteHandler, toss_boys_get_anim(TOSS_BOYS_ANIM_DISPENSER), 0x7f, 120, 110, 0x4900, 1, 0x7f, 0);
    gTossBoys->ballSprite = sprite_create(gSpriteHandler, toss_boys_get_anim(TOSS_BOYS_ANIM_BALL1), 0, 120, 120, 0x700, 0, 0, 0x8000);

    gTossBoys->ballAffineGroup = scene_affine_group_alloc();
    assign_sprite_affine_param(gTossBoys->ballSprite, gTossBoys->ballAffineGroup);
    func_080022d8(gTossBoys->ballAffineGroup);
    set_affine_scale_rotation(gTossBoys->ballAffineGroup, 0x100, 0);

    gTossBoys->ballMotionTaskId = -1;
    gTossBoys->affineRotation = 0;
    gTossBoys->affineRotationSpeed = 0;
    gTossBoys->affineScaleOffset = 0;
    gTossBoys->ballInFlightFlag = FALSE;
    gTossBoys->barelyActive = FALSE;
    gTossBoys->recoveryTimer = 0;
    gTossBoys->recoveryCompleteFlag = FALSE;

    gTossBoys->arrowSprite = sprite_create(gSpriteHandler, toss_boys_get_anim(TOSS_BOYS_ANIM_ARROW_RED), 0, 120, 80, 0x4f00, 1, 0, 0x8002);

    init_drumtech(&gTossBoys->drumTech);
    set_drumtech_bank(toss_boys_drumtech_bank);

    gTossBoys->queuedDrumNoteId = -1;
    gTossBoys->pitchOffset = 0;
    gTossBoys->enabledButtonsMask = (DPAD_ALL | A_BUTTON | B_BUTTON);
    gameplay_set_input_buttons(gTossBoys->enabledButtonsMask, 0);

    for (i = 0; i < TOSS_BOYS_PLAYER_COUNT; i++) {
        gTossBoys->playerButtonLockTimer[i] = 0;
    }

    tp = text_printer_create_new(get_current_mem_id(), 2, 240, 0x1e);

    if (gTossBoys->version == ENGINE_VER_TOSS_REMIX_5) {
        text_printer_set_x_y(tp, 0, 8);
        text_printer_set_layer(tp, 0x4c00);
        text_printer_center_by_content(tp, FALSE);
    } else {
        text_printer_set_x_y(tp, 0, 20);
        text_printer_set_layer(tp, 0x4c00);
        text_printer_set_alignment(tp, 2);
        text_printer_center_by_content(tp, TRUE);
    }

    text_printer_set_palette(tp, 0);
    text_printer_set_colors(tp, 0);
    text_printer_set_line_spacing(tp, 20);
    gameplay_set_text_printer(tp);

    D_03004b10.BLDMOD =  BLDMOD_BG0_SRC | (BLEND_MODE_ALPHA << 6) | BLDMOD_BG0_TGT | BLDMOD_BG1_TGT | BLDMOD_BG2_TGT | BLDMOD_BG3_TGT | BLDMOD_SPRITES_TGT | BLDMOD_BACKDROP_TGT;
    D_03004b10.COLEV = 0x1000;

    gTossBoys->colorEffectLevel = 0;
    toss_boys_init_soshi_sprite();
}

void toss_boys_engine_event_stub() {

}

void toss_boys_update_player_timers(void) {
    u32 i;

    for(i = 0; i < TOSS_BOYS_PLAYER_COUNT; i++){
        if(gTossBoys->playerAnimCooldown[i] != 0){
            gTossBoys->playerAnimCooldown[i]--;
        }

        if(gTossBoys->playerBarelyTimer[i] != 0){
            gTossBoys->playerBarelyTimer[i]--;
        }
    }
}

void toss_boys_lock_player_buttons(u32 index, u32 value) {
    if(gTossBoys->playerButtonLockTimer[index] <= value){
        gTossBoys->playerButtonLockTimer[index] = value;

        gTossBoys->enabledButtonsMask &= ~toss_boys_button_masks[index];

        gameplay_set_input_buttons(gTossBoys->enabledButtonsMask, 0);
    }
}


void toss_boys_update_button_locks(void) {
    u32 i;
    u8 state;
    struct Animation *anim;

    for (i = 0; i < TOSS_BOYS_PLAYER_COUNT; i++) {
        if (gTossBoys->playerButtonLockTimer[i] != 0) {
            gTossBoys->playerButtonLockTimer[i]--;
            if (gTossBoys->playerButtonLockTimer[i] != 0) continue;
            
            gTossBoys->enabledButtonsMask |= toss_boys_button_masks[i];
            gameplay_set_input_buttons(gTossBoys->enabledButtonsMask, 0);
            
            state = gTossBoys->playerReadyState[i];
            anim = toss_boys_action_anims[state][i];
            if (anim != NULL) {
                sprite_set_anim(gSpriteHandler, gTossBoys->playerSprite[i], anim, toss_boys_action_anim_playback[state][i], 1, 0x7F, 0);
            }
        }
    }
}

void toss_boys_update_ball_affine(void) {
    gTossBoys->affineScaleOffset = FIXED_POINT_MUL(gTossBoys->affineScaleOffset, 220);
    
    if (gTossBoys->barelyActive != FALSE) {
        s16 phase;
        s32 product;
        s32 delta = clamp_int32(gTossBoys->affineRotationSpeed, -24, 24);
        
        gTossBoys->affineRotation += delta;
        
        phase = D_08935fcc[gTossBoys->barelyOscPhase];
        product = FIXED_POINT_MUL(phase, 100);
        
        set_affine_stretch_rotation(gTossBoys->ballAffineGroup, 320 + product, 320 - product, gTossBoys->affineRotation);
        
        gTossBoys->barelyOscPhase += 24;
    } else {
        gTossBoys->affineRotation += gTossBoys->affineRotationSpeed;
        set_affine_scale_rotation(gTossBoys->ballAffineGroup, 256 + gTossBoys->affineScaleOffset, gTossBoys->affineRotation);
    }
}

void toss_boys_update_pitch_modulation(void) {
    s32 sign;
    s32 amplitude;
    s32 modulation;

    if (gTossBoys->pitchOffset < 0) {
        sign = -1;
    } else {
        sign = 1;
    }
        
    gTossBoys->pitchOffset = FIXED_TO_INT(sign * gTossBoys->pitchOffset * 245) * sign;
    amplitude = gTossBoys->pitchOffset >> 2;
    modulation = FIXED_TO_INT((amplitude * gSineTable[gTossBoys->pitchOscPhase & 0x7FF]));
    
    gTossBoys->pitchOscPhase += 256;

    set_soundplayer_pitch(get_soundplayer_from_id(5), gTossBoys->pitchOffset + modulation);
}

void toss_boys_pan_bg_to_target(u32 arg) {
    if(gTossBoys->ballInFlightFlag == FALSE){
        return;
    }

    D_03004b10.BG_OFS[0].x = (256 - toss_boys_bg_pan_targets[arg].x);
    D_03004b10.BG_OFS[0].y = (128 - toss_boys_bg_pan_targets[arg].y);

    scene_start_integer_interp(1, ticks_to_frames(0x10), &gTossBoys->colorEffectLevel, 0, 10);
    play_sound_w_pitch_volume(&s_ninja_wind_seqData, 0xA0, 0);
}

void toss_boys_clear_color_effect(void){
    gTossBoys->colorEffectLevel = 0;
}

void toss_boys_engine_update(void) {
    u16 blendLevel;

    toss_boys_update_button_locks();
    toss_boys_update_player_timers();
    toss_boys_update_ball_affine();
    update_drumtech();
    toss_boys_update_pitch_modulation();

    if (gTossBoys->recoveryTimer != 0) {
        gTossBoys->recoveryTimer--;

        if (gTossBoys->recoveryTimer == 0) {
            gTossBoys->recoveryCompleteFlag = 1;
        }
    }

    blendLevel = (gTossBoys->ballInFlightFlag != 0) ? gTossBoys->colorEffectLevel : 0;
    D_03004b10.COLEV = blendLevel | ((0x10 - blendLevel) << 8);

    toss_boys_update_soshi_timer();
}

void toss_boys_engine_stop(void) {
}

void toss_boys_reset_ball(void) {
    sprite_set_visible(gSpriteHandler, gTossBoys->ballSprite, FALSE);
    gTossBoys->targetIndex = TOSS_BOYS_PLAYER_DISPENSER;
}

void toss_boys_throw_ball(u32 param, s32 velocity, u32 amplitude, u32 throwSpeed)
{
    s32 duration;
    struct Vector2 *srcPosition;
    struct Vector2 *dstPosition;
    s32 task;
    s32 frame;
    s32 time;

    if (gTossBoys->ballInFlightFlag != 0) {
        return;
    }

    gTossBoys->ballInFlightFlag = TRUE;
    gTossBoys->recoveryTimer = 0;
    gTossBoys->recoveryCompleteFlag = 0;
    gTossBoys->sourceIndex = TOSS_BOYS_PLAYER_DISPENSER;
    gTossBoys->targetIndex = param;
    gTossBoys->throwVelocity = velocity;
    gTossBoys->defaultCueDuration = amplitude;
    gTossBoys->barelyActive = 0;

    srcPosition = &toss_boys_player_positions[gTossBoys->sourceIndex];
    dstPosition = &toss_boys_player_positions[gTossBoys->targetIndex];

    task = gTossBoys->ballMotionTaskId;
    if (task >= 0) {
        if (get_task_state(task) != 0) {
            force_cancel_task(task);
        }
    }

    frame = ticks_to_frames(gTossBoys->defaultCueDuration);
    time = throwSpeed - 5;
    duration = frame - time;

    gTossBoys->ballMotionTaskId = scene_set_sprite_motion_sine_wave(
        gTossBoys->ballSprite,
        srcPosition->x, srcPosition->y,
        dstPosition->x, dstPosition->y,
        gTossBoys->throwVelocity, duration);

    sprite_set_visible(gSpriteHandler, gTossBoys->ballSprite, TRUE);
    sprite_set_anim_cel(gSpriteHandler, gTossBoys->dispenserSprite, 0);
    play_sound(&s_f_toss_ball_seqData);

    sprite_set_anim(gSpriteHandler, gTossBoys->arrowSprite, toss_boys_get_anim(toss_boys_arrow_anim_ids[param]), 0, 1, 0, 2);

    sprite_set_visible(gSpriteHandler, gTossBoys->arrowSprite, TRUE);

    toss_boys_play_soshi_strum();
}

void toss_boys_throw_ball_event(u32 arg0) {
    u32 param = arg0 & 3;
    s32 velocity = (arg0 >>= 2) & 0x3ff;
    u32 amplitude = arg0 >> 10;

    toss_boys_throw_ball(param, velocity, amplitude, 0);
}

void toss_boys_set_throw_param(u32 arg0) {
    gTossBoys->sourceIndex = gTossBoys->targetIndex;
    gTossBoys->targetIndex = arg0 & 3;
    arg0 >>= 2;
    gTossBoys->throwVelocity = arg0 & 0x3ff;
    gTossBoys->defaultCueDuration = arg0 >> 10;
}


void toss_boys_start_ball_motion(struct TossBoysCue *cue, s32 offset) {
    s32 frame;
    s32 time;
    s32 duration;

    struct Vector2 *srcPosition = &toss_boys_player_positions[cue->fromIndex];
    struct Vector2 *dstPosition = &toss_boys_player_positions[cue->toIndex];
    
    s32 task = gTossBoys->ballMotionTaskId;
    if (task >= 0 && get_task_state(task) != 0) {
        force_cancel_task(task);
    }
    
    frame = ticks_to_frames(cue->duration);
    time = offset - 5;
    duration = frame - time;
    
    gTossBoys->ballMotionTaskId = scene_set_sprite_motion_sine_wave(gTossBoys->ballSprite,
        srcPosition->x, srcPosition->y,
        dstPosition->x, dstPosition->y,
        cue->throwSpeed, duration);
    
    sprite_set_visible(gSpriteHandler, gTossBoys->ballSprite, TRUE);
    gTossBoys->affineRotationSpeed = toss_boys_affine_rotation_table[cue->fromIndex][cue->toIndex] * 4;
    if (cue->drumNoteId >= 0) {
        play_drumtech_note(cue->drumNoteId, 0x100, 0);
    }
}

void toss_boys_cue_spawn(struct Cue *cue, struct TossBoysCue *tbCue, u32 param) {
    tbCue->playerIndex = param & 0xF;
    tbCue->actionType = param >> 4;

    tbCue->throwSpeed = gTossBoys->throwVelocity;
    tbCue->duration = gTossBoys->defaultCueDuration;

    tbCue->fromIndex = gTossBoys->sourceIndex;
    tbCue->toIndex = gTossBoys->targetIndex;

    tbCue->inputDisabled = FALSE;

    tbCue->drumNoteId = gTossBoys->queuedDrumNoteId;
    gTossBoys->queuedDrumNoteId = -1;

    if (gTossBoys->recoveryCompleteFlag != FALSE) {
        if (tbCue->duration != 0 && tbCue->duration != 0x18) {
            gameplay_set_cue_input_buttons(cue, 0);
            tbCue->inputDisabled = TRUE;
            gTossBoys->recoveryCompleteFlag = FALSE;
        }
    }
}

u32 toss_boys_cue_update(struct Cue *cue, struct TossBoysCue *tbCue, u32 runningTime, u32 duration) {
    if (runningTime > duration + ticks_to_frames(0xC)) {
        return 1;
    } else {
        return 0;
    }
}

void toss_boys_cue_despawn(struct Cue *cue, struct TossBoysCue *tbCue) {

}

void toss_boys_process_cue_result(struct Cue *cue, struct TossBoysCue *tbCue, u32 result) {
    struct Vector2* pos;
    
    if (gTossBoys->ballInFlightFlag == FALSE || gTossBoys->recoveryTimer != 0){
        gameplay_ignore_this_cue_result();
        return;    
    }
    if (gTossBoys->recoveryCompleteFlag != 0) {
        gameplay_ignore_this_cue_result();
        return;  
    } 
    
    if (result != 0) {
        gTossBoys->barelyActive = TRUE;
        gTossBoys->playerBarelyTimer[tbCue->playerIndex] = ticks_to_frames(0x24);
    } else {
        gTossBoys->barelyActive = result;
    }

    switch (tbCue->actionType) {
        case 0:
            toss_boys_start_ball_motion(tbCue, gameplay_get_last_hit_offset());
            toss_boys_play_player_animation(tbCue->playerIndex, 0);
            toss_boys_lock_player_buttons(tbCue->playerIndex, ticks_to_frames(8));
            play_sound_w_pitch_volume(toss_boys_ball_bounce_sfx[tbCue->playerIndex], 0x100, 0);
            sprite_set_anim(gSpriteHandler, gTossBoys->ballSprite, toss_boys_get_anim(TOSS_BOYS_ANIM_BALL1), 0, 0, 0, 0);
            gTossBoys->affineScaleOffset = 0x80;
            break;

        case 1:
            toss_boys_set_player_ready_state(tbCue->playerIndex, 2);
            toss_boys_play_player_animation(tbCue->playerIndex, 0);
            sprite_set_visible(gSpriteHandler, gTossBoys->ballSprite, FALSE);
            toss_boys_lock_player_buttons(tbCue->playerIndex, -1);
            play_sound_w_pitch_volume(toss_boys_ball_bounce_sfx[tbCue->playerIndex], 0x100, 0);
            break;

        case 2:
        {
            toss_boys_play_player_animation(tbCue->playerIndex, 0);
            toss_boys_set_player_ready_state(tbCue->playerIndex, 0);
            sprite_set_visible(gSpriteHandler, gTossBoys->ballSprite, FALSE);
            toss_boys_lock_player_buttons(tbCue->playerIndex, ticks_to_frames(0x24));
            play_sound_w_pitch_volume(toss_boys_ball_pop_sfx[tbCue->playerIndex], 0x100, 0);
            toss_boys_play_drum_note(tbCue->playerIndex + 31);

            pos = &toss_boys_player_positions[tbCue->playerIndex];

            sprite_create(gSpriteHandler, toss_boys_get_anim(TOSS_BOYS_ANIM_POP_EFFECT), 0, pos->x, pos->y, 0x4200, 1, 0, 3);
        
            gTossBoys->ballInFlightFlag = FALSE;
            break;
        }
    }

    gTossBoys->pitchOffset = 0;
}

void toss_boys_cue_hit(struct Cue* cue, struct TossBoysCue* tbCue, u32 pressed, u32 released) {
    toss_boys_process_cue_result(cue, tbCue, 0);
}

void toss_boys_cue_barely(struct Cue* cue, struct TossBoysCue* tbCue, u32 pressed, u32 released) {
    toss_boys_process_cue_result(cue, tbCue, 1);
}

void toss_boys_cue_miss(struct Cue *cue, struct TossBoysCue *tbCue) {
    struct Vector2 *pos;
    u32 recoveryTimer;
    u32 dest;
    s32 velocity;

    recoveryTimer = gTossBoys->recoveryTimer;
    if (recoveryTimer != 0) {
        gameplay_ignore_this_cue_result();
        return;
    }

    if (gTossBoys->ballInFlightFlag == FALSE) {
        gameplay_ignore_this_cue_result();

        if (tbCue->inputDisabled == FALSE) {
            return;
        }

        gameplay_ignore_this_cue_result();

        dest = tbCue->toIndex;
        if (tbCue->duration == 0x30) {
            velocity = 60;
        } else {
            velocity = 100;
        }

        toss_boys_throw_ball(dest, velocity, tbCue->duration, 5);
        return;
    }

    tbCue->throwSpeed = toss_boys_throw_speed_table[tbCue->fromIndex][tbCue->toIndex];
    tbCue->throwSpeed = ((u16)tbCue->throwSpeed * tbCue->duration) / 24;

    sprite_set_anim(gSpriteHandler, gTossBoys->playerSprite[tbCue->playerIndex], toss_boys_get_anim((u8)toss_boys_miss_anim_ids[tbCue->playerIndex]), 0, 1, 0x7F, recoveryTimer);

    gTossBoys->playerAnimCooldown[tbCue->playerIndex] = ticks_to_frames(0xC);
    gTossBoys->playerReadyState[tbCue->playerIndex] = 0;

    toss_boys_lock_player_buttons(tbCue->playerIndex, ticks_to_frames(0xC));

    play_sound_w_pitch_volume(toss_boys_ball_miss_sfx[tbCue->playerIndex], 0x100, 0);

    sprite_set_anim(gSpriteHandler, gTossBoys->ballSprite, toss_boys_get_anim(TOSS_BOYS_ANIM_BALL1), 0, recoveryTimer, recoveryTimer, recoveryTimer);

    sprite_set_visible(gSpriteHandler, gTossBoys->ballSprite, FALSE);

    gTossBoys->affineScaleOffset = recoveryTimer;

    pos = &toss_boys_player_positions[tbCue->playerIndex];

    sprite_create(gSpriteHandler, toss_boys_get_anim(TOSS_BOYS_ANIM_POP_EFFECT), 0, pos->x, pos->y + 4, 0x4200, 1, recoveryTimer, 3);

    gTossBoys->recoveryTimer = ticks_to_frames(0x24);
    gTossBoys->pitchOffset = 3072;
    gTossBoys->ballInFlightFlag = FALSE;

    beatscript_enable_loops();
}

void toss_boys_play_player_animation(u32 index, u32 value) {
    s32 animIndex;
    s8 *animTable;
    u32 animID;
    u32 tableAddr;
    s8* finalAddr;
    struct Animation* anim;

    animIndex = gTossBoys->playerReadyState[index];

    if (gTossBoys->ballInFlightFlag == FALSE || gTossBoys->recoveryTimer != 0 || gTossBoys->recoveryCompleteFlag != FALSE) {
        animIndex = 0;
    }

    if (gTossBoys->playerBarelyTimer[index] != 0) animTable = toss_boys_barely_anim_ids;
    if (gTossBoys->playerBarelyTimer[index] == 0) animTable = toss_boys_hit_anim_ids;

    finalAddr = (index + animIndex * 3) + (u32)animTable; // i hate this
    anim = toss_boys_get_anim(*finalAddr);
    sprite_set_anim(gSpriteHandler, gTossBoys->playerSprite[index], anim, value, 1, 0x7F, 0);
    gTossBoys->playerAnimCooldown[index] = ticks_to_frames(0xC);
}

void toss_boys_set_player_ready_state(u32 index, u32 value)
{
    u32 state;
    struct Animation* anim;
    s16 sprite;
    s8 animId;

    state = value;
    gTossBoys->playerReadyState[index] = state;
    if (gTossBoys->ballInFlightFlag == FALSE || gTossBoys->recoveryTimer != 0 || gTossBoys->recoveryCompleteFlag != FALSE) {
        state = 0;
    }
    
    animId = toss_boys_ready_anim_ids[state][index];
    if (animId >= 0) {
        anim = toss_boys_get_anim(animId);
        sprite_set_anim(gSpriteHandler, gTossBoys->playerSprite[index], anim, toss_boys_ready_anim_playback[state][index], 1, 0x7F, 0);
    }
}

void toss_boys_set_player_ready_state_event(u32 arg0) {
    toss_boys_set_player_ready_state(arg0 & 0xF, (arg0>>4) & 0xF);
}

void toss_boys_tick_affine_transform(void) {
    gTossBoys->affineRotation = gTossBoys->affineRotation + gTossBoys->affineRotationSpeed;
    gTossBoys->affineScaleOffset = FIXED_POINT_MUL(gTossBoys->affineScaleOffset, 220);
    set_affine_scale_rotation(gTossBoys->ballAffineGroup, gTossBoys->affineScaleOffset + 256, gTossBoys->affineRotation);
}

void toss_boys_input_event(u32 pressed, u32 released) {
    if((pressed & A_BUTTON) != 0){
        toss_boys_play_player_animation(0, 1);
        toss_boys_lock_player_buttons(0, ticks_to_frames(0xc));
    }

    if((pressed & B_BUTTON) != 0){
        toss_boys_play_player_animation(1, 1);
        toss_boys_lock_player_buttons(1, ticks_to_frames(0xc));
    }

    if((pressed & DPAD_ANY) != 0){
        toss_boys_play_player_animation(2, 1);
        toss_boys_lock_player_buttons(2, ticks_to_frames(0xc));
    }

    play_sound(&s_f_toss_swing_seqData);
}

void toss_boys_common_beat_animation(void) {
    u32 i;
    u8 animIndex;
    s8 animId;
    
    for(i = 0; i < TOSS_BOYS_PLAYER_COUNT; i++){
        if (gTossBoys->playerAnimCooldown[i] != 0)
            continue;

        animIndex = gTossBoys->playerReadyState[i];
        
        if (gTossBoys->ballInFlightFlag == FALSE || gTossBoys->recoveryTimer != 0 || gTossBoys->recoveryCompleteFlag != FALSE) {
            animIndex = 0;
        }

        animId = toss_boys_beat_anim_ids[animIndex][i];
        if (animId < 0)
            continue;

        sprite_set_anim( gSpriteHandler, gTossBoys->playerSprite[i], toss_boys_get_anim(animId), toss_boys_beat_anim_playback[animIndex][i], 1, 0x7F, 0);
    }

    toss_boys_soshi_update();
}

void toss_boys_common_display_text() {

}

void toss_boys_common_init_tutorial() {

}
