#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void generateFibonacci(int n, int *fibonacciArray) {
    fibonacciArray[0] = 0;
    fibonacciArray[1] = 1;

    for (int i = 2; i < n; i++) {
        fibonacciArray[i] = fibonacciArray[i - 1] + fibonacciArray[i - 2];
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_fibonacci_numbers>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "Please enter a positive integer.\n");
        return 1;
    }

    key_t key = ftok("fibonacci.c", 'R'); 

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int shmid = shmget(key, n * sizeof(int), IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    int *shm = shmat(shmid, NULL, 0);

    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    }

    if (pid == 0) {
        generateFibonacci(n, shm);
        exit(0);
    } else {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Fibonacci Sequence generated by the child process: ");
            for (int i = 0; i < n; i++) {
                printf("%d ", shm[i]);
            }
            printf("\n");
        } else {
            fprintf(stderr, "Child process terminated abnormally.\n");
        }

        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL); 
    }

    return 0;
}