


//POSIX信号量和System信号量作用相同，都是用于同步操作，达到无冲突的访问共享资源目的。
//但POSIX可用于线程间同步
//#include<semaphore.h>
//int sem_init(sem_t sem ,int pshared ,unsigned int value);
//参数：
//    pshared ：0表示线程间通信，非零表示进程间通信
//    value ：信号量初始值
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>


//定义信号量
#define CONSUMER_COUNT 1
#define PRODUCTER_COUNT 1
#define BUFFER_SIZE 5
//空间大小
int buffer[BUFFER_SIZE];

//定义全局变量
unsigned short in = 0;//入数组
unsigned short out = 0;//出数组
//产品值
unsigned short produce_id = 0;
unsigned short consume_id = 0;
//定义信号量，互斥量
sem_t sem_data;
sem_t sem_black;
pthread_mutex_t g_mutex;
pthread_t thread[PRODUCTER_COUNT+CONSUMER_COUNT];

void *consume(void* arg){
    while(1){
        printf("%d wait buffer not empty\n",(int *)arg);
        sem_wait(&sem_data);
        pthread_mutex_lock(&g_mutex);
        int i =0;
        for(;i<BUFFER_SIZE;i++){
            printf("%2d ",i);
            if(thread[i]==-1){
                printf("%s","NULL");
            }else{
                printf("%d",buffer[i]);
            }
            printf("\n");
        }
        consume_id = buffer[out];
        printf("%d begin consume product %d\n",(int*)arg ,consume_id);
        buffer[out]= -1;
        out = (out+1)%BUFFER_SIZE;
        printf("%d end consume product %d\n",(int *)arg ,consume_id);
        pthread_mutex_unlock(&g_mutex);
        sem_post(&sem_black);
        sleep(1);
    }
    return NULL;
}

void *produce(void *arg ){
    while(1){
        printf("%d wait buffer not full\n",(void*)arg);
        sem_wait(&sem_black);
        pthread_mutex_lock(&g_mutex);
        int i = 0;
        for(;i<BUFFER_SIZE;i++){
            printf("%2d ",i);
            if(buffer[i]==-1){
                printf("%s","NULL");
            }else{
                printf("%d",buffer[i]);
            }
            if(i == in){
                printf("\t<--produce");
            }
            printf("\n");
        }
        printf("%d begin produce product %d\n",(void*)arg,produce_id);
        buffer[in] = produce_id;
        in = (in+1)%BUFFER_SIZE;
        printf("%d end produce product %d\n",(void*)arg,produce_id++);
        pthread_mutex_unlock(&g_mutex);
        sem_post(&sem_data);
        sleep(5);
    }
return NULL;
}
int main(){
    //初始化信号量
    sem_init(&sem_data,0,0);
    sem_init(&sem_black,0,BUFFER_SIZE);
    int i = 0;
    //创建消费者线程
    for(;i<CONSUMER_COUNT;i++){
        pthread_create(&thread[i],NULL,consume,(void*)i);
    }
    //创建生产者线程
    for(i=0;i<PRODUCTER_COUNT;i++){
        pthread_create(&thread[CONSUMER_COUNT+i],NULL,produce ,(void* )i);
    }
    //线程等待
    for(i=0;i<CONSUMER_COUNT+PRODUCTER_COUNT;i++){
        pthread_join(thread[i],NULL);
    }
    sem_destroy(&sem_data);
    sem_destroy(&sem_black);
    pthread_mutex_destroy(&g_mutex);
    return 0;
}
