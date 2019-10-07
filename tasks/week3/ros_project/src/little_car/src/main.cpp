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
using namespace std;
SVector3 velocity={0,0,0};  //速度向量
SVector3 pre_vel={0,0,0};
void callback(const geometry_msgs::Point::ConstPtr& vel)
{
    velocity.x = vel->x;
    velocity.y = vel->y;
}
void thread_sub();  //声明多线程函数
int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
	little_car car;//初始化控制对象  小车
    car.joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
	car.pos_pub = n.advertise<geometry_msgs::Point>("car_position",1); //小车的位置消息发布
    ros::Subscriber sub = n.subscribe("v_control",5,callback);

    thread t1(thread_sub); //使用多线程控制小车
    ros::Rate loop_rate(60);

	car.set_noise_level(0);		   //设置噪声等级
	float yaw = 0.0;
    int count=0;
    while (ros::ok()) {
	//	yaw += 0.01;
	//	car.set_yaw(yaw); 		   //修改小车的方向
    //	ros::spinOnce();
    	
        car.set_velocity(velocity);//设置小车速度
        car.update_();//小车状态更新
		loop_rate.sleep();
    }


    return 0;
}
void thread_sub()
{
    ros::spin();
}

