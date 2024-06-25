#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 1000 
#define SHM_NAME "/shared_memory"

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} shared_data;

void producer(shared_data *data) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        item = rand() % 100; 

        // Check if buffer is full
        if (sem_trywait(&data->empty) == -1) {
            printf("Buffer is full. Waiting...\n");
            sem_wait(&data->empty); // Wait for an empty slot
        }

        // Wait for exclusive access to the buffer
        sem_wait(&data->mutex);

        // Add the item to the buffer
        data->buffer[data->in] = item;
        data->in = (data->in + 1) % BUFFER_SIZE;
        printf("Producer produced item %d at: %d\n", item, data->in);

        // Release exclusive access to the buffer
        sem_post(&data->mutex);
        // Signal that a full slot is available
        sem_post(&data->full);

        sleep(1); // Producer's production time
    }
}

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    shared_data *data = (shared_data *)mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    producer(data);

    munmap(data, sizeof(shared_data));

    return 0;
}
