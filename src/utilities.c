#include <gb/gb.h>
#include <stdint.h>
#include <stdbool.h>

#include "utilities.h"

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