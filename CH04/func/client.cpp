#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *err);

int main(int argc, char* argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char msg[30];
    int str_len;

    if(argc != 3){
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // client socket 생성
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // client socket -> 주소 할당(bind()를 쓰지 않더라도 OS(대부분 커널)에서 자동으로 할당해줌
    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");
    
    str_len = read(sock, msg, sizeof(msg) - 1);
    if(str_len == -1)
        error_handling("read() error");
    
    printf("Message from server: %s \n", msg);
    close(sock);

    return 0;
}

void error_handling(char *err){
    fputs(err, stderr);
    fputc('\n', stderr);
    exit(1);
}