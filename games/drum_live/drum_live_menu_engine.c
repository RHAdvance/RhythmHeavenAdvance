#include "engines/drum_live_menu.h"


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e5c40] Buffered Textures List
struct CompressedData *drum_live_menu_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e5c44] Graphics Table
struct GraphicsTable drum_live_menu_gfx_table[] = {
    /* OBJ Tileset */ {
        /* Src.  */ &drum_live_menu_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ drum_live_menu_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ drum_live_menu_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e5c74] Poster Descriptions
const char *drum_live_menu_poster_desc[] = {
    /* DRUM GIRLS */
    "\x03\x31" "\x01\x6d" "\x05\x30" "\x01\x34" "Drum Girls LIVE!\n"
    "\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "♪　Night Walk\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "♪　Space Dance\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "♪　Honey Sweet Angel of Love\n"
    "\n",
    
    /* DRUM BOYS  */
    "\x03\x31" "\x01\x6d" "\x05\x30" "\x01\x34" "Drum Boys LIVE!\n"
    "\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "♪　The Clappy Trio\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "♪　Tap Trial\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "♪　WISH - Can't Wait For You\n"
    "\n",

    /* DRUM BAND  */
    "\x03\x31" "\x01\x6d" "\x05\x30" "\x01\x34" "Samurai Drummer's\n"
    "\x03\x31" "\x01\x6d" "\x05\x30" "\x01\x34" "\x01\x52" "Band LIVE! \n"
    "\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "\x01\x4c" "♪　Cosmic Dance\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "♪　The Snappy Trio\n"
    "\x03\x30" "\x01\x73" "\x05\x31" "\x01\x35" "♪　Tap Trial 2\n"
    "\n"
};


  //  //  //  CUE DATA  //  //  //


// [D_089e5c80] Cue 00 (Default)
struct CueDefinition drum_live_menu_cue_default = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x02, 0x02,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ 0x4,
    /* Func. Spawn     */ drum_live_menu_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ drum_live_menu_cue_update,
    /* Func. Despawn   */ drum_live_menu_cue_despawn,
    /* Func. Hit       */ drum_live_menu_cue_hit,
    /* Func. Barely    */ drum_live_menu_cue_barely,
    /* Func. Miss      */ drum_live_menu_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e5cc0] Cue Definition Index
struct CueDefinition *drum_live_menu_cue_index[] = {
    /* 0x00 */ &drum_live_menu_cue_default,
    /* 0x01 */ NULL,
    /* 0x02 */ NULL,
    /* 0x03 */ NULL,
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


// [D_089e5cf4] Common Events
EngineEvent drum_live_menu_common_events[] = {
    /* BEAT_ANIMATION */ drum_live_menu_common_beat_animation,
    /* DISPLAY_TEXT   */ drum_live_menu_common_display_text,
    /* INIT_TUTORIAL  */ drum_live_menu_common_init_tutorial,
    END_OF_COMMON_EVENT_LIST
};

// [D_089e5d04] Engine Events
EngineEvent drum_live_menu_engine_events[] = {
    /* 0x00 */ func_08036f94,
    /* 0x01 */ drum_live_menu_engine_event_stub
};

// [D_089e5d0c] LIVE Menu Game Engine
struct GameEngine drum_live_menu_engine = {
    /* Size in Memory */ sizeof(struct DrumLiveMenuEngineData),
    /* Start Engine   */ drum_live_menu_engine_start,
    /* Update Engine  */ drum_live_menu_engine_update,
    /* Stop Engine    */ drum_live_menu_engine_stop,
    /* Cue Index      */ drum_live_menu_cue_index,
    /* Common Events  */ drum_live_menu_common_events,
    /* Engine Events  */ drum_live_menu_engine_events,
    /* Input Event    */ drum_live_menu_input_event
};
