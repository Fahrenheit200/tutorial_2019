# README of Week3 Task ros_project
- Author:林嘉鸿
- Revised:林嘉鸿
- Date:2019-10-07
- Version:1.0.0
- Abstract:本README为第三周任务5的文档说明以及编译方法说明,本项目中实现了在无噪声的情况下，创建一个新的包使用Publisher发布控制指令来控制小车实现转弯动作。

### 依赖库
- include "ros/ros.h"
- include "std_msgs/Char.h"
- include <std_msgs/Int64.h>
- include "parser.h"
- include <urdf/model.h>
- include <string>
- include <sensor_msgs/JointState.h>
- include <tf/transform_broadcaster.h>
- include <geometry_msgs/Point.h>
- include <random>
- include <iomanip>

### 编译方法
$ catkin_make  
$ source ~/tutorial_2019/tasks/week3/ros_project/devel/setup.bash  
$ roslaunch ~/tutorial_2019/tasks/week3/ros_project/launch/little_car.launch  
$ rosrun publisher car_publisher (在另一个终端中运行,新终端需要先source)  

### 运行结果
运行第三行命令打开Rviz后，小车一开始会静止在中心点不移动;然后启动publisher，小车会在publisher的指令实现转弯动作。
