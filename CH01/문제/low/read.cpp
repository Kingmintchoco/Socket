#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1000

using namespace std;

void error_handling(char* error);

int main(){
    int fd;
    char buf[BUF_SIZE];

    fd = open("p.txt", O_RDONLY);
    if(fd == -1) error_handling("open() error");

    cout << "file discriptor: " << fd << '\n';

    if(read(fd, buf, sizeof(buf)) == -1) error_handling("read() error");
    cout << "file data: " << buf << "\n";

    close(fd);
}


void error_handling(char* error){
    fputs(error, stderr);
    fputc('\n', stderr);
    exit(1);
}