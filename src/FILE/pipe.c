//
// Created by kaihua on 4/3/20.
//

//  进程管道

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void test_rpipe()
{
    char buffer[1024]; memset(buffer,0, sizeof(buffer));

    FILE* fd = popen("uname -a","r");//用 popen　启动命令
    if(fd !=NULL){
        int chars = fread(buffer,sizeof(char),sizeof(buffer),fd);//文件方式读取返回的数据
        if(chars>0){
            printf("Output was:%s\n",buffer);
        }
        pclose(fd);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

void test_wpipe()
{
    char buffer[1024]="There is some chars in the buffer...\n";

    FILE* fd = popen("od -c","w");//用 popen　启动命令
    if(fd !=NULL){
        int i=0;
        while(i++<3){
            printf("write something\n");
            fwrite(buffer, sizeof(char),strlen(buffer),fd);//向管道写入数据
            sleep(1);
        }
        printf("closing...\n");
        pclose(fd);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}