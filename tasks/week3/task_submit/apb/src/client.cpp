#include "ros/ros.h"
#include "apb/abs.h"
#include <cstdlib>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "APBClient");
	if (argc != 3)
	{
		ROS_INFO("usage: APBClient X Y");
		return 1;
	}
	ros::NodeHandle nh;
	ros::ServiceClient client = nh.serviceClient<apb::abs>("add_two_ints");
	apb::abs srv;
	srv.request.a = atoll(argv[1]);
	srv.request.b = atoll(argv[2]);
	if (client.call(srv))
	{
		ROS_INFO("Sum: %ld", (long int)srv.response.sum);
	}
	else
	{
		ROS_ERROR("Failed to call service add_two_ints");
		return 1;
	}
	return 0;
}
