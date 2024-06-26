#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int fds1[2], fds2[2];   // fds1(child -> parent), fds2(parent -> child)
    char str1[] = "supernova";
    char str2[] = "aespa";
    char buf[BUF_SIZE];
    pid_t pid;

    pipe(fds1), pipe(fds2);
    pid = fork();
    if(!pid){
        write(fds1[1], str1, sizeof(str1));
        read(fds2[0], buf, BUF_SIZE);
        printf("Child proc output: %s\n", buf);
    }else{
        read(fds1[0], buf, BUF_SIZE);
        printf("Parent proc output: %s\n", buf);
        write(fds2[1], str2, sizeof(str2));
        sleep(3);
    }
}