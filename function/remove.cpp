#include "../shell.h"
int rm_file(char **args);
int rm_folder(char **args);

int RM(char **args)
{
    struct stat file_stat;                                                      // 用于存储文件信息的结构体
    if ((stat(args[1], &file_stat) == -1) && (stat(args[2], &file_stat) == -1)) // 检查源文件和源文件夹是否都不存在
    {
        perror("无法获取文件信息\n");
        return -1;
    }
    if (strcmp(args[1], "-r") == 0) // 检查第一个参数是否为 "-r"，表示递归删除
    {
        if (rm_folder(args) == -1)
            return -1;
    }
    else
    {
        if (rm_file(args) == -1)
            return -1;
    }
    return 1;
}

int rm_file(char **args)
{
    if (args[1] == NULL)
    {
        perror("无法打开源文件\n");
    }
    remove(args[1]);
    return 1;
}

int rm_folder(char **args)
{

    if (args[2] == NULL)
    {
        perror("无法打开源文件\n");
    }
    DIR *folder_source; // 文件夹相关变量
    char dir_name[128] = {0};
    struct dirent *dir;
    struct stat statbuf;
    stat(args[2], &statbuf);           // 获取文件夹信息
    if (S_ISREG(statbuf.st_mode) == 1) // 删除普通文件
    {
        remove(args[2]);
        return 1;
    }
    else if (S_ISDIR(statbuf.st_mode) == 1) // 如果是文件夹，则递归删除其内容
    {
        folder_source = opendir(args[2]);
        // printf("%s\n", args[2]);
        while ((dir = readdir(folder_source)) != NULL)
        {
            if ((strcmp(".", dir->d_name) == 0) || (strcmp("..", dir->d_name) == 0))
            {
                continue;
            }
            snprintf(dir_name, (strlen(args[2]) + strlen(dir->d_name)) * 2, "%s/%s", args[2], dir->d_name); // 构造子文件/文件夹的路径
            char **temp = (char **)malloc(sizeof(char *) * 3);
            temp[2] = dir_name;
            rm_folder(temp);
            free(temp);
        }
        closedir(folder_source);
    }
    remove(args[2]); // 删除空文件夹或文件
    return 1;
}
