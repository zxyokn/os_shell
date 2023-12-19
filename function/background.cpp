#include "../shell.h"
bool is_background(char **args);
int handle_background(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "&") == 0)
        {
            args[i] = NULL; // 将&位置置空
            break;
        }
    }
    for (int i = 1; args[i] != NULL; i++)
    {
        strcat(args[0], " ");
        strcat(args[0], args[i]); // 将命令和参数合并
    }
    pid_t pid = fork();
    if (pid == 0) // 需要说明的是，此处输出的进程提示会和promt中的提示输出错位，但是不影响使用，可能需要改进
    {
        printf("\n");
        printf("child pid:%d working...\n", getpid());
        sleep(10);                     // 方便演示，延迟10秒
        system((const char *)args[0]); // 执行命令
        // printf("\n");
        printf("child pid:%d done\n", getpid());
        my_shell_promt();
        exit(1);
    }
    return 1;
}

bool is_background(char **args) // 判断是否为&命令
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "&") == 0)
        {
            return true;
        }
    }
    return false;
}