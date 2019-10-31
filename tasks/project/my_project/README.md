# 项目：编程技术方向
- *Author: 张定暄*
##  读者写者问题
- **工程结构**
![png1](https://github.com/sysu-zdx/tutorial_2019/blob/张定暄/tasks/project/my_project/pic/1.png)
  - src存放.cpp文件，bin存放可执行文件，include存放头文件，TEST_FILES存放测试文件(已放入五个测试文件，以abcde编号，不会和考核时的测试文件重名）
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
1.在my_project目录下执行make命令，生成的可执行文件存放于my_project/bin目录下
2.在my_project/bin目录下执行如下命令：
``` 
./reader.out [path/testfile_name]
```
如：要使用my_project/TEST_FILES下的test1.txt测试文件，执行：
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
	
		
