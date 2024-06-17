#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "shared.h"
#include<time.h>

int main() {
    pid_t pid;
    int num_readers = 3; 
    int num_writers = 2; 

    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(shm_fd, sizeof(shared_data)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    shared_data *data = (shared_data *)mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    data->read_count = 0;
    //the third argument initializes the value of the semaphore
    //rw_mutex semaphore is used to control access to the shared resource when writing,
    // ensuring that only one writer can access the resource at a time.
    sem_init(&data->rw_mutex, 1, 1); // semaphore is shared between threads or processes. A value 0 will
    sem_init(&data->mutex, 1, 1); // indicate semaphore is private to the current process.
    //data->mutex to provide mutual exclusion while accessing read_count


    for (int i = 0; i < num_readers; i++) {
        if ((pid = fork()) == 0) {
            char *args[] = {"./reader", NULL};
            execv(args[0], args);
            perror("execv");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_writers; i++) {
        if ((pid = fork()) == 0) {
            char *args[] = {"./writer", NULL};
            execv(args[0], args);
            perror("execv");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num_readers + num_writers; i++) {
        wait(NULL);
    }

    printf("All readers and writers have finished execution.\n");

    sem_destroy(&data->rw_mutex);
    sem_destroy(&data->mutex);
    munmap(data, sizeof(shared_data));
    shm_unlink(SHM_NAME);

    return 0;
}