#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include "std_msgs/Char.h"
#include <ros/ros.h>
#include <random>
#include <iomanip>
using namespace std;

SVector3 velocity;  //速度向量

void Callback(const std_msgs::Char& msg)
{
	ROS_INFO("vel1:%f,%f,%f",velocity.x,velocity.y,velocity.z);
	if(msg.data=='f')//小车向前
	{
		velocity.x=0.008;
		velocity.y=0;
		velocity.z=0;
	}
	if(msg.data=='l')//小车向左
	{
		velocity.x=0;
		velocity.y=-0.008;
		velocity.z=0;
	}
	if(msg.data=='b')//小车向后
	{
		velocity.x=-0.008;
		velocity.y=0;
		velocity.z=0;
	}
	if(msg.data=='r')//小车向右
	{
		velocity.x=0;
		velocity.y=0.008;
		velocity.z=0;
	}
	return;
}

int main(int argc, char** argv) {
    	ros::init(argc, argv, "state_publisher");
	ros::NodeHandle n;
	little_car car;//初始化控制对象:小车
	car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);//小车的位置消息发布
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1);

	ros::Subscriber sub;
	//定义发送消息的频率
    	ros::Rate loop_rate(60);
	sub=n.subscribe("car_ctrl",1000,&Callback);
	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0.0;
    	while (ros::ok()) {
	//	yaw += 0.01;
	//	car.set_yaw(yaw);
		
		ROS_INFO("vel2:%f,%f,%f",velocity.x,velocity.y,velocity.z);
		car.set_velocity(velocity);//设置小车速度
        	car.update_();//小车状态更新
        	ros::spinOnce();
		loop_rate.sleep();
    }
    return 0;
}

