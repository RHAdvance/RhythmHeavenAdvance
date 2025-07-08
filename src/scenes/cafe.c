#include "global.h"
#include "scenes.h"
#include "cafe.h"
#include "graphics/cafe/cafe_graphics.h"

#include "levels.h"
#include "src/scenes/game_select.h"
#include "src/time_keeper.h"


/* CAFE SCENE */


// Set Level Session Play Time
void cafe_session_init_level_playtime(struct LevelPlayActivity *activity) {
    activity->timeOfLastPlay = get_total_playtime(T_MINUTE);
    activity->activeTimeOfLastPlay = get_active_playtime(T_MINUTE);
}


// Init. Level Session
void cafe_session_init_level(struct LevelPlayActivity *activity, s32 levelID) {
    activity->levelID = levelID;
    activity->totalStalePlays = 0;
    activity->justGotPerfect = FALSE;
    cafe_session_init_level_playtime(activity);
}


// Allocate Level Session
struct LevelPlayActivity *cafe_session_alloc_level(s32 levelID) {
    struct LevelPlayActivity *current = gSessionInfo.lastPlayedLevels;
    struct LevelPlayActivity *free = NULL;
    struct LevelPlayActivity *oldest = current;
    s32 i;

    for (i = 0; i < 5; i++, current++) {
        if (current->levelID == levelID) {
            return current;
        }
        if (current->levelID == (u8)LEVEL_NULL) {
            free = current;
        }
        if (current->timeOfLastPlay <= oldest->timeOfLastPlay) {
            oldest = current;
        }
    }

    if (free != NULL) {
        cafe_session_init_level(free, levelID);
        return free;
    } else {
        cafe_session_init_level(oldest, levelID);
        return oldest;
    }
}


// Get Level Session
struct LevelPlayActivity *cafe_session_get_level(s32 levelID) {
    struct LevelPlayActivity *activity = gSessionInfo.lastPlayedLevels;
    s32 i;

    for (i = 0; i < 5; i++, activity++) {
        if (activity->levelID == levelID) {
            return activity;
        }
    }

    return NULL;
}


// Init. Play Session Info
void cafe_session_init(void) {
    u32 i;

    for (i = 0; i < 5; i++) {
        gSessionInfo.lastPlayedLevels[i].levelID = LEVEL_NULL;
    }

    gSessionInfo.unused = 0;
    gSessionInfo.currentFlow = D_030046a8->data.currentFlow;
    gSessionInfo.totalMedals = D_030046a8->data.totalMedals;
    gSessionInfo.timeOfLastCafeVisit = 0;
}


// Add Level to Play Session Info
void cafe_session_add_level(s32 levelID) {
    struct LevelPlayActivity *activity;

    if (levelID < 0) {
        return;
    }

    activity = cafe_session_alloc_level(levelID);

    if (!activity->justGotPerfect) {
        if (activity->totalStalePlays < 255) {
            activity->totalStalePlays++;
        }
        cafe_session_init_level_playtime(activity);
    }
}


// Remove Level from Play Session Info
void cafe_session_remove_level(s32 levelID) {
    struct LevelPlayActivity *activity;

    if (levelID < 0) {
        return;
    }

    activity = cafe_session_get_level(levelID);

    if (activity == NULL) {
        return;
    }

    if (!activity->justGotPerfect) {
        activity->levelID = LEVEL_NULL;
    }
}


// Add Level with Perfect Just Cleared to Session Info
void cafe_session_add_perfect_level(s32 levelID) {
    struct LevelPlayActivity *activity;

    if (levelID < 0) {
        return;
    }

    activity = cafe_session_alloc_level(levelID);
    activity->justGotPerfect = TRUE;
    activity->totalStalePlays = 0;
    cafe_session_init_level_playtime(activity);
}


// Remove Very Old Level Play Activity Sessions
void cafe_session_remove_old_levels(u32 totalPlayTime, u32 inactivityThreshold) {
    u32 i;

    for (i = 0; i < 5; i++) {
        if (gSessionInfo.lastPlayedLevels[i].levelID == (u8)LEVEL_NULL) {
            continue;
        }
        if (totalPlayTime - gSessionInfo.lastPlayedLevels[i].timeOfLastPlay > inactivityThreshold) {
            gSessionInfo.lastPlayedLevels[i].levelID = LEVEL_NULL;
        }
    }
}


// Init. Level Play Activity Indexes
void cafe_session_init_indexes(void) {
    struct LevelPlayActivity *levelSessions = gSessionInfo.lastPlayedLevels;
    u8 *indexes = gCafe->sessionIndexes;
    s32 total = 0;
    s32 older, newer;
    s32 i, j;

    for (i = 0; i < 5; i++) {
        if (levelSessions[i].levelID != (u8)LEVEL_NULL) {
            indexes[total] = i;
            total++;
        }
    }

    gCafe->totalLevelsThisSession = total;

    for (i = 0; i < (total - 1); i++) {
        for (j = (i + 1); j < total; j++) {
            if (levelSessions[indexes[i]].timeOfLastPlay < levelSessions[indexes[j]].timeOfLastPlay) {
                older = indexes[i];
                newer = indexes[j];
                indexes[i] = newer;
                indexes[j] = older;
            }
        }
    }
}


// Init. Session Play Time
void cafe_session_init_playtime(void) {
    s32 playtime = get_total_playtime(T_MINUTE);

    gCafe->timeSinceLastVisit = playtime - gSessionInfo.timeOfLastCafeVisit;
    gSessionInfo.timeOfLastCafeVisit = playtime;
    gCafe->totalPlayTime = playtime;
    gCafe->totalActivePlayTime = get_active_playtime(T_MINUTE);
}


// Remove Level Play Activity with Perfect
void cafe_session_remove_perfect_levels(void) {
    u32 i;

    for (i = 0; i < 5; i++) {
        if (gSessionInfo.lastPlayedLevels[i].justGotPerfect) {
            gSessionInfo.lastPlayedLevels[i].levelID = LEVEL_NULL;
        }
    }
}


// Init. Dialogue Text
void cafe_init_dialogue(void) {
    gCafe->nextDialogueTask = CAFE_EV_INIT_DIALOGUE;
    gCafe->textAdvReady = FALSE;
}


// Start Text Advance Options (Script Function)
void cafe_start_dialogue_inputs(void) {
    struct Animation *anim;
    s16 x, y;

    if (gCafe->disableTextUpdates) {
        return;
    }

    text_printer_get_x_y(gCafe->printer, &x, &y);
    sprite_set_x_y(gSpriteHandler, gCafe->textAdvIcon, x, y);
    sprite_set_visible(gSpriteHandler, gCafe->textAdvIcon, TRUE);

    if (gCafe->queryEnabled) {
        anim = cafe_cursor_option_anim[gCafe->queryResult];
    } else {
        anim = anim_cafe_text_adv_icon;
    }

    sprite_set_anim(gSpriteHandler, gCafe->textAdvIcon, anim, 0, 1, 0, 0);
    gCafe->textAdvReady = TRUE;
    set_pause_beatscript_scene(TRUE);
}


// Update Text Advance Options
void cafe_update_dialogue_inputs(void) {
    if (!cafe_scene_inputs_enabled() || !gCafe->textAdvReady) {
        return;
    }

    if (gCafe->queryEnabled) {
        s8 choice = gCafe->queryResult;

        if (D_03004afc & DPAD_UP) {
            gCafe->queryResult--;
        }
        if (D_03004afc & DPAD_DOWN) {
            gCafe->queryResult++;
        }
        gCafe->queryResult = clamp_int32(gCafe->queryResult, CAFE_OPT_YES, CAFE_OPT_NO);

        if (choice != gCafe->queryResult) {
            sprite_set_anim(gSpriteHandler, gCafe->textAdvIcon, cafe_cursor_option_anim[gCafe->queryResult], 0, 1, 0, 0);
        }
    }

    if (D_03004afc & A_BUTTON) {
        text_printer_set_string(gCafe->printer, NULL);
        sprite_set_visible(gSpriteHandler, gCafe->textAdvIcon, FALSE);
        play_sound(&s_f_cafe_send_mes_seqData);
        gCafe->textAdvReady = FALSE;
        set_pause_beatscript_scene(FALSE);
    }
}


// Check if Barista Can Clear Level
u32 barista_can_clear_level(s32 levelID) {
    u8 *deniedLevels;

    for (deniedLevels = cafe_barista_denied_levels; *deniedLevels != (u8)LEVEL_NULL; deniedLevels++) {
        if (levelID == *deniedLevels) {
            return FALSE;
        }
    }

    return TRUE;
}


// Start of Loop (Script Function)
void cafe_print_dialogue(void) {
    struct LevelPlayActivity *activity;
    const char **dialogue;
    const char *string;
    const char *levelName;
    char *s;
    u32 playtime;
    u32 topic;
    u32 i;
    s32 x, y;
    u32 dialogueTask = gCafe->nextDialogueTask;
    u8 dialogueExhausted = FALSE;

    if (gCafe->disableTextUpdates) {
        return;
    }

    gCafe->bgEvent = CAFE_BG_EV_NONE;
    gCafe->textAdvHold = 0;
    gCafe->queryEnabled = FALSE;
    string = NULL;
    dialogue = NULL;

    switch (dialogueTask) {
        case CAFE_EV_INIT_DIALOGUE:
            if (D_030046a8->data.unk28F) {
                D_030046a8->data.unk28F = FALSE;
                dialogue = cafe_dialogue_first_visit;
                break;
            }
            if (D_030046a8->data.unk294[9]) {
                // Oh! You're here, you're here!
                // I've been waiting, you know!!
                string = "\n"
                         "Oh! You're finally here!\n"
                         "I've been waiting for you!\n"
                         "\n";
                cafe_session_remove_perfect_levels();
                D_030046a8->data.unk294[9] = FALSE;
                dialogueTask = CAFE_EV_ALL_CAMPAIGNS_CLEAR_00;
                break;
            }
            if (gCafe->timeSinceLastVisit == 0) {
                dialogue = cafe_dialogue_come_back_later;
                break;
            }

            playtime = gCafe->totalPlayTime;
            if (playtime <= 20) {
                // Are you making progress?
                // Please do your best!
                string = "\n"
                         "Are you enjoying those Rhythm\n"
                         "Games? Keep up the good work!\n"
                         "\n";
            } else if (playtime <= 60) {
                // Aren't you getting tired?
                // Don't forget to rest now and then.
                string = "\n"
                         "Are you getting tired? It's a good\n"
                         "idea to take a break once in a while.\n"
                         "\n";
            } else {
                // You've been at this a while,
                // haven't you? Please rest a little.
                string = "\n"
                         "You've been keeping busy, haven't you?\n"
                         "Wouldn't you like to take a break?\n"
                         "\n";
            }
            dialogueTask = CAFE_EV_START_TOPIC;
            break;

        case CAFE_EV_START_TOPIC:
            topic = CAFE_TOPIC_RANDOM;
            i = 0;

            while ((topic == CAFE_TOPIC_RANDOM) && (i < gCafe->totalLevelsThisSession)) {
                activity = &gSessionInfo.lastPlayedLevels[gCafe->sessionIndexes[i]];

                if (activity->justGotPerfect) {
                    topic = CAFE_TOPIC_CAMPAIGN_CLEAR;
                    continue;
                }

                switch (get_level_state(&D_030046a8->data, activity->levelID)) {
                    case LEVEL_STATE_OPEN:
                        if ((activity->totalStalePlays >= D_030046a8->data.minFailsForBaristaHelp)
                          && barista_can_clear_level(activity->levelID)) {
                            topic = CAFE_TOPIC_TROUBLE_CLEARING_LEVEL;
                        }
                        break;

                    case LEVEL_STATE_CLEARED:
                        if (activity->totalStalePlays > 2) {
                            topic = CAFE_TOPIC_TROUBLE_GETTING_MEDAL;
                        }
                        break;

                    case LEVEL_STATE_HAS_MEDAL:
                        if ((D_030046a8->data.totalPerfects < ALL_PERFECT_CAMPAIGNS)
                          && !get_campaign_cleared(&D_030046a8->data, get_campaign_from_level_id(activity->levelID))
                          && (activity->totalStalePlays > 2)) {
                            topic = CAFE_TOPIC_TROUBLE_CLEARING_CAMPAIGN;
                        }
                        break;
                }

                i++;
            }

            if (topic != CAFE_TOPIC_RANDOM) {
                if ((gCafe->totalPlayTime - activity->timeOfLastPlay) > 20) {
                    topic = CAFE_TOPIC_REMEMBERING;
                }
                levelName = game_select_get_level_name(activity->levelID);
            } else {
                if ((D_030046a8->data.campaignState == CAMPAIGN_STATE_AVAILABLE)
                  && (D_030046a8->data.playsUntilNextCampaign < 3)
                  && !D_030046a8->data.unk291) {
                    levelName = get_level_name_from_campaign(D_030046a8->data.currentCampaign);
                    topic = CAFE_TOPIC_UPCOMING_CAMPAIGN;
                }
            }

            switch (topic) {
                case CAFE_TOPIC_CAMPAIGN_CLEAR:
                    // Was that you on [...]?
                    // I heard you just got a Perfect!?
                    s = gCafe->string;
                    memcpy(s, "", 1);
                    strcat(s, "\n");
                    strcat(s, "So hey, I hear you got a Perfect rating in ");
                    strcat(s, "\0051" "\0015");
                    strcat(s, levelName);
                    strcat(s, "\0054" "\0018" "!\n");
                    string = s;
                    activity->levelID = LEVEL_NULL;
                    dialogueTask = CAFE_EV_CAMPAIGN_CLEAR_00;
                    break;

                case CAFE_TOPIC_TROUBLE_CLEARING_LEVEL:
                    // You're still on [...].
                    // Are you having trouble?
                    s = gCafe->string;
                    memcpy(s, "", 1);
                    strcat(s, "\n");
                    strcat(s, "Has ");
                    strcat(s, "\0051" "\0015");
                    strcat(s, levelName);
                    strcat(s, "\0054" "\0018" "\nbeen giving you some trouble?\n" "\n");
                    string = s;
                    gCafe->levelToClear = activity->levelID;
                    activity->levelID = LEVEL_NULL;
                    dialogueTask = CAFE_EV_OFFER_CLEAR_00;
                    break;

                case CAFE_TOPIC_TROUBLE_GETTING_MEDAL:
                    // Hmm... is [...] giving you trouble earning that medal?
                    s = gCafe->string;
                    memcpy(s, "", 1);
                    strcat(s, "\n");
                    strcat(s, "Hm... about ");
                    strcat(s, "\0051" "\0015");
                    strcat(s, levelName);
                    strcat(s, "\0054" "\0018" "...\n");
                    strcat(s, "Has the medal been giving you some trouble?\n" "\n");
                    string = s;
                    dialogue = cafe_dialogue_keep_trying;
                    activity->levelID = LEVEL_NULL;
                    break;

                case CAFE_TOPIC_TROUBLE_CLEARING_CAMPAIGN:
                    // Rumor has it [...] was doing a perfect campaign.
                    // Weren't you playing it just now?
                    s = gCafe->string;
                    memcpy(s, "", 1);
                    strcat(s, "\n");
                    strcat(s, "So... \n");
                    strcat(s, "\0051" "\0015");
                    strcat(s, levelName);
                    strcat(s, "\0054" "\0018" "\n");
                    strcat(s, "has been keeping you busy, huh?\n"
                              "Can't stop playing it?");
                    string = s;
                    activity->levelID = LEVEL_NULL;
                    dialogueTask = CAFE_EV_CAMPAIGN_ADVICE_00;
                    break;

                case CAFE_TOPIC_REMEMBERING:
                    activity->timeOfLastPlay = gCafe->totalPlayTime;
                    // Ah! Wait, I remember!
                    string = "\n"
                             "\n"
                             "Hey, I just remembered something!\n"
                             "\n";
                    break;

                case CAFE_TOPIC_UPCOMING_CAMPAIGN:
                    // Hey, here's a tip! Soon [...] is going to be having a perfect campaign.
                    s = gCafe->string;
                    memcpy(s, "", 1);
                    strcat(s, "\nSay, I heard that there's a chance\n"
                              "for a Perfect in ");
                    strcat(s, "\0051" "\0015");
                    strcat(s, levelName);
                    strcat(s, "\0054" "\0018" ".\n\n");
                    string = s;
                    dialogueTask = CAFE_EV_UPCOMING_CAMPAIGN_00;
                    D_030046a8->data.unk291 = TRUE;
                    break;

                default:
                    dialogue = cafe_random_conversation_pool[agb_random(10)];
                    break;
            }
            break;

        case CAFE_EV_CAMPAIGN_CLEAR_00:
            string = cafe_dialogue_shouts_praise[agb_random(5)];
            gCafe->bgEvent = CAFE_BG_EV_CHEER_01;
            gCafe->textAdvHold = 4;
            dialogueTask++;
            break;

        case CAFE_EV_CAMPAIGN_CLEAR_01:
            // Please keep on working hard.
            // I'll be here rooting for you~!
            string = "\n"
                     "Keep working hard out there.\n"
                     "I'm rooting for you!\n"
                     "\n";
            dialogueExhausted = TRUE;
            break;

        case CAFE_EV_OFFER_CLEAR_00:
            // If you like, I could let you
            // <skip that game> if you want to...
            //
            // "Please skip it."
            // "No, thank you."
            string = "Because I can make it so you can\n"
                     "just ""\0051" "\0015" "skip that game altogether.\n"
                     "\0054" "\0018" "What do you say?\n"
                     "　　　　　　　　　　　　　　\"Please!\"\n"
                     "　　　　　　　　　　　　　　\"No, thanks.\"";
            gCafe->queryEnabled = TRUE;
            gCafe->queryResult = CAFE_OPT_YES;
            dialogueTask++;
            break;

        case CAFE_EV_OFFER_CLEAR_01:
            if (gCafe->queryResult == CAFE_OPT_YES) {
                // <Leave it to me!>
                string = "\n"
                         "\n"
                         "\0032" "\001l" "\0051" "\0015" "Leave it to me!" "\0030" "\001s" "\0054" "\0018";
                gCafe->textAdvHold = 3;
                gCafe->bgEvent = CAFE_BG_EV_HELPING;
                dialogueTask = CAFE_EV_OFFER_CLEAR_02_Y;
                get_grid_xy_from_level_id(gCafe->levelToClear, &x, &y);
                D_030046a8->data.recentLevelX = x;
                D_030046a8->data.recentLevelY = y;
                D_030046a8->data.recentLevelState = LEVEL_STATE_CLEARED;
                D_030046a8->data.recentLevelClearedByBarista = TRUE;
                D_030046a8->data.minFailsForBaristaHelp = clamp_int32(D_030046a8->data.minFailsForBaristaHelp + 1, 2, 7);
                write_game_save_data();
            } else {
                // Oh, is that so?
                // You're determined to beat
                // it with your own strength.
                // Excellent!
                string = "\n"
                         "That's the spirit! Stay\n"
                         "confident, and stick\n"
                         "to it.";
                dialogueTask = CAFE_EV_OFFER_CLEAR_02_N;
            }
            break;

        case CAFE_EV_OFFER_CLEAR_02_Y:
            // I hope the next game will go
            // much better for you.
            // Tell me about it next time.
            string = "\n"
                     "...And that's done. Hey, maybe the\n"
                     "next couple of games will give you the\n"
                     "edge you need to finish that last one!";
            dialogueExhausted = TRUE;
            break;

        case CAFE_EV_OFFER_CLEAR_02_N:
            // Well then, please
            // do your best!
            string = "\n"
                     "I'll be here, cheering you on from\n"
                     "behind the counter!\n"
                     "\n";
            dialogueExhausted = TRUE;
            break;

        case CAFE_EV_CAMPAIGN_ADVICE_00:
            // Were you practicing for the
            // <Perfect Campaign>?
            //
            //         "That's right."
            //         "Not right now."
            string = "\0054" "\0018" "Are you just practicing so\n"
                     "\0054" "\0018" "you can have a go " "\0051" "\0015" "at\n"
                     "\0051" "\0015" "getting a Perfect?" "\0054" "\0018" "\n"
                     "　　　　　　　　　　　　　\"That's right!\"\n"
                     "　　　　　　　　　　　　　\"I haven't.\"";
            gCafe->queryEnabled = TRUE;
            gCafe->queryResult = CAFE_OPT_YES;
            dialogueTask++;
            break;

        case CAFE_EV_CAMPAIGN_ADVICE_01:
            if (gCafe->queryResult == CAFE_OPT_YES) {
                string = cafe_dialogue_shouts_cheer[agb_random(5)];
                gCafe->textAdvHold = 3;
                gCafe->bgEvent = CAFE_BG_EV_CHEER_02;
                dialogue = cafe_dialogue_practicing_perfect;
            } else {
                dialogue = cafe_dialogue_not_practicing_perfect;
            }
            break;

        case CAFE_EV_UPCOMING_CAMPAIGN_00:
            // Just try your best and
            // go get that Perfect!
            string = "\n"
                     "I think you've got a good\n"
                     "chance of clearing it.\n"
                     "I'll be rooting for you!\n";
            dialogueExhausted = TRUE;
            break;

        case CAFE_EV_ALL_CAMPAIGNS_CLEAR_00:
            // At long last...
            // You have completed
            // the Perfect Campaign!
            string = "\n"
                     "Word on the wind is that you finally\n"
                     "got all Perfects!\n"
                     "...Is that true?";
            dialogueTask++;
            break;

        case CAFE_EV_ALL_CAMPAIGNS_CLEAR_01:
            // Crazy awesome!!
            string = "\0032" "\001l" "\0051" "\0015" "\n"
                     "Now,\n"
                     "that's perfect!" "\0030" "\001s" "\0054" "\0018";
            gCafe->bgEvent = CAFE_BG_EV_CHEER_02;
            gCafe->textAdvHold = 4;
            dialogue = cafe_dialogue_all_perfects_clear;
            break;

        case CAFE_EV_CONTINUE_DIALOGUE:
            string = *gCafe->dialogue;
            if (*(gCafe->dialogue + 1) != NULL) {
                gCafe->dialogue++;
            } else {
                dialogueExhausted = TRUE;
            }
            break;
    }

    if (dialogue != NULL) {
        if (string == NULL) {
            string = *dialogue++;
            if (*dialogue != NULL) {
                gCafe->dialogue = dialogue;
                dialogueTask = CAFE_EV_CONTINUE_DIALOGUE;
            } else {
                dialogueExhausted = TRUE;
            }
        } else {
            gCafe->dialogue = dialogue;
            dialogueTask = CAFE_EV_CONTINUE_DIALOGUE;
        }
    }

    text_printer_show_text(gCafe->printer, TRUE);
    text_printer_set_string(gCafe->printer, string);

    if (dialogueExhausted) {
        beatscript_disable_loops();
    }

    gCafe->nextDialogueTask = dialogueTask;
}


// Get BG Event (Script Function)
s32 cafe_get_bg_event(void) {
    return gCafe->bgEvent;
}


// Show Text Box
void cafe_text_printer_show_box(void) {
    scene_show_bg_layer(BG_LAYER_1);
}


// Hide Text Box
void cafe_text_printer_hide_box(void) {
    scene_hide_bg_layer(BG_LAYER_1);
}


// Init. Text Printer
void cafe_init_text_printer(void) {
    struct TextPrinter *printer;

    printer = text_printer_create_new(get_current_mem_id(), 6, 176, 32);
    text_printer_set_x_y(printer, 32, 64);
    text_printer_set_layer(printer, 0x800);
    text_printer_set_palette(printer, 8);
    text_printer_set_colors(printer, 0);
    text_printer_center_by_content(printer, TRUE);
    text_printer_run_func_on_finish(printer, cafe_text_printer_show_box, 0);
    text_printer_run_func_on_clear(printer, cafe_text_printer_hide_box, 0);
    gCafe->printer = printer;
    gCafe->textAdvIcon = sprite_create(gSpriteHandler, anim_cafe_text_adv_icon, 0, 64, 64, 0x700, 1, 0, 0x8000);
    gCafe->textAdvHold = 0;
}


// Get Text Advance Hold Time (Script Function)
s32 cafe_get_dialogue_hold_time(void) {
    return gCafe->textAdvHold;
}


// Hide Text (Script Function)
void cafe_clear_dialogue(void) {
    scene_hide_bg_layer(BG_LAYER_1);
    text_printer_show_text(gCafe->printer, FALSE);
}


// Init. Static Variables
void cafe_scene_init_memory(void) {
    cafe_session_init();
}


// Init. Graphics 3
void cafe_scene_init_gfx3(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), cafe_buffered_textures);
    run_func_after_task(task, set_pause_beatscript_scene, FALSE);
}


// Init. Graphics 2
void cafe_scene_init_gfx2(void) {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), cafe_gfx_table, 0x3000);
    run_func_after_task(task, cafe_scene_init_gfx3, 0);
}


// Init. Graphics 1
void cafe_scene_init_gfx1(void) {
    schedule_function_call(get_current_mem_id(), cafe_scene_init_gfx2, 0, 2);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, FALSE, 0, 0, 0, 29, BGCNT_PRIORITY(1));
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 0, 30, BGCNT_PRIORITY(2));
}


// Scene Start
void cafe_scene_start(void *sVar, s32 dArg) {
    func_08007324(FALSE);
    func_080073f0();
    cafe_scene_init_gfx1();
    cafe_init_text_printer();
    cafe_init_dialogue();
    cafe_session_init_playtime();
    cafe_session_remove_old_levels(gCafe->totalPlayTime, 60);
    cafe_session_init_indexes();

    gCafe->inputsEnabled = FALSE;
    gCafe->disableTextUpdates = FALSE;
    gCafe->levelToClear = LEVEL_NULL;
}


// Scene Update (Paused)
void cafe_scene_paused(void *sVar, s32 dArg) {
}


// Scene Update (Active)
void cafe_scene_update(void *sVar, s32 dArg) {
    if (cafe_scene_inputs_enabled()) {
        cafe_update_dialogue_inputs();
    }

    text_printer_update(gCafe->printer);
}


// Check if Scene Can Receive Inputs
u32 cafe_scene_inputs_enabled(void) {
    if (gCafe->inputsEnabled) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Load BG Event Map (Script Function)
void cafe_load_bg_event_map(struct CompressedData *map) {
    func_08003eb8(map, (VRAMBase + 0xF000));
}


// Scene Stop
void cafe_scene_stop(void *sVar, s32 dArg) {
    func_08008628();
    func_08004058();
}
