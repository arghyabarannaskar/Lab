#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHM_SIZE 4096
#define NUM_INTS 100

// Structure to hold result data
struct Result {
    int max;
    int min;
    double average;
};

int main() {
    const char *name = "/my_shared_memory";
    int shm_fd;
    void *ptr;
    pid_t pid;
    
    // Create the shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object into the address space
    ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    
    // Fork the process
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        int *data = (int *)ptr;
        int i;
        int sum = 0;
        struct Result result;

        // Compute maximum, minimum, and average
        result.max = data[0];
        result.min = data[0];
        for (i = 0; i < NUM_INTS; i++) {
            sum += data[i];
            if (data[i] > result.max) {
                result.max = data[i];
            }
            if (data[i] < result.min) {
                result.min = data[i];
            }
        }
        result.average = (double)sum / NUM_INTS;

        // Write result into shared memory
        // *((struct Result *)ptr) = result;
        memcpy(ptr, &result, sizeof(struct Result));

        // Unmap the shared memory segment
        if (munmap(ptr, SHM_SIZE) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        // Exit child process
        exit(EXIT_SUCCESS);
    } else { // Parent process
        int *data = (int *)ptr;
        int i;

        // Generate and write random integers into shared memory
        srand((unsigned int) getpid());
        for (i = 0; i < NUM_INTS; i++) {
            data[i] = rand() % 100; // Generate random integer between 0 and 99
        }

        // Wait for child process to finish
        wait(NULL);

        // Read result from shared memory
        struct Result result = *((struct Result *)ptr);

        // Display result
        printf("Maximum: %d\n", result.max);
        printf("Minimum: %d\n", result.min);
        printf("Average: %.2f\n", result.average);

        // Unmap the shared memory segment
        if (munmap(ptr, SHM_SIZE) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        // Close the shared memory object
        if (close(shm_fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        // Remove the shared memory object
        if (shm_unlink(name) == -1) {
            perror("shm_unlink");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
