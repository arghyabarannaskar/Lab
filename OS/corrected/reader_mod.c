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

    sem_t *mutex = sem_open("mutex", O_RDWR);
    if (mutex == SEM_FAILED) {
        perror("sem_open (mutex)");
        exit(EXIT_FAILURE);
    }

    sem_t *wrt = sem_open("wrt", O_RDWR);
    if (wrt == SEM_FAILED) {
        perror("sem_open (wrt)");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int in;
        printf("\nEnter -1 to quit or enter 1 to read the value of counter: ");
        scanf("%d", &in);
        if (in == -1) {
            break;
        }

        // Reader process
        sem_wait(mutex);
        shared_mem[1]++;
        if (shared_mem[1] == 1) {
            sem_wait(wrt);
        }
        sem_post(mutex);

        printf("Reading counter value: %d\n", shared_mem[0]);

        sem_wait(mutex);
        shared_mem[1]--;
        if (shared_mem[1] == 0) {
            sem_post(wrt);
        }
        sem_post(mutex);
    }

    // Unmap the shared memory
    munmap(shared_mem, SHM_SIZE);

    // Close the file descriptor
    close(fd);

    // Close the semaphores
    sem_close(mutex);
    sem_close(wrt);

    return 0;
}

