#include <stdio.h>
#define BEGIN 1

int main(){
	int c,characters,lines,words,state;
	state = 0;
	// Initialize the data
	characters = lines = words = 0;
	// Read data from stdin
	while((c = getchar()) != '0'){
		characters++;
		switch(c){
			case '\n':
				// New line
				lines ++;
			case ' ':
			case '\t':
				// New word
				state = 0;
				break;
			default:
				// Same letter
				if(state == 0){
					state = BEGIN;
					words ++;
				}
				break;
		}
	}
	// Output statistics
	printf("There is %d characters, %d words, %d lines.\n",characters,words,lines);
	return 0;
}
