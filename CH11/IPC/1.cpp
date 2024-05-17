#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int child[2], parent[2];
    pipe(child), pipe(parent);

    char str[BUF_SIZE], buf[BUF_SIZE];

    pid_t pid;
    for(int i = 0; i < 3; ++i){
        pid = fork();
        if(!pid){   // child proc
            printf("전송할 문자열을 입력하시오: ");
            gets(str);
            write(child[1], str, sizeof(str));

            sleep(3);

            read(parent[0], buf, BUF_SIZE);
            printf("Child proc output: %s\n", buf);
        }else{      // parent proc
            read(child[0], buf, BUF_SIZE);
            printf("Parent proc output: %s\n", buf);

            printf("전송할 문자열을 입력하시오: ");
            gets(str);
            write(parent[1], str, sizeof(str));
            
            sleep(3);
        }
    }
}