#include "bitmap_font.h"
#include "code_08001360.h"
#include "memory_heap.h"
#include "src/lib_0804ca80.h"
#include "src/utf_8.h"

asm(".include \"include/gba.inc\"");//Temporary


  //  //  //  BITMAP FONT  //  //  //


static u8 sObjFontStyle; // BitmapFontOBJ - Font/Style
static u8 sObjStringGlyphWidths[0x40]; // BitmapFontOBJ - Width of Each Glyph in the Current String
static u32 sBgFontStyle; // BitmapFontBG - Font/Style

struct BitmapFontGlyph {
    const struct BitmapFontRange* glyphSet;
    u8 glyphID;
};

extern s32 (*math_sqrt)(s32);
extern u8 sSceneTextCurrentStringId; // Current String in Scene Text Table to Print with SceneObject


static s32 bmp_font_is_hex_digit(char c) {
    if ((c >= '0') && (c <= '9')) {
        return TRUE;
    }

    if ((c >= 'a') && (c <= 'f')) {
        return TRUE;
    }

    if ((c >= 'A') && (c <= 'F')) {
        return TRUE;
    }

    return FALSE;
}


static s32 bmp_font_is_control_code(const char *string, char cmd) {
    return (string[0] == cmd) && bmp_font_is_hex_digit(string[1]);
}


static s32 bmp_font_codepoint_to_glyph(const struct BitmapFontData *font, u32 codepoint, struct BitmapFontGlyph *glyphReq) {
    const struct BitmapFontRange *glyphRange;

    glyphRange = font->glyphRanges;
    while (glyphRange->glyphTextures != NULL) {
        if ((codepoint >= glyphRange->utf8Start) && (codepoint <= glyphRange->utf8End)) {
            if (glyphReq != NULL) {
                glyphReq->glyphSet = glyphRange;
                glyphReq->glyphID = (u8)(codepoint - glyphRange->utf8Start);
            }
            return TRUE;
        }

        glyphRange++;
    }

    return FALSE;
}


static s32 bmp_font_get_glyph_info(const struct BitmapFontData *font, const char *string, struct BitmapFontGlyph *glyphReq, const char **nextString) {
    const char *next;
    s32 codepoint;

    if (nextString != NULL) {
        *nextString = string;
    }

    if (string[0] == '\0') {
        return FALSE;
    }

    next = string;
    if (!utf8_decode_codepoint(&next, &codepoint)) {
        if (nextString != NULL) {
            *nextString = next;
        }
        return FALSE;
    }

    if (nextString != NULL) {
        *nextString = next;
    }

    return bmp_font_codepoint_to_glyph(font, codepoint, glyphReq);
}


// Get printable glyph texture and width.
void bmp_font_get_glyph(const struct BitmapFontData *font, const char *string, const u16 **textureReq, u32 *widthReq) {
    const void *textures;
    const u8 *widths;
    struct BitmapFontGlyph glyph;
    u32 id;

    textures = NULL;
    widths = NULL;

    if (!bmp_font_get_glyph_info(font, string, &glyph, NULL)) {
        if (textureReq != NULL) {
            *textureReq = NULL;
        }
        if (widthReq != NULL) {
            *widthReq = 0;
        }
        return;
    }

    textures = glyph.glyphSet->glyphTextures;
    widths = glyph.glyphSet->glyphWidths;
    id = glyph.glyphID;

    if (textures == NULL) {
        if (textureReq != NULL) {
            *textureReq = NULL;
        }
        if (widthReq != NULL) {
            *widthReq = 0;
        }
    } else {
        if (textureReq != NULL) {
            *textureReq = textures + (((font->textureWidth * font->textureHeight) / 2) * id);
        }

        if (widthReq != NULL) {
            if (widths != NULL) {
                *widthReq = widths[id];
            } else {
                *widthReq = font->textureWidth;
            }
        }
    }
}


// Create new BitmapFont (no casting?).
struct BitmapFontOBJ *create_new_bmp_font_obj_alt(u16 memID, const struct BitmapFontData *fonts, u32 baseTileNum, u32 maxTileRows) {
    return create_new_bmp_font_obj(memID, fonts, baseTileNum, maxTileRows);
}


// Create new BitmapFontOBJ.
struct BitmapFontOBJ *create_new_bmp_font_obj(u16 memID, const struct BitmapFontData *fonts, u16 baseTileNum, u8 maxTileRows) {
    struct BitmapFontOBJ *textObj;

    textObj = mem_heap_alloc_id(memID, sizeof(struct BitmapFontOBJ));
    textObj->memID = memID;
    textObj->fonts = fonts;
    textObj->baseTileNum = baseTileNum;
    textObj->maxAllocatedTileRows = maxTileRows;
    textObj->printedGlyphs = mem_heap_alloc_id(memID, maxTileRows * 16 * sizeof(u16));
    textObj->printedGlyphCounts = mem_heap_alloc_id(memID, maxTileRows * 16 * sizeof(u8));
    textObj->parseString = NULL;
    textObj->parsedOutput = NULL;
    bmp_font_obj_clear_print_data(textObj);

    return textObj;
}


// Delete BitmapFontOBJ.
void delete_bmp_font_obj(struct BitmapFontOBJ *textObj) {
    mem_heap_dealloc(textObj->printedGlyphs);
    mem_heap_dealloc(textObj->printedGlyphCounts);
    if (textObj->parsedOutput != NULL) {
        mem_heap_dealloc(textObj->parsedOutput);
    }
    mem_heap_dealloc(textObj);
}


// Set BitmapFontOBJ parseString() function and allocate space for parsedOutput.
void bmp_font_obj_set_format_parser(struct BitmapFontOBJ *textObj, void *stringParserFunc, u32 maxOutputLength) {
    textObj->parseString = stringParserFunc;
    textObj->parsedOutput = mem_heap_alloc_id(textObj->memID, maxOutputLength);
}


// Set BitmapFontOBJ data.
void bmp_font_obj_set_data(struct BitmapFontOBJ *textObj, const struct BitmapFontData *fonts, u16 baseTileNum, u8 maxTileRows, u32 unused1, u32 unused2, u16 *printedGlyphs, u8 *printedGlyphCounts) {
    textObj->fonts = fonts;
    textObj->baseTileNum = baseTileNum;
    textObj->maxAllocatedTileRows = maxTileRows;
    textObj->printedGlyphs = printedGlyphs;
    textObj->printedGlyphCounts = printedGlyphCounts;
    bmp_font_obj_clear_print_data(textObj);
}


// Clear BitmapFontOBJ printed glyph data.
void bmp_font_obj_clear_print_data(struct BitmapFontOBJ *textObj) {
    u32 i;

    for (i = 0; i < (textObj->maxAllocatedTileRows * 16); i++) {
        textObj->printedGlyphs[i] = 0;
        textObj->printedGlyphCounts[i] = 0;
    }
}


// Get total animation objects required for generated text (ignoring whitespace).
u32 bmp_font_obj_get_anim_total(const char *string) {
    u32 total = 0;

    while (string[0] != '\0') {
        if (bmp_font_is_control_code(string, '.')) {
            string += 2;
            continue;
        }

        if (bmp_font_is_control_code(string, ':')) {
            string += 2;
            continue;
        }

        if (!bmp_font_obj_glyph_is_whitespace(string)) {
            total++;
        }

        string = utf8_get_next_char_ptr(string);
    }

    return total;
}


// Get glyph width.
u32 bmp_font_obj_get_glyph_width(const struct BitmapFontData *font, const char *string) {
    u32 glyphWidth;

    if (bmp_font_obj_glyph_is_whitespace(string)) {
        return font->whitespaceWidth;
    }

    if (bmp_font_is_control_code(string, '.')) {
        return 0;
    }

    if (bmp_font_is_control_code(string, ':')) {
        return 0;
    }

    bmp_font_get_glyph(font, string, NULL, &glyphWidth);
    return glyphWidth;
}


// Parse an ASCII hex digit.
u8 bmp_font_obj_parse_hex_digit(char c) {
    if ((c >= '0') && (c <= '9')) {
        return c - '0';
    }

    if ((c >= 'a') && (c <= 'f')) {
        return c - 'a' + 10;
    }

    if ((c >= 'A') && (c <= 'F')) {
        return c - 'A' + 10;
    }

    return 0;
}


// Get string width.
u32 bmp_font_obj_get_string_width(const struct BitmapFontData *font, const char *string) {
    const struct BitmapFontData *currentFont;
    s32 width;

    currentFont = font;
    width = 0;

    while (string[0] != '\0') {
        if (bmp_font_is_control_code(string, '.')) {
            string += 2;
            continue;
        }

        if (bmp_font_is_control_code(string, ':')) {
            currentFont = &font[bmp_font_obj_parse_hex_digit(string[1])];
            string += 2;
            continue;
        }

        if (width != 0) {
            width += currentFont->spacingWidth;
        }

        width += bmp_font_obj_get_glyph_width(currentFont, string);
        string = utf8_get_next_char_ptr(string);
    }

    if (width < 0) {
        width = 0;
    }

    return width;
}


// Print glyph (fullwidth).
void bmp_font_obj_write_glyph(const u16 *texture, u16 *dest) {
    u32 i;

    for (i = 0; i < 2; i++) {
        dma3_set(texture, dest, 0x40, 0x20, 0x100);
        texture += 0x20;
        dest += 0x200;
    }
}


// Print glyph, returning the tile ID.
u16 bmp_font_obj_print_glyph(struct BitmapFontOBJ *textObj, const char *string, u32 *widthReq) {
    const u16 *texture;
    u16 *address;
    u32 width;
    struct BitmapFontGlyph glyph;
    u8 glyphDataB0, glyphDataB1;
    u32 tileX, tileY, tileID, glyphSet;
    u8 *printed;
    u32 i, j;
    const struct BitmapFontData *font = &textObj->fonts[sObjFontStyle];

    tileX = 99;
    printed = (u8 *)textObj->printedGlyphs;

    if (!bmp_font_get_glyph_info(font, string, &glyph, NULL)) {
        *widthReq = 0;
        return -1;
    }

    glyphSet = glyph.glyphSet - font->glyphRanges;
    glyphDataB0 = (sObjFontStyle << 4) | glyphSet;
    glyphDataB1 = glyph.glyphID;

    for (i = 0; i < textObj->maxAllocatedTileRows; i++) {
        for (j = 0; j < 16; j++) {
            if ((glyphDataB0 == printed[0]) && (glyphDataB1 == printed[1])) {
                *widthReq = bmp_font_obj_get_glyph_width(font, string);
                textObj->printedGlyphCounts[j + (i * 16)]++;
                return textObj->baseTileNum + (j * 2) + ((i * 32) * 2);
            }
            if ((tileX == 99) && (printed[0] == 0) && (printed[1] == 0)) {
                tileX = j;
                tileY = i;
            }
            printed += 2;
        }
    }

    *widthReq = 0;

    if (tileX == 99) {
        return -1;
    }

    tileID = textObj->baseTileNum + (tileX * 2) + ((tileY * 32) * 2);
    address = (void *)((VRAMBase + 0x10000) + (tileID * 0x20));

    bmp_font_get_glyph(font, string, &texture, &width);
    if (texture == NULL) {
        return -1;
    }

    bmp_font_obj_write_glyph(texture, address);
    *widthReq = width;

    i = tileX + (tileY * 16);
    printed = (u8 *)&textObj->printedGlyphs[i];
    printed[0] = glyphDataB0;
    printed[1] = glyphDataB1;
    textObj->printedGlyphCounts[i] = 1;

    return tileID;
}


// Checks if a char is whitespace.
u32 bmp_font_obj_glyph_is_whitespace(const char *string) {
    if (string[0] == ' ') {
        return TRUE;
    }

    return FALSE;
}


// Check if a char is a supported Latin Alphabet char.
u32 bmp_font_obj_get_latin_glyph_type(const char *string) {
    char chr = string[0];

    if (chr >= 'a' && chr <= 'z') {
        return TRUE;
    }

    // Other
    return FALSE;
}


// Create Animation.
struct PrintedTextAnim *bmp_font_obj_print_text(struct BitmapFontOBJ *textObj, const char *string, u32 *widthReq, u32 fontStyle, u32 palette) {
    struct PrintedTextAnim *anim;
    const struct BitmapFontData *currentFont;
    u16 tileNum;
    u16 *oam;
    u32 totalGlyphs;
    u32 glyphWidth;
    s32 xPos;
    u32 glyphIndex;

    if (textObj->parseString != NULL) {
        textObj->parseString(textObj->parsedOutput, string);
        string = textObj->parsedOutput;
    }

    totalGlyphs = bmp_font_obj_get_anim_total(string);
    anim = mem_heap_alloc_id(textObj->memID, (sizeof(struct Animation) * 2) + sizeof(u16) + (totalGlyphs * 3 * sizeof(u16)));
    anim->oam[0] = 0;
    oam = &anim->oam[1];
    xPos = 0;
    glyphIndex = 0;
    sObjFontStyle = fontStyle;

    while (string[0] != '\0') {
        if (bmp_font_is_control_code(string, '.')) {
            palette = bmp_font_obj_parse_hex_digit(string[1]);
            string += 2;
            continue;
        }

        if (bmp_font_is_control_code(string, ':')) {
            sObjFontStyle = bmp_font_obj_parse_hex_digit(string[1]);
            string += 2;
            continue;
        }

        currentFont = &textObj->fonts[sObjFontStyle];
        if (xPos != 0) {
            xPos += currentFont->spacingWidth;
        }

        if (bmp_font_obj_glyph_is_whitespace(string)) {
            xPos += currentFont->whitespaceWidth;
            string = utf8_get_next_char_ptr(string);
            continue;
        }

        tileNum = bmp_font_obj_print_glyph(textObj, string, &glyphWidth);
        if (tileNum == (u16)-1) {
            break;
        }

        if (bmp_font_obj_get_latin_glyph_type(string)) {
            oam[0] = currentFont->descensionHeight;
        } else {
            oam[0] = 0;
        }
        oam[1] = (xPos & 0x1FF) | 0x4000;
        oam[2] = (palette << 12) | tileNum;
        xPos += glyphWidth;

        if (glyphIndex < ARRAY_COUNT(sObjStringGlyphWidths)) {
            sObjStringGlyphWidths[glyphIndex] = glyphWidth;
        }
        glyphIndex++;
        anim->oam[0]++;
        oam += 3;
        string = utf8_get_next_char_ptr(string);
    }

    anim->frames[0].cel = anim->oam;
    anim->frames[0].duration = 100;
    anim->frames[1].cel = NULL;
    anim->frames[1].duration = 0;

    if (widthReq != NULL) {
        *widthReq = xPos;
    }

    return anim;
}


// Get Animation (Unaligned, default FontStyle and Palette).
struct PrintedTextAnim *bmp_font_obj_print_unaligned_default(struct BitmapFontOBJ *textObj, const char *string) {
    return bmp_font_obj_print_unaligned(textObj, string, 0, 0);
}


// Get Animation (Unaligned).
struct PrintedTextAnim *bmp_font_obj_print_unaligned(struct BitmapFontOBJ *textObj, const char *string, u32 fontStyle, u32 palette) {
    return bmp_font_obj_print_text(textObj, string, NULL, fontStyle, palette);
}


// Get Animation (Center-aligned, default FontStyle and Palette).
struct PrintedTextAnim *bmp_font_obj_print_c_default(struct BitmapFontOBJ *textObj, const char *string) {
    return bmp_font_obj_print_c(textObj, string, 0, 0);
}


// Get Animation (Center-aligned).
struct PrintedTextAnim *bmp_font_obj_print_c(struct BitmapFontOBJ *textObj, const char *string, u32 fontStyle, u32 palette) {
    struct PrintedTextAnim *anim;
    u16 *cel, *oam;
    u32 totalWidth, i;

    anim = bmp_font_obj_print_text(textObj, string, &totalWidth, fontStyle, palette);
    totalWidth /= 2;
    cel = anim->frames[0].cel;
    oam = &cel[1];

    for (i = 0; i < cel[0]; i++) {
        ((struct OAM *)oam)->xPos -= totalWidth;
        ((struct OAM *)oam)->yPos -= 8;
        oam += 3;
    }

    return anim;
}


// Get Animation (Left-aligned, default FontStyle and Palette).
struct PrintedTextAnim *bmp_font_obj_print_l_default(struct BitmapFontOBJ *textObj, const char *string) {
    return bmp_font_obj_print_l(textObj, string, 0, 0);
}


// Get Animation (Left-aligned).
struct PrintedTextAnim *bmp_font_obj_print_l(struct BitmapFontOBJ *textObj, const char *string, u32 fontStyle, u32 palette) {
    struct PrintedTextAnim *anim;
    u16 *cel, *oam;
    u32 i;

    anim = bmp_font_obj_print_text(textObj, string, NULL, fontStyle, palette);
    cel = anim->frames[0].cel;
    oam = &cel[1];

    for (i = 0; i < cel[0]; i++) {
        ((struct OAM *)oam)->yPos -= 8;
        oam += 3;
    }

    return anim;
}


// Get Animation (Right-aligned, default FontStyle and Palette).
struct PrintedTextAnim *bmp_font_obj_print_r_default(struct BitmapFontOBJ *textObj, const char *string) {
    return bmp_font_obj_print_r(textObj, string, 0, 0);
}


// Get Animation (Right-aligned).
struct PrintedTextAnim *bmp_font_obj_print_r(struct BitmapFontOBJ *textObj, const char *string, u32 fontStyle, u32 palette) {
    struct PrintedTextAnim *anim;
    u16 *cel, *oam;
    u32 totalWidth, i;

    anim = bmp_font_obj_print_text(textObj, string, &totalWidth, fontStyle, palette);
    cel = anim->frames[0].cel;
    oam = &cel[1];

    for (i = 0; i < cel[0]; i++) {
        ((struct OAM *)oam)->xPos -= totalWidth;
        ((struct OAM *)oam)->yPos -= 8;
        oam += 3;
    }

    return anim;
}


// Get Animation (Shift to XY, default FontStyle and Palette).
struct PrintedTextAnim *bmp_font_obj_print_to_xy_default(struct BitmapFontOBJ *textObj, const char *string, s16 x, s16 y) {
    return bmp_font_obj_print_to_xy(textObj, string, x, y, 0, 0);
}


// Get Animation (Shift to XY).
struct PrintedTextAnim *bmp_font_obj_print_to_xy(struct BitmapFontOBJ *textObj, const char *string, s16 x, s16 y, u32 fontStyle, u32 palette) {
    struct PrintedTextAnim *anim;
    u16 *cel, *oam;
    u32 i;

    anim = bmp_font_obj_print_text(textObj, string, NULL, fontStyle, palette);
    cel = anim->frames[0].cel;
    oam = &cel[1];

    for (i = 0; i < cel[0]; i++) {
        ((struct OAM *)oam)->xPos -= x;
        ((struct OAM *)oam)->yPos -= y;
        oam += 3;
    }

    return anim;
}


// Delete printed BitmapFontOBJ.
void bmp_font_obj_delete_printed_anim(struct BitmapFontOBJ *textObj, struct Animation *anim) {
    u16 *cel, *oam;
    u32 i;

    if (anim == NULL) {
        return;
    }

    cel = anim->cel;
    oam = &cel[1];

    for (i = 0; i < cel[0]; i++) {
        u32 num;

        num = ((struct OAM *)oam)->tileNum - textObj->baseTileNum;
        num = ((num & 0x1F) / 2) + ((num / 64) * 16);

        textObj->printedGlyphCounts[num]--;
        if (textObj->printedGlyphCounts[num] == 0) {
            textObj->printedGlyphs[num] = 0;
        }

        oam += 3;
    }

    mem_heap_dealloc(anim);
}


// Init. BitmapFontOBJPrinter task.
struct BitmapFontOBJPrinter *bmp_font_obj_init_multi_printer(struct BitmapFontOBJPrinter *inputs) {
    struct BitmapFontOBJPrinter *info;

    info = mem_heap_alloc(sizeof(struct BitmapFontOBJPrinter));
    info->textObj = inputs->textObj;
    info->animTable = inputs->animTable;
    info->queue = inputs->queue;
    info->current = 0;

    return info;
}


// Update BitmapFontOBJPrinter task.
u32 bmp_font_obj_update_multi_printer(struct BitmapFontOBJPrinter *info) {
    struct BitmapFontQueuedText *data;
    const char *string;
    u32 current;

    current = info->current;
    data = &info->queue[current];
    string = data->string;

    if (string == NULL) {
        return TRUE;
    }

    if ((s32)string < 0) {
        string = *((const char **)((s32)string & 0x7fffffff));
    }

    switch (data->alignment) {
        case 0:
            info->animTable[current] = bmp_font_obj_print_unaligned(info->textObj, string, data->fontStyle, data->palette);
            break;
        case 1:
            info->animTable[current] = bmp_font_obj_print_c(info->textObj, string, data->fontStyle, data->palette);
            break;
        case 2:
            info->animTable[current] = bmp_font_obj_print_l(info->textObj, string, data->fontStyle, data->palette);
            break;
        case 3:
            info->animTable[current] = bmp_font_obj_print_r(info->textObj, string, data->fontStyle, data->palette);
            break;
    }

    if (data[1].string == NULL) {
        return TRUE;
    } else {
        info->current = current + 1;
        return FALSE;
    }
}


// Start new BitmapFontOBJPrinter task.
s32 bmp_font_obj_print_multiple(u16 memID, struct BitmapFontOBJ *textObj, struct PrintedTextAnim **animTable, struct BitmapFontQueuedText *queue) {
    struct BitmapFontOBJPrinter inputs;

    inputs.textObj = textObj;
    inputs.animTable = animTable;
    inputs.queue = queue;

    return start_new_task(memID, &D_08936b54, &inputs, NULL, 0);
}


// Delete all animations printed by a BitmapFontOBJ.
void bmp_font_obj_delete_multi_printed_anim(struct BitmapFontOBJ *textObj, struct PrintedTextAnim **animTable, struct BitmapFontQueuedText *queue) {
    if (queue->string != NULL) {
        struct BitmapFontQueuedText *strings = queue;
        struct Animation **anim = (struct Animation **)animTable;

        while (strings->string != NULL) {
            bmp_font_obj_delete_printed_anim(textObj, *anim++);
            strings++;
        }
    }
}


// Create "wobbly" animation for printed text.
struct WobblyPrintedTextAnim *bmp_font_obj_print_wobbly(struct BitmapFontOBJ *textObj, struct PrintedTextAnim *anim, u8 frameDuration) {
    struct WobblyPrintedTextAnim *newAnim;
    u16 *cel, *newCel, *newOam;
    u32 count, size;
    u32 i, j;

    count = anim->oam[0];
    cel = &anim->oam[1];

    size = (sizeof(struct Animation) * 6) + ((1 + (count * 3)) * sizeof(u16) * 5);
    newAnim = mem_heap_alloc_id(textObj->memID, size);
    newCel = newAnim->oam;

    for (i = 0; i < (ARRAY_COUNT(newAnim->frames) - 1); i++) {
        (newAnim->frames + i)->cel = newCel;
        (newAnim->frames + i)->duration = frameDuration;
        newCel[0] = count;
        newOam = (newCel += 1);

        for (j = 0; j < (count * 3); j++) {
            *newCel++ = cel[j];
        }

        if (i == 0) {
            continue;
        }

        if (i != 4) {
            for (j = 0; j < count; j++) {
                ((struct OAM *)newOam)->xPos += agb_random(2);
                ((struct OAM *)newOam)->yPos += agb_random(2);

                newOam += 3;
            }
        } else {
            for (j = 0; j < count; j++) {
                if (agb_random(2) != 0) {
                    ((struct OAM *)newOam)->xPos += agb_random(2);
                    ((struct OAM *)newOam)->yPos += 1;
                } else {
                    ((struct OAM *)newOam)->xPos += 1;
                    ((struct OAM *)newOam)->yPos += agb_random(2);
                }

                newOam += 3;
            }
        }
    }

    (newAnim->frames + i)->cel = NULL;
    (newAnim->frames + i)->duration = 0;
    return newAnim;
}


// Replace printed text animation with a wobbly one.
void bmp_font_obj_wobble_printed_anim(struct BitmapFontOBJ *textObj, struct PrintedTextAnim **anim, u8 frameDuration) {
    struct WobblyPrintedTextAnim *wobblyText;

    wobblyText = bmp_font_obj_print_wobbly(textObj, *anim, frameDuration);
    mem_heap_dealloc(*anim);
    *anim = (struct PrintedTextAnim *)wobblyText;
}


// Shift TextObject animation Y position along some sort of curve.
void bmp_font_obj_curve_anim_y(struct Animation *anim, s16 vel) {
    u16 *oam;
    u32 count, i;
    s16 x, centre;

    for (; anim->cel != NULL; anim++) {
        oam = anim->cel;
        count = oam[0];
        oam += 1;

        for (i = 0; i < count; i++) {
            x = ((struct OAM *)oam)->xPos;

            if (x > 256) {
                x -= 512;
            }

            centre = x + (sObjStringGlyphWidths[i] / 2);
            ((struct OAM *)oam)->yPos = -math_sqrt((vel * vel) - (centre * centre)) - 10;

            oam += 3;
        }
    }
}


// Shift TextObject animation position.
void bmp_font_obj_move_anim_xy(struct Animation *anim, s16 x, s16 y) {
    u16 *oam;
    u32 count, i;

    for (; anim->cel != NULL; anim++) {
        oam = anim->cel;
        count = oam[0];
        oam += 1;

        for (i = 0; i < count; i++) {
            ((struct OAM *)oam)->xPos += x;
            ((struct OAM *)oam)->yPos += y;
            oam += 3;
        }
    }
}


// Create new BitmapFontBG.
struct BitmapFontBG *create_new_bmp_font_bg(u16 memID, const struct BitmapFontData *fonts, u8 bgTilesetID, u16 baseTileNum, u8 maxTileRows) {
    struct BitmapFontBG *textObj;

    textObj = mem_heap_alloc_id(memID, sizeof(struct BitmapFontBG));
    textObj->fonts = fonts;
    textObj->tilesetID = bgTilesetID;
    textObj->baseTileNum = baseTileNum;
    textObj->maxAllocatedTileRows = maxTileRows;
    textObj->printedGlyphs = mem_heap_alloc_id(memID, maxTileRows * 16 * sizeof(u16));
    textObj->printedGlyphCounts = mem_heap_alloc_id(memID, maxTileRows * 16 * sizeof(u8));
    bmp_font_bg_clear_print_data(textObj);

    return textObj;
}


// Delete BitmapFontBG.
void delete_bmp_font_bg(struct BitmapFontBG *textObj) {
    mem_heap_dealloc(textObj->printedGlyphs);
    mem_heap_dealloc(textObj->printedGlyphCounts);
    mem_heap_dealloc(textObj);
}


// Set BitmapFontBG data.
void bmp_font_bg_set_data(struct BitmapFontBG *textObj, const struct BitmapFontData *fonts, u8 bgTilesetID, u16 baseTileNum, u8 maxTileRows, u16 *printedGlyphs, u8 *printedGlyphCounts) {
    textObj->fonts = fonts;
    textObj->tilesetID = bgTilesetID;
    textObj->baseTileNum = baseTileNum;
    textObj->maxAllocatedTileRows = maxTileRows;
    textObj->printedGlyphs = printedGlyphs;
    textObj->printedGlyphCounts = printedGlyphCounts;
    bmp_font_bg_clear_print_data(textObj);
}


// Clear BitmapFontBG printed glyph data.
void bmp_font_bg_clear_print_data(struct BitmapFontBG *textObj) {
    u32 i;

    for (i = 0; i < (textObj->maxAllocatedTileRows * 16); i++) {
        textObj->printedGlyphs[i] = 0;
        textObj->printedGlyphCounts[i] = 0;
    }
}


// Print glyph.
void bmp_font_bg_write_glyph(const u16 *texture, u16 *dest) {
    dma3_set(texture, dest, 0x40, 0x10, 0x100);
}


// Print glyph, returning the tile ID.
u16 bmp_font_bg_print_glyph(struct BitmapFontBG *textObj, const char *string) {
    const u16 *texture;
    u16 *address;
    struct BitmapFontGlyph glyph;
    u8 glyphByte0, glyphByte1;
    u32 tileX, tileY, tileID, glyphSet;
    u8 *printed;
    u32 i, j;
    const struct BitmapFontData *font = &textObj->fonts[sBgFontStyle];

    if (!bmp_font_get_glyph_info(font, string, &glyph, NULL)) {
        return -1;
    }

    // Fullwidth Whitespace
    if (bmp_font_obj_glyph_is_whitespace(string)) {
        return -1;
    }

    glyphSet = glyph.glyphSet - font->glyphRanges;
    glyphByte0 = (sBgFontStyle << 4) | glyphSet;
    glyphByte1 = glyph.glyphID;
    tileX = 99;
    printed = (u8 *)textObj->printedGlyphs;

    for (i = 0; i < textObj->maxAllocatedTileRows; i++) {
        for (j = 0; j < 16; j++) {
            if ((glyphByte0 == printed[0]) && (glyphByte1 == printed[1])) {
                textObj->printedGlyphCounts[j + (i * 16)]++;
                return textObj->baseTileNum + (j * 2) + ((i * 16) * 2);
            }
            if ((printed[0] == 0) && (printed[1] == 0)) {
                tileX = j;
                tileY = i;
            }
            printed += 2;
        }
    }

    // Out of Memory
    if (tileX == 99) {
        return -2;
    }

    tileID = textObj->baseTileNum + (tileX * 2) + ((tileY * 16) * 2);
    address = (void *)(VRAMBase + (textObj->tilesetID * 0x4000) + (tileID * 0x20));
    bmp_font_get_glyph(font, string, &texture, NULL);
    if (texture == NULL) {
        return -1;
    }
    bmp_font_bg_write_glyph(texture, address);

    i = tileX + (tileY * 16);
    printed = (u8 *)&textObj->printedGlyphs[i];
    printed[0] = glyphByte0;
    printed[1] = glyphByte1;
    textObj->printedGlyphCounts[i] = 1;

    return tileID;
}


// Parse an ASCII hex digit.
u8 bmp_font_bg_parse_hex_digit(char c) {
    if ((c >= '0') && (c <= '9')) {
        return c - '0';
    }

    if ((c >= 'a') && (c <= 'f')) {
        return c - 'a' + 10;
    }

    if ((c >= 'A') && (c <= 'F')) {
        return c - 'A' + 10;
    }

    return 0;
}


// Print to BG Map.
void bmp_font_bg_print_text(struct BitmapFontBG *textObj, u16 *bgMap, u32 mapWidth, const char *string, u32 palette) {
    u16 tileNum;
    u32 mapX;

    sBgFontStyle = 0;
    mapX = 0;

    while (string[0] != '\0') {
        if (string[0] == '\n') {
            bgMap += (mapWidth * 2);
            string += 1;
            mapX = 0;
            continue;
        }

        if (bmp_font_is_control_code(string, '.')) {
            palette = bmp_font_bg_parse_hex_digit(string[1]);
            string += 2;
            continue;
        }

        if (bmp_font_is_control_code(string, ':')) {
            sBgFontStyle = bmp_font_bg_parse_hex_digit(string[1]);
            string += 2;
            continue;
        }

        tileNum = bmp_font_bg_print_glyph(textObj, string);

        if (tileNum < 0x400) {
            u16 mapTile;

            mapTile = (palette << 12) | (tileNum & 0x3FF);
            bgMap[mapX] = mapTile;
            bgMap[mapWidth + mapX] = mapTile + 1;
        }

        string = utf8_get_next_char_ptr(string);
        mapX++;
    }
}


// Delete printed BitmapFontBG.
void bmp_font_bg_delete_printed_data(struct BitmapFontBG *textObj, const char *string) {
    struct BitmapFontGlyph glyph;
    const char *nextString;
    u8 glyphByte0, glyphByte1;
    u8 *printed;
    u32 fontStyle, glyphSet;
    u32 i;
    const struct BitmapFontData* font;

    fontStyle = 0;

    while (string[0] != '\0') {
        if (string[0] == '\n') {
            string += 1;
            continue;
        }

        if (bmp_font_is_control_code(string, '.')) {
            string += 2;
            continue;
        }

        if (bmp_font_is_control_code(string, ':')) {
            fontStyle = bmp_font_bg_parse_hex_digit(string[1]);
            string += 2;
            continue;
        }

        font = &textObj->fonts[fontStyle];
        if (bmp_font_get_glyph_info(font, string, &glyph, &nextString)) {
            glyphSet = glyph.glyphSet - font->glyphRanges;
            glyphByte0 = (fontStyle << 4) | glyphSet;
            glyphByte1 = glyph.glyphID;
            printed = (u8 *)textObj->printedGlyphs;

            for (i = 0; i < (textObj->maxAllocatedTileRows * 16); i++) {
                if ((printed[0] == glyphByte0) && (printed[1] == glyphByte1)) {
                    if (--textObj->printedGlyphCounts[i] == 0) {
                        printed[0] = printed[1] = 0;
                    }
                    break;
                }
                printed += 2;
            }

            string = nextString;
        } else {
            string = utf8_get_next_char_ptr(string);
        }
    }
}


// Init. BitmapFontBGPrinter task.
struct BitmapFontBGPrinter *bmp_font_bg_init_printer(struct BitmapFontBGPrinter *inputs) {
    struct BitmapFontBGPrinter *info;

    info = mem_heap_alloc(sizeof(struct BitmapFontBGPrinter));
    dma3_set(inputs, info, sizeof(struct BitmapFontBGPrinter), 0x20, 0x100);
    info->fontStyle = 0;
    info->currentMapX = 0;

    return info;
}


// Update BitmapFontBGPrinter task.
u32 bmp_font_bg_update_printer(struct BitmapFontBGPrinter *info) {
    const char *string;
    u16 *bgMap;
    u32 mapX, mapWidth, palette, tileNum;
    u32 processLimit;

    processLimit = info->processLimit;
    sBgFontStyle = info->fontStyle;
    bgMap = info->bgMap;
    mapX = info->currentMapX;
    mapWidth = info->bgMapWidth;
    string = info->string;
    palette = info->palette;

    while (string[0] != '\0') {
        if (string[0] == '\n') {
            bgMap += (mapWidth * 2);
            string += 1;
            mapX = 0;
            continue;
        }

        if (bmp_font_is_control_code(string, '.')) {
            palette = bmp_font_bg_parse_hex_digit(string[1]);
            string += 2;
            continue;
        }

        if (bmp_font_is_control_code(string, ':')) {
            sBgFontStyle = bmp_font_bg_parse_hex_digit(string[1]);
            string += 2;
            continue;
        }

        tileNum = bmp_font_bg_print_glyph(info->textObj, string);

        if (tileNum < 0x400) {
            u16 mapTile;

            mapTile = (palette << 12) | (tileNum & 0x3FF);
            bgMap[mapX] = mapTile;
            bgMap[mapWidth + mapX] = mapTile + 1;
        }

        string = utf8_get_next_char_ptr(string);
        mapX++;
        processLimit--;

        if (processLimit == 0) {
            info->fontStyle = sBgFontStyle;
            info->bgMap = bgMap;
            info->currentMapX = mapX;
            info->string = string;
            info->palette = palette;
            return FALSE;
        }
    }

    return TRUE;
}


// Start new BitmapFontBGPrinter task.
s32 start_bmp_font_bg_printer_task(u16 memID, struct BitmapFontBG *textObj, u16 *bgMapDest, u32 bgMapWidth, const char *string, u32 palette, u32 processLimit) {
    struct BitmapFontBGPrinter inputs;

    inputs.textObj = textObj;
    inputs.bgMap = bgMapDest;
    inputs.bgMapWidth = bgMapWidth;
    inputs.string = string;
    inputs.palette = palette;
    inputs.processLimit = processLimit;

    return start_new_task(memID, &D_08936b64, &inputs, NULL, 0);
}


// Count the total printable characters in a string (including characters not supported by the font).
u32 bmp_font_bg_get_total_printable_chars(const char *string) {
    u32 count = 0;

    while (string[0] != '\0') {
        if (string[0] == '\n') {
            string += 1;
            continue;
        }

        if (bmp_font_is_control_code(string, '.')) {
            string += 2;
            continue;
        }

        if (bmp_font_is_control_code(string, ':')) {
            string += 2;
            continue;
        }

        string = utf8_get_next_char_ptr(string);
        count++;
    }

    return count;
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */


// Render SceneObject
void import_scene_object(struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject object, s16 *spritePool) {
    u16 sprite;
    s32 poolID;

    poolID = -1;

    switch (*object.type) {
        // Sprite (Immediate XY)
        case SCENE_OBJECT_TYPE_IMM_XY: {
            struct SceneSprite *data;

            data = object.sprite;
            poolID = data->poolID;
            sprite = sprite_create_w_attr(spriteHandler, data->anim,
                data->unk8, data->x, data->y, data->z,
                data->unk10, data->unk11, data->unk12, data->unk14);
            break;
        }

        // Sprite (Vector XY)
        case SCENE_OBJECT_TYPE_VEC_XY: {
            struct SceneSpriteVecXY *data;

            data = object.spriteVecXY;
            poolID = data->poolID;
            sprite = sprite_create_w_attr(spriteHandler, data->anim,
                data->unk8, data->pos->x, data->pos->y, data->z,
                data->unk12, data->unk13, data->unk14, data->unk18);
            break;
        }

        // Static Text Object
        case SCENE_OBJECT_TYPE_TEXT: {
            struct PrintedTextAnim *textAnim;
            struct SceneText *data;
            const char *string;
            u32 fontStyle;
            u32 palette;

            if (bitmapFontOBJ == NULL) {
                break;
            }

            data = object.text;
            poolID = data->poolID;

            if ((s32)data->textTable < 0) {
                string = *((char **)((u32)data->textTable & 0x7fffffff));
            } else {
                string = data->textTable[sSceneTextCurrentStringId];
            }
            fontStyle = data->fontStyle;
            palette = data->palette;

            switch (data->alignment) {
                case 0:
                    textAnim = bmp_font_obj_print_unaligned(bitmapFontOBJ, string, fontStyle, palette);
                    break;
                case 1:
                    textAnim = bmp_font_obj_print_c(bitmapFontOBJ, string, fontStyle, palette);
                    break;
                case 2:
                    textAnim = bmp_font_obj_print_l(bitmapFontOBJ, string, fontStyle, palette);
                    break;
                case 3:
                    textAnim = bmp_font_obj_print_r(bitmapFontOBJ, string, fontStyle, palette);
                    break;
            }

            if (data->wobbly == TRUE) {
                struct WobblyPrintedTextAnim *wobblyAnim;

                wobblyAnim = bmp_font_obj_print_wobbly(bitmapFontOBJ, textAnim, 4);
                mem_heap_dealloc(textAnim);
                textAnim = (struct PrintedTextAnim *)wobblyAnim;
            }

            sprite = sprite_create_w_attr(spriteHandler, textAnim->frames, 0, data->x, data->y, data->z, 1, 0, 0, data->unk14);

            if (!data->display) {
                sprite_set_visible(spriteHandler, sprite, FALSE);
            }
            break;
        }
    }

    if ((spritePool != NULL) && (poolID >= 0)) {
        spritePool[poolID] = sprite;
    }
}


// Render All SceneObjects
u32 import_all_scene_objects(struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject *objects, s16 *spritePool) {
    u32 count = 0;

    if (objects->type != NULL) {
        const union SceneObject *obj = objects;

        while (obj->type != NULL) {
            import_scene_object(spriteHandler, bitmapFontOBJ, *obj++, spritePool);
            count++;
        }
    }

    return count;
}


// Set sSceneTextCurrentStringId
void set_scene_object_current_text_id(u32 textID) {
    sSceneTextCurrentStringId = textID;
}


// Init. SceneObjectRenderer task.
struct SceneObjectRenderer *init_scene_object_importer(struct SceneObjectRenderer *inputs) {
    struct SceneObjectRenderer *info;

    info = mem_heap_alloc(sizeof(struct SceneObjectRenderer));
    info->spriteHandler = inputs->spriteHandler;
    info->bitmapFontOBJ = inputs->bitmapFontOBJ;
    info->objects = inputs->objects;
    info->spritePool = inputs->spritePool;

    return info;
}


// Update SceneObjectRenderer task.
u32 update_scene_object_importer(struct SceneObjectRenderer *info) {
    const union SceneObject *objects;
    u32 type;

    objects = info->objects;

    while (objects->type != NULL) {
        import_scene_object(info->spriteHandler, info->bitmapFontOBJ, *objects, info->spritePool);
        type = *(objects++)->type;
        info->objects = objects;

        if (type == 2) {
            if (objects->type == NULL) {
                return TRUE;
            } else {
                return FALSE;
            }
        }
    }

    return TRUE;
}


// Start new SceneObjectRenderer task.
s32 start_new_scene_object_importer(u16 memID, struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject *objects, s16 *spritePool) {
    struct SceneObjectRenderer inputs;

    inputs.spriteHandler = spriteHandler;
    inputs.bitmapFontOBJ = bitmapFontOBJ;
    inputs.objects = objects;
    inputs.spritePool = spritePool;

    return start_new_task(memID, &D_08936b74, &inputs, NULL, 0);
}


// Delete All SceneObjects
void delete_all_scene_objects(struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject *objects, s16 *spritePool) {
    if ((spritePool == NULL) || (objects->type == NULL)) {
        return;
    }

    while (objects->type != NULL) {
        switch (*objects->type) {
            case SCENE_OBJECT_TYPE_IMM_XY: {
                struct SceneSprite *data;

                data = objects->sprite;
                if (data->poolID >= 0) {
                    sprite_delete(spriteHandler, spritePool[data->poolID]);
                    spritePool[data->poolID] = -1;
                }
                break;
            }

            case SCENE_OBJECT_TYPE_VEC_XY: {
                struct SceneSpriteVecXY *data;

                data = objects->spriteVecXY;
                if (data->poolID >= 0) {
                    sprite_delete(spriteHandler, spritePool[data->poolID]);
                    spritePool[data->poolID] = -1;
                }
                break;
            }

            case SCENE_OBJECT_TYPE_TEXT: {
                struct SceneText *data;
                s16 sprite;

                if (bitmapFontOBJ == NULL) {
                    break;
                }

                data = objects->text;
                if (data->poolID >= 0) {
                    sprite = spritePool[data->poolID];
                    bmp_font_obj_delete_printed_anim(bitmapFontOBJ, (struct Animation *)sprite_get_data(spriteHandler, sprite, 7));
                    sprite_delete(spriteHandler, sprite);
                    spritePool[data->poolID] = -1;
                }
                break;
            }
        }
        objects++;
    }
}


// Show/Hide All SceneObjects
void display_all_scene_objects(struct SpriteHandler *spriteHandler, struct BitmapFontOBJ *bitmapFontOBJ, const union SceneObject *objects, s16 *spritePool, u32 show) {
    if ((spritePool == NULL) || (objects->type == NULL)) {
        return;
    }

    while (objects->type != NULL) {
        switch (*objects->type) {
            case SCENE_OBJECT_TYPE_IMM_XY: {
                struct SceneSprite *data;

                data = objects->sprite;
                if (data->poolID >= 0) {
                    sprite_set_visible(spriteHandler, spritePool[data->poolID], show);
                }
                break;
            }

            case SCENE_OBJECT_TYPE_VEC_XY: {
                struct SceneSpriteVecXY *data;

                data = objects->spriteVecXY;
                if (data->poolID >= 0) {
                    sprite_set_visible(spriteHandler, spritePool[data->poolID], show);
                }
                break;
            }

            case SCENE_OBJECT_TYPE_TEXT: {
                struct SceneText *data;

                if (bitmapFontOBJ == NULL) {
                    break;
                }

                data = objects->text;
                if (data->poolID >= 0) {
                    sprite_set_visible(spriteHandler, spritePool[data->poolID], show);
                }
                break;
            }
        }
        objects++;
    }
}
