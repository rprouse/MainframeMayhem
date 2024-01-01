#include <gbdk/platform.h>
#include <stdint.h>

// In external RAM bank 0
char save_ram_initialized;
uint8_t saved_level;
uint8_t saved_moves[256];