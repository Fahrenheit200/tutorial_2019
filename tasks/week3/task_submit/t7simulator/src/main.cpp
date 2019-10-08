#include "ros/ros.h"
#include "mybot_mv.h"
int main(int argc, char** argv)
{
	ros::init(argc, argv, "mybot_mv");
	ros::NodeHandle nh;
	MybotMv bot;
	while (ros::ok())
	{
		bot.update_();
		ros::spinOnce();
	}
}
