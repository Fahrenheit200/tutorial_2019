## Service

- Author: JiLi Liao
- Revised: JiLi Liao
- Date: 2019-10-06
- Version: 1.0.0
- Abstract: Using service to communicate between client and server.


### How to run
``` shell
$ cd ros_project  # 请先确保工程在catkin workspace下
$ catkin_make  
$ source devel/setup.bash
$ roslaunch service_demo service_demo.launch 
```

### Sample Output
``` shell
[ INFO] [1570199112.830510649]: Client: send random float 0.406280
[ INFO] [1570199112.830580632]: Client: accept response Yes
[ INFO] [1570199113.832676347]: Client: send random float 0.613520
[ INFO] [1570199113.832772376]: Client: accept response No
[ INFO] [1570199116.833520227]: Client: send random float 0.498890
[ INFO] [1570199116.833589790]: Client: accept response Yes
[ INFO] [1570199119.835207963]: Client: send random float 0.543980
[ INFO] [1570199119.835278480]: Client: accept response No
[ INFO] [1570199122.836026553]: Client: send random float 0.568900
[ INFO] [1570199122.836095975]: Client: accept response No

```

### others
package name-----service_demo
自定义srv---------service_demo/srv/float_0to1.srv
launch文件--------service_demo/launch/service_demo.launch
参数服务器---------service_demo/cfg/set_time.cfg，通过rqt_reconfigure界面的滑动条修改client发送消息的时间间隔
