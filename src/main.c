#include "main.h"
#include "memory.h"
#include "code_08003b28.h"
#include "bitmap_font.h"
#include "memory_heap.h"

extern u8 haveSeenDisclaimer;


static struct Scene *gCurrentScene;
static struct Scene *gNextScene;
static struct SceneTransition gSceneTrans[10];
static u8 D_03000080;
static struct Scene *D_03000084;
static s32 D_03000088;

static u8 sIsBadFlashCart = 0;

// Default Interrupt Procedure (Do Nothing)
void interrupt_default(void) {
}


// Initialise Scenes (Init. Static Variables)
void init_scene_static_var(void) {
	game_select_scene_init_memory();
	score_results_scene_init_memory();
	main_menu_scene_init_memory();
	gameplay_init_scene_static_var();
	arrival_scene_init_memory();
	dataroom_scene_init_memory();
	studio_scene_init_memory();
	medal_corner_scene_init_memory();
	cafe_scene_init_memory();
}


void func_08000224(void) {
	init_key_listener();
	init_time_keeper();
	init_fast_udivsi3();
	init_math_sqrt();
	mem_heap_init(get_memory_heap_start(), get_memory_heap_length());
	task_pool_init();
	func_08003e64();
	func_08003f28();
	func_080073b8();
	func_080073f0();
	text_printer_init();
	func_0800861c();
	init_save_buffer();
	if (copy_sram_to_save_buffer() != 0) {
		if (copy_sram_backup_to_save_buffer() != 0) {
			clear_save_data();
		} else {
			flush_save_buffer_to_sram();
		}
	}
#ifdef PLAYTEST
	set_playtest_save_data();
#endif
	flush_save_buffer_to_sram_backup();
	
	// Initialize disclaimer flag from save data
	if (CHECK_ADVANCE_FLAG(D_030046a8->data.advanceFlags, ADVANCE_FLAG_SEEN_DISCLAIMER)) {
		haveSeenDisclaimer = TRUE;
	}
	
	set_sound_mode(D_030046a8->data.unk294[8]); // Set DirectSound Mode (Stereo/Mono)
	set_scene_object_current_text_id(scene_get_default_text_id());
	init_scene_static_var();
	func_08001360();
	func_08009150();
	func_080091d8();
	D_03004498 = TRUE;
}


void agb_main(void) {
	REG_WAITCNT = (WAITCNT_SRAM_8
		| WAITCNT_WS0_N_3 | WAITCNT_WS0_S_1
		| WAITCNT_WS1_N_3 | WAITCNT_WS1_S_1
		| WAITCNT_WS2_N_3 | WAITCNT_WS2_S_1
		| WAITCNT_PHI_OUT_NONE | WAITCNT_PREFETCH_ENABLE | WAITCNT_TYPE_GBA);

    // Clear RAM
	DmaFill32(3, 0, ExternWorkRAMBase, 0x40000);
	DmaFill32(3, 0, InternWorkRAMBase, 0x7E00);

    // Set up interrupt handler
	DmaCopy32(3, &interrupt_handler_rom, &interrupt_handler, 0x200);
	DmaCopy32(3, &interrupt_handler_jtbl_rom, &interrupt_handler_jtbl, 0x38);
	REG_INTERRUPT = &interrupt_handler;

    // Clear VRAM
	DmaFill32(3, 0, VRAMBase, 0x18000);
	*(u16 *)PaletteRAMBase = 0x7FFF;

	REG_DISPCNT = 0;
	REG_IME = 0;

	D_03004498 = FALSE;

	init_ewram();
	func_08000224();
	debug_menu_scene_init_memory();
	midi_sound_init(); // Init. MIDI Sound Library
	midi_player_set_reverb(35, 2, 2, 4);
	set_sound_mode(D_030046a8->data.unk294[8]); // Set DirectSound Mode (Stereo/Mono)

	REG_DISPSTAT = 8;
	REG_IE = (INTERRUPT_CART | INTERRUPT_DMA2 | INTERRUPT_TIMER3 | INTERRUPT_VBLANK);
	REG_IF = 0xFFFF;
	REG_IME = 1;

	func_0801d860(FALSE); // Init. Script Operator (Init. Static Variables)
	init_scenes(&scene_warning);
	set_scene_trans_target(&scene_warning, &scene_disclaimer);
	set_scene_trans_target(&scene_disclaimer, &scene_title);
	update_key_listener();

	while (TRUE) {
		func_080013a8();
		get_agb_random_var();
		update_key_listener();
		D_030046a0 += 1;
		process_scenes();

		if (D_03004498) {
			u16 keysPressed = ~REG_KEY;

			if ((keysPressed & RESET_BUTTON_COMBO) == RESET_BUTTON_COMBO) {
				key_rec_set_mode(0, 0x3ff, 0, 0);
				set_current_scene(&scene_soft_reset);
				func_08009548();
				D_03004498 = FALSE;
			}
		}

		midi_sound_main();
		update_time_keeper();
		func_08003ff0();
	}
}


// Initialise Scene Handling
void init_scenes(struct Scene *initial) {
	gCurrentScene = NULL;
	gNextScene = initial;
	gCurrentSceneData = NULL;
	clear_scene_trans();
}


// Update Scene Handling
void process_scenes(void) {
	if (gCurrentScene != NULL) {
		if (gCurrentScene->loopFunc != NULL) {
            // Update Scene
            u32 sceneEnded = gCurrentScene->loopFunc(gCurrentScene->loopParam);

            if (sceneEnded) {
                // Close Scene
                if (gCurrentScene->endFunc != NULL) {
                    gCurrentScene->endFunc(gCurrentScene->endParam);
                }
                if (gCurrentSceneData != NULL) {
                    mem_heap_dealloc(gCurrentSceneData);
                }

                gCurrentSceneData = NULL;
                gNextScene = get_scene_trans_target(gCurrentScene);

                if (D_03000080) {
                    set_scene_trans_target(gCurrentScene, D_03000084);
                    set_scene_trans_var(gCurrentScene, D_03000088);
                } else {
                    dealloc_scene_trans(gCurrentScene);
                }

                gCurrentScene = NULL;
            }
        }
	} else {
        // Initialise Next Scene
		if (gNextScene == NULL) {
			gNextScene = D_08935fb0;
		}

		gCurrentScene = gNextScene;
		gNextScene = NULL;
		D_03000080 = FALSE;

		if (gCurrentScene->requiredMemory != 0) {
			gCurrentSceneData = mem_heap_alloc(gCurrentScene->requiredMemory);
		}

		if (gCurrentScene->initFunc != NULL) {
			gCurrentScene->initFunc(gCurrentScene->initParam);
		}
	}
}


// Set Scene
void set_current_scene(struct Scene *initial) {
	gCurrentScene = NULL;
	gNextScene = initial;
	clear_scene_trans();
}


// Set Next Scene (Transition on Script End)
void set_next_scene(struct Scene *next) {
	set_scene_trans_target(gCurrentScene, next);
}


// Clear Transitions
void clear_scene_trans(void) {
	u32 i;

	for (i = 0; i < ARRAY_COUNT(gSceneTrans); i++) {
		gSceneTrans[i].initial = NULL;
		gSceneTrans[i].target = NULL;
		gSceneTrans[i].variable = 0;
	}
}


// Get Transition Data
struct SceneTransition *get_scene_trans(struct Scene *scene) {
	u32 i;

	for (i = 0; i < ARRAY_COUNT(gSceneTrans); i++) {
		if (gSceneTrans[i].initial == scene) {
			return &gSceneTrans[i];
		}
	}

	return NULL;
}


// Get Transition Next Scene
struct Scene *get_scene_trans_target(struct Scene *scene) {
	struct SceneTransition *transData = get_scene_trans(scene);

	if (transData == NULL) {
		return NULL;
	}

	return transData->target;
}


// Get Transition Variable
s32 get_scene_trans_var(struct Scene *scene) {
	struct SceneTransition *transData = get_scene_trans(scene);

	if (transData == NULL) {
		return 0;
	}

	return transData->variable;
}


// Get Transition Next Scene for Current
struct Scene *get_current_scene_trans_target(void) {
	return get_scene_trans_target(gCurrentScene);
}


// Get Transition Variable for Current
s32 get_current_scene_trans_var(void) {
	return get_scene_trans_var(gCurrentScene);
}


// Allocate Transition Data
struct SceneTransition *alloc_scene_trans(struct Scene *scene) {
	u32 i;

	if (scene == NULL) {
		return NULL;
	}

	for (i = 0; i < ARRAY_COUNT(gSceneTrans); i++) {
		if (gSceneTrans[i].initial == NULL) {
			gSceneTrans[i].initial = scene;
			gSceneTrans[i].target = NULL;
			gSceneTrans[i].variable = 0;
			return &gSceneTrans[i];
		}
	}

	return NULL;
}


// Deallocate Transition Data
void dealloc_scene_trans(struct Scene *scene) {
    u32 i;

	if (scene == NULL) {
	    return;
	}

    for (i = 0; i < ARRAY_COUNT(gSceneTrans); i++) {
        if (gSceneTrans[i].initial == scene) {
            gSceneTrans[i].initial = NULL;
            gSceneTrans[i].target = NULL;
            gSceneTrans[i].variable = 0;
        }
    }
}


// Set Transition Next Scene
void set_scene_trans_target(struct Scene *scene, struct Scene *target) {
	struct SceneTransition *transData;

	if (((transData = get_scene_trans(scene)) != NULL) || ((transData = alloc_scene_trans(scene)) != NULL)) {
		transData->target = target;
	}
}


// Set Transition Variable
void set_scene_trans_var(struct Scene *scene, s32 variable) {
	struct SceneTransition *transData;

	if (((transData = get_scene_trans(scene)) != NULL) || ((transData = alloc_scene_trans(scene)) != NULL)) {
		transData->variable = variable;
	}
}


// Set ? Scene Transition
void func_080006f0(struct Scene *target, s32 variable) {
	D_03000080 = TRUE;
	D_03000084 = target;
	D_03000088 = variable;
}


// Get Current Scene
struct Scene *get_current_scene(void) {
	return gCurrentScene;
}

// basically swidelay from the DS
void delay_loop(u32 count) {
	__asm__ volatile (
		"1:\n"
		"sub %0, %0, #1\n"
		"bne 1b\n"
		: "+r" (count)
		:
		: "cc", "memory"
	);
}

void flash_check(void) {
	const char data[] = {
		0x77, 0x65, 0x20, 0x64, 0x6F, 0x6E, 0x74, 0x20, 0x73, 0x75, 0x70, 0x70,
		0x6F, 0x72, 0x74, 0x20, 0x63, 0x68, 0x65, 0x61, 0x70, 0x20, 0x62, 0x6F,
		0x6F, 0x74, 0x6C, 0x65, 0x67, 0x20, 0x20, 0x20, 0x66, 0x6C, 0x61, 0x73,
		0x68, 0x63, 0x61, 0x72, 0x74, 0x73, 0x2C, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x74, 0x68, 0x69, 0x65, 0x66, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	GBAROM[0xC0] = 33;
	delay_loop(1000);

	// really low quality flashcart - warn the user
	if(GBAROM[0xC0] != 0) {
		GBAROM[0xC0] = 0;
		sIsBadFlashCart = 1;
	}
	
	agb_main();
}