#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "Game.h"

IMPORT_MAP(map);

void START() 
{
    delay(200);

	//scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, 0, 0);
    LoadLevel(1);
}

void UPDATE() 
{
    if (KEY_TICKED(J_A))
        Undo();
    else if (KEY_PRESSED(J_B))
        Explode();
    else if (KEY_RELEASED(J_B))
    {
        exploded = FALSE;
        reset_count = 0;
    }
    else if (KEY_TICKED(J_START))
    {
        //gameState = STATE_GAME_INTRO;
    }
    if (KEY_TICKED(J_UP))
    {
        Move(0, -1);
    }
    else if (KEY_TICKED(J_DOWN))
    {
        Move(0, 1);
    }
    else if (KEY_TICKED(J_RIGHT))
    {
        Move(1, 0);
    }
    else if (KEY_TICKED(J_LEFT))
    {
        Move(-1, 0);
    }
}
