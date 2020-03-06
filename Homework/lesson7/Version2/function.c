#include <stdio.h>
#include <ctype.h>

int main(int argc, char* argv[]){
	char* string;
	// Check parameters
	if(argc != 2){
		printf("Usage: %s [String-To-Be-Converted]\n", argv[0]);
		return -1;
	}
	string = argv[1];
	// Start conversion
	while(*string != '\0'){
		// Convert to uppercase letters
		*string = toupper(*string);
		string++;
	}
	// Output result
	printf("%s\n", argv[1]);
	return 0;
}
