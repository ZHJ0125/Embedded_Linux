#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#define BUFSIZE 1000

int main(int argc, char* argv[]){
	char path[1000];
	// Check parameters
	if(argc != 2){
		printf("Usage ex3-8 <pathname>\n");
		return -1;
	}
	// Get work directory
	if((getcwd(path, BUFSIZE)) == NULL){
		printf("Get current directory erreo!\n");
		return -4;
	}
	printf("Current directory is %s\n",path);
	// Make new directory
	if(mkdir(argv[1], S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH) == -1){
		printf("mkdir failed\n");
		return -2;
	}
	// Change directory
	if(chdir(argv[1]) == -1){
		printf("Fail to change directory\n");
		return -3;
	}
	// Get current directory again
	getcwd(path, BUFSIZE);
	printf("mkdir successed\nNew current directory is %s\n",path);
	// Remove directory
	rmdir(path);
	printf("%s is removed\n",path);
	return 0;
}
