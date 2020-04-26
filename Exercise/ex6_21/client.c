#include "myshm.h"

int main(){
    char *shm;
    int shmid;
    int producer, consumer;
    if((consumer = semget(ftok("consumer", 0), 1, IPC_CREAT|0660)) == -1){
        printf("call semget() failed!\n");
        exit(1);
    }
    // init_a_semaphore(consumer, 0, 1);
    if((producer = semget(ftok("producer", 0), 1, IPC_CREAT|0660)) == -1){
        printf("call semget() failed!\n");
        exit(1);
    }
    // init_a_semaphore(producer, 0, 1);
    if((shmid = shmget(ftok("shared", 0), SHMSZ, IPC_CREAT|0660)) == -1){
        printf("call shmget() failed!\n");
        exit(1);
    }
    if((shm = shmat(shmid, (unsigned char*)0, 0)) < 0){
        printf("call shmat() failed!\n");
        exit(1);
    }
    while(1){
        semaphore_V(consumer);
        semaphore_P(producer);
        printf("Data recived: %s", shm);
        fflush(stdout);
        sleep(1);
        if(strncmp(shm, "end", 3) == 0){
            break;
        }
    }
    semctl(producer, 0, IPC_RMID, 0);
    semctl(consumer, 0, IPC_RMID, 0);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}