#include <gb/gb.h>
#include <stdint.h>
#include "global.h"
#include "logo.h"

void logoScreenInit() {

    // Use the 8000 tileset
    LCDC_REG |= LCDCF_BG8000;

    // Load Background tiles and then map
    // Load Background tiles and then map
    set_bkg_palette( 0, 1, Logo_palettes);
    set_bkg_data(0, Logo_TILE_COUNT, Logo_tiles);
    set_bkg_tiles(0, 0, 20u, 18u, Logo_map);

    // Turn the background map on to make it visible
    SHOW_BKG;

    DISPLAY_ON;
}

void logoScreenUpdate() {
    UPDATE_KEYS();

    if (KEY_TICKED(J_START)) {
         game_state = GS_GAME;
    }
}