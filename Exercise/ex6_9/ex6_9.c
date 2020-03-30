#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
    int n, fd[2];
    pid_t pid;
    char buffer[BUFSIZ + 1];
    if(pipe(fd) < 0){
        printf("pipe failed!\n");
        exit(1);
    }
    if((pid = fork()) < 0){
        printf("Fork failed!\n");
        exit(1);
    }
    else if(pid > 0){
        close(fd[0]);
        write(fd[1], "How are you ?\n", 15);
    }
    else{
        close(fd[1]);
        n = read(fd[0], buffer, BUFSIZ);
        write(STDOUT_FILENO, buffer, n);
    }
    exit(0);
}