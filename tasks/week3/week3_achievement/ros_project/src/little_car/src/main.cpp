#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <cmath>
#define PI 3.1415926535

using namespace std;


int main(int argc, char** argv) {
    	ros::init(argc, argv, "state_publisher");
    	ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    	car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	ros::Publisher cmd_pub = n.advertise<geometry_msgs::Point>("vel_cmd",1);
	geometry_msgs::Point cmd;
    	ros::Rate loop_rate(60);
	SVector3 velocity = {0,0,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0.0;
	float degree = 0.0;
    	while (ros::ok()) {
		cmd.x = 0.05*cos(degree);
		cmd.y = 0.05;
		cmd.z = 0.0;
		degree+=0.05;
		cmd_pub.publish(cmd);
		velocity.x = cmd.x;
		velocity.y = cmd.y;
		velocity.z = cmd.z;
		car.set_velocity(velocity);//设置小车速度
        	car.update_();//小车状态更新/
		loop_rate.sleep();
    }

    return 0;
}


