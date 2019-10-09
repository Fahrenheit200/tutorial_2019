#include <ros/ros.h>
#include "little_car/carmsg.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "car_msg_pulibsher");
    ros::NodeHandle n;
    ros::Publisher car_msg_pub = n.advertise<little_car::carmsg>("velocity",10);
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        little_car::carmsg msg;
        msg.v=0.004;
        msg.yaw=0.005;
        ROS_INFO("car_velocity: %f car_yaw: %f", msg.v, msg.yaw);
        car_msg_pub.publish(msg);
        loop_rate.sleep();
    }
    return 0;
}