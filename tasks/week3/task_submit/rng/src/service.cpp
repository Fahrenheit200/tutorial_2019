#include "ros/ros.h"
#include "rng/rng.h"
#include "rng/rng_paramsConfig.h"
#include "dynamic_reconfigure/server.h"

void callback(rng::rng_paramsConfig &config, uint32_t level)
{
	ROS_INFO("Reconfigure: [%lf, %lf]", config.uniform_min, config.uniform_max);
	//ros::NodeHandle nh;
	//nh.setParam("uniform_min", config.uniform_min);
	//nh.setParam("uniform_max", config.uniform_max);
}
bool deter(rng::rng::Request& req, rng::rng::Response& res)
{
	res.det = (req.rn < 0.5 ? 1 : 0);
	return true;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "RNGServer");
	ros::NodeHandle nh;
	double umin, umax;
	dynamic_reconfigure::Server<rng::rng_paramsConfig> dserver;
	dynamic_reconfigure::Server<rng::rng_paramsConfig>::CallbackType f;
	//nh.param<double>("uniform_min", umin, 0.0);
	//nh.param<double>("uniform_max", umax, 1.0);
	f = boost::bind(&callback, _1, _2);
	dserver.setCallback(f);

	ros::ServiceServer server = nh.advertiseService("examine_rn", deter);
	ROS_INFO("Ready to examine the random numbers.");
	ros::spin();
	return 0;
}
