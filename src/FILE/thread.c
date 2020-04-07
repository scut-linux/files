//
// Created by kaihua on 3/31/20.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

char message[] = "Hello world";

//线程函数　
void *thread_function(void *arg) {
    //使能取消
    if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) != 0) {
        perror("thread pthread_setcancelstate failed.\n");
        exit(EXIT_FAILURE);
    }
    //设置取消方式
    //DEFERRED : 推迟,直到 pthread_join,pthread_cond_wait,pthread_cond_timewait,pthread_testcancel sem_wait or sigwait
    //PTHREAD_CANCEL_ASYNCHRONOUS :立即执行
    if (pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL) != 0) {
        perror("thread thread_setcanceltype failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("thread_function is running .Argument was %s\n", (char *) arg);
    for (int i = 0; i < 10; ++i) {
        printf("thread_function is still running.\n");
        sleep(1);
    }
    //strcpy(message, "Byte");
    //pthread_exit("Thank you for the CPU time");
    pthread_exit(0);
}

//测试
void test_thread() {
    pthread_t a_pthread;
    void *thread_result;

    //创建线程
    if (pthread_create(&a_pthread, NULL, thread_function, (void *) message) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    //取消线程
    sleep(1);
    printf("Canceling ...\n");
    if(pthread_cancel(a_pthread)!=0){
        perror("Thead cancelation failed.\n");
        printf("FAIL\n");
        exit(EXIT_FAILURE);
    }

    //等待线程完成
    printf("waiting ......");
    if (pthread_join(a_pthread, &thread_result) != 0) {
        perror("thread join failed");
        exit(EXIT_FAILURE);
    }

    //打印返回结果
    //printf("Thread joined. it returned =%s\n", (char *) thread_result);
    //printf("Message is now=%s\n", message);
    exit(EXIT_SUCCESS);
}