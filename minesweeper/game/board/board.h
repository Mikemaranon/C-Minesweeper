#ifndef BOARD_H
#define BOARD_H

#include "../entities/entity.h"

typedef struct {
    int xSize;
    int ySize;
    Entity **tiles;   // entity matrix
} Board;

Board *create_board(int x, int y, int mines);
void free_board(Board *b);

#endif
