#include "myshm.h"

int main(){
    char *shm;
    int shmid;
    int producer, consumer;
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
    while(1){
        semaphore_V(consumer);
        semaphore_P(producer);
        printf("Data recived: %s\n", shm);
        sleep(1);
        if(strcmp(shm, "end") == 0){
            break;
        }
    }
    // 删除两个信号量集
    semctl(producer, 0, IPC_RMID, 0);
    semctl(consumer, 0, IPC_RMID, 0);

    return 0;
}