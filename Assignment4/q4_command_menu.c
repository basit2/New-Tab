// Problem 4.4, Filename: q4_command_menu.c, Author: MD Basit Alam
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


void print_menu() {
    printf("1. ls\n");
    printf("2. pwd\n");
    printf("3. uname\n");
    printf("4. exit\n");
}

int main() {
    int choice;
    char *args[2];

    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break;
        }

        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
            return 1;
        } else if (pid == 0) {
            // Child process
            switch (choice) {
                case 1:
                    args[0] = "/bin/ls";
                    args[1] = NULL;
                    execv(args[0], args);
                    break;
                case 2:
                    args[0] = "/bin/pwd";
                    args[1] = NULL;
                    execv(args[0], args);
                    break;
                case 3:
                    args[0] = "/bin/uname";
                    args[1] = NULL;
                    execv(args[0], args);
                    break;
                default:
                    printf("Invalid choice\n");
                    exit(1);
            }
        } else {
            // Parent process
            wait(NULL);  // Wait for child to finish
        }
    }

    return 0;
}
