#include "rumble_backend.h"

#ifdef RUMBLE

// thanks a lot to github.com/evanbowman/gba-rumble for most of this

#define REG_RCNT *(volatile u16 *)(IORAMBase + 0x134)
#define REG_SIOCNT *(volatile u16 *)(IORAMBase + 0x128)
#define REG_SIODATA32 *(volatile u32 *)(IORAMBase + 0x120)

#define RUMBLE_GPIO_DATA *(volatile u16 *)(GameROMBase + 0xC4)
#define RUMBLE_GPIO_DIRECTION *(volatile u16 *)(GameROMBase + 0xC6)
#define RUMBLE_GPIO_CONTROL *(volatile u16 *)(GameROMBase + 0xC8)

#define SIO_SO_HIGH (1 << 3)
#define SIO_START (1 << 7)
#define SIO_32BIT 0x1000
#define SIO_IRQ 0x4000

#define R_NORMAL 0x0000

#define RUMBLE_GBP_UNLOCK_FRAMES 125
#define RUMBLE_GBP_FADE_FRAMES 16
#define RUMBLE_GBP_UNLOCK_KEYMASK 0x030F
#define RUMBLE_GBP_BG0CNT (BGCNT_256_PALETTE | (2 << 2))

#define RUMBLE_GBP_LOGO_PALETTE_SIZE 128
#define RUMBLE_GBP_LOGO_TILEMAP_SIZE 844
#define RUMBLE_GBP_LOGO_TILESET_SIZE 0x4000

enum RumblePlatformMode {
    RUMBLE_PLATFORM_CARTRIDGE = 0,
    RUMBLE_PLATFORM_GBP,
};

enum RumbleGbpState {
    RUMBLE_GBP_START = 0x40000026,
    RUMBLE_GBP_STOP = 0x40000004,
    RUMBLE_GBP_HARD_STOP = 0x40000015,
};

enum GbpCommsStage {
    GBP_COMMS_NINTENDO_HANDSHAKE,
    GBP_COMMS_CHECK_MAGIC1,
    GBP_COMMS_CHECK_MAGIC2,
    GBP_COMMS_RUMBLE,
    GBP_COMMS_FINALIZE,
};

struct GbpCommsState {
    enum GbpCommsStage stage;
    u32 serialIn;
    u16 index;
    u16 out0;
    u16 out1;
};

extern const u8 gbp_logo_palette_bin[];
extern const u8 gbp_logo_tiles_bin[];
extern const u8 gbp_logo_pixels_bin[];

static struct GbpCommsState sGbpComms;
static enum RumblePlatformMode sRumblePlatformMode;
static u32 sRumbleGbpState;

static void rumble_backend_wait_for_frame(void) {
    while (REG_VCOUNT >= 160) {
    }
    while (REG_VCOUNT < 160) {
    }
}

static void rumble_backend_reset_gbp_comms(void) {
    struct GbpCommsState reset = {0};

    sGbpComms = reset;
    sGbpComms.stage = GBP_COMMS_NINTENDO_HANDSHAKE;
}

static void rumble_backend_init_cartridge_gpio(void) {
    RUMBLE_GPIO_CONTROL = 1;
    RUMBLE_GPIO_DIRECTION = 1 << 3;
    RUMBLE_GPIO_DATA = 0;
}

static void rumble_backend_fade_gbp_splash_to_white(void) {
    u32 frame;

    REG_BLDMOD = BLDMOD_BG0_SRC | BLDMOD_BACKDROP_SRC | (BLEND_MODE_LIGHTEN << 6);
    for (frame = 0; frame <= RUMBLE_GBP_FADE_FRAMES; frame++) {
        REG_COLEY = (frame * 16) / RUMBLE_GBP_FADE_FRAMES;
        rumble_backend_wait_for_frame();
    }
    REG_BLDMOD = 0;
    REG_COLEY = 0;
}

static u32 rumble_backend_try_unlock_gbp(void) {
    u32 frame;
    u32 gbpDetected;

    gbpDetected = FALSE;

    REG_DISPCNT = VIDEO_MODE_4TEXT | DISPCNT_DISPLAY_BG0;
    REG_BG0CNT = RUMBLE_GBP_BG0CNT;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;

    DmaCopy16(3, gbp_logo_pixels_bin, (void *)(VRAMBase + 0x8000), RUMBLE_GBP_LOGO_TILESET_SIZE);
    DmaCopy16(3, gbp_logo_tiles_bin, (void *)VRAMBase, RUMBLE_GBP_LOGO_TILEMAP_SIZE);
    DmaCopy16(3, gbp_logo_palette_bin, (void *)PaletteRAMBase, RUMBLE_GBP_LOGO_PALETTE_SIZE);

    for (frame = 0; frame < RUMBLE_GBP_UNLOCK_FRAMES; frame++) {
        rumble_backend_wait_for_frame();
        if (REG_KEY == RUMBLE_GBP_UNLOCK_KEYMASK) {
            gbpDetected = TRUE;
        }
    }

    rumble_backend_fade_gbp_splash_to_white();

    DmaFill32(3, 0, VRAMBase, 0x18000);
    *(u16 *)PaletteRAMBase = 0x7FFF;
    REG_DISPCNT = DISPCNT_FORCE_BLANK;
    REG_BG0CNT = 0;

    return gbpDetected;
}

static void rumble_backend_gbp_serial_start(void) {
    if (sRumblePlatformMode != RUMBLE_PLATFORM_GBP) {
        return;
    }

    if (sGbpComms.serialIn == 0x30000003) {
        return;
    }

    REG_SIOCNT &= ~1;
    REG_SIOCNT |= SIO_START;
}

void rumble_backend_serial_isr(void) {
    u32 result;

    sGbpComms.serialIn = REG_SIODATA32;
    result = 0;

    switch (sGbpComms.stage) {
        case GBP_COMMS_RUMBLE:
            if (sGbpComms.serialIn == 0x30000003) {
                result = sRumbleGbpState;
            } else {
                sGbpComms.stage = GBP_COMMS_FINALIZE;
            }
            break;

        case GBP_COMMS_FINALIZE:
            rumble_backend_reset_gbp_comms();
            return;

        case GBP_COMMS_NINTENDO_HANDSHAKE: {
            static char const handshakeData[] = {"NINTENDO"};
            u16 inLower;

            inLower = (u16)sGbpComms.serialIn;
            if (inLower == 0x8002) {
                result = 0x10000010;
                sGbpComms.stage = GBP_COMMS_CHECK_MAGIC1;
                break;
            }

            if ((sGbpComms.serialIn >> 16) != sGbpComms.out1) {
                sGbpComms.index = 0;
            }

            // to-do: investigate the PR that claims this is invalid
            // https://github.com/evanbowman/gba-rumble/pull/2/changes
            if (sGbpComms.index > 3) {
                sGbpComms.out0 = 0x8000;
            } else {
                u32 expected;

                expected = (u32)~(sGbpComms.out1 | (sGbpComms.out0 << 16));
                if (sGbpComms.serialIn == expected) {
                    sGbpComms.index += 1;
                }
                sGbpComms.out0 = ((const u16 *)handshakeData)[sGbpComms.index];
            }

            sGbpComms.out1 = (u16)~inLower;
            result = sGbpComms.out1;
            result |= (u32)sGbpComms.out0 << 16;
            break;
        }

        case GBP_COMMS_CHECK_MAGIC1:
            if (sGbpComms.serialIn == 0x10000010) {
                result = 0x20000013;
                sGbpComms.stage = GBP_COMMS_CHECK_MAGIC2;
            } else {
                sGbpComms.stage = GBP_COMMS_FINALIZE;
            }
            break;

        case GBP_COMMS_CHECK_MAGIC2:
            if (sGbpComms.serialIn == 0x20000013) {
                result = RUMBLE_GBP_STOP;
                sGbpComms.stage = GBP_COMMS_RUMBLE;
            } else {
                sGbpComms.stage = GBP_COMMS_FINALIZE;
            }
            break;
    }

    REG_SIODATA32 = result;
    REG_SIOCNT |= SIO_START;
}

void rumble_backend_init(void) {
    sRumbleGbpState = RUMBLE_GBP_HARD_STOP;
    sRumblePlatformMode = RUMBLE_PLATFORM_CARTRIDGE;

    if (rumble_backend_try_unlock_gbp()) {
        sRumblePlatformMode = RUMBLE_PLATFORM_GBP;
        REG_RCNT = R_NORMAL;
        REG_SIOCNT = SIO_32BIT | SIO_SO_HIGH;
        REG_SIOCNT |= SIO_IRQ;
        rumble_backend_reset_gbp_comms();
    } else {
        rumble_backend_init_cartridge_gpio();
    }

    rumble_backend_set_state(FALSE);
}

void rumble_backend_update(void) {
    rumble_backend_gbp_serial_start();
}

void rumble_backend_set_state(u32 enabled) {
    if (sRumblePlatformMode == RUMBLE_PLATFORM_GBP) {
        sRumbleGbpState = enabled ? RUMBLE_GBP_START : RUMBLE_GBP_STOP;
    } else {
        rumble_backend_init_cartridge_gpio();
        RUMBLE_GPIO_DATA = enabled ? (1 << 3) : 0;
    }
}

#else

void rumble_backend_init(void) {
}

void rumble_backend_update(void) {
}

void rumble_backend_set_state(u32 enabled) {
    (void)enabled;
}

void rumble_backend_serial_isr(void) {
}

#endif
