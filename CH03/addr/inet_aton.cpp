#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

using namespace std;

void error_handling(char* err);

int main(){
    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    if(!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion Error");
    else
        printf("Network ordered integer addr: %#x \n",
            addr_inet.sin_addr.s_addr);

    return 0;
}

void error_handling(char* err){
    fputs(err, stderr);
    fputc('\n', stderr);
    exit(1);
}