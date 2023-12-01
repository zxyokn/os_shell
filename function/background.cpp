#include "../shell.h"
bool is_background(char **args);
int handle_background(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "&") == 0)
        {
            args[i] = NULL;
            break;
        }
    }
    for (int i = 1; args[i] != NULL; i++)
    {
        strcat(args[0], " ");
        strcat(args[0], args[i]);
    }
    for (int i = 0; args[i] != NULL; i++)
    {
        cout << args[i] << " ";
    }
    cout << endl;
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("\n");
        printf("child pid:%d working...\n", getpid());
        sleep(10);
        system((const char *)args[0]); // 执行命令
        printf("\n");                  //?????????????
        printf("child pid:%d done\n", getpid());
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