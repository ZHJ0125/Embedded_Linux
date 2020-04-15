#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    mqd_t mqID;
    struct mq_attr mqAttr;
    if(mqID = mq_open("testmQueue", O_RDWR | O_CREAT | 0666, NULL) == -1){
        printf("Error!\n");
        exit(1);
    }
    if (mq_getattr(mqID, &mqAttr) < 0){
        printf("get the message queue attribute error\n");
        return -1;
    }
    printf("mq_flags: %ld\n", mqAttr.mq_flags);
    printf("mq_maxmsg: %ld\n", mqAttr.mq_maxmsg);
    printf("mq_msgsize: %ld\n", mqAttr.mq_msgsize);
    printf("mq_curmsgs: %ld\n", mqAttr.mq_curmsgs);

    return 0;
}