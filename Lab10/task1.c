#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int isPrime(int num) {
    if (num < 2) {
        return 0;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; 
        }
    }
    return 1; 
}


void *printPrimes(void *arg) {
    int n = *((int *)arg);
    
    printf("Prime numbers up to %d: ", n);

    for (int i = 2; i <= n; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }

    printf("\n");

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "Please enter a positive integer.\n");
        return 1;
    }

    pthread_t tid;

    if (pthread_create(&tid, NULL, printPrimes, &n) != 0) {
        fprintf(stderr, "Error creating thread.\n");
        return 1;
    }

    if (pthread_join(tid, NULL) != 0) {
        fprintf(stderr, "Error joining thread.\n");
        return 1;
    }

    return 0;
}
