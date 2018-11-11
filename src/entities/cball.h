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

#ifndef _CBALL_H_
#define _CBALL_H_

#include <types.h>

typedef struct{
    u8 x, y;            /**< X, Y position of the Cannon Ball sprite in the screen */
    u8 prevx, prevy;    /**< Previous (before next frame) X, Y position of the Cannon Ball sprite in the screen */
    u8* sprite;         /**< Sprite shown in the screen that represents the Cannon Ball */
    u8 speed;           /**< Movement speed of the Cannon. By default #CBALL_SPEED, but can be slowed by a Power Up. */
    u8 isActive;        /**< Is the Cannon Ball active (in the screen)? 0 = No, 1 = Yes */
    i8 dir;             /**< Move direction 1 = Left to Right, -1 = Right to Left */
} Cball;

void initialise_cball(Cball *cball, i8 dir);
void shoot_cball(Cball *cball, u8 x, u8 y);
u8 update_cball(Cball *cball, u8 *brickmap_active, u8* didHitBrick, u8 speedmod);
void draw_cball(Cball *cball);
void erase_cball(Cball *cball);
u16 which_brick(u8 *x, u8 *y);
u8 check_collisions(Cball *cball, u8 *brickmap_active);

#endif