#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 20

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&empty); // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Acquire mutex lock

        // Produce item
        int item = rand() % 100;
        buffer[i % BUFFER_SIZE] = item;
        printf("Produced item: %d\n", item);

        pthread_mutex_unlock(&mutex); // Release mutex lock
        sem_post(&full); // Signal that buffer is not empty
        usleep(rand() % 100000); // Sleep for random time
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full); // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Acquire mutex lock

        // Consume item
        int item = buffer[i % BUFFER_SIZE];
        printf("Consumed item: %d\n", item);

        pthread_mutex_unlock(&mutex); // Release mutex lock
        sem_post(&empty); // Signal that buffer is not full
        usleep(rand() % 100000); // Sleep for random time
    }
    return NULL;
}

int main() {
    pthread_t prod_tid, cons_tid;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    if (pthread_create(&prod_tid, NULL, producer, NULL) != 0) {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&cons_tid, NULL, consumer, NULL) != 0) {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }

    // Wait for threads to finish
    pthread_join(prod_tid, NULL);
    pthread_join(cons_tid, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
