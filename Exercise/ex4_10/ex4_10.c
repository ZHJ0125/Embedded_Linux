#include <stdio.h>

int get_line(char* buf, int bufsize, FILE* fp){
	if(fgets(buf, bufsize, fp) == NULL){
		if(feof(fp)){
			printf("End of file\n");
			return EOF;
		}
		else{
			printf("Call fgets() failed\n");
			return 0;
		}
	}
	printf("Call fgets: %s \n", buf);
	return 0;
}

char buf[132];
int main(int argc, char* argv[]){
	FILE* fp;
	// Check parameters
	if(argc <= 1){
		printf("Usage: %s file\n", argv[0]);
		return -1;
	}
	// Open file with "w+" mode
	if((fp = fopen(argv[1], "w+")) == NULL){
		printf("Call fopen() failedn\n");
		return -2;
	}
	// Write two lines into file
	fprintf(fp, "This is first line.\n");
	fprintf(fp, "This is second line.\n");
	// Close file
	fclose(fp);

	// Open file with "r+" mode
	if((fp = fopen(argv[1], "r+")) == NULL){
		printf("Call fopen() failedn\n");
		return -3;
	}
	// Read data from file
	get_line(buf, sizeof(buf), fp);
	// fflush(NULL);
	fprintf(fp, "This line should be the new second line.\n");
	fflush(NULL);
	get_line(buf, sizeof(buf), fp);
	// Close file
	fclose(fp);
	return 0;
}
