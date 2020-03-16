//
// Created by kaihua on 3/16/20.
//
#include <syslog.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void test_log()
{
    int logmask;

    openlog("logmask",LOG_PID|LOG_CONS,LOG_USER);
    syslog(LOG_INFO,"informative message, pid=%d",getpid());
    syslog(LOG_DEBUG,"debug message,should appear");
    logmask = setlogmask(LOG_UPTO(LOG_NOTICE));//只记录 <= LOG_NOTICE 的信息,DEBUG不记录
    syslog(LOG_DEBUG,"debug message,should not appear");
    exit(0);
}