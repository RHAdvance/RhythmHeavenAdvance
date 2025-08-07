extern struct SampleData sample_221_data;
struct InstrumentPCM instrument_pcm_0307 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_221_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x0B8000,
};

extern struct SampleData sample_222_data;
struct InstrumentPCM instrument_pcm_0308 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_222_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x0B8000,
};

extern struct SampleData sample_093_data;
extern struct SampleData sdance_and_data;
struct InstrumentPCM instrument_pcm_0309 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_and_data,
#else
    /* Sample    */ &sample_093_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x034867,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_094_data;
extern struct SampleData sdance_pose_data;
struct InstrumentPCM instrument_pcm_0310 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_pose_data,
#else
    /* Sample    */ &sample_094_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_095_data;
extern struct SampleData sdance_let_data;
struct InstrumentPCM instrument_pcm_0311 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_let_data,
#else
    /* Sample    */ &sample_095_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x083502,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_096_data;
extern struct SampleData sdance_sit_data;
struct InstrumentPCM instrument_pcm_0312 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_sit_data,
#else
    /* Sample    */ &sample_096_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_097_data;
extern struct SampleData sdance_down_data;
struct InstrumentPCM instrument_pcm_0313 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_down_data,
#else
    /* Sample    */ &sample_097_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_098_data;
extern struct SampleData sdance_pap_data;
struct InstrumentPCM instrument_pcm_0314 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_pap_data,
#else
    /* Sample    */ &sample_098_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_099_data;
extern struct SampleData sdance_punch_data;
struct InstrumentPCM instrument_pcm_0315 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_punch_data,
#else
    /* Sample    */ &sample_099_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_100_data;
extern struct SampleData sdance_and_g_data;
struct InstrumentPCM instrument_pcm_0316 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_and_g_data,
#else
    /* Sample    */ &sample_100_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x034867,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_101_data;
extern struct SampleData sdance_pose_g_data;
struct InstrumentPCM instrument_pcm_0317 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_pose_g_data,
#else
    /* Sample    */ &sample_101_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_102_data;
extern struct SampleData sdance_let_g_data;
struct InstrumentPCM instrument_pcm_0318 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_let_g_data,
#else
    /* Sample    */ &sample_102_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x083502,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_103_data;
extern struct SampleData sdance_sit_g_data;
struct InstrumentPCM instrument_pcm_0319 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_sit_g_data,
#else
    /* Sample    */ &sample_103_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_104_data;
extern struct SampleData sdance_down_g_data;
struct InstrumentPCM instrument_pcm_0320 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_down_g_data,
#else
    /* Sample    */ &sample_104_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_105_data;
extern struct SampleData sdance_pap_g_data;
struct InstrumentPCM instrument_pcm_0321 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_pap_g_data,
#else
    /* Sample    */ &sample_105_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_106_data;
extern struct SampleData sdance_punch_g_data;
struct InstrumentPCM instrument_pcm_0322 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_punch_g_data,
#else
    /* Sample    */ &sample_106_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_223_data;
struct InstrumentPCM instrument_pcm_0323 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_223_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x0B8000,
};

extern struct SampleData sample_224_data;
extern struct SampleData sdance_and_s_data;
struct InstrumentPCM instrument_pcm_0324 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_and_s_data,
#else
    /* Sample    */ &sample_224_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_225_data;
extern struct SampleData sdance_and_g_s_data;
struct InstrumentPCM instrument_pcm_0325 = {
    /* Type      */ INSTRUMENT_PCM_FIXED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
#ifdef SFX
    /* Sample    */ &sdance_and_g_s_data,
#else
    /* Sample    */ &sample_225_data,
#endif
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern union Instrument inst_bank_47[];
struct InstrumentSubRhythm instrument_rhy_0326 = {
    /* Type      */ INSTRUMENT_SUB_RHYTHM,
    /* Base Key  */ 36,
    /* Sub-Bank  */ inst_bank_47
};
