#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {  // Child Process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Child exiting...\n");
        exit(0); // Child exits but becomes a zombie since the parent does not call wait() immediately
    } 
    else {  // Parent Process
        printf("Parent Process: PID = %d\n", getpid());
        printf("Sleeping for 10 seconds... (Check 'ps aux | grep Z' in another terminal)\n");
        sleep(10);  // Child is in zombie state during this time

        // Now parent collects the child's exit status
        wait(NULL);
        printf("Parent collected child's status, zombie removed.\n");
    }

    return 0;
}
