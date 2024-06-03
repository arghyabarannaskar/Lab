#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main(){
	int shmid;
	int key =123;
	int status;
	char *buffer;
	//creates shared memory segment
	if((shmid = shmget(key, 10, IPC_CREAT | 0666))==-1){
    		printf("Cannot create shared memory\n");
    		exit(0);
  	}
  	//attach it for use
  	buffer = shmat(shmid, NULL, 0);
  	
  	int turn=0;   //initialise turn to 0 for pin process
  	sprintf(buffer, "%d", turn);
  	
  	//loop to create two child processes
  	for(int i=0; i<2; i++){
  		if(fork()!=0){
  			//Parent process
  		}
  		else{
  			//Child Process ping
  			if(i==0){
  			        
  				while(1){
  				        //printf("ping process\n");
  				        sscanf(buffer, "%d", &turn);
                                        while(turn!=0){
                                                sscanf(buffer, "%d", &turn);
                                        }
                                        printf("ping\n");
                                        turn=1;
                                        sprintf(buffer,"%d",turn);
                                        sleep(1);
                                }
  				 
  			}
  			//Child process pong
  			if(i==1){
  			      
  				while(1){
                        sscanf(buffer, "%d", &turn);
                        while(turn!=1){
                                sscanf(buffer, "%d", &turn);
                        }
                                printf("pong\n");
                                turn=0;
                                sprintf(buffer,"%d",turn);
                                sleep(1);
                                }
  			
  			}
  				
  			exit(0);   //exit from child
  		}
  	}  	
  	//two wait system calls for two child processes
  	wait(&status);
  	wait(&status);
  	shmdt(buffer);
  	return 0;
}
