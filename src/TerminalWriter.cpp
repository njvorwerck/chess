#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdexcept>

#include "TerminalWriter.h"

namespace {

    void moveCursor(unsigned int row, unsigned int col) {
        printf("\033[%u;%uH", row, col);
    }

    void changeForeground(Color color) {
        printf("\033[38;5;%um", color);
    }

    void changeBackground(Color color) {
        printf("\033[48;5;%um", color);
    }

    void replacePixel(unsigned int row, unsigned int col, TerminalPixel c) {
        changeForeground(c.fontColor);
        changeBackground(c.bgColor);
        printf("\033[%u;%uH%c", row, col, c.value);
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
    mCurrentWindow.resize(dimensions.row);
    for (int i = 0; i < mCurrentWindow.size(); i++) {
        mCurrentWindow[i].resize(dimensions.col);
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

void TerminalWriter::rawWritePixel(RowCol offset, TerminalPixel pixel) {
    size_t row = mOffset.row + offset.row;
    size_t col = mOffset.col + offset.col;
    mCurrentWindow[offset.row][offset.col] = pixel;
    replacePixel(row, col, pixel);
}

void TerminalWriter::writeAll(TerminalPixelMatrix &window) {
    for (int i = 0; i < window.size(); i++) {
        std::vector<TerminalPixel>& row = window[i];
        for (int j = 0; j < row.size(); j++) {
            RowCol offset(i, j);
            rawWritePixel(offset, row[j]);
        }
    }
    moveCursor(1, 1);
}

void TerminalWriter::writePixel(RowCol offset, TerminalPixel pixel) {
    rawWritePixel(offset, pixel);
    moveCursor(1, 1);
}

TerminalPixelMatrix TerminalWriter::getWindow() {
    return mCurrentWindow;
}

void TerminalWriter::writeChunk(RowCol baseOffset, TerminalPixelMatrix &chunk) {
    for (int i = 0; i < chunk.size(); i++) {
        std::vector<TerminalPixel>& row = chunk[i];
        RowCol chunkOffset(baseOffset.row + i, 0);
        for (int j = 0; j < row.size(); j++) {
            chunkOffset.col = baseOffset.col + j; 
            if(mCurrentWindow[chunkOffset.row][chunkOffset.col] != row[j]) {
                rawWritePixel(chunkOffset, row[j]);
            } 
        }
    }
    moveCursor(1, 1);
}

void TerminalWriter::forcePrint() {
    printTerminalPixelMatrix(mCurrentWindow);
}

void printTerminalPixelMatrix(TerminalPixelMatrix& matrix) {
    moveCursor(1, 1);
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            printf("%c", matrix[i][j].value);
        }
        printf("\n");
    }
}
