#include "global.h"
#include "text.h"
#include "text_printer_data.h"


/* TEXT PRINTER DATA */

struct FontGlyphRange font_glyph_range_small[] = {
    /* ascii */ { small_ascii_0000_007F_bin, small_spacing_ascii_0000_007F_bin, 0x0000, 0x007f },
    /* latin_1_supplement */ { small_latin_1_supplement_0080_00FF_bin, small_spacing_latin_1_supplement_0080_00FF_bin, 0x0080, 0x00ff },
    /* greek_coptic */ { small_greek_coptic_0370_03FF_bin, small_spacing_greek_coptic_0370_03FF_bin, 0x0370, 0x03ff },
    /* cyrillic */ { small_cyrillic_0400_04FF_bin, small_spacing_cyrillic_0400_04FF_bin, 0x0400, 0x04ff },
    /* general_punctuation */ { small_general_punctuation_2000_206F_bin, small_spacing_general_punctuation_2000_206F_bin, 0x2000, 0x206f },
    /* letterlike_symbols */ { small_letterlike_symbols_2100_214F_bin, small_spacing_letterlike_symbols_2100_214F_bin, 0x2100, 0x214f },
    /* arrows */ { small_arrows_2190_21FF_bin, small_spacing_arrows_2190_21FF_bin, 0x2190, 0x21ff },
    /* mathematical_operators */ { small_mathematical_operators_2200_22FF_bin, small_spacing_mathematical_operators_2200_22FF_bin, 0x2200, 0x22ff },
    /* mathematical_technical */ { small_mathematical_technical_2300_23FF_bin, small_spacing_mathematical_technical_2300_23FF_bin, 0x2300, 0x23ff },
    /* box_drawing */ { small_box_drawing_2500_257F_bin, small_spacing_box_drawing_2500_257F_bin, 0x2500, 0x257f },
    /* geometric_shapes */ { small_geometric_shapes_25A0_25FF_bin, small_spacing_geometric_shapes_25A0_25FF_bin, 0x25a0, 0x25ff },
    /* miscellaneous_symbols */ { small_miscellaneous_symbols_2600_26FF_bin, small_spacing_miscellaneous_symbols_2600_26FF_bin, 0x2600, 0x26ff },
    /* cjk_symbols_and_punctuation */ { small_cjk_symbols_and_punctuation_3000_303F_bin, small_spacing_cjk_symbols_and_punctuation_3000_303F_bin, 0x3000, 0x303f },
    /* hiragana */ { small_hiragana_3040_309F_bin, small_spacing_hiragana_3040_309F_bin, 0x3040, 0x309f },
    /* katakana */ { small_katakana_30A0_30FF_bin, small_spacing_katakana_30A0_30FF_bin, 0x30a0, 0x30ff },
    /* cjk_unified_ideographs */ { small_cjk_unified_ideographs_4E00_9FFF_bin, small_spacing_cjk_unified_ideographs_4E00_9FFF_bin, 0x4e00, 0x9fff },
    /* pua */ { small_pua_E000_E010_bin, small_spacing_pua_E000_E010_bin, 0xE000, 0xE010 },
    /* halfwidth_and_fullwidth_forms */ { small_halfwidth_and_fullwidth_forms_FF00_FFEF_bin, small_spacing_halfwidth_and_fullwidth_forms_FF00_FFEF_bin, 0xff00, 0xffef },
    END_OF_RANGE
};

struct FontGlyphRange font_glyph_range_medium[] = {
    /* ascii */ { medium_ascii_0000_007F_bin, medium_spacing_ascii_0000_007F_bin, 0x0000, 0x007f },
    /* latin_1_supplement */ { medium_latin_1_supplement_0080_00FF_bin, medium_spacing_latin_1_supplement_0080_00FF_bin, 0x0080, 0x00ff },
    /* greek_coptic */ { medium_greek_coptic_0370_03FF_bin, medium_spacing_greek_coptic_0370_03FF_bin, 0x0370, 0x03ff },
    /* cyrillic */ { medium_cyrillic_0400_04FF_bin, medium_spacing_cyrillic_0400_04FF_bin, 0x0400, 0x04ff },
    /* general_punctuation */ { medium_general_punctuation_2000_206F_bin, medium_spacing_general_punctuation_2000_206F_bin, 0x2000, 0x206f },
    /* letterlike_symbols */ { medium_letterlike_symbols_2100_214F_bin, medium_spacing_letterlike_symbols_2100_214F_bin, 0x2100, 0x214f },
    /* arrows */ { medium_arrows_2190_21FF_bin, medium_spacing_arrows_2190_21FF_bin, 0x2190, 0x21ff },
    /* mathematical_operators */ { medium_mathematical_operators_2200_22FF_bin, medium_spacing_mathematical_operators_2200_22FF_bin, 0x2200, 0x22ff },
    /* mathematical_technical */ { medium_mathematical_technical_2300_23FF_bin, medium_spacing_mathematical_technical_2300_23FF_bin, 0x2300, 0x23ff },
    /* box_drawing */ { medium_box_drawing_2500_257F_bin, medium_spacing_box_drawing_2500_257F_bin, 0x2500, 0x257f },
    /* geometric_shapes */ { medium_geometric_shapes_25A0_25FF_bin, medium_spacing_geometric_shapes_25A0_25FF_bin, 0x25a0, 0x25ff },
    /* miscellaneous_symbols */ { medium_miscellaneous_symbols_2600_26FF_bin, medium_spacing_miscellaneous_symbols_2600_26FF_bin, 0x2600, 0x26ff },
    /* cjk_symbols_and_punctuation */ { medium_cjk_symbols_and_punctuation_3000_303F_bin, medium_spacing_cjk_symbols_and_punctuation_3000_303F_bin, 0x3000, 0x303f },
    /* hiragana */ { medium_hiragana_3040_309F_bin, medium_spacing_hiragana_3040_309F_bin, 0x3040, 0x309f },
    /* katakana */ { medium_katakana_30A0_30FF_bin, medium_spacing_katakana_30A0_30FF_bin, 0x30a0, 0x30ff },
    /* cjk_unified_ideographs */ { medium_cjk_unified_ideographs_4E00_9FFF_bin, medium_spacing_cjk_unified_ideographs_4E00_9FFF_bin, 0x4e00, 0x9fff },
    /* halfwidth_and_fullwidth_forms */ { medium_halfwidth_and_fullwidth_forms_FF00_FFEF_bin, medium_spacing_halfwidth_and_fullwidth_forms_FF00_FFEF_bin, 0xff00, 0xffef },
    END_OF_RANGE
};

struct FontGlyphRange font_glyph_range_large[] = {
    /* ascii */ { large_ascii_0000_007F_bin, large_spacing_ascii_0000_007F_bin, 0x0000, 0x007f },
    /* latin_1_supplement */ { large_latin_1_supplement_0080_00FF_bin, large_spacing_latin_1_supplement_0080_00FF_bin, 0x0080, 0x00ff },
    /* greek_coptic */ { large_greek_coptic_0370_03FF_bin, large_spacing_greek_coptic_0370_03FF_bin, 0x0370, 0x03ff },
    /* cyrillic */ { large_cyrillic_0400_04FF_bin, large_spacing_cyrillic_0400_04FF_bin, 0x0400, 0x04ff },
    /* general_punctuation */ { large_general_punctuation_2000_206F_bin, large_spacing_general_punctuation_2000_206F_bin, 0x2000, 0x206f },
    /* letterlike_symbols */ { large_letterlike_symbols_2100_214F_bin, large_spacing_letterlike_symbols_2100_214F_bin, 0x2100, 0x214f },
    /* arrows */ { large_arrows_2190_21FF_bin, large_spacing_arrows_2190_21FF_bin, 0x2190, 0x21ff },
    /* mathematical_operators */ { large_mathematical_operators_2200_22FF_bin, large_spacing_mathematical_operators_2200_22FF_bin, 0x2200, 0x22ff },
    /* mathematical_technical */ { large_mathematical_technical_2300_23FF_bin, large_spacing_mathematical_technical_2300_23FF_bin, 0x2300, 0x23ff },
    /* box_drawing */ { large_box_drawing_2500_257F_bin, large_spacing_box_drawing_2500_257F_bin, 0x2500, 0x257f },
    /* geometric_shapes */ { large_geometric_shapes_25A0_25FF_bin, large_spacing_geometric_shapes_25A0_25FF_bin, 0x25a0, 0x25ff },
    /* miscellaneous_symbols */ { large_miscellaneous_symbols_2600_26FF_bin, large_spacing_miscellaneous_symbols_2600_26FF_bin, 0x2600, 0x26ff },
    /* cjk_symbols_and_punctuation */ { large_cjk_symbols_and_punctuation_3000_303F_bin, large_spacing_cjk_symbols_and_punctuation_3000_303F_bin, 0x3000, 0x303f },
    /* hiragana */ { large_hiragana_3040_309F_bin, large_spacing_hiragana_3040_309F_bin, 0x3040, 0x309f },
    /* katakana */ { large_katakana_30A0_30FF_bin, large_spacing_katakana_30A0_30FF_bin, 0x30a0, 0x30ff },
    /* cjk_unified_ideographs */ { large_cjk_unified_ideographs_4E00_9FFF_bin, large_spacing_cjk_unified_ideographs_4E00_9FFF_bin, 0x4e00, 0x9fff },
    /* halfwidth_and_fullwidth_forms */ { large_halfwidth_and_fullwidth_forms_FF00_FFEF_bin, large_spacing_halfwidth_and_fullwidth_forms_FF00_FFEF_bin, 0xff00, 0xffef },
    END_OF_RANGE
};


// [D_089380ac] Text Printer Font Table
struct TextPrinterFont D_089380ac[] = {
    /* Small Text */ {
        /* Glyph Ranges    */ font_glyph_range_small,
        /* Glyph Data Size */ 0x18,
        /* Glyph Spacing   */ 1,
        /* unkA            */ 11,
        /* unkB            */ 10
    },
    /* Medium Text */ {
        /* Glyph Ranges    */ font_glyph_range_medium,
        /* Glyph Data Size */ 0x18,
        /* Glyph Spacing   */ 2,
        /* unkA            */ 11,
        /* unkB            */ 12
    },
    /* Large Text */ {
        /* Glyph Ranges    */ font_glyph_range_large,
        /* Glyph Data Size */ 0x20,
        /* Glyph Spacing   */ 2,
        /* unkA            */ 11,
        /* unkB            */ 16
    },
};

// [D_08938258]
u8 D_08938258[] = { 32, 16, 10, 8, 4 };

// [D_0893825d]
u8 D_0893825d[] = { 1, 2, 3, 4, 8 };
