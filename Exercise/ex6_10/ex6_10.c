#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int n, fd[2];
    pid_t pid;
    char buffer[BUFSIZ+1];
    FILE *fp;
    if(argc <= 1){
        printf("Usage: %s <pathname>\n", argv[0]);
        exit(1);
    }
    if((fp = fopen(argv[1], "r")) == NULL){
        printf("Fail to open file!\n");
        exit(1);
    }
    if(pipe(fd) < 0){
        printf("pipe failed!\n");
        exit(2);
    }
    if((pid = fork()) < 0){
        printf("Fork failed!\n");
        exit(3);
    }
    else if(pid > 0){
        close(fd[0]);
        while(fgets(buffer, BUFSIZ, fp) != NULL){
            n = strlen(buffer);
            if(write(fd[1], buffer, n) != n){
                printf("Fail write to pipe!\n");
                exit(4);
            }
        }
        if(ferror(fp)){
            printf("call fgets() error!\n");
            exit(5);
        }
        close(fd[1]);
        if(waitpid(pid, NULL, 0) < 0){
            printf("call waitpid() error!\n");
            exit(6);
        }
        exit(0);
    }
    else{
        close(fd[1]);
        if(fd[0] != STDIN_FILENO){
            if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO){
                printf("call dup2() error to stdin!\n");
                exit(7);
            }
            close(fd[0]);
        }
        if(execl("upcase", "upcase", NULL) < 0){
            printf("Fail to call upcase()!\n");
            exit(8);
        }
        exit(0);
    }
}