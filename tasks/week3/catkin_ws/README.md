# README of Week3 Task 1-4
- Author:林嘉鸿
- Revised:林嘉鸿
- Date:2019-10-07
- Version:1.0.0
- Abstract:本README为第三周任务1～4的文档说明以及编译方法说明

##任务一：完成Publisher与Subscriber通信
- 所对应的Package：pns
- Package路径：~/catkin_ws/src/pns
- 源代码文件夹：~/catkin_ws/src/pns/src
- 自定义数据类型文件：~/catkin_ws/src/pns/msg/def_message.msg
- launch文件：~/catkin_ws/src/pns/launch/pns.launch
###依赖库
- include "ros/ros.h"
- include <pns/def_message.h>
- include <std_msgs/Int64.h>
###编译方法
$ catkin_make  
$ source ~/tutorial_2019/tasks/week3/catkin_ws/devel/setup.bash  
$ roslaunch pns pns.launch  
###输出示例
[ INFO] [1570429732.448004121]: Send:1714636915,1957747793,424238335  
[ INFO] [1570429732.448566417]: Receive:1714636915,1957747793,424238335  
[ INFO] [1570429733.447521972]: Send:719885386,1649760492,596516649  
[ INFO] [1570429733.449741585]: Receive:719885386,1649760492,596516649  

##任务二：完成Service与Client通信
- 所对应的Package：judge
- Package路径：~/catkin_ws/src/judge
- 源代码文件夹：~/catkin_ws/src/judge/src
- 自定义数据类型文件：~/catkin_ws/src/judge/srv/def_message.srv
- launch文件：~/catkin_ws/src/judge/launch/judge.launch
###依赖库
- include "ros/ros.h"
- include "judge/def_message.h"
- include <std_msgs/Float64.h>
- include <stdlib.h>
###编译方法
$ catkin_make  
$ source ~/tutorial_2019/tasks/week3/catkin_ws/devel/setup.bash  
$ roslaunch judge judge.launch  
###输出示例
[ INFO] [1570430042.363049493]: Send:0.793000  
[ INFO] [1570430042.364698849]: Receive:0.793000  
[ INFO] [1570430042.364776576]: Answer:0  
[ INFO] [1570430042.364970784]: No  
[ INFO] [1570430043.362956940]: Send:0.335000  
[ INFO] [1570430043.364522693]: Receive:0.335000   
[ INFO] [1570430043.364588679]: Answer:1  
[ INFO] [1570430043.364753333]: Yes  

##任务三：完成动态参数服务器
- 所对应的Package：dynamic
- Package路径：~/catkin_ws/src/dynamic
- 源代码文件夹：~/catkin_ws/src/dynamic/src
- 脚本文件：~/catkin_ws/src/dynamic/cfg/dy.cfg
- launch文件：~/catkin_ws/src/dynamic/launch/dynamic.launch
###依赖库
- include <ros/ros.h>
- include <dynamic_reconfigure/server.h>
- include <dynamic/dyConfig.h>
###编译方法
$ catkin_make  
$ source ~/tutorial_2019/tasks/week3/catkin_ws/devel/setup.bash  
$ roslaunch dynamic dynamic.launch  
###输出示例
[ INFO] [1570430328.505861473]: Receive:0.820000
[ INFO] [1570430328.505959805]: No
[ INFO] [1570430329.489330805]: Receive:0.200000
[ INFO] [1570430329.489387800]: Yes


