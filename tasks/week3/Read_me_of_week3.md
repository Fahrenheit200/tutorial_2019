# README of week3
- Author：gear0803(卢知之)
- Revised: gear0803(卢知之)
- Date：2019-10-07
- Version：1.0.0
- Abstract：项目的说明以及本周任务的完成情况

---

##目录
 1. 本次提交的结构
 2. 完成情况的说明


---
###  1. 本次提交的结构
本次只完成了前30分的要求，小车任务基本没做。因此建立了一个和ros_project同级的文件夹：ros_basic来存放这三十分的内容

~/tutorial_2019/tutorial_2019/tasks/week3目录下的结构：
```
 .
├── project_description.md
├── README.md
├── ros_project
│   ├── launch
│   └── src
├── task3_description.md
└── week3_task
    ├── build
    ├── devel
    └── src
```
 
 ./week3_task/src目录下：
```
·
├── CMakeLists.txt -> /opt/ros/melodic/share/catkin/cmake/toplevel.cmake
└── ros_basic
    ├── CMakeLists.txt
    ├── include
    │   └── ros_basic
    ├── launch
    │   ├── pub_sub.launch
    │   └── server_client.launch
    ├── msg
    │   └── my_msg.msg
    ├── package.xml
    ├── src
    │   ├── my_client.cpp
    │   ├── my_publish.cpp
    │   ├── my_server.cpp
    │   └── my_subscribe.cpp
    └── srv
        └── my_srv.srv
```

---
###2.完成情况的说明：
- 1.完成了Publisher和Subscriber通信
- 2.在通信中使用自己的msgs
- 3.编写launch文件启动节点
- 4.完成Server和Client通信  
  
  



####细节说明：
- 1.Publisher和Subscriber通信：因为任务要求里面没说具体内容，我就自定义了一个msgs，里面有两个数据成员name和age，然后Publisher发布信息，Subscriber接受。
- 2.Server和Client通信的时候，为了方便调试，在launch中使用了respawn参数让他们不停地发送接受。但是这样会导致终端疯狂刷新不便观察，就设置了一个小小的延时让他们不要发送接受的那么快。但是还是会出现同一个数据刷出来多次的情况，应该是延时时间不当导致的，但是并不会影响运行，就是显示有点丑...

感想：本周仍然收获颇丰。但是因为上周为了写背景还原器，有点点荒废学业，导致这周不得不抽时间来赶作业，使得任务只完成了一小部分。不过，这也是对我们平衡竞赛和学业的锻炼吧。虽然本周我完成的很糟糕，可能后续希望渺茫，但是我还是想坚持下去，~~搏一搏单车变摩托~~))就算不能成为队员，这一趟也学到了很多东西。
感谢学长们在群上的悉心解答与帮助!!
