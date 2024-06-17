#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "shared.h"
#include<time.h>

void reader(shared_data *data) {
    for (int i = 0; i < 10; i++) { 
        sem_wait(&data->mutex);
        data->read_count++;
        if (data->read_count == 1) {
            sem_wait(&data->rw_mutex); 
        }
        sem_post(&data->mutex);

        printf("\nReader %d: reading data: ", getpid()); //reading data
        for (int j = 0; j < BUFFER_SIZE; j++) {
            printf("%d ", data->data[j]);
        }
        printf("\n");

        sem_wait(&data->mutex);
        data->read_count--;
        if (data->read_count == 0) {
            sem_post(&data->rw_mutex); 
        }
        sem_post(&data->mutex);

        usleep(rand() % 1000000); 
    }
}

int main() {
    srand(time(NULL));

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

    reader(data);

    munmap(data, sizeof(shared_data));

    return 0;
}