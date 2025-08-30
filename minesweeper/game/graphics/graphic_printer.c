#include "graphic_printer.h"

// function declarations
static const char* get_cell_color(Entity *e);
static void print_cell_content(Entity *e, int subcol, int subrow, const char *color);

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

// Prints the board to the terminal
void print_board(Board *b) {
    // prints a row "ySize" times (1-9)
    for (int row = 0; row < b->ySize; row++) {

        // prints the row "CELL_SIZE_Y" times (1-3)
        for (int subrow = 0; subrow < CELL_SIZE_Y; subrow++) {

            // prints cells to each collumn "xSize" times (1-9)
            for (int col = 0; col < b->xSize; col++) {
                Entity *e = &b->tiles[row][col];
                const char *color = get_cell_color(e);

                // Draw each cell with CELL_SIZE_X columns
                for (int subcol = 0; subcol < CELL_SIZE_X; subcol++) {
                    // Print the number centered if revealed and not a bomb
                    print_cell_content(e, subcol, subrow, color);
                }
                printf("%s", RESET);

                // Horizontal spacing between cells
                for (int sp = 0; sp < CELL_SPACING; sp++) {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
}

static void print_cell_content(Entity *e, int subcol, int subrow, const char *color) {
    if (e->revealed && e->type == ENTITY_EMPTY
        && subrow == CELL_SIZE_Y / 2 && subcol == CELL_SIZE_X / 2) {
        printf("%s%s%d%s%s",
            color,
            TXT_BLACK,
            e->adjacentBombs,
            RESET,
            color
        );
    }
    // Print a bomb symbol centered if revealed and is a bomb
    else if (e->revealed && e->type == ENTITY_BOMB
        && subrow == CELL_SIZE_Y / 2 && subcol == CELL_SIZE_X / 2) {
        printf("%s%s*%s%s",
            color,
            TXT_WHITE,
            RESET,
            color
        );
    }
    else {
        // Fill the rest of the cell
        printf("%s ", color);
    }
}
