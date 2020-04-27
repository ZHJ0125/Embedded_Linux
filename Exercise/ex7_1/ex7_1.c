#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>

void print_message(char *ptr);

int main(){
    pthread_t thread1, thread2;
    char *msg1 = "Hello\n";
    char *msg2 = "World\n";
    printf("PID is: %d\n", getpid());
    pthread_create(&thread1, NULL, (void*)(&print_message), (void*)msg1);
    pthread_create(&thread2, NULL, (void*)(&print_message), (void*)msg2);
    sleep(10);  // 延时用来检查进程的数量，是否只有一个进程
    return 0;
}

void print_message(char *ptr){
    int retval;
    printf("Thread ID: %lx ", pthread_self());
    printf("%s", ptr);
    pthread_exit(&retval);
}
