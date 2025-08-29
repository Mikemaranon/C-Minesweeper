#include <stdio.h>
#include "game.h"
#include "board/board.h"

// Function that starts the game
void start_game(const char* difficulty, int rows, int cols, int mines) {
    printf("Starting Minesweeper with difficulty level %d...\n", difficulty);

    Board *board = createBoard(rows, cols, mines);  // intialyze board
    if (!board) return;

    printf("Board is ready. Let's play!\n");
}

