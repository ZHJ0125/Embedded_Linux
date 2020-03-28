#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_quit(int);

int main(){
    sigset_t newmask, oldmask, pendmask;
    // 绑定信号处理函数
    if(signal(SIGQUIT, &sig_quit) == SIG_ERR){
        printf("Couldn't register signal handler for SIGQUIT\n");
        exit(1);
    }
    // 清空信号掩码
    sigemptyset(&newmask);
    // 添加 SIGQUIT 信号至信号掩码中
    sigaddset(&newmask, SIGQUIT);

    // 增加信号
    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
        printf("SIG_BLOCK error\n");
        exit(2);
    }
    // 延时5秒
    sleep(5);
    // pendmask 返回被阻塞的信号集合
    if(sigpending(&pendmask) < 0){
        printf("sigpending error!\n");
        exit(3);
    }
    // 检测 pendmask 里面是否含有 SIGQUIT 信号
    if(sigismember(&pendmask, SIGQUIT)){
        printf("SIGQUIT pending\n");
    }
    // 重置信号掩码
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