#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *msg);

int main(int argc, char *argv[]){
    int sd;
    FILE *fp;

    char buf[BUF_SIZE];
    int len;
    struct sockaddr_in serv_adr;

    if(argc != 3){
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    fp = fopen("receive.dat", "wb");
    sd = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    connect(sd, (struct sockaddr*) &serv_adr, sizeof(serv_adr));

    while((len = read(sd, buf, BUF_SIZE)) != 0)
        fwrite((void*)buf, 1, len, fp);
    
    puts("Received file data");
    write(sd, "Thank you", 10);

    fclose(fp);
    close(sd);
}

void error_handling(char *msg){
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}