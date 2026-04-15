#pragma once


/* TEXT PRINTER DATA */

#define END_OF_RANGE { NULL, NULL, 0x0000, 0x0000 }

struct FontGlyphRange {
    u8 *glyphData;
    u8 *glyphWidths;
    u16 utf8Start;
    u16 utf8End;
};

struct TextPrinterFont {
    struct FontGlyphRange *glyphRanges;
    u8 glyphDataSize;
    u8 glyphSpacing;
    u8 unkA;
    u8 unkB;
};

extern struct TextPrinterFont D_089380ac[];

extern struct FontGlyphRange font_glyph_range_small[];
extern struct FontGlyphRange font_glyph_range_medium[];
extern struct FontGlyphRange font_glyph_range_large[];

extern u8 D_08938258[];
extern u8 D_0893825d[];

/* Small font binaries (glyph data and spacing tables) */
extern u8 small_ascii_0000_007F_bin[];
extern u8 small_spacing_ascii_0000_007F_bin[];
extern u8 small_latin_1_supplement_0080_00FF_bin[];
extern u8 small_spacing_latin_1_supplement_0080_00FF_bin[];
extern u8 small_greek_coptic_0370_03FF_bin[];
extern u8 small_spacing_greek_coptic_0370_03FF_bin[];
extern u8 small_cyrillic_0400_04FF_bin[];
extern u8 small_spacing_cyrillic_0400_04FF_bin[];
extern u8 small_general_punctuation_2000_206F_bin[];
extern u8 small_spacing_general_punctuation_2000_206F_bin[];
extern u8 small_letterlike_symbols_2100_214F_bin[];
extern u8 small_spacing_letterlike_symbols_2100_214F_bin[];
extern u8 small_arrows_2190_21FF_bin[];
extern u8 small_spacing_arrows_2190_21FF_bin[];
extern u8 small_mathematical_operators_2200_22FF_bin[];
extern u8 small_spacing_mathematical_operators_2200_22FF_bin[];
extern u8 small_mathematical_technical_2300_23FF_bin[];
extern u8 small_spacing_mathematical_technical_2300_23FF_bin[];
extern u8 small_box_drawing_2500_257F_bin[];
extern u8 small_spacing_box_drawing_2500_257F_bin[];
extern u8 small_geometric_shapes_25A0_25FF_bin[];
extern u8 small_spacing_geometric_shapes_25A0_25FF_bin[];
extern u8 small_miscellaneous_symbols_2600_26FF_bin[];
extern u8 small_spacing_miscellaneous_symbols_2600_26FF_bin[];
extern u8 small_cjk_symbols_and_punctuation_3000_303F_bin[];
extern u8 small_spacing_cjk_symbols_and_punctuation_3000_303F_bin[];
extern u8 small_hiragana_3040_309F_bin[];
extern u8 small_spacing_hiragana_3040_309F_bin[];
extern u8 small_katakana_30A0_30FF_bin[];
extern u8 small_spacing_katakana_30A0_30FF_bin[];
extern u8 small_cjk_unified_ideographs_4E00_9FFF_bin[];
extern u8 small_spacing_cjk_unified_ideographs_4E00_9FFF_bin[];
extern u8 small_pua_E000_E010_bin[];
extern u8 small_spacing_pua_E000_E010_bin[];
extern u8 small_halfwidth_and_fullwidth_forms_FF00_FFEF_bin[];
extern u8 small_spacing_halfwidth_and_fullwidth_forms_FF00_FFEF_bin[];

/* Medium font binaries */
extern u8 medium_ascii_0000_007F_bin[];
extern u8 medium_spacing_ascii_0000_007F_bin[];
extern u8 medium_latin_1_supplement_0080_00FF_bin[];
extern u8 medium_spacing_latin_1_supplement_0080_00FF_bin[];
extern u8 medium_greek_coptic_0370_03FF_bin[];
extern u8 medium_spacing_greek_coptic_0370_03FF_bin[];
extern u8 medium_cyrillic_0400_04FF_bin[];
extern u8 medium_spacing_cyrillic_0400_04FF_bin[];
extern u8 medium_general_punctuation_2000_206F_bin[];
extern u8 medium_spacing_general_punctuation_2000_206F_bin[];
extern u8 medium_letterlike_symbols_2100_214F_bin[];
extern u8 medium_spacing_letterlike_symbols_2100_214F_bin[];
extern u8 medium_arrows_2190_21FF_bin[];
extern u8 medium_spacing_arrows_2190_21FF_bin[];
extern u8 medium_mathematical_operators_2200_22FF_bin[];
extern u8 medium_spacing_mathematical_operators_2200_22FF_bin[];
extern u8 medium_mathematical_technical_2300_23FF_bin[];
extern u8 medium_spacing_mathematical_technical_2300_23FF_bin[];
extern u8 medium_box_drawing_2500_257F_bin[];
extern u8 medium_spacing_box_drawing_2500_257F_bin[];
extern u8 medium_geometric_shapes_25A0_25FF_bin[];
extern u8 medium_spacing_geometric_shapes_25A0_25FF_bin[];
extern u8 medium_miscellaneous_symbols_2600_26FF_bin[];
extern u8 medium_spacing_miscellaneous_symbols_2600_26FF_bin[];
extern u8 medium_cjk_symbols_and_punctuation_3000_303F_bin[];
extern u8 medium_spacing_cjk_symbols_and_punctuation_3000_303F_bin[];
extern u8 medium_hiragana_3040_309F_bin[];
extern u8 medium_spacing_hiragana_3040_309F_bin[];
extern u8 medium_katakana_30A0_30FF_bin[];
extern u8 medium_spacing_katakana_30A0_30FF_bin[];
extern u8 medium_cjk_unified_ideographs_4E00_9FFF_bin[];
extern u8 medium_spacing_cjk_unified_ideographs_4E00_9FFF_bin[];
extern u8 medium_halfwidth_and_fullwidth_forms_FF00_FFEF_bin[];
extern u8 medium_spacing_halfwidth_and_fullwidth_forms_FF00_FFEF_bin[];

/* Large font binaries */
extern u8 large_ascii_0000_007F_bin[];
extern u8 large_spacing_ascii_0000_007F_bin[];
extern u8 large_latin_1_supplement_0080_00FF_bin[];
extern u8 large_spacing_latin_1_supplement_0080_00FF_bin[];
extern u8 large_greek_coptic_0370_03FF_bin[];
extern u8 large_spacing_greek_coptic_0370_03FF_bin[];
extern u8 large_cyrillic_0400_04FF_bin[];
extern u8 large_spacing_cyrillic_0400_04FF_bin[];
extern u8 large_general_punctuation_2000_206F_bin[];
extern u8 large_spacing_general_punctuation_2000_206F_bin[];
extern u8 large_letterlike_symbols_2100_214F_bin[];
extern u8 large_spacing_letterlike_symbols_2100_214F_bin[];
extern u8 large_arrows_2190_21FF_bin[];
extern u8 large_spacing_arrows_2190_21FF_bin[];
extern u8 large_mathematical_operators_2200_22FF_bin[];
extern u8 large_spacing_mathematical_operators_2200_22FF_bin[];
extern u8 large_mathematical_technical_2300_23FF_bin[];
extern u8 large_spacing_mathematical_technical_2300_23FF_bin[];
extern u8 large_box_drawing_2500_257F_bin[];
extern u8 large_spacing_box_drawing_2500_257F_bin[];
extern u8 large_geometric_shapes_25A0_25FF_bin[];
extern u8 large_spacing_geometric_shapes_25A0_25FF_bin[];
extern u8 large_miscellaneous_symbols_2600_26FF_bin[];
extern u8 large_spacing_miscellaneous_symbols_2600_26FF_bin[];
extern u8 large_cjk_symbols_and_punctuation_3000_303F_bin[];
extern u8 large_spacing_cjk_symbols_and_punctuation_3000_303F_bin[];
extern u8 large_hiragana_3040_309F_bin[];
extern u8 large_spacing_hiragana_3040_309F_bin[];
extern u8 large_katakana_30A0_30FF_bin[];
extern u8 large_spacing_katakana_30A0_30FF_bin[];
extern u8 large_cjk_unified_ideographs_4E00_9FFF_bin[];
extern u8 large_spacing_cjk_unified_ideographs_4E00_9FFF_bin[];
extern u8 large_halfwidth_and_fullwidth_forms_FF00_FFEF_bin[];
extern u8 large_spacing_halfwidth_and_fullwidth_forms_FF00_FFEF_bin[];
