//
// Created by kaihua on 3/19/20.
//

//对终端进行读写
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
//编写getchoise读入终端数据
int getchoice(char *greet, char *choices[]) {
    int chosen = 0;
    int selected;
    char **option;

    do {
        printf("Choice: %s\n", greet); //问候
        option = choices;
        while (*option) {              //选项菜单
            printf("%s\n", *option);
            option++;
        }

        //读入数据 ,查询选择
        do { selected = getchar(); } while (selected == '\n' || selected == ' ');
        option = choices;
        while (*option) {              //选项菜单
            if (selected == *option[0]) {
                chosen = 1;
                break;
            }
            option++;
        }

        if (!chosen) {
            printf("Incorrect choice,select again\n");
        }
    } while (!chosen);
    return selected;
}

char *menu[] = {
        "a - add new record",
        "d - delete record",
        "q - quit",
        NULL,
};

void test_terminal_rw(void) {
    int choice = 0;

    //检测是否被重定向了
    if(!isatty(fileno(stdout))){
        fprintf(stderr,"You are not a terminal!\n");
        exit(1);
    }

    do {
        choice = getchoice("Please select an action", menu);
        printf("You have chosen: %c\n", choice);
    } while (choice != 'q');
    exit(0);
} */

//使用tty
int getchoice(char *greet, char *choices[],FILE*in,FILE*out) {
    int chosen = 0;
    int selected;
    char **option;

    do {
        fprintf(out,"Choice: %s\n", greet); //问候
        option = choices;
        while (*option) {              //选项菜单
            fprintf(out,"%s\n", *option);
            option++;
        }

        //读入数据 ,查询选择
//        do { selected = getchar(); } while (selected == '\n' || selected == ' ');
        do { selected = getc(in); } while (selected == '\n' || selected == ' ');
        option = choices;
        while (*option) {              //选项菜单
            if (selected == *option[0]) {
                chosen = 1;
                break;
            }
            option++;
        }

        if (!chosen) {
            fprintf(out,"Incorrect choice,select again\n");
        }
    } while (!chosen);
    return selected;
}

char *menu[] = {
        "a - add new record",
        "d - delete record",
        "q - quit",
        NULL,
};

void test_terminal_rw(void) {
    int choice = 0;

    //检测是否被重定向了
    if(!isatty(fileno(stdout))){
        fprintf(stderr,"You are not a terminal!\n");
    }

    FILE*in = fopen("/dev/tty","r");
    FILE*out = fopen("/dev/tty","w");
    if(!in || !out){
        fprintf(stderr,"Unable to open /dev/tty\n");
        exit(1);
    }

    do {
        choice = getchoice("Please select an action", menu,in,out);
        printf("You have chosen: %c\n", choice);
    } while (choice != 'q');
    exit(0);
}