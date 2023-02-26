#include "ZGBMain.h"
#include "Level.h"
#include "Levels.h"

UINT8 board[COLUMNS * ROWS];
UINT8 level = 1;

void NextLevel()
{
  if (level < NUM_LEVELS)
    LoadLevel(++level);
}

void PrevLevel()
{
  if (level > 1)
    LoadLevel(--level);
}

void LoadLevel(int num)
{
  int offset = 0;
  // skip to the level we want to load
  for (size_t i = num; i > 1; --i)
  {
    const UINT8 levelSize = Levels[offset];
    offset += levelSize + 1;
  }

  UINT8 row = 0;
  UINT8 column = 0;

  for (UINT8 data = Levels[++offset]; row < ROWS; data = Levels[offset])
  {
    if (column >= COLUMNS)
    {
      ++row;
      column = 0;
    }

    // Count is zero based
    const UINT8 count = ((data >> 3) & 0x1F);
    const UINT8 tile = ((data >> 0) & 0x07);

    for (UINT8 i = 0; i <= count; ++i)
    {
      board[row * COLUMNS + column] = tile;
      ++column;
    }

    ++offset;
  }

  set_bkg_tiles(0, 0, 18, 20, board);

  //findPlayer();
  //arduboy.setRGBled(0, 0, 0);
  //gameState = STATE_GAME_PLAY;
  //reset();

  //setLevel(level);
  //bestScore = getMoves(level);
}