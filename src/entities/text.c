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

#include <cpctelera.h>
#include "text.h"
#include "defines.h"
#include "sprites/font.h"

/**
 * \brief It draws a text (of letters) by using the letters defined in #sprites/fonts.c
 * 
 * The if-else is ordered this way because I mostly use letters and numbers,
 * and #draw_number() is called constantly within the #update_game().
 * 
 * \warning It only accepts uppercase letters!
 * 
 * \param text[] Text to be drawn.
 * \param x Horizontal position where to draw it in the screen.
 * \param y Vertical position where to draw it in the screen.
 */
void draw_text(const u8 text[], u8 x, u8 y){
    u8* pvmem;
    u8 chr;
    u8 idx = 0;

    chr = text[idx];

    while (chr != '\0') {
        pvmem = cpct_getScreenPtr(CPCT_VMEM_START, (idx * FONT_W) + x, y);

        if (chr >= 48 && chr <= 57) {           /* is a number */
            cpct_drawSprite(fnt_numbers[chr - 48], pvmem, FONT_W, FONT_H);
        }else if (chr >= 65 && chr <= 90) {     /* is a letter */
            cpct_drawSprite(fnt_letters[chr - 65], pvmem, FONT_W, FONT_H);
        }else if(chr == 32) {                   /* is a space ) */
            cpct_drawSprite(fnt_symbols[4], pvmem, FONT_W, FONT_H);
        }else if(chr == 41) {                   /* is a close bracket ) */
            cpct_drawSprite(fnt_symbols[2], pvmem, FONT_W, FONT_H);
        }else if(chr == 45) {                   /* is a dash - */
            cpct_drawSprite(fnt_symbols[1], pvmem, FONT_W, FONT_H);
        }else if(chr == 46) {                   /* is a dot . */
            cpct_drawSprite(fnt_symbols[5], pvmem, FONT_W, FONT_H);
        }else if(chr == 47) {                   /* is a slash / */
            cpct_drawSprite(fnt_symbols[3], pvmem, FONT_W, FONT_H);
        }else if(chr == 58) {                   /* is a colon : */
            cpct_drawSprite(fnt_symbols[0], pvmem, FONT_W, FONT_H);
        }

        chr = text[++idx];
    }
}

/**
 * \brief It draws a text (of numbers) by using the numbers defined in #sprites/fonts.c
 * 
 * \param number Number to be drawn.
 * \param x Horizontal position where to draw it in the screen.
 * \param y Vertical position where to draw it in the screen.
 */
void draw_number(u16 number, u8 x, u8 y){
    const u8* chrs[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    u8 digits[6];
    i8 i = 0;

    while (number > 9) {
        digits[i] = number % 10;
        number = number / 10;
        i++;
    }

    digits[i] = number;

    for (; i > -1; i--) {
        draw_text(chrs[digits[i]], x, y);
        x = x + 2;
    }
}