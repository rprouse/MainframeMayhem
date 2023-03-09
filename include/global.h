#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdint.h>
#include <gbdk/platform.h>

#define UPDATE_KEYS()   old_input = input; input = joypad()
#define KEY_PRESSED(K)  (input & (K))
#define KEY_DEBOUNCE(K) ((input & (K)) && (old_input & (K)))
#define KEY_TICKED(K)   ((input & (K)) && !(old_input & (K)))
#define KEY_RELEASED(K) ((old_input & (K)) && !(input & (K)))
#define ANY_KEY_PRESSED (input)

#define SET_BANK(N)     SWITCH_ROM(N); old_bank = bank; bank = N
#define RESTORE_BANK()  SWITCH_ROM(old_bank); bank = old_bank

#define GS_NONE                99
#define GS_LOGO                 0
#define GS_GAME                 1
#define GS_END                  2

#define FALSE                   0
#define TRUE                    1

//game state
extern uint8_t game_state;

//input
extern uint8_t input;
extern uint8_t old_input;

//bank
extern uint8_t bank;
extern uint8_t old_bank;

#endif