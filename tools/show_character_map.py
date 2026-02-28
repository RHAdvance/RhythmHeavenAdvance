#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Character Map Viewer for Rhythm Heaven Advance

Shows which Shift-JIS codes map to which glyph indices in the font.
Useful for understanding what characters are available.
"""

def show_character_mappings():
    """Display the character-to-glyph-index mapping"""
    
    print("=" * 80)
    print("RHYTHM HEAVEN ADVANCE - CHARACTER TO GLYPH INDEX MAPPING")
    print("=" * 80)
    print()
    
    # Based on bmp_font_get_glyph() from src/bitmap_font.c
    
    print("PUNCTUATION/SYMBOLS (Font Punctuation Array)")
    print("-" * 80)
    print("Shift-JIS Range: 0x81 0x40-0x7E")
    base_idx = 0
    for i in range(0x40, 0x7F):
        idx = i - 0x40
        print(f"  0x81 0x{i:02X} Å® Punctuation index {idx:2d}")
    
    print()
    print("Shift-JIS Range: 0x81 0x80-0x9E")
    for i in range(0x80, 0x9F):
        idx = i - 0x41  # Note: 0x41, not 0x80 (see code)
        print(f"  0x81 0x{i:02X} Å® Punctuation index {idx:2d}")
    
    print()
    print("=" * 80)
    print("ARABIC NUMERALS (Font Arabic Numeral Array)")
    print("-" * 80)
    print("Shift-JIS Range: 0x82 0x4F-0x58")
    chars = "0123456789"
    for i, c in enumerate(range(0x4F, 0x59)):
        print(f"  0x82 0x{c:02X} Å® Numeral index {i} ('{chars[i]}')")
    
    print()
    print("=" * 80)
    print("UPPERCASE LATIN ALPHABET (Font Latin Uppercase Array)")
    print("-" * 80)
    print("Shift-JIS Range: 0x82 0x60-0x79")
    chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    for i, c in enumerate(range(0x60, 0x7A)):
        idx = c - 0x60
        print(f"  0x82 0x{c:02X} Å® Latin Upper index {idx:2d} ('{chars[i]}')")
    
    print()
    print("=" * 80)
    print("LOWERCASE LATIN ALPHABET (Font Latin Lowercase Array)")
    print("-" * 80)
    print("Shift-JIS Range: 0x82 0x81-0x9A")
    chars = "abcdefghijklmnopqrstuvwxyz"
    for i, c in enumerate(range(0x81, 0x9B)):
        idx = c - 0x81
        print(f"  0x82 0x{c:02X} Å® Latin Lower index {idx:2d} ('{chars[i]}')")
    
    print()
    print("=" * 80)
    print("HIRAGANA (Font Hiragana Array)")
    print("-" * 80)
    print("Shift-JIS Range: 0x82 0x9F-0xFC")
    total = 0xFC - 0x9F + 1
    print(f"  0x82 0x9F-0xFC Å® Hiragana indices 0-{total-1} ({total} characters)")
    print("  (Ç†, Ç¢, Ç§, Ç¶, Ç®, ... etc.)")
    
    print()
    print("=" * 80)
    print("KATAKANA (Font Katakana Array)")
    print("-" * 80)
    print("Shift-JIS Range: 0x83 0x40-0x7E")
    count1 = 0x7E - 0x40 + 1
    for i in range(0x40, 0x7F):
        idx = i - 0x40
        if i == 0x40:
            print(f"  0x83 0x{i:02X} Å® Katakana index {idx:2d} (ÉA, etc.)")
        elif i == 0x7E:
            print(f"  0x83 0x{i:02X} Å® Katakana index {idx:2d}")
    
    print("...")
    print("Shift-JIS Range: 0x83 0x80-0x9E")
    for i in range(0x80, 0x9F):
        idx = i - 0x41  # Note: offset continues from previous range
        if i == 0x80:
            print(f"  0x83 0x{i:02X} Å® Katakana index {idx:2d}")
        elif i == 0x9E:
            print(f"  0x83 0x{i:02X} Å® Katakana index {idx:2d}")
    
    print()
    print("=" * 80)
    print("SPECIAL NOTES")
    print("-" * 80)
    print("1. Whitespace characters:")
    print("   - 0x81 0x40 = Full-width space")
    print("   - 0x20 0x20 = ASCII space (treated as 2-byte)")
    print("   - 0x81 0x51 = Another space variant")
    print()
    print("2. Halfwidth Latin (special encoding):")
    print("   - First byte = lowercase 'a'-'z'")
    print("   - Second byte = lowercase 'a'-'z'")
    print("   - These get converted to fullwidth automatically")
    print()
    print("3. Control codes for bitmap font:")
    print("   - '.' + digit = Color palette selection (.:0-:f)")
    print("   - ':' + digit = Font style selection (:0-:9)")
    print()
    print("4. Most glyph arrays are in font_definitions.c")
    print("   but the bin/ folder fonts use a different system")
    print("   with sequential glyph indices")
    print()
    print("=" * 80)
    print()


if __name__ == "__main__":
    show_character_mappings()
    
    print("\nTo find which glyph index a specific character uses:")
    print("  1. Convert your character to Shift-JIS bytes")
    print("  2. Use the ranges above to calculate the index")
    print("  3. Check if that index is unused (width = 0) using analyze_font.py")
    print()
