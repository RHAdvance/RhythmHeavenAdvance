// ------- Japanese -------
extern const u8 s_intro_a_mid[];
struct SongHeader s_intro_a_seqData = {
    /* MIDI Sequence */ s_intro_a_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_8,
    /* Volume        */ 60,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_intro_a_seqName,
    /* Song Number   */ 1481
};

extern const u8 s_intro_one_mid[];
struct SongHeader s_intro_one_seqData = {
    /* MIDI Sequence */ s_intro_one_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_8,
    /* Volume        */ 75,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_intro_one_seqName,
    /* Song Number   */ 1482
};

extern const u8 s_intro_two_mid[];
struct SongHeader s_intro_two_seqData = {
    /* MIDI Sequence */ s_intro_two_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_8,
    /* Volume        */ 127,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_intro_two_seqName,
    /* Song Number   */ 1483
};

extern const u8 s_intro_three_mid[];
struct SongHeader s_intro_three_seqData = {
    /* MIDI Sequence */ s_intro_three_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_8,
    /* Volume        */ 127,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_intro_three_seqName,
    /* Song Number   */ 1484
};

extern const u8 s_intro_four_mid[];
struct SongHeader s_intro_four_seqData = {
    /* MIDI Sequence */ s_intro_four_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_8,
    /* Volume        */ 127,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_intro_four_seqName,
    /* Song Number   */ 1485
};

// ------- English -------

struct SongHeader s_intro_a_en_seqData = {
    /* MIDI Sequence */ s_intro_a_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_COUNTIN_EN,
    /* Volume        */ 60,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 55
};

struct SongHeader s_intro_one_en_seqData = {
    /* MIDI Sequence */ s_intro_one_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_COUNTIN_EN,
    /* Volume        */ 75,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 56
};

struct SongHeader s_intro_two_en_seqData = {
    /* MIDI Sequence */ s_intro_two_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_COUNTIN_EN,
    /* Volume        */ 127,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 57
};

struct SongHeader s_intro_three_en_seqData = {
    /* MIDI Sequence */ s_intro_three_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_COUNTIN_EN,
    /* Volume        */ 127,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 58
};

extern const u8 s_intro_go_mid[];
struct SongHeader s_intro_go_en_seqData = {
    /* MIDI Sequence */ s_intro_go_mid,
    /* Sound Player  */ MUSIC_PLAYER_1,
    /* Bank Number   */ INST_BANK_COUNTIN_EN,
    /* Volume        */ 127,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 59
};