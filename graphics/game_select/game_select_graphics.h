#pragma once

#include "global.h"
#include "graphics.h"

/* GAME SELECT - ANIMATIONS */

extern struct Animation anim_game_select_bg_square_large[];
extern struct Animation anim_game_select_bg_square_small[];
extern struct Animation anim_game_select_border_target[];
extern struct Animation anim_game_select_new_game[];
extern struct Animation anim_game_select_clear_game[];
extern struct Animation anim_game_select_get_superb[];
extern struct Animation anim_game_select_stage1[];
extern struct Animation anim_game_select_stage_box[];
extern struct Animation anim_game_select_flow_num[];
extern struct Animation anim_game_select_flow_text[];
extern struct Animation anim_game_select_flow_arrow[];
extern struct Animation anim_game_select_border_perfect3[];
extern struct Animation anim_game_select_text_button[];
extern struct Animation anim_game_select_medal_count_unused[];
extern struct Animation anim_game_select_medal_num[];
extern struct Animation anim_game_select_medal_num0[];
extern struct Animation anim_game_select_medal_text[];
extern struct Animation anim_game_select_stage2[];
extern struct Animation anim_game_select_stage3[];
extern struct Animation anim_game_select_stage4[];
extern struct Animation anim_game_select_stage5[];
extern struct Animation anim_game_select_stage0[];
extern struct Animation anim_game_select_stage6[];
extern struct Animation anim_game_select_stage7[];
extern struct Animation anim_game_select_stage8[];
extern struct Animation anim_game_select_stage9[];
extern struct Animation anim_game_select_border_perfect2[];
extern struct Animation anim_game_select_border_perfect1[];
extern struct Animation anim_game_select_cursor[];
extern struct Animation anim_game_select_perfect_rank[];
extern struct Animation anim_game_select_no_practice[];
extern struct Animation anim_game_select_tempo_up[];

/* GAME SELECT - COMPRESSED GRAPHICS */

extern struct CompressedData game_select_bg_tiles;
extern struct CompressedData game_select_bg_map_description;
extern struct CompressedData game_select_bg_map_perfect_notice;
extern struct CompressedData game_select_obj;

/* GAME SELECT - PALETTES */

extern Palette game_select_obj_pal[];
extern Palette game_select_bg_pal[];

/* GAME SELECT ICONS - UNCOMPRESSED TEXTURES */

extern const u8 icon_karate_man_2_bin[];
extern const u8 icon_sneaky_spirits_bin[];
extern const u8 icon_remix6_bin[];
extern const u8 icon_polyrhythm_bin[];
extern const u8 icon_clappy_trio_bin[];
extern const u8 icon_ninja_bodyguard_bin[];
extern const u8 icon_tap_trial_bin[];
extern const u8 icon_night_walk_bin[];
extern const u8 icon_karate_man_bin[];
extern const u8 icon_spaceball_bin[];
extern const u8 icon_snappy_trio_bin[];
extern const u8 icon_tap_trial_2_bin[];
extern const u8 icon_bouncy_road_bin[];
extern const u8 icon_sick_beats_bin[];
extern const u8 icon_rhythm_tweezers_bin[];
extern const u8 icon_rap_women_bin[];
extern const u8 icon_cosmic_dance_bin[];
extern const u8 icon_bon_dance_bin[];
extern const u8 icon_samurai_slice_bin[];
extern const u8 icon_remix7_bin[];
extern const u8 icon_marching_orders_2_bin[];
extern const u8 icon_marching_orders_bin[];
extern const u8 icon_remix1_bin[];
extern const u8 icon_wizards_waltz_bin[];
extern const u8 icon_bunny_hop_bin[];
extern const u8 icon_rhythm_tweezers_2_bin[];
extern const u8 icon_fireworks_bin[];
extern const u8 icon_remix2_bin[];
extern const u8 icon_power_calligraphy_bin[];
extern const u8 icon_toss_boys_2_bin[];
extern const u8 icon_toss_boys_bin[];
extern const u8 icon_rat_race_bin[];
extern const u8 icon_tram_pauline_bin[];
extern const u8 icon_remix3_bin[];
extern const u8 icon_remix4_bin[];
extern const u8 icon_bon_odori_bin[];
extern const u8 icon_showtime_bin[];
extern const u8 icon_remix8_bin[];
extern const u8 icon_ninja_reincarnate_bin[];
extern const u8 icon_remix5_bin[];
extern const u8 icon_space_dance_bin[];
extern const u8 icon_night_walk_2_bin[];
extern const u8 icon_rap_men_bin[];
extern const u8 icon_quiz_show_bin[];
extern const u8 icon_live_menu_bin[];
extern const u8 icon_cafe_bin[];
extern const u8 icon_toys_menu_bin[];
extern const u8 icon_endless_menu_bin[];
extern const u8 icon_lessons_menu_bin[];
extern const u8 icon_staff_credit_bin[];
extern const u8 icon_bouncy_road_2_bin[];
extern const u8 icon_polyrhythm_2_bin[];
extern const u8 icon_spaceball_2_bin[];
extern const u8 icon_sneaky_spirits_2_bin[];
extern const u8 icon_karate_man_extra_bin[];
extern const u8 icon_rhythm_tweezers_extra_bin[];
extern const u8 icon_marching_orders_extra_bin[];
extern const u8 icon_spaceball_extra_bin[];
extern const u8 icon_clappy_trio_extra_bin[];
extern const u8 icon_remix1_extra_bin[];

/* GAME SELECT ICONS - PALETTES */

extern Palette game_select_bg_icon_pal[];

/* GAME SELECT ICON OVERLAYS - UNCOMPRESSED TEXTURES */

extern const u8 icon_overlay_striped_border_bin[]; // Animated Striped Border (Medal Corner)
extern const u8 icon_overlay_closed_bin[]; // "CLOSE" Icon
extern const u8 icon_overlay_normal_border_bin[]; // Standard Border
extern const u8 icon_overlay_blank1_bin[]; // Blank
extern const u8 icon_overlay_medal_bin[]; // Medal
extern const u8 icon_overlay_new_game_bin[]; // New Game/Remix Circular Spotlight
extern const u8 icon_overlay_blank2_bin[]; // Blank
extern const u8 icon_overlay_perfect_bin[]; // Perfect

/* GAME SELECT ICON OVERLAYS - PALETTES */

extern Palette game_select_bg_overlay_pal[];
