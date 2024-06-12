// Problem 5.2, Filename: q2_string_printing_semaphore_sync.c, Author: MD Basit Alam
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// Semaphore operations
struct sembuf P = {0, -1, 0};  // P operation
struct sembuf V = {0, 1, 0};   // V operation
void P1(int sem_A, int sem_B) {
    int val_A;
    for (int i = 0; i < 20; i++) {
        // val_A = semctl(sem_A, 0, GETVAL);
        // printf("%d\n", val_A);
        semop(sem_A, &P, 1);
        printf("A");
        fflush(stdout);
        // int val_A = semctl(sem_A, 0, GETVAL);
        // printf("%d\n", val_A);
        semop(sem_B, &V, 1);
    }
}
void P2(int sem_B, int sem_C, int sem_A) {
    int turn = 0;
    for (int i = 0; i < 20; i++) {
        // Wait on sem_B
        semop(sem_B, &P, 1);
        printf("B");
        fflush(stdout);
        if (turn == 0) {
            semop(sem_C, &V, 1);
            turn = 1;
        } else {
            semop(sem_A, &V, 1);
            turn = 0;
        }
    }
}
void P3(int sem_C, int sem_A) {
    int turn = 0;
    for (int i = 0; i < 20; i++) {
        // Wait on sem_C
        semop(sem_C, &P, 1);
        printf("C");
        fflush(stdout);
        if (turn == 0) {
            semop(sem_C, &V, 1);
            turn = 1;
        } else {
            semop(sem_A, &V, 1);
            turn = 0;
        }
    }
}
int main() {
    key_t key = ftok("semfile", 65);  // Generate a unique key
    // Create semaphores
    int sem_A = semget(key, 1, 0666 | IPC_CREAT);
    int sem_B = semget(key + 1, 1, 0666 | IPC_CREAT);
    int sem_C = semget(key + 2, 1, 0666 | IPC_CREAT);
    // Initialize semaphores
    semctl(sem_A, 0, SETVAL, 1);  // P1 starts first
    semctl(sem_B, 0, SETVAL, 0);
    semctl(sem_C, 0, SETVAL, 0);
    if (fork() == 0) {
        P1(sem_A, sem_B);
        exit(0);
    }
    if (fork() == 0) {
        P2(sem_B, sem_C, sem_A);
        exit(0);
    }
    if (fork() == 0) {
        P3(sem_C, sem_A);
        exit(0);
    }
    // Wait for children to complete
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("\n");
    // Clean up semaphores
    semctl(sem_A, 0, IPC_RMID, 0);
    semctl(sem_B, 0, IPC_RMID, 0);
    semctl(sem_C, 0, IPC_RMID, 0);
    return 0;
}