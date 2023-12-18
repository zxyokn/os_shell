#include "../shell.h"

int CP(char **args);
int RM(char **args);

int MV(char **args)
{
    if (args[1] == NULL || args[2] == NULL)
    {
        fprintf(stderr, "用法: mv <源文件> <目标文件名或目录>\n");
        return -1;
    }

    // 如果目标路径中包含斜杠，则进行路径检查
    if (strchr(args[2], '/') != NULL)
    {
        // 获取目标路径
        char *dest_path = strdup(args[2]);

        // 获取目标路径的倒数第二级目录
        char *last_slash = strrchr(dest_path, '/');
        if (last_slash != NULL)
        {
            *last_slash = '\0'; // 切断字符串，留下倒数第二级目录
            struct stat dest_stat;
            if (stat(dest_path, &dest_stat) == -1)
            {
                // 目标路径不存在
                fprintf(stderr, "mv: 目标目录不存在\n");
                free(dest_path);
                return -1;
            }
        }

        // 继续执行文件复制和删除操作
        int cp_result = CP(args);
        if (cp_result == -1)
        {
            fprintf(stderr, "mv: 文件复制失败\n");
            free(dest_path);
            return -1;
        }
        // 使用 RM 函数删除源文件
        char **temp_rm = (char **)malloc(sizeof(char *) * 3);
        temp_rm[1] = (char *)"-r";
        temp_rm[2] = args[1];
        int rm_result = RM(temp_rm);
        free(temp_rm);

        if (rm_result == -1)
        {
            fprintf(stderr, "mv: 删除源文件失败\n");
            free(dest_path);
            return -1;
        }

        free(dest_path);
    }
    else
    {
        // 没有二级路径，直接执行 CP 和 RM 操作
        if (CP(args) == -1)
        {
            fprintf(stderr, "mv: 文件复制失败\n");
            return -1;
        }

        char **temp_rm = (char **)malloc(sizeof(char *) * 3);
        temp_rm[1] = (char *)"-r";
        temp_rm[2] = args[1];
        int rm_result = RM(temp_rm);
        free(temp_rm);

        if (rm_result == -1)
        {
            fprintf(stderr, "mv: 删除源文件失败\n");
            return -1;
        }
    }

    return 0;
}
