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

#ifndef _DEFINES_H_
#define _DEFINES_H_

#define HIGHSCORE               6128    /**< Initial High Score shown in the Menu */
#define POINTS_EXTRALIFE        464     /**< How many points to get 1 extra life */
#define DEMO_TIMER              3000    /**< How long until triggering Demo play if nothing happens at Menu*/

/* Screen */
#define SCR_MODE                0       /**< Mode 0 (160x200, 16 colours) */
#define SCR_W                   80      /**< Screen width (in bytes) */
#define SCR_H                   200     /**< Screen height (in bytes) */
#define GAMEAREA_TOP            24      /**< Top pixel of the game area (area where the cannons move) */
#define GAMEAREA_BOT            159     /**< Bottom pixel of the game area (area where the cannons move) */

/* FONT */
#define FONT_TOTAL_LETTERS      26      /**< Total number of letters */
#define FONT_TOTAL_NUMBERS      10      /**< Total number of numbers */
#define FONT_TOTAL_SYMBOLS      6       /**< Total number of symbols */
#define FONT_W                  2       /**< Font letter width */
#define FONT_H                  8       /**< Font letter heigth */

/* Tilemaps */
#define TILE_W                  2       /**< Tile width (in bytes) */
#define TILE_H                  4       /**< Tile height (in bytes) */
#define TILE_MAP_W              40      /**< Map width in tiles */
#define TILE_MAP_H              50      /**< Map height in tiles */

/* Brickmaps */
#define NUMMAPS                 15      /**< Total number of brickmaps */
#define BRICKAREA_X             24      /**< X coordinate where the bricks start to be painted */
#define BRICKAREA_Y             40      /**< Y coordinate where the bricks start to be painted */
#define BRICKMAP_W              16      /**< Number of brickarea in tiles */
#define BRICKMAP_H              30      /**< Number of brickarea in tiles */
#define BRICKAREA_TL            BRICKAREA_X                             /**< Top Left corner */
#define BRICKAREA_TR            BRICKAREA_X + BRICKMAP_H                /**< Top Right corner */
#define BRICKAREA_BL            BRICKAREA_Y                             /**< Bottom Left corner */
#define BRICKAREA_BR            BRICKAREA_Y + BRICKMAP_H * BRICK_H      /**< Bottom Right corner */

/* Bricks */
#define BRICK_W                 2       /**< Brick width in bytes */
#define BRICK_H                 4       /**< Brick height in bytes */
#define BRICK_W_TILES           1       /**< Brick width in tiles */
#define BRICK_H_TILES           1       /**< Brick height in tiles */
#define BRICK_TYPES             16      /**< Types (colours) of different bricks */

/* Scenes */
#define SCENE_MENU              0       /**< Main Menu */
#define SCENE_GAME              1       /**< Game */
#define SCENE_DEMO              2       /**< Demo play */

/* Scoreboards */
#define SBRD_POINTS             "POINTS: "  /**< Text to be drawn in the screen for the Points */
#define SBRD_LIVES              "LIVES: "   /**< text to be drawn in the screen for the Lives */
#define SBRD_L_PWUP_X           1                                   /**< X position in the screen for the Left Power Up */
#define SBRD_L_PWUP_Y           SBRD_L_TXTPOINTS_Y + 0              /**< Y position in the screen for the Left Power Up */
#define SBRD_L_TXTPOINTS_X      8                                   /**< X position in the screen for the Left Points text #SBRD_POINTS */
#define SBRD_L_TXTPOINTS_Y      182                                   /**< Y position in the screen for the Left Points text #SBRD_POINTS */
#define SBRD_L_TXTLIVES_X       SBRD_L_TXTPOINTS_X + 2              /**< X position in the screen for the Left Lives text #SBRD_LIVES */
#define SBRD_L_TXTLIVES_Y       SBRD_L_TXTPOINTS_Y + FONT_H + 1     /**< Y position in the screen for the Left Lives text #SBRD_LIVES */
#define SBRD_L_NUMPOINTS_X      SBRD_L_TXTPOINTS_X + FONT_W * 8     /**< X position in the screen for the Left Points. 8 is the number of characters in the title #SBRD_POINTS */
#define SBRD_L_NUMPOINTS_Y      SBRD_L_TXTPOINTS_Y                  /**< Y position in the screen for the Left Points. */
#define SBRD_L_NUMLIVES_X       SBRD_L_TXTPOINTS_X + FONT_W * 8     /**< X position in the screen for the Left Lives. 8 is the number of characters in the title #SBRD_LIVES */
#define SBRD_L_NUMLIVES_Y       SBRD_L_TXTLIVES_Y                   /**< Y position in the screen for the Left Lives. */
#define SBRD_R_PWUP_X           45                                  /**< X position in the screen for the Left Power Up sprite. */
#define SBRD_R_PWUP_Y           SBRD_R_TXTPOINTS_Y + 0              /**< Y position in the screen for the Left Power Up sprite. */
#define SBRD_R_TXTPOINTS_X      52                                  /**< X position in the screen for the Right Points text #SBRD_POINTS */
#define SBRD_R_TXTPOINTS_Y      182                                 /**< Y position in the screen for the Right Points text #SBRD_POINTS */
#define SBRD_R_TXTLIVES_X       SBRD_R_TXTPOINTS_X + 2              /**< X position in the screen for the Right Lives text #SBRD_LIVES */
#define SBRD_R_TXTLIVES_Y       SBRD_R_TXTPOINTS_Y + FONT_H + 1     /**< Y position in the screen for the Right Lives text #SBRD_LIVES */
#define SBRD_R_NUMPOINTS_X      SBRD_R_TXTPOINTS_X + FONT_W * 8     /**< X position in the screen for the Right Points. 8 is the number of characters in the title #SBRD_POINTS */
#define SBRD_R_NUMPOINTS_Y      SBRD_R_TXTPOINTS_Y                  /**< Y position in the screen for the Right Points. */
#define SBRD_R_NUMLIVES_X       SBRD_R_TXTPOINTS_X + FONT_W * 8     /**< X position in the screen for the Right Lives. 8 is the number of characters in the title #SBRD_LIVES */
#define SBRD_R_NUMLIVES_Y       SBRD_R_TXTLIVES_Y                   /**< Y position in the screen for the Left Lives. */

/* Players (cannons) */
#define CANNON_W                2       /**< Cannon width in bytes */
#define CANNON_H                16      /**< Cannon heigth in bytes */
#define CANNON_PXW              1       /**< Cannon sprite width in pixels (4 / 4) */
#define CANNON_PXH              4       /**< Cannon sprite height in pixels (16 / 4) */
#define LCANNON_ID              1       /**< ID of Left Cannon */
#define LCANNON_X_INI           0       /**< Starting X position of Left Cannon */
#define RCANNON_ID              2       /**< ID of Right Cannon */
#define RCANNON_X_INI           78      /**< Starting X position of Right Cannon */
#define CANNON_MAX_PWUPS        1       /**< Max. power ups that can be active per cannon */
#define CANNON_SPEED            3       /**< Default speed */
#define PLAYER_LIVES_INI        3       /**< Default number of lives at start */

/* Cannon balls */
#define CBALL_W                 1       /**< Cannon ball width in bytes */
#define CBALL_H                 2       /**< Cannon ball heigth in bytes */
#define CBALL_SPEED             2       /**< Cannon ball speed */
#define CBALL_PXW               1       /**< Cannon ball sprite width in pixels (3 / 4, rounded up) */
#define CBALL_PXH               1       /**< Cannon ball sprite height in pixels (3 / 4, rounded up) */

/* Power Ups */
#define PWUP_TYPES              6       /**< Different types of Power Ups available */
#define PWUP_TIMER              150     /**< How long the Power Up is active */
#define PWUP_FLICK_COUNT        30      /**< How long the lives flick, to indicate that a live has been lost */
#define PWUP_W                  7       /**< Power Up width in bytes */
#define PWUP_H                  14      /**< Power Up heigth in bytes */
#define PWUP_PXW                3       /**< Power Up sprite width in pixels (14 / 4, rounded up) */
#define PWUP_PXH                3       /**< Power Up sprite height in pixels (14 / 4, rounded up) */
#define LPWUP_ID                1       /**< ID of Left Power Up */
#define RPWUP_ID                2       /**< ID of Right Power Up */

/* Chicago's 30 nod */
#define CURTAIN_W               11                  /**< Width of the Curtain sprite */
#define CURTAIN_H               159                 /**< Height of the Curtain sprite */
#define LCURTAIN_X_INI          0                   /**< X position of the Left Curtain sprite */
#define LCURTAIN_Y_INI          0                   /**< Y position of the Left Curtain sprite */
#define RCURTAIN_X_INI          SCR_W - CURTAIN_W   /**< X position of the Right Curtain sprite */
#define RCURTAIN_Y_INI          0                   /**< Y position of the Right Curtain sprite */
#define CROWD_W                 80                  /**< Width of the Crowd sprite */
#define CROWD_H                 40                  /**< Height of the Crowd sprite */
#define CROWD_X_INI             0                   /**< X position of the Crowd sprite */
#define CROWD_Y_INI             SCR_H - CROWD_H     /**< Y position of the Crowd sprite */

/* Music and SFX */
#define AUDIO_MUSIC_ADDRESS     0x0040
#define AUDIO_MUSIC_SIZE        397
#define AUDIO_MUSIC_END         0x01CC
#define AUDIO_SFX_ADDRESS       0x01CD
#define AUDIO_SFX_SIZE          210
#define AUDIO_SFX_END           0x29E

#endif