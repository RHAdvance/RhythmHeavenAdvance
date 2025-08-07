#include "engines/marching_orders.h"

asm(".include \"include/gba.inc\""); // Temporary

// For readability.
#define gMarchingOrders ((struct MarchingOrdersEngineData *)gCurrentEngineData)

enum CommanderStatesEnum {
    COMMANDER_STATE_IDLE,
    COMMANDER_STATE_ANGRY,
    COMMANDER_STATE_ANNOYED
};

/* MARCHING ORDERS */

// Get Animation
struct Animation* func_08034100(s32 anim) {
    if (anim < 0) {
        return NULL;
    } else {
        return marching_anim_table[anim][gMarchingOrders->version];
    }
}

// Graphics Init. 3
void marching_init_gfx3(void) {
    func_0800c604(0);
    gameplay_start_screen_fade_in();
}

// Graphics Init. 2
void marching_init_gfx2(void) {
    s32 task;
    func_0800c604(0);
    task = func_08002ee0(get_current_mem_id(), marching_gfx_tables[gMarchingOrders->version], 0x2000);
    run_func_after_task(task, marching_init_gfx3, 0);
}

// Graphics Init. 1
void marching_init_gfx1(void) {
    s32 task;

    func_0800c604(0);
    task = start_new_texture_loader(get_current_mem_id(), marching_buffered_textures);
    run_func_after_task(task, marching_init_gfx2, 0);
}

// Game Engine Start
void marching_engine_start(u32 version) {
    struct PrintedTextAnim *textAnim;
    struct Marcher *marcher;
    u32 i;

    gMarchingOrders->version = version;

    marching_init_gfx1();
    scene_show_obj_layer();

    scene_set_bg_layer_display(BG_LAYER_1, TRUE, 0, 0, 0, 29, 2);
    scene_set_bg_layer_display(BG_LAYER_2, FALSE, 0, 0, 0, 30, 0);
    scene_set_bg_layer_display(BG_LAYER_3, TRUE, 0, 0, 0, 31, 3);

    gMarchingOrders->font = scene_create_obj_font_printer(0x340, 2);
    textAnim = bmp_font_obj_print_l(gMarchingOrders->font, D_0805a670, 1, 0xe);

    gMarchingOrders->textSprite = sprite_create(gSpriteHandler, textAnim, 0, 0x78, 0x16, 0, 0, 0, 0);

    for (i = 0; i < 4; i++) {
        marcher = &gMarchingOrders->marchers[i];
        marcher->sprite = sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_STOP_BEAT), 0, 0x50 + (i * 0x28), 0x78, 0x4800, 1, 0x7f, 0);
        marcher->headSprite = sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_HEAD_R), 0x7f, 0x50 + (i * 0x28), 0x78, 0x47f6, 1, 0x7f, 0x8000);
        sprite_attr_set(gSpriteHandler, marcher->headSprite, 0x1000000);
        sprite_set_origin_x_y(gSpriteHandler, marcher->sprite, &D_03004b10.BG_OFS[3].x, &D_03004b10.BG_OFS[3].y);
        sprite_set_origin_x_y(gSpriteHandler, marcher->headSprite, &D_03004b10.BG_OFS[3].x, &D_03004b10.BG_OFS[3].y);

        marcher->currentAction = 0;
        marcher->idleTimer = 0;
        marcher->idled = FALSE;
    }

    gMarchingOrders->marchersPointing = 0;
    gMarchingOrders->marcherNextFoot = 0;
    gMarchingOrders->playerActionTimer = 0;

    gMarchingOrders->tutorialIcon = sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_TUTORIAL_ICONS), 0, 200, 0x82, 0x479c, 0, 0, 0x8000);
    gMarchingOrders->commanderSprite = sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_COMMANDER), 0x7f, 0x1c, 0x7c, 0x4800, 1, 0x7f, 0);
    gMarchingOrders->commanderActionTimer = 0;
    gMarchingOrders->conveyorEnabled = 0;

    if (version == MARCHING_ORDERS_VER_2_UNUSED) {
        gameplay_set_input_buttons(A_BUTTON | B_BUTTON, 0);
    } else {
        gameplay_set_input_buttons(A_BUTTON | B_BUTTON | DPAD_LEFT | DPAD_RIGHT, 0);
    }
}

// Engine Event 06 (Stub)
void marching_engine_event_stub(void) {
}

// Play Marcher Action Animation
#include "asm/engines/marching_orders/asm_080343b8.s"

// Engine Event 00 (Play Marcher Action)
void marching_play_action(u32 action) {
    u32 i;
    u32 marcherCount = 3;

    // Because beatscript events can only pass in one argument,
    // the 8th bit of the action is used to determine
    // if the action should play on the player's marcher as well.

    if (action & 0x100) {
        marcherCount = 4;
    }

    action = action & 0xfffffeff;

    for (i = 0; i < marcherCount; i++) {
        if (i == 3) {
            if (gMarchingOrders->playerActionTimer == 0) {
                func_080343b8(&gMarchingOrders->marchers[3], action);
                if (action == 7) {
                    gMarchingOrders->marcherNextFoot = 1;
                }
                if (action == 8) {
                    gMarchingOrders->marcherNextFoot = 0;
                }
            }
        } else {
            func_080343b8(&gMarchingOrders->marchers[i], action);
        }
    }
}

// Update Marcher Sprite
void marching_update_marcher_sprite(struct Marcher *marcher) {
    s32 x, y;
    s32 frame;

    x = sprite_get_data(gSpriteHandler, marcher->sprite, SPRITE_DATA_X_POS);
    y = sprite_get_data(gSpriteHandler, marcher->sprite, SPRITE_DATA_Y_POS);

    if (marcher->idleTimer != 0) {
        frame = sprite_get_anim_cel(gSpriteHandler, marcher->sprite);
        x += D_089e5368[frame][gMarchingOrders->version].x;
        y += D_089e5368[frame][gMarchingOrders->version].y;
        marcher->idleTimer++;

        if (marcher->idled == FALSE) {
            if (marcher->idleTimer > ticks_to_frames(0x30)) {
                marcher->idled = TRUE;
                sprite_set_playback(gSpriteHandler, marcher->sprite, -1, 0, 0);
                sprite_set_anim_cel(gSpriteHandler, marcher->sprite, 3);
            }
        } else if (frame == 0) {
            func_080343b8(marcher, 0);
            return;
        }
    }

    sprite_set_x_y(gSpriteHandler, marcher->headSprite, x, y);
}

// Update Marchers
void marching_update_marchers(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        marching_update_marcher_sprite(&gMarchingOrders->marchers[i]);
    }

    if (gMarchingOrders->playerActionTimer != 0) {
        gMarchingOrders->playerActionTimer--;
    }
}

// Engine Event 01 (Set Commander Action)
void marching_set_commander_action(u32 action) {
    if (gMarchingOrders->commanderActionTimer != 0) {
        return;
    }

    switch(action) {
        case COMMANDER_STATE_IDLE:
            sprite_set_anim(gSpriteHandler, gMarchingOrders->commanderSprite, func_08034100(MARCHING_ANIM_COMMANDER), 1, 1, 0x7f, 0);
            gMarchingOrders->commanderActionTimer = ticks_to_frames(8);
            break;
        case COMMANDER_STATE_ANGRY:
            sprite_set_anim(gSpriteHandler, gMarchingOrders->commanderSprite, func_08034100(MARCHING_ANIM_COMMANDER), 0, 1, 0x7f, 0);
            sprite_create(gSpriteHandler, func_08034100(MARCHING_ANIM_ANGRY_PUFF), 0, 0x1e, 0x28, 0x480a, 1, 0, 3);
            play_sound(&s_guntai_ikari_seqData);
            gMarchingOrders->commanderActionTimer = ticks_to_frames(0x18);
            break;
        case COMMANDER_STATE_ANNOYED:
            sprite_set_anim(gSpriteHandler, gMarchingOrders->commanderSprite, func_08034100(MARCHING_ANIM_COMMANDER_ANNOYED), 0, 1, 0x7f, 0);
            gMarchingOrders->commanderActionTimer = ticks_to_frames(0x18);
            break;
    }
}

// Engine Event 02 (Set Tutorial Icon State)
void marching_set_tutorial_icon(s32 state) {
    if (state < 0) {
        sprite_set_visible(gSpriteHandler, gMarchingOrders->tutorialIcon, FALSE);
    } else {
        sprite_set_visible(gSpriteHandler, gMarchingOrders->tutorialIcon, TRUE);
        sprite_set_anim_cel(gSpriteHandler, gMarchingOrders->tutorialIcon, state);
    }
}

// Engine Event 03 (Enable Conveyor)
void marching_enable_conveyor(void) {
    gMarchingOrders->conveyorEnabled = 1;
}

// Update Conveyor
void marching_update_conveyor(void) {
    if (gMarchingOrders->conveyorEnabled) {
        D_03004b10.BG_OFS[3].x--;
    }
}

// Engine Event 04 (Set Marchers Pointing)
void marching_set_marchers_pointing(u8 enabled) {
    gMarchingOrders->marchersPointing = enabled;
}

// Game Engine Update
void marching_engine_update(void) {
    marching_update_marchers();
    marching_update_conveyor();

    if (gMarchingOrders->commanderActionTimer != 0) {
        gMarchingOrders->commanderActionTimer--;
    }
}

// Game Engine Stop
void marching_engine_stop(void) {
}

// Cue - Spawn
void marching_cue_spawn(struct Cue *cue, struct MarchingOrdersCue *info, u32 command) {
    info->command = command;
}

// Cue - Update
u32 marching_cue_update(struct Cue *cue, struct MarchingOrdersCue *info, u32 runningTime, u32 released) {
    if (runningTime > ticks_to_frames(0x78)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Cue - Despawn
void marching_cue_despawn(struct Cue *cue, struct MarchingOrdersCue *info) {
}

// Cue - Hit
void marching_cue_hit(struct Cue *cue, struct MarchingOrdersCue *info, u32 pressed, u32 released) {
    struct Marcher *player = &gMarchingOrders->marchers[3];

    switch (info->command) {
        case MARCHING_CUE_STEP:
            play_sound(gMarchingOrders->marcherNextFoot ? &s_guntai_foot2_seqData : &s_guntai_foot1_seqData);
            marching_player_step();
            break;
        case MARCHING_CUE_TURN_LEFT:
            marching_player_turn_left();
            break;
        case MARCHING_CUE_TURN_RIGHT:
            marching_player_turn_right();
            break;
        case MARCHING_CUE_HALT:
            if (player->idleTimer != 0) {
                play_sound(gMarchingOrders->marcherNextFoot ? &s_guntai_foot2_seqData : &s_guntai_foot1_seqData);
                marching_player_halt();
            }
            break;
    }
}

// Cue - Barely
void marching_cue_barely(struct Cue *cue, struct MarchingOrdersCue *info, u32 pressed, u32 released) {
    marching_cue_hit(cue, info, pressed, released);
    marching_set_commander_action(COMMANDER_STATE_ANNOYED);
}

// Cue - Miss
void marching_cue_miss(struct Cue *cue, struct MarchingOrdersCue *info) {
    beatscript_enable_loops();
    marching_set_commander_action(COMMANDER_STATE_ANGRY);
}

// Player Step
void marching_player_step(void) {
    u32 unk;

    if (gMarchingOrders->marcherNextFoot) {
        unk = 8;
    } else {
        unk = 7;
    }

    func_080343b8(&gMarchingOrders->marchers[3], unk);

    gMarchingOrders->marcherNextFoot ^= 1;
    gMarchingOrders->playerActionTimer = ticks_to_frames(0xc);
}

// Player Turn Left
void marching_player_turn_left(void) {
    func_080343b8(&gMarchingOrders->marchers[3], 3);
    gMarchingOrders->playerActionTimer = ticks_to_frames(0xc);
}

// Player Turn Right
void marching_player_turn_right(void) {
    func_080343b8(&gMarchingOrders->marchers[3], 4);
    gMarchingOrders->playerActionTimer = ticks_to_frames(0xc);
}

// Player Halt
void marching_player_halt(void) {
    func_080343b8(&gMarchingOrders->marchers[3], 1);
    gMarchingOrders->playerActionTimer = ticks_to_frames(0xc);
}

// Input Event
void marching_input_event(u32 pressed, u32 released) {
    struct Marcher *player = &gMarchingOrders->marchers[3];

    if (pressed & A_BUTTON) {
        marching_player_step();
    }

    if (pressed & B_BUTTON && player->idleTimer != 0) {
        marching_player_halt();
    }

    if (pressed & DPAD_LEFT) {
        marching_player_turn_left();
    }

    if (pressed & DPAD_RIGHT) {
        marching_player_turn_right();
    }

    beatscript_enable_loops();
    marching_set_commander_action(COMMANDER_STATE_ANGRY);
}

// Common Event 0 (Beat Animation, Unimplemented)
void marching_common_beat_animation(void) {
}

// Common Event 1 (Display Text)
void marching_common_display_text(const char *text) {
    struct PrintedTextAnim *textAnim;

    if (text == NULL) {
        sprite_set_visible(gSpriteHandler, gMarchingOrders->textSprite, FALSE);
        scene_hide_bg_layer(BG_LAYER_2);
    } else {
        textAnim = bmp_font_obj_print_c(gMarchingOrders->font, text, 1, 0xc);

        delete_bmp_font_obj_text_anim(gMarchingOrders->font, gMarchingOrders->textSprite);
        sprite_set_anim(gSpriteHandler, gMarchingOrders->textSprite, textAnim, 0, 0, 0, 0);
        sprite_set_visible(gSpriteHandler, gMarchingOrders->textSprite, TRUE);
        scene_show_bg_layer(BG_LAYER_2);
    }
}

// Common Event 2 (Init. Tutorial, Unimplemented)
void marching_common_init_tutorial(void) {
}

// Engine Event 05 (Play Sound)
void marching_play_sound(u32 arg0) {
    struct MarchingSfxData *sfx = &marching_sfx_table[gMarchingOrders->version][arg0];

    play_sound_w_pitch_volume(sfx->sound, sfx->volume, sfx->pitch);
}
