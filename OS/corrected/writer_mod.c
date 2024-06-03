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
    fd = shm_open(SHARED_FILE, O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory to the process address space
    shared_mem = (int *)mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    sem_t *wrt = sem_open("wrt", O_RDWR);
    if (wrt == SEM_FAILED) {
        perror("sem_open (wrt)");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int in;
        printf("\nEnter -1 to quit or enter 1 to write (increment counter): ");
        scanf("%d", &in);
        if (in == -1) {
            break;
        }

        // Writer process
        sem_wait(wrt);
        shared_mem[0]++;
        printf("Writing to counter, new value: %d\n", shared_mem[0]);
        sem_post(wrt);
    }

    // Unmap the shared memory
    munmap(shared_mem, SHM_SIZE);

    // Close the file descriptor
    close(fd);

    // Close the semaphore
    sem_close(wrt);

    return 0;
}

