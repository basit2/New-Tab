// Problem 4.3, Filename: q3_palindrome_checker.c, Author: MD Basit Alam
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_palindrome(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int fd1[2], fd2[2];
    pid_t pid;
    char input[100];
    char result[4];

    if (pipe(fd1) == -1 || pipe(fd2) == -1) {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        close(fd1[1]);  // Close writing end of fd1
        close(fd2[0]);  // Close reading end of fd2

        while (1) {
            read(fd1[0], input, sizeof(input));
            if (strcmp(input, "quit") == 0) {
                break;
            }
            if (is_palindrome(input)) {
                strcpy(result, "YES");
            } else {
                strcpy(result, "NO");
            }
            write(fd2[1], result, sizeof(result));
        }
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    } else {
        // Parent process
        close(fd1[0]);  // Close reading end of fd1
        close(fd2[1]);  // Close writing end of fd2

        while (1) {
            printf("Enter a string: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            write(fd1[1], input, sizeof(input));
            if (strcmp(input, "quit") == 0) {
                break;
            }
            read(fd2[0], result, sizeof(result));
            printf("Child Process: %s\n", result);
        }
        close(fd1[1]);
        close(fd2[0]);
    }

    return 0;
}

