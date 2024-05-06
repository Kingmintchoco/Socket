#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *msg);

int main(int argc, char *argv[]){
    int serv_sd, clnt_sd;
    FILE *fp;
    char buf[BUF_SIZE];
    int len;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_size;

    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    fp = fopen("server.cpp", "rb");
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    bind(serv_sd, (struct sockaddr*) &serv_adr, sizeof(serv_adr));
    listen(serv_sd, 5);

    clnt_adr_size = sizeof(clnt_adr);
    clnt_sd = accept(serv_sd, (struct sockaddr*) &clnt_adr, &clnt_adr_size);

    while(1){
        len = fread((void*) buf, 1, BUF_SIZE, fp);
        if(len < BUF_SIZE){
            write(clnt_sd, buf, len);
            break;
        }
        write(clnt_sd, buf, BUF_SIZE);
    }

    shutdown(clnt_sd, SHUT_WR);
    read(clnt_sd, buf, BUF_SIZE);
    printf("Message from client: %s \n", buf);

    fclose(fp);
    close(clnt_sd); close(serv_sd);
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}