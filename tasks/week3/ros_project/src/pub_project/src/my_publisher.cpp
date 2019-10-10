 

#include <ros/ros.h>
#include<iostream>
#include "pub_project/my_pub.h"
#include <cstdlib>


int main(int argc, char **argv)

{

    // ROS节点初始化

    ros::init(argc, argv, "my_publisher");



    // 创建节点句柄

    ros::NodeHandle n;



    // 创建一个Publisher，发布名为/person_info的topic，消息类型为learning_topic::Person，队列长度10
    ros::Publisher my_info_pub = n.advertise<pub_project::my_pub>("/my_info", 10);



    // 设置循环的频率

    ros::Rate loop_rate(1);



    int count = 0;

    while (ros::ok())

    {

        // 初始化learning_topic::Person类型的消息

    	pub_project::my_pub my_msg;

		my_msg.name = "WangGuangshuo";

		my_msg.score  = rand()%100;




        // 发布消息

		my_info_pub.publish(my_msg);



       	ROS_INFO("Publish My Info: name:%s  score:%d  ", 

				  my_msg.name.c_str(), my_msg.score);



        // 按照循环频率延时

        loop_rate.sleep();

    }



    return 0;

}
