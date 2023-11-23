#include "../shell.h"

int CD(char **args)
{
    if (args[1] == NULL) // 未输入目录
    {
        perror("Error!No Path\n");
    }
    if (chdir(args[1]) != 0) // 改变目录失败
    {
        perror("Error!failed to change directory\n");
    }
    return 1;
}