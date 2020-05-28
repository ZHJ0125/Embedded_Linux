#include <stdio.h>
#include <stdlib.h>
char buf[132];

int main(int argc, char* argv[]){
	FILE* fp;
	fpos_t pos;
	if(argc != 2){
		printf("Usage: %s mode\n",argv[0]);
		return -1;
	}
	// Open a file
	if(argv[1][0] != 'a'){
		if((fp = fopen("testfile", "w+")) == NULL){
			printf("Call fopen() failed\n");
			return -2;
		}
	}
	else{
		if((fp = fopen("testfile", "a+")) == NULL){
			printf("Call fopen() failed\n");
			return -3;
		}
	}
	// Write file
	fputs("1234567890", fp);
	fputs("abcdefghij", fp);
	// Check file pos
	fseek(fp, 0, SEEK_END);
	fgetpos(fp, &pos);
	printf("Current file end position is: %ld\n", pos.__pos);
	// Move the pointer position 
	fseek(fp, 30, SEEK_END);
	// Check file pos
	fgetpos(fp, &pos);
	printf("Call fseek(fp, 30, SEEK_END)\n");
	printf("Current file end position is: %ld\n", pos.__pos);
	// Write file
	fputs("abcdefg", fp);
	printf("Write %s \n", "abcdefg");
	// Check file pos
	fgetpos(fp, &pos);
	printf("Current file end position is: %ld\n", pos.__pos);
	// Close file
	fclose(fp);
	return 0;
}
