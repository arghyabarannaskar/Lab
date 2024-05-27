#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

typedef struct {
    int numbers[100];
    int max;
    int min;
    float avg;
} SharedData;

int main() {
    int shm_id;
    SharedData *shared_data;

    // Create a shared memory segment
    shm_id = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment
    shared_data = (SharedData *)shmat(shm_id, NULL, 0);
    if (shared_data == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    // Parent process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process

        // Wait for parent to write data
        while (shared_data->numbers[0] == 0) {
            usleep(100); // Sleep for 100 microseconds
        }

        // Compute maximum, minimum, and average
        int sum = 0;
        shared_data->max = shared_data->min = shared_data->numbers[0];
        for (int i = 0; i < 100; i++) {
            sum += shared_data->numbers[i];
            if (shared_data->numbers[i] > shared_data->max) {
                shared_data->max = shared_data->numbers[i];
            }
            if (shared_data->numbers[i] < shared_data->min) {
                shared_data->min = shared_data->numbers[i];
            }
        }
        shared_data->avg = (float)sum / 100;

        // Detach the shared memory segment
        if (shmdt(shared_data) == -1) {
            perror("shmdt failed");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    } else {
        // Parent process

        // Generate 100 random integers and write to shared memory
        srand(time(NULL));
        for (int i = 0; i < 100; i++) {
            shared_data->numbers[i] = rand() % 1000; // Random numbers between 0 and 999
        }

        // Wait for child to finish computing
        wait(NULL);

        // Read results from shared memory and display
        printf("Maximum: %d\n", shared_data->max);
        printf("Minimum: %d\n", shared_data->min);
        printf("Average: %.2f\n", shared_data->avg);

        // Detach and remove the shared memory segment
        if (shmdt(shared_data) == -1) {
            perror("shmdt failed");
            exit(EXIT_FAILURE);
        }
        if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
            perror("shmctl failed");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
