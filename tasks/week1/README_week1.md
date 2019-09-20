# 第一周任务完成说明
- 作者：方至钰
- 修订：方至钰
- 日期：2019-9-20
- 版本：1.0.0 
- 摘要：这是方至钰完成的空队考核第一周任务的说明，包括helloworld程序的编译执行过程、程序设计能力练习题——最大公共后缀的说明。

***
## helloworld工程的编译和执行
### 1. 创建新的源文件：在ubuntu的终端中输入命令`vim helloworld.cpp`
### 2. 进入vim并编辑helloworld代码，编辑完后按`esc`，输入`:wq`保存退出
### 3. 用g++编译: 
+ 输入命令`g++ -E helloworld.cpp > helloworld.i`可进行预处理，并将`helloworld.i`文件重定向到当前文件夹
+ 输入命令`g++ -S helloworld.i`将预处理的文件转变为汇编语言，产生`helloworld.s`文件
+ 输入命令`g++ -c helloworld.s`将汇编语言的文件转变为目标代码（机器语言），产生`helloworld.o`文件     
+ 输入命令`g++ helloworld.o -o helloworld.out`连接目标代码，产生`helloworld.out`可执行文件
+ 输入命令`./helloworld.out`运行`helloworld.out`，终端就会显示一行`Hello World`

+ 也可以通过更简单的命令直接编译产生可执行文件：输入命令`g++ helloworld.cpp -o helloworld.out`编译并连接，产生`helloworld.out`可执行文件

***
## 程序设计能力练习题：最大公共后缀
### Functions:
	string longestCommon(vector<string>& strs);
### Interfaces:
	string longestCommon(vector<string>& strs){
    //...
    }
### Depend Libraries:
+ `#include <vector>`
+ `#include <string>`
+ `#include <algorithm>`
