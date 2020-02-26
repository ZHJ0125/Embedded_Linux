#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	DIR* dp;
	struct dirent* pdirent;
	// Check parameters
	if(argc != 2){
		printf("Usage: %s <pathname>\n", argv[0]);
		return -1;
	}
	// Open directory
	if((dp = opendir(argv[1])) == NULL){
		printf("Opendir %s failed!\n",argv[1]);
		return -2;
	}
	// Output prompt message
	printf("\nIn directory '%s' has following files:\n\n",argv[1]);
	printf("---------------------------------------\n");
	printf("|     File Name       |  inode number |\n");
	printf("---------------------------------------\n");
	// Output data
	while((pdirent = readdir(dp)) != NULL){
		printf("|     %-16s|    %-11ld|\n", pdirent->d_name, pdirent->d_ino);
	}
	printf("---------------------------------------\n\n");
	// Close directory
	closedir(dp);
	return 0;
}
