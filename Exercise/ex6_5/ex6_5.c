#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_quit(int);

int main(){
    sigset_t newmask, oldmask, pendmask;
    if(signal(SIGQUIT, &sig_quit) == SIG_ERR){
        printf("Couldn't register signal handler for SIGQUIT\n");
        exit(1);
    }
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        printf("SIG_BLOCK error\n");
        exit(2);
    }
    sleep(5);
    if(sigpending(&pendmask) < 0){
        printf("sigpending error!\n");
        exit(3);
    }
    if(sigismember(&pendmask, SIGQUIT)){
        printf("SIGQUIT pending\n");
    }
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
        printf("SIG_SETMASK error!\n");
        exit(4);
    }
    printf("SIGQUIT unblocked!\n");
    sleep(5);
    exit(0);
}

static void sig_quit(int signum){
    printf("Catch SIGQUIT\n");
    if(signal(SIGQUIT, SIG_DFL) == SIG_ERR){
        printf("Couldn't reset SIGQUIT\n");
    }
    return;
}