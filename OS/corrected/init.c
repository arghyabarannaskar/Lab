#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

#define SHARED_FILE "counter.dat"
#define SHM_SIZE sizeof(int) * 2

int main() {
    int fd;
    int *shared_mem;

    // Open the shared memory file
    fd = shm_open(SHARED_FILE, O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Truncate the file to the size of the shared memory
    ftruncate(fd, SHM_SIZE);

    // Map the shared memory to the process address space
    shared_mem = (int *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize the shared memory
    shared_mem[0] = 0;  // counter
    shared_mem[1] = 0;  // read_count

    // Unmap the shared memory
    munmap(shared_mem, SHM_SIZE);

    // Close the file descriptor
    close(fd);

    // Initialize the semaphores
    sem_t *mutex = sem_open("mutex", O_CREAT, 0666, 1);
    if (mutex == SEM_FAILED) {
        perror("sem_open (mutex)");
        exit(EXIT_FAILURE);
    }
    sem_close(mutex);

    sem_t *wrt = sem_open("wrt", O_CREAT, 0666, 1);
    if (wrt == SEM_FAILED) {
        perror("sem_open (wrt)");
        exit(EXIT_FAILURE);
    }
    sem_close(wrt);

    return 0;
}

