#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "shared.h"
#include<time.h>

void writer(shared_data *data) {
    for (int i = 0; i < 10; i++) { 
        sem_wait(&data->rw_mutex); 

        // Writing data
        printf("\nWriter %d: writing data\n", getpid());
        for (int j = 0; j < BUFFER_SIZE; j++) {
            data->data[j] = rand() % 100;
            printf("%d ", data->data[j]);
        }

        sem_post(&data->rw_mutex); 
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

    
    writer(data);

    munmap(data, sizeof(shared_data));

    return 0;
}