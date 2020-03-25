//
// Created by kaihua on 3/23/20.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void test_malloc(){
    char*some_memory;
    int obtained = 0;

    while (obtained < (1024*10)){  //分配10G内存

        //1M 分配
//        some_memory = (char*)malloc(1024*1024);//分配1Mbytes
//        if(some_memory != NULL){
//            obtained++;
//            sprintf(some_memory,"Hello World");
//            printf("%s - now allocated %d Megabytes\n",some_memory,obtained);
//        }else
//        {
//            printf("Error\n");
//            exit(EXIT_FAILURE);
//        }

//        //1K分配
//        for (int i = 0; i < 1024; ++i) {
//            some_memory = malloc(1024);
//            if(some_memory==NULL)exit(EXIT_FAILURE);
//            sprintf(some_memory,"Hello World");
//        }
//        obtained++;
//        printf("%s - now allocated %d Megabytes\n",some_memory,obtained);
//    }

        //破坏性操作，会引起 malloc失败
        some_memory = (char*)malloc(1024*1024*1024);
        char*ptr=some_memory+10;
        while (1){
            *ptr = '\0';
            ptr++;
        }
    }


    exit(EXIT_SUCCESS);
}