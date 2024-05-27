#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>

#define SEM_NAME_P1 "/sem_p1"
#define SEM_NAME_P2 "/sem_p2"
#define SEM_NAME_P3 "/sem_p3"

#define NUM_REPEATS 10

void P1(sem_t *sem_p1, sem_t *sem_p2) {
    while (1) {
        sem_wait(sem_p1); // Wait for permission
        printf("A");
        sem_post(sem_p2); // Signal P2 to proceed
    }
}

void P2(sem_t *sem_p2, sem_t *sem_p3) {
    while (1) {
        sem_wait(sem_p2); // Wait for permission
        printf("B ");
        sem_post(sem_p3); // Signal P3 to proceed
    }
}

void P3(sem_t *sem_p3, sem_t *sem_p1) {
    while (1) {
        sem_wait(sem_p3); // Wait for permission
        printf("C");
        sem_post(sem_p1); // Signal P1 to proceed
    }
}

int main() {
    sem_t *sem_p1, *sem_p2, *sem_p3;

    // Create and initialize semaphores
    sem_p1 = sem_open(SEM_NAME_P1, O_CREAT, 0666, 1); // Initial value 1
    sem_p2 = sem_open(SEM_NAME_P2, O_CREAT, 0666, 0); // Initial value 0
    sem_p3 = sem_open(SEM_NAME_P3, O_CREAT, 0666, 0); // Initial value 0

    if (sem_p1 == SEM_FAILED || sem_p2 == SEM_FAILED || sem_p3 == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    // Fork child processes
    pid_t pid_p1, pid_p2, pid_p3;

    pid_p1 = fork();
    if (pid_p1 == 0) {
        P1(sem_p1, sem_p2);
        exit(EXIT_SUCCESS);
    }

    pid_p2 = fork();
    if (pid_p2 == 0) {
        P2(sem_p2, sem_p3);
        exit(EXIT_SUCCESS);
    }

    pid_p3 = fork();
    if (pid_p3 == 0) {
        P3(sem_p3, sem_p1);
        exit(EXIT_SUCCESS);
    }

    // Wait for child processes to finish
    for (int i = 0; i < NUM_REPEATS; i++) {
        wait(NULL);
    }

    // Close and unlink semaphores
    sem_close(sem_p1);
    sem_close(sem_p2);
    sem_close(sem_p3);
    sem_unlink(SEM_NAME_P1);
    sem_unlink(SEM_NAME_P2);
    sem_unlink(SEM_NAME_P3);

    return 0;
}
