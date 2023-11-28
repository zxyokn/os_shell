- 已完成
  - 基础框架搭建
  - 已完成 help，ls，exit，cp，cd函数功能
  - mv 移动文件
  - rm 删除文件
  - pwd 显示工作目录
  - history 显示历史
  - tree 树状
  - ps 显示进程信息
  - 输入输出重定向
- 未完成
  - 管道
  - 后台运行程序 &
- 待完善
  - ls 功能的补充 如ls -l
  - help 支持函数的个数
  - rm 文件夹代码完善
  - 代码健壮性
  - 颜色
  - tree 好像文件夹后面多一个换行？  路径问题
  - 在help中添加重定向的说明


- 编译命令
  - 修改后先保存在编译
  - ```g++ main.cpp -I ./function function/*.cpp```
  - ```./a.out```
- 如何添加函数
  - 1. 在shell.h文件中修改line 35 ```static char supported_function[10][50] =```中的第一个数字，该数字代表所支持函数的总数
  - 2. 在supported_function中添加"指令名字"
  - 3. 在shell.h中line 41所添加函数的地址，即&函数名字（本shell中均为指令名字的大写，便于区分）
  - 4. 在shell.h中的function_description中添加函数的说明
  - 5. 上述均修改结束后，在shell.h添加```extern int 函数名(char **args)```
  - 6. 在function文件夹下添加对应cpp文件，在首行添加```#include "../shell.h"```

- 注意
  - ps指令是通过遍历/proc文件夹实现的指令，因为macos不支持打开proc文件夹，会导致无法运行，需要linux环境运行该指令

