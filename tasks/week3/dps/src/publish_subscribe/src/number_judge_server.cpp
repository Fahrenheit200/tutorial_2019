#include "ros/ros.h"
#include "publish_subscribe/random_number_judge.h"

bool judge(publish_subscribe::random_number_judge::Request  &req,
		publish_subscribe::random_number_judge::Response &res)
{
	if (req.number <0.5)
		res.status = true;
	else
		res.status = false;
	return true;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "number_judge_server");
	ros::NodeHandle n;

	ros::ServiceServer service = n.advertiseService("number_judge", judge);
	ros::spin();

	return 0;
}
