#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdexcept>

#include "TerminalWriter.h"

namespace {

    void moveCursor(unsigned int row, unsigned int col) {
        printf("\033[%u;%uH", row, col);
    }

    void replaceChar(unsigned int row, unsigned int col, char c) {
        printf("\033[%u;%uH%c", row, col, c);
    }

    void clearScreen() {
        printf("\033[2J");
    }

}

void TerminalWriter::init(RowCol dimensions, RowCol offset) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    mTerminalDims.row = w.ws_row;
    mTerminalDims.col = w.ws_col;
    mCurrentWindow.resize(mTerminalDims.row);
    for (int i = 0; i < mCurrentWindow.size(); i++) {
        mCurrentWindow[i].resize(mTerminalDims.col);
    }
    mWindowDims = dimensions;
    mOffset = offset;
    if (offset.row + dimensions.row > mTerminalDims.row || 
            offset.col + dimensions.col > mTerminalDims.col) {
        throw new std::invalid_argument("Window doesn't fit in terminal");
    }
    clearScreen();
    moveCursor(1, 1);
}

TerminalWriter::TerminalWriter(RowCol dimensions) { 
    RowCol offset(0, 0);
    init(dimensions, offset);
}
TerminalWriter::TerminalWriter(RowCol dimensions, RowCol offset) { 
    init(dimensions, offset);
} 

void TerminalWriter::rawWritePixel(RowCol offset, char pixel) {
    size_t row = mOffset.row + offset.row;
    size_t col = mOffset.col + offset.col;
    mCurrentWindow[row][col] = pixel;
    replaceChar(row, col, pixel);
}

void TerminalWriter::writeAll(std::vector<std::string> &window) {
    for (int i = 0; i < window.size(); i++) {
        std::string row = window[i];
        for (int j = 0; j < row.size(); j++) {
            RowCol offset(i, j);
            rawWritePixel(offset, row[j]);
        }
    }
    moveCursor(1, 1);
}

void TerminalWriter::writePixel(RowCol offset, char pixel) {
    rawWritePixel(offset, pixel);
    moveCursor(1, 1);
}

std::vector<std::string> TerminalWriter::getWindow() {
    return mCurrentWindow;
}
