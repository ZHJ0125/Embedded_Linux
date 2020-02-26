#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]){
	DIR* dp;
	struct stat statBuf;
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
	// Change directory
	if(chdir(argv[1]) == -1){
		printf("Fail to change dir\n");
		return -3;
	}
	// Output folder data
	printf("\nIn directory %s has following files:\n",argv[1]);
	printf("\nFile Name\tinode\n");
	while((pdirent = readdir(dp)) != NULL){
		memset(&statBuf, 0, sizeof(struct stat));
		// Get information
		if(stat(pdirent->d_name, &statBuf) == -1){
			perror("Fail to call stat() ");
			return -4;
		}
		printf("%-10s\t", pdirent->d_name);
		printf("%ld\n", statBuf.st_ino);
	}
	// Close directory
	closedir(dp);
	return 0;
}
