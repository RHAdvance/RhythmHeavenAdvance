#pragma once

#include "global.h"
#include "levels.h"

#define SAVE_BUFFER_SIZE      sizeof(struct SaveBuffer)
#define SAVE_BUFFER_NEW_SIZE  sizeof(struct ExtraSaveData)
#define SAVE_BUFFER_OLD_SIZE  SAVE_BUFFER_SIZE - SAVE_BUFFER_NEW_SIZE
#define EXTRA_MAGIC "ENOT" // yes, like the slugcat

// helper functions
#define SET_ADVANCE_FLAG(flags, flag) (flags |= (1 << flag))
#define CLEAR_ADVANCE_FLAG(flags, flag) (flags &= ~(1 << flag))
#define CHECK_ADVANCE_FLAG(flags, flag) ((flags >> flag) & 1)
#define TOGGLE_ADVANCE_FLAG(flags, flag) (flags ^= (1 << flag))

enum AdvanceFlagsEnum {
    /* 00 */ ADVANCE_FLAG_SAVE_CONVERTED            = (1 << 0),
    /* 01 */ ADVANCE_FLAG_USE_ALT_GAME_SELECT_MUSIC = (1 << 1),
    /* 02 */ ADVANCE_FLAG_SEEN_DISCLAMER            = (1 << 2),
};

extern struct SaveBuffer {
    /* [0x000] Header */
    struct SaveBufferHeader {
        char RIQ[4]; // "RIQ"
        u32 bufferSize;
        u32 checksum;
        u32 unkC; // 0x26040000
    } header;
    /* [0x010] Game Save Data */
    struct TengokuSaveData {
        s8 gsCursorX, gsCursorY;
        s8 recentLevelX, recentLevelY;
        s8 recentLevelState;
        u8 recentLevelClearedByBarista;
        u8 levelStates[TOTAL_LEVELS];
        u16 recentLevelScore;
        u16 levelScores[TOTAL_LEVELS];
        u16 currentFlow;
        u8 unkB0;
        u8 advanceFlags;
        u8 totalSongs;
        u8 unkB3; // above
        struct StudioSongData {
            u8 songID;
            s8 replayID;
            u8 drumKitID;
            u8 unk3;
        } studioSongs[45 + 10];
        u8 levelTotalPlays[TOTAL_LEVELS];
        u8 levelFirstOK[TOTAL_LEVELS];
        u8 levelFirstSuperb[TOTAL_LEVELS];
        u8 totalPerfects;
        u8 campaignsCleared[TOTAL_PERFECT_CAMPAIGNS];
        u8 campaignState;
        u8 campaignAttemptsLeft;
        u8 playsUntilNextCampaign;
        u8 currentCampaign;
        u8 unk26A;
        u8 readingMaterialUnlocked[20];
        u8 drumKitsUnlocked[15];
        u8 totalMedals;
        u8 unk28F;
        u8 minFailsForBaristaHelp;
        u8 unk291;
        u32 unk294[16];
        /*
            u32 highScoreMrUpbeat;
            u32 highScoreMannequinFactory;
            u32 highScoreSickBeatsSP;
            u32 highScoreQuizShowEX;
            u32 unk2A4;
            u32 unk2A8;
            u32 unk2AC;
            u32 unk2B0;
            u32 soundMode;
            u32 perfectClearCafeDialoguePending;
            u32 unk2BC;
            u32 unk2C0;
            u32 unk2C4;
            u32 unk2C8;
            u32 unk2CC;
            u32 unk2D0;
        */
        struct DrumReplaySaveAlloc {
            u8 nextAvailableBlock;
            u8 replayStartBlocks[10];
            u16 replaySizes[10];
            u8 saveMemory[0x38][0x100];
        } drumReplaysAlloc;

        struct ExtraSaveData {
            u32 checksum;
            char magic[4]; // "ENOT"
            u16 extraLevelScores[TOTAL_EXTRA_LEVELS];
            u8 extraLevelStates[TOTAL_EXTRA_LEVELS];
            u8 extraLevelTotalPlays[TOTAL_EXTRA_LEVELS];
            u8 extraLevelFirstOK[TOTAL_EXTRA_LEVELS];
            u8 extraLevelFirstSuperb[TOTAL_EXTRA_LEVELS];
            u8 extraCampaignsCleared[TOTAL_EXTRA_PERFECT_CAMPAIGNS];
            u8 extraReadingMaterialUnlocked[0];
        } extraData;
    } data;
} *D_030046a8;


extern void init_ewram(void);
extern void *get_save_buffer_start(void);
extern void *get_save_buffer_end(void);
extern void *get_memory_heap_start(void);
extern u32 get_memory_heap_length(void);
extern s32 generate_save_buffer_checksum(s32 *buffer, u32 size);
extern void init_save_buffer(void);
extern void clear_save_data(void);
extern void set_playtest_save_data(void);
extern s32 copy_to_save_buffer(u8 *cartRAM);
extern s32 copy_sram_to_save_buffer(void);
extern s32 copy_sram_backup_to_save_buffer(void);
extern void flush_save_buffer(u8 *cartRAM);
extern s32 get_offset_from_save_buffer(void *buffer);
extern void write_save_buffer_header_to_sram(u8 *cartRAM);
extern void write_save_buffer_data_to_sram(u8 *buffer, u32 size);
extern void flush_save_buffer_to_sram(void);
extern void flush_save_buffer_to_sram_backup(void);
extern void func_080009c8_stub(void);
extern void func_080009cc_stub(void);
extern s32 func_080009d0(s16 *);
extern s32 func_080009fc(void);

extern u8 get_level_state(struct TengokuSaveData *saveData, s32 id);
extern u16 get_level_score(struct TengokuSaveData *saveData, s32 id);
extern u8 get_level_total_plays(struct TengokuSaveData *saveData, s32 id);
extern u8 get_level_first_ok(struct TengokuSaveData *saveData, s32 id);
extern u8 get_level_first_superb(struct TengokuSaveData *saveData, s32 id);
extern u8 get_campaign_cleared(struct TengokuSaveData *saveData, s32 id);
extern void set_level_state(struct TengokuSaveData *saveData, s32 id, u8 state);
extern void set_level_score(struct TengokuSaveData *saveData, s32 id, u16 score);
extern void set_level_total_plays(struct TengokuSaveData *saveData, s32 id, u8 totalPlays);
extern void set_level_first_ok(struct TengokuSaveData *saveData, s32 id, u8 firstOK);
extern void set_level_first_superb(struct TengokuSaveData *saveData, s32 id, u8 firstSuperb);
extern void set_campaign_cleared(struct TengokuSaveData *saveData, s32 id, u8 cleared);
extern void set_reading_material_unlocked(struct TengokuSaveData *saveData, s32 id, u8 unlocked);
extern u8 get_reading_material_unlocked(struct TengokuSaveData *saveData, s32 id);