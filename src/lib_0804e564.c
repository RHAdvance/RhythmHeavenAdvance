#include "lib_0804e564.h"

asm(".include \"include/gba.inc\"");//Temporary

static volatile u16 D_03004438;
static volatile u16 D_0300443a;
static struct struct_0300443c *D_0300443c;
static u8 D_03004440;
static u32 D_03004448[6];

// Initialise GPIO
void func_0804e564(void) {
    D_03004438 = 2 | 1;
    *D_08bd0cc8 = D_03004438;
    D_0300443a = 2 | 1;
    D_0300443a |= 8;
    *D_08bd0ccc = D_0300443a;
}

// Read Gyro Data
s32 func_0804e598(void) {
    volatile s32 gyroData;
    volatile s32 (*readFunc)(volatile u16 *) = func_0804e938;

    *D_08bd0cd0 = 1;
    D_03004438 &= ~1;
    *D_08bd0cc8 = D_03004438;

    gyroData = readFunc(&D_03004438);
    D_03004438 |= 1;
    *D_08bd0cc8 = D_03004438;
    *D_08bd0cd0 = 0;

    if ((gyroData != 0) && (gyroData != 0xfff)) {
        return gyroData << 4;
    } else {
        return -1;
    }
}

// Enable Rumble
void func_0804e618(u32 arg0) {
    D_03004438 &= ~8;
    D_03004438 |= (arg0 << 3);
    *D_08bd0cc8 = D_03004438;
}

// Initialise Gyro/Rumble
void func_0804e640(struct struct_0300443c *arg0) {
    func_0804e564();
    D_0300443c = arg0;

    arg0->unk0 = 0;
    arg0->unk20 = D_08bd0cd4[0];
    arg0->unk8 = 0x8000;
    arg0->unkC = arg0->unk8 << arg0->unk20;
    arg0->unk22 = 0;
    arg0->unk1C = 0;
    D_030064d4 = func_0804e598;
    D_03004440 = TRUE;
}

void func_0804e690(u32 arg0) {
    u8 temp;

    D_0300443c->unk0 = arg0;
    temp = D_08bd0cd4[(arg0 / 8) % 4];
    D_0300443c->unkC = (D_0300443c->unkC >> D_0300443c->unk20) << temp;
    D_0300443c->unk20 = temp;
}

void func_0804e6c4(u32 arg0) {
    D_0300443c->unk10 = 0;
    D_0300443c->unk12 = 0;
    D_0300443c->unk18 = 0x7fffffff;
    D_0300443c->unk14 = 0;
    D_0300443c->unk1C = 0;
    D_0300443c->unk22 = arg0;
}

void func_0804e6e4(void) {
    s32 temp_r1;
    u32 temp_r3;
    
    if (!D_0300443c->unk22) return;
    
    temp_r1 = D_0300443c->unk4;
    if (temp_r1 < D_0300443c->unk18) {
        D_0300443c->unk18 = temp_r1;
    }
    if (temp_r1 > D_0300443c->unk14) {
        D_0300443c->unk14 = temp_r1;
    }
    temp_r3 = D_0300443c->unk1C + temp_r1;
    D_0300443c->unk1C = temp_r3;
    D_0300443c->unk10++;
    if ((D_0300443c->unk14 - D_0300443c->unk18) < 0x28) {
        if (0x1d < D_0300443c->unk10) {
            D_0300443c->unk8 = temp_r3 / D_0300443c->unk10;
            D_0300443c->unk22 = 0;
            D_0300443c->unk10 = 0;
            D_0300443c->unk18 = 0x7fffffff;
            D_0300443c->unk14 = 0;
            D_0300443c->unk1C = 0;
            return;
        }
    } else {
        if (D_0300443c->unk12 < D_0300443c->unk10) {
            D_0300443c->unk12 = D_0300443c->unk10;
            D_0300443c->unk8 = temp_r3 / D_0300443c->unk10;
        }
        D_0300443c->unk10 = 0;
        D_0300443c->unk18 = 0x7fffffff;
        D_0300443c->unk14 = 0;
        D_0300443c->unk1C = 0;
    }
        D_0300443c->unk22--;
}

void func_0804e77c(void) {
    u32 temp_r7 = TRUE;
    u32 temp_r5;
    u32 temp_r4;
    u32 temp_r1;
    u32 temp_r0;
    s32 temp_r0_1;
    
    if ((D_0300443c->unk0 & 0x20) || (D_0300443c->unk22)) return;

    temp_r5 = D_0300443c->unk8;
    temp_r1 = D_0300443c->unk4;
    if (temp_r1 < D_0300443c->unk18) {
        D_0300443c->unk18 = temp_r1;
    }
    if (temp_r1 > D_0300443c->unk14) {
        D_0300443c->unk14 = temp_r1;
    }
    temp_r4 = D_0300443c->unk1C + temp_r1;
    D_0300443c->unk1C = temp_r4;
    D_0300443c->unk10++;
    if ((D_0300443c->unk14 - D_0300443c->unk18) < 0x30) {
        if (D_0300443c->unk10 > 0x1d) {
            temp_r4 /= D_0300443c->unk10;
            temp_r0_1 = temp_r4 - temp_r5;
            temp_r0 = 0x100 / (u32)(clamp_int32(ABS(temp_r0_1), 0x10, 0x40));
            if (temp_r4 < temp_r5) {
                temp_r5 -= temp_r0;
                if (temp_r5 < temp_r4) {
                    temp_r5 = temp_r4;
                }
            }
            if (temp_r4 > temp_r5) {
                temp_r5 += temp_r0;
                if (temp_r5 > temp_r4) {
                    temp_r5 = temp_r4;
                }
            }
        } else {
            temp_r7 = FALSE;
        }
    }
    if (temp_r7) {
        D_0300443c->unk10 = 0;
        D_0300443c->unk18 = 0x7fffffff;
        D_0300443c->unk14 = 0;
        D_0300443c->unk1C = 0;
    }
    D_0300443c->unk8 = temp_r5;
}

u32 func_0804e834(void) {
    if (D_0300443c->unk4 != -1) {
        D_0300443c->unkC = (D_0300443c->unkC - (D_0300443c->unkC >> D_0300443c->unk20)) + D_0300443c->unk4;
    }
    return (D_0300443c->unkC >> D_0300443c->unk20) - D_0300443c->unk8;
}

u32 func_0804e870(u32 *arg0) {
    D_0300443c->unk4 = D_030064d4();
    if (D_0300443c->unk4 != -1) {
        func_0804e6e4();
        func_0804e77c();
    }
    *arg0 = func_0804e834();
    if (D_0300443c->unk0 & 1) {
        *arg0 = -*arg0;
    }
    return D_0300443c->unk22;
}

void func_0804e8bc(s32 *arg0) {
    *arg0 = func_0804e598();
}

void func_0804e8cc(u32 arg0) {
    if (arg0) {
        D_0300443c->unk0 &= ~0x20;
    } else {
        D_0300443c->unk0 |= 0x20;
    }
}

// Set Rumble
void func_0804e8f8(u32 arg0) {
    if (!D_03004440) {
        arg0 = FALSE;
    }
    func_0804e618(arg0);
}

// Turn off current Rumble, toggle Rumble
void func_0804e914(u32 arg0) {
    func_0804e618(0);
    D_03004440 = arg0;
}

u32 func_0804e92c(void) {
    return D_0300443c->unk8;
}
