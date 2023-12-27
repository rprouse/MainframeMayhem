#include <gb/gb.h>
#include <gbdk/platform.h>
#include <gbdk/font.h>
#include <gbdk/console.h>
#include <stdio.h>
#include <stdint.h>
#include "global.h"

void endScreenInit(void) {

    HIDE_SPRITES, HIDE_WIN, SHOW_BKG;
    DISPLAY_ON;

    // Use the 8800 tileset
    LCDC_REG |= LCDCF_BG8800;

    init_bkg(0);

    font_init();
    font_set(font_load(font_ibm));

    gotoxy(5, 8);
    printf("Game Over!");
}

void endScreenUpdate(void) {
    UPDATE_KEYS();

    if (KEY_TICKED(J_START)) {
         game_state = GS_LOGO;
    }
}