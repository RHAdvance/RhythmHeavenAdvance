#pragma once

#include <stdint.h>
#include <stdio.h>

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t    s8;
typedef int16_t  s16;
typedef int32_t  s32;

typedef enum Boolean {
    FALSE,
    TRUE
} boolean;

#define ABS(x)  ((x) < 0 ? -(x) : (x))

#define sins(x) gSineTable[((u32)(x))&0x7FF]
#define coss(x) gSineTable[(((u32)(x))+0x200)&0x7FF]

#define sins2(x) D_08935fcc[((u32)(x))&0xFF]
#define coss2(x) D_089361cc[((u32)(x))&0xFF]

#define lerp(start, end, t, total) ((start) + fast_divsi3(((end) - (start)) * (t), (total)))

// Q24.8 fixed-point types.
typedef u16 u8_8;
typedef u32 u24_8;
typedef s16 s8_8;
typedef s32 s24_8;
// Convert integer to fixed-point value.
#define INT_TO_FIXED(x) ((s32)((x) * 256))
// Convert fixed-point value to integer.
#define FIXED_TO_INT(x) ((s32)((x) >> 8))
// Multiply two fixed-point values.
#define FIXED_POINT_MUL(a, b) (((a) * (b)) >> 8)
// Divide numbers, where 'd' is always fixed-point.
#define FIXED_POINT_DIV(n, d) (((n) << 8) / (d))

#define ARRAY_COUNT(a) (s32)(sizeof(a))/sizeof((a)[0])

#define FLOAT_TO_Q8_16(x) ((int32_t)((x) * 65536.0f))

#include "gba/gba.h"
#include "types.h"
#include "sequence_data.h"
