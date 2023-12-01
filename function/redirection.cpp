#include "../shell.h"

char *file_buffer = (char *)malloc(4096);
void handle_redirection(char **args)
{
    int input_redirection = 0;  // 标记是否有输入重定向
    int output_redirection = 0; // 标记是否有输出重定向
    char *input_file = NULL;    // 输入重定向的文件名
    char *output_file = NULL;   // 输出重定向的文件名

    // 检查是否包含输入输出重定向符号
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {
            input_redirection = 1;
            input_file = args[i + 1]; // 获取源文件路径
            FILE *src_r = fopen((const char *)input_file, "r");
            fread(file_buffer, 4096, 1, src_r);
            file_buffer[strlen(file_buffer) - 1] = 0;
            args[i] = file_buffer; // 将"<"置为NULL，以便后续执行命令时忽略
            args[i + 1] = NULL;
            return;
        }
        else if (strcmp(args[i], ">") == 0)
        {
            output_redirection = 1;
            output_file = args[i + 1]; // 获取目标路径
            args[i] = NULL;            // 将">"置为NULL，以便后续执行命令时忽略
        }
    }
    if (input_redirection)
    {
        int inPutFile = open(input_file, O_RDONLY);
        if (inPutFile == -1)
        {
            perror("输入源文件打开失败\n");
            exit(EXIT_FAILURE);
        }
        if (dup2(inPutFile, STDIN_FILENO) == -1) // 将输入源文件描述符复制到标准输入
        {
            perror("输入重定向失败");
            exit(EXIT_FAILURE);
        }
        close(inPutFile);
    }
    if (output_redirection)
    {
        int outPutFile = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666); // 只写方式，不存在则创建，如果文件存在并且以写方式打开，则将文件截断为零长度。
        if (outPutFile == -1)
        {
            perror("打开或创建目标文件失败\n");
            exit(EXIT_FAILURE);
        }
        if (dup2(outPutFile, STDOUT_FILENO) == -1)
        {
            perror("输出重定向失败\n");
            exit(EXIT_FAILURE);
        }
        close(outPutFile);
    }
}
