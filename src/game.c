#include <gb/gb.h>
#include <stdint.h>
#include "game.h"
#include "levels.h"

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

uint8_t palette[7] = { 0x00, 0x01, 0x03, 0x01, 0x01, 0x00, 0x04 };

uint8_t board[ROWS * COLUMNS];  // The game board map
uint8_t attr[ROWS * COLUMNS];   // The game board attributes
uint8_t level = 1;

// Player column and row
int8_t pr;
int8_t pc;

uint8_t undoBuffer[MAX_UNDO];
uint8_t undoCount = 0;

uint8_t reset_count = 0;
BOOLEAN exploded = FALSE;

uint8_t moves = 0;

#define BOARD(r, c) board[r * COLUMNS + c]
#define ATTR(r, c) attr[r * COLUMNS + c]

void drawScreen()
{
    // Update the screen
    set_bkg_tiles(0, 0, COLUMNS, ROWS, board);
    set_bkg_attributes(0, 0, COLUMNS, ROWS, attr);
}

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

void undo(int8_t x, int8_t y, BOOLEAN push)
{
    int8_t r = pr + y;
    int8_t c = pc + x;

    switch (BOARD(r, c))
    {
    case FLOOR:
        BOARD(r, c) = PLAYER;
        ATTR(r, c) = palette[PLAYER];
        //sound.tone(NOTE_C3, NOTE_LENGTH);
        break;
    case GOAL:
        //sound.tone(NOTE_E3, NOTE_LENGTH);
        BOARD(r, c) = PLAYER_ON_GOAL;
        ATTR(r, c) = palette[PLAYER_ON_GOAL];
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
    ATTR(pr, pc) = ATTR(pr, pc) == palette[PLAYER_ON_GOAL] ? palette[GOAL] : palette[FLOOR];

    // Are we pulling a box?
    int8_t br = pr - y;
    int8_t bc = pc - x;
    if (push && BOARD(br, bc) == BOX || BOARD(br, bc) == BOX_ON_GOAL)
    {
        //if (board[pr][pc] == GOAL)
        //    sound.tone(NOTE_C3, NOTE_LENGTH, NOTE_E2, NOTE_LENGTH);
        //else
        //    sound.tone(NOTE_C3, NOTE_LENGTH);

        // Pull the box
        BOARD(pr, pc) = BOARD(pr, pc) == GOAL ? BOX_ON_GOAL : BOX;
        BOARD(br, bc) = BOARD(br, bc) == BOX_ON_GOAL ? GOAL : FLOOR;
        ATTR(pr, pc) = ATTR(pr, pc) == palette[GOAL] ? palette[BOX_ON_GOAL] : palette[BOX];
        ATTR(br, bc) = ATTR(br, bc) == palette[BOX_ON_GOAL] ? palette[GOAL] : palette[FLOOR];
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

    uint8_t move = undoBuffer[moves % MAX_UNDO];
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
    for (uint8_t r = 0; r < ROWS; r++)
    {
        for (uint8_t c = 0; c < COLUMNS; c++)
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

BOOLEAN isSolved()
{
    // Make sure all boxes are on goals
    for (int8_t r = 0; r < ROWS; r++)
    {
        for (int8_t c = 0; c < COLUMNS; c++)
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
    for (uint8_t i = num; i > 1; --i)
    {
        const uint8_t levelSize = Levels[offset];
        offset += levelSize + 1;
    }

    uint8_t row    = 0;
    uint8_t column = 0;

    for (uint8_t data = Levels[++offset]; row < ROWS; data = Levels[offset])
    {
        // Count is zero based
        uint8_t count = data >> 3;
        uint8_t tile = data & 0x07;

        for (uint8_t i = 0; i <= count; ++i)
        {
            BOARD(row, column) = tile;
            ATTR(row, column) = palette[tile];
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

void Move(int8_t x, int8_t y)
{
    int8_t r = pr + y;
    int8_t c = pc + x;

    if (r == -1 || r == ROWS || c == -1 || c == COLUMNS)
    {
        //sound.tone(NOTE_C1, NOTE_LENGTH);
        return;
    }

    switch (BOARD(r, c))
    {
    case FLOOR:
        BOARD(r, c) = PLAYER;
        ATTR(r, c) = palette[PLAYER];
        //sound.tone(NOTE_C3, NOTE_LENGTH);
        moves++;
        undoBuffer[moves % MAX_UNDO] = MOVE;
        break;
    case GOAL:
        //sound.tone(NOTE_E3, NOTE_LENGTH);
        BOARD(r, c) = PLAYER_ON_GOAL;
        ATTR(r, c) = palette[PLAYER_ON_GOAL];

        moves++;
        undoBuffer[moves % MAX_UNDO] = MOVE;
        break;
    case BOX:
    case BOX_ON_GOAL:
        {
            // Need to look one square further then push box
            int8_t r2 = r + y;
            int8_t c2 = c + x;

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

            ATTR(r2, c2) = ATTR(r2, c2) == palette[GOAL] ? palette[BOX_ON_GOAL] : palette[BOX];
            ATTR(r, c) = ATTR(r, c) == palette[BOX_ON_GOAL] ? palette[PLAYER_ON_GOAL] : palette[PLAYER];
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
    ATTR(pr, pc) = ATTR(pr, pc) == palette[PLAYER_ON_GOAL] ? palette[GOAL] : palette[FLOOR];
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