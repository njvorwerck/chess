#ifndef __GAME_PIECE_H__
#define __GAME_PIECE_H__

#include <vector>

#include "UtilityTypes.h"
#include "Board.h"

class GamePiece {


public:

    static const bool BLACK = false;
    static const bool WHITE = true;

    GamePiece(Position position, bool color) : mPosition(position), mColor(color) { }

    virtual bool canMove(Board& board, Position position) = 0;

    virtual std::vector<Position> possibleMoves() = 0;

    virtual char getCharRepresentation() = 0;

protected:

    Position mPosition;
    bool mColor;

};

#endif
