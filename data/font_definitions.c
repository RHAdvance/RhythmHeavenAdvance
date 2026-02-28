#include "global.h"
#include "graphics.h"
#include "src/bitmap_font.h"
#include "font_definitions.h"


/* FONT DEFINITIONS */


// [D_089de30c] Display Font (Large) - Punctuation/Symbols
u8 bitmap_font_warioware_outline_large_symbol_widths[] = {
     0,  9,  8,  5,  5, 10,  6,  6, 12,  9,  9,  9, 11, 10, 10, 11,
    14, 14, 14, 11, 14, 14, 11, 16, 11, 11, 11, 16, 16, 11, 16, 15,
    16, 11,  9, 14, 14,  4,  4,  7,  7, 10, 10,  6,  5,  5,  5, 11,
    11, 13, 13,  8,  9,  7,  7,  7,  6, 14, 10, 13, 13, 12, 13, 13,
    13, 12, 11, 12, 12, 11, 12, 12, 12, 14,  8,  9, 10, 12, 16, 11,
    11, 12, 14, 15, 14, 13, 15, 11, 16, 16, 12, 13, 13, 13
};

// [D_089de36a] Display Font (Large) - Arabic Numerals (Wide)
u8 bitmap_font_warioware_outline_large_numeral_wide_widths[] = {
    14, 12, 13, 13, 13, 13, 13, 13, 13, 13
};

// [D_089de374] Display Font (Large) - Arabic Numerals (Narrow)
u8 bitmap_font_warioware_outline_large_numeral_narrow_widths[] = {
     7,  6,  7,  7,  7,  7,  7,  7,  7,  7
};

// [D_089de37e] Display Font (Large) - Latin Alphabet (Uppercase)
u8 bitmap_font_warioware_outline_large_latin_upper_widths[] = {
    14, 14, 14, 13, 14, 13, 14, 14, 12, 14, 13, 13, 16, 14, 14, 14,
    14, 13, 13, 14, 13, 14, 15, 15, 14, 14
};

// [D_089de398] Display Font (Large) - Latin Alphabet (Lowercase)
u8 bitmap_font_warioware_outline_large_latin_lower_widths[] = {
     8,  8,  8,  8,  8,  8,  8,  8,  4,  7,  8,  5,  8,  8,  8,  8,
     8,  8,  8,  8,  8,  8,  8,  8,  8,  8
};

// [D_089de3b2] Display Font (Large) - Hiragana
u8 bitmap_font_warioware_outline_large_hiragana_widths[] = {
    14,  8, 14,  8, 14,  8, 14,  8, 14,  8, 14,  8, 14,  8, 14,  8, 
    14,  8, 12,  6, 12,  5, 12,  5, 12,  6, 14,  8, 14,  8, 14,  8,  
    14,  8, 14,  8, 16,  8, 13,  8, 13,  8, 13,  8, 13,  8, 16, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16, 16,
    16, 16, 14, 16, 13, 16, 14, 16, 16, 15, 15, 16, 15, 15, 16, 16,
    16, 15, 16, 16, 14, 14,  0,  0,  0,  0,  0,  0,  0,  0
};

// [D_089de410] Display Font (Large) - Katakana
u8 bitmap_font_warioware_outline_large_katakana_widths[] = {
    14, 16, 13, 16, 13, 16, 14, 16, 13, 16, 16, 16, 16, 16, 15, 16,
    16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16,
    16, 16, 13, 15, 16, 16, 16, 15, 15, 16, 16, 16, 16, 13, 15, 16,
    16, 16, 16, 16, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 15, 16,
    15, 15, 14, 16, 14, 16, 13, 15, 16, 15, 16, 15, 15, 14, 15, 16,
    16, 15, 16, 16, 14, 14,  0,  0,  0,  0,  0,  0,  0,  0
};


// [D_089de46e] Display Font (Small) - Punctuation/Symbols
u8 bitmap_font_warioware_outline_small_symbol_widths[] = {
     0,  7,  6,  5,  5,  9,  6,  6, 11,  7,  9,  9, 11, 10, 10, 11,
    14, 11, 11, 11, 10, 10, 11, 14, 11, 11, 11, 11, 11, 11, 11, 15,
    12, 11,  9, 11, 11,  4,  4,  7,  7,  7,  6,  6,  5,  5,  5,  8,
     8, 10, 10,  8,  9,  7,  7,  7,  6, 12,  6, 11, 11, 12, 11, 11,
    11, 12, 11, 12, 12, 11, 12, 12, 11, 14,  8,  9, 10, 12, 11, 12,
    11, 12, 11, 15, 12, 10, 12, 11, 13, 13, 12, 13, 13, 13
};

// [D_089de4cc] Display Font (Small) - Arabic Numerals
u8 bitmap_font_warioware_outline_small_numeral_widths[] = {
    10,  6, 10, 10, 10, 10, 10, 10, 10, 10
};

// [D_089de4d6] Display Font (Small) - Latin Alphabet (Uppercase)
u8 bitmap_font_warioware_outline_small_latin_upper_widths[] = {
    10,  9, 10, 10,  9,  9, 10, 10,  6,  9, 10,  9, 11, 10, 11,  9,
    12, 10,  9, 10, 10, 11, 11, 11, 10, 10
};

// [D_089de4f0] Display Font (Small) - Latin Alphabet (Lowercase)
u8 bitmap_font_warioware_outline_small_latin_lower_widths[] = {
     8,  8,  8,  8,  8,  7,  8,  8,  4,  6,  8,  5,  8,  8,  8,  8,
     8,  7,  8,  7,  8,  8,  8,  8,  8,  8
};

// [D_089de50a] Display Font (Small) - Hiragana
u8 bitmap_font_warioware_outline_small_hiragana_widths[] = {
    10,  8, 10,  8, 10,  8, 10,  8, 10,  8,  9,  8,  9,  8,  9,  8,
     9,  8,  8,  6,  6,  5,  6,  5,  8,  6, 10,  8, 11,  8, 11,  8,
    11,  8, 11,  8, 12,  9, 10,  8, 10,  8, 10,  8, 10,  8, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 12, 12,
    12, 12, 10, 12, 10, 12,  9, 11, 11,  9, 12, 12, 11, 10, 12, 12,
    11, 11, 12, 12,  9,  9,  0,  0,  0,  0,  0,  0,  0,  0
};

// [D_089de568] Display Font (Small) - Katakana
u8 bitmap_font_warioware_outline_small_katakana_widths[] = {
     9, 12,  8, 11,  9, 12, 10, 12,  9, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12,  9, 12, 12, 12, 12,  9, 10, 12, 13, 12, 12,  9, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12,  9, 12,  9, 12,  8, 12, 12, 11, 12, 11, 12,  9, 12, 12,
    11, 12, 12, 12,  9,  9,  0,  0,  0,  0,  0,  0,  0,  0
};


// [D_089de5c8] WarioWare Outline Font
struct BitmapFontData bitmap_font_warioware_outline[] = {
    /* STYLE 1 - LARGE (WIDE NUMERALS) */ {
        /* DIMENSIONS */
            /* Whitespace W. */ 6,
            /* Glyph Width   */ 16,
            /* Glyph Height  */ 16,
            /* Descension H. */ 3,
            /* Spacing Width */ 0,

        /* GLYPHS: PUNCTUATION/SYMBOLS */
            /* Textures */ warioware_outline_large_symbol_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_symbol_widths,
        /* GLYPHS: ARABIC NUMERALS */
            /* Textures */ warioware_outline_large_numeral_wide_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_numeral_wide_widths,
        /* GLYPHS: LATIN ALPHABET (UPPERCASE) */
            /* Textures */ warioware_outline_large_latin_upper_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_latin_upper_widths,
        /* GLYPHS: LATIN ALPHABET (LOWERCASE) */
            /* Textures */ warioware_outline_large_latin_lower_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_latin_lower_widths,
        /* GLYPHS: HIRAGANA */
            /* Textures */ warioware_outline_large_hiragana_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_hiragana_widths,
        /* GLYPHS: KATAKANA */
            /* Textures */ warioware_outline_large_katakana_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_katakana_widths,
    },

    /* STYLE 2 - SMALL */ {
        /* DIMENSIONS */
            /* Whitespace W. */ 5,
            /* Glyph Width   */ 16,
            /* Glyph Height  */ 16,
            /* Descension H. */ 3,
            /* Spacing Width */ -1,

        /* GLYPHS: PUNCTUATION/SYMBOLS */
            /* Textures */ warioware_outline_small_symbol_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_small_symbol_widths,
        /* GLYPHS: ARABIC NUMERALS */
            /* Textures */ warioware_outline_small_numeral_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_small_numeral_widths,
        /* GLYPHS: LATIN ALPHABET (UPPERCASE) */
            /* Textures */ warioware_outline_small_latin_upper_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_small_latin_upper_widths,
        /* GLYPHS: LATIN ALPHABET (LOWERCASE) */
            /* Textures */ warioware_outline_small_latin_lower_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_small_latin_lower_widths,
        /* GLYPHS: HIRAGANA */
            /* Textures */ warioware_outline_small_hiragana_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_small_hiragana_widths,
        /* GLYPHS: KATAKANA */
            /* Textures */ warioware_outline_small_katakana_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_small_katakana_widths,
    },

    /* STYLE 3 - LARGE (NARROW NUMERALS) */ {
        /* DIMENSIONS */
            /* Whitespace W. */ 6,
            /* Glyph Width   */ 16,
            /* Glyph Height  */ 16,
            /* Descension H. */ 3,
            /* Spacing Width */ 0,

        /* GLYPHS: PUNCTUATION/SYMBOLS */
            /* Textures */ warioware_outline_large_symbol_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_symbol_widths,
        /* GLYPHS: ARABIC NUMERALS */
            /* Textures */ warioware_outline_large_numeral_narrow_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_numeral_narrow_widths,
        /* GLYPHS: LATIN ALPHABET (UPPERCASE) */
            /* Textures */ warioware_outline_large_latin_upper_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_latin_upper_widths,
        /* GLYPHS: LATIN ALPHABET (LOWERCASE) */
            /* Textures */ warioware_outline_large_latin_lower_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_latin_lower_widths,
        /* GLYPHS: HIRAGANA */
            /* Textures */ warioware_outline_large_hiragana_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_hiragana_widths,
        /* GLYPHS: KATAKANA */
            /* Textures */ warioware_outline_large_katakana_glyphs_raw_4bpp,
            /* Widths   */ bitmap_font_warioware_outline_large_katakana_widths,
    }
};

// [D_089de670] WarioWare Body Text Font
struct BitmapFontData bitmap_font_warioware_body[] = {
    /* STYLE 1 - TEXT */ {
        /* DIMENSIONS */
            /* Whitespace W. */ 8,
            /* Glyph Width   */ 8,
            /* Glyph Height  */ 16,
            /* Descension H. */ 0,
            /* Spacing Width */ 0,

        /* GLYPHS: PUNCTUATION/SYMBOLS */
            /* Textures */ warioware_body_text_symbol_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: ARABIC NUMERALS */
            /* Textures */ warioware_body_text_numeral_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: LATIN ALPHABET (UPPERCASE) */
            /* Textures */ warioware_body_text_latin_upper_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: LATIN ALPHABET (LOWERCASE) */
            /* Textures */ warioware_body_text_latin_lower_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: HIRAGANA */
            /* Textures */ warioware_body_text_hiragana_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: KATAKANA */
            /* Textures */ warioware_body_text_katakana_glyphs_raw_4bpp,
            /* Widths   */ NULL,
    },

    /* STYLE 2 - ICON */ {
        /* DIMENSIONS */
            /* Whitespace W. */ 8,
            /* Glyph Width   */ 8,
            /* Glyph Height  */ 16,
            /* Descension H. */ 0,
            /* Spacing Width */ 0,

        /* GLYPHS: PUNCTUATION/SYMBOLS */
            /* Textures */ warioware_body_text_symbol_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: ARABIC NUMERALS */
            /* Textures */ warioware_body_icon_numeral_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: LATIN ALPHABET (UPPERCASE) */
            /* Textures */ warioware_body_icon_latin_upper_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: LATIN ALPHABET (LOWERCASE) */
            /* Textures */ warioware_body_text_latin_lower_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: HIRAGANA */
            /* Textures */ warioware_body_text_hiragana_glyphs_raw_4bpp,
            /* Widths   */ NULL,
        /* GLYPHS: KATAKANA */
            /* Textures */ warioware_body_text_katakana_glyphs_raw_4bpp,
            /* Widths   */ NULL,
    }
};
