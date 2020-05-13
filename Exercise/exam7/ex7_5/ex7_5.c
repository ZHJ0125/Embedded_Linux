#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 4
#define OVER (-1)

struct producers{
    int buffer[BUFFER_SIZE];
    int readpos, writepos;
    sem_t sem_read;
    sem_t sem_write;
};

void init(struct producers *b){
    // 初始化信号量集，为当前进程的所有线程所共享
    sem_init(&b->sem_write, 0, BUFFER_SIZE-1);  // sem_write信号量的初值为BUFFER_SIZE-1
    sem_init(&b->sem_read, 0, 0);
    b->readpos = 0;
    b->writepos = 0;
}

void put(struct producers *b, int data){
    sem_wait(&b->sem_write);    // sem_wait函数是将信号量的值减 1，相当于SystemV机制下的 P 操作
    b->buffer[b->writepos] = data;
    b->writepos++;
    if(b->writepos >= BUFFER_SIZE){
        b->writepos = 0;
    }
    sem_post(&b->sem_read);     // sem_read函数是将信号量的值加 1，相当于SystemV机制下的 V 操作
}

int get(struct producers *b){
    int data;
    sem_wait(&b->sem_read);
    data = b->buffer[b->readpos];
    b->readpos++;
    if(b->readpos >= BUFFER_SIZE){
        b->readpos = 0;
    }
    sem_post(&b->sem_write);
    return data;
}

struct producers buffer;

void *producer(void *data){
    int n;
    for(n=0; n<10; n++){
        printf("Process: %d->\n", n);
        put(&buffer, n);
    }
    put(&buffer, OVER);
    return NULL;
}

void *consumer(void *data){
    int d;
    while(1){
        d = get(&buffer);
        if(d == OVER){
            break;
        }
        printf("Consumer: -> %d\n", d);
    }
    return NULL;
}

int main(){
    pthread_t tha, thb;
    void *retval;
    init(&buffer);
    pthread_create(&tha, NULL, producer, 0);
    pthread_create(&thb, NULL, consumer, 0);
    pthread_join(tha, &retval);
    pthread_join(thb, &retval);
    return 0;
}
