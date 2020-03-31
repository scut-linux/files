//
// Created by kaihua on 3/26/20.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//=================================================
static  void ouch(int sig){
    printf("OUCH! i got signal %d\n",sig);
    (void)signal(SIGINT,SIG_DFL);
}

void test_signal()
{
    //关联信号处理函数ouch来处理SIGINT(中断信号)
    (void)signal(SIGINT,ouch);

    while(1)
    {
        printf("Hello World!\n");sleep(1);
    }
}
//=================================================