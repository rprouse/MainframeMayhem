#include <gb/gb.h>
#include <gbdk/platform.h>
#include <gbdk/font.h>
#include <gbdk/console.h>
#include <stdio.h>
#include <stdint.h>
#include "global.h"

#define PRINT_POS(X, Y) print_x = X; print_y  = Y

void endScreenInit() {
    DISPLAY_OFF;
    HIDE_BKG;

    fill_rect(0, 0 , 20, 18, 0);

    font_init();
    font_set(font_load(font_ibm));
    printf("\n\n\n\n\n  Game Over!");

    SHOW_BKG;
    DISPLAY_ON;
}

void endScreenUpdate() {
    UPDATE_KEYS();

    if (KEY_TICKED(J_START)) {
         game_state = GS_LOGO;
    }
}