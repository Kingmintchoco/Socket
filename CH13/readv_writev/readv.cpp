#include <stdio.h>
#include <sys/uio.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    struct iovec vec[2];

    char buf1[BUF_SIZE] = {0, };
    char buf2[BUF_SIZE] = {0, };
    int str_len;

    vec[0].iov_base = buf1;
    vec[0].iov_len = 5;

    vec[1].iov_base = buf2;
    vec[1].iov_len = BUF_SIZE;

    str_len = readv(0, vec, 2);
    printf("Read bytes: %d\n", str_len);
    printf("First Message: %s\n", buf1);
    printf("Second Message: %s\n", buf2);
}