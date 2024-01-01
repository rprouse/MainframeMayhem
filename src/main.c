#include <gb/gb.h>
#include <stdint.h>
#include <gbdk/font.h>
#include "game.h"
#include "global.h"
#include "logoState.h"
#include "gameState.h"
#include "nextLevelState.h"
#include "endState.h"
#include "utilities.h"

typedef void (*FunctionPointer)(void);

const FunctionPointer gameInitStates[] = {
    logoScreenInit,
    gameScreenInit,
    nextLevelScreenInit,
    endScreenInit
};

const FunctionPointer gameUpdateStates[] = {
    logoScreenUpdate,
    gameScreenUpdate,
    nextLevelScreenUpdate,
    endScreenUpdate
};

void main(void)
{
    // Initialize the game state
    uint8_t last_game_state = GS_NONE;
    game_state = GS_LOGO;

    // Initialize the saved state
    InitSavedState();
    level = GetSavedLevel() + 1;

    // Loop forever
    while(1) {
        // Run the initialization function for the current game state
        if (game_state != last_game_state) {
            gameInitStates[game_state]();
            last_game_state = game_state;
        }

        // Run the update function for the current game state
        gameUpdateStates[game_state]();

        // Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
