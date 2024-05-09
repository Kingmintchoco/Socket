#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    pid_t pid = fork();

    if(!pid)
        puts("Hi, I am a child process");
    else{
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", pid);
        sleep(20);                              // sleep 20sec.
    }

    if(!pid)
        puts("End child process");
    else
        puts("End parent process");
}