//int pthread_join(pthread_t tid ,void** value_ptr);
//tid:线程ID
//value_ptr:它指向一个指针，后者指向线程的返回值
//等待进程的返回值：成功返回0；失败返回错误码
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdlib.h>
#include<unistd.h>
void* thread1(void * arg){
    printf("thread 1 returning..\n");
    int *p = (int*)malloc(sizeof(int));
    *p = 1;
    return (void *)p;
}

void* thread2(void * arg){
    printf("thread 2 returning..\n");
    int *p = (int*)malloc(sizeof(int));
    *p = 2;
    //线程终止自己的函数
    pthread_exit((void *)p);
}

void* thread3(void* arg){
    while(1){
        printf("thread 3 is running...\n");
        sleep(1);
    }
    return NULL;
}
int main(){
    //创建线程
    pthread_t tid;
    void * ret;
    //thread 1 return
    pthread_create(&tid,NULL,thread1,NULL);
    pthread_join(tid,&ret);
    printf("thread return ,thread id %x,return code:%d\n",tid,*(int *)ret);
    free(ret);

    //thread 2 return
    pthread_create(&tid,NULL,thread2,NULL);
    pthread_join(tid,&ret);
    printf("thread return ,thread id %x,return code:%d\n",tid,*(int *)ret);
    free(ret);

    //thread 3 cancel by other
    pthread_create(&tid,NULL,thread3,NULL);
    sleep(3);
    pthread_cancel(tid);
    pthread_join(tid,&ret);
    if(ret == PTHREAD_CANCELED){
        printf("thread return ,thread id %x,return code:PTHREAD_CANCELED\n",tid);
    }else{
        printf("thread return ,thread id %x,return code:NULL\n",tid);
    }
    free(ret);
}
