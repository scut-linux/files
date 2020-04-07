//
// Created by kaihua on 3/25/20.
//

//使用system启动
#include <stdlib.h>
#include <stdio.h>

void test_system() {
    printf("Running ps with system\n");
    //system("ps ax");//前台进程
    system("ps ax &");//后台进行
    printf("Done.\n");
    exit(EXIT_SUCCESS);
}


#include <unistd.h>
#include <sys/wait.h>

void test_fork() {
    int n = 0;
    pid_t pid;
    char *message = NULL;
    int exit_code = 0;
    switch ((pid = fork())) {
        case -1:
            fprintf(stderr, "Fork() Error.\n");
            break;
        case 0:
            message = "Child";
            n = 5;
            exit_code = 123;
            break;
        default:
            message = "Parent";
            exit_code = 456;
            n = 3;
            break;
    }

    for (int i = 0; i < n; ++i) {
        printf("%s\n",message);
        sleep(1);
    }

    //等待子进程退出
    if (pid != 0) {
        int stat;
        pid_t child_pid = wait(&stat);//等待子进程退出，并返回子进程的状态码stat
        printf("Child has finished with pid=%d\n", child_pid);
        if (WIFEXITED(stat)) {//判断是不是正常退出　
            printf("Child exited with code=%d\n", WEXITSTATUS(stat));
        } else {
            printf("Child terminated abnormally.\n");
        }
    }

    printf("%s begins exit with code=%d.\n",message,exit_code);
    exit(exit_code);
}
