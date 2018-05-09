#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdlib.h>
#include<unistd.h>

#define CONSUMERS_COUNT 2
#define PRODUCERS_COUNT 2
//定义条件变量与互斥量
pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t thread[CONSUMERS_COUNT+PRODUCERS_COUNT];
//临界资源
struct msg{
    struct msg* next;
    int num;
};
//创建头结点
struct msg* head = NULL;
//消费函数
void* consumer(void *arg){
    struct msg *mp;
    for(;;){
        //加锁
        pthread_mutex_lock(&mutex);
        while(head==NULL){
            printf("%d begin wait a condition...\n",(int *)arg);
            //等待
            pthread_cond_wait(&cond,&mutex);
        }
        printf("%d end wait a condition...\n",(int *)arg);
        printf("%d begin consume product...\n",(int*)arg);
        mp= head;
        head = mp->next;
        //释放锁
        pthread_mutex_unlock(&mutex);
        printf("consume %d\n",mp->num);
        free(mp);
        printf("%d end consume product ...\n",(int*)arg);
        sleep(rand()%5);
    }
}
//生产函数
void* producer(void* arg){
    struct msg *mp;
    for(;;){
        printf("%d begin produce product...\n",(int *)arg);
        mp = (struct msg*)malloc(sizeof(struct msg));
        mp->num = rand()%100+1;
        printf("produce %d\n",mp->num);
        //加锁
        pthread_mutex_lock(&mutex);
        mp->next = head;
        head = mp;
        printf("%d end produce product...\n",(void*)arg);
        //唤醒
        pthread_cond_signal(&cond);
        //释放锁 
        pthread_mutex_unlock(&mutex);
        sleep(rand()%5);
    }
}
int main(void){
    //初始化
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    int i = 0;
    srand((unsigned int)time(NULL));
    //创建消费者线程
    for(;i<CONSUMERS_COUNT;i++){
        pthread_create(&thread[i],NULL,consumer ,(void*)i);
    }
    //创建生产者线程
    for(i=0;i<PRODUCERS_COUNT;i++){
        pthread_create(&thread[i],NULL,producer,(void*)i);
    }
    //等待线程
    for(i=0;i<CONSUMERS_COUNT+PRODUCERS_COUNT;i++){
        pthread_join(thread[i],NULL);
    }
    //销毁
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
