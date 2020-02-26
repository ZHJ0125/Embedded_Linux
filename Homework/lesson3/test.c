#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define LEN 30

int main(){
	int fd;
	char buf[LEN]="\0";
	fd = open("hello.txt", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if(fd == -1){
		perror("Fail to open.");
		return -1;
	}
	if(write(fd, "Hello,software weekly", LEN) == -1){
		perror("Fail to write.");
		return -1;
	}
	if(close(fd) == -1){
		perror("Fail to close.");
		return -1;
	}
	// Check file
	if((fd=open("hello.txt",O_RDWR)) == -1)
	{
		perror("Fail to open.");
		return -1;
	}
	if(read(fd,buf,LEN-1) == -1)
	{
		perror("Fail to read.");
		return -1;
	}
	buf[LEN]='\0';
	printf("%s\n",buf);
	if(close(fd) == -1){
		perror("Fail to close.");
		return -1;
	}
	return 0;
}
