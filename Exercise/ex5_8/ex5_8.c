#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void h_exit(int status){
	if(WIFEXITED(status)){
		printf("Normal termination, exit status = %d\n", WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status)){
		printf("Abnormal termination, signal number = %d %s\n", WTERMSIG(status),
	#ifdef WCOREDUMP
		WCOREDUMP(status)?"(core file generated)":"");
	#else
		"");
	#endif
	}
}

int main(){
	pid_t pid;
	int status;
	// Check whether WCOREDUMP has defined or not
	#ifdef WCOREDUMP
		printf("Defined WCOREDUMP\n");
	#endif
	if((pid = fork()) < 0){
		printf("Fork error!\n");
		exit(0);
	}
	else if(pid == 0){
		exit(7);
	}
	if(wait(&status) != pid){
		printf("Wait error!\n");
		exit(0);
	}
	h_exit(status);
	if((pid = fork()) < 0){
		printf("fork error!\n");
		exit(0);
	}
	else if(pid == 0){
		abort();
	}
	if(wait(&status) != pid){
		printf("Wait() failed\n");
		exit(0);
	}
	h_exit(status);
	if((pid = fork()) < 0){
		printf("fork error!\n");
		exit(0);
	}
	else if(pid == 0){
		status /= 0;
	}
	if(wait(&status) != pid){
		printf("Wait() failed\n");
		exit(0);
	}
	h_exit(status);
	exit(0);
}
