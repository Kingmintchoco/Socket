#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *fp1;
    FILE *fp2;
    char buf[3];

    fp1 = fopen("news.txt", "r");
    fp2 = fopen("cpy.txt", "w");

    while(fgets(buf, 3, fp1) != NULL)
        fputs(buf, fp2);
    
    fclose(fp1);
    fclose(fp2);
}