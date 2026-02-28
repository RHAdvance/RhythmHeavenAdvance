#include "global.h"
#include "riq_main_scene.h"

#include "src/main.h"
#include "src/code_08001360.h"
#include "src/bitmap_font.h"
#include "src/task_pool.h"
#include "src/memory_heap.h"
#include "src/lib_0804ca80.h"

static u8 D_0300155c;

extern u8 haveSeenDisclaimer;

/* GLOBAL RIQ SCENE */


// [func_0801d860] Set D_0300155c
void func_0801d860(u32 arg) {
	D_0300155c = arg;
}


// [func_0801d86c] Script Init.
void func_0801d86c(const struct SubScene *subScene) {
    const struct SubScene *subScenes[4];

    gPauseMenu.state = PAUSE_STATE_PLAY;
    gPauseMenu.enabled = FALSE;
    gPauseMenu.hasBeenUsed = FALSE;
    gPauseMenu.data = NULL;
    if (D_0300155c) {
        func_08006d80();
    }
    func_08006da8(); // Reset Graphics
    func_08007014(0); // Fill Palette (Black)
    func_08006fec(); // Clear OAM Buffer
    func_080073f0(); // Init. OAM Buffer
    func_08003f28();
    func_080013e8(func_0801d9cc);
    subScenes[0] = subScene;
    subScenes[1] = NULL;
    start_beatscript_scene(0);
    set_beatscript_subscenes(subScenes);
}


// [func_0801d8d8] Script Main
u32 func_0801d8d8(void) {
    func_08006e88(); // Flush Graphics Buffer
    func_08003fb4();
    if (gPauseMenu.hasBeenUsed) {
        update_paused_beatscript_scene();
    }
    task_pool_update_constant();
    task_pool_update_delayed();

    /* Script/Pause Handling */
    switch (gPauseMenu.state) {
        case PAUSE_STATE_PLAY:
            /* Check if Pause Screen should open. */
            if (func_0801d9d0()) {
                break;
            }
            /* Otherwise, update Script. */
            update_active_beatscript_scene();
            if (beatscript_scene_is_inactive()) {
                func_0801d98c();
                return TRUE;
            }
            break;

        case PAUSE_STATE_PAUSE:
            /* Update the Pause Screen. */
            func_0801da48();
            if (gPauseMenu.state != PAUSE_STATE_PLAY) {
                break;
            }
            /* If "Continue" was selected, update Script. */
            update_active_beatscript_scene();
            if (beatscript_scene_is_inactive()) {
                func_0801d98c();
                return TRUE;
            }
            break;

        case PAUSE_STATE_STOP:
            if (func_0801dabc()) {
                return TRUE;
            }
            break;
    }

    func_08007410(); // Update OAM
    func_08006f84(); // Update Palette
    func_080042a4(); // Update Backdrop
    return FALSE;
}


// [func_0801d95c] Change Script
void func_0801d95c(const struct Beatscript *script) {
	D_030053c0.threads[0].currentCmd = script;
}


// [func_0801d968] Change Script (w/ Timer Reset)
void func_0801d968(const struct Beatscript *script) {
	D_030053c0.threads[0].currentCmd = script;
	D_030053c0.threads[0].timeUntilNext = 0;
}


// [func_0801d978] Reset BranchStack Position
void func_0801d978(void) {
	D_030053c0.threads[0].stackCounter = 0;
}


// [func_0801d98c] Script Close
void func_0801d98c(void) {
    u32 i;

    func_080013e8(NULL);
    func_08003f28();

    for (i = 0; i < 2;) {
        i++;
        sprite_id_delete(gSpriteHandler, i);
        func_0800222c(i);
        task_pool_force_cancel_id(i);
        mem_heap_dealloc_with_id(i);
    }
}


u32 func_0801d9cc(void) {
}


// [func_0801d9d0] Update Pause Menu (State: Play)
u32 func_0801d9d0(void) {
    u32 i;

    if (!gPauseMenu.enabled
     || gPauseMenu.data == NULL
     || (D_03004afc & gPauseMenu.data->pauseButton) != gPauseMenu.data->pauseButton) {
        return FALSE;
    }

    pause_all_soundplayers(TRUE);
    sprite_handler_set_global_pause(gSpriteHandler, TRUE);
    for (i = 0; i < 2; i++) {
        task_pool_pause_id(i+1, TRUE);
    }

    if (gPauseMenu.data->onPause != NULL) {
        gPauseMenu.data->onPause();
    }
    gPauseMenu.state = PAUSE_STATE_PAUSE;
    gPauseMenu.hasBeenUsed = TRUE;
    return TRUE;
}


// [func_0801da48] Update Pause Menu (State: Pause)
void func_0801da48(void) {
    u32 i;

    switch (gPauseMenu.data->update()) {
        case PAUSE_MENU_SELECTION_CONTINUE:
            pause_all_soundplayers(FALSE);
            sprite_handler_set_global_pause(gSpriteHandler, FALSE);
            for (i = 0; i < 2; i++) {
                task_pool_pause_id(i+1, FALSE);
            }
            gPauseMenu.state = PAUSE_STATE_PLAY;
            break;

        case PAUSE_MENU_SELECTION_QUIT:
            func_080070c4(0x20, 0);
            pause_all_soundplayers(FALSE);
            stop_all_soundplayers();
            play_sound(gPauseMenu.data->quitSfx);
            gPauseMenu.state = PAUSE_STATE_STOP;
            break;
    }
}


// [func_0801dabc] Update Pause Menu (State: Stop)
u32 func_0801dabc(void) {
    if (!D_03004b10.unk854_3) return FALSE;

    stop_soundplayer(D_030053c0.musicPlayer);
    task_pool_pause(FALSE);
    stop_beatscript_scene();
    return TRUE;
}


// [func_0801daf8] Set Pause Handler Definition
void func_0801daf8(const struct PauseMenuDefinition *data) {
    gPauseMenu.data = data;
}


// [func_0801db04] Enable Pause Menu
void pause_menu_enabled(u32 enable) {
    gPauseMenu.enabled = enable;
}


/* DEBUG TEXT (Unused) */


extern FontPalette dev_text_font_pal1[];
extern FontPalette dev_text_font_pal2[];


// Update Font Palette 1.
void dev_text_update_pal1(struct DebugText *debugText) {
    u16 *address;
    u32 lineColor;
    u32 i;

    if (debugText->fontPal1 < 0) {
        return;
    }

    debugText->fontCol1++;
    if (debugText->fontCol1 >= 12) {
        debugText->fontCol1 = 0;
    }

    lineColor = debugText->fontCol1 / 4;
    address = &D_03004b10.bgPalette[debugText->fontPal1][8];

    for (i = 0; i < 4; i++) {
        address[i] = dev_text_font_pal1[lineColor][i];
    }
}


// Update Font Palette 2.
void dev_text_update_pal2(struct DebugText *debugText) {
    u16 *address;
    u32 lineColor;
    u32 i;

    if (debugText->fontPal2 < 0) {
        return;
    }

    address = &D_03004b10.bgPalette[debugText->fontPal2][8];

    if (debugText->fontPal2Enabled) {
        debugText->fontCol2++;
        if (debugText->fontCol2 >= 12) {
            debugText->fontCol2 = 0;
        }

        lineColor = debugText->fontCol2 / 4;
        for (i = 0; i < 4; i++) {
            address[i] = dev_text_font_pal2[lineColor][i];
        }
    } else {
        for (i = 0; i < 4; i++) {
            address[i] = 0;
        }
    }
}


// Create new DebugText object.
struct DebugText *create_new_dev_text(u16 memID, u32 layer, u16 *arg2, u32 tilesetNum, u32 baseTileNum, u32 maxTileRows, u32 palette, u32 fontPal1) {
    struct DebugText *debugText;
    void *tilesetAddress;

    debugText = mem_heap_alloc_id(memID, sizeof(struct DebugText));
    debugText->bgFont = create_new_bmp_font_bg(memID, bitmap_font_warioware_body, tilesetNum, baseTileNum, maxTileRows);
    debugText->bgLayer = layer;
    debugText->cursorMap = arg2;
    debugText->string = mem_heap_alloc_id(memID, 0x400);
    debugText->isPrinted = FALSE;
    debugText->textMap = mem_heap_alloc_id(memID, 0x1000);
    debugText->printerTask = -1;
    debugText->palette = palette;
    debugText->fontPal1 = fontPal1;
    debugText->fontPal2 = -1;
    debugText->fontPal2Enabled = FALSE;
    debugText->fontCol2 = 0;
    debugText->unkD = TRUE;
    debugText->reachedEndOfString = FALSE;
    debugText->tilesetIsOutdated = FALSE;
    debugText->baseTile = baseTileNum;
    tilesetAddress = BG_TILESET_BASE(tilesetNum * 0x4000);
    debugText->tileset = tilesetAddress + (baseTileNum * 0x20);
    debugText->scrollKeys = (LEFT_SHOULDER_BUTTON | RIGHT_SHOULDER_BUTTON);

    return debugText;
}


// [D_089dd908] ?
char D_089dd908[] = "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ";

// Print DebugText object.
void dev_text_print(struct DebugText *debugText, const char *string) {
    u16 *bgMap;
    u32 t1, t2;
    u32 i;

    dev_text_reset_print(debugText);
    func_0800eebc(debugText->string, string);
    strcat(debugText->string, D_089dd908);
    debugText->totalChars = bmp_font_bg_get_total_printable_chars(debugText->string);
    debugText->xOffset = -1;

    bgMap = debugText->cursorMap;
    bmp_font_bg_print_text(debugText->bgFont, bgMap, 32, "Q", debugText->palette);
    t1 = bgMap[0];
    t2 = bgMap[32];
    bgMap++;
    for (i = 0; i < 31; i++) {
        bgMap[i] = t1;
        bgMap[i+32] = t2;
    }

    debugText->printerTask = start_bmp_font_bg_printer_task(get_current_mem_id(), debugText->bgFont, debugText->textMap, 0x200, debugText->string, debugText->palette, 1);
    debugText->unk1C = 0;
    debugText->unk1E = 30;
    debugText->reachedEndOfString = FALSE;
    debugText->isPrinted = TRUE;
}


// Update DebugText object.
void update_dev_text(struct DebugText *debugText) {
    u16 offset;
    s16 x;

    if (debugText->tilesetIsOutdated) {
        return;
    }

    if (debugText->isPrinted) {
        offset = debugText->xOffset;

        if ((offset & 7) == 0) {
            u16 *r2 = &debugText->textMap[debugText->unk1C];
            u16 *r1 = &debugText->cursorMap[debugText->unk1E];

            *r1 = *r2;

            r1 += 0x20;
            r2 += 0x200;
            *r1 = *r2;

            debugText->unk1C++;
            if (debugText->unk1C >= debugText->totalChars) {
                if (debugText->unkD) {
                    debugText->unk1C = 0;
                } else {
                    debugText->unk1C--;
                }
                debugText->reachedEndOfString = TRUE;
            }

            debugText->unk1E++;
            if (debugText->unk1E >= 32) {
                debugText->unk1E = 0;
            }
        }

        offset++;
        if (D_03004ac0 & debugText->scrollKeys) {
            if (offset & 7) {
                offset++;
            }
            if (offset & 7) {
                offset++;
            }
            if (offset & 7) {
                offset++;
            }
        }

        debugText->xOffset = offset;
        dev_text_update_pal1(debugText);
        dev_text_update_pal2(debugText);
    }

    x = (debugText->isPrinted) ? debugText->xOffset : 0;
    D_03004b10.BG_OFS[debugText->bgLayer].x = x;
}


// Reset text/print data.
void dev_text_reset_print(struct DebugText *debugText) {
    if (!debugText->isPrinted) {
        return;
    }

    if (get_task_state(debugText->printerTask)) {
        force_stop_task(debugText->printerTask);
    }

    bmp_font_bg_clear_print_data(debugText->bgFont);
    debugText->isPrinted = FALSE;
    debugText->tilesetIsOutdated = TRUE;
}


// Refresh tileset.
void dev_text_reset_tiles(struct DebugText *debugText) {
    u32 tile;

    if (!debugText->tilesetIsOutdated) {
        return;
    }

    debugText->tilesetIsOutdated = FALSE;
    dma3_fill(0x88888888, debugText->tileset, 0x20, 0x20, 0x100);

    tile = debugText->baseTile + (debugText->palette << 12);
    dma3_fill(tile | (tile << 16), debugText->cursorMap, 0x80, 0x20, 0x100);
}


// Set input keys for scrolling.
void dev_text_set_scroll_keys(struct DebugText *debugText, u16 keys) {
    debugText->scrollKeys = keys;
}


// Set behaviour for when the end of the string has been reached.
void dev_text_set_exhausted_string_behaviour(struct DebugText *debugText, u32 arg) {
    debugText->unkD = arg;
}


// Check if the end of the string has been reached.
u32 dev_text_has_exhausted_string(struct DebugText *debugText) {
    return debugText->reachedEndOfString;
}


// Set FontPal2 ID.
void dev_text_set_font_pal_2(struct DebugText *debugText, u32 palette) {
    debugText->fontPal2 = palette;
}


// Enable FontPal2 (disabling will instead clear the palette).
void dev_text_set_enable_font_pal_2(struct DebugText *debugText, u32 enable) {
    debugText->fontPal2Enabled = enable;
}


// [D_089dd94a] Font Palettes
FontPalette dev_text_font_pal1[] = {
    /* PALETTE 00 (White) */ {
        /* 00 */ TO_RGB555(0x000000),
        /* 01 */ TO_RGB555(0x808080),
        /* 02 */ TO_RGB555(0xC0C0C0),
        /* 03 */ TO_RGB555(0xF8F8F8)
    },
    /* PALETTE 01 (Gold) */ {
        /* 00 */ TO_RGB555(0x000000),
        /* 01 */ TO_RGB555(0x806800),
        /* 02 */ TO_RGB555(0xC0A800),
        /* 03 */ TO_RGB555(0xF8E000)
    },
    /* PALETTE 02 (Blue) */ {
        /* 00 */ TO_RGB555(0x000000),
        /* 01 */ TO_RGB555(0x007080),
        /* 02 */ TO_RGB555(0x2090C0),
        /* 03 */ TO_RGB555(0x40B0F8)
    }
};

// [D_089dd962] Font Palettes
FontPalette dev_text_font_pal2[] = {
    /* PALETTE 00 (White) */ {
        /* 00 */ TO_RGB555(0x000000),
        /* 01 */ TO_RGB555(0x808080),
        /* 02 */ TO_RGB555(0xC0C0C0),
        /* 03 */ TO_RGB555(0xF8F8F8)
    },
    /* PALETTE 01 (Gold) */ {
        /* 00 */ TO_RGB555(0x000000),
        /* 01 */ TO_RGB555(0x806800),
        /* 02 */ TO_RGB555(0xC0A800),
        /* 03 */ TO_RGB555(0xF8E000)
    },
    /* PALETTE 02 (Blue) */ {
        /* 00 */ TO_RGB555(0x000000),
        /* 01 */ TO_RGB555(0x007080),
        /* 02 */ TO_RGB555(0x2090C0),
        /* 03 */ TO_RGB555(0x40B0F8)
    }
};



// For readability.
#define gSoftReset ((struct SoftResetSceneData *)gCurrentSceneData)


/* SOFT RESET */


// Stop
void soft_reset_scene_stop(void *endParam) {
    func_08000224();
    if (haveSeenDisclaimer) {
        set_next_scene(&scene_title);
    } else {
        set_next_scene(&scene_disclaimer);
        set_scene_trans_target(&scene_disclaimer, &scene_title);
    }
}


// Start
void soft_reset_scene_start(void *initParam) {
    func_080013e8(NULL);
    sprite_handler_set_global_pause(gSpriteHandler, TRUE);
    gSoftReset->state = 0;
}


// Update
u32 soft_reset_scene_update(void *loopParam) {
    u32 complete = FALSE;

    func_08006e88();
    func_08003fb4();

    switch (gSoftReset->state) {
        case 0:
            func_080070c4(20, 0);
            fade_out_all_soundplayers(20);
            gSoftReset->state++;
            break;

        case 1:
            if (D_03004b10.unk854_3) {
                func_08004058();
                gSoftReset->state++;
            }
            break;

        case 2:
            if ((D_03004ac0 & RESET_BUTTON_COMBO) != RESET_BUTTON_COMBO) {
                pause_all_soundplayers(FALSE);
                stop_all_soundplayers();
                complete = TRUE;
            }
            break;
    }

    func_08007410();
    func_08006f84();
    func_080042a4();

    return complete;
}


// [D_089dd97c] Soft Reset Scene
struct Scene scene_soft_reset = {
    /* Start  */ soft_reset_scene_start,  0,
    /* Update */ soft_reset_scene_update, 0,
    /* Stop   */ soft_reset_scene_stop,   0,
    /* Memory */ sizeof(struct SoftResetSceneData)
};
