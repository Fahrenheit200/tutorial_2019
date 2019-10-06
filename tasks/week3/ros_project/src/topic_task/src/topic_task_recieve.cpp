#include "ros/ros.h"
#include "topic_task/random_msg.h"

void chatterCallback(const topic_task::random_msg::ConstPtr &msg)
{
    ROS_INFO("I heard [%s] send a msg [%d]", msg->name.c_str(),msg->num);
    return;
}
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "topic_task_recieve_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);
    ros::spin();
    return 0;
}