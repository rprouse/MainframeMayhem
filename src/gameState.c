#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>
#include "global.h"
#include "tiles.h"
#include "game.h"

const palette_color_t palettes[32] = {
    TileCGBPal0c0, TileCGBPal0c1, TileCGBPal0c2, TileCGBPal0c3,
    TileCGBPal1c0, TileCGBPal1c1, TileCGBPal1c2, TileCGBPal1c3,
    TileCGBPal2c0, TileCGBPal2c1, TileCGBPal2c2, TileCGBPal2c3,
    TileCGBPal3c0, TileCGBPal3c1, TileCGBPal3c2, TileCGBPal3c3,
    TileCGBPal4c0, TileCGBPal4c1, TileCGBPal4c2, TileCGBPal4c3,
    TileCGBPal5c0, TileCGBPal5c1, TileCGBPal5c2, TileCGBPal5c3,
    TileCGBPal6c0, TileCGBPal6c1, TileCGBPal6c2, TileCGBPal6c3,
    TileCGBPal7c0, TileCGBPal7c1, TileCGBPal7c2, TileCGBPal7c3,
};

void gameScreenInit(void) {
    DISPLAY_OFF;
    HIDE_BKG;

    // Use the 8000 tileset
    LCDC_REG |= LCDCF_BG8000;

    // Load Background tiles and then load the map
    set_bkg_palette(0, 8, palettes);
    set_bkg_data(0, TileLen, Tile);
    LoadLevel(1);

    // Turn the background map on to make it visible
    SHOW_BKG;
    DISPLAY_ON;
}

void gameScreenUpdate(void) {
    UPDATE_KEYS();

    if (KEY_TICKED(J_A))
        Undo();
    else if (KEY_PRESSED(J_B))
        Explode();
    else if (KEY_RELEASED(J_B)) {
        exploded = false;
        reset_count = 0;
    }
    else if (KEY_TICKED(J_START)) {
        game_state = GS_END;
    }
    if (KEY_TICKED(J_UP)) {
        Move(0, -1);
    }
    else if (KEY_TICKED(J_DOWN)) {
        Move(0, 1);
    }
    else if (KEY_TICKED(J_RIGHT)) {
        Move(1, 0);
    }
    else if (KEY_TICKED(J_LEFT)) {
        Move(-1, 0);
    }
}