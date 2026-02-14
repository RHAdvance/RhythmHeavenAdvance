#include "global.h"
#include "code_0800b778.h"
#include "syscall.h"

#include "src/code_08001360.h"
#include "src/palette.h"
#include "src/affine_param.h"
#include "src/audio.h"
#include "src/graphics_table.h"
#include "src/bitmap_font.h"
#include "src/task_pool.h"
#include "src/memory_heap.h"
#include "src/code_08007468.h"
#include "src/midi/midi.h"
#include "src/lib_0804ca80.h"
#include "src/backdrop.h"

// Could use better split

asm(".include \"include/gba.inc\"");//Temporary


/* BEATSCRIPT SCENE HANDLER */


extern struct BitmapFontData bitmap_font_warioware_outline[];
extern struct BitmapFontData bitmap_font_warioware_body[];

static s32 D_03001310; // Active Mem. ID
static s32 D_03001314; // unused


// ?
u8 func_0800b634(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3) {
    if (arg0[0] + arg1[0] < arg2[0] + arg3[0] + arg3[2]
     && arg2[0] + arg3[0] < arg0[0] + arg1[0] + arg1[2]
     && arg0[1] + arg1[1] < arg2[1] + arg3[1] + arg3[3]
     && arg2[1] + arg3[1] < arg0[1] + arg1[1] + arg1[3]) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Run BeatScript Engine Callback
void run_beatscript_scene_callback(void) {
    if (D_030053c0.callbackFunction != NULL) {
        D_030053c0.callbackFunction(D_030053c0.callbackArgument);
    }
}


// Set BeatScript Engine Callback
void set_beatscript_scene_callback(void function(s32), s32 argument) {
    D_030053c0.callbackFunction = function;
    D_030053c0.callbackArgument = argument;
}


// "Init." Function for an Unknown Array Structure
void func_0800b6dc(struct Struct_0800b71c *container, u32 arg1, u32 arg2, struct Struct_0800b71c_sub *objects) {
    container->total = 0;
    container->unk1_0 = arg1;
    container->unk1_1 = arg2;
    container->objects = objects;

    objects[0].id = -1;
    objects[0].unk1_0 = 0;
    objects[0].unk4 = 0;
}


// "Add" Function for an Unknown Array Structure
void func_0800b71c(struct Struct_0800b71c *container, u32 id, u32 arg2, u32 arg3) {
    struct Struct_0800b71c_sub *object = &container->objects[0];

    while (object->id != (u8)-1) {
        object++;
    }

    object->id = id;
    object->unk1_0 = arg2;
    object->unk4 = arg3;

    object++;
    object->id = -1;
    object->unk1_0 = 0;
    object->unk4 = 0;

    container->total++;
}


// Stub
void func_0800b768_stub(void) {
}


// Stub
void func_0800b76c_stub(void) {
}


// Stub
void func_0800b770_stub(void) {
}


// Stub
void func_0800b774_stub(void) {
}


// Beatscript Engine Init.
void start_beatscript_scene(u32 mode) {
    u32 i;

    D_030053c0.mode = mode;
    D_030053c0.bypassLoops = FALSE;
    D_030053c0.exitLoopNextUpdate = FALSE;
    D_030053c0.paused = FALSE;
    D_030053c0.musicPlayer = NULL;
    D_030053c0.unk0_b7 = FALSE;
    D_030053c0.unk0_b6 = FALSE;
    D_030053c0.unk1C = 2;
    D_030053c0.scriptBaseBPM = 120;
    D_030053c0.musicBaseBPM = 120;
    D_030053c0.scriptSpeed = INT_TO_FIXED(1.0);
    set_beatscript_tempo(120);
    D_030053c0.musicPitchSrc2 = 0;
    scene_set_music_pitch(INT_TO_FIXED(0.0));
    D_030053c0.musicVolume = INT_TO_FIXED(1.0);
    D_030053c0.musicTrkVolume = INT_TO_FIXED(1.0);
    D_030053c0.musicTrkTargets = 0;
    D_030053c0.musicKey = 0;

    for (i = 0; i < ARRAY_COUNT(D_030053c0.threads); i++) {
        D_030053c0.threads[i].active = FALSE;
    }

    func_0800e948();
    scene_tempo_interp_stop();
    scene_music_pitch_interp_stop();
    D_030053c0.musicInterpolationEnabled = TRUE;
    D_030053c0.callbackFunction = NULL;
    D_030053c0.callbackArgument = 0;
}


// Set SubScenes
void set_beatscript_subscenes(const struct SubScene **subScenes) {
    struct BeatscriptThread *thread;
    u32 i;

    D_030053c0.paused = FALSE;
    D_030053c0.bypassLoops = FALSE;
    D_030053c0.exitLoopNextUpdate = FALSE;
    D_030053c0.runningTime = 0;

    for (i = 0; i < ARRAY_COUNT(D_030053c0.threads); i++) {
        D_030053c0.threads[i].active = FALSE;
        D_030053c0.threads[i].unk0_b7 = FALSE;
    }

    for (i = 0; (i < ARRAY_COUNT(D_030053c0.threads)) && (subScenes[i] != NULL); i++) {
        D_030053c0.currentThread = i;
        set_current_mem_id(D_030053c0.currentThread + 1);
        D_030053c0.threads[i].active = TRUE;
        D_030053c0.threads[i].subScene = subScenes[i];
        D_030053c0.threads[i].currentCmd = subScenes[i]->script;
        D_030053c0.threads[i].timeUntilNext = 0;
        D_030053c0.threads[i].stackCounter = 0;
        D_03005588 = &D_030053c0.localVariables[i];
        D_0300558c = D_030053c0.threads[i].sprites;

        if ((D_030053c0.mode == 1) && (i == 1)) {
            D_030053c0.threads[i].startDelay = 2;
            continue;
        }

        if (subScenes[i]->startFunc != NULL) {
            subScenes[i]->startFunc(&D_030053c0.localVariables[i], subScenes[i]->startParam);
        }

        D_030053c0.threads[i].startDelay = 0;
    }
}


// ? (called each loop after the pause menu has been opened at least once, probably by accident)
void update_paused_beatscript_scene(void) {
    const struct SubScene *subScene;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(D_030053c0.threads); i++) {
        D_030053c0.currentThread = i;
        set_current_mem_id(D_030053c0.currentThread + 1);

        if (D_030053c0.threads[i].active && (D_030053c0.threads[i].startDelay == 0)) {
            D_03005588 = &D_030053c0.localVariables[i];
            D_0300558c = D_030053c0.threads[i].sprites;
            subScene = D_030053c0.threads[i].subScene;

            if (subScene->pausedFunc != NULL) {
                subScene->pausedFunc(&D_030053c0.localVariables[i], subScene->pausedParam);
            }
        }
    }
}


// Beatscript Engine Update
void update_active_beatscript_scene(void) {
    struct BeatscriptThread *thread;
    const struct SubScene *subScene;
    void (*subSceneFunc)();
    u32 isId1;
    u32 i, memID;

    isId1 = (D_030053c0.mode == 1);

    if (D_030053c0.exitLoopNextUpdate) {
        D_030053c0.bypassLoops = TRUE;
        D_030053c0.exitLoopNextUpdate = FALSE;
    }

    if (isId1) {
        thread = &D_030053c0.threads[1];
        if (thread->active && (thread->startDelay == 0)) {
            func_0800e004_stub();
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_030053c0.threads); i++) {
        D_030053c0.currentThread = i;
        set_current_mem_id(D_030053c0.currentThread + 1);
        thread = &D_030053c0.threads[i];
        memID = i + 1;

        if (thread->active) {
            D_03005588 = &D_030053c0.localVariables[i];
            D_0300558c = D_030053c0.threads[i].sprites;

            while (thread->active && (thread->timeUntilNext < D_030053c0.deltaTime) && !D_030053c0.paused) {
                func_0800cb28(i);
            }

            subScene = thread->subScene;
            if (thread->active) {
                if (thread->startDelay != 0) {
                    thread->startDelay--;
                    if (thread->startDelay == 0) {
                        subSceneFunc = subScene->startFunc;
                        if (subScene->startFunc != NULL) {
                            subScene->startFunc(&D_030053c0.localVariables[i], subScene->startParam);
                        }
                    }
                } else {
                    subSceneFunc = subScene->updateFunc;
                    if (subScene->updateFunc != NULL) {
                        subScene->updateFunc(&D_030053c0.localVariables[i], subScene->updateParam);
                    }
                }
            }

            if (!thread->active) {
                subSceneFunc = subScene->stopFunc;
                if (subScene->stopFunc != NULL) {
                    subScene->stopFunc(&D_030053c0.localVariables[i], subScene->stopParam);
                }

                if (!thread->unk0_b7) {
                    sprite_id_delete(gSpriteHandler, memID);
                    func_0800222c(memID);
                    mem_heap_dealloc_with_id(memID);
                    task_pool_force_cancel_id(memID);
                }
            }
        }
    }

    if (D_030053c0.musicInterpolationEnabled) {
        func_0800e970();
        scene_tempo_interp_update();
        scene_music_pitch_interp_update();
        set_soundplayer_track_volume(D_030053c0.musicPlayer, D_030053c0.musicTrkTargets, D_030053c0.musicTrkVolume);
        set_soundplayer_volume(D_030053c0.musicPlayer, D_030053c0.musicVolume);
    }

    if (!D_030053c0.paused) {
        for (i = 0; i < ARRAY_COUNT(D_030053c0.threads); i++) {
            D_030053c0.threads[i].timeUntilNext -= D_030053c0.deltaTime;
        }

        D_030053c0.runningTime += D_030053c0.deltaTime;
    }
}


// Check if No Beatscript Threads Are Active
s32 beatscript_scene_is_inactive(void) {
    u32 i;

    for (i = 0; i < ARRAY_COUNT(D_030053c0.threads); i++) {
        if (D_030053c0.threads[i].active) {
            return FALSE;
        }
    }

    return TRUE;
}


// Start Loop
void beatscript_enable_loops(void) {
    D_030053c0.bypassLoops = FALSE;
    D_030053c0.exitLoopNextUpdate = FALSE;
}


// Delayed Loop Exit Task Function
void beatscript_exit_loop_after_delay_callback(void) {
    D_030053c0.exitLoopNextUpdate = TRUE;
}


// Exit Loop After Delay
void beatscript_exit_loop_after_delay(u32 duration) {
    if (D_030053c0.bypassLoops) {
        return;
    }

    if (!D_030053c0.exitLoopNextUpdate) {
        schedule_function_call(get_current_mem_id(), beatscript_exit_loop_after_delay_callback, 0, ticks_to_frames(duration));

        if (D_030053c0.mode == 1) {
            func_0800c3ec(2);
        }
    }
}


// Exit Loop After One Beat
void beatscript_exit_loop_after_one_beat(void) {
    beatscript_exit_loop_after_delay(24);
}


// Exit Loop (If Within a Loop)
void beatscript_force_exit_loop(void) {
    if (D_030053c0.bypassLoops) {
        return;
    }

    if (!D_030053c0.exitLoopNextUpdate) {
        D_030053c0.exitLoopNextUpdate = TRUE;
    }
}


// Force Stop Loop
void beatscript_disable_loops(void) {
    D_030053c0.bypassLoops = TRUE;
}


// Exit Loop on Next Update
void beatscript_force_exit_loop_next_update(void) {
    D_030053c0.exitLoopNextUpdate = TRUE;
}


// Pause Script
void set_pause_beatscript_scene(u32 pause) {
    D_030053c0.paused = pause;
}


// Check if Beatscript Handler Is Paused
u32 beatscript_scene_is_paused(void) {
    return D_030053c0.paused;
}


// Beatscript Engine Force Quit
void stop_beatscript_scene(void) {
    struct BeatscriptThread *thread;
    const struct SubScene *subScene;
    u32 i, memID;

    for (i = 0; i < ARRAY_COUNT(D_030053c0.threads); i++) {
        D_030053c0.currentThread = i;
        set_current_mem_id(D_030053c0.currentThread + 1);
        thread = &D_030053c0.threads[i];
        subScene = thread->subScene;
        memID = i + 1;

        if (thread->active) {
            D_03005588 = &D_030053c0.localVariables[i];
            D_0300558c = D_030053c0.threads[i].sprites;

            if (subScene->stopFunc != NULL) {
                subScene->stopFunc(&D_030053c0.localVariables[i], subScene->stopParam);
            }

            sprite_id_delete(gSpriteHandler, memID);
            func_0800222c(memID);
            mem_heap_dealloc_with_id(memID);
            task_pool_force_cancel_id(memID);
            thread->active = FALSE;
        }
    }
}

extern u8 haveSeenDisclaimer;

// Set Tempo
void set_beatscript_tempo(u16 tempo) {
    s32 speed;

    if (tempo > 1000) {
        tempo -= 1000;
    } else if (!haveSeenDisclaimer) {
        if (agb_random(2) == 0) {
            tempo = agb_random(60) + 1;
        } else {
            tempo = agb_random(200) + 240;
        }
    }

    D_030053c0.scriptBaseBPM = tempo;
    if (D_030053c0.unk0_b6 && D_030053c0.unk0_b7) {
        tempo *= D_030053c0.unk1C;
    }
    tempo = FIXED_POINT_MUL(D_030053c0.scriptSpeed, tempo);
    D_030053c0.scriptBPM = tempo;

    speed = INT_TO_FIXED(tempo);
    D_030053c0.spriteAnimSpeed = speed / 140;
    speed /= D_030053c0.musicBaseBPM;
    D_030053c0.deltaTime = D_030053c0.musicBaseBPM * speed / 150u;

    if (D_030053c0.musicPlayer != NULL) {
        set_soundplayer_speed(D_030053c0.musicPlayer, speed);
    }

    D_030053c0.interpolatingTempo = FALSE;
}


// Update Script Tempo (Interpolation)
void update_beatscript_tempo(void) {
    u32 flag;

    flag = D_030053c0.interpolatingTempo;
    set_beatscript_tempo(D_030053c0.scriptBaseBPM);
    D_030053c0.interpolatingTempo = flag;
}


// Set Script Speed (Q8.8)
void set_beatscript_speed(u16 speed) {
    D_030053c0.scriptSpeed = speed;
    update_beatscript_tempo();
}


// Stub
void func_0800be9c_stub(void) {
}


// Set unk0_b7
void func_0800bea0(u32 arg) {
    D_030053c0.unk0_b7 = arg;
    update_beatscript_tempo();
}


// Set unk1C
void func_0800bebc(u32 arg) {
    D_030053c0.unk1C = arg;
    update_beatscript_tempo();
}


// Play Music
u32 scene_change_music(struct SongHeader *music, u32 override, s32 soundPlayer) {
    if ((D_030053c0.musicPlayer != NULL) && override) {
        stop_soundplayer(D_030053c0.musicPlayer);
    }

    if (music == NULL) {
        D_030053c0.musicPlayer = NULL;
        return;
    }

    gMidiLFOMode = LFO_MODE_DISABLED;
    midi_equalizer_reset();
    midi_equalizer_set_position(0);
    D_030053c0.musicPlayer = (soundPlayer < 0) ? play_sound(music) : play_sound_in_player(soundPlayer, music);
    D_030053c0.musicBaseBPM = get_music_base_tempo(music);
    update_beatscript_tempo();
    scene_update_music_pitch();
    set_soundplayer_volume(D_030053c0.musicPlayer, D_030053c0.musicVolume);
    set_soundplayer_track_volume(D_030053c0.musicPlayer, D_030053c0.musicTrkTargets, D_030053c0.musicTrkVolume);
    set_soundplayer_key(D_030053c0.musicPlayer, D_030053c0.musicKey);
}


// Play Music (Override Existing)
void scene_set_music(struct SongHeader *music) {
    scene_change_music(music, TRUE, -1);
}


// Play Music (No Override)
void scene_play_music(struct SongHeader *music) {
    scene_change_music(music, FALSE, -1);
}


// Play Music in Given SoundPlayer (Override)
void scene_set_music_with_soundplayer(struct SongHeader *music, s32 soundPlayer) {
    scene_change_music(music, TRUE, soundPlayer);
}


// Play Music in Given SoundPlayer (No Override)
void scene_play_music_with_soundplayer(struct SongHeader *music, s32 soundPlayer) {
    scene_change_music(music, FALSE, soundPlayer);
}


// Play Music (override, use predefined SoundPlayer ID)
void scene_set_music_player_by_sound(struct SongHeader *music) {
    struct SoundPlayer *player = get_soundplayer_by_sound(music);

    if (player == NULL) {
        return;
    }

    D_030053c0.musicPlayer = player;
    D_030053c0.musicBaseBPM = get_music_base_tempo(music);
    update_beatscript_tempo();
    scene_update_music_pitch();
    set_soundplayer_volume(D_030053c0.musicPlayer, D_030053c0.musicVolume);
    set_soundplayer_track_volume(D_030053c0.musicPlayer, D_030053c0.musicTrkTargets, D_030053c0.musicTrkVolume);
    set_soundplayer_key(D_030053c0.musicPlayer, D_030053c0.musicKey);
}


// Stop Music
void scene_stop_music(void) {
    stop_soundplayer(D_030053c0.musicPlayer);
}


// Fade-In Music
void scene_fade_in_music(u16 duration) {
    fade_in_soundplayer(D_030053c0.musicPlayer, duration);
}


// Fade-Out Music
void scene_fade_out_music(u16 duration) {
    fade_out_soundplayer(D_030053c0.musicPlayer, duration);
}


// Update Music Pitch (Interpolation)
void scene_update_music_pitch(void) {
    u32 flag;

    flag = D_030053c0.interpolatingMusicPitch;
    scene_set_music_pitch(D_030053c0.musicPitchSrc1);
    D_030053c0.interpolatingMusicPitch = flag;
}


// Set Music Pitch
void scene_set_music_pitch(s16 pitch) {
    D_030053c0.musicPitchSrc1 = pitch;
    pitch += D_030053c0.musicPitchSrc2;
    D_030053c0.musicPitch = pitch;

    if (D_030053c0.musicPlayer != NULL) {
        set_soundplayer_pitch(D_030053c0.musicPlayer, pitch);
    }

    D_030053c0.interpolatingMusicPitch = FALSE;
}


// Set Music Pitch Source 2
void scene_set_music_pitch_env(s16 pitch) {
    D_030053c0.musicPitchSrc2 = pitch;
    scene_update_music_pitch();
}


// Set Music Volume
void scene_set_music_volume(u16 volume) {
    D_030053c0.musicVolume = volume;
    set_soundplayer_volume(D_030053c0.musicPlayer, volume);
}


// Set Volume for Selected Music Channels
void scene_set_music_track_volume(u16 selection, u16 volume) {
    D_030053c0.musicTrkVolume = volume;
    D_030053c0.musicTrkTargets = selection;
    set_soundplayer_track_volume(D_030053c0.musicPlayer, selection, volume);
}


// Set Music Volume (it just calls scene_set_music_volume())
void scene_set_music_volume_env(u32 volume) {
    scene_set_music_volume(volume);
}


// Interpolate Music Volume
void scene_interpolate_music_volume(u32 volume, u32 duration) {
    scene_start_integer_interp(1, duration, &D_030053c0.musicVolume, D_030053c0.musicVolume, volume);
}


// Set Music Volume for Selected Tracks (Integer)
void scene_set_music_track_volume_env(u32 selection, u32 volume) {
    scene_set_music_track_volume(selection, volume);
}


// Interpolate Music Volume for Selected Tracks
void scene_interpolate_music_track_volume(u32 volume, u32 duration) {
    scene_start_integer_interp(1, duration, &D_030053c0.musicTrkVolume, D_030053c0.musicTrkVolume, volume);
}


// Set Music Key
void scene_set_music_key(s32 key) {
    D_030053c0.musicKey = key;

    if (D_030053c0.musicPlayer != NULL) {
        set_soundplayer_key(D_030053c0.musicPlayer, key);
    }
}


void func_0800c1a4_stub(void) {
}


// Get Current Script Tempo
u32 get_beatscript_tempo(void) {
    return D_030053c0.scriptBPM;
}


// Get Sprite Animation Speed
u32 func_0800c1b4(void) {
    return D_030053c0.spriteAnimSpeed;
}


// Return (arg * spriteAnimSpeed)
s32 func_0800c1c0(s24_8 arg) {
    return FIXED_POINT_MUL(arg, D_030053c0.spriteAnimSpeed);
}


// Return (arg * (spriteAnimSpeed ^ 2))
s32 func_0800c1d0(s24_8 arg) {
    return FIXED_POINT_MUL(arg, FIXED_POINT_MUL(D_030053c0.spriteAnimSpeed, D_030053c0.spriteAnimSpeed));
}


// Set Music Panning
void scene_set_soundplayer_panning(struct SoundPlayer *player, s16 panning) {
    panning -= 120u;
    panning = panning * 3u / 4u;

    if (panning < -0x80) {
        panning = -0x80;
    }

    if (panning > 0x7F) {
        panning = 0x7F;
    }

    set_soundplayer_panning(player, panning);
}


// Play Randomly-Selected Music
struct SoundPlayer *scene_set_random_music(struct SongHeader **musicPool) {
    struct SongHeader *music;
    u32 total;

    if (musicPool == NULL) {
        return NULL;
    }

    for (total = 0; musicPool[total] != NULL; total++);

    if (total == 0) {
        return NULL;
    }

    music = musicPool[agb_random(total)];
    scene_set_music(music);

    return sound_player_table[music->soundPlayer].soundPlayer;
}


// Play Sound Effect to Sprite Animation Speed and Music Pitch
struct SoundPlayer *scene_play_sound_to_tempo_and_pitch(struct SongHeader *sfx) {
    struct SoundPlayer *player;

    player = play_sound(sfx);
    set_soundplayer_speed(player, func_0800c1b4());
    set_soundplayer_pitch(player, D_030053c0.musicPitchSrc1);

    return player;
}


// Play Sound Effect to Sprite Animation Speed
struct SoundPlayer *scene_play_sound_to_tempo(struct SongHeader *sfx) {
    struct SoundPlayer *player;

    player = play_sound(sfx);
    set_soundplayer_speed(player, func_0800c1b4());

    return player;
}


// Play Randomly-Selected Sound Effect
struct SoundPlayer *scene_play_random_sound(struct SongHeader **sfxPool) {
    struct SongHeader *sfx;
    u32 total;

    if (sfxPool == NULL) {
        return NULL;
    }

    for (total = 0; sfxPool[total] != NULL; total++);

    if (total == 0) {
        return NULL;
    }

    sfx = sfxPool[agb_random(total)];
    return play_sound(sfx);
}


// Play Randomly-Selected Sound Effect to Sprite Animation Speed and Music Pitch
struct SoundPlayer *scene_play_random_sound_to_tempo_and_pitch(struct SongHeader **sfxPool) {
    struct SongHeader *sfx;
    u32 total;

    if (sfxPool == NULL) {
        return NULL;
    }

    for (total = 0; sfxPool[total] != NULL; total++);

    if (total == 0) {
        return NULL;
    }

    sfx = sfxPool[agb_random(total)];
    return scene_play_sound_to_tempo_and_pitch(sfx);
}


// Play Randomly-Selected Sound Effect to Sprite Animation Speed
struct SoundPlayer *scene_play_random_sound_to_tempo(struct SongHeader **sfxPool) {
    struct SongHeader *sfx;
    u32 total;

    if (sfxPool == NULL) {
        return NULL;
    }

    for (total = 0; sfxPool[total] != NULL; total++);

    if (total == 0) {
        return NULL;
    }

    sfx = sfxPool[agb_random(total)];
    return scene_play_sound_to_tempo(sfx);
}


// Stub
void func_0800c390_stub(void) {
}


// Return 2
u32 func_0800c394(void) {
    return 2;
}


// Get Delta Time
u32 func_0800c398(void) {
    return D_030053c0.deltaTime;
}


// Convert Script Tatums to Real-Time Frames
s32 ticks_to_frames(u32 beats) {
    fast_divsi3(INT_TO_FIXED(beats), D_030053c0.deltaTime);
}


// Get Current Active Thread (Memory ID / SubScene)
u32 get_current_mem_id() {
    return D_03001310;
}


// Set Current Memory ID / SubScene
void set_current_mem_id(u32 memID) {
    D_03001310 = memID;
    sprite_handler_set_mem_id(gSpriteHandler, memID);
}


// Stub
void func_0800c3e4_stub(void) {
}


// Stub
void func_0800c3e8_stub(u32 arg) {
}


// ? (effectively does nothing, but is called anyway)
void func_0800c3ec(u32 arg) {
    func_0800c3e8_stub(arg);
    func_0800c3e8_stub(2);
}


// Stub
void func_0800c3fc_stub(void) {
}


// Stub
void func_0800c400_stub(void) {
}


// Stub
void func_0800c404_stub(void) {
}


// Stub
void func_0800c408_stub(void) {
}


// Stub
void func_0800c40c_stub(void) {
}


// Stub
void func_0800c410_stub(void) {
}


// Stub
void func_0800c414_stub(void) {
}


// Stub
void func_0800c418_stub(void) {
}


// Stub
void func_0800c41c_stub(void) {
}


// Stub
void func_0800c420_stub(void) {
}


// Stub
void func_0800c424_stub(void) {
}


// Stub
void func_0800c428_stub(void) {
}


// Allocate Affine Parameter Group ID
s32 scene_affine_group_alloc(void) {
    return func_08002194(get_current_mem_id());
}


// Allocate Memory
void *scene_mem_heap_alloc(u32 size) {
    return mem_heap_alloc_id(get_current_mem_id(), size);
}


// Start Task
s32 scene_start_new_task(struct TaskMethods *methods, void *inputs, TaskFinalFunc onFinish, u32 onFinishArg) {
    return start_new_task(get_current_mem_id(), methods, inputs, onFinish, onFinishArg);
}


// Save Data
void scene_flush_save_buffer(void) {
    flush_save_buffer_to_sram();
}


// Get Default Scene Text ID
u32 scene_get_default_text_id(void) {
    return 0;
}


// Set Thread unk0_b7
void func_0800c494(u32 id) {
    D_030053c0.threads[id].unk0_b7 = TRUE;
}


// Stub
void func_0800c4ac_stub(void) {
}


// Start Linear Interpolation Task
s32 scene_start_integer_interp(u32 type, u32 duration, void *source, s32 initial, s32 target) {
    struct NumberInterpolator inputs;

    inputs.type = type;
    inputs.duration = duration;
    inputs.source = source;
    inputs.initial = initial;
    inputs.target = target;

    return start_new_task(get_current_mem_id(), &integer_interp_task, &inputs, 0, 0);
}


// Start Number Alternator Task
s32 scene_start_integer_alternator(u32 type, u32 interval, void *source, s32 initial, s32 target) {
    struct NumberInterpolator inputs;

    inputs.type = type;
    inputs.duration = interval;
    inputs.source = source;
    inputs.initial = initial;
    inputs.target = target;

    return start_new_task(get_current_mem_id(), &integer_alternator_task, &inputs, 0, 0);
}


// Start Number Incrementer Task
s32 scene_start_integer_incrementer(u32 type, u32 interval, void *source, s32 initial, s32 increment) {
    struct NumberInterpolator inputs;

    inputs.type = type;
    inputs.duration = interval;
    inputs.source = source;
    inputs.initial = initial;
    inputs.target = increment;

    return start_new_task(get_current_mem_id(), &integer_incrementer_task, &inputs, 0, 0);
}


// Start Number Sine Interpolator Task
s32 scene_start_integer_sine_interp(u32 type, void *source, s32 baseValue, s24_8 initialAngle, s24_8 speed) {
    struct NumberSineInterpolator inputs;

    inputs.type = type;
    inputs.value = baseValue;
    inputs.angle = initialAngle;
    inputs.speed = speed;
    inputs.source = source;

    return start_new_task(get_current_mem_id(), &integer_sine_interp_task, &inputs, NULL, 0);
}


// Set Current Thread
void func_0800c604(u32 thread) {
    D_030053c0.currentThread = thread;
    set_current_mem_id(D_030053c0.currentThread + 1);
    D_03005588 = &D_030053c0.localVariables[thread];
    D_0300558c = D_030053c0.threads[thread].sprites;
}


// Stub
void func_0800c654_stub(void) {
}


// Stub
void func_0800c658_stub(void) {
}


// Stub
void func_0800c65c_stub(void) {
}


// Create BitmapFontOBJ with the WarioWare Outline Font
struct BitmapFontOBJ *scene_create_obj_font_printer(u16 baseTileNum, u8 maxTileRows) {
    struct BitmapFontOBJ *objFont;

    objFont = create_new_bmp_font_obj(get_current_mem_id(), bitmap_font_warioware_outline, baseTileNum, maxTileRows);
    func_0800f09c(objFont);
    return objFont;
}


// ?
void func_0800c694(u32 arg) {
    if (arg > 24) {
        arg = 24;
    }

    func_08009564(arg);
}


// ?
void func_0800c6a4(void) {
    s32 value = func_08009394();

    func_0800c694((ABS(value) * 18 / 200) + 6);
}


// ?
void func_0800c6c8(void) {
    func_0800c6a4();
}


// Stub
void func_0800c6d4_stub(void) {
}


// Stub
void func_0800c6d8_stub(void) {
}


// Stub
void func_0800c6dc_stub(void) {
}


// Stub
void func_0800c6e0_stub(void) {
}


// Beatscript Stream - IF Statement Failed
struct Beatscript *beatscript_stream_jump_cond_if(struct Beatscript *currentCmd) {
    s32 depth = 0;
    s32 command;

    while (TRUE) {
        command = currentCmd->command;
        currentCmd++;

        switch (command) {
            case BS_CMD_IF_EQ:
            case BS_CMD_IF_NEQ:
            case BS_CMD_IF_SET:
            case BS_CMD_IF_CLEAR:
            case BS_CMD_3B:
            case BS_CMD_44:
            case BS_CMD_45:
            case BS_CMD_4B:
            case BS_CMD_4D:
            case BS_CMD_51:
            case BS_CMD_52:
                depth++;
                continue;

            case BS_CMD_ELSE:
                if (depth == 0) {
                    return currentCmd;
                }
                continue;

            case BS_CMD_END_IF:
                if (depth == 0) {
                    return currentCmd;
                }
                depth--;
                continue;
        }
    }
}


// Beatscript Stream - ELSE Statement Jump
struct Beatscript *beatscript_stream_jump_cond_else(struct Beatscript *currentCmd) {
    s32 depth = 0;
    s32 command;

    while (TRUE) {
        command = currentCmd->command;
        currentCmd++;

        switch (command) {
            case BS_CMD_IF_EQ:
            case BS_CMD_IF_NEQ:
            case BS_CMD_IF_SET:
            case BS_CMD_IF_CLEAR:
            case BS_CMD_3B:
            case BS_CMD_44:
            case BS_CMD_45:
            case BS_CMD_4B:
            case BS_CMD_4D:
            case BS_CMD_51:
            case BS_CMD_52:
                depth++;
                continue;

            case BS_CMD_END_IF:
                if (depth == 0) {
                    return currentCmd;
                }
                depth--;
                continue;
        }
    }
}


// Beatscript Stream - SWITCH Statement Start
struct Beatscript *beatscript_stream_jump_cond_switch(struct Beatscript *currentCmd, s32 arg) {
    s32 depth = 0;
    s32 command;
    s32 caseValue;

    while (TRUE) {
        command = currentCmd->command;
        caseValue = currentCmd->param3;
        currentCmd++;

        switch (command) {
            case BS_CMD_SWITCH:
                depth++;
                continue;

            case BS_CMD_CASE:
                if ((depth == 0) && (caseValue == arg)) {
                    return currentCmd;
                }
                continue;

            case BS_CMD_DEFAULT_CASE:
                if (depth == 0) {
                    return currentCmd;
                }
                continue;

            case BS_CMD_END_SWITCH:
                if (depth == 0) {
                    return currentCmd;
                }
                depth--;
                continue;
        }
    }
}


// Beatscript Stream - BREAK Statement Jump
struct Beatscript *beatscript_stream_jump_cond_break(struct Beatscript *currentCmd) {
    s32 depth = 0;
    s32 command;

    while (TRUE) {
        command = currentCmd->command;
        currentCmd++;

        switch (command) {
            case BS_CMD_SWITCH:
                depth++;
                continue;

            case BS_CMD_END_SWITCH:
                if (depth == 0) {
                    return currentCmd;
                }
                depth--;
                continue;
        }
    }
}


// Beatscript Stream - WHILE Statement Failed
struct Beatscript *beatscript_stream_jump_cond_while(struct Beatscript *currentCmd) {
    s32 depth = 0;
    s32 command;

    while (TRUE) {
        command = currentCmd->command;
        currentCmd++;

        switch (command) {
            case BS_CMD_WHILE_EQ:
            case BS_CMD_WHILE_NEQ:
            case BS_CMD_SCENE_WHILE_EQ:
            case BS_CMD_SCENE_WHILE_NEQ:
                depth++;
                continue;

            case BS_CMD_END_WHILE:
                if (depth == 0) {
                    return currentCmd;
                }
                depth--;
                continue;
        }
    }
}


// Beatscript Stream - END_WHILE Statement Jump
struct Beatscript *beatscript_stream_jump_cond_end_while(struct Beatscript *currentCmd) {
    s32 depth = 0;
    s32 command;

    while (TRUE) {
        currentCmd--;
        command = currentCmd->command;

        switch (command) {
            case BS_CMD_END_WHILE:
                depth++;
                continue;

            case BS_CMD_WHILE_EQ:
            case BS_CMD_WHILE_NEQ:
            case BS_CMD_SCENE_WHILE_EQ:
            case BS_CMD_SCENE_WHILE_NEQ:
                if (depth == 0) {
                    return currentCmd;
                }
                depth--;
                continue;
        }
    }
}


// Beatscript Stream - Get Sprite for Motion Task
s16 beatscript_stream_get_sprite_for_motion(s16 *spritePool, s16 args, s16 *destX, s16 *destY) {
    s16 sprite;
    s16 x, y;
    u32 relativeDest;

    if (args < 0) {
        return -1;
    }

    sprite = spritePool[args & ~(1 << 6)];
    x = sprite_get_data(gSpriteHandler, sprite, 4);
    y = sprite_get_data(gSpriteHandler, sprite, 5);
    relativeDest = args & (1 << 6);

    if (*destX == 0x7FFF) {
        *destX = x;
    } else if (relativeDest) {
        *destX += x;
    }

    if (*destY == 0x7FFF) {
        *destY = y;
    } else if (relativeDest) {
        *destY += y;
    }

    return sprite;
}


// Beatscript Stream - Update
#include "asm/code_0800b778/asm_0800cb28.s"


// Stub
void func_0800dfbc_stub(void) {
}


// Stub
void func_0800dfc0_stub(void) {
}


// Get Current Thread's Task ID
s32 func_0800dfc4(void) {
    struct BeatscriptThread *thread = &D_030053c0.threads[get_current_mem_id()] - 1;

    return thread->currentTaskID;
}


// Stub
void func_0800dfe0_stub(void) {
}


// Stub
void func_0800dfe4_stub(void) {
}


// Stub
void func_0800dfe8_stub(void) {
}


// Stub
void func_0800dfec_stub(void) {
}


// Stub
void func_0800dff0_stub(void) {
}


// Stub
void func_0800dff4_stub(void) {
}


// Stub
void func_0800dff8_stub(void) {
}


// Stub
void func_0800dffc_stub(void) {
}


// Stub
void func_0800e000_stub(void) {
}


// Stub
void func_0800e004_stub(void) {
}


// Stub
void func_0800e008_stub(void) {
}


// Stub
void func_0800e00c_stub(void) {
}


// Stub
void func_0800e010_stub(void) {
}


// Stub
void func_0800e014_stub(void) {
}


// Set Video Mode
void scene_set_video_mode(s32 videoMode) {
    u16 *displayControls = &D_03004b10.DISPCNT;

    *displayControls &= ~DISPCNT_VIDEO_MODE_MASK;
    *displayControls |= videoMode;
}


// Show BG Layer
void scene_show_bg_layer(s32 layer) {
    D_03004b10.DISPCNT |= (DISPCNT_DISPLAY_BG(layer));
}


// Hide BG Layer
void scene_hide_bg_layer(s32 layer) {
    D_03004b10.DISPCNT &= ~(DISPCNT_DISPLAY_BG(layer));
}


// Set BG Layer Position
void scene_set_bg_layer_pos(s32 layer, s16 x, s16 y) {
    struct Vector2 *bgOfs = D_03004b10.BG_OFS;

    bgOfs[layer].x = x;
    bgOfs[layer].y = y;
}


// Set BG Layer Render Data
void scene_set_bg_layer_controls(s32 layer, s32 tileset, s32 map, s32 params) {
    u16 *bgControls = D_03004b10.BG_CNT;

    bgControls[layer] = BGCNT_TILEDATA_ADDR(tileset) | BGCNT_TILEMAP_ADDR(map) | params;
}


// Set BG Layer Priority
void scene_set_bg_layer_priority(s32 layer, s32 priority) {
    u16 *bgControls = D_03004b10.BG_CNT;

    bgControls[layer] &= ~BGCNT_PRIORITY_MASK;
    bgControls[layer] |= priority;
}


// Set BG Layer Controls
void scene_set_bg_layer_display(s32 layer, s32 show, s32 x, s32 y, s32 tileset, s32 map, s32 params) {
    scene_set_bg_layer_pos(layer, x, y);
    scene_set_bg_layer_controls(layer, tileset, map, params);

    if (show) {
        scene_show_bg_layer(layer);
    } else {
        scene_hide_bg_layer(layer);
    }
}


// Display OBJ Layer
void scene_show_obj_layer(void) {
    u16 *displayControls = &D_03004b10.DISPCNT;

    *displayControls |= DISPCNT_DISPLAY_OAM;
}


// Hide OBJ Layer
void scene_hide_obj_layer(void) {
    u16 *displayControls = &D_03004b10.DISPCNT;

    *displayControls &= ~DISPCNT_DISPLAY_OAM;
}


// Enable OBJ Windows
void scene_enable_obj_windows(void) {
    u16 *displayControls = &D_03004b10.DISPCNT;

    *displayControls |= DISPCNT_ENABLE_SPRITE_WINDOWS;
}


// Disable OBJ Windows
void scene_disable_obj_windows(void) {
    u16 *displayControls = &D_03004b10.DISPCNT;

    *displayControls &= ~DISPCNT_ENABLE_SPRITE_WINDOWS;
}


// Set OBJ Mosaic Size
void scene_set_obj_mosaic_size(s16 xSize, s16 ySize) {
    if (xSize >= 0) {
        D_03004b10.MOSAIC &= ~MOSAIC_SPR_XSIZE_MASK;
        D_03004b10.MOSAIC |= MOSAIC_SPR_XSIZE(xSize);
    }
    if (ySize >= 0) {
        D_03004b10.MOSAIC &= ~MOSAIC_SPR_YSIZE_MASK;
        D_03004b10.MOSAIC |= MOSAIC_SPR_YSIZE(ySize);
    }
}


// Set BG Mosaic Size
void scene_set_bg_mosaic_size(s16 xSize, s16 ySize) {
    if (xSize >= 0) {
        D_03004b10.MOSAIC &= ~MOSAIC_BG_XSIZE_MASK;
        D_03004b10.MOSAIC |= MOSAIC_BG_XSIZE(xSize);
    }
    if (ySize >= 0) {
        D_03004b10.MOSAIC &= ~MOSAIC_BG_YSIZE_MASK;
        D_03004b10.MOSAIC |= MOSAIC_BG_YSIZE(ySize);
    }
}


// Sprite Motion - Indefinite Linear
s32 scene_set_sprite_motion_indefinite(s16 sprite, s16 startX, s16 startY, s8_8 velX, s8_8 velY) {
    struct SpriteMover_Indefinite_Inputs inputs;

    inputs.sprite = sprite;
    inputs.startX = startX;
    inputs.startY = startY;
    inputs.velX = velX;
    inputs.velY = velY;

    return start_new_task(get_current_mem_id(), &sprite_motion_task_indefinite, &inputs, NULL, 0);
}


// Sprite Motion - Indefinite Linear (from current position)
s32 scene_move_sprite_indefinite(s16 sprite, s8_8 velX, s8_8 velY) {
    s16 x, y;

    get_sprite_xy(sprite, &x, &y);
    return scene_set_sprite_motion_indefinite(sprite, x, y, velX, velY);
}


// Sprite Motion - Decelerate to Point
s32 scene_set_sprite_motion_decelerate(s16 sprite, s16 startX, s16 startY, s16 destX, s16 destY, s8_8 multiplier) {
    struct SpriteMover_Decelerate_Inputs inputs;

    inputs.sprite = sprite;
    inputs.startX = startX;
    inputs.startY = startY;
    inputs.destX = destX;
    inputs.destY = destY;
    inputs.multiplier = multiplier;

    return start_new_task(get_current_mem_id(), &sprite_motion_task_decelerate, &inputs, NULL, 0);
}


// Sprite Motion - Decelerate to Point (from current position)
s32 scene_move_sprite_decelerate(s16 sprite, s16 destX, s16 destY, s8_8 multiplier) {
    s16 x, y;

    get_sprite_xy(sprite, &x, &y);
    return scene_set_sprite_motion_decelerate(sprite, x, y, destX, destY, multiplier);
}


// Sprite Motion - Accelerate to Point
s32 scene_set_sprite_motion_accelerate(s16 sprite, s16 startX, s16 startY, s16 destX, s16 destY, s8_8 velocity, s8_8 acceleration) {
    struct SpriteMover_Accelerate_Inputs inputs;

    inputs.sprite = sprite;
    inputs.startX = startX;
    inputs.startY = startY;
    inputs.destX = destX;
    inputs.destY = destY;
    inputs.velocity = velocity;
    inputs.acceleration = acceleration;

    return start_new_task(get_current_mem_id(), &sprite_motion_task_accelerate, &inputs, NULL, 0);
}


// Sprite Motion - Accelerate to Point (from current position)
s32 scene_move_sprite_accelerate(s16 sprite, s16 destX, s16 destY, s8_8 velocity, s8_8 acceleration) {
    s16 x, y;

    get_sprite_xy(sprite, &x, &y);
    return scene_set_sprite_motion_accelerate(sprite, x, y, destX, destY, velocity, acceleration);
}


// Sprite Motion - LERP to Point
s32 scene_set_sprite_motion_lerp(s16 sprite, s16 startX, s16 startY, s16 destX, s16 destY, u16 duration) {
    struct SpriteMover_TimedLinear_Inputs inputs;

    inputs.sprite = sprite;
    inputs.startX = startX;
    inputs.startY = startY;
    inputs.destX = destX;
    inputs.destY = destY;
    inputs.totalFrames = duration;

    return start_new_task(get_current_mem_id(), &sprite_motion_task_lerp, &inputs, NULL, 0);
}


// Sprite Motion - LERP to Point (from current position)
s32 scene_move_sprite_lerp(s16 sprite, s16 destX, s16 destY, u16 duration) {
    s16 x, y;

    get_sprite_xy(sprite, &x, &y);
    return scene_set_sprite_motion_lerp(sprite, x, y, destX, destY, duration);
}


// Sprite Motion - Sinusoidal Oscillation
s32 scene_set_sprite_motion_sine_osc(s16 sprite, u8 angle, s16 baseX, s16 baseY, s16 baseOffset, s16 amplitude, s16 waveStart, s16 waveEnd, u16 duration) {
    struct SpriteMover_SineOsc_Inputs inputs;

    inputs.sprite = sprite;
    inputs.angle = angle;
    inputs.baseX = baseX;
    inputs.baseY = baseY;
    inputs.baseOffset = baseOffset;
    inputs.amplitude = amplitude;
    inputs.waveStart = waveStart;
    inputs.waveEnd = waveEnd;
    inputs.totalFrames = duration;

    return start_new_task(get_current_mem_id(), &sprite_motion_task_sine_osc, &inputs, NULL, 0);
}


// Sprite Motion - Sinusoidal Oscillation (from current position, no base offset)
s32 scene_move_sprite_sine_osc(s16 sprite, u8 angle, s16 amplitude, s16 waveStart, s16 waveEnd, u16 duration) {
    s16 x, y;

    get_sprite_xy(sprite, &x, &y);
    return scene_set_sprite_motion_sine_osc(sprite, angle, x, y, 0, amplitude, waveStart, waveEnd, duration);
}


// Sprite Motion - Sinusoidal Velocity
s32 scene_set_sprite_motion_sine_vel(s16 sprite, u32 mode, s16 startX, s16 startY, s16 destX, s16 destY, u16 duration) {
    struct SpriteMover_SineVel_Inputs inputs;

    inputs.sprite = sprite;
    inputs.totalFrames = duration;

    switch (mode) {
        case 0:
            inputs.startX = startX;
            inputs.startY = startY;
            inputs.destX = destX;
            inputs.destY = destY;
            inputs.unkA = INT_TO_FIXED(0.0);
            inputs.unkC = INT_TO_FIXED(0.25);
            break;

        case 1:
            inputs.startX = destX;
            inputs.startY = destY;
            inputs.destX = startX;
            inputs.destY = startY;
            inputs.unkA = INT_TO_FIXED(0.25);
            inputs.unkC = INT_TO_FIXED(0.5);
            break;

        case 2:
            inputs.startX = (startX + destX) >> 1;
            inputs.startY = (startY + destY) >> 1;
            inputs.destX = destX;
            inputs.destY = destY;
            inputs.unkA = INT_TO_FIXED(-0.25);
            inputs.unkC = INT_TO_FIXED(0.25);
            break;
    }

    return start_new_task(get_current_mem_id(), &sprite_motion_task_sine_vel, &inputs, NULL, 0);
}


// Sprite Motion - Sinusoidal Velocity (from current position)
s32 scene_move_sprite_sine_vel(s16 sprite, u32 mode, s16 destX, s16 destY, u16 duration) {
    s16 x, y;

    get_sprite_xy(sprite, &x, &y);
    return scene_set_sprite_motion_sine_vel(sprite, mode, x, y, destX, destY, duration);
}


// Sprite Motion - LERP with Sine Oscillation
s32 scene_set_sprite_motion_sine_wave(s16 sprite, s16 startX, s16 startY, s16 destX, s16 destY, s16 amplitude, u16 duration) {
    struct SpriteMover_SineWave_Inputs inputs;

    inputs.sprite = sprite;
    inputs.startX = startX;
    inputs.startY = startY;
    inputs.destX = destX;
    inputs.destY = destY;
    inputs.amplitude = amplitude;
    inputs.totalFrames = duration;

    return start_new_task(get_current_mem_id(), &sprite_motion_task_sine_wave, &inputs, NULL, 0);
}


// Sprite Motion - LERP with Sine Oscillation (from current position)
s32 scene_move_sprite_sine_wave(s16 sprite, s16 destX, s16 destY, s16 amplitude, u16 duration) {
    s16 x, y;

    get_sprite_xy(sprite, &x, &y);
    return scene_set_sprite_motion_sine_wave(sprite, x, y, destX, destY, amplitude, duration);
}


void func_0800e75c(struct struct_0800e75c *arg0) {
    *arg0->unkC = -1;
}


void func_0800e768(struct BitmapFontOBJ *textObj, struct struct_0800e75c *arg1) {
    const char *string;
    struct PrintedTextAnim *textAnim;
    
    if (*arg1->unkC >= 0) {
        return;
    }

    string = arg1->unk0[scene_get_default_text_id()];
    switch (arg1->unkA) {
        case 0:
            textAnim = bmp_font_obj_print_c_default(textObj, string);
            break;
        case 1:
            textAnim = bmp_font_obj_print_l_default(textObj, string);
            break;
        case 2:
            textAnim = bmp_font_obj_print_r_default(textObj, string);
            break;
    }
    *arg1->unkC = sprite_create(gSpriteHandler, textAnim->frames, 0, 
                    arg1->unk4, arg1->unk6, arg1->unk8, 0, 0, 0);
}


void func_0800e7e8(struct BitmapFontOBJ *textObj, struct struct_0800e75c *arg1) {
    struct Animation *textAnim;
    
    if (*arg1->unkC < 0) {
        return;
    }

    textAnim = sprite_get_anim(gSpriteHandler, *arg1->unkC);
    sprite_delete(gSpriteHandler, *arg1->unkC);
    bmp_font_obj_delete_printed_anim(textObj, textAnim);
    *arg1->unkC = -1;
}


void func_0800e830(struct struct_0800e75c **arg0) {
    while (*arg0 != NULL) {
        *(*arg0)->unkC = -1;
        arg0++;
    }
}


void func_0800e850(struct BitmapFontOBJ *textObj, struct struct_0800e75c **arg1) {
    while (*arg1 != NULL) {
        func_0800e768(textObj, *arg1);
        arg1++;
    }
}


void func_0800e86c(struct BitmapFontOBJ *textObj, struct struct_0800e75c **arg1) {
    while (*arg1 != NULL) {
        func_0800e7e8(textObj, *arg1);
        arg1++;
    }
}


void func_0800e888(u32 arg0) {
    sprite_set_visible(gSpriteHandler, D_0300558c[arg0], TRUE);
}


void func_0800e8b0(u32 arg0) {
    sprite_set_visible(gSpriteHandler, D_0300558c[arg0], FALSE);
}


void func_0800e8d8(struct SpriteHandler *handler, s16 id, s8 *arg, u32 cel) {
    while (*arg >= 0) {
        if (cel == *arg) {
            return;
        }
        arg += 4;
    }
}


void func_0800e8f4(s16 arg0, s8 *arg1) {
    if (arg1) {
        sprite_set_callback(gSpriteHandler, arg0, func_0800e8d8, (uintptr_t)arg1);
        sprite_run_callback_every_cel(gSpriteHandler, arg0);
    } else {
        sprite_set_callback(gSpriteHandler, arg0, NULL, (uintptr_t)NULL);
    }
}


// Stub
void func_0800e940_stub(void) {
}


// Stub
void func_0800e944_stub(void) {
}


// ?
void func_0800e948(void) {
    D_030053c0.unk1_b4 = FALSE;
    D_030053c0.unk168 = 0;
    D_030053c0.unk16A = 24;
}


// Update ?
void func_0800e970(void) {
    s24_8 value;
    u8 angle;

    if (!D_030053c0.unk1_b4) {
        return;
    }

    D_030053c0.unk16C += 0x10000 / (u32)ticks_to_frames(D_030053c0.unk16A);
    angle = FIXED_TO_INT(D_030053c0.unk16C);
    value = FIXED_POINT_MUL(D_030053c0.unk168, sins2(angle));
    scene_set_music_pitch_env(FIXED_POINT_MUL(func_0800eaa0(), value));
}


// ?
void func_0800e9d8(void) {
    D_030053c0.unk16C = 0;
    D_030053c0.unk1_b4 = TRUE;
    D_030053c0.unk1_b5 = FALSE;
}


// ?
void func_0800e9f8(void) {
    scene_set_music_pitch_env(0);
    D_030053c0.unk1_b4 = FALSE;
    D_030053c0.unk1_b5 = FALSE;
}


// Set ?
void func_0800ea1c(u16 arg) {
    D_030053c0.unk16A = arg;
}


// Set ?
void func_0800ea2c(s16 arg) {
    D_030053c0.unk168 = arg;
}


// Set ?
void func_0800ea3c(u16 arg) {
    D_030053c0.unk1_b6 = FALSE;
    D_030053c0.unk16E = arg;
    D_030053c0.unk170 = 0;
    D_030053c0.unk1_b5 = TRUE;
}


// Set ?
void func_0800ea70(u16 arg) {
    D_030053c0.unk1_b6 = TRUE;
    D_030053c0.unk16E = arg;
    D_030053c0.unk170 = 0xFFFF;
    D_030053c0.unk1_b5 = TRUE;
}


// Get ?
s32 func_0800eaa0(void) {
    s32 out;
    s32 inc;

    if (!D_030053c0.unk1_b5) {
        return 0x100;
    }

    out = D_030053c0.unk170;
    inc = 0x10000 / ticks_to_frames(D_030053c0.unk16E);

    if (D_030053c0.unk1_b6) {
        out -= inc;
    } else {
        out += inc;
    }

    if (out < 0) {
        out = 0;
    }

    if (out > 0xFFFF) {
        out = 0xFFFF;
    }

    D_030053c0.unk170 = out;

    return FIXED_TO_INT(out);
}


// Stop Tempo Interpolation
void scene_tempo_interp_stop(void) {
    D_030053c0.interpolatingTempo = FALSE;
}


// Update Tempo Interpolation
void scene_tempo_interp_update(void) {
    s32 runningTime, duration;

    if (!D_030053c0.interpolatingTempo) {
        return;
    }

    D_030053c0.interpTempoRunningTime += func_0800c398();

    if (D_030053c0.interpTempoRunningTime >= D_030053c0.interpTempoDuration) {
        set_beatscript_tempo(D_030053c0.interpTempoTarget);
        return;
    }

    if (--D_030053c0.interpTempoFramesUntilUpdate == 0) {
        D_030053c0.interpTempoFramesUntilUpdate = 6;
        runningTime = FIXED_TO_INT(D_030053c0.interpTempoRunningTime);
        duration = FIXED_TO_INT(D_030053c0.interpTempoDuration);
        set_beatscript_tempo(D_030053c0.interpTempoInitial + ((D_030053c0.interpTempoTarget - D_030053c0.interpTempoInitial) * runningTime / duration));
        D_030053c0.interpolatingTempo = TRUE;
    }
}


// Start Tempo Interpolation
void scene_tempo_interp_start(u32 initial, u32 target, u32 duration) {
    D_030053c0.interpTempoInitial = initial;
    D_030053c0.interpTempoTarget = target;
    D_030053c0.interpTempoDuration = INT_TO_FIXED(duration);
    D_030053c0.interpTempoRunningTime = 0;
    D_030053c0.interpTempoFramesUntilUpdate = 6;
    set_beatscript_tempo(initial);
    D_030053c0.interpolatingTempo = TRUE;
}


// Change Tempo
void scene_interpolate_tempo(u32 target, u32 duration) {
    if (duration == 0) {
        set_beatscript_tempo(target);
    } else {
        scene_tempo_interp_start(get_beatscript_tempo(), target, duration);
    }
}


// Stop Music Pitch Interpolation
void scene_music_pitch_interp_stop(void) {
    D_030053c0.interpolatingMusicPitch = FALSE;
}


// Update Music Pitch Interpolation
void scene_music_pitch_interp_update(void) {
    s32 runningTime, duration;

    if (!D_030053c0.interpolatingMusicPitch) {
        return;
    }

    D_030053c0.interpPitchRunningTime += func_0800c398();

    if (D_030053c0.interpPitchRunningTime >= D_030053c0.interpPitchDuration) {
        scene_set_music_pitch(D_030053c0.interpPitchTarget);
        return;
    }

    runningTime = FIXED_TO_INT(D_030053c0.interpPitchRunningTime);
    duration = FIXED_TO_INT(D_030053c0.interpPitchDuration);
    scene_set_music_pitch(D_030053c0.interpPitchInitial + ((D_030053c0.interpPitchTarget - D_030053c0.interpPitchInitial) * runningTime / duration));
    D_030053c0.interpolatingMusicPitch = TRUE;
}


// Start Music Pitch Interpolation
void scene_music_pitch_interp_start(s32 initial, s32 target, u32 duration) {
    D_030053c0.interpPitchInitial = initial;
    D_030053c0.interpPitchTarget = target;
    D_030053c0.interpPitchDuration = INT_TO_FIXED(duration);
    D_030053c0.interpPitchRunningTime = 0;
    scene_set_music_pitch(initial);
    D_030053c0.interpolatingMusicPitch = TRUE;
}


// Change Music Pitch
void scene_interpolate_music_pitch(s32 target, u32 duration) {
    scene_music_pitch_interp_start(D_030053c0.musicPitchSrc1, target, duration);
}


// Enable/Disable Music Envelope Interpolation
void scene_set_music_interp_enabled(u32 enable) {
    D_030053c0.musicInterpolationEnabled = enable;
}


// Fade Music In
void scene_fade_music_in(u32 duration) {
    fade_in_soundplayer(D_030053c0.musicPlayer, duration);
}


// Fade Music Out
void scene_fade_music_out(u32 duration) {
    fade_out_soundplayer(D_030053c0.musicPlayer, duration);
}


// Stub
void func_0800ed54_stub(void) {
}


// Stub
void func_0800ed58_stub(void) {
}


// Stub
void func_0800ed5c_stub(void) {
}


// Stub
void func_0800ed60_stub(u32 speed) {
}


u16 *func_0800ed64(u16 arg0, u16 arg1, u16 arg2) {
    u16 *gradientBuffer = mem_heap_alloc_id(get_current_mem_id(), 160 * sizeof(u16));
    func_0800edc8(gradientBuffer, arg0, arg1, arg2);
    func_0800402c(gradientBuffer, ((u16 *)PaletteRAMBase) + arg2, 1, 0);
    //return gradientBuffer; // ?
}


// Deallocate Memory
void func_0800edb8(void *data) {
    mem_heap_dealloc(data);
    func_08004058();
}


void func_0800edc8(u16 *gradientBuffer, u16 arg1, u16 arg2, u16 arg3) {
    u32 i;

    for (i = 0; i < 160; i++) {
        gradientBuffer[i] = get_blended_color(arg1, arg2, fast_divsi3(INT_TO_FIXED(i), INT_TO_FIXED(0.625)));
    }
}


// Write BG Palette to Graphics Buffer (0-15)
void func_0800edfc(void *bgPalette) {
    dma3_set(bgPalette, D_03004b10.bgPalette, 0x200, 0x10, 0x100);
}


// Write OBJ Palette to Graphics Buffer (0-15)
void func_0800ee1c(void *objPalette) {
    dma3_set(objPalette, D_03004b10.objPalette, 0x200, 0x10, 0x100);
}


// Write BG Palette to Graphics Buffer (0-9)
void func_0800ee3c(void *bgPalette) {
    dma3_set(bgPalette, D_03004b10.bgPalette, 0x140, 0x10, 0x100);
}


// Write OBJ Palette to Graphics Buffer (0-9)
void func_0800ee5c(void *objPalette) {
    dma3_set(objPalette, D_03004b10.objPalette, 0x140, 0x10, 0x100);
}


// Write BG Palette to Graphics Buffer (12-15)
void func_0800ee7c(void *bgPalette) {
    dma3_set(bgPalette, D_03004b10.bgPalette[12], 0x80, 0x10, 0x100);
}


// Write OBJ Palette to Graphics Buffer (12-15)
void func_0800ee9c(void *objPalette) {
    dma3_set(objPalette, D_03004b10.objPalette[12], 0x80, 0x10, 0x100);
}


#include "asm/code_0800b778/asm_0800eebc.s"


// Set String
void func_0800f070(u32 id, const char *string) {
    D_030053c0.strings[id] = string;
}


// Clear Strings
void func_0800f084(void) {
    u32 i;

    for (i = 0; i < 10; i++) {
        func_0800f070(i, NULL);
    }
}


// Set OBJ Font Parsing/Filtering Function
void func_0800f09c(struct BitmapFontOBJ *objFont) {
    bmp_font_obj_set_format_parser(objFont, func_0800eebc, 0x101);
}


// Split here

struct struct_0800f0b4 *func_0800f0b4(u32 arg0, u32 arg1, u16 *arg2, u32 arg3, u16 arg4, s32 arg5) {
    struct struct_0800f0b4 *temp_r7;
    u32 i, i1;

    temp_r7 = scene_mem_heap_alloc(sizeof(struct struct_0800f0b4));
    temp_r7->unk0 = get_current_mem_id();
    temp_r7->unk4 = arg2;
    temp_r7->unk48 = arg0;
    temp_r7->unk4A = arg1;
    temp_r7->unk4C = arg1 - arg0;
    temp_r7->unk8 = scene_mem_heap_alloc(temp_r7->unk4C * 16);
    temp_r7->unk4F = arg3;
    temp_r7->unk78 = arg4;
    temp_r7->unk50 = scene_mem_heap_alloc(arg3 * sizeof(struct struct_0800f0b4_sub));
    for (i1 = 0; i1 < arg3; i1++) {
        temp_r7->unk50[i1].unk0 |= -1;
    }

    i = 0;
    do {
        s8 temp_r1 = func_08002194(get_current_mem_id());
        if (temp_r1 < 0) {
            break;
        }
        temp_r7->unk54[i] = temp_r1;
        i++;
    } while (i < arg5);
    temp_r7->unk4E = i;
    temp_r7->unk74 = scene_mem_heap_alloc(i * 8);
    func_0800402c(arg2, (u16 *)&REG_BG2PA, 8, 0);
    return temp_r7;
}


void func_0800f180(struct struct_0800f0b4 *arg0) {
    u32 i;
    
    func_08004058();
    for (i = 0; i < arg0->unk4F; i++) {
        func_0800f89c(arg0, (s16)i);
    }
    for (i = 0; i < arg0->unk4E; i++) {
        func_080021b8(arg0->unk54[i]);
    }
    mem_heap_dealloc(arg0->unk8);
    mem_heap_dealloc(arg0->unk50);
    mem_heap_dealloc(arg0->unk74);
    mem_heap_dealloc(arg0);
}


void func_0800f1ec(struct struct_0800f0b4 *arg0) {
    dma3_set(arg0->unk8, &arg0->unk4[arg0->unk48 * 8], arg0->unk4C * 16, 32, 0x100);
}


void func_0800f218(struct struct_0800f0b4 *arg0) {
    func_0800f22c(arg0);
    func_0800f614(arg0);
}


#define sins3(x) D_08935fcc[(x)]
#define coss3(x) D_089361cc[(x)]

void func_0800f22c(struct struct_0800f0b4 *arg0) {
    struct struct_0800f0b4_sub1 *sp0;
    struct struct_0800f0b4_sub2 *temp_r5;
    struct struct_0800f0b4_sub3 *temp_r8;
    s32 temp_r0;
    s32 temp_r0_1;
    s32 temp_r0_2;
    s24_8 sp4;
    s24_8 sp8;
    s24_8 spC;
    s24_8 sp10;
    s24_8 sp14;
    s24_8 sp18;
    s24_8 sp1C;
    s24_8 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 temp_r4;
    s32 sp30;
    s32 temp_r9;
    s32 sp34;
    s32 sp38;
    s32 temp_r6;

    sp0 = &arg0->unkC;

    // something weird going on here
    temp_r0 = *(u8 *)&arg0->unk18;
    sp4 = sins2(*(u8 *)&arg0->unk18);
    sp8 = coss2(*(u8 *)&arg0->unk18);
    spC = sins2(arg0->unk1A);
    sp10 = coss2(arg0->unk1A);
    sp14 = sins3(arg0->unk1C >> 1);
    sp18 = coss3(arg0->unk1C >> 1);
    sp1C = sins3(arg0->unk1E >> 1);
    sp20 = coss3(arg0->unk1E >> 1);

    sp24 = fast_divsi3(INT_TO_FIXED(sp0->unk4), -spC);
    sp28 = Div(INT_TO_FIXED(sp18 * 15) * 8, sp14);
    sp2C = fast_divsi3(sp0->unk4 * sp10, -spC);
    temp_r4 = fast_divsi3(sp28 * sp1C, sp20);
    sp30 = fast_divsi3(-temp_r4 - temp_r4, INT_TO_FIXED(0.625));
    temp_r9 = temp_r4 + arg0->unk48 * sp30;
    sp34 = -fast_divsi3(sp28 * sp14, sp18);
    sp38 = (arg0->unk1A >= -arg0->unk1E) ? FIXED_TO_INT(fast_divsi3(sp28 * spC, sp10)) + 80 : 0;

    temp_r5 = arg0->unk8;
    for (temp_r6 = arg0->unk48; temp_r6 < arg0->unk4A; temp_r6++) {
        if (temp_r6 < sp38) {
            temp_r5->unkC = 0;
            temp_r5->unk8 = 0;
            temp_r5->unk4 = 0;
            temp_r5->unk0 = 0;
        } else {
            s32 temp_r0_l;
            s32 temp_r2_l;
            s32 temp_r3_l;
            s32 temp_r4_l;

            temp_r0_l = fast_divsi3(INT_TO_FIXED(sp24), FIXED_TO_INT((sp28 * spC) + (temp_r9 * sp10)));
            temp_r4_l = FIXED_TO_INT(temp_r0_l * spC);
            temp_r2_l = sp2C - FIXED_TO_INT(temp_r9 * temp_r0_l);
            temp_r3_l = FIXED_TO_INT(sp34 * temp_r4_l);

            temp_r5->unk8 = sp0->unk0 + FIXED_TO_INT((temp_r2_l * sp8) - (temp_r3_l * sp4));
            temp_r5->unkC = sp0->unk8 + FIXED_TO_INT((temp_r2_l * sp4) + (temp_r3_l * sp8));
            temp_r5->unk0 = FIXED_TO_INT(-temp_r4_l * sp4);
            temp_r5->unk4 = FIXED_TO_INT(temp_r4_l * sp8);
        }

        temp_r9 += sp30;
        temp_r5++;
    }

    temp_r8 = &arg0->unk20;
    temp_r8->unk0 = FIXED_TO_INT(sp8 * sp10);
    temp_r8->unk2 = spC;
    temp_r8->unk4 = FIXED_TO_INT(sp4 * sp10);
    temp_r8->unk6 = FIXED_TO_INT(-sp8 * spC);
    temp_r8->unk8 = sp10;
    temp_r8->unkA = FIXED_TO_INT(-sp4 * spC);
    temp_r8->unkC = -sp4;
    temp_r0 = 0;
    temp_r8->unkE = 0;
    temp_r8->unk10 = sp8;
    arg0->unk34 = FIXED_TO_INT(sp8 * sp10);
    arg0->unk38 = spC;
    arg0->unk3C = FIXED_TO_INT(sp4 * sp10);
    temp_r0_1 = fast_divsi3(((sp18 * 16) - sp18) * 8, sp14);
    arg0->unk40 = ABS(temp_r0_1);
    temp_r0_2 = fast_divsi3(INT_TO_FIXED((sp20 * 4) + sp20), sp1C);
    arg0->unk44 = ABS(temp_r0_2);
}


void func_0800f4a0(struct struct_0800f0b4 *arg0, s32 *arg1, s32 *arg2) {
    struct struct_0800f0b4_sub3 *temp_r3;
    s32 temp_r4;
    s32 temp_r5;
    s32 temp_r6;
    struct struct_0800f0b4_sub1 *temp_r8;

    temp_r3 = &arg0->unk20;
    temp_r8 = &arg0->unkC;
    temp_r6 = arg1[0] - temp_r8->unk0;
    temp_r4 = arg1[1] - temp_r8->unk4;
    temp_r5 = arg1[2] - temp_r8->unk8;
    arg2[0] = FIXED_TO_INT(temp_r3->unk0 * temp_r6 + temp_r3->unk2 * temp_r4 + temp_r3->unk4 * temp_r5);
    arg2[1] = FIXED_TO_INT(temp_r3->unk6 * temp_r6 + temp_r3->unk8 * temp_r4 + temp_r3->unkA * temp_r5);
    arg2[2] = FIXED_TO_INT(temp_r3->unkC * temp_r6 + temp_r3->unkE * temp_r4 + temp_r3->unk10 * temp_r5);
}


void func_0800f524(struct struct_0800f0b4 *arg0, s32 *arg1, u16 *arg2) {
    if (arg1[0] <= 0) {
        arg2[2] = 0;
        arg2[1] = 0;
        arg2[0] = 0;
    } else {
        arg2[0] = fast_divsi3(arg1[2] * arg0->unk40, arg1[0]) + 120;
        arg2[1] = 80 - (fast_divsi3(arg1[1] * arg0->unk44, arg1[0]) >> 4);
        arg2[2] = fast_divsi3(arg1[0], arg0->unk40);
    }
}


void func_0800f570(struct struct_0800f0b4 *arg0, u32 arg1, u32 arg2, u32 arg3) {
    arg0->unkC.unk0 = arg1;
    arg0->unkC.unk4 = arg2;
    arg0->unkC.unk8 = arg3;
}


void func_0800f578(struct struct_0800f0b4 *arg0, s32 arg1, s32 arg2) {
    arg0->unk18 = arg1;
    arg0->unk1A = arg2;
}


void func_0800f580(struct struct_0800f0b4 *arg0, s32 arg1, s32 arg2) {
    arg0->unk1C = arg1;
    arg0->unk1E = arg2;
}


void func_0800f588(struct struct_0800f0b4 *arg0, u32 arg1) {
    s32 i1;
    s32 i;
    u8 *temp_r5;
    struct struct_0800f0b4_sub *temp_r7;
    
    temp_r5 = arg0->unk7B;
    temp_r7 = &arg0->unk50[arg1];

    for (i = 0; i < arg0->unk7A; i++) {
        u32 temp_r1 = temp_r5[i];
        struct struct_0800f0b4_sub *temp_r0 = &arg0->unk50[temp_r1];
        if (temp_r0->unk10[0] > temp_r7->unk10[0]) {
            break;
        }
    }
    if (i >= arg0->unk4E) {
        return;
    }
    for (i1 = arg0->unk4E - 2; i1 >= i; i1--) {
        temp_r5[i1 + 1] = temp_r5[i1];
    }
    temp_r5[i] = arg1;
    if (arg0->unk7A < arg0->unk4E) {
        arg0->unk7A++;
    }
}


void func_0800f614(struct struct_0800f0b4 *arg0) {
    struct struct_0800f0b4_sub *temp_r6;
    u32 i;
    s8 *temp_sl;

    arg0->unk7A = 0;
    temp_r6 = arg0->unk50;
    for (i = 0; i < arg0->unk4F; i++, temp_r6++) {
        if (temp_r6->unk0 >= 0) {
            func_0800f4a0(arg0, temp_r6->unk4, temp_r6->unk10);
            func_0800f524(arg0, temp_r6->unk10, temp_r6->unk1C);
            if ((!temp_r6->unk1C[2]) || 
                (temp_r6->unk1C[0] < (-0x400000 >> 0x10)) || (temp_r6->unk1C[0] > 0x130) || 
                (temp_r6->unk1C[1] < (-0x400000 >> 0x10)) || (temp_r6->unk1C[1] > 0xe0)) {
                continue;
            }    
            func_0800f588(arg0, i);
        }
    }
    
    temp_r6 = arg0->unk50;
    for (i = 0; i < arg0->unk4F; temp_r6++, i++) {
        s16 sprite = temp_r6->unk0;
        if (sprite >= 0) {
            sprite_set_visible(gSpriteHandler, sprite, FALSE);
        }
    }

    temp_sl = arg0->unk54;
    for (i = 0; i < arg0->unk7A; temp_sl++, i++) {
        s16 temp_r4;
        s16 sprite;
        
        temp_r6 = &arg0->unk50[arg0->unk7B[i]];
        sprite = temp_r6->unk0;
        sprite_set_x_y_z(gSpriteHandler, sprite, temp_r6->unk1C[0], temp_r6->unk1C[1], arg0->unk78 + i);
        sprite_set_affine_params(gSpriteHandler, sprite, *temp_sl, (s16 *)func_08002520(*temp_sl));
        temp_r4 = FIXED_TO_INT(temp_r6->unk1C[2] * temp_r6->unk24);
        func_080024dc(*temp_sl, temp_r4, 0);
        if (temp_r4 > 0xff) {
            func_0804dc8c(gSpriteHandler, sprite, 1);
            sprite_set_visible(gSpriteHandler, sprite, TRUE);
        } else if (temp_r4 > 0x7f) {
            func_0804dc8c(gSpriteHandler, sprite, 3);
            sprite_set_visible(gSpriteHandler, sprite, TRUE);
        } else {   
            sprite_set_visible(gSpriteHandler, sprite, FALSE);
        }
    }
}


s16 func_0800f7c0(struct struct_0800f0b4 *arg0, struct Animation *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 arg6, s32 arg7, s32 arg8) {
    s16 i;
    struct struct_0800f0b4_sub *temp_r5;

    temp_r5 = arg0->unk50;
    for (i = 0; i < arg0->unk4F; i++, temp_r5++) {
        if (temp_r5->unk0 < 0) {
            u16 temp_r4;

            temp_r4 = sprite_handler_get_mem_id(gSpriteHandler);
            sprite_handler_set_mem_id(gSpriteHandler, arg0->unk0);
            temp_r5->unk0 = sprite_create(gSpriteHandler, arg1, 0, 0, 0, 0, 1, SPRITE_PLAYBACK_NORMAL_LOOP, 0);
            sprite_set_visible(gSpriteHandler, temp_r5->unk0, FALSE);
            temp_r5->unk4[0] = arg3;
            temp_r5->unk4[1] = arg4;
            temp_r5->unk4[2] = arg5;
            temp_r5->unk24 = arg6;
            temp_r5->unk28 = arg1;
            temp_r5->unk2C = arg2;
            sprite_handler_set_mem_id(gSpriteHandler, temp_r4);
            return i;
        }
    }
    return -1;
}


void func_0800f89c(struct struct_0800f0b4 *arg0, s16 arg1) {
    if ((arg1 >= 0)) {
        s16 sprite = arg0->unk50[arg1].unk0;

        if (sprite >= 0) {
            sprite_delete(gSpriteHandler, sprite);
            arg0->unk50[arg1].unk0 = -1;
        }
    }
}


s16 func_0800f8d8(struct struct_0800f0b4 *arg0, s16 arg1) {
    return arg0->unk50[arg1].unk0;
}


void func_0800f8ec(struct struct_0800f0b4 *arg0) {
    func_0800f22c(arg0);
}


void func_0800f8f8(struct struct_0800f0b4 *arg0, u32 arg1) {
    func_0800f588(arg0, arg1);
}
