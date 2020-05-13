#include <stdio.h>

int main(int argc, char* argv[]){
	int i;
	FILE* fp;
	if(argc <= 1){
		printf("Usage: %s file\n", argv[0]);
		return -1;
	}
	// Open file with "w" mode
	fp = fopen(argv[1], "w");
	// Get one char from file
	fgetc(fp);
	printf("%d\n", ferror(fp));
	// Write file
	fputs("abcdefgh", fp);
	// Close and open again
	fclose(fp);
	fp = fopen(argv[1], "r");
	// Move file pointer
	fseek(fp, 0, SEEK_END);
	fgetc(fp);
	if(feof(fp)){
		printf("File end\n");
	}
	// Clear error
	clearerr(fp);
	printf("%d %d\n", ferror(fp), feof(fp));
	fclose(fp);
	return 0;
}
