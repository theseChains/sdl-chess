#include "TileColor.h"

TileColor getTileColor(int x, int y)
{
    if ((x + y) % 2 == 0)
        return TileColor::dark;
    
    return TileColor::light;
}
