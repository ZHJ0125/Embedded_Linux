#include <stdio.h>
int main(int argc, char* argv[]){
	char buf[1024];
	FILE* fp;
	// Check parameters
	if(argc <= 1){
		printf("Uasge: %s filename\n",argv[0]);
		return -1;
	}
	// Open file
	if((fp = fopen(argv[1], "r")) == NULL){
		printf("File open error\n");
		return -2;
	}
	// Read data from filepoint
	while((fgets(buf, 1024, fp)) != 0){
		// Output file data
		puts(buf);
	}
	return 0;
}
