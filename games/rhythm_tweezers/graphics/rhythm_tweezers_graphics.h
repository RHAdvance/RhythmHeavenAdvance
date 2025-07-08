#pragma once

#include "global.h"
#include "graphics.h"

/* RHYTHM TWEEZERS - ANIMATIONS */

extern struct Animation anim_veg_face_onion[];
extern struct Animation anim_veg_face_turnip[];
extern struct Animation rhythm_tweezers_anim02[];
extern struct Animation anim_rhythm_tweezers_short_hair[];
extern struct Animation anim_tweezers_pluck_hit[];
extern struct Animation rhythm_tweezers_anim05[];
extern struct Animation anim_tweezers_pluck_barely[];
extern struct Animation anim_tweezers_pluck_miss[];
extern struct Animation anim_rhythm_tweezers_falling_hair[];
extern struct Animation anim_rhythm_tweezers_hair_stubble[];
extern struct Animation anim_rhythm_tweezers_tutorial_text[];
extern struct Animation rhythm_tweezers_anim11[];
extern struct Animation anim_rhythm_tweezers_long_hair[];
extern struct Animation anim_tweezers_pull[];
extern struct Animation anim_veg_face_potato[];

/* RHYTHM TWEEZERS - COMPRESSED GRAPHICS */

extern struct CompressedData rhythm_tweezers_bg_tiles; // BG Tiles - Vegetables
extern struct CompressedData rhythm_tweezers_extra_bg_tiles; // BG Tiles - Vegetables (Extra)
extern struct CompressedData rhythm_tweezers_bg_map_onion; // BG Map - Onion
extern struct CompressedData rhythm_tweezers_bg_map_turnip; // BG Map - Turnip
extern struct CompressedData rhythm_tweezers_bg_map_potato; // BG Map - Potato
extern struct CompressedData rhythm_tweezers_extra_bg_map_pumpkin; // BG Map - Pumpkin
extern struct CompressedData rhythm_tweezers_extra_bg_map_sweet_potato; // BG Map - Sweet Potato
extern struct CompressedData rhythm_tweezers_extra_bg_map_watermelon; // BG Map - Watermelon
extern struct CompressedData rhythm_tweezers_obj; // OBJ Tiles
extern struct CompressedData rhythm_tweezers_no_peeking_sign_bg_tiles; // BG Tiles - Mask
extern struct CompressedData rhythm_tweezers_no_peeking_sign_bg_map; // BG Map - Mask

/* RHYTHM TWEEZERS - PALETTES */

extern Palette rhythm_tweezers_pal[];
extern Palette rhythm_tweezers_2_pal[];
extern Palette rhythm_tweezers_extra_pal[];