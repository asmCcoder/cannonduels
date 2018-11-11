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

#ifndef _CANNON_H_
#define _CANNON_H_

#include <types.h>
#include "cball.h"
#include "pwup.h"

typedef enum { IDLE, UP, DOWN, FIRE } Actions; /**< Possible actions of a Cannon */

typedef struct{
    u8 isAI;            /**< 0 = No (player controlled), 1 or 2 = Yes (computer controlled) */
    u8 x, y;            /**< X, Y position of the Cannon in the screen */
    u8 prevx, prevy;    /**< Previous (before next frame) X,Y position of the Cannon in the screen */
    u8* sprite;         /**< Sprite shown in the screen that represents the Cannon */
    u8 speed;           /**< Movement speed of the Cannon. By default #CANNON_SPEED, but can be slowed by a Power Up. */
    u8 isShooting;      /**< Is the Cannon shooting at thus moment? 0 = No, 1 = Yes */
    u8 isHit;           /**< Has the Cannon been hit by a Cannon Ball? 0 = No, 1 = Yes */
    u8 didHitBrick;     /**< Did the Cannon Ball hit a brick? */
    u8 didHitWall;      /**< Did the Cannon Ball hit the opposite wall? */
    u16 points;         /**< Points collected. If changing u16 to something else, we need to change draw_number() in text.c */
    u8 lives;           /**< Remaining lives. Starts with #PLAYER_LIVES_INI, but can be increased by Extra Lifes */
    u16 extralife;      /**< How many points needed to get next Extra Life */
    Actions action;     /**< Current Action (Idle, move up, move down, fire) */
} Cannon;

void initialise_cannon(Cannon *cannon, u8 cannon_id, u8 isAI);
void update_cannon(Cannon *cannon, Pwup *pwup, u8 cannon_id, Cball *cballs, u8 brickmap_num);
void draw_cannon(Cannon *cannon);

#endif