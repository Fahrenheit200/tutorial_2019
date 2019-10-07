#include "ros/ros.h"
#include "apb/ab.h"

void apb_callback(const apb::ab::ConstPtr& msg)
{
	ROS_INFO("%d + %d = %d", msg->a, msg->b, (msg->a + msg->b));
}
int main(int argc, char** argv)
{
	ros::init(argc, argv, "APBSubscriber");
	ros::NodeHandle nh;
	ros::Subscriber sub = nh.subscribe("adder", 1000, apb_callback);
	ros::spin();
	return 0;
}
