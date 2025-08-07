#include "global.h"
#include "sound.h"
#include "midi.h"


/* AUDIO LIBRARY - MIDI CHANNELS */


// Update MidiChannel Modulation
void midi_channel_update_mod(struct MidiBus *midiBus, u32 track) {
    struct MidiChannel *midiChannel = &midiBus->midiChannel[track];
    s32 modVolume;
    u32 busVolume;
    u32 result;

    // Update Modulation
    if (midiChannel->modDelayCount != 0) {
        midiChannel->modDelayCount--;
        midiChannel->modCount = 0;
    } else {
        midiChannel->modCount += midiChannel->modSpeed;
    }

    midiChannel->modResult = (midiChannel->modDepth * midi_sine_table[(midiChannel->modCount >> 8)]) >> 8;

    // Update Volume Wheel
    modVolume = 128;
    if (midiChannel->modType == MOD_TYPE_TREMOLO) {
        modVolume += midiChannel->modResult;
        if (modVolume < 0) modVolume = 0;
        if (modVolume > 160) modVolume = 160;
    }

    if (midiChannel->modType == MOD_TYPE_PANNING) {
        midi_channel_update_panning(midiBus, track);
    }

    busVolume = ((midiBus->volumeTrackMap >> track) & 1) ? midiBus->volumeB : midiBus->volumeA;
    result = modVolume;
    result = (busVolume * midiChannel->volume * midiChannel->expression * result) >> 21;
    if (result > 0xFF) result = 0xFF;
    midiChannel->volumeWheel = result;

    // Update Random Key Offset
    if ((midiChannel->keyModDepth != 0) && (midiChannel->keyModInterval != 0)) {
        if (midiChannel->keyModCount == 0) {
            midiChannel->keyModCount = midiChannel->keyModInterval;
        }
        midiChannel->keyModCount--;
    }
}

// add a comment here it's confusing


// Update MidiChannel Modulation (All)
void midi_channel_update_mod_all(struct MidiBus *midiBus) {
    u32 i;

    for (i = 0; i < midiBus->totalChannels; i++) {
        midi_channel_update_mod(midiBus, i);
    }
}


// SoundChannel Note Cut
void midi_channel_cut(struct MidiBus *midiBus, u32 track) {
    struct MidiChannel *midiChannel = &midiBus->midiChannel[track];
    u32 i;

    if (midiChannel->volumeWheel == 0) {
        midi_channel_stop(midiBus, track);
        return;
    }

    for (i = 0; i < gMidiSoundChannelCount; i++) {
        if (gMidiSoundChannelPool[i].active && (gMidiSoundChannelPool[i].midiChannel == midiChannel)) {
            gMidiSoundChannelPool[i].adsr.stage = ADSR_STAGE_FORCE_STOP;
        }
    }

    for (i = 0; i < TOTAL_PSG_CHANNELS; i++) {
        if (gMidiPSGChannelPool[i].active && (gMidiPSGChannelPool[i].midiChannel == midiChannel)) {
            gMidiPSGChannelPool[i].adsr.stage = ADSR_STAGE_FORCE_STOP;
        }
    }
}


// SoundChannel Stop
void midi_channel_stop(struct MidiBus *midiBus, u32 track) {
    struct MidiChannel *midiChannel = &midiBus->midiChannel[track];
    u32 i;

    for (i = 0; i < gMidiSoundChannelCount; i++) {
        if (gMidiSoundChannelPool[i].active && (gMidiSoundChannelPool[i].midiChannel == midiChannel)) {
            gMidiSoundChannelPool[i].active = FALSE;
            midi_sampler_stop(i);
        }
    }

    for (i = 0; i < TOTAL_PSG_CHANNELS; i++) {
        if (gMidiPSGChannelPool[i].active && (gMidiPSGChannelPool[i].midiChannel == midiChannel)) {
            gMidiPSGChannelPool[i].adsr.stage = ADSR_STAGE_RELEASE;
            gMidiPSGChannelPool[i].adsr.envelope = 0;
        }
    }
}


// SoundChannel Note Cut (All)
void midi_channel_cut_all(struct MidiBus *midiBus) {
    u32 i;

    for (i = 0; i < midiBus->totalChannels; i++) {
        midi_channel_cut(midiBus, i);
    }
}


// SoundChannel Stop (All)
void midi_channel_stop_all(struct MidiBus *midiBus) {
    u32 i;

    for (i = 0; i < midiBus->totalChannels; i++) {
        midi_channel_stop(midiBus, i);
    }
}


// Set MidiBus Priority
void midi_bus_set_priority(struct MidiBus *midiBus, u8 priority) {
    u32 i;

    midiBus->priority = priority; // and here too

    for (i = 0; i < midiBus->totalChannels; i++) {
        midi_channel_set_priority(midiBus, i, 0);
    }
}


// Set MidiBus Track Volume & Mask
void midi_bus_set_track_volume(struct MidiBus *midiBus, u8 volume, u16 mask) {
    midiBus->volumeB = volume;
    midiBus->volumeTrackMap = mask;
}


// Initialise MidiChannel
void midi_channel_init(struct MidiChannel *midiChannel) {
    midiChannel->disabled = FALSE;
    midiChannel->fixedPitch = FALSE;
    midiChannel->instPatch = 0;
    midiChannel->bankSelect = 0;
    midiChannel->volume = 100;
    midiChannel->panning = 64;
    midiChannel->expression = 127;
    midiChannel->unk4_b21 = 0;
    midiChannel->modDepth = 0;
    midiChannel->modType = MOD_TYPE_VIBRATO;
    midiChannel->modRange = 1;
    midiChannel->modSpeed = (60 << 8);
    midiChannel->modCount = 0;
    midiChannel->modDelay = 0;
    midiChannel->modDelayCount = 0;
    midiChannel->modResult = 0;
    midiChannel->pitchWheel = 0x2000;
    midiChannel->pitchRange = 2;
    midiChannel->priority = 0;
    midiChannel->filterEQ = FALSE;
    midiChannel->phaseStereo = FALSE;
    midiChannel->randomPitchResult = (1 << 8);
    midiChannel->randomPitchFloor = (1 << 8);
    midiChannel->randomPitchRange = 0;
    midiChannel->keyModDepth = 0;
    midiChannel->keyModInterval = 0;
    midiChannel->keyModCount = 0;
    
    // too much text

}


// Initialise MidiBus
void midi_bus_init(struct MidiBus *midiBus, u32 totalChannels, struct MidiChannel *midiChannelArray) {
    u32 i;

    midiBus->volumeA = 100;
    midiBus->volumeB = 100;
    midiBus->volumeTrackMap = 0;
    midiBus->key = 0;
    midiBus->panning = 0;
    midiBus->pitch = 0;
    midiBus->unk8 = (20 << 8);
    midiBus->tuningTable = midi_tuning_table;
    midiBus->totalChannels = totalChannels;
    midiBus->midiChannel = midiChannelArray;

    for (i = 0; i < totalChannels; i++) {
        midi_channel_init(&midiChannelArray[i]);
    }

    midiBus->priority = 0;

    for (i = 0; i < ARRAY_COUNT(midiBus->keyModScale); i++) {
        midiBus->keyModScale[i] = 0;
    }
}


// Set MidiBus Sound Bank
void midi_bus_set_bank(struct MidiBus *midiBus, union Instrument *instrumentBank) {
    midiBus->soundBank = instrumentBank;
}


/* SOUND CHANNEL OPERATIONS */


// Update SoundChannel Pitch
u32 midi_note_update_pitch(struct SoundChannel *soundChannel) {
    struct MidiBus *midiBus;
    struct MidiChannel *midiChannel;
    s32 outputFrequency, keyFrequency;
    u32 randomKeyOffsetMax;
    s32 key, subKey;
    s32 pitchWheel;
    u32 inc;

    // Do not calculate pitch envelope for unpitched instruments.
    if (*soundChannel->instrument.type == INSTRUMENT_PCM_FIXED) {
        return 0;
    }

    midiBus = soundChannel->midiBus;
    midiChannel = soundChannel->midiChannel;
    outputFrequency = soundChannel->frequency;

    // Do not calculate frequency modulation if MidiChannel is set to fixed pitch.
    if (midiChannel->fixedPitch) {
        return outputFrequency;
    }

    // Pitch Envelope: Random Key Offset
    randomKeyOffsetMax = midiChannel->keyModDepth;
    if ((randomKeyOffsetMax != 0) && (midiChannel->keyModInterval != 0) && (midiChannel->keyModCount == 0)) {
        s32 randomKey = soundChannel->key + midi_random((randomKeyOffsetMax * 2) + 1) - randomKeyOffsetMax + midiBus->key;
        s32 pitchRange;
        s32 what = randomKey;

        while (what < 0) randomKey += 12; // ????????
        randomKey += midiBus->keyModScale[what % ARRAY_COUNT(midiBus->keyModScale)];

        while (randomKey < 0) {
            randomKey += 12;
        }
        while (randomKey > 127) {
            randomKey -= 12;
        }

        outputFrequency = midi_key_to_freq(midiBus, randomKey);
        soundChannel->frequency = outputFrequency;
        pitchRange = midiChannel->pitchRange;
        soundChannel->pitchDecFreq = soundChannel->frequency - midi_key_to_freq(midiBus, randomKey - pitchRange);
        soundChannel->pitchIncFreq = midi_key_to_freq(midiBus, randomKey + pitchRange) - soundChannel->frequency;
        soundChannel->modStepFreq = midi_key_to_freq(midiBus, randomKey + midiChannel->modRange) - soundChannel->frequency;
    }

    // Pitch Envelope: MidiChannel Pitch Wheel (14 Bits, Signed)
    pitchWheel = midiChannel->pitchWheel;
    if (pitchWheel != 0x2000) {
        u32 frequencyRange = (pitchWheel < 0x2000) ? soundChannel->pitchDecFreq : soundChannel->pitchIncFreq;

        if (pitchWheel < 0x2000) {
            outputFrequency -= frequencyRange;
        } else {
            pitchWheel -= 0x2000;
        }

        key = pitchWheel / (0x2000 / 12); // 682
        subKey = pitchWheel - (key * (0x2000 / 12));
        keyFrequency = midi_step_freq_table[key];
        inc = midi_step_freq_table[key + 1] - keyFrequency;
        inc = keyFrequency + ((inc * subKey) / (0x2000 / 12));
        outputFrequency += ((inc * frequencyRange) >> 16);
    }

    // Pitch Envelope: MidiBus Fine-Pitch (Q24.8, Signed)
    if (midiBus->pitch != 0) {
        key = (midiBus->pitch >> 8);
        subKey = midiBus->pitch & 0xFF;

        while (key < 0 || key >= 12) {
            if (key < 0) {
                outputFrequency >>= 1;
                key += 12;
            } else {
                outputFrequency <<= 1;
                key -= 12;
            }
        }

        keyFrequency = midi_step_freq_table[key];
        inc = midi_step_freq_table[key + 1] - keyFrequency;
        inc = keyFrequency + ((inc * subKey) >> 8);
        outputFrequency += ((inc * outputFrequency) >> 16);
    }

    // Pitch Envelope: Modulation
    if (midiChannel->modType == MOD_TYPE_VIBRATO) {
        outputFrequency += ((midiChannel->modResult * soundChannel->modStepFreq * 8) >> 8);
    }

    // Pitch Envelope: Random Pitch
    if (midiChannel->randomPitchResult != (1 << 8)) {
        outputFrequency = ((outputFrequency * midiChannel->randomPitchResult) >> 8);
    }

    return outputFrequency;
}


// Update SoundChannel Volume
u32 midi_note_update_volume(struct SoundChannel *soundChannel) {
    u32 volume;

    if (soundChannel->midiChannel == NULL) {
        return (soundChannel->velocity * (soundChannel->adsr.envelope >> 16)) >> 7;
    } else {
        volume = soundChannel->midiChannel->volumeWheel * soundChannel->velocity * (soundChannel->adsr.envelope >> 16);
        return volume >> 14;
    }
}


// Update SoundChannel ADSR
u32 midi_note_update_adsr(struct SoundChannel *soundChannel) {
    struct InstrumentPCM *instrument;
    struct AdsrEnvelope *adsr;
    u32 finished;
    s32 envelope;
    u32 release;

    finished = FALSE;
    instrument = soundChannel->instrument.pcm;
    adsr = &soundChannel->adsr;
    envelope = adsr->envelope;

    switch (adsr->stage) {
        /* ATTACK:
            Trigger: Note On
            Increment: inst->attack
            Target: 127 (Q8.16)
        */
        case ADSR_STAGE_ATTACK:
            envelope += instrument->attack;
            if (envelope >= (127 << 16)) {
                envelope = (127 << 16);
                adsr->stage = ADSR_STAGE_DECAY;
            }
            break;

        /* DECAY:
            Trigger: Attack End
            Decrement: inst->decay
            Target: inst->sustain
        */
        case ADSR_STAGE_DECAY:
            envelope -= instrument->decay;
            if (envelope <= instrument->sustain) {
                envelope = instrument->sustain;
                adsr->stage = ADSR_STAGE_SUSTAIN;
            }
            break;

        /* FADE:
            Trigger: Decay End
            Decrement: inst->fade
            Target: 0
        */
        case ADSR_STAGE_SUSTAIN:
            envelope -= instrument->fade;
            if (envelope >= (127 << 16)) {
                envelope = (127 << 16);
            } else if (envelope <= 0) {
                envelope = 0;
                finished = TRUE;
            }
            break;

        /* RELEASE:
            Trigger: Note Off, Muted Note
            Decrement: inst->release
            Target: 0
        */
        case ADSR_STAGE_RELEASE:
            envelope -= instrument->release;
            if (envelope <= 0) {
                envelope = 0;
                finished = TRUE;
            }
            break;

        /* RELEASE (Note Cut):
            Trigger: Note Override, End of Loop Region, End of Track
            Decrement: inst->release (or default of 0x60000 if not set)
            Target: 0
        */
        case ADSR_STAGE_FORCE_STOP:
            release = instrument->release;
            if (instrument->release == 0) {
                release = (6 << 16);
            }
            envelope -= release;
            if (envelope <= 0) {
                envelope = 0;
                finished = TRUE;
            }
            break;
    }

    adsr->envelope = envelope;
    return finished;
}


// Update PCM SoundChannel
void midi_note_update_id(u32 id) {
    struct SoundChannel *soundChannel = &gMidiSoundChannelPool[id];

    if (!soundChannel->active) {
        return;
    }

    if (midi_sampler_is_active(id)) {
        soundChannel->justStarted = FALSE;
        if (!soundChannel->midiChannel->fixedPitch) {
            midi_sampler_set_frequency(id, midi_note_update_pitch(soundChannel));
        }

        midi_sampler_set_volume(id, midi_note_update_volume(soundChannel));
        if (midi_note_update_adsr(soundChannel) == FALSE) {
            return;
        }

        midi_sampler_stop(id);
    }

    soundChannel->active = FALSE;
}


// Update PCM SoundChannel (All)
void midi_note_update_all(void) {
    u32 i;

    for (i = 0; i < gMidiSoundChannelCount; i++) {
        midi_note_update_id(i);
    }

    midi_psg_update();
}


// Initialise PCM SoundChannels
void midi_note_init(u32 totalChannels, struct SoundChannel *soundChannelPool) {
    u32 i;

    gMidiSoundChannelCount = totalChannels;
    gMidiSoundChannelPool = soundChannelPool;

    for (i = 0; i < gMidiSoundChannelCount; i++) {
        gMidiSoundChannelPool[i].active = FALSE;
    }
}


// Get First Active PCM SoundChannel not at ADSR Stage RELEASE.
s32 midi_note_get_first_active(struct MidiChannel *midiChannel, u8 key) {
    struct SoundChannel *soundChannel = gMidiSoundChannelPool;
    struct AdsrEnvelope *adsr;
    s32 i;

    for (i = 0; i < gMidiSoundChannelCount; i++, soundChannel++) {
        if (soundChannel->active && (soundChannel->midiChannel == midiChannel) && (soundChannel->key == key)) {
            adsr = &gMidiSoundChannelPool[i].adsr;
            if (adsr->stage != ADSR_STAGE_RELEASE) {
                return i;
            }
        }
    }

    return -1;
}


// Get First Inactive PCM SoundChannel
s32 midi_note_get_first_inactive(void) {
    s32 i;

    for (i = 0; i < gMidiSoundChannelCount; i++) {
        if (!gMidiSoundChannelPool[i].active) {
            return i;
        }
    }

    return -1;
}


// Get PCM SoundChannel with Lowest Volume
s32 midi_note_get_quietest_released(void) {
    struct SoundChannel *soundChannel;
    u32 lowestVolume, channelVolume;
    s32 index, i;

    index = -1;
    lowestVolume = 0x10000;

    for (i = 0, soundChannel = gMidiSoundChannelPool; i < gMidiSoundChannelCount; i++, soundChannel++) {
        if (soundChannel->active && (soundChannel->adsr.stage == ADSR_STAGE_RELEASE)) {
            channelVolume = soundChannel->midiChannel->volumeWheel * soundChannel->velocity;
            if (channelVolume < lowestVolume) {
                lowestVolume = channelVolume;
                index = i;
            }
        }

    }

    return index;
}


// Get PCM SoundChannel with Lowest Volume (exclude ADSR)
s32 midi_note_get_quietest_unreleased(void) {
    u32 lowestVolume, channelVolume;
    s32 index, i;

    index = -1;
    lowestVolume = 0x10000;

    for (i = 0; i < gMidiSoundChannelCount; i++) {
        if (gMidiSoundChannelPool[i].active) {
            channelVolume = gMidiSoundChannelPool[i].midiChannel->volumeWheel * gMidiSoundChannelPool[i].velocity;
            if (channelVolume < lowestVolume) {
                lowestVolume = channelVolume;
                index = i;
            }
        }
    }

    return index;
}


// Get PCM SoundChannel with Lowest Priority and Velocity
s32 midi_note_get_least_significant(struct MidiBus *midiBus, u32 track, u32 velocity) {
    struct SoundChannel *soundChannel;
    struct MidiChannel *midiChannel;
    u32 channelPriority, lowestPriority;
    u32 lowestVolume;
    s32 index, i;

    midiChannel = &midiBus->midiChannel[track];
    channelPriority = (midiChannel->priority << 4) + (15 - track);
    velocity *= midiChannel->volumeWheel;
    lowestPriority = channelPriority;
    index = -1;

    for (i = 0, soundChannel = gMidiSoundChannelPool; i < gMidiSoundChannelCount; i++, soundChannel++) {
        if (!soundChannel->active || (soundChannel->priority > lowestPriority)) {
            continue;
        }

        if (soundChannel->priority == lowestPriority) {
            if ((lowestPriority == channelPriority) && soundChannel->justStarted) {
                u32 volume = soundChannel->velocity;
                volume *= soundChannel->midiChannel->volumeWheel;
                if (volume > velocity) {
                    continue;
                }
            }

            if (index < 0) {
                lowestVolume = soundChannel->velocity * soundChannel->midiChannel->volumeWheel;
                index = i;
            } else if (lowestVolume > (soundChannel->velocity * soundChannel->midiChannel->volumeWheel)) {
                index = i;
                lowestVolume = soundChannel->velocity * soundChannel->midiChannel->volumeWheel;
            }
        } else {
            lowestPriority = soundChannel->priority;
            lowestVolume = soundChannel->velocity * soundChannel->midiChannel->volumeWheel;
            index = i;
        }
    }

    return index;
}


// SoundChannel Midi 'Note Off' Event
void midi_note_stop(struct MidiBus *midiBus, u32 track, u8 key) {
    struct SoundChannel *psgChannel, *pcmChannel;
    struct AdsrEnvelope *adsr;
    s32 adsrState;
    s32 i;

    // Set ADSR Stage to RELEASE for all relevant PCM SoundChannels.
    do {
        if ((i = midi_note_get_first_active(&midiBus->midiChannel[track], key)) < 0) {
            break;
        }

        adsr = &gMidiSoundChannelPool[i].adsr;
        adsr->stage = ADSR_STAGE_RELEASE;
    } while (TRUE);

    // Set ADSR Stage to RELEASE for all relevant PSG SoundChannels.
    psgChannel = gMidiPSGChannelPool;
    adsrState = ADSR_STAGE_RELEASE;
    for (i = 3; i >= 0; i--, psgChannel++) {
        if (psgChannel->active && (psgChannel->midiChannel == &midiBus->midiChannel[track]) && (psgChannel->key == key)) {
            adsr = &psgChannel->adsr;
            adsr->stage = adsrState;
        }
    }
}


// Return First Most Replaceable DirectSound Channel
s32 midi_note_get_free(struct MidiBus *midiBus, u32 track, u8 key, u8 velocity) {
    s32 channel;

    // Return the first inactive buffer.
    channel = midi_note_get_first_inactive();
    if (channel >= 0) {
        return channel;
    }

    // Return the quietest buffer (below threshold; see function).
    channel = midi_note_get_quietest_released();
    if (channel >= 0) {
        return channel;
    }

    // Return a buffer of a lower priority.
    channel = midi_note_get_least_significant(midiBus, track, velocity);
    if (channel >= 0) {
        return channel;
    }

    return -1;
}


// Convert PCM SoundChannel Panning to Sampler Stereo Bias (Right)
u8 midi_get_stereo_bias_r(u8 panning) {
    return (panning >= 64) ? 127 : (panning * 2);
}


// Convert PCM SoundChannel Panning to Sampler Stereo Bias (Left)
u8 midi_get_stereo_bias_l(u8 panning) {
    return (panning < 64) ? 127 : ((127 - panning) * 2);
}


// Get Frequency of Midi Key
u32 midi_key_to_freq(struct MidiBus *midiBus, u8 key) {
    if (key > 127) {
        key = (key < 191) ? 127 : 0;
    }

    return midiBus->tuningTable[key];
}


// SoundChannel Midi 'Note On' Event
void midi_note_start(struct MidiBus *midiBus, u32 track, u8 noteKey, u8 noteVelocity) {
    struct MidiChannel *midiChannel;
    struct SoundChannel *soundChannel;
    s32 channelIndex;
    s32 key, randomKey;
    u32 randomKeyOffsetMax;
    u32 pitchRange;
    s32 panning;
    s32 stereoPhase;
    u32 isPSG, isSubRhythm;
    union Instrument instrument;
    struct InstrumentPCM *instPCM;
    struct InstrumentPSG *instPSG;
    struct AdsrEnvelope *adsr;

    // A "Note ON" instruction with a velocity of 0 is a "Note OFF" instruction.
    if (noteVelocity == 0) {
        midi_note_stop(midiBus, track, noteKey);
        return;
    }

    midiChannel = &midiBus->midiChannel[track];
    if (midiChannel->disabled) {
        return;
    }

    instrument = midiBus->soundBank[midiChannel->instPatch];
    if (instrument.type == NULL) {
        return;
    }

    // Get instrument from sub-bank.
    isSubRhythm = FALSE;
    switch (*instrument.type) {
        case INSTRUMENT_SUB_RHYTHM:
            isSubRhythm = TRUE;
            instrument = instrument.rhy->subBank[noteKey - instrument.rhy->baseKey];
            if (instrument.type == NULL) {
                return;
            }
            if (*instrument.type == INSTRUMENT_SUB_RHYTHM || *instrument.type == INSTRUMENT_SUB_SPLIT) {
                return;
            }
            break;

        case INSTRUMENT_SUB_SPLIT:
            instrument = instrument.spl->subBank[instrument.spl->keySplitTable[noteKey - instrument.spl->baseKey]];
            if (instrument.type == NULL) {
                return;
            }
            if (*instrument.type == INSTRUMENT_SUB_RHYTHM || *instrument.type == INSTRUMENT_SUB_SPLIT) {
                return;
            }
            break;
    }

    if (*instrument.type == INSTRUMENT_PSG || *instrument.type == INSTRUMENT_PSG_ALT) {
        // Initialise PSG instrument.
        instPSG = instrument.psg;
        isPSG = TRUE;
        soundChannel = &gMidiPSGChannelPool[instrument.psg->channel];
    } else {
        // Initialise PCM instrument.
        instPCM = instrument.pcm;
        isPSG = FALSE;
        channelIndex = midi_note_get_free(midiBus, track, noteKey, noteVelocity);
        if (channelIndex < 0) {
            return;
        }
        soundChannel = &gMidiSoundChannelPool[channelIndex];
    }

    // Use the built-in key & panning parameters.
    if (!isSubRhythm) {
        key = noteKey + midiBus->key;
        panning = 0;
    } else {
        key = (isPSG) ? instPSG->key : instPCM->key;
        panning = (isPSG) ? instPSG->panning : instPCM->panning;
        if (panning == 127) panning = 0;
    }

    if (key < 0 || key > 127) {
        return;
    }

    // For "Unpitched" instruments, use key from SampleData.
    if (!isPSG && (instPCM->type == INSTRUMENT_PCM_FIXED)) {
        key = instPCM->sample->pitch;
    }

    // Prevent DirectSound interrupts from reading the channel until after initialisation.
    soundChannel->active = FALSE;

    // Initialise SoundChannel frequency.
    randomKeyOffsetMax = midiChannel->keyModDepth;
    if (randomKeyOffsetMax != 0) {
        key += midi_random((randomKeyOffsetMax * 2) + 1) - randomKeyOffsetMax;
        randomKey = key;

        while (randomKey < 0) {
            randomKey += 12;
        }

        key += midiBus->keyModScale[randomKey % ARRAY_COUNT(midiBus->keyModScale)];
        while (key < 0) {
            key += 12;
        }
        while (key > 127) {
            key -= 12;
        }
    }

    soundChannel->frequency = midi_key_to_freq(midiBus, key);

    if (isPSG && (instPSG->channel == PSG_NOISE_CHANNEL)) {
        soundChannel->frequency = key;
    }

    pitchRange = midiChannel->pitchRange;
    soundChannel->pitchDecFreq = soundChannel->frequency - midi_key_to_freq(midiBus, key - pitchRange);
    soundChannel->pitchIncFreq = midi_key_to_freq(midiBus, pitchRange + key) - soundChannel->frequency;
    soundChannel->modStepFreq = midi_key_to_freq(midiBus, key + midiChannel->modRange) - soundChannel->frequency;

    // Initialise SoundChannel.
    soundChannel->key = noteKey;
    soundChannel->velocity = noteVelocity;
    soundChannel->midiChannel = midiChannel;
    soundChannel->panning = panning;
    soundChannel->priority = (midiChannel->priority << 4) + (15 - track);
    soundChannel->justStarted = TRUE;
    soundChannel->midiBus = midiBus;

    // Initialise SoundChannel ADSR.
    adsr = &soundChannel->adsr;
    adsr->stage = ADSR_STAGE_ATTACK;
    adsr->envelope = (isPSG) ? instPSG->initial : instPCM->initial;

    // Initialise SoundChannel instrument.
    if (!isPSG) {
        soundChannel->instrument.pcm = instPCM;
    } else {
        soundChannel->instrument.psg = instPSG;
    }

    // Calculate Random Pitch envelope.
    if (midiChannel->randomPitchRange != 0) {
        midiChannel->randomPitchResult = midiChannel->randomPitchFloor + midi_random(midiChannel->randomPitchRange);
    }

    // Initialise sound outputs.
    if (isPSG) {
        midi_psg_start_id(instPSG->channel);
    } else {
        midi_sampler_stop(channelIndex);
        midi_sampler_load(channelIndex, instPCM->sample);
        midi_sampler_set_volume(channelIndex, midi_note_update_volume(soundChannel));
        stereoPhase = (midiChannel->phaseStereo) ? -1 : 1;
        panning += midi_channel_get_panning(midiBus, track);
        if (panning < 0) panning = 0;
        if (panning > 127) panning = 127;
        midi_sampler_set_stereo_bias(channelIndex, midi_get_stereo_bias_l(panning), midi_get_stereo_bias_r(panning) * stereoPhase);
        midi_sampler_set_frequency(channelIndex, midi_note_update_pitch(soundChannel));
        midi_sampler_set_enable_fast_resample(channelIndex, instPCM->fastRead);
        midi_sampler_set_enable_eq(channelIndex, midiChannel->filterEQ);
        midi_sampler_start(channelIndex);
    }

    midiChannel->modDelayCount = midiChannel->modDelay;
    soundChannel->active = TRUE;
}


/* MIDI CHANNEL OPERATIONS */


// Set MidiChannel Pitch Wheel [Evnt_E]
void midi_channel_set_pitch(struct MidiBus *midiBus, u32 track, u16 pitch) {
    midiBus->midiChannel[track].pitchWheel = pitch;
}


// Set MidiChannel Volume [Ctrl_07]
void midi_channel_set_volume(struct MidiBus *midiBus, u32 track, u8 volume) {
    midiBus->midiChannel[track].volume = volume;
}


// Set MidiChannel Panning [Ctrl_0A]
void midi_channel_set_panning(struct MidiBus *midiBus, u32 track, u8 panning) {
    midiBus->midiChannel[track].panning = panning;
    midi_channel_update_panning(midiBus, track);
}


// Calculate MidiChannel Panning Envelope
u8 midi_channel_get_panning(struct MidiBus *midiBus, u32 track) {
    struct MidiChannel *midiChannel = &midiBus->midiChannel[track];
    s32 panning = midiChannel->panning + (midiBus->panning >> 1);

    if (midiChannel->modType == MOD_TYPE_PANNING) {
        panning += (midiChannel->modResult >> 1);
    }

    if (panning < 0) panning = 0;
    if (panning > 127) panning = 127;
    return panning;
}


// Update SampleStream Panning
void midi_channel_update_panning(struct MidiBus *midiBus, u32 track) {
    s32 panning, isStereo, i;
    struct MidiChannel *midiChannel;
    struct SoundChannel *soundChannel;

    panning = midi_channel_get_panning(midiBus, track);
    midiChannel = &midiBus->midiChannel[track];
    isStereo = (midiChannel->phaseStereo) ? -1 : 1;

    for (i = 0, soundChannel = gMidiSoundChannelPool; i < gMidiSoundChannelCount; i++, soundChannel++) {
        if (soundChannel->active && (soundChannel->midiChannel == midiChannel)) {
            panning += soundChannel->panning;
            if (panning < 0) panning = 0;
            if (panning > 127) panning = 127;
            midi_sampler_set_stereo_bias(i, midi_get_stereo_bias_l(panning), midi_get_stereo_bias_r(panning) * isStereo);
        }
    }
}


// Set MidiChannel Instrument/Patch [Evnt_C]
void midi_channel_set_patch(struct MidiBus *midiBus, u32 track, u8 patch) {
    midiBus->midiChannel[track].instPatch = patch;
}


// Set MidiChannel Expression [Ctrl_0B]
void midi_channel_set_expression(struct MidiBus *midiBus, u32 track, u8 expression) {
    midiBus->midiChannel[track].expression = expression;
}


// Set MidiChannel Bank Select [Ctrl_00; Ctrl_20]
void midi_channel_set_bankselect(struct MidiBus *midiBus, u32 track, u16 args) {
    u16 bankSelect = midiBus->midiChannel[track].bankSelect;

    if (args & 0x8000) {
        // MIDI Controller 00
        bankSelect &= 0x3F80;       // Bits 0-6  = 0
        bankSelect |= (args << 7);  // Bits 7-13 = args
    } else {
        // MIDI Controller 20
        bankSelect &= 0x7F; // Bits 7-13 = 0
        bankSelect |= args; // Bits 0-6  = args
    }

    midiBus->midiChannel[track].bankSelect = bankSelect;
}


// Set Disable MidiChannel
void midi_channel_set_disable(struct MidiBus *midiBus, u32 track, u8 disable) {
    midiBus->midiChannel[track].disabled = disable;
}


// Set MidiChannel Modulation Depth [Ctrl_01]
void midi_channel_set_mod_depth(struct MidiBus *midiBus, u32 track, u8 depth) {
    midiBus->midiChannel[track].modDepth = depth;
}


// Set MidiChannel unk4_b21
void midi_channel_set_unk4_b21(struct MidiBus *midiBus, u32 track, u8 arg) {
    midiBus->midiChannel[track].unk4_b21 = arg;
}


// Set MidiChannel Filter EQ [Ctrl_48]
void midi_channel_set_enable_filter_eq(struct MidiBus *midiBus, u32 track, u8 useFilter) {
    midiBus->midiChannel[track].filterEQ = useFilter;
}


// Set MidiChannel Modulation Type [Ctrl_16]
void midi_channel_set_mod_type(struct MidiBus *midiBus, u32 track, u8 type) {
    midiBus->midiChannel[track].modType = type;
}


// Set MidiChannel Modulation Range
void midi_channel_set_mod_range(struct MidiBus *midiBus, u32 track, u8 arg) {
    midiBus->midiChannel[track].modRange = arg;
}


// Set MidiChannel Modulation Speed [Ctrl_15]
void midi_channel_set_mod_speed(struct MidiBus *midiBus, u32 track, u16 speed) {
    midiBus->midiChannel[track].modSpeed = speed << 8;
}


// Set MidiChannel Modulation Delay [Ctrl_1A]
void midi_channel_set_mod_delay(struct MidiBus *midiBus, u32 track, u8 delay) {
    midiBus->midiChannel[track].modDelay = delay;
}


// Set MidiChannel Modulation Range [Ctrl_14]
void midi_channel_set_pitch_range(struct MidiBus *midiBus, u32 track, u8 range) {
    midiBus->midiChannel[track].pitchRange = range;
}


// Set MidiChannel Offset/Split Stereo Effect [Ctrl_4B]
void midi_channel_set_stereo_phase(struct MidiBus *midiBus, u32 track, u32 isStereo) {
    midiBus->midiChannel[track].phaseStereo = isStereo;
    midi_channel_set_panning(midiBus, track, midiBus->midiChannel[track].panning);
}


// Set MidiChannel Priority [Ctrl_21]
void midi_channel_set_priority(struct MidiBus *midiBus, u32 track, u8 priority) {
    midiBus->midiChannel[track].priority = priority + midiBus->priority;
}


// Set MidiChannel Random Base Pitch [Ctrl_52]
    // Each time this channel performs a note, the base pitch of the note will be
    // offset by an amount within this range. This pitch is only randomised on start.
void midi_channel_set_random_pitch(struct MidiBus *midiBus, u32 track, u8 range) {
    u32 min = 0x8000u / (0x80 + range);
    u32 max = 0x10000u / (0x100 - range);

    midiBus->midiChannel[track].randomPitchFloor = min;
    midiBus->midiChannel[track].randomPitchRange = max - min;
    midiBus->midiChannel[track].randomPitchResult = 0x100;
}


// Set MidiChannel Random Key Modulation Depth [Ctrl_53]
void midi_channel_set_random_key_mod_depth(struct MidiBus *midiBus, u32 track, u8 maxOffset) {
    midiBus->midiChannel[track].keyModDepth = maxOffset;
}


// Set MidiChannel Random Key Modulation Speed [Ctrl_54]
void midi_channel_set_random_key_mod_speed(struct MidiBus *midiBus, u32 track, u8 interval) {
    midiBus->midiChannel[track].keyModInterval = interval;
    midiBus->midiChannel[track].keyModCount = interval;
}


/* MIDI BUS OPERATIONS */


// Set MidiBus Key
void midi_bus_set_key(struct MidiBus *midiBus, s8 key) {
    midiBus->key = key;
}


// Set MidiBus Volume
void midi_bus_set_volume(struct MidiBus *midiBus, u8 volume) {
    midiBus->volumeA = volume;
}


// Set MidiBus Panning
void midi_bus_set_panning(struct MidiBus *midiBus, s8 panning) {
    u32 i;

    midiBus->panning = panning;
    for (i = 0; i < midiBus->totalChannels; i++) {
        midi_channel_update_panning(midiBus, i);
    }
}


// Set MidiBus Pitch
void midi_bus_set_pitch(struct MidiBus *midiBus, s16 pitch) {
    midiBus->pitch = pitch;
}


// Set MidiBus Pitch Wheel Range
void midi_bus_set_pitch_range(struct MidiBus *midiBus, u8 range) {
    u32 i;

    for (i = 0; i < midiBus->totalChannels; i++) {
        midiBus->midiChannel[i].pitchRange = range;
    }
}


// Set MidiBus unk8
void midi_bus_set_unk8(struct MidiBus *midiBus, u16 arg) {
    midiBus->unk8 = arg;
}


// Set MidiBus Tuning
void midi_bus_set_tuning(struct MidiBus *midiBus, u16 *table) {
    midiBus->tuningTable = table;
}
