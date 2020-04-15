#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
    key_t key;
    int msqid;

    printf("Enter the desired key in hex = ");
    scanf("%x", &key);

    printf("\nKey = 0x%x\n", key);
    if((msqid = msgget(key, IPC_CREAT|0660)) == -1){
        printf("The msgget failed.\n");
        exit(1);
    }
    printf("The msgget succeed: msqid = %d\n", msqid);
    exit(0);
}