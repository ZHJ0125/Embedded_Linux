#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#define BUFSIZE 20

int main(int argc, char* argv[]){
	int num;
	int fd;
	char buf[BUFSIZE]="\0";
	// Only one command, no parameters
	if(argc < 2){
		// In this case, the input stream is standard input(stdin)
		// and the output stream is standard output(stdout)
		while(1)
		while(fgets(buf,BUFSIZE-1,stdin)!=NULL){
			// fputs(buf,stdout);
			printf("%s",buf);
			memset(buf,0,BUFSIZE);
		}
	}
	// Two or more parameters
	// Read data from file and display to stdout
	else{
		// Open all files one by one
		for(num=1; num<argc; num++){
			// Open target file
			if((fd=open(*(argv+num),O_RDONLY)) == -1){
				perror("Fail to Open file");
				return -1;
			}
			// Read file
			while(read(fd,buf,BUFSIZE-1) > 0){
				printf("%s",buf);
				memset(buf,0,BUFSIZE);
			}
			// Close file
			close(fd);
		}
	}
	return 0;
}
