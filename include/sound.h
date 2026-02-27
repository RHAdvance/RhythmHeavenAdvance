#pragma once

enum PsgChannelsEnum {
    /* 00 */ PSG_PULSE_CHANNEL_1,
    /* 01 */ PSG_PULSE_CHANNEL_2,
    /* 02 */ PSG_WAVE_CHANNEL,
    /* 03 */ PSG_NOISE_CHANNEL,
    /* -- */ TOTAL_PSG_CHANNELS
};

enum SoundPlayersEnum {
    /* 00 */ MUSIC_PLAYER_0,
    /* 01 */ MUSIC_PLAYER_1,
    /* 02 */ MUSIC_PLAYER_2,
    /* 03 */ SFX_PLAYER_0,
    /* 04 */ SFX_PLAYER_1,
    /* 05 */ SFX_PLAYER_2,
    /* 06 */ SFX_PLAYER_3,
    /* 07 */ SFX_PLAYER_4,
    /* 08 */ SFX_PLAYER_5,
    /* 09 */ SFX_PLAYER_6,
    /* 10 */ SFX_PLAYER_7,
    /* 11 */ SFX_PLAYER_8,
    /* 12 */ SFX_PLAYER_9,
    /* -1 */ DEFAULT_SOUND_PLAYER = 0xFF
};

enum MidiTracksEnum {
    MIDI_TRACK_0    = (1 << 0),
    MIDI_TRACK_1    = (1 << 1),
    MIDI_TRACK_2    = (1 << 2),
    MIDI_TRACK_3    = (1 << 3),
    MIDI_TRACK_4    = (1 << 4),
    MIDI_TRACK_5    = (1 << 5),
    MIDI_TRACK_6    = (1 << 6),
    MIDI_TRACK_7    = (1 << 7),
    MIDI_TRACK_8    = (1 << 8),
    MIDI_TRACK_9    = (1 << 9),
    MIDI_TRACK_10   = (1 << 10),
    MIDI_TRACK_11   = (1 << 11),
    MIDI_TRACK_12   = (1 << 12),
    MIDI_TRACK_13   = (1 << 13),
    MIDI_TRACK_14   = (1 << 14),
    MIDI_TRACK_15   = (1 << 15)
};

enum DirectSoundModesEnum {
    /* 00 */ DIRECTSOUND_MODE_STEREO,
    /* 01 */ DIRECTSOUND_MODE_MONO1,
    /* 02 */ DIRECTSOUND_MODE_MONO2
};

enum InstrumentBanksEnum {
	/* 000 */ INST_BANK_UNUSED_0,
	/* 001 */ INST_BANK_UNUSED_1,
	/* 002 */ INST_BANK_UNUSED_2,
	/* 003 */ INST_BANK_UNUSED_3,
	/* 004 */ INST_BANK_UNUSED_4,
	/* 005 */ INST_BANK_54,
	/* 006 */ INST_BANK_UNUSED_5,
	/* 007 */ INST_BANK_UNUSED_7,
	/* 008 */ INST_BANK_UNUSED_8,
	/* 009 */ INST_BANK_UNUSED_9,
	/* 010 */ INST_BANK_UNUSED_10,
	/* 011 */ INST_BANK_UNUSED_11,
	/* 012 */ INST_BANK_UNUSED_12,
	/* 013 */ INST_BANK_UNUSED_13,
	/* 014 */ INST_BANK_UNUSED_14,
	/* 015 */ INST_BANK_UNUSED_15,
	/* 016 */ INST_BANK_UNUSED_16,
	/* 017 */ INST_BANK_55,
	/* 018 */ INST_BANK_1,
	/* 019 */ INST_BANK_2,
	/* 020 */ INST_BANK_3,
	/* 021 */ INST_BANK_4,
	/* 022 */ INST_BANK_5,
	/* 023 */ INST_BANK_6,
	/* 024 */ INST_BANK_7,
	/* 025 */ INST_BANK_8,
	/* 026 */ INST_BANK_9,
	/* 027 */ INST_BANK_10,
	/* 028 */ INST_BANK_11,
	/* 029 */ INST_BANK_12,
	/* 030 */ INST_BANK_13,
	/* 031 */ INST_BANK_14,
	/* 032 */ INST_BANK_15,
	/* 033 */ INST_BANK_16,
	/* 034 */ INST_BANK_17,
	/* 035 */ INST_BANK_UNUSED_35,
	/* 036 */ INST_BANK_UNUSED_36,
	/* 037 */ INST_BANK_UNUSED_37,
	/* 038 */ INST_BANK_UNUSED_38,
	/* 039 */ INST_BANK_UNUSED_39,
	/* 040 */ INST_BANK_47,
	/* 041 */ INST_BANK_49,
	/* 042 */ INST_BANK_50,
	/* 043 */ INST_BANK_48,
	/* 044 */ INST_BANK_UNUSED_44,
	/* 045 */ INST_BANK_51,
	/* 046 */ INST_BANK_52,
	/* 047 */ INST_BANK_53,
	/* 048 */ INST_BANK_UNUSED_48,
	/* 049 */ INST_BANK_UNUSED_49,
	/* 050 */ INST_BANK_18,
	/* 051 */ INST_BANK_19,
	/* 052 */ INST_BANK_20,
	/* 053 */ INST_BANK_21,
	/* 054 */ INST_BANK_22,
	/* 055 */ INST_BANK_23,
	/* 056 */ INST_BANK_24,
	/* 057 */ INST_BANK_25,
	/* 058 */ INST_BANK_26,
	/* 059 */ INST_BANK_27,
	/* 060 */ INST_BANK_28,
	/* 061 */ INST_BANK_29,
	/* 062 */ INST_BANK_30,
	/* 063 */ INST_BANK_31,
	/* 064 */ INST_BANK_32,
	/* 065 */ INST_BANK_33,
	/* 066 */ INST_BANK_34,
	/* 067 */ INST_BANK_35,
	/* 068 */ INST_BANK_36,
	/* 069 */ INST_BANK_37,
	/* 070 */ INST_BANK_38,
	/* 071 */ INST_BANK_39,
	/* 072 */ INST_BANK_40,
	/* 073 */ INST_BANK_41,
	/* 074 */ INST_BANK_42,
	/* 075 */ INST_BANK_43,
	/* 076 */ INST_BANK_44,
	/* 077 */ INST_BANK_45,
	/* 078 */ INST_BANK_46,
	/* 079 */ INST_BANK_UNUSED_79,
	/* 080 */ INST_BANK_UNUSED_80,
	/* 081 */ INST_BANK_UNUSED_81,
	/* 082 */ INST_BANK_UNUSED_82,
	/* 083 */ INST_BANK_UNUSED_83,
	/* 084 */ INST_BANK_UNUSED_84,
	/* 085 */ INST_BANK_UNUSED_85,
	/* 086 */ INST_BANK_UNUSED_86,
	/* 087 */ INST_BANK_UNUSED_87,
	/* 088 */ INST_BANK_UNUSED_88,
	/* 089 */ INST_BANK_UNUSED_89,
	/* 090 */ INST_BANK_UNUSED_90,
	/* 091 */ INST_BANK_UNUSED_91,
	/* 092 */ INST_BANK_UNUSED_92,
	/* 093 */ INST_BANK_UNUSED_93,
	/* 094 */ INST_BANK_UNUSED_94,
	/* 095 */ INST_BANK_UNUSED_95,
	/* 096 */ INST_BANK_UNUSED_96,
	/* 097 */ INST_BANK_UNUSED_97,
	/* 098 */ INST_BANK_UNUSED_98,
	/* 099 */ INST_BANK_UNUSED_99,
	/* 100 */ INST_BANK_56,
	/* 101 */ INST_BANK_57,
	/* 102 */ INST_BANK_58,
	/* 103 */ INST_BANK_59,
	/* 104 */ INST_BANK_60,
	/* 105 */ INST_BANK_61,
	/* 106 */ INST_BANK_UNUSED_106,
	/* 107 */ INST_BANK_UNUSED_107,
	/* 108 */ INST_BANK_UNUSED_108,
	/* 109 */ INST_BANK_UNUSED_109,
	/* 110 */ INST_BANK_62,
	/* 111 */ INST_BANK_63
};


/* INSTRUMENT DATA STRUCTURES */


// Sample Data (known in M4A as "WaveData")
    // Contains information from header and sampler data sections of standard
    // audio file formats.
    //
    // Both 'loopStart' and 'loopEnd' must be set to 0 for there to be no loop.
struct SampleData {
	u32 length;     // Waveform length, in bytes.
	u32 sampleRate; // Base samplerate, in Hertz.
	u32 pitch;      // Sample base MIDI key.
	u32 loopStart;  // Sample loop start offset, in bytes.
	u32 loopEnd;    // Sample loop end offset, in bytes.
	const u32 *waveform; // Waveform address.
};

// Instrument Data (known in M4A as "ToneData")
    // Contains information akin to standard MIDI sound bank file formats,
    // and up to 128 may appear (directly) in each bank.
union Instrument {
    u8 *type;
    struct InstrumentPCM *pcm;
    struct InstrumentPSG *psg;
    struct InstrumentSubRhythm *rhy;
    struct InstrumentSubSplit *spl;
};

// PCM Instrument Data
    // Contains note playback information for PCM sampled instruments.
    //
    // The type can be either PCM_ALIGNED ('A') or PCM_FIXED ('F'). The former
    // allows the tone to play at a variety of keys/pitches. The latter
    // forces the tone to output its samples to the PCM buffer at a 1:1 rate,
    // which may have unintended results if the waveform samplerate does not
    // match the global output samplerate (13379Hz by default).
    //
    // The 'key' and 'panning' fields provide default values to use only when
    // called as part of a percussion bank.
struct InstrumentPCM {
	u8 type;        // Tone type (common). Always either PCM_ALIGNED or PCM_FIXED.
	u8 key:7;       // Default MIDI key, if part of a percussion bank.
    u8 fastRead:1;  // If TRUE, use Fast-Resample PCM read method.
	s16 panning;    // Default MIDI panning, if part of a percussion bank.
	struct SampleData *sample;  // Sampling data.
	s32 initial;    // Q16.16 ADSR initial envelope value.
	s32 sustain;    // Q16.16 ADSR envelope level during SUSTAIN stage.
	s32 attack;     // Q16.16 ADSR inc. during ATTACK stage.
	s32 decay;      // Q16.16 ADSR dec. during DECAY stage.
	s32 fade;       // Q16.16 ADSR dec. during SUSTAIN stage.
	s32 release;    // Q16.16 ADSR dec. during RELEASE stage.
};

// PSG Instrument Data
    // Contains note playback information for instruments output through the
    // CGB sound channels.
    //
    // The type can be either PSG ('P') or PSG_ALT ('Q'). There is no functional
    // difference between these two types, and the latter is never used in
    // Rhythm Tengoku.
    //
    // The 'key' and 'panning' fields provide default values to use only when
    // called as part of a percussion bank.
struct InstrumentPSG {
	u8 type;        // Tone type (common). Always either PSG or PSG_ALT.
	u8 key;         // Base MIDI key, if part of a percussion bank.
	s16 panning;    // Base MIDI panning, if part of a percussion bank.
	u32 *wavetable; // 4-bit waveform (32 samples), for the WAVE channel.
	s32 initial;    // Q16.16 ADSR initial envelope value.
	s32 sustain;    // Q16.16 ADSR envelope level during SUSTAIN stage.
	s32 attack;     // Q16.16 ADSR inc. during ATTACK stage.
	s32 decay;      // Q16.16 ADSR dec. during DECAY stage.
	s32 fade;       // Q16.16 ADSR dec. during SUSTAIN stage.
	s32 release;    // Q16.16 ADSR dec. during RELEASE stage.
	u32 channel:2;  // Target CGB sound channel.
	u32 length:8;   // Note length (inserted directly into the relevant sound register).
	u32 sweep:7;    // Sweep parameters (all, inserted directly into REG_SOUND1CNT_L).
    u32 dutyTone:2; // Duty cycle, for PULSE channels.
    u32 dutyNoise:13; // Duty cycle, for the NOISE channel.
};

// Percussion Bank Data
    // Contains an instrument bank and the base MIDI key which instrument
    // mapping starts on.
    //
    // The type can only be SUB_RHYTHM ('R'). The label "rhythm" originates
    // from M4A.
    //
    // Unintended playback or crashes may occur if the instrument is made to
    // perform a note lower than its base key. Additionally, if the requested
    // instrument within the sub-bank is another sub-bank instrument, playback
    // will be denied entirely.
struct InstrumentSubRhythm {
	u32 type:8;         // Tone type (common). Always SUB_RHYTHM.
	u32 baseKey:24;     // Base MIDI key where instrument mapping starts.
	union Instrument *subBank;  // Instrument sub-bank.
};

// Multi-Instrument Data
    // Contains an instrument bank, an array of key-instrument mappings,
    // and the base MIDI key which key-instrument mapping starts on.
    //
    // The type can only be SUB_SPLIT ('S'). The label "split" originates
    // from M4A.
    //
    // Unintended playback or crashes may occur if the instrument is made to
    // perform a note lower than its base key, and/or if the key split table
    // requests an out-of-range instrument. Additionally, if the requested
    // instrument within the sub-bank is another sub-bank instrument, playback
    // will be denied entirely.
struct InstrumentSubSplit {
    u32 type:8;         // Tone type (common). Always SUB_SPLIT.
	u32 baseKey:24;     // Base MIDI key where key-instrument mapping starts.
	u8 *keySplitTable;  // Key-instrument mapping table.
	union Instrument *subBank;  // Instrument sub-bank.
};

// Song Header (name from M4A)
    // The main sound file to be referenced throughout a project using the
    // MIDI library. Contains the primary playback information for a music
    // sequence.
    //
    // The 'songNum' field is a holdover from M4A, though it is still used when
    // determining the default SoundPlayer to play this song with, despite the
    // presence of a 'soundPlayer' field here (which is never read).
struct SongHeader {
    const u8 *midiSequence;
    u32 soundPlayer:5;
    u32 soundBank:10;
    u32 volume:7;
    u32 priority:10;
    u32 unk8;
    char *title;
    u32 songNum;
};


/* MEMORY STRUCTURES */


// MIDI Channel
    // Strongly resembling the MIDI Channel of General MIDI specifications,
    // containing runtime instrument playback memory. Some fields are
    // modifiable but serve no purpose in the library.
    //
    // Despite General MIDI separating MIDI Channels from MIDI Tracks, the
    // library always uses the Track ID wherever the Channel ID would be
    // requested.
struct MidiChannel {
    u32 disabled:1;     // Disable channel.
    u32 fixedPitch:1;   // Disable pitch modulation.
    u32 instPatch:7;    // Instrument patch number (0-127).
    u32 bankSelect:14;  // Target bank (unused - MIDI specification only).
    u32 volume:7;       // Volume level (0-127).
    u32 filterEQ:1;     // Apply EQ filter to output.
    u32 phaseStereo:1;  // Apply stereo phase effect.
    u32 panning:7;      // Panning level (0-64-127).
    u32 expression:7;   // Expression level (0-127).
    u32 modDepth:7;     // Modulation depth.
    u32 unk4_b21:7;     // Unknown modifiable value (defaults to 0).
    u32 modType:2;      // Modulation target (defaults to PITCH).
    u32 unk4_b30:2;     // Unused
    u32 pitchWheel:14;  // 14-bit signed pitch envelope.
    u32 volumeWheel:8;  // 8-bit unsigned volume envelope.
    u32 priority:10;    // Priority.
    u8  modRange;       // Modulation range.
    s8  modResult;      // Modulation value.
    u8  unkE;           // Unused
    u8  pitchRange;     // Pitch wheel range, in octaves (defaults to 2).
    u16 modSpeed;       // Q8.8 modulation counter increment (defaults to 60.0).
    u16 modCount;       // Q8.8 modulation counter, ticking up.
    u8  modDelay;       // Modulation base delay time, in frames.
    u8  modDelayCount;  // Modulation delay clock, ticking down to 0.
    u16 randomPitchFloor;   // Q8.8 random base pitch - minimum.
    u16 randomPitchRange;   // Q8.8 random base pitch - range.
    u16 randomPitchResult;  // Q8.8 random base pitch - value.
    u8  keyModDepth;        // Random key modulation - max offset.
    u8  keyModInterval;     // Random key modulation - interval.
    u8  keyModCount;        // Random key modulation - clock.
};

// MIDI Channel Bus
    // Manages MIDI Channel output for all given tracks for a SoundPlayer,
    // including allocation of playback to output Sound Channels.
struct MidiBus {
    u8  volumeA;            // Primary volume level.
    u8  volumeB;            // Secondary volume level.
    u16 volumeTrackMap;     // Bitmask mapping of MIDI Tracks to primary or secondary volume levels.
    s8  key;                // Output MIDI key offset.
    s8  panning;            // Output panning offset.
    s16 pitch;              // Q8.8 output pitch offset.
    u16 unk8;               // Q8.8 unknown modifiable value (defaults to 20.0).
    u16 *tuningTable;       // MIDI key frequency table.
    union Instrument *soundBank;     // Instrument bank.
    u32 totalChannels:5;             // Total number of MidiChannels controlled by this MidiBus.
    u32 isPaused:1;                  // TRUE if the owning SoundPlayer is paused
    u32 priority:26;                 // Priority value.
    struct MidiChannel *midiChannel; // Child MIDI Channels.
    s8  keyModScale[12];             // Offsets for each key in an octave for randomised key modulation.
};

// MIDI Track Stream/Reader
    // Reads instructions from a specific MIDI Track.
    //
    // Despite General MIDI specifications, each of these streams has a respective
    // MIDI Channel which it will always provide instructions for.
struct MidiTrackStream {
    u32 active:1;           // TRUE if active.
    u32 activeAtLoop:1;     // TRUE if active at Loop Start.
    u32 command:8;          // Buffered MIDI instruction.
    u32 commandAtLoop:8;    // Buffered MIDI instruction at Loop Start.
    u32 withinLoop:1;       // TRUE if this stream has been updated for the loop region.
    const u8 *startPos;     // Track start position.
    const u8 *currentPos;   // Current position.
    u32 clocksThisFrame;    // Clocks passed this frame.
    const u8 *loopStartPos; // Loop Start position.
    u32 unused;             // Unused value.
    u32 clocksPassed;       // Clocks passed in total.
};

// MIDI Player
    // The primary structure for sound playback. A convention seems to exist
    // where sound play/start functions must return a pointer to the SoundPlayer
    // which is now playing it.
    //
    // Rhythm Tengoku operates 13 of these in total:
    //  - 1 for primary BGM (15 tracks).
    //  - 2 for secondary BGM (12 tracks each).
    //  - 10 for SFX (5 tracks each).
struct SoundPlayer {
    u32 totalTracks:5;      // Maximum MIDI Tracks this SoundPlayer can process.
    u32 usedTracks:5;       // Total MIDI Tracks used by the current MIDI, no higher than the maximum.
    u32 withinLoop:1;       // Set to TRUE upon passing the Loop Start marker.
    u32 isPaused:1;         // Set to TRUE when paused.
    u32 midiTempo:9;        // Current MIDI tempo, in Beats Per Minute.
    u32 priorityEnabled:1;  // If TRUE, priority values will be checked before playing a new sound.
    u32 unused:5;           // Unused.
    u32 volumeFadeType:3;   // Current volume fade effect type.
    struct MidiBus *midiBus;            // Effect and playback manager for all MIDI Channels.
    struct MidiTrackStream *midiReader; // Array of MIDI Track streams.
    struct SongHeader *song;    // Current loaded SongHeader.
    u32 clocksPerFrame;         // Q24.8 MIDI clocks passed each frame, assuming 60FPS.
    const char *loopStartSym;   // String denoting Loop Start marker ("[").
    const char *loopEndSym;     // String denoting Loop End marker ("]").
    u8  loopStartSymLen;        // Length of the Loop Start marker string (1).
    u8  loopEndSymLen;          // Length of the Loop End marker string (1).
    u16 midiQuarterNote;        // Number of MIDI clocks per quarter note, as defined by the MIDI.
    u16 volumeA;            // Q8.8 primary volume envelope.
    u16 volumeB;            // Q8.8 secondary volume envelope.
    u16 volumeTrackMap;     // Bitmask mapping of MIDI Tracks to primary or secondary volume envelopes.
    u16 playerSpeed;        // Q8.8 playback speed envelope.
    u16 volumeFadeEnv;      // Q1.15 volume fade envelope.
    u16 volumeFadeSpd;      // Q1.15 volume fade increment per frame.
    u8  songVolume;         // Base volume, as specified by the SongHeader.
    s8  rvb1Wet;            // 64 + RVB1.
    s8  rvb2Phase;          // 64 + RVB2.
    s8  rvb3Decay;          // 64 + RVB3.
    s8  rvb4LowCut;         // 64 + RVB4.
    u32 clocksPassedAtLoop; // Clocks passed upon reaching the Loop Start marker.
};

// Sound Channel
    // Instrument/note playback controller, functioning as a virtual instrument.
    //
    // Four of these are especially reserved for CGB sound channel playback,
    // while the total number of those used for PCM sampled instruments may be
    // specified at compile-time (the default is 12). Each of the PCM sampled
    // Sound Channels has a respective SampleStream for buffered waveform output.
struct SoundChannel {
    u32 active:1;       // TRUE if currently outputting a note.
    u32 key:7;          // MIDI key (0-127).
    u32 velocity:7;     // MIDI velocity (0-127).
    u32 frequency:17;   // Frequency, in hertz.
    union Instrument instrument;        // Current instrument.
    struct MidiBus *midiBus;            // Source channel bus.
    struct MidiChannel *midiChannel;    // Source MIDI Channel.
    u16 pitchDecFreq;   // Difference between the current frequency and the lowest frequency within range, in hertz.
    u16 pitchIncFreq;   // Difference between the highest frequency within range and the current frequency, in hertz.
    s16 modStepFreq;    // Frequency of a modulation output step, in hertz.
    u16 priority:15;    // Priority value.
    u16 justStarted:1;  // Set to TRUE between initialisation and the first update.
    s16 panning;        // Panning value.
    struct AdsrEnvelope {
        u32 stage:8;        // Current stage (starts on ATTACK).
        u32 envelope:24;    // Volume envelope.
    } adsr;             // ADSR controller.
};

// DirectSound Sample Stream
    // Reads and writes PCM sampled data to the PCM buffer.
struct SampleStream {
    u8 active:1;        // TRUE if the stream is outputting samples.
    u8 hasFrequency:1;  // TRUE if sample output rate is not 1.0.
    u8 fastRead:1;      // If TRUE, use Fast-Resample PCM read method.
    u8 equalize:1;      // Apply EQ filter.
    u8 volume;          // Volume envelope.
    s8 leftBias;        // Stereo left bias.
    s8 rightBias;       // Stereo right bias.
    const u32 *sample;  // PCM wave address.
    u32 length;         // Q18.14 sample length.
    u32 position;       // Q18.14 stream position.
    u32 loopStart;      // Q18.14 loop start offset.
    u32 loopEnd;        // Q18.14 loop end offset.
    u32 frequency;      // Q18.14 sample output rate.
    u32 rate;           // uh... something that helps convert note frequency to 13379Hz
};

// Low-Frequency Oscillator Mode
    // DISABLED - LFO will not update nor apply to any MIDI Channels.
    // KEYPRESS - LFO will reset when a note is played by any of the caller MIDI Channels.
    // CONSTANT - LFO will run continuously until the mode is changed.
enum LfoModesEnum {
    LFO_MODE_DISABLED,
    LFO_MODE_KEYPRESS,
    LFO_MODE_CONSTANT
};
extern u8 gMidiLFOMode;

// Low-Frequency Oscillator
    // General-purpose customizable oscillator. Used for an auto-wah effect in
    // the MIDI library.
    //
    // The oscillator uses MIDI clocks as time units, and assumes a rate of 24
    // MIDI clocks per quarter note. The clock rate is synchronized with the
    // caller SoundPlayer.
extern struct LFO {
    u8  delay;      // Initial delay upon trigger, in MIDI clocks.
    u8  attack;     // Time to reach maximum amplitude (after initial delay), in MIDI clocks.
    u16 rate;       // Q0.16 oscillation speed, in cycles per MIDI clock.
    u8  offset;     // Q0.8 cycle offset.
    u8  endPos;     // Q0.8 max cycle position before stopping entirely.
    u8  stage;      // Current state.
    s8  output;     // Q0.8 output multiplier.
    u32 clocks;     // Q24.8 running time, in MIDI clocks.
} gMidiLFO;


/* SONG & SOUNDPLAYER DATA STRUCTURES */


// Song Table (from M4A)
    // Pointless but still used holdover from M4A. Song headers include an index
    // for this table, which is used to retrieve the song header (again) and its
    // default sound player.
extern struct SongTable {
    struct SongHeader *song;    // Sound file.
    u16 player;                 // SoundPlayer index.
} song_header_table[];

// Sound Player List
    // Pointers to all Sound Players in order, for quick iteration.
extern struct SoundPlayer *sound_players[];

// Sound Player Initialisation Table
    // Initialisation data for Sound Players, including allocated memory addresses.
extern struct SoundPlayerInitTable {
    u16 id:5;
    u16 totalTracks:5;
    u16 priorityEnabled:6;
    struct MidiChannel *midiChannels;
    struct MidiBus *midiBus;
    struct MidiTrackStream *trackStreams;
    struct SoundPlayer *soundPlayer;
} sound_player_init_table[];

// Total Number of Sound Players
extern u8 sound_player_count;

// Sound Player Table
    // Data table for Sound Players in order, for more complex iteration.
extern struct SoundPlayerTable {
    struct SoundPlayer *soundPlayer;
    u32 unused;
    u16 totalTracks;
    u16 priorityEnabled;
} sound_player_table[];
