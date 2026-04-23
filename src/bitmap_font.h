#pragma once

#include "global.h"
#include "graphics.h"
#include "data/bitmap_font_data.h"

// Definition of a Bitmap Font.
struct BitmapFontData {
    u8 whitespaceWidth;  // Whitespace Width
    u8 textureWidth;     // Glyph Texture Width
    u8 textureHeight;    // Glyph Texture Height
    u8 descensionHeight; // Descension Height for Lowercase Latin Alphabet Characters
    s8 spacingWidth;     // Glyph Spacing
    const void *symbolTextures;
    const u8 *symbolWidths;
    const void *arabicNumeralTextures;
    const u8 *arabicNumeralWidths;
    const void *latinUppercaseTextures;
    const u8 *latinUppercaseWidths;
    const void *latinLowercaseTextures;
    const u8 *latinLowercaseWidths;
    const void *hiraganaTextures;
    const u8 *hiraganaWidths;
    const void *katakanaTextures;
    const u8 *katakanaWidths;
};

struct BmpFontSymbolEntry {
    u16 codepoint;
    u8  index;
};

// Bitmap Font Printer which creates OBJ Animations.
struct BitmapFontOBJ {
    u16 memID;
    const struct BitmapFontData *fonts;
    u16 baseTileNum;
    u8 maxAllocatedTileRows;
    u16 *printedGlyphs;
    u8 *printedGlyphCounts;
    void (*parseString)(char *, const char *);
    char *parsedOutput;
};

// Bitmap Font Printer which writes to BG Maps.
struct BitmapFontBG {
    const struct BitmapFontData *fonts;
    u16 baseTileNum;
    u8 tilesetID;
    u8 maxAllocatedTileRows;
    u16 *printedGlyphs;
    u8 *printedGlyphCounts;
};

// Generated OBJ Animation for text.
struct PrintedTextAnim {
    struct Animation frames[2];
    u16 oam[0];
};

// Generated OBJ Animation for wobbly/shaky text.
struct WobblyPrintedTextAnim {
    struct Animation frames[6];
    u16 oam[0];
};

// Text queue for the multi-string BitmapFontOBJ printer task.
struct BitmapFontQueuedText {
    const char *string;
    u32 alignment:4;
    u32 fontStyle:4;
    u32 palette:4;
};

// Multi-string BitmapFontOBJ printer task.
struct BitmapFontOBJPrinter {
    struct BitmapFontOBJ *textObj;
    struct PrintedTextAnim **animTable;
    struct BitmapFontQueuedText *queue;
    u32 current;
};

// BitmapFontBG printer task.
struct BitmapFontBGPrinter {
    struct BitmapFontBG *textObj;
    u32 fontStyle:4;
    u32 palette:4;
    u32 processLimit:8;
    u32 currentMapX:10;
    u16 bgMapWidth;
    u16 *bgMap;
    const char *string;
};


extern void bmp_font_get_glyph(const struct BitmapFontData *font, const char *string, const u16 **textureReq, u32 *widthReq);
extern struct BitmapFontOBJ *create_new_bmp_font_obj_alt(u16 memID, const struct BitmapFontData *fonts, u32 baseTileNum, u32 maxTileRows);
extern struct BitmapFontOBJ *create_new_bmp_font_obj(u16 memID, const struct BitmapFontData *fonts, u16 baseTileNum, u8 maxTileRows);
extern void delete_bmp_font_obj(struct BitmapFontOBJ *textObj);
extern void bmp_font_obj_set_format_parser(struct BitmapFontOBJ *textObj, void *stringParserFunc, u32 maxOutputLength);
extern void bmp_font_obj_set_data(struct BitmapFontOBJ *textObj, const struct BitmapFontData *fonts, u16 baseTileNum, u8 maxTileRows, u32, u32, u16 *printedGlyphs, u8 *printedGlyphCounts);
extern void bmp_font_obj_clear_print_data(struct BitmapFontOBJ *textObj);
extern u32 bmp_font_obj_get_anim_total(const char *string);
extern u32 bmp_font_obj_get_glyph_width(const struct BitmapFontData *font, const char *string);
extern u8 bmp_font_obj_parse_hex_digit(char c);
extern u32 bmp_font_obj_get_string_width(const struct BitmapFontData *font, const char *string);
extern void bmp_font_obj_write_glyph(const u16 *texture, u16 *dest);
extern u16 bmp_font_obj_print_glyph(struct BitmapFontOBJ *textObj, const char *string, u32 *widthReq);
extern u32 bmp_font_obj_glyph_is_whitespace(const char *string);
extern u32 bmp_font_obj_get_latin_glyph_type(const char *string);
extern struct PrintedTextAnim *bmp_font_obj_print_text(struct BitmapFontOBJ *textObj, const char *string, u32 *widthReq, u32 fontStyle, u32 palette);
extern struct PrintedTextAnim *bmp_font_obj_print_unaligned_default(struct BitmapFontOBJ *textObj, const char *string);
extern struct PrintedTextAnim *bmp_font_obj_print_unaligned(struct BitmapFontOBJ *textObj, const char *string, u32 fontStyle, u32 palette);
extern struct PrintedTextAnim *bmp_font_obj_print_c_default(struct BitmapFontOBJ *textObj, const char *string);
extern struct PrintedTextAnim *bmp_font_obj_print_c(struct BitmapFontOBJ *textObj, const char *string, u32 fontStyle, u32 palette);
extern struct PrintedTextAnim *bmp_font_obj_print_l_default(struct BitmapFontOBJ *textObj, const char *string);
extern struct PrintedTextAnim *bmp_font_obj_print_l(struct BitmapFontOBJ *textObj, const char *string, u32 fontStyle, u32 palette);
extern struct PrintedTextAnim *bmp_font_obj_print_r_default(struct BitmapFontOBJ *textObj, const char *string);
extern struct PrintedTextAnim *bmp_font_obj_print_r(struct BitmapFontOBJ *textObj, const char *string, u32 fontStyle, u32 palette);
extern struct PrintedTextAnim *bmp_font_obj_print_to_xy_default(struct BitmapFontOBJ *textObj, const char *string, s16 x, s16 y);
extern struct PrintedTextAnim *bmp_font_obj_print_to_xy(struct BitmapFontOBJ *textObj, const char *string, s16 x, s16 y, u32 fontStyle, u32 palette);
extern void bmp_font_obj_delete_printed_anim(struct BitmapFontOBJ *textObj, struct Animation *anim);
extern struct BitmapFontOBJPrinter *bmp_font_obj_init_multi_printer(struct BitmapFontOBJPrinter *inputs);
extern u32 bmp_font_obj_update_multi_printer(struct BitmapFontOBJPrinter *info);
extern s32 bmp_font_obj_print_multiple(u16 memID, struct BitmapFontOBJ *textObj, struct PrintedTextAnim **animTable, struct BitmapFontQueuedText *queue);
extern void bmp_font_obj_delete_multi_printed_anim(struct BitmapFontOBJ *textObj, struct PrintedTextAnim **animTable, struct BitmapFontQueuedText *queue);
extern struct WobblyPrintedTextAnim *bmp_font_obj_print_wobbly(struct BitmapFontOBJ *textObj, struct PrintedTextAnim *anim, u8 frameDuration);
extern void bmp_font_obj_wobble_printed_anim(struct BitmapFontOBJ *textObj, struct PrintedTextAnim **anim, u8 frameDuration);
extern void bmp_font_obj_curve_anim_y(struct Animation *anim, s16 vel);
extern void bmp_font_obj_move_anim_xy(struct Animation *anim, s16 x, s16 y);

extern struct BitmapFontBG *create_new_bmp_font_bg(u16 memID, const struct BitmapFontData *fonts, u8 bgTilesetID, u16 baseTileNum, u8 maxTileRows);
extern void delete_bmp_font_bg(struct BitmapFontBG *textObj);
extern void bmp_font_bg_set_data(struct BitmapFontBG *textObj, const struct BitmapFontData *fonts, u8 bgTilesetID, u16 baseTileNum, u8 maxTileRows, u16 *printedGlyphs, u8 *printedGlyphCounts);
extern void bmp_font_bg_clear_print_data(struct BitmapFontBG *textObj);
extern void bmp_font_bg_write_glyph(const u16 *texture, u16 *dest);
extern u16 bmp_font_bg_print_glyph(struct BitmapFontBG *textObj, const char *string);
extern u8 bmp_font_bg_parse_hex_digit(char c);
extern void bmp_font_bg_print_text(struct BitmapFontBG *textObj, u16 *bgMap, u32 mapWidth, const char *string, u32 palette);
extern void bmp_font_bg_delete_printed_data(struct BitmapFontBG *textObj, const char *string);
extern struct BitmapFontBGPrinter *bmp_font_bg_init_printer(struct BitmapFontBGPrinter *inputs);
extern u32 bmp_font_bg_update_printer(struct BitmapFontBGPrinter *info);
extern s32 start_bmp_font_bg_printer_task(u16 memID, struct BitmapFontBG *textObj, u16 *bgMapDest, u32 bgMapWidth, const char *string, u32 palette, u32 processLimit);
extern u32 bmp_font_bg_get_total_printable_chars(const char *string);


// Scene-initialisation data for Objects/Sprites, on the level of Graphics Tables and Buffered Texture lists.
union SceneObject {
    // Generic access to the "type" field.
    u8 *type;

    // [TYPE 0] Sprite with an immediate XY position.
    struct SceneSprite {
        u8 type;
        s8 poolID;
        struct Animation *anim;
        s8 unk8;
        s16 x;
        s16 y;
        u16 z;
        s8 unk10;
        s8 unk11;
        u16 unk12;
        u32 unk14;
    } *sprite;

    // [TYPE 1] Sprite with a pointer XY position.
    struct SceneSpriteVecXY {
        u8 type;
        s8 poolID;
        struct Animation *anim;
        s8 unk8;
        struct Vector2 *pos;
        u16 z;
        s8 unk12;
        s8 unk13;
        u16 unk14;
        u32 unk18;
    } *spriteVecXY;

    // [TYPE 2] Text Sprite, written with a Bitmap Font.
    struct SceneText {
        u8 type;
        s8 poolID;
        const char **textTable;
        u8 alignment;
        u8 fontStyle;
        u8 palette;
        u8 display:1;
        u8 wobbly:7;
        s16 x;
        s16 y;
        u16 z;
        u32 unk14;
    } *text;
};

// SceneObject rendering task.
struct SceneObjectRenderer {
    struct SpriteHandler *spriteHandler;
    struct BitmapFontOBJ *bitmapFontOBJ;
    const union SceneObject *objects;
    s16 *spritePool;
};

// Values for the SceneObject "type" field.
enum SceneObjectTypesEnum {
    SCENE_OBJECT_TYPE_IMM_XY,
    SCENE_OBJECT_TYPE_VEC_XY,
    SCENE_OBJECT_TYPE_TEXT
};

// End of SceneObject list.
#define END_OF_SCENE_OBJECTS_LIST { .type = NULL }


extern void import_scene_object(struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject object, s16 *spritePool);
extern u32 import_all_scene_objects(struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject *objects, s16 *spritePool);
extern void set_scene_object_current_text_id(u32 textID);
extern struct SceneObjectRenderer *init_scene_object_importer(struct SceneObjectRenderer *inputs);
extern u32 update_scene_object_importer(struct SceneObjectRenderer *info);
extern s32 start_new_scene_object_importer(u16 memID, struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject *objects, s16 *spritePool);
extern void delete_all_scene_objects(struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject *objects, s16 *spritePool);
extern void display_all_scene_objects(struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject *objects, s16 *spritePool, u32 show);
