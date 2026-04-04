#pragma once

#include "global.h"

extern void rumble_backend_init(void);
extern void rumble_backend_update(void);
extern void rumble_backend_set_state(u32 enabled);
extern void rumble_backend_serial_isr(void);
