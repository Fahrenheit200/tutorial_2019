# 请先确保工程在catkin workspace下

$ catkin_make 

$ source devel/setup.bash

$ roslaunch test_msgs testmsgs.launch

然后会有一个新的终端，加上原来的终端总共两个终端来展示他们的通信内容

通信内容是自定义的消息类型，消息类型是一个数字，该数字是随机产生的

限定随机生成的数字为0-100
