#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100
void error_handling(char *err);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    fd_set reads, temps;

    socklen_t adr_size;
    int fd_max, str_len, fd_num, i;
    char buf[BUF_SIZE];

    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;

    while(1){
        temps = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        if((fd_num = select(fd_max + 1, &temps, 0, 0, &timeout)) == -1)
            break;
        
        if(!fd_num)
            continue;
        
        for(i = 0; i < fd_max + 1; ++i){
            if(FD_ISSET(i, &temps)){
                if(i == serv_sock){     // connection req
                    adr_size = sizeof(clnt_adr);
                    clnt_sock =
                        accept(serv_sock, (struct sockaddr*) &clnt_adr, &adr_size);

                    FD_SET(clnt_sock, &reads);
                    if(fd_max < clnt_sock)
                        fd_max = clnt_sock;
                    
                    printf("connected client: %d\n", clnt_sock);
                }else{                  // read msg!
                    str_len = read(i, buf, BUF_SIZE);
                    if(!str_len){
                        FD_CLR(i, &reads);
                        close(i);
                        printf("closed client: %d\n", i);
                    }else{
                        write(i, buf, str_len); // echo
                    }
                }
            }
        }
    }

    close(serv_sock);
}

void error_handling(char *err){
    fputs(err, stderr);
    fputc('\n', stderr);
    exit(1);
}