## Title Here: Readme Tutorial

- Author: 黄浩东
- Revised: 黄浩东
- Date: 2019-10-04
- Version: 1.0.0
- Abstract: 完成Publisher与Subscriber的编写 

### Functions:
	使用自己创建的自定义消息类型，信息订阅节点订阅话题并将数据输出到终端，并编写了ROS launch文件 
### Interfaces:
	Package名称为pub_sub_test
	节点名称为pub与sub 
	
    void messageCallback(const pub_sub_test::my_msg::ConstPtr& msg)
    {
	//输出ABC的和 
        ROS_INFO("I heard: A=%d,B=%d,C=%d sum=[%d]",msg->A,msg->B,msg->C,msg->A+msg->B+msg->C);
    }
    
    其中msg/my_msg内容为： int32 A
	                  int32 B
		          int32 C 
        
### Depend Libraries:
        #include "ros/ros.h"
        #include "pub_sub_test/my_msg.h"

依赖库：
        -依赖ros 
编译提示：
        $ catkin_make //在ros_pubsub目录下 
        $ source devel/setup.bash 
测试程序：
        $ roslaunch pub_sub_test node.launch

