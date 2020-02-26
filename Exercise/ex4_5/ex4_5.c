#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define NAMESIZE 30

// Store student information
struct {
	char name[NAMESIZE];
	long number;
	short department;
	short scores[10];
} student;
// Store student grades
short* pscores;

int main(int argc, char* argv[]){
	FILE* fpstudents;
	FILE* fpscore;
	short data;
	// Check parameters
	if(argc <= 2){
		printf("Usage: %s <sourcefile> <destfile>",argv[0]);
		return -1;
	}
	// Open source file
	if((fpstudents = fopen(argv[1], "rb")) == NULL){
		printf("Open sourcefile %s failed!\n",argv[1]);
		return -2;
	}
	// Open destination file
	if((fpscore = fopen(argv[2], "wb")) == NULL){
		printf("Created destfile %s failed!\n",argv[2]);
		return -3;
	}
	// Read student data and extract grade information
	while(fread(&student, sizeof(student), 1, fpstudents) == 1){
		// Get one person grade
		pscores = student.scores;
		// Write student information into the destination file
		if(fwrite(&pscores, sizeof(short), 3, fpscore) != 3){
			printf("Error in writing file!\n");
			return -4;
		}
	}
	fclose(fpstudents);
	fclose(fpscore);
	
	// Open destination file
    if((fpscore = fopen(argv[2], "rb")) == NULL){
        printf("Open destfile %s failed!\n",argv[2]);
        return -3;
    }
	// Output data
	while(fread(&data, sizeof(short), 1, fpscore) == 1){
		printf("%d ",data);
    }
	printf("\n");
	fclose(fpscore);
	
	return 0;
}
