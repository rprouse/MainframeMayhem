#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Level.h"

IMPORT_MAP(map);

void START() 
{
	//scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, 0, 0);
  LoadLevel(1);
}

void UPDATE() 
{
}
