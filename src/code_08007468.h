#pragma once

#include "global.h"
#include "graphics.h"
#include "sound.h"
#include "data/data_08936b54.h"
#include "src/bitmap_font.h"
#include "src/graphics_table.h"

struct unk_struct_08008b00 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    s32 unkC;
};

extern s32 (*math_sqrt)(s32);

/* GRAPHICS UTIL */
extern void get_sprite_xy(s16 sprite, s16 *xReq, s16 *yReq);
extern void assign_sprite_affine_param(s16 sprite, s8 affineIndex);
extern void set_affine_scale_rotation(s8 affineParam, s16 scale, s16 rotation);
extern void set_affine_stretch_rotation(s8 affineParam, s16 xScale, s16 yScale, s16 rotation);
extern struct SpriteMover_Indefinite *start_sprite_motion_task_indefinite(struct SpriteMover_Indefinite_Inputs *inputs);
extern u32 update_sprite_motion_task_indefinite(struct SpriteMover_Indefinite *task);
extern struct SpriteMover_Decelerate *start_sprite_motion_task_decelerate(struct SpriteMover_Decelerate_Inputs *inputs);
extern u32 update_sprite_motion_task_decelerate(struct SpriteMover_Decelerate *task);
extern struct SpriteMover_Accelerate *start_sprite_motion_task_accelerate(struct SpriteMover_Accelerate_Inputs *inputs);
extern u32 update_sprite_motion_task_accelerate(struct SpriteMover_Accelerate *task);
extern struct SpriteMover_TimedLinear *start_sprite_motion_task_lerp(struct SpriteMover_TimedLinear_Inputs *inputs);
extern u32 update_sprite_motion_task_lerp(struct SpriteMover_TimedLinear *task);
extern u32 update_sprite_motion_task_sine_osc(struct SpriteMover_SineOsc *task);
extern struct SpriteMover_SineOsc *start_sprite_motion_task_sine_osc(struct SpriteMover_SineOsc_Inputs *inputs);
extern u32 update_sprite_motion_task_sine_vel(struct SpriteMover_SineVel *task);
extern struct SpriteMover_SineVel *start_sprite_motion_task_sine_vel(struct SpriteMover_SineVel_Inputs *inputs);
extern u32 update_sprite_motion_task_sine_wave(struct SpriteMover_SineWave *task);
extern struct SpriteMover_SineWave *start_sprite_motion_task_sine_wave(struct SpriteMover_SineWave_Inputs *inputs);
extern void delete_bmp_font_obj_text_anim(struct BitmapFontOBJ *bmpFontOBJ, s16 sprite);
extern void delete_bmp_font_obj_text_sprite(struct BitmapFontOBJ *bmpFontOBJ, s16 sprite);

/* FAST DIVISION */
extern void init_fast_udivsi3(void);
extern s32 fast_divsi3(s32 dividend, s32 divisor);

/* INTERPOLATION */
extern struct NumberInterpolator *start_integer_interp_task(struct NumberInterpolator *inputs);
extern u32 update_integer_interp_task(struct NumberInterpolator *task);
extern struct NumberInterpolator *start_integer_alternator_task(struct NumberInterpolator *inputs);
extern u32 update_integer_alternator_task(struct NumberInterpolator *task);
extern struct NumberInterpolator *start_integer_incrementer_task(struct NumberInterpolator *inputs);
extern u32 update_integer_incrementer_task(struct NumberInterpolator *task);
extern void set_target_for_integer_task(s32 taskID, s32 newTarget);
extern struct NumberSineInterpolator *start_integer_sine_interp_task(struct NumberSineInterpolator *inputs);
extern u32 update_integer_sine_interp_task(struct NumberSineInterpolator *task);
extern struct BlendControlsInterpolator *start_lcd_blend_mode_interp(struct BlendControlsInterpolator *inputs);
extern u32 update_lcd_blend_mode_interp(struct BlendControlsInterpolator *task);
extern s32 interp_lcd_blend_mode(u16 memID, u32 blendControls, u32 duration, u32 flip);
extern void interp_screen_window_size(u16 memID, u32 window, u32 duration,
                                        s32 initialX1, s32 initialY1, s32 initialX2, s32 initialY2,
                                        s32 targetX1, s32 targetY1, s32 targetX2, s32 targetY2);

/* STRING */
extern char *strncpy(char *s1, const char *s2, u32 len);
extern char *strcat(char *s1, const char *s2);
extern char *strncat(char *s1, const char *s2, u32 len);
extern s32 strncmp(const char *s1, const char *s2, u32 len);
extern void strint(char *s, u32 n);
extern void strnint(char *s, u32 n, u32 len);
extern void strintf(char *s, u32 n);
extern void strnintf(char *s, u32 n, u32 len);

/* ? */
// extern ? func_08008370(?);
extern struct unk_struct_08008420 *func_08008420(struct unk_struct_08008420_init *inputs);
extern u32 func_08008464(struct unk_struct_08008420 *task);

/* SCHEDULED FUNCTION CALL */
extern struct ScheduledFunctionTask *init_scheduled_function_task(struct ScheduledFunctionTask *inputs);
extern u32 update_scheduled_function_task(struct ScheduledFunctionTask *task);
extern s32 schedule_function_call(u16 memID, void *function, s32 param, u32 delay);

/* BUFFERED TEXTURE */
extern u32 decompress_gfx_init(struct CompressedGFX *gfx, u32 size, u32 limit, struct GFXDecompressProgress *progress);
extern u32 decompress_gfx_resume(struct GFXDecompressProgress *progress);
// extern ? func_08008608(?);
// extern ? func_0800861c(?);
// extern ? func_08008628(?);
// extern ? func_08008658(?);
// extern ? func_0800869c(?);
// extern ? func_080086c4(?);
// extern ? func_08008720(?);
extern struct TextureLoader *init_texture_loader_task(struct TextureLoaderInputs *inputs);
extern u32 update_texture_loader_task(struct TextureLoader *task);
extern u32 start_new_texture_loader(u16 memID, struct CompressedData **textureList);

/* ? */
extern s32 clamp_int32(s32 var, s32 min, s32 max); // Signed Clamp
// extern ? func_080087e8(?);
// extern ? func_08008910(?);
// extern ? func_08008938(?);
// extern ? func_08008968(?);
// extern ? func_08008990(?);
// extern ? func_080089c0(?);
// extern ? func_08008a70(?);
// extern ? func_08008ab8(?);
extern void func_08008b00(u32 unused_arg0, u32 unused_arg1, s16 arg2, s24_8 arg3, s24_8 arg4, s16 arg5, s24_8 arg6, s24_8 arg7, u16 arg8, struct unk_struct_08008b00 *arg9, u32 arg10, u32 arg11);
extern void func_08008d44(u32 unused_arg0, u32 unused_arg1, s16 arg2, s24_8 arg3, s24_8 arg4, s16 arg5, s24_8 arg6, s24_8 arg7, u16 arg8, struct unk_struct_08008b00 *arg9, u32 arg10);
extern void func_08008d88(u32 unused_arg0, u32 unused_arg1, s16 arg2, s24_8 arg3, s24_8 arg4, s16 arg5, s24_8 arg6, s24_8 arg7, u16 arg8, struct unk_struct_08008b00 *arg9, u32 arg10);

s32 snprintf(char *s, s32 n, const char *fmt, ...);
