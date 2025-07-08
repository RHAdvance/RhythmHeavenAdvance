#include "global.h"
#include "results.h"
#include "graphics/results/results_graphics.h"

#include "levels.h"
#include "cues.h"
#include "src/scenes/game_select.h"

const struct MarkingCriteria *genericMarkingCriteria[] = {
    NULL,
};

/* RESULTS */


#define COMMENT_PALETTE 4
#define EXTRA_COMMENT_PALETTE 2
#define RANK_COMMENT_LINE_SPACING 16
#define RANK_EXTRA_COMMENT_MARGIN 8
#define MAX_POINTS_PER_INPUT 10
#define POINTS_LOST_PER_MISS -20
#define COMMENT_BASE_LINE 8
#define COMMENT_TILE_Y(line) ((COMMENT_BASE_LINE * 2) + ((line) * 2))


static struct ScoreHandler sScoreHandler; // Global Score Handler
static u8 D_03001540; // Update save data upon reaching leaving scene.


// [D_089d7980] Main Score Handler
struct ScoreHandler *score_handler = &sScoreHandler;


#include "data/scenes/results/data.inc.c"


// Set D_03001540
void results_set_enable_save(u32 updateSave) {
    D_03001540 = updateSave;
}


// Return TRUE (used in the Perfect Certificate scene, likely for development purposes)
u32 results_campaign_is_enabled(void) {
    return TRUE;
}


 // Save Result
void results_save_to_cart(u32 levelState) {
    struct TengokuSaveData *saveData = &D_030046a8->data;
    s32 levelID;

    if (!D_03001540) {
        return;
    }

    saveData->recentLevelState = levelState;
    saveData->recentLevelScore = results_calculate_final_score();

    levelID = get_level_id_from_grid_xy(saveData->recentLevelX, saveData->recentLevelY);
    cafe_session_add_level(levelID);

    if (levelID >= 0) {
        set_level_total_plays(saveData, levelID, get_level_total_plays(saveData, levelID) + 1);
    }

    flush_save_buffer_to_sram();
}


// Get Animation for Comment Text
struct Animation *results_get_comment_anim(const char *comment, u32 anchor, u32 colors) {
    struct Animation *anim;

    if ((COMMENT_TILE_Y(gResults->currentLine) < 0) || (COMMENT_TILE_Y(gResults->currentLine) >= 32)) {
        return NULL;
    }

    anim = text_printer_get_unformatted_line_anim(get_current_mem_id(), 0, COMMENT_TILE_Y(gResults->currentLine), TEXT_PRINTER_FONT_SMALL, comment, anchor, colors, 256);
    gResults->currentLine++;
    return anim;
}


// Initialise Input Tracker
void results_init_tracker(struct InputScoreTracker *tracker) {
    tracker->totalInputs = 0;
    tracker->totalHits = 0;
    tracker->totalBarelies = 0;
    tracker->totalEarliness = 0;
    tracker->totalLateness = 0;
}


// Initialise Cue Input Trackers and Marking Criteria
void results_init_cue_tracking(void) {
    u32 i;

    score_handler->markingData = NULL;

    for (i = 0; i < ARRAY_COUNT(score_handler->cueInputTrackers); i++) {
        results_init_tracker(&score_handler->cueInputTrackers[i]);
    }
}


// Initialise Results Handler
void results_init_score_handler(void) {
    u32 i;

    score_handler->unk0_b0 = FALSE;
    score_handler->totalRecoveries = 0;
    score_handler->prevInputLevel = -1;
    score_handler->totalIrrelevantInputs = 0;

    for (i = 0; i < ARRAY_COUNT(score_handler->anyInputTrackers); i++) {
        results_init_tracker(&score_handler->anyInputTrackers[i]);
    }

    results_init_cue_tracking();
    score_handler->headerText = NULL;
    score_handler->totalPoints = 0;
    score_handler->maximumPoints = 0;
}


// Import Criteria (Script Event)
void results_import_marking_criteria(const struct MarkingCriteria **markingData) {
    score_handler->markingData = markingData;
}


// Set Header Text (Script Event)
void results_set_header(char *headerText) {
    score_handler->headerText = headerText;
}


// Assess Inputs (Script Event)
void results_enable_input_tracking(u32 assess) {
    score_handler->markingInputs = assess;
}


// Check if Assessing Inputs
u32 results_tracking_is_enabled(void) {
    return score_handler->markingInputs;
}


// Register Input
void results_register_input(u32 criterion, u32 level, s32 offset) {
    struct InputScoreTracker *tracker = &score_handler->anyInputTrackers[criterion];
    s32 points;

    if (!score_handler->markingInputs) {
        return;
    }

    if (level == CUE_RESULT_NONE) {
        score_handler->totalIrrelevantInputs++;
        return;
    }

    tracker->totalInputs++;
    points = 0;

    switch (level) {
        case CUE_RESULT_HIT:
            tracker->totalHits++;
            if (score_handler->prevInputLevel == CUE_RESULT_MISS) {
                score_handler->totalRecoveries++;
            }
            points = MAX_POINTS_PER_INPUT - ABS(offset) + 1;
            break;
        case CUE_RESULT_BARELY:
            tracker->totalBarelies++;
            if (score_handler->prevInputLevel == CUE_RESULT_MISS) {
                score_handler->totalRecoveries++;
            }
            points = MAX_POINTS_PER_INPUT - ABS(offset);
            break;
        case CUE_RESULT_MISS:
            offset = 0;
            points = POINTS_LOST_PER_MISS;
            break;
    }

    if (points > MAX_POINTS_PER_INPUT) points = MAX_POINTS_PER_INPUT;
    score_handler->totalPoints += points;
    score_handler->maximumPoints += MAX_POINTS_PER_INPUT;

    if (offset < 0) {
        tracker->totalEarliness -= offset;
    } else {
        tracker->totalLateness += offset;
    }

    score_handler->prevInputLevel = level;
}


// Register Input for Cue
void results_register_cue_input(u32 criterion, u32 level, s32 offset) {
    struct InputScoreTracker *tracker = &score_handler->cueInputTrackers[criterion];

    if (!score_handler->markingInputs) {
        return;
    }

    tracker->totalInputs++;

    switch (level) {
        case CUE_RESULT_HIT:
            tracker->totalHits++;
            break;
        case CUE_RESULT_BARELY:
            tracker->totalBarelies++;
            break;
        case CUE_RESULT_MISS:
            offset = 0;
            break;
    }

    if (offset < 0) {
        tracker->totalEarliness -= offset;
    } else {
        tracker->totalLateness += offset;
    }
}


// Calculate Input Averages
void results_tracker_calculate_averages(struct InputScoreTracker *tracker) {
    tracker->totalMisses = tracker->totalInputs - (tracker->totalHits + tracker->totalBarelies);

    if (tracker->totalInputs == 0) return;

    tracker->avgHits = Div(INT_TO_FIXED(tracker->totalHits), tracker->totalInputs);
    tracker->avgBarelies = Div(INT_TO_FIXED(tracker->totalBarelies), tracker->totalInputs);
    tracker->avgMisses = Div(INT_TO_FIXED(tracker->totalMisses), tracker->totalInputs);

    if (tracker->totalInputs == tracker->totalMisses) return;

    tracker->avgEarliness = Div(INT_TO_FIXED(tracker->totalEarliness), tracker->totalInputs - tracker->totalMisses);
    tracker->avgLateness = Div(INT_TO_FIXED(tracker->totalLateness), tracker->totalInputs - tracker->totalMisses);
}


// DEBUG Calculate Skill Tracker Averages
void results_tracker_calculate_skill_averages(void) {
    struct InputScoreTracker *globalInputs = &score_handler->anyInputTrackers[3];
    u32 i;

    for (i = 0; i < 3; i++) {
        results_tracker_calculate_averages(&score_handler->anyInputTrackers[i]);
        globalInputs->totalInputs += score_handler->anyInputTrackers[i].totalInputs;
        globalInputs->totalHits += score_handler->anyInputTrackers[i].totalHits;
        globalInputs->totalBarelies += score_handler->anyInputTrackers[i].totalBarelies;
        globalInputs->totalEarliness += score_handler->anyInputTrackers[i].totalEarliness;
        globalInputs->totalLateness += score_handler->anyInputTrackers[i].totalLateness;
    }

    results_tracker_calculate_averages(&score_handler->anyInputTrackers[3]);
}


// DEBUG Render Skill Assessment
void results_render_skills(struct ResultsSkillData *data) {
    u32 scoreSum, weightSum;
    s32 y;
    u32 i;

    y = 40;
    scoreSum = 0;
    weightSum = 0;

    for (i = 0; data[i].descPool != NULL; i++) {
        struct PrintedTextAnim *textAnim;
        u32 total, grade;

        total = 0;
        while (data[i].descPool[total] != NULL) {
            total++;
        }

        textAnim = bmp_font_obj_print_r(gResults->objFont, data[i].descPool[agb_random(total)], 1, 7);
        sprite_create(gSpriteHandler, textAnim->frames, 0, 176, y, 0x4800, 1, 0, 0);

        grade = score_handler->skillScores[i] = clamp_int32(data[i].measure(), RESULTS_GRADE_D, RESULTS_GRADE_S);
        scoreSum += data[i].weight * grade;
        weightSum += data[i].weight;

        textAnim = bmp_font_obj_print_l(gResults->objFont, results_letter_ranks[grade], 1, 7);
        sprite_create(gSpriteHandler, textAnim->frames, 0, 192, y, 0x4800, 1, 0, 0);

        y += 16;
    }

    score_handler->avgSkillScore = Div(INT_TO_FIXED(scoreSum), weightSum * RESULTS_GRADE_S);
}


// DEBUG Measure Skill - Accuracy
u32 results_measure_skill_accuracy(void) {
    struct InputScoreTracker *inputs = &score_handler->anyInputTrackers[3];
    u32 accuracy;
    u32 grade, hitGrade;

    accuracy = inputs->avgEarliness + inputs->avgLateness;
    grade = RESULTS_GRADE_D;

    if (accuracy < INT_TO_FIXED(4 + 0.25)) {
        grade = RESULTS_GRADE_C;
    }

    if (accuracy < INT_TO_FIXED(3 + 0.25)) {
        grade = RESULTS_GRADE_B;
    }

    if (accuracy < INT_TO_FIXED(2 + 0.25)) {
        grade = RESULTS_GRADE_A;
    }

    if (accuracy < INT_TO_FIXED(1 + 0.25)) {
        grade = RESULTS_GRADE_S;
    }

    if (inputs->totalBarelies != 0 && grade == RESULTS_GRADE_S) {
        grade = RESULTS_GRADE_A;
    }

    hitGrade = results_measure_skill_hit_avg();

    if (grade > hitGrade) {
        grade = hitGrade;
    }

    return grade;
}


// DEBUG Measure Skill - Barelies (Tracker 2)
u32 results_measure_skill_barely_trk2(void) {
    struct InputScoreTracker *inputs = &score_handler->anyInputTrackers[2];
    struct InputScoreTracker *globalInputs = &score_handler->anyInputTrackers[3];
    u32 grade;

    if (globalInputs->avgMisses > INT_TO_FIXED(0.75)) {
        return RESULTS_GRADE_D;
    }

    grade = RESULTS_GRADE_D;

    if (inputs->totalBarelies < 8) {
        grade = RESULTS_GRADE_C;
    }

    if (inputs->totalBarelies < 4) {
        grade = RESULTS_GRADE_B;
    }

    if (globalInputs->totalMisses == 0 && inputs->totalBarelies == 0) {
        grade = RESULTS_GRADE_A;

        if (inputs->avgEarliness + inputs->avgLateness < INT_TO_FIXED(1.25)) {
            grade = RESULTS_GRADE_S;
        }
    }

    return grade;
}


// DEBUG Measure Skill - Barelies (Tracker 1)
u32 results_measure_skill_barely_trk1(void) {
    struct InputScoreTracker *inputs = &score_handler->anyInputTrackers[1];
    struct InputScoreTracker *globalInputs = &score_handler->anyInputTrackers[3];
    u32 grade;

    if (globalInputs->avgMisses > INT_TO_FIXED(0.75)) {
        return RESULTS_GRADE_D;
    }

    grade = RESULTS_GRADE_D;

    if (inputs->totalBarelies < 8) {
        grade = RESULTS_GRADE_C;
    }

    if (inputs->totalBarelies < 4) {
        grade = RESULTS_GRADE_B;
    }

    if (globalInputs->totalMisses == 0 && inputs->totalBarelies == 0) {
        grade = RESULTS_GRADE_A;

        if (inputs->avgEarliness + inputs->avgLateness < INT_TO_FIXED(1.25)) {
            grade = RESULTS_GRADE_S;
        }
    }

    return grade;
}


// DEBUG Measure Skill - Hits
u32 results_measure_skill_hit_avg(void) {
    struct InputScoreTracker *inputs = &score_handler->anyInputTrackers[3];
    u32 hits;

    if (inputs->avgMisses > INT_TO_FIXED(0.75)) {
        return RESULTS_GRADE_D;
    }

    hits = Div(INT_TO_FIXED(inputs->totalHits), inputs->totalInputs);

    if (hits >= INT_TO_FIXED(1.000)) {
        return RESULTS_GRADE_S;
    }

    if (hits >= INT_TO_FIXED(0.960)) {
        return RESULTS_GRADE_A;
    }

    if (hits >= INT_TO_FIXED(0.900)) {
        return RESULTS_GRADE_B;
    }

    if (hits >= INT_TO_FIXED(0.785)) {
        return RESULTS_GRADE_C;
    }

    return RESULTS_GRADE_D;
}


// DEBUG Measure Skill - Irrelevant Inputs
u32 results_measure_skill_irrelevant_inputs(void) {
    switch (score_handler->totalIrrelevantInputs) {
        case 0:
            return RESULTS_GRADE_A;
        case 1:
            return RESULTS_GRADE_B;
        case 2:
            return RESULTS_GRADE_C;
        default:
            return RESULTS_GRADE_D;
    }
}


// DEBUG Measure Skill - Accuracy (Lenient)
u32 results_measure_skill_accuracy_lenient(void) {
    struct InputScoreTracker *inputs = &score_handler->anyInputTrackers[3];
    u32 accuracy;
    u32 grade;

    if (inputs->avgMisses > INT_TO_FIXED(0.75)) {
        return RESULTS_GRADE_D;
    }

    accuracy = inputs->avgEarliness + inputs->avgLateness;
    grade = RESULTS_GRADE_D;

    if (accuracy < INT_TO_FIXED(7 + 0.25)) {
        grade = RESULTS_GRADE_C;
    }

    if (accuracy < INT_TO_FIXED(5 + 0.25)) {
        grade = RESULTS_GRADE_B;
    }

    if (accuracy < INT_TO_FIXED(3 + 0.25)) {
        grade = RESULTS_GRADE_A;
    }

    if (accuracy < INT_TO_FIXED(1 + 0.25)) {
        grade = RESULTS_GRADE_S;
    }

    return grade;
}


// DEBUG Measure Skill - Misses
u32 results_measure_skill_miss(void) {
    struct InputScoreTracker *inputs = &score_handler->anyInputTrackers[3];

    if (inputs->avgMisses > INT_TO_FIXED(0.75)) {
        return RESULTS_GRADE_D;
    }

    if (inputs->totalMisses < 4) {
        return RESULTS_GRADE_A;
    }

    if (inputs->totalMisses < 6) {
        return RESULTS_GRADE_B;
    }

    if (inputs->totalMisses < 8) {
        return RESULTS_GRADE_C;
    }

    return RESULTS_GRADE_D;
}


// DEBUG Measure Skill - Misses (Tracker 2)
u32 results_measure_skill_miss_trk2(void) {
    struct InputScoreTracker *inputs = &score_handler->anyInputTrackers[2];
    struct InputScoreTracker *globalInputs = &score_handler->anyInputTrackers[3];

    if (globalInputs->avgMisses > INT_TO_FIXED(0.75)) {
        return RESULTS_GRADE_D;
    }

    if (inputs->totalMisses < 1) {
        return RESULTS_GRADE_A;
    }

    if (inputs->totalMisses < 3) {
        return RESULTS_GRADE_B;
    }

    if (inputs->totalMisses < 5) {
        return RESULTS_GRADE_C;
    }

    return RESULTS_GRADE_D;
}


// DEBUG Measure Skill - Random
u32 results_measure_skill_random(void) {
    return agb_random(5);
}


// DEBUG Load Results (Script Function)
void results_render_skill_screen(void) {
    struct InputScoreTracker *inputs = &score_handler->anyInputTrackers[3];
    struct PrintedTextAnim *textAnim;
    char scoreString[0x20];
    char numString[0x20];
    u32 badInputScore, score, level;

    textAnim = bmp_font_obj_print_c(gResults->objFont, ":1" "––––" ":0" "@@‚f‚’‚‚„‚…@@" ":1" "––––", 0, 7);
    sprite_create(gSpriteHandler, textAnim->frames, 0, 120, 16, 0x4800, 1, 0, 0);

    results_tracker_calculate_skill_averages();
    badInputScore = (inputs->totalMisses * 10) + (inputs->totalBarelies * 3);

    level = 2;
    if (badInputScore >= 10) {
        level = 1;
    }
    if (badInputScore >= 30) {
        level = 0;
    }

    switch (level) {
        case 0:
            results_render_skills(results_skill_data_low);
            break;
        case 1:
            results_render_skills(results_skill_data_mid);
            break;
        case 2:
            results_render_skills(results_skill_data_high);
            break;
    }

    score = FIXED_TO_INT(score_handler->avgSkillScore * 30);
    score -= score_handler->totalIrrelevantInputs * 3;
    score = 70 + clamp_int32(score, 0, 30);
    score -= inputs->totalMisses * 10;
    score = clamp_int32(score, 0, 100);

    if (score == 0) {
        if (inputs->totalHits != 0 || inputs->totalBarelies != 0) {
            score = FIXED_TO_INT(inputs->avgHits * 10);
            score += FIXED_TO_INT(inputs->avgBarelies * 3);
            score = clamp_int32(score, 1, 10) + agb_random(3);
        }
    }

    strintf(numString, score);
    memcpy(scoreString, ".5:1" "‚q|‚h‚p@@" ".6:0", 21);
    strcat(scoreString, numString);

    textAnim = bmp_font_obj_print_r(gResults->objFont, scoreString, 0, 0);
    sprite_create(gSpriteHandler, textAnim->frames, 0, 204, 144, 0x4800, 0, 0, 0);
}


// Prepare Negative Remarks (return total failed criteria)
u32 results_get_negative_comments(void) {
    const struct MarkingCriteria **criteriaTable = score_handler->markingData;
    struct InputScoreTracker *tracker;
    const char *comments[3];
    char *commentsText;
    u32 totalFailed = 0;
    u32 i;
    u16 *commentSprites;

    tracker = score_handler->cueInputTrackers;
    commentSprites = gResults->commentSprites;
    commentsText = gResults->negativeCommentsText;
    gResults->singleCommentTryAgain = FALSE;

    for (criteriaTable; *criteriaTable != NULL; tracker++, criteriaTable++) {
        const struct MarkingCriteria *criteria;
        u32 checkAvgHits, overrideOtherComments;
        u32 failedThisCriterion;

        if (tracker->totalInputs == 0) {
            continue;
        }

        failedThisCriterion = FALSE;
        criteria = *criteriaTable;
        checkAvgHits = criteria->flags & ~0x80;
        overrideOtherComments = criteria->flags & 0x80;

        if (!criteria->checkAverageMisses) {
            if (tracker->totalMisses <= criteria->maxMissesBeforeFail) {
                goto label7A; // :vomit_emoji:
            }
        } else {
            if (tracker->avgMisses > criteria->maxMissesBeforeFail) {
                failedThisCriterion = TRUE;
            }

            label7A:
            if (!failedThisCriterion) {
                if ((checkAvgHits == TRUE) && (tracker->avgHits < criteria->minHitsBeforeFail)) {
                    failedThisCriterion = TRUE;
                }

                if (!failedThisCriterion) {
                    continue;
                }
            }
        }

        if (overrideOtherComments) {
            gResults->singleCommentTryAgain = TRUE;
            comments[0] = criteria->negativeRemark;
            totalFailed = 1;
            break;
        }

        comments[totalFailed] = criteria->negativeRemark;
        totalFailed++;
        if (totalFailed > 2) {
            break;
        }
    }

    for (i = 0; i < totalFailed; i++) {
        struct Animation *anim;
        u16 sprite;
        size_t prefixLength = 0;

        strcpy(commentsText, results_try_again_comment_pool[clamp_int32(i, 0, 2)]);
        strcat(commentsText, comments[i]);
        prefixLength = strlen(commentsText) - strlen(comments[i]);
        
        // Convert the first character of the statement to lowercase if it's uppercase
        // An exception is made for sentences starting in the word "I" and contractions like "I'm"
        if (commentsText[prefixLength] >= 'A' && commentsText[prefixLength] <= 'Z' && results_try_again_comment_pool[i] != "" && !(commentsText[prefixLength] == 'I' && (commentsText[prefixLength+1] == ' ' || commentsText[prefixLength+1]  == '\''))) {
            commentsText[prefixLength] += 32;
        }
        anim = results_get_comment_anim(commentsText, TEXT_ANCHOR_BOTTOM_LEFT, 3);
        sprite = sprite_create(gSpriteHandler, anim, 0, 0, 0, 0x800, 0, 0, 0);
        sprite_set_base_palette(gSpriteHandler, sprite, COMMENT_PALETTE);
        commentSprites[i] = sprite;
    }

    gResults->totalNegativeComments = totalFailed;
    return totalFailed;
}

// [D_089d7b34] Rank Comment Pool (Try Again)
const char *results_try_again_comment_pool[] = {
    "",
    "Likewise, ",
    "Also... "
};


// Prepare Positive Comments (return average succeeded criteria)
s24_8 results_get_positive_comments(void) {
    const struct MarkingCriteria **criteriaTable = score_handler->markingData;
    struct InputScoreTracker *tracker;
    char *commentsText;
    u32 totalPassed = 0;
    u32 totalCriteria = 0;
    s24_8 averagePassed;
    u16 *commentSprites;
    u32 imperfectionPenalty;

    tracker = score_handler->cueInputTrackers;
    commentSprites = &gResults->commentSprites[gResults->totalNegativeComments];
    imperfectionPenalty = 0;
    commentsText = mem_heap_alloc(0x100);

    for (criteriaTable; *criteriaTable != NULL; tracker++, criteriaTable++) {
        const struct MarkingCriteria *criteria;
        struct Animation *anim;
        u16 sprite;
        u32 palette;
        u32 passedThisCriterion;

        if (tracker->totalInputs == 0) {
            continue;
        }

        passedThisCriterion = TRUE;
        criteria = *criteriaTable;

        if (tracker->totalMisses > 0) {
            passedThisCriterion = FALSE;
            imperfectionPenalty = 1;
        }

        if (criteria->minHitsForSuccess == 0) {
            continue;
        }

        totalCriteria++;

        if (!passedThisCriterion) {
            continue;
        }

        if (tracker->avgHits < criteria->minHitsForSuccess) {
            passedThisCriterion = FALSE;
        }

        if (!passedThisCriterion) {
            continue;
        }

        if (gResults->totalNegativeComments > 0) {
            char modifiedRemark[0x100];
            strcpy(modifiedRemark, criteria->positiveRemark);

            // Convert the first character of the positive remark to lowercase if it's uppercase
            // An exception is made for sentences starting in the word "I" and contractions like "I'm"
            if (modifiedRemark[0] >= 'A' && modifiedRemark[0] <= 'Z' && !(modifiedRemark[0] == 'I' && (modifiedRemark[1] == ' ' || modifiedRemark[1] == '\''))) {
                modifiedRemark[0] += 32;
            }

            memcpy(commentsText, "...but ", 8);
            strcat(commentsText, modifiedRemark);
            anim = results_get_comment_anim(commentsText, TEXT_ANCHOR_BOTTOM_RIGHT, 3);
            palette = EXTRA_COMMENT_PALETTE;
        } else {
            size_t prefixLength = 0;
            switch (totalPassed) {
                case 0:
                    memcpy(commentsText, "", 1);
                    break;
                case 1:
                    memcpy(commentsText, "And, ", 10); // ("moreover,")
                    break;
                default:
                    memcpy(commentsText, "Plus, ", 9); // ("also,")
                    break;
            }
            strcat(commentsText, criteria->positiveRemark);
            palette = COMMENT_PALETTE;
            if (totalPassed > 0) {
                prefixLength = strlen(commentsText) - strlen(criteria->positiveRemark);
        
                // Convert the first character of the statement to lowercase if it's uppercase
                // An exception is made for sentences starting in the word "I" and contractions like "I'm"
                if (commentsText[prefixLength] >= 'A' && commentsText[prefixLength] <= 'Z' && !(commentsText[prefixLength] == 'I' && (commentsText[prefixLength+1] == ' ' || commentsText[prefixLength+1]  == '\''))) {
                    commentsText[prefixLength] += 32;
                }
            }

            anim = results_get_comment_anim(commentsText, TEXT_ANCHOR_BOTTOM_LEFT, 3);
            palette = COMMENT_PALETTE;
        }

        sprite = sprite_create(gSpriteHandler, anim, 0, 0, 0, 0x800, 0, 0, 0);
        sprite_set_base_palette(gSpriteHandler, sprite, palette);
        commentSprites[totalPassed] = sprite;

        totalPassed++;
        if (totalPassed > 2) {
            break;
        }

        if (gResults->totalNegativeComments) {
            sprite_set_visible(gSpriteHandler, commentSprites[0], FALSE);
            break;
        }
    }

    mem_heap_dealloc(commentsText);
    gResults->totalPositiveComments = totalPassed;

    if (totalCriteria == 0) {
        return INT_TO_FIXED(0.0);
    }

    averagePassed = INT_TO_FIXED(totalPassed) / totalCriteria;
    if (averagePassed == INT_TO_FIXED(1.0)) {
        averagePassed -= imperfectionPenalty;
    }

    return averagePassed;
}

// [D_089d7b40] Rank Comment Pool (OK)
const char *results_ok_comment_pool[] = {
    "I guess that was all right.",
    "Good enough...",
    "I don't know...",
    "Hm..."
};


// Display Comments
void results_render_comments(void) {
    u16 *commentSprites;
    u32 totalNegativeComments, totalComments;
    u32 negativeCommentWidth, positiveCommentWidth, totalWidth;
    s32 y;
    u32 i;

    commentSprites = gResults->commentSprites;
    totalNegativeComments = gResults->totalNegativeComments;
    totalComments = gResults->totalNegativeComments + gResults->totalPositiveComments;

    negativeCommentWidth = 0;
    for (i = 0; i < totalNegativeComments; i++) {
        u32 width = sprite_get_data(gSpriteHandler, commentSprites[i], 24);

        if (negativeCommentWidth < width)
            negativeCommentWidth = width;
    }

    positiveCommentWidth = 0;
    for (i = totalNegativeComments; i < totalComments; i++) {
        u32 width = sprite_get_data(gSpriteHandler, commentSprites[i], 24);

        if (positiveCommentWidth < width)
            positiveCommentWidth = width;
    }

    totalWidth = positiveCommentWidth;
    if (totalWidth < negativeCommentWidth)
        totalWidth = negativeCommentWidth;

    if (totalNegativeComments != 0) {
        y = SCREEN_CENTER_Y - ((totalNegativeComments - 1) * (RANK_COMMENT_LINE_SPACING / 2));

        for (i = 0; i < totalNegativeComments; i++) {
            sprite_set_x_y(gSpriteHandler, commentSprites[i], SCREEN_CENTER_X - (negativeCommentWidth / 2), y);
            y += RANK_COMMENT_LINE_SPACING;
        }
        y += RANK_EXTRA_COMMENT_MARGIN;

        for (i = totalNegativeComments; i < totalComments; i++) {
            sprite_set_x_y(gSpriteHandler, commentSprites[i], SCREEN_CENTER_X + (totalWidth / 2), y);
            y += RANK_COMMENT_LINE_SPACING;
        }
    } else {
        y = SCREEN_CENTER_Y - ((totalComments - 1) * (RANK_COMMENT_LINE_SPACING / 2));

        for (i = totalNegativeComments; i < totalComments; i++) {
            sprite_set_x_y(gSpriteHandler, commentSprites[i], SCREEN_CENTER_X - (totalWidth / 2), y);
            y += RANK_COMMENT_LINE_SPACING;
        }
    }
}


// RANK Display Comments (Script Event)
void results_publish_comments(void) {
    struct InputScoreTracker *tracker = score_handler->cueInputTrackers;
    const struct MarkingCriteria **criteriaTable = score_handler->markingData;
    struct Scene *scene;
    struct Animation *textAnim;
    s16 textSprite;
    u32 totalCriteriaFailed, averageCriteriaSucceeded;
    u32 previousResult;

    // bye bye crashes~!
    if(criteriaTable == NULL) {
        criteriaTable = genericMarkingCriteria;
        score_handler->markingData = criteriaTable;
    }

    update_plays_until_next_campaign();

    while (*criteriaTable != NULL) {
        if (tracker->totalInputs > 0) {
            results_tracker_calculate_averages(tracker);
        }
        criteriaTable++;
        tracker++;
    }

    totalCriteriaFailed = results_get_negative_comments();
    averageCriteriaSucceeded = results_get_positive_comments();
    results_render_comments();

    if (totalCriteriaFailed != 0) {
        gResults->finalResultLevel = RESULTS_RANK_TRY_AGAIN;
        sprite_set_anim_cel(gSpriteHandler, gResults->resultIcon, RESULT_ICON_TRY_AGAIN);
        results_save_to_cart(LEVEL_STATE_NULL);
        return;
    }

    if (game_select_roll_credits_after_epilogue()) {
        scene = get_scene_trans_target(&scene_epilogue);
        set_scene_trans_target(&scene_epilogue, &scene_staff_credit_remix_6);
        set_scene_trans_target(&scene_staff_credit_remix_6, scene);
        game_select_disable_credits_after_epilogue();
    }

    if (averageCriteriaSucceeded == INT_TO_FIXED(0.0)) {
        textAnim = results_get_comment_anim(results_ok_comment_pool[agb_random(4)], TEXT_ANCHOR_BOTTOM_CENTER, 3);
        textSprite = sprite_create(gSpriteHandler, textAnim, 0, SCREEN_CENTER_X, SCREEN_CENTER_Y, 0x800, 0, 0, 0);
        sprite_set_base_palette(gSpriteHandler, textSprite, COMMENT_PALETTE);
    }

    if (averageCriteriaSucceeded == INT_TO_FIXED(1.0)) {
        gResults->finalResultLevel = RESULTS_RANK_SUPERB;
        sprite_set_anim_cel(gSpriteHandler, gResults->resultIcon, RESULT_ICON_SUPERB);
        results_save_to_cart(LEVEL_STATE_HAS_MEDAL);

        previousResult = get_level_state_from_grid_xy(D_030046a8->data.recentLevelX, D_030046a8->data.recentLevelY);
        if (previousResult < LEVEL_STATE_HAS_MEDAL) {
            gResults->medalObtained = TRUE;
        }
    }

    else {
        gResults->finalResultLevel = RESULTS_RANK_OK;
        sprite_set_anim_cel(gSpriteHandler, gResults->resultIcon, RESULT_ICON_OK);
        results_save_to_cart(LEVEL_STATE_CLEARED);

        if (averageCriteriaSucceeded != 0) {
            gResults->stillJustOK = TRUE;
        }
    }
}


// Calculate Final Score
u32 results_calculate_final_score(void) {
    s32 points, maxPoints;
    s32 penalty, maxPenalty;
    u32 result, maxResult;

    maxPoints = score_handler->maximumPoints;
    points = clamp_int32(score_handler->totalPoints, 0, score_handler->maximumPoints);

    if (points > 0) {
        maxPenalty = ((points * -15) << 1) / 100; // (awesome: they performed logical shift on a negative value)
        penalty = score_handler->totalIrrelevantInputs * -10;
        points += clamp_int32(penalty, maxPenalty, 0);
    }
    points = clamp_int32(points, 0, maxPoints);

    result = points * points;
    maxResult = maxPoints * maxPoints;

    // Keep within the bounds of a short
    while (maxResult > 0x10000) {
        maxResult >>= 1;
        result >>= 1;
    }

    if (maxPoints != 0) {
        return MAX_LEVEL_SCORE * result / maxResult;
    }

    return 0;
}
