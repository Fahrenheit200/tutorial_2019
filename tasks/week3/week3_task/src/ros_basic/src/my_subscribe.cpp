#include<ros/ros.h>
#include"ros_basic/my_msg.h"

void infoCallBack(const ros_basic::my_msg::ConstPtr& msg)
{
	ROS_INFO("subscribe info:name:%s age:%d",msg->name.c_str(),msg->age);
}

int main(int argc,char** argv)
{
	ros::init(argc,argv,"my_subscribe");
	ros::NodeHandle n;

	ros::Subscriber info_sub=n.subscribe("/my_msg_info",10,infoCallBack);

	ros::spin();

	return 0;

}
