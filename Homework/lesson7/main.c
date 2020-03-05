#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	int childpid;
	if((pid = fork()) == -1){
		printf("Fail to create child progress\n");
		return -1;
	}
	if(pid == 0){
		// 进入子进程
		// printf("Here is child progress\n");
		printf("Please enter lowercase letters :\n");
		// 调用 function 实现转换和输出
		execl("./function", "./function", NULL);
		printf("Fail to call execl()\n");
	}
	else{
		wait(&childpid);	// 父进程等待子进程结束
		// printf("child progress exit successful\n");
	}
	return 0;
}
