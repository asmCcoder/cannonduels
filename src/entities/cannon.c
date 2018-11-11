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
#include "cannon.h"
#include "ai.h"
#include "../defines.h"
#include "../sprites/sprites.h"
#include "../entities/gamebkg.h"

/**
 * \brief Initialises (sets default values) a Cannon.
 * \param cannon Struct of the Cannon to initialise.
 * \param cannon_id ID used to identify which Cannon is (left or right).
 * \param isAI Flag that indicates if this Cannon is an AI (played by Computer) or not (played by Human).
 */
void initialise_cannon(Cannon *cannon, u8 cannon_id, u8 isAI){
    if(cannon_id == LCANNON_ID){
        cannon->x = LCANNON_X_INI;
        cannon->sprite = spr_cannon_left;
    }else if(cannon_id == RCANNON_ID){
        cannon->x = RCANNON_X_INI;
        cannon->sprite = spr_cannon_right;
    }

    cannon->isAI = isAI;
    cannon->y = (SCR_H / 2) - (CANNON_H / 2);
    cannon->speed = CANNON_SPEED;
    cannon->isShooting = 0;
    cannon->isHit = 0;
    cannon->didHitBrick = 0;
    cannon->didHitWall = 0;
    cannon->points = 0;
    if(cannon->isAI == 2){  /* 5 lives when in Demo Mode */
        cannon->lives = 5;
    }else{
        cannon->lives = PLAYER_LIVES_INI;
    }
    cannon->extralife = POINTS_EXTRALIFE;
    cannon->action = IDLE;
}

/**
 * \brief Updates the position of a Cannon in the screen and checks for Extra Life.
 * 
 * Checks which keys the player has pressed, so this function knows if 
 * the Cannon should move up, move down or fire a Cannon Ball. If a move
 * has to be done, the Y position is changed by the default speed of a
 * Cannon and the speed modification raised by a Power Up.
 * 
 * If the Cannon is an AI, #update_AI() is called to decide which action is
 * to be perfomed (move up, move down or fire a Cannon Ball).
 * 
 * If a multiple of #POINTS_EXTRALIFE is reached, the Cannon gets 1 Extra Life.
 * 
 * \param cannon Struct of the Cannon to update.
 * \param pwup Struct of the Power Ups of this Cannon.
 * \param cannon_id ID uses to identify which Cannon is (left or right).
 * \param cball Struct of the Cannon Ball of this Cannon.
 * \param brickmap_num Current brickmap number. Used to select which AI to use.
 */
void update_cannon(Cannon *cannon, Pwup *pwup, u8 cannon_id, Cball *cball, u8 brickmap_num){
    u8 ai_action = 0;
    i8 cannon_offset = 0;
    
    cpct_scanKeyboard_f();

    /* LEFT CANNON */
    if(cannon_id == LCANNON_ID){
        if(cannon->isAI){   /* Cannon is controlled by Computer */
            cannon->action = update_AI(brickmap_num, cannon, cball);
            cannon_offset = CANNON_W;
        }else{              /* Cannon is controlled by Human player */
            if(cpct_isKeyPressed(Key_A)){           /* Cannon goes Up */
                cannon->action = UP;
            }else if(cpct_isKeyPressed(Key_Z)){     /* Cannon goes Down */
                cannon->action = DOWN;
            }
            
            if(cpct_isKeyPressed(Key_X)){           /* Cannon fires */
                cannon->action = FIRE;
                cannon_offset = CANNON_W;
            }
        }
    /* RIGHT CANNON */
    }else{
        if(cannon->isAI){   /* Cannon is controlled by Computer */
            cannon->action = update_AI(brickmap_num, cannon, cball);
            cannon_offset = -CANNON_W;
        }else{              /* Cannon is controlled by Human player */
            if(cpct_isKeyPressed(Key_F1)){          /* Cannon goes Up */
                cannon->action = UP;
            }else if(cpct_isKeyPressed(Key_F0)){    /* Cannon goes Down */
                cannon->action = DOWN;
            }
            
            if(cpct_isKeyPressed(Key_FDot)){        /* Cannon fires */
                cannon->action = FIRE;
                cannon_offset = -CANNON_W;
            }
        }
    }

    switch(cannon->action){
        case UP:
            if(cannon->y > GAMEAREA_TOP){
                cannon->y -= cannon->speed + pwup->speedmod;
            }
            break;
        case DOWN:
            if(cannon->y < GAMEAREA_BOT){
                cannon->y += cannon->speed + pwup->speedmod;
            }
            break;
    }

    if(cannon->action == FIRE){
        if(cannon->isShooting == 1){
            cannon->isShooting = 0;
        }else{
            if(pwup->firemod){
                cannon->isShooting = 1;
                shoot_cball(cball, cannon->x + cannon_offset, cannon->y + CANNON_H / 2);
            }
        }
    }

    cannon->action = IDLE;

    if(cannon->points >= cannon->extralife){
        cannon->lives++;
        cannon->extralife += POINTS_EXTRALIFE;
    }
}

/**
 * \brief Re-draws a Cannon at the new X, Y position.
 * \param cannon Struct of the Cannon to update.
 */
void draw_cannon(Cannon *cannon){
    u8 w, h;

    /* Erase cannon sprite */
    w = CANNON_PXW + (cannon->prevx & 1);
    h = CANNON_PXH + (cannon->prevy & 3 ? 1 : 0);
    cpct_etm_drawTileBox2x4(cannon->prevx / 2, cannon->prevy / 4, w, h, 
                            TILE_MAP_W, CPCT_VMEM_START, gamebkg);
    cannon->prevx = cannon->x;
    cannon->prevy = cannon->y;

    /* Re-draw cannon sprite */
    cpct_drawSpriteMasked(cannon->sprite, 
                          cpct_getScreenPtr(CPCT_VMEM_START, cannon->x, cannon->y),
                          CANNON_W, CANNON_H);
}
