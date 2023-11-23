#include "../shell.h"

bool cmp(string s1, string s2);

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

// 用于ls的排序
bool cmp(string s1, string s2)
{
    return s1 < s2;
}