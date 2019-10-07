#include "parser.h"
#include <urdf/model.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Point.h>
#include <ros/ros.h>
#include "little_car/myfloat32.h"
#include <random>
#include <iomanip>
using namespace std;

littlecar car;//初始化控制对象  小车
//car.set_noise_level(0);        //设置噪声等级


 //回调函数，该结点每收到一条消息时都将调用该函数
 void chatterCallback(const little_car::myfloat32::ConstPtr& msg)
{
		SVector3 velocity={msg->x, 0.004, 0};  //速度向量
		car.set_velocity(velocity);//设置小车速度
		car.update_();//小车状态更新
		
 
}
int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
//	car.set_noise_level(0);        //设置噪声等级
     car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
 	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
	/* 
	 *请添加一个Subscriber，从你自己编写的Publisher处订阅指令
	 */
	ros::Subscriber sub = n.subscribe("v", 100, chatterCallback);
	ros::spin();
    return 0;
}

