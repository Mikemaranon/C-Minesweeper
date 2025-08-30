#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include "../board/board.h"

// ANSI background colors
#define RESET       "\x1b[0m"
#define GREEN       "\x1b[42m"   // hidden
#define BLUE        "\x1b[104m"  // flagged
#define LGREEN      "\x1b[102m"  // revealed empty
#define RED         "\x1b[101m"  // bomb
#define BG_WHITE    "\x1b[47m"   // white background for focus

// ANSI text colors
#define TXT_BLACK   "\x1b[30m"
#define TXT_WHITE   "\x1b[97m"

// Cell dimensions and spacing
#define CELL_SIZE_X 7
#define CELL_SIZE_Y 3
#define CELL_SPACING 2

// public function declarations
void clear_screen();
void print_board(Board *b);

#endif
