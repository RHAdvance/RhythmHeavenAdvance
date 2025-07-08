#pragma once

#include "global.h"
#include "engines.h"

#include "games/rhythm_tweezers/graphics/rhythm_tweezers_graphics.h"

// Engine Macros/Enums:
#define RHYTHM_TWEEZERS_FALLING_HAIR_AMOUNT 5

enum RhythmTweezersHeldHairsEnum {
    TWEEZERS_HELD_HAIR_NONE,
    TWEEZERS_HELD_HAIR_FULL,
    TWEEZERS_HELD_HAIR_BARELY
};

enum RhythmTweezersVegetableTypesEnum {
    VEGETABLE_TYPE_ONION,
    VEGETABLE_TYPE_TURNIP,
    VEGETABLE_TYPE_POTATO
};

#define RT_VEGETABLE_BG_MAP_L *(u32 *)(VRAMBase + 0xF000) // VRAM BG Map for vegetable textures (left).
#define RT_VEGETABLE_BG_MAP_R *(u32 *)(VRAMBase + 0xF800) // VRAM BG Map for vegetable textures (right).


// Engine Types:
struct RhythmTweezersEngineData {
    u8 version; // Value:   Version { 0..2 = Rhythm Tweezers; 3..5 = Rhythm Tweezers 2 }
    struct RhythmTweezersTweezers {
        struct AffineSprite *sprite; // Sprite: Tweezers
        u8  isMoving;   // Flag:    Active
        u8  heldHair;   // State:   Holding { 0 = None; 1 = Full Hair; 2 = Half Hair }
        s16 rotation;   // Value:   0x800 = 360 degrees
        u32 cycleTime;  // Counter: Cycle Position
        u32 cycleTarget;    // Value:   Cycle Target
        u8  isPulling;  // Flag:    Pulling (assigned but never used)
    } tweezers;
    u32 hairCycleTime;  // Counter: Hair Placement Cycle Position
    u32 hairCycleTarget;    // Value:   Hair Placement Cycle Target
    u8  fallingHairsNext;  // Counter: Next Available Falling Hair {0..4}
    struct RhythmTweezersFallingHair {
        struct AffineSprite *sprite; // Sprite: Falling Hair
        s32 fallDistance;   // Counter:   Vertical Position
        u32 fallSpeed;      // Value: Vertical Velocity
        s16 rotation;       // Value:   Rotation
        u16 rotationSpeed;  // Value:   Randomised Rotation Speed ( agb_random(0x1f) - 0xf )
    } fallingHairs[RHYTHM_TWEEZERS_FALLING_HAIR_AMOUNT];
    struct RhythmTweezersVegetable {
        s16 spriteCurrent;  // Sprite:  Current Vegetable Face
        s16 spriteNext;     // Sprite:  Upcoming Vegetable Face
        u8  typeCurrent;    // State:   Current Vegetable Type { 0 = Onion; 1 = Turnip; 2 = Potato }
        u8  typeNext;       // State:   Upcoming Vegetable Type { 0 = Onion; 1 = Turnip; 2 = Potato }
        u8  isScrolling;    // Flag:    Screen Scrolling
        u32 scrollTime;     // Counter: Screen Scroll Time
        u32 scrollTarget;   // Value:   Screen Scroll Target
        u8  bgMapSide;      // Flag:    Destination Vegetable BG Map { 0 = D_0600f800 (Right); -1 = D_0600f000 (Left) }
    } vegetable;
    struct {
        u16 full; // Queued/Missed
        u16 half; // Barely'd
    } existingHairs;
    s16 tutorialSprite; // Sprite:  Tutorial Text (Unused)
    s16 screenHorizontalPosition; // Value:   Global Horizontal Position (for vegetable faces and hair)
    s16 maskPosition;  // Value:   Mask Vertical Position (-160 = Hidden; 0 = Fully Visible)
    s16 maskVelocity;  // Value:   Mask Vertical Velocity (-8 = Down; 8 = Up)
};

struct RhythmTweezersCue {
    u32 unk0_b0:5;
    u32 isLongHair:4;
    u32 finished:1;
    struct AffineSprite *sprite;
    u32 null8;
    u32 nullC;
    u32 null10;
    u32 null14;
    u32 null18;
    u32 null1C;
    u32 null20;
    u32 null24;
    s16 rotation;
    u16 null2A;
    u16 pullTime; // Current pulling time.
    u16 pullTarget; // Target pulling time.
};


// Engine Definition Data:
extern struct CompressedData *rhythm_tweezers_veg_bg_maps[]; // Array of BG Map pointers for vegetable textures
extern struct CompressedData *rhythm_tweezers_extra_veg_bg_maps[]; // Array of BG Map pointers for vegetable textures
extern struct CompressedData *rhythm_tweezers_buffered_textures[]; // Buffered Textures List
extern struct GraphicsTable *rhythm_tweezers_gfx_tables[]; // Graphics Table
extern struct Animation *rhythm_tweezers_veg_face_anim[]; // Array of animation pointers for vegetable faces


// Functions:
extern void rhythm_tweezers_init_veg(void); // Initialise Vegetable Face
extern void rhythm_tweezers_scroll_to_next_veg(u32); // Engine Event 02 (Scroll to New Vegetable)
extern void rhythm_tweezers_play_cash_reg_sfx(void); // Engine Event 04 (Play Cash Register SFX)
extern void rhythm_tweezers_update_scroll(void); // Update Vegetable (Scrolling)
extern void rhythm_tweezers_set_next_veg_type(u32); // Engine Event 03 (Set Upcoming Vegetable Type)
extern void rhythm_tweezers_removed_engine_event(void); // Engine Event 06 (STUB)
extern void rhythm_tweezers_update_veg(void); // Update Vegetable
extern void rhythm_tweezers_init_falling_hairs(void); // Initialise Falling Hairs
extern void rhythm_tweezers_update_falling_hairs(void); // Update Falling Hairs
extern void rhythm_tweezers_spawn_falling_hair(u32); // Spawn Falling Hair
extern void rhythm_tweezers_init_tweezers(void); // Initialise Tweezers
extern void rhythm_tweezers_spawn_tweezers(void); // Engine Event 00 (Spawn Tweezers)
extern void rhythm_tweezers_update_tweezers_cycle(void); // Update Tweezers (Position)
extern void rhythm_tweezers_update_vertical_scroll(void); // Update Tweezers (Vertical Screen Scroll)
extern void rhythm_tweezers_update_tweezers(void); // Update Tweezers
extern void rhythm_tweezers_init_gfx3(void); // Graphics Init. 3
extern void rhythm_tweezers_init_gfx2(void); // Graphics Init. 2
extern void rhythm_tweezers_init_gfx1(void); // Graphics Init. 1
extern void rhythm_tweezers_engine_start(u32 version); // Game Engine Start
extern void rhythm_tweezers_engine_event_stub(void); // Engine Event 09 (STUB)
extern void rhythm_tweezers_update_mask(void); // Update Mask
extern void rhythm_tweezers_show_mask(void); // Engine Event 07 (Show Mask)
extern void rhythm_tweezers_hide_mask(void); // Engine Event 08 (Hide Mask)
extern void rhythm_tweezers_engine_update(void); // Game Engine Update
extern void rhythm_tweezers_engine_stop(void); // Game Engine Stop (STUB)
extern void rhythm_tweezers_start_hair_cycle(void); // Engine Event 01 (Reset Hair Placement Cycle)
extern void rhythm_tweezers_update_hair_cycle(void); // Update Hair Placement Cycle
extern void rhythm_tweezers_cue_spawn(struct Cue *, struct RhythmTweezersCue *, u32 isLongHair); // Cue - Spawn
extern u32  rhythm_tweezers_cue_update_short(struct Cue *, struct RhythmTweezersCue *, u32 runningTime, u32 duration); // Cue - Update (Short Hair)
extern u32  rhythm_tweezers_cue_update_long(struct Cue *, struct RhythmTweezersCue *, u32 runningTime, u32 duration); // Cue - Update (Long Hair)
extern void rhythm_tweezers_cue_despawn(struct Cue *, struct RhythmTweezersCue *); // Cue - Despawn
extern void rhythm_tweezers_cue_hit_short(struct Cue *, struct RhythmTweezersCue *, u32 pressed, u32 released); // Cue - Hit (Short Hair)
extern void rhythm_tweezers_cue_hit_long(struct Cue *, struct RhythmTweezersCue *, u32 pressed, u32 released); // Cue - Hit/Barely (Long Hair)
extern void rhythm_tweezers_cue_barely_short(struct Cue *, struct RhythmTweezersCue *, u32 pressed, u32 released); // Cue - Barely (Short Hair)
extern void rhythm_tweezers_cue_miss(struct Cue *, struct RhythmTweezersCue *); // Cue - Miss
extern void rhythm_tweezers_input_event(u32 pressed, u32 released); // Input Event
extern void rhythm_tweezers_common_beat_animation(void); // Common Event 0 (Beat Animation, Unimplemented)
extern void rhythm_tweezers_common_display_text(void); // Common Event 1 (Display Text, Unimplemented)
extern void rhythm_tweezers_hide_tutorial_text(void); // Engine Event 05 (Hide Tutorial Text, Unused)
