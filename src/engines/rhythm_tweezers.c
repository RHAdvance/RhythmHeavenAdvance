#include "engines/rhythm_tweezers.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/text_printer.h"
#include "src/affine_sprite.h"
#include "src/lib_0804ca80.h"
asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gRhythmTweezers ((struct RhythmTweezersEngineData *)gCurrentEngineData)


/* RHYTHM TWEEZERS */


// [func_0802e750] Initialise Vegetable Face
void rhythm_tweezers_init_veg(void) {
    struct RhythmTweezersVegetable *vegetable = &gRhythmTweezers->vegetable;
    u8 type = (gRhythmTweezers->version % 3);

    vegetable->spriteCurrent = sprite_create(gSpriteHandler, rhythm_tweezers_veg_face_anim[type], 0, 120, 16, 0x4800, -1, 0, 0);
    sprite_set_origin_x_y(gSpriteHandler, vegetable->spriteCurrent, &gRhythmTweezers->screenHorizontalPosition, &D_03004b10.BG_OFS[BG_LAYER_1].y);

    vegetable->spriteNext = sprite_create(gSpriteHandler, rhythm_tweezers_veg_face_anim[type], 0, 120, 16, 0x4800, 0, 0, 0);
    sprite_set_x(gSpriteHandler, vegetable->spriteNext, 0x178);
    sprite_set_origin_x_y(gSpriteHandler, vegetable->spriteNext, &gRhythmTweezers->screenHorizontalPosition, &D_03004b10.BG_OFS[BG_LAYER_1].y);

    vegetable->bgMapSide = 0;
    gRhythmTweezers->screenHorizontalPosition = 0;
    vegetable->isScrolling = FALSE;
}


// [func_0802e828] Engine Event 02 (Scroll to New Vegetable)
void rhythm_tweezers_scroll_to_next_veg(u32 time) {
    struct RhythmTweezersVegetable *vegetable = &gRhythmTweezers->vegetable;
    u32 side;
    u32 *bgMap;

    vegetable->isScrolling = TRUE;
    vegetable->scrollTime = 0;
    vegetable->scrollTarget = ticks_to_frames(time);
    sprite_set_anim(gSpriteHandler, vegetable->spriteNext, rhythm_tweezers_veg_face_anim[vegetable->typeNext], 0, 0, 0, 0);

    side = vegetable->bgMapSide;
    bgMap = &RT_VEGETABLE_BG_MAP_R;
    if (side) bgMap = &RT_VEGETABLE_BG_MAP_L;
    func_08003eb8(gRhythmTweezers->version >= 6 ? rhythm_tweezers_extra_veg_bg_maps[vegetable->typeNext] : rhythm_tweezers_veg_bg_maps[vegetable->typeNext], bgMap);
}


// [func_0802e89c] Engine Event 04 (Play Cash Register SFX)
void rhythm_tweezers_play_cash_reg_sfx(void) {
    play_sound(&s_f_hair_next_seqData);
}


// [func_0802e8ac] Update Vegetable (Scrolling)
void rhythm_tweezers_update_scroll(void) {
    struct RhythmTweezersVegetable *vegetable = &gRhythmTweezers->vegetable;
    u32 x;

    vegetable->scrollTime += 1;

    // Vegetable has reached its destination.
    if (vegetable->scrollTime >= vegetable->scrollTarget) {
        gRhythmTweezers->screenHorizontalPosition = 0;
        vegetable->bgMapSide ^= 1;
        D_03004b10.BG_OFS[BG_LAYER_1].x = vegetable->bgMapSide << 8;
        vegetable->isScrolling = FALSE;
        gameplay_reset_cues();

        sprite_set_anim(gSpriteHandler, vegetable->spriteCurrent, rhythm_tweezers_veg_face_anim[vegetable->typeNext], 0, -1, 0, 0);
        vegetable->typeCurrent = vegetable->typeNext;
    }

    // Vegetable has not yet reached its destination.
    else {
        x = 1024 * vegetable->scrollTime / vegetable->scrollTarget;
        x = (-coss(x) + 0x100) >> 1;

        gRhythmTweezers->screenHorizontalPosition = x;
        D_03004b10.BG_OFS[BG_LAYER_1].x = x;
        if (vegetable->bgMapSide != 0) {
            D_03004b10.BG_OFS[BG_LAYER_1].x = x + 0x100;
        }
    }
}


// [func_0802e96c] Engine Event 03 (Set Upcoming Vegetable Type)
void rhythm_tweezers_set_next_veg_type(u32 type) {
    struct RhythmTweezersVegetable *vegetable = &gRhythmTweezers->vegetable;

    vegetable->typeNext = type;
}


// [func_0802e97c] Engine Event 06 (STUB)
void rhythm_tweezers_removed_engine_event(void) {
}


// [func_0802e980] Update Vegetable
void rhythm_tweezers_update_veg(void) {
    struct RhythmTweezersVegetable *vegetable = &gRhythmTweezers->vegetable;

    if (vegetable->isScrolling) {
        rhythm_tweezers_update_scroll();
    }
}


// [func_0802e99c] Initialise Falling Hairs
void rhythm_tweezers_init_falling_hairs(void) {
    struct RhythmTweezersFallingHair *hair;
    u32 i;

    for (i = 0; i < RHYTHM_TWEEZERS_FALLING_HAIR_AMOUNT; i++) {
        hair = &gRhythmTweezers->fallingHairs[i];
        hair->sprite = create_affine_sprite(anim_rhythm_tweezers_falling_hair, 0, 120, 16, 0x4800, 0x100, -0x200, 0, 0, 0x8000, 0);
        affine_sprite_rotate_with_orbit(hair->sprite, TRUE);
        affine_sprite_set_orbit_distance(hair->sprite, 0x4c);
        hair->fallDistance = 0xc800;
        hair->fallSpeed = 0;
    }
    gRhythmTweezers->fallingHairsNext = 0;
}


// [func_0802ea20] Update Falling Hairs
void rhythm_tweezers_update_falling_hairs(void) {
    struct RhythmTweezersFallingHair *hair;
    u32 i = 0;

    for (i; i < RHYTHM_TWEEZERS_FALLING_HAIR_AMOUNT; i++) {
        hair = &gRhythmTweezers->fallingHairs[i];
        if (hair->fallDistance <= 0xc7ff) {
            hair->fallDistance += hair->fallSpeed += 0x20;
            hair->rotation += hair->rotationSpeed;
            affine_sprite_set_y(hair->sprite, (s16) ((hair->fallDistance >> 8) + 0x10));
            affine_sprite_set_rotation(hair->sprite, hair->rotation);
        }
    }
}


// [func_0802ea74] Spawn Falling Hair
void rhythm_tweezers_spawn_falling_hair(u32 arg0) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;
    struct RhythmTweezersFallingHair *hair = &gRhythmTweezers->fallingHairs[gRhythmTweezers->fallingHairsNext];

    hair->rotation = -0x200;
    hair->rotationSpeed = agb_random(0x1f) - 15;

    affine_sprite_set_y(hair->sprite, 0x10);
    affine_sprite_set_orbit_angle(hair->sprite, tweezers->rotation);
    affine_sprite_set_rotation(hair->sprite, hair->rotation);
    affine_sprite_set_visible(hair->sprite, 1);

    hair->fallDistance = 0;
    hair->fallSpeed = 0;
    affine_sprite_set_anim_cel(hair->sprite, arg0);

    if (++gRhythmTweezers->fallingHairsNext > (RHYTHM_TWEEZERS_FALLING_HAIR_AMOUNT - 1)) {
        gRhythmTweezers->fallingHairsNext = 0;
    }
}


// [func_0802eaf8] Initialise Tweezers
void rhythm_tweezers_init_tweezers(void) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;

    tweezers->rotation = -0x200;
    tweezers->sprite = create_affine_sprite(anim_tweezers_pluck_hit, 0x7f, 120, 16, 0x4800, 0x100, -0x200, 1, 0x7f, 0, 0);
    affine_sprite_set_orbit(tweezers->sprite, tweezers->rotation, 0x4c);
    affine_sprite_rotate_with_orbit(tweezers->sprite, TRUE);

    tweezers->isMoving = FALSE;
    tweezers->heldHair = TWEEZERS_HELD_HAIR_NONE;
    tweezers->isPulling = FALSE;
    gRhythmTweezers->existingHairs.full = 0;
}


// [func_0802eb7c] Engine Event 00 (Spawn Tweezers)
void rhythm_tweezers_spawn_tweezers(void) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;

    tweezers->isMoving = TRUE;
    tweezers->cycleTime = 0;
    tweezers->cycleTarget = ticks_to_frames(0xa8);
    tweezers->heldHair = TWEEZERS_HELD_HAIR_NONE;
}


// [func_0802eba0] Update Tweezers (Position)
void rhythm_tweezers_update_tweezers_cycle(void) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;
    u32 a = 0x4ea;
    u32 b = 0x5d5 * tweezers->cycleTime / tweezers->cycleTarget;

    tweezers->rotation = a - b;
    tweezers->cycleTime += 1;

    if (tweezers->cycleTime >= tweezers->cycleTarget) {
        tweezers->isMoving = FALSE;
        tweezers->heldHair = TWEEZERS_HELD_HAIR_NONE;
    }
}


// [func_0802ebdc] Update Tweezers (Vertical Screen Scroll)
void rhythm_tweezers_update_vertical_scroll(void) {
    // If the screen is not in the normal vertical position, scroll down.
    if (D_03004b10.BG_OFS[BG_LAYER_1].y != 0) {
        D_03004b10.BG_OFS[BG_LAYER_1].y -= 1;
    }
}


// [func_0802ebf8] Update Tweezers
void rhythm_tweezers_update_tweezers(void) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;
    s8 temp;

    rhythm_tweezers_update_vertical_scroll();
    if (tweezers->isMoving) {
        if (tweezers->isMoving == TRUE) {
            rhythm_tweezers_update_tweezers_cycle();
        }
    }

    if (tweezers->heldHair != TWEEZERS_HELD_HAIR_NONE) {
        temp = affine_sprite_get_anim_cel(tweezers->sprite);
        if (temp == affine_sprite_get_total_cels(tweezers->sprite) - 2) {
            rhythm_tweezers_spawn_falling_hair(tweezers->heldHair - 1);
            tweezers->heldHair = TWEEZERS_HELD_HAIR_NONE;
        }
    }
    affine_sprite_set_orbit_angle(tweezers->sprite, tweezers->rotation);
}


// [func_0802ec50] Graphics Init. 3
void rhythm_tweezers_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// [func_0802ec60] Graphics Init. 2
void rhythm_tweezers_init_gfx2(void) {
    u32 temp;

    func_0800c604(0);
    temp = func_08002ee0(get_current_mem_id(), rhythm_tweezers_gfx_tables[gRhythmTweezers->version], 0x2000);
    run_func_after_task(temp, &rhythm_tweezers_init_gfx3, 0);
}


// [func_0802eca0] Graphics Init. 1
void rhythm_tweezers_init_gfx1(void) {
    u32 temp;

    func_0800c604(0);
    temp = start_new_texture_loader(get_current_mem_id(), rhythm_tweezers_buffered_textures);
    run_func_after_task(temp, &rhythm_tweezers_init_gfx2, 0);
}


// [func_0802eccc] Game Engine Start
void rhythm_tweezers_engine_start(u32 version) {
    struct TextPrinter *textPrinter;

    // Standard game setup.
    gRhythmTweezers->version = version;
    rhythm_tweezers_init_gfx1(); // Load graphics.
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_0, TRUE, 0, -160, 2, 28, 0x8000);
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 30, 0x4002);

    // Rhythm Tweezers setup.
    rhythm_tweezers_init_tweezers(); // Initialise tweezers.
    rhythm_tweezers_init_falling_hairs(); // Initialise falling hairs.
    rhythm_tweezers_init_veg(); // Initialise vegetable face.
    gRhythmTweezers->maskPosition = -160;
    gRhythmTweezers->maskVelocity = -8;
    gRhythmTweezers->tutorialSprite = sprite_create(gSpriteHandler, anim_rhythm_tweezers_tutorial_text, 0, 120, 150, 0, 0, 0, 0x8000);

    // Other setup.
    textPrinter = text_printer_create_new(get_current_mem_id(), 1, 240, 30);
    text_printer_set_x_y(textPrinter, 0, 140);
    text_printer_set_layer(textPrinter, 0x8800);
    text_printer_center_by_content(textPrinter, TRUE);
    text_printer_set_palette(textPrinter, 1);
    text_printer_set_colors(textPrinter, 0);
    gameplay_set_text_printer(textPrinter);
    gameplay_set_input_buttons(A_BUTTON | DPAD_ALL, 0);
}


// [func_0802edc4] Engine Event 09 (STUB)
void rhythm_tweezers_engine_event_stub(void) {
}


// [func_0802edc8] Update Mask
void rhythm_tweezers_update_mask(void) {
    gRhythmTweezers->maskPosition = clamp_int32(gRhythmTweezers->maskPosition + gRhythmTweezers->maskVelocity, -160, 0);
    D_03004b10.BG_OFS[BG_LAYER_0].y = gRhythmTweezers->maskPosition;
}


// [func_0802ee00] Engine Event 07 (Show Mask)
void rhythm_tweezers_show_mask(void) {
    gRhythmTweezers->maskVelocity = 8;
}


// [func_0802ee10] Engine Event 08 (Hide Mask)
void rhythm_tweezers_hide_mask(void) {
    gRhythmTweezers->maskVelocity = -8;
}


// [func_0802ee24] Game Engine Update
void rhythm_tweezers_engine_update(void) {
    rhythm_tweezers_update_tweezers(); // Update tweezers.
    rhythm_tweezers_update_falling_hairs(); // Update falling hairs.
    rhythm_tweezers_update_hair_cycle(); // Update hair position cycle.
    rhythm_tweezers_update_veg(); // Update vegetable.
    rhythm_tweezers_update_mask(); // Update mask.
}


// [func_0802ee40] Game Engine Stop (STUB)
void rhythm_tweezers_engine_stop(void) {
}


// [func_0802ee44] Engine Event 01 (Reset Hair Placement Cycle)
void rhythm_tweezers_start_hair_cycle(void) {
    gRhythmTweezers->hairCycleTime = 0;
    gRhythmTweezers->hairCycleTarget = ticks_to_frames(0x48);
    gRhythmTweezers->existingHairs.full = 0;
    gRhythmTweezers->existingHairs.half = 0;
}


// [func_0802ee6c] Update Hair Placement Cycle
void rhythm_tweezers_update_hair_cycle(void) {
    gRhythmTweezers->hairCycleTime++;
    // Fantastic work, Nintendo SPD.
}


// [func_0802ee7c] Cue - Spawn
void rhythm_tweezers_cue_spawn(struct Cue *cue, struct RhythmTweezersCue *info, u32 isLongHair) {
    struct RhythmTweezersEngineData *rhythmTweezers;
    struct Animation *anim;
    u32 rotation;

    rhythmTweezers = gRhythmTweezers;
    rotation = 0x340;
    rotation -= 640 * rhythmTweezers->hairCycleTime / rhythmTweezers->hairCycleTarget;

    anim = (!isLongHair) ? anim_rhythm_tweezers_short_hair : anim_rhythm_tweezers_long_hair;
    info->sprite = create_affine_sprite(anim, 0, 120, 16, 0x4800, INT_TO_FIXED(1.0), -0x200, 1, 0x7f, 0, 0);
    affine_sprite_rotate_with_orbit(info->sprite, TRUE);

    affine_sprite_set_orbit(info->sprite, rotation, 76);
    affine_sprite_set_origin_x_y(info->sprite, &gRhythmTweezers->screenHorizontalPosition, &D_03004b10.BG_OFS[BG_LAYER_1].y);

    info->isLongHair = isLongHair;
    info->finished = FALSE;

    gRhythmTweezers->existingHairs.full++;

    if (!isLongHair) {
        play_sound_w_pitch_volume(&s_hanabi_pon_seqData, 0xd0, 0);
    } else {
        play_sound(&s_f_hair_appear_long_seqData);
    }
}


// [func_0802ef54] Cue - Update (Short Hair)
u32 rhythm_tweezers_cue_update_short(struct Cue *cue, struct RhythmTweezersCue *info, u32 runningTime, u32 duration) {
    if (runningTime > (duration * 2)) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// !TODO - It's always with these cue functions, I swear: https://decomp.me/scratch/xtw97
// [func_0802ef68] Cue - Update (Long Hair)
#include "asm/engines/rhythm_tweezers/asm_0802ef68.s"


// [func_0802f164] Cue - Despawn
void rhythm_tweezers_cue_despawn(struct Cue *cue, struct RhythmTweezersCue *info) {
    delete_affine_sprite(info->sprite);
}


// [func_0802f170] Cue - Hit (Short Hair)
void rhythm_tweezers_cue_hit_short(struct Cue *cue, struct RhythmTweezersCue *info, u32 pressed, u32 released) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;
    struct RhythmTweezersVegetable *vegetable = &gRhythmTweezers->vegetable;
    u32 temp;

    affine_sprite_set_anim(info->sprite, anim_rhythm_tweezers_hair_stubble, 0, 0, 0, 0);
    affine_sprite_set_anim(tweezers->sprite, anim_tweezers_pluck_hit, 0, 1, 0x7f, 0);
    D_03004b10.BG_OFS[BG_LAYER_1].y = 2;

    if (tweezers->heldHair) rhythm_tweezers_spawn_falling_hair(tweezers->heldHair - 1);
    tweezers->heldHair = TWEEZERS_HELD_HAIR_FULL;

    sprite_set_anim_cel(gSpriteHandler, vegetable->spriteCurrent, 1);
    gRhythmTweezers->existingHairs.full -= 1;

    temp = *(u32 *)(&gRhythmTweezers->existingHairs);
    if (temp == 0) {
        sprite_set_playback(gSpriteHandler, vegetable->spriteCurrent, 0, 0, 0);
        sprite_set_anim_cel(gSpriteHandler, vegetable->spriteCurrent, 2);
    }
}


// [func_0802f21c] Cue - Hit/Barely (Long Hair)
void rhythm_tweezers_cue_hit_long(struct Cue *cue, struct RhythmTweezersCue *info, u32 pressed, u32 released) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;
    u32 temp;

    gameplay_ignore_this_cue_result();
    if (tweezers->heldHair != TWEEZERS_HELD_HAIR_NONE) rhythm_tweezers_spawn_falling_hair(tweezers->heldHair - 1);
    affine_sprite_set_visible(tweezers->sprite, 0);
    affine_sprite_set_anim(info->sprite, anim_tweezers_pull, 0, 0, 0, 0);

    info->rotation = tweezers->rotation;
    tweezers->isPulling = TRUE;
    info->finished = TRUE;
    info->pullTime = 0;
    info->pullTarget = ticks_to_frames(0x0C) - gameplay_get_last_hit_offset();
    gameplay_set_input_buttons(0, 0);

    stop_sound(&s_f_hair_nuki_long_seqData);
    play_sound(&s_f_hair_tuneru_seqData);
}


// [func_0802f2a0] Cue - Barely (Short Hair)
void rhythm_tweezers_cue_barely_short(struct Cue *cue, struct RhythmTweezersCue *info, u32 pressed, u32 released) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;
    struct RhythmTweezersVegetable *vegetable = &gRhythmTweezers->vegetable;

    affine_sprite_set_anim(info->sprite, anim_rhythm_tweezers_hair_stubble, 0, 1, 0x7f, 0);
    affine_sprite_set_anim(tweezers->sprite, anim_tweezers_pluck_barely, 0, 1, 0x7f, 0);

    if (tweezers->heldHair != TWEEZERS_HELD_HAIR_NONE) rhythm_tweezers_spawn_falling_hair(tweezers->heldHair - 1);
    tweezers->heldHair = TWEEZERS_HELD_HAIR_BARELY;

    sprite_set_anim_cel(gSpriteHandler, vegetable->spriteCurrent, 1);

    gRhythmTweezers->existingHairs.full -= 1;
    gRhythmTweezers->existingHairs.half += 1;
}


// [func_0802f330] Cue - Miss
void rhythm_tweezers_cue_miss(struct Cue *cue, struct RhythmTweezersCue *info) {
    beatscript_enable_loops();
}


// [func_0802f33c] Input Event
void rhythm_tweezers_input_event(u32 pressed, u32 released) {
    struct RhythmTweezersTweezers *tweezers = &gRhythmTweezers->tweezers;

    affine_sprite_set_anim(tweezers->sprite, anim_tweezers_pluck_miss, 0, 1, 0x7f, 0);

    if (tweezers->heldHair != TWEEZERS_HELD_HAIR_NONE) {
        rhythm_tweezers_spawn_falling_hair(tweezers->heldHair - 1);
    }
    tweezers->heldHair = TWEEZERS_HELD_HAIR_NONE;
}


// [func_0802f378] Common Event 0 (Beat Animation, Unimplemented)
void rhythm_tweezers_common_beat_animation(void) {
}


// [func_0802f37c] Common Event 1 (Display Text, Unimplemented)
void rhythm_tweezers_common_display_text(void) {
}


// [func_0802f380] Engine Event 05 (Hide Tutorial Text, Unused)
void rhythm_tweezers_hide_tutorial_text(void) {
    sprite_set_visible(gSpriteHandler, gRhythmTweezers->tutorialSprite, FALSE);
}
