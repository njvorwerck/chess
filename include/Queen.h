#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "GamePiece.h"

class Queen : protected GamePiece {

public:

    virtual bool canMove(Board& board, Position position);

    virtual vector<Position> possibleMoves();

};

#endif
