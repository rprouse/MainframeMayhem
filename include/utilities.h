#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>

#define UPDATE_KEYS()   old_input = input; input = joypad()
#define KEY_PRESSED(K)  (input & (K))
#define KEY_DEBOUNCE(K) ((input & (K)) && (old_input & (K)))
#define KEY_TICKED(K)   ((input & (K)) && !(old_input & (K)))
#define KEY_RELEASED(K) ((old_input & (K)) && !(input & (K)))
#define ANY_KEY_PRESSED (input)

#define SET_BANK(N)     SWITCH_ROM(N); old_bank = bank; bank = N
#define RESTORE_BANK()  SWITCH_ROM(old_bank); bank = old_bank

// Resets all background attributes from 0,0 to w,h to 0
void reset_bkg_attributes(uint8_t w, uint8_t h);

#endif