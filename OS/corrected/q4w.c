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
    const int SIZE = 4*sizeof(int);

    //creating semaphore
    key_t key = ftok("semfile", 65); 
    int rw_mutex = semget(key, 1, 0666 | IPC_CREAT); //no of elements
    int mutex = semget(key+1, 1, 0666 | IPC_CREAT); // no of free slots

    //creating queue to place produced items
    const char *name = "q4_shm";

    int shm_fd;
    int *counter; //lets assume writers write to counter by incrimenting and reader reads it
    int *read_count;

    
    shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);

    counter = (int *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    *counter = 0;
    read_count = (int *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);//index 1 of shared memory is read_count variable
    read_count = counter +1;
    *read_count = 0;

    // printf("read count %d\n", *counter);

    //creating the ipc system v seamfores
    semctl(rw_mutex, 0, SETVAL, 1);
    semctl(mutex, 0, SETVAL, 1);



    int idx=0; //index where to put the produced items
    while(1){
        int in;
        printf("\nEnter -1 to quit or enter a positive number (1) to write(increment counter)\n");
        scanf("%d", &in);
        if(in==-1){
            break;
        }
        semop(rw_mutex, &P, 1);
        *counter = *counter+1;
        printf("writing to counter, now value of counter is %d\n", *counter);

        semop(rw_mutex, &V, 1);
    }

    semctl(rw_mutex, 0, IPC_RMID, 0);
    semctl(mutex, 0, IPC_RMID, 0);
    shm_unlink(name);

    return 0;
}
