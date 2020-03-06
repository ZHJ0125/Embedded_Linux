#include <stdio.h>
#include <ctype.h>

void main(){
	char origin[100];
	char* string;
	while(1){
		// Enter origin from keyboard
		fgets(origin, 100, stdin);
		string = origin;
		// Start conversion
		while(*string != '\0'){
			// Conversion over with '#'
			if(*string == '#'){
				*(string+1) = '\0';
				printf("%s\n", origin);
				return;
			}
			// Convert to uppercase letters
			*string = toupper(*string);
			string++;
		}
		// Output result
		printf("%s", origin);
	}
}
