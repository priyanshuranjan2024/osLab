#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_child(char *name) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) { // Child process
        printf("%s: PID = %d, Parent PID = %d\n", name, getpid(), getppid());
        sleep(1); // Sleep to ensure process hierarchy visibility
    } 
    else {
        wait(NULL); // Parent waits for child to finish
    }
}

int main() {
    printf("Parent Process: P1, PID = %d\n", getpid());

    pid_t p2 = fork();
    if (p2 == 0) {
        printf("P2: PID = %d, Parent PID = %d\n", getpid(), getppid());
        create_child("P6"); // P2 -> P6
        create_child("P5"); // P2 -> P5

        pid_t p5 = fork();
        if (p5 == 0) {
            printf("P5: PID = %d, Parent PID = %d\n", getpid(), getppid());
            create_child("P7"); // P5 -> P7
            exit(0);
        }
        wait(NULL); // P2 waits for P5
        exit(0);
    }

    pid_t p3 = fork();
    if (p3 == 0) {
        printf("P3: PID = %d, Parent PID = %d\n", getpid(), getppid());
        create_child("P4"); // P3 -> P4
        exit(0);
    }

    // P1 waits for P2 and P3 to complete
    wait(NULL);
    wait(NULL);

    return 0;
}
