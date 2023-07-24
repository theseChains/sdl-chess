#ifndef PIECE_H
#define PIECE_H

#include "Colors.h"
#include "PieceType.h"
#include "Renderer.h"

#include <SDL2/SDL_image.h>

#include <tuple>

class Piece
{
public:
    Piece(PieceType type, PieceColor color, SDL_Texture* texture, std::pair<int, int> position);

    void draw(Renderer& renderer);

    SDL_Rect& getRectangle();
    PieceType getType() const;
    std::pair<int, int> getPosition() const;
    std::pair<int, int> getBoardPosition() const;
    PieceColor getColor() const;

    void setPosition(std::pair<int, int> position);
    void setBoardPosition(std::pair<int, int> position);
    void setHasMoved();

    void select();
    void deselect();
    bool isSelected() const;

    bool hasMoved() const;

    bool operator==(const Piece& other) const;

private:
    PieceType m_type{};
    PieceColor m_color{};
    SDL_Rect m_rectangle{};
    SDL_Texture* m_texture{};
    std::pair<int, int> m_position{};
    bool m_isSelected{ false };

    bool m_hasMoved{ false };
};

#endif
