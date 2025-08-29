#ifndef BOARD_H
#define BOARD_H

#include "entities/entity.h"

typedef struct {
    int xSize;
    int ySize;
    Entity **tiles;   // entity matrix
} Board;

Board *createBoard(int x, int y, int mines);
void freeBoard(Board *b);

#endif
