#include "global.h"
#include "graphics.h"
#include "text.h"
#include "src/scenes/cafe.h"
#include "graphics/cafe/cafe_graphics.h"


  /* CAFE - DIALOGUE */


// [D_089cd2e8] Dialogue - First Visit
    /* -------------------------------- */
        //
        // Welcome. This is your
        // first time here, isn't it?
        //
    /* -------------------------------- */
        // This is the Cafe.
        // <When you can't finish a game>,
        // or when you just want a break,
        // please come here and relax.
    /* -------------------------------- */
        //
        // I'm pretty good at Rhythm Games.
        // If you need help, <come to the Cafe>.
        //
    /* -------------------------------- */
        //
        // I'm still unpacking boxes, so
        // please come back in a bit.
        //
    /* -------------------------------- */
        //
        //
        // See you later.
        //
    /* -------------------------------- */

const char *cafe_dialogue_first_visit[] = {
    /* ------------------------------------------------ */
        "\n"
        "Welcome to the caf‡Q.\n"
        "This your first time here?\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Feel free to come on by anytime you\n"
        "find the games " "\0051" "\0015" "too hard to play " "\0054" "\0018" "or\n"
        "you just need to take a break.",
    /* ------------------------------------------------ */
        "\n"
        "If there's anything I can\n"
        "do to help, well, " "\0051" "\0015" "that's\n"
        "what I'm here for." "\0054" "\0018" "",
    /* ------------------------------------------------ */
        "I'm a little busy right now,\n"
        "since I only just opened,\n"
        "for the day, but we'll talk\n"
        "more later.",
    /* ------------------------------------------------ */
        "\n"
        "Come back soon!\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd300] Dialogue - Come Back Later
    /* -------------------------------- */
        //
        //
        // Come back in a while!
        //
    /* -------------------------------- */

const char *cafe_dialogue_come_back_later[] = {
    /* ------------------------------------------------ */
        "\n"
        "I've got some other customers\n"
        "to deal with. We'll talk later.\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd308] Dialogue - Keep Trying
    /* -------------------------------- */
        //
        // You know, after a few tries
        // I think you'll manage that superb.
        //
    /* -------------------------------- */
        //
        // Just keep moving to the music,
        // and you'll have fun doing it, too.
        //
    /* -------------------------------- */
        //
        // Don't let it frustrate you.
        // You're supposed to enjoy yourself.
        //
    /* -------------------------------- */

const char *cafe_dialogue_keep_trying[] = {
    /* ------------------------------------------------ */
        "\n"
        "Give it some practice and you'll do\n"
        "fine. I'm sure of it!\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "I'm sure playing together\n"
        "with the music will be pretty\n"
        "fun all its own.",
    /* ------------------------------------------------ */
        "\n"
        "Try not to get all worked up out\n"
        "there. Make sure to have a good time.\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd318] Dialogue - Practicing for the Perfect Campaign
    /* -------------------------------- */
        //
        // Sorry for yelling. I just got
        // a little too excited there.
        //
    /* -------------------------------- */
        //
        // Please try your best
        // for those Perfects.
        // See you soon!
    /* -------------------------------- */

const char *cafe_dialogue_practicing_perfect[] = {
    /* ------------------------------------------------ */
        "\n"
        "...Sorry for yelling. I just got a little\n"
        "excited.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Good luck on getting those Perfects!\n"
        "See you around.\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd324] Dialogue - Not Practicing for the Perfect Campaign
    /* -------------------------------- */
        //
        // Is that right? Loose lips can sink
        // friendships... please forgive me.
        //
    /* -------------------------------- */
        //
        // Please enjoy the
        // game. See you!
        //
    /* -------------------------------- */

const char *cafe_dialogue_not_practicing_perfect[] = {
    /* ------------------------------------------------ */
        "\n"
        "Is that so? My bad then.\n"
        "Guess that's why you shouldn't put\n"
        "so much stock in a rumor.",
    /* ------------------------------------------------ */
        "\n"
        "Enjoy the games at your own pace,\n"
        "alright? See you around.\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd330] Dialogue - All Perfects Cleared
    /* -------------------------------- */
        //
        // You must have excellent rhythm
        // sense to have gotten this far!
        //
    /* -------------------------------- */
        //
        // Oh, I'm so happy I think
        // I might just start to cry.
        //
    /* -------------------------------- */
        //
        // Well, in celebration I've added
        // more songs to the studio.
        //
    /* -------------------------------- */
        //
        // Wow. It looks like you've
        // mastered the game. Not bad.
        //
    /* -------------------------------- */
        //
        // Had enough, I suppose? Go
        // get some rest. I'll be waiting.
        //
    /* -------------------------------- */

const char *cafe_dialogue_all_perfects_clear[] = {
    /* ------------------------------------------------ */
        "\n"
        "If you've made it this far, then your\n"
        "sense of rhythm has just got to be\n"
        "a step above the rest!",
    /* ------------------------------------------------ */
        "\n"
        "I'm so proud of you. Moved to tears,\n"
        "even!\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "I know it's not much of a gift,\n"
        "but I've opened up more studio songs\n"
        "for you.\n",
    /* ------------------------------------------------ */
        "\n"
        "So I guess that means you've collected\n"
        "everything?\n"
        "Impressive!",
    /* ------------------------------------------------ */
        "\n"
        "Good work out there, my friend.\n"
        "You've really earned a break.\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd348] Praise
    /* -------------------------------- */
        //
        //
        // Not too bad!!
    /* -------------------------------- */
        //
        //
        // You're good!!
    /* -------------------------------- */
        //
        //
        // Congratulations!!
    /* -------------------------------- */
        //
        //
        // Good job!!
    /* -------------------------------- */
        //
        //
        // Unbelievable!!
    /* -------------------------------- */

const char *cafe_dialogue_shouts_praise[] = {
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "That's great!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "Amazing!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "Congratulations!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "Great job!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "I can't believe it!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
};


// [D_089cd35c] Encouragement
    /* -------------------------------- */
        //
        //
        // <Go for it!>
    /* -------------------------------- */
        //
        //
        // <Fight!>
    /* -------------------------------- */
        //
        //
        // <Go! Go!>
    /* -------------------------------- */
        //
        //
        // Good luck!
    /* -------------------------------- */
        //
        //
        // I was moved!
    /* -------------------------------- */

const char *cafe_dialogue_shouts_cheer[] = {
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "Go for it!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "Give it your all!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "Keep going!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "Good luck!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "I'm impressed!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
};


// [D_089cd370] Dialogue - Rhythm Sense
    /* -------------------------------- */
        //
        // By the way, I wonder how
        // Rhythm Sense is for humans?
        //
    /* -------------------------------- */
        //
        // Well, not that I'm very
        // aware of it myself.
        //
    /* -------------------------------- */
        //
        // But you'll be a bit happier once you
        // find your Rhythm Sense, I'm sure.
        //
    /* -------------------------------- */
        //
        // Maybe I should try a little harder
        // to get good at Rhythm Heaven...
        //
    /* -------------------------------- */

const char *cafe_dialogue_rhythm_sense[] = {
    /* ------------------------------------------------ */
        "\n"
        "By the way, is a sense of rhythm any\n"
        "different for humans?\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Well, not like my rhythm couldn't do with\n"
        "a bit of work, but...\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "When your sense of rhythm\n"
        "improves... that's gotta be\n"
        "euphoric, huh?",
    /* ------------------------------------------------ */
        "\n"
        "Maybe I should try some of those\n"
        "rhythm games myself...\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd384] Dialogue - Offbeats
    /* -------------------------------- */
        //
        // I hear the word "offbeat" often.
        // Do you know what an "offbeat" is?
        //
    /* -------------------------------- */
        // Honestly, I wasn't sure
        // what it meant either.
        // So, the other day I looked
        // up the definition.
    /* -------------------------------- */
        //
        // How do I explain it...
        // Well, you naturally clap
        // your hands to music, right?
    /* -------------------------------- */
        // Halfway between one clap
        // and the next (the "onbeats")
        // is called the "offbeat".
        // At least, so I understand.
    /* -------------------------------- */
        // Did you know that already?
        // Sorry if it seems like I'm
        // talking down to you.
        // Anyways, see you again.
    /* -------------------------------- */

const char *cafe_dialogue_offbeats[] = {
    /* ------------------------------------------------ */
        "\n"
        "You've probably heard of something\n"
        "called an offbeat. Do you know what\n"
        "that is?",
    /* ------------------------------------------------ */
        "\n"
        "I'm no expert myself, but I think\n"
        "I've got the jist of it.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "So, suppose you're clapping to\n"
        "the beat of some music, right?\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Well, the offbeat is supposed to be\n"
        "the exact point right inbetween each\n"
        "of your claps.",
    /* ------------------------------------------------ */
        "\n"
        "At least I think so. I'm not so great at\n"
        "explaining this stuff, but I hope it helps.\n"
        "See you around.",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd39c] Dialogue - Rhythm Test
    /* -------------------------------- */
        //
        // Say, when was the last time you
        // checked your "Rhythm Test" score?
        //
    /* -------------------------------- */
        //
        // I just tried it again yesterday, but
        // 65 points seems to be my limit...
        //
    /* -------------------------------- */
        //
        // I always have trouble with
        // the rests in the second test.
        //
    /* -------------------------------- */
        //
        // Counting to yourself is hard, isn't it?
        // I always go too fast or lose my place.
        //
    /* -------------------------------- */
        //
        // Well, nothing we can do but practice.
        // Take care for now.
        //
    /* -------------------------------- */

const char *cafe_dialogue_rhythm_test[] = {
    /* ------------------------------------------------ */
        "\n"
        "Say, have you tried doing the\n"
        "Rhythm Test again?\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "I've been giving it a spin lately.\n"
        "Seems like 65 points is my limit.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "That second test gives me quite\n"
        "a bit of trouble.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Counting those silent beats...\n"
        "It's tricky, don't you think?\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Well, let's take it one step at a time.\n"
        "See you around.\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd3b4] Dialogue - Drum Lessons
    /* -------------------------------- */
        //
        // Let me ask... have you tried the
        // Drum Lessons in the Prize Corner?
        //
    /* -------------------------------- */
        //
        // I take lessons once a week, but
        // I don't really seem to improve.
        //
    /* -------------------------------- */
        // The teacher is really strict.
        // I asked him for an easier
        // lesson, but he told me to
        // just keep on trying my best.
    /* -------------------------------- */
        //
        // You'll find it's hard to quit
        // once you start a lesson.
        //
    /* -------------------------------- */
        // Maybe it's for the best.
        // For musical instruments, you
        // just have to keep at it.
        // You should try your best, too.
    /* -------------------------------- */

const char *cafe_dialogue_drum_lessons[] = {
    /* ------------------------------------------------ */
        "\n"
        "You ever check out the drum\n"
        "lessons in the bonus corner?\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "I've been taking lessons every week,\n"
        "but I never seem to get any better.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "My teacher told me that I have a\n"
        "bit of a problem pacing myself, that\n"
        "I shouldn't push myself so much.",
    /* ------------------------------------------------ */
        "\n"
        "But once you start getting into it,\n"
        "it's hard to stop.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "I guess no one can master the drums\n"
        "in a day, though. We should take\n"
        "our time with that stuff.",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd3cc] Dialogue - Staying Up All Night
    /* -------------------------------- */
        //
        // By the way, right now
        // I'm terribly tired...
        //
    /* -------------------------------- */
        //
        // I was up all last night playing.
        // I just couldn't stop myself...
        //
    /* -------------------------------- */
        //
        // What? Oh, I was talking to myself.
        // It was a monologue... sorry.
        //
    /* -------------------------------- */
        //
        // Learn from me, and don't forget
        // to take a break every so often.
        // Anyway, see you again.
    /* -------------------------------- */

const char *cafe_dialogue_adhd[] = {
    /* ------------------------------------------------ */
        "\n"
        "I'm not sure why, but man, am I tired...\n"
        "\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "I was up last night playing until\n"
        "who-knows-when...\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Oops! Sorry. I'm talking to myself again.\n"
        "Don't mind me.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Want to go for a drive with me, sometime?\n"
        "If that's alright with you, I mean.\n"
        "See you around.",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd3e0] Dialogue - Coffee
    /* -------------------------------- */
        //
        // By the way, here's the
        // coffee you ordered.
        //
    /* -------------------------------- */
        //
        // Hm? You didn't order it?
        // Ah, I see. This is actually
        // for the guy next to you...
    /* -------------------------------- */
        //
        // Well... he isn't a talkative person,
        // but you seem to be getting along.
        //
    /* -------------------------------- */
        //
        // All I can do is pour
        // the coffee, but... heh.
        //
    /* -------------------------------- */

const char *cafe_dialogue_coffee[] = {
    /* ------------------------------------------------ */
        "\n"
        "So, I made you some coffee.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Wait, you didn't order coffee?\n"
        "Oh, this is from the person\n"
        "sitting next to you. His treat.",
    /* ------------------------------------------------ */
        "\n"
        "He's not much for words, but\n"
        "he's pretty friendly, and I guess\n"
        "generous too.",
    /* ------------------------------------------------ */
        "\n"
        "Me? I can make coffee, but...\n"
        "need to work on the rest. Heh...\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd3f4] Dialogue - Dog
    /* -------------------------------- */
        //
        // By the way, if you hadn't
        // noticed, I'm actually a dog.
        //
    /* -------------------------------- */
        //
        // I'm not one of those young pups,
        // either. I'm nine years old.
        //
    /* -------------------------------- */
        //
        // When you get to be my age,
        // time really does seem to fly.
        //
    /* -------------------------------- */
        //
        // Hey, you're a human, right?
        // Well, despite our species I still
        // hope that we can get along
    /* -------------------------------- */

const char *cafe_dialogue_dog_barista[] = {
    /* ------------------------------------------------ */
        "\n"
        "By the way, I'm actually a dog.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "I'm nine years old. Pretty spry\n"
        "for my age if I say so.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Time goes by pretty fast when you're\n"
        "as old as I am.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "You're a human, right? They say I'm\n"
        "supposed to be your best friend.\n"
        "We'd better get along then!",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd408] Dialogue - Music
    /* -------------------------------- */
        //
        // By the way, what do
        // you do when you're sad?
        // I always listen to music.
    /* -------------------------------- */
        //
        // Taking out a good old record and
        // reminiscing about the past
        // always makes me feel better.
    /* -------------------------------- */
        //
        // Music is strange, isn't it?
        // It has this mysterious
        // power to heal the heart.
    /* -------------------------------- */
        //
        // Just don't think that good
        // rhythm makes you qualified
        // to be a doctor, ha ha ha.
    /* -------------------------------- */

const char *cafe_dialogue_healing_with_music[] = {
    /* ------------------------------------------------ */
        "\n"
        "So, when you're sad, what do\n"
        "you do to cheer yourself up?\n"
        "Me, I listen to music.",
    /* ------------------------------------------------ */
        "\n"
        "Dusting off a favorite record of mine\n"
        "and taking a nostalgia trip...\n"
        "That never fails to put me at ease.",
    /* ------------------------------------------------ */
        "\n"
        "Music's weird like that. Why does\n"
        "it have such power over our feelings,\n"
        "do you think?",
    /* ------------------------------------------------ */
        "\n"
        "Maybe if I studied this stuff I'd know,\n"
        "but I haven't! Sorry! Heh.\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd41c] Dialogue - Speaking Through Rhythm
    /* -------------------------------- */
        //
        // Say... did you know that you can
        // have a conversation with rhythm?
        //
    /* -------------------------------- */
        //
        // By attaching words and meanings
        // to certain beats, you can have a
        // conversation without speaking.
    /* -------------------------------- */
        // For example... you could play
        // a drum beat to ask "How are
        // you?" or say "Please come
        // visit!" even from far away.
    /* -------------------------------- */
        //
        // I learned it from another
        // customer, and now I want
        // to try it for myself.
    /* -------------------------------- */
        // Then again, if we gave speeches
        // with bongos or the neighbors
        // argued with trumpets, it'd get
        // noisy, don't you think? Ha ha ha.
    /* -------------------------------- */

const char *cafe_dialogue_speaking_with_music[] = {
    /* ------------------------------------------------ */
        "\n"
        "I heard you can hold a conversation\n"
        "with only rhythm.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "You can put words and meanings\n"
        "behind different rhythms like morse\n"
        "code and talk without speaking.",
    /* ------------------------------------------------ */
        "\n"
        "Like, bang out a message into one\n"
        "of those taiko drums, and you could\n"
        "communicate acres apart.",
    /* ------------------------------------------------ */
        "\n"
        "At least that's what a customer\n"
        "once told me. Doesn't that sound\n"
        "fun?",
    /* ------------------------------------------------ */
        "\n"
        "But if you had percussive election\n"
        "speeches or bongo arguments...\n"
        "Expect a lot of noise. Ahahaha!",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd434] Dialogue - Ranks and Medals
    /* -------------------------------- */
        //
        // By the way, have you ever
        // gotten a "Superb" rating on a game?
        //
    /* -------------------------------- */
        //
        // There are three grades, you know:
        // "Try Again", "OK" and "Superb".
        //
    /* -------------------------------- */
        //
        // If you get a "Superb",
        // you'll even get a medal.
        //
    /* -------------------------------- */
        // Collecting lots of medals will
        // unlock all sorts of prizes that
        // you can play with. Please do your
        // best to collect them all!
    /* -------------------------------- */
        //
        // Oh... but if you already knew that,
        // I'm sorry if I bored you.
        // See you later.
    /* -------------------------------- */

const char *cafe_dialogue_ranks_and_medals[] = {
    /* ------------------------------------------------ */
        "\n"
        "By the way, have you ever gotten a\n"
        "Superb rank on a game?\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "There are three ranks you can get:\n"
        "Try Again, OK, and Superb.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "And, if you get a Superb,\n"
        "you also get a medal.\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "Those medals let you unlock\n"
        "some prizes. Sounds like it\n"
        "would be worth your while.",
    /* ------------------------------------------------ */
        "\n"
        "But you probably already knew that,\n"
        "right? Sorry if I bored you.\n"
        "See you around.",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd44c] Random Dialogue Pool
const char **cafe_random_conversation_pool[] = {
    cafe_dialogue_rhythm_sense,
    cafe_dialogue_offbeats,
    cafe_dialogue_rhythm_test,
    cafe_dialogue_drum_lessons,
    cafe_dialogue_adhd,
    cafe_dialogue_coffee,
    cafe_dialogue_dog_barista,
    cafe_dialogue_healing_with_music,
    cafe_dialogue_speaking_with_music,
    cafe_dialogue_ranks_and_medals
};
