#pragma once

#include "global.h"


extern s32 utf8_decode_codepoint(const char **string, u32 *codepoint);
extern u32 utf8_get_char_len(const char *string);
extern const char *utf8_get_next_char_ptr(const char *string);
extern s32 utf8_codepoint_is_in_list(u32 codepoint, const char *list);