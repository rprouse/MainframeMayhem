#include <gb/gb.h>
#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/font.h>
#include <gbdk/console.h>
#include <stdio.h>
#include "global.h"
#include "game.h"
#include "levels.h"
#include "utilities.h"

void nextLevelScreenInit(void) {

    HIDE_SPRITES, HIDE_WIN, SHOW_BKG;
    DISPLAY_ON;

    // Use the 8800 tileset
    LCDC_REG |= LCDCF_BG8800;

    reset_bkg_attributes(COLUMNS, ROWS);

    init_bkg(0);

    font_init();
    font_set(font_load(font_ibm));

    gotoxy(1, 7);
    printf("Level %d complete", level);
    gotoxy(5, 8);
    printf("Moves: %d", moves);
    gotoxy(4, 13);
    printf("A next level");
    gotoxy(4, 14);
    printf("B redo level");
}

void nextLevelScreenUpdate(void) {
    UPDATE_KEYS();

    if (KEY_TICKED(J_A)) {

        if (level < NUM_LEVELS) {
            level++;
            game_state = GS_GAME;
        } else {
            game_state = GS_END;
        }
    } else if (KEY_TICKED(J_B)) {
        game_state = GS_GAME;
    }
}