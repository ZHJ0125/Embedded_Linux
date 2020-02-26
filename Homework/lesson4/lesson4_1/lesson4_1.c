#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define STRING "write to the file!"
#define BUFSIZE 10

int main(){
	int fd;
	struct stat statbuf;
	char buf[20]="\0";
	int res;
	// Open file
	if((fd=open("test.c",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR)) == -1){
		perror("Fail to open:");
		return -1;
	}
	printf("Open file successful\n");
	// Write to file
	if((res = write(fd, STRING, strlen(STRING))) <= 0){
		perror("Fail to write:");
		return -2;
	}
	printf("Write data successful\n");
	// Get file size
	if(fstat(fd,&statbuf) == -1){
		perror("Fail to call fstat()");
		return -4;
	}
	printf("File size: %ld\n",statbuf.st_size);
	// Change offset
	lseek(fd, 0, SEEK_SET);
	// Read file
	if(read(fd, buf, BUFSIZE) == -1){
		perror("Fail to read");
		return 0;
	}
	printf("File data: %s\n", buf);
	close(fd);
	return 0;
}
