#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <sstream>
#include <random>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "publish");
	ros::NodeHandle n;
	ros::Publisher random_number_pub = n.advertise<std_msgs::Float64>("RandomNumber", 1000);
	ros::Rate loop_rate(5);
	long long count = 0;
	double random_number;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<double> urb(0, 1);
	while (ros::ok())
	{
		random_number = urb(rng);
		std_msgs::Float64 msg;
		msg.data = random_number;
		random_number_pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
		++count;
	}
	return 0;
}

