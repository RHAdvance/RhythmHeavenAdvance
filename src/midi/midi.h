#pragma once

#include "global.h"
#include "sound.h"

// VALUES
enum PsgToneDutyEnum {
    /* 00 */ PSG_TONE_DUTY_12_5,
    /* 01 */ PSG_TONE_DUTY_25,
    /* 02 */ PSG_TONE_DUTY_50,
    /* 03 */ PSG_TONE_DUTY_75
};

enum PsgNoiseDutyEnum {
    /* 00 */ PSG_NOISE_COUNTER_15,
    /* 01 */ PSG_NOISE_COUNTER_7
};

enum ModulationTypeEnum {
    /* 00 */ MOD_TYPE_VIBRATO,
    /* 01 */ MOD_TYPE_TREMOLO,
    /* 02 */ MOD_TYPE_PANNING
};

enum AdsrStageEnum {
    /* 00 */ ADSR_STAGE_ATTACK,
    /* 01 */ ADSR_STAGE_DECAY,
    /* 02 */ ADSR_STAGE_SUSTAIN,
    /* 03 */ ADSR_STAGE_RELEASE,
    /* 04 */ ADSR_STAGE_FORCE_STOP
};

enum LfoStageEnum {
    /* 00 */ LFO_STAGE_DISABLED,
    /* 01 */ LFO_STAGE_PRE_DELAY,
    /* 02 */ LFO_STAGE_ATTACK,
    /* 03 */ LFO_STAGE_SUSTAIN
};

enum VolumeFadeTypeEnum {
    /* 00 */ VOL_FADE_RESET,
    /* 01 */ VOL_FADE_IN,
    /* 02 */ VOL_FADE_OUT_CLEAR,
    /* 03 */ VOL_FADE_OUT_PAUSE
};

enum MidiSystemExclusiveMessageEnum {
    /* 00 */ SYS_EXC_EVENT_LFO_SETTINGS,
    /* 01 */ SYS_EXC_EVENT_KEY_MOD_SCALE
};

enum MidiMetaEventTypeEnum {
    /* 00 */ META_EVENT_OTHER,
    /* 01 */ META_EVENT_TRACK_END,
    /* 02 */ META_EVENT_LOOP_START,
    /* 03 */ META_EVENT_LOOP_END
};

enum MidiTrackReaderEndEnum {
    /* 00 */ M_TRACK_READER_CONTINUE,
    /* 01 */ M_TRACK_READER_STOP,
    /* 02 */ M_TRACK_READER_LOOP
};

#define INSTRUMENT_PCM_ALIGNED  'A' // 0x41
#define INSTRUMENT_PCM_FIXED    'F' // 0x46
#define INSTRUMENT_PSG          'P' // 0x50
#define INSTRUMENT_PSG_ALT      'Q' // 0x51
#define INSTRUMENT_SUB_RHYTHM   'R' // 0x52
#define INSTRUMENT_SUB_SPLIT    'S' // 0x53

#define MSG_NOTE_OFF                    0x80
#define MSG_NOTE_ON                     0x90
#define MSG_POLYPHONIC_KEY_PRESSURE     0xA0
#define MSG_CONTROLLER_CHANGE           0xB0
#define MSG_PROGRAM_CHANGE              0xC0
#define MSG_CHANNEL_PRESSURE            0xD0
#define MSG_PITCH_WHEEL_CHANGE          0xE0

#define META_TEXT_MARKER    0x06
#define META_END_OF_TRACK   0x2F
#define META_SET_TEMPO      0x51

#define M_CONTROLLER_BANK_SELECT_MSB    0x00
#define M_CONTROLLER_MOD_DEPTH          0x01
#define M_CONTROLLER_VOLUME             0x07
#define M_CONTROLLER_PANNING            0x0A
#define M_CONTROLLER_EXPRESSION         0x0B
#define M_CONTROLLER_SELECT_VAR         0x0E
#define M_CONTROLLER_SET_VAR            0x10
#define M_CONTROLLER_PITCH_RANGE        0x14
#define M_CONTROLLER_MOD_SPEED          0x15
#define M_CONTROLLER_MOD_TYPE           0x16
#define M_CONTROLLER_MOD_DELAY          0x1A
#define M_CONTROLLER_BANK_SELECT_LSB    0x20
#define M_CONTROLLER_PRIORITY           0x21
#define M_CONTROLLER_EQ_MODE            0x48
#define M_CONTROLLER_LFO_MODE           0x49
#define M_CONTROLLER_SET_EQ             0x4A
#define M_CONTROLLER_STEREO             0x4B
#define M_CONTROLLER_LFO_GAIN           0x4C
#define M_CONTROLLER_EQ_GAIN            0x4D
#define M_CONTROLLER_RVB1_WET           0x4E
#define M_CONTROLLER_RVB2_PHASE         0x4F
#define M_CONTROLLER_RVB3_DECAY         0x50
#define M_CONTROLLER_RVB4_LOW_CUT       0x51
#define M_CONTROLLER_RANDOM_BASE_PITCH  0x52
#define M_CONTROLLER_KEY_MOD_DEPTH      0x53
#define M_CONTROLLER_KEY_MOD_SPEED      0x54

#define AUDIO_SAMPLE_RATE 13379
#define DIRECTSOUND_CHANNEL_COUNT 12
#define SOUND_PLAYER_COUNT 13
#define DMA_SAMPLE_BUFFER_SIZE 1568
#define SAMPLE_SCRATCHPAD_SIZE 0x80


// TYPES
struct MidiNote {
    u32 channel:4;
    u32 key:7;
    u32 velocity:7;
};

typedef volatile u16 *IOReg;


// STATIC VARIABLES
// extern volatile s32 sPCMBufferArea[1568 * 2 / 4];   // DIRECTSOUND - DMA Source Addresses { &sPCMBufferArea[0] = Right; &sPCMBufferArea[gMidiPCMBufSize32] = Left }
// extern s32 sPCMScratchArea[0x80 * 2];               // DIRECTSOUND - Sample Processing ScratchPad
// extern struct SampleStream sSamplerArea[12];        // DIRECTSOUND - DMA Sample Readers (12 Channels)
// extern struct SoundChannel sSoundChannelArea[12];   // DIRECTSOUND - DirectSound Channels (12 Channels)

extern u16 gMidiVCOUNTAtStart;      // MAIN - Set to REG_VCOUNT near the start of each update.
extern u32 gMidiSoundMode;          // DIRECTSOUND - Initial Sound Mode { 0 = Stereo; 1 = Mono (One Channel); 2 = Mono (Two Channels) }
extern s32 gMidiReverbScratch[4];   // REVERB - Previous Processed Samples (R+L, x2)
extern u16 gMidiSamplerCount;       // DIRECTSOUND - Number of DMA Sample Readers ( = 12)
extern s32 gMidiEQArea[3];          // FILTER EQ - [0] = Filter Setting; [1], [2] = Previous Samples (R+L)
extern u32 gMidiPlayerNewDeltaTime; // SOUNDPLAYER - New Delta Time
extern u32 gMidiReverb2Phase;       // REVERB - Stereo Phase (default = 0)
extern u32 gMidiReverb4LowCut;      // REVERB - Low Cut / High Level (default = 4)
extern u32 gMidiScratchSize;        // DIRECTSOUND - Sample Processing ScratchPad Size, in L+R pairs ( = 0x80)
extern volatile u32 *gMidiPCMBufR;  // DIRECTSOUND - REG_DMA1SAD (Right Audio Source) ( = &sPCMBufferArea)
extern u8  gMidiLFODepth;           // LFO - Multiplier [mCtrl4C]
extern struct SoundPlayer *gMidiLFOPlayer;  // LFO - Controller Sound Player (for Speed)
extern u16 gMidiCommVarCurrent;             // UNDEFINED - Current byte in gMidiCommVars to set [mCtrl0E]

extern struct MidiNote gMidiNotePool[20];   // MIDI - Note Buffer
extern struct SoundChannel gMidiPSGChannelPool[TOTAL_PSG_CHANNELS]; // PSG CHANNEL - PSG Channels { 0 = Tone+Sweep; 1 = Tone; 2 = Wave; 3 = Noise }
extern s8  gMidiSampleTable[0x400];     // DIRECTSOUND - DMA Buffer Sample = gMidiSampleTable[(ScratchPad Sample >> 7) & 0x3FF]
extern u16 gMidiCommVarTotal;           // UNDEFINED - Total Bytes in array at gMidiCommVars
extern volatile u32 gMidiPCMBufSize32;  // DIRECTSOUND - Number of 32-bit samples per DMA Source Address ( = 1568 / 4)
extern u8  gMidiEQHighGain;             // FILTER EQ - High Gain [mCtrl4C]

// extern struct LFO gMidiLFO;      // LFO - Low-Frequency Oscillator
// extern u8 gMidiLFOMode;          // LFO - Mode { 0 = Disabled; 1 = Note Triggered; 2 = Constant }
extern volatile u32 gMidiPCMBufWritePos;    // DIRECTSOUND - PCM Buffer Write Position (Update)
extern u8  gMidiEQIsGlobal;         // FILTER EQ - Enable Global Filter
extern u32 gMidiReverb3Decay;       // REVERB - Decay (default = 2)

extern u16 gMidiNoteNext;           // MIDI - Next Available MIDI Note
extern u8 *gMidiCommVars;           // UNDEFINED - (Byte at offset gMidiCommVarCurrent set by [mCtrl10])
extern u16 gMidiVCOUNTAtEnd;        // MIDI4AGB - Set to REG_VCOUNT near the end of each SoundPlayer update.
extern u16 gMidiVCOUNTAtSamplerEnd; // DIRECTSOUND - Set to REG_VCOUNT at the end of each SampleStream update loop.
extern struct SampleStream *gMidiSamplerPool;   // DIRECTSOUND - SampleStream (12 Channels, at sSamplerArea)
extern u16 gMidiSoundChannelCount;  // DIRECTSOUND - Number of DirectSound Channels ( = 12)
extern s8  gMidiReverbControls[4];  // REVERB - Reverb Controller Update Scratch
extern u32 gMidiDMASampleRate;      // MAIN - Global Sample Rate ( = 13379Hz)

extern volatile u32 gMidiPCMBufReadPos; // DIRECTSOUND - PCM Buffer Read Position (Interrupt)
extern u32 gMidiReverb1Wet;         // REVERB - Wet Level (default = 0)
extern u32 gMidiSamplesPerFrame;    // MAIN - 13379Hz / 60 (samples per frame, at 60fps)
extern u16 gMidiSamplerGain;        // DIRECTSOUND - Sampler Volume Multiplier (when EQ filter is applied)
extern s32 *gMidiSampleScratch;     // DIRECTSOUND - Sample Processing ScratchPad ( = &sPCMScratchArea)
extern u32 gMidiTM0Rate;            // MAIN - Hardware Timer 0 Value (16776921 / 13379Hz)
extern volatile u32 *gMidiPCMBufL;  // DIRECTSOUND - REG_DMA2SAD (Left Audio Source) ( = &sPCMBufferArea[gMidiPCMBufSize32] ( = &D_03001ea8))
extern struct SoundChannel *gMidiSoundChannelPool;  // DIRECTSOUND - DirectSound Channels (12 Channels, at sSoundChannelArea)
extern s8  gMidiEQPrevPos;          // FILTER EQ - Duplicate of gMidiEQArea[0] used for just one (1) singular calculation.
extern u16 gMidiDirectSoundEnabled; // DIRECTSOUND - Enable DirectSound


// DATA
extern u16 midi_tuning_table[128];      // MIDI Note to Frequency Table (A4 = 440Hz)
extern u32 midi_step_freq_table[14];    // Semitones to Frequency Table
extern s16 midi_sine_table[0x100];      // Sine Table (Q8.8)
extern s16 midi_cosine_table[0x100];    // Cosine Table (Q8.8)
extern u16 midi_psg_wave_vol_table[];
extern IOReg midi_psg_env_regs[];
extern IOReg midi_psg_freq_regs[];
extern u8 midi_psg_noise_freq_table[];
extern char midi_loop_start_sym[];
extern char midi_loop_end_sym[];

extern union Instrument *instrument_banks[];
extern u32 last_sound_player_id;

extern u8 midi_direct_player_enabled;
extern u8 midi_direct_player_bank_id;
extern u8 midi_direct_player_volume;
extern u8 midi_direct_player_priority;
extern u8 midi_direct_player_tempo;

/* ASSEMBLY */

typedef void (*ThumbFunc)();
#define ALIGN_THUMB_FUNC(x) (ThumbFunc)((u32)&x|1)

extern ThumbFunc midi_asm_init_mode;
extern ThumbFunc midi_asm_read_pcm_accurate;
extern ThumbFunc midi_asm_update_scratch;
extern ThumbFunc midi_asm_update_buffer;
extern ThumbFunc midi_asm_read_pcm_fixed;
extern ThumbFunc midi_asm_read_pcm_fast;
extern ThumbFunc midi_asm_apply_eq;

/* INTERRUPT_DMA2 */

extern void midi_interrupt_dma2(void);

/* DIRECTSOUND STREAM OPERATIONS */

extern void midi_sampler_load(u32 id, struct SampleData *sampleData);
extern void midi_sampler_start(u32 id);
extern void midi_sampler_stop(u32 id);
extern void midi_sampler_set_stereo_bias(u32 id, u32 left, u32 right);
extern void midi_sampler_set_volume(u32 id, u32 volume);
extern void midi_sampler_set_frequency(u32 id, u32 frequency);
extern void midi_sampler_set_enable_fast_resample(u32 id, u32 enable);
extern void midi_sampler_set_enable_eq(u32 id, u32 enable);

/* DIRECTSOUND OPERATIONS */

extern void midi_directsound_init(u32 soundMode, u32 sampleRate, u32 bufferSize, volatile s32 *buffer, u32 scratchSize,
                                    s32 *scratch, u16 samplerCount, struct SampleStream *samplerPool);
extern void midi_directsound_update(void);
extern void midi_directsound_flush(void);
extern void midi_directsound_set_reverb(u32 rvb0, u32 rvb1, u32 rvb2, u32 rvb3);
extern u32  midi_sampler_is_active(u32 id);
extern void midi_equalizer_set_position(u32 position);
extern void midi_equalizer_set_high_gain(u8 gain);
extern void midi_equalizer_init(void);
extern void midi_equalizer_reset(void);
extern void midi_equalizer_set(u32 enable, u32 position, u32 gain);

/* MIDI BUS UPDATE OPERATIONS */

extern void midi_channel_update_mod(struct MidiBus *midiBus, u32 track);
extern void midi_channel_update_mod_all(struct MidiBus *midiBus);
extern void midi_channel_cut(struct MidiBus *midiBus, u32 track);
extern void midi_channel_stop(struct MidiBus *midiBus, u32 track);
extern void midi_channel_cut_all(struct MidiBus *midiBus);
extern void midi_channel_stop_all(struct MidiBus *midiBus);
extern void midi_channel_stop_psg(struct MidiBus *midiBus, u32 track);
extern void midi_channel_stop_psg_all(struct MidiBus *midiBus);

/* MIDI BUS INITIALISATION OPERATIONS */

extern void midi_bus_set_priority(struct MidiBus *midiBus, u8 priority);
extern void midi_bus_set_track_volume(struct MidiBus *midiBus, u8 volume, u16 mask);
extern void midi_channel_init(struct MidiChannel *midiChannel);
extern void midi_bus_init(struct MidiBus *midiBus, u32 totalChannels, struct MidiChannel *midiChannelArray);
extern void midi_bus_set_bank(struct MidiBus *midiBus, union Instrument *instrumentBank);

/* SOUND CHANNEL OPERATIONS */

extern u32  midi_note_update_pitch(struct SoundChannel *soundChannel);
extern u32  midi_note_update_volume(struct SoundChannel *soundChannel);
extern u32  midi_note_update_adsr(struct SoundChannel *soundChannel);
extern void midi_note_update_id(u32 id);
extern void midi_note_update_all(void);
extern void midi_note_init(u32 totalChannels, struct SoundChannel *soundChannelPool);
extern s32  midi_note_get_first_active(struct MidiChannel *midiChannel, u8 key);
extern s32  midi_note_get_first_inactive(void);
extern s32  midi_note_get_quietest_released(void);
extern s32  midi_note_get_quietest_unreleased(void);
extern s32  midi_note_get_least_significant(struct MidiBus *midiBus, u32 track, u32 velocity);
extern void midi_note_stop(struct MidiBus *midiBus, u32 track, u8 key);
extern s32  midi_note_get_free(struct MidiBus *midiBus, u32 track, u8 key, u8 velocity);
extern u8   midi_get_stereo_bias_r(u8 panning);
extern u8   midi_get_stereo_bias_l(u8 panning);
// extern u32 midi_key_to_freq(struct MidiBus *midiBus, u8 key);
extern void midi_note_start(struct MidiBus *midiBus, u32 track, u8 key, u8 velocity);

/* MIDI CHANNEL OPERATIONS */

extern void midi_channel_set_pitch(struct MidiBus *midiBus, u32 track, u16 pitch);
extern void midi_channel_set_volume(struct MidiBus *midiBus, u32 track, u8 volume);
extern void midi_channel_set_panning(struct MidiBus *midiBus, u32 track, u8 panning);
extern u8   midi_channel_get_panning(struct MidiBus *midiBus, u32 track);
extern void midi_channel_update_panning(struct MidiBus *midiBus, u32 track);
extern void midi_channel_set_patch(struct MidiBus *midiBus, u32 track, u8 patch);
extern void midi_channel_set_expression(struct MidiBus *midiBus, u32 track, u8 expression);
extern void midi_channel_set_bankselect(struct MidiBus *midiBus, u32 track, u16 args);
extern void midi_channel_set_disable(struct MidiBus *midiBus, u32 track, u8 disable);
extern void midi_channel_set_mod_depth(struct MidiBus *midiBus, u32 track, u8 depth);
extern void midi_channel_set_unk4_b21(struct MidiBus *midiBus, u32 track, u8 arg);
extern void midi_channel_set_enable_filter_eq(struct MidiBus *midiBus, u32 track, u8 useFilter);
extern void midi_channel_set_mod_type(struct MidiBus *midiBus, u32 track, u8 type);
extern void midi_channel_set_mod_range(struct MidiBus *midiBus, u32 track, u8 arg);
extern void midi_channel_set_mod_speed(struct MidiBus *midiBus, u32 track, u16 speed);
extern void midi_channel_set_mod_delay(struct MidiBus *midiBus, u32 track, u8 delay);
extern void midi_channel_set_pitch_range(struct MidiBus *midiBus, u32 track, u8 range);
extern void midi_channel_set_stereo_phase(struct MidiBus *midiBus, u32 track, u32 isStereo);
extern void midi_channel_set_priority(struct MidiBus *midiBus, u32 track, u8 priority);
extern void midi_channel_set_random_pitch(struct MidiBus *midiBus, u32 track, u8 range);
extern void midi_channel_set_random_key_mod_depth(struct MidiBus *midiBus, u32 track, u8 maxOffset);
extern void midi_channel_set_random_key_mod_speed(struct MidiBus *midiBus, u32 track, u8 interval);

/* MIDI BUS OPERATIONS */

extern void midi_bus_set_key(struct MidiBus *midiBus, s8 key);
extern void midi_bus_set_volume(struct MidiBus *midiBus, u8 volume);
extern void midi_bus_set_panning(struct MidiBus *midiBus, s8 panning);
extern void midi_bus_set_pitch(struct MidiBus *midiBus, s16 pitch);
extern void midi_bus_set_pitch_range(struct MidiBus *midiBus, u8 range);
extern void midi_bus_set_unk8(struct MidiBus *midiBus, u16 arg);
extern void midi_bus_set_tuning(struct MidiBus *midiBus, u16 *table);

/* LOW-FREQUENCY OSCILLATOR OPERATIONS */

extern void midi_lfo_init(struct LFO *lfo, u8 delay, u8 attack, u8 period, u8 offset, u8 endPos);
extern void midi_lfo_start(struct LFO *lfo);
extern void midi_lfo_stop(struct LFO *lfo);
extern void midi_lfo_update(struct LFO *lfo, u32 clocksPassed);

/* RANDOM */

extern u32  midi_random(u16 range);

/* PSG CHANNEL OPERATIONS */

extern void midi_psg_init(void);
extern void midi_psg_start_id(u32 id);
extern u32  midi_psg_get_frequency(u32 freq);
extern u32  midi_psg_get_volume(u32 vol);
extern void midi_psg_update_id(u32 id);
extern void midi_psg_update(void);

/* SOUND PLAYER OPERATIONS */

extern u16  midi_player_parse_be16(const u8 *stream);
extern u32  midi_player_parse_be32(const u8 *stream);
extern u32  midi_player_get_loop_sym_size(const char *loopMarker);
extern void midi_player_play_header(struct SoundPlayer *soundPlayer, struct SongHeader *song);
extern void midi_player_play_id(u16 soundIndex);
extern void midi_player_stop(struct SoundPlayer *soundPlayer);
extern void midi_player_set_pause(struct SoundPlayer *soundPlayer, u8 pause);
extern u32  midi_player_is_playing(struct SoundPlayer *soundPlayer);
extern void midi_player_pause(struct SoundPlayer *soundPlayer);
extern void midi_player_unpause(struct SoundPlayer *soundPlayer);
extern void midi_player_pause_all(void);
extern void midi_player_unpause_all(void);
extern void midi_player_set_volume_a(struct SoundPlayer *soundPlayer, u16 volume);
extern void midi_player_set_volume_b(struct SoundPlayer *soundPlayer, u16 trackMask, u16 volume);
extern void midi_player_set_pitch(struct SoundPlayer *soundPlayer, u16 trackMask, s16 pitch);
extern void midi_player_set_panning(struct SoundPlayer *soundPlayer, u16 trackMask, s8 panning);
extern void midi_player_pause_id(u16 soundIndex);
extern u32  midi_player_text_is_loop_sym(const char *string, const u8 *byteStream, u32 length);
extern u32  midi_player_get_clocks_per_frame(u16 tempo, u16 speed, u16 quarterNote);
extern void midi_player_set_speed(struct SoundPlayer *soundPlayer, u16 speed);
extern void midi_player_set_volume_fade(struct SoundPlayer *soundPlayer, u16 type, u16 duration);
extern void midi_player_fade_out_to_stop(struct SoundPlayer *soundPlayer, u16 duration);
extern void midi_player_fade_out_to_pause(struct SoundPlayer *soundPlayer, u16 duration);
extern void midi_player_fade_in(struct SoundPlayer *soundPlayer, u16 duration);

/* MIDI SEQUENCE OPERATIONS */

extern void midi_player_parse_sys_exc_message(struct SoundPlayer *soundPlayer, const u8 *stream);
extern u32  midi_player_parse_meta_event(struct SoundPlayer *soundPlayer, const u8 **upstream);
extern void midi_player_parse_controller_change(struct SoundPlayer *soundPlayer, u32 track, u8 controller, u8 value);
extern void midi_player_add_note(u32 track, u32 key, u32 velocity);
extern u32  midi_player_read_track(struct SoundPlayer *soundPlayer, u32 track);
extern void midi_player_update_track(struct SoundPlayer *soundPlayer, u32 track);

/* MAIN SOUND */

extern void midi_player_update_volume_fade(struct SoundPlayer *soundPlayer);
extern void midi_player_update_sequence(struct SoundPlayer *soundPlayer);
extern void midi_sound_main(void);
extern void midi_player_set_reverb(u32 rvb0, u32 rvb1, u32 rvb2, u32 rvb3);
extern void midi_stub(void);
extern void midi_player_init(struct SoundPlayer *soundPlayer, struct MidiBus *midiBus, u32 totalTracks,
                                struct MidiTrackStream *midiReader, u32 priorityEnabled);
extern u32  midi_parse_variable_length(const u8 **upstream);
extern void midi_direct_player_init(struct SoundPlayer *soundPlayer, struct MidiTrackStream *midiReader, u32 totalTracks,
                                        struct MidiBus *midiBus, struct MidiChannel *midiChannels, u8 *sequenceSource);
extern void midi_direct_player_append_sequence(u8 *midiIn, u32 length);
extern u32  midi_direct_player_read_sequence(void);
extern void midi_direct_player_update(void);
extern void midi_sound_init(void);
