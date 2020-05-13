#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char buffer[BUFSIZ + 1];
    FILE *fpin, *fpout;
    if(argc < 2){
        printf("Usage: %s <pathname>\n", argv[0]);
        exit(1);
    }
    if((fpin = fopen(argv[1], "r")) == NULL){
        printf("Can't open %s\n", argv[1]);
        exit(1);
    }
    if((fpout = popen("./upcase", "w")) == NULL){
        printf("popen error!\n");
        exit(1);
    }
    while((fgets(buffer, BUFSIZ, fpin)) != NULL){
        if(fputs(buffer, fpout) == EOF){
            printf("fputd error to pipe\n");
            exit(1);
        }
    }
    if(ferror(fpin)){
        printf("fgets error!\n");
        exit(1);
    }
    if(pclose(fpout) == -1){
        printf("pclose error!\n");
        exit(1);
    }
    exit(0);
}