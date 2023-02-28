#ifndef LabScreen_H
#define LabScreen_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define LabScreen_TILE_ORIGIN 0
#define LabScreen_TILE_W 8
#define LabScreen_TILE_H 8
#define LabScreen_TILE_COUNT 88

BANKREF_EXTERN(LabScreen)

extern const uint8_t LabScreen_tiles[1408];
extern const uint8_t LabScreen_map[360];

#endif
