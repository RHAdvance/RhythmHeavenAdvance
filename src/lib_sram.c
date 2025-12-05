#include "global.h"
#include "lib_sram.h"

asm(".include \"include/gba.inc\"");//Temporary

extern u16 verify_sram_fast_code[];    // Static Copy of verify_sram_fast_rom()
extern u16 read_sram_fast_code[];      // Static Copy of read_sram_fast_rom()
extern u32 write_int_sram_fast_code[]; // Static Copy of write_int_sram_fast_rom()

extern void (*write_int_sram_fast_rom)(const u8 *src, u8 *dest, u32 size); // ARM Function


/* SRAM Library */


// (https://decomp.me/scratch/twvo4)
#include "asm/lib_sram/asm_0804c870.s"

void write_sram_fast(const u8 *src, u8 *dest, u32 size) { // r4, r6, r5
    u32 words; // r7

    REG_WAITCNT = (REG_WAITCNT & ~WAITCNT_SRAM_MASK) | WAITCNT_SRAM_8;

    while ((u32)src & 3) {
        *dest++ = *src++;
        size--;

        if (size == 0) {
            return;
        }
    }

    words = size / 4;
    if (words != 0) {
        write_int_sram_fast(src, dest, words);
        src += (words * 4);
        dest += (words * 4);
    }

    size &= 3;
    while (size != 0) {
        *dest++ = *src++;
        size--;
    }
}

// ...
#include "asm/lib_sram/asm_0804c920.s"

// (https://decomp.me/scratch/qFu1X)
#include "asm/lib_sram/asm_0804c96c.s"

// ...
#include "asm/lib_sram/asm_0804ca40.s"
