#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int openshm(int size){
    int shmid;
    if((shmid = shmget(IPC_PRIVATE, size, 0)) == -1){
        PRINTF("Get shared memory failed!\n");
        return -1;
    }
    return shmid;
}