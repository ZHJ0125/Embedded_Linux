#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	pid_t pid;
	int status;
	// Check parameter format
	if(argc != 2){
		printf("Usage: %s [0/-1]\n", argv[0]);
		return -1;
	}
	// Fail to create child process
	if((pid = fork()) < 0){
		printf("Fork error!\n");
		exit(0);
	}
	// Execute child process
	else if(pid == 0){
		printf("Child pid = %d\n",getpid());
		if((atoi(argv[1])) == 0){
			exit(0);
		}
		else{
			abort();
		}
	}
	// Execute parent process
	else{
		// Wait child process to end
		if(wait(&status) != pid){
			printf("call wait() error!\n");
			exit(0);
		}
		// Check the status returned from child process
		if(WIFEXITED(status)){			// Child process ends normally
			printf("Normal termination, exit status = %d\n", WEXITSTATUS(status));
		}
		else if(WIFSIGNALED(status)){	// Child process ends abnormally
			printf("Abnormal termination, signal number = %d %s\n", WTERMSIG(status),
			#ifdef WCOREDUMP
				WCOREDUMP(status) ? "(core file generated)" : "");
			#else
				"");
			#endif
		}
	}
	return 0;
}
