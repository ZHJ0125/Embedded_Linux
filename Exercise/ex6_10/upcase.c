#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    int i;
    char buffer[BUFSIZ+1];
    
    fgets(buffer, BUFSIZ, stdin);
    for(i=0; i<strlen(buffer); i++){
        buffer[i] = toupper(buffer[i]);
    }
    printf("%s\n", buffer);
    return 0;
}