#include "shell.h"

// 输出提示符，包括当前路径和shell名称
void my_shell_promt()
{
    char path[500];
    getcwd(path, 500); // 获取当前路径
    char command_promt[200] = "[myshell ";
    strcat(command_promt, path);
    strcat(command_promt, "]$");
    printf("%s", command_promt); // 输出提示符
}

// 对所获取的指令进行分词
char **parse(char *buffer)
{
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

// 寻找对应函数
int function_find(char **args)
{
    int status = -1;
    if (args == NULL)
        return status; // 未传入参数
    else
    {
        for (int i = 0; i < num; i++)
        {
            if (strcmp(args[0], supported_function[i]) == 0)
            {
                return (*myfunction[i])(args); // 依据分词结果的第一部分寻找对应函数，利用函数库找到对应函数的地址
            }
        }
    }
    return 1;
}

int CD(char **args)
{
    // printf("%s\n", args[1]);
    if (args[1] == NULL)
    {
        perror("Error!No Path\n");
    }
    // printf("%d", chdir("123"));
    if (chdir(args[1]) != 0)
    {
        perror("Error!failed to change directory\n");
    }
    return 1;
}

int HELP(char **args)
{
    for (int i = 0; i < num; i++)
        printf("%s\n", supported_function[i]);
    return 1;
}

int EXIT(char **args)
{
    exit(0);
}

// 用于ls的排序
bool cmp(string s1, string s2)
{
    return s1 < s2;
}

int LS(char **args)
{
    char s[100];      // 用于存储文件名的缓冲区
    string res[1000]; // 用于存储文件名的字符串数组
    DIR *dir = opendir(".");
    struct dirent *rent;
    int count = 0;
    while ((rent = readdir(dir))) // 利用dirent中的readdir来获取文件
    {
        strcpy(s, rent->d_name);         // 获取文件名
        if (s[0] != '.' && s[0] != '\0') // 判定为非隐藏文件才显示
        {
            res[count++] = s;
        }
    }
    sort(res, res + count, cmp); // 排序输出文件
    for (int i = 0; i < count; i++)
        cout << res[i] << " " << endl;
    // printf("%s ", res[i]);
    // printf("\n");             //string printf好像不是很兼容
    closedir(dir);
    return 1;
}

// 复制文件
int cp_file(char **args)
{

    FILE *file_source = NULL;
    FILE *file_destination = NULL;
    file_source = fopen(args[1], "r"); // 初始化所需复制的文件
    if (file_source == NULL)           // 检查源文件与目的地址的存在性
    {
        perror("no source file\n");
    }
    file_destination = fopen(args[2], "w"); // 初始化复制地址
    if (file_destination == NULL)
    {
        perror("no destination\n");
    }
    int ch = EOF;
    while ((ch = fgetc(file_source)) != EOF)
    {
        // printf("%c\n", ch);
        fputc(ch, file_destination); // 进行文件复制
    }
    fclose(file_source);
    fclose(file_destination);
    return 1;
}

// 复制文件夹
int cp_folder(char **args)
{
    if (mkdir(args[2], 0777)) // 在目标地址新建复制的文件夹
    {
        printf("目标文件夹已存在\n");
        return -1;
    }
    DIR *folder_source = opendir(args[1]); // 初始化所需复制的文件夹
    if (folder_source == NULL)
    {
        perror("no source folder\n");
    }

    char new_folder_source[4096];      // 新的源文件夹路径
    char new_folder_destination[4096]; // 新的目标文件夹路径

    struct dirent *srcDirent = NULL;
    int flag = 0;

    while ((srcDirent = readdir(folder_source)) != NULL)
    {
        flag++;
        if (flag > 2) // 去除 . 和 .. 的影响 即隐藏文件夹的影响
        {
            bzero(new_folder_source, sizeof(new_folder_source)); // 清空字符串
            bzero(new_folder_destination, sizeof(new_folder_destination));

            sprintf(new_folder_source, "%s/%s", args[1], srcDirent->d_name); // 构建新的源和目标文件夹路径
            sprintf(new_folder_destination, "%s/%s", args[2], srcDirent->d_name);

            if (srcDirent->d_type == DT_DIR)
            {
                char **temp;
                temp[1] = new_folder_source;
                temp[2] = new_folder_destination;
                cp_folder(temp);
            }
            else
            {
                char **temp;
                temp[1] = new_folder_source;
                temp[2] = new_folder_destination;
                cp_file(temp);
            }
        }
    }
    closedir(folder_source);
    return 1;
}
// cp函数的实现
int CP(char **args)
{
    struct stat file_stat;               // 判断是否为文件or文件夹
    if (stat(args[1], &file_stat) == -1) // 初始化结构体
    {
        perror("Error getting file information");
        return -1;
    }

    if (S_ISDIR(file_stat.st_mode) == 1)
    {
        if (cp_folder(args) == -1) // 复制文件夹
            return -1;
    }

    else if (S_ISREG(file_stat.st_mode) == 1)
    {
        if (cp_file(args) == -1) // 复制文件
            return -1;
    }
}
