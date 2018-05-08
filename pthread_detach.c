#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
//默认情况下，新创建的线程是joinable（可结合）的，线程退出后，需要对其进行pthread_join操作，否则无法释放资源，从而造成系统泄漏。
//如果不关心线程的返回值，join是一种负担，这个时候，我们可以告诉系统，当线程退出时，自动释放线程资源。
void *thread1(void *arg){
    //分离线程，
    //pthread_detach（pthread_t thread ） 可以是线程组内其他线程对目的线程进行分离，也可以是线程自己分离
    pthread_detach(pthread_self());
    printf("%s\n",(char*)arg);
    return NULL;
}
int main(void){
    pthread_t tid;
    //创建线程
    if(pthread_create(&tid,NULL,thread1,"thread1 run...\n")!= 0){
        printf("create thread1 error\n");
        return 1;
    }
    int ret = 0;
//    sleep(1);
    if(pthread_join(tid,NULL)==0){
        printf("pthead wait success\n");
        ret = 0;
    }else{
        printf("pthread wait failed\n");
        ret = 1;
    }
    return ret;
}
