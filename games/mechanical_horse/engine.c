#include "engines/mechanical_horse.h"


// [D_0805a924] Mechanical Horse BG - Graphics Table 0
const struct GraphicsTable D_0805a924[] = {
    /* BG Tileset */ {
        /* Src.  */ &mechanical_horse_photo_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_photo_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_0805a948] Mechanical Horse BG - Graphics Table 1
const struct GraphicsTable D_0805a948[] = {
    /* BG Tileset */ {
        /* Src.  */ &mechanical_horse_space_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_space_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_0805a96c] Mechanical Horse BG - Graphics Table 2
const struct GraphicsTable D_0805a96c[] = {
    /* BG Tileset */ {
        /* Src.  */ &mechanical_horse_blur_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_blur_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_0805a990] Mechanical Horse BG - Graphics Table 3
const struct GraphicsTable D_0805a990[] = {
    /* BG Tileset */ {
        /* Src.  */ &mechanical_horse_city_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_city_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_0805a9b4] Mechanical Horse BG - Graphics Table 4
const struct GraphicsTable D_0805a9b4[] = {
    /* BG Tileset */ {
        /* Src.  */ &mechanical_horse_road_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_road_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_0805a9d8] Mechanical Horse BG - Graphics Table 5
const struct GraphicsTable D_0805a9d8[] = {
    /* BG Tileset */ {
        /* Src.  */ &mechanical_horse_trees_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_trees_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e8d9c] Backgrounds
struct MechanicalHorseBG mechanical_horse_backgrounds[] = {
    /* 0x00 */ {
        /* Palette   */ mechanical_horse_bg_01_pal,
        /* GFX Table */ D_0805a9d8
    },
    /* 0x01 */ {
        /* Palette   */ mechanical_horse_bg_02_pal,
        /* GFX Table */ D_0805a9b4
    },
    /* 0x02 */ {
        /* Palette   */ mechanical_horse_bg_03_pal,
        /* GFX Table */ D_0805a990
    },
    /* 0x03 */ {
        /* Palette   */ mechanical_horse_bg_04_pal,
        /* GFX Table */ D_0805a96c
    },
    /* 0x04 */ {
        /* Palette   */ mechanical_horse_bg_05_pal,
        /* GFX Table */ D_0805a948
    },
    /* 0x05 */ {
        /* Palette   */ mechanical_horse_bg_06_pal,
        /* GFX Table */ D_0805a924
    }
};

// Empty String
const char D_0805a9fc[] = "";

// ?
const s32 D_0805aa00[] = {
    3, 3, 2, 3
};

// ?
const s32 D_0805aa10[] = {
    3, 3, 2, 3
};

// ?
const s32 D_0805aa20[] = {
    0x60,  0x80,  0xc0,  0x100,
    0x200, 0x400, 0x600, 0x800
};

// ?
const s24_8 D_0805aa40[][2] = {
    {INT_TO_FIXED(-2), INT_TO_FIXED(-2.5)},
    {INT_TO_FIXED(-3), INT_TO_FIXED(-3)},
    {INT_TO_FIXED(-4), INT_TO_FIXED(-3.5)},
    {INT_TO_FIXED(-5), INT_TO_FIXED(-4)}
};

// ? (duration values)
const u32 D_0805aa60[][4] = {
    { 0x10, 0x20, 0x10, 0x20 },
    { 0x18, 0x18, 0x18, 0x18 },
    { 0x18, 0x0C, 0x0C, 0x00 },
    { 0x18, 0x0C, 0x0C, 0x0C }
};

const s32 D_0805aaa0[] = {
    0xd800, 0x14000, 0x1e000, 0x28000
};

const s32 D_0805aab0[][4] = {
    { 0x4c, 0x76, 0x93, 0xbd },
    { 0x4a, 0x71, 0x88, 0xaf },
    { 0x4f, 0x8f, 0xa2, -0x40 },
    { 0x45, 0x63, 0x81, 0xa1 },
};

// [D_089e8dcc] Buffered Textures List
struct CompressedData *mechanical_horse_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e8dd0] Graphics Table
struct GraphicsTable gfx_table_mechanical_horse[] = {
    /* BG Tileset */ {
        /* Src.  */ &mechanical_horse_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_bg_map_ground,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_bg_map_speedometer,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &mechanical_horse_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ mechanical_horse_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ mechanical_horse_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* BG Tileset */ {
        /* Src.  */ &mechanical_horse_trees_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0x8000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &mechanical_horse_trees_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ mechanical_horse_bg_01_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x20
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[2],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};


  //  //  //  LESSON DATA  //  //  //


// [D_089e8e60] Horse Clops (Player)
struct SongHeader *mechanical_horse_player_horse_sfx[] = {
    /* WALK */
        /* 0x00 */ &s_uma_walk1_seqData,
        /* 0x01 */ &s_uma_walk2_seqData,
        /* 0x02 */ &s_uma_walk3_seqData,
        /* 0x03 */ &s_uma_walk4_seqData,
    /* TROT */
        /* 0x00 */ &s_uma_trot1_seqData,
        /* 0x01 */ &s_uma_trot2_seqData,
        /* 0x02 */ &s_uma_trot1_seqData,
        /* 0x03 */ &s_uma_trot2_seqData,
    /* CANTER */
        /* 0x00 */ &s_uma_canter1_seqData,
        /* 0x01 */ &s_uma_canter2_seqData,
        /* 0x02 */ &s_uma_canter3_seqData,
        /* 0x03 */ &s_uma_hihin_seqData,
    /* GALLOP */
        /* 0x00 */ &s_uma_galop1_seqData,
        /* 0x01 */ &s_uma_galop2_seqData,
        /* 0x02 */ &s_uma_galop3_seqData,
        /* 0x03 */ &s_uma_galop4_seqData
};

// [D_089e8ea0] Horse Clops (Teacher)
struct SongHeader *mechanical_horse_teacher_horse_sfx[] = {
    /* WALK */ 
        /* 0x00 */ &s_uma_walk1_t_seqData,
        /* 0x01 */ &s_uma_walk2_t_seqData,
        /* 0x02 */ &s_uma_walk3_t_seqData,
        /* 0x03 */ &s_uma_walk4_t_seqData,
    /* TROT */ 
        /* 0x04 */ &s_uma_trot1_t_seqData,
        /* 0x05 */ &s_uma_trot2_t_seqData,
        /* 0x06 */ &s_uma_trot1_t_seqData,
        /* 0x07 */ &s_uma_trot2_t_seqData,
    /* CANTER */
        /* 0x08 */ &s_uma_canter1_t_seqData,
        /* 0x09 */ &s_uma_canter2_t_seqData,
        /* 0x0a */ &s_uma_canter3_t_seqData,
        /* 0x0b */ &s_uma_hihin_seqData,
    /* GALLOP */ 
        /* 0x0c */ &s_uma_galop1_t_seqData,
        /* 0x0d */ &s_uma_galop2_t_seqData,
        /* 0x0e */ &s_uma_galop3_t_seqData,
        /* 0x0f */ &s_uma_galop4_t_seqData
};

// [D_089e8ee0] Lesson BGM
struct SongHeader *mechanical_horse_lesson_bgm[] = {
    /* WALK   */ &s_uma_bgm1_seqData,
    /* TROT   */ &s_uma_bgm2_seqData,
    /* CANTER */ &s_uma_bgm3_seqData,
    /* GALLOP */ &s_uma_bgm4_seqData
};

// [D_089e8ef0] Horse Animations
struct Animation *mechanical_horse_anim[] = {
    /* WALK   */ anim_horse_walk,
    /* TROT   */ anim_horse_trot,
    /* CANTER */ anim_horse_canter,
    /* GALLOP */ anim_horse_gallop
};

// [D_089e8f00] Jockey Animations
struct Animation *mechanical_horse_jockey_anim[] = {
    /* WALK   */ anim_horse_walk_jockey,
    /* TROT   */ anim_horse_trot_jockey,
    /* CANTER */ anim_horse_canter_jockey,
    /* GALLOP */ anim_horse_gallop_jockey
};

// [D_089e8f10] Lesson Text Animations
struct Animation *mechanical_horse_lesson_text_anim[][4] = {
    /* WALK */ {
        /* 0x00 */ anim_horse_text_pak,
        /* 0x01 */ anim_horse_text_ka,
        /* 0x02 */ anim_horse_text_pak,
        /* 0x03 */ anim_horse_text_ka
    },
    /* TROT */ {
        /* 0x00 */ anim_horse_text_tot,
        /* 0x01 */ anim_horse_text_ka,
        /* 0x02 */ anim_horse_text_tot,
        /* 0x03 */ anim_horse_text_ka
    },
    /* CANTER */ {
        /* 0x00 */ anim_horse_text_pa,
        /* 0x01 */ anim_horse_text_ta,
        /* 0x02 */ anim_horse_text_rap,
        /* 0x03 */ anim_horse_text_pa
    },
    /* GALLOP */ {
        /* 0x00 */ anim_horse_text_do,
        /* 0x01 */ anim_horse_text_do,
        /* 0x02 */ anim_horse_text_do,
        /* 0x03 */ anim_horse_text_dod
    }
};


  //  //  //  CUE DATA  //  //  //


// [D_089e8f50] Cue 00 (Walk)
struct CueDefinition mechanical_horse_cue_walk = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | B_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ mechanical_horse_cue_spawn,
    /* Spawn Parameter */ HORSE_LESSON_1_WALK,
    /* Func. Update    */ mechanical_horse_cue_update,
    /* Func. Despawn   */ mechanical_horse_cue_despawn,
    /* Func. Hit       */ mechanical_horse_cue_hit,
    /* Func. Barely    */ mechanical_horse_cue_barely,
    /* Func. Miss      */ mechanical_horse_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e8f90] Cue 01 (Trot)
struct CueDefinition mechanical_horse_cue_trot = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | B_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ mechanical_horse_cue_spawn,
    /* Spawn Parameter */ HORSE_LESSON_2_TROT,
    /* Func. Update    */ mechanical_horse_cue_update,
    /* Func. Despawn   */ mechanical_horse_cue_despawn,
    /* Func. Hit       */ mechanical_horse_cue_hit,
    /* Func. Barely    */ mechanical_horse_cue_barely,
    /* Func. Miss      */ mechanical_horse_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e8fd0] Cue 02 (Canter)
struct CueDefinition mechanical_horse_cue_canter = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | B_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ mechanical_horse_cue_spawn,
    /* Spawn Parameter */ HORSE_LESSON_3_CANTER,
    /* Func. Update    */ mechanical_horse_cue_update,
    /* Func. Despawn   */ mechanical_horse_cue_despawn,
    /* Func. Hit       */ mechanical_horse_cue_hit,
    /* Func. Barely    */ mechanical_horse_cue_barely,
    /* Func. Miss      */ mechanical_horse_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e9010] Cue 03 (Gallop)
struct CueDefinition mechanical_horse_cue_gallop = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON | B_BUTTON | DPAD_RIGHT | DPAD_LEFT | DPAD_UP | DPAD_DOWN),
    /* Total Duration  */ 0x0C,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ mechanical_horse_cue_spawn,
    /* Spawn Parameter */ HORSE_LESSON_4_GALLOP,
    /* Func. Update    */ mechanical_horse_cue_update,
    /* Func. Despawn   */ mechanical_horse_cue_despawn,
    /* Func. Hit       */ mechanical_horse_cue_hit,
    /* Func. Barely    */ mechanical_horse_cue_barely,
    /* Func. Miss      */ mechanical_horse_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e9050] Cue Definition Index
struct CueDefinition *mechanical_horse_cue_index[] = {
    /* 0x00 */ &mechanical_horse_cue_walk,
    /* 0x01 */ &mechanical_horse_cue_trot,
    /* 0x02 */ &mechanical_horse_cue_canter,
    /* 0x03 */ &mechanical_horse_cue_gallop,
    /* 0x04 */ NULL,
    /* 0x05 */ NULL,
    /* 0x06 */ NULL,
    /* 0x07 */ NULL,
    /* 0x08 */ NULL,
    /* 0x09 */ NULL,
    /* 0x0A */ NULL,
    /* 0x0B */ NULL,
    END_OF_CUE_INDEX
};


  //  //  //  GAME ENGINE DATA  //  //  //


// [D_089e9084] Common Events
EngineEvent mechanical_horse_common_events[] = {
    /* BEAT_ANIMATION */ mechanical_horse_common_beat_animation,
    /* DISPLAY_TEXT   */ mechanical_horse_common_display_text,
    /* INIT_TUTORIAL  */ // None
    END_OF_COMMON_EVENT_LIST
};

// [D_089e9090] Engine Events
EngineEvent mechanical_horse_engine_events[] = {
    /* 0x00 */ func_08041444,
    /* 0x01 */ func_080415c0,
    /* 0x02 */ func_080416cc,
    /* 0x03 */ func_08041730,
    /* 0x04 */ func_08041744,
    /* 0x05 */ func_080417ac,
    /* 0x06 */ func_080424f0,
    /* 0x07 */ func_08042504
};

// [D_089e90b0] Mechanical Horse Game Engine
struct GameEngine mechanical_horse_engine = {
    /* Size in Memory */ sizeof(struct MechanicalHorseEngineData),
    /* Start Engine   */ mechanical_horse_engine_start,
    /* Update Engine  */ mechanical_horse_engine_update,
    /* Stop Engine    */ mechanical_horse_engine_stop,
    /* Cue Index      */ mechanical_horse_cue_index,
    /* Common Events  */ mechanical_horse_common_events,
    /* Engine Events  */ mechanical_horse_engine_events,
    /* Input Event    */ mechanical_horse_input_event
};