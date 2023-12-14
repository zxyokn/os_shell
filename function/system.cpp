#include "../shell.h"

int SYSTEM(char **args)
{
    char *args1 = (char *)malloc(1024 * sizeof(char *));

    for (int i = 1; args[i] != NULL; i++)
    {
        strcat(args1, " ");
        strcat(args1, args[i]); // 将命令和参数合并
    }
    system((const char *)args1); // 执行命令
    return 1;
}