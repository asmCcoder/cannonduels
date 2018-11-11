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

/**
 * \file game.c
 * \author David Asta
 * \brief This file contains the functions for the scene GAME
 */

#include <stdio.h>
#include <cpctelera.h>
#include "game.h"
#include "../defines.h"
#include "../entities/text.h"
#include "../entities/cannon.h"
#include "../entities/cball.h"
#include "../entities/pwup.h"
#include "../entities/gamebkg.h"
#include "../entities/brickmaps.h"
#include "../sprites/sprites.h"
#include "../audio/audio.h"


/* Players */
Cannon lcannon;     /**< struct of the cannon at the left side (Player 1) */
Cannon rcannon;     /**< struct of the cannon at the right side (Player 2) */

/* Cannon balls */
Cball lcball;       /**< struct of the cannon balls shot by the left cannon */
Cball rcball;       /**< struct of the cannon balls shot by the left cannon */

/* Power Ups */
Pwup lpwup;         /**< struct of the left cannon's power ups */
Pwup rpwup;         /**< struct of the right cannon's power ups */

/* Bricks & Brickmaps */
u8* const bricks[BRICK_TYPES] = {   spr_brick_black,
                                    spr_brick_blue,
                                    spr_brick_brightblue,
                                    spr_brick_red,
                                    spr_brick_brightred,
                                    spr_brick_green,
                                    spr_brick_cyan,
                                    spr_brick_skyblue,
                                    spr_brick_yellow,
                                    spr_brick_white,
                                    spr_brick_orange,
                                    spr_brick_brightgreen,
                                    spr_brick_brightcyan,
                                    spr_brick_brightyellow,
                                    spr_brick_pastelyellow,
                                    spr_brick_brightwhite
                                };  /**< Types of bricks */
u8 brickmap_active[BRICKMAP_W * BRICKMAP_H];    /**< The active brickmap that is being played */
u8 brickmap_num;                                /**< Current brickmap being shown in screen */
u8 total_players;                               /**< How many players (0, 1 or 2) */
u16 total_bricks;                               /**< Total number of bricks of the current brickmap */
u8 sbrdl_lives_flicking;                        /**< Flag ON/OFF to make the Lives counter flick on Left side*/
u8 sbrdl_lives_flicker_count;                   /**< How many flicks on Left side */
u8 sbrdr_lives_flicking;                        /**< Flag ON/OFF to make the Lives counter flick on Right side*/
u8 sbrdr_lives_flicker_count;                   /**< How many flicks on Right side */

/**
 * \brief Initialises the Game scene.
 * 
 * Draws the tiles in the background,
 * calls to the initialisation of the brickmap,
 * cannon, cannon ball and power ups.
 * 
 * \param total_players How many players (0, 1 or 2).
 */
void initialise_game(u8 players){
    total_players = players;

    /* Initialise SFX. No music */
    cpct_akp_musicInit(audio_sfx);
    cpct_akp_SFXInit(audio_sfx);

    /* Initialise background. Draw tiles */
    cpct_etm_drawTilemap2x4(TILE_MAP_W, TILE_MAP_H, CPCT_VMEM_START, gamebkg);

    /* Initialise Brickmap */
    if(total_players == 0){
        /* If number of players is 0 (it is a Demo), start with a random map */
        brickmap_num = get_random_map();
    }else{
        brickmap_num = 0;
    }
    
    initialise_brickmap();

    /* Initialise Cannons */
    if(total_players == 0){         /* 0 players, then both Cannons are AI */
        initialise_cannon(&lcannon, LCANNON_ID, 2);
        initialise_cannon(&rcannon, RCANNON_ID, 2);
    }else{                          /* 1 or 2 players, then left Cannon is Human */
        initialise_cannon(&lcannon, LCANNON_ID, 0);

        if(total_players == 1){     /* 1 player, then Right Cannon is AI */
            initialise_cannon(&rcannon, RCANNON_ID, 1);
        }else{                      /* 2 player, then Right Cannon is Human */
            initialise_cannon(&rcannon, RCANNON_ID, 0);
        }
    }

    /* Initialise Cannon Balls and Power Ups */
    initialise_cball(&lcball, 1);
    initialise_pwup(&lpwup);
    initialise_cball(&rcball, -1);
    initialise_pwup(&rpwup);

    /* Draw scoreboards' texts*/
    draw_text(SBRD_POINTS, SBRD_L_TXTPOINTS_X, SBRD_L_TXTPOINTS_Y);
    draw_text(SBRD_LIVES, SBRD_L_TXTLIVES_X, SBRD_L_TXTLIVES_Y);
    draw_text(SBRD_POINTS, SBRD_R_TXTPOINTS_X, SBRD_R_TXTPOINTS_Y);
    draw_text(SBRD_LIVES, SBRD_R_TXTLIVES_X, SBRD_R_TXTLIVES_Y);
    sbrdl_lives_flicking = 0;
    sbrdl_lives_flicker_count = 0;
    sbrdr_lives_flicking = 0;
    sbrdr_lives_flicker_count = 0;
}

/**
 * \brief Updates the information that is shown in the screen meanwhile Game scene is active.
 * 
 * If any cannon lost all lives, shows game over screen.
 * If all bricks have been destroyed, loads next brickmap.
 * 
 * \return #SCENE_GAME if games must continue or #SCENE_MENU is game finished or canceled by ESC key.
 */
u8 update_game(){
    u8 bricktype;

    cpct_setBorder(HW_BLACK);

    if(lcannon.lives == 0 || rcannon.lives == 0){
        if(lcannon.isAI && rcannon.isAI){
            return SCENE_MENU;
        }else{
            return show_gameover();
        }
    }

    if(total_bricks == 0){
        if(total_players == 0){
            /* If number of players is 0 (it is a Demo), start with a random map */
            brickmap_num = get_random_map();
        }else{
            brickmap_num++;
        }

        initialise_brickmap();
    }

    /* Abort game and go back to Main Menu if ESC key is pressed */
    cpct_scanKeyboard();
    if(cpct_isKeyPressed(Key_Esc)){
        return SCENE_MENU;
    }

    update_cannon(&lcannon, &lpwup, LCANNON_ID, &lcball, brickmap_num);
    update_cannon(&rcannon, &rpwup, RCANNON_ID, &rcball, brickmap_num);

    bricktype = update_cball(&lcball, brickmap_active, &rcannon.didHitWall, lpwup.cballmod);
    if(bricktype < 99){
        cpct_akp_SFXPlay(2, 15, 80 + bricktype, 0, 0, AY_CHANNEL_B);
        lcannon.didHitBrick = 1;
        total_bricks--;
        lcannon.points += calculate_points_per_brick(bricktype) * lpwup.pointsmod;
        
        if(lpwup.isActive == 0){
            check_for_pwup(LCANNON_ID);
        }
    }else{
        lcannon.didHitBrick = 0;
    }

    bricktype = update_cball(&rcball, brickmap_active, &lcannon.didHitWall, rpwup.cballmod);
    if(bricktype < 99){
        cpct_akp_SFXPlay(2, 15, 80 + bricktype, 0, 0, AY_CHANNEL_B);
        rcannon.didHitBrick = 1;
        total_bricks--;
        rcannon.points += calculate_points_per_brick(bricktype) * rpwup.pointsmod;

        if(lpwup.isActive == 0){
            check_for_pwup(RCANNON_ID);
        }
    }else{
        rcannon.didHitBrick = 0;
    }

    update_pwup(&lpwup, gamebkg);
    update_pwup(&rpwup, gamebkg);

    /* Cannon ball reached opposite side. Did it hit opposite cannon? */
    if(lcannon.didHitWall){
        check_cannon_hit(LCANNON_ID);   
        lcannon.didHitWall = 0;
    }

    if(rcannon.didHitWall){
        check_cannon_hit(RCANNON_ID);
        rcannon.didHitWall = 0;
    }
    
    cpct_waitVSYNC();
    cpct_akp_musicPlay();

    draw_cannon(&lcannon);
    draw_cannon(&rcannon);
  
    draw_cball(&lcball);
    draw_cball(&rcball);
  
    draw_pwup(&lpwup);
    draw_pwup(&rpwup);

    draw_scoreboard();

    return SCENE_GAME;
}

/**
 * \brief Draws Scoreboards' values
 */
void draw_scoreboard(){
    draw_text("MAP:", 2, 2);
    draw_number(brickmap_num, 10, 2);
    draw_text("BRICKS:           ", SCR_W / 2, 2);
    draw_number(total_bricks, SCR_W / 2 + 15, 2);
    
    draw_number(lcannon.points, SBRD_L_NUMPOINTS_X, SBRD_L_NUMPOINTS_Y);
    draw_number(rcannon.points, SBRD_R_NUMPOINTS_X, SBRD_R_NUMPOINTS_Y);

    if(sbrdl_lives_flicker_count == 0){
        draw_number(lcannon.lives, SBRD_L_NUMLIVES_X, SBRD_L_NUMLIVES_Y);
    }else{
        if(sbrdl_lives_flicking){
            draw_text("      ", SBRD_L_NUMLIVES_X, SBRD_L_NUMLIVES_Y);
            sbrdl_lives_flicking = 0;
            sbrdl_lives_flicker_count--;
        }else{
            draw_number(lcannon.lives, SBRD_L_NUMLIVES_X, SBRD_L_NUMLIVES_Y);
            sbrdl_lives_flicking = 1;
            sbrdl_lives_flicker_count--;
        }
    }
    
    if(sbrdr_lives_flicker_count == 0){
        draw_number(rcannon.lives, SBRD_R_NUMLIVES_X, SBRD_R_NUMLIVES_Y);
    }else{
        if(sbrdr_lives_flicking){
            draw_text("      ", SBRD_R_NUMLIVES_X, SBRD_R_NUMLIVES_Y);
            sbrdr_lives_flicking = 0;
            sbrdr_lives_flicker_count--;
        }else{
            draw_number(rcannon.lives, SBRD_R_NUMLIVES_X, SBRD_R_NUMLIVES_Y);
            sbrdr_lives_flicking = 1;
            sbrdr_lives_flicker_count--;
        }
    }
}

/**
 * \brief Checks if the Cannon Ball hit the opposite Cannon.
 * 
 * \param cannon_id #LCANNON_ID or #RCANNON_ID
 */
void check_cannon_hit(u8 cannon_id){
    if(cannon_id == LCANNON_ID){
        if(rcball.x >= lcannon.x
            && rcball.y >= lcannon.y
            && rcball.y <= lcannon.y + CANNON_H){
                cpct_akp_SFXPlay(1, 15, 35, 0, 0, AY_CHANNEL_C);
                lcannon.isHit = 1;
                lcannon.lives--;
                sbrdl_lives_flicker_count = PWUP_FLICK_COUNT;
                cpct_setBorder(HW_BRIGHT_BLUE);
        }
    }else{
        if(lcball.x >= rcannon.x
            && lcball.x <= rcannon.x + CANNON_W
            && lcball.y >= rcannon.y
            && lcball.y <= rcannon.y + CANNON_H){
                cpct_akp_SFXPlay(1, 15, 35, 0, 0, AY_CHANNEL_C);
                rcannon.isHit = 1;
                rcannon.lives--;
                sbrdr_lives_flicker_count = PWUP_FLICK_COUNT;
                cpct_setBorder(HW_BRIGHT_RED);
        }
    }
}

/**
 * \brief Initialises a brickmap.
 * 
 * It uses #brickmap_num to know which brickmap to use from #brickmaps array.
 * If all brickmaps have been used, then starts by the first one again.
 * It call #draw_brickmap(), so it's drawn in the screen.
 */

void initialise_brickmap(){
    if(brickmap_num == NUMMAPS){
        brickmap_num = 0;
    }

    /* Copy new brickmap to active brickmap array, so it is shown in the screen */
    cpct_memcpy(&brickmap_active, &brickmaps[brickmap_num], BRICKMAP_W * BRICKMAP_H);

    total_bricks = bricks_in_brickmaps[brickmap_num];
    draw_brickmap();
}

/**
 * \brief Draws active brickmap to the screen.
 */
void draw_brickmap(){
    u8 x, y, bricktype;

    /* Brickmap from brickmaps.c (needs 480 bytes per map ) */
    for(y=0; y < BRICKMAP_H; y++){
        for(x=0; x < BRICKMAP_W; x++){
            bricktype = brickmap_active[y * BRICKMAP_W + x];
            if(bricktype < 99){    /* 99 indicates no brick on the map */
                cpct_drawSprite(bricks[bricktype], 
                                cpct_getScreenPtr(CPCT_VMEM_START, 
                                                  BRICKAREA_X + x * BRICK_W, 
                                                  BRICKAREA_Y + y * BRICK_H), 
                                BRICK_W, BRICK_H);
            }
        }
    }
}

/**
 * \brief Calculates how many points player gets for hitting a brick.
 * 
 * Brick type determines how many points player gets.
 * 
 * \param bricktype Which brick type has hit.
 * \return points How many points are obtained.
 */
u8 calculate_points_per_brick(u8 bricktype){
    u8 points = 0;

    if(bricktype == 0){
        points = 1;
    }else{
        points = bricktype + 1;
    }

    return points;
}

/**
 * \brief Checks if player should get a Power Up after hitting a brick.
 * 
 * The Power Up is calculated randomly.
 * It then calls #spawn_pwup to show it on screen.
 * 
 * \param cannon_id #LCANNON_ID or #RCANNON_ID 
 */
void check_for_pwup(u8 cannon_id){
    u8 random_number = cpct_rand();

    if(random_number < PWUP_TYPES * 2){
        random_number = random_number / 2;

        if(cannon_id == LCANNON_ID){
            if(lpwup.isActive == 0){
                spawn_pwup(&lpwup, &rpwup, random_number, cannon_id);
            }
        }else{
            if(rpwup.isActive == 0){
                spawn_pwup(&rpwup, &lpwup, random_number, cannon_id);
            }
        }
    }
}

/**
 * \brief Shows the Game Over screen.
 * 
 * This screen uses sprites from the game Chicago's 30 by Topo Soft,
 * which is a requirement for getting extra points in the 
 * CPCRetroDev 2018 contest.
 * 
 * It updates the High Score (if surpassed) that is shown in the Menu screen.
 * 
 * \return #SCENE_MENU So that the game will return to Menu after player has press the SPACE key.
 */
u8 show_gameover(){
    u8 str[6];

    cpct_akp_stop();

    cpct_clearScreen_f64(0x0000);

    /* nod to Chicago’s 30 by Topo Soft for CPCRetroDev 2018 */ 
    /* Left Curtain */
    cpct_drawSprite(spr_chicago30_curtain, 
                   cpct_getScreenPtr(CPCT_VMEM_START, LCURTAIN_X_INI, LCURTAIN_Y_INI),
                   CURTAIN_W, CURTAIN_H);
    /* Right Curtain */
    cpct_hflipSpriteM0(CURTAIN_W, CURTAIN_H, spr_chicago30_curtain);
    cpct_drawSprite(spr_chicago30_curtain, 
                   cpct_getScreenPtr(CPCT_VMEM_START, RCURTAIN_X_INI, RCURTAIN_Y_INI),
                   CURTAIN_W, CURTAIN_H);
    /* Cinema crowd */
    cpct_drawSprite(spr_chicago30_crowd_left, 
                   cpct_getScreenPtr(CPCT_VMEM_START, 0, SCR_H - CROWD_H),
                   CROWD_W / 2, CROWD_H);
    cpct_drawSprite(spr_chicago30_crowd_right, 
                   cpct_getScreenPtr(CPCT_VMEM_START, SCR_W / 2, SCR_H - CROWD_H),
                   CROWD_W / 2, CROWD_H);

    draw_text("GAME   OVER", 28, 20);

    if(lcannon.lives == 0){
        draw_text("BLUE PLAYER  DEAD", 24, 40);
    }else{
        draw_text("RED PLAYER DEAD", 24, 40);
    }

    draw_text("BLUE PLAYER", 12, 80);
    sprintf(str, "%3u", lcannon.points);
    draw_text(str, 16, 100);

    draw_text("RED PLAYER", 48, 80);
    sprintf(str, "%3u", rcannon.points);
    draw_text(str, 50, 100);

    if(lcannon.points > highscore){
        highscore = lcannon.points;
    }

    if(rcannon.points > highscore){
        highscore = rcannon.points;
    }

    draw_text("PRESS SPACE TO CONTINUE", 17, 145);

    /* Wait until SPACE is pressed */
    do{
        cpct_scanKeyboard();
    }while(!cpct_isKeyPressed(Key_Space));

    return SCENE_MENU;
}

/**
 * \brief Selects a random map number
 * 
 * It is used If number of players is 0 (it is a Demo),
 * to start with a random map
 * 
 * \return random_number A random number between 0 and NUMMAPS
 */
u8 get_random_map(){
    u8 random_number = cpct_rand() / NUMMAPS;

    if(random_number >= NUMMAPS){
        random_number = NUMMAPS - 1;
    }

    return random_number;
}