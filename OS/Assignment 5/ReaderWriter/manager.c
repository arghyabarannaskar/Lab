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
    int num_readers = 3; // Number of reader processes
    int num_writers = 2; // Number of writer processes

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

    // Initialize the shared data
    data->read_count = 0;
    sem_init(&data->rw_mutex, 1, 1);
    sem_init(&data->mutex, 1, 1);

    // Create reader processes
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

    // Create writer processes
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

    // Wait for all child processes to finish
    for (int i = 0; i < num_readers + num_writers; i++) {
        wait(NULL);
    }

    printf("All readers and writers have finished execution.\n");

    // Cleanup
    sem_destroy(&data->rw_mutex);
    sem_destroy(&data->mutex);
    munmap(data, sizeof(shared_data));
    shm_unlink(SHM_NAME);

    return 0;
}
