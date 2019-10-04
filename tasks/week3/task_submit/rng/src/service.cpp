#include "ros/ros.h"
#include "rng/rng.h"

bool deter(rng::rng::Request& req, rng::rng::Response& res)
{
	res.det = (req.rn < 0.5 ? 1 : 0);
	return true;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "RNGServer");
	ros::NodeHandle nh;
	ros::ServiceServer server = nh.advertiseService("examine_rn", deter);
	ROS_INFO("Ready to examine the random numbers.");
	ros::spin();
	return 0;
}
