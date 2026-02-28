#include "engines/sick_beats.h"
#include "src/scenes/gameplay.h"
#include "src/memory.h"
#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/code_08008dcc.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"
#include "src/affine_sprite.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gSickBeats ((struct SickBeatsEngineData *)gCurrentEngineData)


/* SICK BEATS */


// Init Particles
void sick_beats_init_particles(void) {
    u32 i;
    if (gSickBeats->version != ENGINE_VER_SICK_BEATS_ENDLESS) {
        return;
    }
    gSickBeats->particleSprites[0] = sprite_create(gSpriteHandler, anim_sick_beats_endless_particle, 0, 64, 64, 0x800, 0, 0, 0x8000);
    for (i = 1; i < SICK_BEATS_PARTICLE_AMOUNT; i++) { // Copy particles
        gSickBeats->particleSprites[i] = sprite_clone(gSpriteHandler, gSickBeats->particleSprites[0]);
    }

    for (i = 0; i < SICK_BEATS_PARTICLE_AMOUNT; i++) {
        gSickBeats->particleCounters[i] = 0;
    }
    gSickBeats->particleCurrent = 0;
    gSickBeats->particlePitch = 1;
    gSickBeats->particleCels = sprite_get_data(gSpriteHandler, gSickBeats->particleSprites[0], 2);
}

// Update Particles
void sick_beats_update_particles(void) {
    u32 i;

    if ((gSickBeats->version != ENGINE_VER_SICK_BEATS_ENDLESS) || gSickBeats->microbeWasHurt) {
        return;
    }
    for (i = 0; i < SICK_BEATS_PARTICLE_AMOUNT; i++) {
        if (gSickBeats->particleCounters[i]) {
            gSickBeats->particleCounters[i] -= 1;
            if (!gSickBeats->particleCounters[i]) {
                sprite_set_visible(gSpriteHandler, gSickBeats->particleSprites[i], 0);
            }
        }
    }
}

// Play Particle Sound
void sick_beats_play_particle_sound(void) {
    u32 particlePitch;
    s32 pitch;
    
    func_0800c604(0);
    particlePitch = clamp_int32(gSickBeats->particlePitch, 1, 8);
    pitch = sick_beats_particle_sfx_pitch[agb_random(particlePitch)];
    play_sound_w_pitch_volume(&s_f_virus_note_land_seqData, 128, pitch);
}

// https://decomp.me/scratch/N1kry
// Process Particle
#include "asm/engines/sick_beats/asm_080429e8.s"

// Process X Particles
void sick_beats_process_x_particles(u32 particleAmount) {
    u32 i;

    if (gSickBeats->version != ENGINE_VER_SICK_BEATS_ENDLESS) {
        return;
    }
    for (i = 0; i < particleAmount; i++) {
        func_080429e8();
    }
}

// Engine Event 0x06 (Increment Particle Pitch)
void sick_beats_increment_particle_pitch(void) {
    if (gSickBeats->version != ENGINE_VER_SICK_BEATS_ENDLESS) {
        return;
    }
    if (gSickBeats->particlePitch < gSickBeats->particleCels) {
        gSickBeats->particlePitch++;
    }
}

// Init Counters
void sick_beats_init_counters(void) {
    u32 i, j;
    s32 x, y;
    struct SickBeatsScoreCounter *counter;
    
    if (gSickBeats->version != ENGINE_VER_SICK_BEATS_ENDLESS) {
        return;
    }
    for (i = 0; i < ARRAY_COUNT(gSickBeats->scoreCounters); i++) {
        counter = &gSickBeats->scoreCounters[i];
        
        if (i == SICK_BEATS_SCORE_CURRENT) {
            counter->counterSprite = sprite_create(gSpriteHandler, anim_sick_beats_score_counter, 0, 214, 40, 0x8f00, 0, 0, 0);
            x = 214;
            y = 40;
        } else {
            counter->counterSprite = sprite_create(gSpriteHandler, anim_sick_beats_high_score_counter, 0, 214, 16, 0x8f00, 0, 0, 0);
            x = 214;
            y = 16;
        }

        for (j = 0; j < ARRAY_COUNT(counter->digitSprite); j++) {
            counter->digitSprite[j] = sprite_create(gSpriteHandler, anim_sick_beats_score_num, 0, x - 5 * j, y, 0x8f00, 0, 0, 0);
        }
    }
    gSickBeats->unk21C = 0;
}

// Draw Score
void sick_beats_draw_score(u32 type) {
    u32 i;
    struct SickBeatsScoreCounter *scoreCounters = &gSickBeats->scoreCounters[type];
    u32 value = scoreCounters->value;

    for (i = 0; i < ARRAY_COUNT(scoreCounters->digitSprite); i++) {
        sprite_set_anim_cel(gSpriteHandler, scoreCounters->digitSprite[i], value % 10);
        value /= 10;
    }
}

// Update Score
void sick_beats_update_score(u32 type, u32 value) {
    if (gSickBeats->version != ENGINE_VER_SICK_BEATS_ENDLESS) {
        return;
    }
    gSickBeats->scoreCounters[type].value = clamp_int32(value, 0, 9999);
    sick_beats_draw_score(type);
    if (type != SICK_BEATS_SCORE_CURRENT) {
        return;
    }
    if (gSickBeats->scoreCounters[SICK_BEATS_SCORE_CURRENT].value > gSickBeats->scoreCounters[SICK_BEATS_SCORE_HIGH].value) {
        gSickBeats->scoreCounters[SICK_BEATS_SCORE_HIGH].value = gSickBeats->scoreCounters[SICK_BEATS_SCORE_CURRENT].value;
        sick_beats_draw_score(SICK_BEATS_SCORE_HIGH);
    }
}

// Add Score
void sick_beats_add_score(u32 value) {
    if (gSickBeats->version == ENGINE_VER_SICK_BEATS_ENDLESS) {
        sick_beats_update_score(0, gSickBeats->scoreCounters[SICK_BEATS_SCORE_CURRENT].value + value);
    }
}

// Init Virus
void sick_beats_init_virus(void) {
    u32 i;
    struct SickBeatsVirus *virus = &gSickBeats->virus;

    for (i = 0; i < ARRAY_COUNT(virus->exists); i++) {
        virus->exists[i] = FALSE;
    }
    virus->state = SICK_BEATS_VIRUS_STATE_INVALID;
    virus->current = 0;
    virus->spawnedCounter = 0;
    virus->hitsRequired1 = 1;
    virus->virusCuePalette = 0;
    virus->hitsRequired = 1;
    virus->virusPalette = 0;

    for (i = 0; i < SICK_BEATS_VIRUS_AMOUNT; i++) {
        virus->virusData[i].path = NULL;
    }
}

// Process Virus Data
void sick_beats_process_virus_data(struct SickBeatsVirusData *virusData) {
    struct SickBeatsVirus *virus = &gSickBeats->virus;
    struct SickBeatsPath *path = virusData->path;
    
    if (!path) {
        return;
    }
    virusData->rest -= func_0800c398();
    while (virusData->rest < 0) {
        switch (path->command) {
            case 0xfe: // Rest
                break;
            case 0xff: // Stop
                virusData->path = NULL;
                return;
            case 0xe: // Set Marking Criteria
                gameplay_set_marking_criteria(path->arg);
                break;
            case 0xf: // Spawn Cue (No Entering)
                virus->exists[virusData->virusID] = TRUE;
                break;
            default: // Spawn Cue
                virus->state = path->command;
                virus->current = virusData->virusID;
                virus->hitsRequired1 = virusData->hitsRequired;
                virus->virusCuePalette = virusData->palette;
                gameplay_spawn_cue(path->arg);
        }
        path++;
        virusData->rest += INT_TO_FIXED(path->rest);
    }
    virusData->path = path;
}

// Update Virus
void sick_beats_update_virus(void) {
    u32 i;
    struct SickBeatsEngineData *engineData;
    struct SickBeatsVirusData *virusData;
    
    engineData = gSickBeats;
    i = 0;
    virusData = engineData->virus.virusData;

    for (i; i < SICK_BEATS_VIRUS_AMOUNT; i++) {
        sick_beats_process_virus_data(virusData);
        virusData++;
    }
}

// Engine Event 0x00 (Set Virus/Virus Action)
void sick_beats_set_virus(u32 arg) {
    struct SickBeatsVirus *virus = &gSickBeats->virus;
    virus->state = (arg >> 8);
    virus->current = (arg >> 0); 
}

// Engine Event 0x01 (Spawn Virus)
void sick_beats_spawn_virus(struct SickBeatsPath *path) {
    struct SickBeatsVirus *virus = &gSickBeats->virus;
    struct SickBeatsVirusData *virusData;
    u32 i = 0;
    
    for (virusData = &virus->virusData[0]; virusData->path != NULL; virusData = &virus->virusData[i]) {
        if (++i > (SICK_BEATS_VIRUS_AMOUNT - 1)) {
            return;
        }
    }
    if (i > (SICK_BEATS_VIRUS_AMOUNT - 1)) {
        return;
    }
    virusData->path = path;
    virusData->virusID = virus->spawnedCounter;
    virusData->rest = 0;
    virusData->hitsRequired = virus->hitsRequired;
    virusData->palette = virus->virusPalette;
    if (++virus->spawnedCounter > 0xff) {
        virus->spawnedCounter = 0;
    }
}

// Engine Event 0x02 (Set Hits Required)
void sick_beats_set_virus_hits(u32 hits) {
    struct SickBeatsVirus *virus = &gSickBeats->virus;

    virus->hitsRequired = hits;
}

// Engine Event 0x03 (Set Virus Palette)
void sick_beats_set_virus_palette(u32 palette) {
    struct SickBeatsVirus *virus = &gSickBeats->virus;

    virus->virusPalette = palette;
}

// Init Forks 
void sick_beats_init_forks(void) {
    struct SickBeatsForks *forks = &gSickBeats->forks;

    forks->launcher = sprite_create(gSpriteHandler, anim_fork_launcher, 0, 104, 60, 0x4800, 1, 0x7f, 0);
    forks->spriteUp = create_affine_sprite(anim_fork_hit_none2, 0, 104, 60, 0x4800, INT_TO_FIXED(1), 
                                        INT_TO_FIXED(-2), 1, 0x7f, 0, FALSE); // facing up
    forks->spriteDown = create_affine_sprite(anim_fork_hit_none2, 0, 104, 60, 0x4800, INT_TO_FIXED(1), 
                                        INT_TO_FIXED(2), 1, 0x7f, 0, FALSE); // facing down
    forks->spriteLeft = create_affine_sprite(anim_fork_hit_none2, 0, 104, 60, 0x4800, INT_TO_FIXED(1), 
                                        INT_TO_FIXED(4), 1, 0x7f, 0, FALSE); // facing left
    forks->spriteRight = create_default_affine_sprite(anim_fork_hit_none2, 0, 104, 60, 0x4800, 1, 0x7f, FALSE); // facing right
    forks->counterRight = forks->counterLeft = forks->counterDown = forks->counterUp = 0;
}

// Update Forks 
void sick_beats_update_forks(void) {
    struct SickBeatsForks *forks = &gSickBeats->forks;
    u16 buttons = DPAD_LEFT | DPAD_RIGHT | DPAD_UP | DPAD_DOWN;

    affine_sprite_set_visible(forks->spriteUp, 1);
    affine_sprite_set_visible(forks->spriteDown, 1);
    affine_sprite_set_visible(forks->spriteLeft, 1);
    affine_sprite_set_visible(forks->spriteRight, 1);
    if (forks->counterUp) {
        forks->counterUp--;
        buttons = DPAD_LEFT | DPAD_RIGHT | DPAD_DOWN;
        affine_sprite_set_anim_cel(forks->spriteUp, 0);
        affine_sprite_set_visible(forks->spriteUp, 0);
    }
    if (forks->counterDown) {
        forks->counterDown--;
        buttons &= ~(DPAD_DOWN);
        affine_sprite_set_anim_cel(forks->spriteDown, 0);
        affine_sprite_set_visible(forks->spriteDown, 0);
    }
    if (forks->counterLeft) {
        forks->counterLeft--;
        buttons &= ~(DPAD_LEFT);
        affine_sprite_set_anim_cel(forks->spriteLeft, 0);
        affine_sprite_set_visible(forks->spriteLeft, 0);
    }
    if (forks->counterRight) {
        forks->counterRight--;
        buttons &= ~(DPAD_RIGHT);
        affine_sprite_set_anim_cel(forks->spriteRight, 0);
        affine_sprite_set_visible(forks->spriteRight, 0);
    }
    
    gameplay_set_input_buttons(buttons, 0);
}

// Set Fork Counter
void sick_beats_set_fork_counter(u32 input) {
    struct SickBeatsForks *forks = &gSickBeats->forks;
    u32 forkCounter = ticks_to_frames(30);

    if (input & DPAD_UP) {
        forks->counterUp = forkCounter;
    }
    if (input & DPAD_DOWN) {
        forks->counterDown = forkCounter;
    }
    if (input & DPAD_LEFT) {
        forks->counterLeft = forkCounter;
    }
    if (input & DPAD_RIGHT) {
        forks->counterRight = forkCounter;
    } 
    sprite_set_anim_cel(gSpriteHandler, forks->launcher, 0);
}

// Init Yellow Microbe
void sick_beats_init_yellow_microbe(void) {
    struct SickBeatsYellowMicrobe *yellowMicrobe = &gSickBeats->yellowMicrobe;

    yellowMicrobe->sprite = sprite_create(gSpriteHandler, anim_yellow_microbe_beat, 0, 174, 138, 0x8900, 1, 0x7f, 0);
    yellowMicrobe->state = SICK_BEATS_MICROBE_STATE_BEAT;
}

// Update Yellow Microbe
void sick_beats_update_yellow_microbe(void) {
    struct SickBeatsYellowMicrobe *yellowMicrobe = &gSickBeats->yellowMicrobe;

    if (yellowMicrobe->eventTimer) {
        yellowMicrobe->eventTimer--;
        return;
    } else {
        switch (yellowMicrobe->state) {
            case SICK_BEATS_MICROBE_STATE_BEAT:
                return;
            case SICK_BEATS_MICROBE_STATE_HURT:
                if (yellowMicrobe->isHurt) {
                    sick_beats_set_yellow_microbe_state(SICK_BEATS_MICROBE_STATE_VANISH);
                    play_sound(&s_f_virus_face_fadeout_seqData);
                    sick_beats_set_next_doctor_state(SICK_BEATS_DOCTOR_STATE_FAIL);
                }
                if (gSickBeats->gameOverBeatscript && (!gSickBeats->microbeWasHurt)) {
                    gSickBeats->microbeWasHurt = TRUE;
                    gSickBeats->gameOverCounter = 9999;
                    func_0801d968(gSickBeats->gameOverBeatscript);
                }
                break;
            case SICK_BEATS_MICROBE_STATE_VANISH:
                if (yellowMicrobe->isHurt) {
                    sick_beats_set_yellow_microbe_state(SICK_BEATS_MICROBE_STATE_VIRUS);
                }
                break;
            case SICK_BEATS_MICROBE_STATE_VIRUS:
                if (yellowMicrobe->isHurt) {
                    if (gSickBeats->microbeWasHurt) {
                        sprite_set_playback(gSpriteHandler, yellowMicrobe->sprite, 1, 0, 0);
                        sprite_set_callback(gSpriteHandler, yellowMicrobe->sprite, 0, 0);
                        yellowMicrobe->isHurt = FALSE;
                    } else {
                        sick_beats_set_yellow_microbe_state(SICK_BEATS_MICROBE_STATE_RETURN);
                    }
                }
                break;
            case SICK_BEATS_MICROBE_STATE_RETURN:
                if (yellowMicrobe->isHurt) {
                    sick_beats_set_yellow_microbe_state(SICK_BEATS_MICROBE_STATE_BEAT);
                }
                break;
            
        }
    }
}

// Yellow Microbe Sprite End Callback
void sick_beats_yellow_microbe_callback(u32 arg0, u32 arg1, u8 *isHurt) {
    *isHurt = TRUE;
}

// Set Yellow Microbe State
void sick_beats_set_yellow_microbe_state(u32 state) {
    struct SickBeatsYellowMicrobe *yellowMicrobe = &gSickBeats->yellowMicrobe;
    if (state == SICK_BEATS_MICROBE_STATE_BEAT) {
        sprite_set_anim(gSpriteHandler, yellowMicrobe->sprite, sick_beats_microbe_event_anim[SICK_BEATS_MICROBE_STATE_BEAT], 0, 1, 0x1b, 0);
        sprite_set_callback(gSpriteHandler, yellowMicrobe->sprite, 0, 0);
    } else {
        sprite_set_anim(gSpriteHandler, yellowMicrobe->sprite, sick_beats_microbe_event_anim[state], 0, 1, 0, 4);
        sprite_set_callback(gSpriteHandler, yellowMicrobe->sprite, sick_beats_yellow_microbe_callback, (u32)&yellowMicrobe->isHurt);
    }

    yellowMicrobe->state = state;
    yellowMicrobe->isHurt = FALSE;
    yellowMicrobe->eventTimer = ticks_to_frames(sick_beats_microbe_event_durations[state]);
}

// Graphics Init. 3
void sick_beats_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

// Graphics Init. 2
void sick_beats_init_gfx2(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), gfx_table_sick_beats, 0x2000);
    run_func_after_task(task, sick_beats_init_gfx3, 0);
}

// Graphics Init. 1
void sick_beats_init_gfx1(void) {
    u32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), sick_beats_buffered_textures);
    run_func_after_task(task, sick_beats_init_gfx2, 0);
}

// Game Engine Start
void sick_beats_engine_start(u32 version) {
    gSickBeats->version = version;
    sick_beats_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 0, 30, 2);
    sick_beats_init_yellow_microbe();
    sick_beats_init_forks();
    sick_beats_init_virus();
    gSickBeats->doctorSprite = sprite_create(gSpriteHandler, anim_virus_doctor_beat, 0, 17, 155, 0x800, 1, 0x7f, 0);
    gSickBeats->radioSprite = sprite_create(gSpriteHandler, anim_sick_beats_radio, 0, 17, 155, 0x810, 1, 0x7f, 0);
    gSickBeats->doctorCurrentState = SICK_BEATS_DOCTOR_STATE_BEAT;
    gSickBeats->doctorNextState = SICK_BEATS_DOCTOR_STATE_INVALID;
    gSickBeats->unk1F2 = 0;
    gSickBeats->doctorBeatCounter = 0;
    sick_beats_init_counters();
    sick_beats_update_score(0, 0);
    sick_beats_update_score(1, D_030046a8->data.unk294[2]);
    sick_beats_init_particles();
    gameplay_set_input_buttons(0, 0);
    gameplay_prevent_dpad_overlap(FALSE);
    gSickBeats->microbeWasHurt = FALSE;
    gSickBeats->gameOverBeatscript = NULL;
    gSickBeats->gameOverCounter = 0;
}

// Engine Event 0x07 (STUB)
void sick_beats_engine_event_stub(void) {

}

// Update Doctor
void sick_beats_update_doctor(void) {
    if (gSickBeats->doctorBeatCounter) {
        gSickBeats->doctorBeatCounter--;
        if ((!gSickBeats->doctorBeatCounter) && (gSickBeats->doctorNextState > SICK_BEATS_DOCTOR_STATE_INVALID)) {
            gSickBeats->doctorCurrentState = gSickBeats->doctorNextState;
            gSickBeats->doctorNextState = SICK_BEATS_DOCTOR_STATE_INVALID;
            gSickBeats->unk1F2 = 0;
        }
    }
}

// Game Engine Update
void sick_beats_engine_update(void) {
    gSickBeats->highestPriorityState = 0; // Reset priority each frame
    sick_beats_update_yellow_microbe();
    sick_beats_update_forks();
    sick_beats_update_virus();
    sick_beats_update_doctor();
    sick_beats_update_particles();
    if (gSickBeats->microbeWasHurt) {
        if (gSickBeats->gameOverCounter) {
            gSickBeats->gameOverCounter--;
        } else {
            if (D_03004afc & A_BUTTON) {
                set_pause_beatscript_scene(FALSE);
            }
        }
    }
}

// Set Next Doctor State
void sick_beats_set_next_doctor_state(s32 state) {
    if ((gSickBeats->doctorCurrentState <= state) && (gSickBeats->doctorNextState <= state)) {
        if ((gSickBeats->doctorCurrentState == SICK_BEATS_DOCTOR_STATE_HITONE || gSickBeats->doctorCurrentState == SICK_BEATS_DOCTOR_STATE_HITCONSECUTIVE) && (state == SICK_BEATS_DOCTOR_STATE_HITONE)) {
            state = SICK_BEATS_DOCTOR_STATE_HITCONSECUTIVE;
        }
        gSickBeats->doctorNextState = state;
    }
}

// Engine Event 0x04 (Set Game Over Beatscript)
void sick_beats_set_game_over_beatscript(struct Beatscript *beatscript) {
    gSickBeats->gameOverBeatscript = beatscript;
}

// Engine Event 0x05 (Endless Game Over)
void sick_beats_endless_play_game_over(void) {
    sprite_create(gSpriteHandler, anim_sick_beats_game_over, 0, 120, 80, 0x400, 1, 0, 0);
    gSickBeats->gameOverCounter = 20;
    D_030046a8->data.unk294[2] = gSickBeats->scoreCounters[SICK_BEATS_SCORE_HIGH].value; // high score
}

// Game Engine Stop
void sick_beats_engine_stop(void) {

}

// Get Virus Data From ID
struct SickBeatsVirusData *sick_beats_get_virus_data(u32 id) {
    u32 i = 0;
    struct SickBeatsVirus *virus = &gSickBeats->virus;
    struct SickBeatsVirusData *virusData = gSickBeats->virus.virusData;
    struct SickBeatsVirusData *virusData1 = virus->virusData;

    for (i; (i < SICK_BEATS_VIRUS_AMOUNT); virusData++, virusData1++, i++) {
        if (virusData->path && virusData->virusID == id) {
            return virusData1;
        }
    }
    
    return NULL;
}

// Cue - Spawn
void sick_beats_cue_spawn(struct Cue *cue, struct SickBeatsCue *info, u32 unused) {
    struct SickBeatsVirus *virus = &gSickBeats->virus;
    struct VirusAction *act;
    u32 isVirusHit = FALSE;
    
    info->virusState = virus->state;
    //
    info->currentVirus = virus->current;
    info->hitAmount = virus->hitsRequired1;
    info->virusPalette = virus->virusCuePalette;
    act = &sick_beats_virus_actions[info->virusState];
    if (act->rotation) {
        info->virusSprite = create_affine_sprite(act->anim, 0, act->x, act->y, 0x8800, INT_TO_FIXED(1), act->rotation,
                                            act->playbackArg1, act->playbackArg2, act->playbackArg3, 1);
    } else {
        info->virusSprite = create_default_affine_sprite(act->anim, 0, act->x, act->y, 0x8800, 
                                            act->playbackArg1, act->playbackArg2, act->playbackArg3);
    }
    affine_sprite_orr_attr(info->virusSprite, act->unkC);
    affine_sprite_set_base_palette(info->virusSprite, info->virusPalette);
    if (info->virusState == SICK_BEATS_VIRUS_STATE_ENTER_TUBE) {
        virus->exists[info->currentVirus] = TRUE;
    } else if (!virus->exists[info->currentVirus]) {
        affine_sprite_set_visible(info->virusSprite, 0);
        isVirusHit = TRUE;
    }
    info->isVirusHitOnce = FALSE;
    info->unk0_b5 = FALSE;
    switch (info->virusState) {
        case SICK_BEATS_VIRUS_STATE_UP_APPEAR:
        case SICK_BEATS_VIRUS_STATE_LEFT_APPEAR:
        case SICK_BEATS_VIRUS_STATE_DOWN_APPEAR:
        case SICK_BEATS_VIRUS_STATE_RIGHT_APPEAR:
            if (isVirusHit) {
                break;
            }
            {
                struct SoundPlayer *player;
                s8 panning;
                s16 pitch;
                u8 priority;
                
                // Priority: RIGHT(4) > DOWN(3) > LEFT(2) > UP(1)
                if (info->virusState == SICK_BEATS_VIRUS_STATE_RIGHT_APPEAR) 
                    priority = 4;
                else if (info->virusState == SICK_BEATS_VIRUS_STATE_DOWN_APPEAR)
                    priority = 3;
                else if (info->virusState == SICK_BEATS_VIRUS_STATE_LEFT_APPEAR)
                    priority = 2;
                else 
                    priority = 1; // UP_APPEAR
                
                // Update highest priority
                if (priority > gSickBeats->highestPriorityState) {
                    gSickBeats->highestPriorityState = priority;
                }
                
                // Set panning and pitch based on highest priority state
                if (gSickBeats->highestPriorityState == 4) {
                    panning = 0;                    // RIGHT (DOWN button) - center
                    pitch = INT_TO_FIXED(-4.0);     // Lower pitch
                } else if (gSickBeats->highestPriorityState == 3) {
                    panning = -90;                 // DOWN (LEFT button) - left
                    pitch = 0;                      // Normal pitch
                } else if (gSickBeats->highestPriorityState == 2) {
                    panning = 0;                    // LEFT (UP button) - center
                    pitch = 0;                      // Normal pitch
                } else {
                    panning = 90;                  // UP (RIGHT button) - right
                    pitch = 0;                      // Normal pitch
                }
                
                player = play_sound_in_player(SFX_PLAYER_0, &s_f_virus_uhihi_seqData);
                if (player) {
                    midi_player_set_panning(player, 0xFFFF, panning);
                    midi_player_set_pitch(player, 0xFFFF, pitch);
                }
            }
            break;
        case SICK_BEATS_VIRUS_STATE_UP_DASH_INVULN:
        case SICK_BEATS_VIRUS_STATE_LEFT_DASH_INVULN:
        case SICK_BEATS_VIRUS_STATE_DOWN_DASH_INVULN:
        case SICK_BEATS_VIRUS_STATE_RIGHT_DASH_INVULN:
            if (isVirusHit) {
                break;
            }
            play_sound(&s_virus_dash_seqData);
            break;
        case SICK_BEATS_VIRUS_STATE_UP_DASH_VULN:
            gameplay_set_cue_input_buttons(cue, DPAD_RIGHT);
            break;
        case SICK_BEATS_VIRUS_STATE_LEFT_DASH_VULN:
            gameplay_set_cue_input_buttons(cue, DPAD_UP);
            break;
        case SICK_BEATS_VIRUS_STATE_DOWN_DASH_VULN:
            gameplay_set_cue_input_buttons(cue, DPAD_LEFT);
            break;
        case SICK_BEATS_VIRUS_STATE_RIGHT_DASH_VULN:
            gameplay_set_cue_input_buttons(cue, DPAD_DOWN);
            break;
        case SICK_BEATS_VIRUS_STATE_ATTACK_MICROBE:
            if (isVirusHit) {
                break;
            }
            play_sound(&s_f_virus_in_seqData);
            break;
        case SICK_BEATS_VIRUS_STATE_ENTER_TUBE:
            return;
    }
}

// Cue - Update
u32 sick_beats_cue_update(struct Cue *cue, struct SickBeatsCue *info, u32 runningTime, u32 duration) {
    struct SickBeatsVirus *virus = &gSickBeats->virus;

    if (!virus->exists[info->currentVirus]) {
        return TRUE;
    }

    if (runningTime > ticks_to_frames(120)) {
        return TRUE;
    }

    switch (info->virusState) {
        case SICK_BEATS_VIRUS_STATE_ENTER_TUBE:
            affine_sprite_set_x(info->virusSprite, math_lerp(256, 176, runningTime, ticks_to_frames(24)));
            if (runningTime > ticks_to_frames(24)) {
                return TRUE;
            }
            break;

        case SICK_BEATS_VIRUS_STATE_UP_APPEAR:
        case SICK_BEATS_VIRUS_STATE_LEFT_APPEAR:
        case SICK_BEATS_VIRUS_STATE_DOWN_APPEAR:
        case SICK_BEATS_VIRUS_STATE_RIGHT_APPEAR:
            if (runningTime > ticks_to_frames(24)) {
                return TRUE;
            }
            break;

        case SICK_BEATS_VIRUS_STATE_UP_DASH_VULN:
        case SICK_BEATS_VIRUS_STATE_LEFT_DASH_VULN:
        case SICK_BEATS_VIRUS_STATE_DOWN_DASH_VULN:
        case SICK_BEATS_VIRUS_STATE_RIGHT_DASH_VULN:
            if (!info->isVirusHitOnce && (runningTime > ticks_to_frames(24))) {
                info->isVirusHitOnce = TRUE;
                play_sound(&s_virus_dash_seqData);
            }
            if (runningTime > ticks_to_frames(48)) {
                return TRUE;
            }
            break;

        case SICK_BEATS_VIRUS_STATE_ATTACK_MICROBE:
            affine_sprite_set_y(info->virusSprite, math_lerp(104, 138, runningTime, ticks_to_frames(48)));
            if (!info->isVirusHitOnce && (runningTime > ticks_to_frames(40))) {
                info->isVirusHitOnce = TRUE;
                if (!gSickBeats->microbeWasHurt) {
                    sick_beats_set_yellow_microbe_state(SICK_BEATS_MICROBE_STATE_HURT);
                }
            }
            if (runningTime > ticks_to_frames(48)) {
                virus->exists[info->currentVirus] = FALSE;
                play_sound(&s_virus_miss_seqData);
                return TRUE;
            }
            break;
    }

    return FALSE;
}

// Cue - Despawn
void sick_beats_cue_despawn(struct Cue *cue, struct SickBeatsCue *info) {
    delete_affine_sprite(info->virusSprite);
}

// Fork Sprite End Callback
void sick_beats_fork_callback(u32 arg0, u32 arg1, struct AffineSprite *sprite) {
    delete_affine_sprite(sprite);
}

// Process Cue
struct AffineSprite *sick_beats_process_cue(struct SickBeatsCue *info, struct Animation *anim, struct SongHeader *seqData) {
    s16 virusEffectSprite;
    struct SickBeatsVirus *virus = &gSickBeats->virus;
    struct AffineSprite *baseVirusAfSprite = info->virusSprite;
    struct AffineSprite *nextVirusAfSprite = NULL; // hit animation
    s32 virusX = affine_sprite_get_base_sprite_x(info->virusSprite);
    s32 virusY = affine_sprite_get_base_sprite_y(info->virusSprite);
    u32 palette = info->virusPalette;

    if (info->hitAmount > 1) {
        if (palette == 8) {
            palette = 0;
        }
        if (info->virusPalette == 9) {
            palette = 8;
        }
        anim = anim_fork_hit_tough_virus;
        virusEffectSprite = sprite_create(gSpriteHandler, anim_tough_virus_hit_effect, 0, virusX, virusY, 0x87ff, 1, 0, 3);
        sprite_set_base_palette(gSpriteHandler, virusEffectSprite, info->virusPalette);
    }
    
    virusEffectSprite = -1;
    switch (info->virusState) {
        case SICK_BEATS_VIRUS_STATE_UP_DASH_VULN:
            nextVirusAfSprite = create_affine_sprite(anim, 0, virusX, virusY, 0x8800, INT_TO_FIXED(1), INT_TO_FIXED(0), 1, 0x7f, 4, 0);
            virusEffectSprite = sprite_create(gSpriteHandler, anim_virus_dash_up_half, 0, virusX, virusY, 0x8800, 1, 0, 3);
            sick_beats_set_fork_counter(DPAD_RIGHT);
            break;
        case SICK_BEATS_VIRUS_STATE_LEFT_DASH_VULN:
            nextVirusAfSprite = create_affine_sprite(anim, 0, virusX, virusY, 0x8800, INT_TO_FIXED(1), INT_TO_FIXED(-2), 1, 0x7f, 4, 0);
            virusEffectSprite = sprite_create(gSpriteHandler, anim_virus_dash_left_half, 0, virusX, virusY, 0x8800, 1, 0, 3);
            sick_beats_set_fork_counter(DPAD_UP);
            break;
        case SICK_BEATS_VIRUS_STATE_DOWN_DASH_VULN:
            nextVirusAfSprite = create_affine_sprite(anim, 0, virusX, virusY, 0x8800, INT_TO_FIXED(1), INT_TO_FIXED(4), 1, 0x7f, 4, 0);
            virusEffectSprite = sprite_create_w_attr(gSpriteHandler, anim_virus_dash_up_half, 0, virusX, virusY, 0x8800, 1, 0, 3, 0x2000);
            sick_beats_set_fork_counter(DPAD_LEFT);
            break;
        case SICK_BEATS_VIRUS_STATE_RIGHT_DASH_VULN:
            nextVirusAfSprite = create_affine_sprite(anim, 0, virusX, virusY, 0x8800, INT_TO_FIXED(1), INT_TO_FIXED(2), 1, 0x7f, 4, 0);
            virusEffectSprite = sprite_create_w_attr(gSpriteHandler, anim_virus_dash_left_half, 0, virusX, virusY, 0x8800, 1, 0, 3, 0x1000);
            sick_beats_set_fork_counter(DPAD_DOWN);
            break;
        default:
            gameplay_ignore_this_cue_result();
            break;
    }
    
    if (virusEffectSprite > -1) {
        sprite_set_base_palette(gSpriteHandler, virusEffectSprite, info->virusPalette);
    }
    if (nextVirusAfSprite) {
        affine_sprite_set_callback(nextVirusAfSprite, sick_beats_fork_callback, (u32)nextVirusAfSprite);
        affine_sprite_set_base_palette(nextVirusAfSprite, palette);
        affine_sprite_set_anim_speed(nextVirusAfSprite, (u32)INT_TO_FIXED(get_beatscript_tempo()) / 125);
        affine_sprite_set_visible(baseVirusAfSprite, 0);
        if (--info->hitAmount) {
            struct SickBeatsVirusData *virusData = sick_beats_get_virus_data(info->currentVirus);
            virusData->hitsRequired--;
            virusData->palette = palette;
            info->isVirusHitOnce = TRUE;
            info->unk0_b5 = TRUE;
            play_sound_in_player(SFX_PLAYER_1, &s_block_hit_seqData);
        } else {
            virus->exists[info->currentVirus] = FALSE;
            play_sound(seqData);
        }
    }
    return nextVirusAfSprite;
}

// Cue - Hit
void sick_beats_cue_hit(struct Cue *cue, struct SickBeatsCue *info, u32 pressed, u32 released) {
    if (sick_beats_process_cue(info, anim_fork_hit_virus, &s_f_virus_hit_seqData)) {
        sick_beats_set_next_doctor_state(SICK_BEATS_DOCTOR_STATE_HITONE);
        if (gSickBeats->doctorNextState == SICK_BEATS_DOCTOR_STATE_HITCONSECUTIVE) {
            sick_beats_add_score(5);
            sick_beats_process_x_particles(7);
        } else {
            sick_beats_add_score(2);
            sick_beats_process_x_particles(5);
        }
    }
}

// Cue - Barely
void sick_beats_cue_barely(struct Cue *cue, struct SickBeatsCue *info, u32 pressed, u32 released) {
    if (sick_beats_process_cue(info, (gameplay_get_last_hit_offset() < 0) ? anim_fork_hit_early : anim_fork_hit_late, &s_f_virus_osii_seqData)) {
        sick_beats_add_score(1);
        sick_beats_process_x_particles(2);
    }
}

// Cue - Miss
void sick_beats_cue_miss(struct Cue *cue, struct SickBeatsCue *info) {
    // Anything but the last dash will be ignored 
    if (info->virusState != SICK_BEATS_VIRUS_STATE_RIGHT_DASH_VULN) { 
        gameplay_ignore_this_cue_result();
    }
    switch (info->virusState) {
        case SICK_BEATS_VIRUS_STATE_RIGHT_DASH_VULN:
        case SICK_BEATS_VIRUS_STATE_LEFT_DASH_VULN:
        case SICK_BEATS_VIRUS_STATE_UP_DASH_VULN:
        case SICK_BEATS_VIRUS_STATE_DOWN_DASH_VULN:
            if (!info->unk0_b5) {
                info->unk0_b5 = TRUE;
                affine_sprite_set_visible(info->virusSprite, 1);
            }
            break;
    }
}

// Input Event
void sick_beats_input_event(u32 pressed, u32 released) {
    s32 posY;
    s32 rotation;
    s32 posX;
    struct AffineSprite *forkSprite;
    
    if (pressed & DPAD_UP) {
        posX = 104;
        posY = 16;
        rotation = INT_TO_FIXED(-2);
        sick_beats_set_fork_counter(DPAD_UP);
    } else if (pressed & DPAD_DOWN) {
        posX = 104;
        posY = 104;
        rotation = INT_TO_FIXED(2);
        sick_beats_set_fork_counter(DPAD_DOWN);
    } else if (pressed & DPAD_LEFT) {
        posX = 32;
        posY = 60;
        rotation = INT_TO_FIXED(4);
        sick_beats_set_fork_counter(DPAD_LEFT);
    } else if (pressed & DPAD_RIGHT) {
        posX = 176;
        posY = 60;
        rotation = INT_TO_FIXED(0);
        sick_beats_set_fork_counter(DPAD_RIGHT);
    }
    forkSprite = create_affine_sprite(anim_fork_hit_none1, 0, posX, posY, 0x8800, INT_TO_FIXED(1), rotation, 1, 0x7f, 4, 1);
    if (forkSprite) {
        affine_sprite_set_callback(forkSprite, sick_beats_fork_callback, (u32)forkSprite);
    }
    gameplay_add_cue_result(0, 3, 0);
    play_sound(&s_virus_fork_seqData);
}

// Common Event 0 (Beat Animation)
void sick_beats_common_beat_animation(void) {
    struct SickBeatsYellowMicrobe *yellowMicrobe = &gSickBeats->yellowMicrobe;
    
    if (gSickBeats->unk1F2 == 0) {
        sprite_set_anim(gSpriteHandler, gSickBeats->doctorSprite, sick_beats_doctor_anim[gSickBeats->doctorCurrentState], 0, 1, 0x7f, 0);
    }
    gSickBeats->unk1F2++;
    if (gSickBeats->unk1F2 >= D_089e92f0[gSickBeats->doctorCurrentState]) {
        gSickBeats->doctorCurrentState = SICK_BEATS_DOCTOR_STATE_BEAT;
        sick_beats_set_next_doctor_state(SICK_BEATS_DOCTOR_STATE_BEAT);
    }
    gSickBeats->doctorBeatCounter = ticks_to_frames(12);
    if (yellowMicrobe->state == SICK_BEATS_MICROBE_STATE_BEAT) {
        sprite_set_anim_cel(gSpriteHandler, yellowMicrobe->sprite, 0);
    }
    sprite_set_anim_cel(gSpriteHandler, gSickBeats->radioSprite, 1);
}

// Common Event 1 (Display Text, Unimplemented)
void sick_beats_common_display_text(void) {

}
