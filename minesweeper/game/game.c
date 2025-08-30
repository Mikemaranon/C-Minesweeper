#include "game.h"
#include "board/board.h"
#include "graphics/graphic_printer.h"
#include "sysconf/sysconf.h"

static void begin_game_loop(Board *board);

// Function that starts the game
void start_game(const char* difficulty, int rows, int cols, int mines) {
    printf("Starting Minesweeper with difficulty level %s...\n", difficulty);

    Board *board = create_board(rows, cols, mines);  // intialyze board
    if (!board) return;

    printf("Board is ready. Let's play!\n");
    begin_game_loop(board); // Start the game loop (not implemented here)

    free_board(board); // Free the board after use
}

static void begin_game_loop(Board *board) {

    int running = 1;
    char ch;

    set_raw_mode(1);

    do {
        clear_screen();
        print_board(board); // Example function to print the board state

        if (read(STDIN_FILENO, &ch, 1) > 0) {
            switch (ch) {
                case 'o':
                case 'O':
                    break;
                case 'w':
                case 'W':
                    break;
                case 'a':
                case 'A':
                    break;
                case 's':
                case 'S':
                    break;
                case 'd':
                case 'D':
                    break;
                case 10: // Enter
                    break;
                case 127: // backspace
                    break;
                case 'q': // exit
                case 'Q':
                    running = 0;
                    break;
            }
        }
    } while (running == 1);
}