#include "game.h"
#include "board/board.h"
#include "graphics/graphic_printer.h"
#include "sysconf/sysconf.h"

static void beginGameLoop(Board *board);

// Function that starts the game
void start_game(const char* difficulty, int rows, int cols, int mines) {
    printf("Starting Minesweeper with difficulty level %s...\n", difficulty);

    Board *board = create_board(rows, cols, mines);  // intialyze board
    if (!board) return;

    printf("Board is ready. Let's play!\n");
    beginGameLoop(board); // Start the game loop (not implemented here)

    free_board(board); // Free the board after use
}

static void beginGameLoop(Board *board) {

    int running = 1;
    char ch;

    set_raw_mode(1);

    do {
        clear_screen();
        print_board(board); // Example function to print the board state

        if (read(STDIN_FILENO, &ch, 1) > 0) {
            switch (ch) {
                case 'w':
                case 'W':
                    move_cursor(board, 0, -1);
                    break;
                case 'a':
                case 'A':
                    move_cursor(board, -1, 0);
                    break;
                case 's':
                case 'S':
                    move_cursor(board, 0, 1);
                    break;
                case 'd':
                case 'D':
                    move_cursor(board, 1, 0);
                    break;
                case 10: // Enter
                    flag_tile(board);
                    break;
                case 127: // backspace
                    reveal_tile(board);
                    break;
                case 'q': // exit
                case 'Q':
                    running = 0;
                    set_raw_mode(0);
                    break;
            }
        }
    } while (running == 1);
}