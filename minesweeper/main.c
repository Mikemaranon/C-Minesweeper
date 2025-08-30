#include "main.h"
#include "game/game.h"
#include "game/graphics/graphic_printer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const Difficulty DIFFICULTIES[] = {
    {5, 5, 5, "Beginner"},
    {12, 12, 30, "Intermediate"},
    {18, 18, 65, "Expert"}
};

const int NUM_DIFFICULTIES = sizeof(DIFFICULTIES) / sizeof(DIFFICULTIES[0]);

int main(void) {
    clear_screen();
    printf("Welcome to the Game!\n");
    
    int choice;
    bool menu = true;
    // Main menu loop
    while (menu) {        
        choice = print_menu();

        // Set menu to false if input is valid (1-3)
        if (choice >= 1 && choice <= 3) {
            switch (choice) {
                case 1:
                    run_game();
                    menu = true;
                    break;
                case 2:
                    show_instructions();
                    menu = true;
                    break;
                case 3:
                    printf("Exiting the game. Goodbye!\n");
                    menu = false;
                    break;
                
                default:
                    printf("Invalid choice! Please select a valid option.\n");
                    break;
            }
        } else {
            printf("Invalid input! Please enter a number between 1 and 3.\n");
            // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    return 0;
}

int print_menu() {
    int c;
    clear_screen();

    printf("\n\033[1;33m"); // Yellow, bold text
    printf("╔════════════════════════════╗\n");
    printf("║         MINESWEEPER        ║\n");
    printf("╠════════════════════════════╣\n");
    printf("║                            ║\n");
    printf("║     1. \033[1;32mPlay Game\033[1;33m           ║\n");
    printf("║     2. \033[1;36mInstructions\033[1;33m        ║\n");
    printf("║     3. \033[1;31mExit\033[1;33m                ║\n");
    printf("║                            ║\n");
    printf("╚════════════════════════════╝\n");
    printf("\033[1;37m"); // Reset to white
    printf("Enter your choice (1-3): ");
    if (scanf("%d", &c) != 1) {
        // clean buffer for invalid input
        int tmp;
        while ((tmp = getchar()) != '\n' && tmp != EOF);
        return -1; // invalid input
    }
    return c;
}

void show_instructions() {
    clear_screen();

    FILE *file = fopen("minesweeper/assets/instructions.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open instructions.txt\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Loop through the buffer and replace literal "\033" with the real ESC character
        for (char *p = buffer; *p; ++p) {
            if (*p == '\\' && *(p+1) == '0' && *(p+2) == '3' && *(p+3) == '3') {
                putchar('\x1B'); // Insert the real ESC character
                p += 3;          // Skip over "033"
            } else {
                putchar(*p);     // Print the current character as-is
            }
        }
    }

    fclose(file);

    printf("\033[0m\n"); // Reset colors at the end
    printf("Press Enter to return to the menu...");

    // Clear input buffer and wait for Enter
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}


void run_game() {
    clear_screen();
    
    printf("╔════════════════════════════════════════╗\n");
    printf("║         Select Difficulty Level        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    for (int i = 0; i < NUM_DIFFICULTIES; i++) {
        printf("║ %d. %s (%dx%d with %d mines)\n", i + 1, DIFFICULTIES[i].name, DIFFICULTIES[i].rows, DIFFICULTIES[i].cols, DIFFICULTIES[i].mines);
        printf("╚═════════════════════════════════════════\n");
    }
    printf("Enter your choice (1-%d): ", NUM_DIFFICULTIES);
    
    int choice;
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > NUM_DIFFICULTIES) {
        printf("Invalid input! Returning to menu.\n");
        // Clear input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    Difficulty selected = DIFFICULTIES[choice - 1];
    printf("Starting %s game with %dx%d grid and %d mines...\n", selected.name, selected.rows, selected.cols, selected.mines);
    
    start_game(selected.name, selected.rows, selected.cols, selected.mines); // Call the game start function from game.c
    
    printf("Press Enter to return to the menu...");
    while (getchar() != '\n'); // Clear any leftover input
    getchar(); // Wait for Enter
}