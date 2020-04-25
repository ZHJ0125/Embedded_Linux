#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    int shmid;
    char c;
    char *shmptr, *s;
    if((shmid = shmget(12345, 256, IPC_CREAT|0666)) < 0){
        printf("call shmget() failed!\n");
        exit(1);
    }
    if((shmptr = shmat(shmid, 0, 0)) < 0){
        shmctl(shmid, IPC_RMID, NULL);
        printf("call shmat() failed!\n");
        exit(2);
    }
    s = shmptr;
    for(c='a'; c<='z'; c++){
        *s = c;
        s++;
    }
    *s = '\n';
    while(*shmptr != '*');
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}