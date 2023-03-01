#include "ZGBMain.h"
#include "Game.h"
#include "Levels.h"

#define FRAMES_TO_RESET      90
#define EXPLODE_FRAMES        6

// Undo buffer defines
#define UP      0x01
#define DOWN    0x02
#define LEFT    0x04
#define RIGHT   0x08
#define PUSH    0x10
#define MOVE    0x00

#if DEBUG
#define MAX_UNDO             10
#else
#define MAX_UNDO            128
#endif

UINT8 board[ROWS * COLUMNS];
UINT8 level = 1;

// Player column and row
INT8 pr;
INT8 pc;

UINT8 undoBuffer[MAX_UNDO];
UINT8 undoCount = 0;

UINT8 reset_count = 0;
BOOLEAN exploded = FALSE;

UINT8 moves = 0;

#define BOARD(r, c) board[r * COLUMNS + c]

// This will reset the level after FRAMES_TO_RESET of the B button being held down
void Explode()
{
    if (exploded) return;

    reset_count++;
    if (reset_count > FRAMES_TO_RESET)
    {
        //gameState = STATE_LEVEL_INIT;
        exploded = TRUE;
        reset_count = 0;
        return;
    }

    //sound.tone(NOTE_C3 + reset_count, NOTE_LENGTH);
}

void undo(INT8 x, INT8 y, BOOLEAN push)
{
    INT8 r = pr + y;
    INT8 c = pc + x;

    switch (BOARD(r, c))
    {
    case FLOOR:
        BOARD(r, c) = PLAYER;
        //sound.tone(NOTE_C3, NOTE_LENGTH);
        break;
    case GOAL:
        //sound.tone(NOTE_E3, NOTE_LENGTH);
        BOARD(r, c) = PLAYER_ON_GOAL;
        break;
    case WALL:
    case BOX:
    case BOX_ON_GOAL:
    default:
        // This should never happen!
        return;
    }

    // Set the board based on where the player WAS
    BOARD(pr, pc) = BOARD(pr, pc) == PLAYER_ON_GOAL ? GOAL : FLOOR;

    // Are we pulling a box?
    INT8 br = pr - y;
    INT8 bc = pc - x;
    if (push && BOARD(br, bc) == BOX || BOARD(br, bc) == BOX_ON_GOAL)
    {
        //if (board[pr][pc] == GOAL)
        //    sound.tone(NOTE_C3, NOTE_LENGTH, NOTE_E2, NOTE_LENGTH);
        //else
        //    sound.tone(NOTE_C3, NOTE_LENGTH);

        // Pull the box
        BOARD(pr, pc) = BOARD(pr, pc) == GOAL ? BOX_ON_GOAL : BOX;
        BOARD(br, bc) = BOARD(br, bc) == BOX_ON_GOAL ? GOAL : FLOOR;
    }

    pr = r;
    pc = c;
    moves--;
    undoCount--;
}

void Undo()
{
    if (undoCount == 0)
        return; // No more undos left

    UINT8 move = undoBuffer[moves % MAX_UNDO];
    BOOLEAN push = (move & PUSH) == PUSH;
    if ((move & LEFT) == LEFT)
        undo(-1, 0, push);
    else if ((move & RIGHT) == RIGHT)
        undo(1, 0, push);
    else if ((move & DOWN) == DOWN)
        undo(0, -1, push);
    else if ((move & UP) == UP)
        undo(0, 1, push);

    drawScreen();
}

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
    set_bkg_tiles(0, 0, COLUMNS, ROWS, board);
}

BOOLEAN isSolved()
{
    // Make sure all boxes are on goals
    for (INT8 r = 0; r < ROWS; r++)
    {
        for (INT8 c = 0; c < COLUMNS; c++)
        {
            if (BOARD(r, c) == BOX)
                return FALSE;
        }
    }
    //setMoves(level, moves);
    //setRandomEncouragement();
    return TRUE;
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

    UINT8 row    = 0;
    UINT8 column = 0;

    for (UINT8 data = Levels[++offset]; row < ROWS; data = Levels[offset])
    {
        // Count is zero based
        UINT8 count = data >> 3;
        UINT8 tile = data & 0x07;

        for (UINT8 i = 0; i <= count; ++i)
        {
            BOARD(row, column) = tile;
            column++;
        }

        if (column >= COLUMNS)
        {
            ++row;
            column = 0;
        }

        ++offset;
    }

    findPlayer();
    //gameState = STATE_GAME_PLAY;
    
    // reset
    moves = 0;
    undoCount = 0;
    reset_count = 0;

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
        moves++;
        undoBuffer[moves % MAX_UNDO] = MOVE;
        break;
    case GOAL:
        //sound.tone(NOTE_E3, NOTE_LENGTH);
        BOARD(r, c) = PLAYER_ON_GOAL;
        moves++;
        undoBuffer[moves % MAX_UNDO] = MOVE;
        break;
    case BOX:
    case BOX_ON_GOAL:
        {
            // Need to look one square further then push box
            INT8 r2 = r + y;
            INT8 c2 = c + x;

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
            moves++;
            undoBuffer[moves % MAX_UNDO] = PUSH;
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

    if (x == 1)
        undoBuffer[moves % MAX_UNDO] |= LEFT;
    else if (x == -1)
        undoBuffer[moves % MAX_UNDO] |= RIGHT;
    else if (y == 1)
        undoBuffer[moves % MAX_UNDO] |= DOWN;
    else if (y == -1)
        undoBuffer[moves % MAX_UNDO] |= UP;

    if (undoCount < MAX_UNDO)
        undoCount++;

    drawScreen();

    if (isSolved() == TRUE)
    {
        NextLevel();
    }
}