#include "ros/ros.h"
#include "publish_subscribe/random_number_judge.h"
#include <random>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "number_judge_client");

	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<publish_subscribe::random_number_judge>("number_judge");
	publish_subscribe::random_number_judge srv;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<double> urb(0, 1);
	double random_number = urb(rng);

	srv.request.number = random_number;
	if (client.call(srv))
	{
		ROS_INFO("Random Number: %lf", random_number);
		ROS_INFO("Judge: %d", (int)srv.response.status);
	}
	else
	{
		ROS_ERROR("Failed to call service random number judge");
		return 1;
	}

	return 0;
}
