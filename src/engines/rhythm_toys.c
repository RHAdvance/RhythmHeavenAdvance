#include "engines/rhythm_toys.h"
#include "src/code_080092cc.h"

// For readability.
#define gRhythmToys ((struct RhythmToysEngineData *)gCurrentEngineData)


/* RHYTHM TOYS */


// Cat Machine Play Func.
void rhythm_toys_cat_machine_play(u32 button) {
    struct DrumTechNote *sequence;
    
    if (gRhythmToys->buttonTimers[button] != 0) {
        sequence = cat_machine_2_drum_seq_table[button];
    } else {
        sequence = cat_machine_1_drum_seq_table[button];
    }

    play_drumtech_seq(sequence, 0, 0);
    gRhythmToys->soundPlayer = play_sound_in_player(0, cat_machine_meow_sfx_table[button]);
}

// Rap Machine Play Func.
void rhythm_toys_rap_machine_play(u32 button) {
    stop_sound(&s_rap_15ji_desuka_seqData);
    stop_sound(&s_rap_oyatu_desuka_seqData);
    stop_sound(&s_rap_wakari_desuka_seqData);
    stop_sound(&s_rap_oisi_kamone_seqData);
    stop_sound(&s_rap_herusi_kamone_seqData);
    stop_sound(&s_rap_soremoso_kamone_seqData);
    stop_sound(&s_rap_tanosi_kamone_seqData);
    stop_sound(&s_rap_oyatuha_saiko_seqData);
    stop_sound(&s_rap_kibunha_saiko_seqData);
    stop_sound(&s_rap_orette_saiko_seqData);
    stop_sound(&s_rap_kimitte_saiko_seqData);

    if (gRhythmToys->changeRapMachineSfxTableTimer == 0) {
        gRhythmToys->rapMachineSfxTable = agb_random(4);
    }

    gRhythmToys->changeRapMachineSfxTableTimer = ticks_to_frames(0x24);
    gRhythmToys->soundPlayer = play_sound(rap_machine_sfx_pool[gRhythmToys->rapMachineSfxTable][button]);

    if (button == RHYTHM_TOYS_DOWN_BUTTON) {
        if (gRhythmToys->musicPlaying) {
            rhythm_toys_stop_music();
        } else {
            if (gRhythmToys->playAltRapMachineSong) {
                rhythm_toys_play_music(&s_rap_machine_bgm_seqData);
                D_030053c0.musicTrkVolume = 0;
                D_030053c0.musicTrkTargets = 0;
            } else {
                rhythm_toys_play_music(&s_rap_bgm_seqData);
                D_030053c0.musicTrkVolume = 0;
                D_030053c0.musicTrkTargets = -23;
            }

            gRhythmToys->playAltRapMachineSong ^= 1;
        }
    }
}

// Confession Machine Play Func.
void rhythm_toys_love_machine_play(u32 button) {
    if (gRhythmToys->soundPlayer != NULL) {
        fade_out_soundplayer(gRhythmToys->soundPlayer, 0x1e);
    }
    
    gRhythmToys->soundPlayer = scene_play_random_sound(love_machine_sfx_table[button]);
}

// Get Sprite Animation
struct Animation* rhythm_toys_get_sprite_anim(u32 sprite) {
    return rhythm_toys_sprite_table[sprite][gRhythmToys->version].anim;
}

// Get Sprite X
u16 rhythm_toys_get_sprite_x(u32 sprite) {
    struct Vector2 *vec2 = rhythm_toys_sprite_table[sprite][gRhythmToys->version].vec2;
    return vec2->x;
}

// Get Sprite Y
u16 rhythm_toys_get_sprite_y(u32 sprite) {
    struct Vector2 *vec2 = rhythm_toys_sprite_table[sprite][gRhythmToys->version].vec2;
    return vec2->y;
}

// Init. Demo
void rhythm_toys_init_demo(void) {
    gRhythmToys->hasNoDemo = rhythm_toys_demo_table[gRhythmToys->version] == NULL;
    gRhythmToys->demoSprite = sprite_create(gSpriteHandler, 
        rhythm_toys_get_sprite_anim(RHYTHM_TOYS_SPRITE_DEMO_ICON), 0, 
        rhythm_toys_get_sprite_x(RHYTHM_TOYS_SPRITE_DEMO_ICON), 
        rhythm_toys_get_sprite_y(RHYTHM_TOYS_SPRITE_DEMO_ICON), 
        0x800, 0, 0, 0
    );

    gRhythmToys->demoEnabled = FALSE;

    if (gRhythmToys->hasNoDemo) {
        sprite_set_visible(gSpriteHandler, gRhythmToys->demoSprite, FALSE);
    }
}

// Toggle Demo
void rhythm_toys_toggle_demo(u32 currentMachine) {
    if (gRhythmToys->hasNoDemo == 0) {
        if (gRhythmToys->demoEnabled) {
            rhythm_toys_end_demo();
        }

        sprite_set_playback(gSpriteHandler, gRhythmToys->demoSprite, 1, 0, 0);
        sprite_set_anim_cel(gSpriteHandler, gRhythmToys->demoSprite, 1);

        gRhythmToys->demoEnabled = TRUE;

        gRhythmToys->currentDemoAction = rhythm_toys_demo_table[currentMachine];
        gRhythmToys->demoDeltaTime = 0;
        rhythm_toys_stop_music();
    }
}

// End Demo
void rhythm_toys_end_demo(void) {
    if (gRhythmToys->hasNoDemo == 0 && gRhythmToys->demoEnabled) {
        sprite_set_playback(gSpriteHandler, gRhythmToys->demoSprite, 0, 0, 0);
        sprite_set_anim_cel(gSpriteHandler, gRhythmToys->demoSprite, 0);
        stop_drumtech();
        gRhythmToys->demoEnabled = FALSE;
        rhythm_toys_stop_music();
    }
}

// Update Demo
void rhythm_toys_update_demo(void) {
    u16 button;

    if (gRhythmToys->hasNoDemo == 0 && gRhythmToys->demoEnabled) {
        gRhythmToys->demoDeltaTime -= func_0800c398();

        while (gRhythmToys->demoDeltaTime < 0) {
            button = gRhythmToys->currentDemoAction->button;
            
            if (button == (u16)RHYTHM_TOYS_DEMO_STOP) {
                rhythm_toys_end_demo();
                return;
            }

            if (button < RHYTHM_TOYS_DEMO_REST) {
                rhythm_toys_button_press(button);
            }

            gRhythmToys->demoDeltaTime += (gRhythmToys->currentDemoAction->deltaTime) * 0x100;
            gRhythmToys->currentDemoAction++;
        }
    }
}

// Graphics Init. 3
void rhythm_toys_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

// Graphics Init. 2
void rhythm_toys_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), rhythm_toys_gfx_tables[gRhythmToys->version], 0x2000);
    run_func_after_task(task, rhythm_toys_init_gfx3, 0);
}

// Graphics Init. 1
void rhythm_toys_init_gfx1(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), rhythm_toys_buffered_textures);
    run_func_after_task(task, rhythm_toys_init_gfx2, 0);
}

// Game Engine Start
void rhythm_toys_engine_start(u32 version) {
    u32 i;
    s16 sprite;
    
    gRhythmToys->version = version;

    set_beatscript_tempo(*rhythm_toys_demo_bpm_table[version]);
    rhythm_toys_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 1);
    
    gRhythmToys->characterSpriteR = sprite_create(gSpriteHandler, 
        rhythm_toys_get_sprite_anim(RHYTHM_TOYS_SPRITE_MACHINE_R), 0x7f,    
        rhythm_toys_get_sprite_x(RHYTHM_TOYS_SPRITE_MACHINE_R),
        rhythm_toys_get_sprite_y(RHYTHM_TOYS_SPRITE_MACHINE_R),
        0x800, 1, 0x7f, 0
    );

    if (version == ENGINE_VER_RAP_MACHINE) {
        gRhythmToys->characterSpriteL = sprite_create(gSpriteHandler, 
            rhythm_toys_get_sprite_anim(RHYTHM_TOYS_SPRITE_MACHINE_L), 0x7f,
            rhythm_toys_get_sprite_x(RHYTHM_TOYS_SPRITE_MACHINE_L),
            rhythm_toys_get_sprite_y(RHYTHM_TOYS_SPRITE_MACHINE_L),
            0x7ff, 1, 0x7f, 0
        );
    } else {
        gRhythmToys->characterSpriteL = gRhythmToys->characterSpriteR;
    }

    init_drumtech(&gRhythmToys->drumtech);

    for (i = 0; i < 6; i++) {
        gRhythmToys->buttonTimers[i] = 0;
    }

    gameplay_set_input_buttons(0, 0);

    for (i = 0; i < 6; i++) {
        gRhythmToys->buttonSprites[i] = sprite_create(gSpriteHandler,
            rhythm_toys_get_sprite_anim(rhythm_toys_button_anim_ids[i]), 0x7f,
            rhythm_toys_get_sprite_x(rhythm_toys_button_anim_ids[i]),
            rhythm_toys_get_sprite_y(rhythm_toys_button_anim_ids[i]),
            0x700, 1, 0x7f, 0
        );
    }

    gameplay_prevent_dpad_overlap(FALSE);
    rhythm_toys_init_demo();

    gRhythmToys->updateDisabled = FALSE;
    gRhythmToys->musicPlaying = FALSE;
    gRhythmToys->soundPlayer = NULL;
    gRhythmToys->changeRapMachineSfxTableTimer = 0;
    gRhythmToys->playAltRapMachineSong = FALSE;
    gRhythmToys->rapMachineSfxTable = agb_random(4);
}

// Engine Event 0x00 (Stub)
void rhythm_toys_engine_event_stub(void) {
}

// Reset Button Timer
void rhythm_toys_reset_button_timer(u32 button) {
    gRhythmToys->buttonTimers[button] = clamp_int32(ticks_to_frames(6) - 2, 0, 10);
}

// Press Button
void rhythm_toys_button_press(s32 button) {
    s16 sprite;
    
    if (RHYTHM_TOYS_DEMO_STOP < button) {
        if (button < RHYTHM_TOYS_UP_BUTTON) {
            sprite = gRhythmToys->characterSpriteR;
        } else {
            sprite = gRhythmToys->characterSpriteL;
        }

        sprite_set_anim(gSpriteHandler, sprite, rhythm_toys_get_sprite_anim(rhythm_toys_machine_anim_ids[button]), 0, 1, 0x7f, 0);
        sprite_set_anim_cel(gSpriteHandler, gRhythmToys->buttonSprites[button], 0);   
        rhythm_toys_play_func_table[gRhythmToys->version](button);
    }
}

// Play Music
void rhythm_toys_play_music(struct SongHeader *song) {
    scene_set_music(song);
    gRhythmToys->musicPlaying = TRUE;
}

// Stop Music
void rhythm_toys_stop_music(void) {
    scene_stop_music();
    gRhythmToys->musicPlaying = FALSE;
}

// Game Engine Update
void rhythm_toys_engine_update(void) {
    u32 i;
    s32 button;
    
    if (gRhythmToys->updateDisabled == FALSE) {
        set_drumtech_note_func(rhythm_toys_reset_button_timer);

        for (i = 0; i < 6; i++) {
            if (gRhythmToys->buttonTimers[i] != 0) {
                gRhythmToys->buttonTimers[i]--;
            }
        }

        if (gRhythmToys->demoEnabled) {
            rhythm_toys_update_demo();
            
            if (D_03004afc & START_BUTTON) {
                rhythm_toys_end_demo();
            }
        } else {
            button = RHYTHM_TOYS_DEMO_STOP;

            if (D_03004afc & DPAD_RIGHT) {
                button = RHYTHM_TOYS_RIGHT_BUTTON;
            }

            if (D_03004afc & DPAD_UP) {
                button = RHYTHM_TOYS_UP_BUTTON;
            }
            
            if (D_03004afc & DPAD_DOWN) {
                button = RHYTHM_TOYS_DOWN_BUTTON;
            }

            if (D_03004afc & DPAD_LEFT) {
                button = RHYTHM_TOYS_LEFT_BUTTON;
            }

            if (D_03004afc & B_BUTTON) {
                button = RHYTHM_TOYS_B_BUTTON;
            }

            if (D_03004afc & A_BUTTON) {
                button = RHYTHM_TOYS_A_BUTTON;
            }

            rhythm_toys_button_press(button);

            if (D_03004afc & START_BUTTON) {
                rhythm_toys_toggle_demo(gRhythmToys->version);
            }
        }

        update_drumtech();

        if (D_03004afc & SELECT_BUTTON) {
            stop_drumtech();
            beatscript_disable_loops();

            gRhythmToys->updateDisabled = TRUE;

            if (gRhythmToys->soundPlayer != NULL) {
                fade_out_soundplayer(gRhythmToys->soundPlayer, 10);
            }

            play_sound(&s_menu_cancel2_seqData);
            rumble_play_menu_cancel();
        }

        if (gRhythmToys->changeRapMachineSfxTableTimer) {
            gRhythmToys->changeRapMachineSfxTableTimer--;
        }
    }
}

// Game Engine Stop
void rhythm_toys_engine_stop(void) {
}

// Cue - Spawn
void rhythm_toys_cue_spawn(struct Cue *cue, struct RhythmToysCue *info, u32 param) {
}

// Cue - Update
u32 rhythm_toys_cue_update(struct Cue *cue, struct RhythmToysCue *info, u32 runningTime, u32 released) {
    if (runningTime > ticks_to_frames(0x78)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Cue - Despawn
void rhythm_toys_cue_despawn(struct Cue *cue, struct RhythmToysCue *info) {
}

// Cue - Hit
void rhythm_toys_cue_hit(struct Cue *cue, struct RhythmToysCue *info, u32 pressed, u32 released) {
}

// Cue - Barely
void rhythm_toys_cue_barely(struct Cue *cue, struct RhythmToysCue *info, u32 pressed, u32 released) {
}

// Cue - Miss
void rhythm_toys_cue_miss(struct Cue *cue, struct RhythmToysCue *info) {
}

// Input Event
void rhythm_toys_input_event(u32 pressed, u32 released) {
}

// Common Event 0 (Beat Animation, Unimplemented)
void rhythm_toys_common_beat_animation(void) {
}

// Common Event 1 (Display Text, Unimplemented)
void rhythm_toys_common_display_text(void) {
}

// Common Event 2 (Init. Tutorial, Unimplemented)
void rhythm_toys_common_init_tutorial(void) {
}
