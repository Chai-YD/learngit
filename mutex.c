#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//互斥量
pthread_mutex_t mutex;
int ticket = 100;
void *thread(void * arg){
    //上锁
    //如果把锁上在这里，对于临界变量还会出现错误
    char* id = (char *)arg;
    while(1){
        pthread_mutex_lock(&mutex);
        if(ticket>0){
            usleep(1000);
            printf("%s sells ticket:%d\n",id,ticket);
            ticket--;
            //解锁
            pthread_mutex_unlock(&mutex);
        }else{
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
}

int main(){
    //初始化
    pthread_mutex_init(&mutex,NULL);
    pthread_t t1,t2,t3,t4;
    pthread_create(&t1,NULL,thread,"thread 1");
    pthread_create(&t2,NULL,thread,"thread 2");
    pthread_create(&t3,NULL,thread,"thread 3");
    pthread_create(&t4,NULL,thread,"thread 4");


    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    //销毁
    pthread_mutex_destroy(&mutex);
}
