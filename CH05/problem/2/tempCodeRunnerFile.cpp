#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

using namespace std;

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_adr;

    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    serv_adr.sin_port = htons(9190);

    connect(sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr));

    char buf[BUF_SIZE];
    recv(sock, buf, sizeof(buf), 0);
    cout << "Message from server: " << buf << "\n";

    close(sock);
}