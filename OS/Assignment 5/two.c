#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Define semaphores
sem_t sem_P1, sem_P2, sem_P3;

// Function prototypes
void *P1(void *arg);
void *P2(void *arg);
void *P3(void *arg);

int main() {
    // Initialize semaphores
    sem_init(&sem_P1, 0, 1);  // Initialized with 1 to allow P1 to execute first
    sem_init(&sem_P2, 0, 0);
    sem_init(&sem_P3, 0, 0);

    // Create threads for each process
    pthread_t thread_P1, thread_P2, thread_P3;
    pthread_create(&thread_P1, NULL, P1, NULL);
    pthread_create(&thread_P2, NULL, P2, NULL);
    pthread_create(&thread_P3, NULL, P3, NULL);

    // Wait for threads to finish
    pthread_join(thread_P1, NULL);
    pthread_join(thread_P2, NULL);
    pthread_join(thread_P3, NULL);

    // Destroy semaphores
    sem_destroy(&sem_P1);
    sem_destroy(&sem_P2);
    sem_destroy(&sem_P3);

    return 0;
}

void *P1(void *arg) {
    while (1) {
        sem_wait(&sem_P1);  // Wait for semaphore to be available
        printf("A");
        sem_post(&sem_P2);  // Signal P2 to execute next
    }
}

void *P2(void *arg) {
    while (1) {
        sem_wait(&sem_P2);  // Wait for semaphore to be available
        printf("B");
        sem_post(&sem_P3);  // Signal P3 to execute next
    }
}

void *P3(void *arg) {
    while (1) {
        sem_wait(&sem_P3);  // Wait for semaphore to be available
        printf("C");
        sem_post(&sem_P1);  // Signal P1 to execute next
    }
}
