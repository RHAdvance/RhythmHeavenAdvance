#pragma once

#include "global.h"
#include "engines.h"

#include "games/rat_race/graphics/rat_race_graphics.h"

// Engine Types:
struct Rat {
    s16 ratSprite;
    s16 sweatSprite;
    u8 unk4;
    u8 unk5;
    u32 unk8;
    u32 unkC;
};

struct RatRaceElement {
u16 unk0;
u8 active;
u8 pad[0x5];
};

struct RatRaceEngineData {
    u8 version;
    u8 pad1[0xF];
    u8 unk10;
    u8 pad2[0x7];
    u32 unk18;
    s8 unk1C;
    u8 pad3[0x3];
    s32 unk20;
    u32 unk24;
    u32 unk28;
    u8 unk2C;
    u8 pad4[0x3];
    u32 unk30;
    u32 unk34;
    u8 pad5[0x34];
    u16 unk6C;
    u8 pad6[0x2];
    u32 unk70;
    u16 cat_pupils_sprite;
    u16 cat_eyelids_sprite;
    u16 cat_paw_sprite;
    u16 cat_paw2_sprite;
    u8 unk7C;
    u8 pad7[0x3];
    u32 unk80;
    s32 unk84;
    u8 pad8[0x4A];
    u8 unkD2;
    u8 pad9[0x7];
    u8 unkDA;
    u8 pad10[0xD];
    u32 unkE8;
    struct RatRaceElement element[6];
    u8 unk11C;
    u8 unk11D;
    u8 unk11E;
    u8 pad11[0x1];
};

struct RatRaceCue {
    /* add fields here */
};


// Engine Data:
extern const char D_0805a8b4[];


// Engine Definition Data:
extern struct CompressedData *rat_race_buffered_textures[];
extern struct GraphicsTable rat_race_gfx_table[];
extern u32 D_089e66bc[];
extern u8 D_089e6834[];
extern u8 D_089e684c[];
extern struct Rat rat_race_init_rat_data[];
extern s32 D_089e68ac[];


// Functions:
extern void rat_race_init_gfx3(void); // Graphics Init. 3
extern void rat_race_init_gfx2(void); // Graphics Init. 2
extern void rat_race_init_gfx1(void); // Graphics Init. 1
extern void rat_race_engine_start(u32 version); // Game Engine Start
extern void rat_race_engine_event_stub(); // Engine Event 00 (STUB)
extern void func_0803a158(); // Engine Event 02 (?)
// extern ? func_0803a164(?);
// extern ? func_0803a198(?);
extern void func_0803a1d4(); // Engine Event 09 (?)
extern void func_0803a1e4(); // Engine Event 0A (?)
extern void func_0803a1f8(); // Engine Event 03 (?)
extern void func_0803a204(); // Engine Event 04 (?)
// extern ? func_0803a230(?);
extern void func_0803a2a8(); // Engine Event 06 (?)
extern void func_0803a350(); // Engine Event 07 (?)
extern void func_0803a3b8(); // Engine Event 08 (?)
// extern ? func_0803a3c4(?);
extern void func_0803a41c(); // Engine Event 0C (?)
extern void func_0803a434(); // Engine Event 0F (?)
extern void rat_race_engine_update(void); // Game Engine Update
extern void func_0803a47c(); // Engine Event 11 (?)
extern void func_0803a490(); // Engine Event 12 (?)
extern void rat_race_engine_stop(void); // Game Engine Stop
// extern ? func_0803a4a8(?);
extern void rat_race_cue_spawn_stop(struct Cue *, struct RatRaceCue *, u32 param); // Cue - Spawn (Stop)
extern u32  rat_race_cue_update_stop(struct Cue *, struct RatRaceCue *, u32 runningTime, u32 duration); // Cue - Update (Stop)
extern void rat_race_cue_despawn_stop(struct Cue *, struct RatRaceCue *); // Cue - Despawn (Stop)
extern void rat_race_cue_spawn_dash(struct Cue *, struct RatRaceCue *, u32 param); // Cue - Spawn (Dash)
extern u32  rat_race_cue_update_dash(struct Cue *, struct RatRaceCue *, u32 runningTime, u32 duration); // Cue - Update (Dash)
extern void rat_race_cue_despawn_dash(struct Cue *, struct RatRaceCue *); // Cue - Despawn (Dash)
extern void rat_race_cue_hit_stop(struct Cue *, struct RatRaceCue *, u32 pressed, u32 released); // Cue - Hit (Stop)
extern void rat_race_cue_hit_dash(struct Cue *, struct RatRaceCue *, u32 pressed, u32 released); // Cue - Hit (Dash)
extern void rat_race_cue_barely(struct Cue *, struct RatRaceCue *, u32 pressed, u32 released); // Cue - Barely
extern void rat_race_cue_miss(struct Cue *, struct RatRaceCue *); // Cue - Miss
extern void rat_race_input_event(u32 pressed, u32 released); // Input Event
extern void rat_race_common_beat_animation(void); // Common Event 0 (Beat Animation, Unimplemented)
extern void rat_race_common_display_text(void); // Common Event 1 (Display Text, Unimplemented)
extern void rat_race_common_init_tutorial(struct Scene *); // Common Event 2 (Init. Tutorial)
// extern ? func_0803a678(?);
extern void func_0803a798(u32 param); // Engine Event 05 (?)
// extern ? func_0803a8e4(?);
extern void func_0803aa58(); // Engine Event 0B (?)
// extern ? func_0803aa9c(?);
// extern ? func_0803aba4(?);
extern void func_0803ac98(); // Engine Event 0D (?)
extern void func_0803ad50(); // Engine Event 10 (?)
// extern ? func_0803ad60(?);
// extern ? func_0803aef4(?);
extern void func_0803b034(); // Engine Event 01 (?)
// extern ? func_0803b1ac(?);
// extern ? func_0803b1e8(?);
// extern ? func_0803b230(?);
// extern ? func_0803b258(?);
// extern ? func_0803b37c(?);
// extern ? func_0803b924(?);
// extern ? func_0803b9fc(?);
// extern ? func_0803baa0(?);
// extern ? func_0803baf8(?);
// extern ? func_0803bb2c(?);
// extern ? func_0803bbd8(?);
// extern ? func_0803bc08(?);
// extern ? func_0803bc40(?);
extern void func_0803bc98(); // Engine Event 0E (?)
// extern ? func_0803bd0c(?);
// extern ? func_0803bd58(?);
