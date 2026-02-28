#include "engines/mechanical_horse.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gMechanicalHorse ((struct MechanicalHorseEngineData *)gCurrentEngineData)


/* MECHANICAL HORSE */


void func_08040c2c() {
    gMechanicalHorse->unk2fe = 0;
    gMechanicalHorse->unk306 = -1;
    gMechanicalHorse->unk300 = 0;
}

void func_08040c58() {
    u32* temp;
    switch (gMechanicalHorse->unk2fe) {
        case 0:
        case 1:
        case 2:
            gMechanicalHorse->unk30c += gMechanicalHorse->unk2d0 / 2;
            break;
        case 3:
            gMechanicalHorse->unk30c += INT_TO_FIXED(13);
            break;
        case 4:
            gMechanicalHorse->unk30c = 0;
            break;
        case 5:
            gMechanicalHorse->unk30c = 0;
            break;
    }
    scene_set_bg_layer_pos(0, FIXED_TO_INT(gMechanicalHorse->unk30c), 0);
}


void func_08040cfc() {
    gMechanicalHorse->unk300 = 0;
}

void func_08040d10() {
    u16 a = get_current_mem_id();
    s32 task = palette_fade_in(a, gMechanicalHorse->unk304, 2, gMechanicalHorse->unk302, &mechanical_horse_backgrounds[gMechanicalHorse->unk2ff].palette[0][0], D_03004b10.bgPalette[0]);
    run_func_after_task(task, func_08040cfc, 0);
    gMechanicalHorse->unk2fe = gMechanicalHorse->unk2ff;
}

#include "asm/engines/mechanical_horse/asm_08040d90.s"

#include "asm/engines/mechanical_horse/asm_08040dd8.s"

void func_08040e80() {
    if (gMechanicalHorse->unk300 == 0 && gMechanicalHorse->unk306 >= 0) {
        func_08040dd8();
    }
    func_08040c58();
}

#include "asm/engines/mechanical_horse/asm_08040eb0.s"

void mechanical_horse_init_gfx3() {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

void mechanical_horse_init_gfx2() {
    s32 task;

    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), gfx_table_mechanical_horse, 0x2000);
    run_func_after_task(task, mechanical_horse_init_gfx3, 0);
}

void mechanical_horse_init_gfx1() {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), mechanical_horse_buffered_textures);
    run_func_after_task(task, mechanical_horse_init_gfx2, 0);
}

void mechanical_horse_engine_start(u32 version) {
    u8 i;
    gMechanicalHorse->version = version;
    mechanical_horse_init_gfx1();
    scene_show_obj_layer();
    scene_set_bg_layer_display(0, 1, 0, 0, 2, 28, 3);
    scene_set_bg_layer_display(1, 1, 0, 0, 0, 29, 2);
    scene_set_bg_layer_display(2, 1, 0, 0, 0, 30, 1);
    scene_set_bg_layer_display(3, 0, 0, 0, 0, 31, 0);
    gMechanicalHorse->unk2e4 = 0x1000;
    gMechanicalHorse->unk2e8 = 0;
    D_03004b10.BLDMOD = 0x142;
    D_03004b10.COLEV = 0x1000;
    gMechanicalHorse->text_font = scene_create_obj_font_printer(0x380, 1);
    gMechanicalHorse->text_sprite =
        sprite_create(gSpriteHandler, bmp_font_obj_print_c(gMechanicalHorse->text_font, D_0805a9fc, 1, 0xf)->frames, 0, 0x80, 0x90, 0, 0, 0, 0);
    for (i = 0; i < 2; i++) {
        gMechanicalHorse->horse[i].unk2 = 0;
        gMechanicalHorse->horse[i].cel = 0;
        gMechanicalHorse->horse[i].unk4 = 0;
        if (i == 0) {
            gMechanicalHorse->horse[i].pos_x = INT_TO_FIXED(88);
            gMechanicalHorse->horse[i].pos_y = INT_TO_FIXED(100);
        } else {
            gMechanicalHorse->horse[i].pos_x = INT_TO_FIXED(184);
            gMechanicalHorse->horse[i].pos_y = INT_TO_FIXED(100);
        }
        gMechanicalHorse->horse[i].unk10 = gMechanicalHorse->horse[i].unk14 = 0;
        if (i == 0) {
            gMechanicalHorse->horse[i].sprite =
                sprite_create(gSpriteHandler, anim_horse_still, 0, FIXED_TO_INT(gMechanicalHorse->horse[i].pos_x), FIXED_TO_INT(gMechanicalHorse->horse[i].pos_y), 0x8004, 0, 0, 0);
        } else {
            gMechanicalHorse->horse[i].sprite =
                sprite_create(gSpriteHandler, anim_horse_still, 0, FIXED_TO_INT(gMechanicalHorse->horse[i].pos_x), FIXED_TO_INT(gMechanicalHorse->horse[i].pos_y), 0x8007, 0, 0, 0);
            sprite_set_base_palette(gSpriteHandler, gMechanicalHorse->horse[i].sprite, -1);
        }
        gMechanicalHorse->jockey[i].unk2 = 0;
        gMechanicalHorse->jockey[i].cel = 0;
        if (i == 0) {
            gMechanicalHorse->jockey[i].sprite = 
                sprite_create(gSpriteHandler, anim_horse_walk_jockey, 0, FIXED_TO_INT(gMechanicalHorse->horse[i].pos_x), FIXED_TO_INT(gMechanicalHorse->horse[i].pos_y), 0x8003, 0, 0, 0);
        } else {
            gMechanicalHorse->jockey[i].sprite = 
                sprite_create(gSpriteHandler, anim_horse_walk_jockey, 0, FIXED_TO_INT(gMechanicalHorse->horse[i].pos_x), FIXED_TO_INT(gMechanicalHorse->horse[i].pos_y), 0x8006, 0, 0, 0);
            sprite_set_base_palette(gSpriteHandler, gMechanicalHorse->jockey[i].sprite, -1);
        }
    }
    for (i = 0; i < 20; i++) {
        gMechanicalHorse->unk3c[i].sprite = sprite_create(gSpriteHandler, anim_horse_text_pak, 0, -0x40, -0x40, 0x8002, 0, 0, 0);
        gMechanicalHorse->unk3c[i].unk2 = 0;
        sprite_set_visible(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, FALSE);
    }
    for (i = 0; i < 4; i++) {
        gMechanicalHorse->unk26c[i].pos_x = INT_TO_FIXED(-64);
        gMechanicalHorse->unk26c[i].pos_y = INT_TO_FIXED(144);
        gMechanicalHorse->unk26c[i].unk10 = gMechanicalHorse->unk26c[i].unk14 = 0;
        gMechanicalHorse->unk26c[i].sprite =
            sprite_create(gSpriteHandler, anim_horse_text_pak, 0, FIXED_TO_INT(gMechanicalHorse->unk26c[i].pos_x), FIXED_TO_INT(gMechanicalHorse->unk26c[i].pos_y), 1, 0, 0, 0);
        gMechanicalHorse->unk26c[i].unk2 = 0;
        gMechanicalHorse->unk26c[i].unk3 = 0;
        gMechanicalHorse->unk26c[i].unk4 = 0;
        sprite_set_visible(gSpriteHandler, gMechanicalHorse->unk26c[i].sprite, FALSE);
    }
    gMechanicalHorse->tachometer_hand =
        create_affine_sprite(anim_horse_tachometer_hand, 0, 87, 144, 0x800, 0x100, 0, 0, 0, 0x8000, 0);
    gMechanicalHorse->speedometer_hand =
        create_affine_sprite(anim_horse_speedometer_hand, 0, 143, 144, 0x800, 0x100, 0, 0, 0, 0x8000, 0);
    gMechanicalHorse->high_speed_light_sprite =
        sprite_create(gSpriteHandler, anim_horse_high_speed_light, 0, 94, 130, 0x800, 1, 0, 0x8000);
    func_08040c2c();
    gMechanicalHorse->unk2cc = 0;
    gMechanicalHorse->unk2d0 = 0;
    gMechanicalHorse->unk2d4 = 0;
    gMechanicalHorse->unk2d8 = 0;
    gMechanicalHorse->unk2e9 = 0;
    gMechanicalHorse->unk2ea = 0;
    gMechanicalHorse->unk2eb = 1;
    gMechanicalHorse->music_volume = 0x40;
    gMechanicalHorse->unk2ee = 0;
    gMechanicalHorse->unk2f0 = 0x100;
    gameplay_set_input_buttons(DPAD_ANY | A_BUTTON | B_BUTTON, 0);
}

void func_08041444(int arg0) {
    u32 temp;
    u8 temp4;
    struct SoundPlayer* temp1;
    if (arg0 == 0) {
        temp1 = play_sound(mechanical_horse_player_horse_sfx[gMechanicalHorse->unk2cc * 4 + gMechanicalHorse->horse[0].cel]);
    } else {
        u24_8 temp2;
        s24_8 temp3;
        
        temp1 = play_sound(mechanical_horse_teacher_horse_sfx[gMechanicalHorse->unk2cc * 4 + gMechanicalHorse->horse[arg0].cel]);
        
        if (gMechanicalHorse->horse[0].unk2 == 1) {
            temp2 = INT_TO_FIXED(0.25);
        } else {
            temp2 = INT_TO_FIXED(1);
        }
        
        temp3 = FIXED_TO_INT(gMechanicalHorse->horse[1].pos_x) - 128;
        temp3 = ABS(temp3);
        if (temp3 >= 128) {
            temp2 = clamp_int32(128 - temp3 + temp2, INT_TO_FIXED(0.25), INT_TO_FIXED(1));
        }
        
        set_soundplayer_volume(temp1, temp2);
    }

    sprite_set_anim_cel(gSpriteHandler, gMechanicalHorse->horse[arg0].sprite, gMechanicalHorse->horse[arg0].cel);

    temp4 = gMechanicalHorse->horse[arg0].cel += 1;

    if (temp4 > D_0805aa00[gMechanicalHorse->unk2cc]) {
        gMechanicalHorse->horse[arg0].cel = 0;
    }

    sprite_set_anim_cel(gSpriteHandler, gMechanicalHorse->jockey[arg0].sprite, gMechanicalHorse->jockey[arg0].cel);


    if (((gMechanicalHorse->jockey[arg0].cel += 1) & 0xff) > D_0805aa10[gMechanicalHorse->unk2cc]) {
        gMechanicalHorse->jockey[arg0].cel = 0;
    }

    if (arg0 == 1) {
        gMechanicalHorse->horse[1].unk4 = 0;
        gMechanicalHorse->horse[1].unk10 += D_0805aa20[gMechanicalHorse->unk2cc];
    }

}

void func_080415c0(u32 lesson) {
    u8 i;
    gMechanicalHorse->unk2cc = lesson;

    sprite_set_anim(gSpriteHandler, gMechanicalHorse->horse[1].sprite, mechanical_horse_anim[lesson], 0, 0, 0, SPRITE_PLAYBACK_NORMAL_LOOP);
    sprite_set_anim(gSpriteHandler, gMechanicalHorse->jockey[1].sprite, mechanical_horse_jockey_anim[lesson], 0, 0, 0, SPRITE_PLAYBACK_NORMAL_LOOP);

    for(i = 0; i < 4; i++){
        gMechanicalHorse->unk26c[i].pos_x = INT_TO_FIXED(D_0805aab0[lesson][i]);

        sprite_set_x_y(gSpriteHandler, gMechanicalHorse->unk26c[i].sprite, FIXED_TO_INT(gMechanicalHorse->unk26c[i].pos_x), FIXED_TO_INT(gMechanicalHorse->unk26c[i].pos_y));
        sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk26c[i].sprite, mechanical_horse_lesson_text_anim[lesson][i], 1, 0, 0, SPRITE_PLAYBACK_NORMAL_LOOP);
    }
}

// prints specified text?
void func_080416cc(const char* string) {
    delete_bmp_font_obj_text_anim(gMechanicalHorse->text_font, gMechanicalHorse->text_sprite);
    sprite_set_anim(gSpriteHandler, gMechanicalHorse->text_sprite, (struct Animation*)bmp_font_obj_print_c(gMechanicalHorse->text_font, string, 1, 0xc), 0, 1, 0, 0);
}

void func_08041730(u8 unk) {
    gMechanicalHorse->unk2e8 = unk;
}

void func_08041744(u32 arg0) {
    u8 i;
    gMechanicalHorse->unk2e9 = arg0;
    for (i = 0; i < 4; i++) {
        sprite_set_visible(gSpriteHandler, gMechanicalHorse->unk26c[i].sprite, arg0);
    }
    if (arg0 == 0 && gMechanicalHorse->unk2cc == 3) {
        gMechanicalHorse->unk2e9 = 1;
    }
}

#include "asm/engines/mechanical_horse/asm_080417ac.s"

#include "asm/engines/mechanical_horse/asm_0804188c.s"

u8 func_08041940(void) {
    u8 i;
    for (i = 0; i < 20; i++) {
        if (gMechanicalHorse->unk3c[i].unk2 == 0) {
            return i;
        }  
    }
    return 0;
}

void func_08041970(void) {
    u8 i;
    boolean isPlayer;
    u32 temp2;
    for (i = 0; i < 20; i++) {
        switch (gMechanicalHorse->unk3c[i].unk2) {
            case 2:
            case 3:
                isPlayer = FALSE;
                if (gMechanicalHorse->unk3c[i].unk2 == 2) {
                    isPlayer = TRUE;
                }

                if (isPlayer) {
                    gMechanicalHorse->unk3c[i].pos_x = gMechanicalHorse->horse[0].pos_x;
                    gMechanicalHorse->unk3c[i].pos_z = INT_TO_FIXED(128.0078125);
                } else {
                    gMechanicalHorse->unk3c[i].pos_x = gMechanicalHorse->horse[1].pos_x;
                    gMechanicalHorse->unk3c[i].pos_z = INT_TO_FIXED(128.01953125);
                }
                gMechanicalHorse->unk3c[i].pos_y = INT_TO_FIXED(96);
                gMechanicalHorse->unk3c[i].unk14[0] = D_0805aa40[gMechanicalHorse->unk2cc][0];
                gMechanicalHorse->unk3c[i].unk14[1] = D_0805aa40[gMechanicalHorse->unk2cc][1];
                gMechanicalHorse->unk3c[i].unk4 = 0;
                if (gMechanicalHorse->unk2cc == 0) {
                    if (gMechanicalHorse->unk3c[i].unk3 == 0 || gMechanicalHorse->unk3c[i].unk3 == 2) {
                        sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_pak, 0, 0, 0, 0);
                    } else {
                        sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_ka, 0, 0, 0, 0);
                    }
                } else {
                    if (gMechanicalHorse->unk2cc == 1) {     
                        if (gMechanicalHorse->unk3c[i].unk3 == 0 || gMechanicalHorse->unk3c[i].unk3 == 2) {               
                            sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_tot, 0, 0, 0, 0);
                        } else {
                            sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_ka, 0, 0, 0, 0);
                        }
                    } else if (gMechanicalHorse->unk2cc == 2) {
                        if (gMechanicalHorse->unk3c[i].unk3 == 0) {
                            sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_pa, 0, 0, 0, 0);
                        } else if (gMechanicalHorse->unk3c[i].unk3 == 1) {
                            sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_ta, 0, 0, 0, 0); 
                        } else {
                            sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_rap, 0, 0, 0, 0);
                        }
                    } else {
                        if (gMechanicalHorse->unk3c[i].unk3 <= 2) {
                             sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_do, 0, 0, 0, 0);
                        } else {
                             sprite_set_anim(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, anim_horse_text_dod, 0, 0, 0, 0);
                        }
                    }
                }
                sprite_set_x_y_z(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, FIXED_TO_INT(gMechanicalHorse->unk3c[i].pos_x), FIXED_TO_INT(gMechanicalHorse->unk3c[i].pos_y), gMechanicalHorse->unk3c[i].pos_z);
                sprite_set_visible(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, 1);
                gMechanicalHorse->unk3c[i].unk2 = 4;
                break;
            case 4:
                gMechanicalHorse->unk3c[i].pos_x += gMechanicalHorse->unk3c[i].unk14[0];
                gMechanicalHorse->unk3c[i].pos_y += gMechanicalHorse->unk3c[i].unk14[1];
                gMechanicalHorse->unk3c[i].unk14[1] += INT_TO_FIXED(0.125); 
                sprite_set_x_y(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, FIXED_TO_INT(gMechanicalHorse->unk3c[i].pos_x), FIXED_TO_INT(gMechanicalHorse->unk3c[i].pos_y));
                if ((gMechanicalHorse->unk3c[i].pos_x < INT_TO_FIXED(-16)) || (gMechanicalHorse->unk3c[i].pos_y > INT_TO_FIXED(112))) {
                    gMechanicalHorse->unk3c[i].unk2 = 0;
                    sprite_set_visible(gSpriteHandler, gMechanicalHorse->unk3c[i].sprite, 0);
                }
                break;
            case 1:
                if (gMechanicalHorse->unk3c[i].unk4-- > 0) {
                    break;
                }
                gMechanicalHorse->unk3c[i].unk2 = 3;
                break;
            case 0:
                break;
        }
    }
}

#include "asm/engines/mechanical_horse/asm_08041c98.s"

#include "asm/engines/mechanical_horse/asm_08041ddc.s"

#include "asm/engines/mechanical_horse/asm_08041f80.s"

#include "asm/engines/mechanical_horse/asm_08042020.s"

#include "asm/engines/mechanical_horse/asm_080420c0.s"

#include "asm/engines/mechanical_horse/asm_0804231c.s"

#include "asm/engines/mechanical_horse/asm_08042438.s"

void func_0804249c(void) {
    u32 temp = gMechanicalHorse->unk2e4;
    u32 temp1;
    u16 temp2;
    u8 temp3 = gMechanicalHorse->unk2e8;
    temp1 = temp + 0x40;
    if (temp3) {
        temp1 -= 0x80;
    }
    gMechanicalHorse->unk2e4 = temp1;
    gMechanicalHorse->unk2e4 = clamp_int32(gMechanicalHorse->unk2e4, 0, 0x1000);
    temp2 = FIXED_TO_INT(gMechanicalHorse->unk2e4);
    D_03004b10.COLEV = temp2 | INT_TO_FIXED(16 - temp2);
}

void func_080424f0(u16 unk) {
    gMechanicalHorse->unk2ee = unk;
}

#include "asm/engines/mechanical_horse/asm_08042504.s"

#include "asm/engines/mechanical_horse/asm_08042548.s"

void mechanical_horse_engine_update() {
    func_080420c0();
    func_0804188c();
    func_08041970();
    func_0804231c();
    func_08042548();
    func_08042438();
    func_08040e80();
    func_0804249c();
    scene_set_music_volume(gMechanicalHorse->music_volume);
}

void mechanical_horse_engine_stop() {
}

#include "asm/engines/mechanical_horse/asm_08042758.s"

#include "asm/engines/mechanical_horse/asm_080427b0.s"

void mechanical_horse_cue_despawn(struct Cue *cue, struct MechanicalHorseCue *data) {
}

void mechanical_horse_cue_hit(struct Cue *cue, struct MechanicalHorseCue *data, u32 pressed, u32 released) {
    if (gMechanicalHorse->unk2e9 == 0) {
        gameplay_ignore_this_cue_result();
    } else if (gMechanicalHorse->horse[0].unk2 == 0) {
        func_08041c98();
    } else {
        func_08041ddc();
    }
}

void mechanical_horse_cue_barely(struct Cue *cue, struct MechanicalHorseCue *data, u32 pressed, u32 released) {
    mechanical_horse_cue_hit(cue, data, pressed, released);
}

void mechanical_horse_cue_miss(struct Cue *cue, struct MechanicalHorseCue *data) {
    gameplay_ignore_this_cue_result();
    func_08042020();
}

void mechanical_horse_input_event(u32 pressed, u32 released) {
    if (gMechanicalHorse->horse[0].unk2 == 0) {
        func_08041c98();
    } else {
        func_08041f80();
    }
}

void mechanical_horse_common_beat_animation() {
}

void mechanical_horse_common_display_text() {
}