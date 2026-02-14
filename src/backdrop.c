#include "code_08003b28.h"

asm(".include \"include/gba.inc\"");//Temporary


/* GRADIENT BACKDROP */


// VALUES
#define GRADIENT_BUFFER_SIZE (16u * 10u)

// VARIABLES
static struct {
    u32 enabled:1;
    u32 wordSize:1;
    u32 queuedWordSize:1;
    u32 hasQueuedChanges:1;
    u16 wordCount;
    u16 queuedWordCount;
    u16 *source;
    u16 *dest;
    u16 *queuedSource;
    u16 *queuedDest;
} sBackdropRenderer;
static u16 sGradientBuffer[GRADIENT_BUFFER_SIZE];
static u16 sColor1Index;
static u16 sColor2Index;
static u8 sGradientIsAllocated;
static u16 sColor1Value;
static u16 sColor2Value;
static s16 sBaseOffsetFromPaletteRAM;
static u8 sGradientStartIndex;
static u8 sGradientEndIndex;


extern u8 sFading;

// Reset Gradient Backdrop
void func_08003f28(void) {
    volatile u32 dummy;

    sBackdropRenderer.enabled = FALSE;
    sBackdropRenderer.hasQueuedChanges = FALSE;
    sGradientIsAllocated = FALSE;
}


// Flush Gradient to Palette RAM (DMA0)
void func_08003f50(void) {
    u32 controls;

    REG_DMA0CNT = 0;

    if (!sBackdropRenderer.enabled || sFading) {
        return;
    }

    REG_DMA0SAD = (u32)sBackdropRenderer.source;
    REG_DMA0DAD = (u32)sBackdropRenderer.dest;
    controls = sBackdropRenderer.wordCount | sBackdropRenderer.wordSize << 10 | DMACNT_ENABLE << 16;
    REG_DMA0CNT = controls;

    REG_DMA0SAD = (u32)sBackdropRenderer.source + (sBackdropRenderer.wordCount << (sBackdropRenderer.wordSize + 1));
    REG_DMA0DAD = (u32)sBackdropRenderer.dest;
    REG_DMA0CNT = controls | (DMACNT_START_MODE_HBLANK | DMACNT_REPEAT | DMACNT_DEST_INC_TYPE_INCREMENT_WITHOUT) << 16;
}


// Flush Gradient to Palette RAM (DMA3)
void func_08003fb4(void) {
    u32 controls;

    if (!sBackdropRenderer.enabled || sFading) {
        return;
    }

    REG_DMA3SAD = (u32)sBackdropRenderer.source;
    REG_DMA3DAD = (u32)sBackdropRenderer.dest;
    controls = sBackdropRenderer.wordCount | sBackdropRenderer.wordSize << 10 | DMACNT_ENABLE << 16;
    REG_DMA3CNT = controls;
}


// Update Gradient Backdrop
void func_08003ff0(void) {
    if (!sBackdropRenderer.hasQueuedChanges) {
        return;
    }

    sBackdropRenderer.source = sBackdropRenderer.queuedSource;
    sBackdropRenderer.dest = sBackdropRenderer.queuedDest;
    sBackdropRenderer.wordCount = sBackdropRenderer.queuedWordCount;
    sBackdropRenderer.wordSize = sBackdropRenderer.queuedWordSize;
    sBackdropRenderer.hasQueuedChanges = FALSE;
    sBackdropRenderer.enabled = TRUE;
}


// Set Buffers for Gradient Backdrop
void func_0800402c(u16 *source, u16 *dest, u32 wordCount, u32 wordSize) {
    sBackdropRenderer.queuedSource = source;
    sBackdropRenderer.queuedDest = dest;
    sBackdropRenderer.queuedWordCount = wordCount;
    sBackdropRenderer.queuedWordSize = wordSize;
    sBackdropRenderer.hasQueuedChanges = TRUE;
}


// Disable Gradient Backdrop
void func_08004058(void) {
    sBackdropRenderer.enabled = FALSE;
    sBackdropRenderer.hasQueuedChanges = FALSE;
}


// Generate Gradient (https://decomp.me/scratch/2u6Wo)
#include "asm/code_08003980/asm_08004070.s"


// Set Backdrop
void func_080041d0(u16 color1Index, u16 color2Index, u16 baseOffset) {
    sColor1Value = -1;
    sColor2Value = -1;
    sColor1Index = color1Index;
    sColor2Index = color2Index;
    sGradientStartIndex = 0;
    sGradientEndIndex = GRADIENT_BUFFER_SIZE;
    func_08004070(TRUE);
    sGradientIsAllocated = TRUE;
    func_0800402c(sGradientBuffer, ((u16 *)PaletteRAMBase) + baseOffset, 1, 0);
    sBaseOffsetFromPaletteRAM = baseOffset;
}


// Disable Gradient Backdrop
void func_08004248(void) {
    sGradientIsAllocated = FALSE;
    func_08004058();
}


// Set Gradient Bounds
void func_0800425c(u32 startIndex, u32 endIndex) {
    sGradientStartIndex = startIndex;
    sGradientEndIndex = endIndex;
}


// Get Target Base Offset
s32 func_08004270(void) {
    if (!sBackdropRenderer.enabled || !sGradientIsAllocated) {
        return -1;
    }

    return sBaseOffsetFromPaletteRAM;
}


// Update Generated Gradient
void func_080042a4(void) {
    if (!sGradientIsAllocated) {
        return;
    }

    func_08004070(FALSE);
}


// ?
void func_080042bc(s32 arg0, s32 arg1, s32 arg2, u16 *buffer, u32 shift) {
    s32 i;
    s32 r5;
    s32 r7;
    s32 r6;
    s32 value;

    for (i = 0; i < arg1 - arg2; i++) {
        buffer[i << shift] = -1;
    }

    for (i = 160u - 1; i > arg1 + arg2; i--) {
        buffer[i << shift] = -1;
    }

    r5 = arg2;
    r7 = 0;
    r6 = -(arg2 * 2) + 3;

    while (r5 >= r7) {
        value = clamp_int32(arg0 - r5, 0, 239) << 8 | clamp_int32(arg0 + r5, 0, 239);
        if (arg1 + r7 < 160u) {
            buffer[(arg1 + r7) << shift] = value;
        }
        if (arg1 - r7 < 160u) {
            buffer[(arg1 - r7) << shift] = value;
        }

        value = clamp_int32(arg0 - r7, 0, 239) << 8 | clamp_int32(arg0 + r7, 0, 239);
        if (arg1 + r5 < 160u) {
            buffer[(arg1 + r5) << shift] = value;
        }
        if (arg1 - r5 < 160u) {
            buffer[(arg1 - r5) << shift] = value;
        }

        if (r6 >= 0) {
            r5--;
            r6 -= (r5 * 4);
        }
        r7++;
        r6 += 2 + (r7 * 4);
    }
}
