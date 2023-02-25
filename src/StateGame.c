#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Levels.h"

#define ROWS 20
#define COLUMNS 18

IMPORT_MAP(map);

UINT8 board[COLUMNS*ROWS];

void loadLevel(int num)
{
  int offset = 0;
  // skip to the level we want to load
  for (size_t i = num; i > 1; --i)
  {
    const uint8_t levelSize = Levels[offset];
    offset += levelSize + 1;
  }

  uint8_t row = 0;
  uint8_t column = 0;

  for (uint8_t data = Levels[++offset]; row < ROWS; data = Levels[offset])
  {
    if (column >= COLUMNS)
    {
      ++row;
      column = 0;
    }

    // Count is zero based
    const uint8_t count = ((data >> 3) & 0x1F);
    const uint8_t tile = ((data >> 0) & 0x07);

    for (uint8_t i = 0; i <= count; ++i)
    {
      board[row * COLUMNS + column] = tile;
      ++column;
    }

    ++offset;
  }

  //findPlayer();
  //arduboy.setRGBled(0, 0, 0);
  //gameState = STATE_GAME_PLAY;
  //reset();

  //setLevel(level);
  //bestScore = getMoves(level);
}

void START() 
{
	//scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, 0, 0);
  loadLevel(1);
  set_bkg_tiles(0, 0, 18, 20, board);
}

void UPDATE() 
{
}
