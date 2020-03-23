#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void sighandler(int signum);

int main(){
    char buffer1[100], buffer2[100];
    int i;
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if(sigaction(SIGTERM, &act, NULL) == -1){
        printf("Couldn't register signal handler!\n");
        return -1;
    }
    printf("Pid of this process: %d\n", getpid());

    while(1){
        printf("Please input: \n");
        fgets(buffer1, sizeof(buffer1), stdin);
        for(i=0; i<100; i++){
            if(buffer1[i] >= 97 && buffer1[i] <= 122){
                buffer2[i] = buffer1[i] - 32;
            }
            else{
                buffer2[i] = buffer1[i];
            }
        }
        printf("Your input is: %s\n", buffer2);
    }
    exit(0);
}

void sighandler(int signum){
    printf("Catch signal SIGTERM\n");
    exit(0);
}