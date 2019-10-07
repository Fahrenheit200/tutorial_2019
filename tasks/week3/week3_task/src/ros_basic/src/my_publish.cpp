#include<ros/ros.h>
#include"ros_basic/my_msg.h"

int main(int argc,char** argv)
{
	ros::init(argc,argv,"my_publisher");

	ros::NodeHandle n;

	ros::Publisher info_pub=n.advertise<ros_basic::my_msg>("/my_msg_info",10);
	ros::Rate loop_rate(10);

	int count=0;
	while(ros::ok())
	{
		ros_basic::my_msg somemsg;
		somemsg.name="blackbox";
		somemsg.age=19;

		info_pub.publish(somemsg);

		loop_rate.sleep();
	
	
	}
	return 0;




}
