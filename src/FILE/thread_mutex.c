//
// Created by kaihua on 4/1/20.
//

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *thread_function2(void *arg);

pthread_mutex_t mutex; //互斥量


#define  WORK_SIZE 1024
char work_area[WORK_SIZE];
int time_to_exit = 0;

void test_thread_mutex() {
    //初始化互斥量
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed.\n");
        exit(EXIT_FAILURE);
    }

    //创建线程
    pthread_t a_thread;
    if (pthread_create(&a_thread, NULL, thread_function2, NULL) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    //输入数据,输入end结束===>读入数据时，发送信号量
    pthread_mutex_lock(&mutex); //上锁
    printf("Input some text,Enter 'end' to finish\n");
    while (!time_to_exit) {
        fgets(work_area, WORK_SIZE, stdin);
        pthread_mutex_unlock(&mutex); //读入数据后解锁

        //检查子进程是否完成数据统计
        while (1) {
            pthread_mutex_lock(&mutex);
            if (work_area[0] != 0) {
                pthread_mutex_unlock(&mutex);
                usleep(20000);
            } else break;
        }
    }
    pthread_mutex_unlock(&mutex);

    //子线程读到 'end'　时会退出，这里等待子线程結
    void *thread_result = NULL;
    printf("\nWaiting for thread to finish...\n");
    if (pthread_join(a_thread, &thread_result) != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }


    //子线程已经结束打印提示
    printf("thread joined.\n");
    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}


//线程＝＝接收数据并退出
void *thread_function2(void *arg) {
    sleep(1);
    pthread_mutex_lock(&mutex);//上锁
    while (strncmp("end", work_area, 3) != 0) {
        printf("You input %d characters\n", strlen((work_area)) - 1);
        work_area[0] = '\0';
        pthread_mutex_unlock(&mutex);

        //等待主线程处理work_area[0]==0
        sleep(1);
        while (work_area[0] == '\0') {
            pthread_mutex_unlock(&mutex);
            sleep(1);
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_mutex_unlock(&mutex);
    //接收到end退出
    time_to_exit = 1;//提示主线程要退出啦
    work_area[0] = 0;
    pthread_exit(NULL);
}



//void test_attr()
//{
//    pthread_attr_t attr;
//    pthread_attr_init(&attr);//初始化属性
//    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置脱离属性
//    pthread_create(&thread,&attr,function,(void*)message); //创建detach线程
//    pthread_attr_destroy(&attr);//回收属性
//
//    struct sched_param sched;
//    pthread_attr_setschedpolicy(&attr,SCHED_OTHER);              //设置其他调度方式
//    sched.sched_priority = sched_get_priority_min(SCHED_OTHER);  //最小优化级
//    pthread_attr_setschedparam(&attr,&sched);                    //设置线程属性
//
//}