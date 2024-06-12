// Problem 4.2, Filename: q2_prime_numbers_parallel.c, Author: MD Basit Alam
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

void print_primes(int start, int end) {
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    pid_t pid[10];
    int range = 10000; //program prints upto range*10(i.e. total processes)

    for (int i = 0; i < 10; i++) {
        pid[i] = fork();

        if (pid[i] < 0) {
            fprintf(stderr, "Fork Failed");
            return 1;
        } else if (pid[i] == 0) {
            int start = i * range + 1;
            int end = (i + 1) * range;
            printf("\n[Child #%d, PID: %d] Created, Started printing primes from %d to %d\n",i,getpid(),start,end);
            print_primes(start, end);
            printf("\n[Child #%d, PID: %d] Exiting\n",i,getpid());
            exit(0);
        }
    }

    for (int i = 0; i < 10; i++) {
        wait(NULL);  // Wait for all child processes to complete
    }

    return 0;
}
