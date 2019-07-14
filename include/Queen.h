#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "GamePiece.h"

class Queen : public GamePiece {

public:

    Queen(Position position, bool color) : GamePiece(position, color) { }

    virtual bool canMove(Board& board, Position position) { return true; }

    virtual std::vector<Position> possibleMoves() { return std::vector<Position>(); }

    virtual char getCharRepresentation() { return 'Q'; }

};

#endif
