#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
geometry_msgs::Point position; //小车的位置信息
geometry_msgs::Point velocity; //小车的速度控制
using namespace std;
//示例函数  使小车前进
//我们希望你能通过这个函数，模仿实现控制小车的速度，运动方向，转弯等动作
int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
    ros::Rate loop_rate(30);
	SVector3 velocity={0,0.05,0};
    while (ros::ok()) {
		car.set_velocity(velocity);
        car.update_();
		loop_rate.sleep();
    }


    return 0;
}

