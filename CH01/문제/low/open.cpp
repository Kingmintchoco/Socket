#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void error_handling(char* msg);

int main(){
    int fd;
    char buf[] = "low\n";

    fd = open("p.txt", O_CREAT | O_WRONLY | O_TRUNC);
    if(fd == -1) error_handling("open() error");
    
    cout << "file descriptor: " << fd << "\n";

    if(write(fd, buf, sizeof(buf)) == -1) error_handling("write() error");
    
    close(fd);
    return 0;
}


void error_handling(char* msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}