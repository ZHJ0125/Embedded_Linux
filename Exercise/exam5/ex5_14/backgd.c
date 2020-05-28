#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;
    printf("My PID is: %d\n", getpid());
    sleep(10);
    while(1){
        printf("Test\n");
        sleep(2);
    }
    return 0;
}

