#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TRUE 1
#define FALSE 0

void error_handling(char *err);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    char msg[30];
    int opt, len;
    socklen_t optlen, clnt_adr_size;
    struct sockaddr_in serv_adr, clnt_adr;

    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");
   
    optlen = sizeof(opt);
    opt = TRUE;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*) &opt, optlen);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    clnt_adr_size = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, &clnt_adr_size);

    while((len = read(clnt_sock, msg, sizeof(msg))) != 0){
        write(clnt_sock, msg, len);
        write(1, msg, len);
    }

    close(clnt_sock);
    close(serv_sock);
}

void error_handling(char *err){
    fputs(err, stderr);
    fputc('\n', stderr);
    exit(1);
}