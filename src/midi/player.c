#include "global.h"
#include "sound.h"
#include "midi.h"


/* AUDIO LIBRARY - SOUNDPLAYER */


// STATIC VARIABLES
static s32 D_03001594;  // Unused

static struct SoundPlayer *sDirectPlayer;   // DirectMidi SoundPlayer
static struct MidiBus *sDirectBus;          // DirectMidi MidiBus
static u8 *sDirectSequence;                 // DirectMidi Sequence (max. size = 0x200)
static u16 sDirectLength;                   // DirectMidi Sequence Length
static u8 sDirectLastCommand;               // DirectMidi Sequence Current Command

static u8 sMidiCommVar1;
static u8 sMidiCommVar2;
static u8 sMidiCommVar3;
static u8 sMidiCommVar4;


// Evaluate Big-Endian Short
u16 midi_player_parse_be16(const u8 *stream) {
    return (stream[0] << 8) | stream[1];
}


// Evaluate Big-Endian Integer
u32 midi_player_parse_be32(const u8 *stream) {
    return (stream[0] << 24) | (stream[1] << 16) | (stream[2] << 8) | stream[3];
}


// Get SoundPlayer Loop Marker Symbol Length
u32 midi_player_get_loop_sym_size(const char *loopMarker) {
    u8 i;

    for (i = 0; loopMarker[i] != '\0'; i++);

    return i;
}


// Play
void midi_player_play_header(struct SoundPlayer *soundPlayer, struct SongHeader *song) {
    struct MidiBus *midiBus;
    struct MidiTrackStream *mTrkReader;
    const u8 *mTrkStream;
    const u8 *mTrkStart;
    u32 chunkLength;
    u32 trackTotal;
    u32 clocks;
    u32 i;

    // Reading Sequence Data:
    if (midi_player_is_playing(soundPlayer)) {
        if (soundPlayer->priorityEnabled && !soundPlayer->isPaused) {
            if (soundPlayer->song->priority > song->priority) {
                return;
            }
        }
    }

    midiBus = soundPlayer->midiBus;
    midi_channel_stop_all(midiBus);
    midi_bus_init(midiBus, midiBus->totalChannels, midiBus->midiChannel);
    midi_bus_set_bank(midiBus, instrument_banks[song->soundBank]);
    midi_bus_set_volume(midiBus, song->volume);
    midi_bus_set_priority(midiBus, song->priority);
    soundPlayer->song = song;
    soundPlayer->songVolume = song->volume;

    // Reading MIDI Data:
    mTrkStream = song->midiSequence;

    // Header:
    mTrkStream += 4; // Skip (Header: "MThd")
    chunkLength = midi_player_parse_be32(mTrkStream);
    mTrkStream += 4; // Skip (Header: Length)
    trackTotal = midi_player_parse_be16(mTrkStream + 2); // Header: Number of MIDI Tracks
    soundPlayer->usedTracks = trackTotal;

    if (soundPlayer->usedTracks > soundPlayer->totalTracks) {
        soundPlayer->usedTracks = soundPlayer->totalTracks;
    }
    soundPlayer->midiQuarterNote = midi_player_parse_be16(mTrkStream + 4); // Header: Division
    mTrkStream += chunkLength; // Skip (Header: Data)

    // Track:
    mTrkReader = soundPlayer->midiReader;
    for (i = 0; i < soundPlayer->usedTracks; i++) {
        mTrkStream += 4; // Skip (Track: Header)
        chunkLength = midi_player_parse_be32(mTrkStream);
        mTrkStream += 4; // Skip (Track: Length)
        mTrkStart = mTrkStream;
        mTrkStream += chunkLength;
        mTrkReader->active = TRUE;
        mTrkReader->startPos = mTrkStart;
        clocks = midi_parse_variable_length(&mTrkStart);
        mTrkReader->clocksThisFrame = clocks << 8;
        mTrkReader->currentPos = mTrkStart;
        mTrkReader->clocksPassed = clocks;
        mTrkReader->activeAtLoop = FALSE;
        mTrkReader->withinLoop = FALSE;
        mTrkReader++;
    }

    // Other Data:
    soundPlayer->withinLoop = FALSE;
    soundPlayer->isPaused = FALSE;
    soundPlayer->clocksPerFrame = 1;
    soundPlayer->volumeA = (1 << 8);
    soundPlayer->playerSpeed = (1 << 8);
    soundPlayer->volumeB = (1 << 8);
    soundPlayer->volumeFadeType = 0;
    soundPlayer->volumeFadeEnv = (1 << 15);
    soundPlayer->volumeFadeSpd = 0;
    soundPlayer->loopStartSym = midi_loop_start_sym;
    soundPlayer->loopStartSymLen = midi_player_get_loop_sym_size(midi_loop_start_sym);
    soundPlayer->loopEndSym = midi_loop_end_sym;
    soundPlayer->loopEndSymLen = midi_player_get_loop_sym_size(midi_loop_end_sym);
    soundPlayer->rvb1Wet = 64;
    soundPlayer->rvb2Phase = 64;
    soundPlayer->rvb3Decay = 64;
    soundPlayer->rvb4LowCut = 64;
    soundPlayer->clocksPassedAtLoop = 0;
}


// Play from SongTable
void midi_player_play_id(u16 soundIndex) {
    struct SoundPlayer *soundPlayer;
    struct SongHeader *song;

    soundPlayer = sound_player_table[song_header_table[soundIndex].player].soundPlayer;
    song = song_header_table[soundIndex].song;
    midi_player_play_header(soundPlayer, song);
}


// Stop
void midi_player_stop(struct SoundPlayer *soundPlayer) {
    midi_channel_cut_all(soundPlayer->midiBus);
    soundPlayer->song = NULL;
}


// Set Pause
void midi_player_set_pause(struct SoundPlayer *soundPlayer, u8 pause) {
    struct MidiBus *midiBus = soundPlayer->midiBus;
    u32 i;

    soundPlayer->isPaused = pause;

    if (pause) {
        midiBus->isPaused = TRUE;

        for (i = 0; i < gMidiSoundChannelCount; i++) {
            if (gMidiSoundChannelPool[i].active && (gMidiSoundChannelPool[i].midiBus == midiBus)) {
                midi_sampler_stop(i);
            }
        }

        midi_channel_stop_psg_all(midiBus);
    } else {
        midiBus->isPaused = FALSE;

        for (i = 0; i < gMidiSoundChannelCount; i++) {
            if (gMidiSoundChannelPool[i].active && (gMidiSoundChannelPool[i].midiBus == midiBus)) {
                gMidiSamplerPool[i].active = TRUE;
            }
        }
    }
}


// Check for Active Midi Readers
u32 midi_player_is_playing(struct SoundPlayer *soundPlayer) {
    u32 i;

    if (soundPlayer->song == NULL) {
        return FALSE;
    }

    for (i = 0; i < soundPlayer->usedTracks; i++) {
        if (soundPlayer->midiReader[i].active) {
            return TRUE;
        }
    }

    return FALSE;
}


// Pause
void midi_player_pause(struct SoundPlayer *soundPlayer) {
    midi_player_set_pause(soundPlayer, TRUE);
}


// Unpause
void midi_player_unpause(struct SoundPlayer *soundPlayer) {
    midi_player_set_pause(soundPlayer, FALSE);
}


// Pause All
void midi_player_pause_all(void) {
    u32 i;

    for (i = 0; i <= last_sound_player_id; i++) {
        midi_player_set_pause(sound_players[i], TRUE);
    }
}


// Unpause All
void midi_player_unpause_all(void) {
    u32 i;

    for (i = 0; i <= last_sound_player_id; i++) {
        midi_player_set_pause(sound_players[i], FALSE);
    }
}


// Set Primary Volume Envelope
void midi_player_set_volume_a(struct SoundPlayer *soundPlayer, u16 volume) {
    soundPlayer->volumeA = volume;
}


// Set Secondary Volume Envelope and Track Mask
void midi_player_set_volume_b(struct SoundPlayer *soundPlayer, u16 trackMask, u16 volume) {
    soundPlayer->volumeB = volume;
    soundPlayer->volumeTrackMap = trackMask;
}


// Set Pitch
void midi_player_set_pitch(struct SoundPlayer *soundPlayer, u16 trackMask, s16 pitch) {
    midi_bus_set_pitch(soundPlayer->midiBus, pitch);
}


// Set Panning
void midi_player_set_panning(struct SoundPlayer *soundPlayer, u16 trackMask, s8 panning) {
    midi_bus_set_panning(soundPlayer->midiBus, panning);
}


// Pause Song from Index
void midi_player_pause_id(u16 songNum) {
    struct SongHeader *song = song_header_table[songNum].song;
    u32 i;

    for (i = 0; i <= last_sound_player_id; i++) {
        if ((sound_players[i] != NULL) && (sound_players[i]->song == song)) {
            midi_player_pause(sound_players[i]);
        }
    }
}


// Check if Stream Output is Equal to String
u32 midi_player_text_is_loop_sym(const char *string, const u8 *byteStream, u32 length) {
    u32 i;

    for (i = 0; i < length; i++) {
        if (string[i] != byteStream[i]) {
            return FALSE;
        }
    }

    return TRUE;
}


// Get MIDI Ticks Per Frame
u32 midi_player_get_clocks_per_frame(u16 tempo, u16 speed, u16 quarterNote) {
    return (tempo * speed * quarterNote) / (60u * 60u);
}


// Set Speed
void midi_player_set_speed(struct SoundPlayer *soundPlayer, u16 speed) {
    u32 clocksPerFrame;

    soundPlayer->playerSpeed = speed;
    clocksPerFrame = midi_player_get_clocks_per_frame(soundPlayer->midiTempo, speed, soundPlayer->midiQuarterNote);
    if (clocksPerFrame < 1) clocksPerFrame = 1;
    soundPlayer->clocksPerFrame = clocksPerFrame;
}


// Set Volume Fade { type = 0..3 }
void midi_player_set_volume_fade(struct SoundPlayer *soundPlayer, u16 type, u16 duration) {
    switch (type) {
        case VOL_FADE_RESET:
            soundPlayer->volumeFadeEnv = (1 << 15);
            soundPlayer->volumeFadeSpd = 0;
            break;

        case VOL_FADE_IN:
            if (duration < 1) duration = 1;
            if (soundPlayer->volumeFadeType == VOL_FADE_RESET) {
                soundPlayer->volumeFadeEnv = 0;
            }
            soundPlayer->volumeFadeSpd = (1 << 15) / duration;
            soundPlayer->isPaused = FALSE;
            break;

        case VOL_FADE_OUT_CLEAR:
        case VOL_FADE_OUT_PAUSE:
            if (soundPlayer->volumeFadeType == VOL_FADE_RESET) {
                soundPlayer->volumeFadeEnv = (1 << 15);
            }
            if (duration > 0) {
                soundPlayer->volumeFadeSpd = (1 << 15) / duration;
            } else {
                soundPlayer->volumeFadeEnv = 0;
                soundPlayer->volumeFadeSpd = 1;
                if (type == VOL_FADE_OUT_CLEAR) {
                    type = VOL_FADE_RESET;
                    midi_player_stop(soundPlayer);
                } else {
                    midi_player_set_pause(soundPlayer, TRUE);
                }
            }
            break;
    }

    soundPlayer->volumeFadeType = type;
}


// Volume Fade-Out & Clear
void midi_player_fade_out_to_stop(struct SoundPlayer *soundPlayer, u16 duration) {
    midi_player_set_volume_fade(soundPlayer, VOL_FADE_OUT_CLEAR, duration);
}


// Volume Fade-Out & Pause
void midi_player_fade_out_to_pause(struct SoundPlayer *soundPlayer, u16 duration) {
    midi_player_set_volume_fade(soundPlayer, VOL_FADE_OUT_PAUSE, duration);
}


// Volume Fade-In
void midi_player_fade_in(struct SoundPlayer *soundPlayer, u16 duration) {
    midi_player_set_volume_fade(soundPlayer, VOL_FADE_IN, duration);
}


// MidiStream System-Exclusive Message [Evnt_F0]
void midi_player_parse_sys_exc_message(struct SoundPlayer *soundPlayer, const u8 *stream) {
    struct MidiBus *midiBus = soundPlayer->midiBus;
    u8 type = *stream;
    u32 i;

    stream++;
    switch (type) {
        case SYS_EXC_EVENT_LFO_SETTINGS:
            midi_equalizer_reset();
            gMidiLFOMode = LFO_MODE_DISABLED;
            gMidiLFODepth = stream[0] * 2;
            midi_lfo_init(&gMidiLFO, stream[1] * 2, stream[2] * 2, stream[3] * 2, stream[4] * 2, stream[5] * 2);
            midi_equalizer_set_high_gain(stream[6]);
            gMidiLFOPlayer = soundPlayer;
            break;

        case SYS_EXC_EVENT_KEY_MOD_SCALE:
            for (i = 0; i < ARRAY_COUNT(midiBus->keyModScale); i++) {
                midiBus->keyModScale[i] = stream[i] - 64;
            }
            break;
    }
}


// MidiStream Meta Event (Loop Start, Loop End, Track End, Set Tempo)
u32 midi_player_parse_meta_event(struct SoundPlayer *soundPlayer, const u8 **upstream) {
    const u8 *stream = *upstream;
    u8 event = *stream;
    u32 length;
    u32 tempo;

    stream++;
    length = midi_parse_variable_length(&stream);
    *upstream = stream + length;

    switch (event) {
        case META_TEXT_MARKER:
            if (length == soundPlayer->loopStartSymLen) {
                if (midi_player_text_is_loop_sym(soundPlayer->loopStartSym, stream, length)) {
                    return META_EVENT_LOOP_START;
                }
            }
            if (length == soundPlayer->loopEndSymLen) {
                if (midi_player_text_is_loop_sym(soundPlayer->loopEndSym, stream, length)) {
                    return META_EVENT_LOOP_END;
                }
            }
            return META_EVENT_OTHER;

        case META_END_OF_TRACK:
            return META_EVENT_TRACK_END;

        case META_SET_TEMPO:
            tempo = 60000000u / ((stream[0] << 16) | (stream[1] << 8) | stream[2]);
            soundPlayer->midiTempo = tempo;
            gMidiPlayerNewDeltaTime = midi_player_get_clocks_per_frame(tempo, soundPlayer->playerSpeed, soundPlayer->midiQuarterNote);
            return META_EVENT_OTHER;

        default:
            return META_EVENT_OTHER;
    }
}


// MidiStream Controller Change [Evnt_B]
void midi_player_parse_controller_change(struct SoundPlayer *soundPlayer, u32 track, u8 controller, u8 value) {
    struct MidiBus *midiBus = soundPlayer->midiBus;

    switch (controller) {
        case M_CONTROLLER_BANK_SELECT_MSB:
            midi_channel_set_bankselect(midiBus, track, value | 0x8000);
            break;

        case M_CONTROLLER_MOD_DEPTH:
            midi_channel_set_mod_depth(midiBus, track, value);
            break;

        case M_CONTROLLER_VOLUME:
            midi_channel_set_volume(midiBus, track, value);
            break;

        case M_CONTROLLER_PANNING:
            midi_channel_set_panning(midiBus, track, value);
            break;

        case M_CONTROLLER_EXPRESSION:
            midi_channel_set_expression(midiBus, track, value);
            break;

        case M_CONTROLLER_PITCH_RANGE:
            midi_channel_set_pitch_range(midiBus, track, value);
            break;

        case M_CONTROLLER_MOD_SPEED:
            midi_channel_set_mod_speed(midiBus, track, value);
            break;

        case M_CONTROLLER_MOD_TYPE:
            midi_channel_set_mod_type(midiBus, track, value);
            break;

        case M_CONTROLLER_MOD_DELAY:
            midi_channel_set_mod_delay(midiBus, track, value);
            break;

        case M_CONTROLLER_BANK_SELECT_LSB:
            midi_channel_set_bankselect(midiBus, track, value);
            break;

        case M_CONTROLLER_PRIORITY:
            midi_channel_set_priority(midiBus, track, value);
            break;

        case M_CONTROLLER_SELECT_VAR:
            gMidiCommVarCurrent = value;
            break;

        case M_CONTROLLER_SET_VAR:
            if (gMidiCommVarCurrent < gMidiCommVarTotal) {
                gMidiCommVars[gMidiCommVarCurrent] = value;
            }
            break;

        case M_CONTROLLER_EQ_MODE:
            midi_channel_set_enable_filter_eq(midiBus, track, value);
            break;

        case M_CONTROLLER_LFO_MODE:
            gMidiLFOMode = value;
            switch (value) {
                case LFO_MODE_DISABLED:
                case LFO_MODE_KEYPRESS:
                    midi_lfo_stop(&gMidiLFO);
                    break;
                case LFO_MODE_CONSTANT:
                    midi_equalizer_reset();
                    midi_lfo_start(&gMidiLFO);
                    break;
            }
            break;

        case M_CONTROLLER_SET_EQ:
            gMidiLFOMode = LFO_MODE_DISABLED;
            midi_lfo_stop(&gMidiLFO);
            midi_equalizer_reset();
            midi_equalizer_set_position((value * 2) - 0x80);
            break;

        case M_CONTROLLER_LFO_GAIN:
            gMidiLFODepth = value * 2;
            break;

        case M_CONTROLLER_EQ_GAIN:
            midi_equalizer_set_high_gain(value);
            break;

        case M_CONTROLLER_STEREO:
            midi_channel_set_stereo_phase(midiBus, track, value);
            break;

        case M_CONTROLLER_RVB1_WET:
            soundPlayer->rvb1Wet = value;
            break;

        case M_CONTROLLER_RVB2_PHASE:
            soundPlayer->rvb2Phase = value;
            break;

        case M_CONTROLLER_RVB3_DECAY:
            soundPlayer->rvb3Decay = value;
            break;

        case M_CONTROLLER_RVB4_LOW_CUT:
            soundPlayer->rvb4LowCut = value;
            break;

        case M_CONTROLLER_RANDOM_BASE_PITCH:
            midi_channel_set_random_pitch(midiBus, track, value);
            break;

        case M_CONTROLLER_KEY_MOD_DEPTH:
            midi_channel_set_random_key_mod_depth(midiBus, track, value);
            break;

        case M_CONTROLLER_KEY_MOD_SPEED:
            midi_channel_set_random_key_mod_speed(midiBus, track, value);
            break;
    }
}


// MidiStream Note Off/On [Evnt_8; Evnt_9]
void midi_player_add_note(u32 track, u32 key, u32 velocity) {
    struct MidiNote *midiNote;

    if (gMidiNoteNext < ARRAY_COUNT(gMidiNotePool)) {
        midiNote = &gMidiNotePool[gMidiNoteNext++];
        midiNote->channel = track;
        midiNote->key = key;
        midiNote->velocity = velocity;
    }
}


// MidiStream Messages/Events
u32 midi_player_read_track(struct SoundPlayer *soundPlayer, u32 track) {
    u32 trackEndType = M_TRACK_READER_CONTINUE;
    struct MidiTrackStream *reader = &soundPlayer->midiReader[track];
    struct MidiTrackStream *tempReader;
    const u8 *byteStream = reader->currentPos;
    u8 command;
    u16 pitch;
    u32 i;

    command = byteStream[0];
    if ((command & 0x80) != 0) {
        reader->command = command;
        byteStream++;
    }
    command = reader->command;

    // MIDI Meta Events & System Messages
    if (command >= 0xF0) {
        switch (command & 0x0F) {
            // MIDI System Exclusive Message (F0)
            case 0x00:
                i = midi_parse_variable_length(&byteStream);
                midi_player_parse_sys_exc_message(soundPlayer, byteStream);
                byteStream += i;
                break;

            // MIDI Meta Events (FF)
            case 0x0F:
                switch (midi_player_parse_meta_event(soundPlayer, &byteStream)) {
                    // End of Track
                    case META_EVENT_TRACK_END:
                        midi_channel_set_mod_speed(soundPlayer->midiBus, track, 0);
                        return M_TRACK_READER_STOP;

                    // Marker: Loop Start
                    case META_EVENT_LOOP_START:
                        if (soundPlayer->withinLoop) {
                            break;
                        }
                        reader->activeAtLoop = reader->active;
                        reader->commandAtLoop = reader->command;
                        reader->loopStartPos = byteStream;
                        reader->withinLoop = TRUE;
                        soundPlayer->clocksPassedAtLoop = reader->clocksPassed;
                        soundPlayer->withinLoop = TRUE;
                        break;

                    // Marker: Loop End
                    case META_EVENT_LOOP_END:
                        if (!soundPlayer->withinLoop) {
                            break;
                        }
                        for (i = 0; i < soundPlayer->usedTracks; i++) {
                            tempReader = &soundPlayer->midiReader[i];
                            tempReader->active = tempReader->activeAtLoop;
                            tempReader->command = tempReader->commandAtLoop;
                            if (reader == tempReader) {
                                byteStream = reader->loopStartPos;
                            } else {
                                tempReader->currentPos = tempReader->loopStartPos;
                                tempReader->clocksThisFrame = reader->clocksThisFrame;
                            }
                            midi_channel_cut(soundPlayer->midiBus, i);
                        }
                        trackEndType = M_TRACK_READER_LOOP;
                        break;
                }
                break;

            // Else, Do Nothing
            default:
                i = midi_parse_variable_length(&byteStream);
                byteStream += i;
                break;
        }
    }

    // MIDI Messages { 80, 90, A0, B0, C0, D0, E0 }
    else {
        switch (command & 0xF0) {
            // Note Off
            case MSG_NOTE_OFF:
                midi_player_add_note(track, byteStream[0], 0);
                byteStream += 2;
                break;

            // Note On
            case MSG_NOTE_ON:
                midi_player_add_note(track, byteStream[0], byteStream[1]);
                byteStream += 2;
                break;

            // Polyphonic Key Pressure (Aftertouch) [Not Supported]
            case MSG_POLYPHONIC_KEY_PRESSURE:
                byteStream += 2;
                break;

            // MIDI Controller Change
            case MSG_CONTROLLER_CHANGE:
                midi_player_parse_controller_change(soundPlayer, track, byteStream[0], byteStream[1]);
                byteStream += 2;
                break;

            // Program Change
            case MSG_PROGRAM_CHANGE:
                midi_channel_set_patch(soundPlayer->midiBus, track, byteStream[0]);
                byteStream += 1;
                break;

            // Channel Pressure (Aftertouch) [Not Supported]
            case MSG_CHANNEL_PRESSURE:
                byteStream += 1;
                break;

            // Pitch Wheel Change
            case MSG_PITCH_WHEEL_CHANGE:
                pitch = (byteStream[0] & 0x7F) | ((byteStream[1] & 0x7F) << 7);
                midi_channel_set_pitch(soundPlayer->midiBus, track, pitch);
                byteStream += 2;
                break;
        }
    }

    // Close
    reader->currentPos = byteStream;
    return trackEndType;
}


// Update MidiStream
void midi_player_update_track(struct SoundPlayer *soundPlayer, u32 track) {
    struct MidiTrackStream *reader;
    struct MidiChannel *channel;
    struct MidiNote *note;
    u32 anyNotePlayed;
    u32 clocks;
    u32 i;

    reader = &soundPlayer->midiReader[track];
    if (!reader->active) {
        return;
    }

    anyNotePlayed = FALSE;
    gMidiNoteNext = 0; // Reset "Current Note To Modify" counter.

    while (reader->clocksThisFrame < soundPlayer->clocksPerFrame) {
        if (soundPlayer->withinLoop && !reader->withinLoop && (reader->clocksPassed >= soundPlayer->clocksPassedAtLoop)) {
            reader->activeAtLoop = reader->active;
            reader->commandAtLoop = reader->command;
            reader->loopStartPos = reader->currentPos;
            reader->withinLoop = TRUE;
        }

        if (midi_player_read_track(soundPlayer, track) == M_TRACK_READER_STOP) {
            reader->active = FALSE;
            midi_channel_cut(soundPlayer->midiBus, track);
            return;
        }

        clocks = midi_parse_variable_length(&reader->currentPos);
        if (clocks != 0) {
            for (note = gMidiNotePool, i = 0; i < gMidiNoteNext; i++, note++) {
                if (note->velocity != 0) { // Note has non-zero velocity.
                    midi_note_start(soundPlayer->midiBus, note->channel, note->key, note->velocity);
                    anyNotePlayed = TRUE;
                } else { // Note is muted.
                    midi_note_stop(soundPlayer->midiBus, note->channel, note->key);
                }
            }
            gMidiNoteNext = 0; // Reset "Current Note To Modify" counter.
        }

        reader->clocksThisFrame += clocks << 8;
        reader->clocksPassed += clocks;
    }

    reader->clocksThisFrame -= soundPlayer->clocksPerFrame;

    // Use Filter EQ with LFO
    if (anyNotePlayed) {
        channel = &soundPlayer->midiBus->midiChannel[track];
        if (channel->filterEQ && (gMidiLFOMode == LFO_MODE_KEYPRESS)) {
            midi_equalizer_reset();
            midi_lfo_start(&gMidiLFO);
        }
    }
}


// Update SoundPlayer Volume
void midi_player_update_volume_fade(struct SoundPlayer *soundPlayer) {
    u32 volumeProduct;
    u32 volumeLevel;

    switch (soundPlayer->volumeFadeType) {
        case VOL_FADE_RESET:
            break;

        case VOL_FADE_IN:
            soundPlayer->volumeFadeEnv += soundPlayer->volumeFadeSpd;
            if (soundPlayer->volumeFadeEnv >= (1 << 15)) {
                soundPlayer->volumeFadeType = VOL_FADE_RESET;
                soundPlayer->volumeFadeEnv = (1 << 15);
                soundPlayer->volumeFadeSpd = 0;
            }
            break;

        case VOL_FADE_OUT_CLEAR:
            if (soundPlayer->volumeFadeEnv < soundPlayer->volumeFadeSpd) {
                soundPlayer->volumeFadeType = VOL_FADE_RESET;
                soundPlayer->volumeFadeEnv = 0;
                midi_player_stop(soundPlayer);
            } else {
                soundPlayer->volumeFadeEnv -= soundPlayer->volumeFadeSpd;
            }
            break;

        case VOL_FADE_OUT_PAUSE:
            if (soundPlayer->volumeFadeEnv < soundPlayer->volumeFadeSpd) {
                soundPlayer->volumeFadeEnv = 0;
                midi_player_set_pause(soundPlayer, TRUE);
            } else {
                soundPlayer->volumeFadeEnv -= soundPlayer->volumeFadeSpd;
            }
            break;
    }

    volumeProduct = (soundPlayer->songVolume * soundPlayer->volumeA * soundPlayer->volumeFadeEnv) >> 8;
    volumeLevel = volumeProduct >> 15;
    if (volumeLevel > 0xFF) volumeLevel = 0xFF;
    midi_bus_set_volume(soundPlayer->midiBus, volumeLevel);

    volumeLevel = ((volumeProduct >> 8) * soundPlayer->volumeB) >> 15;
    if (volumeLevel > 0xFF) volumeLevel = 0xFF;
    midi_bus_set_track_volume(soundPlayer->midiBus, volumeLevel, soundPlayer->volumeTrackMap);
}


// Update SoundPlayer MidiStream
void midi_player_update_sequence(struct SoundPlayer *soundPlayer) {
    struct MidiTrackStream *mTrkReader;
    u32 noActiveReader;
    u32 i;

    // If the SoundPlayer is stopped or paused, do not proceed.
    if ((soundPlayer->song == NULL) || soundPlayer->isPaused) {
        return;
    }

    gMidiPlayerNewDeltaTime = 0;

    // Update MIDI Track Streams
    for (i = 0; i < soundPlayer->usedTracks; i++) {
        midi_player_update_track(soundPlayer, i);
    }

    // If the above loop modifies the value of gMidiPlayerNewDeltaTime, apply to SoundPlayer.
    if (gMidiPlayerNewDeltaTime != 0) {
        soundPlayer->clocksPerFrame = gMidiPlayerNewDeltaTime;
    }

    // Check if any MIDI Track Readers are currently operating.
    mTrkReader = soundPlayer->midiReader;
    noActiveReader = TRUE;
    for (i = 0; (i < soundPlayer->usedTracks) && noActiveReader; i++, mTrkReader++) {
        if (mTrkReader->active) {
            noActiveReader = FALSE;
        }
    }

    // If none are active, remove the Sound Sequence from the SoundPlayer.
    if (noActiveReader) {
        soundPlayer->song = NULL;
    }
}


// Update Main
void midi_sound_main(void) {
    struct SoundPlayer *soundPlayer;
    u32 clocks;
    u32 i;
    s32 rvb0 = gMidiReverbControls[0];
    s32 rvb1 = gMidiReverbControls[1];
    s32 rvb2 = gMidiReverbControls[2];
    s32 rvb3 = gMidiReverbControls[3];

    gMidiVCOUNTAtStart = REG_VCOUNT;

    // Standard Sound Players
    for (i = 0; i <= last_sound_player_id; i++) {
        soundPlayer = sound_players[i];
        if (soundPlayer != NULL) {
            midi_player_update_volume_fade(soundPlayer);
            midi_player_update_sequence(soundPlayer);
            midi_channel_update_mod_all(soundPlayer->midiBus);
            if (soundPlayer->song != NULL) {
                rvb0 -= (64 * 2) - (soundPlayer->rvb1Wet * 2);
                rvb1 -= 64 - soundPlayer->rvb2Phase;
                rvb2 -= 64 - soundPlayer->rvb3Decay;
                rvb3 -= 64 - soundPlayer->rvb4LowCut;
            }
        }
    }

    // DirectMidi Player
    soundPlayer = sDirectPlayer;
    if (midi_direct_player_enabled && (soundPlayer != NULL)) {
        midi_direct_player_update();
        rvb0 -= (64 * 2) - (soundPlayer->rvb1Wet * 2);
        rvb1 -= 64 - soundPlayer->rvb2Phase;
        rvb2 -= 64 - soundPlayer->rvb3Decay;
        rvb3 -= 64 - soundPlayer->rvb4LowCut;
    }

    // LFO
    if ((gMidiLFOPlayer != NULL) && (gMidiLFOMode != LFO_MODE_DISABLED)) {
        clocks = midi_player_get_clocks_per_frame(gMidiLFOPlayer->midiTempo, gMidiLFOPlayer->playerSpeed, 24);
        midi_lfo_update(&gMidiLFO, clocks);
        midi_equalizer_set_position((gMidiLFO.output * gMidiLFODepth) >> 8);
    }

    midi_note_update_all();
    gMidiVCOUNTAtEnd = REG_VCOUNT;

    if (rvb0 < 0) rvb0 = 0;
    if (rvb0 > 127) rvb0 = 127;
    if (rvb1 < 0) rvb1 = 0;
    if (rvb1 > 127) rvb1 = 127;
    if (rvb2 < 0) rvb2 = 0;
    if (rvb2 > 127) rvb2 = 127;
    if (rvb3 < 0) rvb3 = 0;
    if (rvb3 > 127) rvb3 = 127;

    midi_directsound_set_reverb(rvb0, rvb1, rvb2, rvb3);
    midi_directsound_update();
}


// Set Main Reverb Controller Scratch/Queue
void midi_player_set_reverb(u32 rvb0, u32 rvb1, u32 rvb2, u32 rvb3) {
    gMidiReverbControls[0] = rvb0;
    gMidiReverbControls[1] = rvb1;
    gMidiReverbControls[2] = rvb2;
    gMidiReverbControls[3] = rvb3;
}


// Stub
void midi_stub(void) {
}


// Initialise SoundPlayer
void midi_player_init(struct SoundPlayer *soundPlayer, struct MidiBus *midiBus, u32 totalTracks, struct MidiTrackStream *midiReader, u32 priorityEnabled) {
    soundPlayer->song = NULL;
    soundPlayer->midiBus = midiBus;
    soundPlayer->totalTracks = totalTracks;
    soundPlayer->midiReader = midiReader;
    soundPlayer->priorityEnabled = priorityEnabled;
    soundPlayer->songVolume = 100;
}


// Parse Midi Variable-Length Quantity
u32 midi_parse_variable_length(const u8 **upstream) {
    const u8 *stream = *upstream;
    u32 time = 0;
    u8 current;

    do {
        current = *stream++;
        time <<= 7;
        time |= (current & 0x7F);
    } while ((current & 0x80) != 0);

    *upstream = stream;
    return time;
}


/* DIRECT-MIDI SOUND PLAYER */


// Initialise DirectMidi Player
void midi_direct_player_init(struct SoundPlayer *soundPlayer, struct MidiTrackStream *midiReader, u32 totalTracks,
                                struct MidiBus *midiBus, struct MidiChannel *midiChannels, u8 *sequenceSource) {
    if (!midi_direct_player_enabled) {
        return;
    }

    midi_bus_init(midiBus, totalTracks, midiChannels);
    midi_bus_set_bank(midiBus, instrument_banks[midi_direct_player_bank_id]);
    midi_bus_set_volume(midiBus, midi_direct_player_volume);
    midi_bus_set_priority(midiBus, midi_direct_player_priority);
    midi_player_init(soundPlayer, midiBus, totalTracks, midiReader, midi_direct_player_priority);

    soundPlayer->playerSpeed = (1 << 8);
    soundPlayer->volumeB = (1 << 8);
    soundPlayer->volumeFadeType = 0;
    soundPlayer->volumeFadeEnv = (1 << 15);
    soundPlayer->volumeFadeSpd = 0;
    soundPlayer->midiTempo = midi_direct_player_tempo;
    soundPlayer->clocksPerFrame = midi_player_get_clocks_per_frame(midi_direct_player_tempo, (1 << 8), 24);
    soundPlayer->rvb1Wet = 64;
    soundPlayer->rvb2Phase = 64;
    soundPlayer->rvb3Decay = 64;
    soundPlayer->rvb4LowCut = 64;

    sDirectPlayer = soundPlayer;
    sDirectBus = midiBus;
    sDirectSequence = sequenceSource;
    sDirectLength = 0;
    sDirectLastCommand = 0;
}


// Append DirectMidi Sequence Instructions
void midi_direct_player_append_sequence(u8 *midiIn, u32 length) {
    while ((length != 0) && (sDirectLength < 0x200)) {
        sDirectSequence[sDirectLength++] = *midiIn;
        midiIn++;
        length--;
    }
}


// Parse DirectMidi Sequence Instructions
u32 midi_direct_player_read_sequence(void) {
    struct SoundPlayer *soundPlayer = sDirectPlayer;
    u8 *stream = sDirectSequence;
    u32 sequenceLength = sDirectLength;
    u32 lengthIsInsufficient = FALSE;
    u32 i;

    while ((sequenceLength != 0) && !lengthIsInsufficient) {
        u32 shortCommandLength, longCommandLength;
        u8 *commandArgs;
        u8 command, arg0, arg1;
        u32 track;
        u16 pitch;

        if (stream[0] >= 0x80) {
            command = 0xF0 & stream[0];
            track = 0x0F & stream[0];
            commandArgs = stream + 1;
            i = 1;
            sDirectLastCommand = ((command >= 0x80) && (command < 0xF0)) ? stream[0] : 0;
        } else {
            command = 0xF0 & sDirectLastCommand;
            track = 0x0F & sDirectLastCommand;
            commandArgs = stream;
            i = 0;
        }

        shortCommandLength = i + 1;
        longCommandLength = i + 2;
        arg0 = commandArgs[0];
        arg1 = commandArgs[1];

        switch (command) {
            // Note Off
            case MSG_NOTE_OFF:
                if (sequenceLength < longCommandLength) {
                    lengthIsInsufficient = TRUE;
                    break;
                }
                midi_player_add_note(track, arg0, 0);
                stream += longCommandLength;
                sequenceLength -= longCommandLength;
                break;

            // Note On
            case MSG_NOTE_ON:
                if (sequenceLength < longCommandLength) {
                    lengthIsInsufficient = TRUE;
                    break;
                }
                midi_player_add_note(track, arg0, arg1);
                stream += longCommandLength;
                sequenceLength -= longCommandLength;
                break;

            // Polyphonic Key Pressure (Aftertouch) [Not Supported]
            case MSG_POLYPHONIC_KEY_PRESSURE:
                if (sequenceLength < longCommandLength) {
                    lengthIsInsufficient = TRUE;
                    break;
                }
                stream += longCommandLength;
                sequenceLength -= longCommandLength;
                break;

            // MIDI Controller Change
            case MSG_CONTROLLER_CHANGE:
                if (sequenceLength < longCommandLength) {
                    lengthIsInsufficient = TRUE;
                    break;
                }
                midi_player_parse_controller_change(soundPlayer, track, arg0, arg1);
                stream += longCommandLength;
                sequenceLength -= longCommandLength;
                break;

            // Program Change
            case MSG_PROGRAM_CHANGE:
                if (sequenceLength < shortCommandLength) {
                    lengthIsInsufficient = TRUE;
                    break;
                }
                midi_channel_set_patch(soundPlayer->midiBus, track, arg0);
                stream += shortCommandLength;
                sequenceLength -= shortCommandLength;
                break;

            // Channel Pressure (Aftertouch) [Not Supported]
            case MSG_CHANNEL_PRESSURE:
                if (sequenceLength < shortCommandLength) {
                    lengthIsInsufficient = TRUE;
                    break;
                }
                stream += shortCommandLength;
                sequenceLength -= shortCommandLength;
                break;

            // Pitch Wheel Change
            case MSG_PITCH_WHEEL_CHANGE:
                if (sequenceLength < longCommandLength) {
                    lengthIsInsufficient = TRUE;
                    break;
                }
                pitch = (arg0 & 0x7F) | ((arg1 & 0x7F) << 7);
                midi_channel_set_pitch(soundPlayer->midiBus, track, pitch);
                stream += longCommandLength;
                sequenceLength -= longCommandLength;
                break;

            // Meta Event / System Message
            case 0xF0:
                switch (track) {
                    case 0:
                        for (i = 1; (i < sequenceLength) && (stream[i] < 0x80); i++);
                        midi_player_parse_sys_exc_message(soundPlayer, stream + 1);
                        stream += i;
                        sequenceLength -= i;
                        break;

                    case 1:
                    case 2:
                    case 3:
                        if (sequenceLength < 2) {
                            lengthIsInsufficient = TRUE;
                            break;
                        }
                        stream += 2;
                        sequenceLength -= 2;
                        break;

                    default:
                        stream += 1;
                        sequenceLength -= 1;
                        break;
                }
                break;

            default:
                stream += 1;
                sequenceLength -= 1;
                break;
        }
    }

    for (i = 0; i < sequenceLength; i++) {
        sDirectSequence[i] = stream[i];
    }

    sDirectLength = sequenceLength;
}


// Update DirectMidi Player
void midi_direct_player_update(void) {
    struct MidiChannel *midiChannel;
    struct MidiNote *note;
    u32 anyNotePlayed;
    u32 i;

    midi_channel_update_mod_all(sDirectBus);
    anyNotePlayed = FALSE;
    gMidiNoteNext = 0;
    midi_direct_player_read_sequence();

    for (note = gMidiNotePool, i = 0; i < gMidiNoteNext; i++, note++) {
        if (note->velocity != 0) {
            midi_note_start(sDirectBus, note->channel, note->key, note->velocity);

            midiChannel = &sDirectBus->midiChannel[note->channel];
            if (midiChannel->filterEQ && (gMidiLFOMode == LFO_MODE_KEYPRESS)) {
                anyNotePlayed = TRUE;
            }
        } else {
            midi_note_stop(sDirectBus, note->channel, note->key);
        }
    }
    if (anyNotePlayed) {
        midi_equalizer_reset();
        midi_lfo_start(&gMidiLFO);
    }
}


/* SOUND AREA */


#include "audio/sound_players.inc.c"


// Initialise Sound Area
void midi_sound_init(void) {
    u32 i;

    midi_directsound_init(DIRECTSOUND_MODE_STEREO, AUDIO_SAMPLE_RATE,
                    DMA_SAMPLE_BUFFER_SIZE, (void *)sPCMBufferArea,
                    SAMPLE_SCRATCHPAD_SIZE, (void *)sPCMScratchArea,
                    DIRECTSOUND_CHANNEL_COUNT, sSamplerArea);
    midi_psg_init();
    midi_note_init(DIRECTSOUND_CHANNEL_COUNT, sSoundChannelArea);

    for (i = 0; i < SOUND_PLAYER_COUNT; i++) {
        midi_bus_init(sound_player_init_table[i].midiBus, sound_player_init_table[i].totalTracks, sound_player_init_table[i].midiChannels);
        midi_player_init(sound_player_init_table[i].soundPlayer, sound_player_init_table[i].midiBus, sound_player_init_table[i].totalTracks,
                            sound_player_init_table[i].trackStreams, sound_player_init_table[i].priorityEnabled);
    }

    gMidiCommVars = &sMidiCommVar1;
    gMidiCommVarTotal = 4;

    for (i = 0; i < 4; i++) {
        gMidiCommVars[i] = 0;
    }

    gMidiLFOMode = LFO_MODE_DISABLED;
    gMidiLFOPlayer = NULL;
    gMidiReverbControls[0] = 0;
    gMidiReverbControls[1] = 0;
    gMidiReverbControls[2] = 0;
    gMidiReverbControls[3] = 0;
    sDirectPlayer = NULL;
}
