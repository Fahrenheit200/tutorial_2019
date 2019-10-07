/**
 *该例程将订阅turtle1/pose话题，消息类型turtlesim::Pose
 */

#include<ros/ros.h>
#include"data_pkg/data.h"

//接受到订阅的消息后，会进入消息回调函数
void dataCallback(const data_pkg::data::ConstPtr& msg)
{
	//将接受到的消息打印出来
	ROS_INFO("Subcribe data info: fig:%d",msg->fig);
}

int main(int argc,char **argv)
{
	//初始化ROS节点
	ros::init(argc,argv,"dataSub");

	//创建节点句柄
	ros::NodeHandle n;
	
	//创建一个Subscriber,订阅名为/turtle1/pose的topic，注册回调函数poseCallback
	ros::Subscriber data_info_sub = n.subscribe("/data_info",10,dataCallback);

	//循环等待回调函数
	ros::spin();

	return 0;
}
