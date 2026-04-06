.section .text
.syntax unified

.include "include/gba.inc"

glabel entry_point
/* 080000d0 */ MOV R0, 0x12 @ Set R0 to 0x12
/* 080000d4 */ MSR CPSR_all, R0
/* 080000d8 */ LDR SP, val_000108
/* 080000dc */ MOV R0, 0x1F @ Set R0 to 0x1F
/* 080000e0 */ MSR CPSR_all, R0
/* 080000e4 */ LDR SP, val_000104

@ Set interrupt handler
/* 080000e8 */ LDR R1, =REG_INTERRUPT
/* 080000ec */ ADR R0, interrupt_handler_rom
/* 080000f0 */ STR R0, [R1] @ Save the address of the interrupt handler to REG_INTERUPT

@ Jump into main code
/* 080000f4 */ LDR R1, =flash_check @ Begin processing THUMB code
/* 080000f8 */ MOV LR, PC @ Set LR to PC
/* 080000fc */ BX R1
/* 08000100 */ B entry_point

val_000104:
/* 08000104 */ .word D_03007F00
val_000108:
/* 08000108 */ .word D_03007FA0



glabel interrupt_handler_rom
/* 0800010c */ MOV32 R3, REG_IE
/* 08000114 */ LDR R2, [R3] @ Load both REG_IE and REG_IF as one word
/* 08000118 */ AND R1, R2, R2, LSR 0x10 @ Set R1 to all interrupts that have been both registered and acknowledged

@ For a cartridge interrupt, instead of trying to handle it skip right through to the end
/* 0800011c */ ANDS R0, R1, INTERRUPT_CART
/* 08000120 */ BNE interrupt_handler_fatal

@ Iterate through all interrupts until one is found, and set R2 based on the one triggered.
/* 08000124 */ MOV R2, 0x0 @ Set R2 to 0
/* 08000128 */ ANDS R0, R1, INTERRUPT_DMA2
/* 0800012c */ BNE interrupt_handler_registered
/* 08000130 */ ADD R2, R2, 0x4 @ R2 = 0x4
/* 08000134 */ ANDS R0, R1, INTERRUPT_VBLANK
/* 08000138 */ BNE interrupt_handler_registered
/* 0800013c */ ADD R2, R2, 0x4 @ R2 = 0x8
/* 08000140 */ ANDS R0, R1, INTERRUPT_HBLANK
/* 08000144 */ BNE interrupt_handler_registered
/* 08000148 */ ADD R2, R2, 0x4 @ R2 = 0xC
/* 0800014c */ ANDS R0, R1, INTERRUPT_VCOUNT
/* 08000150 */ BNE interrupt_handler_registered
/* 08000154 */ ADD R2, R2, 0x4 @ R2 = 0x10
/* 08000158 */ ANDS R0, R1, INTERRUPT_TIMER0
/* 0800015c */ BNE interrupt_handler_registered
/* 08000160 */ ADD R2, R2, 0x4 @ R2 = 0x14
/* 08000164 */ ANDS R0, R1, INTERRUPT_TIMER1
/* 08000168 */ BNE interrupt_handler_registered
/* 0800016c */ ADD R2, R2, 0x4 @ R2 = 0x18
/* 08000170 */ ANDS R0, R1, INTERRUPT_TIMER2
/* 08000174 */ BNE interrupt_handler_registered
/* 08000178 */ ADD R2, R2, 0x4 @ R2 = 0x1C
/* 0800017c */ ANDS R0, R1, INTERRUPT_TIMER3
/* 08000180 */ BNE interrupt_handler_registered
/* 08000184 */ ADD R2, R2, 0x4 @ R2 = 0x20
/* 08000188 */ ANDS R0, R1, INTERRUPT_COMM
/* 0800018c */ BNE interrupt_handler_registered
/* 08000190 */ ADD R2, R2, 0x4 @ R2 = 0x24
/* 08000194 */ ANDS R0, R1, INTERRUPT_DMA0
/* 08000198 */ BNE interrupt_handler_registered
/* 0800019c */ ADD R2, R2, 0x4 @ R2 = 0x28
/* 080001a0 */ ANDS R0, R1, INTERRUPT_DMA1
/* 080001a4 */ BNE interrupt_handler_registered
/* 080001a8 */ ADD R2, R2, 0x4 @ R2 = 0x2C
/* 080001ac */ ANDS R0, R1, INTERRUPT_DMA3
/* 080001b0 */ BNE interrupt_handler_registered
/* 080001b4 */ ADD R2, R2, 0x4 @ R2 = 0x30
/* 080001b8 */ ANDS R0, R1, INTERRUPT_BUTTON
/* 080001bc */ BNE interrupt_handler_registered

interrupt_handler_registered:
/* 080001c0 */ STRH R0, [R3,0x2]
/* 080001c4 */ LDR R1, =interrupt_handler_jtbl
/* 080001c8 */ ADD R1, R1, R2 @ Set R1 to R1 + R2
/* 080001cc */ LDR R0, [R1] @ Jumptable based on interrupt type
/* 080001d0 */ BX R0

@ Cartridge interrupt
interrupt_handler_fatal:

 @ Disable the sound circuit
/* 080001d4 */ MOV R0, 0x0 @ Set R0 to 0
/* 080001d8 */ MOV32 R3, REG_SOUNDCNT_X
/* 080001e0 */ STRH R0, [R3]

@ Enter an infinite loop to end the program
interrupt_handler_infinite_loop:
/* 080001e4 */ B interrupt_handler_infinite_loop

.ltorg

.section .rodata

glabel interrupt_handler_jtbl_rom
/* 0804f300 */ .word midi_interrupt_dma2 @ INTERRUPT_DMA2
/* 0804f304 */ .word func_08001380 @ INTERRUPT_VBLANK
/* 0804f308 */ .word func_080091a4 @ INTERRUPT_HBLANK
/* 0804f30c */ .word func_08009268 @ INTERRUPT_VCOUNT
/* 0804f310 */ .word interrupt_default @ INTERRUPT_TIMER0
/* 0804f314 */ .word interrupt_default @ INTERRUPT_TIMER1
/* 0804f318 */ .word interrupt_default @ INTERRUPT_TIMER2
#ifdef RUMBLE
/* 0804f31c */ .word rumble_timer_isr @ INTERRUPT_TIMER3
#else
/* 0804f31c */ .word interrupt_default @ INTERRUPT_TIMER3
#endif
#ifdef RUMBLE
/* 0804f320 */ .word rumble_backend_serial_isr @ INTERRUPT_COMM
#else
/* 0804f320 */ .word interrupt_default @ INTERRUPT_COMM
#endif
/* 0804f324 */ .word interrupt_default @ INTERRUPT_DMA0
/* 0804f328 */ .word interrupt_default @ INTERRUPT_DMA1
/* 0804f32c */ .word interrupt_default @ INTERRUPT_DMA3
/* 0804f330 */ .word interrupt_default @ INTERRUPT_BUTTON
/* 0804f334 */ .word interrupt_default
@ above is dma'd

.end
