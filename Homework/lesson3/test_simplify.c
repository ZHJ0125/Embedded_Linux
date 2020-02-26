#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define LEN 30
#define FILENAME "hello.txt"
#define STR "Hello,software weekly"

int main(){
	int fd;
	char buf[LEN]="\0";
	if((fd = open(FILENAME, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR)) == -1){
		perror("Fail to open");
		return -1;
	}
	write(fd, STR, LEN);
	close(fd);
	// Check file
	fd=open(FILENAME, O_RDWR);
	read(fd,buf,LEN-1);
	close(fd);
	buf[LEN]='\0';
	printf("%s\n",buf);
	return 0;
}
