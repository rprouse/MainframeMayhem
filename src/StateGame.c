#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Levels.h"

IMPORT_MAP(map);

void START() 
{
	//scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, 0, 0);
  //set_bkg_data(0, 20 * 18, Levels);
  set_bkg_tiles(0, 0, 8, 10, Levels);
}

void UPDATE() 
{
}
