#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd;
	char buf[10];
	fd = open("./test.c", 0);
	read(fd, buf, 10);
	printf("======= Output in main() ======\n%s\n",buf);
	printf("fd of test.c is: %d\n",fd);
	fcntl(fd, F_SETFD, 1);	// setoff close_on_exec
	execl("./test", "./test", NULL);
	printf("execl error\n");
}
