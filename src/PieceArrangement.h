#ifndef PIECE_ARRANGEMENT_H
#define PIECE_ARRANGEMENT_H

#include <array>

#include "Aliases.h"
#include "Colors.h"
#include "Constants.h"
#include "PieceType.h"

namespace config
{
    static constexpr ColorAndType bRook{ PieceColor::black, PieceType::rook };
    static constexpr ColorAndType bKnight{ PieceColor::black,
                                           PieceType::knight };
    static constexpr ColorAndType bBishop{ PieceColor::black,
                                           PieceType::bishop };
    static constexpr ColorAndType bQueen{ PieceColor::black, PieceType::queen };
    static constexpr ColorAndType bKing{ PieceColor::black, PieceType::king };
    static constexpr ColorAndType bPawn{ PieceColor::black, PieceType::pawn };
    static constexpr ColorAndType wRook{ PieceColor::white, PieceType::rook };
    static constexpr ColorAndType wKnight{ PieceColor::white,
                                           PieceType::knight };
    static constexpr ColorAndType wBishop{ PieceColor::white,
                                           PieceType::bishop };
    static constexpr ColorAndType wQueen{ PieceColor::white, PieceType::queen };
    static constexpr ColorAndType wKing{ PieceColor::white, PieceType::king };
    static constexpr ColorAndType wPawn{ PieceColor::white, PieceType::pawn };
    static constexpr ColorAndType noPiece{ PieceColor::noColor,
                                           PieceType::none };

    inline constexpr PieceArrangement arrangement{
        { { { bRook, bKnight, bBishop, bQueen, bKing, bBishop, bKnight,
              bRook } },
          { { bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn, bPawn } },
          { { noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece,
              noPiece } },
          { { noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece,
              noPiece } },
          { { noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece,
              noPiece } },
          { { noPiece, noPiece, noPiece, noPiece, noPiece, noPiece, noPiece,
              noPiece } },
          { { wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn, wPawn } },
          { { wRook, wKnight, wBishop, wQueen, wKing, wBishop, wKnight,
              wRook } } }
    };
}

#endif
