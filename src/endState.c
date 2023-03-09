#include <gb/gb.h>
#include <stdint.h>
#include "global.h"

void endScreenInit() {
    // Turn the background map off to make it invisible
    HIDE_BKG;

    DISPLAY_OFF;
}

void endScreenUpdate() {
    UPDATE_KEYS();

    if (KEY_TICKED(J_START)) {
         game_state = GS_LOGO;
    }
}