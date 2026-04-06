#include "code_080092cc.h"
#ifdef RUMBLE
#include "rumble_backend.h"
#endif
#include "memory.h"

// Gyro/Rumble Library Interface

#define RUMBLE_MAX_INTENSITY 0xFF

#ifdef RUMBLE
#define RUMBLE_MENU_MOVE_INTENSITY 96
#define RUMBLE_MENU_CONFIRM_INTENSITY 120
#define RUMBLE_MENU_CANCEL_INTENSITY 84
#define RUMBLE_MENU_LIMIT_INTENSITY 72
#define RUMBLE_MENU_LIMIT_PULSE_COUNT 2
#define RUMBLE_MENU_LIMIT_GAP_TICKS 14
#define RUMBLE_MENU_ERROR_INTENSITY 84
#define RUMBLE_MENU_BONUS_INTENSITY 144
#endif

static struct struct_0300443c D_03001110;
static s32 D_03001134[22]; // ..?
static u32 D_03001190;
static u32 D_03001194; // ..?
static u32 D_03001198; // ..?
static u8 D_0300119c; 
static u8 D_0300119d;
static volatile u32 D_030011a0;
static u8 D_030011a4;
static s32 D_030011a8;
static u32 D_030011ac;
static s32 D_030011b0[20];
static u8 D_03001200;
static u8 D_03001201;
static s32 D_03001204;
static u32 D_03001208;
static volatile u16 D_0300120c;
static volatile u16 D_0300120e;
static volatile u32 *D_03001210;
static s32 D_03001214; // ..?
static u8 sRumbleQueuedPulseCount;
static u8 sRumbleQueuedPulseGap;
static u8 sRumbleQueuedPulseDelay;
static u32 sRumbleQueuedPulseIntensity;

extern u32 (*fast_udivsi3)(u32 dividend, u32 divisor); // move into a header

static void rumble_gpio_init(void);
static void rumble_set_hardware_state(u32 enabled);
static u32 rumble_clamp_intensity(u32 intensity);
static void rumble_begin_pulse(u32 intensity);
static void rumble_queue_pattern(u32 intensity, u32 pulseCount, u32 gapTicks);
static void rumble_clear_pattern(void);
static void rumble_cancel_pulse(void);
static void rumble_set_enabled(u32 enable);

void func_080092cc(void) {
    func_0804e640(&D_03001110);
    func_0804e690(24);
    func_0804e6c4(300);
    if (!D_03004aec) {
        D_03004aec = 60;
    }
    D_0300119c = 0;
    D_0300119d = 0;
    D_030064d4 = func_080093c0;
}

u32 func_0800931c(void) {
    u32 temp_r2 = func_0804e870(&D_03001190);

    if ((D_03001190 + 0xb) < 0x17) {
        if (D_0300119c < 6) {
            D_0300119c++;
        } else {
            D_03001190 = 0;
        }
    } else {
        D_0300119c = 0;
    }
    D_0300119d = temp_r2 == 0;
    return temp_r2;
}

s32 func_0800936c(void) {
    s32 *temp = &D_03001190;
    return FIXED_POINT_MUL((INT_TO_FIXED(D_03004aec) / 49), *temp) >> 4; // / 16
}

s32 func_08009394(void) {
    return func_0800936c();
}

s32 func_080093a0(void) {
    return 0;
}

s32 func_080093a4(void) {
    return 0;
}

u32 func_080093a8(void) {
    return D_03001190;
}

u32 func_080093b4(void) {
    return D_0300119d;
}

s32 func_080093c0(void) {
    s32 temp_r0;
    u32 temp_r3 = 0;
    u32 temp_ip = 1;
    u32 i;
    s32 sp0[20];
    s32 temp;
    
    REG_IE &= ~INTERRUPT_TIMER3;
    temp = D_030011a0;
    
    for (i = 0; i < temp; i++) {
        sp0[i] = D_030011b0[i];
    }
    D_030011a0 = 0;
    REG_IE |= INTERRUPT_TIMER3;
    if (temp) {
        temp_r3 = ABS(sp0[0]);
        for (i = 1; i < temp; i++) {
            temp_r0 = ABS(sp0[i]);
            if (temp_r0 > temp_r3) {
                temp_r3 = ABS(sp0[i]);
            }
        }
        temp_ip = 1;
    }
    return fast_udivsi3(temp_r3, temp_ip);
}

void func_08009458(void) {
    s32 temp_r4;

    func_0804e8f8(0);
    temp_r4 = func_0804e598();
    if ((D_030011a0 < 0x14) && (temp_r4 != -1)) {
        D_030011b0[D_030011a0++] = temp_r4;
    }
    if (D_030011a4 & 1) {
        func_0804e8f8(TRUE);
        D_030011a8 += 0xaaa;
        if (D_030011a8 >= D_030011ac) {
            D_030011a4 &= ~1;
            if (D_030011ac > 0x10000) {
                D_030011a8 = 0x10000;
            }
        }
    } else {
        func_0804e8f8(FALSE);
        D_030011a8 -= 0x375;
        if (D_030011a8 < 0) {
            D_030011a8 = 0;
        }
    }
    REG_TM3 = ((TIMER_ENABLE | TIMER_IRQ | TIMER_FREQUENCY_1024_PULSES) << 16) | 0xfff0;
}

void func_08009508(void) {
    REG_TM3 = ((TIMER_ENABLE | TIMER_IRQ | TIMER_FREQUENCY_1024_PULSES) << 16) | 0xfff0;
    func_0804e8f8(FALSE);
    D_030011a4 = 0;
    D_030011a8 = 0;
    D_030011ac = 0;
    D_030011a0 = 0;
}

void func_08009548(void) {
    REG_TM3 = 0;
    func_0804e8f8(FALSE);
    func_0804e914(FALSE);
}

void rumble_request_pulse(u32 arg0) {
    s24_8 temp_r4;
#ifdef RUMBLE
    rumble_clear_pattern();
    rumble_begin_pulse(arg0);
    return;
#endif
    if (arg0 > RUMBLE_MAX_INTENSITY) {
        arg0 = RUMBLE_MAX_INTENSITY;
    }
    temp_r4 = INT_TO_FIXED(arg0) * 16;
    if (((D_030011a4 & 1) == 0) || (D_030011ac <= temp_r4)) {
        D_030011ac = temp_r4;
    }
    if (D_030011a8 < D_030011ac) {
        D_030011a4 |= 1;
    }
}

void rumble_play_menu_move(void) {
#ifdef RUMBLE
    rumble_request_pulse(RUMBLE_MENU_MOVE_INTENSITY);
#endif
}

void rumble_play_menu_confirm(void) {
#ifdef RUMBLE
    rumble_request_pulse(RUMBLE_MENU_CONFIRM_INTENSITY);
#endif
}

void rumble_play_menu_cancel(void) {
#ifdef RUMBLE
    rumble_request_pulse(RUMBLE_MENU_CANCEL_INTENSITY);
#endif
}

void rumble_play_menu_limit(void) {
#ifdef RUMBLE
    rumble_queue_pattern(RUMBLE_MENU_LIMIT_INTENSITY, RUMBLE_MENU_LIMIT_PULSE_COUNT, RUMBLE_MENU_LIMIT_GAP_TICKS);
#endif
}

void rumble_play_menu_error(void) {
#ifdef RUMBLE
    rumble_queue_pattern(RUMBLE_MENU_ERROR_INTENSITY, RUMBLE_MENU_LIMIT_PULSE_COUNT, RUMBLE_MENU_LIMIT_GAP_TICKS);
#endif
}

void rumble_play_menu_bonus(void) {
#ifdef RUMBLE
    rumble_request_pulse(RUMBLE_MENU_BONUS_INTENSITY);
#endif
}

void rumble_play_long(void) {
#ifdef RUMBLE
    rumble_request_pulse(RUMBLE_MAX_INTENSITY);
#endif
}

void func_080095a8(void) {
    func_0804e8f8(FALSE);
    D_030011a4 = 0;
}

void func_080095c0(void) {
    if (D_030011a4 & 1) {
        func_0804e8f8(TRUE);
    } else {
        func_0804e8f8(FALSE);
    }
}

// Split here?

void func_080095e8(u32 arg0) {
    D_03005370 = 0;
    D_03004af4 = 0;
    D_030046b0 = arg0;
}

void func_08009604(void) {
    s32 temp_r2;
    s32 temp_r3;
    s32 temp_r5;
    
    D_03004af4 = 0;
    temp_r5 = D_03005370;
    temp_r3 = func_080093a8();
    temp_r2 = temp_r3 >> 4; // / 16
    D_03005370 = temp_r2;
    if ((temp_r2 >= (D_030046b0 * 8)) && (temp_r2 > temp_r5)) {
        if ((temp_r2 - temp_r5) > ((temp_r2 * 5) >> 3)) { // / 8
            s32 temp = temp_r3 >> 7; // / 128
            temp *= temp;
            temp = FIXED_TO_INT(temp);
            if (!temp) {
                temp = 1;
            }
            D_03004af4 = temp;
        }
    }
}

u32 func_0800965c(void) {
    return D_03004af4;
}

void func_08009668(u32 arg0) {
    D_030046b0 = arg0;
}

static void rumble_gpio_init(void) {
#ifdef RUMBLE
    return;
#else
    REG_GPIO_CNT = 1;
    D_0300120c = 2 | 1;
    REG_GPIO_DATA = D_0300120c;
    D_0300120e = 2 | 1;
    D_0300120e |= 8;
    REG_GPIO_DIR = D_0300120e;
#endif
}

static void rumble_set_hardware_state(u32 arg0) {
    if (!D_03001200) {
        arg0 = FALSE;
    }
#ifdef RUMBLE
    rumble_backend_set_state(arg0);
#else
    REG_GPIO_CNT = 1;
    D_0300120c &= ~8;
    D_0300120c |= arg0 << 3;
    REG_GPIO_DATA = D_0300120c;
#endif
}

static u32 rumble_clamp_intensity(u32 intensity) {
    if (intensity > RUMBLE_MAX_INTENSITY) {
        intensity = RUMBLE_MAX_INTENSITY;
    }

    return intensity;
}


static void rumble_begin_pulse(u32 arg0) {
    s24_8 targetIntensity;
    
    if(CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_DISABLE_RUMBLE)) {
        return;
    }

    arg0 = rumble_clamp_intensity(arg0);
    targetIntensity = INT_TO_FIXED(arg0) * 16;
    if (((D_03001201 & 1) == 0) || (D_03001208 <= targetIntensity)) {
        D_03001208 = targetIntensity;
    }
    if (D_03001204 < D_03001208) {
        D_03001201 |= 1;
    }
}


static void rumble_queue_pattern(u32 intensity, u32 pulseCount, u32 gapTicks) {
    rumble_clear_pattern();
    if (pulseCount == 0) {
        return;
    }

    rumble_begin_pulse(intensity);
    if (pulseCount > 1) {
        sRumbleQueuedPulseCount = pulseCount - 1;
        sRumbleQueuedPulseGap = gapTicks;
        sRumbleQueuedPulseDelay = gapTicks;
        sRumbleQueuedPulseIntensity = rumble_clamp_intensity(intensity);
    }
}


static void rumble_clear_pattern(void) {
    sRumbleQueuedPulseCount = 0;
    sRumbleQueuedPulseGap = 0;
    sRumbleQueuedPulseDelay = 0;
    sRumbleQueuedPulseIntensity = 0;
}


// partial copy of func_08009458 
void rumble_timer_isr(void) {
    if (D_03001201 & 1) {
        rumble_set_hardware_state(TRUE);
        D_03001204 += 0xaaa;
        if (D_03001204 >= D_03001208) {
            D_03001201 &= ~1;
            if (D_03001208 > 0x10000) {
                D_03001204 = 0x10000;
            }
        }
    } else {
        rumble_set_hardware_state(FALSE);
        D_03001204 -= 0x375;
        if (D_03001204 < 0) {
            D_03001204 = 0;
        }
    }

    if (((D_03001201 & 1) == 0) && (D_03001204 == 0) && (sRumbleQueuedPulseCount != 0)) {
        if (sRumbleQueuedPulseDelay != 0) {
            sRumbleQueuedPulseDelay--;
        } else {
            rumble_begin_pulse(sRumbleQueuedPulseIntensity);
            sRumbleQueuedPulseCount--;
            sRumbleQueuedPulseDelay = sRumbleQueuedPulseGap;
        }
    }

    *D_03001210 = ((TIMER_ENABLE | TIMER_IRQ | TIMER_FREQUENCY_1024_PULSES) << 16) | 0xfff0;
}

void rumble_init(u32 arg0) {
    D_03001210 = &(&(REG_TM0))[arg0];
    rumble_gpio_init();
    *D_03001210 = ((TIMER_ENABLE | TIMER_IRQ | TIMER_FREQUENCY_1024_PULSES) << 16) | 0xfff0;
    rumble_set_hardware_state(FALSE);
    D_03001201 = 0;
    D_03001204 = 0;
    D_03001208 = 0;
    D_03001200 = 1;
    rumble_clear_pattern();
}

void rumble_shutdown(void) {
    *D_03001210 = 0;
    rumble_cancel_pulse();
    rumble_set_enabled(FALSE);
}

static void rumble_cancel_pulse(void) {
    rumble_set_hardware_state(FALSE);
    D_03001201 = 0;
    D_03001204 = 0;
    D_03001208 = 0;
    rumble_clear_pattern();
}

static void rumble_set_enabled(u32 arg0) {
    rumble_set_hardware_state(FALSE);
    D_03001200 = arg0;
}
