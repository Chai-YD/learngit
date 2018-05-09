#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//条件变量
//当一个进程互斥的访问某个变量时，它可能发现在其他线程改变状态之前，它什么也做不了。
//例如一个线程访问队列时，发现队列为空，它只能等待，直到其他线程有一个结点添加到队列中。
//这种情况就需要用到条件变量

//创建互斥量
pthread_mutex_t mutex;
//创建条件变量
pthread_cond_t cond;

void* thread1(void* arg){
    while(1){
        pthread_cond_wait(&cond,&mutex);
        printf("你好\n");
    }
}
void* thread2(void *arg){
    while(1){
        pthread_cond_signal(&cond);
        sleep(1);
    }
}
int main(void){
    //初始化
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_t t1,t2;
    //创建线程
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);
    //等待线程，防止系统资源泄漏
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}
