#include "../shell.h"

// 寻找对应函数
int function_find(char **args)
{
    int status = -1;
    if (args == NULL)
        return status; // 未传入参数
    else
    {
        for (int i = 0; i < num; i++)
        {
            if (strcmp(args[0], supported_function[i]) == 0)
            {
                return (*myfunction[i])(args); // 依据分词结果的第一部分寻找对应函数，利用函数库找到对应函数的地址
            }
        }
    }
    return 1;
}