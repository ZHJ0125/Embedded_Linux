#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(argc <= 1){
        fprintf(stderr, "Usage: %s command [arg ...]\n", argv[0]);
        exit(1);
    }
    argv++;
    //argc--;
    if(fork() == 0){
        //setpgrp();
        execvp(*argv, argv);
        printf("%s is not executed\n", *argv);
        exit(0);
    }
    exit(0);
}