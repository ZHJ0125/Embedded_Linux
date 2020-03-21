#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigcatcher(int signum);
int flag = 1;

int main(){
    // Registering signal handlers
    if((signal(SIGINT, &sigcatcher)) == SIG_ERR){
        printf("Couldn't register signal handler\n");
        exit(1);
    }
    // Cyclic display based on flag
    while(flag){
        printf("How are you!\n");
        usleep(100000);   // delay 100ms
    }
    return 0;
}

void sigcatcher(int signum){
    flag = 0;
    printf("Bye bye!\n");
}
