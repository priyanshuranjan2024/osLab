#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>

// Function to clear the screen
void clear_screen() {
    printf("\033[H\033[J"); // ANSI escape code for clearing screen
}

// Function to move cursor
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
    fflush(stdout);
}

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) { // Child Process - Moves horizontally
        int col = 1;
        while (col <= 50) { // Adjust as needed
            clear_screen();
            move_cursor(10, col);
            printf("0");
            fflush(stdout);
            usleep(100000); // Slow movement
            col++;
        }
        exit(0);
    } 
    else { // Parent Process - Moves vertically
        int row = 1;
        while (row <= 20) { // Adjust as needed
            clear_screen();
            move_cursor(row, 25);
            printf("0");
            fflush(stdout);
            usleep(100000); // Slow movement
            row++;
        }
        wait(NULL); // Wait for child
    }

    return 0;
}
