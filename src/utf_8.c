#include "utf_8.h"


s32 utf8_decode_codepoint(const char **string, u32 *codepoint) {
    const u8 *s;
    u32 value;
    u32 length;
    u32 i;

    s = (const u8 *)(*string);

    if (s[0] == '\0') {
        *codepoint = 0;
        return FALSE;
    }

    if (s[0] < 0x80) {
        *string += 1;
        *codepoint = s[0];
        return TRUE;
    }

    if ((s[0] & 0xe0) == 0xc0) {
        value = s[0] & 0x1f;
        length = 2;
    } else if ((s[0] & 0xf0) == 0xe0) {
        value = s[0] & 0x0f;
        length = 3;
    } else if ((s[0] & 0xf8) == 0xf0) {
        value = s[0] & 0x07;
        length = 4;
    } else {
        goto invalid_utf8;
    }

    for (i = 1; i < length; i++) {
        if ((s[i] == '\0') || ((s[i] & 0xc0) != 0x80)) {
            goto invalid_utf8;
        }

        value = (value << 6) | (s[i] & 0x3f);
    }

    if ((length == 2) && (value < 0x80)) {
        goto invalid_utf8;
    }

    if ((length == 3) && (value < 0x800)) {
        goto invalid_utf8;
    }

    if ((length == 4) && ((value < 0x10000) || (value > 0x10ffff))) {
        goto invalid_utf8;
    }

    if ((value >= 0xd800) && (value <= 0xdfff)) {
        goto invalid_utf8;
    }

    *string += length;
    *codepoint = value;
    return TRUE;

invalid_utf8:
    *string += 1;
    *codepoint = s[0];
    return FALSE;
}


u32 utf8_get_char_len(const char *string) {
    const char *next;
    u32 codepoint;

    if (string[0] == '\0') {
        return 0;
    }

    next = string;
    utf8_decode_codepoint(&next, &codepoint);
    return next - string;
}


const char *utf8_get_next_char_ptr(const char *string) {
    return string + utf8_get_char_len(string);
}


s32 utf8_codepoint_is_in_list(u32 codepoint, const char *list) {
    while (list[0] != '\0') {
        const char *next;
        u32 listCodepoint;

        next = list;
        utf8_decode_codepoint(&next, &listCodepoint);
        if (listCodepoint == codepoint) {
            return TRUE;
        }

        list = next;
    }

    return FALSE;
}