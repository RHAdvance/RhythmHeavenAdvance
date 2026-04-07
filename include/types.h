#pragma once

#define DPAD_ALL (DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN)
#define DPAD_ANY DPAD_ALL


/* Math Util. */


struct Vector2 {
    s16 x;
    s16 y;
};

extern s8_8 gSineTable[];
extern s8_8 D_08935fcc[];
extern s8_8 D_089361cc[];


/* Beatscript Scene Engine */


// A Singular Beatscript Instruction
struct Beatscript {
    u32 command:8;
    u32 param1:24;
    u32 param2;
    u32 param3;
};

// Scene Data
struct Scene {
	void (*initFunc)();
	void *initParam;
	u32 (*loopFunc)();
	void *loopParam;
	void (*endFunc)();
	void *endParam;
	u16 requiredMemory;
};

// SubScene Data
struct SubScene {
	void (*startFunc)();
	s32 startParam;
	void (*pausedFunc)();
    s32 pausedParam;
	void (*updateFunc)();
	s32 updateParam;
	void (*stopFunc)();
	s32 stopParam;
    const struct Beatscript *script;
};

// Active SubScene
struct BeatscriptThread {
    u8 active:1;
    u8 stackCounter:4;
    u8 startDelay:2;
    u8 unk0_b7:1;
    const struct SubScene *subScene;
    const struct Beatscript *currentCmd;
    s24_8 timeUntilNext; // Time until next instruction (in Q24.8 Beats)
    const struct Beatscript *jumpStack[8];
    u8 unk30[0x20];
    const struct Beatscript *loopStart;
    u16 unk54;
    s16 sprites[0x20];
    u16 unk96;
    s32 currentTaskID;
};

// Beatscript Handler
extern struct BeatscriptScene {
    u32 mode:4;
    u32 bypassLoops:1;
    u32 exitLoopNextUpdate:1;
    u32 unk0_b6:1;
    u32 unk0_b7:1;
    u32 paused:1;
    u32 currentThread:3;
    u32 unk1_b4:1;
    u32 unk1_b5:1;
    u32 unk1_b6:1;
    u32 interpolatingTempo:1;
    u32 interpolatingMusicPitch:1;
    u32 musicInterpolationEnabled:1;
    u32 isLocalized:1;
    struct SoundPlayer *musicPlayer; // [D_030053c4] Music Player
    u16 musicBaseBPM;
    u16 scriptBaseBPM;
    u16 scriptBPM; // [D_030053cc] Tempo after Speed Multiplication
    u8_8 scriptSpeed; // [Q8.8] Speed Multiplier
    u8_8 spriteAnimSpeed; // [Q8.8] (currentTempo / 140)
    s24_8 deltaTime; // [D_030053d4] Script Ticks per Game Update ([Q8.8] (currentTempo / 150))
    s24_8 runningTime;
    u8  unk1C;
    s8_8 musicPitchSrc1;
    s8_8 musicPitchSrc2;
    s8_8 musicPitch;
    u32 globalVariable; // [D_030053c0 + 0x24] Global (Main Scene) Variable
    struct BeatscriptThread threads[2];
    u32 localVariables[2]; // [D_030053c0 + 0x160] Local (Sub-Scene) Variables
    s16 unk168;
    u16 unk16A;
    u16 unk16C;
    u16 unk16E;
    u16 unk170;
    s16 interpTempoInitial;
    s16 interpTempoTarget;
    u24_8 interpTempoDuration;
    u24_8 interpTempoRunningTime;
    u16 interpTempoFramesUntilUpdate;
    s16 interpPitchInitial;
    s16 interpPitchTarget;
    u24_8 interpPitchDuration;
    u24_8 interpPitchRunningTime;
    u16 musicVolume; // [D_03005550] Beatscript: Music Volume
    u16 musicTrkVolume; // [D_03005552] Beatscript: Music Channel Selection Volume
    u16 musicTrkTargets; // [D_03005554] Beatscript: Music Channel Selection
    s8  musicKey; // [D_03005556] Beatscript: Music Key
    const char *strings[10]; // [D_030053c0 + 0x198]
    void (*callbackFunction)(s32);
    s32 callbackArgument;
} D_030053c0;

extern u32 *D_03005588; // Current Scene Variable
extern s16 *D_0300558c; // Current Scene Sprite Pool
