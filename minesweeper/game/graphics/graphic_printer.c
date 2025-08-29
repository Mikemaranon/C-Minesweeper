#include <stdio.h>
#include "graphic_printer.h"
#include "../board/board.h"

// ANSI background colors
#define RESET   "\x1b[0m"
#define GREEN   "\x1b[42m"   // hidden
#define BLUE    "\x1b[104m"  // flagged
#define LGREEN  "\x1b[102m"  // revealed empty
#define RED     "\x1b[101m"  // bomb

// ANSI text colors
#define TXT_BLACK "\x1b[30m"
#define TXT_WHITE "\x1b[97m"

// Cell dimensions and spacing
#define CELL_SIZE 6
#define CELL_SPACING 2

// Selects background color depending on entity state
static const char* get_cell_color(Entity *e) {
    if (!e->revealed) {
        if (e->type == ENTITY_FLAG) return BLUE;
        return GREEN;
    } else {
        if (e->type == ENTITY_BOMB) return RED;
        return LGREEN;
    }
}

// Clears the terminal screen
void clear_screen() {
    printf("\033[H\033[J");
}

// Prints the game board with graphical cells
void print_board(Board *b) {
    for (int r = 0; r < b->ySize; r++) {
        // Each cell occupies CELL_SIZE rows
        for (int subrow = 0; subrow < CELL_SIZE; subrow++) {
            for (int c = 0; c < b->xSize; c++) {
                Entity *e = &b->tiles[r][c];
                const char *color = get_cell_color(e);

                // Draw each cell with CELL_SIZE columns
                for (int subcol = 0; subcol < CELL_SIZE; subcol++) {
                    // Print number centered if revealed and not a bomb
                    if (e->revealed && e->type == ENTITY_EMPTY
                        && subrow == CELL_SIZE/2 && subcol == CELL_SIZE/2) {
                        printf("%s%s%d%s%s",
                            color,
                            TXT_BLACK,
                            e->adjacentBombs,
                            RESET,
                            color
                        );
                    }
                    // Print a bomb symbol if revealed and it is a bomb
                    else if (e->revealed && e->type == ENTITY_BOMB
                        && subrow == CELL_SIZE/2 && subcol == CELL_SIZE/2) {
                        printf("%s%s*%s%s",
                            color,
                            TXT_WHITE,
                            RESET,
                            color
                        );
                    }
                    else {
                        // Fill rest of the cell
                        printf("%s ", color);
                    }
                }
                printf("%s", RESET);

                // Horizontal spacing between cells
                for (int sp = 0; sp < CELL_SPACING; sp++) {
                    printf(" ");
                }
            }
            printf("\n");
        }
        // Vertical spacing between rows
        for (int sp = 0; sp < CELL_SPACING; sp++) {
            printf("\n");
        }
    }
}
