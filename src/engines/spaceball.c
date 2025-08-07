#include "engines/spaceball.h"

#include "src/code_08001360.h"
#include "src/code_08007468.h"
#include "src/affine_sprite.h"
#include "src/lib_0804ca80.h"

extern s32 (*math_sqrt)(s32);
extern s32 (*fast_udivsi3)(s32, s32);

// For readability.
#define gSpaceball ((struct SpaceballEngineData *)gCurrentEngineData)


/* SPACEBALL */


// Initialise/Reset BG Star Position
void spaceball_reset_star(u32 current) {
    struct SpaceballStar *star;
    s32 scale, x, y;

    scale = agb_random(INT_TO_FIXED(3.0)) + INT_TO_FIXED(1.0);
    x = fast_divsi3((agb_random(SCREEN_WIDTH) - SCREEN_CENTER_X) * scale, INT_TO_FIXED(1.0));
    y = fast_divsi3((agb_random(SCREEN_HEIGHT) - SCREEN_CENTER_Y) * scale, INT_TO_FIXED(1.0));

    star = &gSpaceball->stars[current];
    star->x = x;
    star->y = y;
    star->z = gSpaceball->zoom + scale;
}


// Update BG Star Positions (X, Y)
void spaceball_update_stars_x_y(void) {
    struct SpaceballStar *star;
    s16 sprite;
    s32 scale, x, y;
    u32 i;

    for (i = 0; i < SPACEBALL_STAR_AMOUNT; i++) {
        sprite = gSpaceball->starSprite[i];
        star = &gSpaceball->stars[i];

        scale = fast_divsi3(INT_TO_FIXED(256.0), star->z - gSpaceball->zoom);
        x = FIXED_TO_INT(star->x * scale);
        y = FIXED_TO_INT(star->y * scale);
        sprite_set_x_y(gSpriteHandler, sprite, x + SCREEN_CENTER_X, y + SCREEN_CENTER_Y);
    }
}


// Update BG Star Positions (Z)
void spaceball_update_stars_z(void) {
    struct SpaceballStar *star;
    s32 zMin = gSpaceball->zoom + INT_TO_FIXED(1);
    s32 zMax = gSpaceball->zoom + INT_TO_FIXED(4);
    u32 i;

    for (i = 0; i < SPACEBALL_STAR_AMOUNT; i++) {
        star = &gSpaceball->stars[i];
        star->z -= 8;
        if ((star->z < zMin) || (star->z > zMax)) {
            spaceball_reset_star(i);
        }
    }
}


// Update Entity Position
void spaceball_update_entity(struct AffineSprite *sprite, s32 x, s32 y, s32 z) {
    s32 scale;

    z -= gSpaceball->zoom;
    scale = fast_divsi3(INT_TO_FIXED(256.0), z);

    x = FIXED_TO_INT(x * scale);
    y = FIXED_TO_INT(y * scale);
    affine_sprite_set_x_y(sprite, x + SCREEN_CENTER_X, y + SCREEN_CENTER_Y);
    affine_sprite_set_scale(sprite, scale);
}


// Update Batter Position
void spaceball_update_batter(struct AffineSprite *sprite, s32 x, s32 y, s32 z, struct Animation *animClose, struct Animation *animFar) {
    s32 scale;

    z -= gSpaceball->zoom;
    scale = fast_divsi3(INT_TO_FIXED(256.0), z);

    x = FIXED_TO_INT(x * scale);
    y = FIXED_TO_INT(y * scale);
    affine_sprite_set_x_y(sprite, x + SCREEN_CENTER_X, y + SCREEN_CENTER_Y);

    if (scale > INT_TO_FIXED(0.5)) {
        affine_sprite_set_scale(sprite, scale);
        affine_sprite_set_anim(sprite, animClose, -1, 1, 0x7f, 0);
    } else {
        scale = fast_divsi3(INT_TO_FIXED(512.0), z);
        affine_sprite_set_scale(sprite, scale);
        affine_sprite_set_anim(sprite, animFar, -1, 1, 0x7f, 0);
    }
}


// Update Entities, Stars & Camera
void spaceball_update_graphics(void) {
    s32 scaleH, scaleV, h, v;

    // Update Entities
    spaceball_update_batter(gSpaceball->batter.sprite, gSpaceball->batter.x, gSpaceball->batter.y,
            gSpaceball->batter.z, gSpaceball->batter.animClose, gSpaceball->batter.animFar);

    spaceball_update_entity(gSpaceball->pitcher.sprite, gSpaceball->pitcher.x, gSpaceball->pitcher.y,
            gSpaceball->pitcher.z);

    spaceball_update_entity(gSpaceball->umpire.sprite, gSpaceball->umpire.x, gSpaceball->umpire.y,
            gSpaceball->umpire.z);

    spaceball_update_entity(gSpaceball->poofR.sprite, gSpaceball->poofR.x, gSpaceball->poofR.y,
            gSpaceball->poofR.z);

    spaceball_update_entity(gSpaceball->poofL.sprite, gSpaceball->poofL.x, gSpaceball->poofL.y,
            gSpaceball->poofL.z);

    // Update BG
    scaleH = -INT_TO_FIXED(gSpaceball->zoom * SCREEN_WIDTH);
    if (scaleH < 0) scaleH += 0xff;
    h = FIXED_TO_INT(scaleH);
    scaleV = -INT_TO_FIXED(gSpaceball->zoom * SCREEN_HEIGHT);
    if (scaleV < 0) scaleV += 0xff;
    v = FIXED_TO_INT(scaleV);
    func_08008910(BG_LAYER_2, INT_TO_FIXED(128), INT_TO_FIXED(176), h, v, 0);

    // Update Stars
    if (gSpaceball->currentStar < SPACEBALL_STAR_AMOUNT) {
        gSpaceball->starSprite[gSpaceball->currentStar] = sprite_create(gSpriteHandler, anim_spaceball_bg_star, 0, 0, 0, 0xc800, 1, 0, 0);
        spaceball_reset_star(gSpaceball->currentStar);
        gSpaceball->currentStar++;
    } else {
        spaceball_update_stars_z();
        spaceball_update_stars_x_y();
    }
}


// GFX_INIT Func_02
void spaceball_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// GFX_INIT Func_01
void spaceball_init_gfx2(void) {
    u32 data;

    func_0800c604(0);
    data = func_08002ee0(get_current_mem_id(), spaceball_gfx_tables[gSpaceball->version], 0x2000);
    run_func_after_task(data, spaceball_init_gfx3, 0);
}


// GFX_INIT Func_00
void spaceball_init_gfx1(void) {
    u32 data;

    func_0800c604(0);
    data = start_new_texture_loader(get_current_mem_id(), spaceball_buffered_textures);
    run_func_after_task(data, spaceball_init_gfx2, 0);
}


// MAIN - Init
void spaceball_engine_start(u32 ver) {
    gSpaceball->version = ver;
    spaceball_init_gfx1();
    scene_set_video_mode(VIDEO_MODE_2TEXT_1ROT);
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_2, TRUE, 0, 0, 0, 30, (BGCNT_TILEMAP_SIZE(BG_ROT_TILEMAP_32x32) | BGCNT_256_PALETTE | BGCNT_PRIORITY(BG_PRIORITY_LOW)));
    func_08008910(BG_LAYER_2, INT_TO_FIXED(SCREEN_CENTER_X), INT_TO_FIXED(SCREEN_CENTER_Y), INT_TO_FIXED(SCREEN_WIDTH), INT_TO_FIXED(SCREEN_HEIGHT), 0);
    scene_hide_bg_layer(BG_LAYER_0);
    scene_hide_bg_layer(BG_LAYER_1);
    scene_hide_bg_layer(BG_LAYER_3);

    gSpaceball->batter.sprite = create_affine_sprite(anim_spaceball_batter_green, 0, 170, 80, 0x4800, INT_TO_FIXED(0.5), 0, 0, 0, 0, TRUE);
    gSpaceball->batter.x = 50;
    gSpaceball->batter.y = 0;
    gSpaceball->batter.z = 0;
    gSpaceball->batter.swingTimer = 0;
    spaceball_set_batter_type(0);

    gSpaceball->pitcher.sprite = create_affine_sprite(anim_spaceball_pitcher, 2, 70, 128, 0x4800, INT_TO_FIXED(0.5), 0, 0, 0, 0, TRUE);
    gSpaceball->pitcher.x = -50;
    gSpaceball->pitcher.y = 48;
    gSpaceball->pitcher.z = 0;

    gSpaceball->umpire.sprite = create_affine_sprite(anim_spaceball_ufo_sway, 2, 120, 89, 0x4864, INT_TO_FIXED(0.5), 0, 1, 2, 0x8000, TRUE);
    gSpaceball->umpire.x = 0;
    gSpaceball->umpire.y = 9;
    gSpaceball->umpire.z = 0;
    affine_sprite_set_visible(gSpaceball->umpire.sprite, TRUE);

    gSpaceball->poofR.sprite = create_affine_sprite(anim_spaceball_poof, 2, 154, 132, 0x4864, INT_TO_FIXED(1.0), 0, 1, 0, 0x8002, TRUE);
    gSpaceball->poofR.x = 34;
    gSpaceball->poofR.y = 52;
    gSpaceball->poofR.z = 0;

    gSpaceball->poofL.sprite = create_affine_sprite(anim_spaceball_poof, 2, 122, 132, 0x4864, INT_TO_FIXED(1.0), 0, 1, 0, 0x8002, TRUE);
    gSpaceball->poofL.x = 2;
    gSpaceball->poofL.y = 52;
    gSpaceball->poofL.z = 0;
    affine_sprite_set_flip_h(gSpaceball->poofL.sprite, TRUE);

    gSpaceball->currentStar = 0;
    gSpaceball->zoom = INT_TO_FIXED(-0.5);
    gSpaceball->totalMissed = 0;
    gSpaceball->spaceballType = 0;
    gameplay_set_input_buttons(A_BUTTON, 0);
}


// ENGINE Func_06 - STUB
void spaceball_engine_event_stub(void) {
}


// ENGINE Func_00 - Pitcher Prepare
void spaceball_prepare_pitcher(void) {
    affine_sprite_set_playback(gSpaceball->pitcher.sprite, 0, 0, 0);
    affine_sprite_set_anim_cel(gSpaceball->pitcher.sprite, 0);
}


// Update Batter Swing
void spaceball_update_batter_swing(struct SpaceballBatter *batter) {
    if (batter->swingTimer == 0) return;

    batter->swingTimer--;
    if (batter->swingTimer == 0) {
        affine_sprite_set_playback(batter->sprite, 0, 0, 0);
        affine_sprite_set_anim_cel(batter->sprite, 0);
        gameplay_set_input_buttons(A_BUTTON, 0);
    }
}


// ENGINE Func_01 - Loop Exit Condition (Practice)
void spaceball_loop_exit_condition(void) {
    if (gSpaceball->totalMissed == 0) {
        beatscript_disable_loops();
    } else {
        beatscript_enable_loops();
    }
    gSpaceball->totalMissed = 0;
}


// ENGINE Func_02 - Set Camera Zoom
void spaceball_set_camera_zoom(u32 controls) {
    s32 target = (s32) controls >> 0x10;
    u32 time = controls & 0xffff;
    scene_start_integer_interp(2, ticks_to_frames(time), &gSpaceball->zoom, gSpaceball->zoom, target);
}


// ENGINE Func_03 - Set Batter Variant
void spaceball_set_batter_type(u32 index) {
    gSpaceball->batter.animClose = spaceball_anim_table_batter_close_tables[gSpaceball->version][index];
    gSpaceball->batter.animFar = spaceball_anim_table_batter_far_tables[gSpaceball->version][index];
}


// ENGINE Func_05 - Set Next Spaceball Sprite
void spaceball_set_ball_type(u32 index) {
    gSpaceball->spaceballType = index;
}


// ENGINE Func_04 - Set Umpire Animation
void spaceball_open_ufo(u32 show) {
    struct AffineSprite *sprite = gSpaceball->umpire.sprite;
    if (show) {
        affine_sprite_set_anim(sprite, anim_spaceball_ufo_open, 0, 1, 1, 0);
    } else {
        affine_sprite_set_anim(sprite, anim_spaceball_ufo_sway, 0, 1, 2, 0);
    }
}


// MAIN - Update
void spaceball_engine_update(void) {
    spaceball_update_batter_swing(&gSpaceball->batter);
    spaceball_update_graphics();
}


// MAIN - Close (STUB)
void spaceball_engine_stop(void) {
}


// CUE - Spawn
void spaceball_cue_spawn(struct Cue *cue, struct SpaceballCue *cueInfo, u32 arcTime) {
    u32 temp;
    u32 div;
    u32 time;

    cueInfo->state = 0;
    cueInfo->rotation = agb_random(0x800);
    cueInfo->rotationSpeed = 0x40;
    cueInfo->z = 0;
    cueInfo->unk1C = (arcTime >= 0x18) ? (90 * arcTime / 0x18) : 90;
    cueInfo->sprite = create_affine_sprite(spaceball_anim_table_ball_tables[gSpaceball->version][gSpaceball->spaceballType], 0, 70, 120, 0x479c, INT_TO_FIXED(1), cueInfo->rotation, 1, 0, 0, TRUE);

    temp = cueInfo->unk1C - 48;
    div = math_sqrt(INT_TO_FIXED(1.0) * INT_TO_FIXED(temp) / cueInfo->unk1C);
    time = ticks_to_frames(arcTime);
    cueInfo->endTime = 2 * INT_TO_FIXED(time) / (div + INT_TO_FIXED(1.0));

    spaceball_update_entity(cueInfo->sprite, -50, 40, cueInfo->z);
    cueInfo->missed = FALSE;
    affine_sprite_set_playback(gSpaceball->pitcher.sprite, 1, 0x7f, 0);
    affine_sprite_set_anim_cel(gSpaceball->pitcher.sprite, 1);
}


// Update Spaceball (Launch)
u32 spaceball_cue_update_launch(struct Cue *cue, struct SpaceballCue *cueInfo, u32 runningTime, u32 duration) {
    u32 temp;

    if (runningTime > cueInfo->endTime) {
        play_sound(&s_f_batter_ball_land_seqData);
        affine_sprite_set_anim_cel(gSpaceball->poofR.sprite, 0);
        affine_sprite_set_visible(gSpaceball->poofR.sprite, TRUE);
        affine_sprite_set_anim_cel(gSpaceball->poofL.sprite, 0);
        affine_sprite_set_visible(gSpaceball->poofL.sprite, TRUE);
        if (!cueInfo->missed) {
            gameplay_add_cue_result(gameplay_get_cue_marking_criteria(cue), 2, 0);
        }
        return TRUE;
    }
    else {
        temp = runningTime - (cueInfo->endTime / 2);
        cueInfo->x = math_lerp(70, 138, runningTime, cueInfo->endTime);
        cueInfo->y = 120 - (cueInfo->unk1C - fast_udivsi3(cueInfo->unk1C * (temp << 2) * temp, cueInfo->endTime * cueInfo->endTime));
        spaceball_update_entity(cueInfo->sprite, cueInfo->x - SCREEN_CENTER_X, cueInfo->y - SCREEN_CENTER_Y, cueInfo->z);
        affine_sprite_set_rotation(cueInfo->sprite, cueInfo->rotation);
        cueInfo->rotation += cueInfo->rotationSpeed;
        return FALSE;
    }
}


// Update Spaceball (Hit)
u32 spaceball_cue_update_hit(struct Cue *cue, struct SpaceballCue *cueInfo, u32 runningTime, u32 duration) {
    if (cueInfo->z < gSpaceball->zoom + INT_TO_FIXED(0.25)) return TRUE;

    spaceball_update_entity(cueInfo->sprite, cueInfo->x - SCREEN_CENTER_X, cueInfo->y - SCREEN_CENTER_Y, cueInfo->z);
    affine_sprite_set_rotation(cueInfo->sprite, cueInfo->rotation);
    cueInfo->rotation += cueInfo->rotationSpeed;
    cueInfo->z -= INT_TO_FIXED(0.25);
    return FALSE;
}


// Update Spaceball (Barely)
u32 spaceball_cue_update_barely(struct Cue *cue, struct SpaceballCue *cueInfo, u32 runningTime, u32 duration) {
    if (cueInfo->z < gSpaceball->zoom + INT_TO_FIXED(0.25)) return TRUE;
    if (FIXED_TO_INT(cueInfo->y) > 1000) return TRUE;

    cueInfo->x += cueInfo->xSpeed;
    cueInfo->y += cueInfo->ySpeed;
    cueInfo->ySpeed += INT_TO_FIXED(0.25);
    cueInfo->z -= 4;
    spaceball_update_entity(cueInfo->sprite, cueInfo->x - SCREEN_CENTER_X, (cueInfo->y >> 8) - SCREEN_CENTER_Y, cueInfo->z);
    affine_sprite_set_rotation(cueInfo->sprite, cueInfo->rotation);
    cueInfo->rotation += cueInfo->rotationSpeed;
    return FALSE;
}


// CUE - Update
u32 spaceball_cue_update(struct Cue *cue, struct SpaceballCue *cueInfo, u32 runningTime, u32 duration) {
    u32 finished;

    switch (cueInfo->state) {
        case SPACEBALL_CUE_STATE_LAUNCH:
            finished = spaceball_cue_update_launch(cue, cueInfo, runningTime, duration);
            break;
        case SPACEBALL_CUE_STATE_HIT:
            finished = spaceball_cue_update_hit(cue, cueInfo, runningTime, duration);
            break;
        case SPACEBALL_CUE_STATE_BARELY:
            finished = spaceball_cue_update_barely(cue, cueInfo, runningTime, duration);
            break;
    }
    return finished;
}


// CUE - Despawn
void spaceball_cue_despawn(struct Cue *cue, struct SpaceballCue *cueInfo) {
    delete_affine_sprite(cueInfo->sprite);
}


// CUE - Hit
void spaceball_cue_hit(struct Cue *cue, struct SpaceballCue *cueInfo, u32 pressed, u32 released) {
    struct SpaceballBatter *batter = &gSpaceball->batter;

    affine_sprite_set_playback(batter->sprite, 1, 0x7f, 0);
    affine_sprite_set_anim_cel(batter->sprite, 1);
    batter->swingTimer = ticks_to_frames(0x0A);
    cueInfo->rotationSpeed = 8;
    cueInfo->state = SPACEBALL_CUE_STATE_HIT;
}


// CUE - Barely
void spaceball_cue_barely(struct Cue *cue, struct SpaceballCue *cueInfo, u32 pressed, u32 released) {
    struct SpaceballBatter *batter = &gSpaceball->batter;

    affine_sprite_set_playback(batter->sprite, 1, 0x7f, 0);
    affine_sprite_set_anim_cel(batter->sprite, 1);
    batter->swingTimer = ticks_to_frames(0x0A);
    cueInfo->xSpeed = (gameplay_get_last_hit_offset() < 0) ? -3 : 3;
    cueInfo->rotationSpeed = -8;
    cueInfo->y = INT_TO_FIXED(cueInfo->y);
    cueInfo->ySpeed = INT_TO_FIXED(-4);
    cueInfo->state = SPACEBALL_CUE_STATE_BARELY;
}


// CUE - Miss
void spaceball_cue_miss(struct Cue *cue, struct SpaceballCue *cueInfo) {
    gSpaceball->totalMissed++;
    cueInfo->missed = TRUE;
}


// MAIN - Input Event
void spaceball_input_event(u32 pressed, u32 released) {
    struct SpaceballBatter *batter = &gSpaceball->batter;

    affine_sprite_set_playback(batter->sprite, 1, 0x7f, 0);
    affine_sprite_set_anim_cel(batter->sprite, 1);
    batter->swingTimer = ticks_to_frames(0x0A);
    gameplay_set_input_buttons(0, 0);
}


// COMMON Func_00 - STUB
void spaceball_common_beat_animation(void) {
}


// COMMON Func_01 - STUB
void spaceball_common_display_text(void) {
}
