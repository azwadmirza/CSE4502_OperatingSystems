#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#define SHM_SIZE 5 * sizeof(int)

bool binarySearch(int arr[], int low, int high, int key) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return true;
        }
        if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return false;
}

int main() {
    int shmid;
    key_t key; 
    FILE *fp;
    fp = fopen("shmfile","r");
    fscanf(fp,"%d",&key);
    shmid = shmget(key, SHM_SIZE, 0666);
    int *shm = shmat(shmid, NULL, 0);

    int keyToSearch;
    printf("Enter the value to search: ");
    scanf("%d", &keyToSearch);

    bool result = binarySearch(shm, 0, 4, keyToSearch);

    if (result) {
        printf("Value %d FOUND",keyToSearch);
    } else {
        printf("Value %d NOT Found\n",keyToSearch);
    }

    shmdt(shm);

    return 0;
}
