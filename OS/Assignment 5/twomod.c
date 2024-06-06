#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PRINTS 10

// Global semaphore declarations
sem_t sem_P1, sem_P2, sem_P3;

// Function prototypes
void *P1(void *arg);
void *P2(void *arg);
void *P3(void *arg);

int main() {
    // Initialize semaphores
    sem_init(&sem_P1, 0, 1); // Semaphore for P1, initially unlocked
    sem_init(&sem_P2, 0, 0); // Semaphore for P2, initially locked
    sem_init(&sem_P3, 0, 0); // Semaphore for P3, initially locked

    // Create threads for each process
    pthread_t thread_P1, thread_P2, thread_P3;
    pthread_create(&thread_P1, NULL, P1, NULL);
    pthread_create(&thread_P2, NULL, P2, NULL);
    pthread_create(&thread_P3, NULL, P3, NULL);

    // Wait for all threads to finish
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
    for (int i = 0; i < NUM_PRINTS; i++) {
        sem_wait(&sem_P1);
        printf("A");
        sem_post(&sem_P2);
    }
    pthread_exit(NULL);
}

void *P2(void *arg) {
    for (int i = 0; i < NUM_PRINTS; i++) {
        sem_wait(&sem_P2);
        printf("B");
        sem_post(&sem_P3);
    }
    pthread_exit(NULL);
}

void *P3(void *arg) {
    for (int i = 0; i < NUM_PRINTS; i++) {
        sem_wait(&sem_P3);
        printf("C");
        sem_post(&sem_P1);
    }
    pthread_exit(NULL);
}
