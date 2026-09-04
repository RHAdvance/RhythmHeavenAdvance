#include "data_08936b54.h"
#include "src/code_08003b28.h"
#include "src/code_080068f8.h"
#include "src/code_08007468.h"

// ?
struct TaskMethods D_08936b84 = {
    (TaskStartFunc)func_08006bb4,
    (TaskUpdateFunc)func_08006c08,
    NULL,
    NULL
};

// ?
struct TaskMethods D_08936b94 = {
    (TaskStartFunc)func_08006ca4,
    (TaskUpdateFunc)func_08006ce8,
    NULL,
    NULL
};

// Sprite Motion - Indefinite Linear
struct TaskMethods sprite_motion_task_indefinite = {
    (TaskStartFunc)start_sprite_motion_task_indefinite,
    (TaskUpdateFunc)update_sprite_motion_task_indefinite,
    NULL,
    NULL
};

// Sprite Motion - Decelerate to Point
struct TaskMethods sprite_motion_task_decelerate = {
    (TaskStartFunc)start_sprite_motion_task_decelerate,
    (TaskUpdateFunc)update_sprite_motion_task_decelerate,
    NULL,
    NULL
};

// Sprite Motion - Accelerate to Point
struct TaskMethods sprite_motion_task_accelerate = {
    (TaskStartFunc)start_sprite_motion_task_accelerate,
    (TaskUpdateFunc)update_sprite_motion_task_accelerate,
    NULL,
    NULL
};

// Sprite Motion - LERP to Point
struct TaskMethods sprite_motion_task_lerp = {
    (TaskStartFunc)start_sprite_motion_task_lerp,
    (TaskUpdateFunc)update_sprite_motion_task_lerp,
    NULL,
    NULL
};

// Sprite Motion - Sinusoidal Oscillation
struct TaskMethods sprite_motion_task_sine_osc = {
    (TaskStartFunc)start_sprite_motion_task_sine_osc,
    (TaskUpdateFunc)update_sprite_motion_task_sine_osc,
    NULL,
    NULL
};

// Sprite Motion - Sinusoidal Velocity to Point
struct TaskMethods sprite_motion_task_sine_vel = {
    (TaskStartFunc)start_sprite_motion_task_sine_vel,
    (TaskUpdateFunc)update_sprite_motion_task_sine_vel,
    NULL,
    NULL
};

// Sprite Motion - Move Along Sine Wave
struct TaskMethods sprite_motion_task_sine_wave = {
    (TaskStartFunc)start_sprite_motion_task_sine_wave,
    (TaskUpdateFunc)update_sprite_motion_task_sine_wave,
    NULL,
    NULL
};

// Number Task - Interpolate Linearly
struct TaskMethods integer_interp_task = {
    (TaskStartFunc)start_integer_interp_task,
    (TaskUpdateFunc)update_integer_interp_task,
    NULL,
    NULL
};

// Number Task - Swap Endlessly
struct TaskMethods integer_alternator_task = {
    (TaskStartFunc)start_integer_alternator_task,
    (TaskUpdateFunc)update_integer_alternator_task,
    NULL,
    NULL
};

// Number Task - Increment Endlessly
struct TaskMethods integer_incrementer_task = {
    (TaskStartFunc)start_integer_incrementer_task,
    (TaskUpdateFunc)update_integer_incrementer_task,
    NULL,
    NULL
};

// Number Sine Interpolator Task
struct TaskMethods integer_sine_interp_task = {
    (TaskStartFunc)start_integer_sine_interp_task,
    (TaskUpdateFunc)update_integer_sine_interp_task,
    NULL,
    NULL
};

// Interpolate LCD Special Effects (Blend Controls)
struct TaskMethods lcd_blend_mode_interp_task = {
    (TaskStartFunc)start_lcd_blend_mode_interp,
    (TaskUpdateFunc)update_lcd_blend_mode_interp,
    NULL,
    NULL
};

// Fullwidth Number Characters
char D_08936c64[] = "0123456789";

// ?
struct TaskMethods D_08936c7c = {
    (TaskStartFunc)func_08008420,
    (TaskUpdateFunc)func_08008464,
    NULL,
    NULL
};

// Delayed Function Call
struct TaskMethods delayed_function_call_task = {
    (TaskStartFunc)init_scheduled_function_task,
    (TaskUpdateFunc)update_scheduled_function_task,
    NULL,
    NULL
};

// Buffered Texture Loader
struct TaskMethods D_08936c9c = {
    (TaskStartFunc)init_texture_loader_task,
    (TaskUpdateFunc)update_texture_loader_task,
    NULL,
    NULL
};
