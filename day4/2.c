#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n, i;
    
    printf("Enter the number of child processes to create: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid_t pid = fork(); // Create a child process

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } 
        else if (pid == 0) { // Child process
            printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
            exit(0); // Exit child process to prevent unwanted forking
        }
    }

    // Parent process waits for all child processes to complete
    for (i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("Parent Process: PID = %d\n", getpid());
    return 0;
}
