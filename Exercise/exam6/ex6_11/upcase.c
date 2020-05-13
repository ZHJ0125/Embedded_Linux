#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int i;
    char buffer[BUFSIZ+1];

    while(fgets(buffer, BUFSIZ, stdin) != NULL)
    for(i=0; i<strlen(buffer); i++){
        buffer[i] = toupper(buffer[i]);
        printf("%c", buffer[i]);
    }
    printf("\n");
    return 0;
}