//
// Created by kaihua on 3/24/20.
//
#include <ndbm.h>
#include <stdlib.h>
#include <fcntl.h>
#include <memory.h>
#include <gdbm.h>

#define  TEST_DB_FILE "/tmp/dbm1_test"
#define ITEMS_USED 3

struct test_data {
    char misc_chars[15];
    int any_integer;
    char more_chars[21];
};

void test_dbm() {
    struct test_data is[ITEMS_USED], ir;
    char key_to_use[20];
    int result;
    datum key_datum, data_datum;
    DBM *dbm_prt;

    //打开数据库
    dbm_prt = dbm_open(TEST_DB_FILE, O_RDWR | O_CREAT, 0666);
    if (!dbm_prt) {
        fprintf(stderr, "Failed to open database\n");
        exit(EXIT_FAILURE);
    }

    //初始化一些数据
    memset(is,0, sizeof(is));
    strcpy(is[0].misc_chars,"First!");is[0].any_integer=47;strcpy(is[0].more_chars,"foo");
    strcpy(is[1].misc_chars,"BAR!");  is[1].any_integer=13;strcpy(is[1].more_chars,"lucky");
    strcpy(is[2].misc_chars,"Third!");is[2].any_integer=34;strcpy(is[2].more_chars,"baz");

    //建立关键字
    for (int i = 0; i < ITEMS_USED; i++) {
        sprintf(key_to_use,"%c%c%d",is[i].misc_chars[0],is[i].more_chars[0],is[i].any_integer);
        key_datum.dptr=(void*)key_to_use;
        key_datum.dsize=strlen(key_to_use);
        data_datum.dptr=(void*)&is[i];
        data_datum.dsize= sizeof(struct test_data);

        result=dbm_store(dbm_prt,key_datum,data_datum,DBM_REPLACE);
        if(result!=0){
            fprintf(stderr,"dbm_store failed on key %s\n",key_to_use);
            exit(2);
        }
    }

    //读取数据，看一下是否成功写入
    sprintf(key_to_use,"%c%c%d",'B','l',13);
    key_datum.dptr=key_to_use;
    key_datum.dsize=strlen(key_to_use);
    data_datum=dbm_fetch(dbm_prt,key_datum);
    if(data_datum.dptr){
        printf("Data retrieved\n");
        memcpy(&ir,data_datum.dptr,data_datum.dsize);
        printf("==> %s %d %s\n",ir.misc_chars,ir.any_integer,ir.more_chars);
    }else{
        printf("No data found for key %s\n",key_to_use);
    }
    dbm_close(dbm_prt);
    exit(EXIT_SUCCESS);
}