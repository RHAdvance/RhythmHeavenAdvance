#include "engines/fireworks.h"

#include "src/code_08001360.h"
#include "src/bitmap_font.h"
#include "src/code_08007468.h"
#include "src/text_printer.h"
#include "src/code_0800b778.h"
#include "src/lib_0804ca80.h"

// For readability.
#define gFireworks ((struct FireworksEngineData *)gCurrentEngineData)

enum SpiritSparklerStatesEnum {
    SPIRIT_SPARKLER_STATE_0,
    SPIRIT_SPARKLER_STATE_1,
    SPIRIT_SPARKLER_STATE_2
};

enum NormalFireworkStatesEnum {
    NORMAL_FIREWORK_STATE_0,
    NORMAL_FIREWORK_STATE_1,
    NORMAL_FIREWORK_STATE_2,
    NORMAL_FIREWORK_STATE_3
};

enum TaikoBomberStatesEnum {
    TAIKO_BOMBER_STATE_FLYING,
    TAIKO_BOMBER_STATE_EXPLODING
};


/* FIREWORKS */


// Graphics Init. 3
void fireworks_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}


// Graphics Init. 2
void fireworks_init_gfx2(void) {
    u32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), fireworks_gfx_tables[gFireworks->version], 0x2000);
    run_func_after_task(task, fireworks_init_gfx3, 0);
}


// Graphics Init. 1
void fireworks_init_gfx1(void) {
    u32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), fireworks_buffered_textures);
    run_func_after_task(task, fireworks_init_gfx2, 0);
}


// Game Engine Start
void fireworks_engine_start(u32 version) {
    struct TextPrinter *textPrinter;
    struct PrintedTextAnim *textAnim;
    u8 i;

    gFireworks->version = version;
    fireworks_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 0);
    gFireworks->unk4 = scene_create_obj_font_printer(0x340, 2);
    textAnim = bmp_font_obj_print_c(gFireworks->unk4, D_0805a3d0, 1, 15);
    gFireworks->textSprite = sprite_create(gSpriteHandler, textAnim->frames, 0, 120, 144, 0x7f7, 0, 0, 0);
    gFireworks->screenBrightness = 0;
    gFireworks->patternTableNext = 0;
    D_03004b10.BLDMOD = BLDMOD_BG1_SRC | BLDMOD_BLEND_MODE(BLEND_MODE_LIGHTEN);
    D_03004b10.COLEY = 0;
    gFireworks->skipTutorialSprite = sprite_create(gSpriteHandler, anim_fireworks_skip_tutorial_icon, 0, 208, 152, 0x802, 0, 0, 0);
    sprite_set_visible(gSpriteHandler, gFireworks->skipTutorialSprite, FALSE);
    gFireworks->patternMode = FIREWORKS_PATTERN_MODE_0;
    gFireworks->patternDefault = FIREWORKS_PATTERN_L3;

    for (i = 0; i < FIREWORKS_PARTICLE_AMOUNT; i++) {
        gFireworks->particles[i].sprite = sprite_create(gSpriteHandler, anim_fireworks_particle_red, 0, 0, 0, 0x801, 0, 0, 0);
        gFireworks->particles[i].active = FALSE;
        sprite_set_visible(gSpriteHandler, gFireworks->particles[i].sprite, FALSE);
    }

    textPrinter = text_printer_create_new(get_current_mem_id(), 4, 240, 30);
    text_printer_set_x_y(textPrinter, 0, 8);
    text_printer_set_layer(textPrinter, 0x7f7);
    text_printer_center_by_content(textPrinter, FALSE);
    text_printer_set_palette(textPrinter, 0);
    text_printer_set_colors(textPrinter, 0);
    gameplay_set_text_printer(textPrinter);
    gameplay_set_input_buttons(A_BUTTON, 0);
    gameplay_enable_cue_input_overlap(TRUE);
}


// Engine Event 00 (Set Pattern Mode)
void fireworks_set_pattern_mode(u32 mode) {
    gFireworks->patternMode = mode;

    if (mode == FIREWORKS_PATTERN_MODE_USE_TABLE) {
        sprite_set_visible(gSpriteHandler, gFireworks->skipTutorialSprite, FALSE);
    }
}


// Engine Event 01 (Play Sound)
void fireworks_play_sound(u32 sound) {
    switch (sound) {
        case FIREWORKS_SFX_COME_ON:
            play_sound_in_player(2, &s_intro_comeon_seqData);
            break;
        case FIREWORKS_SFX_ONE:
            play_sound_in_player(2, &s_intro_one_seqData);
            break;
        case FIREWORKS_SFX_TWO:
            play_sound_in_player(2, &s_intro_two_seqData);
            break;
        case FIREWORKS_SFX_THREE:
            play_sound_in_player(2, &s_intro_three_seqData);
            break;
        case FIREWORKS_SFX_NUEI:
            play_sound(CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_SFX) != 0 ?
                &s_f_hanabi_v_nuei_en_seqData : &s_f_hanabi_v_nuei_seqData
            );
            break;
    }
}


// Engine Event 02 (Set Pattern)
void fireworks_set_pattern(u32 pattern) {
    gFireworks->patternDefault = pattern;
}


// Update Particles
void fireworks_update_explosion(void) {
    u8 i;

    for (i = 0; i < FIREWORKS_PARTICLE_AMOUNT; i++) {
        if (gFireworks->particles[i].active) {
            gFireworks->particles[i].x += gFireworks->particles[i].velX;
            gFireworks->particles[i].velX -= gFireworks->particles[i].velX / 32;
            gFireworks->particles[i].y += gFireworks->particles[i].velY;
            gFireworks->particles[i].velY -= (gFireworks->particles[i].velY / 32);
            gFireworks->particles[i].velY += 6;
            sprite_set_x_y(gSpriteHandler, gFireworks->particles[i].sprite, FIXED_TO_INT(gFireworks->particles[i].x), FIXED_TO_INT(gFireworks->particles[i].y));
            if (sprite_get_anim_cel(gSpriteHandler, gFireworks->particles[i].sprite) >= fireworks_particle_durations[gFireworks->particles[i].colour]) {
                gFireworks->particles[i].active = FALSE;
                sprite_set_visible(gSpriteHandler, gFireworks->particles[i].sprite, FALSE);
            }
        }
    }
}


// Create Explosion
void fireworks_create_explosion(u8 pattern, s32 x, s32 y) {
    u8 i;
    u8 colour;
    s32 min;
    u32 max;

    switch (pattern) {
        case FIREWORKS_PATTERN_L3:
            min = 0;
            max = 24;
            colour = agb_random(6);
            break;
        case FIREWORKS_PATTERN_C3:
            min = 24;
            max = 48;
            colour = agb_random(6);
            break;
        case FIREWORKS_PATTERN_R3:
            min = 48;
            max = 72;
            colour = agb_random(6);
            break;
        case FIREWORKS_PATTERN_LL2:
            min = 0;
            max = 16;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_CL2:
            min = 16;
            max = 32;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_CR2:
            min = 32;
            max = 48;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_RR2:
            min = 48;
            max = 64;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_L3_BARELY:
        case FIREWORKS_PATTERN_LL2_BARELY:
            min = 0;
            max = 8;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_C3_BARELY:
        case FIREWORKS_PATTERN_CL2_BARELY:
            min = 16;
            max = 24;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_R3_BARELY:
            min = 40;
            max = 48;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_CR2_BARELY:
            min = 32;
            max = 40;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_RR2_BARELY:
            min = 48;
            max = 56;
            colour = agb_random(3);
            break;
        case FIREWORKS_PATTERN_SP_STAR:
            min = 16;
            max = 40;
            colour = FIREWORKS_PARTICLE_MULTI;
            break;
        case FIREWORKS_PATTERN_SP_CIRCLE:
        default:
            min = 0;
            max = 32;
            colour = FIREWORKS_PARTICLE_MULTI;
            break;
        case FIREWORKS_PATTERN_SP_SPIRAL:
            min = 0;
            max = 32;
            colour = FIREWORKS_PARTICLE_MULTI;
            break;
        case FIREWORKS_PATTERN_SP_SMILE:
            min = 0;
            max = 24;
            colour = FIREWORKS_PARTICLE_MULTI;
            break;
        case FIREWORKS_PATTERN_SP_TSUNKU:
            min = 0;
            max = 31;
            colour = FIREWORKS_PARTICLE_MULTI;
            break;
    }

    for (i = min; i < max; i++) {
        if (pattern == FIREWORKS_PATTERN_SP_CIRCLE) {
            // Inner Circle [16 Particles]
            if (i < (min + 16)) {
                gFireworks->particles[i].initAngle = (i - min) * 16;
                gFireworks->particles[i].initVel = 240;
            }
            // Outer Circle [16 Particles]
            else {
                gFireworks->particles[i].initAngle = ((i - min - 16) * 16) + 8;
                gFireworks->particles[i].initVel = 480;
            }
        }

        else if (pattern == FIREWORKS_PATTERN_SP_SPIRAL) {
            // Inner Loop [16 Particles]
            if (i < (min + 16)) {
                gFireworks->particles[i].initAngle = (i - min) * 16;
                gFireworks->particles[i].initVel = ((i - min) * 16) + 160;
            }
            // Outer Loop [16 Particles]
            else {
                gFireworks->particles[i].initAngle = (i - min - 16) * 16;
                gFireworks->particles[i].initVel = ((i - min - 16) * 16) + 400;
            }
        }

        else if (pattern == FIREWORKS_PATTERN_SP_SMILE) {
            // Left Eye [8 Particles]
            if (i < (min + 8)) {
                gFireworks->particles[i].initAngle = ((i - min) * 4) - 112;
                gFireworks->particles[i].initVel = 720 - ((i - min) * 64);
            }
            // Right Eye [8 Particles]
            else if (i < (min + 16)) {
                gFireworks->particles[i].initAngle = -16 - ((i - min - 8) * 4);
                gFireworks->particles[i].initVel = 720 - ((i - min - 8) * 64);
            }
            // Mouth [8 Particles]
            else {
                gFireworks->particles[i].initAngle = ((i - min - 16) * 16) + 8;
                gFireworks->particles[i].initVel = 480;
            }
        }

        else if (pattern == FIREWORKS_PATTERN_SP_TSUNKU) {
            // This one just reads it from a table, lol.
            gFireworks->particles[i].initAngle = fireworks_mars_pattern[i - min].initAngle;
            gFireworks->particles[i].initVel = fireworks_mars_pattern[i - min].initVelocity;
        }

        else { // STANDARD FIREWORK PATTERN
            // Inner Circle [8 Particles]
            if (i < (min + 8)) {
                gFireworks->particles[i].initAngle = (i - min) * 32;
                gFireworks->particles[i].initVel = 240;
            }
            // Middle Circle [8 Particles]
            else if (i < (min + 16)) {
                gFireworks->particles[i].initAngle = ((i - min - 8) * 32) + 16;
                gFireworks->particles[i].initVel = 480;
            }
            // Outer Circle [8 Particles]
            else {
                gFireworks->particles[i].initAngle = ((i - min - 16) * 32);
                gFireworks->particles[i].initVel = 640;
            }
        }

        gFireworks->particles[i].velX = gFireworks->particles[i].initVel * coss2(gFireworks->particles[i].initAngle) / 256;
        gFireworks->particles[i].velY = gFireworks->particles[i].initVel * sins2(gFireworks->particles[i].initAngle) / 256;
        gFireworks->particles[i].x = x + gFireworks->particles[i].velX;
        gFireworks->particles[i].y = y + gFireworks->particles[i].velY;
        gFireworks->particles[i].colour = colour;

        if ((pattern == FIREWORKS_PATTERN_L3) ||
            (pattern == FIREWORKS_PATTERN_C3) ||
            (pattern == FIREWORKS_PATTERN_R3)) { // STANDARD FIREWORK PATTERN
            if (i < (min + 8)) {
                gFireworks->particles[i].colour = fireworks_particle_combinations[colour].inner;
            }
            else if (i < (min + 16)) {
                gFireworks->particles[i].colour = fireworks_particle_combinations[colour].middle;
            }
            else {
                gFireworks->particles[i].colour = fireworks_particle_combinations[colour].outer;
            }
        }

        gFireworks->particles[i].active = TRUE;
        sprite_set_visible(gSpriteHandler, gFireworks->particles[i].sprite, TRUE);
        sprite_set_x_y(gSpriteHandler, gFireworks->particles[i].sprite, FIXED_TO_INT(gFireworks->particles[i].x), FIXED_TO_INT(gFireworks->particles[i].y));

        if (gFireworks->particles[i].colour == FIREWORKS_PARTICLE_RED) {
            sprite_set_anim(gSpriteHandler, gFireworks->particles[i].sprite, anim_fireworks_particle_red, 0, 1, 127, 0);
        }
        else if (gFireworks->particles[i].colour == FIREWORKS_PARTICLE_GREEN) {
            sprite_set_anim(gSpriteHandler, gFireworks->particles[i].sprite, anim_fireworks_particle_green, 0, 1, 127, 0);
        }
        else if (gFireworks->particles[i].colour == FIREWORKS_PARTICLE_BLUE) {
            sprite_set_anim(gSpriteHandler, gFireworks->particles[i].sprite, anim_fireworks_particle_blue, 0, 1, 127, 0);
        }
        else {
            sprite_set_anim(gSpriteHandler, gFireworks->particles[i].sprite, anim_fireworks_particle_tri_rgb, 0, 1, 127, 0);
        }
    }
}


// Game Engine Update
void fireworks_engine_update(void) {
    fireworks_update_explosion();
    if (gFireworks->screenBrightness != 0) {
        gFireworks->screenBrightness--;
        D_03004b10.COLEY = gFireworks->screenBrightness;
    }
}


// Game Engine Stop
void fireworks_engine_stop(void) {
}


// Cue - Spawn
void fireworks_cue_spawn(struct Cue *cue, struct FireworksCue *info, u32 type) {
    u16 yDistance;
    u8 i;

    info->type = type;
    info->state = 0;
    info->exploded = FALSE;

    switch (gFireworks->patternMode) {
        case FIREWORKS_PATTERN_MODE_0:
            info->pattern = FIREWORKS_PATTERN_C3;
            break;

        case FIREWORKS_PATTERN_MODE_1:
            info->pattern = FIREWORKS_PATTERN_C3;
            break;

        case FIREWORKS_PATTERN_MODE_TAIKO_BOMBER:
            info->pattern = FIREWORKS_PATTERN_TAIKO_BOMBER;
            break;

        case FIREWORKS_PATTERN_MODE_USE_TABLE:
            info->pattern = fireworks_1_pattern_sequence[gFireworks->patternTableNext];
            if (gFireworks->patternTableNext < 42) {
                gFireworks->patternTableNext++;
            }
            break;

        default: // Use pattern set by ENGINE Func_02
            info->pattern = gFireworks->patternDefault;
            break;
    }

    switch (info->pattern) {
        case FIREWORKS_PATTERN_L3:
            info->targetX = INT_TO_FIXED(60);
            info->targetY = INT_TO_FIXED(48) + INT_TO_FIXED(agb_random(5) * 8);
            break;

        case FIREWORKS_PATTERN_C3:
            info->targetX = INT_TO_FIXED(120);
            info->targetY = INT_TO_FIXED(48) + INT_TO_FIXED(agb_random(5) * 8);
            break;

        case FIREWORKS_PATTERN_R3:
            info->targetX = INT_TO_FIXED(180);
            info->targetY = INT_TO_FIXED(48) + INT_TO_FIXED(agb_random(5) * 8);
            break;

        case FIREWORKS_PATTERN_LL2:
            info->targetX = INT_TO_FIXED(30);
            info->targetY = INT_TO_FIXED(48) + INT_TO_FIXED(agb_random(5) * 8);
            break;

        case FIREWORKS_PATTERN_CL2:
            info->targetX = INT_TO_FIXED(90);
            info->targetY = INT_TO_FIXED(48) + INT_TO_FIXED(agb_random(5) * 8);
            break;

        case FIREWORKS_PATTERN_CR2:
            info->targetX = INT_TO_FIXED(150);
            info->targetY = INT_TO_FIXED(48) + INT_TO_FIXED(agb_random(5) * 8);
            break;

        case FIREWORKS_PATTERN_RR2:
            info->targetX = INT_TO_FIXED(210);
            info->targetY = INT_TO_FIXED(48) + INT_TO_FIXED(agb_random(5) * 8);
            break;

        case FIREWORKS_PATTERN_TAIKO_BOMBER:
            info->targetX = INT_TO_FIXED(120);
            info->targetY = INT_TO_FIXED(80);
            // They forgot to put a break here.

        default:
            info->targetX = INT_TO_FIXED(120);
            info->targetY = INT_TO_FIXED(64);
    }

    switch (info->type) {
        case FIREWORKS_CUE_TYPE_SPIRIT_SPARKLER:
            info->x = info->targetX;
            info->velX = 0;
            info->y = INT_TO_FIXED(160);
            info->velY = (info->targetY - info->y) / ticks_to_frames(0x18);
            info->sprite = sprite_create(gSpriteHandler, anim_fireworks_rocket2, 0, FIXED_TO_INT(info->x), FIXED_TO_INT(info->y), 0x801, 1, 0, 0);
            break;

        case FIREWORKS_CUE_TYPE_NORMAL_FIREWORK:
            info->x = info->targetX;
            info->velX = 0;
            info->y = INT_TO_FIXED(160);
            info->velY = (info->targetY - info->y) / ticks_to_frames(0x48);
            info->sprite = sprite_create(gSpriteHandler, anim_fireworks_rocket1, 0, FIXED_TO_INT(info->x), FIXED_TO_INT(info->y), 0x801, 1, 0, 0);
            play_sound(&s_hanabi_hyu_seqData);
            break;

        case FIREWORKS_CUE_TYPE_HAWFINCH_TAIKO_BOMBER:
            info->velX = INT_TO_FIXED(2);
            info->velY = -(ticks_to_frames(0x30) * 64);
            info->x = info->targetX - (ticks_to_frames(0x30) * info->velX);
            yDistance = 0;
            for (i = 0; i < (s32)ticks_to_frames(0x30); i++) {
                yDistance += i;
            }
            info->y = info->targetY - (ticks_to_frames(0x30) * info->velY) - (yDistance * 64);
            info->sprite = sprite_create(gSpriteHandler, anim_fireworks_bomb, 0, FIXED_TO_INT(info->x), FIXED_TO_INT(info->y), 0x801, 0, 0, 0);
            play_sound(CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_NON_JP_SFX) != 0 ?
                &s_f_hanabi_v_tamaya_en_seqData : &s_f_hanabi_v_tamaya_seqData
            );
            break;
    }
}


// Cue - Update
u32 fireworks_cue_update(struct Cue *cue, struct FireworksCue *info, u32 runningTime, u32 duration) {
    switch (info->type) {
        case FIREWORKS_CUE_TYPE_SPIRIT_SPARKLER:
            info->y += info->velY;
            sprite_set_y(gSpriteHandler, info->sprite, FIXED_TO_INT(info->y));
            if (info->state == 0) {
                if (runningTime > ticks_to_frames(0x07)) {
                    info->state = 1;
                    sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_rocket3, 0, 1, 0, 0);
                }
            } else if (info->state == 1) {
                if (runningTime > ticks_to_frames(0x13)) {
                    info->state = 2;
                    sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_rocket4, 0, 1, 0, 0);
                }
            }
            break;

        case FIREWORKS_CUE_TYPE_NORMAL_FIREWORK:
            info->y += info->velY;
            sprite_set_y(gSpriteHandler, info->sprite, FIXED_TO_INT(info->y));
            switch (info->state) {
                case 0:
                    if (runningTime > ticks_to_frames(0x13)) {
                        info->state = 1;
                        sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_rocket2, 0, 1, 0, 0);
                    }
                    break;

                case 1:
                    if (runningTime > ticks_to_frames(0x2B)) {
                        info->state = 2;
                        sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_rocket3, 0, 1, 0, 0);
                    }
                    break;

                case 2:
                    if (runningTime > ticks_to_frames(0x43)) {
                        info->state = 3;
                        sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_rocket4, 0, 1, 0, 0);
                    }
                    break;
            }
            break;

        case FIREWORKS_CUE_TYPE_HAWFINCH_TAIKO_BOMBER:
            if (info->state == TAIKO_BOMBER_STATE_FLYING) {
                info->x += info->velX;
                info->y += info->velY;
                info->velY += INT_TO_FIXED(0.25);
                sprite_set_x_y(gSpriteHandler, info->sprite, FIXED_TO_INT(info->x), FIXED_TO_INT(info->y));
            }
            break;
    }

    if (runningTime > ticks_to_frames(fireworks_cue_durations[info->type])) {
        if (!info->exploded) {
            play_sound_w_pitch_volume(&s_hanabi_ah_seqData, 48, 0);
        }
        return TRUE;
    }

    return FALSE;
}


// Cue - Despawn
void fireworks_cue_despawn(struct Cue *cue, struct FireworksCue *info) {
    sprite_delete(gSpriteHandler, info->sprite);
}


// Cue - Hit
void fireworks_cue_hit(struct Cue *cue, struct FireworksCue *info, u32 pressed, u32 released) {
    info->exploded = TRUE;

    if (info->pattern == FIREWORKS_PATTERN_TAIKO_BOMBER) {
        info->state = TAIKO_BOMBER_STATE_EXPLODING;
        sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_bomb_explode, 0, 1, 127, 0);
        gFireworks->screenBrightness = 0x10;
    } else {
        sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_rocket_explode, 0, 1, 127, 0);
        fireworks_create_explosion(info->pattern, info->targetX, info->targetY);
    }

    if ((gFireworks->patternTableNext == 19) || (gFireworks->patternTableNext == 42)) {
        play_sound(&s_f_hanabi_kansei_seqData);
    }
}


// Cue - Barely
void fireworks_cue_barely(struct Cue *cue, struct FireworksCue *info, u32 pressed, u32 released) {
    u32 pattern;

    info->exploded = TRUE;

    if (info->pattern == FIREWORKS_PATTERN_TAIKO_BOMBER) {
        info->state = TAIKO_BOMBER_STATE_EXPLODING;
        sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_bomb_explode, 0, 1, 127, 0);
    } else {
        sprite_set_anim(gSpriteHandler, info->sprite, anim_fireworks_rocket_explode, 0, 1, 127, 0);
        switch (info->pattern) {
            case FIREWORKS_PATTERN_L3:
                pattern = FIREWORKS_PATTERN_L3_BARELY;
                break;

            case FIREWORKS_PATTERN_R3:
                pattern = FIREWORKS_PATTERN_R3_BARELY;
                break;

            case FIREWORKS_PATTERN_LL2:
                pattern = FIREWORKS_PATTERN_LL2_BARELY;
                break;

            case FIREWORKS_PATTERN_CL2:
                pattern = FIREWORKS_PATTERN_CL2_BARELY;
                break;

            case FIREWORKS_PATTERN_CR2:
                pattern = FIREWORKS_PATTERN_CR2_BARELY;
                break;

            case FIREWORKS_PATTERN_RR2:
                pattern = FIREWORKS_PATTERN_RR2_BARELY;
                break;

            default:
                pattern = FIREWORKS_PATTERN_C3_BARELY;
        }
        fireworks_create_explosion(pattern, info->targetX, info->targetY);
    }

    beatscript_enable_loops();
}


// Cue - Miss
void fireworks_cue_miss(struct Cue *cue, struct FireworksCue *info) {
    beatscript_enable_loops();
}


// Input Event
void fireworks_input_event(u32 pressed, u32 released) {
}


// Common Event 0 (Beat Animation, Unimplemented)
void fireworks_common_beat_animation(void) {
}


// Common Event 1 (Display Text)
void fireworks_common_display_text(char *text) {
    struct PrintedTextAnim *textAnim;

    if (text == NULL) {
        sprite_set_visible(gSpriteHandler, gFireworks->textSprite, FALSE);
    } else {
        textAnim = bmp_font_obj_print_c(gFireworks->unk4, text, 1, 12);
        delete_bmp_font_obj_text_anim(gFireworks->unk4, gFireworks->textSprite);
        sprite_set_anim(gSpriteHandler, gFireworks->textSprite, textAnim->frames, 0, 1, 0, 0);
        sprite_set_visible(gSpriteHandler, gFireworks->textSprite, TRUE);
    }
}


// Common Event 2 (Init. Tutorial)
void fireworks_common_init_tutorial(struct Scene *skipDestination) {
    if (skipDestination != NULL) {
        gameplay_enable_tutorial(TRUE);
        gameplay_set_skip_destination(skipDestination);
        sprite_set_visible(gSpriteHandler, gFireworks->skipTutorialSprite, TRUE);
    } else {
        gameplay_enable_tutorial(FALSE);
        sprite_set_visible(gSpriteHandler, gFireworks->skipTutorialSprite, FALSE);
    }
}
