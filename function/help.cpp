#include "../shell.h"
int HELP(char **args)
{
    for (int i = 0; i < num; i++)
    {
        cout << supported_function[i] << " " << function_description[i] << endl;
    }
    cout << "使用< or > + filename 来进行输入输出重定向" << endl;
    cout << "使用指令a | 指令b 将指令a的输出作为指令b的输入" << endl;
    cout << "使用&指令，将该指令置于后台运行" << endl;
    return 1;
}