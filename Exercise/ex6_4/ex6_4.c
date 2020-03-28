// 打印调用进程的信号掩码中的信号名称
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void pr_mask(int signum){
    sigset_t sigset;
    // 将信号掩码赋值到sigset中
    if(sigprocmask(0, NULL, &sigset) < 0){
        printf("sigprocmask error\n");
        exit(0);
    }
    // 检测信号掩码中是否含有 SIGINT 函数
    if(sigismember(&sigset, SIGINT)){
        printf("SIGINT\n");
    }
    // 检测信号掩码中是否含有 SIGTERM 函数
    if(sigismember(&sigset, SIGTERM)){
        printf("SIGTERM\n");
        exit(0);
    }
}

int main(){
    char buffer1[100], buffer2[100];
    int i;
    // 绑定信号处理函数
    if(signal(SIGINT, &pr_mask) == SIG_ERR){
        printf("Couldn't register signal handler for SIGINT\n");
        exit(1);
    }
    if(signal(SIGTERM, &pr_mask) == SIG_ERR){
        printf("Couldn't register signal handler for SIGTERM\n");
        exit(1);
    }
    // 打印进程 PID
    printf("PID of This Process: %d\n", getpid());
    // 大小写转换
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