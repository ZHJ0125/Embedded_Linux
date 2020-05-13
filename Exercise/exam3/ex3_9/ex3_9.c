#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	char path[1000];
	DIR* dp;
	int num = 0;
	struct dirent* pdirent;
	// Check parameters
	if(argc != 2){
		printf("Usage ex3_9 <pathname>\n");
		return -1;
	}
	// Open directory
	if((dp = opendir(argv[1])) == NULL){
		printf("Opendir %s failed!\n",argv[1]);
		return -2;
	}
	// Read folder data
	/*
	if((pdirent = readdir(dp)) == 0){
		printf("Fail to call readdir()\n");
		return -3;
	}
	*/
	// Output folder data
	printf("In directory %s has following files:\n",argv[1]);
	while((pdirent = readdir(dp)) != NULL){
		printf("%s ",pdirent->d_name);
	}
	printf("\n");
	// Close directory
	closedir(dp);
	return 0;
}
