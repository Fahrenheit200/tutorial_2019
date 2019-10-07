#include "ros/ros.h"
#include "test_msgs/Test.h"
#include<cstdlib>
#include<ctime>

int main(int argc,char **argv)
{
	ros::init(argc,argv,"talker");
	ros::NodeHandle n;
	ros::Publisher chatter_pub=n.advertise<test_msgs::Test>("chatter",1000);
	ros::Rate loop_rate(1);
	
	while(ros::ok())
	{
		srand(time(NULL));
		test_msgs::Test msg;
		msg.num=rand()%101;
		std::cout<<msg.num<<std::endl;
		chatter_pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
