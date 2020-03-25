//
// Created by kaihua on 3/23/20.
//
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

void test_lock() {
    int file_desc;
    int save_errno;

    //使用O_EXCL锁定文件
    file_desc = open("/tmp/LOCK.test", O_RDWR | O_CREAT | O_EXCL, 0444);
    if (file_desc == -1) {
        save_errno = errno;
        printf("Open failed with error %d\n", save_errno);
    } else {
        printf("Open succeeded \n");
        exit(EXIT_SUCCESS);
    }
}
//==============================================================================================================================================
/*
 *   　test_fcntl  :设置10-30 :只读　＝＝》其它程序可以读　　　　　　　　　　　　　　　　　　设置40-50:只写，已经　独占 ==>其它程序不可读，不可以写
 *     test_tfcntl :测试　文件的读写性质
 * */
void test_fcntl() {
    const char *test_file = "/tmp/test_lock";
    int file_desc;
    char *byte_to_write = "A";
    struct flock r1, r2;

    //打开文件　
    file_desc = open(test_file, O_RDWR | O_CREAT, 0666);
    if (!file_desc) {
        fprintf(stderr, "Unable to open %s for read/write\n", test_file);
        exit(EXIT_FAILURE);
    }

    //写入一些数据　
    for (int i = 0; i < 100; ++i) {
        (void) write(file_desc, byte_to_write, 1);
    }

    //10-30字节设为区域１，并在其上设置共享锁
    r1.l_type = F_RDLCK;//只读
    r1.l_whence = SEEK_SET;//开头
    r1.l_start = 10;
    r1.l_len = 20;

    //40-50设为区域２，设置只写
    r2.l_type = F_WRLCK;
    r2.l_whence = SEEK_SET;
    r2.l_start = 40;
    r2.l_len = 10;

    //锁定文件
    printf("Process %d locking file\n", getpid());
    if (fcntl(file_desc, F_SETLK, &r1) == -1) {
        fprintf(stderr, "Failed to lock region 1\n");
    }
    if (fcntl(file_desc, F_SETLK, &r2) == -1) {
        fprintf(stderr, "Failed to lock region 2\n");
    }

    sleep(60);
    printf("Process %d closing file\n", getpid());
    close(file_desc);
    exit(EXIT_SUCCESS);
}

//测试锁定文件　
void show_Lock_info(struct flock *show) {
    printf("\tl_type=%d, ", show->l_type);
    printf("l_whence=%d, ", show->l_whence);
    printf("l_start=%d, ", show->l_start);
    printf("l_len=%d, ", show->l_len);
    printf("l_pid=%d\n", show->l_pid);
}

void test_tfcntl() {
    int file_desc, start_type;
    struct flock r;
    const char *test_file = "/tmp/test_lock";
#define SIZE_TO_TRY 5
    //打开文件　
    file_desc = open(test_file, O_RDWR | O_CREAT, 0666);
    if (!file_desc) {
        fprintf(stderr, "Unable to open %s for read/write\n", test_file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 99; i += SIZE_TO_TRY) {

        //设置区域
        r.l_type = F_WRLCK;
        r.l_whence = SEEK_SET;
        r.l_start = i;
        r.l_len = SIZE_TO_TRY;
        r.l_pid = -1;
        printf("Testing 只写 on region from %d to %d\n", i, i + SIZE_TO_TRY);

        //测试文件上的锁
        if (fcntl(file_desc, F_GETLK, &r) == -1) {
            fprintf(stderr, "F_GETLK f failed\n");
            exit(EXIT_FAILURE);
        }
        if (r.l_pid != -1) {
            printf("只写　woud fail. F_GETLK returned==>\n");
            show_Lock_info(&r);
        } else {
            printf("只写　would succeed.\n");
        }

        //用读锁测试一次
        r.l_type = F_RDLCK;
        r.l_whence = SEEK_SET;
        r.l_start = i;
        r.l_len = SIZE_TO_TRY;
        r.l_pid = -1;
        printf("Testing 只读 on region from %d to %d\n", i, i + SIZE_TO_TRY);

        if (fcntl(file_desc, F_GETLK, &r) == -1) {
            fprintf(stderr, "F_GETLK f failed\n");
            exit(EXIT_FAILURE);
        }
        if (r.l_pid != -1) {
            printf("只读 woud fail. F_GETLK returned==>\n");
            show_Lock_info(&r);
        } else {
            printf("只读 - Lock would succeed.\n");
        }
    }

    close(file_desc);
    exit(EXIT_SUCCESS);
}