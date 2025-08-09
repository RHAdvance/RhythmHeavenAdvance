#include "global.h"
#include "game_select.h"
#include "graphics/game_select/game_select_graphics.h"

#include "levels.h"
#include "src/scenes/reading.h"
#include "src/scenes/studio.h"


/* GAME SELECT SCENE */


#define COLOR_MOD_MAX_WAIT_TIME 60
#define COLOR_MOD_INTERP_TIME 96

enum ColorChangerStatesEnum {
    COLOR_CHANGER_STATE_WAITING,
    COLOR_CHANGER_STATE_INTERPOLATING
};

#define STAGE_PANE_Y_HIDDEN (SCREEN_HEIGHT + 40)
#define STAGE_PANE_Y_VISIBLE (SCREEN_HEIGHT - 20)
#define STAGE_PANE_SPEED 9

enum InfoPaneStatesEnum {
    /* 00 */ INFO_PANE_TASK_NONE,
    /* 01 */ INFO_PANE_TASK_DELAY,
    /* 02 */ INFO_PANE_TASK_PRINT_NAME,
    /* 03 */ INFO_PANE_TASK_PRINT_RANK,
    /* 04 */ INFO_PANE_TASK_PRINT_DESC,
    /* 05 */ INFO_PANE_TASK_RENDER
};

enum FlowPaneStatesEnum {
    /* 00 */ FLOW_PANE_TASK_NONE,
    /* 01 */ FLOW_PANE_TASK_WAIT,
    /* 02 */ FLOW_PANE_TASK_ROLL,
    /* 03 */ FLOW_PANE_TASK_FLICKER
};


static u8 sPlayAltBGM; // Play "Game Select 2" music
static u16 D_0300131e_padding; // unused
static s8 sCurrentCampaign; // Current Perfect Campaign ID
static u16 D_03001322_padding; // unused
static u8 sPlayCreditsAfterEpilogue; // Currently playing through Remix 6 for the first time.
extern u8 sReplayingCampaign;


extern u32 D_03005590; // Unused
extern u32 D_030055d4; // Unused


#define LEVEL_STATE_PERFECT 6 // New state for perfected levels


// Clear sPlayAltBGM
void disable_game_select_2_bgm(void) {
    sPlayAltBGM = FALSE;
}


// Set sPlayAltBGM
void enable_game_select_2_bgm(void) {
    sPlayAltBGM = TRUE;
}


// Play Game Select Music
void play_game_select_bgm(void) {
    if (sPlayAltBGM && !CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_USE_ALT_GAME_SELECT_MUSIC)) {
        set_beatscript_tempo(105);
        scene_set_music(&s_shibafu2_bgm_seqData);
        sPlayAltBGM = FALSE;
    } else {
        set_beatscript_tempo(152);
        scene_set_music(&s_menu_bgm_seqData);
    }
}


// Clear Current Perfect Campaign
void clear_current_campaign(void) {
    sCurrentCampaign = CAMPAIGN_NULL;
}


// Set Current Perfect Campaign
void set_current_campaign(s32 id) {
    sCurrentCampaign = id;
}


// Get Current Perfect Campaign
s32 get_current_campaign(void) {
    return sCurrentCampaign;
}


// Decrement Plays Until Next Perfect Campaign
void update_plays_until_next_campaign(void) {
    if ((D_030046a8->data.campaignState == CAMPAIGN_STATE_AVAILABLE) && (get_level_state_from_id(LEVEL_REMIX_1) >= LEVEL_STATE_CLEARED)) {
        if (D_030046a8->data.playsUntilNextCampaign > 0) {
            D_030046a8->data.playsUntilNextCampaign--;
        }
    }
}


// Get Available Perfect Campaigns
void get_all_uncleared_campaigns(void) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;
    struct CampaignGiftData *gift = campaign_gifts_table;
    u32 i;

    notice->totalAvailable = 0;

    for (i = 0; i < ALL_PERFECT_CAMPAIGNS; i++) {
        if (!get_campaign_cleared(&D_030046a8->data, i)) {
            if (get_level_state_from_grid_xy(gift->x, gift->y) == LEVEL_STATE_HAS_MEDAL) {
                notice->indexes[notice->totalAvailable] = i;
                notice->totalAvailable++;
            }
        }
        gift++;
    }
}


// Start New Perfect Campaign
void start_new_campaign(void) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;
    u32 playsUntilNewCampaign;

    get_all_uncleared_campaigns();

    if (notice->totalAvailable == 0) {
        return;
    }

    playsUntilNewCampaign = 0;
    if (D_030046a8->data.totalMedals < MAX_MEDALS) {
        playsUntilNewCampaign = 1;
    }
    if (D_030046a8->data.totalMedals < (MAX_MEDALS - 3)) {
        playsUntilNewCampaign = agb_random(2) + 2;
    }
    if (D_030046a8->data.totalMedals < (MAX_MEDALS - 18)) {
        playsUntilNewCampaign = agb_random(4) + 3;
    }

    D_030046a8->data.campaignState = CAMPAIGN_STATE_AVAILABLE;
    D_030046a8->data.campaignAttemptsLeft = MAX_PERFECT_ATTEMPTS;
    D_030046a8->data.playsUntilNextCampaign = playsUntilNewCampaign;
    D_030046a8->data.currentCampaign = notice->indexes[agb_random(notice->totalAvailable)];
    D_030046a8->data.unk26A = 0;
    D_030046a8->data.unk291 = 0;
}


// Mark Perfect Campaign As Ready to Start
void activate_campaign_notice(void) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;

    if (D_030046a8->data.playsUntilNextCampaign > 0) {
        return;
    }

    D_030046a8->data.campaignState = CAMPAIGN_STATE_ACTIVE;
    notice->id = D_030046a8->data.currentCampaign;
    notice->x = campaign_gifts_table[notice->id].x;
    notice->y = campaign_gifts_table[notice->id].y;
    notice->hasNewCampaign = TRUE;
}


// Init. Perfect Campaign Notice
void init_campaign_notice(void) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;
    struct Vector2 *vector = &D_03004b10.BG_OFS[BG_LAYER_1];

    notice->borderSprite = sprite_create(gSpriteHandler, anim_game_select_border_perfect3, 0, 48, 72, 0x8878, 1, 0, 0x8000);
    game_select_link_sprite_xy_to_bg(notice->borderSprite);
    notice->textAdvSprite = sprite_create(gSpriteHandler, anim_game_select_text_button, 0, 64, 64, 0x800, 1, 0, 0x8000);
    sprite_set_origin_x_y(gSpriteHandler, notice->textAdvSprite, &vector->x, &vector->y);

    notice->printer = text_printer_create_new(get_current_mem_id(), 5, 120, 26);
    text_printer_set_x_y(notice->printer, 104, 308);
    text_printer_set_layer(notice->printer, 0x800);
    text_printer_set_colors(notice->printer, 0);
    text_printer_set_palette(notice->printer, 1);
    text_printer_set_line_spacing(notice->printer, 16);
    text_printer_center_by_content(notice->printer, 1);
    text_printer_set_x_y_controller(notice->printer, &vector->x, &vector->y);

    notice->hasNewCampaign = FALSE;
    notice->id = CAMPAIGN_NULL;

    switch (D_030046a8->data.campaignState) {
        case CAMPAIGN_STATE_INACTIVE:
            start_new_campaign();
            if (D_030046a8->data.campaignState == CAMPAIGN_STATE_AVAILABLE) {
                activate_campaign_notice();
            }
            break;

        case CAMPAIGN_STATE_AVAILABLE:
            activate_campaign_notice();
            break;

        case CAMPAIGN_STATE_ACTIVE:
            if ((D_030046a8->data.campaignAttemptsLeft > 0)
             && (D_030046a8->data.unk26A < 3)
             && (!get_campaign_cleared(&D_030046a8->data, D_030046a8->data.currentCampaign))) {
                notice->id = D_030046a8->data.currentCampaign;
                notice->x = campaign_gifts_table[notice->id].x;
                notice->y = campaign_gifts_table[notice->id].y;
                display_campaign_icon_border(notice->x, notice->y);
            } else {
                D_030046a8->data.campaignState = CAMPAIGN_STATE_INACTIVE;
                start_new_campaign();
                if (D_030046a8->data.campaignState == CAMPAIGN_STATE_AVAILABLE) {
                    activate_campaign_notice();
                }
                break;
            }
    }

    clear_current_campaign();
}


// Get Perfect Campaign Reward Text
const char *get_campaign_gift_title(s32 id, s32 shortenSongTitle) {
    u32 giftID, giftType;

    if (id < 0) {
        return "";
    }

    giftType = campaign_gifts_table[id].type;
    giftID = campaign_gifts_table[id].id;

    switch (giftType) {
        case CAMPAIGN_GIFT_SONG:
            if (shortenSongTitle) {
                return studio_song_table[giftID].shortTitle;
            } else {
                return studio_song_table[giftID].fullTitle;
            }

        case CAMPAIGN_GIFT_DRUM_KIT:
            return studio_drum_kit_names[giftID];

        case CAMPAIGN_GIFT_READING_MATERIAL:
            return reading_material_table[giftID].title;

        case CAMPAIGN_GIFT_NEW_GAME:
            return "New Game"; // New Game
    }
}


// Start Perfect Campaign Notice
void start_campaign_notice(s32 id) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;
    u32 isSpecialSong = FALSE;
    u32 isStandardSong = FALSE;
    u32 giftType = campaign_gifts_table[id].type;
    u32 giftID = campaign_gifts_table[id].id;
    struct LevelData *level;
    char *string;

    if (giftType == CAMPAIGN_GIFT_SONG) {
        isStandardSong = TRUE;
        switch (giftID) {
            case STUDIO_SONG_HONEY_SWEET_ANGEL:
            case STUDIO_SONG_WISH:
                isStandardSong = FALSE;
                isSpecialSong = TRUE;
                break;
        }
    }

    notice->x = campaign_gifts_table[id].x;
    notice->y = campaign_gifts_table[id].y;
    level = get_level_data_from_grid_xy(notice->x, notice->y);
    string = notice->text;
    memcpy(string, "\001C" "If you get a Perfect in\n", 45); // [Right now]
    strcat(string, level->name); // "<game_name>"
    if(level->flags & LEVEL_DATA_FLAG_IS_EXTRA) {
        strcat(string, " EX!"); // Extra
    }
    strcat(string, "\nright now, you'll earn:\n"); // Get a perfect on this
    strcat(string, ""); // "
    strcat(string, get_campaign_gift_title(id, FALSE)); // "<gift>"
    strcat(string, "\n"); // "
    if (isStandardSong) {
        strcat(string, "as a song."); // 's song
    }
    if (giftType == CAMPAIGN_GIFT_DRUM_KIT || giftType == CAMPAIGN_GIFT_READING_MATERIAL) {
        strcat(string, "as a bonus."); // received as a present!!
    }
    text_printer_set_string(notice->printer, string);

    sprite_set_visible(gSpriteHandler, gGameSelect->selectionBorderSprite, FALSE);
    notice->textAdvDelay = 10;
    notice->noticeDelay = 60;
    scene_interpolate_music_volume(100, ticks_to_frames(0x18));
    gGameSelect->sceneState = GS_STATE_DISPLAYING_CAMPAIGN;
}


// Start a Random Available Perfect Campaign
s32 start_random_campaign_notice(void) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;
    s32 id;

    if (notice->totalAvailable == 0) {
        return CAMPAIGN_NULL;
    }

    id = notice->indexes[agb_random(notice->totalAvailable)];
    start_campaign_notice(id);

    return id;
}


// Update Perfect Campaign Notice
void update_campaign_notice(void) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;
    u32 denyInputs = FALSE;
    s16 x, y;
    s16 textX, textY;

    if (notice->noticeDelay > 0) {
        if (notice->noticeDelay == 30) {
            play_sound(&s_f_campaign_notice_seqData);
        }
        if (--notice->noticeDelay == 0) {
            display_campaign_icon_border(notice->x, notice->y);
            get_pixel_xy_from_grid_xy(notice->x, notice->y, &x, &y);
            game_select_scroll_grid_pane(x, y, 240);
            game_select_scroll_info_pane(0, 256, 240);
            gGameSelect->hideStageTitle = TRUE;
        }
        denyInputs = TRUE;
    }

    if (gGameSelect->gridPaneIsMoving) {
        denyInputs = TRUE;
    }

    if (gGameSelect->infoPaneIsMoving) {
        denyInputs = TRUE;
    }

    if (text_printer_is_busy(notice->printer)) {
        denyInputs = TRUE;
    }

    if (!denyInputs) {
        if (notice->textAdvDelay > 0) {
            denyInputs = TRUE;
            if (--notice->textAdvDelay == 0) {
                text_printer_get_x_y(notice->printer, &textX, &textY);
                sprite_set_x_y(gSpriteHandler, notice->textAdvSprite, textX, textY);
                sprite_set_visible(gSpriteHandler, notice->textAdvSprite, TRUE);
            }
        }
        if (!denyInputs && (D_03004afc & A_BUTTON)) {
            get_pixel_xy_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY, &x, &y);
            game_select_scroll_grid_pane(x, y, 220);
            game_select_scroll_info_pane(0, 0, 220);
            sprite_set_visible(gSpriteHandler, notice->textAdvSprite, FALSE);
            sprite_set_visible(gSpriteHandler, gGameSelect->selectionBorderSprite, TRUE);
            gGameSelect->hideStageTitle = FALSE;
            play_sound(&s_menu_kettei2_seqData);
            scene_interpolate_music_volume(INT_TO_FIXED(1.0), ticks_to_frames(0x18));
            gGameSelect->sceneState = GS_STATE_MAIN;
        }
    }

    text_printer_update(notice->printer);
}


// Display Perfect Campaign Border
void display_campaign_icon_border(s32 x, s32 y) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;
    s16 screenX, screenY;

    get_pixel_xy_from_grid_xy(x, y, &screenX, &screenY);
    screenX += 47;
    screenY += 68;
    sprite_set_anim(gSpriteHandler, notice->borderSprite, campaign_icon_borders[clamp_int32(D_030046a8->data.campaignAttemptsLeft, 1, MAX_PERFECT_ATTEMPTS) - 1], 0, 1, 0, 0);
    sprite_set_x_y(gSpriteHandler, notice->borderSprite, screenX, screenY);
    sprite_set_visible(gSpriteHandler, notice->borderSprite, TRUE);
}


// Hide Perfect Campaign Border
void hide_campaign_icon_border(void) {
    struct CampaignNotice *notice = &gGameSelect->campaignNotice;

    sprite_set_visible(gSpriteHandler, notice->borderSprite, FALSE);
}


// Get Level Name from Campaign ID
const char *get_level_name_from_campaign(s32 id) {
    return get_level_data_from_grid_xy(campaign_gifts_table[id].x, campaign_gifts_table[id].y)->name;
}


// Get Campaign from Grid Position
s32 get_campaign_from_grid_xy(s32 x, s32 y) {
    s32 i;
    struct CampaignGiftData *campaign = campaign_gifts_table;

    for (i = 0; i < ALL_PERFECT_CAMPAIGNS; i++, campaign++) {
        if ((campaign->x == x) && (campaign->y == y)) {
            return i;
        }
    }

    return CAMPAIGN_NULL;
}


// Get Campaign ID from Level ID
s32 get_campaign_from_level_id(s32 id) {
    s32 x, y;

    get_grid_xy_from_level_id(id, &x, &y);
    return get_campaign_from_grid_xy(x, y);
}


// Get Level ID from Grid Position
s32 get_level_id_from_grid_xy(s32 x, s32 y) {
    if ((x < GS_GRID_WIDTH) && (y < GS_GRID_HEIGHT)) {
        return game_select_grid_data[x + (y * GS_GRID_WIDTH)].id;
    }

    return LEVEL_NULL;
}


// Get Level Data from Level ID
struct LevelData *get_level_data_from_id(s32 id) {
    if (id < 0) {
        return NULL;
    }

    return &level_data_table[id];
}


// Get Level Completion State from Level ID
s32 get_level_state_from_id(s32 id) {
    struct TengokuSaveData *saveData = &D_030046a8->data;

    if (id < 0) {
        return LEVEL_STATE_NULL;
    }

    return get_level_state(saveData, id);
}


// Get Level Completion State from Level ID (with Perfect Detection)
s32 get_level_state_with_perfect_from_id(s32 id) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    s32 levelState;

    if (id < 0) {
        return LEVEL_STATE_NULL;
    }

    levelState = get_level_state(saveData, id);

    // Check if the game has been perfected (same logic as rank printing)
    if (get_campaign_cleared(saveData, get_campaign_from_level_id(id))) {
        levelState = LEVEL_STATE_PERFECT;
    }

    return levelState;
}


// Get Level Data from Grid Position
struct LevelData *get_level_data_from_grid_xy(s32 x, s32 y) {
    return get_level_data_from_id(get_level_id_from_grid_xy(x, y));
}


// Get Level Completion State from Grid Position
s32 get_level_state_from_grid_xy(s32 x, s32 y) {
    return get_level_state_from_id(get_level_id_from_grid_xy(x, y));
}


// Get Level Completion State from Grid Position (with Perfect Detection)
s32 get_level_state_with_perfect_from_grid_xy(s32 x, s32 y) {
    return get_level_state_with_perfect_from_id(get_level_id_from_grid_xy(x, y));
}


// Get Grid Position from Level ID
void get_grid_xy_from_level_id(s32 id, s32 *xReq, s32 *yReq) {
    s32 x, y;

    if (id < 0) {
        *xReq = -1;
        *yReq = -1;
        return;
    }

    for (y = 0; y < GS_GRID_HEIGHT; y++) {
        for (x = 0; x < GS_GRID_WIDTH; x++) {
            if (game_select_grid_data[x + (y * GS_GRID_WIDTH)].id == id) {
                *xReq = x;
                *yReq = y;
                return;
            }
        }
    }
}


// Write Game Select Grid to VRAM
void init_game_select_grid_gfx(void) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    void *tileBase, *iconMapBase, *iconOverlayMapBase;
    u32 tileNum;
    u32 i, j;

    tileBase = BG_TILESET_BASE(0);
    dma3_fill(0, tileBase, 0x20, 0x20, 0x200);
    iconMapBase = BG_MAP_BASE(0xE000);
    dma3_fill(0, iconMapBase, 0x2000, 0x20, 0x200);
    iconOverlayMapBase = BG_MAP_BASE(0xC000);
    dma3_fill((0x0100 << 16) | 0x0100, iconOverlayMapBase, 0x2000, 0x20, 0x200);

    tileNum = 1;
    for (i = 0; i < ALL_LEVELS; i++) {
        game_select_print_icon_texture(level_icon_texture_table[i], 0, tileNum);
        tileNum += (3 * 3);
    }

    for (i = 0; i < GS_GRID_HEIGHT; i++) {
        for (j = 0; j < GS_GRID_WIDTH; j++) {
            struct LevelData *levelData;
            s32 levelID, levelState, levelType;
            u32 overlay, palette;

            levelID = game_select_grid_data[j + (i * GS_GRID_WIDTH)].id;

            if (levelID >= 0) {
                u32 tileX = 1 + (j * 5);
                u32 tileY = 4 + (i * 3);

                levelData = &level_data_table[levelID];
                levelType = levelData->type;
                // Only use perfect detection for actual playable levels (like medal system)
                if (levelType == LEVEL_TYPE_GAME || levelType == LEVEL_TYPE_REMIX) {
                    levelState = get_level_state_with_perfect_from_id(levelID);
                } else {
                    levelState = get_level_state_from_id(levelID);
                }
                overlay = level_icon_overlays_map[levelType][levelState];
                if (levelState != LEVEL_STATE_HIDDEN) {
                    tileNum = 1 + (levelData->icon * 3 * 3);
                    palette = level_icon_palette_table[levelData->icon];
                    game_select_print_icon_maps(28, 3, tileX, tileY, 3, 3, tileNum, palette);
                }
                tileNum = 1 + (overlay * 3 * 3) + 0x100;
                
                // Adjust position for perfect overlay (move right 1 tile)
                if (overlay == LEVEL_ICON_OVERLAY_PERFECT) {
                    game_select_print_icon_maps(24, 3, tileX + 1, tileY, 3, 3, tileNum, 8);
                } else {
                    game_select_print_icon_maps(24, 3, tileX, tileY, 3, 3, tileNum, 8);
                }
            }
        }
    }
}


// Get Screen Coordinates from Grid Position
void get_pixel_xy_from_grid_xy(s32 x, s32 y, s16 *xReq, s16 *yReq) {
    *xReq = (x * 40) - 39;
    *yReq = (y * 24) - 36;
}


// Set Level State by Grid Position
void save_level_state_from_grid_xy(s32 x, s32 y, s32 state) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    s32 id;

    if ((x < GS_GRID_WIDTH) && (y < GS_GRID_HEIGHT)) {
        id = game_select_grid_data[x + (y * GS_GRID_WIDTH)].id;

        if (id >= 0) {
            set_level_state(saveData, id, state);
        }
    }
}


// Init. Color Changers
void game_select_init_color_mod(void) {
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gGameSelect->colorChangers); i++) {
        struct ColorChanger *changer = &gGameSelect->colorChangers[i];

        changer->r1 = changer->g1 = changer->b1 = 31;
        changer->r2 = changer->g2 = changer->b2 = 31;
        changer->state = COLOR_CHANGER_STATE_WAITING;
        changer->timer = 1;
        changer->target = (i == 0) ? 0xFE : 0xFF;
    }
}


// Update Color Changer
void game_select_update_color_mod(struct ColorChanger *changer) {
    u32 r, g, b;

    switch (changer->state) {
        case COLOR_CHANGER_STATE_WAITING:
            if (--changer->timer == 0) {
                changer->state = COLOR_CHANGER_STATE_INTERPOLATING;
                changer->r1 = changer->r2;
                changer->g1 = changer->g2;
                changer->b1 = changer->b2;

                if (agb_random(2)) {
                    changer->r2 = agb_random(32);
                    changer->g2 = agb_random(32);
                    changer->b2 = agb_random(32);

                    if ((changer->r2 < 20) && (changer->g2 < 20) && (changer->b2 < 20)) {
                        u8 *darkest = &changer->r2;

                        if (changer->r2 > changer->g2) {
                            darkest = &changer->g2;
                        }
                        if (*darkest > changer->b2) {
                            darkest = &changer->b2;
                        }

                        *darkest = 31 - (*darkest / 4);
                    }
                } else {
                    changer->r2 = 31 * agb_random(2);
                    changer->g2 = 31 * agb_random(2);
                    changer->b2 = 31 * agb_random(2);
                }

                changer->timer = 0;
            }
            break;

        case COLOR_CHANGER_STATE_INTERPOLATING:
            changer->timer++;
            r = math_lerp(changer->r1, changer->r2, changer->timer, COLOR_MOD_INTERP_TIME);
            g = math_lerp(changer->g1, changer->g2, changer->timer, COLOR_MOD_INTERP_TIME);
            b = math_lerp(changer->b1, changer->b2, changer->timer, COLOR_MOD_INTERP_TIME);
            D_03004b10.bgPalette[0][changer->target] = ((r & 0x1F)) | ((g & 0x1F) << 5) | ((b & 0x1F) << 10);

            if (changer->timer >= COLOR_MOD_INTERP_TIME) {
                changer->timer = 1 + agb_random(COLOR_MOD_MAX_WAIT_TIME);
                changer->state = COLOR_CHANGER_STATE_WAITING;
            }
            break;
    }
}


// Update Color Changers
void game_select_update_bg_colors(void) {
    game_select_update_color_mod(&gGameSelect->colorChangers[0]);
    game_select_update_color_mod(&gGameSelect->colorChangers[1]);
}


// Scene Init. Static Variables
void game_select_scene_init_memory(void) {
    D_030055d4 = 0;
    D_03005590 = 0;
    sReplayingCampaign = FALSE; 
    clear_current_campaign();
    game_select_disable_credits_after_epilogue();
    disable_game_select_2_bgm();
}


// Scene Graphics Init. 4 (Colors & Level Icons)
void game_select_scene_init_gfx4(void) {
    func_0800c604(0);
    set_pause_beatscript_scene(FALSE);
    func_080041d0(0xFE, 0xFF, 0);
    func_0800425c(16, 144);
    init_game_select_grid_gfx();
    game_select_init_icon_overlays();
    gGameSelect->loadingSceneGfx = FALSE;
    game_select_set_stage_title(gGameSelect->cursorX);
}


// Scene Graphics Init. 3 (Buffered Textures)
void game_select_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), game_select_buffered_textures);
    run_func_after_task(task, game_select_scene_init_gfx4, 0);
}


// Scene Graphics Init. 2 (Graphics Table)
void game_select_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), game_select_gfx_table, 0x3000);
    run_func_after_task(task, game_select_scene_init_gfx3, 0);
}


// Scene Graphics Init. 1 (BG/OBJ Layers)
void game_select_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), game_select_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 2, 22, BGCNT_TILEMAP_SIZE(2) | BGCNT_PRIORITY(0));
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 2, 24, BGCNT_TILEMAP_SIZE(3) | BGCNT_PRIORITY(1));
    scene_set_bg_layer_display(BG_LAYER_3, TRUE, 0, 0, 0, 28, BGCNT_TILEMAP_SIZE(3) | BGCNT_PRIORITY(2));
}


// Scene Start
void game_select_scene_start(void *sVar, s32 dArg) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    s32 recentLevelState, previousLevelState;
    s16 bgOfsX, bgOfsY;
    s32 prevX, prevY;
    s32 i;

    // Init. Graphics
    gGameSelect->loadingSceneGfx = TRUE;
    func_08007324(FALSE);
    func_080073f0();
    game_select_scene_init_gfx1();
    game_select_init_color_mod();
    game_select_init_stub();

    // Init. Cursor
    gGameSelect->cursorX = D_030046a8->data.gsCursorX;
    gGameSelect->cursorY = D_030046a8->data.gsCursorY;
    get_pixel_xy_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY, &bgOfsX, &bgOfsY);
    scene_set_bg_layer_pos(BG_LAYER_3, bgOfsX, bgOfsY);
    scene_set_bg_layer_pos(BG_LAYER_2, bgOfsX, bgOfsY);
    gGameSelect->selectionBorderSprite = sprite_create(gSpriteHandler, anim_game_select_border_target, 0, 48, 72, 0x4800, 1, 0, 0);
    gGameSelect->cursorSprite = sprite_create(gSpriteHandler, anim_game_select_cursor, 0, 64, 64, 0x47FF, 1, 0, 0);
    game_select_link_sprite_xy_to_bg(gGameSelect->selectionBorderSprite);
    game_select_link_sprite_xy_to_bg(gGameSelect->cursorSprite);
    game_select_move_cursor_to_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY);

    // Init. BG Motion
    gGameSelect->gridPaneIsMoving = FALSE;
    gGameSelect->gridPaneX1 = gGameSelect->gridPaneX2 = bgOfsX;
    gGameSelect->gridPaneY1 = gGameSelect->gridPaneY2 = bgOfsY;
    gGameSelect->infoPaneIsMoving = FALSE;
    gGameSelect->infoPaneX1 = gGameSelect->infoPaneX2 = 0;
    gGameSelect->infoPaneY1 = gGameSelect->infoPaneY2 = 0;

    // Init. Stage Title Pane
    gGameSelect->stageTitleText = sprite_create(gSpriteHandler, anim_game_select_stage1, 0x7F, 60, 140, 0x479C, 1, 0x7F, 0);
    gGameSelect->stageTitlePane = sprite_create_w_attr(gSpriteHandler, anim_game_select_stage_box, 0, 60, 140, 0x479D, 0, 0, 0, 0);
    gGameSelect->stageTitleY = STAGE_PANE_Y_VISIBLE;
    gGameSelect->unk18 = 0;
    gGameSelect->hideStageTitle = FALSE;
    gGameSelect->stageTitlePersistTime = 0;

    // Init. Various
    init_campaign_notice();
    game_select_init_medal_pane();
    game_select_init_squares();
    gGameSelect->inputsEnabled = FALSE;
    game_select_init_info_pane();
    game_select_set_info_pane_to_cursor_target();
    game_select_init_flow_pane();

    // Init. Events
    gGameSelect->totalLevelEventsQueued = 0;
    gGameSelect->levelEventDequeueID = 0;
    gGameSelect->levelEventEnqueueID = 0;
    gGameSelect->levelEventPending = FALSE;
    prevX = saveData->recentLevelX;
    prevY = saveData->recentLevelY;
    recentLevelState = saveData->recentLevelState;
    previousLevelState = get_level_state_from_grid_xy(prevX, prevY);
    gGameSelect->baristaLevelEventPending = FALSE;
    gGameSelect->baristaLevelEventTimer = 0;
    gGameSelect->modelCornerHidden = FALSE;
    
    if (recentLevelState > previousLevelState) {
        game_select_start_level_events(60);
        game_select_enqueue_level_event(prevX, prevY, recentLevelState);

        if (saveData->recentLevelClearedByBarista) {
            gGameSelect->baristaLevelEventPending = TRUE;
            gGameSelect->baristaLevelEventX = prevX;
            gGameSelect->baristaLevelEventY = prevY;
            gGameSelect->baristaLevelEventTimer = 60;
        }

        if ((get_level_id_from_grid_xy(prevX, prevY) == LEVEL_REMIX_6) && (recentLevelState >= LEVEL_STATE_CLEARED)) {
            enable_game_select_2_bgm();
        }
    } else {
        gGameSelect->runningLevelEvents = FALSE;
        gGameSelect->levelEventTimer = 0;
        write_game_save_data();

        if (gGameSelect->campaignNotice.hasNewCampaign) {
            start_campaign_notice(D_030046a8->data.currentCampaign);
            gGameSelect->campaignNotice.hasNewCampaign = FALSE;
        } else {
            gGameSelect->sceneState = GS_STATE_MAIN;
        }
    }

    // unlock tempo up (if existing save file for example) (this is FUCKING dirty and stupid i dont like that and it makes me cry at night)
    if (get_level_state_from_id(LEVEL_REMIX_8) >= LEVEL_STATE_CLEARED && get_level_state_from_id(LEVEL_KARATE_MAN_EXTRA) == LEVEL_STATE_HIDDEN) {
        set_level_state(saveData, LEVEL_KARATE_MAN_EXTRA, LEVEL_STATE_OPEN);
        set_level_state(saveData, LEVEL_RHYTHM_TWEEZERS_EXTRA, LEVEL_STATE_CLOSED);
        set_level_state(saveData, LEVEL_MARCHING_ORDERS_EXTRA, LEVEL_STATE_CLOSED);
        set_level_state(saveData, LEVEL_SPACEBALL_EXTRA, LEVEL_STATE_CLOSED);
        set_level_state(saveData, LEVEL_CLAPPY_TRIO_EXTRA, LEVEL_STATE_CLOSED);
        set_level_state(saveData, LEVEL_REMIX_1_EXTRA, LEVEL_STATE_CLOSED);
    }

    saveData->recentLevelState = LEVEL_STATE_NULL;
    saveData->recentLevelClearedByBarista = FALSE;
    results_set_enable_save(TRUE);
    game_select_disable_credits_after_epilogue();

    /* Init. BGM */
    get_grid_xy_from_level_id(LEVEL_STAFF_CREDIT, &prevX, &prevY);
    if (get_level_state_from_grid_xy(prevX, prevY) >= LEVEL_STATE_CLEARED) {
        enable_game_select_2_bgm();
    }

    /* Init. Scene Transitions */
    set_scene_trans_target(&scene_results_ver_rank, &scene_epilogue);
    set_scene_trans_target(&scene_results_ver_score, &scene_game_select);
    set_scene_trans_target(&scene_epilogue, &scene_game_select);
}


// Disable Credits Playing After Epilogue
void game_select_disable_credits_after_epilogue(void) {
    sPlayCreditsAfterEpilogue = FALSE;
}


// Enable Credits Playing After Epilogue
u32 game_select_roll_credits_after_epilogue(void) {
    return sPlayCreditsAfterEpilogue;
}


// Scene Update (Paused)
void game_select_scene_paused(void *sVar, s32 dArg) {
}


// Scroll Start - Grid
void game_select_scroll_grid_pane(s32 x, s32 y, s24_8 rate) {
    gGameSelect->gridPaneIsMoving = TRUE;
    gGameSelect->gridPaneX1 = gGameSelect->gridPaneX2;
    gGameSelect->gridPaneY1 = gGameSelect->gridPaneY2;
    gGameSelect->gridPaneX2 = x;
    gGameSelect->gridPaneY2 = y;
    gGameSelect->gridPaneMotionDecay = rate;
    gGameSelect->gridPaneMotionTime = INT_TO_FIXED(1.0);
}


// Scroll Start - Description Box
void game_select_scroll_info_pane(s32 x, s32 y, s24_8 rate) {
    gGameSelect->infoPaneIsMoving = TRUE;
    gGameSelect->infoPaneX1 = gGameSelect->infoPaneX2;
    gGameSelect->infoPaneY1 = gGameSelect->infoPaneY2;
    gGameSelect->infoPaneX2 = x;
    gGameSelect->infoPaneY2 = y;
    gGameSelect->infoPaneMotionDecay = rate;
    gGameSelect->infoPaneMotionTime = INT_TO_FIXED(1.0);
}


// Update Screen Scroll
void game_select_update_bg_scroll(void) {
    s24_8 x, y;
    s16 gridX, gridY;
    s32 i;

    if (gGameSelect->gridPaneIsMoving) {
        gGameSelect->gridPaneMotionTime = FIXED_POINT_MUL(gGameSelect->gridPaneMotionTime, gGameSelect->gridPaneMotionDecay);
        x = math_lerp(gGameSelect->gridPaneX2, gGameSelect->gridPaneX1, gGameSelect->gridPaneMotionTime, INT_TO_FIXED(1.0));
        y = math_lerp(gGameSelect->gridPaneY2, gGameSelect->gridPaneY1, gGameSelect->gridPaneMotionTime, INT_TO_FIXED(1.0));
        scene_set_bg_layer_pos(BG_LAYER_3, x, y);
        scene_set_bg_layer_pos(BG_LAYER_2, x, y);

        if (gGameSelect->gridPaneMotionTime == 0) {
            gGameSelect->gridPaneIsMoving = FALSE;
        }
    }

    if (gGameSelect->infoPaneIsMoving) {
        gGameSelect->infoPaneMotionTime = FIXED_POINT_MUL(gGameSelect->infoPaneMotionTime, gGameSelect->infoPaneMotionDecay);
        x = math_lerp(gGameSelect->infoPaneX2, gGameSelect->infoPaneX1, gGameSelect->infoPaneMotionTime, INT_TO_FIXED(1.0));
        y = math_lerp(gGameSelect->infoPaneY2, gGameSelect->infoPaneY1, gGameSelect->infoPaneMotionTime, INT_TO_FIXED(1.0));
        scene_set_bg_layer_pos(BG_LAYER_1, x, y);

        if (gGameSelect->infoPaneMotionTime == 0) {
            gGameSelect->infoPaneIsMoving = FALSE;
        }
    }
}


// Set Selection Border Sprite Z/Layer
void game_select_set_cursor_border_z(void) {
    s32 levelState = get_level_state_with_perfect_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY);
    // Adjust Z level to place selection border under the medal/perfect icon (if present).
    if ((levelState == LEVEL_STATE_HAS_MEDAL) || (levelState == LEVEL_STATE_PERFECT)) {
        sprite_set_z(gSpriteHandler, gGameSelect->selectionBorderSprite, 0x8800);
    } else {
        sprite_set_z(gSpriteHandler, gGameSelect->selectionBorderSprite, 0x4800);
    }
}


// Set Position for Cursor and Selection Border
void game_select_move_cursor_to_grid_xy(s32 x, s32 y) {
    s16 screenX, screenY;

    gGameSelect->cursorX = x;
    gGameSelect->cursorY = y;

    get_pixel_xy_from_grid_xy(x, y, &screenX, &screenY);

    screenX += 47;
    screenY += 68;

    sprite_set_x_y(gSpriteHandler, gGameSelect->selectionBorderSprite, screenX, screenY);
    sprite_set_x_y(gSpriteHandler, gGameSelect->cursorSprite, screenX, screenY);
    game_select_set_cursor_border_z();
}


// Get Next Valid Cursor Position in Given Directions (return FALSE if no movement should occur)
u32 game_select_get_next_valid_xy(s32 *xReq, s32 *yReq, s32 dx, s32 dy) {
    s32 x, y, levelID;

    x = *xReq;
    y = *yReq;

    // No movement is requested.
    if ((dx == 0) && (dy == 0)) {
        return FALSE;
    }

    // If both horizontal and vertical movement is requested, ignore the former.
    if ((dx != 0) && (dy != 0)) {
        dx = 0;
    }

    // Continuously move in the given direction, skipping grid icons that are either absent or hidden.
    while (TRUE) {
        x += dx;
        y += dy;

        // Movement target is out-of-bounds.
        if ((x < 0) || (x >= GS_GRID_WIDTH) || (y < 0) || (y >= (s32)GS_GRID_HEIGHT)) {
            return FALSE;
        }

        // Movement target is a visible grid icon.
        levelID = get_level_id_from_grid_xy(x, y);
        if ((levelID > LEVEL_NULL) && (get_level_state_from_id(levelID) >= LEVEL_STATE_CLOSED)) {
            *xReq = x;
            *yReq = y;
            return TRUE;
        }
    }
}


// Read Directional Inputs
void game_select_read_dpad_inputs(void) {
    s16 screenX, screenY;
    s32 x, y, dx, dy;
    s32 i;

    // Get horizontal and vertical movement.
    dx = dy = 0;
    if (D_030053b8 & DPAD_UP) {
        dy = -1;
    }
    if (D_030053b8 & DPAD_DOWN) {
        dy = 1;
    }
    if (D_030053b8 & DPAD_LEFT) {
        dx = -1;
    }
    if (D_030053b8 & DPAD_RIGHT) {
        dx = 1;
    }

    // No movement is requested.
    if ((dx == 0) && (dy == 0)) {
        return;
    }

    // If both horizontal and vertical movement is requested, ignore the former.
    if ((dx != 0) && (dy != 0)) {
        dx = 0;
    }

    x = gGameSelect->cursorX;
    y = gGameSelect->cursorY;

    // If the movement is invalid or zero, exit.
    if (!game_select_get_next_valid_xy(&x, &y, dx, dy)) {
        return;
    }

    // Movement is valid.
    game_select_move_cursor_to_grid_xy(x, y);
    get_pixel_xy_from_grid_xy(x, y, &screenX, &screenY);
    game_select_scroll_grid_pane(screenX, screenY, 200);
    game_select_set_info_pane_to_cursor_target();

    if (dx != 0) {
        game_select_set_stage_title(x);
    }

    play_sound(&s_menu_cursor1_seqData);
}


// Stub
void game_select_read_inputs_sub1(void) {
}


// Stub
void game_select_read_inputs_sub2(void) {
}


// Read Key Inputs
void game_select_read_inputs(void) {
    struct LevelData *levelData;
    s32 levelState, levelID;
    u32 canHaveCampaign;

    if (!game_select_scene_inputs_enabled()) {
        return;
    }

    /* Update inputs beside A_BUTTON and B_BUTTON. */
    game_select_read_inputs_sub1();
    game_select_read_inputs_sub2();
    game_select_read_dpad_inputs();

    /* A_BUTTON was pressed: Attempt to open the selected level. */
    if (D_03004afc & A_BUTTON) {
        levelState = get_level_state_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY);

        /* If the level can be opened: */
        if ((levelState == LEVEL_STATE_OPEN) || (levelState == LEVEL_STATE_CLEARED) || (levelState == LEVEL_STATE_HAS_MEDAL) || (levelState == LEVEL_STATE_PERFECT)) {
            D_030046a8->data.gsCursorX = gGameSelect->cursorX;
            D_030046a8->data.gsCursorY = gGameSelect->cursorY;
            levelID = get_level_id_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY);
            levelData = get_level_data_from_id(levelID);
            set_next_scene(levelData->scene);

            switch (levelData->type) {
                case LEVEL_TYPE_GAME:
                case LEVEL_TYPE_REMIX:
                    set_scene_trans_target(&scene_results_ver_rank, &scene_epilogue);
                    set_scene_trans_target(&scene_results_ver_score, &scene_game_select);
                    set_scene_trans_target(&scene_epilogue, &scene_game_select);
                    set_scene_trans_var(&scene_epilogue, (s32)levelData);
                    gameplay_pause_menu_set_quit_destination(&scene_game_select);
                    if ((levelID == LEVEL_REMIX_6) && (levelState == LEVEL_STATE_OPEN)) {
                        sPlayCreditsAfterEpilogue = TRUE;
                    }
                    canHaveCampaign = TRUE;

                    // hold select to replay a cleared campaign level
                    if(get_campaign_cleared(&D_030046a8->data, get_campaign_from_level_id(levelID)) && (D_03004ac0 & SELECT_BUTTON)) {
                        D_030046a8->data.campaignState = CAMPAIGN_STATE_ACTIVE;
                        D_030046a8->data.campaignAttemptsLeft = 1;
                        gGameSelect->campaignNotice.id = get_campaign_from_level_id(levelID);
                        gGameSelect->campaignNotice.x = gGameSelect->cursorX;
                        gGameSelect->campaignNotice.y = gGameSelect->cursorY;
                        sReplayingCampaign = TRUE;
                    } else {
                        sReplayingCampaign = FALSE;
                    }

                    break;

                case LEVEL_TYPE_BONUS:
                    if (levelID == LEVEL_LIVE_MENU) {
                        set_scene_trans_target(levelData->scene, &scene_epilogue);
                        set_scene_trans_target(&scene_epilogue, &scene_game_select);
                        set_scene_trans_var(&scene_epilogue, (s32)levelData);
                        gameplay_pause_menu_set_quit_destination(&scene_game_select);
                    } else {
                        set_scene_trans_target(levelData->scene, &scene_game_select);
                        gameplay_pause_menu_set_quit_destination(&scene_game_select);
                    }
                    canHaveCampaign = FALSE;
                    break;
            }

            D_030046a8->data.gsCursorX = D_030046a8->data.recentLevelX = gGameSelect->cursorX;
            D_030046a8->data.gsCursorY = D_030046a8->data.recentLevelY = gGameSelect->cursorY;
            D_030046a8->data.recentLevelState = LEVEL_STATE_NULL;

            if (canHaveCampaign && (D_030046a8->data.campaignState == CAMPAIGN_STATE_ACTIVE) && (gGameSelect->campaignNotice.id >= 0)) {
                if ((gGameSelect->cursorX == gGameSelect->campaignNotice.x) && (gGameSelect->cursorY == gGameSelect->campaignNotice.y)) {
                    set_current_campaign(gGameSelect->campaignNotice.id);
                    D_030046a8->data.campaignAttemptsLeft--;
                    D_030046a8->data.unk26A = 0;
                } else {
                    D_030046a8->data.campaignAttemptsLeft--;
                }
            }

            write_game_save_data();
            set_pause_beatscript_scene(FALSE);
            gGameSelect->inputsEnabled = FALSE;
            play_sound(&s_menu_kettei1_seqData);
            return;
        }

        /* If the level cannot be opened: */
        play_sound(&s_menu_error_seqData);
        return;
    }

    /* B_BUTTON was pressed: Return to Main Menu. */
    if (D_03004afc & B_BUTTON) {
        set_next_scene(&scene_main_menu);
        set_scene_trans_var(&scene_main_menu, 0);
        D_030046a8->data.gsCursorX = D_030046a8->data.recentLevelX = gGameSelect->cursorX;
        D_030046a8->data.gsCursorY = D_030046a8->data.recentLevelY = gGameSelect->cursorY;
        D_030046a8->data.recentLevelState = LEVEL_STATE_NULL;
        write_game_save_data();
        set_pause_beatscript_scene(FALSE);
        gGameSelect->inputsEnabled = FALSE;
        play_sound(&s_menu_cancel3_seqData);
    }
}


// Set Info Pane to Cursor Target
void game_select_set_info_pane_to_cursor_target(void) {
    s32 levelState = get_level_state_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY);

    switch (levelState) {
        case (LEVEL_STATE_NULL):
        case (LEVEL_STATE_HIDDEN):
        case (LEVEL_STATE_CLOSED):
            game_select_set_info_pane(LEVEL_NULL, LEVEL_STATE_HIDDEN, 10);
            break;

        case (LEVEL_STATE_OPEN):
        case (LEVEL_STATE_CLEARED):
        case (LEVEL_STATE_HAS_MEDAL):
            game_select_set_info_pane(get_level_id_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY), levelState, 10);
            break;
    }
}


// Update Stage Title Position
void game_select_update_stage_title_pos(void) {
    s32 yTarget, y;

    // Get a target Y position.
    if (gGameSelect->hideStageTitle) {
        yTarget = STAGE_PANE_Y_HIDDEN;
    } else {
        yTarget = STAGE_PANE_Y_VISIBLE;

        // If the Stage Title would obscure any level icons, hide the pane.
        if (gGameSelect->cursorY < 10) {
            if (gGameSelect->stageTitlePersistTime == 0) {
                yTarget = STAGE_PANE_Y_HIDDEN;
            }
        } else {
            gGameSelect->stageTitlePersistTime = 0;
        }
    }

    // Get a Y position up to 9px closer to the target from the current position.
    y = gGameSelect->stageTitleY;
    if (y < yTarget) {
        y += STAGE_PANE_SPEED;
        if (y > yTarget) {
            y = yTarget;
        }
    }
    if (y > yTarget) {
        y -= STAGE_PANE_SPEED;
        if (y < yTarget) {
            y = yTarget;
        }
    }

    // Implement new Y value.
    sprite_set_y(gSpriteHandler, gGameSelect->stageTitleText, y);
    sprite_set_y(gSpriteHandler, gGameSelect->stageTitlePane, y);
    gGameSelect->stageTitleY = y;

    // Update persistence timer.
    if (gGameSelect->stageTitlePersistTime > 0) {
        gGameSelect->stageTitlePersistTime--;
    }
}


// Set Stage Title
void game_select_set_stage_title(s32 x) {
    s32 i;

    sprite_set_anim(gSpriteHandler, gGameSelect->stageTitleText, game_select_stage_title_anim[x], 0, 1, 0x7f, 0);
    gGameSelect->stageTitlePersistTime = 100;
}


// Update Stage Title
void game_select_update_stage_title(void) {
    game_select_update_stage_title_pos();
}


// Link Sprite X/Y to Grid BG H/V Offset
void game_select_link_sprite_xy_to_bg(s16 sprite) {
    sprite_set_origin_x_y(gSpriteHandler, sprite, &D_03004b10.BG_OFS[BG_LAYER_3].x, &D_03004b10.BG_OFS[BG_LAYER_3].y);
}


// Scene Update (Active)
void game_select_scene_update(void *sVar, s32 dArg) {
    s16 bgOfsX, bgOfsY;
    s32 i;

    if (gGameSelect->loadingSceneGfx) {
        return;
    }

    bgOfsX = D_03004b10.BG_OFS[BG_LAYER_3].x;
    bgOfsY = D_03004b10.BG_OFS[BG_LAYER_3].y;

    switch (gGameSelect->sceneState) {
        case GS_STATE_UNLOCKING_LEVELS:
            game_select_update_level_events();
            break;

        case GS_STATE_MAIN:
            game_select_read_inputs();
            break;

        case GS_STATE_DISPLAYING_CAMPAIGN:
            update_campaign_notice();
            break;
    }

    game_select_update_bg_colors();
    game_select_update_stub();
    game_select_update_info_pane();
    game_select_update_bg_scroll();
    game_select_update_stage_title();
    bgOfsX -= D_03004b10.BG_OFS[BG_LAYER_3].x;
    bgOfsY -= D_03004b10.BG_OFS[BG_LAYER_3].y;
    game_select_update_bg_squares(bgOfsX - 1, bgOfsY);
    game_select_update_icon_squares();
    game_select_update_flow_pane();
    game_select_update_medal_pane();

    if(D_03004b10.BG_OFS[BG_LAYER_3].x >= (9 * 40) - 39){
        if(!gGameSelect->modelCornerHidden) {
            for(i = 6; i < 12; i++){
                game_select_clear_bg_tiles(28, 3, 1 + (1 * 5), 4 + (i * 3), 3, 3, 0, 0);
                game_select_clear_bg_tiles(24, 3, 1 + (1 * 5), 4 + (i * 3), 3, 3, 1280, 0);
            }
            game_select_clear_bg_tiles(28, 3, 1 + (2 * 5), 4 + (6 * 3), 3, 3, 0, 0);
            game_select_clear_bg_tiles(24, 3, 1 + (2 * 5), 4 + (6 * 3), 3, 3, 1280, 0);
            gGameSelect->modelCornerHidden = TRUE;
        }
    } else {
        if(gGameSelect->modelCornerHidden) {
            for (i = 6; i < 12; i++) {
                game_select_set_icon_map_after_level_event(1, i);
            }
            game_select_set_icon_map_after_level_event(2, 6);
            gGameSelect->modelCornerHidden = FALSE;
        }
    }

}


// Check if Scene Can Receive Inputs
u32 game_select_scene_inputs_enabled(void) {
    if (gGameSelect->inputsEnabled) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Set D_030055d4 and D_03005590
void game_select_set_unused_static_var(u32 arg0, u32 arg1) {
    D_030055d4 = arg0;
    D_03005590 = arg1;
}


// Return the Total Number of Levels
u32 game_select_get_total_levels(void) {
    return ALL_LEVELS;
}


// Get Level Name from ID
const char *game_select_get_level_name(s32 id) {
    struct LevelData *levelData;

    if (id < 0) {
        return NULL;
    }

    if (id >= ALL_LEVELS) {
        return NULL;
    }

    levelData = &level_data_table[id];
    return levelData->name;
}


// Enqueue New Level Event
void game_select_enqueue_level_event(s32 x, s32 y, s32 state) {
    struct QueuedLevelEvent *data;
    s32 oldState;

    if (state == LEVEL_STATE_NULL) {
        return;
    }

    oldState = get_level_state_from_grid_xy(x, y);
    if ((oldState >= 0) && (oldState < state)) {
        data = &gGameSelect->levelEventsQueue[gGameSelect->levelEventEnqueueID];
        data->x = x;
        data->y = y;
        data->state = state;

        gGameSelect->totalLevelEventsQueued++;
        if (++gGameSelect->levelEventEnqueueID >= ARRAY_COUNT(gGameSelect->levelEventsQueue)) {
            gGameSelect->levelEventEnqueueID = 0;
        }
    }
}


// Dequeue New Level Event
void game_select_dequeue_level_event(s32 *xReq, s32 *yReq, s32 *stateReq) {
    struct QueuedLevelEvent *data;

    if (gGameSelect->totalLevelEventsQueued == 0) {
        *stateReq = LEVEL_STATE_NULL;
        return;
    }

    data = &gGameSelect->levelEventsQueue[gGameSelect->levelEventDequeueID];
    *xReq = data->x;
    *yReq = data->y;
    *stateReq = data->state;

    gGameSelect->totalLevelEventsQueued--;
    if (++gGameSelect->levelEventDequeueID >= ARRAY_COUNT(gGameSelect->levelEventsQueue)) {
        gGameSelect->levelEventDequeueID = 0;
    }
}


// Check Level Show/Open Requirements
u32 game_select_check_level_event_req(s32 x, s32 y, s32 newState) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    struct GameSelectGridEntry *gridEntry;
    const s8 *requirements;
    s32 state;

    gridEntry = game_select_grid_data + x + (y * GS_GRID_WIDTH);

    if (gridEntry->id < 0) {
        return FALSE;
    }

    state = get_level_state(saveData, gridEntry->id);
    requirements = NULL;

    switch (state) {
        case LEVEL_STATE_HIDDEN:
            if (newState == LEVEL_STATE_CLOSED) {
                requirements = gridEntry->displayReq;
            }
        case LEVEL_STATE_CLOSED:
            if (newState == LEVEL_STATE_OPEN) {
                requirements = gridEntry->unlockReq;
            }
    }

    if (requirements == NULL) {
        return FALSE;
    }

    while (TRUE) {
        s32 x, y;

        if (requirements[0] == -1) {
            return TRUE;
        }

        x = requirements[1];
        y = requirements[2];
        gridEntry = game_select_grid_data + x + (y * GS_GRID_WIDTH);

        if (gridEntry->id < 0) {
            return FALSE;
        }

        state = get_level_state(saveData, gridEntry->id);

        switch (requirements[0]) {
            case LEVEL_STATE_HAS_MEDAL:
                if (state == LEVEL_STATE_CLEARED) {
                    return FALSE;
                }
            case LEVEL_STATE_CLEARED:
                if (state == LEVEL_STATE_OPEN) {
                    return FALSE;
                }
            case LEVEL_STATE_OPEN:
                if (state == LEVEL_STATE_CLOSED) {
                    return FALSE;
                }
            case LEVEL_STATE_CLOSED:
                if (state == LEVEL_STATE_APPEARING) {
                    return FALSE;
                }
                if (state == LEVEL_STATE_HIDDEN) {
                    return FALSE;
                }
                break;

            default:
                return FALSE;
        }

        requirements += 3;
    }

    return TRUE;
}


// Set Level Icon Map After Level Event
void game_select_set_icon_map_after_level_event(s32 x, s32 y) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    struct LevelData *levelData;
    s32 id, state, type;
    u32 tileX, tileY, tileNum, overlay, palette;

    id = get_level_id_from_grid_xy(x, y);

    if (id < 0) {
        return;
    }

    tileX = 1 + (x * 5);
    tileY = 4 + (y * 3);
    levelData = &level_data_table[id];
    type = levelData->type;
    // Only use perfect detection for actual playable levels (like medal system)
    if (type == LEVEL_TYPE_GAME || type == LEVEL_TYPE_REMIX) {
        state = get_level_state_with_perfect_from_id(id);
    } else {
        state = get_level_state_from_id(id);
    }
    overlay = level_icon_overlays_map[type][state];

    if ((state == LEVEL_STATE_HIDDEN) || (state == LEVEL_STATE_APPEARING)) {
        return;
    }

    tileNum = 1 + (levelData->icon * 9);
    palette = level_icon_palette_table[levelData->icon];
    game_select_print_icon_maps(28, 3, tileX, tileY, 3, 3, tileNum, palette);

    tileNum = 1 + (overlay * 9) + 0x100;
    
    // Adjust position for perfect overlay (move right 1 tile)
    if (overlay == LEVEL_ICON_OVERLAY_PERFECT) {
        game_select_print_icon_maps(24, 3, tileX + 1, tileY, 3, 3, tileNum, 8);
    } else {
        game_select_print_icon_maps(24, 3, tileX, tileY, 3, 3, tileNum, 8);
    }
}


// Helper Function
void enqueue_level_event_after_reveal(u32 args) {
    s32 x, y, state;

    y = args & 0xFF;
    args >>= 8;

    x = args & 0xFF;
    args >>= 8;

    state = args;

    game_select_enqueue_level_event(x, y, state);
}


// Set Level Event Target
u32 game_select_set_level_event_target(s32 x, s32 y, u32 moveCursor, s24_8 scrollRate) {
    s16 screenX, screenY;

    gGameSelect->levelEventTargetX = x;
    gGameSelect->levelEventTargetY = y;

    get_pixel_xy_from_grid_xy(x, y, &screenX, &screenY);
    game_select_scroll_grid_pane(screenX, screenY, scrollRate);

    if (gGameSelect->cursorX != x) {
        gGameSelect->hideStageTitle = TRUE;
    }

    if (moveCursor) {
        game_select_move_cursor_to_grid_xy(x, y);
    }
}


// Process Level Event Targets List
u32 game_select_process_level_event_targets(const s8 *eventTargets) {
    struct GameSelectGridEntry *gridEntry;
    s32 x, y;

    if (eventTargets == NULL) {
        return;
    }

    while ((eventTargets[0] >= 0) && (eventTargets[1] >= 0)) {
        x = eventTargets[0];
        y = eventTargets[1];
        gridEntry = game_select_grid_data + x + (y * GS_GRID_WIDTH);

        if (game_select_check_level_event_req(x, y, LEVEL_STATE_OPEN)) {
            s32 state = LEVEL_STATE_OPEN;

            if (gridEntry->flags & LEVEL_EVENT_CLEAR_BY_DEFAULT) {
                state = LEVEL_STATE_CLEARED;
            }
            game_select_enqueue_level_event(x, y, state);

            if (gridEntry->flags & LEVEL_EVENT_TARGET_ON_OPEN) {
                game_select_set_level_event_target(x, y, gridEntry->flags & LEVEL_EVENT_MOVE_CURSOR, 240);
                if (gGameSelect->levelEventTimer < 90) {
                    gGameSelect->levelEventTimer = 90;
                }
            }
        }

        else if (game_select_check_level_event_req(x, y, LEVEL_STATE_CLOSED)) {
            s32 args;

            args = LEVEL_STATE_CLOSED;
            args <<= 8;
            args |= x;
            args <<= 8;
            args |= y;

            game_select_spawn_icon_square(x, y, enqueue_level_event_after_reveal, args, gridEntry->orderIndex * 6);
            if (gridEntry->flags & LEVEL_EVENT_TARGET_ON_SHOW) {
                game_select_set_level_event_target(x, y, gridEntry->flags & LEVEL_EVENT_MOVE_CURSOR, 250);
            }
            save_level_state_from_grid_xy(x, y, LEVEL_STATE_APPEARING);
        }

        eventTargets += 2;
    }
}


// Process Level Events
u32 game_select_process_level_events(void) {
    struct GameSelectGridEntry *gridEntry;
    const s8 *eventTargets;
    s16 screenX, screenY;
    s32 x, y, state, id;
    s16 sprite;

    if (gGameSelect->levelEventPending) {
        gGameSelect->levelEventPending = FALSE;
        game_select_process_level_event_targets(gGameSelect->levelEventTargets);
        return FALSE;
    }

    game_select_dequeue_level_event(&x, &y, &state);
    if (state == LEVEL_STATE_NULL) {
        return TRUE;
    }

    id = get_level_id_from_grid_xy(x, y);
    get_pixel_xy_from_grid_xy(x, y, &screenX, &screenY);

    switch (state) {
        case LEVEL_STATE_OPEN:
            screenX += 47;
            screenY += 68;
            sprite = sprite_create(gSpriteHandler, anim_game_select_new_game, 0, screenX, screenY, 0x4864, 1, 0, 3);
            game_select_link_sprite_xy_to_bg(sprite);
            play_sound(&s_f_open_game_seqData);
            break;

        case LEVEL_STATE_CLEARED:
            screenX += 47;
            screenY += 68;
            sprite = sprite_create(gSpriteHandler, anim_game_select_clear_game, 0, screenX, screenY, 0x4864, 1, 0, 3);
            game_select_link_sprite_xy_to_bg(sprite);
            play_sound(&s_f_clear_game_seqData);

            cafe_session_remove_level(id);
            set_level_first_ok(&D_030046a8->data, id, get_level_total_plays(&D_030046a8->data, id));
            break;

        case LEVEL_STATE_HAS_MEDAL:
            screenX += 47;
            screenY += 68;
            sprite = sprite_create(gSpriteHandler, anim_game_select_get_superb, 0, screenX, screenY, 0x4864, 1, 0, 3);
            game_select_link_sprite_xy_to_bg(sprite);
            play_sound_w_pitch_volume(&s_f_clear_game_seqData, INT_TO_FIXED(0.5), INT_TO_FIXED(2.0));
            play_sound(&s_f_get_medal_seqData);

            D_030046a8->data.totalMedals++;
            game_select_refresh_medal_count(127);
            cafe_session_remove_level(id);
            set_level_first_superb(&D_030046a8->data, id, get_level_total_plays(&D_030046a8->data, id));
            if(get_level_first_ok(&D_030046a8->data, id) == 0) {
                set_level_first_ok(&D_030046a8->data, id, get_level_total_plays(&D_030046a8->data, id));
            }
            break;
    }

    save_level_state_from_grid_xy(x, y, state);
    game_select_set_icon_map_after_level_event(x, y);

    if ((x == gGameSelect->cursorX) && (y == gGameSelect->cursorY)) {
        game_select_set_cursor_border_z();
        game_select_set_info_pane_to_cursor_target();
    }

    gridEntry = game_select_grid_data + x + (y * GS_GRID_WIDTH);

    if ((state == LEVEL_STATE_CLEARED) || (state == LEVEL_STATE_HAS_MEDAL)) {
        if ((gridEntry->flags & LEVEL_EVENT_DELAY_CLEAR)) {
            gGameSelect->levelEventTimer = 60;
        }
    }
    if (state == LEVEL_STATE_OPEN) {
        if ((gridEntry->flags & LEVEL_EVENT_DELAY_OPEN)) {
            gGameSelect->levelEventTimer = 60;
        }
    }
    if (state == LEVEL_STATE_CLOSED) {
        if ((gridEntry->flags & LEVEL_EVENT_DELAY_SHOW)) {
            gGameSelect->levelEventTimer = 60;
        }
    }

    eventTargets = NULL;
    if (gridEntry->id >= 0) {
        eventTargets = gridEntry->targets;
    }

    if (gGameSelect->levelEventTimer == 0) {
        game_select_process_level_event_targets(eventTargets);
    } else {
        gGameSelect->levelEventPending = TRUE;
        gGameSelect->levelEventTargets = eventTargets;
    }

    return FALSE;
}


// Update Level Events
void game_select_update_level_unlocks(void) {
    while (!game_select_process_level_events()) {
        if (gGameSelect->levelEventTimer > 0) {
            return;
        }
    }
}


// Start Level Events
void game_select_start_level_events(u32 delay) {
    gGameSelect->runningLevelEvents = TRUE;
    gGameSelect->levelEventTargetX = gGameSelect->cursorX;
    gGameSelect->levelEventTargetY = gGameSelect->cursorY;
    gGameSelect->levelEventTimer = delay;
    gGameSelect->sceneState = GS_STATE_UNLOCKING_LEVELS;
}


// Update Level Events
void game_select_update_level_events(void) {
    s16 screenX, screenY;
    s32 x, y;
    u32 eventsFinished;

    // Decrement timer.
    if (gGameSelect->levelEventTimer > 0) {
        gGameSelect->levelEventTimer--;
        return;
    }

    // Scroll to show Barista-cleared level.
    if (gGameSelect->baristaLevelEventPending) {
        gGameSelect->baristaLevelEventPending = FALSE;

        x = gGameSelect->baristaLevelEventX;
        y = gGameSelect->baristaLevelEventY;
        gGameSelect->levelEventTargetX = x;
        gGameSelect->levelEventTargetY = y;
        get_pixel_xy_from_grid_xy(x, y, &screenX, &screenY);
        game_select_scroll_grid_pane(screenX, screenY, 240);

        if (gGameSelect->cursorX != x) {
            gGameSelect->hideStageTitle = TRUE;
        }

        gGameSelect->levelEventTimer = 120;
        return;
    }

    // Update level-unlock events.
    eventsFinished = TRUE;
    if (game_select_check_for_icon_squares()) {
        eventsFinished = FALSE;
    }
    if ((gGameSelect->totalLevelEventsQueued > 0) || (gGameSelect->levelEventPending)) {
        game_select_update_level_unlocks();
        eventsFinished = FALSE;
    }
    if (gGameSelect->gridPaneIsMoving) {
        eventsFinished = FALSE;
    }

    if (!eventsFinished) {
        return;
    }

    // Return to cursor position.
    if ((gGameSelect->cursorX != gGameSelect->levelEventTargetX) || (gGameSelect->cursorY != gGameSelect->levelEventTargetY)) {
        if (gGameSelect->baristaLevelEventTimer > 0) {
            gGameSelect->levelEventTimer = gGameSelect->baristaLevelEventTimer;
            gGameSelect->baristaLevelEventTimer = 0;
        } else {
            gGameSelect->levelEventTargetX = gGameSelect->cursorX;
            gGameSelect->levelEventTargetY = gGameSelect->cursorY;
            get_pixel_xy_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY, &screenX, &screenY);
            game_select_scroll_grid_pane(screenX, screenY, 240);
        }
        return;
    }

    gGameSelect->baristaLevelEventTimer = 0;
    gGameSelect->runningLevelEvents = FALSE;
    gGameSelect->hideStageTitle = FALSE;
    D_030046a8->data.gsCursorX = gGameSelect->cursorX;
    D_030046a8->data.gsCursorY = gGameSelect->cursorY;

#if REV < 1
    if (gGameSelect->manualUnlockEnabled) {
        save_level_state_from_grid_xy(gGameSelect->manualUnlockX, gGameSelect->manualUnlockY, LEVEL_STATE_OPEN);
    }
#endif

    write_game_save_data();

    if (gGameSelect->campaignNotice.hasNewCampaign) {
        start_campaign_notice(D_030046a8->data.currentCampaign);
        gGameSelect->campaignNotice.hasNewCampaign = FALSE;
    } else {
        gGameSelect->sceneState = GS_STATE_MAIN;
    }
}


// Set Medal Count
void game_select_set_medal_count(u32 total) {
    total = clamp_int32(total, 0, 99);

    sprite_set_anim_cel(gSpriteHandler, gGameSelect->medalPaneDigit1, total % 10);
    sprite_set_anim_cel(gSpriteHandler, gGameSelect->medalPaneDigit2, (total < 10) ? 10 : (total / 10));
    sprite_set_x(gSpriteHandler, gGameSelect->medalPaneDigit1, (total < 10) ? 163 : 167);
}


// Init. Medal Pane
void game_select_init_medal_pane(void) {
    struct Vector2 *bgOfs = &D_03004b10.BG_OFS[BG_LAYER_1];

    gGameSelect->medalPaneTitle = sprite_create(gSpriteHandler, anim_game_select_medal_text, 0, 161, 151, 0x800, 0, 0, 0);
    gGameSelect->medalPaneDigit1 = sprite_create(gSpriteHandler, anim_game_select_medal_num, 0, 168, 151, 0x800, 0, 0x7f, 0);
    gGameSelect->medalPaneDigit2 = sprite_create(gSpriteHandler, anim_game_select_medal_num, 0, 168, 151, 0x800, 0, 0x7f, 0);
    sprite_set_x_y(gSpriteHandler, gGameSelect->medalPaneDigit2, 160, 151);

    sprite_set_origin_x_y(gSpriteHandler, gGameSelect->medalPaneTitle, &bgOfs->x, &bgOfs->y);
    sprite_set_origin_x_y(gSpriteHandler, gGameSelect->medalPaneDigit1, &bgOfs->x, &bgOfs->y);
    sprite_set_origin_x_y(gSpriteHandler, gGameSelect->medalPaneDigit2, &bgOfs->x, &bgOfs->y);
    game_select_set_medal_count(D_030046a8->data.totalMedals);
    gGameSelect->medalPaneFlickerTimer = 0;
}


// Update Medal Pane Flicker
u32 game_select_update_medal_pane_flicker(void) {
    u32 render;

    if (gGameSelect->medalPaneFlickerTimer > 0) {
        render = ~(--gGameSelect->medalPaneFlickerTimer / 16) & 1;

        sprite_set_visible(gSpriteHandler, gGameSelect->medalPaneTitle, render);
        sprite_set_visible(gSpriteHandler, gGameSelect->medalPaneDigit1, render);
        sprite_set_visible(gSpriteHandler, gGameSelect->medalPaneDigit2, render);
    }
}


// Update Medal Pane
void game_select_update_medal_pane(void) {
    game_select_update_medal_pane_flicker();
}


// Refresh Medal Count
void game_select_refresh_medal_count(u32 flickerDuration) {
    game_select_set_medal_count(D_030046a8->data.totalMedals);
    gGameSelect->medalPaneFlickerTimer = flickerDuration;
}


// Init. Level Info Pane
void game_select_init_info_pane(void) {
    struct Vector2 *bgOfs = &D_03004b10.BG_OFS[BG_LAYER_1];

    gGameSelect->infoPaneName = -1;
    gGameSelect->infoPaneRank = -1;
    gGameSelect->infoPaneDesc = text_printer_create_new(get_current_mem_id(), 4, 104, 32);
    text_printer_set_x_y(gGameSelect->infoPaneDesc, 129, 50);
    text_printer_set_layer(gGameSelect->infoPaneDesc, 0x800);
    text_printer_set_colors(gGameSelect->infoPaneDesc, 0);
    text_printer_set_palette(gGameSelect->infoPaneDesc, 8);
    text_printer_set_line_spacing(gGameSelect->infoPaneDesc, 15);
    text_printer_center_by_content(gGameSelect->infoPaneDesc, 1);
    text_printer_set_x_y_controller(gGameSelect->infoPaneDesc, &bgOfs->x, &bgOfs->y);
    text_printer_set_shadow_colors(gGameSelect->infoPaneDesc, -1);
    gGameSelect->perfectClearedSprite = sprite_create(gSpriteHandler, anim_game_select_perfect_rank, 0, 187, 112, 0x80A, 1, 0, 0x8000);
    sprite_set_origin_x_y(gSpriteHandler, gGameSelect->perfectClearedSprite, &bgOfs->x, &bgOfs->y);
    gGameSelect->noPracticeSprite = sprite_create(gSpriteHandler, anim_game_select_no_practice, 0, 188, 94, 0x80A, 1, 0, 0x8000);
    sprite_set_origin_x_y(gSpriteHandler, gGameSelect->noPracticeSprite, &bgOfs->x, &bgOfs->y);
    gGameSelect->tempoUpSprite = sprite_create(gSpriteHandler, anim_game_select_tempo_up, 0, 154, 38, 0x80A, 1, 0, 0x8000);
    sprite_set_origin_x_y(gSpriteHandler, gGameSelect->tempoUpSprite, &bgOfs->x, &bgOfs->y);
    gGameSelect->infoPaneIsClear = TRUE;
    gGameSelect->infoPaneTask = INFO_PANE_TASK_NONE;
}


// Delete Level Info Pane Text Sprite
void game_select_delete_info_pane_sprite(s16 *ptr) {
    s16 sprite = *ptr;

    if (sprite < 0) {
        return;
    }

    text_printer_delete_anim((void *)sprite_get_data(gSpriteHandler, sprite, 7));
    sprite_delete(gSpriteHandler, sprite);
    *ptr = -1;
}


// Clear Level Info Pane
void game_select_clear_info_pane(void) {
    if (gGameSelect->infoPaneIsClear) {
        return;
    }

    text_printer_fill_vram_tiles(0, 24, 32, 8, 0);
    game_select_delete_info_pane_sprite(&gGameSelect->infoPaneName);
    game_select_delete_info_pane_sprite(&gGameSelect->infoPaneRank);
    text_printer_clear(gGameSelect->infoPaneDesc);
    sprite_set_visible(gSpriteHandler, gGameSelect->perfectClearedSprite, FALSE);
    sprite_set_visible(gSpriteHandler, gGameSelect->noPracticeSprite, FALSE);
    sprite_set_visible(gSpriteHandler, gGameSelect->tempoUpSprite, FALSE);
    sprite_set_x_y(gSpriteHandler, gGameSelect->perfectClearedSprite, 187, 112);
    text_printer_set_x_y(gGameSelect->infoPaneDesc, 129, 50);
    text_printer_set_line_spacing(gGameSelect->infoPaneDesc, 15);
    gGameSelect->infoPaneIsClear = TRUE;
}


// Print Level Name
void game_select_print_level_name(struct LevelData *levelData) {
    struct Animation *anim;
    const char *string;

    text_printer_fill_vram_tiles(0, 26, 16, 2, 0);
    string = levelData->name;
    anim = text_printer_get_formatted_line_anim(get_current_mem_id(), 0, 26, TEXT_PRINTER_FONT_SMALL, &string, TEXT_ANCHOR_BOTTOM_CENTER, 0, 104, 0, -1);
    gGameSelect->infoPaneName = sprite_create(gSpriteHandler, anim, 0, 180, 30, 0x800, 1, 0, 0x8000);
    sprite_set_base_palette(gSpriteHandler, gGameSelect->infoPaneName, 7);
    gGameSelect->infoPaneIsClear = FALSE;
}


// Print Level Description
void game_select_print_level_desc(struct LevelData *levelData) {
    text_printer_set_string(gGameSelect->infoPaneDesc, levelData->description);
    gGameSelect->infoPaneIsClear = FALSE;
}


// Print Level Rank
void game_select_print_level_rank(s32 levelState) {
    struct Animation *anim;
    const char *string;
    u32 i;
    u32 found = FALSE;

    if (get_level_score(&D_030046a8->data, gGameSelect->infoPaneLevelID) == DEFAULT_LEVEL_SCORE) {
        levelState = LEVEL_STATE_OPEN;
    }

    // Check if the game has been perfected
    if (get_campaign_cleared(&D_030046a8->data, get_campaign_from_level_id(gGameSelect->infoPaneLevelID))) {
        levelState = LEVEL_STATE_PERFECT; // Use the new "perfect" rank
    }

    found = gGameSelect->infoPaneLevelData->flags & (LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE);

    text_printer_fill_vram_tiles(16, 26, 16, 2, 0);
    string = game_select_rank_text[levelState];
    anim = text_printer_get_formatted_line_anim(get_current_mem_id(), 16, 26, TEXT_PRINTER_FONT_SMALL, &string, TEXT_ANCHOR_BOTTOM_RIGHT, 0, 104, 0, -1);
    gGameSelect->infoPaneRank = sprite_create(gSpriteHandler, anim, 0, 228, found ? 116 : 113, 0x800, 1, 0, 0x8000);
    sprite_set_base_palette(gSpriteHandler, gGameSelect->infoPaneRank, game_select_rank_palette[levelState]);
    gGameSelect->infoPaneIsClear = FALSE;

}

// Update Level Info Pane
void game_select_process_info_pane(void) {
    struct Vector2 *bgOfs = &D_03004b10.BG_OFS[BG_LAYER_1];
    s32 campaign;
    u32 i;

    // Set the flag for the current info pane level

    switch (gGameSelect->infoPaneTask) {
        case INFO_PANE_TASK_DELAY:
            if (--gGameSelect->infoPaneDelay == 0) {
                gGameSelect->infoPaneTask = INFO_PANE_TASK_PRINT_NAME;
            }
            break;

        case INFO_PANE_TASK_PRINT_NAME:
            game_select_print_level_name(gGameSelect->infoPaneLevelData);
            gGameSelect->infoPaneTask = INFO_PANE_TASK_PRINT_RANK;
            break;

        case INFO_PANE_TASK_PRINT_RANK:
            if (gGameSelect->infoPaneLevelData->type != 2) {
                game_select_print_level_rank(gGameSelect->infoPaneLevelState);
            }
            gGameSelect->infoPaneTask = INFO_PANE_TASK_PRINT_DESC;
            break;

        case INFO_PANE_TASK_PRINT_DESC:
            game_select_print_level_desc(gGameSelect->infoPaneLevelData);
            gGameSelect->infoPaneTask = INFO_PANE_TASK_RENDER;

            if(gGameSelect->infoPaneLevelData->flags & LEVEL_DATA_FLAG_IS_EXTRA) {
                text_printer_set_line_spacing(gGameSelect->infoPaneDesc, 14);
                text_printer_set_x_y(gGameSelect->infoPaneDesc, 129, 60);
            } else if (gGameSelect->infoPaneLevelData->flags & LEVEL_DATA_FLAG_NO_PRACTICE) {
                text_printer_set_line_spacing(gGameSelect->infoPaneDesc, 14);
                text_printer_set_x_y(gGameSelect->infoPaneDesc, 129, 47);
            }

        case INFO_PANE_TASK_RENDER:
            if (!text_printer_is_busy(gGameSelect->infoPaneDesc)) {
                sprite_set_visible(gSpriteHandler, gGameSelect->infoPaneName, TRUE);
                sprite_set_origin_x_y(gSpriteHandler, gGameSelect->infoPaneName, &bgOfs->x, &bgOfs->y);
                sprite_set_visible(gSpriteHandler, gGameSelect->infoPaneRank, TRUE);
                sprite_set_origin_x_y(gSpriteHandler, gGameSelect->infoPaneRank, &bgOfs->x, &bgOfs->y);

                campaign = get_campaign_from_grid_xy(gGameSelect->cursorX, gGameSelect->cursorY);
                if ((campaign >= 0) && get_campaign_cleared(&D_030046a8->data, campaign)) {
                    sprite_set_visible(gSpriteHandler, gGameSelect->perfectClearedSprite, TRUE);
                }

                if (gGameSelect->infoPaneLevelData->flags & LEVEL_DATA_FLAG_IS_EXTRA) {
                    sprite_set_visible(gSpriteHandler, gGameSelect->tempoUpSprite, TRUE);
                    sprite_set_x_y(gSpriteHandler, gGameSelect->perfectClearedSprite, 187, 115);
                    text_printer_set_line_spacing(gGameSelect->infoPaneDesc, 14);
                    text_printer_set_x_y(gGameSelect->infoPaneDesc, 129, 60);
                } else if (gGameSelect->infoPaneLevelData->flags & LEVEL_DATA_FLAG_NO_PRACTICE) {
                    sprite_set_visible(gSpriteHandler, gGameSelect->noPracticeSprite, TRUE);
                    sprite_set_x_y(gSpriteHandler, gGameSelect->perfectClearedSprite, 187, 115);
                    text_printer_set_line_spacing(gGameSelect->infoPaneDesc, 14);
                    text_printer_set_x_y(gGameSelect->infoPaneDesc, 129, 47);
                }

                gGameSelect->infoPaneTask = INFO_PANE_TASK_NONE;
            }
            break;
    }
}


// Set Level Info Pane
void game_select_set_info_pane(s32 id, s32 state, s32 delay) {
    game_select_clear_info_pane();
    if (id < 0) {
        gGameSelect->infoPaneTask = INFO_PANE_TASK_NONE;
    } else {
        gGameSelect->infoPaneLevelID = id;
        gGameSelect->infoPaneLevelState = state;
        gGameSelect->infoPaneDelay = delay;
        gGameSelect->infoPaneLevelData = &level_data_table[id];
        gGameSelect->infoPaneTask = INFO_PANE_TASK_DELAY;
    }
}


// Update Level Info Pane
void game_select_update_info_pane(void) {
    game_select_process_info_pane();
    text_printer_update(gGameSelect->infoPaneDesc);
}


// Calculate Flow
u32 game_select_calculate_flow(u32 *modifierReq, u32 *averageReq) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    s24_8 completionModifier;
    u32 modifiedScore;
    u32 totalGames = 0;
    u32 totalScore = 0;
    u32 i;

    for (i = 0; i < ALL_LEVELS; i++) {
        u32 score = get_level_score(saveData, i);

        if (score != DEFAULT_LEVEL_SCORE) {
            totalGames++;
            totalScore += score;
        }
    }

    if (totalGames == 0) {
        return 0;
    }

    // Min = 0.7 (0 levels played)
    // Max = 1.4 (48 levels played)
    completionModifier = INT_TO_FIXED((ALL_RHYTHM_GAMES + totalGames) * 7) / (ALL_RHYTHM_GAMES * 10);

    // Min = 0 (0 * 0.7)
    // Max = 1400 (1000 * 1.4)
    modifiedScore = FIXED_TO_INT(completionModifier * totalScore) / totalGames;

    if (modifierReq != NULL) {
        *modifierReq = completionModifier;
    }

    if (averageReq != NULL) {
        *averageReq = totalScore / totalGames;
    }

    return modifiedScore;
}


// Unused Flow Calculation
u32 game_select_calculate_flow_old(void) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    s24_8 completionModifier;
    u32 baseScore;
    u32 totalGames = 0;
    u32 totalScore = 0;
    u32 i;

    for (i = 0; i < ALL_LEVELS; i++) {
        u32 score = get_level_score(saveData, i);

        if (score != DEFAULT_LEVEL_SCORE) {
            totalGames++;
            totalScore += score;
        }
    }

    if (totalGames == 0) {
        return 0;
    }

    // Min = 0.7 (0-3 levels played)
    // Max = 1.4 (28+ levels played)
    completionModifier = INT_TO_FIXED(0.7) + (INT_TO_FIXED(clamp_int32(totalGames - 3, 0, 25) * 7) / (25 * 10));

    // Min =  30 (avg. score <= 300)
    // Max = 100 (avg. score >= 995)
    baseScore = clamp_int32((5 + (totalScore / totalGames)) / 10, 30, 100);

    // Min =  21 ( 30 * 0.7)
    // Max = 140 (100 * 1.4)
    return FIXED_TO_INT(baseScore * completionModifier);
}


// Update Scores
u32 game_select_update_scores(void) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    struct FlowDisplay *flowPane = &gGameSelect->flowDisplay;
    u32 modifier, average;
    u32 prevModScore, newModScore;
    u32 newScore, score, flow;
    u32 medalWasObtained = FALSE;
    u32 newLevelState;
    s32 x, y, levelID;
    u32 i;

    newScore = saveData->recentLevelScore;

    // Arrived from another menu or Staff Credit.
    if (newScore == DEFAULT_LEVEL_SCORE) {
        flowPane->previousScore = D_030046a8->data.currentFlow;
        flowPane->currentScore = D_030046a8->data.currentFlow;
        return 0;
    }

    x = saveData->recentLevelX;
    y = saveData->recentLevelY;
    levelID = get_level_id_from_grid_xy(x, y);
    newLevelState = saveData->recentLevelState;

    if ((get_level_state_from_grid_xy(x, y) < LEVEL_STATE_HAS_MEDAL) && (newLevelState == LEVEL_STATE_HAS_MEDAL)) {
        medalWasObtained = TRUE;
    }
    if (medalWasObtained) {
        prevModScore = game_select_calculate_flow(NULL, NULL);
    }

    // Save new score.
    if (levelID >= 0) {
        score = get_level_score(saveData, levelID);

        if (score == DEFAULT_LEVEL_SCORE) {
            // New scores have a weight of 100%.
            score = newScore;
        } else if (score < newScore) {
            // Improved scores have a weight of 75%.
            score = ((score + (newScore * 3)) / 4);
        } else {
            // Worse scores have a weight of 25%.
            score = ((newScore + (score * 3)) / 4) & 0xFFFFFF;
        }

        set_level_score(saveData, levelID, score);
    }

    saveData->recentLevelScore = DEFAULT_LEVEL_SCORE;
    newModScore = game_select_calculate_flow(&modifier, &average);

    // If a new medal was obtained, but the new flow value would be worse, apply a bonus to all scores and recalculate.
    if (medalWasObtained) {
        if (newModScore < prevModScore) {
            u32 scoreBonus = (INT_TO_FIXED(prevModScore) / modifier) - average + 1;

            for (i = 0; i < ALL_LEVELS; i++) {
                score = get_level_score(saveData, i);

                if (score != DEFAULT_LEVEL_SCORE) {
                    set_level_score(saveData, i, clamp_int32(score + scoreBonus, 0, MAX_LEVEL_SCORE));
                }
            }
        }
        newModScore = game_select_calculate_flow(NULL, NULL);
    }

    flow = newModScore / 10;
    if (flow < 9) {
        flow = 9;
    }

    flowPane->previousScore = saveData->currentFlow;
    flowPane->currentScore = saveData->currentFlow = flow;
}


// Init. Flow Display
void game_select_init_flow_pane(void) {
    struct FlowDisplay *flowPane = &gGameSelect->flowDisplay;
    struct Vector2 *bgOfs = &D_03004b10.BG_OFS[BG_LAYER_1];
    u32 initialScore;
    u32 updateFlow;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(flowPane->digits); i++) {
        flowPane->digits[i] = sprite_create(gSpriteHandler, anim_game_select_flow_num, 10, 212 - (i * 8), 128, 0, 0, 0, 0);
        sprite_set_origin_x_y(gSpriteHandler, flowPane->digits[i], &bgOfs->x, &bgOfs->y);
    }

    flowPane->title = sprite_create(gSpriteHandler, anim_game_select_flow_text, 0, 130, 128, 0, 0, 0, 0);
    sprite_set_origin_x_y(gSpriteHandler, flowPane->title, &bgOfs->x, &bgOfs->y);

    flowPane->arrow = sprite_create(gSpriteHandler, anim_game_select_flow_arrow, 0, 226, 128, 0, 0, 0, 0x8000);
    sprite_set_origin_x_y(gSpriteHandler, flowPane->arrow, &bgOfs->x, &bgOfs->y);

    updateFlow = game_select_update_scores();
    initialScore = flowPane->previousScore;

    if (initialScore > 0) {
        for (i = 0; i < ARRAY_COUNT(flowPane->digits); i++) {
            sprite_set_anim_cel(gSpriteHandler, flowPane->digits[i], ((initialScore != 0) ? (initialScore % 10) : 10));
            initialScore /= 10;
        }
    }

    flowPane->state = (flowPane->currentScore > 0) && updateFlow;
    flowPane->timer = 60;
    if (D_030046a8->data.recentLevelClearedByBarista) {
        flowPane->timer = 180;
    }
}


// Update Flow Display
void game_select_update_flow_pane(void) {
    struct FlowDisplay *flowPane = &gGameSelect->flowDisplay;
    u32 volume, flow, render;
    u32 i;

    switch (flowPane->state) {
        case FLOW_PANE_TASK_WAIT:
            if (--flowPane->timer == 0) {
                flowPane->state = FLOW_PANE_TASK_ROLL;
                flowPane->timer = 120;
                flowPane->counter = 0;
                sprite_set_playback(gSpriteHandler, flowPane->title, 1, 0, 0);
            }
            break;

        case FLOW_PANE_TASK_ROLL:
            if (gGameSelect->sceneState == GS_STATE_DISPLAYING_CAMPAIGN) {
                volume = 100;
            } else {
                volume = 0x100;
                flowPane->timer--;
            }

            if (flowPane->timer == 0) {
                flowPane->state = FLOW_PANE_TASK_FLICKER;
                flowPane->timer = 240;

                sprite_set_playback(gSpriteHandler, flowPane->title, 0, 0, 0);
                sprite_set_anim_cel(gSpriteHandler, flowPane->title, 0);
                flow = flowPane->currentScore;

                for (i = 0; i < ARRAY_COUNT(flowPane->digits); i++) {
                    sprite_set_anim_cel(gSpriteHandler, flowPane->digits[i], ((flow != 0) ? (flow % 10) : 10));
                    flow /= 10;
                }

                sprite_set_anim_cel(gSpriteHandler, flowPane->arrow, 1);
                if (flowPane->previousScore < flowPane->currentScore) {
                    sprite_set_anim_cel(gSpriteHandler, flowPane->arrow, 0);
                }

                if ((flowPane->previousScore > flowPane->currentScore)) {
                    sprite_set_anim_cel(gSpriteHandler, flowPane->arrow, 2);
                }

                play_sound(&s_f_point_stop_seqData);
            } else {
                if ((flowPane->counter & 1) == 0) {
                    sprite_set_anim_cel(gSpriteHandler, flowPane->digits[0], agb_random(10));
                    sprite_set_anim_cel(gSpriteHandler, flowPane->digits[1], agb_random(10));
                    sprite_set_anim_cel(gSpriteHandler, flowPane->digits[2], agb_random((flowPane->timer) ? 10 : 2));

                    if ((flowPane->counter & 3) == 0) {
                        play_sound_w_pitch_volume(&s_f_point_roll_seqData, volume, 0);
                    }
                }
            }
            break;

        case FLOW_PANE_TASK_FLICKER:
            if (--flowPane->timer == 0) {
                flowPane->state = FLOW_PANE_TASK_NONE;

                if (flowPane->previousScore > 0) {
                    sprite_set_visible(gSpriteHandler, flowPane->arrow, TRUE);
                }

                for (i = 0; i < ARRAY_COUNT(flowPane->digits); i++) {
                    sprite_set_visible(gSpriteHandler, flowPane->digits[i], TRUE);
                }
            } else {
                render = (flowPane->timer >> 4) & 1;
                render ^= 1;

                for (i = 0; i < ARRAY_COUNT(flowPane->digits); i++) {
                    sprite_set_visible(gSpriteHandler, flowPane->digits[i], render);
                }

                if (flowPane->previousScore > 0) {
                    sprite_set_visible(gSpriteHandler, flowPane->arrow, render);
                }
            }
            break;
    }

    flowPane->counter++;
}


// Scene Stop
void game_select_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08003f28();
    func_08004058();
    func_08006d80();
    func_08007014(0);
}


// Init. Stub
void game_select_init_stub(void) {
}


// Init. Level Icon Overlays
void game_select_init_icon_overlays(void) {
    u32 i;

    dma3_fill(0, BG_TILESET_BASE(0xA000), 0x20, 0x20, 0x200);

    for (i = 0; level_icon_overlay_data[i] != NULL; i++) {
        game_select_animate_icon(level_icon_overlay_data[i], 2, 1 + (i * 9) + 0x100);
    }
}


// Update Stub
void game_select_update_stub(void) {
}


// Init. Level Icon Overlay Animator Task
struct LevelIconAnimatorTask *game_select_init_icon_animator(struct LevelIconAnimatorTask *inputs) {
    struct LevelIconAnimatorTask *task;

    task = mem_heap_alloc(sizeof(struct LevelIconAnimatorTask));
    task->tilesetBase = inputs->tilesetBase;
    task->texture = inputs->texture;
    task->frameData = inputs->frameData;
    task->size = inputs->size;
    task->currentFrame = 0;
    task->timeUntilNext = task->frameData[1];

    dma3_set(task->texture + (task->frameData[0] * task->size), task->tilesetBase, task->size, 0x20, 0x200);

    return task;
}


// Update Level Icon Overlay Animator Task
u32 game_select_update_icon_animator(struct LevelIconAnimatorTask *task) {
    s32 frame;

    if (--task->timeUntilNext == 0) {
        task->currentFrame++;
        frame = task->frameData[task->currentFrame * 2];

        if (frame == LEVEL_ICON_ANIM_STOP) {
            return TRUE;
        }

        if (frame == LEVEL_ICON_ANIM_LOOP) {
            task->currentFrame = 0;
            frame = task->frameData[0];
        }

        task->timeUntilNext = task->frameData[(task->currentFrame * 2) + 1];
        dma3_set(&task->texture[frame * task->size], task->tilesetBase, task->size, 0x20, 0x200);
    }

    return FALSE;
}


// Start new Level Icon Overlay Animator Task
s32 game_select_start_new_icon_animator(u16 memID, const void *texture, u16 *tilesetBase, u32 size, const s8 *frameData) {
    struct LevelIconAnimatorTask inputs;

    inputs.texture = texture;
    inputs.tilesetBase = tilesetBase;
    inputs.size = size;
    inputs.frameData = frameData;

    return start_new_task(memID, &level_icon_overlay_animator_task, &inputs, NULL, 0);
}


// Animate Level Icon Overlay Texture
s32 game_select_animate_icon(struct GameSelectOverlay *overlay, u32 tilesetNum, u32 baseTileNum) {
    void *tilesetBase = (void *)(VRAMBase + (tilesetNum * 0x4000) + (baseTileNum * 0x20));

    return game_select_start_new_icon_animator(get_current_mem_id(), overlay->texture, tilesetBase, overlay->width * overlay->height * 0x20, overlay->animData);
}


// Write Level Icon Map to 2x2 BG Map Space
void game_select_print_icon_map(u32 baseMapNum, u32 mapSize, u32 tileX, u32 tileY, u32 width, u32 height, u32 tilesPerRow, u32 tileNum, u32 palette) {
    u32 mapX = 0;
    u32 mapY = 0;
    u32 mapNum;
    u16 mapTile;
    u16 *mapDest;
    u32 i, j;

    mapX = tileX >> 5;
    mapY = tileY >> 5;
    tileX &= 0x1F;
    tileY &= 0x1F;

    switch (mapSize) {
        case 0:
            mapNum = 0;
            break;
        case 1:
            mapNum = mapX & 1;
            break;
        case 2:
            mapNum = mapY & 1;
            break;
        case 3:
            mapNum = (mapX & 1) + ((mapY & 1) << 1);
            break;
    }

    mapDest = ((u16 *)VRAMBase) + ((baseMapNum + mapNum) << 10) + tileX + (tileY << 5);
    mapTile = (palette << 12) | tileNum;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            mapDest[j] = (mapTile + j);
        }
        mapDest += 0x20;
        mapTile += tilesPerRow;
    }
}


// Write Level Icon Map
void game_select_print_icon_maps(u32 baseMap, u32 mapSize, u32 tileX, u32 tileY, u32 width, u32 height, u32 tileNum, u32 palette) {
    u32 x, y, w, h, num;

    // MAP 0 - Upper-Left Corner
    if ((tileX < 0x20) && (tileY < 0x20)) {
        if ((tileX + width) > 0x20) {
            w = 0x20 - tileX;
        } else {
            w = width;
        }

        if ((tileY + height) > 0x20) {
            h = 0x20 - tileY;
        } else {
            h = height;
        }

        game_select_print_icon_map(baseMap, mapSize, tileX, tileY, w, h, width, tileNum, palette);
    }

    if (mapSize == 0) {
        return;
    }

    // MAP 1 - Upper-Right Corner
    if ((mapSize & 1) && (tileX + width > 0x20) && (tileX < 0x40) && (tileY < 0x20)) {
        x = tileX;
        num = tileNum;

        w = width;
        if (tileX < 0x20) {
            x = 0x20;
            w += tileX - 0x20;
            num += 0x20 - tileX;
        }
        if (tileX + width > 0x40) {
            w += 0x40 - (tileX + width);
        }

        if (tileY + height > 0x20) {
            h = 0x20 - tileY;
        } else {
            h = height;
        }

        game_select_print_icon_map(baseMap, mapSize, x, tileY, w, h, width, num, palette);
    }

    // MAP 2 - Lower-Left Corner
    if ((mapSize & 2) && (tileX < 0x20) && (tileY + height > 0x20) && (tileY < 0x40)) {
        y = tileY;
        num = tileNum;

        w = 0;
        if (tileX + width > 0x20) {
            w = 0x20 - tileX;
        } else {
            w = width;
        }

        h = height;
        if (tileY < 0x20) {
            y = 0x20;
            h += tileY - 0x20;
            num += width * (0x20 - tileY);
        }
        if (tileY + height > 0x40) {
            h += 0x40 - (tileY + height);
        }

        game_select_print_icon_map(baseMap, mapSize, tileX, y, w, h, width, num, palette);
    }

    // MAP 3 - Lower-Right Corner
    if ((mapSize == 3) && (tileX + width > 0x20) && (tileX < 0x40) && (tileY + height > 0x20) && (tileY < 0x40)) {
        x = tileX;
        y = tileY;
        num = tileNum;

        w = width;
        if (tileX < 0x20) {
            x = 0x20;
            w += tileX - 0x20;
            num += 0x20 - tileX;
        }
        if (tileX + width > 0x40) {
            w += 0x40 - (tileX + width);
        }

        h = height;
        if (tileY < 0x20) {
            y = 0x20;
            h += tileY - 0x20;
            num += width * (0x20 - tileY);
        }
        if (tileY + height > 0x40) {
            h += 0x40 - (tileY + height);
        }

        game_select_print_icon_map(baseMap, mapSize, x, y, w, h, width, num, palette);
    }
}


// Write Level Icon Texture to VRAM
void game_select_print_icon_texture(const void *texture, u32 tileset, u32 tileNum) {
    dma3_set(texture, (void *)(VRAMBase + (tileset * 0x4000) + (tileNum * 0x20)), 0x20 * 3 * 3, 0x20, 0x200);
}


// Init. BG Squares
void game_select_init_squares(void) {
    struct Vector2 *vector;
    s32 x, y;
    u32 i;
    s8 temp;

    x = 544;
    y = 384;

    for (i = 0; i < 16; i++) {
        vector = &gGameSelect->squareVectors[i];
        vector->x = agb_random(x);
        vector->y = agb_random(y);
        gGameSelect->squareSprites[i] = sprite_create_w_attr(gSpriteHandler, anim_game_select_bg_square_large, agb_random(6), 0, 0, 0xC800, -1, 0x7f, 0, 4);
        sprite_set_anim_speed(gSpriteHandler, gGameSelect->squareSprites[i], agb_random(INT_TO_FIXED(1.0)) + INT_TO_FIXED(1.0));
    }

    x *= 2;
    y *= 2;

    for (i = 16; i < ARRAY_COUNT(gGameSelect->squareVectors); i++) {
        vector = &gGameSelect->squareVectors[i];
        vector->x = agb_random(x);
        vector->y = agb_random(y);
        gGameSelect->squareSprites[i] = sprite_create_w_attr(gSpriteHandler, anim_game_select_bg_square_small, agb_random(6), 0, 0, 0xC800, -1, 0x7f, 0, 4);
        sprite_set_anim_speed(gSpriteHandler, gGameSelect->squareSprites[i], agb_random(INT_TO_FIXED(1.0)) + INT_TO_FIXED(1.0));
    }

    D_03004b10.BLDMOD = (BLDMOD_BG0_TGT | BLDMOD_BG1_TGT | BLDMOD_BG2_TGT | BLDMOD_BG3_TGT | BLDMOD_BACKDROP_TGT);
    D_03004b10.COLEV = (COLEV_SRC_PIXEL(16) | COLEV_TGT_PIXEL(16));

    for (i = 0; i < ARRAY_COUNT(gGameSelect->newIconSquares); i++) {
        gGameSelect->newIconSquares[i].active = FALSE;
    }
}


// Update BG Squares
void game_select_update_bg_squares_motion(s32 dx, s32 dy) {
    struct Vector2 *vector;
    s32 x, y, x2, y2;
    u32 i;

    x = 272;
    y = 192;
    x2 = x * 2;
    y2 = y * 2;

    // Large Squares
    for (i = 0; i < 16; i++) {
        vector = &gGameSelect->squareVectors[i];
        vector->x += dx;
        vector->y += dy;

        if (vector->x < 0) {
            vector->x = x2;
            vector->y = agb_random(y2);
        }
        if (vector->x > x2) {
            vector->x = 0;
            vector->y = agb_random(y2);
        }
        if (vector->y < 0) {
            vector->x = agb_random(x2);
            vector->y = y2;
        }
        if (vector->y > y2) {
            vector->x = agb_random(x2);
            vector->y = 0;
        }

        sprite_set_x_y(gSpriteHandler, gGameSelect->squareSprites[i], 120 + ((vector->x - x) >> 1), 80 + ((vector->y - y) >> 1));
    }

    x = x2;
    y = y2;
    x2 = x * 2;
    y2 = y * 2;

    // Small Squares
    for (i = 16; i < ARRAY_COUNT(gGameSelect->squareVectors); i++) {
        vector = &gGameSelect->squareVectors[i];
        vector->x += dx;
        vector->y += dy;

        if (vector->x < 0) {
            vector->x = x2;
            vector->y = agb_random(y2);
        }
        if (vector->x > x2) {
            vector->x = 0;
            vector->y = agb_random(y2);
        }
        if (vector->y < 0) {
            vector->x = agb_random(x2);
            vector->y = y2;
        }
        if (vector->y > y2) {
            vector->x = agb_random(x2);
            vector->y = 0;
        }

        sprite_set_x_y(gSpriteHandler, gGameSelect->squareSprites[i], SCREEN_CENTER_X + ((vector->x - x) >> 2), SCREEN_CENTER_Y + ((vector->y - y) >> 2));
    }
}


// Spawn New Icon Square
void game_select_spawn_icon_square(s16 x, s16 y, void *onFinish, s32 onFinishArg, u32 delay) {
    struct NewIconSquare *shadow = gGameSelect->newIconSquares;
    s32 x1, y1, x2, y2;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gGameSelect->newIconSquares); i++) {
        if (!shadow->active) {
            break;
        }
        shadow++;
    }

    if (i >= ARRAY_COUNT(gGameSelect->newIconSquares)) {
        return;
    }

    x2 = 20 + (x * 40);
    y1 = (4 + (y * 3)) * 8;
    y2 = y1 + 12;
    x1 = x2 + agb_random(200);

    x1 -= 200;
    y1 -= 188;

    shadow->sprite = sprite_create(gSpriteHandler, anim_game_select_bg_square_large, 0, x1, y1, 0x479C, 1, 0, 0x8000);
    sprite_set_anim_speed(gSpriteHandler, shadow->sprite, INT_TO_FIXED(2.0));
    sprite_set_base_palette(gSpriteHandler, shadow->sprite, 1);
    game_select_link_sprite_xy_to_bg(shadow->sprite);
    shadow->xIn = x;
    shadow->yIn = y;
    shadow->x1 = x1;
    shadow->y1 = y1;
    shadow->x2 = x2;
    shadow->y2 = y2;
    shadow->progress = INT_TO_FIXED(1.0);
    shadow->onFinish = onFinish;
    shadow->onFinishArg = onFinishArg;
    shadow->delay = delay;
    shadow->active = TRUE;
}


// Update New Icon Square
void game_select_update_icon_square(struct NewIconSquare *shadow) {
    s32 x, y;

    if (!shadow->active) {
        return;
    }

    if (shadow->delay > 0) {
        shadow->delay--;
        return;
    }

    if (shadow->progress != 0) {
        x = math_lerp(shadow->x2, shadow->x1, shadow->progress, INT_TO_FIXED(1.0));
        y = math_lerp(shadow->y2, shadow->y1, shadow->progress, INT_TO_FIXED(1.0));
        sprite_set_x_y(gSpriteHandler, shadow->sprite, x, y);
        sprite_set_visible(gSpriteHandler, shadow->sprite, TRUE);
        shadow->progress = FIXED_POINT_MUL(INT_TO_FIXED(0.9), shadow->progress);
        return;
    }

    if (shadow->onFinish != NULL) {
        shadow->onFinish(shadow->onFinishArg);
    }

    sprite_set_base_palette(gSpriteHandler, shadow->sprite, 0);
    sprite_set_anim_speed(gSpriteHandler, shadow->sprite, INT_TO_FIXED(1.0));
    sprite_set_anim(gSpriteHandler, shadow->sprite, anim_game_select_clear_game, 0, 1, 0, 3);
    sprite_set_x_y_z(gSpriteHandler, shadow->sprite, shadow->x2 - 12, shadow->y2 - 12, 0x4864);
    play_sound(&s_f_appear_game_seqData);
    shadow->active = FALSE;
}


// Update New Icon Squares
void game_select_update_icon_squares(void) {
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gGameSelect->newIconSquares); i++) {
        game_select_update_icon_square(&gGameSelect->newIconSquares[i]);
    }
}


// Check for Active New Icon Squares
u32 game_select_check_for_icon_squares(void) {
    struct NewIconSquare *shadow = gGameSelect->newIconSquares;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(gGameSelect->newIconSquares); i++) {
        if (shadow->active) {
            return TRUE;
        }
        shadow++;
    }

    return FALSE;
}


// Update BG Squares
void game_select_update_bg_squares(s32 dx, s32 dy) {
    game_select_update_bg_squares_motion(dx, dy);
}

void game_select_clear_bg_tiles(u32 baseMap, u32 mapSize, u32 tileX, u32 tileY, u32 width, u32 height, u32 tileNum, u32 palette) {
    u32 mapX, mapY, mapNum;
    u16 mapTile;
    u16 *mapDest;
    u16 *newMapDest;
    u32 i, j;

    mapX = tileX >> 5;
    mapY = tileY >> 5;
    tileX &= 0x1F;
    tileY &= 0x1F;

    switch (mapSize) {
        case 0:
            mapNum = 0;
            break;
        case 1:
            mapNum = mapX & 1;
            break;
        case 2:
            mapNum = mapY & 1;
            break;
        case 3:
            mapNum = (mapX & 1) + ((mapY & 1) << 1);
            break;
        default:
            mapNum = 0;
            break;
    }

    mapDest = ((u16 *)VRAMBase) + ((baseMap + mapNum) << 10) + tileX + (tileY << 5);
    mapTile = (palette << 12) | tileNum;

    for (i = 0; i < height; i++) {
        if ((tileY + i) >= 32) {
/*
i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware 
i hate the gba hardware 
i hate the gba hardware i hate the gba hardware 
i hate the gba hardware i hate the gba hardware i hate the gba hardware 
i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware 
i hate the gba hardware i hate the gba hardware i hate the gba hardware i hate the gba hardware https://www.coranac.com/tonc/text/regbg.htm
https://www.coranac.com/tonc/text/regbg.htm
https://www.coranac.com/tonc/text/regbg.htmhttps://www.coranac.com/tonc/text/regbg.htm
https://www.coranac.com/tonc/text/regbg.htmhttps://www.coranac.com/tonc/text/regbg.htm
https://www.coranac.com/tonc/text/regbg.htmhttps://www.coranac.com/tonc/text/regbg.htm
https://www.coranac.com/tonc/text/regbg.htm
*/

            u32 newMapY = (tileY + i) >> 5;
            u32 newTileY = (tileY + i) & 0x1F;
            u32 newMapNum;
            
            switch (mapSize) {
                case 0:
                    newMapNum = 0;
                    break;
                case 1:
                    newMapNum = mapX & 1;
                    break;
                case 2:
                    newMapNum = newMapY & 1;
                    break;
                case 3:
                    newMapNum = (mapX & 1) + ((newMapY & 1) << 1);
                    break;
                default:
                    newMapNum = 0;
                    break;
            }
            
            newMapDest = ((u16 *)VRAMBase) + ((baseMap + newMapNum) << 10) + tileX + (newTileY << 5);
            
            for (j = 0; j < width; j++) {
                if ((tileX + j) < 32) {
                    newMapDest[j] = mapTile;
                }
            }
        } else {
            for (j = 0; j < width; j++) {
                if ((tileX + j) < 32) {
                    mapDest[j] = mapTile;
                }
            }
            mapDest += 0x20;
        }
    }
}