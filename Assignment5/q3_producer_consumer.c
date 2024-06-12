// Problem 5.3, Filename: q3_producer_consumer.c, Author: MD Basit Alam
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define BUFFER_SIZE 5 // Buffer size

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
} SharedBuffer;

void sem_wait(int sem_id, int sem_num) {
    struct sembuf sem_op = { sem_num, -1, 0 };
    semop(sem_id, &sem_op, 1);
}

void sem_signal(int sem_id, int sem_num) {
    struct sembuf sem_op = { sem_num, 1, 0 };
    semop(sem_id, &sem_op, 1);
}

void print_buffer(SharedBuffer *sharedBuffer) {
    printf("Buffer: ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i == sharedBuffer->in) {
            printf("[I]%d ", sharedBuffer->buffer[i]);
        } else if (i == sharedBuffer->out) {
            printf("[O]%d ", sharedBuffer->buffer[i]);
        } else {
            printf("%d ", sharedBuffer->buffer[i]);
        }
    }
    printf("\n");
}

void producer(SharedBuffer *sharedBuffer, int sem_id) {
    int item;
    while (1) {
        printf("Enter an item to produce (-1 to exit): ");
        scanf("%d", &item);
        if (item == -1) break;

        sem_wait(sem_id, 0); // Wait if buffer is full

        sharedBuffer->buffer[sharedBuffer->in] = item;
        sharedBuffer->in = (sharedBuffer->in + 1) % BUFFER_SIZE;

        sem_signal(sem_id, 1); // Signal that buffer is not empty

        printf("Produced item: %d\n", item);
        print_buffer(sharedBuffer);
    }
}

void consumer(SharedBuffer *sharedBuffer, int sem_id) {
    int item;
    char consume;
    while (1) {
        sem_wait(sem_id, 1); // Wait if buffer is empty
        
        printf("Consume an item? (y/n): ");
        scanf(" %c", &consume);
        if (consume != 'y') break;

        item = sharedBuffer->buffer[sharedBuffer->out];
        sharedBuffer->out = (sharedBuffer->out + 1) % BUFFER_SIZE;

        sem_signal(sem_id, 0); // Signal that buffer is not full

        printf("Consumed item: %d\n", item);
        print_buffer(sharedBuffer);
    }
}

int main() {
    key_t key = ftok("/tmp", 'a'); // Generate a key
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int shmid = shmget(key, sizeof(SharedBuffer), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    SharedBuffer *sharedBuffer = (SharedBuffer *)shmat(shmid, NULL, 0);
    if (sharedBuffer == (SharedBuffer *)-1) {
        perror("shmat");
        exit(1);
    }

    int sem_id = semget(key, 2, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(1);
    }

    semctl(sem_id, 0, SETVAL, BUFFER_SIZE); // Semaphore 0: Tracks free space
    semctl(sem_id, 1, SETVAL, 0); // Semaphore 1: Tracks filled space

    sharedBuffer->in = 0;
    sharedBuffer->out = 0;

    char role;
    printf("Are you a producer (p) or a consumer (c)? ");
    scanf(" %c", &role);

    if (fork() == 0) {
        if (role == 'p') {
            producer(sharedBuffer, sem_id);
        } else if (role == 'c') {
            consumer(sharedBuffer, sem_id);
        } else {
            printf("Invalid role\n");
        }
        exit(0);
    }

    wait(NULL); // Wait for child process to finish

    shmdt(sharedBuffer);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID, 0);

    return 0;
}
