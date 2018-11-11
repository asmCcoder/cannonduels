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
#include "defines.h"
#include "sprites/sprites.h"
#include "sprites/tiles.h"
#include "scenes/menu.h"
#include "scenes/game.h"


/* Firmware Colours: 0 1 2 3 6 9 10 11 12 13 15 18 20 24 25 26
    FW  Name            HW      RGB
     0  Black           54h       0   0   0
     1  Blue            44h       0   0  50
     2  Bright Blue     55h       0   0 100
     3  Red             5Ch      50   0   0
     6  Bright Red      4Ch     100   0   0
     9  Green           56h       0  50   0
    10  Cyan            46h       0  50  50
    11  Sky Blue        57h       0  50 100
    12  Yellow          5Eh      50  50   0
    13  White           40h      50  50  50
    15  Orange          4Eh     100  50   0
    18  Bright Green    52h       0 100   0
    20  Bright Cyan     53h       0 100 100
    24  Bright Yellow   4Ah     100 100   0
    25  Pastel Yellow   43h     100 100  50
    26  Bright White    4Bh     100 100 100
*/
const u8 game_palette[16] = { 0x54, 0x44, 0x55, 0x5c, 0x4c, 0x56, 0x46, 0x57,
                              0x5e, 0x40, 0x4e, 0x52, 0x53, 0x4a, 0x43, 0x4b }; /**< The (Hardware) palette used by this game */

u8 num_players; /**< How many player will playing (0 = Demo, 1 = Player vs Computer, 2 = Player vs Player) */
u16 highscore;  /**< Highest score */


/**
 * \brief Initialises the CPC so that it's ready for the game.
 * 
 * disables firmware, sets the video mode to 0, 
 * sets border colour to 1st colour in the palette,
 * sets palette and sets tileset pointers
 */
void initialise_cpc(){
    cpct_disableFirmware();
    cpct_setVideoMode(SCR_MODE);
    cpct_setBorder(game_palette[0]);
    cpct_setPalette(game_palette, 16);    
    cpct_etm_setTileset2x4(tiles_tileset);
}

/**
 * \brief Initialises a scene before it can be shown on the screen.
 */ 
void initialise_scene(u8 scene){
    if(scene == SCENE_MENU){
        initialise_menu();
    }else if(scene == SCENE_GAME){
        if(num_players > 0){    /* To avoid double initialisation of Game,
                                 * as Demo already calls  initialise_game() 
                                 */
            initialise_game(num_players);
        }
    }else if(scene == SCENE_DEMO){
        initialise_game(0);
    }
}

/**
 * \brief Main function.
 * 
 * It calls the initializations and contains the main loop for the game.
 * Everything goes through this loop. Each time a scene is updated, it
 * comes back here and decides which scene should be shown next. 
 */
void main(){
    u8 scene_current = SCENE_MENU;
    u8 scene_next = scene_current;
    highscore = HIGHSCORE;

    initialise_cpc();
    initialise_scene(scene_current);

    while (1){
        if(scene_current == SCENE_MENU){
            scene_next = update_menu(&num_players);
        }else if(scene_current == SCENE_GAME){
            scene_next = update_game();
        }else if(scene_current == SCENE_DEMO){
            scene_next = update_game();
        }

        if(scene_next != scene_current){
            scene_current = scene_next;
            initialise_scene(scene_current);
        }
    }
}

