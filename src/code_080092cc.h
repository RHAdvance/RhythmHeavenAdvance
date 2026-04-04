#pragma once

#include "global.h"
#include "lib_0804e564.h"

extern u16 D_030046b0;
extern s16 D_03004aec;
extern u16 D_03004af4;
extern s16 D_03005370;


extern void func_080092cc(void);
extern u32 func_0800931c(void);
extern s32 func_0800936c(void);
extern s32 func_08009394(void);
extern s32 func_080093a0(void);
extern s32 func_080093a4(void);
extern u32 func_080093a8(void);
extern u32 func_080093b4(void);
extern s32 func_080093c0(void);
extern void func_08009458(void);
extern void func_08009508(void);
extern void func_08009548(void);
extern void rumble_request_pulse(u32 intensity);
extern void rumble_play_menu_move(void);
extern void rumble_play_menu_confirm(void);
extern void rumble_play_menu_cancel(void);
extern void rumble_play_menu_limit(void);
extern void rumble_play_menu_error(void);
extern void rumble_play_menu_bonus(void);
extern void func_080095a8(void);
extern void func_080095c0(void);
extern void func_080095e8(u32);
extern void func_08009604(void);
extern u32 func_0800965c(void);
extern void func_08009668(u32);
extern void rumble_timer_isr(void);
extern void rumble_init(u32 timerIndex);
extern void rumble_shutdown(void);
