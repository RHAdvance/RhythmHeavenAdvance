extern const u8 s_hanabi_1_mid[];
struct SongHeader s_hanabi_1_seqData = {
    /* MIDI Sequence */ s_hanabi_1_mid,
    /* Sound Player  */ SFX_PLAYER_5,
    /* Bank Number   */ INST_BANK_7,
    /* Volume        */ 80,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_hanabi_1_seqName,
    /* Song Number   */ 1469
};

extern const u8 s_hanabi_2_mid[];
struct SongHeader s_hanabi_2_seqData = {
    /* MIDI Sequence */ s_hanabi_2_mid,
    /* Sound Player  */ SFX_PLAYER_5,
    /* Bank Number   */ INST_BANK_7,
    /* Volume        */ 80,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_hanabi_2_seqName,
    /* Song Number   */ 1470
};

extern const u8 s_hanabi_3_mid[];
struct SongHeader s_hanabi_3_seqData = {
    /* MIDI Sequence */ s_hanabi_3_mid,
    /* Sound Player  */ SFX_PLAYER_5,
    /* Bank Number   */ INST_BANK_7,
    /* Volume        */ 80,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_hanabi_3_seqName,
    /* Song Number   */ 1471
};

extern const u8 s_hanabi_hai_mid[];
struct SongHeader s_hanabi_hai_seqData = {
    /* MIDI Sequence */ s_hanabi_hai_mid,
    /* Sound Player  */ SFX_PLAYER_5,
    /* Bank Number   */ INST_BANK_7,
    /* Volume        */ 90,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ s_hanabi_hai_seqName,
    /* Song Number   */ 1472
};

extern const u8 s_f_hanabi_v_tamaya_mid[];
struct SongHeader s_f_hanabi_v_tamaya_seqData = {
    /* MIDI Sequence */ s_f_hanabi_v_tamaya_mid,
    /* Sound Player  */ SFX_PLAYER_0,
    /* Bank Number   */ INST_BANK_59,
    /* Volume        */ 70,
    /* Priority      */ 80,
    /* unk8          */ 0xff,
    /* Song Title    */ s_f_hanabi_v_tamaya_seqName,
    /* Song Number   */ 525
};

extern const u8 s_f_hanabi_v_nuei_mid[];
struct SongHeader s_f_hanabi_v_nuei_seqData = {
    /* MIDI Sequence */ s_f_hanabi_v_nuei_mid,
    /* Sound Player  */ SFX_PLAYER_4,
    /* Bank Number   */ INST_BANK_59,
    /* Volume        */ 105,
    /* Priority      */ 90,
    /* unk8          */ 0xff,
    /* Song Title    */ s_f_hanabi_v_nuei_seqName,
    /* Song Number   */ 527
};

// --------------------------------------------------------------

extern const u8 s_hanabi_1_en_mid[];
struct SongHeader s_hanabi_1_en_seqData = {
    /* MIDI Sequence */ s_hanabi_1_en_mid,
    /* Sound Player  */ SFX_PLAYER_5,
    /* Bank Number   */ INST_BANK_FIREWORKS_EN,
    /* Volume        */ 80,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 60
};

struct SongHeader s_hanabi_2_en_seqData = {
    /* MIDI Sequence */ s_hanabi_2_mid,
    /* Sound Player  */ SFX_PLAYER_5,
    /* Bank Number   */ INST_BANK_FIREWORKS_EN,
    /* Volume        */ 80,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 61
};

struct SongHeader s_hanabi_3_en_seqData = {
    /* MIDI Sequence */ s_hanabi_3_mid,
    /* Sound Player  */ SFX_PLAYER_5,
    /* Bank Number   */ INST_BANK_FIREWORKS_EN,
    /* Volume        */ 80,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 62
};

struct SongHeader s_hanabi_hai_en_seqData = {
    /* MIDI Sequence */ s_hanabi_hai_mid,
    /* Sound Player  */ SFX_PLAYER_5,
    /* Bank Number   */ INST_BANK_FIREWORKS_EN,
    /* Volume        */ 90,
    /* Priority      */ 80,
    /* unk8          */ 0x40,
    /* Song Title    */ NULL,
    /* Song Number   */ 63
};

struct SongHeader s_f_hanabi_v_tamaya_en_seqData = {
    /* MIDI Sequence */ s_f_hanabi_v_tamaya_mid,
    /* Sound Player  */ SFX_PLAYER_0,
    /* Bank Number   */ INST_BANK_FIREWORKS_EN,
    /* Volume        */ 70,
    /* Priority      */ 80,
    /* unk8          */ 0xff,
    /* Song Title    */ NULL,
    /* Song Number   */ 64
};

struct SongHeader s_f_hanabi_v_nuei_en_seqData = {
    /* MIDI Sequence */ s_f_hanabi_v_nuei_mid,
    /* Sound Player  */ SFX_PLAYER_4,
    /* Bank Number   */ INST_BANK_FIREWORKS_EN,
    /* Volume        */ 105,
    /* Priority      */ 90,
    /* unk8          */ 0xff,
    /* Song Title    */ NULL,
    /* Song Number   */ 65
};