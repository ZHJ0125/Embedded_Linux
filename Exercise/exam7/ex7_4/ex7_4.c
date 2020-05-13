#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define BUFFER_SIZE 4
#define OVER (-1)
// struct producers buffer;

// 生产者条件变量结构体
struct producers{
    int buffer[BUFFER_SIZE];            // 定义缓冲区
    pthread_mutex_t lock;               // 定义访问缓冲区的互斥锁
    int readpos, writepos;              // 读写位置
    pthread_cond_t notempty;            // 缓冲区有数据时的标记
    pthread_cond_t notfull;             // 缓冲区未满时的标记
} buffer;

// 初始化缓冲区
void init(struct producers *b){
    pthread_mutex_init(&b->lock, NULL);         // 初始化互斥锁
    pthread_cond_init(&b->notempty, NULL);      // 初始化条件变量
    pthread_cond_init(&b->notfull, NULL);
    b->readpos = 0;
    b->writepos = 0;
}

// 在缓冲区中存放一个整数
void put(struct producers *b, int data){
    // printf("This is put()\n");
    // 锁定生产者的互斥锁
    pthread_mutex_lock(&b->lock);
    // 缓冲区满时等待
    while((b->writepos+1)%BUFFER_SIZE == b->readpos){
        pthread_cond_wait(&b->notfull, &b->lock);
    }
    // 向缓冲区中写入数据
    b->buffer[b->writepos] = data;
    b->writepos++;
    if((b->writepos) >= BUFFER_SIZE){
        b->writepos = 0;
    }
    // 解除notempey阻塞状态，解锁互斥锁
    pthread_cond_signal(&b->notempty);
    pthread_mutex_unlock(&b->lock);
    // usleep(1000);
    
    // printf("pthread_cond_signal notempty return: %d\n", pthread_cond_signal(&b->notempty));
    
}

// 从缓冲区中读取数据，并将数据从缓冲区中移走
int get(struct producers *b){
    int data;
    // 锁定互斥锁
    pthread_mutex_lock(&b->lock);
    // printf("This is get()\n");
    // 当缓冲区中有数据时，等待
    while(b->writepos == b->readpos){
        pthread_cond_wait(&b->notempty, &b->lock);
    }
    // 读取缓冲区数据
    data = b->buffer[b->readpos];
    b->readpos++;
    if(b->readpos >= BUFFER_SIZE){
        b->readpos = 0;
    }
    // 发送缓冲区未满信号，解锁互斥锁
    pthread_cond_signal(&b->notfull);
    pthread_mutex_unlock(&b->lock);
    // usleep(1000);

    // printf("pthread_cond_signal notfull return: %d\n", pthread_cond_signal(&b->notfull));
    
    // 返回读取到的数据
    return data;
}

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