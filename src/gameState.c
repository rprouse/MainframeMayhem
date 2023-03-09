#include <gb/gb.h>
#include <stdint.h>
#include "global.h"
#include "tiles.h"
#include "game.h"

void gameScreenInit() {
    DISPLAY_OFF;
    HIDE_BKG;

    // Load Background tiles and then load the map
    set_bkg_data(0, TileLen, Tile);
    LoadLevel(1);

    // Turn the background map on to make it visible
    SHOW_BKG;
    DISPLAY_ON;
}

void gameScreenUpdate() {
    UPDATE_KEYS();

    if (KEY_TICKED(J_A))
        Undo();
    else if (KEY_PRESSED(J_B))
        Explode();
    else if (KEY_RELEASED(J_B)) {
        exploded = FALSE;
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