#include "../shell.h"

int PS(char **args)
{
    DIR *dir;
    struct dirent *dirent;
    FILE *file;
    char path[1024]; // 路径缓冲区
    char buf[1024];  // 数据缓冲区

    printf("%-23s%s\n", "进程名", "PID");

    if ((dir = opendir("/proc")) == NULL)
    {
        perror("无法打开proc目录\n");
        return -1;
    }

    while ((dirent = readdir(dir)) != NULL) // 遍历 /proc 目录下的进程
    {
        if (dirent->d_name[0] == '.') // 忽略以点开头的目录项
            continue;

        if (dirent->d_name[0] < '0' || dirent->d_name[0] > '9') // 忽略非数字开头的目录项
            continue;

        snprintf(path, sizeof(path) * 2, "/proc/%s/status", dirent->d_name); // 构建进程状态文件路径

        if ((file = fopen(path, "r")) == NULL)
        {
            perror("无法打开文件");
            continue;
        }

        char *name = NULL;
        char *pid = NULL;

        while (fgets(buf, sizeof(buf), file) != NULL) // 读取进程状态文件内容
        {
            if (strncmp(buf, "Name", 4) == 0)
            {
                name = strdup(buf + 6);           // 使用 strdup 分配内存并复制名称
                name[strcspn(name, "\n")] = '\0'; // 移除可能的换行符
            }

            if (strncmp(buf, "Pid", 3) == 0)
            {
                pid = strdup(buf + 5);          // 使用 strdup 分配内存并复制 PID
                pid[strcspn(pid, "\n")] = '\0'; // 移除可能的换行符
                break;
            }
        }

        if (name != NULL && pid != NULL)
        {
            // 输出名称和 PID
            printf("%-20s%s\n", name, pid);
            free(name); // 释放分配的内存
            free(pid);
        }

        fclose(file);
    }

    closedir(dir);
    return 0;
}