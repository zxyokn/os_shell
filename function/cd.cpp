#include "../shell.h"

int CD(char **args)
{
    if (args[1] == NULL) // 未输入目录
    {
        perror("未输入目录\n");
    }
    if (chdir(args[1]) != 0) // 改变目录失败
    {
        perror("切换目录失败\n");
    }
    return 1;
}