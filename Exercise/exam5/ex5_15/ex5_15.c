#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

struct sigway{
    char *sigstr;
    int value;
};

struct sigway sigways[] = {
    "hup",1,"int",2,"quit",3,"ill",4,"trap",5,"iot",6,"abrt",7,"emt",8,
    "fpe",9,"kill",10,"bus",11,"segv",12,"sys",13,"pipe",14,"alrm",15,
    "gterm",16,"user1",17,"user2",18,"cld",19,"pwr",20,"poll",21,(char*)0,0
};

void statport(int pid, int stat);

int main(int argc, char* argv[]){
    int i, pid, stat;
    char *p;
    if(argc <= 1){
        printf("Usage: %s cmd1 cmd2 ... \n", argv[0]);
        return -1;
    }
    setbuf(stdout, NULL);   // 将标准输出流中的数据清空
    // 循环进入每一条命令
    for(i = 1, p = argv[1]; argc > 1; p = argv[1]){
        // Ｐ是指向单条命令的指针，输出命令序号和命令内容
        printf("===== [%d]: command '%s' begin =====\n", i, p);
        if((pid = fork()) == 0){
            // 获取子进程的PID
            printf("Child pid = %d\n", getpid());
            // 逐条执行命令
            execl(argv[1], argv[1], NULL);
            exit(argc);     // 执行失败返回命令序号
        }
        // 父进程等待子进程结束
        pid = wait(&stat);
        // 判断并输出子进程的结束信息
        statport(pid, stat);
        argc--; argv++;
        // 输出命令序号和命令内容
        printf("===== [%d]: command '%s' end =====\n\n", i++, p);
    }
}

/**
* Description: 用来判断和输出子进程的结束状态
* Param: 
*   - int pid: 子进程的标识号
*   - int stat: 子进程的终止状态信息
* Return: void
* Date: 2020/03/16
*/
void statport(int pid, int stat){
    int i;
    if(pid == -1){
        // wait函数错误，没有子进程
        printf("Bad wait\n");
    }
    //　下面是根据stat状态信息，判断子进程的返回状态
    else if((stat&0177) == 0177){
        i = stat>>8;
        printf("Child process: %d stop by signal\n", pid);
        printf("Signal name: %s\n", sigways[i].sigstr);
        printf("Signal value: %d\n", sigways[i].value);
    }
    else if((stat&0xff) == 0){
        printf("Child process: %d exit by 'exit' system call.\n", pid);
        printf("Exit code: %d\n", stat >> 8);
    }
    else if((stat >> 8) == 0){
        if((stat&0200) == 0200){
            printf("Child process: %d '-core dumped' by signal\n", pid);
        }
    }
}