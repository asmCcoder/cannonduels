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
#include "pwup.h"
#include "../defines.h"
#include "../sprites/sprites.h"

u8* const pwups_sprites[PWUP_TYPES] = { spr_pwup_dp,            /**< Double Points */
                                        spr_pwup_tp,            /**< Triple Points */
                                        spr_pwup_slow,          /**< Cannon slow speed */
                                        spr_pwup_freeze,        /**< Cannon cannot move */
                                        spr_pwup_jam,           /**< Cannon cannot fire */
                                        spr_pwup_slowcball      /**< Cannon Ball slow speed */
                                    };


/**
 * \brief Initialises (sets default values) a Power Up.
 * \param pwup Struct of the Power Up to initialise.
 */ 
void initialise_pwup(Pwup *pwup){
    pwup->isActive = 0;
    pwup->triggerBy = 0;
    pwup->speedmod = 0;
    pwup->pointsmod = 1;
    pwup->firemod = 1;
    pwup->cballmod = 0;
}

/**
 * \brief Spawn specific Power Up
 * 
 * Which Power Up is to be spawn is received by the param mod.
 * This mod is a random number generated at #check_for_pwup().
 * 
 * The function is called for each cannon and may activate (spawn)
 * a Power Up for either the Cannon that is calling (own) or the
 * other Cannon (oppo).
 * 
 * \param own_pwup Struct of the Power Ups of the Cannon (own) that is calling this function. 
 * \param oppo_pwup Struct of the Power Ups of the opposite Cannon.
 * \param mod Random number generated that will decide which Power Up is activated (spawn).
 * \param cannon_id Which Cannon is activated the Power Up?
 */
void spawn_pwup(Pwup *own_pwup, Pwup *oppo_pwup, u8 mod, u8 cannon_id){
    u8 isOwn = 0;

    own_pwup->isActive = 1;
    own_pwup->triggerBy = 0;
    own_pwup->sprite = pwups_sprites[mod];
    own_pwup->timer = PWUP_TIMER;

    switch(mod){
        case 0: /**< Double Points */
            own_pwup->pointsmod = 2;
            isOwn = 1;
            break;
        case 1: /**< Triple Points */
            own_pwup->pointsmod = 3;
            isOwn  =1;
            break;
        case 2: /**< Cannon slow speed */
            oppo_pwup->speedmod = -2;
            oppo_pwup->isActive = 1;
            oppo_pwup->triggerBy = 1;
            oppo_pwup->timer = PWUP_TIMER;
            break;
        case 3: /**< Cannon cannot move */
            oppo_pwup->speedmod = -3;
            oppo_pwup->isActive = 1;
            oppo_pwup->triggerBy = 1;
            oppo_pwup->timer = PWUP_TIMER;
            break;
        case 4: /**< Cannon cannot fire */
            oppo_pwup->firemod = 0;
            oppo_pwup->isActive = 1;
            oppo_pwup->triggerBy = 1;
            oppo_pwup->timer = PWUP_TIMER;
            break;
        case 5: /**< Cannon Ball slow speed */
            oppo_pwup->cballmod = 1;
            oppo_pwup->isActive = 1;
            oppo_pwup->triggerBy = 1;
            oppo_pwup->timer = PWUP_TIMER;
            break;
    }

    /* Power Up is shown in the scoreboard area of the Cannon that is affected */
    if(cannon_id == LCANNON_ID){
        if(isOwn){
            own_pwup->x = SBRD_L_PWUP_X;
            own_pwup->y = SBRD_L_PWUP_Y;
        }else{
            own_pwup->x = SBRD_R_PWUP_X;
            own_pwup->y = SBRD_R_PWUP_Y;
        }
    }else{
        if(isOwn){
            own_pwup->x = SBRD_R_PWUP_X;
            own_pwup->y = SBRD_R_PWUP_Y;
        }else{
            own_pwup->x = SBRD_L_PWUP_X;
            own_pwup->y = SBRD_L_PWUP_Y; 
        }
    }
}

/**
 * \brief Uses a timer to check if Power Up should be deactivated and its sprite removed from the screen.
 * 
 * \param pwup Struct of the Power Up to update.
 * \param scrtiles Tiles representing the background image.
 */
void update_pwup(Pwup *pwup, u8 *scrtiles){
    if(pwup->isActive){
        pwup->timer--;

        if(pwup->timer <= 0){
            initialise_pwup(pwup);

            if(pwup->triggerBy == 0){
                /**< If it was trigger by own cannon, then there was a sprite shown */
                /**< Erase sprite */
                cpct_etm_drawTileBox2x4(pwup->x / 2, (pwup->y) / 4, PWUP_PXW + 1, PWUP_PXH + 1, 
                                        TILE_MAP_W, CPCT_VMEM_START, scrtiles);
            }
        }
    }
}

/**
 * \brief Draws sprite representing the Power Up.
 * \param pwup Struct of the Power Up to be drawn.
 */
void draw_pwup(Pwup *pwup){
    if(pwup->isActive){
        if(pwup->triggerBy == 0){
            /**< If it was trigger by own cannon, then there was a sprite shown */
            cpct_drawSprite(pwup->sprite, 
                            cpct_getScreenPtr(CPCT_VMEM_START, pwup->x, pwup->y), 
                            PWUP_W, PWUP_H);
        }
    }
}
