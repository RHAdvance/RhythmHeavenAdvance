// Level Entries Table
struct LevelData level_data_table[] = {
    /* KARATE_MAN */ {
        /* Entry Scene   */ &scene_karate_man,
        /* Level Name    */ "KaratáQka",
        /* Level Desc.   */ "Il faut du rythme,\n"
                            "pour un beau karatáQ.\n"
                            "Faites parler vos\n"
                            "poings en cadenceáR!",
        /* Level Icon    */ 8,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "J'y arriverai peut-àÆtre mieux demain...",
            /* OK        */ "Petite pause dáQjeuneráR!",
            /* SUPERB    */ "J'en ai frappáQ des trucsáR!"
        }
    },
    /* KARATE_MAN_2 */ {
        /* Entry Scene   */ &scene_karate_man_2,
        /* Level Name    */ "KaratáQka 2",
        /* Level Desc.   */ "Concentrez-vous\n"
                            "sur le tempo, il\n"
                            "risque de vous\n"
                            "jouer des tours...",
        /* Level Icon    */ 0,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "What's the point of these speed switchups, anyway!?", /* TODO: Trad */
            /* OK        */ "Well, that's that. Let's eat!", /* TODO: Trad */
            /* SUPERB    */ "I think we went through everything!" /* TODO: Trad */
        }
    },
    /* CLAPPY_TRIO */ {
        /* Entry Scene   */ &scene_clappy_trio,
        /* Level Name    */ "Trio clap clap",
        /* Level Desc.   */ "Vous àÆtes le 3e\n"
                            "membre d'un trio de\n"
                            "clappeurs, regardez\n"
							"bien vos camaradesáR!",
        /* Level Icon    */ 4,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_clappy_trio_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "OháR! Les deux autres sont dáQjág partisáR!",
            /* OK        */ "C'est encore un peu tà∂t pour sauter de joieáR!",
            /* SUPERB    */ "Ces trois-lág sont comme un seul hommeáR!"
        }
    },
    /* SNAPPY_TRIO */ {
        /* Entry Scene   */ &scene_snappy_trio,
        /* Level Name    */ "Trio western clap",
        /* Level Desc.   */ "Inspiration western\n"
                            "pour votre nouveau\n"
                            "morceau, et avec la\n"
                            "tenue qu'il fautáR!",
        /* Level Icon    */ 10,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_snappy_trio_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "C'est l'inconváQnient de jouer dans un western...",
            /* OK        */ "Es-tu sur de vouloir devenir un parfait clappeuráR?", /* TODO: s?r */
            /* SUPERB    */ "On est encore meilleurs avec ces costumesáR!"
        }
    },
    /* POLYRHYTHM */ {
        /* Entry Scene   */ &scene_polyrhythm,
        /* Level Name    */ "Polyrythme",
        /* Level Desc.   */ "S'occuper de deux\n"
							"chaà≤nes de bidules\n"
							"en alternant áO et áM...\n"
							"àπa devrait àÆtre facileáR!",
        /* Level Icon    */ 3,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_polyrhythm_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "La production de masse s'aváare plus difficile que práQvue...",
            /* OK        */ "On arrive ág en produire de plus en plusáR!",
            /* SUPERB    */ "On en a produit plus qu'on ne peut en stockeráR!"
        }
    },
    /* POLYRHYTHM_2 */ {
        /* Entry Scene   */ &scene_polyrhythm_2,
        /* Level Name    */ "Polyrythme 2",
        /* Level Desc.   */ "La production de\n"
                            "bidules accáQláareáR!\n"
                            "áPvitez de prendre\n"
                            "du retardáR!",
        /* Level Icon    */ 51,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_polyrhythm_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Il nous faut produire beaucoup plus de ces bidules...",
            /* OK        */ "En produire plus ne ferait pas de maláR!",
            /* SUPERB    */ "Nous en produirons toujours plusáR!"
        }
    },
    /* NIGHT_WALK */ {
        /* Entry Scene   */ &scene_night_walk,
        /* Level Name    */ "Balade nocturne",
        /* Level Desc.   */ "Rien de tel qu'une\n"
                            "balade de nuit pleine de\n"
                            "rythme et de poáQsie pour\n"
                            "oublier ses soucis.",
        /* Level Icon    */ 7,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_night_walk_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Les trous se confondent dans la nuit...",
            /* OK        */ "Rien de tel qu'une petite promenade ág la belle áQtoileáR!",
            /* SUPERB    */ "J'ai l'impression de ne faire qu'un avec la voie lactáQeáR!"
        }
    },
    /* NIGHT_WALK_2 */ {
        /* Entry Scene   */ &scene_night_walk_2,
        /* Level Name    */ "Balade nocturne 2",
        /* Level Desc.   */ "Quelle belle nuit...\n"
                            "mais attention\n"
                            "aux poissons\n"
                            "?lectriquesáR!",
        /* Level Icon    */ 41,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_night_walk_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "NooonnnáR! Je suis tombáQáR!",
            /* OK        */ "Rien de tel que la fraà≤cheur de la nuit.",
            /* SUPERB    */ "Me voilág devenu l'ami des áQtoilesáR!"
        }
    },
    /* RHYTHM_TWEEZERS */ {
        /* Entry Scene   */ &scene_rhythm_tweezers,
        /* Level Name    */ "Pince poilante",
        /* Level Desc.   */ "Faites la peau\n"
                            "aux poils et la\n"
                            "peau lisse ág\n"
                            "vos clientsáR!",
        /* Level Icon    */ 14,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Je ne peux màÆme pas les vendreáR!",
            /* OK        */ "Pourquoi mes oignons sont-ils poilusáR?",
            /* SUPERB    */ "So fresh and clean! Even the air tastes delicious!" /* TODO: Trad */
        }
    },
    /* RHYTHM_TWEEZERS_2 */ {
        /* Entry Scene   */ &scene_rhythm_tweezers_2,
        /* Level Name    */ "Pince poilante 2",
        /* Level Desc.   */ "Ces oignons sont\n"
                            "encore plus poilusáR!\n"
                            "Faites chauffer\n"
                            "votre pinceáR!",
        /* Level Icon    */ 25,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Pourquoi il faut qu'ils soient si poilus...áR?",
            /* OK        */ "Pourquoi suis-je le seul qui fait pousser des oignons poilusáR?",
            /* SUPERB    */ "Il n'y a plus un poil ág l'horizonáR!"
        }
    },
    /* SICK_BEATS */ {
        /* Entry Scene   */ &scene_sick_beats,
        /* Level Name    */ "Tempo labo",
        /* Level Desc.   */ "\0023" "Note de l'assistantáR:\n"
                            "Nous subissons une\n"
                            "áQpidáQmie de virusáR!\n"
                            "Aidez-nousáR!",
        /* Level Icon    */ 13,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_sick_beats_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Toutes nos recherches... n'ont abouti ág rien...",
            /* OK        */ "L'áQchec pourrait àÆtre la cláQ du succáasáR!",
            /* SUPERB    */ "EuràÆkaáR! Nous avons trouváQ l'antidoteáR!"
        }
    },
    /* BOUNCY_ROAD */ {
        /* Entry Scene   */ &scene_bouncy_road,
        /* Level Name    */ "Tempo máQcano",
        /* Level Desc.   */ "Ces petites balles\n"
                            "attendent un coup de\n"
                            "pouce de votre part pour\n"
							"arriver ág destination.",
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
        /* Level Name    */ "Tempo máQcano 2",
        /* Level Desc.   */ "Ces balles ont\n"
                            "quelque chose\n"
                            "d'attachant, nonáR?\n"
                            "ProtáQgez-lesáR!",
        /* Level Icon    */ 50,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bouncy_road_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Ow! We failed!",
            /* OK        */ "We're working our hardest!",
            /* SUPERB    */ "Easy come, easy go."
        }
    },
    /* NINJA_BODYGUARD */ {
        /* Entry Scene   */ &scene_ninja_bodyguard,
        /* Level Name    */ "Protection ninja",
        /* Level Desc.   */ "Votre seigneur est la\n"
                            "cible du clan ennemiáR!\n"
                            "Bloquez les fláaches\n"
							"en alternant áO et áMáR!",
        /* Level Icon    */ 5,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_ninja_bodyguard_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "My lord has fainted! Nooooo!",
            /* OK        */ "I cannot apologize enough, my lord!",
            /* SUPERB    */ "Not a scratch!"
        }
    },
    /* NINJA_REINCARNATE */ {
        /* Entry Scene   */ &scene_ninja_reincarnate,
        /* Level Name    */ "Descendance ninja",
        /* Level Desc.   */ "Prenez gardeáR!\n"
                            "J'ai háQritáQ du sang\n"
                            "ninja de mes\n"
                            "ancàÆtresáR!",
        /* Level Icon    */ 38,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_ninja_reincarnate_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "You can't give up now! We're counting on you!",
            /* OK        */ "You are... strong. Don't give up yet.",
            /* SUPERB    */ "You have proven your worth! You have our blessing..."
        }
    },
    /* SNEAKY_SPIRITS */ {
        /* Entry Scene   */ &scene_sneaky_spirits,
        /* Level Name    */ "Esprits espiáagles",
        /* Level Desc.   */ "Ces ectoplasmes se\n"
                            "moquent de vousáR!\n"
                            "Faites-leur tater\n"
                            "de vos fláachesáR!",
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
        /* Level Name    */ "Esprits espiáagles 2",
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
        }
    },
    /* SAMURAI_SLICE */ {
        /* Entry Scene   */ &scene_samurai_slice,
        /* Level Name    */ "Rythme tranchant",
        /* Level Desc.   */ "Des dáQmons sáament\n"
                            "la panique en ville.\n"
                            "Samouraà¥áR! Tranchez-\n"
                            "les jusqu'au dernieráR!",
        /* Level Icon    */ 18,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_samurai_slice_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I've broken my blade!",
            /* OK        */ "I shall push myself harder!",
            /* SUPERB    */ "Have you ever seen a sword this sharp?"
        }
    },
    /* SPACEBALL */ {
        /* Entry Scene   */ &scene_spaceball,
        /* Level Name    */ "Baseball de l'espace",
        /* Level Desc.   */ "Restez concentráQ sur\n"
                            "la balle et ne vous\n"
                            "laissez pas tromper par\n"
                            "les effets de camáQra.",
        /* Level Icon    */ 9,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Can I have my ball back? I'll give you my last rice ball...",
            /* OK        */ "Must... train... harder...",
            /* SUPERB    */ "I won first \"space\"!"
        }
    },
    /* SPACEBALL_2 */ {
        /* Entry Scene   */ &scene_spaceball_2,
        /* Level Name    */ "Baseball de l'espace 2",
        /* Level Desc.   */ "Concentrez-vous,\n"
                            "frappez la balle\n"
                            "et essayez de ne\n"
                            "pas pleurer.",
        /* Level Icon    */ 52,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Next time, swing your bat somewhere else!",
            /* OK        */ "I can't give up now!",
            /* SUPERB    */ "Guys, guys, look at what I've won!"
        }
    },
    /* TAP_TRIAL */ {
        /* Entry Scene   */ &scene_tap_trial,
        /* Level Name    */ "Claquettes",
        /* Level Desc.   */ "Suivez bien les petits\n"
                            "singes pour montrer\n"
                            "que vous àÆtes la\n"
                            "meilleure danseuseáR!",
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
        /* Level Name    */ "Super claquettes",
        /* Level Desc.   */ "Vos amis singes sont\n"
                            "de retour avec une\n"
                            "choráQgraphie ináQditeáR!\n"
                            "áf vous de joueráR!",
        /* Level Icon    */ 11,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tap_trial_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Looks like we tapped TOO hard!",
            /* OK        */ "Hey... Where'd our rhythm go?",
            /* SUPERB    */ "Monkeys are the key to tappiness!"
        }
    },
    /* MARCHING_ORDERS */ {
        /* Entry Scene   */ &scene_marching_orders,
        /* Level Name    */ "En avant, marcheáR!",
        /* Level Desc.   */ "Le rythme fait l'union\n"
                            "...et l'union fait la forceáR!\n"
                            "Suivez les ordres\n"
							"du sergent bedonnantáR!",
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
        /* Level Name    */ "En avant, marche 2",
        /* Level Desc.   */ "Cette fois, c'est le\n"
                            "sergent qui est aux\n"
                            "ordresáR! ObáQissez au\n"
                            "nouveau chef lapináR!",
        /* Level Icon    */ 20,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "This is unacceptable...",
            /* OK        */ "I know we can perform better than that!",
            /* SUPERB    */ "Now THIS is a reward!"
        }
    },
    /* WIZARDS_WALTZ */ {
        /* Entry Scene   */ &scene_wizards_waltz,
        /* Level Name    */ "Valse du sorcier",
        /* Level Desc.   */ "Il suffit d'un peu de\n"
                            "magie et de rythme\n"
                            "pour redonner le\n"
                            "sourire a une enfantáR!",
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
        /* Level Name    */ "Lago salto",
        /* Level Desc.   */ "Les lapins aiment\n"
                            "sauter, c'est un fait,\n"
                            "mais celui-ci pousse le\n"
                            "concept un peu loin...",
        /* Level Icon    */ 24,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bunny_hop_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I'm not sure I thought this through...",
            /* OK        */ "Didn't quite stick the landing...",
            /* SUPERB    */ "A perfect landing! Who needs rockets?!"
        }
    },
    /* FIREWORKS */ {
        /* Entry Scene   */ &scene_fireworks,
        /* Level Name    */ "Feux d'artifice",
        /* Level Desc.   */ "C'est la saison\n"
                            "des feux d'artificeáR!\n"
                            "Regardez-moi ces\n"
                            "jolies couleursáR!",
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
        /* Level Name    */ "Calligraphie",
        /* Level Desc.   */ "áPcrivez de beaux\n"
                            "caractáares avec votre\n"
                            "pinceauáR! Ne ratez\n"
                            "pas les finitionsáR!",
        /* Level Icon    */ 28,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_power_power_calligraphy_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Maybe I should stick with pencils...",
            /* OK        */ "Precision! Grace! What's not to like?",
            /* SUPERB    */ "Woo! Calligraphy party!"
        }
    },
    /* POWER_CALLIGRAPHY_2 */ {
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
        }
    },
    /* TOSS_BOYS */ {
        /* Entry Scene   */ &scene_toss_boys,
        /* Level Name    */ "Fous du ballon",
        /* Level Desc.   */ "Entraà≤nez-vous au\n"
                            "lancer de ballon\n"
                            "avec ces trois\n"
                            "amis insáQparablesáR!",
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
        /* Level Name    */ "Fous du ballon 2",
        /* Level Desc.   */ "Nos trois sportifs\n"
                            "ont besoin de\n"
                            "votre aide pour se\n"
                            "perfectionneráR!",
        /* Level Icon    */ 29,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_toss_boys_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Our spirits have been deflated...",
            /* OK        */ "We still have a long way to go!",
            /* SUPERB    */ "Three cheers for our star tosser!"
        }
    },
    /* RAT_RACE */ {
        /* Entry Scene   */ &scene_rat_race,
        /* Level Name    */ "Rats cache-cache",
        /* Level Desc.   */ "Que ne ferait pas un\n"
                            "rat pour un bout de\n"
                            "tomme ou d'emmentaláR?\n"
                            "Attention au chatáR!",
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
        /* Level Name    */ "Gontran & Pauline",
        /* Level Desc.   */ "Ces renards sont les\n"
                            "pros des acrobatiesáR!\n"
                            "Vite, leur spectacle\n"
							"va commenceráR!",
        /* Level Icon    */ 32,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tram_pauline_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We've transformed the show into a failure!",
            /* OK        */ "At least we only messed up half the show...",
            /* SUPERB    */ "We're the perfect duo!"
        }
    },
    /* SHOWTIME */ {
        /* Entry Scene   */ &scene_showtime,
        /* Level Name    */ "Spectacle animalier",
        /* Level Desc.   */ "Le spectacle des\n"
                            "pingouins affiche\n"
                            "completáR! Faites\n"
                            "vibrer le publicáR!",
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
        /* Level Name    */ "Danse spatiale",
        /* Level Desc.   */ "Danser sur la terre\n"
                            "fermeáR? Trop banal.\n"
                            "Sans gravitáQ, c'est\n"
							"une vraie nouveautáQáR!",
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
        /* Level Name    */ "Danse cosmique",
        /* Level Desc.   */ "Vous àÆtes devenus\n"
                            "de váQritables experts,\n"
                            "votre show va\n"
                            "conquáQrir l'universáR!",
        /* Level Icon    */ 16,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_cosmic_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We cannot go on like THIS!",
            /* OK        */ "Is that the best you guys can do?",
            /* SUPERB    */ "We are cosmic superstars!"
        }
    },
    /* RAP_MEN */ {
        /* Entry Scene   */ &scene_rap_men,
        /* Level Name    */ "Mecs du rap",
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
        /* Level Name    */ "Nanas du rap",
        /* Level Desc.   */ "Les rivales des\n"
                            "rappeurs sont lágáR!\n"
                            "áPcoutez leurs\n"
                            "charmantes voixáR!",
        /* Level Icon    */ 15,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rap_women_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "No... This isn't right.",
            /* OK        */ "I know we can rap better than this!",
            /* SUPERB    */ "Yes, yes, YES! We've got it!"
        }
    },
    /* QUIZ_SHOW */ {
        /* Entry Scene   */ &scene_quiz_show,
        /* Level Name    */ "Question de rythme",
        /* Level Desc.   */ "Pour gagner, il faut\n"
                            "savoir compteráR!\n"
                            "Cependant, avoir le\n"
                            "rythme peut aider...",
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
        /* Level Name    */ "LeÅôBon Odori",
        /* Level Desc.   */ "Voici le traditionnel\n"
                            "festival du Bon OdoriáR!\n"
                            "Tapez des mains et\n"
                            "suivez nos voixáR!",
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
        /* Level Name    */ "LaÅôBon Dance",
        /* Level Desc.   */ "Le Bon Odori est\n"
                            "de retour, faites\n"
                            "de ce festival\n"
                            "une ráQussiteáR!",
        /* Level Icon    */ 17,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bon_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "It's over...",
            /* OK        */ "When did it start raining?",
            /* SUPERB    */ "Our new Bon Dance is a lot of fun!"
        }
    },
    /* REMIX_1 */ {
        /* Entry Scene   */ &scene_remix_1,
        /* Level Name    */ "Remix 1",
        /* Level Desc.   */ "Dans ce remix... vous\n"
                            "attendent les jeux que\n"
                            "vous venez de faireáR!\n"
                            "Vous pensez y arriveráR?",
        /* Level Icon    */ 22,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix1_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your performance was like... a cat's snack.",
            /* OK        */ "Your preformance was like... an ordinary breakfast.",
            /* SUPERB    */ "Your performance was like... why, a delicious dinner!"
        }
    },
    /* REMIX_2 */ {
        /* Entry Scene   */ &scene_remix_2,
        /* Level Name    */ "Remix 2",
        /* Level Desc.   */ "Voici un remix pour\n"
                            "le moins entraà≤nantáR!\n"
                            "Ne vous donne-t-il\n"
                            "pas envie de danseráR?",
        /* Level Icon    */ 27,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "That was as lively as... playing ball by yourself.",
            /* OK        */ "That was as lively as... a pleasant game of catch.",
            /* SUPERB    */ "That was as lively as... a huge baseball tournament!"
        }
    },
    /* REMIX_3 */ {
        /* Entry Scene   */ &scene_remix_3,
        /* Level Name    */ "Remix 3",
        /* Level Desc.   */ "La chanson d'amour\n"
                            "de ce remix saura\n"
                            "probablement vous\n"
                            "rendre le sourireáR!",
        /* Level Icon    */ 33,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix3_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Their love ended in... heartbreak...",
            /* OK        */ "Their love ended in... a good friendship.",
            /* SUPERB    */ "Their love ended in... a tender marriage!"
        }
    },
    /* REMIX_4 */ {
        /* Entry Scene   */ &scene_remix_4,
        /* Level Name    */ "Remix 4",
        /* Level Desc.   */ "Ce remix vous fait\n"
                            "voir flouáR? Vous pouvez\n"
                            "compter sur votre\n"
                            "sens du rythmeáR!",
        /* Level Icon    */ 34,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix4_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Today's forecast... raining buckets.",
            /* OK        */ "Today's forecast... very cloudy.",
            /* SUPERB    */ "Today's forecast... clear skies all day!"
        }
    },
    /* REMIX_5 */ {
        /* Entry Scene   */ &scene_remix_5,
        /* Level Name    */ "Remix 5",
        /* Level Desc.   */ "Votre sens du\n"
                            "rythme saura rendre\n"
                            "ce clip musical...\n"
                            "exceptionneláR!",
        /* Level Icon    */ 39,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix5_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "This couple is... in trouble!",
            /* OK        */ "This couple is... a little nervous...",
            /* SUPERB    */ "This couple is... living their happy-ever-after!"
        }
    },
    /* REMIX_6 */ {
        /* Entry Scene   */ &scene_remix_6,
        /* Level Name    */ "Remix 6",
        /* Level Desc.   */ "On y estáR! Tous les\n"
                            "mini-jeux sont lág,\n"
                            "montrez-nous ce dont\n"
                            "vous àÆtes capableáR!",
        /* Level Icon    */ 2,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix6_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your fish tank is... pretty sparse.",
            /* OK        */ "Your fish tank is... unique for sure!",
            /* SUPERB    */ "Your fish tank is... unbelievable!"
        }
    },
    /* REMIX_7 */ {
        /* Entry Scene   */ &scene_remix_7,
        /* Level Name    */ "Remix 7",
        /* Level Desc.   */ "C'est parti pour le\n"
                            "remix des remixesáR!\n"
                            "Ne vous laissez pas\n"
                            "dáQconcentreráR!",
        /* Level Icon    */ 19,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix7_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your Jurassic visit was... terrifying!",
            /* OK        */ "Your Jurassic visit was... rather tame.",
            /* SUPERB    */ "Your Jurassic visit was... too much fun!"
        }
    },
    /* REMIX_8 */ {
        /* Entry Scene   */ &scene_remix_8,
        /* Level Name    */ "Remix 8",
        /* Level Desc.   */ "Voici le remix final\n"
                            "qui mettra votre\n"
                            "sens du rythme\n"
                            "ág l'áQpreuveáR!",
        /* Level Icon    */ 37,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix8_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your road trip was... oh boy...",
            /* OK        */ "Your road trip was... a little long.",
            /* SUPERB    */ "Your road trip was... absolutely spectacular!"
        }
    },
    /* CAFE */ {
        /* Entry Scene   */ &scene_cafe,
        /* Level Name    */ "CafáQ",
        /* Level Desc.   */ "Tout va bienáR? Si vous\n"
                            "avez une petite envie\n"
                            "de parler, n'háQsitez pas\n"
                            "ág venir nous voiráR!",
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
        /* Level Name    */ "Jouets rythmáQs",
        /* Level Desc.   */ "Venez jouer avec\n"
                            "ces jouetsáR! Tout\n"
                            "le monde aime\n"
                            "s'amuser, nonáR?",
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
        /* Level Name    */ "Jeux infinis",
        /* Level Desc.   */ "DáQbloquez des\n"
                            "mini-jeux sans fin\n"
                            "et amusez-vous\n"
                            "sans freináR!",
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
        /* Level Name    */ "Cours de batterie",
        /* Level Desc.   */ "Obtenez des máQdailles\n"
                            "et maà≤trisez la batterie\n"
                            "comme un proáR!\n"
                            "Et en plus c'est gratuitáR!",
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
        /* Level Name    */ "CráQdits",
        /* Level Desc.   */ "Tous ceux qui ont\n"
                            "aidáQ ág faire ce jeu\n"
                            "y figurentáR! N'háQsitez\n"
                            "pas ág aller voiráR!",
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
        /* Level Name    */ "Salle de concert",
        /* Level Desc.   */ "Jouez dans un des\n"
                            "groupes de batteurs et\n"
                            "áQpatez le public avec\n"
                            "votre sens du rythmeáR!",
        /* Level Icon    */ 44,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_drum_live_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "The cleaner says... \"I know you can do it, keep it up!\"",
            /* OK        */ "The owner says... \"You've got great skills, you know!\"",
            /* SUPERB    */ "The producer says... \"You should play at our place, too!\""
        }
    }
};
