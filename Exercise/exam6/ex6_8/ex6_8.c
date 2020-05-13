#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int usr_interrupt = 0;

void synch_signal(int signum){
    usr_interrupt = 1;
}

void child_function(){
    printf("I'm child process. My PID is %d\n", getpid());
    sleep(5);
    kill(getppid(), SIGUSR1);
    puts("Good Bye!\n");
    exit(0);
}

int main(){
    struct sigaction usr_action;
    sigset_t block_mask;
    pid_t child_id;
    sigfillset(&block_mask);
    usr_action.sa_handler = synch_signal;
    usr_action.sa_mask = block_mask;
    usr_action.sa_flags = 0;
    sigaction(SIGUSR1, &usr_action, NULL);
    child_id = fork();
    if(child_id == 0){
        child_function();
    }
    while(!usr_interrupt);
    puts("That's all!\n");
    return 0;
}