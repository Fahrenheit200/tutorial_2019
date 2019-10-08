## 基础考核 - 第三周（9.30-10.7）

-作者: 李泓舟

-修订: 李泓舟

-日期: 2019.10.7

-版本: v3.0.0

-摘要: ROS基础操作



#### 编译运行示例

$ cd test_project

$ catkin_make

$ source devel/setup.bash

$ roslaunch test_pkg talker_listener.launch

$ roslaunch test_pkg judge.launch





#### 运行结果:

talker_listener.launch:

[ INFO] [1570454952.523883989]: I heard: [2]

[ INFO] [1570454952.623787143]: I heard: [3]

[ INFO] [1570454952.722814693]: I heard: [4]

[ INFO] [1570454952.823389902]: I heard: [5]

[ INFO] [1570454952.923396346]: I heard: [6]

[ INFO] [1570454953.023611233]: I heard: [7]

[ INFO] [1570454953.123238913]: I heard: [8]

[ INFO] [1570454953.222818695]: I heard: [9]

[ INFO] [1570454953.323672014]: I heard: [10]



judge.launch:

0.655

No

0.956

No

0.14

Yes

0.26

Yes

0.954

No

0.221