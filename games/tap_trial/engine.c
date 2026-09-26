#include "engines/tap_trial.h"


  //  //  //  ANIMATION DATA  //  //  //


// [D_089e704c] All Animations
struct Animation *tap_trial_anim[][5] = {
    /* 0x00 */ {
        /* 0x00 */ anim_tap_trial_girl_1cue,
        /* 0x01 */ anim_tap_remix_8_girl_1cue,
        /* 0x02 */ anim_tap_remix_7_girl_1cue,
        /* 0x03 */ anim_tap_trial_2_girl_1cue,
        /* 0x04 */ anim_tap_remix_5_girl_1cue
    },
    /* 0x01 */ {
        /* 0x00 */ anim_tap_trial_girl_2cue,
        /* 0x01 */ anim_tap_remix_8_girl_2cue,
        /* 0x02 */ anim_tap_remix_7_girl_2cue,
        /* 0x03 */ anim_tap_trial_2_girl_2cue,
        /* 0x04 */ anim_tap_remix_5_girl_2cue
    },
    /* 0x02 */ {
        /* 0x00 */ anim_tap_trial_girl_1step,
        /* 0x01 */ anim_tap_remix_8_girl_1step,
        /* 0x02 */ anim_tap_remix_7_girl_1step,
        /* 0x03 */ anim_tap_trial_2_girl_1step,
        /* 0x04 */ anim_tap_remix_5_girl_1step
    },
    /* 0x03 */ {
        /* 0x00 */ anim_tap_trial_girl_2step,
        /* 0x01 */ anim_tap_remix_8_girl_2step,
        /* 0x02 */ anim_tap_remix_7_girl_2step,
        /* 0x03 */ anim_tap_trial_2_girl_2step,
        /* 0x04 */ anim_tap_remix_5_girl_2step
    },
    /* 0x04 */ {
        /* 0x00 */ anim_tap_trial_girl_3step_l,
        /* 0x01 */ anim_tap_remix_8_girl_3step_l,
        /* 0x02 */ anim_tap_remix_7_girl_3step_l,
        /* 0x03 */ anim_tap_trial_2_girl_3step_l,
        /* 0x04 */ anim_tap_remix_5_girl_3step_l
    },
    /* 0x05 */ {
        /* 0x00 */ anim_tap_trial_girl_3step_r,
        /* 0x01 */ anim_tap_remix_8_girl_3step_r,
        /* 0x02 */ anim_tap_remix_7_girl_3step_r,
        /* 0x03 */ anim_tap_trial_2_girl_3step_r,
        /* 0x04 */ anim_tap_remix_5_girl_3step_r
    },
    /* 0x06 */ {
        /* 0x00 */ anim_tap_trial_girl_3cue,
        /* 0x01 */ anim_tap_remix_8_girl_3cue,
        /* 0x02 */ anim_tap_remix_7_girl_3cue,
        /* 0x03 */ anim_tap_trial_2_girl_3cue,
        /* 0x04 */ anim_tap_remix_5_girl_3cue
    },
    /* 0x07 */ {
        /* 0x00 */ anim_tap_trial_girl_crouch,
        /* 0x01 */ anim_tap_remix_8_girl_crouch,
        /* 0x02 */ anim_tap_remix_7_girl_crouch,
        /* 0x03 */ anim_tap_trial_2_girl_crouch,
        /* 0x04 */ anim_tap_remix_5_girl_crouch
    },
    /* 0x08 */ {
        /* 0x00 */ anim_tap_trial_girl_jump,
        /* 0x01 */ anim_tap_remix_8_girl_jump,
        /* 0x02 */ anim_tap_remix_7_girl_jump,
        /* 0x03 */ anim_tap_trial_2_girl_jump,
        /* 0x04 */ anim_tap_remix_5_girl_jump
    },
    /* 0x09 */ {
        /* 0x00 */ anim_tap_trial_girl_pose_step,
        /* 0x01 */ anim_tap_remix_8_girl_pose_step,
        /* 0x02 */ anim_tap_remix_7_girl_pose_step,
        /* 0x03 */ anim_tap_trial_2_girl_pose_step,
        /* 0x04 */ anim_tap_remix_5_girl_pose_step
    },
    /* 0x0A */ {
        /* 0x00 */ anim_tap_trial_girl_fall,
        /* 0x01 */ anim_tap_remix_8_girl_fall,
        /* 0x02 */ anim_tap_remix_7_girl_fall,
        /* 0x03 */ anim_tap_trial_2_girl_fall,
        /* 0x04 */ anim_tap_remix_5_girl_fall
    },
    /* 0x0B */ {
        /* 0x00 */ anim_tap_trial_girl_crouch_step,
        /* 0x01 */ anim_tap_remix_8_girl_crouch_step,
        /* 0x02 */ anim_tap_remix_7_girl_crouch_step,
        /* 0x03 */ anim_tap_trial_2_girl_crouch_step,
        /* 0x04 */ anim_tap_remix_5_girl_crouch_step
    },
    /* 0x0C */ {
        /* 0x00 */ anim_tap_trial_girl_beat,
        /* 0x01 */ anim_tap_remix_8_girl_beat,
        /* 0x02 */ anim_tap_remix_7_girl_beat,
        /* 0x03 */ anim_tap_trial_2_girl_beat,
        /* 0x04 */ anim_tap_remix_5_girl_beat
    },
    /* 0x0D */ {
        /* 0x00 */ anim_tap_trial_girl_miss_crouch,
        /* 0x01 */ anim_tap_remix_8_girl_miss_crouch,
        /* 0x02 */ anim_tap_remix_7_girl_miss_crouch,
        /* 0x03 */ anim_tap_trial_2_girl_miss_crouch,
        /* 0x04 */ anim_tap_remix_5_girl_miss_crouch
    },
    /* 0x0E */ {
        /* 0x00 */ anim_tap_trial_girl_miss_pose,
        /* 0x01 */ anim_tap_remix_8_girl_miss_pose,
        /* 0x02 */ anim_tap_remix_7_girl_miss_pose,
        /* 0x03 */ anim_tap_trial_2_girl_miss_pose,
        /* 0x04 */ anim_tap_remix_5_girl_miss_pose
    },
    /* 0x0F */ {
        /* 0x00 */ anim_tap_trial_monkey_1cue,
        /* 0x01 */ anim_tap_remix_8_monkey_1cue,
        /* 0x02 */ anim_tap_remix_7_pig_1cue,
        /* 0x03 */ anim_tap_trial_2_monkey_1cue,
        /* 0x04 */ anim_tap_remix_5_monkey_1cue
    },
    /* 0x10 */ {
        /* 0x00 */ anim_tap_trial_monkey_2cue,
        /* 0x01 */ anim_tap_remix_8_monkey_2cue,
        /* 0x02 */ anim_tap_remix_7_pig_2cue,
        /* 0x03 */ anim_tap_trial_2_monkey_2cue,
        /* 0x04 */ anim_tap_remix_5_monkey_2cue
    },
    /* 0x11 */ {
        /* 0x00 */ anim_tap_trial_monkey_1step,
        /* 0x01 */ anim_tap_remix_8_monkey_1step,
        /* 0x02 */ anim_tap_remix_7_pig_1step,
        /* 0x03 */ anim_tap_trial_2_monkey_1step,
        /* 0x04 */ anim_tap_remix_5_monkey_1step
    },
    /* 0x12 */ {
        /* 0x00 */ anim_tap_trial_monkey_2step,
        /* 0x01 */ anim_tap_remix_8_monkey_2step,
        /* 0x02 */ anim_tap_remix_7_pig_2step,
        /* 0x03 */ anim_tap_trial_2_monkey_2step,
        /* 0x04 */ anim_tap_remix_5_monkey_2step
    },
    /* 0x13 */ {
        /* 0x00 */ anim_tap_trial_monkey_3step_l,
        /* 0x01 */ anim_tap_remix_8_monkey_3step_l,
        /* 0x02 */ anim_tap_remix_7_pig_3step_l,
        /* 0x03 */ anim_tap_trial_2_monkey_3step_l,
        /* 0x04 */ anim_tap_remix_5_monkey_3step_l
    },
    /* 0x14 */ {
        /* 0x00 */ anim_tap_trial_monkey_3step_r,
        /* 0x01 */ anim_tap_remix_8_monkey_3step_r,
        /* 0x02 */ anim_tap_remix_7_pig_3step_r,
        /* 0x03 */ anim_tap_trial_2_monkey_3step_r,
        /* 0x04 */ anim_tap_remix_5_monkey_3step_r
    },
    /* 0x15 */ {
        /* 0x00 */ anim_tap_trial_monkey_3cue,
        /* 0x01 */ anim_tap_remix_8_monkey_3cue,
        /* 0x02 */ anim_tap_remix_7_pig_3cue,
        /* 0x03 */ anim_tap_trial_2_monkey_3cue,
        /* 0x04 */ anim_tap_remix_5_monkey_3cue
    },
    /* 0x16 */ {
        /* 0x00 */ anim_tap_trial_monkey_crouch,
        /* 0x01 */ anim_tap_remix_8_monkey_crouch,
        /* 0x02 */ anim_tap_remix_7_pig_crouch,
        /* 0x03 */ anim_tap_trial_2_monkey_crouch,
        /* 0x04 */ anim_tap_remix_5_monkey_crouch
    },
    /* 0x17 */ {
        /* 0x00 */ anim_tap_trial_monkey_jump,
        /* 0x01 */ anim_tap_remix_8_monkey_jump,
        /* 0x02 */ anim_tap_remix_7_pig_jump,
        /* 0x03 */ anim_tap_trial_2_monkey_jump,
        /* 0x04 */ anim_tap_remix_5_monkey_jump
    },
    /* 0x18 */ {
        /* 0x00 */ anim_tap_trial_monkey_pose_step,
        /* 0x01 */ anim_tap_remix_8_monkey_pose_step,
        /* 0x02 */ anim_tap_remix_7_pig_pose_step,
        /* 0x03 */ anim_tap_trial_2_monkey_pose_step,
        /* 0x04 */ anim_tap_remix_5_monkey_pose_step
    },
    /* 0x19 */ {
        /* 0x00 */ anim_tap_trial_monkey_fall,
        /* 0x01 */ anim_tap_remix_8_monkey_fall,
        /* 0x02 */ anim_tap_remix_7_pig_fall,
        /* 0x03 */ anim_tap_trial_2_monkey_fall,
        /* 0x04 */ anim_tap_remix_5_monkey_fall
    },
    /* 0x1A */ {
        /* 0x00 */ anim_tap_trial_monkey_crouch_step,
        /* 0x01 */ anim_tap_remix_8_monkey_crouch_step,
        /* 0x02 */ anim_tap_remix_7_pig_crouch_step,
        /* 0x03 */ anim_tap_trial_2_monkey_crouch_step,
        /* 0x04 */ anim_tap_remix_5_monkey_crouch_step
    },
    /* 0x1B */ {
        /* 0x00 */ anim_tap_trial_monkey_beat,
        /* 0x01 */ anim_tap_remix_8_monkey_beat,
        /* 0x02 */ anim_tap_remix_7_pig_beat,
        /* 0x03 */ anim_tap_trial_2_monkey_beat,
        /* 0x04 */ anim_tap_remix_5_monkey_beat
    },
    /* 0x1C */ {
        /* 0x00 */ anim_tap_trial_shadow,
        /* 0x01 */ anim_tap_remix_8_shadow,
        /* 0x02 */ anim_tap_remix_7_shadow,
        /* 0x03 */ anim_tap_trial_2_shadow,
        /* 0x04 */ anim_tap_remix_5_shadow
    },
    /* 0x1D */ {
        /* 0x00 */ anim_tap_trial_giraffe_neutral,
        /* 0x01 */ anim_tap_remix_8_dragon_neutral,
        /* 0x02 */ anim_tap_remix_7_giraffe_neutral,
        /* 0x03 */ anim_tap_trial_2_camel_neutral,
        /* 0x04 */ anim_tap_remix_5_giraffe_neutral
    },
    /* 0x1E */ {
        /* 0x00 */ anim_tap_trial_giraffe_bedazzled,
        /* 0x01 */ anim_tap_remix_8_dragon_bedazzled,
        /* 0x02 */ anim_tap_remix_7_giraffe_bedazzled,
        /* 0x03 */ anim_tap_trial_2_camel_bedazzled,
        /* 0x04 */ anim_tap_remix_5_giraffe_bedazzled
    },
    /* 0x1F */ {
        /* 0x00 */ anim_tap_trial_giraffe_sad,
        /* 0x01 */ anim_tap_remix_8_dragon_sad,
        /* 0x02 */ anim_tap_remix_7_giraffe_sad,
        /* 0x03 */ anim_tap_trial_2_camel_sad,
        /* 0x04 */ anim_tap_remix_5_giraffe_sad
    }
};

// [D_089e72cc] Animation Table
struct Animation **tap_trial_anim_table[] = {
    /* 0x00 */ tap_trial_anim[0],
    /* 0x01 */ tap_trial_anim[1],
    /* 0x02 */ tap_trial_anim[2],
    /* 0x03 */ tap_trial_anim[3],
    /* 0x04 */ tap_trial_anim[4],
    /* 0x05 */ tap_trial_anim[5],
    /* 0x06 */ tap_trial_anim[6],
    /* 0x07 */ tap_trial_anim[7],
    /* 0x08 */ tap_trial_anim[8],
    /* 0x09 */ tap_trial_anim[9],
    /* 0x0A */ tap_trial_anim[10],
    /* 0x0B */ tap_trial_anim[11],
    /* 0x0C */ tap_trial_anim[12],
    /* 0x0D */ tap_trial_anim[13],
    /* 0x0E */ tap_trial_anim[14],
    /* 0x0F */ tap_trial_anim[15],
    /* 0x10 */ tap_trial_anim[16],
    /* 0x11 */ tap_trial_anim[17],
    /* 0x12 */ tap_trial_anim[18],
    /* 0x13 */ tap_trial_anim[19],
    /* 0x14 */ tap_trial_anim[20],
    /* 0x15 */ tap_trial_anim[21],
    /* 0x16 */ tap_trial_anim[22],
    /* 0x17 */ tap_trial_anim[23],
    /* 0x18 */ tap_trial_anim[24],
    /* 0x19 */ tap_trial_anim[25],
    /* 0x1A */ tap_trial_anim[26],
    /* 0x1B */ tap_trial_anim[27],
    /* 0x1C */ tap_trial_anim[28],
    /* 0x1D */ tap_trial_anim[29],
    /* 0x1E */ tap_trial_anim[30],
    /* 0x1F */ tap_trial_anim[31]
};

// [D_089e734c] Tap Dance Move
struct TapTrialAction tap_trial_girl_actions[] = {
    /* 0x00 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_1CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(24.0)
    },
    /* 0x01 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_2CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(24.0)
    },
    /* 0x02 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_L,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x03 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_R,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x04 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_1STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x05 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_2STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x06 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_L,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x07 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_R,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x08 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.5),
        /* SFX Pitch    */ INT_TO_FIXED(12.0)
    },
    /* 0x09 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_CROUCH,
        /* Playback 1   */ 1,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.625),
        /* SFX Pitch    */ INT_TO_FIXED(19.0)
    },
    /* 0x0A */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.5),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0B */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.75),
        /* SFX Pitch    */ INT_TO_FIXED(5.0)
    },
    /* 0x0C */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_POSE_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0D */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_FALL,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0E */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_CROUCH_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0F */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(32.0)
    },
    /* 0x10 */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
};

// [D_089e74a0] Tap Dance Move
struct TapTrialAction tap_trial_remix_8_girl_actions[] = {
    /* 0x00 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_1CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(24.0)
    },
    /* 0x01 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_2CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(24.0)
    },
    /* 0x02 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_L,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x03 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_R,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x04 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_1STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x05 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_2STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x06 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_L,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x07 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_R,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x08 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.5),
        /* SFX Pitch    */ INT_TO_FIXED(12.0)
    },
    /* 0x09 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_CROUCH,
        /* Playback 1   */ 1,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.625),
        /* SFX Pitch    */ INT_TO_FIXED(19.0)
    },
    /* 0x0A */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.5),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0B */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.75),
        /* SFX Pitch    */ INT_TO_FIXED(5.0)
    },
    /* 0x0C */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_POSE_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0D */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_FALL,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0E */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_CROUCH_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0F */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(32.0)
    },
    /* 0x10 */ {
        /* Animation ID */ 1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
};

// [D_089e75f4] Tap Dance Move
struct TapTrialAction tap_trial_remix_7_girl_actions[] = {
    /* 0x00 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_1CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(24.0)
    },
    /* 0x01 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_2CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(24.0)
    },
    /* 0x02 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_L,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x03 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_R,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x04 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_1STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x05 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_2STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x06 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_L,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x07 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_R,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x08 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.5),
        /* SFX Pitch    */ INT_TO_FIXED(12.0)
    },
    /* 0x09 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_CROUCH,
        /* Playback 1   */ 1,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.625),
        /* SFX Pitch    */ INT_TO_FIXED(19.0)
    },
    /* 0x0A */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.5),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0B */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.75),
        /* SFX Pitch    */ INT_TO_FIXED(5.0)
    },
    /* 0x0C */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_POSE_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0D */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_FALL,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0E */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_CROUCH_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0F */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(32.0)
    },
    /* 0x10 */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
};

// [D_089e7748] Tap Dance Move
struct TapTrialAction tap_trial_2_girl_actions[] = {
    /* 0x00 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_1CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(24.0)
    },
    /* 0x01 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_2CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(24.0)
    },
    /* 0x02 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_L,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x03 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_R,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x04 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_1STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x05 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_2STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x06 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_L,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x07 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3STEP_R,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x08 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_3CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.5),
        /* SFX Pitch    */ INT_TO_FIXED(12.0)
    },
    /* 0x09 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_CROUCH,
        /* Playback 1   */ 1,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.625),
        /* SFX Pitch    */ INT_TO_FIXED(19.0)
    },
    /* 0x0A */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.5),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0B */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(0.75),
        /* SFX Pitch    */ INT_TO_FIXED(5.0)
    },
    /* 0x0C */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_POSE_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0D */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_FALL,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0E */ {
        /* Animation ID */ TAP_TRIAL_ANIM_GIRL_CROUCH_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_lady_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0F */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_dummy_vol0_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(32.0)
    },
    /* 0x10 */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
};

// [D_089e789c] Tap Dance Actions - Girl
struct TapTrialAction *tap_trial_girl_action_table[] = {
    /* 0x00 */ tap_trial_girl_actions,
    /* 0x01 */ tap_trial_remix_8_girl_actions,
    /* 0x02 */ tap_trial_remix_7_girl_actions,
    /* 0x03 */ tap_trial_2_girl_actions,
    /* 0x04 */ tap_trial_girl_actions
};

// [D_089e78b0] Tap Dance Move
struct TapTrialAction tap_trial_monkey_actions[] = {
    /* 0x00 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_1CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky1_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x01 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_2CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x02 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_L,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x03 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_R,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x04 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_1STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x05 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_2STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x06 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_L,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x07 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_R,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x08 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky3_1_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x09 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_CROUCH,
        /* Playback 1   */ 1,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_tap_jump_ready_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0A */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky4_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0B */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky4_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(5.0)
    },
    /* 0x0C */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_POSE_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0D */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_FALL,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0E */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_CROUCH_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0F */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x10 */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky3_2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
};

// [D_089e7a04] Tap Dance Move
struct TapTrialAction tap_trial_remix_8_monkey_actions[] = {
    /* 0x00 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_1CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky1_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x01 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_2CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x02 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_L,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x03 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_R,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x04 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_1STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x05 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_2STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x06 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_L,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x07 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_R,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x08 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky3_1_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x09 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_CROUCH,
        /* Playback 1   */ 1,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_tap_jump_ready_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0A */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky4_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0B */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky4_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(5.0)
    },
    /* 0x0C */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_POSE_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0D */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_FALL,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0E */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_CROUCH_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0F */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x10 */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky3_2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
};

// [D_089e7b58] Tap Dance Move
struct TapTrialAction tap_trial_remix_7_monkey_actions[] = {
    /* 0x00 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_1CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_tap_pig1_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x01 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_2CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_tap_pig2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x02 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_L,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x03 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_R,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x04 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_1STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x05 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_2STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x06 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_L,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x07 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_R,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x08 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky3_1_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x09 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_CROUCH,
        /* Playback 1   */ 1,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_tap_jump_ready_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0A */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky4_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0B */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky4_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(5.0)
    },
    /* 0x0C */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_POSE_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0D */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_FALL,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0E */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_CROUCH_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0F */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_tap_pig2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x10 */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky3_2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
};

// [D_089e7cac] Tap Dance Move
struct TapTrialAction tap_trial_2_monkey_actions[] = {
    /* 0x00 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_1CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky1_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x01 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_2CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x02 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_L,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x03 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_R,
        /* Playback 1   */ 3,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x04 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_1STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x05 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_2STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x06 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_L,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x07 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3STEP_R,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x08 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_3CUE,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky3_1_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x09 */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_CROUCH,
        /* Playback 1   */ 1,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_f_tap_jump_ready_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0A */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky4_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0B */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_JUMP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 0,
        /* Unused       */ 0,
        /* Playback 3   */ 0,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky4_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(5.0)
    },
    /* 0x0C */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_POSE_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0D */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_FALL,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ NULL,
        /* SFX Volume   */ INT_TO_FIXED(0.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0E */ {
        /* Animation ID */ TAP_TRIAL_ANIM_MONKEY_CROUCH_STEP,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x14,
        /* Sound Effect */ &s_tap_kick_monky_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x0F */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
    /* 0x10 */ {
        /* Animation ID */ -1,
        /* Playback 1   */ 0,
        /* Playback 2   */ 1,
        /* Unused       */ 0,
        /* Playback 3   */ 0x7f,
        /* Playback 4   */ 0,
        /* Duration     */ 0x1E,
        /* Sound Effect */ &s_tap_monky3_2_seqData,
        /* SFX Volume   */ INT_TO_FIXED(1.0),
        /* SFX Pitch    */ INT_TO_FIXED(0.0)
    },
};

// [D_089e7e00] Tap Dance Actions - Monkey
struct TapTrialAction *tap_trial_monkey_action_table[] = {
    /* 0x00 */ tap_trial_monkey_actions,
    /* 0x01 */ tap_trial_remix_8_monkey_actions,
    /* 0x02 */ tap_trial_remix_7_monkey_actions,
    /* 0x03 */ tap_trial_2_monkey_actions,
    /* 0x04 */ tap_trial_monkey_actions
};


  //  //  //  GRAPHICS DATA  //  //  //


// [D_089e7e14] Buffered Textures List
struct CompressedData *tap_trial_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// [D_089e7e18] Graphics Table (Tap Trial)
struct GraphicsTable gfx_table_tap_trial[] = {
    /* BG Tileset */ {
        /* Src.  */ &tap_trial_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_bg_map_text_bubble,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &tap_trial_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ tap_trial_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ tap_trial_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[6],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e7e84] Graphics Table (Remix 7, Remix 8)
struct GraphicsTable gfx_table_tap_trial_remix_8[] = {
    /* BG Tileset */ {
        /* Src.  */ &tap_trial_remix_8_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_remix_8_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_remix_8_bg_map_text_bubble,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &tap_trial_remix_8_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ tap_trial_remix_8_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ tap_trial_remix_8_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[6],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e7ef0] Graphics Table (Remix 7)
struct GraphicsTable gfx_table_tap_trial_remix_7[] = {
    /* BG Tileset */ {
        /* Src.  */ &tap_trial_remix_7_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_remix_7_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_remix_7_bg_map_text_bubble,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &tap_trial_remix_7_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ tap_trial_remix_7_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ tap_trial_remix_7_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[6],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e7f5c] Graphics Table (Tap Trial 2)
struct GraphicsTable gfx_table_tap_trial_2[] = {
    /* BG Tileset */ {
        /* Src.  */ &tap_trial_2_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_2_bg_map_stage,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_2_bg_map,
        /* Dest. */ BG_MAP_BASE(0xF800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_2_bg_map_text_bubble,
        /* Dest. */ BG_MAP_BASE(0xF000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_2_bg_map_2,
        /* Dest. */ BG_MAP_BASE(0xE000),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &tap_trial_2_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ tap_trial_2_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ tap_trial_2_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[6],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e7fe0] Graphics Table (Remix 5)
struct GraphicsTable gfx_table_tap_trial_remix_5[] = {
    /* BG Tileset */ {
        /* Src.  */ &tap_trial_remix_5_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &tap_trial_remix_5_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &tap_trial_remix_5_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ tap_trial_remix_5_bg_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ tap_trial_remix_5_obj_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x140
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[0],
        /* Dest. */ OBJ_PALETTE_BUFFER(12.5),
        /* Size  */ 0x8
    },
    /* OBJ Palette */ {
        /* Src.  */ D_089ccbc8[6],
        /* Dest. */ OBJ_PALETTE_BUFFER(13.5),
        /* Size  */ 0x8
    },
    END_OF_GRAPHICS_TABLE
};

// [D_089e8040] Graphics Table Index
struct GraphicsTable *tap_trial_gfx_tables[] = {
    /* 0x00 */ gfx_table_tap_trial,
    /* 0x01 */ gfx_table_tap_trial_remix_8,
    /* 0x02 */ gfx_table_tap_trial_remix_7,
    /* 0x03 */ gfx_table_tap_trial_2,
    /* 0x04 */ gfx_table_tap_trial_remix_5
};

const char D_0805a8bc[] = "";

// [D_089e8054] ?
const char *D_089e8054[] = {
    "Divine!",
    "Dazzling!",
    "So technical!",
    "Sharp work!",
    "I think I'm in love!",
};

// [D_089e8068] ?
s8 D_089e8068[] = {
    /* 0x00 */ 0,
    /* 0x01 */ -1,
    /* 0x02 */ -1,
    /* 0x03 */ -1,
    /* 0x04 */ -2,
    /* 0x05 */ -2,
    /* 0x06 */ -3,
    /* 0x07 */ 0
};


  //  //  //  CUE DATA  //  //  //


// [D_089e8070] Cue 00 (Default)
struct CueDefinition tap_trial_cue_default = {
    /* Unknown Param.  */ 0,
    /* Input Buttons   */ PRESS_BUTTON(A_BUTTON),
    /* Total Duration  */ 0x18,
    /* Hit Window      */ -0x03, 0x03,
    /* Barely Window   */ -0x05, 0x05,
    /* Tempo-Dependent */ FALSE,
    /* Force-Delete    */ FALSE,
    /* Size in Memory  */ sizeof(struct TapTrialCue),
    /* Func. Spawn     */ tap_trial_cue_spawn,
    /* Spawn Parameter */ 0,
    /* Func. Update    */ tap_trial_cue_update,
    /* Func. Despawn   */ tap_trial_cue_despawn,
    /* Func. Hit       */ tap_trial_cue_hit,
    /* Func. Barely    */ tap_trial_cue_barely,
    /* Func. Miss      */ tap_trial_cue_miss,
    /* SFX Spawn       */ NULL,
    /* SFX Hit         */ NULL,
    /* SFX Barely      */ NULL,
    /* SFX Miss        */ NULL,
    /* Miss Condition  */ NULL
};

// [D_089e80b0] Cue Definition Index
struct CueDefinition *tap_trial_cue_index[] = {
    /* 0x00 */ &tap_trial_cue_default,
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


// [D_089e80e4] Common Events
EngineEvent tap_trial_common_events[] = {
    /* BEAT_ANIMATION */ tap_trial_common_beat_animation,
    /* DISPLAY_TEXT   */ tap_trial_common_display_text,
    /* INIT_TUTORIAL  */ // None
    END_OF_COMMON_EVENT_LIST
};

// [D_089e80f0] Engine Events
EngineEvent tap_trial_engine_events[] = {
    /* 0x00 */ tap_trial_play_monkey_action,
    /* 0x01 */ func_0803e0bc,
    /* 0x02 */ func_0803e0f8,
    /* 0x03 */ func_0803e10c,
    /* 0x04 */ func_0803e258,
    /* 0x05 */ func_0803e160,
    /* 0x06 */ func_0803e1a4,
    /* 0x07 */ func_0803e208,
    /* 0x08 */ func_0803e448,
    /* 0x09 */ func_0803e2e0,
    /* 0x0A */ func_0803e2f4,
    /* 0x0B */ func_0803e310,
    /* 0x0C */ func_0803e324,
    /* 0x0D */ func_0803e338,
    /* 0x0E */ func_0803e354,
    /* 0x0F */ tap_trial_engine_event_stub
};

// [D_089e8130] Tap Trial Game Engine
struct GameEngine tap_trial_engine = {
    /* Size in Memory */ sizeof(struct TapTrialEngineData),
    /* Start Engine   */ tap_trial_engine_start,
    /* Update Engine  */ tap_trial_engine_update,
    /* Stop Engine    */ tap_trial_engine_stop,
    /* Cue Index      */ tap_trial_cue_index,
    /* Common Events  */ tap_trial_common_events,
    /* Engine Events  */ tap_trial_engine_events,
    /* Input Event    */ tap_trial_input_event
};
