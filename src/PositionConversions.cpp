#include "PositionConversions.h"

#include "Constants.h"

std::pair<int, int> getBoardPositionFromMouse(SDL_Point mousePosition)
{
    return convertToBoardPosition({ mousePosition.y, mousePosition.x });
}

std::pair<int, int> convertToBoardPosition(std::pair<int, int> position)
{
    return { position.first / constants::screenPositionMultiplier,
             position.second / constants::screenPositionMultiplier };
}

std::pair<int, int> convertToScreenPosition(std::pair<int, int> position)
{
    return { position.first * constants::screenPositionMultiplier,
             position.second * constants::screenPositionMultiplier };
}

std::pair<int, int> convertToRectanglePosition(std::pair<int, int> position)
{
    return { position.second, position.first };
}
