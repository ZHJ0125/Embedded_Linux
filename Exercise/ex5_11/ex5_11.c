#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int i,ret;
	if(argc != 2){
		printf("Usage: %s num\n", argv[0]);
		exit(1);
	}
	i = atoi(argv[1]);
	printf("Before uid = %d, euid = %d\n", getuid(), geteuid());
	ret = setuid(i);
	printf("After uid = %d, euid = %d\n", getuid(), geteuid());
	printf("ret = %d\n",ret);
}
