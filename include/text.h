#pragma once


/* TEXT MACROS */


// Standard Text: Printer Settings
#define PRINTER_COLOR_0     "\1" "0"
#define PRINTER_COLOR_1     "\1" "1"
#define PRINTER_COLOR_2     "\1" "2"
#define PRINTER_COLOR_3     "\1" "3"
#define PRINTER_SHADOW_0    "\1" "4"
#define PRINTER_SHADOW_1    "\1" "5"
#define PRINTER_SHADOW_2    "\1" "6"
#define PRINTER_SHADOW_3    "\1" "7"
#define PRINTER_SHADOW_NONE "\1" "8"
#define PRINTER_ALIGN_L     "\1" "L"
#define PRINTER_ALIGN_C     "\1" "C"
#define PRINTER_ALIGN_R     "\1" "R"
#define PRINTER_SIZE_S      "\1" "s"
#define PRINTER_SIZE_M      "\1" "m"
#define PRINTER_SIZE_L      "\1" "l"
#define PRINTER_INDENT      "\1" "["
#define PRINTER_INDENT_END  "\1" "]"

// Standard Text: Single-String Options
#define TEXT_COLOR_0        "\2" "0"
#define TEXT_COLOR_1        "\2" "1"
#define TEXT_COLOR_2        "\2" "2"
#define TEXT_COLOR_3        "\2" "3"
#define TEXT_SIZE_S         "\3" "0"
#define TEXT_SIZE_M         "\3" "1"
#define TEXT_SIZE_L         "\3" "2"
#define TEXT_OFFSET(width)  "\4" #width "."
#define TEXT_SHADOW_0       "\5" "0"
#define TEXT_SHADOW_1       "\5" "1"
#define TEXT_SHADOW_2       "\5" "2"
#define TEXT_SHADOW_3       "\5" "3"
#define TEXT_SHADOW_NONE    "\5" "4"

// Bitmap Font: Color Settings
#define FONT_COLOR(x)   "." #x
#define FONT_COLOR_0    "." "0"
#define FONT_COLOR_1    "." "1"
#define FONT_COLOR_2    "." "2"
#define FONT_COLOR_3    "." "3"
#define FONT_COLOR_4    "." "4"
#define FONT_COLOR_5    "." "5"
#define FONT_COLOR_6    "." "6"
#define FONT_COLOR_7    "." "7"
#define FONT_COLOR_8    "." "8"
#define FONT_COLOR_9    "." "9"
#define FONT_COLOR_A    "." "a"
#define FONT_COLOR_B    "." "b"
#define FONT_COLOR_C    "." "c"
#define FONT_COLOR_D    "." "d"
#define FONT_COLOR_E    "." "e"
#define FONT_COLOR_F    "." "f"

// Bitmap Font: Font Styles
#define FONT_STYLE(x)       ":" #x
#define FONT_WW_OUTLINE_L   ":" "0"
#define FONT_WW_OUTLINE_S   ":" "1"
#define FONT_WW_OUTLINE_NUM ":" "2"
#define FONT_WW_BODY_TEXT   ":" "0"
#define FONT_WW_BODY_ICON   ":" "1"

#define CHAR_1_PIXEL_GAP        0xE000
#define CHAR_LEFT_DPAD          0xE001
#define CHAR_RIGHT_DPAD         0xE002
#define CHAR_UP_DPAD            0xE003
#define CHAR_DOWN_DPAD          0xE004
#define CHAR_DPAD               0xE005
#define CHAR_A_BUTTON           0xE006
#define CHAR_B_BUTTON           0xE007
#define CHAR_L_SHOULDER_BUTTON  0xE008
#define CHAR_R_SHOULDER_BUTTON  0xE009
#define CHAR_SPANISH_ORDINAL_A  0xE00A
#define CHAR_FRENCH_ORDINAL_ER  0xE00B
#define CHAR_FRENCH_ORDINAL_EME 0xE00C
#define CHAR_LEFT_ARROW_DOWN    0xE00D
#define CHAR_RIGHT_ARROW_DOWN   0xE00E
#define CHAR_LEFT_ARROW_UP      0xE00F
#define CHAR_RIGHT_ARROW_UP     0xE010
#define CHAR_GBA                0xE011

#define CHAR_1_PIXEL_GAP_UTF8        "\xEE\x80\x80"
#define CHAR_LEFT_DPAD_UTF8          "\xEE\x80\x81"
#define CHAR_RIGHT_DPAD_UTF8         "\xEE\x80\x82"
#define CHAR_UP_DPAD_UTF8            "\xEE\x80\x83"
#define CHAR_DOWN_DPAD_UTF8          "\xEE\x80\x84"
#define CHAR_DPAD_UTF8               "\xEE\x80\x85"
#define CHAR_A_BUTTON_UTF8           "\xEE\x80\x86"
#define CHAR_B_BUTTON_UTF8           "\xEE\x80\x87"
#define CHAR_L_SHOULDER_BUTTON_UTF8  "\xEE\x80\x88"
#define CHAR_R_SHOULDER_BUTTON_UTF8  "\xEE\x80\x89"
#define CHAR_SPANISH_ORDINAL_A_UTF8  "\xEE\x80\x8A"
#define CHAR_FRENCH_ORDINAL_ER_UTF8  "\xEE\x80\x8B"
#define CHAR_FRENCH_ORDINAL_EME_UTF8 "\xEE\x80\x8C"
#define CHAR_LEFT_ARROW_DOWN_UTF8    "\xEE\x80\x8D"
#define CHAR_RIGHT_ARROW_DOWN_UTF8   "\xEE\x80\x8E"
#define CHAR_LEFT_ARROW_UP_UTF8      "\xEE\x80\x8F"
#define CHAR_RIGHT_ARROW_UP_UTF8     "\xEE\x80\x90"
#define CHAR_GBA_UTF8                "\xEE\x80\x91"