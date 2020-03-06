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
		// Execute child process
		// printf("Here is child progress\n");
		printf("Please enter lowercase letters :\n");
		// Call 'function' for conversion and output
		execl("./function", "./function", NULL);
		printf("Fail to call execl()\n");
	}
	else{
		wait(&childpid);	// Wait for the child process to end
		// printf("child progress exit successful\n");
	}
	return 0;
}
