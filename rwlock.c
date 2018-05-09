#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
//读写锁
//注意：写独占，读共享，写锁优先级高
//读写锁本质上是一种自旋锁（长时间等人与短时间等人的例子）

#define READ_COUNT 5
#define WRITE_COUNT 3
int counter = 0;
//定义读写锁
pthread_rwlock_t rwlock;

void* read_tid(void* arg){
    while(1){
        pthread_rwlock_rdlock(&rwlock);
        printf("read:%d :%#x:counter = %d\n",(int *)arg,pthread_self(),counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(900);
    }
}

void* write_tid(void* arg){
    while(1){
        int t = counter;
        //usleep(1000);
        pthread_rwlock_wrlock(&rwlock);
        printf("write:%d:%#x:counter=%d:++counter=%d\n ",(int *)arg ,pthread_self(),t,++counter);
        pthread_rwlock_unlock(&rwlock);
        usleep(5000);
    }
}

int main(void){
    pthread_rwlock_init(&rwlock,NULL);
    int i =0;
    pthread_t tid[8];
    //创建读线程
    for(;i<READ_COUNT;i++){
        pthread_create(&tid[i],NULL,read_tid ,(void*)i);
    }
    //创建写线程
    for(i = 0;i<WRITE_COUNT;i++){
        pthread_create(&tid[i+READ_COUNT],NULL,write_tid,(void*)i);
    }
    //等待线程
    for(i=0;i<READ_COUNT+WRITE_COUNT;i++){
        pthread_join(tid[i],NULL);
    }
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
