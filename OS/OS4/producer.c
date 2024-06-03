/*
Implement the solution to the producer-consumer problem using shared variables.
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>


int main(){
	int shmid,key=2022,ch,item;
	char *buffer;

	//creates shared memory segment of 20 bytes
	//full empty 5 elements
	if((shmid = shmget(key, 28 , IPC_CREAT | 0666))==-1){
    		printf("Cannot create shared memory\n");
    		exit(0);
  	}
  	//attach it for use
  	buffer = shmat(shmid, NULL, 0);
  	
  	
  	int full,empty;
	full=0;
	empty=5;
	sprintf(buffer,"%d",full);
	sprintf(buffer+4,"%d",empty);
  	//do-while loop to produce items repetatively
  	do{
  	        printf("\n1.Produce an item\n2.Exit\nEnter your choice:");
  	        scanf("%d",&ch);
  	        switch(ch){
  	                case 1:
  	                        sscanf(buffer,"%d",&full);
  	                        sscanf(buffer+4,"%d",&empty);
  	                        while(empty==0){
  	                                printf("\nBuffer Full...\n");
  	                                sleep(1);
  	                                sscanf(buffer+4,"%d",&empty);
                                }
  	                        printf("\nEnter item:");
  	                        scanf("%d",&item);
  	                        full+=1;
  	                        empty-=1;
  	                        sprintf(buffer+4+full*4,"%d",item);
  	                        sprintf(buffer,"%d",full);
	                        sprintf(buffer+4,"%d",empty);
  	                        break;
                        case 2:
                                printf("\nProgram Exits...\n");
                                break;
                        default:
                                printf("\nWrong Choice...");
                }
        }while(ch!=2);
        printf("\nItems produces:%d, Buffer slots remains:%d\n",full,empty);
        return 0;
}
