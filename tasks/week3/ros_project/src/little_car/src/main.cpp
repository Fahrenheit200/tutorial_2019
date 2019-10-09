#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include "little_car/carmsg.h"
using namespace std;
float vec=0.000;
float yaw_=0;
void Callback(const little_car::carmsg::ConstPtr& msg)
{

   vec=msg->v;
   yaw_=msg->yaw;
   printf("callb: %f %f\n",vec,yaw_);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	small_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
	ros::Subscriber sub = n.subscribe("velocity",10,Callback);

	/*
	 *若有需要，也可以从小车处发布你所需要的信息
	 */
    ros::Rate loop_rate(60);
	//SVector3 velocity={0,0.002,0};  //速度向量
	car.set_noise_level(0);		   //设置噪声等级
/*	double error_p_x=0;
	double error_i_x=0;
	double error_d_x=0;
	double error_dp_x=0;
	double target_x=0;
	double error_p_y=0;
	double error_i_y=0;
	double error_d_y=0;
	double error_dp_y=0;
	double target_y=vec;
	//float yaw = 0.0;*/
    while (ros::ok()) {
	//	yaw += 0.002;
	/*	SVector3 vec_ = car.get_velocity();
		error_p_x= target_x-vec_.x;
		error_i_x += error_p_x;
		error_d_x = error_p_x-error_dp_x;
		error_dp_x = error_p_x;
		target_x += 0.004*error_p_x+0.000001*error_i_x+1*error_d_x;

		error_p_y= target_y-vec_.y;
		error_i_y += error_p_y;
		error_d_y = error_p_y-error_dp_y;
		error_dp_y = error_p_y;
		target_y += 0.0000004*error_p_y+0.0000001*error_i_y+0.000000003*error_d_y;
	*/
		ros::spinOnce();
		car.set_yaw(yaw_); 		   //修改小车的方向
		car.set_velocity({0,vec,0});
        car.update_();//小车状态更新
		loop_rate.sleep();
    }


    return 0;
}

