#include <stdio.h>
#include "game.h"
#include "board/board.h"
#include "graphics/graphic_printer.h"

static void begin_game_loop(Board *board);

// Function that starts the game
void start_game(const char* difficulty, int rows, int cols, int mines) {
    printf("Starting Minesweeper with difficulty level %s...\n", difficulty);

    Board *board = create_board(rows, cols, mines);  // intialyze board
    if (!board) return;

    printf("Board is ready. Let's play!\n");

    begin_game_loop(board); // Start the game loop (not implemented here)

    // Free the board after use
    free_board(board);
}

static void begin_game_loop(Board *board) {
    // Placeholder for the actual game loop logic
    // This function would handle user input, reveal tiles, check win/loss conditions, etc.
    printf("Game loop not implemented yet.\n");

    int running = 1;
    do {
        // Game loop logic goes here
        print_board(board); // Example function to print the board state
    } while (running == 1);
}