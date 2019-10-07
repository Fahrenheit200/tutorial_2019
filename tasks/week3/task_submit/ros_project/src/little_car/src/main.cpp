#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include <random>
#include <iomanip>
#include <functional>
using namespace std;
SVector3 velocity;
little_car* car_p;
void controlCallback(const geometry_msgs::Point::ConstPtr& msg)
{
	ROS_INFO("Receive a instruction:(%lf, %lf)", msg->x, msg->y);
	velocity.x = msg->x;
	velocity.y = msg->y;
	car_p->set_velocity(velocity);
	car_p->update_position();
	velocity.x = 0; velocity.y = 0;
	car_p->set_velocity(velocity);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    little_car car;//初始化控制对象  小车
    car_p = &car;
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
    ros::Subscriber sub = n.subscribe("car_control", 4, controlCallback);
    ros::Rate loop_rate(60);
    car.set_noise_level(1);		   //设置噪声等级
    velocity.x = 0; velocity.y = 0; velocity.z = 0;
    car.set_velocity(velocity);
    while (ros::ok()) {
		//yaw += 0.08;
		//car.set_yaw(yaw); 		   //修改小车的方向
		//car.set_velocity(velocity);//设置小车速度
	ros::spinOnce();
	car.set_velocity(velocity);
        car.update_();//小车状态更新
	velocity.x = 0; velocity.y = 0;
	loop_rate.sleep();
    }


    return 0;
}

