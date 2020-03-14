#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char file[20],string[8];
char* tmp = "./tmp.";

int main(){
    char* s;
    int fd;
    s = (char*)malloc(10);
    sprintf(s, "%d", getpid());
    printf("call getpid() success\n");
    strcpy(file, tmp);
    strcat(file, s);
    if((fd = creat(file, 0644)) == -1){
        fprintf(stderr, "file: %s creat failed\n", file);
        exit(1);
    }
    write(fd, "TMP file", 9);
    close(fd);
    exit(0);
}