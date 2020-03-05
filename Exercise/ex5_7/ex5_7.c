#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	int fd;
	int stat,pid;
	struct stat stbuf;
	time_t old_time = 0;
	if(argc != 3){
		fprintf(stderr, "Usage:%s watchfile copyfile\n", argv[0]);
		return -1;
	}
	if((fd = open(argv[1], O_RDONLY)) == -1){
		fprintf(stderr, "Watchfile: %s can't open\n", argv[1]);
		return -2;
	}
	fstat(fd, &stbuf);
	old_time = stbuf.st_mtime;
	//printf("Get old time\n");
	close(fd);
	while(1){
		if((fd = open(argv[1], O_RDONLY)) == -1){
			fprintf(stderr, "Watchfile: %s can't open\n", argv[1]);
			return -2;
		}
		fstat(fd, &stbuf);
		close(fd);
		if(old_time != stbuf.st_mtime){
		//	printf("mtime changed\n");
			while((pid = fork()) == -1);
		//	printf("Create a child progress\n");
			if(pid == 0){
				execl("/bin/cp", "/bin/cp", argv[1], argv[2], NULL);
				return -3;
			}
		//	printf("Waitting child progress\n");
			wait(&stat);
		//	wait(NULL);
			if(WIFEXITED(stat) > 0){
		//		printf("Child progress exit successful\n");
			}
			old_time = stbuf.st_mtime;
		}
		else{
		//	printf("Sleep(5)\n");
			sleep(5);
		}
	}
	return 0;
}
