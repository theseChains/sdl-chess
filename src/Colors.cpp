#include "Colors.h"

TileColor getTileColor(int x, int y)
{
    if ((x + y) % 2 == 1)
        return TileColor::dark;

    return TileColor::light;
}
