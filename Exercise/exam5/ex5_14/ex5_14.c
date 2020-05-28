#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define MAXARG 10
#define LINSIZ 80               // 限制每条命令的长度
#define CMDSIZ 8                // 限制命令的个数

extern char** environ;
char* quit = "quit.quit";
char cmdbuf[CMDSIZ][LINSIZ];    // 用来存放用户的命令，最多接收8个命令
int cmdflag[CMDSIZ];

int readcmd(void);
void docommand(int i);

int main(){
    int i;
    while (1){
        printf("Mini_SH --> ");
        // Clear flags
        for(i = 7; i >= 0; i--){
            cmdflag[i] = 0;
            cmdbuf[i][0] = '\0';
        }
        // Read command from terminal
        if(i = readcmd()){
            docommand(i);
        }
        // Fail to read command
        else{
            printf("Read Command Failed, Try Again!\n");
        }
    }
}

/**
* @Description: 读取用户输入的命令，各个命令之间以";"分隔，将命令保存在cmdbuf二维数组中，命令以'\0'结尾
* @Param: void
* @Return: int 返回读取命令的个数
* @Date: 2020/03/15
*/
int readcmd(void){
    char c, *p;
    int i = 0;                          // I 表示命令的个数
    p = cmdbuf[0];                      // 清除命令缓冲数组中的数据
    while ((c = getchar()) != '\n'){    // 开始读命令,以回车结束
        // 判定为下一个命令
        if(c == ';'){
            *p = '\0';                  // 本条命令结束
            if( ++i == 6){              // 限制命令的个数 （最多6个命令？？？？）
                return (++i);
            }
            p = cmdbuf[i];              // P指向下一条命令
        }
        // 判断每一条命令的 & 标志，如果存在就记录在cmdflag中，表示命令在后台执行
        else if (c == '&'){
            cmdflag[i] = 1;
        }
        // 同一条命令，使用指针进行记录
        else{
            *(p++) = c;
        }
    }
    *p = '\0';
    // 返回命令的个数
    return (++i);
}

/**
* @Description: 首先逐条处理每一个指令，将处理后的指令保存在args中。
*               注意：*arglp指向了argsp，然后argsp指向了args，args用来存放每条数据；argl相当于argsp
* @Param: int 表示命令的个数
* @Return: void
* @Date: 2020/03/15
*/
void docommand(int i){
    int j, stat, pid;
    char *argl[MAXARG], args[LINSIZ];
    char c, *argsp, **arglp, *p;
    // 读取每一条命令，j 表示当前命令
    for(j = 0; j < i; j++){
        arglp = argl;
        argsp = args;
        p = cmdbuf[j];      // cmfbuf表示每一条命令
        // 按字符读取每一条命令
        while((c = *p++) != '\0'){
            while(c == ' ' || c == '\t'){
                c = *p++;   // 读下一个字符
            }
            if(c == '\0'){  // 该条命令结束了
                *argsp++ = '\0';
                break;
            }
            *arglp++ = argsp;       // 这里arglp指向了argsp，然后arglp再指向下一个
            while((c!=' ') && (c!='\t') && (c!='\0')){
                *argsp++ = c;       // 这里比较关键，将有效的命令字符保存到了argsp所指向的空间args
                c = *p;
                if(c) p++;
            }
            *argsp++ = '\0';
        }
        *arglp = (char*)0;
        if(strcmp(argl[0], quit) == 0){
            printf("Bye Bye!\n");
            exit(0);
        }
        if((pid = fork()) == 0){
            if(cmdflag[j]){
                setpgrp();          // 相当于后台执行
            }
            execve(argl[0], argl, environ);
            printf("Return from execve: %s\n", cmdbuf[i]);
            exit(10);
        }
        else{
            if(!cmdflag[j]){        // 前台执行时，父进程等待命令执行结束
                while(wait(&stat) != pid);
            }
        }
    }
}