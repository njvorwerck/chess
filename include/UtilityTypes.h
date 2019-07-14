#ifndef __UTILITY_TYPES_H__
#define __UTILITY_TYPES_H__

#include <cstddef>

struct RowCol {
    size_t row;
    size_t col;
    RowCol(size_t rowIn, size_t colIn) : row(rowIn), col(colIn) { }
    RowCol() {}
};

typedef RowCol Position;

#endif
