#ifndef __BOARD_H__
#define __BOARD_H__

#include "UtilityTypes.h"
#include "GamePiece.h"

class Board {

public:

    static const size_t BOARD_ROWS = 8;
    static const size_t BOARD_COLS = 8;

    Board() {
        this->reset();
    }

    bool movePiece(Position a, Position b);

    //Sets the game board to the initial position
    void reset(); 

private: 

    GamePiece* mBoard[BOARD_ROWS][BOARD_COLS];

};

#endif
