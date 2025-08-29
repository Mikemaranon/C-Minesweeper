#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Difficulty levels
typedef struct {
    int rows;
    int cols;
    int mines;
    const char* name;
} Difficulty;

static const Difficulty DIFFICULTIES[] = {
    {9, 9, 10, "Beginner"},
    {16, 16, 40, "Intermediate"},
    {16, 30, 99, "Expert"}
};

static const int NUM_DIFFICULTIES = sizeof(DIFFICULTIES) / sizeof(DIFFICULTIES[0]);

int main(void) {
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
    printf("\033[2J\033[H"); // Clear screen and move cursor to home
    printf("\n\033[1;33m"); // Yellow, bold text
    printf("╔════════════════════════════╗\n");
    printf("║         MINESWEEPER        ║\n");
    printf("╠════════════════════════════╣\n");
    printf("║                            ║\n");
    printf("║   1. \033[1;32mPlay Game\033[1;33m      ║\n");
    printf("║   2. \033[1;36mInstructions\033[1;33m   ║\n");
    printf("║   3. \033[1;31mExit\033[1;33m           ║\n");
    printf("║                            ║\n");
    printf("╚════════════════════════════╝\n");
    printf("\033[1;37m"); // Reset to white
    printf("Enter your choice (1-3): ");
    return scanf("%d", &c);
}

void show_instructions() {
    printf("\033[2J\033[H"); // Clear screen and move cursor to home
    
    // Instructions content: READ FROM instructions.txt
    FILE *file = fopen("instructions.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open instructions.txt\n");
        return;
    }

    // Read and display file contents
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);

    printf("\n\033[1;37m"); // Reset to white, new line
    printf("Press Enter to return to the menu...");
    
    // Clear input buffer and wait for Enter
    while (getchar() != '\n'); // Clear any leftover input
    getchar(); // Wait for Enter
}