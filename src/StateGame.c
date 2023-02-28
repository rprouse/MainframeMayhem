#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Keys.h"
#include "Game.h"

IMPORT_MAP(map);

void START() 
{
	//scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, 0, 0);
    LoadLevel(1);
}

void UPDATE() 
{
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
