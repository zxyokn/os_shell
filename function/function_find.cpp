#include "../shell.h"

// 寻找对应函数
int function_find(char **args)
{
    int status = -1;
    if (args == NULL)
        return status;            // 未传入参数
    else if (is_background(args)) // 判断是否为后台命令
    {
        handle_background(args);
        return 1;
    }
    else if (is_pipe(args)) // 判断是否为管道命令
    {
        handle_pipe(args);
        return 1;
    }
    else
    {
        int original_stdin = dup(STDIN_FILENO);
        int original_stdout = dup(STDOUT_FILENO);
        handle_redirection(args);
        for (int i = 0; i < num; i++)
        {
            if (strcmp(args[0], supported_function[i]) == 0)
            {

                int status = (*myfunction[i])(args); // 依据分词结果的第一部分寻找对应函数，利用函数库找到对应函数的地址
                dup2(original_stdin, STDIN_FILENO);
                dup2(original_stdout, STDOUT_FILENO); // 恢复标准输入输出文件描述符
                return status;
            }
        }
    }
    return 1;
}