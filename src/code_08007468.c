#include "global.h"
#include "src/code_08007468.h"
#include "src/code_08003b28.h"
#include "src/bitmap_font.h"
#include "src/memory_heap.h"
#include "src/lib_0804ca80.h"

// Can be better split

asm(".include \"include/gba.inc\"");//Temporary


/* GRAPHICS UTIL */


// Get Sprite XY
void get_sprite_xy(s16 sprite, s16 *xReq, s16 *yReq) {
    *xReq = sprite_get_data(gSpriteHandler, sprite, 4);
    *yReq = sprite_get_data(gSpriteHandler, sprite, 5);
}


// Set Sprite Affine Param.
void assign_sprite_affine_param(s16 sprite, s8 affineIndex) {
    sprite_set_affine_params(gSpriteHandler, sprite, affineIndex, func_08002520(affineIndex));
}


// Set Affine Parameters
void set_affine_scale_rotation(s8 affineParam, s16 scale, s16 rotation) {
    func_0800232c(affineParam, scale, scale, -rotation, 1);
}


// Set Affine Parameters
void set_affine_stretch_rotation(s8 affineParam, s16 xScale, s16 yScale, s16 rotation) {
    func_0800232c(affineParam, xScale, yScale, -rotation, 1);
}


// Sprite Motion - Indefinite Linear (Start)
struct SpriteMover_Indefinite *start_sprite_motion_task_indefinite(struct SpriteMover_Indefinite_Inputs *inputs) {
    struct SpriteMover_Indefinite *task;

    if (inputs->sprite < 0) {
        return TASK_FAILED_TO_START;
    }

    task = mem_heap_alloc(sizeof(struct SpriteMover_Indefinite));
    task->sprite = inputs->sprite;
    task->posX = INT_TO_FIXED(inputs->startX);
    task->posY = INT_TO_FIXED(inputs->startY);
    task->velX = inputs->velX;
    task->velY = inputs->velY;

    sprite_set_x_y(gSpriteHandler, inputs->sprite, inputs->startX, inputs->startY);
    return task;
}


// Sprite Motion - Indefinite Linear (Update)
u32 update_sprite_motion_task_indefinite(struct SpriteMover_Indefinite *task) {
    task->posX += task->velX;
    task->posY += task->velY;

    sprite_set_x_y(gSpriteHandler, task->sprite, FIXED_TO_INT(task->posX), FIXED_TO_INT(task->posY));
    return FALSE;
}


// Sprite Motion - Decelerate to Point (Start)
struct SpriteMover_Decelerate *start_sprite_motion_task_decelerate(struct SpriteMover_Decelerate_Inputs *inputs) {
    struct SpriteMover_Decelerate *task;

    if (inputs->sprite < 0) {
        return TASK_FAILED_TO_START;
    }

    task = mem_heap_alloc(sizeof(struct SpriteMover_Decelerate));
    task->sprite = inputs->sprite;
    task->destX = inputs->destX;
    task->destY = inputs->destY;
    task->dx = INT_TO_FIXED(inputs->startX - inputs->destX);
    task->dy = INT_TO_FIXED(inputs->startY - inputs->destY);
    task->multiplier = inputs->multiplier;

    sprite_set_x_y(gSpriteHandler, inputs->sprite, inputs->startX, inputs->startY);
    return task;
}


// Sprite Motion - Decelerate to Point (Update)
u32 update_sprite_motion_task_decelerate(struct SpriteMover_Decelerate *task) {
    s32 dx = task->dx;
    s32 dy = task->dy;

    dx = ABS(dx);
    dy = ABS(dy);

    dx = FIXED_POINT_MUL(dx, task->multiplier);
    dy = FIXED_POINT_MUL(dy, task->multiplier);

    if (dx < INT_TO_FIXED(1.0)) dx = 0;
    if (dy < INT_TO_FIXED(1.0)) dy = 0;

    if (task->dx < 0) dx = -dx;
    if (task->dy < 0) dy = -dy;

    task->dx = dx;
    task->dy = dy;

    sprite_set_x_y(gSpriteHandler, task->sprite, FIXED_TO_INT(dx) + task->destX, FIXED_TO_INT(dy) + task->destY);

    if ((dx | dy) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Sprite Motion - Accelerate to Point (Start)
struct SpriteMover_Accelerate *start_sprite_motion_task_accelerate(struct SpriteMover_Accelerate_Inputs *inputs) {
    struct SpriteMover_Accelerate *task;

    if (inputs->sprite < 0) {
        return TASK_FAILED_TO_START;
    }

    task = mem_heap_alloc(sizeof(struct SpriteMover_Accelerate));
    task->sprite = inputs->sprite;
    task->startX = inputs->startX;
    task->startY = inputs->startY;
    task->dx = inputs->destX - inputs->startX;
    task->dy = inputs->destY - inputs->startY;
    task->distanceTravelled = 0;
    task->totalDistance = INT_TO_FIXED(math_sqrt(task->dx * task->dx + task->dy * task->dy));
    task->velocity = inputs->velocity;
    task->acceleration = inputs->acceleration;

    sprite_set_x_y(gSpriteHandler, inputs->sprite, inputs->startX, inputs->startY);
    return task;
}


// Sprite Motion - Accelerate to Point (Update)
u32 update_sprite_motion_task_accelerate(struct SpriteMover_Accelerate *task) {
    s24_8 distTravelled, totalDist;
    u32 reachedEnd;
    s16 x, y;

    task->distanceTravelled += task->velocity;
    task->velocity += task->acceleration;

    if (task->velocity < 0 && task->acceleration < 0) {
        return TRUE;
    }

    distTravelled = task->distanceTravelled;
    totalDist = task->totalDistance;
    reachedEnd = FALSE;

    if (distTravelled >= totalDist) {
        distTravelled = totalDist;
        reachedEnd = TRUE;
    }

    if (reachedEnd) {
        x = task->startX + task->dx;
        y = task->startY + task->dy;
    } else {
        x = task->startX + lerp(0, task->dx, distTravelled, totalDist);
        y = task->startY + lerp(0, task->dy, distTravelled, totalDist);
    }

    sprite_set_x_y(gSpriteHandler, task->sprite, x, y);
    return reachedEnd;
}


// Sprite Motion - LERP to Point (Start)
struct SpriteMover_TimedLinear *start_sprite_motion_task_lerp(struct SpriteMover_TimedLinear_Inputs *inputs) {
    struct SpriteMover_TimedLinear *task;

    if (inputs->sprite < 0) {
        return TASK_FAILED_TO_START;
    }

    task = mem_heap_alloc(sizeof(struct SpriteMover_TimedLinear));
    task->sprite = inputs->sprite;
    task->startX = inputs->startX;
    task->startY = inputs->startY;
    task->dx = inputs->destX - inputs->startX;
    task->dy = inputs->destY - inputs->startY;
    task->totalFrames = inputs->totalFrames;
    task->framesPassed = 0;

    sprite_set_x_y(gSpriteHandler, inputs->sprite, inputs->startX, inputs->startY);
    return task;
}


// Sprite Motion - LERP to Point (Update)
u32 update_sprite_motion_task_lerp(struct SpriteMover_TimedLinear *task) {
    s32 totalFrames = task->totalFrames;
    u32 reachedEnd = (++task->framesPassed >= totalFrames);
    s32 framesPassed = task->framesPassed;
    s16 x = task->startX + lerp(0, task->dx, framesPassed, totalFrames);
    s16 y = task->startY + lerp(0, task->dy, framesPassed, totalFrames);

    sprite_set_x_y(gSpriteHandler, task->sprite, x, y);
    return reachedEnd;
}


// Sprite Motion - Sinusoidal Oscillation (Update)
u32 update_sprite_motion_task_sine_osc(struct SpriteMover_SineOsc *task) {
    u8 wavePos = lerp(task->waveStart, task->waveEnd, task->framesPassed, task->totalFrames);

    s32 offset = task->baseOffset + FIXED_TO_INT(task->amplitude * sins2(wavePos));
    
    u16 xPos = FIXED_TO_INT(offset * coss2(task->angle)) + task->baseXPos;
    u16 yPos = FIXED_TO_INT(offset * sins2(task->angle)) + task->baseYPos;

    sprite_set_x_y(gSpriteHandler, task->sprite, xPos, yPos);

    return (++task->framesPassed > task->totalFrames);
}


// Sprite Motion - Sinusoidal Oscillation (Start)
struct SpriteMover_SineOsc *start_sprite_motion_task_sine_osc(struct SpriteMover_SineOsc_Inputs *inputs) {
    struct SpriteMover_SineOsc *task;

    if (inputs->sprite < 0) {
        return TASK_FAILED_TO_START;
    }

    task = mem_heap_alloc(sizeof(struct SpriteMover_SineOsc));
    task->sprite = inputs->sprite;
    task->baseXPos = inputs->baseX;
    task->baseYPos = inputs->baseY;
    task->baseOffset = inputs->baseOffset;
    task->amplitude = inputs->amplitude;
    task->waveStart = inputs->waveStart;
    task->waveEnd = inputs->waveEnd;
    task->framesPassed = 0;
    task->totalFrames = inputs->totalFrames;
    task->angle = inputs->angle;

    update_sprite_motion_task_sine_osc(task);
    return task;
}


// Sprite Motion - Sinusoidal Velocity to Point (Update)
u32 update_sprite_motion_task_sine_vel(struct SpriteMover_SineVel *task) {
    s32 temp_r5 = lerp(task->unkA, task->unkC, task->framesPassed, task->totalFrames);

    u16 xPos = task->startXPos + FIXED_TO_INT(task->dx * func_080019a4(temp_r5));
    u16 yPos = task->startYPos + FIXED_TO_INT(task->dy * func_080019a4(temp_r5));

    sprite_set_x_y(gSpriteHandler, task->sprite, xPos, yPos);

    return (++task->framesPassed > task->totalFrames);
}


// Sprite Motion - Sinusoidal Velocity to Point (Start)
struct SpriteMover_SineVel *start_sprite_motion_task_sine_vel(struct SpriteMover_SineVel_Inputs *inputs) {
    struct SpriteMover_SineVel *task;

    if (inputs->sprite < 0) {
        return TASK_FAILED_TO_START;
    }

    task = mem_heap_alloc(sizeof(struct SpriteMover_SineVel));
    task->sprite = inputs->sprite;
    task->startXPos = inputs->startX;
    task->startYPos = inputs->startY;
    task->dx = inputs->destX - inputs->startX;
    task->dy = inputs->destY - inputs->startY;
    task->unkA = inputs->unkA * 16;
    task->unkC = inputs->unkC * 16;
    task->framesPassed = 0;
    task->totalFrames = inputs->totalFrames;

    update_sprite_motion_task_sine_vel(task);
    return task;
}


// Sprite Motion - Move Along Sine Wave (Update)
u32 update_sprite_motion_task_sine_wave(struct SpriteMover_SineWave *task) {
    s32 totalFrames = task->totalFrames;
    u32 reachedEnd = (++task->framesPassed >= totalFrames);
    s32 framesPassed = task->framesPassed;
    // Lerp from 0 to pi in terms of sine angle
    s32 temp_r8 = lerp(0, 0x800, framesPassed, totalFrames);

    s16 x = task->startX + lerp(0, task->dx, framesPassed, totalFrames);
    s16 y = task->startY + lerp(0, task->dy, framesPassed, totalFrames) - FIXED_TO_INT(func_080019a4(temp_r8) * task->amplitude);

    sprite_set_x_y(gSpriteHandler, task->sprite, x, y);
    return reachedEnd;
}


// Sprite Motion - Move Along Sine Wave (Start)
struct SpriteMover_SineWave *start_sprite_motion_task_sine_wave(struct SpriteMover_SineWave_Inputs *inputs) {
    struct SpriteMover_SineWave *task;

    if (inputs->sprite < 0) {
        return TASK_FAILED_TO_START;
    }

    task = mem_heap_alloc(sizeof(struct SpriteMover_SineWave));
    task->sprite = inputs->sprite;
    task->startX = inputs->startX;
    task->startY = inputs->startY;
    task->dx = inputs->destX - inputs->startX;
    task->dy = inputs->destY - inputs->startY;
    task->amplitude = inputs->amplitude;
    task->framesPassed = 0;
    task->totalFrames = inputs->totalFrames;

    sprite_set_x_y(gSpriteHandler, task->sprite, task->startX, task->startY);
    return task;
}


// Delete Text Generated by BitmapFontOBJ
void delete_bmp_font_obj_text_anim(struct BitmapFontOBJ *bmpFontOBJ, s16 sprite) {
    if (sprite < 0) {
        return;
    }

    bmp_font_obj_delete_printed_anim(bmpFontOBJ, (struct Animation *)sprite_get_data(gSpriteHandler, sprite, 7));
}


// Delete Text and Sprite Generated by BitmapFontOBJ
void delete_bmp_font_obj_text_sprite(struct BitmapFontOBJ *bmpFontOBJ, s16 sprite) {
    delete_bmp_font_obj_text_anim(bmpFontOBJ, sprite);
    sprite_delete(gSpriteHandler, sprite);
}


/* FAST DIVISION */


#define FAST_UDIVSI3_SIZE ((u32)&fast_udivsi3_rom_end - (u32)fast_udivsi3_rom)

extern u32 fast_udivsi3_rom();
extern void *fast_udivsi3_rom_end;
extern u32 (*fast_udivsi3)(u32 dividend, u32 divisor);

static s32 fast_udivsi3_code[136];


// Init.
void init_fast_udivsi3(void) {
    DmaCopy32(3, fast_udivsi3_rom, fast_udivsi3_code, FAST_UDIVSI3_SIZE);
    fast_udivsi3 = (void *)fast_udivsi3_code;
}


// Divides two signed integers using a fast algorithm contained in IWRAM.
// Much quicker than the versions contained in libc and libagbsyscall.
s32 fast_divsi3(s32 dividend, s32 divisor) {
    u32 quotient;
    u32 isNegative = FALSE;

    if (dividend & 0x80000000) {
        dividend = -dividend;
        isNegative = TRUE;
    }

    if (divisor & 0x80000000) {
        divisor = -divisor;
        isNegative ^= TRUE;
    }

    quotient = fast_udivsi3(dividend, divisor);
    return isNegative ? -quotient : quotient;
}


/* INTERPOLATION */


// Initialise Number Linear Interpolator Task
struct NumberInterpolator *start_integer_interp_task(struct NumberInterpolator *inputs) {
    struct NumberInterpolator *task;

    task = mem_heap_alloc(sizeof(struct NumberInterpolator));
    task->type = inputs->type;
    task->duration = inputs->duration;
    task->runningTime = 0;
    task->source = inputs->source;
    task->initial = inputs->initial;
    task->target = inputs->target;

    switch (task->type) {
        case 0:
            *(u8 *)task->source = task->initial;
            break;
        case 1:
            *(u16 *)task->source = task->initial;
            break;
        case 2:
            *(u32 *)task->source = task->initial;
            break;
    }

    return task;
}


// Update Number Linear Interpolator Task
u32 update_integer_interp_task(struct NumberInterpolator *task) {
    s32 current = task->initial + fast_divsi3((task->target - task->initial) * task->runningTime, task->duration);

    switch (task->type) {
        case 0:
            *(u8 *)task->source = current;
            break;
        case 1:
            *(u16 *)task->source = current;
            break;
        case 2:
            *(u32 *)task->source = current;
            break;
    }

    return (++task->runningTime > task->duration);
}


// Initialise Number Alternator Task
struct NumberInterpolator *start_integer_alternator_task(struct NumberInterpolator *inputs) {
    struct NumberInterpolator *task;

    task = mem_heap_alloc(sizeof(struct NumberInterpolator));
    task->type = inputs->type;
    task->duration = inputs->duration;
    task->runningTime = 0;
    task->source = inputs->source;
    task->initial = inputs->initial;
    task->target = inputs->target;

    switch (task->type) {
        case 0:
            *(u8 *)task->source = task->initial;
            break;
        case 1:
            *(u16 *)task->source = task->initial;
            break;
        case 2:
            *(u32 *)task->source = task->initial;
            break;
    }

    return task;
}


// Update Number Alternator Task
u32 update_integer_alternator_task(struct NumberInterpolator *task) {
    s32 newInitial, newTarget;

    if (++task->runningTime >= task->duration) {
        task->runningTime = 0;
        newInitial = task->target;
        newTarget = task->initial;
        task->target = newTarget;
        task->initial = newInitial;

        switch (task->type) {
            case 0:
                *(u8 *)task->source = newInitial;
                break;
            case 1:
                *(u16 *)task->source = newInitial;
                break;
            case 2:
                *(u32 *)task->source = newInitial;
                break;
        }
    }

    return FALSE;
}


// Initialise Number Incrementer Task
struct NumberInterpolator *start_integer_incrementer_task(struct NumberInterpolator *inputs) {
    struct NumberInterpolator *task;

    task = mem_heap_alloc(sizeof(struct NumberInterpolator));
    task->type = inputs->type;
    task->duration = inputs->duration;
    task->runningTime = 0;
    task->source = inputs->source;
    task->initial = inputs->initial;
    task->target = inputs->target;

    switch (task->type) {
        case 0:
            *(u8 *)task->source = task->initial;
            break;
        case 1:
            *(u16 *)task->source = task->initial;
            break;
        case 2:
            *(u32 *)task->source = task->initial;
            break;
    }

    return task;
}


// Update Number Incrementer Task
u32 update_integer_incrementer_task(struct NumberInterpolator *task) {
    s32 current;

    if (++task->runningTime >= task->duration) {
        task->runningTime = 0;
        current = task->initial + task->target;
        task->initial = current;

        switch (task->type) {
            case 0:
                *(u8 *)task->source = current;
                break;
            case 1:
                *(u16 *)task->source = current;
                break;
            case 2:
                *(u32 *)task->source = current;
                break;
        }
    }

    return FALSE;
}


// Set Target Value for Number Task
void set_target_for_integer_task(s32 taskID, s32 newTarget) {
    struct NumberInterpolator *task = get_task_info(taskID);

    if (task != NULL) {
        task->target = newTarget;
    }
}


// Initialise Number Sine Interpolator Task
struct NumberSineInterpolator *start_integer_sine_interp_task(struct NumberSineInterpolator *inputs) {
    struct NumberSineInterpolator *task;
    s32 current;

    task = mem_heap_alloc(sizeof(struct NumberSineInterpolator));
    task->type = inputs->type;
    task->angle = inputs->angle;
    task->speed = inputs->speed;
    task->value = inputs->value;
    task->source = inputs->source;

    current = FIXED_POINT_MUL(sins(FIXED_TO_INT(task->angle)), task->value);

    switch (task->type) {
        case 0:
            *(u8 *)task->source = current;
            break;
        case 1:
            *(u16 *)task->source = current;
            break;
        case 2:
            *(u32 *)task->source = current;
            break;
    }

    return task;
}


// Update Number Sine Interpolator Task
u32 update_integer_sine_interp_task(struct NumberSineInterpolator *task) {
    s32 current;

    task->angle += task->speed;
    current = FIXED_POINT_MUL(sins(FIXED_TO_INT(task->angle)), task->value);

    switch (task->type) {
        case 0:
            *(u8 *)task->source = current;
            break;
        case 1:
            *(u16 *)task->source = current;
            break;
        case 2:
            *(u32 *)task->source = current;
            break;
    }

    return FALSE;
}


// Initialise LCD Special Effects Interpolator
struct BlendControlsInterpolator *start_lcd_blend_mode_interp(struct BlendControlsInterpolator *inputs) {
    struct BlendControlsInterpolator *task;
    u32 tgtLevel, srcLevel;

    task = mem_heap_alloc(sizeof(struct BlendControlsInterpolator));
    task->blendControls = inputs->blendControls;
    task->duration = inputs->duration;
    task->runningTime = 0;
    task->flip = inputs->flip;

    tgtLevel = 0x10 * (inputs->flip != 0);
    srcLevel = 0x10 - tgtLevel;
    switch (task->blendControls & BLDMOD_BLEND_MODE_MASK) {
        case (BLEND_MODE_OFF * 0x40):
        case (BLEND_MODE_ALPHA * 0x40):
            D_03004b10.COLEV = (srcLevel | (tgtLevel << 8));
            break;

        case (BLEND_MODE_LIGHTEN * 0x40):
        case (BLEND_MODE_DARKEN * 0x40):
            D_03004b10.COLEY = tgtLevel;
            break;
    }

    D_03004b10.BLDMOD = task->blendControls;
    return task;
}


// Update LCD Special Effects Interpolator
u32 update_lcd_blend_mode_interp(struct BlendControlsInterpolator *task) {
    u32 tgtLevel, srcLevel;

    task->runningTime++;
    tgtLevel = Div(task->runningTime * 0x10, task->duration);

    if (task->flip) {
        srcLevel = tgtLevel;
        tgtLevel = 0x10 - tgtLevel;
    } else {
        srcLevel = 0x10 - tgtLevel;
    }

    switch (task->blendControls & BLDMOD_BLEND_MODE_MASK) {
        case (BLEND_MODE_OFF * 0x40):
        case (BLEND_MODE_ALPHA * 0x40):
            D_03004b10.COLEV = (srcLevel | (tgtLevel << 8));
            break;

        case (BLEND_MODE_LIGHTEN * 0x40):
        case (BLEND_MODE_DARKEN * 0x40):
            D_03004b10.COLEY = tgtLevel;
            break;
    }

    if (task->runningTime < task->duration) {
        return FALSE;
    } else {
        return TRUE;
    }
}


// Interpolate LCD Special Effects
s32 interp_lcd_blend_mode(u16 memID, u32 blendControls, u32 duration, u32 flip) {
    struct BlendControlsInterpolator inputs;

    inputs.blendControls = blendControls;
    inputs.duration = duration;
    inputs.flip = flip;

    return start_new_task(memID, &lcd_blend_mode_interp_task, &inputs, NULL, 0);
}


// Interpolate Window Size
void interp_screen_window_size(u16 memID, u32 window, u32 duration,
                                s32 initialX1, s32 initialY1, s32 initialX2, s32 initialY2,
                                s32 targetX1, s32 targetY1, s32 targetX2, s32 targetY2) {
    struct NumberInterpolator inputs;
    void *windowLeftEdge;
    void *windowRightEdge;
    void *windowTopEdge;
    void *windowBottomEdge;

    inputs.type = 0;
    inputs.duration = duration;

    windowRightEdge = (window != 0) ? &D_03004b10.WIN1H : &D_03004b10.WIN0H;
    windowBottomEdge = (window != 0) ? &D_03004b10.WIN1V : &D_03004b10.WIN0V;
    windowLeftEdge = windowRightEdge + 1;
    windowTopEdge = windowBottomEdge + 1;

    inputs.source = windowLeftEdge;
    inputs.initial = initialX1;
    inputs.target = targetX1;
    start_new_task(memID, &integer_interp_task, &inputs, NULL, 0);

    inputs.source = windowTopEdge;
    inputs.initial = initialY1;
    inputs.target = targetY1;
    start_new_task(memID, &integer_interp_task, &inputs, NULL, 0);

    inputs.source = windowRightEdge;
    inputs.initial = initialX2;
    inputs.target = targetX2;
    start_new_task(memID, &integer_interp_task, &inputs, NULL, 0);

    inputs.source = windowBottomEdge;
    inputs.initial = initialY2;
    inputs.target = targetY2;
    start_new_task(memID, &integer_interp_task, &inputs, NULL, 0);

    D_03004b10.DISPCNT |= DISPCNT_ENABLE_WINDOW(window);
}


/* STRING */


extern char D_08936c64[]; // "?申O?申P?申Q?申R?申S?申T?申U?申V?申W?申X"


// Copy Substring
char *strncpy(char *s1, const char *s2, u32 len) {
    char *s = s1;
    u32 i;

    for (i = 0; (*s2 != '\0') && (i < len); i++) {
        *s1++ = *s2++;
    }

    return s;
}


// Concatenate String
char *strcat(char *s1, const char *s2) {
    char *s = s1;

    while (*s1 != '\0') {
        s1++;
    }

    while (*s2 != '\0') {
        *s1++ = *s2++;
    }

    *s1 = '\0';
    return s;
}


// Concatenate Substring
char *strncat(char *s1, const char *s2, u32 len) {
    char *s = s1;
    u32 i;

    while (*s1 != '\0') {
        s1++;
    }

    for (i = 0; (*s2 != '\0') && (i < len); i++) {
        *s1++ = *s2++;
    }

    *s1 = '\0';

    return s;
}


// Compare Strings
s32 strncmp(const char *s1, const char *s2, u32 len) {
    u32 i;

    for (i = 0; ((*s1 != '\0') || (*s2 != '\0')) && (i < len); i++) {
        if (*s1 != *s2) {
            return (*s1 > *s2) ? 1 : -1;
        }

        s1++;
        s2++;
    }

    return 0;
}


// Integer to String (Halfwidth)
void strint(char *s, u32 n) {
    u32 len = 1;
    u32 d, i;

    for (d = 10; d <= n; d *= 10) {
        len++;
    }

    s += len;
    *s = '\0';

    for (i = 0; i < len; i++) {
        *(--s) = '0' + (n % 10);
        n /= 10;
    }
}


// Integer to String (Halfwidth)
void strnint(char *s, u32 n, u32 len) {
    u32 i;

    s += len;
    *s = '\0';

    for (i = 0; i < len; i++) {
        *(--s) = '0' + (n % 10);
        n /= 10;
    }
}


// Integer to String (Fullwidth)
void strintf(char *s, u32 n) {
    u32 len = 1;
    u32 d, i;

    for (d = n; d > 9; d /= 10) {
        len++;
    }

    s += (len * 2);
    *s = '\0';

    for (i = 0; i < len; i++) {
        char *c = &D_08936c64[(n % 10) * 2];

        s -= 2;
        s[0] = c[0];
        s[1] = c[1];
        n /= 10;
    }
}


// Integer to String (Fullwidth)
void strnintf(char *s, u32 n, u32 len) {
    u32 i;

    s += (len * 2);
    *s = '\0';

    for (i = 0; i < len; i++) {
        char *c = &D_08936c64[(n % 10) * 2];

        s -= 2;
        s[0] = c[0];
        s[1] = c[1];
        n /= 10;
    }
}


/* ? */


void func_08008370(u32 *arg0, u32 *arg1, u32 arg2, u32 arg3) {
    u32 temp_r1;
    u32 temp;
    u32 temp_r6;
    u32 temp_r7;
    u32 temp_ip;
    u32 i;
    
    temp_ip = (arg2 + 3) >> 2;
    arg0 += temp_ip;
    arg1 += temp_ip * 2;
    temp_r6 = 0x33333333; // constant 1100 bit pattern
    temp_r1 = (arg3 << 0) | (arg3 << 4) | (arg3 << 8) | (arg3 << 0xc); // initial pattern
    temp_r1 |= (temp_r1 << 0x10); // copy into high bytes
    temp_r7 = (arg2 + 3) >> 4;
    for (i = 0; i < temp_r7; i++) {
        arg0 -= 4;
        arg1 -= 4 * 2;

        temp = arg0[3];
        arg1[6] = (temp & temp_r6) + temp_r1;
        arg1[7] = ((temp >> 2) & temp_r6) + temp_r1;
        temp = arg0[2];
        arg1[4] = (temp & temp_r6) + temp_r1;
        arg1[5] = ((temp >> 2) & temp_r6) + temp_r1;
        temp = arg0[1];
        arg1[2] = (temp & temp_r6) + temp_r1;
        arg1[3] = ((temp >> 2) & temp_r6) + temp_r1;
        temp = arg0[0];
        arg1[0] = (temp & temp_r6) + temp_r1;
        arg1[1] = ((temp >> 2) & temp_r6) + temp_r1;
    }
    for (i = 0; i < temp_ip; i++) {
        arg0 -= 1;
        arg1 -= 1 * 2;

        temp = arg0[0];
        arg1[0] = (temp & temp_r6) + temp_r1;
        arg1[1] = ((temp >> 2) & temp_r6) + temp_r1;
    }
}


// D_08936c7c function 1
struct unk_struct_08008420 *func_08008420(struct unk_struct_08008420_init *inputs) {
    struct unk_struct_08008420 *task;
    u32 temp_r3;

    task = mem_heap_alloc(sizeof(struct unk_struct_08008420));
    task->unk8 = (inputs->unk8 + 3) >> 2;
    task->unkC = (inputs->unkC + 3) >> 2;
    task->unk0 = &inputs->unk0[task->unk8];
    task->unk4 = &inputs->unk4[task->unk8 * 2];
    temp_r3 = inputs->unk10;
    temp_r3 = (temp_r3 << 0) | (temp_r3 << 4) | (temp_r3 << 8) | (temp_r3 << 0xc);
    temp_r3 |= (temp_r3 << 0x10);
    task->unk10 = temp_r3;
    return task;
}

// D_08936c7c function 2
u32 func_08008464(struct unk_struct_08008420 *task) {
    u32 *temp_r4 = task->unk0;
    u32 *temp_r2 = task->unk4;
    u32 temp_r5 = 0x33333333;
    u32 temp_r3 = task->unk10;
    u32 temp;
    u32 i;
    u32 temp_r8 = (task->unkC > task->unk8) ? task->unk8 : task->unkC;
    u32 temp_ip = temp_r8 >> 2;
    
    for (i = 0; i < temp_ip; i++) {
        temp_r4 -= 4;
        temp_r2 -= 4 * 2;

        temp = temp_r4[3];
        temp_r2[6] = (temp & temp_r5) + temp_r3;
        temp_r2[7] = ((temp >> 2) & temp_r5) + temp_r3;
        temp = temp_r4[2];
        temp_r2[4] = (temp & temp_r5) + temp_r3;
        temp_r2[5] = ((temp >> 2) & temp_r5) + temp_r3;
        temp = temp_r4[1];
        temp_r2[2] = (temp & temp_r5) + temp_r3;
        temp_r2[3] = ((temp >> 2) & temp_r5) + temp_r3;
        temp = temp_r4[0];
        temp_r2[0] = (temp & temp_r5) + temp_r3;
        temp_r2[1] = ((temp >> 2) & temp_r5) + temp_r3;
    }
    for (i = 0; i < (temp_r8 & 3); i++) {
        temp_r4 -= 1;
        temp_r2 -= 1 * 2;

        temp = temp_r4[0];
        temp_r2[0] = (temp & temp_r5) + temp_r3;
        temp_r2[1] = ((temp >> 2) & temp_r5) + temp_r3;
    }
    
    task->unk0 = temp_r4;
    task->unk4 = temp_r2;
    task->unk8 -= temp_r8;
    
    if (task->unk8 > 0) {
        return FALSE;
    } else {
        return TRUE;
    }
}


/* SCHEDULED FUNCTION CALL */


// Initialise Scheduled Function Task
struct ScheduledFunctionTask *init_scheduled_function_task(struct ScheduledFunctionTask *inputs) {
    struct ScheduledFunctionTask *task;

    task = mem_heap_alloc(sizeof(struct ScheduledFunctionTask));
    task->function = inputs->function;
    task->param = inputs->param;
    task->delay = inputs->delay;
    return task;
}

// Update Scheduled Function Task
u32 update_scheduled_function_task(struct ScheduledFunctionTask *task) {
    if (task->delay) {
        task->delay--;
        return FALSE;
    }
    if (task->function) {
        task->function(task->param);
    }
    return TRUE;
}

// Scheduled Function Call
s32 schedule_function_call(u16 memID, void *function, s32 param, u32 delay) {
    struct ScheduledFunctionTask inputs;

    inputs.function = function;
    inputs.param = param;
    inputs.delay = delay;
    return start_new_task(memID, &delayed_function_call_task, &inputs, NULL, 0);
}


/* BUFFERED TEXTURE */

static struct GFXDecompressProgress D_030010d0;
extern u32 decompress_gfx_rom(struct GFXDecompressProgress *);

u32 decompress_gfx_init(struct CompressedGFX *gfx, u32 size, u32 limit, struct GFXDecompressProgress *progress) {
    u32 (*decompress_gfx)(struct GFXDecompressProgress *);

    if (!progress) {
        progress = &D_030010d0;
    }
    progress->data = gfx->data;
    progress->size = size;
    progress->count = ((gfx->count - 1) << 16) | 0x2020;
    progress->curwin1 = *gfx->window1;
    progress->curwin2 = *gfx->window2;
    progress->win1 = gfx->window1 + 1;
    progress->win2 = gfx->window2 + 1;
    progress->lim1 = limit;
    progress->lim2 = limit;

    decompress_gfx = decompress_gfx_rom;
    return decompress_gfx(progress);
}

u32 decompress_gfx_resume(struct GFXDecompressProgress *progress) {
    u32 (*decompress_gfx)(struct GFXDecompressProgress *);

    if (!progress) {
        progress = &D_030010d0;
    }
    progress->lim1 = progress->lim2;

    decompress_gfx = decompress_gfx_rom;
    return decompress_gfx(progress);
}

#include "asm/code_08007468/asm_08008608.s"

#include "asm/code_08007468/asm_0800861c.s"

#include "asm/code_08007468/asm_08008628.s"

#include "asm/code_08007468/asm_08008658.s"

#include "asm/code_08007468/asm_0800869c.s"

#include "asm/code_08007468/asm_080086c4.s"

#include "asm/code_08007468/asm_08008720.s"

// D_08936c9c function 1
#include "asm/code_08007468/asm_0800873c.s"

// D_08936c9c function 2
#include "asm/code_08007468/asm_08008758.s"

#include "asm/code_08007468/asm_080087b4.s"


/* ? */


// Clamp Signed Integer
s32 clamp_int32(s32 var, s32 min, s32 max) {
    if (var < min) {
        return min;
    }
    if (var > max) {
        return max;
    }
    return var;
}


#include "asm/code_08007468/asm_080087e8.s"

#include "asm/code_08007468/asm_08008910.s"

#include "asm/code_08007468/asm_08008938.s"

#include "asm/code_08007468/asm_08008968.s"

#include "asm/code_08007468/asm_08008990.s"

#include "asm/code_08007468/asm_080089c0.s"

#include "asm/code_08007468/asm_08008a70.s"

#include "asm/code_08007468/asm_08008ab8.s"

void func_08008b00(u32 unused_arg0, u32 unused_arg1, s16 arg2, s24_8 arg3, s24_8 arg4,
    s16 arg5, s24_8 arg6, s24_8 arg7, u16 arg8,
    struct unk_struct_08008b00 *arg9, u32 arg10, u32 arg11) {

    s24_8 temp_sp0, temp_sp4, temp_r9, temp_r8;
    s32 ret_r5, ret_sp8;
    s24_8 temp_r7, ret_spc, ret_sp10;
    s32 ret_sp14;
    s24_8 temp_sp18, temp_sp1c, temp_sp20;
    s32 i;
    s24_8 temp_8000 = INT_TO_FIXED(128);

    temp_sp0 = arg11 ? sins(arg5) : sins2(arg5);
    temp_sp4 = arg11 ? coss(arg5) : coss2(arg5);

    temp_r9 = arg11 ? sins(-arg2) : sins2(-arg2);
    temp_r8 = arg11 ? coss(-arg2) : coss2(-arg2);

    ret_r5 = fast_divsi3(160 * 256, arg8);
    ret_sp14 = fast_divsi3(160 * 256, arg8);
    ret_sp8 = fast_divsi3(ret_r5 * 240, 160);

    temp_r7 = INT_TO_FIXED(-ret_r5) >> 1;

    ret_spc = fast_divsi3(INT_TO_FIXED(ret_r5), 160);
    temp_r7 += fast_divsi3(ret_r5 * arg7, 160);
    arg3 += fast_divsi3(ret_r5 * arg6, 160);
    ret_sp10 = fast_divsi3(INT_TO_FIXED(ret_r5), 160);

    temp_sp18 = ret_sp14 * temp_sp0;

    temp_sp1c = arg3 - temp_8000;
    temp_sp20 = arg4 - temp_8000;

    for (i = 0; i < 160; i++) {
        s24_8 temp_r1;
        s32 temp_r5_2 = FALSE;
        if (temp_sp0 != 0) {
            temp_r1 = FIXED_POINT_MUL(temp_r7, temp_sp4) - temp_sp18;
            if (temp_r1 == 0) {
                temp_r5_2 = TRUE;
            }
        }
        if ((temp_sp0 == 0) || temp_r5_2) {
            arg9->unk8 = -1;
            arg9->unkC = -1;
            arg9->unk6 = 0;
            arg9->unk4 = 0;
            arg9->unk2 = 0;
            arg9->unk0 = 0;
        } else {
            s24_8 m_r4, m_r3, m_r2;
            temp_r1 = fast_divsi3(INT_TO_FIXED(ret_sp14) << 8, temp_r1); // fixed point division
            m_r4 = FIXED_POINT_MUL(-temp_r1, temp_sp0);

            m_r3 = temp_sp1c - (ret_sp8 >> 1) * m_r4;
            m_r2 = temp_sp20 + FIXED_POINT_MUL(temp_r1, temp_r7);

            arg9->unk8 = ((temp_r8 * m_r3 - temp_r9 * m_r2) >> 8) + temp_8000; // doesn't work with the macros
            arg9->unkC = ((temp_r9 * m_r3 + temp_r8 * m_r2) >> 8) + temp_8000;
            
            m_r4 *= ret_sp10;
            arg9->unk0 = FIXED_POINT_MUL(temp_r8, m_r4) >> 0x8;
            arg9->unk2 = 0;
            arg9->unk4 = FIXED_POINT_MUL(temp_r9, m_r4) >> 0x8;
            arg9->unk6 = 0;
        }
        temp_r7 += ret_spc;
        arg9 += arg10;
    }
}

void func_08008d44(u32 unused_arg0, u32 unused_arg1, s16 arg2, s24_8 arg3, s24_8 arg4, s16 arg5, s24_8 arg6, s24_8 arg7, u16 arg8, struct unk_struct_08008b00 *arg9, u32 arg10) {
    func_08008b00(unused_arg0, unused_arg1, arg2, arg3, arg4, arg5 - 0x200, arg6, arg7, arg8, arg9, arg10, 0);
}

void func_08008d88(u32 unused_arg0, u32 unused_arg1, s16 arg2, s24_8 arg3, s24_8 arg4, s16 arg5, s24_8 arg6, s24_8 arg7, u16 arg8, struct unk_struct_08008b00 *arg9, u32 arg10) {
    func_08008b00(unused_arg0, unused_arg1, arg2, arg3, arg4, arg5 - 0x200, arg6, arg7, arg8, arg9, arg10, 1);
}

static void int_to_str(char *buf, s32 value) {
    char tmp[12];
    s32 i = 0, j = 0;
    s32 is_negative = 0;
    if (value < 0) {
        is_negative = 1;
        value = -value;
    }
    do {
        tmp[i++] = '0' + (value % 10);
        value /= 10;
    } while (value && i < 11);
    if (is_negative) tmp[i++] = '-';
    while (i > 0) buf[j++] = tmp[--i];
    buf[j] = '\0';
}

static void uint_to_str(char *buf, u32 value) {
    char tmp[11];
    s32 i = 0, j = 0;
    do {
        tmp[i++] = '0' + (value % 10);
        value /= 10;
    } while (value && i < 10);
    while (i > 0) buf[j++] = tmp[--i];
    buf[j] = '\0';
}

static void uint_to_hex(char *buf, u32 value) {
    char tmp[9];
    s32 i = 0, j = 0;
    do {
        s32 digit = value & 0xF;
        tmp[i++] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
        value >>= 4;
    } while (value && i < 8);
    while (i > 0) buf[j++] = tmp[--i];
    buf[j] = '\0';
}

s32 snprintf(char *s, s32 n, const char *fmt, ...) {
    va_list args;
    s32 i = 0, o = 0;
    s32 k;
    char pad_char;
    int width;
    int left;
    char spec;
    char buf_temp[24];
    int bl, sl;
    const char *ss;
    u32 vval;
    int j;
    va_start(args, fmt);
    while (fmt[i] && o < n - 1) {
        if (fmt[i] == '%') {
            i++;
            pad_char = ' ';
            width = 0;
            left = 0;
            /* handle flags: '-' for left-justify, '0' for zero-pad */
            while (fmt[i] == '-' || fmt[i] == '0') {
                if (fmt[i] == '-') {
                    left = 1;
                    pad_char = ' ';
                    i++;
                } else if (fmt[i] == '0') {
                    if (!left) pad_char = '0';
                    i++;
                }
            }
            while (fmt[i] >= '0' && fmt[i] <= '9') {
                width = width * 10 + (fmt[i] - '0');
                i++;
            }
            spec = fmt[i];
            if (spec == 'd' || spec == 'i') {
                s32 v = va_arg(args, s32);
                int_to_str(buf_temp, v);
                bl = 0; while (buf_temp[bl]) bl++;
                if (!left) {
                    for (k = 0; k < width - bl && o < n - 1; ++k) s[o++] = pad_char;
                    for (k = 0; buf_temp[k] && o < n - 1; k++) s[o++] = buf_temp[k];
                } else {
                    for (k = 0; buf_temp[k] && o < n - 1; k++) s[o++] = buf_temp[k];
                    for (k = 0; k < width - bl && o < n - 1; ++k) s[o++] = pad_char;
                }
            } else if (spec == 'u') {
                vval = va_arg(args, u32);
                uint_to_str(buf_temp, vval);
                bl = 0; while (buf_temp[bl]) bl++;
                if (!left) {
                    for (k = 0; k < width - bl && o < n - 1; ++k) s[o++] = pad_char;
                    for (k = 0; buf_temp[k] && o < n - 1; k++) s[o++] = buf_temp[k];
                } else {
                    for (k = 0; buf_temp[k] && o < n - 1; k++) s[o++] = buf_temp[k];
                    for (k = 0; k < width - bl && o < n - 1; ++k) s[o++] = pad_char;
                }
            } else if (spec == 'x' || spec == 'X') {
                vval = va_arg(args, u32);
                uint_to_hex(buf_temp, vval);
                bl = 0; while (buf_temp[bl]) bl++;
                if (spec == 'X') {
                    for (j = 0; j < bl; ++j) {
                        if (buf_temp[j] >= 'a' && buf_temp[j] <= 'f') buf_temp[j] = buf_temp[j] - 'a' + 'A';
                    }
                }
                if (!left) {
                    for (k = 0; k < width - bl && o < n - 1; ++k) s[o++] = pad_char;
                    for (k = 0; buf_temp[k] && o < n - 1; k++) s[o++] = buf_temp[k];
                } else {
                    for (k = 0; buf_temp[k] && o < n - 1; k++) s[o++] = buf_temp[k];
                    for (k = 0; k < width - bl && o < n - 1; ++k) s[o++] = pad_char;
                }
            } else if (spec == 's') {
                ss = va_arg(args, const char *);
                sl = 0; while (ss[sl]) sl++;
                if (!left) {
                    for (k = 0; k < width - sl && o < n - 1; ++k) s[o++] = pad_char;
                    for (k = 0; ss[k] && o < n - 1; k++) s[o++] = ss[k];
                } else {
                    for (k = 0; ss[k] && o < n - 1; k++) s[o++] = ss[k];
                    for (k = 0; k < width - sl && o < n - 1; ++k) s[o++] = pad_char;
                }
            } else if (spec == 'c') {
                char c = (char)va_arg(args, int);
                if (!left) {
                    for (k = 0; k < width - 1 && o < n - 1; ++k) s[o++] = pad_char;
                    s[o++] = c;
                } else {
                    s[o++] = c;
                    for (k = 0; k < width - 1 && o < n - 1; ++k) s[o++] = pad_char;
                }
            } else if (spec == '%') {
                if (!left) {
                    for (k = 0; k < width - 1 && o < n - 1; ++k) s[o++] = pad_char;
                    s[o++] = '%';
                } else {
                    s[o++] = '%';
                    for (k = 0; k < width - 1 && o < n - 1; ++k) s[o++] = pad_char;
                }
            } else {
                s[o++] = '%';
                if (o < n - 1) s[o++] = spec;
            }
            i++;
        } else {
            s[o++] = fmt[i++];
        }
    }
    s[o] = '\0';
    va_end(args);
    return o;
}
