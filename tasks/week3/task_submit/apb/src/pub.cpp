#include <cstdlib>
#include <ctime>
#include "ros/ros.h"
#include "apb/ab.h"

int main(int argc, char** argv)
{
	srand(time(0));
	ros::init(argc, argv, "APBPublisher");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<apb::ab>("adder", 1000);
	ros::Rate rate(2);
	while (ros::ok())
	{
		apb::ab msg;
		msg.a = rand() % 100; msg.b = rand() % 100;
		ROS_INFO("Data:a:%d  b:%d", msg.a, msg.b);
		pub.publish(msg);
		rate.sleep();
	}
	return 0;
}
