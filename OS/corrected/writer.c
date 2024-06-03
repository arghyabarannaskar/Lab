#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

#define SEM_KEY 5678

void down(int semid, int semnum) {
    struct sembuf sop;
    sop.sem_num = semnum;
    sop.sem_op = -1;
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

void up(int semid, int semnum) {
    struct sembuf sop;
    sop.sem_num = semnum;
    sop.sem_op = 1;
    sop.sem_flg = 0;
    semop(semid, &sop, 1);
}

int main() {
    int semid = semget(SEM_KEY, 2, 0666|IPC_CREAT);
    
    while (1) {
        down(semid, 1);  // down(resource)
        
        // Writing section
        printf("Writer %d is writing\n", getpid());
        sleep(2);  // Simulate writing time
        
        up(semid, 1);  // up(resource)
        
        sleep(3);  // Simulate time between writes
    }
    
    return 0;
}

