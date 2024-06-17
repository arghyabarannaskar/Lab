#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SHM_NAME "/shared_memory"
#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} shared_data;

int main() {
    pid_t pid1, pid2;

    // Create shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, sizeof(shared_data)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object into the address space
    shared_data *data = (shared_data *)mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize the shared data (only by the manager)
    data->in = 0;
    data->out = 0;
    sem_init(&data->empty, 1, BUFFER_SIZE);
    sem_init(&data->full, 1, 0);
    sem_init(&data->mutex, 1, 1);

    // Fork the first child to run the producer
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }else if (pid1 == 0) {
        char *args[] = {"./producer", NULL};
        execv(args[0], args);
        perror("execv");
        exit(EXIT_FAILURE);
    } else {
        pid2 = fork();
        if(pid2 == 0){
            char *args[] = {"./consumer", NULL};
            execv(args[0], args);
            perror("execv");
            exit(EXIT_FAILURE);
        }else if (pid2 < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    } 

    // Wait for both children to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Both producer and consumer have finished execution.\n");

    // Cleanup
    sem_destroy(&data->empty);
    sem_destroy(&data->full);
    sem_destroy(&data->mutex);
    munmap(data, sizeof(shared_data));
    shm_unlink(SHM_NAME);

    return 0;
}