#pragma once

#include "global.h"
#include "scenes.h"


// VALUES
enum GameSelectStatesEnum {
    /* 00 */ GS_STATE_LOADING,
    /* 01 */ GS_STATE_UNLOCKING_LEVELS,
    /* 02 */ GS_STATE_MAIN,
    /* 03 */ GS_STATE_DISPLAYING_CAMPAIGN
};

enum CampaignBordersEnum {
    /* 00 */ CAMPAIGN_BORDER_0_FLOWERS,
    /* 01 */ CAMPAIGN_BORDER_3_FLOWERS,
    /* 02 */ CAMPAIGN_BORDER_6_FLOWERS
};

#define MAX_PERFECT_ATTEMPTS 3

#define GS_GRID_WIDTH 15u
#define GS_GRID_HEIGHT 12u

#define LEVEL_EVENT_TARGET_ON_SHOW   (1 << 0)
#define LEVEL_EVENT_MOVE_CURSOR      (1 << 1)
#define LEVEL_EVENT_CLEAR_BY_DEFAULT (1 << 2)
#define LEVEL_EVENT_DELAY_CLEAR      (1 << 3)
#define LEVEL_EVENT_DELAY_OPEN       (1 << 4)
#define LEVEL_EVENT_DELAY_SHOW       (1 << 5)
#define LEVEL_EVENT_TARGET_ON_OPEN   (1 << 6)

#define LEVEL_ICON_ANIM_STOP -2
#define LEVEL_ICON_ANIM_LOOP -1

enum LevelIconOverlaysEnum {
    /* 00 */ LEVEL_ICON_OVERLAY_BLANK,
    /* 01 */ LEVEL_ICON_OVERLAY_CLOSED,
    /* 02 */ LEVEL_ICON_OVERLAY_UNCLEARED,
    /* 03 */ LEVEL_ICON_OVERLAY_CLEARED,
    /* 04 */ LEVEL_ICON_OVERLAY_MEDAL,
    /* 05 */ LEVEL_ICON_OVERLAY_REMIX_CLOSED,
    /* 06 */ LEVEL_ICON_OVERLAY_REMIX_UNCLEARED,
    /* 07 */ LEVEL_ICON_OVERLAY_BONUS,
    /* 08 */ LEVEL_ICON_OVERLAY_PERFECT
};


// MACROS
#define gGameSelect ((struct GameSelectSceneData *)gCurrentSceneData)


// TYPES
struct GameSelectSceneData {
    /* [0x000] Scene */
    u8 sceneState;
    u32 inputsEnabled;
    u32 loadingSceneGfx:1;
    u32 hideStageTitle:1;
    u32 unused8:30;

    /* [0x00C] Cursor */
    s16 selectionBorderSprite;
    s16 cursorSprite;
    s8 cursorX, cursorY; // { 1..9 }, { 6..11 }

    /* [0x012] Stage Title Pane */
    s16 stageTitleText;
    s16 stageTitlePane;
    s16 stageTitleY;
    u16 unk18;
    u16 stageTitlePersistTime;

    /* [0x01C] BG Color Controls */
    struct ColorChanger {
        u8 state;
        u8 r1, g1, b1;
        u8 r2, g2, b2;
        u16 timer;
        u16 target;
    } colorChangers[2];

    /* [0x034] Level Info Pane */
    s16 infoPaneName;
    struct TextPrinter *infoPaneDesc;
    s16 infoPaneRank;
    u8 infoPaneIsClear;
    u8 infoPaneLevelState;
    u8 infoPaneDelay;
    u8 infoPaneTask;
    struct LevelData *infoPaneLevelData;
    s16 infoPaneLevelID;
    u16 unused4A;
    u16 unused4C;

    /* [0x04E] BG Motion (Grid Pane) */
    u8 gridPaneIsMoving;
    s16 gridPaneX1, gridPaneY1;
    s16 gridPaneX2, gridPaneY2;
    u16 gridPaneMotionTime;
    u16 gridPaneMotionDecay;

    /* [0x05C] BG Motion (Info Pane) */
    u8 infoPaneIsMoving;
    s16 infoPaneX1, infoPaneY1;
    s16 infoPaneX2, infoPaneY2;
    u16 infoPaneMotionTime;
    u16 infoPaneMotionDecay;

    /* [0x06A] Squares */
    s16 squareSprites[50];
    struct Vector2 squareVectors[50];
    struct NewIconSquare {
        u8 active;
        s16 sprite;
        s16 xIn, yIn;
        s16 x1, y1;
        s16 x2, y2;
        s16 progress;
        void (*onFinish)();
        s32 onFinishArg;
        u16 delay;
    } newIconSquares[10];

    /* [0x2D8] Level Events */
    u8 runningLevelEvents;
    u8 levelEventTimer;
    u8 totalLevelEventsQueued;
    u8 levelEventDequeueID;
    u8 levelEventEnqueueID;
    struct QueuedLevelEvent {
        s8 x, y;
        s8 state;
    } levelEventsQueue[16];
    u8 levelEventPending;
    const s8 *levelEventTargets;
    s8 levelEventTargetX;
    s8 levelEventTargetY;

    /* [0x32C] Flow Pane */
    struct FlowDisplay {
        s16 title;
        s16 digits[3];
        s16 arrow;
        u8 state;
        u16 timer;
        u16 counter;
        u16 currentScore;
        u16 previousScore;
    } flowDisplay;

    /* [0x340] Campaign Notice */
    struct CampaignNotice {
        u8 hasNewCampaign;
        s8 id;
        s16 x, y;
        s16 borderSprite;
        u16 textAdvDelay;
        u16 noticeDelay;
        struct TextPrinter *printer;
        s16 textAdvSprite;
        char text[0x100];
        u8 unused452;
        u8 totalAvailable;
        u8 indexes[48];
    } campaignNotice;
    u8 unused484[100];

    /* [0x4E8] Medal Pane */
    s16 medalPaneTitle;
    s16 medalPaneDigit1;
    s16 medalPaneDigit2;
    u16 medalPaneFlickerTimer;

#if REV < 1
    /* [0x4F0] Unused Forced Level Unlock */
    u8 unused4F0;
    s8 manualUnlockX;
    s8 manualUnlockY;
    u8 manualUnlockEnabled;
#endif

    /* [0x4F4] Barista Level Unlock */
    u8 baristaLevelEventPending;
    s8 baristaLevelEventX;
    s8 baristaLevelEventY;
    u16 baristaLevelEventTimer;

    /* [0x4F8] Perfect Rank Icon */
    s16 perfectClearedSprite;
    s16 noPracticeSprite;
    s16 tempoUpSprite;
    s32 modelCornerHidden;
};

struct CampaignGiftData {
    s8 x, y;
    u8 type;
    u32 id;
};

enum LevelDataFlags {
    LEVEL_DATA_FLAG_NONE = 0,
    LEVEL_DATA_FLAG_IS_EXTRA = (1 << 0),
    LEVEL_DATA_FLAG_NO_PRACTICE = (1 << 1),
};

struct LevelData {
    struct Scene *scene;
    const char *name;
    const char *description;
    u16 icon;
    u8 type;
    const struct GraphicsTable **epilogueGfx;
    const char *epilogueText[3];
    u8 flags;
};

struct GameSelectGridEntry {
    s16 id;
    const s8 *displayReq;
    const s8 *unlockReq;
    const s8 *targets;
    u8 flags;
    u8 orderIndex;
};

struct GameSelectOverlay {
    u8 width, height;
    const u8 *texture;
    const s8 *animData;
};

struct LevelIconAnimatorTask {
    const u8 *texture;
    u16 *tilesetBase;
    const s8 *frameData;
    u16 size;
    u8 currentFrame;
    u8 timeUntilNext;
};


// DATA
extern struct CampaignGiftData campaign_gifts_table[];
extern struct Animation *campaign_icon_borders[];
extern struct LevelData level_data_table[];
extern const u8 *level_icon_texture_table[];
extern struct GameSelectGridEntry game_select_grid_data[];
extern u8 level_icon_palette_table[];
extern struct GraphicsTable game_select_gfx_table[];
extern struct CompressedData *game_select_buffered_textures[];
extern struct Animation *game_select_stage_title_anim[];
extern const char *game_select_rank_text[];
extern u8 game_select_rank_palette[];
extern struct GameSelectOverlay *level_icon_overlay_data[];
extern u8 *level_icon_overlays_map[];
extern struct TaskMethods level_icon_overlay_animator_task;


// FUNCTIONS
extern void disable_game_select_2_bgm(void);
extern void enable_game_select_2_bgm(void);
extern void play_game_select_bgm(void);

extern void clear_current_campaign(void);
extern void set_current_campaign(s32 id);
extern s32 get_current_campaign(void);
extern void update_plays_until_next_campaign(void);
extern void get_all_uncleared_campaigns(void);
extern void start_new_campaign(void);
extern void activate_campaign_notice(void);
extern void init_campaign_notice(void);
extern const char *get_campaign_gift_title(s32 id, s32 shortenSongTitle);
extern void start_campaign_notice(s32 id);
extern s32 start_random_campaign_notice(void);
extern void update_campaign_notice(void);
extern void display_campaign_icon_border(s32 x, s32 y);
extern void hide_campaign_icon_border(void);
extern const char *get_level_name_from_campaign(s32 id);
extern s32 get_campaign_from_grid_xy(s32 x, s32 y);
extern s32 get_campaign_from_level_id(s32 id);

extern s32 get_level_id_from_grid_xy(s32 x, s32 y);
extern struct LevelData *get_level_data_from_id(s32 id);
extern s32 get_level_state_from_id(s32 id);
extern s32 get_level_state_with_perfect_from_id(s32 id);
extern struct LevelData *get_level_data_from_grid_xy(s32 x, s32 y);
extern s32 get_level_state_from_grid_xy(s32 x, s32 y);
extern s32 get_level_state_with_perfect_from_grid_xy(s32 x, s32 y);
extern void get_grid_xy_from_level_id(s32 id, s32 *xReq, s32 *yReq);
extern void init_game_select_grid_gfx(void);
extern void get_pixel_xy_from_grid_xy(s32 x, s32 y, s16 *xReq, s16 *yReq);
extern void save_level_state_from_grid_xy(s32 x, s32 y, s32 state);

extern void game_select_init_color_mod(void);
extern void game_select_update_color_mod(struct ColorChanger *changer);
extern void game_select_update_bg_colors(void);

extern void game_select_scene_init_memory(void);
extern void game_select_scene_init_gfx4(void);
extern void game_select_scene_init_gfx3(void);
extern void game_select_scene_init_gfx2(void);
extern void game_select_scene_init_gfx1(void);
extern void game_select_scene_start(void *sVar, s32 dArg);
extern void game_select_disable_credits_after_epilogue(void);
extern u32 game_select_roll_credits_after_epilogue(void);
extern void game_select_scene_paused(void *sVar, s32 dArg);
extern void game_select_scroll_grid_pane(s32 x, s32 y, s24_8 rate);
extern void game_select_scroll_info_pane(s32 x, s32 y, s24_8 rate);
extern void game_select_update_bg_scroll(void);
extern void game_select_set_cursor_border_z(void);
extern void game_select_move_cursor_to_grid_xy(s32 x, s32 y);
extern u32 game_select_get_next_valid_xy(s32 *xReq, s32 *yReq, s32 dx, s32 dy);
extern void game_select_read_dpad_inputs(void);
extern void game_select_read_inputs_sub1(void);
extern void game_select_read_inputs_sub2(void);
extern void game_select_read_inputs(void);
extern void game_select_set_info_pane_to_cursor_target(void);
extern void game_select_update_stage_title_pos(void);
extern void game_select_set_stage_title(s32 x);
extern void game_select_update_stage_title(void);
extern void game_select_link_sprite_xy_to_bg(s16 sprite);
extern void game_select_scene_update(void *sVar, s32 dArg);
extern u32 game_select_scene_inputs_enabled(void);
extern void game_select_set_unused_static_var(u32 arg0, u32 arg1);
extern u32 game_select_get_total_levels(void);
extern const char *game_select_get_level_name(s32 id);
extern void game_select_enqueue_level_event(s32 x, s32 y, s32 state);
extern void game_select_dequeue_level_event(s32 *xReq, s32 *yReq, s32 *stateReq);
extern u32 game_select_check_level_event_req(s32 x, s32 y, s32 state);
extern void game_select_set_icon_map_after_level_event(s32 x, s32 y);
extern void enqueue_level_event_after_reveal(u32 args);
extern u32 game_select_set_level_event_target(s32 x, s32 y, u32 moveCursor, s24_8 scrollRate);
extern u32 game_select_process_level_event_targets(const s8 *data);
extern u32 game_select_process_level_events(void);
extern void game_select_update_level_unlocks(void);
extern void game_select_start_level_events(u32 delay);
extern void game_select_update_level_events(void);
extern void game_select_set_medal_count(u32 total);
extern void game_select_init_medal_pane(void);
extern u32 game_select_update_medal_pane_flicker(void);
extern void game_select_update_medal_pane(void);
extern void game_select_refresh_medal_count(u32 flickerDuration);
extern void game_select_init_info_pane(void);
extern void game_select_delete_info_pane_sprite(s16 *ptr);
extern void game_select_clear_info_pane(void);
extern void game_select_print_level_name(struct LevelData *levelData);
extern void game_select_print_level_desc(struct LevelData *levelData);
extern void game_select_print_level_rank(s32 levelState);
extern void game_select_process_info_pane(void);
extern void game_select_set_info_pane(s32 id, s32 state, s32 delay);
extern void game_select_update_info_pane(void);
extern u32 game_select_calculate_flow(u32 *modifierReq, u32 *averageReq);
extern u32 game_select_calculate_flow_old(void);
extern u32 game_select_update_scores(void);
extern void game_select_init_flow_pane(void);
extern void game_select_update_flow_pane(void);
extern void game_select_scene_stop(void *sVar, s32 dArg);

extern void game_select_init_stub(void);
extern void game_select_init_icon_overlays(void);
extern void game_select_update_stub(void);
extern struct LevelIconAnimatorTask *game_select_init_icon_animator(struct LevelIconAnimatorTask *inputs);
extern u32 game_select_update_icon_animator(struct LevelIconAnimatorTask *task);
extern s32 game_select_start_new_icon_animator(u16 memID, const void *texture, u16 *tilesetBase, u32 size, const s8 *frameData);
extern s32 game_select_animate_icon(struct GameSelectOverlay *overlay, u32 tilesetNum, u32 baseTileNum);
extern void game_select_print_icon_map(u32 baseMap, u32 mapSize, u32 tileX, u32 tileY, u32 width, u32 height, u32 tilesPerRow, u32 tileNum, u32 palette);
extern void game_select_print_icon_maps(u32 baseMap, u32 mapSize, u32 tileX, u32 tileY, u32 width, u32 height, u32 tileNum, u32 palette);
extern void game_select_print_icon_texture(const void *texture, u32 tileset, u32 tileNum);
extern void game_select_init_squares(void);
extern void game_select_update_bg_squares_motion(s32 dx, s32 dy);
extern void game_select_spawn_icon_square(s16 x, s16 y, void *onFinish, s32 onFinishArg, u32 delay);
extern void game_select_update_icon_square(struct NewIconSquare *shadow);
extern void game_select_update_icon_squares(void);
extern u32 game_select_check_for_icon_squares(void);
extern void game_select_update_bg_squares(s32 dx, s32 dy);
extern void game_select_clear_bg_tiles(u32 baseMap, u32 mapSize, u32 tileX, u32 tileY, u32 width, u32 height, u32 tileNum, u32 palette);