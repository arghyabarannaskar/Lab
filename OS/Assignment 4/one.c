#include<unistd.h> //for fork()
#include<stdio.h>
#include<stdlib.h> // for EXIT_FAILURE
#include<sys/types.h> // for pid_t
#include<sys/wait.h>
// #include<errno.h>  //for error handling -> perror()

int main(){
    pid_t pid;
    int status;

    pid = fork();

    if(pid < 0){
        perror("fork failure");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){
        printf("Child process: PID = %d, parent PID = %d\n", getpid(), getppid());
        sleep(2); //simulate some work in the child process
        exit(EXIT_SUCCESS);
    }else {
        printf("Parent process: PID = %d, parent PID = %d\n", getpid(), getppid());

        if(wait(&status) == -1){
            perror("wait failed");
            exit(EXIT_FAILURE);
        }

        if(WIFEXITED(status)){
            printf("parent process: Child exited with status = %d\n", WEXITSTATUS(status));
        }else{
            printf("Parent process: Child did not exit successfully\n");
        }
    }
    
    return 0;
}