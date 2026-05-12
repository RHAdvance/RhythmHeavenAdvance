#pragma once

#include "global.h"
#include "scenes.h"


// VALUES
enum CafeDialogueTasksEnum {
    /* 00 */ CAFE_EV_INIT_DIALOGUE,
    /* 01 */ CAFE_EV_START_TOPIC,
    /* 02 */ CAFE_EV_UNUSED_02,
    /* 03 */ CAFE_EV_UNUSED_03,
    /* 04 */ CAFE_EV_UNUSED_04,
    /* 05 */ CAFE_EV_UNUSED_05,
    /* 06 */ CAFE_EV_CAMPAIGN_CLEAR_00,
    /* 07 */ CAFE_EV_CAMPAIGN_CLEAR_01,
    /* 08 */ CAFE_EV_UNUSED_08,
    /* 09 */ CAFE_EV_UNUSED_09,
    /* 10 */ CAFE_EV_UNUSED_10,
    /* 11 */ CAFE_EV_OFFER_CLEAR_00,
    /* 12 */ CAFE_EV_OFFER_CLEAR_01,
    /* 13 */ CAFE_EV_OFFER_CLEAR_02_Y,
    /* 14 */ CAFE_EV_OFFER_CLEAR_02_N,
    /* 15 */ CAFE_EV_UNUSED_15,
    /* 16 */ CAFE_EV_UNUSED_16,
    /* 17 */ CAFE_EV_UNUSED_17,
    /* 18 */ CAFE_EV_UNUSED_18,
    /* 19 */ CAFE_EV_UNUSED_19,
    /* 20 */ CAFE_EV_UNUSED_20,
    /* 21 */ CAFE_EV_CAMPAIGN_ADVICE_00,
    /* 22 */ CAFE_EV_CAMPAIGN_ADVICE_01,
    /* 23 */ CAFE_EV_UNUSED_23,
    /* 24 */ CAFE_EV_UNUSED_24,
    /* 25 */ CAFE_EV_UNUSED_25,
    /* 26 */ CAFE_EV_UPCOMING_CAMPAIGN_00,
    /* 27 */ CAFE_EV_ALL_CAMPAIGNS_CLEAR_00,
    /* 28 */ CAFE_EV_ALL_CAMPAIGNS_CLEAR_01,
    /* 29 */ CAFE_EV_EXTRA_CAMPAIGNS_CLEAR_00,
    /* 30 */ CAFE_EV_ALL_CAMPAIGNS_BIG_CLEAR_00,
    /* 31 */ CAFE_EV_ALL_CAMPAIGNS_BIG_CLEAR_01,
    /* 32 */ CAFE_EV_CONTINUE_DIALOGUE
};

enum CafeDialogueTopicsEnum {
    /* 00 */ CAFE_TOPIC_RANDOM,
    /* 01 */ CAFE_TOPIC_CAMPAIGN_CLEAR,
    /* 02 */ CAFE_TOPIC_TROUBLE_CLEARING_LEVEL,
    /* 03 */ CAFE_TOPIC_TROUBLE_GETTING_MEDAL,
    /* 04 */ CAFE_TOPIC_TROUBLE_CLEARING_CAMPAIGN,
    /* 05 */ CAFE_TOPIC_REMEMBERING,
    /* 06 */ CAFE_TOPIC_UPCOMING_CAMPAIGN,
};

enum CafeBgEventsEnum {
    /* 00 */ CAFE_BG_EV_NONE,
    /* 01 */ CAFE_BG_EV_CHEER_01,
    /* 02 */ CAFE_BG_EV_HELPING,
    /* 03 */ CAFE_BG_EV_CHEER_02,
};

enum CafeOptionResultsEnum {
    /* 00 */ CAFE_OPT_YES,
    /* 01 */ CAFE_OPT_NO
};


// MACROS
#define gCafe ((struct CafeSceneData *)gCurrentSceneData)
#define END_OF_DIALOGUE NULL


// TYPES
struct CafeSceneData {
    u32 inputsEnabled;
    struct TextPrinter *printer;
    s16 textAdvIcon;
    u16 nextDialogueTask;
    u8 textAdvReady;
    u8 disableTextUpdates;
    u8 totalLevelsThisSession;
    u8 unused;
    u8 sessionIndexes[5];
    u16 timeSinceLastVisit;
    u16 totalPlayTime;
    u16 totalActivePlayTime;
    u8 bgEvent;
    u8 textAdvHold;
    u8 queryEnabled;
    s8 queryResult;
    s16 levelToClear;
    const char **dialogue;
    char string[0x800];
};

struct PlaySessionInfo {
    struct LevelPlayActivity {
        u8 levelID;
        u8 totalStalePlays;
        u8 justGotPerfect;
        u16 timeOfLastPlay;
        u16 activeTimeOfLastPlay;
    } lastPlayedLevels[5];
    u8 totalMedals;
    u8 unused;
    u16 currentFlow;
    u16 timeOfLastCafeVisit;
};


// [0x030055A0] Play Session
extern struct PlaySessionInfo gSessionInfo;


// DATA
extern struct Animation *cafe_cursor_option_anim[];
extern u8 cafe_barista_denied_levels[];
extern struct GraphicsTable cafe_gfx_table[];
extern struct CompressedData *cafe_buffered_textures[];
extern const char **cafe_random_conversation_pool[];
extern const char *cafe_dialogue_first_visit[];
extern const char *cafe_dialogue_come_back_later[];
extern const char *cafe_dialogue_keep_trying[];
extern const char *cafe_dialogue_shouts_praise[];
extern const char *cafe_dialogue_shouts_cheer[];
extern const char *cafe_dialogue_practicing_perfect[];
extern const char *cafe_dialogue_not_practicing_perfect[];
extern const char *cafe_dialogue_all_perfects_clear[];
extern const char *cafe_dialogue_extra_perfects_clear[];
extern const char *cafe_dialogue_all_perfects_clear_big[];


// FUNCTIONS
extern void cafe_session_init_level_playtime(struct LevelPlayActivity *activity);
extern void cafe_session_init_level(struct LevelPlayActivity *activity, s32 levelID);
extern struct LevelPlayActivity *cafe_session_alloc_level(s32 levelID);
extern struct LevelPlayActivity *cafe_session_get_level(s32 levelID);
extern void cafe_session_init(void);
extern void cafe_session_add_level(s32 levelID);
extern void cafe_session_remove_level(s32 levelID);
extern void cafe_session_add_perfect_level(s32 levelID);
extern void cafe_session_remove_old_levels(u32 totalPlayTime, u32 inactivityThreshold);
extern void cafe_session_init_indexes(void);
extern void cafe_session_init_playtime(void);
extern void cafe_session_remove_perfect_levels(void);

extern void cafe_init_dialogue(void);
extern void cafe_start_dialogue_inputs(void);
extern void cafe_update_dialogue_inputs(void);
extern u32  barista_can_clear_level(s32 levelID);
extern void cafe_print_dialogue(void);
extern s32  cafe_get_bg_event(void);
extern void cafe_text_printer_show_box(void);
extern void cafe_text_printer_hide_box(void);
extern void cafe_init_text_printer(void);
extern s32  cafe_get_dialogue_hold_time(void);
extern void cafe_clear_dialogue(void);

extern void cafe_scene_init_memory(void);
extern void cafe_scene_init_gfx3(void);
extern void cafe_scene_init_gfx2(void);
extern void cafe_scene_init_gfx1(void);
extern void cafe_scene_start(void *sVar, s32 dArg);
extern void cafe_scene_paused(void *sVar, s32 dArg);
extern void cafe_scene_update(void *sVar, s32 dArg);
extern u32  cafe_scene_inputs_enabled(void);
extern void cafe_load_bg_event_map(struct CompressedData *map);
extern void cafe_scene_stop(void *sVar, s32 dArg);
