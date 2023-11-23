#include "../shell.h"
int HELP(char **args)
{
    for (int i = 0; i < num; i++)
    {
        cout << supported_function[i] << " " << function_description[i] << endl;
    }
    return 1;
}