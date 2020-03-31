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
extern void test_terminal_rw();
extern void test_termios();
extern  void test_malloc();
extern void test_lock();
extern void test_fcntl();
extern  void test_tfcntl();
extern  void test_dbm();
extern  void test_system();
extern void test_fork();
extern void test_signal();
extern void test_sigaction();
extern void test_thread();

int main(int argc,char*argv[])
{
    //lowlevel();
    //test_getopt(argc,argv);
    //test_getopt_long(argc,argv);
    //test_env(argc,argv);
    //time_0();
    //test_log();
    //test_rlimit();
    //test_terminal_rw();
    //test_termios();
    //test_malloc();
    //test_lock();
    //test_fcntl();
    //test_tfcntl();
    //test_dbm();
    //test_system();
    //test_fork();
    //test_signal();
    //test_sigaction();
     test_thread();
    exit(0);
}
