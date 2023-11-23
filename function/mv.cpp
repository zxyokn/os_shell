#include "../shell.h"
int MV(char **args) // 简单理解为先复制文件到目标目录，再将原文件删除
{
    CP(args);
    char **temp = (char **)malloc(sizeof(char *) * 3);
    temp[1] = "-r";
    temp[2] = args[1];
    RM(temp);
    free(temp);
    return 1;
}
