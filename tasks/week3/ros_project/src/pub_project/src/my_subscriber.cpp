#include <ros/ros.h>

#include "pub_project/my_pub.h"



// 接收到订阅的消息后，会进入消息回调函数

void myInfoCallback(const pub_project::my_pub::ConstPtr& msg)

{

    // 将接收到的消息打印出来

    ROS_INFO("Subcribe Person Info: name:%s  score:%d  ", 
			 msg->name.c_str(), msg->score);

}



int main(int argc, char **argv)

{

    // 初始化ROS节点

    ros::init(argc, argv, "my_subscriber");



    // 创建节点句柄

    ros::NodeHandle n;



    // 创建一个Subscriber，订阅名为/person_info的topic，注册回调函数personInfoCallback

    ros::Subscriber my_info_sub = n.subscribe("/my_info", 10, myInfoCallback);



    // 循环等待回调函数

    ros::spin();



    return 0;

}
