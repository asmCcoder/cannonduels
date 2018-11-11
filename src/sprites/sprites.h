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

#ifndef _SPRITES_H_
#define _SPRITES_H_

#include <types.h>
#include "defines.h"

/*
 * -------------------------- CANNONS --------------------------
 */
extern const u8 spr_cannon_left[64];
extern const u8 spr_cannon_right[64];

/*
 * -------------------------- BRICKS --------------------------
 */
extern const u8 spr_brick_black[BRICK_W * BRICK_H];
extern const u8 spr_brick_blue[BRICK_W * BRICK_H];
extern const u8 spr_brick_brightblue[BRICK_W * BRICK_H];
extern const u8 spr_brick_red[BRICK_W * BRICK_H];
extern const u8 spr_brick_brightred[BRICK_W * BRICK_H];
extern const u8 spr_brick_green[BRICK_W * BRICK_H];
extern const u8 spr_brick_cyan[BRICK_W * BRICK_H];
extern const u8 spr_brick_skyblue[BRICK_W * BRICK_H];
extern const u8 spr_brick_yellow[BRICK_W * BRICK_H];
extern const u8 spr_brick_white[BRICK_W * BRICK_H];
extern const u8 spr_brick_orange[BRICK_W * BRICK_H];
extern const u8 spr_brick_brightgreen[BRICK_W * BRICK_H];
extern const u8 spr_brick_brightcyan[BRICK_W * BRICK_H];
extern const u8 spr_brick_brightyellow[BRICK_W * BRICK_H];
extern const u8 spr_brick_pastelyellow[BRICK_W * BRICK_H];
extern const u8 spr_brick_brightwhite[BRICK_W * BRICK_H];

/*
 * -------------------------- CANNONBALLS --------------------------
 */
extern const u8 spr_cball[12];

/*
 * -------------------------- POWER UPS --------------------------
 */

extern const u8 spr_pwup_dp[PWUP_W * PWUP_H];
extern const u8 spr_pwup_tp[PWUP_W * PWUP_H];
extern const u8 spr_pwup_slow[PWUP_W * PWUP_H];
extern const u8 spr_pwup_freeze[PWUP_W * PWUP_H];
extern const u8 spr_pwup_jam[PWUP_W * PWUP_H];
extern const u8 spr_pwup_slowcball[PWUP_W * PWUP_H];

/*
 * ---------------- CAR from Chicago's 30 ------------------
 * nod to Chicago’s 30 de Topo Soft for CPCRetroDev 2018
 */

extern const u8 spr_chicago30_crowd_left[1600];
extern const u8 spr_chicago30_crowd_right[1600];
extern const u8 spr_chicago30_curtain[1749];

#endif