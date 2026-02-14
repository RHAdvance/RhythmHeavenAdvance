#include "global.h"
#include "text_printer.h"

#include "src/memory_heap.h"
#include "src/lib_0804ca80.h"
#include "data/text_printer_data.h"

asm(".include \"include/gba.inc\"");//Temporary


  //  //  //  TEXT PRINTER  //  //  //


typedef void (PrintGlyphToVRAMFunc)(void *args);
extern PrintGlyphToVRAMFunc text_print_glyph_to_vram_rom;

#define GLYPH_BUFFER_SIZE 0x80
static struct FormattedGlyph {
    const char *formatSrc;
    const char *charSrc;
    s16 id;
    u16 xOffset;
    u8 width;
    u8 lineColors;
    s8 shadowColors;
    u8 font;
    u8 spacing;
} *sGlyphBuffer; // Formatted Glyph Buffer

static void (*sModifyPrinterSettings)(s32, s32); // Formatting Escape Char. '\1' Function
static s32 text_print_glyph_to_vram_code[54]; // ARM Function

static s32 sCurrentLineWidth;   // Printer Line Width
static s8 sPrinterAlignment;    // Printer Alignment
static s8 sPrinterColors;       // Printer Colors
static s8 sPrinterFont;         // Printer Font
static s8 sPrinterIndentWidth;  // Printer Indent Width
static s8 sPrinterShadowColors; // Printer Shadow Colors



// Init. Static Variables
void text_printer_init(void) {
    dma3_set(text_print_glyph_to_vram_rom, text_print_glyph_to_vram_code, sizeof(text_print_glyph_to_vram_code), 0x20, 0x100);
    sGlyphBuffer = mem_heap_alloc(GLYPH_BUFFER_SIZE * sizeof(struct FormattedGlyph));
    sModifyPrinterSettings = NULL;
}


// Get Spacing Width
s32 text_font_get_spacing(s32 font) {
    return D_089380ac[font].glyphSpacing;
}


// Get Glyph Width
s32 text_font_get_glyph_width(s32 font, s32 glyphID) {
    if (glyphID < 0) return 0;

    return D_089380ac[font].glyphWidths[glyphID];
}


// Get Glyph Width
s32 text_font_get_next_glyph_width(s32 font, const char **stream) {
    s32 glyphID;

    if (**stream == '\0') {
        return 0;
    }

    glyphID = text_printer_get_glyph_id(stream);
    if (glyphID < 0) {
        return 0;
    }

    return D_089380ac[font].glyphWidths[glyphID];
}


// Get Width of a String
s32 text_font_calculate_string_width(s32 font, const char *string) {
    s32 totalWidth, spacing;
    s32 glyphID;

    totalWidth = 0;
    spacing = D_089380ac[font].glyphSpacing;

    while (*string != '\0') {
        glyphID = text_printer_get_glyph_id(&string);
        if (glyphID >= 0) {
            totalWidth += text_font_get_glyph_width(font, glyphID) + spacing;
        }
    }

    if (totalWidth != 0) {
        totalWidth -= spacing;
    }

    return totalWidth;
}


// Print Glyph to VRAM
void text_printer_print_glyph(s32 tileOfsX, s32 tileOfsY, s32 font, s32 glyphID, s32 lineColors) {
    PrintGlyphToVRAMFunc *printGlyphToVRAM = (PrintGlyphToVRAMFunc *)(&text_print_glyph_to_vram_code);
    u32 args[4];

    if (glyphID < 0) return;

    args[0] = VRAMBase + ((tileOfsX >> 3) * 32) + (tileOfsY * 32 * 32);
    args[1] = (u32)(D_089380ac[font].glyphData + (D_089380ac[font].glyphDataSize * glyphID));
    args[2] = ((tileOfsX & 7) << 2) + lineColors;
    args[3] = font;
    printGlyphToVRAM(args);
}


// Print String to VRAM (return width in pixels)
s32 text_printer_print_unformatted_line(s32 tileBaseX, s32 tileBaseY, s32 font, const char *string, s32 maxWidth, s32 lineColors) {
    const char *ellipsis;
    s32 ellipsisID, glyphID;
    s32 ellipsisWidth, glyphWidth;
    s32 spacing, totalWidth;

    totalWidth = 0;
    spacing = D_089380ac[font].glyphSpacing;
    ellipsis = D_089380d0;
    ellipsisID = text_printer_get_glyph_id(&ellipsis);
    ellipsisWidth = text_font_get_glyph_width(font, ellipsisID);

    while (*string != '\0') {
        glyphID = text_printer_get_glyph_id(&string);
        if (glyphID < 0) continue;

        glyphWidth = text_font_get_glyph_width(font, glyphID);
        if (*string != '\0') {
            if ((totalWidth + glyphWidth + spacing + ellipsisWidth) > maxWidth) {
                string = ellipsis;
                glyphID = ellipsisID;
                glyphWidth = ellipsisWidth;
            }
        } else {
            if ((totalWidth + glyphWidth) > maxWidth) {
                string = ellipsis;
                glyphID = ellipsisID;
                glyphWidth = ellipsisWidth;
            }
        }

        text_printer_print_glyph(tileBaseX + totalWidth, tileBaseY, font, glyphID, lineColors);
        totalWidth += glyphWidth + spacing;
    }

    if (totalWidth != 0) {
        totalWidth -= spacing;
    }

    return totalWidth;
}


// Check if Character is Any Sort of Open Bracket
s32 text_glyph_is_open_bracket(const char *c) {
    const char *brackets;
    char c1, c2;

    c1 = c[0];
    c2 = c[1];

    if ((char)(c1 - '\x20') < '\x5f') {
        // Half-Width Open Brackets
        for (brackets = D_089380e4; brackets[0] != '\0'; brackets += 1) {
            if (c1 == brackets[0]) {
                return TRUE;
            }
        }
    } else {
        // Full-Width Open Brackets
        for (brackets = D_089380d4; brackets[0] != '\0'; brackets += 2) {
            if ((c1 == brackets[0]) && (c2 == brackets[1])) {
                return TRUE;
            }
        }
    }

    return FALSE;
}


// Check if Character is Any Sort of Ending Punctuation
s32 text_glyph_is_end_punctuation(const char *c) {
    const char *punctuation;
    char c1, c2;

    c1 = c[0];
    c2 = c[1];

    if ((char)(c1 - '\x20') < '\x5f') {
        // Half-Width Ending Punctuation
        for (punctuation = D_08938138; punctuation[0] != '\0'; punctuation += 1) {
            if (c1 == punctuation[0]) {
                return TRUE;
            }
        }
    } else {
        // Full-Width Ending Punctuation
        for (punctuation = D_089380e8; punctuation[0] != '\0'; punctuation += 2) {
            if ((c1 == punctuation[0]) && (c2 == punctuation[1])) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

extern u8 haveSeenDisclaimer;

// since no cart reseller with 2 functioning braincells will fall for this, i took the liberty
// of replacing the messages with stuff that won't traumatize people!!!
char* badBoyMessages[6] = {
    "oh noes anti piracy",
    "3800 yen",
    "hello world",
    "rhythm rhythm rhythm",
    "i love tap!",
    "super mario"
};

// Print Formatted Line to VRAM (return width in pixels)
s32 text_printer_print_formatted_line(s32 tileBaseX, s32 tileBaseY, s32 font, const char **charStream, s32 maxWidth, s32 lineColors, s32 indentWidth, s32 shadowColors) {
    struct FormattedGlyph *fGlyphData;
    const char *stream, *tempStream;
    s32 spacing, glyphWidth, totalWidth, maxWidthWithShadow;
    s32 totalGlyphs;
    s32 maxWidthExceeded;
    s32 glyphID;
    u32 i;

    if(!haveSeenDisclaimer){
        i = agb_random(ARRAY_COUNT(badBoyMessages));
        stream = badBoyMessages[i];
    } else {
        stream = *charStream;
    }
    
    spacing = D_089380ac[font].glyphSpacing;
    fGlyphData = sGlyphBuffer;
    totalGlyphs = 0;
    maxWidthExceeded = FALSE;

    fGlyphData->formatSrc = stream;
    totalWidth = clamp_int32(indentWidth, 0, maxWidth);

    while (*stream != '\0') {
        if (*stream < ' ') {
            s32 newLine = FALSE;

            switch (*stream) {
                case '\n': // Insert Newline
                    stream += 1;
                    newLine = TRUE;
                    break;

                case '\1': // Set Text Printer Data
                    if (sModifyPrinterSettings != NULL) {
                        sModifyPrinterSettings(stream[1], totalWidth);
                    }
                    stream += 2;
                    break;

                case '\2': // Set Colors?
                    lineColors = stream[1] - '0';
                    stream += 2;
                    break;

                case '\3': // Set Font
                    font = stream[1] - '0';
                    spacing = D_089380ac[font].glyphSpacing;
                    stream += 2;
                    break;

                case '\4': // Insert Padding
                    stream += 1;
                    totalWidth = 0;
                    while (*stream != '.') {
                        totalWidth = (totalWidth * 10) + *stream - '0';
                        stream += 1;
                    }
                    totalWidth = clamp_int32(totalWidth, 0, maxWidth);
                    stream += 1;
                    break;

                case '\5': // Set Text Shadow
                    shadowColors = stream[1] - '0';
                    if (shadowColors > 3) {
                        shadowColors = TEXT_PRINTER_SHADOW_DISABLED;
                    }
                    stream += 2;
                    break;
            }
            if (!newLine) continue;
            else break;
        }

        tempStream = stream;
        glyphID = text_printer_get_glyph_id(&stream);
        if (glyphID < 0) {
            continue;
        }

        glyphWidth = text_font_get_glyph_width(font, glyphID);
        maxWidthWithShadow = maxWidth + ((shadowColors >= 0) ? -1 : 0);
        if ((totalWidth + glyphWidth) > maxWidthWithShadow) {
            stream = tempStream;
            maxWidthExceeded = TRUE;
            break;
        }

        fGlyphData->id = glyphID;
        fGlyphData->xOffset = totalWidth;
        fGlyphData->width = glyphWidth;
        fGlyphData->lineColors = lineColors;
        fGlyphData->shadowColors = shadowColors;
        fGlyphData->charSrc = tempStream;
        fGlyphData->font = font;
        fGlyphData->spacing = spacing;
        fGlyphData++;
        totalGlyphs++;

        fGlyphData->formatSrc = stream;
        totalWidth += spacing + glyphWidth;
    }

    if (totalWidth != 0) {
        totalWidth -= spacing;
    }

    if (maxWidthExceeded && (totalGlyphs != 0)) {
        if (text_glyph_is_open_bracket(sGlyphBuffer[totalGlyphs - 1].charSrc)) {
            fGlyphData--;
            totalGlyphs--;
            totalWidth -= (fGlyphData->width + fGlyphData->spacing);
            stream = fGlyphData->formatSrc;
        } else if (text_glyph_is_end_punctuation(stream)) {
            do {
                fGlyphData--;
                totalGlyphs--;
                totalWidth -= (fGlyphData->width + fGlyphData->spacing);
            } while ((totalGlyphs != 0) && text_glyph_is_end_punctuation(fGlyphData->charSrc));
            stream = fGlyphData->formatSrc;
        }

        if (totalGlyphs != 0) {
            struct FormattedGlyph *lastGlyph;
            s32 xStart, w1, w2;

            lastGlyph = &sGlyphBuffer[totalGlyphs] - 1;
            xStart = sGlyphBuffer[0].xOffset;
            w1 = clamp_int32((maxWidth - lastGlyph->width - xStart), 0, maxWidth);
            w2 = clamp_int32((lastGlyph->xOffset - xStart), 0, maxWidth);

            for (i = 0; i < totalGlyphs; i++) {
                sGlyphBuffer[i].xOffset = xStart + ((sGlyphBuffer[i].xOffset - xStart) * w1 / w2);
            }

            totalWidth = w1 + lastGlyph->width;
        }
    }

    for (fGlyphData = sGlyphBuffer, i = 0; i < totalGlyphs; i++, fGlyphData++) {
        text_printer_print_glyph((tileBaseX + fGlyphData->xOffset), tileBaseY, fGlyphData->font, fGlyphData->id, fGlyphData->lineColors);

        if (fGlyphData->shadowColors >= 0) {
            text_printer_print_glyph((tileBaseX + fGlyphData->xOffset + 1), tileBaseY, fGlyphData->font, fGlyphData->id, fGlyphData->shadowColors);
        }
    }

    *charStream = stream;
    return totalWidth;
}


// Create Animation (https://decomp.me/scratch/CQpoA)
#include "asm/code_080092cc/asm_08009de4.s"


// Get Animation (Type 1)
struct Animation *text_printer_get_unformatted_line_anim(u32 memID, s32 tileBaseX, s32 tileBaseY, s32 font, const char *string, u32 anchor, s32 lineColors, s32 maxWidth) {
    return func_08009de4(memID, tileBaseX, tileBaseY, font, &string, anchor, lineColors, maxWidth, TRUE, 0, -1);
}


// Get Animation (Type 2)
struct Animation *text_printer_get_formatted_line_anim(u32 memID, s32 tileBaseX, s32 tileBaseY, s32 font, const char **string, u32 anchor, s32 lineColors, s32 maxWidth, s32 indentWidth, s32 shadowColors) {
    return func_08009de4(memID, tileBaseX, tileBaseY, font, string, anchor, lineColors, maxWidth, FALSE, indentWidth, shadowColors);
}


// Get sCurrentLineWidth
s32 text_printer_get_current_line_width(void) {
    return sCurrentLineWidth;
}


// Delete Text Animation
void text_printer_delete_anim(struct Animation *anim) {
    if (anim == NULL) return;

    mem_heap_dealloc(anim->cel);
    mem_heap_dealloc(anim);
}


// Set sModifyPrinterSettings
void text_printer_set_format_func(void *func) {
    sModifyPrinterSettings = func;
}


// Fill Allocated Space With Given Pixel
void text_printer_clear_tiles(u32 tileBaseX, u32 tileBaseY, u32 allocatedTiles, u32 unused, u32 color) {
    void *tilesetBase;
    u32 tileOffset;
    u32 tile;

    tile = color & 0xf;
    tile |= (tile << 4);
    tile |= (tile << 8);
    tile |= (tile << 16);

    tileOffset = (tileBaseX + (tileBaseY * 0x20)) * 0x20;
    tilesetBase = (void *)(VRAMBase + tileOffset);
    dma3_fill(tile, tilesetBase, allocatedTiles * 0x20, 0x20, 0x200);
    tilesetBase = (void *)(VRAMBase + tileOffset + 0x400);
    dma3_fill(tile, tilesetBase, allocatedTiles * 0x20, 0x20, 0x200);
}


// Fill Allocated Space With Given Pixel
void text_printer_fill_vram_tiles(u32 tileBaseX, u32 tileBaseY, u32 allocatedTiles, u32 unused, u32 color) {
    text_printer_clear_tiles(tileBaseX, tileBaseY + 64, allocatedTiles, unused, color);
}


// Get Glyph ID 
s32 text_printer_get_glyph_id(const char **string) {
    const char *s;
    char c1;
    char c2;
    s8 r0;
    s32 id;

    s = *string;
    c1 = s[0];
    (*string)++;

    r0 = (c1 - 0x20);
    if ((u8)r0 < 0x5f) {
        c2 = D_08938194[((u8)r0 * 2) + 1];
        c1 = D_08938194[(u8)r0 * 2];
    } else {
        c2 = s[1];
        (*string)++;
    }

    r0 = (c1 + 0x7f);
    if ((u8)r0 < 0x1f) {
        id = (u16)D_08938140[c1 - 0x81];
    } else {
        r0 = (c1 + 0x20);
        if ((u8)r0 < 0xb) {
            id = (u16)D_0893817e[c1 - 0xe0];
        } else {
            id = -1;
        }
    }

    if (id != -1) {
        if (c2 < 0x7f) {
            id -= 0x40 - c2;
        } else {
            r0 = (c2 + 0x80);
            if ((u8)r0 < 0x7d) {
                id -= 0x41 - c2;
            } else {
                id = -1;
            }
        }
    }

    return id;
}


// Get Value for unk4
u32 func_0800a1ac(u32 maxWidth) {
    if (maxWidth > 128) return 0;
    if (maxWidth > 80) return 1;
    if (maxWidth > 64) return 2;
    if (maxWidth > 32) return 3;
    return 4;
}


// Get Value for unk28
s32 func_0800a1d4(u32 totalLines, u32 id) {
    u32 x;

    x = D_08938258[id] * totalLines;

    if (id == 2) {
        x += (totalLines * 2) / 3;
    }

    return ((x + 31) / 32) * 2;
}


// Create New
struct TextPrinter *text_printer_create_new(u16 memID, u32 totalLines, u32 maxWidth, u32 arg3) {
    struct TextPrinter *textPrinter;
    u32 i;

    textPrinter = mem_heap_alloc_id(memID, sizeof(struct TextPrinter));
    textPrinter->memID = memID;
    textPrinter->mode = TEXT_PRINTER_MODE_STANDARD;
    textPrinter->totalLines = totalLines;
    textPrinter->lineSprites = mem_heap_alloc_id(memID, totalLines * sizeof(s16));
    textPrinter->lineWidths = mem_heap_alloc_id(memID, totalLines * sizeof(s16));
    textPrinter->lineAlignments = mem_heap_alloc_id(memID, totalLines * sizeof(u8));
    textPrinter->lineStrings = mem_heap_alloc_id(memID, totalLines * sizeof(u32));
    textPrinter->lineShadowSprites = mem_heap_alloc_id(memID, totalLines * sizeof(s16));

    for (i = 0; i < totalLines; i++) {
        textPrinter->lineSprites[i] = -1;
        textPrinter->lineStrings[i] = NULL;
        textPrinter->lineShadowSprites[i] = -1;
    }

    textPrinter->palette = 0;
    textPrinter->lineColors = 0;
    textPrinter->maxWidth = maxWidth;
    textPrinter->unk4 = func_0800a1ac(maxWidth);
    textPrinter->unk28 = func_0800a1d4(totalLines, textPrinter->unk4);
    textPrinter->unk26 = arg3 - textPrinter->unk28;
    textPrinter->alignment = 0;
    textPrinter->indentWidth = 0;
    textPrinter->currentLine = 0;
    textPrinter->x = 0;
    textPrinter->y = 8;
    textPrinter->z = 0;
    textPrinter->currentlyPrinting = FALSE;
    textPrinter->string = NULL;
    textPrinter->font = TEXT_PRINTER_FONT_SMALL;
    textPrinter->lineSpacing = 16;
    textPrinter->centerText = FALSE;
    textPrinter->finished = FALSE;
    textPrinter->onFinish = NULL;
    textPrinter->onClear = NULL;
    textPrinter->ySrc = NULL;
    textPrinter->xSrc = NULL;
    textPrinter->unk54 = 0;
    textPrinter->shadowColors = TEXT_PRINTER_SHADOW_DISABLED;
    textPrinter->renderToScreen = TRUE;

    return textPrinter;
}


// Format Function for Escape Character '\1'
void text_printer_format_func(u32 arg, s32 xOffset) {
    switch (arg) {
        case '0':
        case '1':
        case '2':
        case '3':
            sPrinterColors = arg - '0';
            break;
        case '4':
        case '5':
        case '6':
        case '7':
            sPrinterShadowColors = arg - '4';
            break;
        case '8':
            sPrinterShadowColors = TEXT_PRINTER_SHADOW_DISABLED;
            break;
        case 'L':
            sPrinterAlignment = TEXT_ALIGNMENT_LEFT;
            break;
        case 'R':
            sPrinterAlignment = TEXT_ALIGNMENT_RIGHT;
            break;
        case 'C':
            sPrinterAlignment = TEXT_ALIGNMENT_CENTER;
            break;
        case 's':
            sPrinterFont = TEXT_PRINTER_FONT_SMALL;
            break;
        case 'm':
            sPrinterFont = TEXT_PRINTER_FONT_MEDIUM;
            break;
        case 'l':
            sPrinterFont = TEXT_PRINTER_FONT_LARGE;
            break;
        case '[':
            sPrinterIndentWidth = xOffset;
            break;
        case ']':
            sPrinterIndentWidth = 0;
            break;
    }
}


//
const char *text_printer_process_next_line(struct TextPrinter *textPrinter, u32 currentLine, const char *string) {
    struct Animation *anim;
    u32 id;
    u32 allocatedTiles;
    u32 linesPerGridRow;
    u32 gridX, gridY;
    u32 tileX, tileY;
    u32 tileOffset;
    void *tilesetBase;

    s32 currentDisplayLine;
    u16 x, y;
    u32 z;
    u16 sprite;

    sPrinterAlignment = textPrinter->alignment;
    sPrinterColors = textPrinter->lineColors;
    sPrinterFont = textPrinter->font;
    sPrinterIndentWidth = textPrinter->indentWidth;
    sPrinterShadowColors = textPrinter->shadowColors;
    text_printer_set_format_func(text_printer_format_func);

    id = textPrinter->unk4;
    allocatedTiles = D_08938258[id];
    linesPerGridRow = D_0893825d[id];
    gridX = currentLine % linesPerGridRow;
    gridY = currentLine / linesPerGridRow;
    tileX = gridX * allocatedTiles;
    tileY = textPrinter->unk26 + (gridY * 2);

    tileOffset = ((tileY * 0x20) + tileX) * 0x20;
    tilesetBase = OBJ_TILESET_BASE(tileOffset);
    dma3_fill(0, tilesetBase, allocatedTiles * 0x20, 0x20, 0x200);
    tilesetBase = OBJ_TILESET_BASE(tileOffset + 0x400);
    dma3_fill(0, tilesetBase, allocatedTiles * 0x20, 0x20, 0x200);

    currentDisplayLine = currentLine - textPrinter->unk54;
    if (currentDisplayLine < 0) {
        currentDisplayLine += textPrinter->totalLines;
    }
    x = textPrinter->x;
    y = (textPrinter->lineSpacing * currentDisplayLine) + textPrinter->y;
    z = textPrinter->z;

    anim = text_printer_get_formatted_line_anim(textPrinter->memID, tileX, tileY, textPrinter->font, &string, 2, textPrinter->lineColors, textPrinter->maxWidth, textPrinter->indentWidth, textPrinter->shadowColors);
    sprite = sprite_create(gSpriteHandler, anim, 0, x, y, z, 0, 0, 0x8000);
    sprite_set_base_palette(gSpriteHandler, sprite, textPrinter->palette);
    sprite_set_origin_x_y(gSpriteHandler, sprite, textPrinter->xSrc, textPrinter->ySrc);
    textPrinter->lineSprites[currentLine] = sprite;
    textPrinter->lineWidths[currentLine] = text_printer_get_current_line_width();
    textPrinter->lineAlignments[currentLine] = sPrinterAlignment;
    sprite_set_x_y_z(gSpriteHandler, textPrinter->lineShadowSprites[currentLine], x, y, z + 1);
    sprite_set_origin_x_y(gSpriteHandler, textPrinter->lineShadowSprites[currentLine], textPrinter->xSrc, textPrinter->ySrc);

    textPrinter->alignment = sPrinterAlignment;
    textPrinter->lineColors = sPrinterColors;
    textPrinter->font = sPrinterFont;
    textPrinter->indentWidth = sPrinterIndentWidth;
    textPrinter->shadowColors = sPrinterShadowColors;

    return string;
}


// Align Sprites
void text_printer_align_sprites(struct TextPrinter *textPrinter) {
    u16 xCentre, xAligned;
    u32 greatestWidth;
    u32 i;

    if (textPrinter->centerText) {
        greatestWidth = 0;
        for (i = 0; i < textPrinter->totalLines; i++) {
            if (textPrinter->lineSprites[i] >= 0) {
                if (greatestWidth < textPrinter->lineWidths[i]) {
                    greatestWidth = textPrinter->lineWidths[i];
                }
            }
        }
        xCentre = ((textPrinter->maxWidth - greatestWidth) / 2) + textPrinter->x;
    } else {
        greatestWidth = textPrinter->maxWidth;
        xCentre = textPrinter->x;
    }

    for (i = 0; i < textPrinter->totalLines; i++) {
        if (textPrinter->lineSprites[i] >= 0) {
            switch (textPrinter->lineAlignments[i]) {
                case TEXT_ALIGNMENT_LEFT:
                    xAligned = xCentre;
                    break;
                case TEXT_ALIGNMENT_RIGHT:
                    xAligned = (xCentre + greatestWidth) - textPrinter->lineWidths[i];
                    break;
                case TEXT_ALIGNMENT_CENTER:
                    xAligned = xCentre + ((greatestWidth - textPrinter->lineWidths[i]) / 2);
                    break;
            }
            sprite_set_x(gSpriteHandler, textPrinter->lineSprites[i], xAligned);
        }
    }
}


// Show/Hide Text
void text_printer_show_text_now(struct TextPrinter *textPrinter, u32 show) {
    u32 i;

    for (i = 0; i < textPrinter->totalLines; i++) {
        if (textPrinter->lineSprites[i] >= 0) {
            sprite_set_visible(gSpriteHandler, textPrinter->lineSprites[i], show);
        }
        if (textPrinter->lineShadowSprites[i] >= 0) {
            sprite_set_visible(gSpriteHandler, textPrinter->lineShadowSprites[i], show);
        }
    }
}


// Show/Hide Text On Render
void text_printer_show_text(struct TextPrinter *textPrinter, u32 show) {
    if (textPrinter == NULL) return;

    textPrinter->renderToScreen = show;
    if (!textPrinter->currentlyPrinting) {
        text_printer_show_text_now(textPrinter, show);
    }
}


// Update (Single-String)
void text_printer_update_standard(struct TextPrinter *textPrinter) {
    if (textPrinter->currentlyPrinting == FALSE) {
        return;
    }

    if (textPrinter->string == NULL) {
        textPrinter->currentlyPrinting = FALSE;
        return;
    }

    if (textPrinter->canceled) {
        textPrinter->canceled = FALSE;
        return;
    }

    textPrinter->string = text_printer_process_next_line(textPrinter, textPrinter->currentLine, textPrinter->string);
    textPrinter->currentLine++;

    if ((*textPrinter->string == '\0') || (textPrinter->currentLine >= textPrinter->totalLines)) {
        text_printer_align_sprites(textPrinter);
        text_printer_show_text_now(textPrinter, textPrinter->renderToScreen);
        textPrinter->currentlyPrinting = FALSE;
        textPrinter->finished = TRUE;

        if (textPrinter->onFinish != NULL) {
            textPrinter->onFinish(textPrinter->onFinishArg);
        }
    }
}


// Update (Multi-String)
void text_printer_update_split_table(struct TextPrinter *textPrinter) {
    u32 totalLineStrings;
    u32 firstLineString;
    u32 i;

    totalLineStrings = 0;
    for (i = 0; i < textPrinter->totalLines; i++) {
        if (textPrinter->lineStrings[i] != NULL) {
            if (totalLineStrings == 0) {
                firstLineString = i;
            }
            totalLineStrings++;
        }
    }

    if (totalLineStrings == 0) return;

    text_printer_process_next_line(textPrinter, firstLineString, textPrinter->lineStrings[firstLineString]);

    if (textPrinter->lineStrings[firstLineString] != NULL) {
        mem_heap_dealloc(textPrinter->lineStrings[firstLineString]);
    }

    textPrinter->lineStrings[firstLineString] = NULL;

    if (totalLineStrings < 2) {
        text_printer_align_sprites(textPrinter);
        text_printer_show_text_now(textPrinter, textPrinter->renderToScreen);
        textPrinter->currentlyPrinting = FALSE;
        textPrinter->finished = TRUE;
        if (textPrinter->onFinish != NULL) {
            textPrinter->onFinish(textPrinter->onFinishArg);
        }
    }
}


// Update
void text_printer_update(struct TextPrinter *textPrinter) {
    if (textPrinter == NULL) return;

    switch (textPrinter->mode) {
        case TEXT_PRINTER_MODE_STANDARD:
            text_printer_update_standard(textPrinter);
            break;
        case TEXT_PRINTER_MODE_STATIC_TABLE:
            text_printer_update_split_table(textPrinter);
            break;
    }
}


// Remove Text
void text_printer_clear(struct TextPrinter *textPrinter) {
    u32 finished;
    s16 sprite;
    u32 i;

    if (textPrinter == NULL) return;

    finished = textPrinter->finished;

    for (i = 0; i < textPrinter->totalLines; i++) {
        sprite = textPrinter->lineSprites[i];
        if (sprite >= 0) {
            text_printer_delete_anim((void *)sprite_get_data(gSpriteHandler, sprite, 7));
            sprite_delete(gSpriteHandler, sprite);
            textPrinter->lineSprites[i] = -1;
        }

        if (textPrinter->lineStrings[i] != NULL) {
            mem_heap_dealloc(textPrinter->lineStrings[i]);
        }
        textPrinter->lineStrings[i] = NULL;

        if (textPrinter->lineShadowSprites[i] >= 0) {
            sprite_delete(gSpriteHandler, textPrinter->lineShadowSprites[i]);
            textPrinter->lineShadowSprites[i] = -1;
        }
    }

    textPrinter->currentLine = 0;
    textPrinter->currentlyPrinting = FALSE;
    textPrinter->finished = FALSE;
    textPrinter->string = NULL;
    textPrinter->unk54 = 0;

    if (finished) {
        if (textPrinter->onClear != NULL) {
            textPrinter->onClear(textPrinter->onClearArg);
        }
    }
}


// Delete Text Printer
void text_printer_delete(struct TextPrinter *textPrinter) {
    if (textPrinter == NULL) return;

    text_printer_clear(textPrinter);
    mem_heap_dealloc(textPrinter->lineSprites);
    mem_heap_dealloc(textPrinter->lineWidths);
    mem_heap_dealloc(textPrinter->lineAlignments);
    mem_heap_dealloc(textPrinter->lineShadowSprites);
    mem_heap_dealloc(textPrinter);
}


// Set Text
void text_printer_set_string(struct TextPrinter *textPrinter, const char *text) {
    if (textPrinter == NULL) return;

    if (textPrinter->mode == TEXT_PRINTER_MODE_STANDARD) {
        text_printer_clear(textPrinter);

        if (text != NULL) {
            textPrinter->canceled = TRUE;
            textPrinter->currentlyPrinting = TRUE;
            textPrinter->string = text;
        }
    }
}


// Get Text
const char *text_printer_get_text(struct TextPrinter *textPrinter) {
    if (textPrinter == NULL) return NULL;

    if (textPrinter->mode == TEXT_PRINTER_MODE_STANDARD) {
        if ((textPrinter->string != NULL) && (*textPrinter->string != '\0')) {
            return textPrinter->string;
        }
    }

    return NULL;
}


// Reinsert Text ("Continue"?)
void text_printer_resume(struct TextPrinter *textPrinter) {
    if (textPrinter == NULL) return;

    if (textPrinter->mode == TEXT_PRINTER_MODE_STANDARD) {
        if ((textPrinter->string != NULL) && (*textPrinter->string != '\0')) {
            text_printer_set_string(textPrinter, textPrinter->string);
        }
    }
}


// Set Text (Table Mode)
void func_0800aac0(struct TextPrinter *textPrinter, s32 lineIndex, const char *string, s16 shadowSprite) {
    struct TextPrinter *printer;
    s16 lineSprite;
    u32 line;

    line = lineIndex;
    printer = textPrinter;

    if (printer == NULL) {
        return;
    }

    if ((printer->mode == TEXT_PRINTER_MODE_STATIC_TABLE) && (line < printer->totalLines)) {
        lineSprite = printer->lineSprites[line];
        if (lineSprite >= 0) {
            text_printer_delete_anim((void *)sprite_get_data(gSpriteHandler, lineSprite, 7));
            sprite_delete(gSpriteHandler, lineSprite);
            printer->lineSprites[line] = -1;
        }

        if (printer->lineShadowSprites[line] >= 0) {
            sprite_delete(gSpriteHandler, printer->lineShadowSprites[line]);
            printer->lineShadowSprites[line] = -1;
        }

        printer->lineShadowSprites[line] = shadowSprite;
        sprite_set_visible(gSpriteHandler, printer->lineShadowSprites[line], FALSE);

        if (printer->lineStrings[line] != NULL) {
            mem_heap_dealloc(printer->lineStrings[line]);
        }

        if (string != NULL) {
            printer->lineStrings[line] = mem_heap_alloc_id(printer->memID, strlen(string) + 1);
            strcpy(printer->lineStrings[line], string);
        } else {
            printer->lineStrings[line] = NULL;
        }

        if (string != NULL) {
            printer->currentlyPrinting = TRUE;
        }
    }
}


// Clear Text (Table Mode)
void func_0800abb0(struct TextPrinter *textPrinter, s32 line) {
    struct TextPrinter *printer = textPrinter;
    s16 sprite;
    u32 i;

    if (printer == NULL) {
        return;
    }

    if (printer->mode == TEXT_PRINTER_MODE_STATIC_TABLE) {
        line %= printer->totalLines;
        if (line < 0) {
            line += printer->totalLines;
        }
        printer->unk54 = line;

        for (i = 0; i < printer->totalLines; i++) {
            sprite = printer->lineSprites[line];
            if (sprite >= 0) {
                sprite_set_y(gSpriteHandler, sprite, (printer->lineSpacing * i) + printer->y);
            }

            sprite = printer->lineShadowSprites[line];
            if (sprite >= 0) {
                sprite_set_y(gSpriteHandler, sprite, (printer->lineSpacing * i) + printer->y);
            }

            line++;
            if (line >= printer->totalLines) {
                line = 0;
            }
        }
    }
}


// Get Active Printing Status
s32 text_printer_is_busy(struct TextPrinter *textPrinter) {
    if (textPrinter == NULL) return FALSE;

    return textPrinter->currentlyPrinting;
}


// Set X & Y
void text_printer_set_x_y(struct TextPrinter *textPrinter, s16 x, s16 y) {
    if (textPrinter == NULL) return;

    textPrinter->x = x;
    textPrinter->y = y;
}


// Set X
void text_printer_set_x(struct TextPrinter *textPrinter, s16 x) {
    if (textPrinter == NULL) return;

    textPrinter->x = x;
}


// Set Y
void text_printer_set_y(struct TextPrinter *textPrinter, s16 y) {
    if (textPrinter == NULL) return;

    textPrinter->y = y;
}


// Set Z (Sprite Depth)
void text_printer_set_layer(struct TextPrinter *textPrinter, u16 z) {
    if (textPrinter == NULL) return;

    textPrinter->z = z;
}


// Set Palette
void text_printer_set_palette(struct TextPrinter *textPrinter, u32 palette) {
    if (textPrinter == NULL) return;

    textPrinter->palette = palette;
}


// Set Colors
void text_printer_set_colors(struct TextPrinter *textPrinter, u32 colors) {
    if (textPrinter == NULL) return;

    textPrinter->lineColors = colors;
}


// Set Alignment
void text_printer_set_alignment(struct TextPrinter *textPrinter, u32 alignment) {
    if (textPrinter == NULL) return;

    textPrinter->alignment = alignment;
}


// Set Center Text
void text_printer_center_by_content(struct TextPrinter *textPrinter, u32 center) {
    if (textPrinter == NULL) return;

    textPrinter->centerText = center;
}


// Get unk26
s32 func_0800ace8(struct TextPrinter *textPrinter) {
    if (textPrinter == NULL) return 0;

    return textPrinter->unk26;
}


// Store Centred X & Y to Vector
void text_printer_get_x_y(struct TextPrinter *textPrinter, s16 *vx, s16 *vy) {
    if (textPrinter == NULL) return;

    *vx = (textPrinter->maxWidth / 2) + textPrinter->x;
    *vy = (textPrinter->currentLine * textPrinter->lineSpacing) + textPrinter->y;
}


// Set On-Print Function and Parameter
void text_printer_run_func_on_finish(struct TextPrinter *textPrinter, void *onPrint, s32 param) {
    if (textPrinter == NULL) return;

    textPrinter->onFinish = onPrint;
    textPrinter->onFinishArg = param;
}


// Set On-Clear Function and Parameter
void text_printer_run_func_on_clear(struct TextPrinter *textPrinter, void *onClear, s32 param) {
    if (textPrinter == NULL) return;

    textPrinter->onClear = onClear;
    textPrinter->onClearArg = param;
}


// Export Text Printer Data
void text_printer_export_data(struct TextPrinter *textPrinter, struct TextPrinterData *data) {
    if (textPrinter == NULL) return;

    data->string = textPrinter->string;
    data->font = textPrinter->font;
    data->colors = textPrinter->lineColors;
    data->alignment = textPrinter->alignment;
    data->indentWidth = textPrinter->indentWidth;
}


// Import Text Printer Data
void text_printer_import_data(struct TextPrinter *textPrinter, struct TextPrinterData *data) {
    if (textPrinter == NULL) return;

    textPrinter->string = data->string;
    textPrinter->font = data->font;
    textPrinter->lineColors = data->colors;
    textPrinter->alignment = data->alignment;
    textPrinter->indentWidth = data->indentWidth;
    text_printer_resume(textPrinter);
}


// Set X & Y Sources
void text_printer_set_x_y_controller(struct TextPrinter *textPrinter, s16 *xSrc, s16 *ySrc) {
    if (textPrinter == NULL) return;

    textPrinter->xSrc = xSrc;
    textPrinter->ySrc = ySrc;
}


// Set X Source
void text_printer_set_x_controller(struct TextPrinter *textPrinter, s16 *xSrc) {
    if (textPrinter == NULL) return;

    textPrinter->xSrc = xSrc;
}


// Set Y Source
void text_printer_set_y_controller(struct TextPrinter *textPrinter, s16 *ySrc) {
    if (textPrinter == NULL) return;

    textPrinter->ySrc = ySrc;
}


// Set Print Mode
void text_printer_set_mode(struct TextPrinter *textPrinter, u32 mode) {
    if (textPrinter == NULL) return;

    text_printer_clear(textPrinter);
    textPrinter->mode = mode;
}


// Get Line Sprite
s16 text_printer_get_line_sprite(struct TextPrinter *textPrinter, s32 line) {
    if (textPrinter == NULL) return -1;

    if ((line >= 0) && (line < textPrinter->totalLines)) {
        return textPrinter->lineSprites[line];
    }

    return -1;
}


// Set Line Spacing
void text_printer_set_line_spacing(struct TextPrinter *textPrinter, u32 lineSpacing) {
    if (textPrinter == NULL) return;

    textPrinter->lineSpacing = lineSpacing;
}


// Set Shadow Colors
void text_printer_set_shadow_colors(struct TextPrinter *textPrinter, s32 shadowColors) {
    if (textPrinter == NULL) return;

    textPrinter->shadowColors = shadowColors;
}



/* LISTBOX PRINTER */



// Get... something.
s32 listbox_get_y(struct Listbox *listbox) {
    return listbox->y + ((listbox->selLine + listbox->selMinLine) * listbox->lineSpacing);
}


// Set Palette for... some line.
void func_0800ae3c(struct Listbox *listbox, u32 palette) {
    s32 line, maxLines;
    s16 sprite;

    line = listbox->scrollIndex + listbox->selMinLine + listbox->selLine;
    maxLines = listbox->maxLines;

    line %= maxLines;
    if (line < 0) {
        line += maxLines;
    }

    sprite = text_printer_get_line_sprite(listbox->printer, line);
    sprite_set_base_palette(gSpriteHandler, sprite, palette);
}


// Listbox On-Finish Function
void func_0800ae88(struct Listbox *listbox) {
    func_0800ae3c(listbox, listbox->unk12);

    if (listbox->unk3C) {
        if (listbox->onFinish != NULL) {
            listbox->onFinish(listbox->onFinishArg);
        }
        listbox->unk3C = FALSE;
    }
}


// Create New Listbox
struct Listbox *create_new_listbox(
        u16 memID, u32 maxLines, u32 maxWidth, u32 arg3, u32 selectedPalette, u32 unselectedPalette,
        u32 colors, s32 x, s32 y, u32 z, u32 lineSpacing, u32 selectionItem,
        s32 totalItems, struct Animation *selectionAnim, u32 selMinLine, u32 selMaxLine,
        u32 selectionLine, const char *getString(), s16 getSprite()
    ) {

    struct Listbox *listbox;
    struct TextPrinter *printer;
    const char *string;
    s32 sprite;
    s32 line;
    u32 i;

    listbox = mem_heap_alloc_id(memID, sizeof(struct Listbox));
    listbox->memID = memID;
    listbox->printer = text_printer_create_new(memID, maxLines, maxWidth, arg3);
    text_printer_set_mode(listbox->printer, TEXT_PRINTER_MODE_STATIC_TABLE);
    text_printer_set_x_y_controller(listbox->printer, &listbox->textX, &listbox->textY);
    text_printer_set_x_y(listbox->printer, x, y);
    text_printer_set_layer(listbox->printer, z);
    text_printer_set_palette(listbox->printer, unselectedPalette);
    text_printer_set_colors(listbox->printer, colors);
    text_printer_set_line_spacing(listbox->printer, lineSpacing);
    text_printer_run_func_on_finish(listbox->printer, func_0800ae88, (s32)listbox);
    listbox->maxLines = maxLines;
    listbox->unk12 = selectedPalette;
    listbox->palette = unselectedPalette;
    listbox->colors = colors;
    listbox->x = x;
    listbox->y = y;
    listbox->z = z;
    listbox->lineSpacing = lineSpacing;
    listbox->scrollIndex = 0;
    listbox->listY = 0;
    listbox->listX = 0;
    listbox->velY = 0;
    listbox->textX = 0;
    listbox->textY = 0;
    listbox->selItem = selectionItem;
    listbox->totalItems = totalItems;
    listbox->selMinLine = selMinLine;
    listbox->selMaxLine = selMaxLine;
    listbox->selLine = selectionLine;
    listbox->getString = getString;
    listbox->getSprite = getSprite;

    if (selectionAnim != NULL) {
        listbox->selSprite = sprite_create(gSpriteHandler, selectionAnim, 0, x, listbox_get_y(listbox), z, 1, 0, 0);
    } else {
        listbox->selSprite = -1;
    }

    sprite_set_origin_x_y(gSpriteHandler, listbox->selSprite, &listbox->textX, &listbox->textY);
    listbox->unk3C = TRUE;
    listbox->onScroll = NULL;
    listbox->onFinish = NULL;

    line = selectionItem - selectionLine - selMinLine;

    for (i = 0; i < maxLines; i++) {
        if ((line >= 0) && (line < totalItems)) {
            printer = listbox->printer;
            string = getString(line);
            sprite = (getSprite != NULL) ? getSprite(line) : -1;

            func_0800aac0(printer, i, string, sprite);
        }
        line++;
    }

    return listbox;
}


// Update Listbox
void update_listbox(struct Listbox *listbox) {
    struct Listbox *list = listbox;
    s32 velY, temp;

    if (listbox == NULL) {
        return;
    }

    // Investigate this: (https://decomp.me/scratch/GfMM8)
    temp = ((u32)listbox->velY) >> 31;
    velY = listbox->velY;
    if (velY < 0) {
        velY = -velY;
    }

    listbox->velY = (velY * 5) >> 3;

    if (temp != 0) {
        listbox->velY = -listbox->velY;
    }

    list->textX = list->listX;
    list->textY = list->listY + list->velY;
    list->itemsX = list->textX;
    list->itemsY = ((list->selItem - list->selMinLine - list->selLine) * list->lineSpacing) + list->listY + list->velY;
    text_printer_update(list->printer);
}


// Delete Listbox
void delete_listbox(struct Listbox *listbox) {
    if (listbox == NULL) {
        return;
    }

    text_printer_delete(listbox->printer);

    if (listbox->selSprite >= 0) {
        sprite_delete(gSpriteHandler, listbox->selSprite);
    }

    mem_heap_dealloc(listbox);
}


// Get Text Printer
struct TextPrinter *listbox_get_text_printer(struct Listbox *listbox) {
    if (listbox == NULL) {
        return NULL;
    }

    return listbox->printer;
}


// Get Selection Item
s32 listbox_get_sel_item(struct Listbox *listbox) {
    if (listbox == NULL) {
        return 0;
    }

    return listbox->selItem;
}


// Get Selection Line
s32 listbox_get_sel_line(struct Listbox *listbox) {
    if (listbox == NULL) {
        return 0;
    }

    return listbox->selLine;
}


// Scroll Up
void listbox_scroll_up(struct Listbox *listbox) {
    struct TextPrinter *printer;
    const char *string;
    s32 sprite;
    s32 next, line;

    if ((listbox == NULL) || (listbox->selItem <= 0)) {
        return;
    }

    func_0800ae3c(listbox, listbox->palette);

    if (listbox->selLine <= 0) {
        next = listbox->selItem - listbox->selLine - listbox->selMinLine;
        line = listbox->scrollIndex % listbox->maxLines;

        if (line < 0) {
            line += listbox->maxLines;
        }

        printer = listbox->printer;
        string = listbox->getString(next);

        if (listbox->getSprite != NULL) {
            sprite = listbox->getSprite(next);
        } else {
            sprite = -1;
        }

        func_0800aac0(printer, line, string, sprite);
        listbox->scrollIndex--;
        func_0800abb0(listbox->printer, listbox->scrollIndex);
        listbox->velY = 16;
    } else {
        listbox->selLine--;
        sprite_set_y(gSpriteHandler, listbox->selSprite, listbox_get_y(listbox));
    }

    listbox->selItem--;
    func_0800ae3c(listbox, listbox->unk12);

    if (listbox->onScroll != NULL) {
        listbox->onScroll(listbox->onScrollArg, listbox->selItem, listbox->selItem + 1);
    }
}


// Scroll Down
void listbox_scroll_down(struct Listbox *listbox) {
    struct TextPrinter *printer;
    const char *string;
    s32 sprite;
    s32 next, line, max;

    if ((listbox == NULL) || (listbox->selItem >= (listbox->totalItems - 1))) {
        return;
    }

    func_0800ae3c(listbox, listbox->palette);

    if (listbox->selLine < (listbox->selMaxLine - 1)) {
        listbox->selLine++;
        sprite_set_y(gSpriteHandler, listbox->selSprite, listbox_get_y(listbox));
    } else {
        next = listbox->selItem - listbox->selLine - listbox->selMinLine + listbox->maxLines - 1;
        line = (listbox->scrollIndex - 1) % listbox->maxLines;

        if (line < 0) {
            line += listbox->maxLines;
        }

        printer = listbox->printer;
        string = listbox->getString(next);

        if (listbox->getSprite != NULL) {
            sprite = listbox->getSprite(next);
        } else {
            sprite = -1;
        }

        func_0800aac0(printer, line, string, sprite);
        listbox->scrollIndex++;
        func_0800abb0(listbox->printer, listbox->scrollIndex);
        listbox->velY = -16;
    }

    listbox->selItem++;
    func_0800ae3c(listbox, listbox->unk12);

    if (listbox->onScroll != NULL) {
        listbox->onScroll(listbox->onScrollArg, listbox->selItem, listbox->selItem - 1);
    }
}


// Set On-Scroll Function and Parameter
void listbox_run_func_on_scroll(struct Listbox *listbox, void onScroll(), s32 onScrollArg) {
    if (listbox == NULL) {
        return;
    }

    listbox->onScroll = onScroll;
    listbox->onScrollArg = onScrollArg;
}


// Set On-Finish Function and Parameter
void listbox_run_func_on_finish(struct Listbox *listbox, void onFinish(), s32 onFinishArg) {
    if (listbox == NULL) {
        return;
    }

    listbox->onFinish = onFinish;
    listbox->onFinishArg = onFinishArg;
}


// Get Sprite for... some line.
s16 func_0800b32c(struct Listbox *listbox) {
    struct Listbox *listbox1 = listbox;
    s32 temp;
    
    if (listbox == NULL) {
        return; // !UB: no return value
    }

    temp = listbox->scrollIndex + listbox->selMinLine + listbox->selLine;
    temp %= listbox->maxLines;
    if (temp < 0) {
        temp += listbox->maxLines;
    }
    return text_printer_get_line_sprite(listbox1->printer, temp);
}


// Check if Listbox is Busy
s32 listbox_is_busy(struct Listbox *listbox) {
    if (listbox != NULL) {
        return (listbox != NULL) && (text_printer_is_busy(listbox->printer) != FALSE);
    } else {
        return FALSE;
    }
}


// Offset Position
void listbox_offset_x_y(struct Listbox *listbox, s16 x, s16 y) {
    if (listbox == NULL) {
        return;
    }

    listbox->listX = x;
    listbox->listY = y;
    listbox->textX = x;
    listbox->textY = y + listbox->velY;
    listbox->itemsX = listbox->listX;
    listbox->itemsY = ((listbox->selItem - listbox->selMinLine - listbox->selLine) * listbox->lineSpacing) + listbox->listY + listbox->velY;
}


// Show Selection Sprite
void listbox_show_sel_sprite(struct Listbox *listbox) {
    if (listbox == NULL) {
        return;
    }

    sprite_set_visible(gSpriteHandler, listbox->selSprite, TRUE);
}


// Hide Selection Sprite
void listbox_hide_sel_sprite(struct Listbox *listbox) {
    if (listbox == NULL) {
        return;
    }

    sprite_set_visible(gSpriteHandler, listbox->selSprite, FALSE);
}


// Link Sprite to Listbox
void listbox_link_sprite_x_y_to_line(struct Listbox *listbox, s16 sprite, s32 line) {
    if (listbox == NULL) {
        return;
    }

    sprite_set_origin_x_y(gSpriteHandler, sprite, &listbox->itemsX, &listbox->itemsY);
    sprite_set_x_y(gSpriteHandler, sprite, listbox->x, line * listbox->lineSpacing + listbox->y);
}


// ?
void func_0800b454(struct Listbox *listbox, s32 arg1) {
    struct TextPrinter *printer;
    const char *string;
    s32 sprite;
    s32 line, maxLines;

    if (listbox == NULL) {
        return;
    }

    if ((arg1 >= 0) && (arg1 < listbox->totalItems)) {
        line = arg1 - listbox->selItem + listbox->selMinLine + listbox->selLine;
        if (line < 0) {
            return;
        }

        maxLines = listbox->maxLines;
        if (line >= maxLines) {
            return;
        }

        line += listbox->scrollIndex;
        line %= maxLines;
        if (line < 0) {
            line += maxLines;
        }

        printer = listbox->printer;
        string = listbox->getString(arg1);
        sprite = (listbox->getSprite != NULL) ? listbox->getSprite(arg1) : -1;

        func_0800aac0(printer, line, string, sprite);
    }
}


// Set Selection Sprite
void listbox_set_sel_sprite(struct Listbox *listbox, struct Animation *selectionAnim) {
    if (listbox == NULL) {
        return;
    }

    if (listbox->selSprite >= 0) {
        sprite_delete(gSpriteHandler, listbox->selSprite);
    }

    listbox->selSprite = -1;

    if (selectionAnim != NULL) {
        listbox->selSprite = sprite_create(gSpriteHandler, selectionAnim, 0, listbox->x, listbox_get_y(listbox), listbox->z, 1, 0, 0);
        sprite_set_origin_x_y(gSpriteHandler, listbox->selSprite, &listbox->textX, &listbox->textY);
    }
}


// Get Selection Sprite
s16 listbox_get_sel_sprite(struct Listbox *listbox) {
    if (listbox == NULL) {
        return -1;
    }

    return listbox->selSprite;
}
