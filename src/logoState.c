#include <gb/gb.h>
#include <stdint.h>
#include "global.h"
#include "logo.h"
#include "game.h"
#include "utilities.h"

void logoScreenInit(void)
{
    HIDE_SPRITES, HIDE_WIN, SHOW_BKG;
    DISPLAY_OFF;

    // Use the 8000 tileset
    LCDC_REG |= LCDCF_BG8000;

    // Load Background tiles and then map
    set_bkg_palette( 0, 1, Logo_palettes);
    set_bkg_data(0, Logo_TILE_COUNT, Logo_tiles);
    set_bkg_tiles(0, 0, 20u, 18u, Logo_map);
    reset_bkg_attributes(COLUMNS, ROWS);

    // Turn the background map on to make it visible
    SHOW_BKG;

    DISPLAY_ON;
}

void logoScreenUpdate(void) {
    UPDATE_KEYS();

    if (KEY_TICKED(J_START)) {
         game_state = GS_GAME;
    }
}