#include <stdio.h>
#include <sys/types.h>
#include <utime.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int i,fd;
	struct stat statbuf;
	struct utimbuf times;
	// Verify input parameters
	if(argc != 2){
		printf("Usage:ex3-3 filename\n");
		return 1;
	}
	// Open file
	if((fd = open(argv[1], O_RDWR)) == -1){
		printf("%s open failed\n", argv[1]);
		return 2;
	}
	// Get file information, stored in the structure "statbuf"
	if(stat(argv[1], &statbuf) == -1){
		return 3;
	}
	// Truncate the file
	if(ftruncate(fd, 0) == -1){
		printf("%s truncate failed\n", argv[1]);
		return 4;
	}
	printf("%s is truncated now\n", argv[1]);
	// Get file information from statbuf into times
	times.actime = statbuf.st_atime;
	times.modtime = statbuf.st_mtime;
	// Modify file information
	if(utime(argv[1], &times) == 0){
		printf("utime() call successful\n");
	}
	else{
		printf("Error: utime() call failed\n");
	}
	return 0;
}
