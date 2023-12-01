#include "../shell.h"
int p_tree(char *path, int level);

int TREE(char **args)
{
    const char *path;
    // if (args[1] == NULL)
    // {
    // path = getcwd(NULL, 0); // 如果未提供路径，则使用当前工作目录
    // p_tree((char *)".", 1);
    // }
    // else
    // {

    path = args[1];
    // cout << path << endl;
    p_tree(args[1], 1);
    //}
    chdir(path); // 切换当前工作目录为最终目录
    return 1;    // 理论上是不需要在主函数中存入path，但是在p_tree中变换目录老是出问题，暂如此解决
}

int p_tree(char *path, int level)
{

    DIR *source = opendir(path); // 打开指定目录
    struct dirent *dir;
    struct stat file_stat;
    chdir(path);
    while ((dir = readdir(source)) != NULL)
    {
        stat(dir->d_name, &file_stat);
        if ('.' == dir->d_name[0]) // 忽略以点开头的文件和目录（隐藏文件）
            continue;
        else if ((strcmp(".", dir->d_name) == 0) || (strcmp("..", dir->d_name) == 0))
        {
            continue;
        }
        // 打印缩进，表示目录层级
        int depth = level;
        // 设置颜色和修饰符
        if (S_ISDIR(file_stat.st_mode))
        {
            printf("\033[1;34m"); // 使用蓝色表示目录
        }
        else
        {
            printf("\033[0m"); // 恢复默认颜色
        }

        // 打印缩进
        while (depth--)
        {
            printf("|  ");
        }
        // 打印文件或目录名
        printf("|-- %s", dir->d_name);
        // 如果是目录，则递归调用 p_tree 函数
        if (S_ISDIR(file_stat.st_mode))
        {
            printf("\n");
            p_tree(dir->d_name, level + 1);
        }
        // 恢复默认颜色
        printf("\033[0m");
        // 换行
        printf("\n");
        // while (depth--)
        // {
        //     printf("|_");
        // }
        // printf("%s\n", dir->d_name);
        // depth = level;
        // // 如果是目录，则递归调用 p_tree 函数
        // if (S_ISDIR(file_stat.st_mode))
        // {
        //     p_tree(dir->d_name, depth + 2);
        //     printf("|\n"); // 打印目录之间的分隔线
        //    }
    }
    chdir("..");
    closedir(source);
    return 1;
}
