#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

using namespace std;

int main(){
    int fd1, fd2, fd3;

    fd1 = socket(PF_INET, SOCK_STREAM, 0);
    fd2 = open("p.dat", O_CREAT | O_WRONLY | O_TRUNC);
    fd3 = socket(PF_INET, SOCK_DGRAM, 0);

    cout << "file discriptor 1: " << fd1 << "\n";
    cout << "file discriptor 2: " << fd2 << "\n";
    cout << "file discriptor 3: " << fd3 << "\n";

    close(fd1); close(fd2); close(fd3);
    return 0;
}