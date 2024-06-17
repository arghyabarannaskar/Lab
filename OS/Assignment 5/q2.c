#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/wait.h>


struct sembuf P= {0, -1, 0}; //P operation
struct sembuf V = {0, 1, 0}; //V operation

void P1(int sem_A, int sem_B){
    int val_A;
    for(int i = 0; i<20; i++){
        semop(sem_A, &P, 1);
        
        printf("A");
        
        fflush(stdout);

        semop(sem_B, &V, 1);
    }
}

void P2(int sem_B, int sem_C, int sem_A){
    int turn = 0;
    for(int i = 0; i<20; i++){
        semop(sem_B, &P, 1);
    
       printf("B");
       if((i & 1)) printf(" ");
        
        fflush(stdout);
        if(turn == 0){
            semop(sem_C, &V, 1);
            turn++;
        }else{
            semop(sem_A, &V, 1);
            turn = 0;
        }
    }
}


void P3(int sem_C, int sem_A){
    int turn = 0;
    for(int i = 0; i<20; i++){
        semop(sem_C, &P, 1);
       
        printf("C");
        
        fflush(stdout);
        if(turn == 0){
            semop(sem_C, &V, 1);
            turn = 1;
        }else{
            semop(sem_A, &V, 1);
            turn = 0;
        }
    }
}


int main(){
    key_t key = ftok("semfile", 65); //Generating a unique key

    int sem_A = semget(key, 1, 0666 | IPC_CREAT);
    int sem_B = semget(key+1, 1, 0666 | IPC_CREAT);
    int sem_C = semget(key+2, 1, 0666 | IPC_CREAT);

    semctl(sem_A, 0, SETVAL, 1);
    semctl(sem_B, 0, SETVAL, 0);
    semctl(sem_C, 0, SETVAL, 0);

    if(fork() == 0){
        P1(sem_A, sem_B);
        exit(0);
    }

    if(fork() == 0){
        P2(sem_B, sem_C, sem_A);
        exit(0);
    }

    if(fork() == 0){
        P3(sem_C, sem_A);
        exit(0);
    }

    for(int i = 0; i<3; i++){
        wait(NULL);
    }

    printf("\n");

    semctl(sem_A, 0, IPC_RMID, 0);
    semctl(sem_B, 0, IPC_RMID, 0);
    semctl(sem_C, 0, IPC_RMID, 0);

    return 0;
}