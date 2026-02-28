extern struct SampleData sample_001_data;
struct InstrumentPCM instrument_pcm_0001 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_001_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x59CC48,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x106A05,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x13E350,
};

extern struct SampleData sample_002_data;
struct InstrumentPCM instrument_pcm_0002 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_002_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x000000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x00FC1F,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x082378,
};

extern struct SampleData sample_002_data;
struct InstrumentPCM instrument_pcm_0003 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_002_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x402433,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x00540A,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x055552,
};

extern struct SampleData sample_003_data;
struct InstrumentPCM instrument_pcm_0004 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_003_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x1E7FBA,
};

extern struct SampleData sample_004_data;
struct InstrumentPCM instrument_pcm_0005 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_004_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x13E350,
};

extern struct SampleData sample_005_data;
struct InstrumentPCM instrument_pcm_0006 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_005_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x1E7FBA,
};

extern struct SampleData sample_006_data;
struct InstrumentPCM instrument_pcm_0007 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_006_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x218000,
};

extern struct SampleData sample_007_data;
struct InstrumentPCM instrument_pcm_0008 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_007_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x1E7FBA,
};

extern struct SampleData sample_008_data;
struct InstrumentPCM instrument_pcm_0009 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_008_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x13E350,
};

extern struct SampleData sample_009_data;
struct InstrumentPCM instrument_pcm_0010 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_009_data,
    /* ADSR Init */ 0x000000,
    /* ADSR Sus  */ 0x7F0000,
    /* ADSR Atk  */ 0x4D9364,
    /* ADSR Dec  */ 0x208000,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x055552,
};

extern union Instrument inst_bank_42[];
struct InstrumentSubSplit instrument_spl_0011 = {
    /* Type      */ INSTRUMENT_SUB_SPLIT,
    /* Base Key  */ 12,
    /* Key Split */ keysplit_table_9,
    /* Sub-Bank  */ inst_bank_42
};

extern struct SampleData sample_010_data;
struct InstrumentPCM instrument_pcm_0012 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_010_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x66A052,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x106A05,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x18EA90,
};

extern struct SampleData sample_011_data;
struct InstrumentPCM instrument_pcm_0013 = {
    /* Type      */ INSTRUMENT_PCM_ALIGNED,
    /* Key       */ 0x3C,
    /* Fast Read */ FALSE,
    /* Panning   */ 127,
    /* Sample    */ &sample_011_data,
    /* ADSR Init */ 0x7F0000,
    /* ADSR Sus  */ 0x267C1F,
    /* ADSR Atk  */ 0x600000,
    /* ADSR Dec  */ 0x09D936,
    /* ADSR Fade */ 0x000000,
    /* ADSR Rel  */ 0x0F6A90,
};

extern union Instrument inst_bank_50[];
struct InstrumentSubRhythm instrument_rhy_0014 = {
    /* Type      */ INSTRUMENT_SUB_RHYTHM,
    /* Base Key  */ 36,
    /* Sub-Bank  */ inst_bank_50
};

extern union Instrument inst_bank_48[];
struct InstrumentSubRhythm instrument_rhy_0015 = {
    /* Type      */ INSTRUMENT_SUB_RHYTHM,
    /* Base Key  */ 36,
    /* Sub-Bank  */ inst_bank_48
};

extern union Instrument inst_bank_47[];
struct InstrumentSubRhythm instrument_rhy_0016 = {
    /* Type      */ INSTRUMENT_SUB_RHYTHM,
    /* Base Key  */ 36,
    /* Sub-Bank  */ inst_bank_47
};
