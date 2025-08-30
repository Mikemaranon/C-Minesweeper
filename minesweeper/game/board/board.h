#ifndef BOARD_H
#define BOARD_H

#include "../entities/entity.h"

typedef struct {
    int positionX;  // current cursor position X
    int positionY;  // current cursor position Y
} Cursor;

typedef struct {
    int xSize;
    int ySize;
    Entity **tiles;   // entity matrix
    Cursor cursor;    // cursor position
} Board;

Board *create_board(int x, int y, int mines);
void set_initial_cursor(Board *b);
void move_cursor(Board *b, int dx, int dy);
void free_board(Board *b);

#endif
