#include "keyrequest/ctrl.h"
#include "ros/ros.h"
void ctrlCallback(const keyrequest::ctrl::ConstPtr &msg)
{
    ROS_INFO("Recieve Cmd = [%c] [%s]", char(msg->cmd), msg->move.c_str());
}
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "keyrecieve_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("ctrlcmd", 1, ctrlCallback);
    ros::spin();
    return 0;
}
