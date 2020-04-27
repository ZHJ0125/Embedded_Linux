#include "myshm.h"

int main(){
    int shmid;
    char *shm, *s;
    int producer, consumer, i;
    char readbuf[SHMSZ];
    int fd_consumer, fd_producer, fd_shared;

    // 创建相关的文件
    fd_consumer = open(CONSUMER, O_RDONLY|O_CREAT, 0660);
    fd_producer = open(PRODUCER, O_RDONLY|O_CREAT, 0660);
    fd_shared = open(SHARED, O_RDONLY|O_CREAT, 0660);
    close(fd_consumer);
    close(fd_producer);
    close(fd_shared);

    if((consumer = semget(ftok("consumer", 0), 1, IPC_CREAT|0660)) == -1){
        printf("call semget() failed!\n");
        exit(1);
    }
    init_a_semaphore(consumer, 0, 0);
    if((producer = semget(ftok("producer", 0), 1, IPC_CREAT|0660)) == -1){
        printf("call semget() failed!\n");
        exit(1);
    }
    init_a_semaphore(producer, 0, 0);
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
        sprintf(shm, "%s -> Message %d from producer %d", readbuf, i, getpid());
        semaphore_V(producer);
        if(strncmp(readbuf, "end", 3) == 0){
            break;
        }
    }

    // 移除文件
    remove(CONSUMER);
    remove(PRODUCER);
    remove(SHARED);

    return 0;
}