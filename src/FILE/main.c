//
// Created by kaihua on 3/13/20.
//

#include <stdlib.h>

extern int lowlevel();
extern int STDIO();
extern int test_getopt(int argc, char *argv[]);
extern int test_getopt_long(int argc, char *argv[]);
extern void test_env(int argc,char*argv[]);
extern void time_0();
extern void test_log();
extern void test_rlimit();
int main(int argc,char*argv[])
{
    //lowlevel();
    //test_getopt(argc,argv);
    //test_getopt_long(argc,argv);
    //test_env(argc,argv);
    //time_0();
    //test_log();
    test_rlimit();

    exit(0);
}
