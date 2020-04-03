//
// Created by kaihua on 4/1/20.
//

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *thread_function1(void *arg);

sem_t bin_sem;


#define  WORK_SIZE 1024
char work_area[WORK_SIZE];

void test_thread_sem() {
    //初始化信号量
    if (sem_init(&bin_sem, 0, 0) != 0) {
        perror("Semaphore initialization failed.\n");
        exit(EXIT_FAILURE);
    }

    //创建线程
    pthread_t a_thread;
    if (pthread_create(&a_thread, NULL, thread_function1, NULL) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    //输入数据,输入end结束===>读入数据时，发送信号量
    printf("Input some text,Enter 'end' to finish\n");
    while (strncmp("end", work_area, 3) != 0) {
        fgets(work_area, WORK_SIZE, stdin);
        sem_post(&bin_sem);
    }

    //子线程读到 'end'　时会退出，这里等待子线程結
    void *thread_result = NULL;
    printf("\nWaiting for thread to finish...\n");
    if (pthread_join(a_thread, &thread_result) != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    //子线程已经结束打印提示
    printf("thread joined.\n");
    sem_destroy(&bin_sem);
    exit(EXIT_SUCCESS);
}


//线程＝＝接收数据并退出
void *thread_function1(void *arg)
{
    sem_wait(&bin_sem);//等待输入信号量
    while (strncmp("end",work_area,3) !=0){
        printf("You input %d characters\n",strlen((work_area))-1);
        sem_wait(&bin_sem);
    }
    //接收到end退出
    pthread_exit(NULL);
}