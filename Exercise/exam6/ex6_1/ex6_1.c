#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigcatcher(int signum);

int main(){
    char buffer1[100], buffer2[100];
    int i;
    if((signal(SIGTERM, &sigcatcher)) == SIG_ERR){
        printf("Couldn't register signal hanlder!\n");
        exit(1);
    }
    printf("Pid of This Process : %d\n", getpid());
    printf("Please input: \n");
    while(1){
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

void sigcatcher(int signum){
    printf("Catch Signal SIGTERM\n");
    exit(0);
}