## Topic

- Author: JiLi Liao
- Revised: JiLi Liao
- Date: 2019-10-06
- Version: 1.0.0
- Abstract: Using topic to communicate between talker and listener.


### How to run
``` shell
$ cd ros_project  # 请先确保工程在catkin workspace下
$ catkin_make  
$ source devel/setup.bash
$ roslaunch topic_demo topic_demo.launch
```

### Sample Output
``` shell
[ INFO] [1570196403.611841300]: Listener: get a num 13
[ INFO] [1570196404.611823336]: Listener: get a num 2
[ INFO] [1570196405.611859714]: Listener: get a num 8
[ INFO] [1570196406.611405271]: Listener: get a num 17
[ INFO] [1570196407.611425204]: Listener: get a num 14
[ INFO] [1570196408.612499953]: Listener: get a num 3
[ INFO] [1570196409.611612950]: Listener: get a num 9
```

### others
package name----topic_demo
自定义msg--------topic_demo/msg/rand_int.msg
launch文件-------topic_demo/launch/topic_demo.launch
参数服务器--------topic_demo/cfg/set_max.cfg，通过rqt_reconfigure界面的滑动条修改talker发送随机数的最大值

