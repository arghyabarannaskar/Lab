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

#define NUM_VALUES 10

typedef struct {
    int max;
    int min;
    double avg;
} Result;

struct sembuf P = {0, -1, 0}; // P operation wait
struct sembuf V = {0, 1, 0};  // V operation siganl

void generateRandomNumbers(double* numbers) {
    srand(time(NULL));
    for (int i = 0; i < NUM_VALUES; i++) {
        numbers[i] = rand() % 1000;
    }
}

int main() {
    const int SIZE = (NUM_VALUES+5)*sizeof(double);
    pid_t childPid;
    Result* result;

    //creating semaphore
    key_t key = ftok("semfile", 65); 
    int sem_A = semget(key, 1, 0666 | IPC_CREAT);

    semctl(sem_A, 0, SETVAL, 0); 

    // Create child process
    childPid = fork();

    if (childPid < 0) {
        perror("fork");
        exit(1);
    } else if (childPid == 0) {
        // Child process

        // usleep(1000);

        semop(sem_A, &P, 1);

        const char *name = "q2_shm";

        int shm_fd;
        double *ptr;

        shm_fd = shm_open(name, O_RDWR, 0666);
        // ftruncate(shm_fd, SIZE);


        ptr = (double *)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);


        double max = ptr[0];
        double min = ptr[0];
        // printf("\nmax%.2f\n", max);
        // printf("\nmin %.2f\n", min);
        double s = 0;
        for(int i=0;i<NUM_VALUES;i++){
            // printf("%d ", ptr[i]);
            if(ptr[i]>max){
                // printf("\ngreater %.2f\n", ptr[i]);
                max = ptr[i];
            }
            if(ptr[i]<min){
                // printf("\nsmaller %.2f\n", ptr[i]);
                min = ptr[i];
            }
            s += ptr[i];
        }
        ptr[NUM_VALUES] = max;
        ptr[NUM_VALUES+1] = min;
        ptr[NUM_VALUES+2] = s/NUM_VALUES;
        // semop(sem_A, &V, 1);

        semctl(sem_A, 0, IPC_RMID, 0);

        exit(0);
    } else {
        // Parent process
        const char *name = "q2_shm";

        int shm_fd;
        double *ptr;

        shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
        ftruncate(shm_fd, SIZE);


        ptr = (double *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

        // Generate random numbers
        double numbers[NUM_VALUES];
        generateRandomNumbers(numbers);

        for(int i = 0; i < NUM_VALUES; i++){
            printf("%.1f ", numbers[i]);
        }
        // Write numbers into shared memory
        for (int i = 0; i < NUM_VALUES; i++) {
            // sharedMemory[i] = numbers[i];
            ptr[i] = numbers[i];
        }
        printf("\n");
        semop(sem_A, &V, 1);

        // Wait for the child to finish computation
        wait(NULL);

        printf("Maximum: %.2f\n", ptr[NUM_VALUES]);
        printf("Minimum: %.2f\n", ptr[NUM_VALUES+1]);
        printf("Average: %.2f\n", ptr[NUM_VALUES+2]);

        semctl(sem_A, 0, IPC_RMID, 0);
    }

    return 0;
}
