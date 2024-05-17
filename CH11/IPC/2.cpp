#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int fds1[2], fds2[2];

    char str1[] = "supernova";
    char str2[] = "aespa";
    char str3[] = "tick tick bam";
    char *arr[] = {str1, str2, str3};

    char buf[BUF_SIZE];

    pid_t pid;
    pipe(fds1), pipe(fds2);

    pid = fork();
    if(!pid){
        for(int i = 0; i < 3; ++i){
            write(fds1[1], arr[i], strlen(arr[i]) + 1);
            read(fds2[0], buf, BUF_SIZE);
            printf("Child proc output: %s\n", buf);
        }
    }else{
        for(int i = 0; i < 3; ++i){
            read(fds1[0], buf, BUF_SIZE);
            printf("Parent proc output: %s\n", buf);
            write(fds2[1], arr[i], strlen(arr[i]) + 1);
        }
    }
}