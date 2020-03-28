#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int alarm_flag = 1;

/* SIGALRM 信号处理函数 */
void sig_alrm(int signum){
    printf("5秒钟延时结束\n");
    alarm_flag = 0;
}

/* SIGINT和SIGQUIT的信号处理函数 */
void sig_allin(int signum){
    if(signum == SIGINT){
        printf("捕获到了 SIGINT 信号\n");
    }
    else if(signum == SIGQUIT){
        printf("捕获到了 SIGQUIT 信号\n");
    }
}

int main(int argc, char* argv[]){
    sigset_t newmask, nowmask, pendmask;
    int i;

    /* 检查主函数的参数个数 */
    if(argc < 2){
        printf("Usage: %s num(>0)\n", argv[0]);
        return -1;
    }
    /* 循环显示 */
    for(i = atoi(argv[1]); i > 0; i--){
        printf("how are you?\n");
    }

    /* 注册SIGALRM、SIGINT、SIGQUIT的信号处理函数 */
    if(signal(SIGALRM, &sig_alrm) == SIG_ERR){
        printf("Couldn't register signal handler for SIGALRM\n");
        exit(1);
    }
    if(signal(SIGINT, &sig_allin) == SIG_ERR){
        printf("Couldn't register signal handler for SIGINT\n");
        exit(1);
    }
    if(signal(SIGQUIT, &sig_allin) == SIG_ERR){
        printf("Couldn't register signal handler for SIGQUIT\n");
        exit(1);
    }

    /* 将SIGINT添加到信号屏蔽集中 */
    sigemptyset(&newmask);
    sigemptyset(&nowmask);
    sigaddset(&newmask, SIGINT);
    if(sigprocmask(SIG_BLOCK, &newmask, NULL) < 0){
        printf("SIG_BLOCK error!\n");
        exit(1);
    }
    printf("屏蔽了 SIGINT 信号\n");

    /* 延时5秒钟，用来测试SIGINT和SIGQUIT信号是否被屏蔽 */
    printf("开始延时5秒钟 ...\n");
    alarm(5);
    while(alarm_flag);

    /* 读取处于未决状态的信号，保存至信号集 pendmask 中 */
    if(sigpending(&pendmask) < 0){
        printf("sigpending error!\n");
        exit(3);
    }
    if(!sigismember(&pendmask, SIGQUIT)){
        printf("SIGQUIT 信号不在屏蔽集中\n");
    }
    
    /* 取消对SIGINT的屏蔽 */
    if(sigprocmask(SIG_UNBLOCK, &newmask, NULL) < 0){
        printf("SIG_BLOCK error!\n");
        exit(1);
    }
    printf("取消了对 SIGINT 信号的屏蔽\n");
    /* 检测SIGINT是否已经取消屏蔽 */
    if(sigprocmask(0, NULL, &nowmask) < 0){
        printf("SIG_BLOCK error!\n");
        exit(1);
    }
    if(!sigismember(&nowmask, SIGINT)){
        printf("检测到 SIGINT 确实已经取消屏蔽了\n");
    }
    return 0;
}
