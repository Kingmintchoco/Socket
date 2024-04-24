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

    int cnt = 0, num;
    cout << "Employee count: ";
    cin >> cnt;
    
    send(sock, &cnt, sizeof(cnt), 0);
    
    for(int i = 1; i <= cnt; ++i){
        cout << i << ": ";

        // info input
        string info, name, age;
        cin >> name >> age;
        info = name + " " + age;

        int len = info.size();
        send(sock, &len, sizeof(len), 0);
        send(sock, info.c_str(), len, 0);
    }
    
    close(sock);
}