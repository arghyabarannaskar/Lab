// shared.h
#ifndef SHARED_H
#define SHARED_H

#include <semaphore.h>

#define SHM_NAME "/rw_shared_memory"
#define BUFFER_SIZE 100

typedef struct {
    int data[BUFFER_SIZE];
    sem_t rw_mutex;
    sem_t mutex;
    int read_count;
} shared_data;

#endif // SHARED_H
