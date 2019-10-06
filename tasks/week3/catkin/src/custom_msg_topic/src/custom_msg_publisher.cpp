#include <ros/ros.h>
#include "custom_msg_topic/custom_msg.h"
#include <sstream>
int main(int argc, char** argv)
{
    ros::init(argc,argv,"custom_msg_publisher");
    ros::NodeHandle n;
    ros::Publisher custom_msg_pub = n.advertise<custom_msg_topic::custom_msg>("randowm_number",1000);

    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        custom_msg_topic::custom_msg msg;
        msg.a = rand();
	ROS_INFO("publisher number: %d", msg.a);
        custom_msg_pub.publish(msg);
        loop_rate.sleep();
    }   
    return 0;
}
