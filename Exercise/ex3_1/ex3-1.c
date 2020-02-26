#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define PERMS 0666
#define DUMMY 0
#define BUFSIZE 1024

int main(int argc, char* argv[])
{
	int source_fd,target_fd,num;
	char iobuffer[BUFSIZE];
	// Validate input parameters
	if(argc != 3)
	{
		printf("Usage:copy Sourcefile Targetfile\n");
		return 1;
	}
	// Open Source file
	if((source_fd = open(*(argv+1),O_RDONLY,DUMMY)) == -1)
	{
		printf("Source file open error!\n");
		return 2;
	}
	// Open target file
	if((target_fd = open(*(argv+2),O_WRONLY|O_CREAT,PERMS)) == -1)
	{
		printf("Target file open error!\n");
		return 3;
	}
	// Implement the "copy" function
	while((num = read(source_fd,iobuffer,BUFSIZE)) > 0)
	{
		if(write(target_fd,iobuffer,num) != num)
		{
			printf("Target file write error!\n");
			return 4;
		}
	}
	// Close file
	close(source_fd);
	close(target_fd);
	return 0;
}
