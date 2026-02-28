#include "global.h"
#include "gameplay.h"
#include "graphics/gameplay/gameplay_graphics.h"

asm(".include \"include/gba.inc\"");//Temporary


// For readability.
#define gGameplay ((struct GameplaySceneData *)gCurrentSceneData)

#define PAUSE_MENU_PALETTE_MOD 0x3DEF3DEF // Equivalent to RGB #7F7F7F

enum PauseMenuOptionsEnum {
    PAUSE_OPTION_CONTINUE,
    PAUSE_OPTION_QUIT
};

extern const struct Beatscript D_089cfda4[]; // Generic Fade-Out Sequence

extern u8 sReplayingCampaign;

/* MAIN GAMEPLAY SCENE */


static struct Scene *D_03001328; // Pause Menu Quit Destination


// [func_08016e04] Set Sound Effect Original Tempo
void gameplay_set_sound_tempo(u32 tempo) {
    gGameplay->sfxTempo = tempo;
}


// [func_08016e18] Match SoundPlayer to Current Tempo
struct SoundPlayer *gameplay_align_soundplayer_to_tempo(struct SoundPlayer *player) {
    u16 tempo = gGameplay->sfxTempo;

    if (tempo != 0) {
        set_soundplayer_speed(player, Div(INT_TO_FIXED(get_beatscript_tempo()), tempo));
    }

    return player;
}


// [func_08016e54] Play Sound
struct SoundPlayer *gameplay_play_sound(struct SongHeader *sfx) {
    return gameplay_align_soundplayer_to_tempo(play_sound(sfx));
}


// [func_08016e64] Play Sound
struct SoundPlayer *gameplay_play_sound_in_player(u32 player, struct SongHeader *sfx) {
    return gameplay_align_soundplayer_to_tempo(play_sound_in_player(player, sfx));
}


// [func_08016e74] Play Sound
struct SoundPlayer *gameplay_play_sound_w_pitch_volume(struct SongHeader *sfx, u32 volume, u32 pitch) {
    return gameplay_align_soundplayer_to_tempo(play_sound_w_pitch_volume(sfx, volume, pitch));
}


// [func_08016e84] Play Sound
struct SoundPlayer *gameplay_play_sound_in_player_w_pitch_volume(u32 player, struct SongHeader *sfx, u32 volume, s32 pitch) {
    return gameplay_align_soundplayer_to_tempo(play_sound_in_player_w_pitch_volume(player, sfx, volume, pitch));
}


// [func_08016e94] Initialise Static Variables
void gameplay_init_scene_static_var(void) {
    gameplay_pause_menu_set_quit_destination(&scene_debug_menu);
}


// [func_08016ea4] Graphics Init. 1
void gameplay_init_gfx1(void) {
    u32 data;

    data = start_new_texture_loader(0, gameplay_common_buffered_textures);
    run_func_after_task(data, set_pause_beatscript_scene, FALSE);
}


// [func_08016ec4] Scene Start
void gameplay_start_scene(void) {
    func_08002e78(gameplay_common_gfx_table);
    func_08007324(FALSE);
    func_080073f0();
    gameplay_init_overlay();
    gameplay_init_pause_menu();
    gameplay_set_text_printer(NULL);
    gGameplay->gameEngine = NULL;
    gameplay_init_cues();
    results_enable_input_tracking(FALSE);
    results_init_score_handler();
    gGameplay->mercyEnabled = TRUE;
    gGameplay->forgivableMisses = 0;
    gGameplay->playInputsEnabled = FALSE;
    gGameplay->buttonPressFilter = 0;
    gGameplay->buttonReleaseFilter = 0;
    gGameplay->assessIrrelevantInputs = TRUE;
    gGameplay->unk64 = 0;
    gGameplay->isTutorial = FALSE;
    gGameplay->skippingTutorial = FALSE;
    gGameplay->skipDestination = NULL;
    gGameplay->skipTutorialButton = SELECT_BUTTON;
    gGameplay->fadeInTicks = 0x10;
    gGameplay->allowCueInputOverlap = FALSE;
    gGameplay->loopCounterStart = 0;
    gGameplay->goingForPerfect = FALSE;
    gGameplay->assessPerfectInputs = TRUE;
    gGameplay->perfectFailed = FALSE;
    gGameplay->missPunishmentTimer = 0;
    gGameplay->missPunishmentInterval = 0x0C;
    gGameplay->dpadCannotOverlap = TRUE;
    gGameplay->dpadIsOpen = TRUE;
    gGameplay->earlinessRangeMax = -1;
    gGameplay->latenessRangeMin = 1;
    gGameplay->earlinessRangeMin = -0x80;
    gGameplay->latenessRangeMax = 0x7f;
    gGameplay->autoplayEnabled = FALSE;
    midi_player_set_reverb(35, 2, 2, 4);
    if (get_current_scene_trans_target() == NULL) {
        set_next_scene(&scene_results_ver_rank);
    }
    score_results_set_grade_thresholds(NULL);
}


// [func_08016ffc] Scene Update Frozen
void gameplay_update_paused_scene(void) {
}


// [func_08017000] Scene Update
void gameplay_update_scene(void) {
    u32 pressed, released, buttonsOnly;

    if (gGameplay->skippingTutorial) return;

    if (gGameplay->gameEngine != NULL) {
        if (gGameplay->gameEngine->updateFunc != NULL) {
            gGameplay->gameEngine->updateFunc();
        }
    }

    // if L and R are held then enable auto play else disable auto play
    #ifdef AUTOPLAY
    if ((D_03004ac0 & (LEFT_SHOULDER_BUTTON | RIGHT_SHOULDER_BUTTON)) == (LEFT_SHOULDER_BUTTON | RIGHT_SHOULDER_BUTTON)) {
        gGameplay->autoplayEnabled = TRUE;
    } else {
        gGameplay->autoplayEnabled = FALSE;
    }
    #endif

    if(gGameplay->autoplayEnabled){
        struct Cue *cue = gGameplay->cues;
        while (cue != NULL) {
            struct CueDefinition *cueDef = &cue->data;
            s32 runningTime = cue->runningTime;
            s32 duration = cue->duration;
            if (!cue->unk48_b0 && !cue->hasExpired && runningTime == duration) {
                u16 input = (cueDef->buttonFilter & 0x8000) ? 0 : cueDef->buttonFilter;
                u16 release = (cueDef->buttonFilter & 0x8000) ? cueDef->buttonFilter : 0;

                // ok so checks if there are multiple buttons
                // and if there is then only keep the lowest button
                // (else it registers as a miss for the... wrong button... thanks drum lessons!)
                if (input & (input - 1)) {
                    input &= (u16)(0 - input);
                }
                if (release & (release - 1)) {
                    release &= (u16)(0 - release);
                }
                
                if (gameplay_inputs_are_enabled()) { // if play inputs are enabled
                    if ((input != 0) || (release != 0)) {
                        gameplay_update_inputs(input, release); // Update Inputs
                    }
                }
            }
            cue = cue->prev;
        }
    } else {
        pressed = D_03004afc & gGameplay->buttonPressFilter;
        released = D_03004b00 & gGameplay->buttonReleaseFilter;

        if (gGameplay->dpadCannotOverlap == TRUE) {
            if (gGameplay->dpadIsOpen) {
                if (pressed & DPAD_ALL) {
                    buttonsOnly = pressed & ~DPAD_ALL;
                    if (pressed & DPAD_UP) {
                        pressed = DPAD_UP;
                    }
                    if (pressed & DPAD_DOWN) {
                        pressed = DPAD_DOWN;
                    }
                    if (pressed & DPAD_LEFT) {
                        pressed = DPAD_LEFT;
                    }
                    if (pressed & DPAD_RIGHT) {
                        pressed = DPAD_RIGHT;
                    }
                    pressed |= buttonsOnly;
                    gGameplay->dpadIsOpen = FALSE;
                    gGameplay->dpadClosedTimer = 10;
                }
            } else {
                pressed &= ~DPAD_ALL;
                if (D_03004ac0 & DPAD_ALL) {
                    if (--gGameplay->dpadClosedTimer == 0) {
                        gGameplay->dpadIsOpen = TRUE;
                    }
                } else {
                    gGameplay->dpadIsOpen = TRUE;
                }
            }
        }


        if (gameplay_inputs_are_enabled()) { // if play inputs are enabled
            if ((pressed != 0) || (released != 0)) {
                gameplay_update_inputs(pressed, released); // Update Inputs
            }
        }
    }

    gameplay_update_all_cues(); // Update Cues
    gameplay_update_text(); // Update Text

    if (gGameplay->missPunishmentTimer != 0) {
        gGameplay->missPunishmentTimer--;
    }

    if (D_03004afc & gGameplay->skipTutorialButton) {
        if (gGameplay->isTutorial) {
            gameplay_skip_tutorial(); // Skip Tutorial
        }
    }
}


// [func_0801714c] Check if Play Inputs are Enabled
u32 gameplay_inputs_are_enabled(void) {
    if (gGameplay->playInputsEnabled) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// [func_08017168] Clear Secondary Palette Buffer
void gameplay_clear_palette_buffer(Palette buffer) {
    dma3_fill(0, buffer, 0x3E0, 0x20, 0x200);
}


// [func_08017188] Load New Engine
void gameplay_set_current_engine(const struct GameEngine *engine, u32 version) {
    const struct GameEngine *temp = engine;
    u32 i;
    void (*func)();

    if (gGameplay->gameEngine != NULL) {
        gameplay_reset_cues();
        gameplay_enable_cue_spawning(TRUE);
        func = gGameplay->gameEngine->closeFunc;
        if (func != NULL) {
            func(gGameplay->gameEngine);
        }
        if (gGameplay->gameEngineData != NULL) {
            mem_heap_dealloc(gGameplay->gameEngineData);
        }
        sprite_id_delete(gSpriteHandler, get_current_mem_id());
        func_0800222c(get_current_mem_id());
        task_pool_force_cancel_id(get_current_mem_id());
        mem_heap_dealloc_with_id(get_current_mem_id());
        gameplay_set_text_printer(NULL);
    }

    scene_set_video_mode(0);
    scene_hide_bg_layer(BG_LAYER_0);
    scene_hide_bg_layer(BG_LAYER_1);
    scene_hide_bg_layer(BG_LAYER_2);
    scene_hide_bg_layer(BG_LAYER_3);
    func_08004058();
    func_08007344(gameplay_clear_palette_buffer);
    gameplay_prevent_dpad_overlap(TRUE);
    gGameplay->sfxTempo = 0;
    gGameplay->gameEngine = engine;

    if (engine == NULL) {
        return;
    }

    if (engine->gameDataSize > 0) {
        gGameplay->gameEngineData = mem_heap_alloc(engine->gameDataSize);
        dma3_fill(0, gGameplay->gameEngineData, engine->gameDataSize, 0x20, 0x200);
    } else {
        gGameplay->gameEngineData = NULL;
    }
    gCurrentEngineData = gGameplay->gameEngineData;
    
    for (i = 0; i < 12; i++) {
        gGameplay->cueDefinitions[i] = NULL;
    }

    for (i = 0; (i < 12) && (engine->cueDefinitions[i] != (void *)-1); i++) {
        gGameplay->cueDefinitions[i] = engine->cueDefinitions[i];
    }

    for (i = 0; i < 3; i++) {
        gGameplay->commonFunctions[i] = NULL;
    }

    for (i = 0; (i < 3) && (engine->commonFunctions[i] != (void *)-1); i++) {
        gGameplay->commonFunctions[i] = engine->commonFunctions[i];
    }

    temp = engine;
    func = temp->initFunc;
    if (func != NULL) {
        func(version);
    }
}


// [func_0801732c] Get Current Game Engine Data
void *gameplay_get_engine_data(void) {
    return gGameplay->gameEngineData;
}


// [func_08017338] Set Input Button Filters
void gameplay_set_input_buttons(u16 press, u16 release) {
    gGameplay->buttonPressFilter = press;
    gGameplay->buttonReleaseFilter = release;
}


// [func_08017348] Run Engine-Common Event
s32 gameplay_run_common_event(s32 param, s32 id) {
    s32 returnVal = 0;
    EngineEvent *functions = gGameplay->commonFunctions;

    if (functions == NULL) { // literally never possible
        return returnVal;
    }

    if (functions[id] != NULL) {
        // Engine events usually return void, but this code gets the return value
        // even if it's garbage data.
        s32 (*commonFunc)() = (void *)functions[id];
        returnVal = commonFunc(param);
    }

    return returnVal;
}


// [func_08017380] Set Parameter for Engine-Specific Event
void gameplay_set_engine_event_param(s32 param) {
    gGameplay->engineFuncParam = param;
}


// [func_0801738c] Run Engine-Specific Event
s32 gameplay_run_engine_event(const struct GameEngine *engine, s32 id) {
    s32 returnVal = 0;

    if (gGameplay->gameEngine != engine) {
        return returnVal;
    }

    if ((gGameplay->gameEngine->engineFunctions != NULL) && (gGameplay->gameEngine->engineFunctions[id] != NULL)) {
        // Engine events usually return void, but this code gets the return value
        // even if it's garbage data.
        s32 (*engineFunc)() = (void *)gGameplay->gameEngine->engineFunctions[id];
        returnVal = engineFunc(gGameplay->engineFuncParam);
    }

    return returnVal;
}


// [func_080173c4] Enable Play Inputs
void gameplay_inputs_enabled(u32 enable) {
    gGameplay->playInputsEnabled = enable;
}


// [func_080173d0] Assess Non-Cue Inputs
void gameplay_assess_irrelevant_inputs(u32 arg) {
    gGameplay->assessIrrelevantInputs = arg;
}


// [func_080173dc] Set Next Cue Spawn SFX
void gameplay_set_next_cue_spawn_sfx(struct SongHeader *sfx) {
    gGameplay->nextCueSpawnSfx = sfx;
}


// [func_080173e8] Set Next Cue Hit SFX
void gameplay_set_next_cue_hit_sfx(struct SongHeader *sfx) {
    gGameplay->nextCueHitSfx = sfx;
}


// [func_080173f4] Set Next Cue Barely SFX
void gameplay_set_next_cue_barely_sfx(struct SongHeader *sfx) {
    gGameplay->nextCueBarelySfx = sfx;
}


// [func_08017400] Set Next Cue Miss SFX
void gameplay_set_next_cue_miss_sfx(struct SongHeader *sfx) {
    gGameplay->nextCueMissSfx = sfx;
}


// [func_0801740c] Force-Stop Music MIDI Track
void gameplay_force_stop_music_midi_track(s32 midiTrack) {
    struct SoundPlayer *soundPlayer = D_030053c0.musicPlayer;

    if ((soundPlayer == NULL) || (midiTrack < 0)) return;

    soundPlayer->midiReader[midiTrack].active = FALSE;
    soundPlayer->midiReader[midiTrack].activeAtLoop = FALSE;
}


// [func_08017448] Set isTutorial
void gameplay_enable_tutorial(u32 isTutorial) {
    gGameplay->isTutorial = isTutorial;
}


// [func_08017458] Set skipDestination
void gameplay_set_skip_destination(struct Scene *scene) {
    gGameplay->skipDestination = scene;
}


// [func_08017468] Set Skip Tutorial Button
void gameplay_set_skip_button(u32 buttons) {
    gGameplay->skipTutorialButton = buttons;
}


// [func_0801747c] Set Skip Destination
void gameplay_set_tutorial(struct Scene *scene) {
    if (scene != NULL) {
        gameplay_enable_tutorial(TRUE);
        gameplay_set_skip_destination(scene);
        sprite_set_visible(gSpriteHandler, gGameplay->skipTutorialSprite, TRUE);
    } else {
        gameplay_enable_tutorial(FALSE);
        gameplay_set_skip_destination(NULL);
        sprite_set_visible(gSpriteHandler, gGameplay->skipTutorialSprite, FALSE);
    }
}


// [func_080174e8] Display Skip Tutorial Icon
void gameplay_display_skip_icon(u32 corner) {
    sprite_set_anim_cel(gSpriteHandler, gGameplay->skipTutorialSprite, corner);
}


// [func_08017514] Skip Tutorial
void gameplay_skip_tutorial(void) {
    sprite_id_set_enable_updates(gSpriteHandler, get_current_mem_id(), 1);
    task_pool_pause_id(get_current_mem_id(), TRUE);
    set_pause_beatscript_scene(FALSE);
    func_0801d968(D_089cfda4);
    pause_menu_enabled(FALSE);
    gGameplay->skippingTutorial = TRUE;
}


// [func_08017568] Set Screen Fade-In
void gameplay_set_screen_fade_in_time(u32 duration) {
    gGameplay->fadeInTicks = duration;
}


// [func_08017578] Fade-In Screen
void gameplay_start_screen_fade_in(void) {
    if (gGameplay->fadeInTicks != 0) {
        func_0800703c(gGameplay->fadeInTicks, 0);
    }
    func_08007324(TRUE);
    func_08007370();
}


// [func_080175a0] Set initial counter value
void gameplay_set_initial_counter_value(u32 count) {
    gGameplay->loopCounterStart = count;
}


// [func_080175b0] Reset loop counter
void gameplay_reset_loop_counter(void) {
    gGameplay->loopCounter = gGameplay->loopCounterStart;
}


// [func_080175c4] Increment loop counter
void gameplay_increment_loop_counter(void) {
    gGameplay->loopCounter++;
}


// [func_080175d8] Get loop counter
u32 gameplay_get_loop_counter(void) {
    return gGameplay->loopCounter;
}


// [func_080175e8] Set Global Reverb
void gameplay_set_reverb(u32 level) {
    midi_player_set_reverb(clamp_int32(level + 35, 0, 127), 2, 2, 4);
}


// [func_08017604] Start Perfect Campaign
void gameplay_start_perfect_campaign(void) {
    if (get_current_campaign() < 0) {
        return;
    }

    if (!gGameplay->goingForPerfect) {
        gGameplay->goingForPerfect = TRUE;
        sprite_set_visible(gSpriteHandler, gGameplay->perfectSprite, TRUE);
    }
}


// [func_08017648] Start/Stop Assessing Inputs for Perfect Campaign
void gameplay_check_for_perfect(u32 assessInputs) {
    gGameplay->assessPerfectInputs = assessInputs;
}


// [func_0801765c] Register Imperfect Input
void gameplay_register_imperfect_input(void) {
    if (!gGameplay->perfectFailed && gGameplay->goingForPerfect && gGameplay->assessPerfectInputs) {
        sprite_set_anim(gSpriteHandler, gGameplay->perfectSprite, anim_gameplay_perfect_miss, 0, 1, 0, 2);
        play_sound(&s_f_fail_perfect_seqData);
        gGameplay->perfectFailed = TRUE;
    }
}


// [func_080176cc] Register Perfect Input
void gameplay_register_perfect_input(void) {
    if (!gGameplay->perfectFailed && gGameplay->goingForPerfect && gGameplay->assessPerfectInputs) {
        sprite_set_anim(gSpriteHandler, gGameplay->perfectSprite, anim_gameplay_perfect_hit, 0, 1, 0x7f, 0);
    }
}


// [func_08017728] Run Game Engine Event (convenience method)
s32 gameplay_run_engine_event_w_param(const struct GameEngine *engine, u32 function, s32 param) {
    gameplay_set_engine_event_param(param);
    return gameplay_run_engine_event(engine, function);
}


// [func_08017744] Set Miss Punishment Interval
void gameplay_set_miss_punishment_duration(u32 duration) {
    gGameplay->missPunishmentInterval = duration;
}


// [func_08017758] Set Inter-Engine Variable
void gameplay_set_inter_engine_variable(u32 i, s32 val) {
    if (i >= ARRAY_COUNT(gGameplay->interEngineVariableSpace)) {
        return;
    }

    gGameplay->interEngineVariableSpace[i] = val;
}


// [func_0801777c] Get Inter-Engine Variable
s32 gameplay_get_inter_engine_variable(u32 i) {
    if (i >= ARRAY_COUNT(gGameplay->interEngineVariableSpace)) {
        return 0;
    }

    return gGameplay->interEngineVariableSpace[i];
}


// [func_080177a4] Set D-Pad Input Overlap Handling
void gameplay_prevent_dpad_overlap(u32 preventOverlap) {
    gGameplay->dpadCannotOverlap = preventOverlap;
    gGameplay->dpadIsOpen = TRUE;
}


// [func_080177c8] Enable Mercy
void gameplay_enable_mercy(u32 enable) {
    gGameplay->mercyEnabled = enable;
}


// [func_080177dc] Set Total Forgivable Misses
void gameplay_set_mercy_count(u32 total) {
    gGameplay->forgivableMisses = total;
}


// [func_080177f0] Scene Stop
void gameplay_stop_scene(void) {
    struct Scene *tempScene;

    sprite_id_delete(gSpriteHandler, 16);
    gameplay_reset_cues(); // Reset Cues
    if (gGameplay->gameEngine->closeFunc != NULL) {
        gGameplay->gameEngine->closeFunc();
    }
    if (gGameplay->gameEngineData != NULL) {
        mem_heap_dealloc(gGameplay->gameEngineData);
    }
    if (gGameplay->skippingTutorial) {
        if (gGameplay->skipDestination != NULL) {
            tempScene = get_current_scene_trans_target();
            set_next_scene(gGameplay->skipDestination);
            set_scene_trans_target(gGameplay->skipDestination, tempScene);
        }
        stop_all_soundplayers(); // Sound
    } else {
        if (gGameplay->goingForPerfect && !gGameplay->perfectFailed && !sReplayingCampaign) {
            set_next_scene(&scene_perfect);
            set_scene_trans_target(&scene_perfect, get_scene_trans_target(&scene_epilogue));
        }
    }

    func_08008628();
    func_08004058();
    midi_player_set_reverb(35, 2, 2, 4);
}


// [func_080178ac] Reset All Cue Data
void gameplay_reset_cues(void) {
    struct Cue *cue, *prev;

    cue = gGameplay->cues;
    while (cue != NULL) {
        prev = cue->prev;
        gameplay_despawn_cue(cue);
        cue = prev;
    }

    gGameplay->cues = NULL;
    gGameplay->nextCueSpawnSfx = NULL;
    gGameplay->nextCueHitSfx = NULL;
    gGameplay->nextCueBarelySfx = NULL;
    gGameplay->nextCueMissSfx = NULL;
    gGameplay->nextCueDuration = 0;
}


// [func_080178e4] Initialise Cues
void gameplay_init_cues(void) {
    gGameplay->cues = NULL;
    gGameplay->currentCue = NULL;
    gGameplay->cueSpawnsEnabled = TRUE;
    gGameplay->currentMarkingCriteria = 0;
    gameplay_reset_cues();
}


// [func_08017908] Set Current Marking Criteria
void gameplay_set_marking_criteria(u32 criteria) {
    gGameplay->currentMarkingCriteria = criteria;
}


// [func_08017918] Get Current Marking Criteria
u32 gameplay_get_marking_criteria(void) {
    return gGameplay->currentMarkingCriteria;
}


// [func_08017928] Register Cue Result
void gameplay_add_cue_result(u32 markingCriteria, u32 cueResult, s32 timingOffset) {
    u32 noCue = (cueResult == CUE_RESULT_NONE);

    if (!gGameplay->assessIrrelevantInputs && noCue) {
        return;
    }

    // some kind of score-related mercy system or something
    if ((cueResult == CUE_RESULT_MISS) && gGameplay->mercyEnabled && (gGameplay->forgivableMisses != 0)) {
        cueResult = CUE_RESULT_BARELY;
        gGameplay->forgivableMisses--;
    }

    // Results
    results_register_input(0, cueResult, timingOffset);
    if (!noCue) {
        results_register_cue_input(markingCriteria, cueResult, timingOffset);
    }

    // Perfect Campaign
    if (cueResult == CUE_RESULT_HIT) {
        gameplay_register_perfect_input();
    } else if (cueResult < 4) {
        gameplay_register_imperfect_input();
    }
}


// [func_080179a0] Add Input Hit
void gameplay_add_cue_result_hit(s32 offset) {
    gameplay_add_cue_result(gGameplay->currentMarkingCriteria, CUE_RESULT_HIT, offset);
}


// [func_080179bc] Add Input Barely
void gameplay_add_cue_result_barely(s32 offset) {
    gameplay_add_cue_result(gGameplay->currentMarkingCriteria, CUE_RESULT_BARELY, offset);
}


// [func_080179d8] Add Input Miss
void gameplay_add_cue_result_miss(s32 offset) {
    gameplay_add_cue_result(gGameplay->currentMarkingCriteria, CUE_RESULT_MISS, offset);
}


// [func_080179f4] Spawn Cue
void gameplay_spawn_cue(s32 id) {
    const struct CueDefinition *cueDef;
    struct Cue *newCue, *prevCue;

    if ((!gGameplay->cueSpawnsEnabled) || ((cueDef = gGameplay->cueDefinitions[id]) == NULL)) {
        return;
    }

    newCue = mem_heap_alloc(sizeof(struct Cue));
    if (cueDef->cueInfoSize != 0) {
        newCue->gameCueInfo = mem_heap_alloc(cueDef->cueInfoSize);
    } else {
        newCue->gameCueInfo = NULL;
    }
    dma3_set(cueDef, &newCue->data, sizeof(struct CueDefinition), 0x20, 0x200);

    newCue->unk48_b0 = FALSE;
    newCue->hasExpired = FALSE;

    do {} while (0); // fake matching / macro?

    newCue->runningTime = 0;

    if (gGameplay->nextCueDuration != 0) {
        newCue->duration = ticks_to_frames(gGameplay->nextCueDuration);
        gGameplay->nextCueDuration = 0;
    } else {
        newCue->duration = ticks_to_frames(cueDef->duration);
    }

    newCue->spawnSfx  = ((gGameplay->nextCueSpawnSfx != NULL)  ? gGameplay->nextCueSpawnSfx  : cueDef->spawnSfx);
    newCue->hitSfx    = ((gGameplay->nextCueHitSfx != NULL)    ? gGameplay->nextCueHitSfx    : cueDef->hitSfx);
    newCue->barelySfx = ((gGameplay->nextCueBarelySfx != NULL) ? gGameplay->nextCueBarelySfx : cueDef->barelySfx);
    newCue->missSfx   = ((gGameplay->nextCueMissSfx != NULL)   ? gGameplay->nextCueMissSfx   : cueDef->missSfx);

    newCue->markingCriteria = gGameplay->currentMarkingCriteria;

    gGameplay->nextCueSpawnSfx = NULL;
    gGameplay->nextCueHitSfx = NULL;
    gGameplay->nextCueBarelySfx = NULL;
    gGameplay->nextCueMissSfx = NULL;

    prevCue = gGameplay->cues;

    newCue->next = NULL;
    newCue->prev = prevCue;

    if (prevCue != NULL) {
        prevCue->next = newCue;
    }

    gGameplay->cues = newCue;

    gGameplay->cancelThisCueSpawning = FALSE;

    if (cueDef->spawnFunc != NULL) {
        cueDef->spawnFunc(newCue, newCue->gameCueInfo, cueDef->spawnParam);
    }

    if (gGameplay->cancelThisCueSpawning) {
        gGameplay->cues = prevCue;
        prevCue->next = NULL;
        mem_heap_dealloc(newCue);
    } else {
        gGameplay->currentCue = newCue;
        gameplay_play_sound(newCue->spawnSfx);
    }
}


// [func_08017b34] Request Scene to Delete the Currently-Spawning Cue
void gameplay_cancel_this_cue_spawn(void) {
    gGameplay->cancelThisCueSpawning = TRUE;
}


// [func_08017b44] Despawn Cue
void gameplay_despawn_cue(struct Cue *cue) {
    struct Cue *prev, *next;

    if (cue->data.despawnFunc != NULL) {
        cue->data.despawnFunc(cue, cue->gameCueInfo);
    }

    if (cue->gameCueInfo != NULL) {
        mem_heap_dealloc(cue->gameCueInfo);
    }

    next = cue->next;
    prev = cue->prev;

    if (next != NULL) {
        next->prev = prev;
    } else {
        gGameplay->cues = prev;
    }

    if (prev != NULL) {
        prev->next = next;
    }

    mem_heap_dealloc(cue);
}


// [func_08017b88] Enable Cue Spawning
void gameplay_enable_cue_spawning(u32 enable) {
    gGameplay->cueSpawnsEnabled = enable;
}


// [func_08017b98] Update Cue
void gameplay_update_cue(struct Cue *cue) {
    struct CueDefinition *cueDef;
    s32 missTimeOffset;
    u32 hasExpired;

    cueDef = &cue->data;

    cue->runningTime++;
    gGameplay->ignoreThisCueResult = FALSE;
    if (cueDef->tempoDependent) {
        missTimeOffset = ticks_to_frames(cueDef->missWindowLate);
    } else {
        missTimeOffset = cueDef->missWindowLate;
    }
    if (!cue->unk48_b0 && !cue->hasExpired) {
        if (cue->runningTime > cue->duration + missTimeOffset) {
            cue->hasExpired = TRUE;
            if (cueDef->missFunc != NULL) {
                cueDef->missFunc(cue, cue->gameCueInfo);
            }
            if (!gGameplay->ignoreThisCueResult) {
                gameplay_add_cue_result(cue->markingCriteria, CUE_RESULT_MISS, 0);
            }
            gameplay_play_sound(cue->missSfx);
            if (cueDef->deleteWithoutUpdate) { // unused feature! awesome!
                gameplay_despawn_cue(cue); // Despawn Cue
                return;
            }
        }
    }
    if (cueDef->updateFunc != NULL) {
        hasExpired = cueDef->updateFunc(cue, cue->gameCueInfo, cue->runningTime, cue->duration);
        if (hasExpired) {
            if (hasExpired == TRUE) gameplay_despawn_cue(cue); // Despawn Cue
        }
    }
}


// [func_08017c68] Update All Cues
void gameplay_update_all_cues(void) {
    struct Cue *cue, *prev;

    cue = gGameplay->cues;
    while (cue != NULL) {
        prev = cue->prev;
        gameplay_update_cue(cue);
        cue = prev;
    }
}


// [func_08017c8c] Determine Cue Input Timing
s32 gameplay_calculate_input_timing(struct Cue *cue, u16 pressed, u16 released, s32 *offset) {
    struct CueDefinition *cueDef;
    s32 runningTime, duration;
    s32 hitEarly, hitLate, missEarly, missLate;
    u16 input;

    cueDef = &cue->data;
    input = (cueDef->buttonFilter & 0x8000) ? released : pressed;

    if (((input & cueDef->buttonFilter & ~0x8000) == 0) || cue->unk48_b0 || cue->hasExpired) {
        return CUE_TIMING_MISS;
    }

    runningTime = cue->runningTime;
    duration = cue->duration;

    if (cueDef->tempoDependent) { // Used by the Rhythm Test, Mr. Upbeat, and the unused drumming tutorials.
        hitEarly = ticks_to_frames(cueDef->hitWindowEarly);
        hitLate = ticks_to_frames(cueDef->hitWindowLate);
        missEarly = ticks_to_frames(cueDef->missWindowEarly);
        missLate = ticks_to_frames(cueDef->missWindowLate);
    } else {
        hitEarly = cueDef->hitWindowEarly;
        hitLate = cueDef->hitWindowLate;
        missEarly = cueDef->missWindowEarly;
        missLate = cueDef->missWindowLate;
    }

    hitEarly = clamp_int32(hitEarly, gGameplay->earlinessRangeMin, gGameplay->earlinessRangeMax);
    hitLate = clamp_int32(hitLate, gGameplay->latenessRangeMin, gGameplay->latenessRangeMax);
    missEarly = clamp_int32(missEarly, gGameplay->earlinessRangeMin, gGameplay->earlinessRangeMax);
    missLate = clamp_int32(missLate, gGameplay->latenessRangeMin, gGameplay->latenessRangeMax);

    if (gGameplay->missPunishmentTimer != 0) {
        hitEarly = -1;
        hitLate = 1;
    }

    hitEarly += duration;
    hitLate += duration;
    missEarly += duration;
    missLate += duration;

    if ((runningTime < missEarly) || (runningTime > missLate)) {
        return CUE_TIMING_MISS;
    }

    if (cueDef->missCondition != NULL) { // unused feature! cool!
        if (cueDef->missCondition(cue, cue->gameCueInfo)) {
            return CUE_TIMING_MISS;
        }
    }

    *offset = runningTime - duration;
    if ((runningTime >= hitEarly) && (runningTime <= hitLate)) {
        return CUE_TIMING_HIT;
    } else {
        return CUE_TIMING_BARELY;
    }
}


// [func_08017e2c] Hit/Barely Event
void gameplay_register_hit_barely(struct Cue *cue, s32 timingLevel, s32 offset, u32 pressed, u32 released) {
    struct CueDefinition *cueDef = &cue->data;
    CueHitEvent hitEvent;

    gGameplay->ignoreThisCueResult = FALSE;
    cue->unk48_b0 = TRUE;
    gGameplay->lastCueInputOffset = offset;

    if (timingLevel == CUE_TIMING_HIT) {
        hitEvent = cueDef->hitFunc;
        if (hitEvent != NULL) {
            hitEvent(cue, cue->gameCueInfo, pressed, released);
        }
        // RUN_IF_NOT_NULL_B(hitFunc, cue, cue->gameCueInfo, pressed, released);
        // RUN_IF_NOT_NULL(hitFunc, hitFunc(cue, cue->gameCueInfo, pressed, released));
        if (gGameplay->ignoreThisCueResult == FALSE) {
            gameplay_add_cue_result(cue->markingCriteria, 0, offset);
            gameplay_play_sound(cue->hitSfx);
        }
    } else {
        hitEvent = cueDef->barelyFunc;
        if (hitEvent != NULL) {
            hitEvent(cue, cue->gameCueInfo, pressed, released);
        }
        if (gGameplay->ignoreThisCueResult == FALSE) {
            gameplay_add_cue_result(cue->markingCriteria, 1, offset);
            gameplay_play_sound(cue->barelySfx);
        }
    }
}


// [func_08017ec8] Update Inputs
void gameplay_update_inputs(u32 pressed, u32 released) {
    s32 timingOffset, closestCueTimingOffset; // input accuracy offset in ticks
    s32 hitAnyCue, missInput, missedCuesForThisButton; // boolean
    struct Cue *cue, *prev, *closestCue;
    enum CueHitTiming timingLevel, closestCueTimingLevel;
    u32 currentInput, unrelatedInputs; // button combo
    u16 press, release; // button combo
    u32 i;

    hitAnyCue = FALSE;
    missInput = FALSE;
    unrelatedInputs = 0;

    for (i = 0; i < 32; i++) {
        currentInput = (pressed | (released << 16)) & (1 << i);

        if (currentInput == 0) {
            continue;
        }

        press = currentInput;
        release = currentInput >> 16;
        missedCuesForThisButton = TRUE;
        closestCue = NULL;
        closestCueTimingOffset = 9999;
        closestCueTimingLevel = CUE_TIMING_MISS;

        cue = gGameplay->cues;
        while (cue != NULL) {
            prev = cue->prev;
            timingLevel = gameplay_calculate_input_timing(cue, press, release, &timingOffset);
            switch (gGameplay->allowCueInputOverlap) {
                case FALSE: // If cues overlap, only register the closest cue to this input.
                    if (timingLevel != CUE_TIMING_MISS) {
                        if (ABS(timingOffset) < ABS(closestCueTimingOffset)) {
                            closestCue = cue;
                            closestCueTimingOffset = timingOffset;
                            closestCueTimingLevel = timingLevel;
                        }
                        missedCuesForThisButton = FALSE;
                    }
                    break;
                case TRUE: // If cues overlap, register input for all.
                    if (timingLevel != CUE_TIMING_MISS) {
                        gameplay_register_hit_barely(cue, timingLevel, timingOffset, press, release);
                        hitAnyCue = TRUE;
                        missedCuesForThisButton = FALSE;
                    }
                    break;
            }
            cue = prev;
        }

        if (closestCue != NULL) {
            gameplay_register_hit_barely(closestCue, closestCueTimingLevel, closestCueTimingOffset, press, release);
            hitAnyCue = TRUE;
        }

        if (missedCuesForThisButton) {
            unrelatedInputs |= currentInput;
            missInput = TRUE;
        }
        pressed &= gGameplay->buttonPressFilter;
        released &= gGameplay->buttonReleaseFilter;
    }

    if (!hitAnyCue) {
        unrelatedInputs = press | (release << 16);
        missInput = TRUE;
    }

    unrelatedInputs &= gGameplay->buttonPressFilter | (gGameplay->buttonReleaseFilter << 16);

    if (unrelatedInputs == 0) {
        missInput = FALSE;
    }

    if (missInput) {
        gameplay_add_cue_result(0, CUE_RESULT_NONE, 0); // marking criteria, enum, accuracy
        if (gGameplay->gameEngine->inputFunc != NULL) {
            gGameplay->gameEngine->inputFunc(unrelatedInputs & 0xffff, unrelatedInputs >> 16);
        }
        gGameplay->missPunishmentTimer = ticks_to_frames(gGameplay->missPunishmentInterval);
    }
}


// [func_08018054] Get Timing Offset of Most Recent Hit/Barely
s32 gameplay_get_last_hit_offset(void) {
    return gGameplay->lastCueInputOffset;
}

// [func_08018068] Prevent Scene from Updating Results for This Cue
void gameplay_ignore_this_cue_result(void) {
    gGameplay->ignoreThisCueResult = TRUE;
}


// [func_08018078] Allow Cue Input Overlap
void gameplay_enable_cue_input_overlap(u32 allow) {
    gGameplay->allowCueInputOverlap = allow;
}


// [func_08018088] Set Cue Spawn SFX
void gameplay_set_cue_spawn_sfx(struct Cue *cue, struct SongHeader *sfx) {
    cue->spawnSfx = sfx;
}


// [func_0801808c] Set Cue Hit SFX
void gameplay_set_cue_hit_sfx(struct Cue *cue, struct SongHeader *sfx) {
    cue->hitSfx = sfx;
}


// [func_08018090] Set Cue Barely SFX
void gameplay_set_cue_barely_sfx(struct Cue *cue, struct SongHeader *sfx) {
    cue->barelySfx = sfx;
}


// [func_08018094] Set Cue Miss SFX
void gameplay_set_cue_miss_sfx(struct Cue *cue, struct SongHeader *sfx) {
    cue->missSfx = sfx;
}


// [func_08018098] Get Cue Spawn SFX
struct SongHeader *gameplay_get_cue_spawn_sfx(struct Cue *cue) {
    return cue->spawnSfx;
}


// [func_0801809c] Get Cue Hit SFX
struct SongHeader *gameplay_get_cue_hit_sfx(struct Cue *cue) {
    return cue->hitSfx;
}


// [func_080180a0] Get Cue Barely SFX
struct SongHeader *gameplay_get_cue_barely_sfx(struct Cue *cue) {
    return cue->barelySfx;
}


// [func_080180a4] Get Cue Miss SFX
struct SongHeader *gameplay_get_cue_miss_sfx(struct Cue *cue) {
    return cue->missSfx;
}


// [func_080180a8] Get Cue Data unk0
u32 gameplay_get_cue_unk0(struct Cue *cue) {
    return cue->data.unk0;
}


// [func_080180ac] Get Cue Input Buttons
u32 gameplay_get_cue_input_buttons(struct Cue *cue) {
    return cue->data.buttonFilter;
}


// [func_080180b0] Set Cue Input Buttons
void gameplay_set_cue_input_buttons(struct Cue *cue, u32 buttons) {
    cue->data.buttonFilter = buttons;
}


// [func_080180b4] Set Cue Duration
void gameplay_set_cue_duration(struct Cue *cue, u32 duration) {
    cue->duration = duration;
}


// [func_080180bc] Get Cue Marking Criteria
u32 gameplay_get_cue_marking_criteria(struct Cue *cue) {
    return cue->markingCriteria;
}


// [func_080180c4] Set Cue Hit Window
void gameplay_set_cue_hit_window(s32 time) {
    gGameplay->earlinessRangeMax = -time;
    gGameplay->latenessRangeMin = time;
}


// [func_080180ec] Set Cue Barely Window
void gameplay_set_cue_barely_window(s32 time) {
    gGameplay->earlinessRangeMin = -time;
    gGameplay->latenessRangeMax = time;
}


// [func_08018114] Set Next Cue Duration
void gameplay_set_next_cue_duration(u32 duration) {
    gGameplay->nextCueDuration = duration;
}


// [func_08018124] Get Cue and GameCueInfo
void gameplay_get_cue_info(struct Cue **cue, void **info) {
    *cue = gGameplay->cues;
    *info = (*cue)->gameCueInfo;
}

// [func_08018138] Get Previous Cue and GameCueInfo
void gameplay_get_previous_cue_info(struct Cue *cue, struct Cue **prev, void **info) {
    if ((cue != NULL) && (cue->prev != NULL)) {
        *prev = cue->prev;
        *info = (*prev)->gameCueInfo;
    } else {
        *prev = NULL;
        *info = NULL;
    }
}


// [func_08018154] Initialise Common Graphics (Perfect Campaign, etc.)
void gameplay_init_overlay(void) {
    u32 memID;

    memID = sprite_handler_get_mem_id(gSpriteHandler);
    sprite_handler_set_mem_id(gSpriteHandler, 16);
    gGameplay->pauseSprite = sprite_create(gSpriteHandler, anim_gameplay_pause_title, 0, 120, 80, 0, 1, 0, 0x8000);
    gGameplay->pauseOptionsSprite = sprite_create(gSpriteHandler, anim_gameplay_pause_option1, 0, 120, 80, 0, 1, 0, 0x8000);
    gGameplay->skipTutorialSprite = sprite_create(gSpriteHandler, anim_gameplay_skip_icon, 0, 120, 80, 0, 0, 0, 0x8000);
    gGameplay->aButtonSprite = sprite_create(gSpriteHandler, anim_gameplay_text_button_black, 0, 64, 64, 0x64, 1, 0, 0x8000);
    gGameplay->perfectSprite = sprite_create(gSpriteHandler, anim_gameplay_perfect_icon, 0, 230, 10, 0x5A, 1, 0x7f, 0x8000);
    sprite_set_paused(gSpriteHandler, gGameplay->pauseSprite, 1);
    sprite_set_paused(gSpriteHandler, gGameplay->pauseOptionsSprite, 1);
    sprite_id_set_base_tile(gSpriteHandler, 16, 960);
    sprite_id_set_base_palette(gSpriteHandler, 16, 14);
    sprite_handler_set_mem_id(gSpriteHandler, memID);
}


// [func_080182ac] Set D_03001328
void gameplay_pause_menu_set_quit_destination(struct Scene *scene) {
    D_03001328 = scene;
};


// [func_080182b8] Screen Darken (Pause)
void gameplay_pause_menu_darken_screen(void) {
    u32 *palBuf;
    u32 i;

    palBuf = (u32 *)D_03004b10.bgPalette;
    dma3_set(palBuf, &gGameplay->paletteBuffer, sizeof(gGameplay->paletteBuffer), 0x20, 0x200);

    for (i = 0; i < 0x3E; i++, palBuf += 4) {
        palBuf[0] = (palBuf[0] / 2) & PAUSE_MENU_PALETTE_MOD;
        palBuf[1] = (palBuf[1] / 2) & PAUSE_MENU_PALETTE_MOD;
        palBuf[2] = (palBuf[2] / 2) & PAUSE_MENU_PALETTE_MOD;
        palBuf[3] = (palBuf[3] / 2) & PAUSE_MENU_PALETTE_MOD;
    }
}


// [func_08018318] Screen Lighten (Unpause)
void gameplay_pause_menu_lighten_screen(void) {
    dma3_set(&gGameplay->paletteBuffer, D_03004b10.bgPalette, sizeof(D_03004b10.bgPalette) + sizeof(D_03004b10.objPalette), 0x20, 0x200);
}


// [func_08018344] Open Pause Menu
void gameplay_start_pause_menu(void) {
    gGameplay->unpausing = FALSE;
    gGameplay->currentPauseOption = PAUSE_OPTION_CONTINUE;
    sprite_set_anim_cel(gSpriteHandler, gGameplay->pauseSprite, 0);
    sprite_set_anim(gSpriteHandler, gGameplay->pauseOptionsSprite, anim_gameplay_pause_option1, 0, 1, 0, 0);
    sprite_set_visible(gSpriteHandler, gGameplay->pauseSprite, TRUE);
    sprite_set_visible(gSpriteHandler, gGameplay->pauseOptionsSprite, TRUE);
    gameplay_pause_menu_darken_screen();
    play_sound(&s_f_pause_on_seqData);
}


// [func_080183c8] Update Pause Menu
s32 gameplay_update_pause_menu(void) {
    if (!gGameplay->unpausing) {
        if (D_03004afc & DPAD_LEFT) {
            gGameplay->currentPauseOption = PAUSE_OPTION_CONTINUE;
            sprite_set_anim(gSpriteHandler, gGameplay->pauseOptionsSprite, anim_gameplay_pause_option1, 0, 1, 0, 0);
            play_sound(&s_f_pause_cursor_seqData);
        }
        if (D_03004afc & DPAD_RIGHT) {
            gGameplay->currentPauseOption = PAUSE_OPTION_QUIT;
            sprite_set_anim(gSpriteHandler, gGameplay->pauseOptionsSprite, anim_gameplay_pause_option2, 0, 1, 0, 0);
            play_sound(&s_f_pause_cursor_seqData);
        }
        if (D_03004afc & A_BUTTON) {
            sprite_set_visible(gSpriteHandler, gGameplay->pauseSprite, FALSE);
            sprite_set_visible(gSpriteHandler, gGameplay->pauseOptionsSprite, FALSE);
            if (gGameplay->currentPauseOption == PAUSE_OPTION_CONTINUE) {
                gGameplay->unpausing = TRUE;
                play_sound(&s_f_pause_continue_seqData);
                return PAUSE_MENU_SELECTION_PENDING;
            } else {
                gGameplay->perfectFailed = TRUE;
                set_next_scene(D_03001328);
                return PAUSE_MENU_SELECTION_QUIT;
            }
        }
        if (D_03004afc & (B_BUTTON | START_BUTTON)) {
            sprite_set_visible(gSpriteHandler, gGameplay->pauseSprite, FALSE);
            sprite_set_visible(gSpriteHandler, gGameplay->pauseOptionsSprite, FALSE);
            gGameplay->unpausing = TRUE;
            play_sound(&s_f_pause_continue_seqData);
            return PAUSE_MENU_SELECTION_PENDING;
        }
        return PAUSE_MENU_SELECTION_PENDING;
    }

    if (D_03004ac0 & (A_BUTTON | B_BUTTON | START_BUTTON)) {
        return PAUSE_MENU_SELECTION_PENDING;
    }

    gameplay_pause_menu_lighten_screen();
    D_03004b00 = 0;
    return PAUSE_MENU_SELECTION_CONTINUE;
}


// [func_08018524] Initialise Pause Handler
void gameplay_init_pause_menu(void) {
    func_0801daf8(&gameplay_pause_menu_data);
    pause_menu_enabled(FALSE); // Disable Pause Menu
}


// [func_0801853c] Set Skip Tutorial Icon Display
void gameplay_set_skip_icon(u32 corner, u32 show) {
    sprite_set_anim_cel(gSpriteHandler, gGameplay->skipTutorialSprite, corner);
    sprite_set_visible(gSpriteHandler, gGameplay->skipTutorialSprite, show);
}


// [func_0801858c] Set Text Button Style
void gameplay_set_text_advance_icon(u32 style) {
    sprite_set_anim(gSpriteHandler, gGameplay->aButtonSprite, gameplay_text_adv_icons[style], 0, 1, 0, 0);
}


// [func_080185d0] Display A Button Prompt
void gameplay_display_text_advance_icon(s16 x, s16 y, s32 show) {
    sprite_set_visible(gSpriteHandler, gGameplay->aButtonSprite, show);
    if (show) {
        sprite_set_x_y(gSpriteHandler, gGameplay->aButtonSprite, x, y);
    }
}


// [func_08018630] Initialise Text Elements
void gameplay_set_text_printer(struct TextPrinter *textPrinter) {
    gGameplay->textPrinter = textPrinter;
    gGameplay->pausedAtTextBox = FALSE;
    gGameplay->printingTutorialText = FALSE;
}


// [func_08018660] Display Text
void gameplay_display_text(const char *text) {
    text_printer_set_string(gGameplay->textPrinter, text);
    gameplay_display_text_advance_icon(0, 0, FALSE);
    gGameplay->printingTutorialText = FALSE;
}


//
void gameplay_align_text_advance_icon(void) {
    s16 x, y;

    if (gGameplay->textPrinter != NULL) {
        text_printer_get_x_y(gGameplay->textPrinter, &x, &y);
        gameplay_display_text_advance_icon(x, y, TRUE);
    }
}


//
void gameplay_display_text_and_wait(void) {
    if (gGameplay->skippingTutorial) return;

    if (text_printer_is_busy(gGameplay->textPrinter)) {
        gGameplay->printingTutorialText = TRUE;
    } else {
        gameplay_align_text_advance_icon();
        gGameplay->printingTutorialText = FALSE;
    }
    gGameplay->textButtonPressFilter = gGameplay->buttonPressFilter;
    gGameplay->textButtonReleaseFilter = gGameplay->buttonReleaseFilter;
    gameplay_set_input_buttons(0, 0);
    set_pause_beatscript_scene(TRUE);
    gGameplay->pausedAtTextBox = TRUE;
}


// [func_0801875c] Update Text
void gameplay_update_text(void) {
    if (gGameplay->skippingTutorial) {
        return;
    }

    text_printer_update(gGameplay->textPrinter);

    if (!gGameplay->pausedAtTextBox) {
        return;
    }

    if (!text_printer_is_busy(gGameplay->textPrinter) && gGameplay->printingTutorialText) {
        gameplay_align_text_advance_icon(); // Text-related
        gGameplay->printingTutorialText = FALSE;
    }

    if (!text_printer_is_busy(gGameplay->textPrinter) && (D_03004afc & A_BUTTON)) {
        text_printer_set_string(gGameplay->textPrinter, NULL);
        gameplay_display_text_advance_icon(0, 0, FALSE); // Hide A Button Prompt
        play_sound(&s_f_send_mes_seqData);
        gameplay_set_input_buttons(gGameplay->textButtonPressFilter, gGameplay->textButtonReleaseFilter);
        set_pause_beatscript_scene(FALSE);
        gGameplay->pausedAtTextBox = FALSE;
    }
}


// Set Text X Position
void gameplay_set_text_x(s32 x) {
    if (gGameplay->textPrinter != NULL) {
        text_printer_set_x(gGameplay->textPrinter, x);
    }
}


// Set Text Y Position
void gameplay_set_text_y(s32 y) {
    if (gGameplay->textPrinter != NULL) {
        text_printer_set_y(gGameplay->textPrinter, y);
    }
}


// Set Text Z Position (Sprite Depth/Layer)
void gameplay_set_text_z(u16 z) {
    sprite_set_z(gSpriteHandler, gGameplay->aButtonSprite, z);

    if (gGameplay->textPrinter != NULL) {
        text_printer_set_layer(gGameplay->textPrinter, z);
    }
}
