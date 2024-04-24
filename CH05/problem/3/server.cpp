#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUF_SIZE 1024

using namespace std;

int main(){
    int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(9190);

    bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    listen(serv_sock, 5);

    int clnt_sock = accept(serv_sock, nullptr, nullptr);

    char buf[BUF_SIZE];
    while(1){
        memset(buf, 0, sizeof(buf));
        ssize_t len = recv(clnt_sock, buf, sizeof(buf), 0);
        if(len <= 0) break;
        cout << "Message from client: " << buf << "\n";
    }

    close(clnt_sock);
    close(serv_sock);
}