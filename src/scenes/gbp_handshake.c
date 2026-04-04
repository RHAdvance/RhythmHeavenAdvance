#include "global.h"
#include "scenes.h"
#include "../rumble_backend.h"


#ifdef RUMBLE

#define RUMBLE_GBP_UNLOCK_FRAMES 125
#define RUMBLE_GBP_FADE_FRAMES 16
#define RUMBLE_GBP_UNLOCK_KEYMASK 0x030F
#define RUMBLE_GBP_BG0CNT (BGCNT_256_PALETTE | (2 << 2))

#define RUMBLE_GBP_LOGO_PALETTE_SIZE 128
#define RUMBLE_GBP_LOGO_TILEMAP_SIZE 844
#define RUMBLE_GBP_LOGO_TILESET_SIZE 0x4000

enum GbpHandshakeState {
    GBP_HANDSHAKE_STATE_SHOW_LOGO,
    GBP_HANDSHAKE_STATE_FADE_OUT,
    GBP_HANDSHAKE_STATE_DONE
};

struct GbpHandshakeSceneData {
    u16 state;
    u16 timer;
    u32 gbpDetected;
};

#define gGbpHandshake ((struct GbpHandshakeSceneData *)gCurrentSceneData)

extern const u8 gbp_logo_palette_bin[];
extern const u8 gbp_logo_tiles_bin[];
extern const u8 gbp_logo_pixels_bin[];

static void gbp_handshake_scene_finish(u32 useGbp) {
    DmaFill32(3, 0, VRAMBase, 0x18000);
    *(u16 *)PaletteRAMBase = 0x7FFF;

    REG_BLDMOD = 0;
    REG_COLEY = 0;
    REG_DISPCNT = DISPCNT_FORCE_BLANK;
    REG_BG0CNT = 0;

    rumble_backend_select_platform(useGbp);
}

#else

struct GbpHandshakeSceneData {
    u8 unused;
};

#endif


void gbp_handshake_scene_start(void *sVar, s32 dArg) {
    (void)sVar;
    (void)dArg;

#ifdef RUMBLE
    gGbpHandshake->state = GBP_HANDSHAKE_STATE_SHOW_LOGO;
    gGbpHandshake->timer = 0;
    gGbpHandshake->gbpDetected = FALSE;

    REG_BLDMOD = 0;
    REG_COLEY = 0;

    REG_DISPCNT = VIDEO_MODE_4TEXT | DISPCNT_DISPLAY_BG0;
    REG_BG0CNT = RUMBLE_GBP_BG0CNT;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;

    DmaCopy16(3, gbp_logo_pixels_bin, (void *)(VRAMBase + 0x8000), RUMBLE_GBP_LOGO_TILESET_SIZE);
    DmaCopy16(3, gbp_logo_tiles_bin, (void *)VRAMBase, RUMBLE_GBP_LOGO_TILEMAP_SIZE);
    DmaCopy16(3, gbp_logo_palette_bin, (void *)PaletteRAMBase, RUMBLE_GBP_LOGO_PALETTE_SIZE);
#else
    rumble_backend_select_platform(FALSE);
#endif
}

u32 gbp_handshake_scene_update(void *sVar, s32 dArg) {
    (void)sVar;
    (void)dArg;

#ifdef RUMBLE
    switch (gGbpHandshake->state) {
        case GBP_HANDSHAKE_STATE_SHOW_LOGO:
            if (REG_KEY == RUMBLE_GBP_UNLOCK_KEYMASK) {
                gGbpHandshake->gbpDetected = TRUE;
            }

            gGbpHandshake->timer++;
            if (gGbpHandshake->timer >= RUMBLE_GBP_UNLOCK_FRAMES) {
                gGbpHandshake->state = GBP_HANDSHAKE_STATE_FADE_OUT;
                gGbpHandshake->timer = 0;
                REG_BLDMOD = BLDMOD_BG0_SRC | BLDMOD_BACKDROP_SRC | (BLEND_MODE_LIGHTEN << 6);
            }
            break;

        case GBP_HANDSHAKE_STATE_FADE_OUT:
            REG_COLEY = (gGbpHandshake->timer * 16) / RUMBLE_GBP_FADE_FRAMES;
            gGbpHandshake->timer++;

            if (gGbpHandshake->timer > RUMBLE_GBP_FADE_FRAMES) {
                gbp_handshake_scene_finish(gGbpHandshake->gbpDetected);
                gGbpHandshake->state = GBP_HANDSHAKE_STATE_DONE;
                return TRUE;
            }
            break;

        default:
            return TRUE;
    }

    return FALSE;
#else
    return TRUE;
#endif
}

void gbp_handshake_scene_stop(void *sVar, s32 dArg) {
    (void)sVar;
    (void)dArg;
}


struct Scene scene_gbp_handshake = {
    /* Start  */ gbp_handshake_scene_start,  0,
    /* Update */ gbp_handshake_scene_update, 0,
    /* Stop   */ gbp_handshake_scene_stop,   0,
    /* Memory */ sizeof(struct GbpHandshakeSceneData)
};
