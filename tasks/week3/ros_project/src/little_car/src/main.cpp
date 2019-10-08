#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <thread>
#include <std_msgs/Char.h>
#include <cmath>
#include <chrono>

#define MAX_VEL 0.008
#define PI 3.14159265358979323846

using namespace std;

SVector3 velocity={0,0,0};  //速度向量
float yaw = 0.0;

void thread1(){
	/* 使用多线程以20Hz的频率控制小车走S型轨迹 */
	float tmp1 = velocity.x, tmp2 = velocity.y;
	yaw += PI / 2;
	std::this_thread::sleep_for(chrono::milliseconds(50));
	for(int i=0; i<100; i++){
		yaw -= PI / 100;
		velocity.x = MAX_VEL * -1 * sin(yaw);
		velocity.y = MAX_VEL * cos(yaw);
		std::this_thread::sleep_for(chrono::milliseconds(50));
	}
	for(int i=0; i<100; i++){
		yaw += PI / 100;
		velocity.x = MAX_VEL * -1 * sin(yaw);
		velocity.y = MAX_VEL * cos(yaw);
		std::this_thread::sleep_for(chrono::milliseconds(50));
	}
	yaw -= PI / 2;
	velocity.x = tmp1;
	velocity.y = tmp2;
}

/* server接受到信息的响应函数 */
void infoCallback(const std_msgs::Char msg){
    if(msg.data == 'd'){
		velocity.x = 0;
		velocity.y = 0;
		ROS_INFO("don't move");
	}else if(msg.data == 'l'){
		yaw += PI /2;
		float v = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		velocity.x = v * -1 * sin(yaw);
		velocity.y = v * cos(yaw);
		ROS_INFO("turn left");
	}else if(msg.data == 'r'){
		yaw -= PI /2;
		float v = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
		velocity.x = v * -1 * sin(yaw);
		velocity.y = v * cos(yaw);
		ROS_INFO("turn right");
	}else if(msg.data == 'g'){
		velocity.x = MAX_VEL * -1 * sin(yaw);
		velocity.y = MAX_VEL * cos(yaw);
		ROS_INFO("move forward");
	}else if(msg.data == 's'){
		thread task1(thread1);
		task1.detach();
		ROS_INFO("S-shaped trajectory");
	}
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	ros::Subscriber sub = n.subscribe<std_msgs::Char>("ctrl_car_info", 1, &infoCallback); //接受控制小车的消息

    ros::Rate loop_rate(60);
	car.set_noise_level(0);		   //设置噪声等级

    while (ros::ok()) {
		car.set_yaw(yaw); 		   //修改小车的方向
		car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
		ros::spinOnce();
		loop_rate.sleep();
    }

    return 0;
}

