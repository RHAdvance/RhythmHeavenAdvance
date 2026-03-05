#define EMPTY_GRID_ENTRY { LEVEL_NULL, NULL, NULL, NULL, 0, 0 }

#define REQ_MEDAL(x, y) LEVEL_STATE_HAS_MEDAL, x, y
#define REQ_CLEAR(x, y) LEVEL_STATE_CLEARED, x, y
#define REQ_OPEN(x, y) LEVEL_STATE_OPEN, x, y
#define REQ_SHOWN(x, y) LEVEL_STATE_CLOSED, x, y
#define REQ_TOTAL_MEDALS(count) LEVEL_EVENT_REQ_TOTAL_MEDALS, count, 0
#define END_REQ -1

#define TARGET(x, y) x, y
#define END_TARGETS TARGET(-1, -1)

#define TARGET_ON_SHOW   LEVEL_EVENT_TARGET_ON_SHOW
#define MOVE_CURSOR      LEVEL_EVENT_MOVE_CURSOR
#define CLEAR_BY_DEFAULT LEVEL_EVENT_CLEAR_BY_DEFAULT
#define DELAY_CLEAR      LEVEL_EVENT_DELAY_CLEAR
#define DELAY_OPEN       LEVEL_EVENT_DELAY_OPEN
#define DELAY_SHOW       LEVEL_EVENT_DELAY_SHOW
#define TARGET_ON_OPEN   LEVEL_EVENT_TARGET_ON_OPEN


// [D_089ceafc] Game Select Grid Data
struct GameSelectGridEntry game_select_grid_data[GS_GRID_WIDTH * GS_GRID_HEIGHT] = {
    /* Entry (x=00, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=02, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=03, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=04, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=05, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=06, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=07, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=08, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=09, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=10, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=11, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=00) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=00) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=02, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=03, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=04, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=05, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=06, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=07, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=08, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=09, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=10, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=11, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=01) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=01) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=02, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=03, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=04, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=05, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=06, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=07, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=08, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=09, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=10, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=11, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=02) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=02) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=02, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=03, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=04, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=05, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=06, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=07, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=08, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=09, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=10, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=11, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=03) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=03) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=02, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=03, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=04, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=05, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=06, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=07, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=08, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=09, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=10, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=11, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=04) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=04) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=02, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=03, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=04, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=05, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=06, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=07, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=08, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=09, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=10, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=11, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=05) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=05) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=06) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=06) */ {
        /* Level ID */ LEVEL_LIVE_MENU,
        /* Show Req */ (s8[]) { REQ_CLEAR(2, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(9, 6), END_REQ },
        /* Targets  */ (s8[]) { TARGET(3, 6), TARGET(3, 7), TARGET(3, 8), TARGET(3, 9), TARGET(3, 10), TARGET(3, 11), TARGET(10, 6), TARGET(10, 7), TARGET(10, 8), TARGET(10, 9), TARGET(10, 10), TARGET(10, 11), END_TARGETS },
        /* Flags */ CLEAR_BY_DEFAULT | DELAY_CLEAR | DELAY_SHOW | TARGET_ON_OPEN,
        /* Delay */ 5
    },
    /* Entry (x=02, y=06) */ {
        /* Level ID */ LEVEL_REMIX_1,
        /* Show Req */ (s8[]) { REQ_SHOWN(2, 11), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(2, 7), REQ_CLEAR(2, 8), REQ_CLEAR(2, 9), REQ_CLEAR(2, 10), REQ_CLEAR(2, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(1, 6), TARGET(1, 7), TARGET(1, 8), TARGET(1, 9), TARGET(1, 10), TARGET(1, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=03, y=06) */ {
        /* Level ID */ LEVEL_REMIX_2,
        /* Show Req */ (s8[]) { REQ_SHOWN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(3, 7), REQ_CLEAR(3, 8), REQ_CLEAR(3, 9), REQ_CLEAR(3, 10), REQ_CLEAR(3, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(4, 6), TARGET(4, 7), TARGET(4, 8), TARGET(4, 9), TARGET(4, 10), TARGET(3, 11), TARGET(4, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=04, y=06) */ {
        /* Level ID */ LEVEL_REMIX_3,
        /* Show Req */ (s8[]) { REQ_CLEAR(3, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(4, 7), REQ_CLEAR(4, 8), REQ_CLEAR(4, 9), REQ_CLEAR(4, 10), REQ_CLEAR(4, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(5, 6), TARGET(5, 7), TARGET(5, 8), TARGET(5, 9), TARGET(5, 10), TARGET(4, 11), TARGET(5, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=05, y=06) */ {
        /* Level ID */ LEVEL_REMIX_4,
        /* Show Req */ (s8[]) { REQ_CLEAR(4, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(5, 7), REQ_CLEAR(5, 8), REQ_CLEAR(5, 9), REQ_CLEAR(5, 10), REQ_CLEAR(5, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(6, 6), TARGET(6, 7), TARGET(6, 8), TARGET(6, 9), TARGET(6, 10), TARGET(5, 11), TARGET(6, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=06, y=06) */ {
        /* Level ID */ LEVEL_REMIX_5,
        /* Show Req */ (s8[]) { REQ_CLEAR(5, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(6, 7), REQ_CLEAR(6, 8), REQ_CLEAR(6, 9), REQ_CLEAR(6, 10), REQ_CLEAR(6, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(7, 6), TARGET(7, 7), TARGET(7, 8), TARGET(7, 9), TARGET(7, 10), TARGET(6, 11), TARGET(7, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=07, y=06) */ {
        /* Level ID */ LEVEL_REMIX_6,
        /* Show Req */ (s8[]) { REQ_CLEAR(6, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(7, 7), REQ_CLEAR(7, 8), REQ_CLEAR(7, 9), REQ_CLEAR(7, 10), REQ_CLEAR(7, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(8, 6), TARGET(1, 7), TARGET(8, 7), TARGET(8, 8), TARGET(8, 9), TARGET(8, 10), TARGET(7, 11), TARGET(8, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=08, y=06) */ {
        /* Level ID */ LEVEL_REMIX_7,
        /* Show Req */ (s8[]) { REQ_CLEAR(7, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(8, 7), REQ_CLEAR(8, 8), REQ_CLEAR(8, 9), REQ_CLEAR(8, 10), REQ_CLEAR(8, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(9, 6), TARGET(9, 7), TARGET(9, 8), TARGET(9, 9), TARGET(9, 10), TARGET(8, 11), TARGET(9, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=09, y=06) */ {
        /* Level ID */ LEVEL_REMIX_8,
        /* Show Req */ (s8[]) { REQ_CLEAR(8, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(9, 7), REQ_CLEAR(9, 8), REQ_CLEAR(9, 9), REQ_CLEAR(9, 10), REQ_CLEAR(9, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(1, 6), TARGET(9, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=10, y=06) */ {
        /* Level ID */ LEVEL_REMIX_1_EXTRA,
        /* Show Req */ (s8[]) { REQ_TOTAL_MEDALS(48), REQ_CLEAR(9, 6), REQ_OPEN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(10, 7), REQ_CLEAR(10, 8), REQ_CLEAR(10, 9), REQ_CLEAR(10, 10), REQ_CLEAR(10, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(10, 11), END_TARGETS },
        /* Flags */ DELAY_CLEAR,
        /* Delay */ 5
    },
    /* Entry (x=11, y=06) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=06) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=06) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=06) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=07) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=07) */ {
        /* Level ID */ LEVEL_STAFF_CREDIT,
        /* Show Req */ (s8[]) { REQ_CLEAR(2, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(7, 6), END_REQ },
        /* Targets  */ NULL,
        /* Flags */ CLEAR_BY_DEFAULT,
        /* Delay */ 4
    },
    /* Entry (x=02, y=07) */ {
        /* Level ID */ LEVEL_CLAPPY_TRIO,
        /* Show Req */ (s8[]) { REQ_SHOWN(2, 11), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(2, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(2, 6), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=03, y=07) */ {
        /* Level ID */ LEVEL_BON_ODORI,
        /* Show Req */ (s8[]) { REQ_SHOWN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(3, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(3, 6), TARGET(3, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=04, y=07) */ {
        /* Level ID */ LEVEL_SPACE_DANCE,
        /* Show Req */ (s8[]) { REQ_CLEAR(3, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(4, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(4, 6), TARGET(4, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=05, y=07) */ {
        /* Level ID */ LEVEL_RAP_MEN,
        /* Show Req */ (s8[]) { REQ_CLEAR(4, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(5, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(5, 6), TARGET(5, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=06, y=07) */ {
        /* Level ID */ LEVEL_TAP_TRIAL,
        /* Show Req */ (s8[]) { REQ_CLEAR(5, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(6, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(6, 6), TARGET(6, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=07, y=07) */ {
        /* Level ID */ LEVEL_TAP_TRIAL_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(6, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(7, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(7, 6), TARGET(7, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=08, y=07) */ {
        /* Level ID */ LEVEL_MARCHING_ORDERS_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(7, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(8, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(8, 6), TARGET(8, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=09, y=07) */ {
        /* Level ID */ LEVEL_SNEAKY_SPIRITS_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(8, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(9, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(9, 6), TARGET(9, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=10, y=07) */ {
        /* Level ID */ LEVEL_CLAPPY_TRIO_EXTRA,
        /* Show Req */ (s8[]) { REQ_TOTAL_MEDALS(48), REQ_CLEAR(9, 6), REQ_OPEN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(10, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(10, 6), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 4
    },
    /* Entry (x=11, y=07) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=07) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=07) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=07) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=08) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=08) */ {
        /* Level ID */ LEVEL_DRUM_LESSONS,
        /* Show Req */ (s8[]) { REQ_CLEAR(2, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(1, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(1, 8), END_TARGETS },
        /* Flags */ CLEAR_BY_DEFAULT,
        /* Delay */ 3
    },
    /* Entry (x=02, y=08) */ {
        /* Level ID */ LEVEL_SPACEBALL,
        /* Show Req */ (s8[]) { REQ_SHOWN(2, 11), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(2, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(2, 6), TARGET(2, 7), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=03, y=08) */ {
        /* Level ID */ LEVEL_SICK_BEATS,
        /* Show Req */ (s8[]) { REQ_SHOWN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(3, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(3, 6), TARGET(3, 7), TARGET(3, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=04, y=08) */ {
        /* Level ID */ LEVEL_TRAM_PAULINE,
        /* Show Req */ (s8[]) { REQ_CLEAR(3, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(4, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(4, 6), TARGET(4, 7), TARGET(4, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=05, y=08) */ {
        /* Level ID */ LEVEL_POLYRHYTHM,
        /* Show Req */ (s8[]) { REQ_CLEAR(4, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(5, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(5, 6), TARGET(5, 7), TARGET(5, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=06, y=08) */ {
        /* Level ID */ LEVEL_FIREWORKS,
        /* Show Req */ (s8[]) { REQ_CLEAR(5, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(6, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(6, 6), TARGET(6, 7), TARGET(6, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=07, y=08) */ {
        /* Level ID */ LEVEL_RAP_WOMEN,
        /* Show Req */ (s8[]) { REQ_CLEAR(6, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(7, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(7, 6), TARGET(7, 7), TARGET(7, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=08, y=08) */ {
        /* Level ID */ LEVEL_NIGHT_WALK_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(7, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(8, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(8, 6), TARGET(8, 7), TARGET(8, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=09, y=08) */ {
        /* Level ID */ LEVEL_SPACEBALL_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(8, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(9, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(9, 6), TARGET(9, 7), TARGET(9, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=10, y=08) */ {
        /* Level ID */ LEVEL_SPACEBALL_EXTRA,
        /* Show Req */ (s8[]) { REQ_TOTAL_MEDALS(48), REQ_CLEAR(9, 6), REQ_OPEN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(10, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(10, 6), TARGET(10, 7), TARGET(10, 11),END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 3
    },
    /* Entry (x=11, y=08) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=08) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=08) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=08) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=09) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=09) */ {
        /* Level ID */ LEVEL_ENDLESS_GAMES,
        /* Show Req */ (s8[]) { REQ_CLEAR(2, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(1, 9), END_REQ },
        /* Targets  */ (s8[]) { TARGET(1, 9), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | CLEAR_BY_DEFAULT,
        /* Delay */ 2
    },
    /* Entry (x=02, y=09) */ {
        /* Level ID */ LEVEL_MARCHING_ORDERS,
        /* Show Req */ (s8[]) { REQ_SHOWN(2, 11), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(2, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(2, 6), TARGET(2, 8), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=03, y=09) */ {
        /* Level ID */ LEVEL_RAT_RACE,
        /* Show Req */ (s8[]) { REQ_SHOWN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(3, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(3, 6), TARGET(3, 8), TARGET(3, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=04, y=09) */ {
        /* Level ID */ LEVEL_BUNNY_HOP,
        /* Show Req */ (s8[]) { REQ_CLEAR(3, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(4, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(4, 6), TARGET(4, 8), TARGET(4, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=05, y=09) */ {
        /* Level ID */ LEVEL_POWER_CALLIGRAPHY,
        /* Show Req */ (s8[]) { REQ_CLEAR(5, 8), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(5, 8), END_REQ },
        /* Targets  */ (s8[]) { TARGET(5, 6), TARGET(5, 8), TARGET(5, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=06, y=09) */ {
        /* Level ID */ LEVEL_TOSS_BOYS,
        /* Show Req */ (s8[]) { REQ_CLEAR(5, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(6, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(6, 6), TARGET(6, 8), TARGET(6, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=07, y=09) */ {
        /* Level ID */ LEVEL_COSMIC_DANCE,
        /* Show Req */ (s8[]) { REQ_CLEAR(6, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(7, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(7, 6), TARGET(7, 8), TARGET(7, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=08, y=09) */ {
        /* Level ID */ LEVEL_NINJA_REINCARNATE,
        /* Show Req */ (s8[]) { REQ_CLEAR(7, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(8, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(8, 6), TARGET(8, 8), TARGET(8, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=09, y=09) */ {
        /* Level ID */ LEVEL_POLYRHYTHM_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(8, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(9, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(9, 6), TARGET(9, 8), TARGET(9, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=10, y=09) */ {
        /* Level ID */ LEVEL_MARCHING_ORDERS_EXTRA,
        /* Show Req */ (s8[]) { REQ_TOTAL_MEDALS(48), REQ_CLEAR(9, 6), REQ_OPEN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(10, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(10, 6), TARGET(10, 8), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 2
    },
    /* Entry (x=11, y=09) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=09) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=09) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=09) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=10) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=10) */ {
        /* Level ID */ LEVEL_RHYTHM_TOYS,
        /* Show Req */ (s8[]) { REQ_CLEAR(2, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(1, 10), END_REQ },
        /* Targets  */ (s8[]) { TARGET(1, 10), END_TARGETS },
        /* Flags */ CLEAR_BY_DEFAULT,
        /* Delay */ 1
    },
    /* Entry (x=02, y=10) */ {
        /* Level ID */ LEVEL_RHYTHM_TWEEZERS,
        /* Show Req */ (s8[]) { REQ_SHOWN(2, 11), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(2, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(2, 6), TARGET(2, 9), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=03, y=10) */ {
        /* Level ID */ LEVEL_SAMURAI_SLICE,
        /* Show Req */ (s8[]) { REQ_SHOWN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(3, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(3, 6), TARGET(3, 9), TARGET(3, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=04, y=10) */ {
        /* Level ID */ LEVEL_SHOWTIME,
        /* Show Req */ (s8[]) { REQ_CLEAR(3, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(4, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(4, 6), TARGET(4, 9), TARGET(4, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=05, y=10) */ {
        /* Level ID */ LEVEL_NIGHT_WALK,
        /* Show Req */ (s8[]) { REQ_CLEAR(4, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(5, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(5, 6), TARGET(5, 9), TARGET(5, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=06, y=10) */ {
        /* Level ID */ LEVEL_NINJA_BODYGUARD,
        /* Show Req */ (s8[]) { REQ_CLEAR(5, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(6, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(6, 6), TARGET(6, 9), TARGET(6, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=07, y=10) */ {
        /* Level ID */ LEVEL_BON_DANCE,
        /* Show Req */ (s8[]) { REQ_CLEAR(6, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(7, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(7, 6), TARGET(7, 9), TARGET(7, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=08, y=10) */ {
        /* Level ID */ LEVEL_RHYTHM_TWEEZERS_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(7, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(8, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(8, 6), TARGET(8, 9), TARGET(8, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=09, y=10) */ {
        /* Level ID */ LEVEL_TOSS_BOYS_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(8, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(9, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(9, 6), TARGET(9, 9), TARGET(9, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=10, y=10) */ {
        /* Level ID */ LEVEL_RHYTHM_TWEEZERS_EXTRA,
        /* Show Req */ (s8[]) { REQ_TOTAL_MEDALS(48), REQ_CLEAR(9, 6), REQ_OPEN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_CLEAR(10, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(10, 6), TARGET(10, 9), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 1
    },
    /* Entry (x=11, y=10) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=10) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=10) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=10) */ EMPTY_GRID_ENTRY,

    /* Entry (x=00, y=11) */ EMPTY_GRID_ENTRY,
    /* Entry (x=01, y=11) */ {
        /* Level ID */ LEVEL_CAFE,
        /* Show Req */ (s8[]) { REQ_CLEAR(2, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(1, 11), END_REQ },
        /* Targets  */ (s8[]) { TARGET(1, 11), END_TARGETS },
        /* Flags */ CLEAR_BY_DEFAULT,
        /* Delay */ 0
    },
    /* Entry (x=02, y=11) */ {
        /* Level ID */ LEVEL_KARATE_MAN,
        /* Show Req */ NULL,
        /* Open Req */ NULL,
        /* Targets  */ (s8[]) { TARGET(2, 6), TARGET(2, 7), TARGET(2, 8), TARGET(2, 9), TARGET(2, 10), TARGET(10, 11), END_TARGETS },
        /* Flags */ 0,
        /* Delay */ 0
    },
    /* Entry (x=03, y=11) */ {
        /* Level ID */ LEVEL_SNEAKY_SPIRITS,
        /* Show Req */ (s8[]) { REQ_SHOWN(1, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(3, 11), REQ_SHOWN(3, 10), REQ_SHOWN(3, 9), REQ_SHOWN(3, 8), REQ_SHOWN(3, 7), REQ_SHOWN(3, 6), END_REQ },
        /* Targets  */ (s8[]) { TARGET(3, 6), TARGET(3, 10), TARGET(3, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | DELAY_OPEN,
        /* Delay */ 0
    },
    /* Entry (x=04, y=11) */ {
        /* Level ID */ LEVEL_WIZARDS_WALTZ,
        /* Show Req */ (s8[]) { REQ_CLEAR(3, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(4, 11), REQ_SHOWN(4, 10), REQ_SHOWN(4, 9), REQ_SHOWN(4, 8), REQ_SHOWN(4, 7), REQ_SHOWN(4, 6), END_REQ },
        /* Targets  */ (s8[]) { TARGET(4, 6), TARGET(4, 10), TARGET(4, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | DELAY_OPEN,
        /* Delay */ 0
    },
    /* Entry (x=05, y=11) */ {
        /* Level ID */ LEVEL_QUIZ_SHOW,
        /* Show Req */ (s8[]) { REQ_CLEAR(4, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(5, 11), REQ_SHOWN(5, 10), REQ_SHOWN(5, 9), REQ_SHOWN(5, 8), REQ_SHOWN(5, 7), REQ_SHOWN(5, 6), END_REQ },
        /* Targets  */ (s8[]) { TARGET(5, 6), TARGET(5, 10), TARGET(5, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | DELAY_OPEN,
        /* Delay */ 0
    },
    /* Entry (x=06, y=11) */ {
        /* Level ID */ LEVEL_BOUNCY_ROAD,
        /* Show Req */ (s8[]) { REQ_CLEAR(5, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(6, 11), REQ_SHOWN(6, 10), REQ_SHOWN(6, 9), REQ_SHOWN(6, 8), REQ_SHOWN(6, 7), REQ_SHOWN(6, 6), END_REQ },
        /* Targets  */ (s8[]) { TARGET(6, 6), TARGET(6, 10), TARGET(6, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | DELAY_OPEN,
        /* Delay */ 0
    },
    /* Entry (x=07, y=11) */ {
        /* Level ID */ LEVEL_SNAPPY_TRIO,
        /* Show Req */ (s8[]) { REQ_CLEAR(6, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(7, 11), REQ_SHOWN(7, 10), REQ_SHOWN(7, 9), REQ_SHOWN(7, 8), REQ_SHOWN(7, 7), REQ_SHOWN(7, 6), END_REQ },
        /* Targets  */ (s8[]) { TARGET(7, 6), TARGET(7, 10), TARGET(7, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | DELAY_OPEN,
        /* Delay */ 0
    },
    /* Entry (x=08, y=11) */ {
        /* Level ID */ LEVEL_KARATE_MAN_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(7, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(8, 11), REQ_SHOWN(8, 10), REQ_SHOWN(8, 9), REQ_SHOWN(8, 8), REQ_SHOWN(8, 7), REQ_SHOWN(8, 6), END_REQ },
        /* Targets  */ (s8[]) { TARGET(8, 6), TARGET(8, 10), TARGET(8, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | DELAY_OPEN,
        /* Delay */ 0
    },
    /* Entry (x=09, y=11) */ {
        /* Level ID */ LEVEL_BOUNCY_ROAD_2,
        /* Show Req */ (s8[]) { REQ_CLEAR(8, 6), END_REQ },
        /* Open Req */ (s8[]) { REQ_SHOWN(9, 11), REQ_SHOWN(9, 10), REQ_SHOWN(9, 9), REQ_SHOWN(9, 8), REQ_SHOWN(9, 7), REQ_SHOWN(9, 6), END_REQ },
        /* Targets  */ (s8[]) { TARGET(9, 6), TARGET(9, 10), TARGET(9, 11), TARGET(10, 11), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | DELAY_OPEN,
        /* Delay */ 0
    },
    /* Entry (x=10, y=11) */ {
        /* Level ID */ LEVEL_KARATE_MAN_EXTRA,
        /* Show Req */ (s8[]) { REQ_TOTAL_MEDALS(48), REQ_CLEAR(9, 6), REQ_OPEN(1, 6), END_REQ },
        /* Open Req */ (s8[]) {
            REQ_TOTAL_MEDALS(48),
            REQ_SHOWN(10, 11), REQ_SHOWN(10, 10), REQ_SHOWN(10, 9), REQ_SHOWN(10, 8), REQ_SHOWN(10, 7), REQ_SHOWN(10, 6),
            END_REQ
        },
        /* Targets  */ (s8[]) { TARGET(10, 6), TARGET(10, 10), TARGET(10, 11), END_TARGETS },
        /* Flags */ TARGET_ON_SHOW | TARGET_ON_OPEN | DELAY_OPEN,
        /* Delay */ 0
    },
    /* Entry (x=11, y=11) */ EMPTY_GRID_ENTRY,
    /* Entry (x=12, y=11) */ EMPTY_GRID_ENTRY,
    /* Entry (x=13, y=11) */ EMPTY_GRID_ENTRY,
    /* Entry (x=14, y=11) */ EMPTY_GRID_ENTRY
};
