#include "ros/ros.h"
#include <cmath>
#include <geometry_msgs/Point.h>
#define Pi 3.1415926
int main(int argc,char **argv)
{
    ros::init(argc,argv,"contorler");
    ros::NodeHandle n;
    ros::Publisher control_pub = n.advertise<geometry_msgs::Point>("v_control",1);
    ros::Rate loop_rate(20);
    int count = 0;
    while(ros::ok()){
        geometry_msgs::Point vel;    //小车速度，用来pub
        vel.x = 0.006*cos(Pi/40*count);     //周期为4s
        if(int(count/40)%2==0)   vel.y = 0.006*sin(Pi/40*count);
        else    vel.y = -0.006*sin(Pi/40*count);
        vel.z = 0;
        control_pub.publish(vel);
        ros::spinOnce();
        loop_rate.sleep();
        count++;
    }
    return 0;
}
