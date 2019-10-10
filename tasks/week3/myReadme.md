# Task：Ros 的各种任务

## Head Message

- Author: 王广烁

- Revised: 王广烁

- Date: 2019年10月6日

- Version: 1.0.0

- Abstract: 完成了部分第三周ros操作系统相关的任务

- Achievement: 完成了Publisher与Subscriber通信，在通信中使用自己的msgs，编写launch文件来启动节点，完成Service与Client通信，完成动态参数服务器


##Notice

- 关于不能完成大部分任务：国庆除了本项目之后还有许多堆积起来的任务（上周因为opencv而落下的），又因为其他的事情而花去许多时间，所以学习时间一共只有四天，所以花了一天来入门ros，花了两天来调了很多参数来做题（后面两个大题做了一些但是没有成功所以选择放弃）。然后还有一天拿来学习主科了...虽然很想完成任务但是还是很无奈啊


##What I did in each file
- my_server：输出一个随机数，同时判断是否小于0.5，如果小于0.5则回应“Yes”，否则回应“No”
- pub_sub：使用了自己的msgs，实现了publisher与subscriber的通信
- dynamic_tutorials：设置了数字的范围，并且动态修改之后可以在终端反馈新信息（反馈最大值与最小值）
- my_launch: 对于上述的三个文件都编写了launch文件


##Where I put my files

- 添加的文件：myReadme.md 与一个 Project3文件夹

- "完成了Publisher与Subscriber通信，在通信中使用自己的msgs"的任务在"Project3/src/pub_project"这个包中

- "编写launch文件来启动节点"的任务在"Project3/src/my_launch"这个包中

- "完成Service与Client通信"的任务在"Project3/src/my_service"这个包中

- "完成动态参数服务器"的任务在"Project3/src/dynamic_tutorials"这个包中


## Compiling Method

- 进入Project3的文件后，右键“在终端打开”，之后点击在终端输入“catkin_make”,之后再输入"roslaunch my_launch my_service"来运行service与client通信
- 或者进入Project3的文件后，右键“在终端打开”，之后点击在终端输入“catkin_make”,输入"roslaunch my_launch pub_sub"来运行publisher与subscriber通信

- 命令行输入如下

		$ catkin_make

		$ source devel/setup.bash

		$ roslaunch my_launch my_service.launch
		//或者 $ roslaunch my_launch pub_sub.launch
		//或者 $ roslaunch my_launch dynamic.launch


	









