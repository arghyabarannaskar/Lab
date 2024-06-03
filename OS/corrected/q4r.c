#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

#include <sys/ipc.h>
#include <sys/sem.h>

#define NUM_SLOTS 5

struct sembuf P = {0, -1, 0}; // P operation wait
struct sembuf V = {0, 1, 0};  // V operation siganl

int main() {
    const int SIZE = (2)*sizeof(int);

    //creating semaphore
    key_t key = ftok("semfile", 65); 
    int rw_mutex = semget(key, 1, 0666); //no of elements
    int mutex = semget(key+1, 1, 0666); // no of free slots

    //creating queue to place produced items
    const char *name = "q4_shm";

    int shm_fd;
    int *ptr;

    shm_fd = shm_open(name, O_RDWR, 0666);
    // ftruncate(shm_fd, SIZE);

    int *counter; //lets assume writers write to counter by incrimenting and reader reads it
    int *read_count;

    counter = (int *)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    read_count = counter+1;

    // printf("counter %d\n", *counter);
    // printf("read_count %d\n", *read_count);

    while(1){
        int in;
        printf("\nEnter -1 to quit or enter a positive number(1) to read the value of counter\n");
        scanf("%d", &in);
        if(in==-1){
            break;
        }
        semop(mutex, &P, 1);
        // printf("here\n");
        // printf("read count %d\n", *read_count);
        *read_count = *read_count+1; 
        if(*read_count==1){
            semop(rw_mutex, &P, 1);
        }
        semop(mutex, &V, 1);

        printf("reading counter value as %d\n",*counter);

        semop(mutex, &P, 1);
        *read_count = *read_count-1;
        if(*read_count==0){
            semop(rw_mutex, &V, 1);
        }
        semop(mutex, &V, 1);
    }

    semctl(rw_mutex, 0, IPC_RMID, 0);
    semctl(mutex, 0, IPC_RMID, 0);
    shm_unlink(name);

    return 0;
}