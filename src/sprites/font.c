/* ---------------------------LICENSE NOTICE-------------------------------- 
MIT License

Copyright (c) 2018 David Asta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "font.h"

const u8 fnt_letters[FONT_TOTAL_LETTERS][FONT_W * FONT_H] = {
    /* A */
    { 
        0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 
        0x41, 0xC3, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41
    },
    /* B */
    { 
        0x04, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 
        0x41, 0xC3, 0x41, 0x41, 0x41, 0x41, 0x41, 0x82
    },
    /* C */
    { 
        0x04, 0x0C, 0x04, 0x0C, 0x04, 0x00, 0x04, 0x00, 
        0x41, 0x00, 0x41, 0x00, 0x41, 0xC3, 0x41, 0xC3
    },
    /* D */
    { 
        0x04, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x82
    },
    /* E */
    { 
        0x04, 0x0C, 0x04, 0x00, 0x04, 0x00, 0x04, 0x0C, 
        0x41, 0xC3, 0x41, 0x00, 0x41, 0x00, 0x41, 0xC3
    },
    /* F */
    { 
        0x04, 0x0C, 0x04, 0x00, 0x04, 0x00, 0x04, 0x08, 
        0x41, 0x82, 0x41, 0x00, 0x41, 0x00, 0x41, 0x00
    },
    /* G */
    { 
        0x04, 0x0C, 0x04, 0x0C, 0x04, 0x00, 0x04, 0x00, 
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0xC3
    },
    /* H */
    { 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 
        0x41, 0xC3, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41
    },
    /* I */
    { 
        0x04, 0x0C, 0x04, 0x0C, 0x00, 0x08, 0x00, 0x08, 
        0x00, 0x82, 0x00, 0x82, 0x41, 0xC3, 0x41, 0xC3
    },
    /* J */
    { 
        0x04, 0x0C, 0x04, 0x0C, 0x00, 0x04, 0x00, 0x04, 
        0x00, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0xC3
    },
    /* K */
    { 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 
        0x41, 0x82, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41
    },
    /* L */
    { 
        0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 
        0x41, 0x00, 0x41, 0x00, 0x41, 0xC3, 0x41, 0xC3
    },
    /* M */
    { 
        0x04, 0x04, 0x04, 0x0C, 0x04, 0x0C, 0x04, 0x0C, 
        0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41
    },
    /* N */
    { 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 0x04, 0x0C, 
        0x41, 0xC3, 0x41, 0xC3, 0x41, 0x41, 0x41, 0x41
    },
    /* O */
    { 
        0x04, 0x0C, 0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 
        0x41, 0x41, 0x41, 0x41, 0x41, 0xC3, 0x41, 0xC3
    },
    /* P */
    { 
        0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C, 
        0x41, 0x00, 0x41, 0x00, 0x41, 0x00, 0x41, 0x00
    },
    /* Q */
    { 
        0x04, 0x0C, 0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 
        0x41, 0x41, 0x41, 0xC3, 0x41, 0xC3, 0x00, 0x41
    },
    /* R */
    { 
        0x04, 0x08, 0x04, 0x04, 0x04, 0x04, 0x04, 0x08, 
        0x41, 0x82, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41
    },
    /* S */
    { 
        0x04, 0x0C, 0x04, 0x00, 0x04, 0x00, 0x04, 0x0C, 
        0x41, 0xC3, 0x00, 0x41, 0x00, 0x41, 0x41, 0xC3
    },
    /* T */
    { 
        0x04, 0x0C, 0x04, 0x0C, 0x00, 0x82, 0x00, 0x82, 
        0x00, 0x82, 0x00, 0x82, 0x00, 0x82, 0x00, 0x82
    },
    /* U */
    { 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
        0x41, 0x41, 0x41, 0x41, 0x41, 0xC3, 0x41, 0xC3
    },
    /* V */
    { 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
        0x41, 0x41, 0x41, 0xC3, 0x41, 0xC3, 0x00, 0x82
    },
    /* W */
    {
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
        0x41, 0x41, 0x41, 0xC3, 0x41, 0xC3, 0x41, 0x41
    },
    /* X */
    { 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x08, 
        0x00, 0x82, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41
    },
    /* Y */
    { 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
        0x00, 0x82, 0x00, 0x82, 0x00, 0x82, 0x00, 0x82
    },
    /* Z */
    { 
        0x04, 0x0C, 0x00, 0x04, 0x00, 0x04, 0x00, 0x08, 
        0x00, 0x82, 0x41, 0x00, 0x41, 0x00, 0x41, 0xC3
    }
};

const u8 fnt_numbers[FONT_TOTAL_NUMBERS][FONT_W * FONT_H] = {
    /* 0 */
    { 
        0x00, 0x20, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x08
    },
    /* 1 */
    { 
        0x00, 0x20, 0x10, 0x20, 0x10, 0x20, 0x00, 0x20, 
        0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x04, 0x0C
    },
    /* 2 */
    { 
        0x10, 0x30, 0x00, 0x10, 0x00, 0x10, 0x10, 0x30, 
        0x04, 0x0C, 0x04, 0x00, 0x04, 0x00, 0x04, 0x0C
    },
    /* 3 */
    { 
        0x10, 0x30, 0x00, 0x10, 0x00, 0x10, 0x10, 0x30, 
        0x04, 0x0C, 0x00, 0x04, 0x00, 0x04, 0x04, 0x0C
    },
    /* 4 */
    { 
        0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 
        0x04, 0x0C, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04
    },
    /* 5 */
    { 
        0x10, 0x30, 0x10, 0x00, 0x10, 0x00, 0x10, 0x30, 
        0x04, 0x0C, 0x00, 0x04, 0x00, 0x04, 0x04, 0x0C
    },
    /* 6 */
    { 
        0x10, 0x30, 0x10, 0x00, 0x10, 0x00, 0x10, 0x30, 
        0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C
    },
    /* 7 */
    { 
        0x10, 0x30, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 
        0x00, 0x04, 0x00, 0x04, 0x00, 0x04, 0x00, 0x04
    },
    /* 8 */
    { 
        0x10, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 
        0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0C
    },
    /* 9 */
    { 
        0x10, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 
        0x04, 0x0C, 0x00, 0x04, 0x00, 0x04, 0x04, 0x0C
    },
};

const u8 fnt_symbols[FONT_TOTAL_SYMBOLS][FONT_W * FONT_H] = {
    /* Colon */
    {
        0x00, 0x00, 0x00, 0xA0, 0x00, 0xA0, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0xA0, 0x00, 0xA0, 0x00, 0x00
    },
    /* Dash */
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
        0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    },
    /* Close bracket */
    {
        0x50, 0x00, 0x00, 0xA0, 0x00, 0xF0, 0x00, 0x50, 
        0x00, 0x50, 0x00, 0xF0, 0x00, 0xA0, 0x50, 0x00
    },
    /* Slash */
    {
        0x00, 0x50, 0x00, 0x50, 0x00, 0x50, 0x00, 0xA0, 
        0x00, 0xA0, 0x50, 0x00, 0x50, 0x00, 0x50, 0x00
    },
    /* Space */
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    },
    /* Dot */
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20
    }
};