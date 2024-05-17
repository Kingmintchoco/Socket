#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *err);
void read_childproc(int sig);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    int fds[2];

    pid_t pid;
    struct sigaction act;
    socklen_t adr_size;
    int str_len, state;
    char buf[BUF_SIZE];

    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    
    pipe(fds);
    pid = fork();
    if(!pid){   // child proc: 클라이언트 메시지를 파일에 저장하는 proc
        FILE *fp = fopen("echomsg.txt", "wt");
        char msg[BUF_SIZE];

        int len;
        for(int i = 0; i < 10; ++i){
            len = read(fds[0], msg, BUF_SIZE);
            fwrite((void*) msg, 1, len, fp);
        }

        fclose(fp);
        return 0;
    }

    while(1){
        adr_size = sizeof(clnt_adr);
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_adr, &adr_size);
        if(clnt_sock == -1)
            continue;
        else
            puts("new client connected...");
        
        pid = fork();
        if(!pid){   // child proc: 클라이언트가 보낸 데이터를 수신
            close(serv_sock);
            while((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0){
                write(clnt_sock, buf, str_len);
                write(fds[1], buf, str_len);
            }

            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        }else
            close(clnt_sock);
    }

    close(serv_sock);
    return 0;
}

void read_childproc(int sig){
    pid_t pid;
    int status;
    pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id: %d\n", pid);
}

void error_handling(char *err){
    fputs(err, stderr);
    fputc('\n', stderr);
    exit(1);
}