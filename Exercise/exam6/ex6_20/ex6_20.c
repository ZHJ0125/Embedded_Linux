#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

char array[4000];

int main(){
    int shmid;
    char *ptr, *shmptr;
    printf("array[] from %x to %x\n", &array[0], &array[3999]);
    printf("stack around %x\n", &shmid);
    if((ptr = malloc(10000)) == NULL){
        printf("call malloc() failed!\n");
        exit(1);
    }
    if((shmid = shmget(IPC_PRIVATE, 10000, SHM_R|SHM_W)) < 0){
        printf("call smget() failed!\n");
        exit(2);
    }
    if((shmptr = shmat(shmid, 0, 0)) < 0){
        printf("call shmat() failed!\n");
        exit(3);
    }
    printf("shared memory attached from %x to %x\n", shmptr, shmptr-10000);
    if(shmctl(shmid, IPC_RMID, 0) < 0){
        printf("call shmctl() failed!\n");
        exit(4);
    }
    return 0;
}