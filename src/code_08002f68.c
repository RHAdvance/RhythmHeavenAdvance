#include "code_08001360.h"
#include "code_08002f68.h"
#include "memory_heap.h"


/* ARITHMETIC */


#define FUNC_SQRT_SIZE ((u32)&math_sqrt_rom_end - (u32)math_sqrt_rom)

extern s32 math_sqrt_rom(s32 value);
extern void *math_sqrt_rom_end;
extern s32 (*math_sqrt)(s32 value);

extern u8 D_0893640c[];
extern u16 D_0893644e[];

static s32 math_sqrt_code[120];

extern u8 sFading;


// Init. sqrt()
void init_math_sqrt(void) {
    DmaCopy32(3, math_sqrt_rom, math_sqrt_code, FUNC_SQRT_SIZE);
    math_sqrt = (void *)math_sqrt_code;
}


// ? (8 bits)
u8 func_08002f9c(s16 arg0, s16 arg1) {
    s32 r6;
    s32 sign;

    r6 = 0;
    sign = 1;

    if (arg0 < 0) {
        arg0 = -arg0;
        r6 = (64 * 2);
        sign = -sign;
    }

    if (arg1 < 0) {
        arg1 = -arg1;
        sign = -sign;
    }

    if (arg0 < arg1) {
        s32 swap;

        r6 += (64 * sign);
        sign = -sign;
        swap = arg0;
        arg0 = arg1;
        arg1 = swap;
    }

    return r6 + (sign * D_0893640c[64 * arg1 / arg0]);
}


// ? (16 bits)
u16 func_08003004(s16 arg0, s16 arg1) {
    s32 r6;
    s32 sign;

    r6 = 0;
    sign = 1;

    if (arg0 < 0) {
        arg0 = -arg0;
        r6 = (512 * 2);
        sign = -sign;
    }

    if (arg1 < 0) {
        arg1 = -arg1;
        sign = -sign;
    }

    if (arg0 < arg1) {
        s32 swap;

        r6 += (512 * sign);
        sign = -sign;
        swap = arg0;
        arg0 = arg1;
        arg1 = swap;
    }

    return r6 + (sign * D_0893644e[256 * arg1 / arg0]);
}


void func_08003070(struct struct_08003070 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6) {
    if ((arg1 + arg3) > arg0->unk14) {
        u32 temp = arg0->unk14 - arg1;
        u32 temp1 = arg3 - temp;
        
        func_08003070(arg0, arg1, arg2, temp, arg4, arg5, arg6);
        func_08003070(arg0, 0, arg2, temp1, arg4, arg5 + temp, arg6);
    } else if ((arg2 + arg4) > arg0->unk15) {
        u32 temp = arg0->unk15 - arg2;
        u32 temp1 = arg4 - temp;

        func_08003070(arg0, arg1, arg2, arg3, temp, arg5, arg6);
        func_08003070(arg0, arg1, 0, arg3, temp1, arg5, arg6 + temp);
    } else {
        u32 temp_r8 = (!arg0->unk0_b0) ? 16 * sizeof(u16) : 32 * sizeof(u16);
        u8 *temp_r6 = &arg0->unk8[(arg1 + arg2 * arg0->unk14) * temp_r8];
        u8 *temp_r4 = &arg0->unk18[(arg5 + arg6 * arg0->unk20) * temp_r8];
        u32 i;

        for (i = 0; i < arg4; i++) {
            dma3_set(temp_r4, temp_r6, arg3 * temp_r8, 32, 256);
            temp_r6 += arg0->unk14 * temp_r8;
            temp_r4 += arg0->unk20 * temp_r8;
        }
    }
}

void func_0800318c(struct struct_08003070 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6) {
    if ((arg1 + arg5) > 32) {
        u32 temp = 32 - arg1;
        u32 temp1 = arg5 - temp;
        
        func_0800318c(arg0, arg1, arg2, arg3, arg4, temp, arg6);
        func_0800318c(arg0, 0, arg2, arg3 + temp, arg4, temp1, arg6);
    } else {
        if ((arg2 + arg6) > 32) {
            u32 temp = 32 - arg2;
            u32 temp1 = arg6 - temp;
            
            func_0800318c(arg0, arg1, arg2, arg3, arg4, arg5, temp);
            func_0800318c(arg0, arg1, 0, arg3, arg4 + temp, arg5, temp1);
        } else {
            u16 *temp_r6 = &arg0->unkC[arg1] + arg2 * 32;
            u16 *temp_r4 = &arg0->unk44[arg3] + arg0->unk14 * arg4;
            u32 i;
            
            for (i = 0; i < arg6; i++) {
                dma3_set(temp_r4, temp_r6, arg5 * 2, 16, 256);
                temp_r6 += 32;
                temp_r4 += arg0->unk14;
            }
        }
    }
}

void func_08003278(struct struct_08003070 *arg0) {
    u32 i;
    
    if (!arg0->unk0_b1) return;
    for (i = 0; i < arg0->unk0_b2; i++) {
        u32 temp_r5;
        u32 temp_r8;
        
        temp_r8 = arg0->unk10;
        temp_r8 += arg0->unk22[i];
        
        temp_r5 = arg0->unk12;
        temp_r5 += arg0->unk2A[i];
        func_08003070(arg0, temp_r8 % arg0->unk14, temp_r5 % arg0->unk15, arg0->unk32[i], arg0->unk3A[i], temp_r8, temp_r5);
        func_0800318c(arg0, temp_r8 % 32, temp_r5 % 32, arg0->unk22[i], arg0->unk2A[i], arg0->unk32[i], arg0->unk3A[i]);
    }
    arg0->unk58[0] = arg0->unk4E + arg0->unk52;
    arg0->unk5C[0] = arg0->unk50 + arg0->unk54;
    arg0->unk0_b1 = 0;
    arg0->unk0_b2 = 0;
}

void func_08003384(struct struct_08003070 *arg0) {
    arg0->unk0_b1 = 0;
    arg0->unk0_b2 = 0;
}

u32 func_08003398(struct struct_08003070 *arg0) {
    return arg0->unk0_b1;
}

void func_080033a0(struct struct_08003070 *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6) {
    u32 temp_r3;
    s32 temp_r5;
    s32 temp_r9;

    // ????
    u8 arg1_1 = arg1;
    u8 arg2_1 = arg2;
    u8 arg3_1 = arg3;
    u8 arg4_1 = arg4;
    u16 arg5_1 = arg5;
    u16 arg6_1 = arg6;
    u32 sp28;
    
    temp_r9 = arg0->unk14;
    sp28 = arg5_1 % temp_r9;
    temp_r5 = arg0->unk15;
    temp_r3 = arg6_1 % temp_r5;

    if ((sp28 + arg3_1) > temp_r9) {
        u32 temp = temp_r9 - sp28;
        u32 temp1 = arg3_1 - temp;
        
        func_080033a0(arg0, arg1_1, arg2_1, temp, arg4_1, arg5_1, arg6_1);
        func_080033a0(arg0, arg1_1 + temp, arg2_1, temp1, arg4_1, arg5_1 + temp, arg6_1);
    } else if ((temp_r3 + arg4_1) > temp_r5) {
        u32 temp = temp_r5 - temp_r3;
        u32 temp1 = arg4_1 - temp;
        
        func_080033a0(arg0, arg1_1, arg2_1, arg3_1, temp, arg5_1, arg6_1);
        func_080033a0(arg0, arg1_1, arg2_1 + temp, arg3_1, temp1, arg5_1, arg6_1 + temp);
    } else {
        u16 *temp_r6 = &arg0->unk44[arg1_1] + arg2_1 * temp_r9;
        u8 *temp_r7 = &arg0->unk1C[arg5_1] + arg6_1 * arg0->unk20;
        u32 temp_r4 = sp28 + temp_r9 * temp_r3 + arg0->unk16;
        u32 i, j;

        for (i = 0; i < arg4_1; i++) {
            if (!arg0->unk0_b0) {
                for (j = 0; j < arg3_1; j++) {
                    temp_r6[j] = (temp_r4 + j) | (temp_r7[j] << 12);
                }
            } else {
                for (j = 0; j < arg3_1; j++) {
                    temp_r6[j] = temp_r4 + j;
                }
                
            }
            temp_r4 += arg0->unk14;
            temp_r6 += arg0->unk14;
            temp_r7 += arg0->unk20;
        }
        
    }
}

void func_0800351c(struct struct_08003070 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    if (arg0->unk0_b2 < 8) {
        u16 temp = arg0->unk0_b2;

        arg0->unk22[temp] = arg1;
        arg0->unk2A[temp] = arg2;
        arg0->unk32[temp] = arg3;
        arg0->unk3A[temp] = arg4;
        func_080033a0(arg0, arg1, arg2, arg3, arg4, arg0->unk10 + arg1, arg0->unk12 + arg2);
        arg0->unk0_b2++;
        arg0->unk0_b1 = 1;
    }
}

void func_08003598(struct struct_08003070 *arg0, u16 arg1, u16 arg2) {
    arg0->unk10 = arg1;
    arg0->unk12 = arg2;
}

void func_080035a0(struct struct_08003070 *arg0, struct struct_080035a0 *arg1, u8 *arg2, u16 *arg3,
                    u8 arg4, u8 arg5, u16 arg6, u16 *arg7, u8 arg8, u8 arg9, u16 *arg10, u16 *arg11,
                    u16 arg12, u16 arg13) {
    u32 temp_r4;
    u32 i;
    u32 j;
    u16 *temp;
    
    arg0->unk0_b0 = arg1->unk0;
    temp_r4 = (!arg0->unk0_b0) ? 16 * sizeof(u16) : 32 * sizeof(u16);
    arg0->unk4 = arg1->unkC;
    arg0->unk0_b1 = 0;
    arg0->unk0_b2 = 0;
    arg0->unk8 = arg2;
    arg0->unkC = arg3;
    arg0->unk14 = arg4;
    arg0->unk15 = arg5;
    arg0->unk16 = arg6;
    arg0->unk18 = arg1->unk10;
    arg0->unk1C = &arg1->unk10[arg1->unk4 * arg1->unk8 * temp_r4];
    arg0->unk20 = arg1->unk4;
    arg0->unk21 = arg1->unk8;
    arg0->unk44 = arg7;
    arg0->unk4C = arg8;
    arg0->unk4D = arg9;
    arg0->unk58 = arg10;
    arg0->unk5C = arg11;
    arg0->unk52 = arg12;
    arg0->unk54 = arg13;

    for (i = 0; i < arg5; i++) {
        for (j = 0; j < arg4; j++) {
            (&arg7[i * arg4])[j] = (j + arg4 * i) & 0x3ff;
        }
    }
}

void func_080036c4(struct struct_08003070 *arg0, u16 arg1, u16 arg2) {
    u32 temp = arg0->unk4C + 1;
    u32 temp1 = arg0->unk4D + 1;
    
    arg0->unk10 = arg1 / 8;
    arg0->unk12 = arg2 / 8;
    arg0->unk48 = arg1;
    arg0->unk4A = arg2;
    arg0->unk4E = arg1 & 0xff;
    arg0->unk50 = arg2 & 0xff;
    func_0800351c(arg0, 0, 0, temp, temp1);
}

void func_08003720(struct struct_08003070 *arg0, u16 arg1, u16 arg2) {
    u32 temp_r8;
    u32 temp_r9;
    u32 temp_sl;
    u32 sp4;
    u32 temp_r2;
    u32 temp_r0;
    
    if ((arg0->unk48 == arg1) && (arg0->unk4A == arg2)) return;
    temp_r8 = arg1 / 8;
    temp_sl = arg2 / 8;
    temp_r2 = arg0->unk48;
    temp_r0 = arg0->unk4A;
    temp_r2 /= 8;
    temp_r9 = temp_r2;
    temp_r0 /= 8;
    sp4 = temp_r0;
    if ((temp_r8 == temp_r9) && (temp_sl == sp4)) {
        arg0->unk48 = arg1;
        arg0->unk4A = arg2;
        arg0->unk4E = arg1 & 0xff;
        arg0->unk50 = arg2 & 0xff;
        arg0->unk0_b1 = 1;
    } else {
        s32 temp_r5 = temp_r8 - temp_r9;
        s32 temp_r6 = temp_sl - sp4;
        temp_r5 = ABS(temp_r5);
        temp_r6 = ABS(temp_r6);
        
        if ((temp_r5 >= (arg0->unk4C + 1)) || (temp_r6 >= (arg0->unk4D + 1))) {
            func_080036c4(arg0, arg1, arg2);
        } else {
            u32 temp_r2;
            u32 temp_r7;
            
            arg0->unk10 = temp_r8;
            arg0->unk12 = temp_sl;
            arg0->unk48 = arg1;
            arg0->unk4A = arg2;
            arg0->unk4E = arg1 & 0xff;
            arg0->unk50 = arg2 & 0xff;
            
            if (temp_r5) {
                temp_r7 = arg0->unk4D + 1;
                
                if (temp_r8 >= temp_r9) {
                    u32 temp1 = arg0->unk4C;
                    u32 temp = temp_r5 - 1;
                    temp_r2 = temp1 - temp;
                } else {
                    temp_r2 = 0;
                }
                func_0800351c(arg0, temp_r2, 0, temp_r5, temp_r7);
            }
            if (temp_r6) {
                u32 temp1 = arg0->unk4C;
                u32 temp = temp_r5 - 1;
                u32 temp_r3 = temp1 - temp;
                u32 temp_r0;
                temp_r2 = (temp_r8 < temp_r9) ? temp_r5 : 0;
                
                if (temp_sl >= sp4) {
                    u32 temp1 = arg0->unk4D;
                    u32 temp = temp_r6 - 1;
                    temp_r0 = temp1 - temp;
                } else {
                    temp_r0 = 0;
                }
                func_0800351c(arg0, temp_r2, temp_r0, temp_r3, temp_r6);
            }
        }
    }
}


// Write Palette Table to Memory
void pal_table_write(struct PaletteTable *palTable, u16 *dest) {
    while (palTable->source != NULL) {
        dma3_set(palTable->source, dest + palTable->index * 16, palTable->total * 16 * 2, 0x20, 0x100);
        palTable++;
    }
}


// Interpolate Palette Table
u32 pal_table_start_fade(struct PaletteInterpolator *palInterps, struct PaletteTable *palTable, u32 frames, u32 fadeType, u16 *palBuffer) {
    u16 *dest, *buffer;
    u16 *sourceA, *sourceB;
    u32 i;
    sFading = TRUE;

    for (i = 0; palTable->source != NULL; palTable++, i++) {
        while (palInterps->isActive) {
            palInterps++;
        }

        dest = ((u16 *)(PaletteRAMBase)) + (palTable->index * 16);
        buffer = (palBuffer + (palTable->index * 16));

        switch (fadeType) {
            case PAL_TABLE_FADE_TO_BLACK:
                sourceA = (u16 *)palTable->source;
                pal_interp_init_ptc(palInterps, frames, palTable->total, sourceA, COLOR_BLACK, dest, buffer);
                break;

            case PAL_TABLE_FADE_FROM_BLACK:
                sourceB = (u16 *)palTable->source;
                pal_interp_init_ctp(palInterps, frames, palTable->total, COLOR_BLACK, sourceB, dest, buffer);
                break;

            case PAL_TABLE_FADE_TO_WHITE:
                sourceA = (u16 *)palTable->source;
                pal_interp_init_ptc(palInterps, frames, palTable->total, sourceA, COLOR_WHITE, dest, buffer);
                break;

            case PAL_TABLE_FADE_FROM_WHITE:
                sourceB = (u16 *)palTable->source;
                pal_interp_init_ctp(palInterps, frames, palTable->total, COLOR_WHITE, sourceB, dest, buffer);
                break;
        }

        palInterps++;
    }

    sFading = FALSE;

    return i;
}


// Create Palette Table With No Entries
void pal_table_init(struct PaletteTable *palTable) {
    palTable->source = NULL;
    palTable->total = 0;
    palTable->index = 0;
}


// Copy Palette Table
void pal_table_set_copy(struct PaletteTable *palTable, struct PaletteTable *srcTable) {
    while (srcTable->source != NULL) {
        palTable->source = srcTable->source;
        palTable->index = srcTable->index;
        palTable->total = srcTable->total;
        palTable++;
        srcTable++;
    }
    palTable->source = NULL;
    palTable->total = 0;
    palTable->index = 0;
}


// Copy Palette Table (to Specified Length)
void pal_table_set_copy_len(struct PaletteTable *palTable, struct PaletteTable *srcTable, u32 len) {
    while ((srcTable->source != NULL) && (len > 0)) {
        palTable->source = srcTable->source;
        palTable->index = srcTable->index;
        palTable->total = srcTable->total;
        palTable++;
        srcTable++;
        len--;
    }

    palTable->source = NULL;
    palTable->total = 0;
    palTable->index = 0;
}


// Create Palette Table Entry
void pal_table_set(struct PaletteTable *palTable, u16 *source, u32 index, u32 total) {
    palTable->source = source;
    palTable->index = index;
    palTable->total = total;
    palTable++;

    palTable->source = NULL;
    palTable->total = 0;
    palTable->index = 0;
}


// Append Copy of Palette Table
void pal_table_add_copy(struct PaletteTable *palTable, struct PaletteTable *srcTable) {
    while (palTable->source != NULL) {
        palTable++;
    }

    pal_table_set_copy(palTable, srcTable);
}


// Append Copy of Palette Table (to Specified Length)
void pal_table_add_copy_len(struct PaletteTable *palTable, struct PaletteTable *srcTable, u32 len) {
    while (palTable->source != NULL) {
        palTable++;
    }

    pal_table_set_copy_len(palTable, srcTable, len);
}


// Append New Palette Table
void pal_table_add(struct PaletteTable *palTable, u16 *source, u32 index, u32 total) {
    while (palTable->source != NULL) {
        palTable++;
    }

    pal_table_set(palTable, source, index, total);
}


// Store Byte to Byte Stream (Increment After)
void stream_push8(u8 **stream, u32 value) {
    u8 *s = *stream;

    *s++ = value;
    *stream = s;
}


// Store Short to Byte Stream (Increment After)
void stream_push16(u8 **stream, u32 value) {
    u8 *s = *stream;

    *s++ = value;
    *s++ = (value >> 8);
    *stream = s;
}


// Store Integer to Byte Stream (Increment After)
void stream_push32(u8 **stream, u32 value) {
    u8 *s = *stream;

    *s++ = value;
    *s++ = (value >> 8);
    *s++ = (value >> 16);
    *s++ = (value >> 24);
    *stream = s;
}


// Load Byte from Byte Stream (Decrement Before)
u32 stream_pop8(u8 **stream) {
    u8 *s = *stream;

    *stream = (s -= 1);
    return s[0];
}


// Load Short from Byte Stream (Decrement Before)
u32 stream_pop16(u8 **stream) {
    u8 *s = *stream;

    *stream = (s -= 2);
    return s[0] | (s[1] << 8);
}


// Load Integer from Byte Stream (Decrement Before)
u32 stream_pop32(u8 **stream) {
    u8 *s = *stream;

    *stream = (s -= 4);
    return s[0] | (s[1] << 8) | (s[2] << 16) | (s[3] << 24);
}


// Get Absolute Value (16 bits)
s16 math_abs16(s16 value) {
    return (value < 0) ? -value : value;
}


// Get Absolute Value (32 bits)
s32 math_abs32(s32 value) {
    return (value < 0) ? -value : value;
}


// Generate Shuffled Array of All Values from MIN to MAX
void func_08003ac4(u16 *array, u16 min, u16 max) {
    u16 range;
    s32 i;

    range = max - min;

    for (i = 0; i <= range; i++) {
        array[i] = min + i;
    }

    for (i = range; i > 0; i--) {
        s32 rand = agb_random(i + 1);
        s32 prev = array[i];

        array[i] = array[rand];
        array[rand] = prev;
    }
}
