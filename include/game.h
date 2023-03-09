#ifndef GAME_H
#define GAME_H

#include "types.h"

#define ROWS    18
#define COLUMNS 20

#define FLOOR          0x00
#define WALL           0x01
#define GOAL           0x02
#define BOX            0x03
#define BOX_ON_GOAL    0x04
#define PLAYER         0x05
#define PLAYER_ON_GOAL 0x06

void NextLevel();
void PrevLevel();
void LoadLevel(int num);
void Move(INT8 x, INT8 y);
void Undo();
void Explode();

extern BOOLEAN exploded;
extern UINT8 reset_count;

#endif
