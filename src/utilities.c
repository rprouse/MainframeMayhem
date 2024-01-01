#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

#include "utilities.h"
#include "global.h"

//saved state
extern char save_ram_initialized;
extern uint8_t saved_level;
extern uint8_t saved_moves[];

void reset_bkg_attributes(uint8_t w, uint8_t h)
{
    VBK_REG = VBK_ATTRIBUTES;
    uint8_t x, y;
    for (y = 0; y < h; y++)
    {
        for (x = 0; x < w; x++)
        {
            set_bkg_tile_xy(x, y, 0);
        }
    }
    VBK_REG = VBK_TILES;
}

void InitSavedState(void)
{
    ENABLE_RAM;

    SWITCH_RAM_MBC5(0);
    if (save_ram_initialized == 's')
    {
        return;
    }

    saved_level = 0;
    uint8_t i;
    for (i = 0; i < 255; i++)
    {
        saved_moves[i] = 0;
    }
    save_ram_initialized = 's';
}

uint8_t GetSavedLevel(void)
{
    uint8_t level;
    SWITCH_RAM_MBC5(0);
    level = saved_level;
    return level;
}

void SetSavedLevel(uint8_t level)
{
    SWITCH_RAM_MBC5(0);
    saved_level = level;
}

uint8_t GetSavedMoves(uint8_t level)
{
    uint8_t moves;
    SWITCH_RAM_MBC5(0);
    moves = saved_moves[level];
    return moves;
}

void SetSavedMoves(uint8_t level, uint8_t moves)
{
    SWITCH_RAM_MBC5(0);
    saved_moves[level] = moves;
}