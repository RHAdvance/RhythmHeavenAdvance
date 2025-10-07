// [D_089d7e74] Reading Material Table
struct ReadingMaterial reading_material_table[] = {
    /* WELCOME ("Rhythm Tengoku Welcome") */ {
        /* TITLE ---------------------------------------------------------- */
            "Greetings",
        /* BODY ----------------------------------------------------------- */
            "Greetings!\n"
            "\n"
            "Thank you very much for purchasing\n"
            "Rhythm Heaven Advance.\n"
            "Oh... you've borrowed it from a friend?\n"
            "A-and it's... u-used?\n"
            "Well, that's beside the point. The fact is, we're truly\n"
            "honored that you've put your interest into this game.\n"
            "It's been nice meeting you, and we hope this game\n"
            "gives you joy and fulfillment for years to come!\n"
            "Thank you very much!",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    },

    /* MANUAL ("Handling Instructions") */ {
        /* TITLE ---------------------------------------------------------- */
            "How to play",
        /* BODY ----------------------------------------------------------- */
            "How to play the game:\n"
            "\n"
            "Well, this is a pretty straightforward game.\n"
            "What can I really say...?\n"
            "Oh, right, the idea is to play along to the music, \n"
            "so try to feel the flow when you play. That's my advice!\n"
            "And that's about it. Pleasure to meet you, by the way!",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_cherry_gfx_table,
            /* BGM */ &reading_style_cherry_bgm
        /* ---------------------------------------------------------------- */
    },

    /* CAFE ("More Than a Barista") */ {
        /* TITLE ---------------------------------------------------------- */
            "From the Barista",
        /* BODY ----------------------------------------------------------- */
            "I own and operate a Caf" "\x87\x51"".\n"
            "Or, to put it simple, I'm the barista.\n"
            "It's going well thanks to the regulars\n"
            "And, uh, just to let you know, I'm a dog.\n"
            "Many of my customers love listening to music.\n"
            "A lot of them even achieved Perfect Campaigns!\n"
            "I was pretty surprised to learn that.\n"
            "I may look all professional when I run my Caf" "\x87\x51""\n"
            "but I'll be honest, I'm really putting on a front.\n"
            "See, it's a little embarrassing, but when I'm off the\n"
            "clock, I'm always jamming out with these little\n"
            "dog-sized headphones! What can I say?\n"
            "I need a little flow wherever I go.\n"
            "It's complicated. Heh...\n"
            "I do go out from time to time, so if you happen to\n"
            "run into me... please pet me!\n"
            "See you around.",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_TWEEZERS ("Letter to the Editor") */ {
        /* TITLE ---------------------------------------------------------- */
            "Plucking Letter",
        /* BODY ----------------------------------------------------------- */
            "I'm an old gentleman who maintains a vegetable\n"
            "farm. So, one day, all my vegetables just started\n"
            "growing hair!\n"
            "It was so creepy! I couldn't sell them like that!\n"
            "I tried plucking the hairs, but I just couldn't get them\n"
            "all nice and smooth like a vegetable ought to be.\n"
            "Well, to lighten up the mood, I put on some music.\n"
            "Before I knew it, I found myself plucking to the beat.\n"
            "And... I plucked them clean! And it's even a little fun!\n"
            "The power of music is really something else!\n"
            "You've got to try plucking hairs off of your\n"
            "vegetables!\n"
            "I can't recommend it enough!",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* NIGHT_WALK ("Night Walk Riddle") */ {
        /* TITLE ---------------------------------------------------------- */
            "Night Walk Information",
        /* BODY ----------------------------------------------------------- */
            "There's this strange fellow who you might recognize\n"
            "from Night Walk. He seems to really love music.\n"
            "Apparently he's worked with music before,\n"
            "and landed a role in this game through connections.\n"
            "I ran into him in the city one time. All he said was\n"
            "\"I love music!\", and just disappeared up some stairs.\n"
            "I wonder if I'll ever meet that music-loving guy again.\n"
            "Come to think of it, I don't even know his name...\n"
            "\n"
            "Okay, time for a quiz!\n"
            "His name is...\n"
            "\n"
            "\001C" "\0031" "\001m" "á@áAáBáC-áCáBáD\n"
            "\001L" "\0030" "\001s" "\n"
            "Answer which letters go in each of the numbers!\n"
            "If you answer correctly, you'll be able to read the\n"
            "following text!\n"
            "\n"
            "\0031" "\001m" "\001C" "Secret of the\n"
            "\"Quiz Show\"game\n"
            "\0030" "\001s" "\001C" "\n"
            "In this g" "\0031" "\001m" "áB" "\0030" "\001s" "me, the" "\0031" "\001m" "á@áAáBáC" "\0030" "\001s" "er has to m" "\0031" "\001m" "áB" "\0030" "\001s" "tch\n"
            "\0030" "\001s" "the host's " "\0031" "\001m" "áD" "\0030" "\001s" "umber of button " "\0031" "\001m" "á@" "\0030" "\001s" "resses. But\n"
            "\0030" "\001s" "if you mash the butto" "\0031" "\001m" "áD" "\0030" "\001s" "s rea" "\0031" "\001m" "áAáA" "\0030" "\001s" "y f" "\0031" "\001m" "áB" "\0030" "\001s" "st instead,\n"
            "\0030" "\001s" "somethi" "\0031" "\001m" "áD" "\0030" "\001s" "g interesting can h" "\0031" "\001m" "áB" "\0030" "\001s" "ppen.\n"
            "\0030" "\001s" "It's nothing crazy or an" "\0031" "\001m" "áC" "\0030" "\001s" "thing, but it's neat!",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* SPACEBALL ("Inside Spaceball") */ {
        /* TITLE ---------------------------------------------------------- */
            "Spaceball Report",
        /* BODY ----------------------------------------------------------- */
            "We're here in outer space for an exclusive interview\n"
            "with the spacefaring baseball player, the\n"
            "Space Batter!\n"
            "\n"
            "Q. How is this season looking so far?\n"
            "A. I've been eating rice balls, so it's right on the mark!\n"
            "\n"
            "Q. What would you say your goal is?\n"
            "A. To not miss any rice balls!\n"
            "Q. You have a girlfriend, right?\n"
            "A. Yes, I do.\n"
            "\n"
            "Q. What would you say is her best trait?\n"
            "A. She makes a mean rice ball!\n"
            "\n"
            "Q. Why do you wear masks in the middle of games?\n"
            "A. Hm? What do you mean?\n"
            "\n"
            "Q. Like when you wore a full rabbit costume,\n"
            "for instance?\n"
            "A. I don't know what you're talking about.\n"
            "\n"
            "Q. Please answer the question!\n"
            "A. Uh... It's time for me to go! Sorry!\n"
            "\n"
            "He's just left his seat!\n"
            "Seems there's been some kind of problem.\n"
            "That concludes this interstellar interview.",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* MECHANICAL_HORSE ("Mechanical Horse's Story") */ {
        /* TITLE ---------------------------------------------------------- */
            "Horse Machine's Story",
        /* BODY ----------------------------------------------------------- */
            "We were given the chance to interview \"Mr. F,\"\n"
            "inventor of the Horse Machine in the Rhythm Toys\n"
            "section, about its development.\n"
            "\n"
            "\n"
            "Mr. F: \"The idea came about because I just really\n"
            "wanted to share the joys of riding a horse. So\n"
            "development sort of revolved around that idea.\"\n"
            "\n"
            "Mr. F's comments were as simple as they were\n"
            "passionate.\n"
            "\n"
            "Mr. F: \"But in trying to make a game out of it, I found\n"
            "myself losing sight of that end goal. I considered\n"
            "giving up many times.\"\n"
            "\n"
            "It was a struggle for Mr. F, who found it difficult to\n"
            "express his vision within a standard framework.\n"
            "Mr. F: \"But thinking about the kinds of people who\n"
            "use the Horse Machine and get even a little joy\n"
            "out of it...\n"
            "\n"
            "Well, the hardships sort of just drift away.\"\n"
            "\n"
            "Mr. F, you are truly devoted to your craft. We look\n"
            "forward to seeing your next creations. Thank you.",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* MARCHING_ORDERS ("Marcher's Diary") */ {
        /* TITLE ---------------------------------------------------------- */
            "Squadmate Activity Log",
        /* BODY ----------------------------------------------------------- */
            "April 16: I enlisted in the Marcher group!\n"
            "I'm gonna give it my all and help everybody I can!\n"
            "\n"
            "April 20: Today I marched out of line with the others.\n"
            "Sarge gave me an earful for that one...\n"
            "\n"
            "April 28: Today we were assigned to clean the front\n"
            "of the station. This pleasant old lady came by and\n"
            "offered me some candy for my hard work.\n"
            "That made my whole day!\n"
            "\n"
            "May 4: I've been pretty sluggish lately.\n"
            "I'm not sure if that's what they mean by\n"
            "\"spring fever\".\n"
            "If I don't shape up soon, I might get shipped out...\n"
            "\n"
            "May 8: Something's up with Sarge...\n"
            "Yesterday, he told us that he's been dancing with\n"
            "some rabbits up in outer space.\n"
            "Is he... okay?\n"
            "\n"
            "May 16: Recently, I've been coming across people\n"
            "who look just like Sarge...\n"
            "It's got to be my imagination, right?\n"
            "\n"
            "May 22: You'll never believe it! Sarge is...\n"
            "\n"
            "The log ends here.\n"
            "Just what could've been happening with Sarge?",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_cherry_gfx_table,
            /* BGM */ &reading_style_cherry_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RAP_MEN ("Rap Report") */ {
        /* TITLE ---------------------------------------------------------- */
            "A Certain Radio Station",
        /* BODY ----------------------------------------------------------- */
            "Hey there! I'm DJ MON-K!\n"
            "We've got a couple of wonderful guests here today.\n"
            "Allow me to introduce the RAPMEN (RM)! Pleased\n"
            "to meet you today!\n"
            "RM: \"Hey, viewers at home! We are the RAPMEN!\"\n"
            "DJ: \"Your latest song is really good, huh?\"\n"
            "RM: \"You know it! It's pretty clear, huh?\"\n"
            "DJ: \"Uh uh! It's the GREATEST!\"\n"
            "RM: \"All that said, we're kind of in a jam right now.\"\n"
            "DJ: \"O-Oh! W-What is it?\"\n"
            "RM: \"Well first, some knock-off rap duo sprung\n"
            "up outta nowhere! They call themselves the\n"
            "'RAPWOMEN', I think.\"\n"
            "DJ: \"Maybe so, huh.\"\n"
            "RM: \"Yeah. And those wannabes ate our stash of\n"
            "snacks we kept in our dressing room!\"\n"
            "DJ: \"Unbelievable!\"\n"
            "RM: \"And if that wasn't enough, they left a little\n"
            "note for us.\"\n"
            "DJ: \"What did it say?\"\n"
            "RM: \"It said 'Sweets are the GREATEST!'\"\n"
            "DJ: \"Oh wow. That's bold.\"\n"
            "RM: \"Right!? It was enough to make me yell...\"\n"
            "DJ \"You were like, \"Hey! Who ATE IT!?\"\n"
            "RM: \"Uh... Yeah! How do you know that?\"\n"
            "DJ: \"Because I've been playing Rhythm Heaven\n"
            "Advance! Roll the commercial!\"\n"
            "AD: \"UP your flow with Rhythm Heaven Advance!\n"
            "Available now! Game and system sold separately.\"\n"
            "End.",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_cherry_gfx_table,
            /* BGM */ &reading_style_cherry_bgm
        /* ---------------------------------------------------------------- */
    },

    /* BON_ODORI ("Lyrics - The Bon Odori") */ {
        /* TITLE ---------------------------------------------------------- */
            "Lyrics Card á@",
        /* BODY ----------------------------------------------------------- */
            "TheÅôBon Odori\n"
            "Song: Ami Tokito\n"
            "Music: TSUNKU\n"
            "\n"
            "\n"
            "Haa~\n"
            "            Hanabi Agare ba~\n"
            "\n"
            "Haa~ Ah~\n"
            "            Kansei Agaru~\n"
            "\n"
            "Haa~\n"
            "            Ninki Agare ba~\n"
            "\n"
            "Haa~ Ah~\n"
            "            Kyuuryou Agaru~\n"
            "\n"
            "Matsuri da Wasshoi!\n"
            "Nippon chuu ga Wasshoi!\n"
            "\n"
            "Sore Hikkuri Kaette\n"
            "Ha~ Bon Odori~\n"
            "\n"
            "Haa~\n"
            "            Ame ga Agare ba~\n"
            "\n"
            "Haa~ Ah~\n"
            "            Yagura ni Agaru~\n"
            "\n"
            "Hora! Matsuri da Wasshoi!\n"
            "Korezo Made in Japan\n"
            "\n"
            "Sore Hikkuri Kaette\n"
            "Ha~ Bon Odori~\n"
            "\n"
            "\n"
            "Translation: Mizuka Lover & ThisIsMyUsername\n"
            "\n"
            "\n"
            "Haa~\n"
            "             When the fireworks fly~\n"
            "\n"
            "Haa~ Ah~\n"
            "            Our spirits will be high~\n"
            "\n"
            "Haa~\n"
            "            If we perform for more eyes~\n"
            "\n"
            "Haa~ Ah~\n"
            "            Ensure our profits will rise~\n"
            "\n"
            "Here's our celebration!\n"
            "Of their generation!\n"
            "\n"
            "So let's all turn around and Dondo Pan Pan\n"
            "Ha~ Bon Odori~\n"
            "\n"
            "Haa~\n"
            "            When the rain goes away~\n"
            "\n"
            "Haa~ Ah~\n"
            "            Climb the tower and play~\n"
            "\n"
            "Come on! Join our Celebration!\n"
            "Honor our Festival Made in Japan\n"
            "\n"
            "So let's all turn around and Dondo Pan Pan\n"
            "Ha~ Bon Odori~\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* REMIX3 ("Lyrics - Honey Sweet Angel of Love") */ {
        /* TITLE ---------------------------------------------------------- */
            "Lyrics Card áA",
        /* BODY ----------------------------------------------------------- */
            "Honey Sweet Angel of Love\n"
            "Song: Ami Tokito\n"
            "Music: TSUNKU\n"
            "Arrangement: Hideyuki \"Daichi\" Suzuki\n"
            "Translation: Cash Banooka\n"
            "\n"
            "YouÅfve cast loveÅfs charm on me\n"
            "What wonder from above\n"
            "We're ever-changing, you see\n"
            "The endless nuance of love\n"
            "Honey Sweet Angel\n"
            "\n"
            "What would it mean to say:\n"
            "\"I love you so much today!\"\n"
            "Clueless\n"
            "Can't tell you what it means, so\n"
            "Put in another way\n"
            "Love has a lot to pay\n"
            "Weakness\n" 
            "Is all love leaves for me, woe\n"
            "\n"
            "Bittersweetness between us\n"
            "Turns as sour as milk\n"
            "That's not unusual\n"
            "For lovebirds like ourselves!\n"
            "I love you!\n"
            "\n"
            "YouÅfve cast loveÅfs charm on me\n"
            "What wonder from above\n"
            "We're ever-changing, you see\n"
            "The endless nuance of love\n"
            "Honey Sweet Angel",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* REMIX5 ("Lyrics - WISH Can't Wait For You") */ {
        /* TITLE ---------------------------------------------------------- */
            "Lyrics Card áB",
        /* BODY ----------------------------------------------------------- */
            "Can't Wait For You\n"
            "Song: Sohshi Tanaka\n"
            "Music: TSUNKU\n"
            "Arrangement: Koichi Yuasa\n"
            "Translation: MilaDoesStuff\n"
            "\n"
            "I can't wait for you anymore\n" 
            "We have to say our goodbyes\n"
            "Wish I had loved you more before the soon sunrise\n"
            "I'll reminisce about what we had done beneath\n"
            "the vast night skies\n"
            "The warmth of those memories I recognize\n"
            "\n"
            "We met under the city lights\n"
            "I know your smile's just as bright\n"
            "I was pulled in your warm embrace\n"
            "Thoughts all blurring in a race\n"
            "It was all happening so fast\n"
            "It didn't feel like time had passed\n"
            "Before I knew it you leaned in your face\n"
            "Kissing under the moon's grace\n"
            "\n"
            "All my dreams clouded in a haze\n"
            "All of you clouded in a haze\n"
            "It's so hot, can't ignore\n"
            "I'm so hurt, to the core\n"
            "I can't take it anymore\n"
            "\n"
            "I can't wait for you anymore\n"
            "We have to say our goodbyes\n" 
            "Wish I had loved you more before the soon sunrise\n"
            "I'll reminisce about what we had done beneath\n"
            "the vast night skies\n"
            "The warmth of those memories I recognize\n"
            "\n"
            "I can't wait for you anymore\n"
            "We have to say our goodbyes\n"
            "Our dreams were nothing more than pure ambitious lies\n"
            "Don't you remember the train that we took where we\n"
            "had our life's highs\n"
            "The warmth of those memories I recognize\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* REMIX8 ("The Final Letter") */ {
        /* TITLE ---------------------------------------------------------- */
            "Final Letter",
        /* BODY ----------------------------------------------------------- */
            "You received this Final Letter from\n"
            "the Rhythm League.\n"
            "\n"
            "\"Congratulations on getting a Perfect on Remix 8!\n"
            "Such a feat certainly is impressive! ...is how I should\n"
            "be congratulating you, but I won't.\n"
            "You have performed outstandingly here in\n"
            "Rhythm Heaven Advance.\n"
            "That much is undeniable, and I fully recognize it.\n"
            "You are the best! One of the greatest! ...is how I feel,\n"
            "but that's enough praise.\n"
            "See, any rhythm you experienced in this game is just\n"
            "a tiny fraction of a world of rhythm.\n"
            "If this experience has made you more interested in\n"
            "rhythm at all, we strongly encourage learning more\n"
            "about it. Because developing your flow is the best!\n"
            "It can't be recommended enough! And... well... ahem.\n"
            "I should stop getting excited and start recommending.\n"
            "We're serious.\n"
            "We really want you to develop your flow even further!\n"
            "\n"
            "We believe you have the potential to lead a world\n"
            "of rhythm!\n"
            "In fact, we can ONLY believe in you!\n"
            "You really are the best!\n"
            "Thank you so much for playing!\"\n"
            "\n"
            "\001R" "Rhythm League Representative\n"
            "\001R" "Space Gramps",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    },

    /* NINJA_BODYGUARD ("The Ninja Scroll") */ {
        /* TITLE ---------------------------------------------------------- */
            "Ninja Scroll",
        /* BODY ----------------------------------------------------------- */
            "Nice to meet you all. I'm Tanaka. The other day I\n"
            "found a bizarre scroll in the back of storage.\n"
            "Written was the following:\n"
            "\n"
            "\"To you who reads this: You did not come across\n"
            "this scroll by chance. I used the powers of ninjutsu\n"
            "to ensure that it would reach you. Do you understand?\n"
            "Indeed, the writer of this scroll is not only a ninja\n"
            "but your ancestor as well.\n"
            "The other day, I protected my lord from a\n"
            "storm of arrows.\n"
            "I risked my life. The night following this daunting task,\n"
            "a dream came to me. I saw a young man.\n"
            "A discontented man with his back against the world.\n"
            "According to the fortune teller, that young man is you.\n"
            "Much like me, you risk your life to protect someone.\n"
            "A young woman. She too is said to be a descendant\n"
            "of my lord.\n"
            "I know not if you can comprehend this scroll, but\n"
            "if so, I ask that you continue to protect her.\"\n"
            "\n"
            "Now, there actually is a woman in my heart.\n"
            "The other day, I saved her from a slingshot attack.\n"
            "I put my life on the line. Who knows what could\n"
            "happen next? My ancestor's ninjutsu might just\n"
            "help in a pinch one day.",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_cherry_gfx_table,
            /* BGM */ &reading_style_cherry_bgm
        /* ---------------------------------------------------------------- */
    },

    /* TOSS_BOYS ("Rhythm Stand-Up") */ {
        /* TITLE ---------------------------------------------------------- */
            "Rhythm Stand-Up",
        /* BODY ----------------------------------------------------------- */
            "Yellow: \"Hello, I'm Yellow!\"\n"
            "Blue: \"Hello, I'm Blue!\"\n"
            "Both: \"Y&B! Nice to meet you!\"\n"
            "Yellow: \"Hey Blue! Did you hear? I'm in a music class!\"\n"
            "Blue: \"Wait, really? No way! What instrument are you\n"
            "learning, Yellow? Is it the guitar? Drums maybe?\"\n"
            "Yellow: \"Well, my part is...\"\n"
            "Blue: \"Yeah? What?\"\n"
            "Yellow: \"I'll be playing rhythm!\"\n"
            "Blue: \"Wha? You can't 'play' rhythm, Yellow.\n"
            "It's not an instrument. Where did you hear that?\"\n"
            "Yellow: \"Well, I told the teacher I wanted to play\n"
            "drums,\n"
            "and they told me I should practice 'rhythm' first!\"\n"
            "Blue: \"Yellow, I think they meant you need to\n"
            "improve your sense of rhythm.\"\n"
            "Yellow: \"Oh yeah, they said exactly that! That's\n"
            "incredible! How did you know? Are you psychic?\"\n"
            "Blue: \"How did I- What do you mean 'how did I know'!?\n"
            "It's just common sense!\"\n"
            "Yellow: \"Hey, man! No need to get so angry.\"\n"
            "Blue: \"Ah... You know, you're right, I'm sorry...\"\n"
            "Yellow: \"Oop! Blue, your fly is down!\"\n"
            "Blue: \"Huh!? Wait, really?\"\n"
            "Yellow: \"No, I lied.\"\n"
            "Blue: \"Why I oughta...!\"\n"
            "Yellow: \"Why I oughta- Man, that's kind of a\n"
            "cheesy line, don't you think?\"\n"
            "Blue: \"Ugh... Leave me alone.\"\n"
            "Yellow: \"GRAAAGH!\"\n"
            "Blue: \"Huh!? Why are you mad? What did I do?\"\n"
            "Yellow: \"Anyway, we were talking about my music\n"
            "class?\"\n"
            "Blue: \"Huh? Uh, yeah, that's right.\"\n"
            "Yellow: \"Geez... way to derail the whole thing...\"\n"
            "Blue: \"Ah, I'm sorry... wait, I'M sorry?\n"
            "You were the one who-- by lying that my fly was down!\"\n"
            "Yellow: \"Hey hey, no need to get so angry.\"\n"
            "Blue: \"Oh, that's rich coming from you! Anyway, your\n"
            "music class?\"\n"
            "Yellow: \"Right! So apparently I'm supposed to\n"
            "practice to improve something called 'censorisms'...?\"\n"
            "Blue: \"Your sense of rhythm! Moron!\"\n"
            "Both: \"Thank you! You've been a wonderful audience!\"\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_manzai_gfx_table,
            /* BGM */ &reading_style_manzai_bgm
        /* ---------------------------------------------------------------- */
    },

    /* FAN_MAIL ("Fan Mailbag") */ {
        /* TITLE ---------------------------------------------------------- */
            "Joyful Voices",
        /* BODY ----------------------------------------------------------- */
            "We've received many letters from\n"
            "satisfied players of Rhythm Heaven Advance.\n"
            "So, SO many in fact(!), that we can't\n"
            "show all of them, but here are just a few\n"
            "of our players' thoughts!\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "Just by improving my sense of rhythm...\n"
            "\n"
            "\0031" "\001m" "I've become... popular?\n"
            "\0030" "\001s" "\n"
            "Before I found \"Rhythm Heaven Advance\",\n"
            "I had no luck with women, but now I'm a real hot shot\n"
            "with a new lease on life!\n"
            "\n"
            "\001R" "Mr. T, Age 38, Office Worker\n"
            "\001L" "Just by improving my sense of rhythm...\n"
            "\n"
            "\0031" "\001m" "I've become...\n"
            "\0031" "\001R" "a better singer?"
            "\0030" "\001s" "\n"
            "\001L" "Before I found \"Rhythm Heaven Advance\",\n"
            "I was the textbook definition of tone-deaf,\n"
            "but lately people have told me my singing is much nicer!\n"
            "I'm still tone deaf, of course, but at least I'm happy!\n"
            "\001R" "Mrs. H, Age 29, Housewife\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_FORMULA ("The Rhythm Formula") */ {
        /* TITLE ---------------------------------------------------------- */
            "Understanding Rhythm",
        /* BODY ----------------------------------------------------------- */
            "\001C" "\0032" "\001m" "\n"
            "\n"
            "Sense of rhythm ÅΩ Flow\n"
            "\n"
            "Sense of rhythm ÅÇ Flow\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "Explanation: Flow is an element included in anyone's\n"
            "sense of rhythm, but not a sense of rhythm itself.\n"
            "\001C" "\0032" "\001m" "\n"
            "\n"
            "\n"
            "\n"
            "Rhythm ÅÇ Sense of rhythm\n"
            "\n"
            "\001C" "\0030" "\001s" "\n"
            "Explanation: Rhythm is what ticks at a steady pace.\n"
            "A sense of rhythm is how you maintain that pace,\n"
            "expressed naturally by way of flow.\n"
            "\001C" "\0031" "\001m" "\n"
            "\n"
            "\n"
            "Good dancing ÅÇ Good sense of rhythm\n"
            "\n"
            "\001C" "\0030" "\001s" "\n"
            "Explanation: Someone who's a good dancer does not\n"
            "inherently have a good sense of rhythm.",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_classroom_gfx_table,
            /* BGM */ &reading_style_classroom_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_DIAGNOSIS ("Rhythm Diagnosis") */ {
        /* TITLE ---------------------------------------------------------- */
            "Rhythm Type Diagnosis",
        /* BODY ----------------------------------------------------------- */
            "\001C" "\0031" "\001m" "Rhythm Diagnosis\n"
            "\0030" "\001s" "\n"
            "Let's diagnose your sense of rhythm.\n"
            "Choose the ones that apply to you!\n"
            "\n"
            "I think that I have a good sense of rhythm.\n"
            "Yes - Go to Page 2!\n"
            "No - Go to Page 3!\n"
            "-1-\n"
            "\n"
            "Between Rock and Pop music, I like...\n"
            "\n"
            "\n"
            "\n"
            "Rock - Go to Page 4!\n"
            "Pop - Go to Page 5!\n"
            "\n"
            "-2-\n"
            "\n"
            "Between Jazz and Classical music, I like...\n"
            "\n"
            "\n"
            "\n"
            "Jazz - Go to Page 6!\n"
            "Classical - Go to Page 7!\n"
            "\n"
            "-3-\n"
            "\n"
            "I think you need a good sense of rhythm to dance well.\n"
            "\n"
            "\n"
            "\n"
            "Yes - Go to Page 8!\n"
            "No - Go to Page 9!\n"
            "\n"
            "-4-\n"
            "\n"
            "I think that if you can hear good rhythm,\n"
            "then you can express it.\n"
            "\n"
            "\n"
            "Yes - Go to Page 10!\n"
            "No - Go to Page 11!\n"
            "\n"
            "-5-\n"
            "\n"
            "I don't think anyone has a sense of rhythm at all.\n"
            "\n"
            "\n"
            "\n"
            "Yes - Go to Page 9!\n"
            "No - Go to Page 8!\n"
            "\n"
            "-6-\n"
            "\n"
            "I think that a sense of rhythm is inherent,\n"
            "meaning you can't improve it with training.\n"
            "\n"
            "\n"
            "Yes - Go to Page 10!\n"
            "No - Go to Page 11!\n"
            "\n"
            "-7-\n"
            "\n"
            "I think that your sense of rhythm is cooler\n"
            "when you have flow.\n"
            "\n"
            "\n"
            "Yes - Go to Page 12!\n"
            "No - Go to Page 13!\n"
            "\n"
            "-8-\n"
            "\n"
            "I think that a sense of rhythm and\n"
            "flow are just about the same thing.\n"
            "\n"
            "\n"
            "Yes - Go to Page 14!\n"
            "No - Go to Page 15!\n"
            "\n"
            "-9-\n"
            "\n"
            "I don't think you can become popular just by\n"
            "having a good sense of rhythm.\n"
            "\n"
            "\n"
            "Yes - Go to Page 16!\n"
            "No - Go to Page 17!\n"
            "\n"
            "-10-\n"
            "\n"
            "I think that having a good sense of rhythm\n"
            "makes it easy to mask being tone deaf.\n"
            "\n"
            "\n"
            "Yes - Go to Page 18!\n"
            "No - Go to Page 19!\n"
            "\n"
            "-11-\n"
            "\n"
            "I think that a good sense of rhythm is easier\n"
            "to acquire at a young age.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 21!\n"
            "\n"
            "-12-\n"
            "\n"
            "I don't think you can improve your\n"
            "sense of rhythm after becoming an adult.\n"
            "\n"
            "\n"
            "Yes - Go to Page 21!\n"
            "No - Go to Page 22!\n"
            "\n"
            "-13-\n"
            "\n"
            "I think that rhythm and\n"
            "everyday life are unrelated.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 22!\n"
            "\n"
            "-14-\n"
            "\n"
            "I think that even a sense of rhythm that you've had\n"
            "for over three years can quickly be lost\n"
            "if you're not mindful of it.\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 20!\n"
            "\n"
            "-15-\n"
            "\n"
            "I think that your sense of rhythm will\n"
            " improve if you train long and hard.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 22!\n"
            "\n"
            "-16-\n"
            "\n"
            "I think that your sense of rhythm can improve\n"
            "in just 30 seconds if you stay mindful of it.\n"
            "\n"
            "\n"
            "Yes - Go to Page 22!\n"
            "No - Go to Page 23!\n"
            "\n"
            "-17-\n"
            "\n"
            "I don't think it's a good thing to\n"
            "always feel a sense of rhythm.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 20!\n"
            "\n"
            "-18-\n"
            "\n"
            "I think that a good sense of rhythm is\n"
            "acquired by repetition, not theory.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 21!\n"
            "\n"
            "-19-\n"
            "\001C" "Your Sense of Rhythm\n"
            "\0031" "\001m" "Flow Type" "\0030" "\001s" "\n"
            "\n"
            "\001C" "You have a good attitude about your sense of rhythm.\n"
            "You might not have confidence in your\n"
            "sense of rhythm quite yet, but you could probably\n"
            "use rhythm to lead an enjoyable life.\n"
            "Enjoy getting into the flow!\n"
            "\001C" "-20-\n"
            "\001C" "Your Sense of Rhythm\n"
            "\0031" "\001m" "Shy Type" "\0030" "\001s" "\n"
            "\n"
            "\001C" "You're nervous about your sense of rhythm, huh?\n"
            "Everyone has a sense of rhythm.\n"
            "If you live life being mindful of the rhythms\n"
            "around you, your sense of rhythm can only grow.\n"
            "Make sure to relax.\n"
            "\001C" "-21-\n"
            "\001C" "Your Sense of Rhythm\n"
            "\0031" "\001m" "Carefree Type" "\0030" "\001s" "\n"
            "\n"
            "\001C" "You should learn the difference between a sense\n"
            "of rhythm and flow. A good flow can only go so far\n"
            "if your sense of rhythm is poor.\n"
            "Steady your sense of rhythm and\n"
            "your flow could improve everyone's mood.\n"
            "\001C" "-22-\n"
            "\001C" "Your Sense of Rhythm\n"
            "\0031" "\001m" "Catchy Type" "\0030" "\001s" "\n"
            "\n"
            "\001C" "You may have a hard time grasping rhythm.\n"
            "If you find ways to incorporate your sense of rhythm\n"
            "into your daily routine,\n"
            "perhaps it can grow and improve.\n"
            "It might even make things more fun that way!\n"
            "\001C" "-23-\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_classroom_gfx_table,
            /* BGM */ &reading_style_classroom_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_POEM ("Rhythm Poem Digest") */ {
        /* TITLE ---------------------------------------------------------- */
            "Rhythm Poem Collection",
        /* BODY ----------------------------------------------------------- */
            "\001C" "\0031" "\001m" "\"To Nurture\"\n"
            "\n"
            "\001C" "\0030" "\001s" "I have nurtured it,\n"
            "For the day when it will learn to use its wings.\n"
            "In the wake of a casual, everyday life,\n"
            "Naturally,\n"
            "Enjoyably,\n"
            "That which is now only very, very small,\n"
            "My sense of rhythm...\n"
            "\001C" "\0031" "\001m" "\"Karate Rhythm\"\n"
            "\001C" "\0030" "\001s" "\n"
            "Hey! Baby! How's it going?\n"
            "This beat is non-stop.\n"
            "Hey! Baby! Listen to my phrase.\n"
            "I can give you\n"
            "the sense of rhythm.\n"
            "Oh, yeah.\n"
            "Awake, baby! Trust me!\n"
            "This beat is non-stop!\n"
            "New groove in your soul.\n"
            "Oh, yeah!\n"
            "This beat!\n"
            "You are growing up well.\n"
            "Hey, baby!\n"
            "Hold onto your ambition.\n"
            "Hey! Oh, yeah!\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_HAIKU ("Rhythm Haiku Folio") */ {
        /* TITLE ---------------------------------------------------------- */
            "Rhythm Haiku Collection",
        /* BODY ----------------------------------------------------------- */
            "\n"
            "\001L" "\0030" "\001s" "Let us exercise\n"
            "\001C" "\0030" "\001s" "something which everyone has,\n"
            "\001R" "\0030" "\001s" "a sense of rhythm\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "\"Your sense of rhythm can be developed with\n"
            "practice, especially when it's worked into\n"
            "your daily routine.\"\n"
            "\n"
            "\n"
            "\001L" "\0030" "\001s" "You can make all your\n"
            "\001C" "\0030" "\001s" "everyday activities\n"
            "\001R" "\0030" "\001s" "much more rhythmical\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "\"It's good to feel and improve your sense of rhythm\n"
            "throughout your day, such as while walking,\n"
            "brushing your teeth, cooking, etc...\n"
            "You should always keep rhythm in mind.\"\n"
            "\n"
            "\001L" "\0030" "\001s" "Your sense of rhythm,\n"
            "\001C" "\0030" "\001s" "if your flow can be improved,\n"
            "\001R" "\0030" "\001s" "gets even cooler\n"
            "\n"
            "\001C" "\0030" "\001s" "\"However, a sense of rhythm and good flow are not\n"
            "one and the same. Try to improve your flow while\n"
            "also being mindful of your sense of rhythm.\"\n"
            "\n"
            "\n"
            "\001L" "\0030" "\001s" "In a break or pause\n"
            "\001C" "\0030" "\001s" "children who lack patience are\n"
            "\001R" "\0030" "\001s" "simply too stubborn\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "\"It can be difficult to count accurately during a rest,\n"
            "and it's easy to resume the beat prematurely, but the\n"
            "ability to stay calm and wait affects your \n"
            "flow the most.\"\n"
            "\n"
            "\001L" "\0030" "\001s" "Even in adults,\n"
            "\001C" "\0030" "\001s" "something still rapidly grows:\n"
            "\001R" "\0030" "\001s" "Their sense of rhythm\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "\"From simply being mindful of it, your sense of rhythm\n"
            "can grow exponentially, no matter your age.\"\n"
            "\n"
            "\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_haiku_gfx_table,
            /* BGM */ &reading_style_haiku_bgm
        /* ---------------------------------------------------------------- */
    },

    /* READING_MATERIAL_CREDITS */ {
        /* TITLE ---------------------------------------------------------- */
            "Credits",
        /* BODY ----------------------------------------------------------- */
            "This is a temporary, unlocked after Karate Man EX!,\n"
            "credits reading material for the\n"
            "Rhythm Heaven Advance project.\n"
            "\n"
            "I implemented this to see if its possible and if the\n"
            "system is working correctly!\n"
            "\n"
            "For the actual system, I want it to be after Remix 1 EX!\n"
            "And for the writing to be (not to spoil it) unique\n"
            "But for now though, here are the proper credits for all\n"
            "the incredible people who contributed to this project:\n"
            "\n"
            "Asset Assembly:\n"
            "+ SkyeStage\n"
            "+ Cash Banooka\n"
            "+ geometricentric\n"
            "+ somethingAccurate\n"
            "+ TinyCastleGuy\n"
            "+ The Eggo55\n"
            "+ Vincells\n"
            "+ WindowsTiger\n"
            "+ Kievit\n"
            "+ NotWario\n"
            "+ amdree\n"
            "+ patataofcourse\n"
            "+ Nate Candles\n"
            "\n"
            "Graphic Design:\n"
            "+ Tailx\n"
            "+ vincells\n"
            "+ Borists\n"
            "\n"
            "Main Programming:\n"
            "+ Itaific\n"
            "+ ShaffySwitcher\n"
            "\n"
            "Coding Contributions:\n"
            "+ Deni_iguess\n"
            "+ patataofcourse\n"
            "+ Arthurtilly\n"
            "+ Estexnt\n"
            "+ Nibblez\n"
            "+ Conhlee\n"
            "+ MissKnowledge\n"
            "\n"
            "\n"
            "Translation and Localization:\n"
            "+ Mizuka Lover\n"
            "+ ShaffySwitcher\n"
            "+ somethingAccurate\n"
            "+ patataofcourse\n"
            "\n"
            "Localization Support:\n"
            "+ Cash Banooka\n"
            "+ SkyStage\n"
            "+ RedRobocon\n"
            "+ ThisIsMyUsername\n"
            "\n"
            "SFX:\n"
            "+ Rhythm Heaven Megamix\n"
            "+ Cherryberryfaygo\n"
            "+ Nabix and all of his siblings\n"
            "\n"
            "Bug Testing:\n"
            "Everyone on the Rhythm Heaven Advance discord!\n"
            "with special mention to nwqol\n"
            "\n"
            "Thank you all for your hard work!\n"
            "Rhythm Heaven Advance exists because of you!\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    }
};
