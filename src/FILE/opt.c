//
// Created by kaihua on 3/16/20.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*测试getopt,getopt_long,输入参数*/

int test_getopt(int argc, char *argv[]) {
    int opt;
    /*if: 表示if 后面要加参数
     * lr 表示后面不用加参数*/
    while ((opt = getopt(argc, argv, ":if:lr")) != -1) {
        switch (opt) {
            case 'i':
            case 'r':
            case 'l':
                printf("option is %c\n.", opt);
                break;
            case 'f':
                printf("filename is %s\n", optarg);
                break;
            case '?':
                printf("unkonw option:%c\n", optopt);
                break;
            case ':':
                printf("you need a value!\n");
                break;
        }
    }
    return 0;
}


#include <getopt.h>

int test_getopt_long(int argc, char *argv[]) {
    int opt;
    struct option longopts[] = {
            /*长名       ,后面参数个数,getopt_long返回值,返回值*/
            {"initialize", 0, NULL, 'i',},
            {"file", 1, NULL, 'f',},
            {"list", 0, NULL, 'l',},
            {"restart", 0, NULL, 'r',},
            {0, 0, 0, 0,}
    };
    /*if: 表示if 后面要加参数
     * lr 表示后面不用加参数*/
    while ((opt = getopt_long(argc, argv, ":if:lr", longopts, NULL)) != -1) {
        switch (opt) {
            case 'i':
            case 'r':
            case 'l':
                printf("option is %c\n.", opt);
                break;
            case 'f':
                printf("filename is %s\n", optarg);
                break;
            case '?':
                printf("unkonw option:%c\n", optopt);
                break;
            case ':':
                printf("you need a value!\n");
                break;
        }
    }
    for (; optind < argc; optind++) {
        printf("argument is:%s\n", argv[optind]);
    }
    return 0;
}