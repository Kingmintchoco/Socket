#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int fds[2];
    char str[] = "Who are you?";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds);
    pid = fork();       // child process create
    if(pid == 0){       // child process
        write(fds[1], str, sizeof(str));
    }else{              // parent process
        read(fds[0], buf, BUF_SIZE);
        puts(buf);
    }
}