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
#include <fcntl.h>
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
extern int MV(char **args);
extern int RM(char **args);
extern int PWD(char **args);
extern int HISTORY(char **args);
extern int TREE(char **args);
extern int PS(char **args);
extern void handle_redirection(char **args);
extern void handle_pipe(char **args);
extern bool is_pipe(char **args); // 判断是否为管道命令
extern bool is_background(char **args);
extern int handle_background(char **args);
extern int UPPER(char **args);
extern int CLEAR(char **args);
extern int SYSTEM(char **args);
static char supported_function[][50] =
    {
        "cd", "help", "exit", "ls", "cp", "mv", "rm", "pwd", "history", "tree", "ps", "up", "clear", "system"};

static int (*myfunction[])(char **) = // 函数指针数组
    {
        &CD, &HELP, &EXIT, &LS, &CP, &MV, &RM, &PWD, &HISTORY, &TREE, &PS, &UPPER, &CLEAR, &SYSTEM};

static string function_description[] =
    {
        "输入cd+指定地址来跳转目录",
        "输入help来查看本shell所支持的指令及其用法",
        "输入exit退出shell程序",
        "输入ls查看当前目录下的内容",
        "输入cp+源文件+指定目录，将该文件复制到指定目录中",
        "输入mv+源文件+指定目录，将该文件移动到指定目录中",
        "输入rm+源文件或rm -r+源文件夹，来删除指定文件或文件夹",
        "输入pwd来获取当前工作目录的路径",
        "输入history来显示shell命令的历史记录",
        "输入tree+指定目录来显示指定目录的树状结构，或仅输入tree来显示当前目录的树状结构",
        "输入ps指令显示正在运行的进程的信息",
        "输入up指令用于将小写字母转换为大写字母，此命令用于管道功能的测试",
        "输入clear指令清空屏幕",
        "输入system指令调用系统指令"};

static int num = sizeof(supported_function) / sizeof(supported_function[0]); // 用于计算所支持函数的数量

extern char *file_buffer;
#endif