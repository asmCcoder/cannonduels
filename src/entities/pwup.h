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

#ifndef _PWUP_H_
#define _PWUP_H_

#include <types.h>

typedef struct{
    u8 x, y;        /**< X, Y position of the Power Up sprite in the screen */
    u8* sprite;     /**< Sprite shown in the screen that represents the Power Up */
    u8 isActive;    /**< Is the Power Up currently active? 0 = No, 1 = Yes */
    u8 triggerBy;   /**< Who triggered it? 0 = own cannon, 1 = other cannon */
    u8 timer;       /**< For how long the Power Up will be active? */
    /* Modifiers */
    i8 speedmod;    /**< Cannon speed modifier (adds to Cannon speed) */
    u8 pointsmod;   /**< Points multiplier (multiplies to points) */
    u8 firemod;     /**< Cannon shoot modifier (Can Cannon fire? 0 = No, 1 = Yes) */
    u8 cballmod;    /**< Cannon Ball speed modifier (adds to Cannon Ball speed) */
} Pwup;

void initialise_pwup(Pwup *pwup);
void update_pwup(Pwup *pwup, u8 *scrtiles);
void draw_pwup(Pwup *pwup);
void spawn_pwup(Pwup *own_pwup, Pwup *oppo_pwup, u8 mod, u8 cannon_id);

#endif