#pragma once

#include "global.h"
#include "scenes.h"


#define RESET_BUTTON_COMBO (A_BUTTON | B_BUTTON | SELECT_BUTTON | START_BUTTON)

struct SceneTransition {
    struct Scene *initial;
    struct Scene *target;
    s32 variable;
};

extern u8 D_03004498;
extern s32 D_030046a0;

extern void *interrupt_handler_rom;
extern void *interrupt_handler;
extern void *interrupt_handler_jtbl_rom;
extern void *interrupt_handler_jtbl;
extern struct Scene *D_08935fac; // Pointer to Title Screen
extern struct Scene *D_08935fb0; // Pointer to Title Screen (again)
extern struct Scene scene_soft_reset; // Soft Reset Scene
extern struct Scene scene_warning;

extern void init_scene_static_var(void);
extern void func_08000224(void);
extern void agb_main(void);
extern void init_scenes(struct Scene *initial);
extern void process_scenes(void);
extern void set_current_scene(struct Scene *initial);
extern void set_next_scene(struct Scene *next);
extern void clear_scene_trans(void);
extern struct SceneTransition *get_scene_trans(struct Scene *scene);
extern struct Scene *get_scene_trans_target(struct Scene *scene);
extern s32 get_scene_trans_var(struct Scene *scene);
extern struct Scene *get_current_scene_trans_target(void);
extern s32 get_current_scene_trans_var(void);
extern struct SceneTransition *alloc_scene_trans(struct Scene *scene);
extern void dealloc_scene_trans(struct Scene *scene);
extern void set_scene_trans_target(struct Scene *scene, struct Scene *target);
extern void set_scene_trans_var(struct Scene *scene, s32 variable);
extern void func_080006f0(struct Scene *target, s32 variable);
extern struct Scene *get_current_scene(void);

extern void trigger_req_save_data_sync(void);
