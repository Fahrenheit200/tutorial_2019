#include "ros/ros.h"
#include "week3_tutorial/myName.h"

//回调函数，该结点每收到一条消息时都将调用该函数，
//该函数将收到的数据在命令行窗口输出
void chatterCallback(const week3_tutorial::myName::ConstPtr& msg)
{
		ROS_INFO("I heard: [%s]", msg->myName.c_str());
}

int main(int argc, char **argv)
{
		ros::init(argc, argv, "Subscriber");
		ros::NodeHandle n;
		ros::Subscriber sub = n.subscribe("message", 1000, chatterCallback);
		ros::spin();
		return 0;
}
