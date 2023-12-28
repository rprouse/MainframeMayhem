#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdint.h>
#include <gbdk/platform.h>

#define GS_NONE                99
#define GS_LOGO                 0
#define GS_GAME                 1
#define GS_END                  2

//game state
extern uint8_t game_state;

//input
extern uint8_t input;
extern uint8_t old_input;

//bank
extern uint8_t bank;
extern uint8_t old_bank;

#endif