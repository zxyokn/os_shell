#include "../shell.h"

void handle_pipe(char **args)
{
    int original_stdin;
    int original_stdout;
    // 分割命令为两部分
    char **args1 = args;
    char **args2 = (char **)malloc(1024 * sizeof(char **));
    for (int i = 0; i < 10; i++)
    {
        args2[i] = (char *)malloc(1024 * sizeof(char *));
    }
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "|") == 0)
        {
            args[i] = NULL; // 分割命令
            memcpy(args2[0], args[i + 1], strlen(args[i + 1]));
            args2[1] = NULL;
            break;
        }
    }
    // cout << args1[0] << " " << args2[0] << endl;

    for (int i = 0; args1[i] != NULL; i++)
    {
        if (args1[i + 1] == NULL)
        {
            // cout << i << endl;
            args1[i + 1] = (char *)">";
            args1[i + 2] = (char *)"temp.txt";
            break;
        }
    }

    for (int i = 0; args2[i] != NULL; i++)
    {

        // cout << i << endl;
        if (args2[i + 1] == NULL)
        {
            args2[i + 1] = (char *)"<";
            args2[i + 2] = (char *)"temp.txt";
            args2[i + 3] = NULL;
            break;
        }
    }
    // cout << args1[0] << " " << args1[1] << " " << args1[2];
    // if (args1[3] != NULL)
    //     cout << " " << args1[3] << endl;
    // else
    //     cout << endl;
    // cout << args2[0] << " " << args2[1] << " " << args2[2] << endl;

    pid_t child_pid;
    child_pid = fork(); // 创建子进程

    if (child_pid == -1)
    {
        perror("创建子进程失败\n"); // pwd | tree
        exit(EXIT_FAILURE);
    }
    original_stdout = dup(STDOUT_FILENO);
    original_stdin = dup(STDIN_FILENO);
    if (child_pid == 0) // 子进程
    {

        handle_redirection(args1);
        for (int i = 0; i < num; i++)
        {
            if (strcmp(args1[0], supported_function[i]) == 0)
            {
                (*myfunction[i])(args1); // 依据分词结果的第一部分寻找对应函数，利用函数库找到对应函数的地址
                dup2(original_stdin, STDIN_FILENO);
                dup2(original_stdout, STDOUT_FILENO); // 恢复标准输入输出文件描述符
            }
        }
        exit(EXIT_SUCCESS);
    }
    else // 父进程
    {
        wait(NULL);

        handle_redirection(args2);

        for (int i = 0; i < num; i++)
        {
            if (strcmp(args2[0], supported_function[i]) == 0)
            {
                (*myfunction[i])(args2); // 依据分词结果的第一部分寻找对应函数，利用函数库找到对应函数的地址

                dup2(original_stdin, STDIN_FILENO);
                dup2(original_stdout, STDOUT_FILENO); // 恢复标准输入输出文件描述符
                memset(file_buffer, 0, strlen(file_buffer));
            }
        }
    }
    remove("temp.txt");
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
