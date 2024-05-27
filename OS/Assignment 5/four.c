#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int shared_data = 0;
int num_readers = 0;
sem_t mutex, rw_mutex;

void *reader(void *arg) {
    while (1) {
        sem_wait(&mutex); // Acquire mutex to protect num_readers
        num_readers++;
        if (num_readers == 1) {
            sem_wait(&rw_mutex); // If first reader, acquire rw_mutex to block writers
        }
        sem_post(&mutex); // Release mutex

        // Read shared data
        printf("Reader %ld read: %d\n", (long)arg, shared_data);
        usleep(rand() % 1000000); // Sleep for random time

        sem_wait(&mutex); // Acquire mutex to protect num_readers
        num_readers--;
        if (num_readers == 0) {
            sem_post(&rw_mutex); // If last reader, release rw_mutex to allow writers
        }
        sem_post(&mutex); // Release mutex

        usleep(rand() % 1000000); // Sleep for random time
    }
    return NULL;
}

void *writer(void *arg) {
    while (1) {
        sem_wait(&rw_mutex); // Acquire rw_mutex to block other writers and readers

        // Write to shared data
        shared_data++;
        printf("Writer %ld wrote: %d\n", (long)arg, shared_data);
        usleep(rand() % 1000000); // Sleep for random time

        sem_post(&rw_mutex); // Release rw_mutex to allow other writers and readers
        usleep(rand() % 1000000); // Sleep for random time
    }
    return NULL;
}

int main() {
    pthread_t reader_tid[NUM_READERS], writer_tid[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1); // mutex for protecting num_readers
    sem_init(&rw_mutex, 0, 1); // rw_mutex for controlling access to shared_data

    // Create reader threads
    for (long i = 0; i < NUM_READERS; i++) {
        if (pthread_create(&reader_tid[i], NULL, reader, (void *)i) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    // Create writer threads
    for (long i = 0; i < NUM_WRITERS; i++) {
        if (pthread_create(&writer_tid[i], NULL, writer, (void *)i) != 0) {
            perror("pthread_create failed");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for reader threads to finish
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_tid[i], NULL);
    }

    // Wait for writer threads to finish
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_tid[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
