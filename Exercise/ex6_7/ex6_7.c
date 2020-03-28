#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void inthandler(int signum);
void continuehandler(int signum);
void terminatehandler(int signum);

int main(){
    char buffer[100];
    if(signal(SIGINT, &inthandler) == SIG_ERR){
        printf("Couldn't register signal handler for SIGINT!\n");
        exit(2);
    }
    if(signal(SIGTSTP, &inthandler) == SIG_ERR){
        printf("Couldn't register signal handler for SIGTSTP!\n");
        exit(2);
    }
    if(signal(SIGCONT, &continuehandler) == SIG_ERR){
        printf("Couldn't register signal handler for SIGTSTP!\n");
        exit(2);
    }
    if(signal(SIGTERM, &terminatehandler) == SIG_ERR){
        printf("Couldn't register signal handler for SIGTSTP!\n");
        exit(2);
    }
    printf("PID of this process : %d\n", getpid());

    while(1){
        printf("Please input:\n");
        fgets(buffer, sizeof(buffer), stdin);
        if(strcmp(buffer, "int\n") == 0){
            raise(SIGINT);
        }
        else if(strcmp(buffer, "stop\n") == 0){
            raise(SIGTSTP);
        }
        else if(strcmp(buffer, "continue\n") == 0){
            raise(SIGCONT);
        }
        else if(strcmp(buffer, "quit\n") == 0){
            raise(SIGTERM);
        }
        else{
            printf("Your input is : %s\n", buffer);
        }
    }
    exit(0);
}

void inthandler(int signum){
    printf("Catch signal %d\n\n", signum);
}

void continuehandler(int signum){
    printf("Continue Code\n\n");
}

void terminatehandler(int signum){
    printf("Signal SIGTERM\n\n");
    exit(0);
}