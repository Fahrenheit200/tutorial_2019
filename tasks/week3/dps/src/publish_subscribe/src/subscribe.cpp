#include "ros/ros.h"
#include "std_msgs/Float64.h"

void rnCallback(const std_msgs::Float64::ConstPtr& msg)
{
	ROS_INFO("%lf", msg->data);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "subscribe");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("RandomNumber", 1000, rnCallback);
	ros::spin();
	return 0;
}

