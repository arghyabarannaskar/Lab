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
    const int SIZE = (NUM_SLOTS)*sizeof(int);

    //creating semaphore
    key_t key = ftok("semfile", 65); 
    int sem_E = semget(key, 1, 0666 | IPC_CREAT); //no of elements
    int sem_F = semget(key+1, 1, 0666 | IPC_CREAT); // no of free slots
    int sem_S = semget(key+2, 1, 0666 | IPC_CREAT); //binary sem for mutual exclution

    //creating queue to place produced items
    const char *name = "q2_shm";

    int shm_fd;
    int *ptr;

    shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);

    ptr = (int *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    //creating the ipc system v seamfores
    semctl(sem_S, 0, SETVAL, 1);
    semctl(sem_F, 0, SETVAL, NUM_SLOTS);
    semctl(sem_E, 0, SETVAL, 0);


    int idx=0; //index where to put the produced items
    while(1){
        int in;
        printf("\nEnter -1 to quit or enter a positive number to produce that number\n");
        scanf("%d", &in);
        if(in==-1){
            break;
        }
        semop(sem_F, &P, 1);
        semop(sem_S, &P, 1);
        

        printf("produced item %d\n", in);
        ptr[idx] = in;
        idx = (idx+1)%NUM_SLOTS;

        semop(sem_S, &V, 1);
        semop(sem_E, &V, 1);
    }

    semctl(sem_S, 0, IPC_RMID, 0);
    semctl(sem_E, 0, IPC_RMID, 0);
    semctl(sem_F, 0, IPC_RMID, 0);
    shm_unlink(name);

    return 0;
}






