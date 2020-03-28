#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int quitflag = 0;

int main(){
    void sig_int(int);
    sigset_t newmask, oldmask, zeromask;

    if(signal(SIGINT, &sig_int) == SIG_ERR){
        printf("Couldn't register signal hanlder for SIGINT!\n");
        exit(1);
    }
    if(signal(SIGQUIT, &sig_int) == SIG_ERR){
        printf("Couldn't register signal hanlder for SIGQUIT!\n");
        exit(1);
    }
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        printf("SIG_BLOCK error!\n");
        exit(3);
    }
    while(quitflag == 0){
        sigsuspend(&zeromask);
    }
    printf("Process wake up\n");
    quitflag = 0;
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        exit(0);
    }
}

void sig_int(int signum){
    if(signum == SIGINT){
        printf("\n interrupt\n");
    }
    else if(signum == SIGQUIT){
        printf("Catch SIGQUIT\n");
        quitflag = 1;
    }
    return;
}