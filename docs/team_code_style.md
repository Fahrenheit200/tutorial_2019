## 空中机器人团队代码规范
- **作者**：寅一
- **修订**：张昊
- **日期**：2019-09-13
- **版本**：1.1.0
- **摘要**：这是空中机器人团队的代码规范，包含这么写代码及其注释、readme、测试程序、文件结构，git上怎么写comment和wiki、什么情况下可以commit、什么情况下建分支和merge。

---
### 零、为什么会有代码规范
在团队协作中，有很多个同学一起完成一个项目，良好的代码结构和代码规范能让团队协作更有效
```
在文件project_main.h中
class Project
{

}；
void getFileName();
float person_id;
#define _FOO_H_
const float E = 2.71
```
从上面的代码中，通过命名我们能看出来，Project是一个类，getFileName是一个函数，person_id是一个变量,E是一个常量，仅仅通过命名我们就可以很好的区分各种不同类型。
- 这里的class我们采用单词拼接的形式，每个单词的首字母大写。
- 函数也采用单词拼接的形式，第一个单词首字母小写，之后的单词首字母小写
- 变量采用单词_单词的格式，每个单词小写，采用下划线连接
- 常量使用const来定义，并且单词完全大写
- 宏定义保护使用 _PROJECT_MODULE_H_ 的形式来写
```
#ifndef _PROJECT_MODULE_H_
#define _PROJECT_MODULE_H_
...
#endif
```


### 一、如何写好一份文档
（1）**前言**：代码可以不会写，但是人话一定要会说。在大家看懂你写的bug之前，请先学会写好一份`人类可以正常快速看懂`的README。中英文都可以（吉祥物喜欢用英文）。在今后的团队中协作中，有一份良好的代码规范会帮助我们节约大量的沟通时间。
（2）**表头信息**：表头信息非常重要，包含*这个坑是谁最先挖的（作者/Author）*、*最后一位添加bug的人（修订/Revised）*、*最后一次修改的日期（日期/Date）*、*最新的更改（版本/Version）*、*展示一下您最新添加的bug（摘要/Abstract）*。

```md
## Title Here: Readme Tutorial
- Author: Champion-Liu
- Revised: Champion-Liu
- Date: 2018-09-13
- Version: 1.0.0
- Abstract: Hello, this is the readme tutorial about how to show out your bug.
```

（3）**说明内容**：包括模块怎么的功能是什么、接口是什么、需要哪些依赖库、怎么编译、测试程序怎么运行，如果没有的话统统不准git commit到master分支上。

```md
### Functions:
	... //Brief is okay
### Interfaces:
	... //C++ style declaration
### Depend Libraries:
	... //should include origin websites
```
（4）切记文档是用来看的！文档是用来看的！文档是用来看的！重点是简单清晰的说明代码用途。
接口示例：

```cpp
/// Initialize the module
static bool Hello::init();
/// Quit the module
static void Hello::quit();
```

依赖库示例：

```md
常见的库，不需要说明安装方式
依赖opencv
依赖pthread
不常见的库，一定要说明安装方式
依赖zbar
安装方式：
。。。。。。
```

编译提示：

```md
mkdir build
cd build
cmake .. -DGPU
make -j16
```

测试程序：

```md
# how to run:
cd bin
./hello_test

# the result if it is running well:
>>> hello
```

---

### 二、如何写好代码及其注释
（1）**前言**：doxygen是一款可以把注释转换为文档的工具，效果的话可以看下[opencv文档](http://docs.opencv.org/3.4.3/)。  
（2）**代码风格**：头文件使用`*.hpp`，源文件使用`*.cpp`；  
（3）**注释风格**：[可以看一下这里](https://blog.csdn.net/wenrenhua08/article/details/39591239)。  

---

### 三、项目的结构是怎么样的
对于独立的模块：

```
DigitsMerger(项目名)
|- inc/ (模块头文件)
|- src/ (模块源文件)
|- bin/ (编译后的模块测试执行文件)
|- test/ (模块测试的源文件)
|- readme.md (说明文档)
|- CMakeLists.txt (既作为项目子模块编译文件，又作为模块测试文件主编译文件)
```

---

### 四、如何与队友愉快地使用git
(1) **如何commit**: 编译通过而且文档写完才可以到master分支。  
(2) **如何merge**：使用GitKraken。  
(3) **什么时候需要新分支**：你自己挖坑的时候。  
(4) **Wiki怎么写**：参照tutorial_2018的wiki。

---

### 五、吉祥物御用的基础模块
+ 官方指定类：

```cpp
class Publisher; //!< 信息共享
class SRobot;		//!< 实用类型  
```

+ 官方指定多线程写法：

```cpp
#include <atomic>
#include <thread>
#include <mutex>

std::thread thr;

... //TODO: 而不是使用pthread
```
