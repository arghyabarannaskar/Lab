#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>


int main(){
	int shmid;
	int key =220;
	int status,max,min,sum;
	float avg;
	char *buffer;
	//creates shared memory segment
	if((shmid = shmget(key, 420, IPC_CREAT | 0666))==-1){
    		printf("Cannot create shared memory\n");
    		exit(0);
  	}
  	//attach it for use
  	buffer = shmat(shmid, NULL, 0);
  	
  	int turn=0;   //initialise turn to 0 for parent process
  	sprintf(buffer, "%d", turn);
  	
  	if(fork()!=0){
  	        //parent process
  	        //waiting for child to give turn permission
  	        while(turn!=0){
  	                sscanf(buffer, "%d" , &turn);
                }
                printf("Randomly generated 100 numbers in parent process are:\n");
                int i;
                //srand() must be used before rand() to produce differenct random numbers on every execution
                //srand(val) start generating at different starting point and time(0) for current time
                srand(time(0));  
                //loop to generate 100 random numbers 
                for(i=1;i<=100;i++)
                {
                        int temp=rand()%1000;
                        printf("%d",temp);
                        //store numbers in shared memory
                        sprintf(buffer+(4*i),"%d",temp);
                        /*if(i!=100)
                                printf(",");
                        else
                                printf("\n");*/
                                printf(" ");
                }
                fflush(stdout);
                //release turn and pass the numbers to child process for operations
                turn=1;
                sprintf(buffer, "%d" ,turn);
                //waiting for child to give turn permission
                while(turn!=0){
                        sscanf(buffer, "%d" , &turn);
                }
                sscanf(buffer+(4*101),"%d",&max);
                sscanf(buffer+(4*102),"%d",&min);
                sscanf(buffer+(4*103),"%f",&avg);
                sleep(1);
                printf("\nMax = %d\nMin = %d\nAverage = %.2f\n",max,min,avg);
                printf("Parent terminates\n");
  	}
  	else{
  	        //child process
  	        //waiting for parent to give turn permission
  	        while(turn!=1){
  	                sscanf(buffer, "%d" , &turn);
                }
                int val;
                sscanf(buffer+4, "%d" , &val);
                max=val;
                min=val;
                sum=val;
                int i;
                //loop to find min,max and  sum of values in shared memory
                for(i=2;i<=100;i++)
                {
                        sscanf(buffer+(4*i),"%d",&val);
                        if(val>max)
                                max=val;
                        if(val<min)
                                min=val;
                        sum+=val;
                }
                avg=(float)sum/100.0;
                //store max,min and average in shared memory
                sprintf(buffer+(4*101),"%d",max);
                sprintf(buffer+(4*102),"%d",min);
                sprintf(buffer+(4*103),"%.2f",avg);
                //release the turn and pass to parent process
                turn=0;
                sprintf(buffer, "%d" ,turn);
                printf("\nchild terminates\n");
        }
        shmdt(buffer);
        return 0;
}
