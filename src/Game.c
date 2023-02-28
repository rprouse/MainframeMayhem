#include "ZGBMain.h"
#include "Game.h"
#include "Levels.h"

UINT8 board[COLUMNS * ROWS];
UINT8 level = 1;

#define BOARD(r, c) board[r * COLUMNS + c]

// Player column and row
INT8 pr;
INT8 pc;

// Finds the player in the new board
void findPlayer()
{
    for (UINT8 r = 0; r < ROWS; r++)
    {
        for (UINT8 c = 0; c < COLUMNS; c++)
        {
            if (BOARD(r, c) == PLAYER || BOARD(r, c) == PLAYER_ON_GOAL)
            {
                pr = r;
                pc = c;
                return;
            }
        }
    }
}

void drawScreen()
{
    // Update the screen
    set_bkg_tiles(0, 0, 18, 20, board);
}

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
            BOARD(row, column) = tile;
            ++column;
        }

        ++offset;
    }

    findPlayer();
    //arduboy.setRGBled(0, 0, 0);
    //gameState = STATE_GAME_PLAY;
    //reset();

    //setLevel(level);
    //bestScore = getMoves(level);

    drawScreen();
}

void Move(INT8 x, INT8 y)
{

    INT8 r = pr + y;
    INT8 c = pc + x;

    if (r == -1 || r == ROWS || c == -1 || c == COLUMNS)
    {
        //sound.tone(NOTE_C1, NOTE_LENGTH);
        return;
    }

    switch (BOARD(r, c))
    {
    case FLOOR:
        BOARD(r, c) = PLAYER;
        //sound.tone(NOTE_C3, NOTE_LENGTH);
        //moves++;
        //undoBuffer[moves % MAX_UNDO] = MOVE;
        break;
    case GOAL:
        //sound.tone(NOTE_E3, NOTE_LENGTH);
        BOARD(r, c) = PLAYER_ON_GOAL;
        //moves++;
        //undoBuffer[moves % MAX_UNDO] = MOVE;
        break;
    case BOX:
    case BOX_ON_GOAL:
        {
            // Need to look one square further then push box
            UINT8 r2 = r + y;
            UINT8 c2 = c + x;

            if (r2 == -1 || r2 == ROWS || c2 == -1 || c2 == COLUMNS ||
                BOARD(r2, c2) == WALL ||
                BOARD(r2, c2) == BOX ||
                BOARD(r2, c2) == BOX_ON_GOAL)
            {
                //sound.tone(NOTE_C1, NOTE_LENGTH);
                return;
            }

            //if (board[r2][c2] == GOAL)
            //    sound.tone(NOTE_C3, NOTE_LENGTH, NOTE_E3, NOTE_LENGTH);
            //else
            //    sound.tone(NOTE_C3, NOTE_LENGTH);

            // Push the box
            BOARD(r2, c2) = BOARD(r2, c2) == GOAL ? BOX_ON_GOAL : BOX;
            BOARD(r, c) = BOARD(r, c) == BOX_ON_GOAL ? PLAYER_ON_GOAL : PLAYER;
            //moves++;
            //undoBuffer[moves % MAX_UNDO] = PUSH;
        }
        break;
    case WALL:
    default:
        return;
    }

    // Set the board based on where the player WAS
    BOARD(pr, pc) = BOARD(pr, pc) == PLAYER_ON_GOAL ? GOAL : FLOOR;
    pr = r;
    pc = c;

    //if (x == 1)
    //    undoBuffer[moves % MAX_UNDO] |= LEFT;
    //else if (x == -1)
    //    undoBuffer[moves % MAX_UNDO] |= RIGHT;
    //else if (y == 1)
    //    undoBuffer[moves % MAX_UNDO] |= DOWN;
    //else if (y == -1)
    //    undoBuffer[moves % MAX_UNDO] |= UP;

    //if (undoCount < MAX_UNDO)
    //    undoCount++;

    drawScreen();
}