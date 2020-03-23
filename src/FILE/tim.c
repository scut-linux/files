//
// Created by kaihua on 3/16/20.
//
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void time_0()
{
    struct  tm*ptm;
    time_t the_time;
    (void) time(&the_time);
    ptm = gmtime(&the_time);
    printf("Raw time is %ld\n",the_time);
    printf("gmtime-> data: %02d/%02d/%02d-%02d  time: %02d/%02d/%02d\n",
           ptm->tm_year,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_wday,
           ptm->tm_hour,ptm->tm_min,ptm->tm_sec
    );
    printf("asctime:%s",asctime(ptm));
    printf("ctime  :%s",ctime(&the_time));
    exit(0);
}