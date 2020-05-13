#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid;
    // 创建子进程
    if((pid = fork()) < 0){
        printf("Fork Error!\n");
        return -1;
    }
    // 执行子进程
    else if (pid == 0)
    {
        // 再次创建子子进程
        if((pid = fork()) < 0){
            printf("Fork Error!\n");
            return -2;
        }
        // 父进程
        else if (pid > 0)
        {
            exit(0);
        }
        sleep(2);
        // 获取子子进程的PID
        printf("Second child, parent pid = %d\n", getpid());
        exit(0);        
    }
    // 执行父进程
    if(waitpid(pid, NULL, 0) != pid){
        printf("call waitpid() error!\n");
        exit(0);
    }
    exit(0);
}