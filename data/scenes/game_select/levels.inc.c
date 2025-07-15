// Level Entries Table
struct LevelData level_data_table[] = {
    /* KARATE_MAN */ {
        /* Entry Scene   */ &scene_karate_man,
        /* Level Name    */ "Karate Man",
        /* Level Desc.   */ "The key to karate,\n"
                            "like all things, is rhythm.\n"
                            "Now, let us throw some\n"
                            "stuff for you to punch.",
        /* Level Icon    */ 8,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "There's always tomorrow...",
            /* OK        */ "Let's break for lunch now!",
            /* SUPERB    */ "Look at all this stuff I punched away!"
        }
    },
    /* KARATE_MAN_2 */ {
        /* Entry Scene   */ &scene_karate_man_2,
        /* Level Name    */ "Karate Man 2",
        /* Level Desc.   */ "Something's up with\n"
                            "the speed! Take care\n"
                            "as we throw you some\n"
                            "more stuff to punch.",
        /* Level Icon    */ 0,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "What's wrong with the speed?!",
            /* OK        */ "Well, that's that. Let's eat!",
            /* SUPERB    */ "I think we went through everything!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* CLAPPY_TRIO */ {
        /* Entry Scene   */ &scene_clappy_trio,
        /* Level Name    */ "The Clappy Trio",
        /* Level Desc.   */ "Clap your hands in\n"
                            "order! You're the third\n"
                            "clapper. Keep an eye\n"
							"on the other two!",
        /* Level Icon    */ 4,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_clappy_trio_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "The trio just went solo!",
            /* OK        */ "You need to make it to more of our practice sessions...",
            /* SUPERB    */ "Trio-riffic!"
        }
    },
    /* SNAPPY_TRIO */ {
        /* Entry Scene   */ &scene_snappy_trio,
        /* Level Name    */ "The Snappy Trio",
        /* Level Desc.   */ "Look at the trio in their\n"
                            "Western outfits!\n"
                            "So cool! Dare we say\n"
                            "they look... snappy?",
        /* Level Icon    */ 10,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_snappy_trio_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I spent everything I had on this outfit!",
            /* OK        */ "We were so close...",
            /* SUPERB    */ "Perfect sync! It's gotta be the outfits, right?"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* POLYRHYTHM */ {
        /* Entry Scene   */ &scene_polyrhythm,
        /* Level Name    */ "Polyrhythm",
        /* Level Desc.   */ "Manage the áO and áM\n"
							"paths at the same time\n"
							"to keep the red things\n"
							"rolling! Simple enough?",
        /* Level Icon    */ 3,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_polyrhythm_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Mass producing these will be harder than I thought...",
            /* OK        */ "Still getting the hang of making these red things!",
            /* SUPERB    */ "We've produced more of these than we can stock!"
        }
    },
    /* POLYRHYTHM_2 */ {
        /* Entry Scene   */ &scene_polyrhythm_2,
        /* Level Name    */ "Polyrhythm 2",
        /* Level Desc.   */ "The left and right paths\n"
                            "have unique patterns!\n"
                            "Mind the tempo and\n"
                            "play to the polyrhythm!",
        /* Level Icon    */ 51,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_polyrhythm_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We need to produce a whole lot more red things...",
            /* OK        */ "Producing more of these red things woudn't hurt!",
            /* SUPERB    */ "Red thing production is at an all time high!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* NIGHT_WALK */ {
        /* Entry Scene   */ &scene_night_walk,
        /* Level Name    */ "Night Walk",
        /* Level Desc.   */ "What's better than a\n"
                            "stroll in the starlight?\n"
                            "How about a series of\n"
                            "jumps in the starlight?",
        /* Level Icon    */ 7,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_night_walk_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Didn't see that hole in the dark!",
            /* OK        */ "Nothing like a stroll at night.",
            /* SUPERB    */ "You followed us up here!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* NIGHT_WALK_2 */ {
        /* Entry Scene   */ &scene_night_walk_2,
        /* Level Name    */ "Night Walk 2",
        /* Level Desc.   */ "Time to jump in the\n"
                            "starlight again!\n"
                            "Keep a look out\n"
                            "for the electric fish.",
        /* Level Icon    */ 41,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_night_walk_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "No! You fell!",
            /* OK        */ "The night breeze feels so cool...",
            /* SUPERB    */ "You made friends with the stars!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RHYTHM_TWEEZERS */ {
        /* Entry Scene   */ &scene_rhythm_tweezers,
        /* Level Name    */ "Rhythm Tweezers",
        /* Level Desc.   */ "\n"
                            "My roots are showing!\n"
                            "Can you pluck them off?\n",
        /* Level Icon    */ 14,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I can't sell these!",
            /* OK        */ "Wh-why do my vegetables grow hair?",
            /* SUPERB    */ "So fresh and clean! Even the air tastes delicious!"
        }
    },
    /* RHYTHM_TWEEZERS_2 */ {
        /* Entry Scene   */ &scene_rhythm_tweezers_2,
        /* Level Name    */ "Rhythm Tweezers 2",
        /* Level Desc.   */ "My roots are\n"
                            "growing back!\n"
                            "Please pluck them\n"
                            "off again!",
        /* Level Icon    */ 25,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Why do you have to be so hairy!?",
            /* OK        */ "Why do only our vegetables grow hair, anyway...?",
            /* SUPERB    */ "How refreshing! Even the air is nice and crisp!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SICK_BEATS */ {
        /* Entry Scene   */ &scene_sick_beats,
        /* Level Name    */ "Sick Beats",
        /* Level Desc.   */ "\0023" "Assistant's memo:\n"
                            "\"We have an outbreak\n"
                            "of an unknown virus!\n"
                            "Help us, Dr. Cutlery!\"",
        /* Level Icon    */ 13,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_sick_beats_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "All our research... amounted to nothing...",
            /* OK        */ "Failure may be the key to success!",
            /* SUPERB    */ "We've finally found our cure!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* BOUNCY_ROAD */ {
        /* Entry Scene   */ &scene_bouncy_road,
        /* Level Name    */ "Bouncy Road",
        /* Level Desc.   */ "See that ball bouncing\n"
                            "down the road?\n"
                            "You wouldn't want to\n"
							"let it fall...would you?",
        /* Level Icon    */ 12,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bouncy_road_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Ow! That was hard...",
            /* OK        */ "Nice combo!",
            /* SUPERB    */ "Where's the challenge?"
        }
    },
    /* BOUNCY_ROAD_2 */ {
        /* Entry Scene   */ &scene_bouncy_road_2,
        /* Level Name    */ "Bouncy Road 2",
        /* Level Desc.   */ "See that ball bouncing\n"
                            "down the road?\n"
                            "It's a rather nice ball,\n"
                            "so dont let it fall!",
        /* Level Icon    */ 50,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bouncy_road_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Ow! We failed!",
            /* OK        */ "We're working our hardest!",
            /* SUPERB    */ "Easy come, easy go."
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* NINJA_BODYGUARD */ {
        /* Entry Scene   */ &scene_ninja_bodyguard,
        /* Level Name    */ "Ninja Bodyguard",
        /* Level Desc.   */ "An enemy is attacking\n"
                            "your lord! Block the\n"
                            "arrows with your sword\n"
							"using áO and áM!",
        /* Level Icon    */ 5,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_ninja_bodyguard_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I cannot apologize enough, my lord!",
            /* OK        */ "Sorry...",
            /* SUPERB    */ "Not a scratch!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* NINJA_REINCARNATE */ {
        /* Entry Scene   */ &scene_ninja_reincarnate,
        /* Level Name    */ "Ninja Reincarnate",
        /* Level Desc.   */ "You know, my family's\n"
                            "ancestors came from\n"
                            "a long lineage of ninjas.\n"
                            "Cool, right?",
        /* Level Icon    */ 38,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_ninja_reincarnate_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Don't give up! We're counting on you!",
            /* OK        */ "You are... strong. Don't give up yet.",
            /* SUPERB    */ "You have proven your worth! You have our blessing..."
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SNEAKY_SPIRITS */ {
        /* Entry Scene   */ &scene_sneaky_spirits,
        /* Level Name    */ "Sneaky Spirits",
        /* Level Desc.   */ "These spirits aren't\n"
                            "exactly evil, but they\n"
                            "ARE mean; they'll laugh\n"
                            "at you if you miss.",
        /* Level Icon    */ 1,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_sneaky_spirits_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Escaped ghosts are nothing but trouble.",
            /* OK        */ "This one's not going anywhere!",
            /* SUPERB    */ "No ghost escapes on your watch!"
        }
    },
    /* SNEAKY_SPIRITS_2 */ {
        /* Entry Scene   */ &scene_sneaky_spirits_2,
        /* Level Name    */ "Sneaky Spirits 2",
        /* Level Desc.   */ "Those spirits are\n"
                            "acting up again!\n"
                            "Let them have it,\n"
                            "archery style!",
        /* Level Icon    */ 53,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_sneaky_spirits_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Gah! They slipped right past you!",
            /* OK        */ "\"L-Let me go! Please!\"",
            /* SUPERB    */ "You ghosts stay and think about what you've done!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SAMURAI_SLICE */ {
        /* Entry Scene   */ &scene_samurai_slice,
        /* Level Name    */ "Samurai Slice",
        /* Level Desc.   */ "Demons have put\n"
                            "the town in a panic!\n"
                            "Look out! Samurai--\n"
                            "slice them allÅI",
        /* Level Icon    */ 18,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_samurai_slice_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I've broken my blade!",
            /* OK        */ "I shall push myself harder!",
            /* SUPERB    */ "Have you ever seen a sword this sharp?"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SPACEBALL */ {
        /* Entry Scene   */ &scene_spaceball,
        /* Level Name    */ "Spaceball",
        /* Level Desc.   */ "Ignore the camera's\n"
                            "zooms! Make the ball\n"
                            "zoom away! Don't blink!\n"
                            "Don't wipe your tears!",
        /* Level Icon    */ 9,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Can I have my ball back? I'll give you my last rice ball...",
            /* OK        */ "Must... train... harder...",
            /* SUPERB    */ "I won first \"space\"!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SPACEBALL_2 */ {
        /* Entry Scene   */ &scene_spaceball_2,
        /* Level Name    */ "Spaceball 2",
        /* Level Desc.   */ "Ignore the camera's\n"
                            "zooms! Just believe\n"
                            "in yourself and\n"
                            "send the ball flying!",
        /* Level Icon    */ 52,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Next time, swing your bat somewhere else!",
            /* OK        */ "I can't give up now!",
            /* SUPERB    */ "Guys, guys, look at what I've won!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* TAP_TRIAL */ {
        /* Entry Scene   */ &scene_tap_trial,
        /* Level Name    */ "Tap Trial",
        /* Level Desc.   */ "You are the girl.\n"
                            "They are the monkeys.\n"
                            "Follow them to tap\n"
                            "stardom!",
        /* Level Icon    */ 6,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tap_trial_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Gotta tap out.",
            /* OK        */ "You were ALMOST as good as a monkey...",
            /* SUPERB    */ "Tap loves you too, Giraffe!"
        }
    },
    /* TAP_TRIAL_2 */ {
        /* Entry Scene   */ &scene_tap_trial_2,
        /* Level Name    */ "Tap Trial 2",
        /* Level Desc.   */ "The monkeys are \n"
                            "bringing their A game!\n"
                            "Can you keep up? Don't\n"
                            "let them out-tap you!",
        /* Level Icon    */ 11,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tap_trial_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Looks like we tapped TOO hard!",
            /* OK        */ "Hey... Where'd our rhythm go?",
            /* SUPERB    */ "Monkeys are the key to tappiness!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* MARCHING_ORDERS */ {
        /* Entry Scene   */ &scene_marching_orders,
        /* Level Name    */ "Marching Orders",
        /* Level Desc.   */ "Ready, march! Following\n"
                            "orders as a unit builds\n"
                            "your camaraderie.\n"
							"Also, rhythm.",
        /* Level Icon    */ 21,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Wait! You left without us!",
            /* OK        */ "Today's mission: Cleaning. ",
            /* SUPERB    */ "Mission success! We rescued the alien!"
        }
    },
    /* MARCHING_ORDERS_2 */ {
        /* Entry Scene   */ &scene_marching_orders_2,
        /* Level Name    */ "Marching Orders 2",
        /* Level Desc.   */ "Ready, march!\n"
                            "This mission requires\n"
                            "finesse and technique,\n"
                            "so march your best!",
        /* Level Icon    */ 20,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "This is unacceptable...",
            /* OK        */ "I know we can perform better than that!",
            /* SUPERB    */ "Now THIS is a reward!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* WIZARDS_WALTZ */ {
        /* Entry Scene   */ &scene_wizards_waltz,
        /* Level Name    */ "Wizard's Waltz",
        /* Level Desc.   */ "There's a lonely girl\n"
                            "over there. Put your\n"
                            "flower power to good\n"
                            "use to cheer her up!",
        /* Level Icon    */ 23,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_wizards_waltz_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "... I'm scared!",
            /* OK        */ "These will look SO lovely when they bloom!",
            /* SUPERB    */ "Who could feel lonely with all these flowers?"
        }
    },
    /* BUNNY_HOP */ {
        /* Entry Scene   */ &scene_bunny_hop,
        /* Level Name    */ "Bunny Hop",
        /* Level Desc.   */ "This rabbit has an\n"
                            "impossible goal: to jump\n"
                            "to the moon! Can you\n"
                            "make his dream reality?",
        /* Level Icon    */ 24,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bunny_hop_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I'm not sure I thought this through...",
            /* OK        */ "Didn't quite stick the landing...",
            /* SUPERB    */ "A perfect landing! Who needs rockets?!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* FIREWORKS */ {
        /* Entry Scene   */ &scene_fireworks,
        /* Level Name    */ "Fireworks",
        /* Level Desc.   */ "It's not summertime\n"
                            "without fireworks!\n"
                            "Light them up to fill the\n"
                            "sky with pretty colors!",
        /* Level Icon    */ 26,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_fireworks_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Cough, cough... I think I blew it...",
            /* OK        */ "That wasn't half bad!",
            /* SUPERB    */ "I am THE go-to fireworks guy!"
        }
    },
    /* POWER_CALLIGRAPHY */ {
        /* Entry Scene   */ &scene_power_calligraphy,
        /* Level Name    */ "Power Calligraphy",
        /* Level Desc.   */ "Japanese calligraphy\n"
                            "requires grace, finesse,\n"
                            "and a shocking amount\n"
                            "of upper body strength.",
        /* Level Icon    */ 28,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_power_power_calligraphy_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Maybe I should stick with pencils...",
            /* OK        */ "Precision! Grace! What's not to like?",
            /* SUPERB    */ "Woo! Calligraphy party!"
        }
    },
    /* POWER_CALLIGRAPHY_2 */ { // this still kills me lmao
        /* Entry Scene   */ &scene_power_calligraphy,
        /* Level Name    */ "",
        /* Level Desc.   */ "\n"
                            "\n"
                            "\n"
                            "",
        /* Level Icon    */ 28,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_power_calligraphy_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "",
            /* OK        */ "",
            /* SUPERB    */ ""
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* TOSS_BOYS */ {
        /* Entry Scene   */ &scene_toss_boys,
        /* Level Name    */ "Toss Team",
        /* Level Desc.   */ "This trio of friends love\n"
                            "practicing volleyball.\n"
                            "Listen for their names\n"
                            "as they pass their ball!",
        /* Level Icon    */ 30,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_toss_boys_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We've been tossed out!",
            /* OK        */ "Next time, we'll toss better than the best!",
            /* SUPERB    */ "Toss World Championship, here we come!"
        }
    },
    /* TOSS_BOYS_2 */ {
        /* Entry Scene   */ &scene_toss_boys_2,
        /* Level Name    */ "Toss Team 2",
        /* Level Desc.   */ "This trio of friends love\n"
                            "practicing volleyball.\n"
                            "Today, they're training\n"
                            "harder than ever!",
        /* Level Icon    */ 29,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_toss_boys_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Our spirits have been deflated...",
            /* OK        */ "We still have a long way to go!",
            /* SUPERB    */ "Three cheers for our star tossers!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RAT_RACE */ {
        /* Entry Scene   */ &scene_rat_race,
        /* Level Name    */ "Rat Race",
        /* Level Desc.   */ "You are a rat. She is\n"
                            "a cat. You love cheese.\n"
                            "All the ingredients of a\n"
                            "tense encounter.",
        /* Level Icon    */ 31,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rat_race_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I guess we could try to eat the plate...",
            /* OK        */ "You know, I really like cheese. Like, a LOT.",
            /* SUPERB    */ "We'll have to start a family to eat all this!"
        }
    },
    /* TRAM_PAULINE */ {
        /* Entry Scene   */ &scene_tram_pauline,
        /* Level Name    */ "Tram & Pauline",
        /* Level Desc.   */ "Gather round, one and\n"
                            "all! Tram and Pauline's\n"
                            "acrobatic fox show\n"
							"is about to begin!",
        /* Level Icon    */ 32,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tram_pauline_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We've transformed the show into a failure!",
            /* OK        */ "At least we only half messed up the show...",
            /* SUPERB    */ "We're the perfect duo!"
        }
    },
    /* SHOWTIME */ {
        /* Entry Scene   */ &scene_showtime,
        /* Level Name    */ "Showtime",
        /* Level Desc.   */ "It's showtime!\n"
                            "Our plucky penguins\n"
                            "are ready to start\n"
                            "their routine!",
        /* Level Icon    */ 36,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_showtime_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We've betrayed our audience...",
            /* OK        */ "I know we're capable of more than this...",
            /* SUPERB    */ "They loved us out there!"
        }
    },
    /* SPACE_DANCE */ {
        /* Entry Scene   */ &scene_space_dance,
        /* Level Name    */ "Space Dance",
        /* Level Desc.   */ "You want a dancing\n"
                            "challenge? Try dancing\n"
                            "in zero gravity!\n"
							"IN SPAAAAAAAAAACE!",
        /* Level Icon    */ 40,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_space_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Our despair has lead us into a black hole!",
            /* OK        */ "Let us aim for the stars!",
            /* SUPERB    */ "We are space superstars!"
        }
    },
    /* COSMIC_DANCE */ {
        /* Entry Scene   */ &scene_cosmic_dance,
        /* Level Name    */ "Cosmic Dance",
        /* Level Desc.   */ "These paragons of\n"
                            "dancing have mastered\n"
                            "their Zero-G moves\n"
                            "and want to show off!",
        /* Level Icon    */ 16,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_cosmic_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We cannot go on like THIS!",
            /* OK        */ "Is that the best you guys can do?",
            /* SUPERB    */ "We are cosmic superstars!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RAP_MEN */ {
        /* Entry Scene   */ &scene_rap_men,
        /* Level Name    */ "RAPMEN",
        /* Level Desc.   */ "The coolest rapping\n"
                            "duo has arrived! Their\n"
                            "hot rapping skills are\n"
                            "the talk of the town!",
        /* Level Icon    */ 42,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rap_men_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We need more practice...",
            /* OK        */ "I think our tone was off.",
            /* SUPERB    */ "We're looking forward to hearing you again!"
        }
    },
    /* RAP_WOMEN */ {
        /* Entry Scene   */ &scene_rap_women,
        /* Level Name    */ "RAPWOMEN",
        /* Level Desc.   */ "The RAPMEN have\n"
                            "some new rivals!\n"
                            "Don't be distracted\n"
                            "by their cute voices!",
        /* Level Icon    */ 15,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rap_women_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "No... This isn't right.",
            /* OK        */ "I know we can rap better than this!",
            /* SUPERB    */ "Yes, yes, YES! We've got it!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* QUIZ_SHOW */ {
        /* Entry Scene   */ &scene_quiz_show,
        /* Level Name    */ "Quiz Show",
        /* Level Desc.   */ "Play a quiz where you\n"
                            "copy the host's pattern.\n"
                            "Seems simple, right?\n"
                            "Simple, but not easy.",
        /* Level Icon    */ 43,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_quiz_show_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I can do better... I can do better...",
            /* OK        */ "I have to study... for next time... Zzz...",
            /* SUPERB    */ "I won the grand prize! A world tour!"
        }
    },
    /* BON_ODORI */ {
        /* Entry Scene   */ &scene_bon_odori,
        /* Level Name    */ "TheÅôBon Odori",
        /* Level Desc.   */ "Let's celebrate the\n"
                            "Japanese Bon Festival!\n"
                            "Clap along as they sing\n"
                            "their traditional song!",
        /* Level Icon    */ 35,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bon_odori_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I feel so cold...",
            /* OK        */ "Oh... the quaint fizzle of a sparkler...",
            /* SUPERB    */ "That was so much fun! I can't wait for next year!"
        }
    },
    /* BON_DANCE */ {
        /* Entry Scene   */ &scene_bon_dance,
        /* Level Name    */ "Bon Dance",
        /* Level Desc.   */ "The Bon Festival has\n"
                            "a new, modern look!\n"
                            "Clap along to the\n"
                            "groovy tune! Yay!",
        /* Level Icon    */ 17,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bon_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "It's over...",
            /* OK        */ "When did it start raining?",
            /* SUPERB    */ "Our new Bon Dance is a lot of fun!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_1 */ {
        /* Entry Scene   */ &scene_remix_1,
        /* Level Name    */ "Remix ÇP",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "Stage 1's games have\n"
                            "all been remixed!\n"
                            "Think you can beat it?",
        /* Level Icon    */ 22,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix1_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your performance was like... a cat's snack.",
            /* OK        */ "Your preformance was like... an ordinary breakfast.",
            /* SUPERB    */ "Your performance was like... why, a delicious dinner!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_2 */ {
        /* Entry Scene   */ &scene_remix_2,
        /* Level Name    */ "Remix ÇQ",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This one's got a lively\n"
                            "atmosphere perfect\n"
                            "for dance lessons!",
        /* Level Icon    */ 27,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "That was as lively as... playing ball by yourself.",
            /* OK        */ "That was as lively as... a pleasant game of catch.",
            /* SUPERB    */ "That was as lively as... a huge baseball tournament!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_3 */ {
        /* Entry Scene   */ &scene_remix_3,
        /* Level Name    */ "Remix ÇR",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This one's got an\n"
                            "adorable love song with\n"
                            "adorable love lyrics!",
        /* Level Icon    */ 33,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix3_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Their love ended in... heartbreak...",
            /* OK        */ "Their love ended in... a good friendship.",
            /* SUPERB    */ "Their love ended in... a tender marriage!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_4 */ {
        /* Entry Scene   */ &scene_remix_4,
        /* Level Name    */ "Remix ÇS",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This one's got a casual,\n"
                            "easygoing vibe, like a\n"
                            "nice, pleasant stroll...",
        /* Level Icon    */ 34,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix4_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Today's forecast... raining buckets.",
            /* OK        */ "Today's forecast... very cloudy.",
            /* SUPERB    */ "Today's forecast... clear skies all day!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_5 */ {
        /* Entry Scene   */ &scene_remix_5,
        /* Level Name    */ "Remix ÇT",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This one's got some\n"
                            "melancholic lyrics.\n"
                            "Try to keep your cool!",
        /* Level Icon    */ 39,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix5_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "This couple is... in trouble!",
            /* OK        */ "This couple is... a little nervous...",
            /* SUPERB    */ "This couple is... living their happy-ever-after!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_6 */ {
        /* Entry Scene   */ &scene_remix_6,
        /* Level Name    */ "Remix ÇU",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "Every game you've\n"
                            "played is here! Show\n"
                            "us what you've learned!",
        /* Level Icon    */ 2,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix6_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your fish tank is... pretty sparse.",
            /* OK        */ "Your fish tank is... unique for sure!",
            /* SUPERB    */ "Your fish tank is... unbelievable!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_7 */ {
        /* Entry Scene   */ &scene_remix_7,
        /* Level Name    */ "Remix ÇV",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "A lot of the Remixes\n"
                            "make a comeback here!\n"
                            "It's a Remix Remix!",
        /* Level Icon    */ 19,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix7_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your Jurassic visit was... terrifying!",
            /* OK        */ "Your Jurassic visit was... rather tame.",
            /* SUPERB    */ "Your Jurassic visit was... too much fun!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_8 */ {
        /* Entry Scene   */ &scene_remix_8,
        /* Level Name    */ "Remix ÇW",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This final remix is a\n"
                            "real challenge! Show\n"
                            "us what you've learned!",
        /* Level Icon    */ 37,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix8_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your road trip was... oh boy...",
            /* OK        */ "Your road trip was... a little long.",
            /* SUPERB    */ "Your road trip was... absolutely spectacular!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* CAFE */ {
        /* Entry Scene   */ &scene_cafe,
        /* Level Name    */ "Caf" "\x87\x51"" Counselling",
        /* Level Desc.   */ "How are you feeling?\n"
                            "If something's on your\n"
                            "mind, feel free to\n"
                            "come and talk.",
        /* Level Icon    */ 45,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_cafe_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* RHYTHM_TOYS */ {
        /* Entry Scene   */ &scene_toys_menu,
        /* Level Name    */ "Rhythm Toys",
        /* Level Desc.   */ "Collect medals to\n"
                            "play with some\n"
                            "Rhythm Toys!\n"
                            "Check them out!",
        /* Level Icon    */ 46,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_toys_menu_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* ENDLESS_GAMES */ {
        /* Entry Scene   */ &scene_endless_menu,
        /* Level Name    */ "Endless Games",
        /* Level Desc.   */ "Collect medals to\n"
                            "unlock special\n"
                            "Endless Games!\n"
                            "Check them out!",
        /* Level Icon    */ 47,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_endless_menu_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* DRUM_LESSONS */ {
        /* Entry Scene   */ &scene_lessons_menu,
        /* Level Name    */ "Drum Lessons",
        /* Level Desc.   */ "Collect medals to take\n"
                            "some Drum Lessons.\n"
                            "You could become\n"
                            "a master drummer!",
        /* Level Icon    */ 48,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_lessons_menu_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* STAFF_CREDIT */ {
        /* Entry Scene   */ &scene_staff_credit,
        /* Level Name    */ "Staff Credits",
        /* Level Desc.   */ "Here's the staff who\n"
                            "helped develop\n"
                            "this game. Feel free\n"
                            "to take a look!",
        /* Level Icon    */ 49,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_staff_credit_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* LIVE_MENU */ {
        /* Entry Scene   */ &scene_drum_live,
        /* Level Name    */ "Concert",
        /* Level Desc.   */ "We're hosting a\n"
                            "concert! We think\n"
                            "you've got good rhythm,\n"
                            "so give it a try!",
        /* Level Icon    */ 44,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_drum_live_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "The cleaner says... \"I know you can do it, keep it up!\"",
            /* OK        */ "The owner says... \"You've got great skills, you know!\"",
            /* SUPERB    */ "The producer says... \"You should play at our place, too!\""
        }
    },
    /* KARATE_MAN */ {
        /* Entry Scene   */ &scene_karate_man_extra,
        /* Level Name    */ "Karate Man",
        /* Level Desc.   */ "We've increased the\n"
                            "speed! Do your best\n"
                            "as we throw more\n"
                            "stuff for you to punch.",
        /* Level Icon    */ 54,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "The tournament didn't go well...",
            /* OK        */ "I did well at the tournament, even if I didn't win.",
            /* SUPERB    */ "I won the tournament and took home the gold!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RHYTHM_TWEEZERS */ {
        /* Entry Scene   */ &scene_rhythm_tweezers_extra,
        /* Level Name    */ "Rhythm Tweezers",
        /* Level Desc.   */ "My roots are showing!\n"
                            "Don't let the speed stop\n"
                            "you from plucking them!\n",
        /* Level Icon    */ 55,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I can't pluck anything at this speed!",
            /* OK        */ "These hairs are pretty tough to pluck.",
            /* SUPERB    */ "Look at those flowers! They're so refreshing!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* MARCHING_ORDERS */ {
        /* Entry Scene   */ &scene_marching_orders_extra,
        /* Level Name    */ "Marching Orders",
        /* Level Desc.   */ "Ready, march!\n"
                            "This mission will\n"
                            "require quick marching,\n"
							"so keep focused!",
        /* Level Icon    */ 56,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "MONSTER! Retreat! Retreat!",
            /* OK        */ "Ah, there's the lost puppy!",
            /* SUPERB    */ "We've successfully rescued the lost puppy! Hooray!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SPACEBALL */ {
        /* Entry Scene   */ &scene_spaceball_extra,
        /* Level Name    */ "Spaceball",
        /* Level Desc.   */ "Ignore the camera's wild\n"
                            "zooms! Make the ball\n"
                            "fly wildly away!\n"
                            "Don't lose to the speed!",
        /* Level Icon    */ 57,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Ahhh! Nooooooo!",
            /* OK        */ "Graaaah!",
            /* SUPERB    */ "A home run! I did it!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* CLAPPY_TRIO */ {
        /* Entry Scene   */ &scene_clappy_trio_extra,
        /* Level Name    */ "The Clappy Trio",
        /* Level Desc.   */ "Clap your hands in\n"
                            "order! You're the third\n"
                            "clapper. Watch out for\n"
							"your quick friends!",
        /* Level Icon    */ 58,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_clappy_trio_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Wait! Don't leave without us!",
            /* OK        */ "This is one nice space cruise!",
            /* SUPERB    */ "I've discovered a new planet! Great!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_1 */ {
        /* Entry Scene   */ &scene_remix_1_extra,
        /* Level Name    */ "Remix ÇP",
        /* Level Desc.   */ "This is the Extra Remix.\n"
                            "Can you keep up with\n"
                            "its speed? Good luck\n"
                            "and have fun!",
        /* Level Icon    */ 59,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix1_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "This is going to take a while...",
            /* OK        */ "Just a normal chick. \"Cheep-Cheep!\"",
            /* SUPERB    */ "You've grown splendidly! You look dignified!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    }
};
