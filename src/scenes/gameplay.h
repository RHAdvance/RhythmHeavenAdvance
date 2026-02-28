#pragma once

#include "global.h"
#include "scenes.h"
#include "engines.h"
#include "src/main.h"
#include "riq_main_scene.h"

// Scene Macros/Enums:


// Scene Types:
struct GameplaySceneData {
	s32 unk0;
	s32 unk4;
	u8 playInputsEnabled; // A, B, +, L, R
	u8 assessIrrelevantInputs; // Register inputs with no relevant cue.
    u16 buttonPressFilter;
	u16 buttonReleaseFilter;
	const struct GameEngine *gameEngine; // Game Engine Pointer
	void *gameEngineData; // Same value as gCurrentEngineData
	struct Cue *cues; // Linked List (most recent element)
	const struct CueDefinition *cueDefinitions[12]; // Cue Definitions (copied from Game Engine)
	EngineEvent commonFunctions[3]; // Engine "Common" Functions
	struct Cue *currentCue; // Current Cue
	u8 cueSpawnsEnabled;
    u8 cancelThisCueSpawning;
    u8 allowCueInputOverlap; // If multiple cues for the same input overlap, register the input for all cues (otherwise only consider the most relevant cue).
    s32 engineFuncParam; // Parameter used when calling Engine-specific Functions
    u8 unk64;
	struct SongHeader *nextCueSpawnSfx;
	struct SongHeader *nextCueHitSfx;
	struct SongHeader *nextCueBarelySfx;
	struct SongHeader *nextCueMissSfx;
	u8 ignoreThisCueResult;
    s8 lastCueInputOffset; // Most Recent Input Timing Offset (how early/late the most recent input was)
	u8 currentMarkingCriteria; // Current Marking Criteria
	u8 isTutorial;
	u8 skippingTutorial; // Currently changing scenes.
	struct Scene *skipDestination; // Skip Tutorial destination scene
	u16 fadeInTicks; // Remaining ticks for screen fade-in?
    u16 nextCueDuration;
    u16 loopCounter;
    u16 loopCounterStart;
    s16 pauseSprite;
    s16 pauseOptionsSprite;
    u8 unpausing; // Pause Menu is currently being exited.
    u8 currentPauseOption;
    u32 paletteBuffer[0x100]; // Palette Buffer
    s16 skipTutorialSprite;
    s16 aButtonSprite;
    struct TextPrinter *textPrinter;
    u8  pausedAtTextBox;
    u8  printingTutorialText;
    u16 textButtonPressFilter;
    u16 textButtonReleaseFilter;
    s16 perfectSprite;
    u8  goingForPerfect;
    u8  assessPerfectInputs;
    u8  perfectFailed;
    u8  missPunishmentTimer;
    u8  missPunishmentInterval;
    s8  earlinessRangeMax; // Input Timing Window Duration - Early, Max.
    s8  latenessRangeMin; // Input Timing Window Duration - Late, Min.
    s8  earlinessRangeMin; // Input Timing Window Duration - Early, Min.
    s8  latenessRangeMax; // Input Timing Window Duration - Late, Max.
    u16 sfxTempo; // Assumed original tempo of any sound effect played.
    u16 skipTutorialButton; // Button filter for skipping tutorials.
    s32 interEngineVariableSpace[64];
    u8  dpadCannotOverlap;
    u8  dpadIsOpen;
    u8  dpadClosedTimer;
    u8  mercyEnabled;
    u8  forgivableMisses;
    u8  autoplayEnabled;
};


// Sound Effects:
extern struct SongHeader s_f_pause_quit_seqData;


// Scene Data:
extern struct GraphicsTable gameplay_common_gfx_table[]; // Graphics Table (Common Gameplay Graphics/Palettes, e.g. Pause Menu)
extern struct CompressedData *gameplay_common_buffered_textures[]; // Buffered Textures List
extern struct PauseMenuDefinition gameplay_pause_menu_data; // Pause Handler Definition
extern struct Animation *gameplay_text_adv_icons[2]; // A Button Prompt Animations { 0 = Black; 1 = White }


// Functions - Audio:
extern void gameplay_set_sound_tempo(u32 tempo); // [func_08016e04] Define Sound Effect Base Tempo
extern struct SoundPlayer *gameplay_align_soundplayer_to_tempo(struct SoundPlayer *player); // [func_08016e18] Match SoundPlayer to Current Tempo
extern struct SoundPlayer *gameplay_play_sound(struct SongHeader *sfx); // [func_08016e54] Play Sound
extern struct SoundPlayer *gameplay_play_sound_in_player(u32 player, struct SongHeader *sfx); // [func_08016e64] Play Sound
extern struct SoundPlayer *gameplay_play_sound_w_pitch_volume(struct SongHeader *sfx, u32 volume, u32 pitch); // [func_08016e74] Play Sound
extern struct SoundPlayer *gameplay_play_sound_in_player_w_pitch_volume(u32 player, struct SongHeader *sfx, u32 volume, s32 pitch); // [func_08016e84] Play Sound

// Functions - Scene:
extern void gameplay_init_scene_static_var(void); // [func_08016e94] Initialise Static Variables
extern void gameplay_init_gfx1(void); // [func_08016ea4] Graphics Init. 1
extern void gameplay_start_scene(void); // [func_08016ec4] Scene Start
extern void gameplay_update_paused_scene(void); // [func_08016ffc] Scene Update (Paused)
extern void gameplay_update_scene(void); // [func_08017000] Scene Update (Active)
extern u32  gameplay_inputs_are_enabled(void); // [func_0801714c] Check if Play Inputs are Enabled
extern void gameplay_clear_palette_buffer(Palette buffer); // [func_08017168] Clear Secondary Palette Buffer (loaded to D_03004b10.unk858)
extern void gameplay_set_current_engine(const struct GameEngine *engine, u32 version); // [func_08017188] Load New Engine
extern void *gameplay_get_engine_data(void); // [func_0801732c] Get Current Game Engine Data
extern void gameplay_set_input_buttons(u16 press, u16 release); // [func_08017338] Set Input Button Filters
extern s32  gameplay_run_common_event(s32 param, s32 id); // [func_08017348] Run Engine-Common Event
extern void gameplay_set_engine_event_param(s32 param); // [func_08017380] Set Parameter for Engine-Specific Event
extern s32  gameplay_run_engine_event(const struct GameEngine *engine, s32 id); // [func_0801738c] Run Engine-Specific Event
extern void gameplay_inputs_enabled(u32 enable); // [func_080173c4] Enable Play Inputs
extern void gameplay_assess_irrelevant_inputs(u32 assess); // [func_080173d0] Assess Non-Cue Inputs
extern void gameplay_set_next_cue_spawn_sfx(struct SongHeader *sfx); // [func_080173dc] Set Next Cue Spawn SFX
extern void gameplay_set_next_cue_hit_sfx(struct SongHeader *sfx); // [func_080173e8] Set Next Cue Hit SFX
extern void gameplay_set_next_cue_barely_sfx(struct SongHeader *sfx); // [func_080173f4] Set Next Cue Barely SFX
extern void gameplay_set_next_cue_miss_sfx(struct SongHeader *sfx); // [func_08017400] Set Next Cue Miss SFX
extern void gameplay_force_stop_music_midi_track(s32 midiTrack); // [func_0801740c] Force-Stop Music MIDI Track
extern void gameplay_enable_tutorial(u32 isTutorial); // [func_08017448] Set isTutorial
extern void gameplay_set_skip_destination(struct Scene *scene); // [func_08017458] Set skipDestination
extern void gameplay_set_skip_button(u32 buttons); // [func_08017468] Set Skip Tutorial Button
extern void gameplay_set_tutorial(struct Scene *scene); // [func_0801747c] Set Skip Destination (i.e. if Select is pressed in a tutorial)
extern void gameplay_display_skip_icon(u32 corner); // [func_080174e8] Display Skip Tutorial Icon
extern void gameplay_skip_tutorial(void); // [func_08017514] Skip Tutorial
extern void gameplay_set_screen_fade_in_time(u32 duration); // [func_08017568] Set Screen Fade-In
extern void gameplay_start_screen_fade_in(void); // [func_08017578] Fade-In Screen
extern void gameplay_set_initial_counter_value(u32 count); // [func_080175a0] Set Initial Loop Counter Value
extern void gameplay_reset_loop_counter(void); // [func_080175b0] Reset Loop Counter
extern void gameplay_increment_loop_counter(void); // [func_080175c4] Increment Loop Counter
extern u32  gameplay_get_loop_counter(void); // [func_080175d8] Get Loop Counter
extern void gameplay_set_reverb(u32 level); // [func_080175e8] Set Global Reverb
extern void gameplay_start_perfect_campaign(void); // [func_08017604] Start Perfect Campaign
extern void gameplay_check_for_perfect(u32 assessInputs); // [func_08017648] Start/Stop Assessing Inputs for Perfect Campaign
extern void gameplay_register_imperfect_input(void); // [func_0801765c] Register Imperfect Input
extern void gameplay_register_perfect_input(void); // [func_080176cc] Register Perfect Input
extern s32  gameplay_run_engine_event_w_param(const struct GameEngine *engine, u32 function, s32 param); // [func_08017728] Run Game Engine Event (convenience method)
extern void gameplay_set_miss_punishment_duration(u32 duration); // [func_08017744] Set Miss Punishment Interval
extern void gameplay_set_inter_engine_variable(u32 i, s32 val); // [func_08017758] Set Inter-Engine Variable
extern s32  gameplay_get_inter_engine_variable(u32 i); // [func_0801777c] Get Inter-Engine Variable
extern void gameplay_prevent_dpad_overlap(u32 preventOverlap); // [func_080177a4] Set D-Pad Input Overlap Handling
extern void gameplay_enable_mercy(u32 enable); // [func_080177c8] Enable Mercy
extern void gameplay_set_mercy_count(u32 total); // [func_080177dc] Set Total Forgivable Misses
extern void gameplay_stop_scene(void); // [func_080177f0] Scene Stop

// Functions - Cues:
extern void gameplay_reset_cues(void); // [func_080178ac] Reset All Cue Data
extern void gameplay_init_cues(void); // [func_080178e4] Init. All Cues
extern void gameplay_set_marking_criteria(u32 criteria); // [func_08017908] Set Current Marking Criteria
extern u32  gameplay_get_marking_criteria(void); // [func_08017918] Get Current Marking Criteria
extern void gameplay_add_cue_result(u32 markingCriteria, u32 cueResult, s32 timingOffset); // [func_08017928] Register Cue Result
extern void gameplay_add_cue_result_hit(s32 offset); // [func_080179a0] Add Input Hit
extern void gameplay_add_cue_result_barely(s32 offset); // [func_080179bc] Add Input Barely
extern void gameplay_add_cue_result_miss(s32 offset); // [func_080179d8] Add Input Miss
extern void gameplay_spawn_cue(s32 id); // [func_080179f4] Spawn Cue
extern void gameplay_cancel_this_cue_spawn(void); // [func_08017b34] Request Scene to Delete the Currently-Spawning Cue
extern void gameplay_despawn_cue(struct Cue *cue); // [func_08017b44] Despawn Cue
extern void gameplay_enable_cue_spawning(u32 enable); // [func_08017b88] Enable Cue Spawning
extern void gameplay_update_cue(struct Cue *cue); // [func_08017b98] Update Cue
extern void gameplay_update_all_cues(void); // [func_08017c68] Update All Cues
extern s32  gameplay_calculate_input_timing(struct Cue *cue, u16 pressed, u16 released, s32 *offset); // [func_08017c8c] Determine Input Timing
extern void gameplay_register_hit_barely(struct Cue *cue, s32 timingLevel, s32 offset, u32 pressed, u32 released); // [func_08017e2c] Hit/Barely Event
extern void gameplay_update_inputs(u32 pressed, u32 released); // [func_08017ec8] Update Inputs
extern s32  gameplay_get_last_hit_offset(void); // [func_08018054] Get Timing Offset of Most Recent Hit/Barely
extern void gameplay_ignore_this_cue_result(void); // [func_08018068] Prevent Scene from Updating Results for This Cue
extern void gameplay_enable_cue_input_overlap(u32 allow); // [func_08018078] Allow Cue Input Overlap
extern void gameplay_set_cue_spawn_sfx(struct Cue *cue, struct SongHeader *sfx); // [func_08018088] Set Cue Spawn SFX
extern void gameplay_set_cue_hit_sfx(struct Cue *cue, struct SongHeader *sfx); // [func_0801808c] Set Cue Hit SFX
extern void gameplay_set_cue_barely_sfx(struct Cue *cue, struct SongHeader *sfx); // [func_08018090] Set Cue Barely SFX
extern void gameplay_set_cue_miss_sfx(struct Cue *cue, struct SongHeader *sfx); // [func_08018094] Set Cue Miss SFX
extern struct SongHeader *gameplay_get_cue_spawn_sfx(struct Cue *cue); // [func_08018098] Get Cue Spawn SFX
extern struct SongHeader *gameplay_get_cue_hit_sfx(struct Cue *cue); // [func_0801809c] Get Cue Hit SFX
extern struct SongHeader *gameplay_get_cue_barely_sfx(struct Cue *cue); // [func_080180a0] Get Cue Barely SFX
extern struct SongHeader *gameplay_get_cue_miss_sfx(struct Cue *cue); // [func_080180a4] Get Cue Miss SFX
extern u32  gameplay_get_cue_unk0(struct Cue *cue); // [func_080180a8] Get Cue Data unk0
extern u32  gameplay_get_cue_input_buttons(struct Cue *cue); // [func_080180ac] Get Cue Input Buttons
extern void gameplay_set_cue_input_buttons(struct Cue *cue, u32 buttons); // [func_080180b0] Set Cue Input Buttons
extern void gameplay_set_cue_duration(struct Cue *cue, u32 duration); // [func_080180b4] Set Cue Duration
extern u32  gameplay_get_cue_marking_criteria(struct Cue *cue); // [func_080180bc] Get Cue Marking Criteria
extern void gameplay_set_cue_hit_window(s32 time); // [func_080180c4] Set Cue Hit Window
extern void gameplay_set_cue_barely_window(s32 time); // [func_080180ec] Set Cue Barely Window
extern void gameplay_set_next_cue_duration(u32 duration); // [func_08018114] Set Next Cue Duration
extern void gameplay_get_cue_info(struct Cue **cue, void **info); // [func_08018124] Get Cue and GameCueInfo
extern void gameplay_get_previous_cue_info(struct Cue *cue, struct Cue **prev, void **info); // [func_08018138] Get Previous Cue and GameCueInfo

// Functions - Video:
extern void gameplay_init_overlay(void); // [func_08018154] Initialise Common Graphics (Perfect Campaign, etc.)
extern void gameplay_pause_menu_set_quit_destination(struct Scene *scene); // [func_080182ac] Set D_03001328
extern void gameplay_pause_menu_darken_screen(void); // [func_080182b8] Screen Darken (Pause)
extern void gameplay_pause_menu_lighten_screen(void); // [func_08018318] Screen Lighten (Unpause)
extern void gameplay_start_pause_menu(void); // [func_08018344] Open Pause Menu
extern s32  gameplay_update_pause_menu(void); // [func_080183c8] Update Pause Menu
extern void gameplay_init_pause_menu(void); // [func_08018524] Initialise Pause Handler
extern void gameplay_set_skip_icon(u32 corner, u32 show); // [func_0801853c] Set Skip Tutorial Icon Display
extern void gameplay_set_text_advance_icon(u32 style); // [func_0801858c] Set Text Button Style
extern void gameplay_display_text_advance_icon(s16 x, s16 y, s32 show); // [func_080185d0] Display A Button Prompt
extern void gameplay_set_text_printer(struct TextPrinter *textPrinter); // [func_08018630] Init. Text
extern void gameplay_display_text(const char *text); // [func_08018660] Display Text
extern void gameplay_align_text_advance_icon(void); // [func_08018698]
extern void gameplay_display_text_and_wait(void); // [func_080186d4]
extern void gameplay_update_text(void); // [func_0801875c] Update Text
extern void gameplay_set_text_x(s32 x); // [func_08018828] Set Text X Position
extern void gameplay_set_text_y(s32 y); // [func_0801884c] Set Text Y Position
extern void gameplay_set_text_z(u16 z); // [func_08018870] Set Text Z Position (Sprite Depth/Layer)
