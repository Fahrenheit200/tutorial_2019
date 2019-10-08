#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Char.h>
#include <cstring>

int main(int argc, char** argv){
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::Char>("ctrl_car_info", 1);
    ros::Duration(0.5).sleep();
    std_msgs::Char msg;
    msg.data = argv[1][0];
    ros::Rate loop_rate(10);
    pub.publish(msg); 
    loop_rate.sleep();
    
    return 0;
}

