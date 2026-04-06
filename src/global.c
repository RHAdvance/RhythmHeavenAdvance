#include "global.h"
#include "graphics.h"
#include "memory_heap.h"
#include "midi/midi.h"
#include "scenes/cafe.h"
#include "scenes/riq_main_scene.h"
#include "lib_sram.h"
#include "lib_0804e564.h"

/* Interrupt Handler */
COMMON_DATA void *interrupt_handler_jtbl[14] = {0};
COMMON_DATA u8 D_03004498 = 0;
COMMON_DATA __attribute__((aligned(8))) u32 interrupt_handler[0x80] = {0};

/* Main Game State */
COMMON_DATA s32 D_030046a0 = 0;
COMMON_DATA void* gCurrentSceneData = 0;
COMMON_DATA struct SaveBuffer* D_030046a8 = 0;

/* Internal Library */
COMMON_DATA __attribute__((aligned(8))) u16 D_030046b0 = 0;
COMMON_DATA u16 D_030046b4 = 0;
COMMON_DATA u16 D_030046b8 = 0;
COMMON_DATA __attribute__((aligned(8))) Palette D_030046c0[32] = {0};
COMMON_DATA u16 D_03004ac0 = 0;
COMMON_DATA __attribute__((aligned(16))) struct struct_03004ad0 D_03004ad0 = {0};
COMMON_DATA s32 (*math_sqrt)(s32) = 0;
COMMON_DATA u8 sSceneTextCurrentStringId = 0;
COMMON_DATA s16 D_03004aec = 0;
COMMON_DATA s32 (*D_03004af0)(const u16 *src, u16 *dest, const u8 *rleData, u32 sizeData) = 0;
COMMON_DATA u16 D_03004af4 = 0;
COMMON_DATA u32 (*fast_udivsi3)(u32 dividend, u32 divisor) = 0;
COMMON_DATA u16 D_03004afc = 0;
COMMON_DATA u16 D_03004b00 = 0;
COMMON_DATA __attribute__((aligned(16))) struct GraphicsBuffer D_03004b10 = {0};
COMMON_DATA struct BufferedTextureEntry *D_0300536c = NULL;
COMMON_DATA s16 D_03005370 = 0;
COMMON_DATA u32 sRecMaxKeys = 0;
COMMON_DATA u16 D_03005378 = 0;

/* Input/Graphics Library */
COMMON_DATA u16 D_0300537c = 0;
COMMON_DATA struct SpriteHandler *gSpriteHandler = NULL;
COMMON_DATA __attribute__((aligned(16))) u32 D_03005390[8] = {0};
COMMON_DATA u8 D_030053b0 = 0;
COMMON_DATA u32 sRecCurrentKey = 0;
COMMON_DATA u16 D_030053b8 = 0;
COMMON_DATA __attribute__((aligned(16))) struct BeatscriptScene D_030053c0 = {0};
COMMON_DATA u32 *D_03005588 = NULL;
COMMON_DATA s16 *D_0300558c = NULL;

/* Rhythm Tengoku Global */
COMMON_DATA u32 D_03005590 = 0;
COMMON_DATA __attribute__((aligned(16))) struct PlaySessionInfo gSessionInfo = {0};
COMMON_DATA void *gCurrentEngineData = NULL;
COMMON_DATA u32 D_030055d4 = 0;
COMMON_DATA s8 sMainMenuButton = 0;
COMMON_DATA __attribute__((aligned(8))) struct PauseMenu gPauseMenu = {0};

/* Sound Library */
COMMON_DATA __attribute__((aligned(16))) u16 gMidiVCOUNTAtStart = 0;
COMMON_DATA u32 gMidiSoundMode = 0;
COMMON_DATA __attribute__((aligned(16))) s32 gMidiReverbScratch[4] = {0};
COMMON_DATA u16 gMidiSamplerCount = 0;
COMMON_DATA __attribute__((aligned(16))) s32 gMidiEQArea[3] = {0};
COMMON_DATA u32 gMidiPlayerNewDeltaTime = 0;
COMMON_DATA u32 gMidiReverb2Phase = 0;
COMMON_DATA u32 gMidiReverb4LowCut = 0;
COMMON_DATA u32 gMidiScratchSize = 0;
COMMON_DATA volatile u32 *gMidiPCMBufR = NULL;
COMMON_DATA u8 gMidiLFODepth = 0;
COMMON_DATA struct SoundPlayer *gMidiLFOPlayer = NULL;
COMMON_DATA u16 gMidiCommVarCurrent = 0;
COMMON_DATA __attribute__((aligned(8))) struct MidiNote gMidiNotePool[20] = {0};
COMMON_DATA struct SoundChannel gMidiPSGChannelPool[TOTAL_PSG_CHANNELS] = {0};
COMMON_DATA s8 gMidiSampleTable[0x400] = {0};
COMMON_DATA u16 gMidiCommVarTotal = 0;
COMMON_DATA volatile u32 gMidiPCMBufSize32 = 0;
COMMON_DATA u8 gMidiEQHighGain = 0;
COMMON_DATA __attribute__((aligned(8))) struct LFO gMidiLFO = {0};
COMMON_DATA u8 gMidiLFOMode = 0;
COMMON_DATA volatile u32 gMidiPCMBufWritePos = 0;
COMMON_DATA u8 gMidiEQIsGlobal = 0;
COMMON_DATA u32 gMidiReverb3Decay = 0;
COMMON_DATA __attribute__((aligned(8))) u32 gMidiARM_FuncTable[10] = {0};
COMMON_DATA u16 gMidiNoteNext = 0;
COMMON_DATA u8 *gMidiCommVars = NULL;
COMMON_DATA u16 gMidiVCOUNTAtEnd = 0;
COMMON_DATA u16 gMidiVCOUNTAtSamplerEnd = 0;
COMMON_DATA struct SampleStream *gMidiSamplerPool = NULL;
COMMON_DATA u16 gMidiSoundChannelCount = 0;
COMMON_DATA s8 gMidiReverbControls[4] = {0};
COMMON_DATA u32 gMidiDMASampleRate = 0;
COMMON_DATA __attribute__((aligned(16))) u32 gMidiARM_FuncArea[0x240] = {0};
COMMON_DATA volatile u32 gMidiPCMBufReadPos = 0;
COMMON_DATA u32 gMidiReverb1Wet = 0;
COMMON_DATA u32 gMidiSamplesPerFrame = 0;
COMMON_DATA u16 gMidiSamplerGain = 0;
COMMON_DATA s32 *gMidiSampleScratch = NULL;
COMMON_DATA u32 gMidiTM0Rate = 0;
COMMON_DATA volatile u32 *gMidiPCMBufL = NULL;
COMMON_DATA struct SoundChannel *gMidiSoundChannelPool = NULL;
COMMON_DATA s8 gMidiEQPrevPos = 0;
COMMON_DATA u16 gMidiDirectSoundEnabled = 0;

/* SRAM Library */
COMMON_DATA void (*read_sram_fast)(const u8 *src, u8 *dest, u32 size) = NULL;
COMMON_DATA void (*write_int_sram_fast)(const u8 *src, u8 *dest, u32 size) = NULL;
COMMON_DATA void (*verify_sram_fast)(const u8 *src, u8 *dest, u32 size) = NULL;

/* lib_0804e564 */
COMMON_DATA s32 (*D_030064d4)(void) = NULL;