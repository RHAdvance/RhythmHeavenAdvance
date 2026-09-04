#include "global.h"
#include "graphics.h"
#include "src/bitmap_font.h"
#include "src/scenes/results.h"
#include "graphics/results/results_graphics.h"


  /* RESULTS - MISC. DATA */


// [D_089d7984] Letter Ranks
const char *results_letter_ranks[] = {
    ":1.1" "D",
    ":1.5" "C",
    ":1.4" "B",
    ":1.6" "A",
    ":1.2" "S"
};


// [D_089d7998] DEBUG Skill Comments - Accuracy
const char *results_skill_text_accuracy[] = {
    "Professional Accuracy",
    "Sense of Rhythm",
    "Accuracy Satisfaction",
    NULL
};


// [D_089d79a8] DEBUG Skill Comments - Barelies (Tracker 2)
    // Technique Level
    // Adaptability
    // Reflexes
const char *results_skill_text_barely_trk2[] = {
    "Technique Level",
    "Adaptability",
    "Reflexes",
    NULL
};


// [D_089d79b8] DEBUG Skill Comments - Barelies (Tracker 1)
    // Responsibility
    //
    // Steadiness
const char *results_skill_text_barely_trk1[] = {
    "Responsibility",
    "The Most Important Part",
    "Grasp",
    NULL
};


// [D_089d79c8] DEBUG Skill Comments - Hits
const char *results_skill_text_hit_avg[] = {
    "Amateur Accuracy",
    "Ordinary Accuracy",
    "Moderate Accuracy",
    NULL
};


// [D_089d79d8] DEBUG Skill Comments - Irrelevant Inputs
const char *results_skill_text_irrelevant_inputs[] = {
    "Conservation of Stamina",
    "Rationality",
    "Calmness",
    NULL
};


// [D_089d79e8] DEBUG Skill Comments - Accuracy (Lenient)
const char *results_skill_text_accuracy_lenient[] = {
    "Stability",
    "Your Rhythm's Core",
    "Consistency",
    NULL
};


// [D_089d79f8] DEBUG Skill Comments - Misses
const char *results_skill_text_miss[] = {
    "Motivation",
    "Visual Strength",
    "Attitude",
    NULL
};


// [D_089d7a08] DEBUG Skill Comments - Misses (Tracker 2)
const char *results_skill_text_miss_trk2[] = {
    "Adaptability",
    "Flexibility",
    "Carefulness",
    NULL
};


// [D_089d7a18] DEBUG Skill Comments - Random
const char *results_skill_text_random[] = {
    "Next Year's Love",
    "This Year's Wealth",
    "Tomorrow's Weather",
    "Yesterday's Dinner",
    "Blood Type Prediction",
    "Your Upbringing",
    "Your Humanity",
    NULL
};


// [D_089d7a38] DEBUG Results Skills - High Level
struct ResultsSkillData results_skill_data_high[] = {
    /* 0x00 */ {
        /* Weight */ 8,
        /* Desc.  */ results_skill_text_accuracy,
        /* Calc.  */ results_measure_skill_accuracy
    },
    /* 0x01 */ {
        /* Weight */ 5,
        /* Desc.  */ results_skill_text_hit_avg,
        /* Calc.  */ results_measure_skill_hit_avg
    },
    /* 0x02 */ {
        /* Weight */ 10,
        /* Desc.  */ results_skill_text_barely_trk2,
        /* Calc.  */ results_measure_skill_barely_trk2
    },
    /* 0x03 */ {
        /* Weight */ 7,
        /* Desc.  */ results_skill_text_barely_trk1,
        /* Calc.  */ results_measure_skill_barely_trk1
    },
    /* 0x04 */ {
        /* Weight */ 0,
        /* Desc.  */ results_skill_text_irrelevant_inputs,
        /* Calc.  */ results_measure_skill_irrelevant_inputs
    },
    /* 0x05 */ {
        /* Weight */ 0,
        /* Desc.  */ results_skill_text_random,
        /* Calc.  */ results_measure_skill_random
    },
    END_OF_RESULTS_SKILL_LIST
};


// [D_089d7a8c] DEBUG Results Skills - OK Level
struct ResultsSkillData results_skill_data_mid[] = {
    /* 0x00 */ {
        /* Weight */ 8,
        /* Desc.  */ results_skill_text_hit_avg,
        /* Calc.  */ results_measure_skill_hit_avg
    },
    /* 0x01 */ {
        /* Weight */ 9,
        /* Desc.  */ results_skill_text_accuracy_lenient,
        /* Calc.  */ results_measure_skill_accuracy_lenient
    },
    /* 0x02 */ {
        /* Weight */ 7,
        /* Desc.  */ results_skill_text_barely_trk2,
        /* Calc.  */ results_measure_skill_barely_trk2
    },
    /* 0x03 */ {
        /* Weight */ 6,
        /* Desc.  */ results_skill_text_barely_trk1,
        /* Calc.  */ results_measure_skill_barely_trk1
    },
    /* 0x04 */ {
        /* Weight */ 0,
        /* Desc.  */ results_skill_text_irrelevant_inputs,
        /* Calc.  */ results_measure_skill_irrelevant_inputs
    },
    /* 0x05 */ {
        /* Weight */ 0,
        /* Desc.  */ results_skill_text_random,
        /* Calc.  */ results_measure_skill_random
    },
    END_OF_RESULTS_SKILL_LIST
};


// [D_089d7ae0] DEBUG Results Skills - Low Level
struct ResultsSkillData results_skill_data_low[] = {
    /* 0x00 */ {
        /* Weight */ 9,
        /* Desc.  */ results_skill_text_miss,
        /* Calc.  */ results_measure_skill_miss
    },
    /* 0x01 */ {
        /* Weight */ 6,
        /* Desc.  */ results_skill_text_accuracy_lenient,
        /* Calc.  */ results_measure_skill_accuracy_lenient
    },
    /* 0x02 */ {
        /* Weight */ 9,
        /* Desc.  */ results_skill_text_miss_trk2,
        /* Calc.  */ results_measure_skill_miss_trk2
    },
    /* 0x03 */ {
        /* Weight */ 6,
        /* Desc.  */ results_skill_text_barely_trk1,
        /* Calc.  */ results_measure_skill_barely_trk1
    },
    /* 0x04 */ {
        /* Weight */ 0,
        /* Desc.  */ results_skill_text_irrelevant_inputs,
        /* Calc.  */ results_measure_skill_irrelevant_inputs
    },
    /* 0x05 */ {
        /* Weight */ 0,
        /* Desc.  */ results_skill_text_random,
        /* Calc.  */ results_measure_skill_random
    },
    END_OF_RESULTS_SKILL_LIST
};
