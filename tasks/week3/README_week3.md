# 第二周任务完成说明
- 作者：方至钰
- 修订：方至钰
- 日期：2019-10-7
- 版本：1.0.0 
- 摘要：这是方至钰完成的空队考核第三周任务的说明，主要是基于ros的一些任务，包括消息的发布和订阅节点、服务器和客户端、动态参数服务器、以及为以上几个工程写launch文件。另外，还尝试完成通过publisher控制小车走S型路线。

***
## 一、pub&sub
### 1. 模块功能
+ 信息发布节点`publisher`产生随机数据并发布，使用自己创建的自定义消息类型，信息订阅节点`subscriber`订阅话题并将数据输出到终端。
### 2. 依赖库
+ -依赖ros
### 3. 编译、测试提示
+ `$ cd tutorial_2019/tasks/week3/catkin_ws`
+ `$ catkin_make`
+ `$ source devel/setup.bash`
+ `$ roslaunch pub_sub pub_sub.launch`

***
## 二、srv&cli、动态参数服务器dynamic_param_server
### 1. 模块功能
+ `client` 产生一个 0 到 1 内的随机浮点数，然后发给 `server`，`server` 接受到请求后，判断随机数是否小于 0.5，若是则回应布尔值 1，否则回应 0。`client` 接收到回应后，先输出产生的随机数，然后输出 `Yes` 或 `No` 到终端。
+ `dynamic_param_server` 可以调整产生的随机数范围和非零小数位数。
### 2. 依赖库
+ -依赖ros
### 3. 编译、测试提示
+ `$ cd tutorial_2019/tasks/week3/catkin_ws`
+ `$ catkin_make`
+ `$ source devel/setup.bash`
+ `$ roslaunch srv_cli srv_cli.launch`


***
## 三、通过pub_v控制小车走S型路线
### 1. 模块功能
+ 使用 `pub_v` 来发布指令来控制小车的方向和速度，实现小车走S型路线。
### 2. 依赖库
+ -依赖ros
### 3. 编译、测试提示
+ `$ cd tutorial_2019/tasks/week3/ros_project`
+ `$ catkin_make`
+ `$ source devel/setup.bash`
+ `$ roslaunch launch/little_car.launch`

