#include "ros/ros.h"
#include "custom_msg_topic/custom_msg.h"
void infoCallback(const custom_msg_topic::custom_msgConstPtr &msg)
{
    ROS_INFO("HEY:[%d]", msg->a);
}
int main(int argc, char** argv)
{   
    ros::init(argc,argv,"custom_msg_subscriber");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("random_number",1000,infoCallback);
    ros::spin();
    return 0;

}
