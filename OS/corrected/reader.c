#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

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
    int shmid = shmget(SHM_KEY, sizeof(int), 0666|IPC_CREAT);
    int *read_count = (int *)shmat(shmid, NULL, 0);
    
    int semid = semget(SEM_KEY, 2, 0666|IPC_CREAT);
    
    // Semaphores: 0 - mutex, 1 - resource
    // Initialize semaphores (this should be done only once, typically in a separate initialization script or program)
    union semun sem_union;
    sem_union.val = 1;
    semctl(semid, 0, SETVAL, sem_union);  // mutex semaphore
    sem_union.val = 1;
    semctl(semid, 1, SETVAL, sem_union);  // resource semaphore
    
    while (1) {
        down(semid, 0);  // down(mutex)
        (*read_count)++;
        if (*read_count == 1) {
            down(semid, 1);  // down(resource)
        }
        up(semid, 0);  // up(mutex)
        
        // Reading section
        printf("Reader %d is reading\n", getpid());
        sleep(1);  // Simulate reading time
        
        down(semid, 0);  // down(mutex)
        (*read_count)--;
        if (*read_count == 0) {
            up(semid, 1);  // up(resource)
        }
        up(semid, 0);  // up(mutex)
        
        sleep(1);  // Simulate time between reads
    }
    
    shmdt(read_count);
    return 0;
}

