#include "ros/ros.h"
#include "pub_sub_test/my_msg.h" 

void messageCallback(const pub_sub_test::my_msg::ConstPtr& msg)
{
    ROS_INFO("I heard: A=%d,B=%d,C=%d sum=[%d]",msg->A,msg->B,msg->C,msg->A+msg->B+msg->C);
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"sub_node");
    ros::NodeHandle n;
    ros::Subscriber sub=n.subscribe("add_num_msg",10,messageCallback);
    ros::spin();
    return 0;
}
