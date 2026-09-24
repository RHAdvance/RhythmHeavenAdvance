/* Rhythm Toys - Confession Machine */


// Sound Effect Pool
struct SongHeader *const love_machine_sfx_pool_right[] = {
    &s_heat_v_anataga_seqData,
    &s_heat_v_anatatara_seqData,
    &s_heat_v_kimiga_seqData,
    NULL
};

// Sound Effect Pool
struct SongHeader *const love_machine_sfx_pool_left[] = {
    &s_heat_v_jituhane_seqData,
    &s_heat_v_watasine_seqData,
    &s_heat_v_watasitara_seqData,
    NULL
};

// Sound Effect Pool
struct SongHeader *const love_machine_sfx_pool_down[] = {
    &s_heat_v_okubyo_seqData,
    &s_heat_v_majime_seqData,
    &s_heat_v_kouitta_seqData,
    NULL
};

// Sound Effect Pool
struct SongHeader *const love_machine_sfx_pool_up[] = {
    &s_heat_v_doji_seqData,
    &s_heat_v_sugoi_seqData,
    &s_heat_v_koumietemo_seqData,
    NULL
};

// Sound Effect Pool
struct SongHeader *const love_machine_sfx_pool_b[] = {
    &s_heat_v_demo_seqData,
    &s_heat_v_yappari_seqData,
    &s_heat_v_dakedo_seqData,
    NULL
};

// Sound Effect Pool
struct SongHeader *const love_machine_sfx_pool_a[] = {
    &s_heat_v_suki_seqData,
    &s_heat_v_kirai_seqData,
    &s_heat_v_seki_seqData,
    NULL
};

// Sound Effect Pool EN
struct SongHeader *const love_machine_sfx_pool_right_en[] = {
    &s_heat_v_anataga_en_seqData,
    &s_heat_v_anatatara_en_seqData,
    &s_heat_v_kimiga_en_seqData,
    NULL
};

// Sound Effect Pool EN
struct SongHeader *const love_machine_sfx_pool_left_en[] = {
    &s_heat_v_jituhane_en_seqData,
    &s_heat_v_watasine_en_seqData,
    &s_heat_v_watasitara_en_seqData,
    NULL
};

// Sound Effect Pool EN
struct SongHeader *const love_machine_sfx_pool_down_en[] = {
    &s_heat_v_okubyo_en_seqData,
    &s_heat_v_majime_en_seqData,
    &s_heat_v_kouitta_en_seqData,
    NULL
};

// Sound Effect Pool EN
struct SongHeader *const love_machine_sfx_pool_up_en[] = {
    &s_heat_v_doji_en_seqData,
    &s_heat_v_sugoi_en_seqData,
    &s_heat_v_koumietemo_en_seqData,
    NULL
};

// Sound Effect Pool EN
struct SongHeader *const love_machine_sfx_pool_b_en[] = {
    &s_heat_v_demo_en_seqData,
    &s_heat_v_yappari_en_seqData,
    &s_heat_v_dakedo_en_seqData,
    NULL
};

// Sound Effect Pool EN
struct SongHeader *const love_machine_sfx_pool_a_en[] = {
    &s_heat_v_suki_en_seqData,
    &s_heat_v_kirai_en_seqData,
    &s_heat_v_seki_en_seqData,
    NULL
};

// [D_089e9b04] Confession Machine SFX Pool Table
struct SongHeader *const *love_machine_sfx_table[] = {
    /* A */ love_machine_sfx_pool_a,
    /* B */ love_machine_sfx_pool_b,
    /* U */ love_machine_sfx_pool_up,
    /* D */ love_machine_sfx_pool_down,
    /* L */ love_machine_sfx_pool_left,
    /* R */ love_machine_sfx_pool_right
};

// [D_089e9b04] Confession Machine SFX Pool Table EN
struct SongHeader *const *love_machine_sfx_table_en[] = {
    /* A */ love_machine_sfx_pool_a_en,
    /* B */ love_machine_sfx_pool_b_en,
    /* U */ love_machine_sfx_pool_up_en,
    /* D */ love_machine_sfx_pool_down_en,
    /* L */ love_machine_sfx_pool_left_en,
    /* R */ love_machine_sfx_pool_right_en
};

// [D_089e9b1c] Confession Machine Demo BPM
u16 love_machine_demo_bpm = 130;

// [D_089e9b20] Confession Machine Demo Script (Unused)
struct RhythmToysDemo love_machine_demo_seq[] = {
    /* 0x00 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x5F },
    /* 0x01 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x5F },
    /* 0x02 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x8E },
    /* 0x03 */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x18 },
    /* 0x04 */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x19 },
    /* 0x05 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x60 },
    /* 0x06 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x5F },
    /* 0x07 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x8E },
    /* 0x08 */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x18 },
    /* 0x09 */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x19 },
    /* 0x0A */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x60 },
    /* 0x0B */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x5F },
    /* 0x0C */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x8E },
    /* 0x0D */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x18 },
    /* 0x0E */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x19 },
    /* 0x0F */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x60 },
    /* 0x10 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x5F },
    /* 0x11 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x5F },
    /* 0x12 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x13 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x14 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x15 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x16 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x2F },
    /* 0x17 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x9C },
    /* 0x18 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x19 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x16 },
    /* 0x1A */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x86 },
    /* 0x1B */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x1C */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x16 },
    /* 0x1D */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x86 },
    /* 0x1E */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x1F */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x16 },
    /* 0x20 */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x26 },
    /* 0x21 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x22 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x16 },
    /* 0x23 */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x26 },
    /* 0x24 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x25 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x24 },
    /* 0x26 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x0C },
    /* 0x27 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x24 },
    /* 0x28 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x0C },
    /* 0x29 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x24 },
    /* 0x2A */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x03 },
    /* 0x2B */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x03 },
    /* 0x2C */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x03 },
    /* 0x2D */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x03 },
    /* 0x2E */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x0C },
    /* 0x2F */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x23 },
    /* 0x30 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x8E },
    /* 0x31 */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x18 },
    /* 0x32 */ { RHYTHM_TOYS_DEMO_PRESS_DOWN, 0x19 },
    /* 0x33 */ { RHYTHM_TOYS_DEMO_PRESS_B, 0x60 },
    /* 0x34 */ { RHYTHM_TOYS_DEMO_PRESS_A, 0x5F },
    /* STOP */ END_OF_RHYTHM_TOYS_DEMO
};
