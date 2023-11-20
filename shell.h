#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <dirent.h>
#include <algorithm>
#include <string>
#include <sys/stat.h>
using namespace std;
#define tok_dilim " "  // 定义分词
#define tok_bufsize 64 // 分词最大为64
#define max_size 1024  // 命令长度最大值

extern void my_shell_promt();          // 输出提示符，包括当前路径和shell名称
extern char **parse(char *buffer);     // 对所获取的指令进行分词
extern int function_find(char **args); // 依据分词结果寻找函数
extern int CD(char **args);
extern int HELP(char **args);
extern int EXIT(char **args);
extern int LS(char **args);
extern int CP(char **args);

static char supported_function[5][50] =
    {
        "cd", "help", "exit", "ls", "cp"};

static int (*myfunction[])(char **) = // 函数指针数组
    {
        &CD, &HELP, &EXIT, &LS, &CP};

static int num = sizeof(supported_function) / sizeof(supported_function[0]); // 用于计算所支持函数的数量

#endif