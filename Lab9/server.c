#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 5 * sizeof(int)

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int shmid;
    key_t key = ftok("shmfile",65);
    FILE *fp;
    fp=fopen("shmfile","w");
    fprintf(fp,"%d",key);
    fclose(fp);
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    int *shm = shmat(shmid, NULL, 0);


    printf("Enter 5 random integers: ");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &shm[i]);
    }

    bubbleSort(shm, 5);
    shmdt(shm);

    return 0;
}
