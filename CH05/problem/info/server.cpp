#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

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

    int clnt_sock, cnt;
    vector <pair <string, string> > info;

    clnt_sock = accept(serv_sock, nullptr, nullptr);
    read(clnt_sock, &cnt, sizeof(cnt));

    for(int i = 0; i < cnt; ++i){
        int len;
        char buf[BUF_SIZE];

        recv(clnt_sock, &len, sizeof(len), 0);
        recv(clnt_sock, buf, len, 0);

        string str(buf, len);
        size_t pos = str.find(' ');
        string a = str.substr(0, pos);
        string b = str.substr(pos + 1);
        
        info.push_back(make_pair(a, b));
    }

    for(int i = 0; i < info.size(); ++i){
        cout << (i + 1) << ": " << info[i].first << ", " << info[i].second << '\n'; 
    }

    close(clnt_sock);
    close(serv_sock);
}