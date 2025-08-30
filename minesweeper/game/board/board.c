#include <stdlib.h>
#include <time.h>
#include "board.h"

// Function prototypes for internal use
static void checkAdjacentTiles(Board *b, int x, int y);
static void fillBoard(Board *b, int mines);
static void fillValues(Board *b);
static void focusTile(Board *b, int x, int y);
static void removeFocus(Board *b, int x, int y);

// Creates and initializes a new board
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

// Sets the initial cursor position to the center of the board
void set_initial_cursor(Board *b) {
    if (!b) return;
    b->cursor.positionX = b->xSize / 2;
    b->cursor.positionY = b->ySize / 2;

    focusTile(b, b->cursor.positionX, b->cursor.positionY);
}

// Moves the cursor by (dx, dy), ensuring it stays within board bounds
void move_cursor(Board *b, int dx, int dy) {
    if (!b) return;

    removeFocus(b, b->cursor.positionX, b->cursor.positionY);

    b->cursor.positionX += dx;
    b->cursor.positionY += dy;

    // Ensure cursor stays within bounds
    if (b->cursor.positionX < 0) {
        b->cursor.positionX = 0;
    }
        
    if (b->cursor.positionX >= b->xSize) {
        b->cursor.positionX = b->xSize - 1;
    }

    if (b->cursor.positionY < 0) {
        b->cursor.positionY = 0;
    }

    if (b->cursor.positionY >= b->ySize) {
        b->cursor.positionY = b->ySize - 1;
    }

    focusTile(b, b->cursor.positionX, b->cursor.positionY);
}

void flag_tile(Board *b) {
    if (!b) return;
    int x = b->cursor.positionX;
    int y = b->cursor.positionY;
    Entity *e = &b->tiles[y][x];

    if (!e->revealed) {
        e->flagged = !e->flagged; // Toggle flag
    }
}

int reveal_tile(Board *b) {
    if (!b) {
        return -1;
    }
    
    int x = b->cursor.positionX;
    int y = b->cursor.positionY;
    Entity *e = &b->tiles[y][x];

    if (!e->revealed && !e->flagged) {
        e->revealed = 1; // Reveal the tile
        if (e->type == ENTITY_BOMB) {
            return 0; // Hit a bomb
        }
    }

    checkAdjacentTiles(b, x, y);

    return 1; // Safe
}

// Frees the memory allocated for the board
void free_board(Board *b) {
    if (!b) return;
    for (int i = 0; i < b->ySize; i++) {
        free(b->tiles[i]);
    }
    free(b->tiles);
    free(b);
}

static void checkAdjacentTiles(Board *b, int x, int y) {
    if (!b) return;

    Entity *e = &b->tiles[y][x];
    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    // --- CASE 0 ---
    if (e->adjacentBombs == 0) {
        // first reveal all adjacent non-revealed, non-bomb tiles
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx >= b->xSize || ny >= b->ySize)
                continue;

            Entity *adj = &b->tiles[ny][nx];

            if (!adj->revealed && adj->type != ENTITY_BOMB) {
                adj->revealed = 1;
            }
        }

        // Now recurse on neighbors that are 0
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx >= b->xSize || ny >= b->ySize)
                continue;

            Entity *adj = &b->tiles[ny][nx];

            if (adj->adjacentBombs == 0 && !adj->revealed) {
                checkAdjacentTiles(b, nx, ny);
            }
        }
    } 
    // --- CASE != 0 ---
    else {
        // if revealed, check "chording"
        if (e->revealed) {
            int flagCount = 0;
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || ny < 0 || nx >= b->xSize || ny >= b->ySize)
                    continue;

                Entity *adj = &b->tiles[ny][nx];
                if (adj->flagged) flagCount++;
            }

            // if flags >= adjacentBombs, reveal all non-flagged neighbors
            if (flagCount >= e->adjacentBombs) {
                for (int i = 0; i < 8; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx < 0 || ny < 0 || nx >= b->xSize || ny >= b->ySize)
                        continue;

                    Entity *adj = &b->tiles[ny][nx];
                    if (!adj->revealed && !adj->flagged && adj->type != ENTITY_BOMB) {
                        adj->revealed = 1;

                        // if a revealed neighbor is 0, recurse
                        if (adj->adjacentBombs == 0) {
                            checkAdjacentTiles(b, nx, ny);
                        }
                    }
                }
            }
        }
    }
}


static void removeFocus(Board *b, int x, int y) {
    if (!b) return;
    b->tiles[y][x].focused = 0; // Remove focus from tile
}

static void focusTile(Board *b, int x, int y) {
    if (x >= 0 && x < b->xSize && y >= 0 && y < b->ySize) {
        b->tiles[y][x].focused = 1; // Set focus to the specified tile
    }
}

// Fills the board with bombs and empty tiles
static void fillBoard(Board *b, int mines) {
    if (!b) return;

    srand(time(NULL));

    // initialyze all tiles as empty
    for (int r = 0; r < b->ySize; r++) {
        for (int c = 0; c < b->xSize; c++) {
            b->tiles[r][c].type = ENTITY_EMPTY;
            b->tiles[r][c].revealed = 0;
            b->tiles[r][c].adjacentBombs = 0;
        }
    }

    // Random unique positions for bombs
    int totalCells = b->xSize * b->ySize;
    int *positions = malloc(sizeof(int) * totalCells);
    for (int i = 0; i < totalCells; i++) positions[i] = i;

    // Mix positions
    for (int i = totalCells - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = positions[i];
        positions[i] = positions[j];
        positions[j] = tmp;
    }

    // set bombs
    for (int i = 0; i < mines; i++) {
        int pos = positions[i];
        int r = pos / b->xSize;
        int c = pos % b->xSize;
        b->tiles[r][c].type = ENTITY_BOMB;
    }

    free(positions);
}

// Fills the board with the count of adjacent bombs for each tile
static void fillValues(Board *b) {
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
