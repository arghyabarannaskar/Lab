#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

#define NUM_CHILDREN 10
#define RANGE_SIZE 1000000

int is_prime(int number){
	if(number <= 1) return 0; // 0 and 1 are not prime
	if(number <=3) return 1; // 2 and 3 are primes

	for(int i = 2; i*i<=number; i++){
		if(number % i == 0) return 0;
	}

	return 1;
}

void print_prime(int start, int end){
	for(int i = start; i<= end; i++){
		if(is_prime(i)) printf("%d ", i);
	}
	printf("\n");
}

int main(){
	pid_t pid;
	int range_start = 1;
	int segment_size = RANGE_SIZE / NUM_CHILDREN;

	for(int i = 0; i< NUM_CHILDREN; i++){
		pid = fork();

		if(pid < 0){
			perror("fork failed");
			exit(EXIT_FAILURE);
		}

		if(pid == 0){
			printf("child %d: PID = %d, parent PID = %d\n", i+1, getpid(), getppid());
            
            int child_start = segment_size*i + range_start;
            int child_end = child_start + segment_size -1;

            print_prime(child_start, child_end);

			exit(EXIT_SUCCESS);
		}
	}

    for(int i = 0; i<NUM_CHILDREN; i++){
		wait(NULL);
	}

	return 0;
}