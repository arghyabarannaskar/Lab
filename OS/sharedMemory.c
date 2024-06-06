#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define SHARED_MEM_SIZE 4096

int main() {
    const char *name = "/my_shared_memory";
    int shm_fd;
    void *ptr;

    // Step 1: Create the shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Step 2: Configure the size of the shared memory object
    if (ftruncate(shm_fd, SHARED_MEM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Step 3: Map the shared memory object into the address space
    ptr = mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Write to the shared memory
        const char *message = "Hello from the child process!";
        printf("Child: Writing to shared memory: %s\n", message);
        sprintf(ptr, "%s", message);

        // Unmap the shared memory segment
        if (munmap(ptr, SHARED_MEM_SIZE) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
        // Wait for the child process to finish
        wait(NULL);

        // Read from the shared memory
        printf("Parent: Reading from shared memory: %s\n", (char *)ptr);

        // Unmap the shared memory segment
        if (munmap(ptr, SHARED_MEM_SIZE) == -1) {
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
