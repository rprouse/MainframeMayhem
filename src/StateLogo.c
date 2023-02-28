#include "Banks/SetAutoBank.h"
#include "Keys.h"

#include "ZGBMain.h"
#include "LabScreen.h"

void START()
{
    // Load Background tiles and then map
    set_bkg_data(LabScreen_TILE_ORIGIN, LabScreen_TILE_COUNT, LabScreen_tiles);
    set_bkg_tiles(0, 0, 20u, 18u, LabScreen_map);

    // Turn the background map on to make it visible
    SHOW_BKG;
}

void UPDATE()
{
    if (ANY_KEY_PRESSED)
    {
        SetState(StateGame);
    }
}
