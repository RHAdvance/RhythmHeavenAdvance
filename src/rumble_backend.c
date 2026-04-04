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

static struct GbpCommsState sGbpComms;
static enum RumblePlatformMode sRumblePlatformMode;
static u32 sRumbleGbpState;

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

void rumble_backend_select_platform(u32 useGbp) {
    sRumbleGbpState = RUMBLE_GBP_HARD_STOP;

    if (useGbp) {
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

void rumble_backend_init(void) {
    rumble_backend_select_platform(FALSE);
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

void rumble_backend_select_platform(u32 useGbp) {
    (void)useGbp;
}

void rumble_backend_update(void) {
}

void rumble_backend_set_state(u32 enabled) {
    (void)enabled;
}

void rumble_backend_serial_isr(void) {
}

#endif
