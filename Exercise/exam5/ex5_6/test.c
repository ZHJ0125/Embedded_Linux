#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int i,fd;
	char buf[1000];
	for(i=0; i<1000; i++){
		buf[i] = '\0';
	}
	fd = open("./ex5_6.c", 0);
	printf("===== fd=%d in test.c =====\n",fd);
	fd -= 1;
	read(fd, buf, 1000);
	printf("===== Output in test.c =====\n%s\n",buf);
	return 0;
}
