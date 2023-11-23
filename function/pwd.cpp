#include "../shell.h"
int PWD(char **args)
{
    char *path = getcwd(NULL, 0); // 直接使用pwd获取当前路径
    printf("%s\n", path);
    return 1;
}