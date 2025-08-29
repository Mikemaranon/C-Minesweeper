#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdbool.h>

// Difficulty levels
typedef struct {
    int rows;
    int cols;
    int mines;
    const char* name;
} Difficulty;

extern const Difficulty DIFFICULTIES[];
extern const int NUM_DIFFICULTIES;

// Menu functions
int print_menu(void);
void show_instructions(void);
void run_game(void);

#endif // MINESWEEPER_H
