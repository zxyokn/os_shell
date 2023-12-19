#include "../shell.h"
int UPPER(char **args)
{
    for (int i = 0; i < strlen(args[1]); i++)
    {
        if (args[1][i] == '\x1b')
            continue;
        if (args[1][i] >= 'a' && args[1][i] <= 'z')
        {
            args[1][i] -= 32;
        }
    }
    cout << args[1] << endl;
    return 1;
}
// 仅用于测试 管道功能