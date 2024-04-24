#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *err);

int main(int argc, char *argv[]){
    int sock;
    char msg[BUF_SIZE];
    int str_len;
    socklen_t adr_sz;

    struct sockaddr_in serv_adr, from_adr;
    
    if(argc != 3){
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        error_handling("socket() error");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    while(1){
        fputs("Insert message(q to quit): ", stdout);
        fgets(msg, sizeof(msg), stdin);

        if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) break;

        sendto(sock, msg, strlen(msg), 0,
            (struct sockaddr*) &serv_adr, sizeof(serv_adr));
        adr_sz = sizeof(from_adr);
        str_len = recvfrom(sock, msg, BUF_SIZE, 0,
            (struct sockaddr*) &from_adr, &adr_sz);
        msg[str_len] = 0;
        printf("Message from server: %s", msg);
    }

    close(sock);
}

void error_handling(char *err){
    fputs(err, stderr);
    fputc('\n', stderr);
    exit(1);
}