#include "../shell.h"

// 寻找对应函数
int function_find(char **args)
{
    int status = -1;
    if (args == NULL)
        return status; // 未传入参数
    else
    {
        // 保存原始标准输入输出文件描述符
        int original_stdin = dup(STDIN_FILENO);
        int original_stdout = dup(STDOUT_FILENO);

        handle_redirection(args);
        for (int i = 0; i < num; i++)
        {
            if (strcmp(args[0], supported_function[i]) == 0)
            {
                return (*myfunction[i])(args); // 依据分词结果的第一部分寻找对应函数，利用函数库找到对应函数的地址
            }
        }
        fflush(stdout);
        fflush(stdin);
        // 恢复标准输入输出文件描述符
        dup2(STDIN_FILENO, original_stdin);
        dup2(STDOUT_FILENO, original_stdout);

        // 关闭保存的文件描述符
        // close(original_stdin);
        // close(original_stdout);
    }
    return 1;
}