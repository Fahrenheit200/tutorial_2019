## Little Car

- Author: JiLi Liao
- Revised: JiLi Liao
- Date: 2019-10-07
- Version: 1.0.0
- Abstract: Using topic to control little car.


### How to run
``` shell
$ cd ros_project  # 请先确保工程在catkin workspace下
$ catkin_make  
$ source devel/setup.bash
$ roslaunch roslaunch launch/little_car.launch
```

### How to control car
``` shell
# 另开一个终端
$ cd ros_project  # 请先确保工程在catkin workspace下
$ source devel/setup.bash
$ rosrun control_car talker g   # 小车前进
$ rosrun control_car talker l   # 小车左转
$ rosrun control_car talker r   # 小车右转
$ rosrun control_car talker d   # 小车原地不动
$ rosrun control_car talker s   # 小车走S型轨迹
```