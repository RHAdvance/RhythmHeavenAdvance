#include "global.h"
#include "graphics.h"
#include "src/scenes/medal_corner.h"
#include "graphics/medal_corner/medal_corner_graphics.h"


  /* MEDAL CORNER MENUS - SCENE DATA */


extern struct MedalCornerMenu toys_menu_data;
extern struct MedalCornerMenu endless_menu_data;
extern struct MedalCornerMenu lessons_menu_data;
extern const u8 endlessgames_bg_bin;
extern const u8 endlessgames_bg_map_bin;
extern const u8 endlessgames_obj_bin;
extern const u8 rhythmtoys_bg_bin;
extern const u8 rhythmtoys_bg_map_bin;
extern const u8 rhythmtoys_obj_bin;
extern const u8 drumlessons_bg_bin;
extern const u8 drumlessons_bg_map_bin;
extern const u8 drumlessons_obj_bin;

// [D_089dd498] Medal Corner Menus
struct MedalCornerMenu *medal_corner_menu_table[] = {
    /* TOYS    */ &toys_menu_data,
    /* ENDLESS */ &endless_menu_data,
    /* LESSONS */ &lessons_menu_data
};


#include "toys_menu.inc.c"
#include "endless_menu.inc.c"
#include "lessons_menu.inc.c"


// [D_089dd794] ???
char medal_corner_locked_text[] = "???";


// [D_089dd79c] Buffered Textures List
struct CompressedData *medal_corner_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};
