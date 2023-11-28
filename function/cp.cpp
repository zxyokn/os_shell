#include "../shell.h"
int cp_file(char **args);
int cp_folder(char **args);

// cp函数的实现
int CP(char **args)
{
    struct stat file_stat;               // 用于判断是否为文件or文件夹
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

            snprintf(new_folder_source, strlen(args[1]) + strlen(srcDirent->d_name), "%s/%s", args[1], srcDirent->d_name); // 构建新的源和目标文件夹路径
            snprintf(new_folder_destination, strlen(args[2]) + strlen(srcDirent->d_name), "%s/%s", args[2], srcDirent->d_name);

            if (srcDirent->d_type == DT_DIR)
            {
                char **temp = (char **)malloc(sizeof(char *) * 3);
                temp[1] = new_folder_source;
                temp[2] = new_folder_destination;
                cp_folder(temp);
                free(temp);
            }
            else
            {
                char **temp = (char **)malloc(sizeof(char *) * 3);
                temp[1] = new_folder_source;
                temp[2] = new_folder_destination;
                cp_file(temp);
                free(temp);
            }
        }
    }
    closedir(folder_source);
    return 1;
}