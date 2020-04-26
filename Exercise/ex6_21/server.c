#include "myshm.h"

int main(){
    int shmid;
    char *shm, *s;
    int producer, consumer, i;
    char readbuf[SHMSZ];

    if((consumer = semget(ftok("consumer", 0), 1, IPC_CREAT|0660)) == -1){
        printf("call semget() failed!\n");
        exit(1);
    }
    init_a_semaphore(consumer, 0, 1);
    if((producer = semget(ftok("producer", 0), 1, IPC_CREAT|0660)) == -1){
        printf("call semget() failed!\n");
        exit(1);
    }
    init_a_semaphore(producer, 0, 1);
    if((shmid = shmget(ftok("shared", 0), SHMSZ, IPC_CREAT|0660)) == -1){
        printf("call shmget() failed!\n");
        exit(1);
    }
    if((shm = shmat(shmid, (unsigned char*)0, 0)) < 0){
        printf("call shmat() failed!\n");
        exit(1);
    }
    for(i=0;;i++){
        printf("Enter text: ");
        // fgets(readbuf, SHMSZ, stdin);
        scanf("%s", readbuf);
        getchar();
        semaphore_P(consumer);
        sprintf(shm, "%s -> Message %d from producer %d\n", readbuf, i, getpid());
        semaphore_V(producer);
        if(strcmp(readbuf, "end") == 0){
            break;
        }
    }

    return 0;
}