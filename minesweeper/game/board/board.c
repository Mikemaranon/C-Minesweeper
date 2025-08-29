#include <stdlib.h>
#include <time.h>
#include "board.h"

Board *create_board(int x, int y, int mines) {
    Board *b = malloc(sizeof(Board));
    if (!b) return NULL;

    b->xSize = x;
    b->ySize = y;

    b->tiles = malloc(y * sizeof(Entity*));
    if (!b->tiles) { free(b); return NULL; }

    for (int i = 0; i < y; i++) {
        b->tiles[i] = calloc(x, sizeof(Entity));
        if (!b->tiles[i]) {
            for (int j = 0; j < i; j++) free(b->tiles[j]);
            free(b->tiles);
            free(b);
            return NULL;
        }
    }

    fillBoard(b, mines);
    fillValues(b);

    return b;
}

void fillBoard(Board *b, int mines) {
    if (!b) return;

    srand(time(NULL));

    // Primero inicializamos todo como EMPTY
    for (int r = 0; r < b->ySize; r++) {
        for (int c = 0; c < b->xSize; c++) {
            b->tiles[r][c].type = ENTITY_EMPTY;
            b->tiles[r][c].revealed = 0;
            b->tiles[r][c].adjacentBombs = 0;
        }
    }

    // Ponemos bombas de forma aleatoria usando Fisher-Yates sobre índices
    int totalCells = b->xSize * b->ySize;
    int *positions = malloc(sizeof(int) * totalCells);
    for (int i = 0; i < totalCells; i++) positions[i] = i;

    // Mezclamos posiciones
    for (int i = totalCells - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = positions[i];
        positions[i] = positions[j];
        positions[j] = tmp;
    }

    // Colocamos las bombas
    for (int i = 0; i < mines; i++) {
        int pos = positions[i];
        int r = pos / b->xSize;
        int c = pos % b->xSize;
        b->tiles[r][c].type = ENTITY_BOMB;
    }

    free(positions);
}

void fillValues(Board *b) {
    int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int r = 0; r < b->ySize; r++) {
        for (int c = 0; c < b->xSize; c++) {
            if (b->tiles[r][c].type == ENTITY_BOMB) {
                b->tiles[r][c].adjacentBombs = -1; // opcional
                continue;
            }

            int count = 0;
            for (int i = 0; i < 8; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < b->ySize && nc >= 0 && nc < b->xSize) {
                    if (b->tiles[nr][nc].type == ENTITY_BOMB) count++;
                }
            }
            b->tiles[r][c].adjacentBombs = count;
        }
    }
}

void free_board(Board *b) {
    if (!b) return;
    for (int i = 0; i < b->ySize; i++) {
        free(b->tiles[i]);
    }
    free(b->tiles);
    free(b);
}
