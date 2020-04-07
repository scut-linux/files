//
// Created by kaihua on 3/19/20.
//

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#define PASSWORD_LEN 8

void test_termios()
{
    struct  termios irset,nrset;
    char password[PASSWORD_LEN];

    tcgetattr(fileno(stdin),&irset);//读取标准输入的当前设置

    //关闭ECHO
    nrset=irset;
    nrset.c_lflag &=~ECHO;
    printf("Enter password: ");

    //设置新属性
    if(tcsetattr(fileno(stdin),TCSAFLUSH,&nrset) !=0){
        fprintf(stderr,"Could not set attributes\n");
    }else{
        fgets(password,PASSWORD_LEN,stdin);
        tcsetattr(fileno(stdin),TCSANOW,&irset);
        fprintf(stdout,"\nYou entered %s\n",password);
    }exit(0);
}