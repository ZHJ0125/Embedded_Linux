#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	int i;
	struct stat buf;
	char* ptr;
	// Check all files
	for(i=1; i<argc; i++){
		printf("%s: ", argv[i]);
		// Get file information and stored into buf
		if(lstat(argv[i], &buf) == -1){
			printf("Error::lstat() call failed\n");
			continue;
		}
		// Determine the file type
		switch(S_IFMT & buf.st_mode){
			case S_IFREG: ptr = "regular"; break;
			case S_IFDIR: ptr = "directory"; break;
			case S_IFCHR: ptr = "character special"; break;
			case S_IFBLK: ptr = "block special"; break;
			case S_IFIFO: ptr = "fifo"; break;
			case S_IFLNK: ptr = "symbolic link"; break;
			case S_IFSOCK: ptr = "socket"; break;
			default: ptr = "unknown mode";
		}
		printf("%s\n", ptr);
	}
	return 0;
}
