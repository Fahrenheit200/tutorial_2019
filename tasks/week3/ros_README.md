## 表头信息

- 作者: 雷发兴
- 修订: 雷发兴
- 日期: 2019年09月28日
- 版本: 1.0.0
- 摘要: 完成Publisher与Subscriber通信，在通信中使用自己的msgs，编写launch文件来启动节点

##说明内容
###完成情况
只完成了任务表中的以下任务：
- 完成Publisher与Subscriber通信
- 在通信中使用自己的msgs
- 编写launch文件来启动节点
- 完成Service与Client通信
- 完成动态参数服务器
- 实现通过Publisher控制小车运动
- 使用多线程以20Hz的频率控制小车

###文件说明
1. 工作空间文件命名为 "catkin_ws"，生成的package命名为 “week3_tutorial”。
2. 实现Publisher与Subscriber通信的两个cpp文件分别命名为“Publisher.cpp”和“Subscriber.cpp”，通信中自己定义的msgs文件命名为“myName.msg”，用于启动节点的launch文件命名为“tutorial.launch”。
3. 实现Service与Client通信判断随机浮点数的两个cpp文件分别命名为“random_float_server.cpp”和“random_float_client.cpp”，为动态参数服务器而自定义的srv文件命名为“random_float.srv”，用于启动server节点和可视化窗口的launch文件命名为“dynamic_rand_float.launch”
4. 动态参数服务器实现的是调整生成的随机浮点数的范围，默认生成范围是0-1，通过服务器可在0-1到0-10之间调整
5. 通过Publisher使小车转弯对应的publisher文件命名为“turn_publisher.cpp”，保存在ros_project工程的little_car包的src文件中

## 任务1：完成Publisher与Subscriber通信，在通信中使用自己的msgs，编写launch文件来启动节点
###编译与运行提示
先在终端中将文件目录转到 `catkin_ws`文件夹下，运行以下指令
参考命令行如下：
```shell
$ cd catkin_ws  # 请先确保工程在catkin workspace下
$ catkin_make
$ source devel/setup.bash
$ roslaunch week3_tutorial tutorial.launch
```
如果指令“$ roslaunch week3_tutorial tutorial.launch”报错，请重新开一个终端，再输入一次这个指令

## 任务2：完成Service与Client通信，完成动态参数服务器
###编译与运行提示
先在终端中将文件目录转到 `catkin_ws`文件夹下，运行以下指令
参考命令行如下：
```shell
$ cd catkin_ws  # 请先确保工程在catkin workspace下
$ catkin_make
$ source devel/setup.bash
$ roslaunch week3_tutorial dynamic_rand_float.launch
```
此时动态服务器可视化窗口已打开，重新开一个终端，再输入以下指令运行client节点
参考命令行如下：
```shell
$ rosrun week3_tutorial random_float_client
[ INFO] [1570440526.054739121]: Range of random float numbers: 0 to 1
[ INFO] [1570440526.057969264]: random float number: 0.150900
[ INFO] [1570440526.058033893]: YES

```
你也可以调整参数，不断输入指令“$ rosrun week3_tutorial random_float_client”来查看相应的输出结果

## 任务3：实现通过Publisher控制小车运动，使用多线程以20Hz的频率控制小车
###编译与运行提示
先在终端中将文件目录转到 `ros_project`文件夹下，运行以下指令
参考命令行如下：
```shell
$ cd ros_project  # 请先确保工程在catkin workspace下
$ catkin_make
$ source devel/setup.bash
$  roslaunch ./launch/little_car.launch 
```

























