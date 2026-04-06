

/* SOUND PLAYER DATA */


// VALUES
#define N_TRACKS_MUS0   15
#define N_TRACKS_MUS1   12
#define N_TRACKS_MUS2   12
#define N_TRACKS_SFX    5


// STATIC VARIABLES
static struct SoundPlayer sMusicPlayer0;
static struct SoundPlayer sMusicPlayer1;
static struct SoundPlayer sMusicPlayer2;
static struct SoundPlayer sSfxPlayer0;
static struct SoundPlayer sSfxPlayer1;
static struct SoundPlayer sSfxPlayer2;
static struct SoundPlayer sSfxPlayer3;
static struct SoundPlayer sSfxPlayer4;
static struct SoundPlayer sSfxPlayer5;
static struct SoundPlayer sSfxPlayer6;
static struct SoundPlayer sSfxPlayer7;
static struct SoundPlayer sSfxPlayer8;
static struct SoundPlayer sSfxPlayer9;

extern struct MidiChannel sMusicPlayer0Channels[N_TRACKS_MUS0];
extern struct MidiBus sMusicPlayer0MidiBus;
extern struct MidiTrackStream sMusicPlayer0Streams[N_TRACKS_MUS0];
extern struct MidiChannel sMusicPlayer1Channels[N_TRACKS_MUS1];
extern struct MidiBus sMusicPlayer1MidiBus;
extern struct MidiTrackStream sMusicPlayer1Streams[N_TRACKS_MUS1];
extern struct MidiChannel sMusicPlayer2Channels[N_TRACKS_MUS2];
extern struct MidiBus sMusicPlayer2MidiBus;
extern struct MidiTrackStream sMusicPlayer2Streams[N_TRACKS_MUS2];
extern struct MidiChannel sSfxPlayer0Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer0MidiBus;
extern struct MidiTrackStream sSfxPlayer0Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer1Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer1MidiBus;
extern struct MidiTrackStream sSfxPlayer1Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer2Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer2MidiBus;
extern struct MidiTrackStream sSfxPlayer2Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer3Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer3MidiBus;
extern struct MidiTrackStream sSfxPlayer3Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer4Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer4MidiBus;
extern struct MidiTrackStream sSfxPlayer4Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer5Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer5MidiBus;
extern struct MidiTrackStream sSfxPlayer5Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer6Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer6MidiBus;
extern struct MidiTrackStream sSfxPlayer6Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer7Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer7MidiBus;
extern struct MidiTrackStream sSfxPlayer7Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer8Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer8MidiBus;
extern struct MidiTrackStream sSfxPlayer8Streams[N_TRACKS_SFX];
extern struct MidiChannel sSfxPlayer9Channels[N_TRACKS_SFX];
extern struct MidiBus sSfxPlayer9MidiBus;
extern struct MidiTrackStream sSfxPlayer9Streams[N_TRACKS_SFX];

// Last SoundPlayer Index
u32 last_sound_player_id = SOUND_PLAYER_COUNT - 1;


// DirectPlayer Data
u8 midi_direct_player_enabled = TRUE;
u8 midi_direct_player_bank_id = INST_BANK_37;
u8 midi_direct_player_volume = 127;
u8 midi_direct_player_priority = 0;
u8 midi_direct_player_tempo = 150;


// [D_08aa4324] SoundPlayer List
struct SoundPlayer *sound_players[] = {
    &sMusicPlayer0,
    &sMusicPlayer1,
    &sMusicPlayer2,
    &sSfxPlayer0,
    &sSfxPlayer1,
    &sSfxPlayer2,
    &sSfxPlayer3,
    &sSfxPlayer4,
    &sSfxPlayer5,
    &sSfxPlayer6,
    &sSfxPlayer7,
    &sSfxPlayer8,
    &sSfxPlayer9
};


// [D_08aa4358] SoundPlayer Initialisation Table
struct SoundPlayerInitTable sound_player_init_table[] = {
    /* MUSIC PLAYER 0 */ {
        /* Player Index  */ MUSIC_PLAYER_0,
        /* Track Count   */ N_TRACKS_MUS0,
        /* Use Priority  */ FALSE,
        /* MIDI Channels */ sMusicPlayer0Channels,
        /* MIDI Bus      */ &sMusicPlayer0MidiBus,
        /* MIDI Streams  */ sMusicPlayer0Streams,
        /* Sound Player  */ &sMusicPlayer0
    },
    /* MUSIC PLAYER 1 */ {
        /* Player Index  */ MUSIC_PLAYER_1,
        /* Track Count   */ N_TRACKS_MUS1,
        /* Use Priority  */ FALSE,
        /* MIDI Channels */ sMusicPlayer1Channels,
        /* MIDI Bus      */ &sMusicPlayer1MidiBus,
        /* MIDI Streams  */ sMusicPlayer1Streams,
        /* Sound Player  */ &sMusicPlayer1
    },
    /* MUSIC PLAYER 2 */ {
        /* Player Index  */ MUSIC_PLAYER_2,
        /* Track Count   */ N_TRACKS_MUS2,
        /* Use Priority  */ FALSE,
        /* MIDI Channels */ sMusicPlayer2Channels,
        /* MIDI Bus      */ &sMusicPlayer2MidiBus,
        /* MIDI Streams  */ sMusicPlayer2Streams,
        /* Sound Player  */ &sMusicPlayer2
    },
    /* SFX PLAYER 0 */ {
        /* Player Index  */ SFX_PLAYER_0,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer0Channels,
        /* MIDI Bus      */ &sSfxPlayer0MidiBus,
        /* MIDI Streams  */ sSfxPlayer0Streams,
        /* Sound Player  */ &sSfxPlayer0
    },
    /* SFX PLAYER 1 */ {
        /* Player Index  */ SFX_PLAYER_1,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer1Channels,
        /* MIDI Bus      */ &sSfxPlayer1MidiBus,
        /* MIDI Streams  */ sSfxPlayer1Streams,
        /* Sound Player  */ &sSfxPlayer1
    },
    /* SFX PLAYER 2 */ {
        /* Player Index  */ SFX_PLAYER_2,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer2Channels,
        /* MIDI Bus      */ &sSfxPlayer2MidiBus,
        /* MIDI Streams  */ sSfxPlayer2Streams,
        /* Sound Player  */ &sSfxPlayer2
    },
    /* SFX PLAYER 3 */ {
        /* Player Index  */ SFX_PLAYER_3,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer3Channels,
        /* MIDI Bus      */ &sSfxPlayer3MidiBus,
        /* MIDI Streams  */ sSfxPlayer3Streams,
        /* Sound Player  */ &sSfxPlayer3
    },
    /* SFX PLAYER 4 */ {
        /* Player Index  */ SFX_PLAYER_4,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer4Channels,
        /* MIDI Bus      */ &sSfxPlayer4MidiBus,
        /* MIDI Streams  */ sSfxPlayer4Streams,
        /* Sound Player  */ &sSfxPlayer4
    },
    /* SFX PLAYER 5 */ {
        /* Player Index  */ SFX_PLAYER_5,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer5Channels,
        /* MIDI Bus      */ &sSfxPlayer5MidiBus,
        /* MIDI Streams  */ sSfxPlayer5Streams,
        /* Sound Player  */ &sSfxPlayer5
    },
    /* SFX PLAYER 6 */ {
        /* Player Index  */ SFX_PLAYER_6,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer6Channels,
        /* MIDI Bus      */ &sSfxPlayer6MidiBus,
        /* MIDI Streams  */ sSfxPlayer6Streams,
        /* Sound Player  */ &sSfxPlayer6
    },
    /* SFX PLAYER 7 */ {
        /* Player Index  */ SFX_PLAYER_7,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer7Channels,
        /* MIDI Bus      */ &sSfxPlayer7MidiBus,
        /* MIDI Streams  */ sSfxPlayer7Streams,
        /* Sound Player  */ &sSfxPlayer7
    },
    /* SFX PLAYER 8 */ {
        /* Player Index  */ SFX_PLAYER_8,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer8Channels,
        /* MIDI Bus      */ &sSfxPlayer8MidiBus,
        /* MIDI Streams  */ sSfxPlayer8Streams,
        /* Sound Player  */ &sSfxPlayer8
    },
    /* SFX PLAYER 9 */ {
        /* Player Index  */ SFX_PLAYER_9,
        /* Track Count   */ N_TRACKS_SFX,
        /* Use Priority  */ TRUE,
        /* MIDI Channels */ sSfxPlayer9Channels,
        /* MIDI Bus      */ &sSfxPlayer9MidiBus,
        /* MIDI Streams  */ sSfxPlayer9Streams,
        /* Sound Player  */ &sSfxPlayer9
    }
};


// [D_08aa445c] SoundPlayer Count
u8 sound_player_count = SOUND_PLAYER_COUNT;


// [D_08aa4460] Simplified SoundPlayer Table
struct SoundPlayerTable sound_player_table[] = {
    /* MUSIC PLAYER 0 */ {
        /* Sound Player */ &sMusicPlayer0,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_MUS0,
        /* Use Priority */ FALSE
    },
    /* MUSIC PLAYER 1 */ {
        /* Sound Player */ &sMusicPlayer1,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_MUS1,
        /* Use Priority */ FALSE
    },
    /* MUSIC PLAYER 2 */ {
        /* Sound Player */ &sMusicPlayer2,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_MUS2,
        /* Use Priority */ FALSE
    },
    /* SFX PLAYER 0 */ {
        /* Sound Player */ &sSfxPlayer0,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 1 */ {
        /* Sound Player */ &sSfxPlayer1,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 2 */ {
        /* Sound Player */ &sSfxPlayer2,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 3 */ {
        /* Sound Player */ &sSfxPlayer3,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 4 */ {
        /* Sound Player */ &sSfxPlayer4,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 5 */ {
        /* Sound Player */ &sSfxPlayer5,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 6 */ {
        /* Sound Player */ &sSfxPlayer6,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 7 */ {
        /* Sound Player */ &sSfxPlayer7,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 8 */ {
        /* Sound Player */ &sSfxPlayer8,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    },
    /* SFX PLAYER 9 */ {
        /* Sound Player */ &sSfxPlayer9,
        /* NULL         */ 0,
        /* Track Count  */ N_TRACKS_SFX,
        /* Use Priority */ TRUE
    }
};
