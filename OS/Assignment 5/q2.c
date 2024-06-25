#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h> // For O_CREAT, O_EXCL

void P1(sem_t *sem_A, sem_t *sem_B) {
    for (int i = 0; i < 20; i++) {
        sem_wait(sem_A);
        printf("A");
        fflush(stdout);
        sem_post(sem_B);
    }
}

void P2(sem_t *sem_B, sem_t *sem_C, sem_t *sem_A) {
    int turn = 0;
    for (int i = 0; i < 20; i++) {
        sem_wait(sem_B);
        printf("B");
        if ((i & 1)) printf(" ");
        fflush(stdout);
        if (turn == 0) {
            sem_post(sem_C);
            turn++;
        } else {
            sem_post(sem_A);
            turn = 0;
        }
    }
}

void P3(sem_t *sem_C, sem_t *sem_A) {
    int turn = 0;
    for (int i = 0; i < 20; i++) {
        sem_wait(sem_C);
        printf("C");
        fflush(stdout);
        if (turn == 0) {
            sem_post(sem_C);
            turn = 1;
        } else {
            sem_post(sem_A);
            turn = 0;
        }
    }
}

int main() {
    sem_t *sem_A = sem_open("/semA", O_CREAT | O_EXCL, 0666, 1);
    sem_t *sem_B = sem_open("/semB", O_CREAT | O_EXCL, 0666, 0);
    sem_t *sem_C = sem_open("/semC", O_CREAT | O_EXCL, 0666, 0);

    if (sem_A == SEM_FAILED || sem_B == SEM_FAILED || sem_C == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
        P1(sem_A, sem_B);
        exit(0);
    }

    if (fork() == 0) {
        P2(sem_B, sem_C, sem_A);
        exit(0);
    }

    if (fork() == 0) {
        P3(sem_C, sem_A);
        exit(0);
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("\n");

    sem_unlink("/semA");
    sem_unlink("/semB");
    sem_unlink("/semC");

    return 0;
}
