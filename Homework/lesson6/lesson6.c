#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define NUM_OF_STUDENT 8
#define NUM_OF_MARK 6

struct student {
	char name[10];
	int mark[NUM_OF_MARK];
	int stuid;
	double avg;
	int total;
	int rank;
};


/*************************************************
Function: main
Description: Generate Student's ID Marks Name Total&Average ,and display them.
Input: None
Output: Student's Data
Return: zero
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
int main()
{
	struct student stu[NUM_OF_STUDENT];		// Define struct student
	Generate_Student_Mark(stu);				// Set student's marks
	Show_Student_Mark(stu);					// Display student's marks
	//Count_Total_Score(stu);				// Calculate total marks of every student
	//Show_Total_Mark(stu);					// Display total marks
	Count_TotalAndAvg(stu);					// Calculate Total and Average mark of every student
	Show_TotalAndAvg(stu);					// Display Total and Average mark

	/************** Used to test "Generate_Random_String" function *****************
	srand(time(NULL));
	for(int i=0;i<10;i++)
	{
		printf("%s\n",Generate_Random_String(4,6));
	}
	************************************ Test End **********************************/

	Generate_Random_Name(stu,4,6);			// Generate Random Student's Name which Length from 4 to 6
	Show_Student_Name(stu);					// Display Student's Name

	Generate_Student_ID(stu);				// Generate student's ID
	Show_Student_ID(stu);					// Display Student's ID

	Show_Student_Rank(Count_Rank(stu));		// Calculate student's rank and display it
	//Show_TotalAndAvg(stu);				// Display Student's Total and Average mark (just for test)

	Show_All_Data(stu);						// Display All Data of structure	
	Show_Data_Sorted_By_Mark(stu);			// Display Data which Sorted by Mark

	Write_Data_to_File(stu, "StudentData");	// Write Student's Data to file
	return 0;
}


/*************************************************
Function: Generate_Student_Mark
Description: Set struct student's data of marks
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/25
*************************************************/
void Generate_Student_Mark(struct student* test)
{
	int mark;
	int con = 0;
	int less_than60 = 0;
	int more_than90 = 0;
	srand(time(NULL));
	while(con < NUM_OF_STUDENT)		// loop for erery struct
	{
		int current;
		for(current=0; current<NUM_OF_MARK;)
		{
			mark = rand()%101;		// mark from 0~100
			if(mark < 60)			// mark < 60
			{
				less_than60 ++;
				if(less_than60 > (int)(6*NUM_OF_STUDENT*0.1));	// num of "less than 60" > 10%
				else
				{
					*(((test+(con))->mark)+(current++)) = mark;
				}
			}
			else if(mark > 90)		// mark > 90
			{
				more_than90 ++;
				if(more_than90 > (int)(6*NUM_OF_STUDENT*0.1));	// num of "more than 90" > 10%
				else
				{
					*(((test+(con))->mark)+(current++)) = mark;
				}
			}
			else
			{
				*(((test+(con))->mark)+(current++)) = mark;
			}
		}
		con ++;		// for next struct
	}
}



/*************************************************
Function: Count_Total_Scroe
Description: Calculate Total mark of every student
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/25
*************************************************/
void Count_Total_Score(struct student* test)
{
	int total;
	int con = 0;
	while(con < NUM_OF_STUDENT)
	{
		total = 0 ;		// init total variable
		int current;
		for(current=0; current<NUM_OF_MARK; current++)
		{
			total += *(((test+(con))->mark)+(current));
		}
		((test+(con++))->total) = total;		// Record data into Struct
	}
}



/*************************************************
Function: Count_TotalAndAvg
Description: Calculate Total and average mark of every student
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Count_TotalAndAvg(struct student* test)
{
	int total;
	int con = 0;
	while(con < NUM_OF_STUDENT)
	{
		total = 0 ;		// init total variable
		int current;
		for(current=0; current<NUM_OF_MARK; current++)
		{
			total += *(((test+(con))->mark)+(current));
		}
		((test+(con))->total) = total;		// Record data into Struct
		((test+(con++))->avg) = ((total * 1.0) / NUM_OF_MARK);	// Record average mark of student
	}
}



/*************************************************
Function: Show_Student_Mark
Description: Display struct student's data of marks
Input: Structure pointer of student *test
Output: Student's Marks
Return: None
Author: ZhangH.J.
Date: 2019/10/25
*************************************************/
void Show_Student_Mark(struct student* test)
{
	int con=0;
	while(con < NUM_OF_STUDENT)	// loop for every struct
	{
		//printf("mark of student %d is %d \n", con, *(test->mark+(con++)));
		printf("The marks of student %d is :", con);
		int current = 0;
		for(current=0;current<NUM_OF_MARK;current++)	// loop for every student 
		{
			printf("%d ",*((test+(con))->mark+(current)));
		}
		printf("\n");
		con ++;
	}
}



/*************************************************
Function: Show_Total_Mark
Description: Display Total mark of every student
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/25
*************************************************/
void Show_Total_Mark(struct student* test)
{
	int con = 0;
	while(con < NUM_OF_STUDENT)
	{
		printf("The total mark of student %d is : %d\n",con,((test+(con))->total));
		con ++;		// loop for next student
	}
}



/*************************************************
Function: Show_TotalAndAvg
Description: Display Total And Average mark of every student
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Show_TotalAndAvg(struct student* test)
{
	int con = 0;
	while(con < NUM_OF_STUDENT)
	{
		printf("Student %d -> Total : %d \t Average : %.2lf\n",con,((test+(con))->total),((test+(con))->avg));
		con ++;		// loop for next student
	}
}



/*************************************************
Function: Generate_Random_String
Description: Generate random string which length from min to max
Input: Min means Minimum length ; Max means maximum length of String.
Output: None
Return: Char pointer to a random string
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
char* Generate_Random_String(int Min, int Max)
{
	int bit = 0;
	//srand(time(NULL));		// Set random number seed
	int length = rand()%(Max-Min+1) + Min;	// length from Min to Max
	static char temp_char[1];
	temp_char[0] = rand()%26 + 'A';		// Generate an uppercase letter for first name char
	static char src[1];
	static char dest[10];
	static char string[10];
	strcpy(dest,"\0");		// Initial value
	while(bit < length)
	{
		strcpy(src, temp_char);
		strcat(dest, src);
		temp_char[0] = rand()%26 + 'a';		// Generate an lower case letters
		bit ++;
	}
	strcpy(string, dest);

	return string;			// return pointer of random string
}



/*************************************************
Function: Generate_Random_Name
Description: Generate random Name of every student
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Generate_Random_Name(struct student* test, int Min, int Max)
{
	int con = 0;
	while(con < NUM_OF_STUDENT)
	{
		char *name = Generate_Random_String(Min,Max);
		strcpy(((test+(con++))->name), name);
	}
}



/*************************************************
Function: Show_Student_Name
Description: Display Name of every student
Input: Structure pointer of student *test
Output: Every student's name
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Show_Student_Name(struct student *test)
{
	int con = 0;
	while(con < NUM_OF_STUDENT)
	{
		printf("The name of student %d is %s\n",con++,((test+(con))->name));
	}
}



/*************************************************
Function: Generate_Student_ID
Description: Generate Student's ID for every student
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Generate_Student_ID(struct student* test)
{
	int con = 0;
	while(con < NUM_OF_STUDENT)
	{
		((test+(con))->stuid) = con + 1;
		con ++;
	}
}



/*************************************************
Function: Show_Student_ID
Description: Display ID of every student
Input: Structure pointer of student *test
Output: Every student's ID
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Show_Student_ID(struct student *test)
{
    int con = 0;
    while(con < NUM_OF_STUDENT)
    {
        printf("The ID of student %d is %d\n",con++,((test+(con))->stuid));
    }
}



/*************************************************
Function: Sorted_Student_By_Mark
Description: Sorted Student Srtuct by student's Marks
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/27
*************************************************/
void Sorted_Student_By_Mark(struct student *test)
{
	struct student *p = test;
	int con = 0;
	int current;
	// Begin to sort by mark
	for(con=0; con<NUM_OF_STUDENT-1; con++)
	{
		for(current=0; current<NUM_OF_STUDENT-1-con; current++)
		{
			if(((p+(current))->total) < ((p+(current+1))->total))
			{
				struct student temp = *(p+(current));
				*(p+(current)) = *(p+(current+1));
				*(p+(current+1)) = temp;
			}
		}
	}	// End of sort by mark	
}



/*************************************************
Function: Sorted_Student_By_StuID
Description: Sorted Student Srtuct by student's ID
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/27
*************************************************/
void Sorted_Student_By_StuID(struct student *test)
{
    struct student *p = test;
    int con = 0;
    int current;
    // Begin to sort by StuID
    for(con=0; con<NUM_OF_STUDENT-1; con++)
    {
        for(current=0; current<NUM_OF_STUDENT-1-con; current++)
        {
            if(((p+(current))->stuid) > ((p+(current+1))->stuid))
            {
                struct student temp = *(p+(current));
                *(p+(current)) = *(p+(current+1));
                *(p+(current+1)) = temp;
            }
        }
    }   // End of sort by mark  	
}



/*************************************************
Function: Count_Rank
Description: Calculate the ranking of every student
Input: Structure pointer of student *test
Output: None
Return: Struct student pointer which sorted by mark.
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
struct student* Count_Rank(struct student *test)
{
	int con = 0;

	// The following part is equal to function "Sorted_Student_By_Matk".
/*	struct student *p = test;
	int con = 0;
	int current;
	// Begin to sort by mark
	for(con=0; con<NUM_OF_STUDENT-1; con++)
	{
		for(current=0; current<NUM_OF_STUDENT-1-con; current++)
		{
			if(((p+(current))->total) < ((p+(current+1))->total))
			{
				struct student temp = *(p+(current));
				*(p+(current)) = *(p+(current+1));
				*(p+(current+1)) = temp;
			}
		}
	}	// End of sort by mark
*/
	Sorted_Student_By_Mark(test);
	// Begin to Tag rank number
	for(con=0; con<NUM_OF_STUDENT; con++)
	{
		((test+(con))->rank) = con + 1;
	}	// End of tag
	Sorted_Student_By_StuID(test);

	// The following part is equal to function "Sorted_Student_By_StuID".
/*	// Begin to Recovery structure data
	for(con=0; con<NUM_OF_STUDENT-1; con++)
    {
        for(current=0; current<NUM_OF_STUDENT-1-con; current++)
        {
            if(((p+(current))->stuid) > ((p+(current+1))->stuid))
            {
                struct student temp = *(p+(current));
                *(p+(current)) = *(p+(current+1));
                *(p+(current+1)) = temp;
            }
        }
    }   // End of sort by stuid
*/
	return test;
}



/*************************************************
Function: Show_Student_Rank
Description: Display the ranking of every student
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Show_Student_Rank(struct student* test)
{
	int con = 0;
	while(con < NUM_OF_STUDENT)
	{
		printf("The rank of student %d is %d\n", con++, (test+(con))->rank);
	}
}



/*************************************************
Function: Show_All_Data
Description: Display All data of every student
Input: Structure pointer of student *test
Output: None
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Show_All_Data(struct student *test)
{
	int con = 0;
	int current;
	printf("\nStuID\tName\t\tMarks\t\tTotal\tAverage\tRank\n");
	while(con < NUM_OF_STUDENT)
	{
		printf("%d\t%s\t",(test+(con))->stuid, (test+(con))->name);		// Display StudentID and Name
		for(current=0; current<NUM_OF_MARK; current++)
		{
			printf("%d ",*((test+(con))->mark+(current)));				// Display marks
		}
		printf("\t%d\t%.2lf\t%d\n", (test+(con))->total, (test+(con))->avg, (test+(con))->rank);		// Display Total Average and Ranking.
		con ++;		// for next student
	}
	printf("\n");	// Split display
}



/*************************************************
Function: Show_Data_Sorted_By_Mark
Description: Show All Data which have sorted by Mark
Input: Structure pointer of student *test
Output: All Data sorted by mark
Return: None
Author: ZhangH.J.
Date: 2019/10/26
*************************************************/
void Show_Data_Sorted_By_Mark(struct student *test)
{
/*	int con = 0;
	int current;
	struct student *p = test;
	for(con=0; con<NUM_OF_STUDENT-1; con++)
	{
		for(current=0; current<NUM_OF_STUDENT-1-con; current++)
		{
			if(((p+(current))->total) < ((p+(current+1))->total))
			{
				struct student temp = *(p+(current));
				*(p+(current)) = *(p+(current+1));
				*(p+(current+1)) = temp;
			}
		}
	}   // End of sort by mark
*/	// Begin to print

	// The above code is equal to function "Sorted_Student_By_Mark".
	Sorted_Student_By_Mark(test);
	Show_All_Data(test);
	Sorted_Student_By_StuID(test);
}



/*************************************************
Function: Write_Data_to_File
Description: Write All Student's Data to File,and append local time.
Input: Structure pointer of student *test; The File Name of StudentData
Output: The File Called "FileName".
Return: None
Author: ZhangH.J.
Date: 2019/10/27
*************************************************/
void Write_Data_to_File(struct student *test, char* FileName)
{
    FILE *fp;
    if((fp=fopen(FileName,"a+"))==NULL)
    {
        printf("File cannot be opened\n");
        exit(0);
    }
    else
    {
        //printf("File opened for writing\n");
        //fprintf(fp, "This is testing for fprintf...\n");
        //fputs("This is testing for fputs...\n", fp);
        int con = 0;
        int current;
        fprintf(fp,"\nStuID\tName\t\tMarks\t\t\tTotal\tAverage\tRank\n");
        while(con < NUM_OF_STUDENT)
        {
            fprintf(fp,"%d\t\t%s\t",(test+(con))->stuid, (test+(con))->name);     // Display StudentID and Name

            for(current=0; current<NUM_OF_MARK; current++)
            {
                fprintf(fp,"%d ",*((test+(con))->mark+(current)));              // Display marks
            }
            fprintf(fp,"\t%d\t\t%.2lf\t%d\n", (test+(con))->total, (test+(con))->avg, (test+(con))->rank);        // Display Total Average and Ranking.
            con ++;     // for next student
        }
        fprintf(fp,"\n");   // Split display

		// The following part used to get local and write time to DataFile
		time_t tmpcal_ptr;
		struct tm *tmp_ptr = NULL;
		time(&tmpcal_ptr);
		//printf("tmpcal_ptr=%ld\n", tmpcal_ptr);
		tmp_ptr = localtime(&tmpcal_ptr);
		fprintf (fp,"The latest Record added in:%d.%d.%d ", (1900+tmp_ptr->tm_year), (1+tmp_ptr->tm_mon), tmp_ptr->tm_mday);
		fprintf(fp,"%d:%d:%d\n\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
	}
    fclose(fp);
    printf("Written to file completion (^o^)!\n\n");
}

