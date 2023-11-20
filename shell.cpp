#include "shell.h"

int main()
{
    char *buffer = (char *)malloc(max_size); // 为命令分配空间

    while (1)
    {
        my_shell_promt(); // 输出提示符，包括当前路径和shell名称
        char **args;
        int status;
        fgets(buffer, max_size, stdin); // 获取所输入的命令
        if (buffer[0] == '\n')          // 若只输入回车会被无视
            continue;
        buffer[strlen(buffer) - 1] = 0; // 去掉回车换行
        args = parse(buffer);           // 对指令进行分词
        status = function_find(args);   // 依据分词结果寻找函数进行实现
    }
}