#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 20

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
        item = rand() % 100; // Produce a random item

        // Wait for an empty slot in the buffer
        sem_wait(&data->empty);
        // Wait for exclusive access to the buffer
        sem_wait(&data->mutex);

        // Add the item to the buffer
        data->buffer[data->in] = item;
        data->in = (data->in + 1) % BUFFER_SIZE;
        printf("Producer produced item: %d\n", item);

        // Release exclusive access to the buffer
        sem_post(&data->mutex);
        // Signal that a full slot is available
        sem_post(&data->full);

        sleep(1); // Simulate production time
    }
}

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
    // Create shared memory object
    int shm_fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
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
    data->in = 0;
    data->out = 0;
    sem_init(&data->empty, 1, BUFFER_SIZE);
    sem_init(&data->full, 1, 0);
    sem_init(&data->mutex, 1, 1);

    // Create producer and consumer processes
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process - Consumer
        consumer(data);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process - Producer
        producer(data);

        // Wait for the child process to finish
        wait(NULL);

        // Cleanup
        sem_destroy(&data->empty);
        sem_destroy(&data->full);
        sem_destroy(&data->mutex);
        munmap(data, sizeof(shared_data));
        shm_unlink("/shared_memory");

        printf("All done!\n");
    }

    return 0;
}
