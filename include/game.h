#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

#define ROWS    18
#define COLUMNS 20

#define FLOOR          0x00
#define WALL           0x01
#define GOAL           0x02
#define BOX            0x03
#define BOX_ON_GOAL    0x04
#define PLAYER         0x05
#define PLAYER_ON_GOAL 0x06

void NextLevel(void);
void PrevLevel(void);
void LoadLevel(uint8_t num);
void Move(int8_t x, int8_t y);
void Undo(void);

extern uint8_t level;
extern uint8_t moves;

#endif
