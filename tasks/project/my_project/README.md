# 项目：编程技术方向
- *Author: 张定暄*
##  1.读者写者问题
- **工程结构**

![png1](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/1.png)

  - `src`存放`.cpp`文件，`bin`存放可执行文件，`include`存放头文件，`TEST_FILES`存放测试文件(已放入五个测试文件，以abcde编号，不会和考核时的测试文件重名）
- **使用到的头文件**
```javascript
#include<iostream>
#include<thread>
#include<mutex>
#include<fstream>
#include<algorithm>
#include<deque>
#include<sstream>
```
- **运行方法**
1.在`my_project`目录下执行make命令，生成的可执行文件存放于`my_project/bin`目录下

2.在`my_project/bin`目录下执行如下命令：

``` 
./reader.out [path/testfile_name]
```
如：要使用`my_project/TEST_FILES`下的`test1.txt`测试文件，执行：
```
./reader.out ../TEST_FILES/test1.txt
```
- **测试结果截图**
  - testa.txt

![a.input](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/4.png)

![a.output](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/3.png)

  - testb.txt

![b.input](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/5.png)

![b.output](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/6.png)

  - testc.txt

![c.input](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/7.png)

![c.output](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/8.png)

  - testd.txt

![d.input](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/9.png)

![d.output](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/10.png)

- teste.txt

![e.input](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/11.png)

![e.ooutput](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/12.png)

# 2.门电路设计
- *很抱歉因为一些原因没能按时完成这题，所以不做提交，真的很抱歉!*
		
