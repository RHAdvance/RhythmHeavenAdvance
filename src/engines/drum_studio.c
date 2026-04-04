// Might need some more splitting

#include "engines/drum_studio.h"
#include "src/scenes/gameplay.h"
#include "src/scenes/drum_replay.h"
#include "src/memory.h"
#include "src/code_08001360.h"
#include "src/task_pool.h"
#include "src/memory_heap.h"
#include "src/code_08007468.h"
#include "src/text_printer.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"
#include "src/code_080092cc.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gDrumStudio ((struct DrumStudioEngineData *)gCurrentEngineData)

enum DrumStudioStatesEnum {
    DRUM_STUDIO_STATE_INACTIVE,
    DRUM_STUDIO_STATE_DRUMMING,
    DRUM_STUDIO_STATE_SAVING_REPLAY
};

enum SaveReplayOptionsEnum {
    REPLAY_SAVE_OPTION_YES,
    REPLAY_SAVE_OPTION_NO
};

extern struct Scene scene_studio;


/* DRUM LESSONS */


// Init. Drum Samurai Sprite
void drum_lessons_init_teacher_sprite(s16 sprite) {
    struct StudioDrummer *teacher = &gDrumStudio->teacher;

    sprite_set_x_y(gSpriteHandler, sprite, 152, 136);
    sprite_set_origin_x_y(gSpriteHandler, sprite, &teacher->xController, &teacher->yController);
    sprite_set_base_tile(gSpriteHandler, sprite, 640);
    gDrumStudio->teacherDrumKitID = 0;
}


// Init. Drum Samurai
void drum_lessons_init_teacher(void) {
    struct StudioDrummer *teacher = &gDrumStudio->teacher;

    teacher->snareDrum = sprite_create(gSpriteHandler, anim_drum_teacher_kit_snare, 0, 64, 64, 0x480c, 1, 0x7f, 0);
    teacher->bassDrum = sprite_create(gSpriteHandler, anim_drum_teacher_kit_bass, 0, 152, 136, 0x480f, 1, 0x7f, 0);
    teacher->tomDrum = sprite_create(gSpriteHandler, anim_drum_teacher_kit_tom, 0, 64, 64, 0x4814, 1, 0x7f, 0);
    teacher->hiHat = sprite_create(gSpriteHandler, anim_drum_teacher_kit_hihat, 0, 64, 64, 0x4819, 1, 0x7f, 0);
    teacher->pedalHiHat = -1;
    teacher->rightPedal = sprite_create(gSpriteHandler, anim_drum_teacher_kit_pedal_r, 0, 64, 64, 0x480a, 1, 0x7f, 0);
    teacher->leftPedal = sprite_create(gSpriteHandler, anim_drum_teacher_kit_pedal_l, 0, 64, 64, 0x480b, 1, 0x7f, 0);
    teacher->splashCymbal = sprite_create(gSpriteHandler, anim_drum_teacher_kit_splash, 0, 64, 64, 0x481e, 1, 0x7f, 0);
    teacher->crashCymbal = sprite_create(gSpriteHandler, anim_drum_teacher_kit_crash, 0, 64, 64, 0x47ec, 1, 0x7f, 0);
    teacher->head = sprite_create(gSpriteHandler, anim_drum_teacher_head, 0, 64, 64, 0x47f4, 1, 0x7f, 0);
    teacher->body = sprite_create(gSpriteHandler, anim_drum_teacher_body, 0, 64, 64, 0x47ec, 1, 0x7f, 0);
    teacher->rightLeg = sprite_create(gSpriteHandler, anim_drum_teacher_use_pedal_r, 0, 64, 64, 0x47ee, 1, 0x7f, 0);
    teacher->leftLeg = sprite_create(gSpriteHandler, anim_drum_teacher_use_pedal_l, 0, 64, 64, 0x47fb, 1, 0x7f, 0);
    teacher->leftArm = sprite_create(gSpriteHandler, anim_drum_teacher_use_snare_l, 0, 64, 64, 0x47f6, 1, 0x7f, 0);
    teacher->rightArm = sprite_create(gSpriteHandler, anim_drum_teacher_use_snare_r, 0, 64, 64, 0x47e2, 1, 0x7f, 0);
    teacher->seat = sprite_create(gSpriteHandler, anim_drum_teacher_kit_seat, 0, 64, 64, 0x47f0, 1, 0x7f, 0);
    teacher->coffeeSteam = -1;

    drum_lessons_init_teacher_sprite(teacher->snareDrum);
    drum_lessons_init_teacher_sprite(teacher->bassDrum);
    drum_lessons_init_teacher_sprite(teacher->tomDrum);
    drum_lessons_init_teacher_sprite(teacher->hiHat);
    drum_lessons_init_teacher_sprite(teacher->rightPedal);
    drum_lessons_init_teacher_sprite(teacher->leftPedal);
    drum_lessons_init_teacher_sprite(teacher->splashCymbal);
    drum_lessons_init_teacher_sprite(teacher->crashCymbal);
    drum_lessons_init_teacher_sprite(teacher->head);
    drum_lessons_init_teacher_sprite(teacher->body);
    drum_lessons_init_teacher_sprite(teacher->rightLeg);
    drum_lessons_init_teacher_sprite(teacher->leftLeg);
    drum_lessons_init_teacher_sprite(teacher->leftArm);
    drum_lessons_init_teacher_sprite(teacher->rightArm);
    drum_lessons_init_teacher_sprite(teacher->seat);

    teacher->xController = 0;
    teacher->yController = 0;
    teacher->headPosX = 152;
    teacher->headPosY = 136;
    teacher->leftArmPosX = 152;
    teacher->leftArmPosY = 136;
    teacher->rightArmPosX = 152;
    teacher->rightArmPosY = 136;
    gDrumStudio->unk3C1 = TRUE;
}


// Play Drum Kit (Drum Samurai)
void func_080271a8(u16 button) {
    play_drumtech_kit_w_anim(drum_teacher_kits[gDrumStudio->teacherDrumKitID], button);
}


// Play Drum Kit (Drum Samurai)
void func_080271d4(u32 drumKitID, u32 unused1, u16 button, u32 unused3) {
    play_drumtech_kit_no_anim(drum_teacher_kits[drumKitID], button);
}


// Engine Event 12 (Set Drum Samurai Expression)
void drum_lessons_set_teacher_expression(u32 expression) {
    struct StudioDrummer *teacher = &gDrumStudio->teacher;
    struct Animation *headAnim;
    struct Animation *rightArmAnim;
    struct Animation *leftArmAnim;

    if (!gDrumStudio->unk3C1) {
        return;
    }

    headAnim = drum_teacher_expressions_anim[expression].head;
    rightArmAnim = drum_teacher_expressions_anim[expression].rightArm;
    leftArmAnim = drum_teacher_expressions_anim[expression].leftArm;

    if (headAnim != NULL) {
        sprite_set_anim(gSpriteHandler, teacher->head, headAnim, 0, 1, 0x7f, 0);
    } else {
        sprite_set_anim(gSpriteHandler, teacher->head, anim_drum_teacher_head, 0x7f, 1, 0x7f, 0);
    }

    if (rightArmAnim != NULL) {
        sprite_set_anim(gSpriteHandler, teacher->rightArm, rightArmAnim, 0, 1, 0x7f, 0);
    } else {
        sprite_set_anim(gSpriteHandler, teacher->rightArm, anim_drum_teacher_use_snare_r, 0x7f, 1, 0x7f, 0);
    }

    if (leftArmAnim != NULL) {
        sprite_set_anim(gSpriteHandler, teacher->leftArm, leftArmAnim, 0, 1, 0x7f, 0);
    } else {
        sprite_set_anim(gSpriteHandler, teacher->leftArm, anim_drum_teacher_use_snare_l, 0x7f, 1, 0x7f, 0);
    }
}


#include "asm/engines/drumming_lessons/asm_08027304.s"

#include "asm/engines/drumming_lessons/asm_08027350.s"

#include "asm/engines/drumming_lessons/asm_0802739c.s"

#include "asm/engines/drumming_lessons/asm_080273e4.s"

#include "asm/engines/drumming_lessons/asm_0802742c.s"

#include "asm/engines/drumming_lessons/asm_08027474.s"

#include "asm/engines/drumming_lessons/asm_080274d0.s"

#include "asm/engines/drumming_lessons/asm_08027518.s"

#include "asm/engines/drumming_lessons/asm_08027560.s"

#include "asm/engines/drumming_lessons/asm_080275a8.s"

#include "asm/engines/drumming_lessons/asm_080275d0.s"

#include "asm/engines/drumming_lessons/asm_080275f8.s"

#include "asm/engines/drumming_lessons/asm_08027668.s"

#include "asm/engines/drumming_lessons/asm_08027728.s"

#include "asm/engines/drumming_lessons/asm_08027744.s"

#include "asm/engines/drumming_lessons/asm_08027760.s"

#include "asm/engines/drumming_lessons/asm_0802777c.s"

#include "asm/engines/drumming_lessons/asm_080277a0.s"


// Engine Event 0x0C (Loop Exit Condition)
void func_080277b8(void) {
    struct Cue *cue;
    struct DrumLessonsCue *info;

    if (gDrumStudio->unk425 == 0) {
        func_08027f4c(gDrumStudio->unk424 + 1);
        gDrumStudio->unk458 = 0;
        if (gDrumStudio->unk424 > 3) {
            gDrumStudio->unk427 = 1;
            results_enable_input_tracking(FALSE);
            func_08027c90(0);
            beatscript_disable_loops();
        } else {
            if (gDrumStudio->unk424 > 1) {
                text_printer_show_text(gDrumStudio->lessonTextPrinter, FALSE);
            }
            gDrumStudio->unk426 += 10;
            if (gDrumStudio->unk426 > 64) {
                gDrumStudio->unk426 = 64;
            }
        }
    } else {
        func_08027f4c(0);
        results_init_score_handler();
    }

    gameplay_get_cue_info(&cue, (void**)&info);
    while (cue != NULL) {
        if (info->bit4) {
            info->bit5 = TRUE;
        }
        gameplay_get_previous_cue_info(cue, &cue, (void**)&info);
    }
}


#include "asm/engines/drumming_lessons/asm_08027888.s"

#include "asm/engines/drumming_lessons/asm_080278d0.s"

#include "asm/engines/drumming_lessons/asm_080278e8.s"

#include "asm/engines/drumming_lessons/asm_08027948.s"


// Init. Drum Lessons
void drum_lessons_init_lesson(void) {
    u32 i;

    gDrumStudio->unk426 = 64;
    gDrumStudio->unk41C = 0;
    gDrumStudio->drumVolume = INT_TO_FIXED(120.0);
    gDrumStudio->unk427 = 0;
    gDrumStudio->unk42E = 0;
    gDrumStudio->unk424 = 0;
    gDrumStudio->unk458 = 0;
    gDrumStudio->unk45A = 0;
    gDrumStudio->unk45C = 0;
    gDrumStudio->lessonTextPrinter = text_printer_create_new(get_current_mem_id(), 4, 128, 32);
    text_printer_set_x_y(gDrumStudio->lessonTextPrinter, 110, 40);
    text_printer_set_layer(gDrumStudio->lessonTextPrinter, 0x700);
    text_printer_set_colors(gDrumStudio->lessonTextPrinter, 0);
    text_printer_set_palette(gDrumStudio->lessonTextPrinter, 3);
    text_printer_center_by_content(gDrumStudio->lessonTextPrinter, TRUE);
    text_printer_set_alignment(gDrumStudio->lessonTextPrinter, 1);
    gDrumStudio->textAdvIconSprite = sprite_create(gSpriteHandler, anim_drum_lessons_text_adv_icon, 0, 64, 64, 0x700, 1, 0, 0x8000);
    sprite_set_base_tile(gSpriteHandler, gDrumStudio->textAdvIconSprite, 640);
    gDrumStudio->lessonRankSprite = sprite_create(gSpriteHandler, anim_drum_lessons_rank_s, 0, 208, 96, 0x700, 1, 0, 0x8000);
    gDrumStudio->slowIconSprite = sprite_create(gSpriteHandler, anim_drum_lessons_slow_icon, 0, 120, 80, 0x600, 1, 0, 0x8000);
    sprite_set_base_tile(gSpriteHandler, gDrumStudio->slowIconSprite, 640);
    gDrumStudio->unk562 = 0;
    gDrumStudio->unk563 = 0;
    gDrumStudio->unk564 = 0;

    for (i = 0; i < DRUM_STUDIO_ACCURACY_LIGHTS_AMOUNT; i++) {
        gDrumStudio->accuracyLightSprites[i] = sprite_create(gSpriteHandler, drum_lessons_accuracy_light_anim[i], 0x7f, drum_lessons_accuracy_light_positions[i].x, drum_lessons_accuracy_light_positions[i].y, 0x4f00, 1, 0x7f, 0x8002);
        sprite_set_base_tile(gSpriteHandler, gDrumStudio->accuracyLightSprites[i], 640);
    }

    gDrumStudio->unk576 = 0;
    gDrumStudio->musicPlayer = NULL;
}


// DRUM LESSON - Engine Event 0x0D (Set Lesson Dialogue)
void drum_lessons_set_dialogue(const char *string) {
    text_printer_set_string(gDrumStudio->lessonTextPrinter, string);
}


// DRUM LESSON - Engine Event 0x10 (Show/Hide Lesson Dialogue)
void drum_lessons_show_dialogue(u32 show) {
    text_printer_show_text(gDrumStudio->lessonTextPrinter, show);
}


#include "asm/engines/drumming_lessons/asm_08027bd8.s"

#include "asm/engines/drumming_lessons/asm_08027c54.s"

#include "asm/engines/drumming_lessons/asm_08027c90.s"

#include "asm/engines/drumming_lessons/asm_08027d08.s"


// Update Drum Lesson
void drum_lessons_update_lesson(void) {
    u32 volume;

    if (gDrumStudio->unk41C > 0) {
        gDrumStudio->unk41C--;
        gDrumStudio->drumVolume = INT_TO_FIXED(0.0);
        scene_set_music_volume_env(INT_TO_FIXED(1.0));
        if ((gDrumStudio->unk41C == 30) && !gDrumStudio->unk427) {
            drum_lessons_set_teacher_expression(0);
        }
        if (gDrumStudio->unk45A > 0) {
            if (--gDrumStudio->unk45A == 0) {
                drum_lessons_set_teacher_expression(1);
            }
        }
    } else {
        gDrumStudio->drumVolume += INT_TO_FIXED(8.0);
        if (gDrumStudio->drumVolume > INT_TO_FIXED(120.0)) {
            gDrumStudio->drumVolume = INT_TO_FIXED(120.0);
        }
        volume = FIXED_TO_INT(gDrumStudio->drumVolume);
        set_drumtech_volume(volume);
        scene_set_music_volume_env(INT_TO_FIXED(1.0) - volume);
    }

    if (gDrumStudio->unk427 && (gDrumStudio->unk426 < 64)) {
        gDrumStudio->unk426++;
    }
    func_080278e8();
    text_printer_update(gDrumStudio->lessonTextPrinter);
    if (gDrumStudio->unk45C) {
        if (D_03004afc & A_BUTTON) {
            gDrumStudio->unk45C = 0;
            play_sound(&s_f_send_mes_seqData);
            set_pause_beatscript_scene(FALSE);
        }
    }
    func_08027d08();
}


// Decrement unk426
void func_08027f1c(void) {
    if (!gDrumStudio->unk427) {
        if (gDrumStudio->unk426 > 0) {
            gDrumStudio->unk426--;
        }
    }
}


// Set unk424
void func_08027f4c(u32 arg) {
    if (!gDrumStudio->unk427) {
        gDrumStudio->unk424 = arg;
    }
}


// Engine Event 11 (?)
void func_08027f70(void) {
    gDrumStudio->unk427 = FALSE;
    func_08027f4c(0);
}


// ?
void func_08027f90(void) {
    if (gDrumStudio->version != 4) {
        return;
    }

    if (!gDrumStudio->unk427) {
        if (gDrumStudio->unk424 > 1) {
            drum_lessons_set_teacher_expression(3);
        }
        func_08027f4c(0);
    }
}


#include "asm/engines/drumming_lessons/asm_08027fc8.s"


// Engine Event 14 (Calculate & Display Rank)
void drum_lessons_get_score(void) {
    char *resultsText = gDrumStudio->lessonResultText;
    char num[2];
    u32 score, rank;
    u32 digit1, digit2, digit3, digit4;
    s32 lessonID;

    num[1] = '\0';
    score = results_calculate_final_score();
    rank = func_08027fc8(score);
    digit1 = score % 10;
    score /= 10;
    digit2 = score % 10;
    score /= 10;
    digit3 = score % 10;
    score /= 10;
    digit4 = score % 10;

    memcpy(resultsText, D_0805a0c0, 40);

    if (digit4 > 0) {
        num[0] = ('0' + digit4);
        strcat(resultsText, num);
    }

    if ((digit4 > 0) || (digit3 > 0)) {
        num[0] = ('0' + digit3);
        strcat(resultsText, num);
    }

    num[0] = ('0' + digit2);
    strcat(resultsText, num);
    strcat(resultsText, D_0805a0c8);

    num[0] = ('0' + digit1);
    strcat(resultsText, num);
    strcat(resultsText, D_0805a0cc);
    strcat(resultsText, drum_lessons_rank_text[rank]);

    drum_lessons_set_dialogue(resultsText);
    set_beatscript_tempo(150);
    scene_set_music(drum_lessons_rank_sfx[rank]);
    set_pause_beatscript_scene(TRUE);

    gDrumStudio->unk45C = 1;
    sprite_set_anim(gSpriteHandler, gDrumStudio->lessonRankSprite, drum_lessons_rank_anim[rank], 0, 1, 0, 0);
    sprite_set_visible(gSpriteHandler, gDrumStudio->lessonRankSprite, TRUE);

    lessonID = medal_corner_get_lesson_id();
    if (lessonID >= 0) {
        if (func_080281c4(lessonID) < rank) {
            func_0802818c(lessonID, rank);
        }
    }
}


#include "asm/engines/drumming_lessons/asm_0802818c.s"

#include "asm/engines/drumming_lessons/asm_080281c4.s"

#include "asm/engines/drumming_lessons/asm_080281e8.s"

#include "asm/engines/drumming_lessons/asm_080281fc.s"


// Change BG Monitor Palette
void drum_studio_start_monitor2(Palette *palette) {
    func_0800c604(0);
    scene_show_bg_layer(BG_LAYER_2);
    scene_show_bg_layer(BG_LAYER_3);
    palette_fade_in(get_current_mem_id(), 0x40, 4, drum_lessons_bg_screen_pal[0][0], &palette[0][0], BG_PALETTE_BUFFER(0));
}


// Start BG Monitor Display
void drum_studio_start_monitor1(void) {
    s32 task;
    u32 id;

    id = gDrumStudio->replayData->songID;
    gDrumStudio->unk3F0 = id;
    gDrumStudio->bg2PosX = gDrumStudio->bg2PosY = 0;
    gDrumStudio->bg3PosX = gDrumStudio->bg3PosY = 0;
    gDrumStudio->bg2VelX = drum_studio_bg_table[id].bg2VelX;
    gDrumStudio->bg2VelY = drum_studio_bg_table[id].bg2VelY;
    gDrumStudio->bg3VelX = drum_studio_bg_table[id].bg3VelX;
    gDrumStudio->bg3VelY = drum_studio_bg_table[id].bg3VelY;
    task = func_08002ee0(get_current_mem_id(), drum_studio_bg_table[id].gfxTable, 0x2000);
    run_func_after_task(task, drum_studio_start_monitor2, (s32)drum_studio_bg_table[id].palette);
}


// Engine Event 03 (Start BG Monitor Display)
void drum_studio_event_start_monitor(u32 unused) {
    drum_studio_start_monitor1();
}


// Stop BG Monitor Display
void drum_studio_stop_monitor2(void) {
    func_0800c604(0);
    scene_hide_bg_layer(BG_LAYER_2);
    scene_hide_bg_layer(BG_LAYER_3);
}


// Revert BG Monitor Palette
void drum_studio_stop_monitor1(void) {
    Palette *palette;
    s32 task;

    if (gDrumStudio->unk3F0 < 0) {
        return;
    }

    palette = drum_studio_bg_table[gDrumStudio->unk3F0].palette;
    task = palette_fade_out(get_current_mem_id(), 0x20, 4, &palette[0][0], drum_lessons_bg_screen_pal[0][0], BG_PALETTE_BUFFER(0));
    run_func_after_task(task, drum_studio_stop_monitor2, 0);
    gDrumStudio->unk3F0 = -1;
}


// Engine Event 04 (Stop BG Monitor Display)
void drum_studio_event_stop_monitor(void) {
    drum_studio_stop_monitor1();
}


#include "asm/engines/drumming_lessons/asm_080283ac.s"

#include "asm/engines/drumming_lessons/asm_080283f8.s"

#include "asm/engines/drumming_lessons/asm_08028444.s"

#include "asm/engines/drumming_lessons/asm_080284a4.s"

#include "asm/engines/drumming_lessons/asm_08028504.s"

#include "asm/engines/drumming_lessons/asm_08028564.s"

#include "asm/engines/drumming_lessons/asm_080285d4.s"

#include "asm/engines/drumming_lessons/asm_08028634.s"

#include "asm/engines/drumming_lessons/asm_08028694.s"

#include "asm/engines/drumming_lessons/asm_080286f4.s"

#include "asm/engines/drumming_lessons/asm_0802871c.s"

#include "asm/engines/drumming_lessons/asm_08028744.s"


// Init. Drum Kit
void drum_studio_init_kit(void) {
    struct StudioDrummer *player = &gDrumStudio->player;
    const struct DrumTechKit *drumKit;
    DrumPlayFunc playFunc;
    u32 drummingButtons;

    sprite_set_visible(gSpriteHandler, player->snareDrum, TRUE);
    sprite_set_visible(gSpriteHandler, player->bassDrum, TRUE);
    sprite_set_visible(gSpriteHandler, player->tomDrum, TRUE);
    sprite_set_visible(gSpriteHandler, player->hiHat, TRUE);
    sprite_set_visible(gSpriteHandler, player->leftPedal, TRUE);
    sprite_set_visible(gSpriteHandler, player->rightPedal, TRUE);
    sprite_set_visible(gSpriteHandler, player->crashCymbal, TRUE);
    sprite_set_visible(gSpriteHandler, player->splashCymbal, TRUE);
    sprite_set_playback(gSpriteHandler, player->hiHat, 0, 0, 0);
    sprite_set_anim_cel(gSpriteHandler, player->hiHat, 2);
    sprite_set_visible(gSpriteHandler, player->pedalHiHat, FALSE);
    sprite_set_playback(gSpriteHandler, player->pedalHiHat, 1, 0x7f, 0);
    sprite_set_anim(gSpriteHandler, player->rightLeg, anim_drum_student_use_pedal_r, 0x7f, 1, 0x7f, 0);
    set_drumtech_hihat_gfx(player->hiHat);
    set_drumtech_pedal_hihat_gfx(player->pedalHiHat, player->rightLeg, anim_drum_student_use_pedal_r, anim_drum_student_use_pedal_hihat);

    playFunc = D_089e2988[gDrumStudio->playerDrumKitID];
    if (playFunc != NULL) {
        CALL_DRUM_PLAY_FUNC(playFunc);
    }

    drumKit = drum_studio_kits[gDrumStudio->playerDrumKitID];
    drummingButtons = 0;

    if (drumKit->aButton != NULL) {
        drummingButtons |= A_BUTTON;
    }
    if (drumKit->bButton != NULL) {
        drummingButtons |= B_BUTTON;
    }
    if (drumKit->dpadUp != NULL) {
        drummingButtons |= DPAD_UP;
    }
    if (drumKit->dpadDown != NULL) {
        drummingButtons |= DPAD_DOWN;
    }
    if (drumKit->dpadLeft != NULL) {
        drummingButtons |= DPAD_LEFT;
    }
    if (drumKit->dpadRight != NULL) {
        drummingButtons |= DPAD_RIGHT;
    }
    if (drumKit->lButton != NULL) {
        drummingButtons |= LEFT_SHOULDER_BUTTON;
    }
    if (drumKit->rButton != NULL) {
        drummingButtons |= RIGHT_SHOULDER_BUTTON;
    }

    gDrumStudio->drummingButtons = drummingButtons;
    gameplay_set_input_buttons(drummingButtons, 0);
}


// Get Total Drum Kits (15)
s32 drum_studio_get_total_kits(void) {
    return 15;
}


// Graphics Init. 3
void drum_studio_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
    func_080041d0(0, 1, 0);
    func_0800425c(64, 120);
}


// Graphics Init. 2
void drum_studio_init_gfx2(void) {
    struct GraphicsTable *gfxTable = drum_studio_gfx_table;
    s32 task;

    func_0800c604(0);
    if (gDrumStudio->version == ENGINE_VER_DRUM_LESSONS) {
        gfxTable = drum_lessons_gfx_table;
    }

    task = func_08002ee0(get_current_mem_id(), gfxTable, 0x2000);
    run_func_after_task(task, drum_studio_init_gfx3, 0);
}


// Graphics Init. 1
void drum_studio_init_gfx1(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), drum_studio_buffered_textures);
    run_func_after_task(task, drum_studio_init_gfx2, 0);
}


// Game Engine Start
void drum_studio_engine_start(u32 version) {
    struct StudioDrummer *player = &gDrumStudio->player;
    s32 var;

    gDrumStudio->version = version;
    drum_studio_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, BG_PRIORITY_HIGH);
    scene_set_bg_layer_display(BG_LAYER_2, FALSE, 0, 0, 2, 30, BG_PRIORITY_LOW);
    scene_set_bg_layer_display(BG_LAYER_3, FALSE, 0, 0, 2, 31, BG_PRIORITY_LOWEST);

    player->snareDrum = sprite_create(gSpriteHandler, anim_drum_student_kit_snare, 0, 120, 100, 0x480c, 1, 0x7f, 0);
    player->bassDrum = sprite_create(gSpriteHandler, anim_drum_student_kit_bass, 0, 120, 100, 0x480f, 1, 0x7f, 0);
    player->tomDrum = sprite_create(gSpriteHandler, anim_drum_student_kit_tom, 0, 120, 100, 0x4814, 1, 0x7f, 0);
    player->hiHat = sprite_create(gSpriteHandler, anim_drum_student_kit_hihat, 0, 120, 100, 0x4819, 1, 0x7f, 0);
    player->pedalHiHat = sprite_create(gSpriteHandler, anim_drum_student_kit_pedal_hihat, 0, 120, 100, 0x4808, 1, 0x7f, 0x8000);
    player->rightPedal = sprite_create(gSpriteHandler, anim_drum_student_kit_pedal_r, 0, 123, 97, 0x480a, 1, 0x7f, 0);
    player->leftPedal = sprite_create(gSpriteHandler, anim_drum_student_kit_pedal_l, 0, 119, 96, 0x480b, 1, 0x7f, 0);
    player->splashCymbal = sprite_create(gSpriteHandler, anim_drum_student_kit_splash, 0, 120, 100, 0x481e, 1, 0x7f, 0);
    player->crashCymbal = sprite_create(gSpriteHandler, anim_drum_student_kit_crash, 0, 120, 100, 0x47ec, 1, 0x7f, 0);
    player->head = sprite_create(gSpriteHandler, anim_drum_student_head, 0, 120, 100, 0x47f4, 1, 0x7f, 0);
    player->body = sprite_create(gSpriteHandler, anim_drum_student_body, 0, 120, 100, 0x47ec, 1, 0x7f, 0);
    player->rightLeg = sprite_create(gSpriteHandler, anim_drum_student_use_pedal_r, 0, 120, 100, 0x47ee, 1, 0x7f, 0);
    player->leftLeg = sprite_create(gSpriteHandler, anim_drum_student_use_pedal_l, 0, 120, 100, 0x47fb, 1, 0x7f, 0);
    player->leftArm = sprite_create(gSpriteHandler, anim_drum_student_use_snare_l, 0, 102, 90, 0x47f6, 1, 0x7f, 0);
    player->rightArm = sprite_create(gSpriteHandler, anim_drum_student_use_snare_r, 0, 120, 100, 0x47e2, 1, 0x7f, 0);
    player->seat = sprite_create(gSpriteHandler, anim_drum_student_kit_seat, 0, 120, 100, 0x47f0, 1, 0x7f, 0);
    player->coffeeSteam = sprite_create(gSpriteHandler, anim_drum_student_coffee_steam, 0, 99, 82, 0x47eb, 1, 0, 0x8000);
    player->xController = 56;
    player->yController = -8;
    sprite_id_set_origin_x_y(gSpriteHandler, get_current_mem_id(), &player->xController, &player->yController);
    player->headPosX = 120;
    player->headPosY = 100;
    player->leftArmPosX = 102;
    player->leftArmPosY = 90;
    player->rightArmPosX = 120;
    player->rightArmPosY = 100;

    gDrumStudio->songTitlePrinter = text_printer_create_new(get_current_mem_id(), 1, 144, 32);
    text_printer_set_x_y(gDrumStudio->songTitlePrinter, 96, 9);
    text_printer_set_layer(gDrumStudio->songTitlePrinter, 0x700);
    text_printer_set_colors(gDrumStudio->songTitlePrinter, 3);
    text_printer_set_palette(gDrumStudio->songTitlePrinter, 3);
    text_printer_center_by_content(gDrumStudio->songTitlePrinter, TRUE);
    text_printer_set_x_controller(gDrumStudio->songTitlePrinter, &gDrumStudio->songTitlePosX);
    gDrumStudio->songTitleBgSprite = sprite_create(gSpriteHandler, anim_drum_studio_song_title_bubble, 0, 224, 8, 0x800, 0, 0, 0);
    sprite_set_origin_x(gSpriteHandler, gDrumStudio->songTitleBgSprite, &gDrumStudio->songTitlePosX);
    gDrumStudio->songTitlePosX = -144;
    gDrumStudio->unk3FC = 0;

    gDrumStudio->replaySaveOptionSprite = sprite_create(gSpriteHandler, anim_drum_studio_save_option_y, 0, 180, 102, 0x800, 1, 0, 0x8000);
    gDrumStudio->currentSaveOption = REPLAY_SAVE_OPTION_YES;
    gDrumStudio->replayTextPrinter = text_printer_create_new(get_current_mem_id(), 2, 120, 32);
    text_printer_set_x_y(gDrumStudio->replayTextPrinter, 120, 64);
    text_printer_set_layer(gDrumStudio->replayTextPrinter, 0x700);
    text_printer_set_colors(gDrumStudio->replayTextPrinter, 0);
    text_printer_set_palette(gDrumStudio->replayTextPrinter, 3);
    text_printer_center_by_content(gDrumStudio->replayTextPrinter, TRUE);

    gDrumStudio->memoryWarningSprite = sprite_create(gSpriteHandler, anim_drum_studio_memory_warning, 0, 240, 160, 0x800, 1, 0, 0x8000);

    init_drumtech(&gDrumStudio->drumTech);

    gDrumStudio->replayID = 0;
    switch (version) {
        case ENGINE_VER_DRUM_STUDIO_PLAY:
        case ENGINE_VER_DRUM_STUDIO_2:
        case ENGINE_VER_DRUM_STUDIO_LISTEN:
            gDrumStudio->replayID = get_current_scene_trans_var();
            break;
    }

    if (gDrumStudio->version == ENGINE_VER_DRUM_STUDIO_LISTEN) {
        while (D_030046a8->data.studioSongs[gDrumStudio->replayID].unk3 & 2) {
            if (++gDrumStudio->replayID >= D_030046a8->data.totalSongs) {
                gDrumStudio->replayID = 0;
            }
        }
    }

    gDrumStudio->playerDrumKitID = 0;
    switch (version) {
        case ENGINE_VER_DRUM_STUDIO_PLAY:
            gDrumStudio->playerDrumKitID = clamp_int32(studio_get_current_kit(), 0, drum_studio_get_total_kits());
            break;
        case ENGINE_VER_DRUM_STUDIO_LISTEN:
            gDrumStudio->playerDrumKitID = D_030046a8->data.studioSongs[gDrumStudio->replayID].drumKitID;
            break;
    }

    gDrumStudio->drumReplaySeq = mem_heap_alloc_id(get_current_mem_id(), 0x3800);
    gDrumStudio->drummingButtons = (A_BUTTON | B_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN | RIGHT_SHOULDER_BUTTON | LEFT_SHOULDER_BUTTON);
    gameplay_set_input_buttons(gDrumStudio->drummingButtons, 0);
    gameplay_prevent_dpad_overlap(FALSE);
    gDrumStudio->state = DRUM_STUDIO_STATE_DRUMMING;
    gDrumStudio->unk3CD = 0;
    gDrumStudio->unk3CE = FALSE;
    gDrumStudio->bg2PosX = gDrumStudio->bg2PosY = 0;
    gDrumStudio->bg2VelX = gDrumStudio->bg2VelY = 0;
    gDrumStudio->bg3PosX = gDrumStudio->bg3PosY = 0;
    gDrumStudio->bg3VelX = gDrumStudio->bg3VelY = 0;
    gDrumStudio->unk3F0 = -1;
    gDrumStudio->unk3C1 = FALSE;
    gDrumStudio->unk57C = 0;

    switch (version) {
        case ENGINE_VER_DRUM_STUDIO_0:
            break;
        case ENGINE_VER_DRUM_STUDIO_PLAY:
            break;
        case ENGINE_VER_DRUM_STUDIO_2:
            break;
        case ENGINE_VER_DRUM_STUDIO_LISTEN:
            break;
        case ENGINE_VER_DRUM_LESSONS: // Drum Lessons
            scene_show_bg_layer(BG_LAYER_2);
            scene_show_bg_layer(BG_LAYER_3);
            drum_lessons_init_lesson();
            drum_lessons_init_teacher();
            break;
    }

    drum_studio_init_kit();
    gameplay_assess_irrelevant_inputs(FALSE);
}


// Engine Event 0x1A (STUB)
void drum_studio_engine_event_stub(void) {
}


// Exit (SELECT_BUTTON Was Pressed)
void drum_studio_select_button_exit(void) {
    u32 unk3CD = gDrumStudio->unk3CD;

    play_sound(&s_menu_cancel2_seqData);
    gDrumStudio->unk3CE = 0;

    if ((unk3CD == 2) && (gDrumStudio->replayData->songID == STUDIO_SONG_SILENCE) && (gDrumStudio->unk57C > 300)) {
        func_0801d968(D_089e2b04);
    } else {
        gDrumStudio->unk3CD = 0;
        key_rec_set_mode(0, 0x3ff, 0, 0);
        set_pause_beatscript_scene(FALSE);
        func_0801d968(D_089e2ad4);
    }

    if (gDrumStudio->version == ENGINE_VER_DRUM_LESSONS) {
        if (gDrumStudio->musicPlayer != NULL) {
            fade_out_soundplayer(gDrumStudio->musicPlayer, 0x0A);
        }
    }
}


#include "asm/engines/drumming_lessons/asm_08029178.s"

#include "asm/engines/drumming_lessons/asm_0802918c.s"

#include "asm/engines/drumming_lessons/asm_080291bc.s"


// Update Song Title
void drum_studio_update_song_title(void) {
    if (gDrumStudio->unk402 > 0) {
        if (--gDrumStudio->unk402 == 0) {
            gDrumStudio->unk3FC = INT_TO_FIXED(1.0);
            gDrumStudio->unk3FE = -144;
            gDrumStudio->unk400 = 0;
            text_printer_set_string(gDrumStudio->songTitlePrinter, gDrumStudio->songTitleText);
            sprite_set_anim_cel(gSpriteHandler, gDrumStudio->songTitleBgSprite, gDrumStudio->unk408);
        }
    }

    if (gDrumStudio->unk3FC != 0) {
        gDrumStudio->unk3FC = ((gDrumStudio->unk3FC << 4) - gDrumStudio->unk3FC) >> 4;
        gDrumStudio->songTitlePosX = FIXED_TO_INT((INT_TO_FIXED(1.0) - gDrumStudio->unk3FC) * (gDrumStudio->unk400 - gDrumStudio->unk3FE));
        gDrumStudio->songTitlePosX += gDrumStudio->unk3FE;
    }

    text_printer_update(gDrumStudio->songTitlePrinter);
}


#include "asm/engines/drumming_lessons/asm_080292e0.s"


// Engine Event 00 (Init. Studio Script & Recording)
const struct Beatscript *drum_studio_init_script(void) {
    struct StudioSongData *replayData;
    u32 r7;
    u32 availableSpace;
    u32 replaySize;

    if (gDrumStudio->version == ENGINE_VER_DRUM_LESSONS) {
        return NULL;
    }

    gDrumStudio->replayData = replayData = &D_030046a8->data.studioSongs[gDrumStudio->replayID];
    gDrumStudio->unk418 = 0;
    dma3_fill(0, gDrumStudio->drumReplaySeq, 0x3800, 0x20, 0x200);

    switch (gDrumStudio->version) {
        case 0:
            r7 = 1;
            break;

        case 1:
            r7 = 2;
            break;

        case 2:
            r7 = 3;
            break;

        case 3:
            r7 = 0;
            if (replayData->unk3 & 1) {
                r7 = 3;
            } else {
                gDrumStudio->playerDrumKitID = 0;
                drum_studio_init_kit();
            }
            func_0802918c(studio_song_table[replayData->songID].fullTitle, replayData->unk3 & 1);
            if (replayData->songID == STUDIO_SONG_SILENCE) {
                gDrumStudio->unk402 = 120;
            }
            func_080292e0(~replayData->unk3 & 1);
            studio_song_list_select_item(gDrumStudio->replayID);
            break;
    }

    switch (r7) {
        case 0:
            set_studio_drummer_mode(0);
            break;

        case 1:
            set_studio_drummer_mode(0);
            break;

        case 2: // Record Replay
            set_studio_drummer_mode(1);
            availableSpace = get_remaining_replay_data_space(&D_030046a8->data.drumReplaysAlloc);
            key_rec_set_mode(1, 0x3ff, gDrumStudio->drumReplaySeq, availableSpace / 2);
            if ((availableSpace == 0) || (get_available_replay_data_id(&D_030046a8->data.drumReplaysAlloc) < 0)) {
                sprite_set_visible(gSpriteHandler, gDrumStudio->memoryWarningSprite, TRUE);
            }
            gDrumStudio->playerDrumKitID = clamp_int32(studio_get_current_kit(), 0, drum_studio_get_total_kits());
            break;

        case 3: // Listen to Replay
            set_studio_drummer_mode(2);
            replaySize = get_saved_replay_data(&D_030046a8->data.drumReplaysAlloc, replayData->replayID, gDrumStudio->drumReplaySeq);
            key_rec_set_mode(3, 0x3ff, gDrumStudio->drumReplaySeq, replaySize / 2);
            gDrumStudio->playerDrumKitID = replayData->drumKitID;
            drum_studio_init_kit();
            break;
    }

    gDrumStudio->unk3CD = r7;
    return studio_song_table[replayData->songID].script;
}


// Engine Event 01 (?)
s32 func_080295d4(void) {
    s32 result = FALSE;

    if (gDrumStudio->version == ENGINE_VER_DRUM_LESSONS) {
        return FALSE;
    }

    switch (gDrumStudio->unk3CD) {
        case 0:
        case 1:
            break;
        case 2:
            gDrumStudio->unk416 = key_rec_get_next();
            key_rec_set_mode(0, 0x3ff, 0, 0);
            break;
        case 3:
            key_rec_set_mode(0, 0x3ff, 0, 0);
            break;
    }

    if (gDrumStudio->version == ENGINE_VER_DRUM_STUDIO_LISTEN) {
        do {
            if (++gDrumStudio->replayID >= D_030046a8->data.totalSongs) {
                gDrumStudio->replayID = 0;
            }
        } while (D_030046a8->data.studioSongs[gDrumStudio->replayID].unk3 & 2);
        result = TRUE;
        func_080291bc();
    }
    gDrumStudio->unk3CD = 0;

    return result;
}


// Align Drummer Parts to Body
void drum_studio_align_drummer_sprites(struct StudioDrummer *drummer, const struct Vector2 *vecOfs) {
    vecOfs += sprite_get_anim_cel(gSpriteHandler, drummer->body);
    sprite_set_x_y(gSpriteHandler, drummer->head, drummer->headPosX + vecOfs->x, drummer->headPosY + vecOfs->y);
    sprite_set_x_y(gSpriteHandler, drummer->leftArm, drummer->leftArmPosX + vecOfs->x, drummer->leftArmPosY + vecOfs->y);
    sprite_set_x_y(gSpriteHandler, drummer->rightArm, drummer->rightArmPosX + vecOfs->x, drummer->rightArmPosY + vecOfs->y);
}


// Update something
void func_0802972c(void) {
    if (gDrumStudio->unk3CD == 2) {
        if (key_rec_reached_end()) {
            sprite_set_visible(gSpriteHandler, gDrumStudio->memoryWarningSprite, TRUE);
        }
    }

    if (gDrumStudio->unk3CD == 3) {
        if (gDrumStudio->replayData->songID == 0) {
            if (key_rec_reached_end()) {
                gDrumStudio->unk418 = 1;
            }
        }
    }
}


// Update BG Monitor Display
void drum_studio_update_monitor(void) {
    gDrumStudio->bg2PosX += gDrumStudio->bg2VelX;
    gDrumStudio->bg2PosY += gDrumStudio->bg2VelY;
    gDrumStudio->bg3PosX += gDrumStudio->bg3VelX;
    gDrumStudio->bg3PosY += gDrumStudio->bg3VelY;
    D_03004b10.BG_OFS[BG_LAYER_2].x = FIXED_TO_INT(gDrumStudio->bg2PosX);
    D_03004b10.BG_OFS[BG_LAYER_2].y = FIXED_TO_INT(gDrumStudio->bg2PosY);
    D_03004b10.BG_OFS[BG_LAYER_3].x = FIXED_TO_INT(gDrumStudio->bg3PosX);
    D_03004b10.BG_OFS[BG_LAYER_3].y = FIXED_TO_INT(gDrumStudio->bg3PosY);
}


// Update (Main Drumming State)
void drum_studio_update_inputs(void) {
    const struct DrumTechKit *drumKit = drum_studio_kits[gDrumStudio->playerDrumKitID];
    u16 current, pressed, released;

    switch (gDrumStudio->unk3CD) {
        case 0:
            current = D_03004ac0;
            pressed = 0;
            released = 0;
            break;
        case 1:
            current = D_03004ac0;
            pressed = D_03004afc;
            released = D_03004b00;
            break;
        case 2:
            current = D_03004ac0;
            pressed = D_03004afc;
            released = D_03004b00;
            break;
        case 3:
            current = D_030046b8;
            pressed = D_03005378;
            released = D_030046b4;
            break;
    }

    current &= gDrumStudio->drummingButtons;
    pressed &= gDrumStudio->drummingButtons;
    released &= gDrumStudio->drummingButtons;
    play_drumtech_kit_w_anim(drumKit, pressed);
    update_drumtech_hihat(drumKit, current, pressed, released);
}


// Check if Replay Cannot Be Saved
s32 drum_studio_cannot_save_replay(void) {
    if (get_remaining_replay_data_space(&D_030046a8->data.drumReplaysAlloc) > 0) {
        if (get_available_replay_data_id(&D_030046a8->data.drumReplaysAlloc) >= 0) {
            if (gDrumStudio->unk416 > 0) {
                return FALSE;
            }
        }
    }
    return TRUE;
}


// Engine Event 05 (Show Replay Save Options)
void drum_studio_show_save_options(void) {
    if (gDrumStudio->version == ENGINE_VER_DRUM_STUDIO_PLAY) {
        if (!drum_studio_cannot_save_replay()) {
            set_pause_beatscript_scene(TRUE);
            text_printer_set_string(gDrumStudio->replayTextPrinter, "Do you want to save\n"
                                                                    "your performance?");
            gDrumStudio->saveOptionsDelayTime = (gDrumStudio->replayData->songID == STUDIO_SONG_SILENCE) ? 15 : 60;
            gDrumStudio->state = DRUM_STUDIO_STATE_SAVING_REPLAY;
        }
    }
}


// Save Replay
void drum_studio_save_replay(void) {
    struct StudioSongData *replayData;
    s32 replayID;
    s32 saveID;

    if (gDrumStudio->replayData->replayID >= 0) {
        return;
    }

    saveID = alloc_replay_save_data(&D_030046a8->data.drumReplaysAlloc, gDrumStudio->drumReplaySeq, gDrumStudio->unk416 * 2);
    if (saveID >= 0) {
        replayID = save_studio_song(gDrumStudio->replayData->songID, saveID, studio_get_current_kit(), 1);
        if (replayID < 0) {
            delete_saved_replay(&D_030046a8->data.drumReplaysAlloc, saveID);
        } else {
            studio_song_list_select_item(replayID);
            set_scene_trans_var(&scene_studio, 0);
        }
    }
    scene_flush_save_buffer();
}


// Update (Save Replay Prompt State)
void drum_studio_update_save_options(void) {
    if (gDrumStudio->saveOptionsDelayTime > 0) {
        if (--gDrumStudio->saveOptionsDelayTime == 0) {
            sprite_set_visible(gSpriteHandler, gDrumStudio->replaySaveOptionSprite, TRUE);
        }
    } else {
        if ((D_03004afc & DPAD_LEFT) && (gDrumStudio->currentSaveOption == REPLAY_SAVE_OPTION_NO)) {
            sprite_set_anim(gSpriteHandler, gDrumStudio->replaySaveOptionSprite, anim_drum_studio_save_option_y, 0, 1, 0, 0);
            gDrumStudio->currentSaveOption = REPLAY_SAVE_OPTION_YES;
            play_sound(&s_menu_cursor1_seqData);
            rumble_play_menu_move();
            return;
        } else if ((D_03004afc & DPAD_RIGHT) && (gDrumStudio->currentSaveOption == REPLAY_SAVE_OPTION_YES)) {
            sprite_set_anim(gSpriteHandler, gDrumStudio->replaySaveOptionSprite, anim_drum_studio_save_option_n, 0, 1, 0, 0);
            gDrumStudio->currentSaveOption = REPLAY_SAVE_OPTION_NO;
            play_sound(&s_menu_cursor1_seqData);
            rumble_play_menu_move();
            return;
        } else if ((D_03004afc & DPAD_LEFT) || (D_03004afc & DPAD_RIGHT)) {
            rumble_play_menu_limit();
            return;
        } else if ((D_03004afc & A_BUTTON)) {
            if (gDrumStudio->currentSaveOption == REPLAY_SAVE_OPTION_YES) {
                play_sound(&s_menu_kettei2_seqData);
                rumble_play_menu_confirm();
                drum_studio_save_replay();
            } else {
                play_sound(&s_menu_cancel3_seqData);
                rumble_play_menu_cancel();
            }
            sprite_set_visible(gSpriteHandler, gDrumStudio->replaySaveOptionSprite, FALSE);
            text_printer_clear(gDrumStudio->replayTextPrinter);
            set_pause_beatscript_scene(FALSE);
            gDrumStudio->state = DRUM_STUDIO_STATE_INACTIVE;
        }
    }
    text_printer_update(gDrumStudio->replayTextPrinter);
}


#include "asm/engines/drumming_lessons/asm_08029b8c.s"


// Game Engine Update
void drum_studio_engine_update(void) {
    if (gDrumStudio->version == ENGINE_VER_DRUM_LESSONS) {
        drum_lessons_update_lesson();
        if ((gDrumStudio->state == DRUM_STUDIO_STATE_DRUMMING) && (gDrumStudio->unk3CD == 1)) {
            if (D_03004afc & gDrumStudio->drummingButtons) {
                set_drumtech_volume(INT_TO_FIXED(1.0));
                if (gDrumStudio->unk41C < 30) {
                    gDrumStudio->unk45A = 30;
                }
                gDrumStudio->unk41C = ticks_to_frames(0x5A);
            }
        }
    }

    switch (gDrumStudio->state) {
        case DRUM_STUDIO_STATE_DRUMMING:
            drum_studio_update_inputs();
            break;
        case DRUM_STUDIO_STATE_SAVING_REPLAY:
            drum_studio_update_save_options();
            break;
    }

    update_drumtech();
    drum_studio_align_drummer_sprites(&gDrumStudio->player, D_089e2b58);
    if (gDrumStudio->unk3C1) {
        drum_studio_align_drummer_sprites(&gDrumStudio->teacher, D_089e2b78);
    }
    func_0802972c();
    drum_studio_update_monitor();
    drum_studio_update_song_title();
    if (gDrumStudio->unk3CE && (D_03004afc & SELECT_BUTTON)) {
        drum_studio_select_button_exit();
    }
    gDrumStudio->unk57C++;
}


// Play Drum Kit
void func_08029cac(u32 drumKitID, u16 keys, u16 pressed, u16 released) {
    struct DrumTechKit *drumKit = drum_studio_kits[drumKitID];

    play_drumtech_kit_no_anim(drumKit, pressed);
    update_drumtech_hihat(drumKit, keys, pressed, released);
}


#include "asm/engines/drumming_lessons/asm_08029cec.s"

#include "asm/engines/drumming_lessons/asm_08029d20.s"


// Cue - Spawn
void drum_studio_cue_spawn(struct Cue *cue, struct DrumLessonsCue *info, u32 drum) {
    info->drum = drum;
    info->bit0 = FALSE;
    info->bit4 = gDrumStudio->unk576;
    info->bit5 = FALSE;
}


// Cue - Update
u32 drum_studio_cue_update(struct Cue *cue, struct DrumLessonsCue *info, u32 runningTime, u32 duration) {
    if ((runningTime > ticks_to_frames(0x18)) && !info->bit0) {
        if (gDrumStudio->unk41C == 0) {
            if (gDrumStudio->unk3C1) {
                func_080271a8(D_089e2ba8[info->drum]);
            } else {
                func_080271d4(gDrumStudio->teacherDrumKitID, 0, D_089e2ba8[info->drum], 0);
            }
        }
        info->bit0 = TRUE;
    }

    if (runningTime > ticks_to_frames(0x30)) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Cue - Despawn
void drum_studio_cue_despawn(struct Cue *cue, struct DrumLessonsCue *info) {
}


// Flash Accuracy Meter Light
void drum_studio_flash_accuracy_meter(void) {
    s32 timingOffset;

    if (gDrumStudio->version != ENGINE_VER_DRUM_LESSONS) {
        return;
    }

    timingOffset = gameplay_get_last_hit_offset();
    if (timingOffset > 0) {
        timingOffset -= 1;
    }
    if (timingOffset < 0) {
        timingOffset += 1;
    }

    timingOffset = clamp_int32(timingOffset + 3, 0, DRUM_STUDIO_ACCURACY_LIGHTS_AMOUNT - 1);
    sprite_set_anim_cel(gSpriteHandler, gDrumStudio->accuracyLightSprites[timingOffset], 0);
    sprite_set_visible(gSpriteHandler, gDrumStudio->accuracyLightSprites[timingOffset], TRUE);
}


// Cue - Hit
void drum_studio_cue_hit(struct Cue *cue, struct DrumLessonsCue *info, u32 pressed, u32 released) {
    if (info->bit5) {
        gameplay_ignore_this_cue_result();
    }

    drum_studio_flash_accuracy_meter();
    func_08027f1c();
}


// Cue - Barely
void drum_studio_cue_barely(struct Cue *cue, struct DrumLessonsCue *info, u32 pressed, u32 released) {
    if (info->bit5) {
        gameplay_ignore_this_cue_result();
    }

    drum_studio_flash_accuracy_meter();
    func_08027f1c();
}


// Cue - Miss
void drum_studio_cue_miss(struct Cue *cue, struct DrumLessonsCue *info) {
    gDrumStudio->unk425 = 1;

    if (info->bit5) {
        gameplay_ignore_this_cue_result();
    }

    func_08027f90();
}


// Input Event
void drum_studio_input_event(u32 pressed, u32 released) {
    if (gDrumStudio->version == ENGINE_VER_DRUM_LESSONS) {
        gDrumStudio->unk425 = 1;
        func_08027f1c();
        func_08027f90();
    }
}


// Common Event 0 (Beat Animation)
void drum_studio_common_beat_animation(void) {
}


// Common Event 1 (Display Text)
void drum_studio_common_display_text(void) {
}


// Common Event 2 (Init. Tutorial)
void drum_studio_common_init_tutorial(void) {
}
