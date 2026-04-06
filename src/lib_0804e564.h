#pragma once

#include "global.h"

// Gyro/Rumble Library

struct struct_0300443c { // Gyro Status?
    u32 unk0;
    s32 unk4;
    u32 unk8;
    s32 unkC;
    u16 unk10;
    u16 unk12;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u8 unk20;
    u8 unk21;
    u16 unk22;
};

#define REG_GPIO_DATA *(volatile u16 *)(GameROMBase + 0xc4)
#define REG_GPIO_DIR *(volatile u16 *)(GameROMBase + 0xc6)
#define REG_GPIO_CNT *(volatile u16 *)(GameROMBase + 0xc8)

extern volatile u16 D_03004438; // GPIO Data Reserve
extern volatile u16 D_0300443a; // GPIO Direction Reserve
extern struct struct_0300443c *D_0300443c; // Gyro Status
extern u8 D_03004440; // Rumble Enabled
extern u32 D_03004448[6]; // Unused?

extern s32 (*D_030064d4)(void); // Read Gyro Data Function?

extern volatile u16 *D_08bd0cc8; // GPIO Data Pointer
extern volatile u16 *D_08bd0ccc; // GPIO Direction Pointer
extern volatile u16 *D_08bd0cd0; // GPIO Control Pointer
extern u8 D_08bd0cd4[4];


extern void func_0804e564(void); // Initialise GPIO
extern s32 func_0804e598(void); // Read Gyro Data
extern void func_0804e618(u32); // Enable Rumble
extern void func_0804e640(struct struct_0300443c *); // Initialise Gyro/Rumbl
extern void func_0804e690(u32);
extern void func_0804e6c4(u32);
extern void func_0804e6e4(void);
extern void func_0804e77c(void);
extern u32 func_0804e834(void);
extern u32 func_0804e870(u32 *);
extern void func_0804e8bc(s32 *);
extern void func_0804e8cc(u32);
extern void func_0804e8f8(u32); // Toggle Rumble
extern void func_0804e914(u32); // Turn off current Rumble, toggle Rumble
extern u32 func_0804e92c(void);

// ARM 
extern volatile s32 func_0804e938(volatile u16 *);
