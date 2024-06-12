// Problem 5.1, Filename: q1_shared_memory_communication.c, Author: MD Basit Alam
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h> // Include the header for wait()

#define SHM_SIZE  sizeof(int) * 103   // size of shared memory segment

// Structure for storing computation results
struct Results {
    int max;
    int min;
    double avg;
};

int main() {
    int shmid;
    key_t key;
    int *shm;
    struct Results *result;

    // Generate a unique key for shared memory
    key = ftok(".", 's');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the address space
    shm = (int *)shmat(shmid, NULL, 0);
    if (shm == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    // Custom set of integers
    int custom_numbers[100] = {
        87, 45, 23, 56, 92, 14, 78, 35, 10, 67,
        29, 58, 91, 42, 74, 63, 17, 81, 50, 95,
        38, 70, 25, 82, 49, 60, 72, 36, 68, 11,
        93, 15, 88, 31, 77, 22, 46, 64, 19, 79,
        51, 96, 41, 83, 55, 71, 33, 84, 54, 65,
        39, 80, 57, 26, 73, 12, 66, 28, 43, 75,
        18, 89, 20, 94, 59, 76, 44, 30, 47, 21,
        62, 90, 27, 85, 52, 40, 86, 53, 16, 69,
        37, 61, 34, 48, 24, 3, 98, 1, 7, 99,
        2, 6, 100, 5, 97, 8, 4, 9, 32, 0
    };

    // Copy custom numbers to shared memory
    for (int i = 0; i < 100; ++i) {
        shm[i] = custom_numbers[i];
    }

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        result = (struct Results *)(shm + 100); // Pointer to the result area in shared memory

        int max = shm[0];
        int min = shm[0];
        double sum = 0;

        for (int i = 0; i < 100; i++) {
            int num = shm[i];
            sum += num;

            if (num > max)
                max = num;
            if (num < min)
                min = num;
        }

        result->max = max;
        result->min = min;
        result->avg = sum / 100.0;

        // Detach the shared memory segment
        shmdt(shm);

    } else {
        // Parent process
        // Wait for the child to finish computation
        wait(NULL);

        result = (struct Results *)(shm + 100); // Pointer to the result area in shared memory

        printf("Maximum: %d\n", result->max);
        printf("Minimum: %d\n", result->min);
        printf("Average: %.2f\n", result->avg);

        // Detach the shared memory segment
        shmdt(shm);

        // Remove the shared memory segment
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
