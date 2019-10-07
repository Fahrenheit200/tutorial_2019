#include"ros/ros.h"
#include "test_msgs/Test.h"

void callback(const test_msgs::Test::ConstPtr & msg)
{
	std::cout<<msg->num<<std::endl;
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"listener");
	ros::NodeHandle n;
	ros::Subscriber sub=n.subscribe("chatter",1000,callback);
	ros::spin();
	return 0;
}

