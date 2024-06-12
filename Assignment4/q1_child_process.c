// Problem 4.1, Filename: q1_child_process.c, Author: MD Basit Alam
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        // Error creating child
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(0);
    } else {
        // Parent process
        wait(&status);  // Wait for child to complete
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
        printf("Child Exit Status = %d\n", WIFEXITED(status));
    }

    return 0;
}
