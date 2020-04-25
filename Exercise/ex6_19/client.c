#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int shmid;
    char c;
    char *shmptr, *s;
    if((shmid = shmget(12345, 256, 0666)) < 0){
        printf("call shmget() failed!\n");
        exit(1);
    }
    if((shmptr = shmat(shmid, 0, 0)) < 0){
        shmctl(shmid, IPC_RMID, NULL);
        printf("call shmat() failed!\n");
        exit(2);
    }
    for(s=shmptr; *s!='\n'; s++){
        putchar(*s);
    }
    printf("\n");
    *shmptr = '*';
    return 0;
}