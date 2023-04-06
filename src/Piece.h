#ifndef PIECE_H
#define PIECE_H

#include "PieceType.h"

class Piece
{
public:
    Piece(PieceType type);

private:
    PieceType m_type{};
};

#endif
