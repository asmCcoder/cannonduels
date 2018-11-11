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
#include "cball.h"
#include "../defines.h"
#include "../sprites/sprites.h"
#include "../entities/gamebkg.h"

/**
 * \brief Initialises (sets default values) a Cannon Ball.
 * \param cball Struct of the Cannon Ball to initialise.
 * \param dir Direction the Cannon Ball moves (left to right, or right to left).
 */ 
void initialise_cball(Cball *cball, i8 dir){
    cball->x = 0;
    cball->y = 0;
    cball->prevx = 0;
    cball->prevy = 0;
    cball->sprite = spr_cball;
    cball->speed = CBALL_SPEED;
    cball->isActive = 0;
    cball->dir = dir;
}

/**
 * \brief Instantiates a Cannon Ball from the Cannon current position.
 * \param cball Struct of the Cannon Ball to instantiate.
 * \param x Current horizontal position of the Cannon.
 * \param y Current vertical position of the Cannon.
 */
void shoot_cball(Cball *cball, u8 x, u8 y){
    if(cball->isActive == 0){
        cpct_akp_SFXPlay(3, 15, 20, 0, 0, AY_CHANNEL_A);
        cball->isActive = 1;
        cball->x = x;
        cball->y = y;
    }
}

/**
 * \brief Updates the position of a Cannon Ball and erases it if it has reach the other side of the screen.
 * 
 * Meanwhile a Cannon Ball is active (shown on the screen), this funcion updates its position,
 * using the default speed of cannon balls and the speed modification of a Power Up.
 * 
 * Once a Cannon Ball reaches the other side of the screen, it erases the ball. Otherwise,
 * it checks if it collided with a brick, by calling #check_collisions().
 * 
 * \param cball Struct of the Cannon Ball to update.
 * \param brickmap_active Active brickmap. Not really used here. Just for passing it to #check_collisions().
 * \param didHitWall If a Cannon Ball reaches the other side of the screen, this flag is activated.
 * \param speedmod Value for the speed modification raised by a Power Up.
 * \return bricktype Which type of Brick has been hit. This is returned by #check_collisions().
 */
u8 update_cball(Cball *cball, u8 *brickmap_active, u8* didHitWall, u8 speedmod){
    u8 bricktype;
    bricktype = 99;

    if(cball->isActive){
        cball->prevx = cball->x;
        cball->prevy = cball->y;

        cball->x += (cball->speed - speedmod) * cball->dir;

        if(cball->x > SCR_W - CBALL_W || cball->x == CBALL_W){
            /* Ball arrived to the opposite side */
            cball->isActive = 0;
            erase_cball(cball);
            *didHitWall = 1;
        }else{
            bricktype = check_collisions(cball, brickmap_active);
        }
    }

    return bricktype;
}

/**
 * \brief Re-draws a Cannon Ball at the new #Cball X, Y position.
 * \param cball Struct of the Cannon Ball to re-draw.
 */
void draw_cball(Cball *cball){
    if(cball->isActive){
        erase_cball(cball);

        /* Re-draw cannon ball sprite */;
        cpct_drawSpriteMasked(cball->sprite, 
                                cpct_getScreenPtr(CPCT_VMEM_START, cball->x, cball->y),
                                CBALL_W, CBALL_H);
    }
}

/**
 * \brief Erases a Cannon Ball sprite.
 * \param cball Struct of the Cannon Ball to erase.
 */
void erase_cball(Cball *cball){
    /* Erase cannon ball sprite */
    cpct_etm_drawTileBox2x4(cball->prevx / 2, (cball->prevy) / 4, 
                            CBALL_PXW, CBALL_PXH, TILE_MAP_W, CPCT_VMEM_START, 
                            gamebkg);
}

/**
 * \brief Calculates which Brick has been hit.
 * 
 * Surely there is a better way of doing this!!! But I don't know how... yet.
 * 
 * \param x Horizontal position of the Cannon Ball. It is a pointer, so it can be changed.
 * \param y Vertical position of the Cannon Ball. It is a pointer, so it can be changed.
 * \return The number of the Brick that was hit by the Cannon Ball.
 */
u16 which_brick(u8 *x, u8 *y){
    u16 brickofbricks, temp, diff;

    *x = *x / TILE_W;
    *y = *y / TILE_H;
    brickofbricks = *y * TILE_MAP_W + *x;
   
    temp = brickofbricks - 412;
    diff = 0;

    if(temp <= 15){
        diff = 0;
    }else if(temp >= 40 && temp <= 55){
        diff = 24;
    }else if(temp >= 80 && temp <= 95){
        diff = 48;
    }else if(temp >= 120 && temp <= 135){
        diff = 72;
    }else if(temp >= 160 && temp <= 175){
        diff = 96;
    }else if(temp >= 200 && temp <= 215){
        diff = 120;
    }else if(temp >= 240 && temp <= 255){
        diff = 144;
    }else if(temp >= 280 && temp <= 295){
        diff = 168;
    }else if(temp >= 320 && temp <= 335){
        diff = 192;
    }else if(temp >= 360 && temp <= 375){
        diff = 216;
    }else if(temp >= 400 && temp <= 415){
        diff = 240;
    }else if(temp >= 440 && temp <= 455){
        diff = 264;
    }else if(temp >= 480 && temp <= 495){
        diff = 288;
    }else if(temp >= 520 && temp <= 535){
        diff = 312;
    }else if(temp >= 560 && temp <= 575){
        diff = 336;
    }else if(temp >= 600 && temp <= 615){
        diff = 360;
    }else if(temp >= 640 && temp <= 655){
        diff = 384;
    }else if(temp >= 680 && temp <= 695){
        diff = 408;
    }else if(temp >= 720 && temp <= 735){
        diff = 432;
    }else if(temp >= 760 && temp <= 775){
        diff = 456;
    }else if(temp >= 800 && temp <= 815){
        diff = 480;
    }else if(temp >= 840 && temp <= 855){
        diff = 504;
    }else if(temp >= 880 && temp <= 895){
        diff = 528;
    }else if(temp >= 920 && temp <= 935){
        diff = 552;
    }else if(temp >= 960 && temp <= 975){
        diff = 576;
    }else if(temp >= 1000 && temp <= 1015){
        diff = 600;
    }else if(temp >= 1040 && temp <= 1055){
        diff = 624;
    }else if(temp >= 1080 && temp <= 1095){
        diff = 648;
    }else if(temp >= 1120 && temp <= 1135){
        diff = 672;
    }else if(temp >= 1160 && temp <= 1175){
        diff = 696;
    }else{
        temp = 0;
    }

    return temp - diff;
}

/**
 * \brief Checks if a Cannon Ball has hit a Brick. If so, deletes the sprite from the screen.
 * \param cball Cannon Ball to check against Bricks.
 * \param brickmap_active Active brickmap, so the functions knows where the bricks are located.
 * \return bricktype Which type of Brick has been hit.
 */
u8 check_collisions(Cball *cball, u8 *brickmap_active){
    u8 x, y, bricktype;
    u16 brick = 0;

    x, y = 0;
    bricktype = 99;

    /* is the Ball inside the brickarea? */
    if(cball->x >= BRICKAREA_TL          /* Top Left corner */
        && cball->x <= BRICKAREA_TR      /* Top Right corner */
        && cball->y >= BRICKAREA_BL      /* Bottom Left corner */
        && cball->y <= BRICKAREA_BR){    /* Bottom Right corner */
            /* Store the values in temp variable, because we will overwrite it to get the brick number */
            x = cball->prevx;
            y = cball->prevy;
            brick = which_brick(&x, &y);

            bricktype = brickmap_active[brick];
            if(bricktype < 99){    /* 99 indicates no brick on the map */
                /* Ball has hit a brick */
                cball->isActive = 0;
                erase_cball(cball);

                /* Erase Brick */
                cpct_etm_drawTileBox2x4(x, y, BRICK_W_TILES, BRICK_H_TILES, 
                                        TILE_MAP_W, CPCT_VMEM_START, gamebkg);

                /* Deactivate the brick */
                brickmap_active[brick] = 99;
            }
 
    }

    return bricktype;
}


