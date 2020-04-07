//
// Created by kaihua on 3/16/20.
//

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//写入一个文件 10000 次
void work()
{
    FILE *f;
    double x = 4.5;
    f=tmpfile();
    for (int i = 0; i < 10000; ++i) {
        fprintf(f,"Do some output\n");
        if(ferror(f)){
            fprintf(stderr,"Error writing to temporary file\n");
            exit(1);
        }
    }

    for (int j = 0; j < 1000000; ++j) {
        x = log(x*x+3.21);
    }
}

void test_rlimit()
{
    struct rusage ru;
    struct rlimit rl;
    int pri;

    //运行-查资源使用
    work();
    getrusage(RUSAGE_SELF,&ru);
    printf("CPU: User=%ld.%06d,System=%ld.%06ld\n",ru.ru_utime.tv_sec,ru.ru_utime.tv_usec,ru.ru_stime.tv_sec,ru.ru_stime.tv_usec);

    pri = getpriority(PRIO_PROCESS,getpid());
    printf("Current priority=%d\n",pri);

    getrlimit(RLIMIT_FSIZE,&rl);
    printf("Current FSIZE limit: soft=%ld,hard=%ld\n",rl.rlim_cur,rl.rlim_max);

    //设置限制文件大小，再用work会失败，
    rl.rlim_cur=1024;
    rl.rlim_max=2048;
    printf("Setting a 2k file size limit\n");
    setrlimit(RLIMIT_FSIZE,&rl);
    work();
    exit(0);
}