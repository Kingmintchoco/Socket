#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

#define BUF_SIZE 1024

using namespace std;

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_adr;

    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = INADDR_ANY;
    serv_adr.sin_port = htons(9190);

    connect(sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr));

    string req;
    while(1){
        req.clear();
        getline(cin, req);
        if(req == "Q" || req == "q") break;
        send(sock, req.c_str(), req.size(), 0);
    }
    
    close(sock);
}