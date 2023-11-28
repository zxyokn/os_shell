#include "../shell.h"
char history[100][1024] = {0}; // 定义数组来存储历史命令
int history_index = 0;         // 记录命令总数

void my_shell_promt()
{
    char path[500];
    getcwd(path, 500); // 获取当前路径
    char command_promt[200] = "[myshell: ";
    strcat(command_promt, path);
    strcat(command_promt, "]$");
    printf("%s", command_promt); // 输出提示符
}

// 对所获取的指令进行分词
char **parse(char *buffer)
{
    snprintf(history[history_index], strlen(buffer), "%s", buffer);
    history_index++;
    int size = tok_bufsize;
    char *token;
    int index = 0;
    char **tokens = (char **)malloc(size * sizeof(char **)); // 定义tokens数组用于记录各个分词的结果
    token = strtok(buffer, tok_dilim);                       // 依据分词符对指令进行分词
    while (token != NULL)
    {
        tokens[index] = token; // 将token结果存入tokens数组
        index++;
        token = strtok(NULL, tok_dilim); // 第二次开始即从NULL开始进行分词
    }
    tokens[index] = NULL; // 将最后一位置为NULL
    return tokens;
}

int HISTORY(char **args)
{
    for (int i = 0; i < history_index; i++)
        printf("%d.%s\n", i + 1, history[i]);
    return 1;
}