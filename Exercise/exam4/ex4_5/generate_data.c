#include <stdio.h>
#include <string.h>
#define NAMESIZE 30
#define MEMBER 5

// Store student information
struct student{
    char name[NAMESIZE];
    long number;
    short department;
    short scores[10];
} stu[MEMBER];

int main(int argc, char* argv[]){
	int num;
	int subject;
	FILE* fpstudents;
	// Init data
	strcpy(stu[0].name, "zhang0");
	strcpy(stu[1].name, "zhang1");
	strcpy(stu[2].name, "zhang2");
	strcpy(stu[3].name, "zhang3");
	strcpy(stu[4].name, "zhang4");
	for(num=0; num<MEMBER; num++){
		stu[num].number = num+10;
		stu[num].department = num+1;
		for(subject=0; subject<10; subject++){
			stu[num].scores[subject] = num * subject + 60;
		}
	}
	// Check parameters
    if(argc <= 1){
        printf("Usage: %s <sourcefile>",argv[0]);
        return -1;
    }
	// Open source file
    if((fpstudents = fopen(argv[1], "wb")) == NULL){
        printf("Open sourcefile %s failed!\n",argv[1]);
        return -2;
    }
	// Write initial data
	if(fwrite(&stu, sizeof(struct student), 5, fpstudents) != 5){
		printf("Initializing data failed!\n");
		return -3;
	}
	// Close file
	fclose(fpstudents);
	return 0;
}
