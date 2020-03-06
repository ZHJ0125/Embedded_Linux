#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 8
#define STRLEN 100

int main(){
	pid_t pid;
	int* End_flag;
	int childpid, shmid;
	char origin[STRLEN];
	char* string;

	// Create shared memory
	if((shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT|0666)) == -1){
		printf("Fail to get shared memory\n");
		return -1;
	}
	End_flag = shmat(shmid, 0, 0);
	*End_flag = 0;

	while(1){
		// Create child process
		if((pid = fork()) == -1){
			printf("Fail to create child progress\n");
			return -2;
		}
		// Execute child process
		if(pid == 0){
			printf("Please enter lowercase (End with '#'):\n");
			fgets(origin, STRLEN, stdin);
			string = origin;
			// Start filtering strings
			while(*string != '\0'){
				// Check Sign of End -> #
				if(*string == '#'){
					*End_flag = 1;
					// Truncated string
					*(string+1) = '\n';
					*(string+2) = '\0';
					// printf("End flag on\n");
					break;
				}
				string++;
			}
			// printf("Ready to call execl()\n");
			// Call 'function' for conversion and output
			execl("./function", "./function", origin, NULL);
			printf("Fail to call execl()\n");
		}
		else{
			wait(&childpid);	// Wait for the child process to end
			// printf("child progress exit successful\n");
			if(*End_flag == 1){
				// printf("Get know flag on\n");
				break;
			}
			// printf("End flag is : %d\n", *End_flag);
		}
	}
	return 0;
}
