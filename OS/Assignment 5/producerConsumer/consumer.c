#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20
#define SHM_NAME "/shared_memory"

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} shared_data;

void consumer(shared_data *data) {
    int item;
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Wait for a full slot in the buffer
        sem_wait(&data->full);
        // Wait for exclusive access to the buffer
        sem_wait(&data->mutex);

        // Remove the item from the buffer
        item = data->buffer[data->out];
        data->out = (data->out + 1) % BUFFER_SIZE;
        printf("Consumer consumed item: %d\n", item);

        // Release exclusive access to the buffer
        sem_post(&data->mutex);
        // Signal that an empty slot is available
        sem_post(&data->empty);

        sleep(1); // Simulate consumption time
    }
}

int main() {
    // Open the shared memory object
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object into the address space
    shared_data *data = (shared_data *)mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Run the consumer
    consumer(data);

    // Cleanup
    munmap(data, sizeof(shared_data));

    return 0;
}
