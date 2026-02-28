#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Font Character Analyzer for Rhythm Heaven Advance

This script helps you:
1. Find unused character slots in the font
2. Understand the glyph data structure
3. Identify safe characters to replace
"""

import struct
import sys

def analyze_glyph_sizes(filename):
    """
    Analyze the glyph sizes file to find unused characters
    
    The .bin files contain width data for each character.
    A width of 0 typically means the character is unused/empty.
    """
    print(f"\n=== Analyzing {filename} ===\n")
    
    with open(filename, 'rb') as f:
        data = f.read()
    
    # Each byte represents the width of one glyph
    print(f"Total glyphs: {len(data)}")
    print(f"File size: {len(data)} bytes\n")
    
    # Find unused characters (width = 0)
    unused = []
    used_count = 0
    
    for i, width in enumerate(data):
        if width == 0:
            unused.append(i)
        else:
            used_count += 1
    
    print(f"Used glyphs: {used_count}")
    print(f"Unused glyphs: {len(unused)}\n")
    
    if unused:
        print("Unused glyph indices (these can be replaced):")
        # Group consecutive unused indices
        groups = []
        start = unused[0]
        end = unused[0]
        
        for idx in unused[1:]:
            if idx == end + 1:
                end = idx
            else:
                groups.append((start, end))
                start = idx
                end = idx
        groups.append((start, end))
        
        for start, end in groups:
            if start == end:
                print(f"  Index {start} (0x{start:04X})")
            else:
                print(f"  Indices {start}-{end} (0x{start:04X}-0x{end:04X}) - {end-start+1} characters")
    
    # Show width distribution
    print("\nWidth distribution:")
    width_counts = {}
    for width in data:
        width_counts[width] = width_counts.get(width, 0) + 1
    
    for width in sorted(width_counts.keys()):
        count = width_counts[width]
        percentage = (count / len(data)) * 100
        print(f"  Width {width:2d}: {count:4d} glyphs ({percentage:5.2f}%)")
    
    return unused


def calculate_glyph_offset(glyph_index, glyph_size_bytes):
    """
    Calculate the byte offset for a glyph in the texture file
    
    glyph_index: The index of the character
    glyph_size_bytes: Size of each glyph in bytes (from TextPrinterFont.glyphDataSize)
                      Small/Medium: 0x18 bytes (24 bytes = 12x16 pixels at 4bpp)
                      Large: 0x20 bytes (32 bytes = 16x16 pixels at 4bpp)
    """
    return glyph_index * glyph_size_bytes


def print_shift_jis_mapping():
    """
    Print the Shift-JIS character mapping used by the game
    """
    print("\n=== Shift-JIS Character Mapping ===\n")
    print("The game uses these byte ranges:")
    print("  0x81 0x40-0x7E : Punctuation/Symbols (63 chars)")
    print("  0x81 0x80-0x9E : Punctuation/Symbols (31 chars)")
    print("  0x82 0x4F-0x58 : Arabic Numerals 0-9 (10 chars)")
    print("  0x82 0x60-0x79 : Uppercase Latin A-Z (26 chars)")
    print("  0x82 0x81-0x9A : Lowercase Latin a-z (26 chars)")
    print("  0x82 0x9F-0xFC : Hiragana (94 chars)")
    print("  0x83 0x40-0x7E : Katakana (63 chars)")
    print("  0x83 0x80-0x9E : Katakana (31 chars)")
    print("\nTotal mapped: 344 characters")
    print("Total in file: 7332 glyphs")
    print("-> Most glyphs are unused/extended character sets\n")


if __name__ == "__main__":
    print("=" * 70)
    print("RHYTHM HEAVEN ADVANCE - FONT CHARACTER ANALYZER")
    print("=" * 70)
    
    # Analyze all three font sizes
    sizes = ['small', 'medium', 'large']
    
    for size in sizes:
        filename = f"bin/text_{size}_glyph_sizes.bin"
        try:
            unused = analyze_glyph_sizes(filename)
        except FileNotFoundError:
            print(f"Error: {filename} not found. Make sure you run this from the project root.")
            sys.exit(1)
    
    print_shift_jis_mapping()
    
    print("\n=== How to Add New Characters ===\n")
    print("1. Choose unused glyph indices from above")
    print("2. Edit the corresponding .bin files:")
    print("   - text_*_glyphs.bin: Add your character graphics (4bpp tiled format)")
    print("   - text_*_glyph_sizes.bin: Set the width for your character")
    print("3. Add mapping to char_remap.c:")
    print("   {input_byte1, input_byte2, output_byte1, output_byte2}")
    print("4. Rebuild and test!")
    print()
