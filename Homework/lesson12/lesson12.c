#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

pthread_mutex_t chopsticks[6];
void *et(void *arg);

int main()
{
    pthread_t A,B,C,D,E;
    //初始化五把锁
    for(int i = 1;i < 6;i++)
    {
        pthread_mutex_init(&chopsticks[i],NULL);
    }
    //创建五个进程
    pthread_create(&A,NULL,et,"A");
    pthread_create(&B,NULL,et,"B");
    pthread_create(&C,NULL,et,"C");
    pthread_create(&D,NULL,et,"D");
    pthread_create(&E,NULL,et,"E");
 
    pthread_join(A,NULL);
    pthread_join(B,NULL);
    pthread_join(C,NULL);
    pthread_join(D,NULL);
    pthread_join(E,NULL);

    return 0;
}

void *et(void *arg)
{
    char phi = *(char *)arg;
    int left,right;
    switch (phi)
    {
        case 'A':
        left = 1;
        right = 5;
        break;
        case 'B':
        left = 2;
        right = 1;
        break;
        case 'C':
        left = 3;
        right = 2;
        break;
         case 'D':
        left = 4;
        right = 3;
        break;
         case 'E':
        left = 5;
        right = 4;
        break;
    }
 
    while(1)
    {
        //思考
        sleep(3);
        pthread_mutex_lock(&chopsticks[left]);
        printf("Philosopher %c pick up chopsitick %d.\n",phi,left);
        int ret = pthread_mutex_trylock(&chopsticks[right]);
        if(ret != 0)
        {
            pthread_mutex_unlock(&chopsticks[left]);
            continue;
        }
        //拿到筷子
        printf("Philosopher %c pick up chopsitick %d.\n",phi,right);
        //吃饭
        printf("Philosopher %c eating.\n",phi);
        //吃饭时间
        sleep(3);
        pthread_mutex_unlock(&chopsticks[left]);
        printf("Philosopher %c lay down chopstick %d.\n",phi,left);
        pthread_mutex_unlock(&chopsticks[right]);
        printf("Philosopher %c lay down chopstick %d.\n",phi,right);
    }
}
