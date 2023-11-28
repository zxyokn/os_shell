#include "../shell.h"

void handle_pipe(char **args)
{
    int original_stdin;
    int original_stdout;
    // 分割命令为两部分
    char **args1 = args;
    char **args2 = NULL;
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            args[i] = NULL; // 分割命令
            args2 = args + i + 1;
            break;
        }
    }
    pid_t child_pid;

    args1[1] = ">";
    args1[2] = "temp.txt";
    args2[2] = "<";
    args2[2] = "temp.txt";
    for (int i = 0; args1[i] != NULL; i++)
        cout << args1[i] << " ";
    cout << endl;
    child_pid = fork(); // 创建子进程

    if (child_pid == -1)
    {
        perror("创建子进程失败\n");
        exit(EXIT_FAILURE);
    }
    // int original_stdin = dup(STDIN_FILENO);
    // original_stdout = dup(STDOUT_FILENO);
    // original_stdin = dup(STDIN_FILENO);
    if (child_pid == 0) // 子进程
    {
        handle_redirection(args1);
        exit(EXIT_SUCCESS);
    }
    else // 父进程
    {
        handle_redirection(args2);
        // 等待子进程结束
        wait(NULL);
    }
    // dup2(original_stdin, STDIN_FILENO);
    // dup2(original_stdout, STDOUT_FILENO); // 恢复标准输入输出文件描述符
}

bool is_pipe(char **args) // 判断是否为管道命令
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            return true;
        }
    }
    return false;
}