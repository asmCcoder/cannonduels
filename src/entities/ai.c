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

#include <stdio.h>
#include <cpctelera.h>
#include "../defines.h"
#include "ai.h"

/**
 * \brief Calls the different levels of AI depending on the current brickmap number.
 * 
 * \param brickmap_num Number of the current brickmap. Used to decide which AI to use. The higher the number, the less dumb AI. 
 * \param cannon Struct of the Cannon using AI.
 * \param cball Struct of the Cball fired by this Cannon.
 * \return Action to be updated in screen (Idle, Move Up, Move Down, Fire).
 */
u8 update_AI(u8 brickmap_num, Cannon *cannon, Cball *cball){
    if(cannon->isAI == 2){  /* Is a Demo. Use advance AI */
        return advanced_AI(cannon, cball); 
    }else{  /* Is NOT a Demo. Use dumbest AIs on 1st map only. Then Advanced AI  */
        if(brickmap_num == 1){
            return simple_AI(cannon, cball);
        }else{
            return advanced_AI(cannon, cball);
        }
    }
}

/**
 * \brief dumb-ish AI.
 * 
 * This AI checks if the Cannon Ball hit any brick in the current 
 * X position. If not, this means there are no more bricks left
 * in this row, so the AI moves to another row.
 * 
 * It's quite easy to beat this AI, as it doesn't move away when 
 * it gets shot.
 * 
 * \param cannon Struct of the Cannon to get an AI action for.
 * \param cball Struct of the Cball of the Cannon being updated.
 * \return Action to be updated in screen (Idle, Move Up, Move Down, Fire).
 */

u8 simple_AI(Cannon *cannon, Cball *cball){
    u8 random_number;
    u8 action = 0;

    if(cball->isActive == 0){
        if(cannon->didHitBrick){
            /* There more bricks, so continue firing */
            cannon->didHitBrick = 0;
            action = 3;
        }else{
            /* No bricks left. Move to another row */
            random_number = cpct_rand();

            if(random_number <= 33){
                action = 1;   /* Up */
            }else if(random_number <= 66){
                action = 2;   /* Down */
            }else{
                action = 3;   /* Fire */
            }
        }
    }

    return action;
}

/**
 * \brief A more advanced dumb-ish AI.
 * 
 * This AI checks if the Cannon Ball hit any brick in the current 
 * X position. If not, this means there are no more bricks left
 * in this row, so the AI moves to another row.
 * 
 * It also checks if the Cannon has been hit by a Cannon Ball, in
 * which case moves away from that position.
 * 
 * \param cannon Struct of the Cannon to get an AI action for.
 * \param cball Struct of the Cball of the Cannon being updated.
 * \return Action to be updated in screen (Idle, Move Up, Move Down, Fire).
 */
u8 advanced_AI(Cannon *cannon, Cball *cball){
    u8 random_number;
    u8 action = 0;

    /* Cannon was hit? Then, move away */
    if(cannon->isHit){
        cannon->isHit = 0;
        random_number = cpct_rand();

        if(random_number <= 50){
            action = 1;   /* Up */
        }else{
            action = 2;   /* Down */
        }
    }

    if(cball->isActive == 0){
        if(cannon->didHitBrick){
             /* There more bricks, so continue firing */
            cannon->didHitBrick = 0;
           
            action = 3;        /* Fire */
        }else{
            /* No bricks left. Move to another row */
            random_number = cpct_rand();

            if(random_number <= 85){
                action = 1;   /* Up */
            }else if(random_number <= 170){
                action = 2;   /* Down */
            }else{
                action = 3;   /* Fire */
            }
        }
    }

    return action;
}
