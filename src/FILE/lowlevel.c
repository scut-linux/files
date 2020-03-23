
/*
 * 底层访问接口
 * */

#include <sys/ioctl.h> //for ioctl


//for write  read  close   dup dup2
#include <unistd.h>

//for open
#include "fcntl.h"
#include <sys/types.h>
#include <sys/stat.h>

//for lseek
#include <sys/types.h>
#include <unistd.h>

//for fstat  stat lstat
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#include "stdio.h"   //for fopen fread fwrite fclose .....


#include "stdlib.h"
#include "string.h"

//for errno
#include <errno.h>


char *write1 = "write 1 to std output\n";
char *write2 = "error to write to std output\n";
char *write3 = "what you input is:\n";


int lowlevel()
{

    /*程序运行时，会打开3个文件: 0标准输入   1标准输出  2警告,可以使用 read write close cltr来操作*/
    close(1);//关闭标志输出
    if (write(1, write1, strlen(write1)) != strlen(write1)) {
        write(2, write2, strlen(write2));
    }

    //char *stre = strerror(errno);  write(2, stre, strlen(stre));
    perror("出错啦");


    /*同样可以使用stdin  stdout,stderr 访问打开的三个文件 */
    /*
    //fclose(stdout);
    if(fwrite(write1,1,strlen(write1),stdout) != strlen(write1))
    {
        fwrite(write2,1,strlen(write2),stderr);
    }
    */

    //也可以使用fgetc,getc getchar()==getc(stdin)  fputc,putc,putchar 来访问
/*    u_char datas[100];int offset=0;
    memset(datas,0,sizeof(datas));
    while(1){
        int c = getc(stdin);
        datas[offset++]=c;
        if (c == '\n')break;
    }
    if(offset>0){
        fwrite(write3,1,strlen(write3),stdout);
        fwrite(datas,1,strlen(datas),stdout);//打印输入的字符
    }*/




    return 0;
}