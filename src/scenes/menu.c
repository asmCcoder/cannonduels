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
#include "menu.h"
#include "../defines.h"
#include "../entities/text.h"
#include "../audio/audio.h"
#include "../sprites/logo.h"
#include "../sprites/footer.h"

u16 demotimer;      /**< A timer to trigger the demo, if player doesn't do anything for a certain amount of time in the Menu screen */

/**
 * \brief Initialises the Menu scene
 * 
 * Starts music,
 * clears screen,
 * draws the logos and text.
 */
void initialise_menu(){
    u8 str[6];

    demotimer = DEMO_TIMER;

    cpct_akp_musicInit(audio_music);

    cpct_clearScreen_f64(0x0000);

    /* Logo */
    cpct_drawSprite(spr_logo_0, cpctm_screenPtr(CPCT_VMEM_START,  0, 0), SPR_LOGO_0_W, SPR_LOGO_0_H);
    cpct_drawSprite(spr_logo_1, cpctm_screenPtr(CPCT_VMEM_START, 40, 0), SPR_LOGO_1_W, SPR_LOGO_1_H);

    /* Options */
    draw_text("1) 1 PLAYER", 30, 120);
    draw_text("2) 2 PLAYERS", 30, 130);

    /* High Score */
    draw_text("HIGH SCORE", 20, 150);
    sprintf(str, "%3u", highscore);
    draw_text(str, 45, 150);

    /* Footer */
    cpct_drawSprite(spr_footer_0, cpctm_screenPtr(CPCT_VMEM_START,  0, SCR_H - SPR_FOOTER_0_H), SPR_FOOTER_0_W, SPR_FOOTER_0_H);
    cpct_drawSprite(spr_footer_1, cpctm_screenPtr(CPCT_VMEM_START, 40, SCR_H - SPR_FOOTER_1_H), SPR_FOOTER_1_W, SPR_FOOTER_1_H);
}

/**
 * \brief Updates the information that is shown in the screen meanwhile the Menu scene is active.
 * 
 * After certain amount of inactivity, it triggers the demo (basically a 0 players Computer vs Computer game.
 * It scans keyboard to get number of players, and stores it in #num_players.
 * 
 * \param num_players A pointer to the global variable that will contain the number of selected players.
 * \return Next scene to be shown (#SCENE_GAME, #SCENE_MENU or #SCENE_DEMO).
 */
u8 update_menu(u8* num_players){
    demotimer--;

    if(demotimer <= 0){
        return SCENE_DEMO;
    }

    cpct_waitVSYNC();
    cpct_akp_musicPlay();

    cpct_scanKeyboard();

    if(cpct_isKeyPressed(Key_0)){           /* 0 Players */
        *num_players = 0;
        return SCENE_DEMO;
    }else if(cpct_isKeyPressed(Key_1)){     /* 1 Player */
        *num_players = 1;
        return SCENE_GAME;
    }else if(cpct_isKeyPressed(Key_2)){     /* 2 Players */
        *num_players = 2;
        return SCENE_GAME;
    }

    return SCENE_MENU;
}
