#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *err);

int main(int argc, char* argv[]){
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char msg[] = "earl gray americano";

    // server를 open할 포트 선택
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    // server socket 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");
    
    // server 주소 초기화
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // server socket에 주소 할당
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    
    // server 연결 대기 상태
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    // client 연결 요청 시 연결 허용
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1)
        error_handling("accept() error");
    
    // 데이터 송수신
    write(clnt_sock, msg, sizeof(msg));

    // 연결 종료
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(char *err){
    fputs(err, stderr);
    fputc('\n', stderr);
    exit(1);
}