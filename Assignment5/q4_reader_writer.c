// Problem 5.4, Filename: q4_reader_writer.c, Author: MD Basit Alam
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define SHM_KEY 12345 // Shared memory key
#define SEM_KEY 67890 // Semaphore key
#define BUFFER_SIZE 10 // Buffer size
#define READER_DELAY 1 // Reader delay in seconds
#define WRITER_DELAY 1 // Writer delay in seconds

typedef struct {
    int data; // Shared data
    int read_count; // Number of active readers
} SharedResource;

void sem_wait(int sem_id, int sem_num) {
    struct sembuf sem_op = { sem_num, -1, 0 };
    semop(sem_id, &sem_op, 1);
}

void sem_signal(int sem_id, int sem_num) {
    struct sembuf sem_op = { sem_num, 1, 0 };
    semop(sem_id, &sem_op, 1);
}

void print_action(const char *action, const char *role, int data) {
    printf("[%s] %s: %d\n", role, action, data);
}

void reader(SharedResource *sharedResource, int sem_id, int reader_id) {
    char role[16];
    snprintf(role, sizeof(role), "Reader %d", reader_id);

    while (1) {
        sem_wait(sem_id, 1); // Mutex to update read_count
        sharedResource->read_count++;
        if (sharedResource->read_count == 1) {
            sem_wait(sem_id, 0); // Block writers if it's the first reader
        }
        printf("[%s] Read count: %d\n", role, sharedResource->read_count);
        sem_signal(sem_id, 1); // Release mutex

        // Reading section
        print_action("Reading data", role, sharedResource->data);
        sleep(READER_DELAY); // Simulate reading delay

        sem_wait(sem_id, 1); // Mutex to update read_count
        sharedResource->read_count--;
        if (sharedResource->read_count == 0) {
            sem_signal(sem_id, 0); // Allow writers if it's the last reader
        }
        printf("[%s] Read count: %d\n", role, sharedResource->read_count);
        sem_signal(sem_id, 1); // Release mutex
    }
}

void writer(SharedResource *sharedResource, int sem_id, int writer_id) {
    char role[16];
    snprintf(role, sizeof(role), "Writer %d", writer_id);

    while (1) {
        sem_wait(sem_id, 0); // Block readers and writers

        // Writing section
        sharedResource->data = rand() % 100; // Write random data
        printf("[%s] Writing data: %d\n", role, sharedResource->data);
        sleep(WRITER_DELAY); // Simulate writing delay

        sem_signal(sem_id, 0); // Release the block
    }
}


int main() {
    int shmid = shmget(SHM_KEY, sizeof(SharedResource), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    SharedResource *sharedResource = (SharedResource *)shmat(shmid, NULL, 0);
    if (sharedResource == (SharedResource *)-1) {
        perror("shmat");
        exit(1);
    }

    int sem_id = semget(SEM_KEY, 2, IPC_CREAT | 0666);
    if (sem_id < 0) {
        perror("semget");
        exit(1);
    }

    semctl(sem_id, 0, SETVAL, 1); // Semaphore 0: Controls access to resource (initially available)
    semctl(sem_id, 1, SETVAL, 1); // Semaphore 1: Mutex for read_count (initially available)

    sharedResource->data = 0;
    sharedResource->read_count = 0;

    int num_readers, num_writers;
    printf("Enter the number of readers: ");
    scanf("%d", &num_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &num_writers);

    for (int i = 0; i < num_readers; i++) {
        if (fork() == 0) {
            reader(sharedResource, sem_id, i + 1);
            exit(0);
        }
    }

    for (int i = 0; i < num_writers; i++) {
        if (fork() == 0) {
            writer(sharedResource, sem_id, i + 1);
            exit(0);
        }
    }

    for (int i = 0; i < num_readers + num_writers; i++) {
        wait(NULL); // Wait for all child processes to finish
    }

    shmdt(sharedResource);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID, 0);

    return 0;
}
