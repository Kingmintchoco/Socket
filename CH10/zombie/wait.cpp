#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    int status;
    pid_t pid = fork();         // 자식 프로세스(1) 생성

    if(!pid)
        return 3;               // 자식 프로세스(1) 종료, main-return(val)을 통한 종료
    else{
        printf("Child(1) PID: %d\n", pid);

        pid = fork();           // 자식 프로세스(2) 생성
        if(!pid)
            exit(7);            // 자식 프로세스(2) 종료, exit(val)을 통한 종료
        else{
            printf("Child(2) PID: %d\n", pid);
            wait(&status);

            if(WIFEXITED(status))
                printf("Child send one: %d\n", WEXITSTATUS(status));
            
            wait(&status);
            if(WIFEXITED(status))
                printf("Child sent two: %d\n", WEXITSTATUS(status));
            
            sleep(30);
        }
    }
}