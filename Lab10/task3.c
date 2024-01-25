#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long **A;
long long **B;
long long **C;
int m,k,n;


struct ThreadData {
    int row;    
    int column; 
};


void *calculateElement(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;

    int row = data->row;
    int column = data->column;

    C[row][column] = 0;

    for (int i = 0; i < k; i++) {
        C[row][column] += A[row][i] * B[i][column];
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <m> <k> <n> to multiply matrices of m x k and k x n\n", argv[0]);
        return 1;
    }
    m=atoi(argv[1]);
    k=atoi(argv[2]);
    n=atoi(argv[3]);

    A=(long long **)malloc(m*sizeof(long long *));
    B=(long long **)malloc(k*sizeof(long long *));
    C=(long long **)malloc(m*sizeof(long long *));
    for(int i=0;i<m;i++){
        A[i]=(long long *)malloc(k*sizeof(long long));
    }
    for(int i=0;i<k;i++){
        B[i]=(long long *)malloc(n*sizeof(long long));
    }
    for(int i=0;i<m;i++){
        C[i]=(long long *)malloc(n*sizeof(long long));
    }

    printf("Input Matrix A of size %d x %d:\n",m,k);
    for(int i=0;i<m;i++){
        for(int j=0;j<k;j++){
            scanf("%lld",&A[i][j]);
        }
    }

    printf("Input Matrix B of size %d x %d:\n",k,n);
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            scanf("%lld",&B[i][j]);
        }
    }
    
    printf("\nMatrix C (Result):\n");

    pthread_t threads[m][n];
    struct ThreadData threadData[m][n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            threadData[i][j].row = i;
            threadData[i][j].column = j;

            if (pthread_create(&threads[i][j], NULL, calculateElement, (void *)&threadData[i][j]) != 0) {
                fprintf(stderr, "Error creating thread.\n");
                return 1;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (pthread_join(threads[i][j], NULL) != 0) {
                fprintf(stderr, "Error joining thread.\n");
                return 1;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%lld ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
