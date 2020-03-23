//
// Created by kaihua on 3/16/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//查询所有环境变量
void get_all_environ(void)
{
    extern char**environ;
    char**env=environ;
    while(*env){
        printf("%s\n",*env);env++;
    }
    exit(0);
}

//char *getenv (const char *__name)
void test_env(int argc,char*argv[])
{

    char *var,*value;
    if(argc==1){
        get_all_environ();
        exit(0);
    }
    if(argc >3)
    {
        fprintf(stderr,"usage: environ var [value]\n");
        exit(1);
    }

    //查询环境变量
    var = argv[1];
    value = getenv(var);
    if(value)
        printf("Variable %s has value %s\n",var,value);
    else
        printf("Variable %s has no value\n",var);

    //设置环境变量
    if(argc==3){
        char*string;
        value = argv[2];
        string = malloc(strlen(var)+strlen(value)+2);
        if(!string){
            fprintf(stderr,"out of memory\n");
            exit(1);
        }
        strcpy(string,var);// var
        strcat(string,"=");// var=
        strcat(string,value);//var=value
        printf("Calling putenv with: %s\n",string);
        if(putenv(string)!=0){
            fprintf(stderr,"putenv failed\n");
            free(string);
            exit(1);
        }

        //再读取一下环境变量
        value=getenv(var);
        if(value)
            printf("New value of %s is %s\n",var,value);
        else
            printf("New value of %s is null??\n",var);
        exit(0);
    }
}

void all_environ()
{
    extern char**environ;
    char**env=environ;
    while(*env){
        printf("%s\n",*env);env++;
    }
    exit(0);
}